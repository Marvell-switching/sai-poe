/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

#include <string.h>
#include "assert.h"
#include <inttypes.h>

#include <h/poe_v3.h>
#include <SAI/inc/sai.h>
#include <h/utils/dictionary.h>
#include <h/utils/lock.h>
#include <h/utils/log.h>

#define SAI_MAJOR 1
#define SAI_MINOR 14
#define SAI_REVISION 0

#define SAI_VERSION(major, minor, revision) (10000 * (major) + 100 * (minor) + (revision))

#define SAI_API_VERSION SAI_VERSION(SAI_MAJOR, SAI_MINOR, SAI_REVISION)

#undef  __MODULE__
#define __MODULE__ SAI_POE

/* global sai db pointer */
global_poe *g_sai_db_ptr = NULL;
/* lock critical sections when reading/writing */
rwlock_excl_t sai_poe_lock;
/* dictionaries holding poe device/pse/port mappings (sai <-> v3 poe) */
Dictionary *poe_object_device_mapping_ptr = NULL, *poe_object_pse_mapping_ptr = NULL, *poe_object_port_mapping_ptr = NULL;

#define POE_TO_SAI_OBJECT(poe_object_id) (((uint64_t)((poe_object_id)->object_type) << 32) | (poe_object_id)->id)

#define SAI_TO_POE_OBJECT(sai_object_id)    \
    ({                                      \
        poe_object_id_t poe_object_id;      \
        poe_object_id.id = (sai_object_id) & 0xFFFFFFFF; \
        poe_object_id.object_type = (sai_object_type_t)((sai_object_id) >> 32); \
        poe_object_id;                      \
    })

#define POE_TO_SAI_RESULT(poe_result) \
    ((poe_result) == POE_OP_OK_E ? SAI_STATUS_SUCCESS : \
    (poe_result) == POE_OP_FAILED_E ? SAI_STATUS_FAILURE : \
    (poe_result) == POE_OP_NOT_SUPPORTED_E ? SAI_STATUS_NOT_SUPPORTED : \
    SAI_STATUS_FAILURE)

/* v3 conversions to SAI */
/* Convert v3 POE PSE status values to SAI */
sai_poe_pse_status_t convertStatusToSai[]={
    SAI_POE_PSE_STATUS_TYPE_NOT_PRESENT,
    SAI_POE_PSE_STATUS_TYPE_ACTIVE,
    SAI_POE_PSE_STATUS_TYPE_FAIL
};

/* Convert v3 POE active channel values to SAI */
sai_poe_port_active_channel_type_t convertActiveChannelToSai[]={
    0xFF,
    SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_A,
    SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_B,
    SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_A_AND_B
};

/* Convert v3 POE class method values to SAI */
sai_poe_port_class_method_type_t convertClassMethodToSai[]={
    0xFF,
    SAI_POE_PORT_CLASS_METHOD_TYPE_REGULAR,
    SAI_POE_PORT_CLASS_METHOD_TYPE_AUTO_CLASS,
};

/* Convert v3 POE signature type values to SAI */
sai_poe_port_signature_type_t convertSignatureTypeToSai[]={
    0xFF,
    SAI_POE_PORT_SIGNATURE_TYPE_SINGLE,
    SAI_POE_PORT_SIGNATURE_TYPE_DUAL
};

/* Convert v3 POE port detection status values to SAI */
const sai_poe_port_status_t convertPoePortDetectionToSai[] = {
    0xFF,
    SAI_POE_PORT_STATUS_TYPE_OFF,
    SAI_POE_PORT_STATUS_TYPE_SEARCHING,
    SAI_POE_PORT_STATUS_TYPE_DELIVERING_POWER,
    SAI_POE_PORT_STATUS_TYPE_FAULT
};

/**
 * @brief create sai object and bind it to poe object
 *
 * @param[in] type object type
 * @param[out] object_id sai object
 * @param[in] attr_count Count
 * @param[in] attr_list Attribute list values
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
sai_status_t create_object(sai_object_type_t type,
                                 sai_object_id_t  *object_id,
                                 uint32_t attr_count,
                                 const sai_attribute_t *attr_list)
{
    LOG_PRINT("create object type");

    if (NULL == object_id) {
        LOG_PRINT("failed to get valid object id");
        return SAI_STATUS_INVALID_PARAMETER;
    }

    poe_object_id_t poe_object_id;
    Dictionary *mapping_db_ptr = NULL;
    uint32_t *mapping_entry_ptr = (uint32_t*)malloc(sizeof(uint32_t));

    switch (type)
    {
        case SAI_OBJECT_TYPE_POE_DEVICE:
            *mapping_entry_ptr = 0;
            mapping_db_ptr = poe_object_device_mapping_ptr;
            LOG_PRINT("type dev");
            break;
        case SAI_OBJECT_TYPE_POE_PSE:
            *mapping_entry_ptr = attr_list[0].value.u32;
            mapping_db_ptr = poe_object_pse_mapping_ptr;
            LOG_PRINT("type pse");
            break;
        case SAI_OBJECT_TYPE_POE_PORT:
            *mapping_entry_ptr = attr_list[0].value.u32;
            mapping_db_ptr = poe_object_port_mapping_ptr;
            LOG_PRINT("type poe");
            break;
        default:
            LOG_ERROR("failed to get valid type");
            return SAI_STATUS_FAILURE;
    }

    /* create object, use the given id and object type to create a unique sai object id */
    memset(&poe_object_id, 0, sizeof(poe_object_id));
    poe_object_id.id = *mapping_entry_ptr;
    poe_object_id.object_type = type;

    uint64_t sai_obj = POE_TO_SAI_OBJECT(&poe_object_id);
    *object_id = (sai_object_id_t)sai_obj;
    
    /* update the dictionary with the new key value pair */
    if((!mapping_db_ptr) || (!dict_put(mapping_db_ptr, *object_id, (void*)(mapping_entry_ptr)))) {
        LOG_ERROR("failed to input dictionary entry");
        return SAI_STATUS_FAILURE;
    }

    LOG_PRINT("created obj, value: 0x%" PRIx64, *object_id);
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief remove object mapping
 *
 * @param[in] type object type
 * @param[in] object_id sai object
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
sai_status_t remove_object(sai_object_type_t type,
                           sai_object_id_t  object_id)
{
    Dictionary *mapping_db_ptr = NULL;

    switch (type)
    {
        case SAI_OBJECT_TYPE_POE_DEVICE:
            mapping_db_ptr = poe_object_device_mapping_ptr;
            break;
        case SAI_OBJECT_TYPE_POE_PSE:
            mapping_db_ptr = poe_object_pse_mapping_ptr;
            break;
        case SAI_OBJECT_TYPE_POE_PORT:
            mapping_db_ptr = poe_object_port_mapping_ptr;
            break;
        default:
            LOG_ERROR("failed to get valid type");
            return SAI_STATUS_FAILURE;
    }

    if((!mapping_db_ptr) || (!dict_remove(mapping_db_ptr, object_id))) {
        LOG_ERROR("failed to input dictionary entry");
        return SAI_STATUS_FAILURE;
    }

    return SAI_STATUS_SUCCESS;
}

sai_status_t check_attribs_on_create(uint32_t attr_count,
                              const sai_attribute_t *attr_list,
                              sai_object_type_t object_type,
                              sai_object_id_t *object_id)
{

    return SAI_STATUS_SUCCESS;
}

sai_status_t find_attrib_in_list(uint32_t attr_count,
                                 const sai_attribute_t *attr_list,
                                 sai_attr_id_t attrib_id,
                                 const sai_attribute_value_t **attr_value,
                                 uint32_t *index)
{
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief checks if device is initialized
 *
 * @return #bool, if initialized true otherwise false
 */
bool poe_device_is_initialized()
{
    if(!g_sai_db_ptr)
        return false;

    return g_sai_db_ptr->is_poe_device_initialized;
}

/**
 * @brief PoE initialization
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
sai_status_t poe_device_initialize()
{
    sai_status_t status = SAI_STATUS_SUCCESS;
    uint32_t num_of_entries = 0;
    
    if (poe_device_is_initialized()) {
        status = SAI_STATUS_SUCCESS;
        goto exit;
    }

    g_sai_db_ptr = (global_poe*)malloc(sizeof(global_poe));
    g_sai_db_ptr->is_poe_device_initialized = true;

    /* create the dictionaries */
    num_of_entries = getNumOfDevices();
    if (num_of_entries == 0) {
        LOG_ERROR("failed to get valid number of device entries");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

    poe_object_device_mapping_ptr = create_dictionary(num_of_entries);
    if(!poe_object_device_mapping_ptr) {
        LOG_ERROR("failed to create dictionary");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

    num_of_entries = getNumOfPse();
    if (num_of_entries == 0) {
        LOG_ERROR("failed to get valid number of PSE entries");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

    poe_object_pse_mapping_ptr = create_dictionary(num_of_entries);
    if(!poe_object_pse_mapping_ptr) {
        LOG_ERROR("failed to create dictionary");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

    num_of_entries = getNumOfPorts();
    if (num_of_entries == 0) {
        LOG_ERROR("failed to get valid number of port entries");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

    poe_object_port_mapping_ptr = create_dictionary(num_of_entries);
    if(!poe_object_port_mapping_ptr) {
        LOG_ERROR("failed to create dictionary");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

exit:
    return status;
}

/**
 * @brief Create a POE device instance
 *
 * @param[out] poe_device_id POE device ID
 * @param[in] switch_id Switch ID
 * @param[in] attr_count Count
 * @param[in] attr_list Attribute list values
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
static sai_status_t create_poe_device(
        _Out_ sai_object_id_t *poe_device_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list
)
{
    LOG_PRINT("create_poe_device");
    
    sai_status_t status;

    /* init semaphore */
    rwlock_excl_init(&sai_poe_lock);
    rwlock_excl_acquire(&sai_poe_lock); 
    status = poe_device_initialize();
    
    if (status != SAI_STATUS_SUCCESS) {
        LOG_ERROR("failed to initialize poe device");
        goto exit;
    }

    status = create_object(SAI_OBJECT_TYPE_POE_DEVICE, poe_device_id, attr_count, attr_list);
    if (status != SAI_STATUS_SUCCESS) {
        LOG_ERROR("failed to create object");
        goto exit;
    }

    LOG_PRINT("create_poe_device success");

exit:
    rwlock_excl_release(&sai_poe_lock);
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Remove POE instance.
 *
 * @param[in] poe_device_id Stp instance id
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 * error code is returned.
 */
static sai_status_t remove_poe_device(_In_ sai_object_id_t poe_device_id)
{
    assert(NULL != g_sai_db_ptr);

    rwlock_excl_acquire(&sai_poe_lock); 

    remove_object(SAI_OBJECT_TYPE_POE_DEVICE, poe_device_id);

    rwlock_excl_release(&sai_poe_lock);

    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Set the attribute of POE instance.
 *
 * @param[in] poe_device_id POE device ID
 * @param[in] attr Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
sai_status_t set_poe_device_attribute(
        _In_ sai_object_id_t poe_device_id, 
        _In_ const sai_attribute_t *attr)
{
    sai_status_t result; 
    uint32_t *internal_device_id_ptr = NULL;

    rwlock_excl_acquire(&sai_poe_lock);
    LOG_PRINT("poe_device_id: 0x%" PRIx64, poe_device_id);
    internal_device_id_ptr = (uint32_t*)dict_get(poe_object_device_mapping_ptr, poe_device_id);
    
    if(internal_device_id_ptr == NULL) {
        rwlock_excl_release(&sai_poe_lock);
        LOG_ERROR("failed to get valid entry");
        return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&sai_poe_lock);

    /* switch case placeholder, may change to function pointers */
    switch (attr->id)
    {
    case SAI_POE_DEVICE_ATTR_POWER_LIMIT_MODE:
        result = poeDevSetPowerLimitMode(*internal_device_id_ptr, attr->value.s32);
        break;
    default:
        LOG_ERROR("invalid attribute %d", attr->id);
        break;
    }

    /* poe result to sai result */
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Get the attribute of POE instance.
 *
 * @param[in] poe_device_id POE device ID
 * @param[in] attr_count Number of the attribute
 * @param[inout] attr_list Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
static sai_status_t get_poe_device_attribute(
        _In_ const sai_object_id_t poe_device_id,
        _In_ uint32_t              attr_count,
        _Inout_ sai_attribute_t   *attr_list)
{
    LOG_PRINT("enter get_poe_device_attribute");
    
    sai_status_t result;
    uint32_t i = 0, *internal_device_id_ptr = NULL;

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&sai_poe_lock);
    LOG_PRINT("poe_device_id: 0x%" PRIx64, poe_device_id);
    internal_device_id_ptr = (uint32_t*)dict_get(poe_object_device_mapping_ptr, poe_device_id);

    if(internal_device_id_ptr == NULL) {
        rwlock_excl_release(&sai_poe_lock);
        LOG_ERROR("failed to get valid entry");
        return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&sai_poe_lock);

    LOG_PRINT("get attribute count: %d", attr_count);
    for(i=0; i<attr_count; i++) {
        LOG_PRINT("for loop %d, id %d", i, attr_list[i].id);
        switch (attr_list[i].id)
        {
        case SAI_POE_DEVICE_ATTR_POE_PSE_LIST:
            result = poeDevGetPseList(*internal_device_id_ptr, &(attr_list[i].value.objlist.count), (uint64_t*)attr_list[i].value.objlist.list);
            LOG_PRINT("poeDevGetPseList, value: %d", attr_list[i].value.objlist.count);
            break;
        case SAI_POE_DEVICE_ATTR_POE_PORT_LIST:
            result = poeDevGetPortList(*internal_device_id_ptr, &(attr_list[i].value.objlist.count), (uint64_t*)attr_list[i].value.objlist.list);
            LOG_PRINT("poeDevGetPortList, value: %d", attr_list[i].value.objlist.count);
            break;
        case SAI_POE_DEVICE_ATTR_TOTAL_POWER:
            result = poeDevGetTotalPower(*internal_device_id_ptr, &(attr_list[i].value.u32));
            LOG_PRINT("poeDevGetTotalPower, value: %d", attr_list[i].value.u32);
            break;
        case SAI_POE_DEVICE_ATTR_POWER_CONSUMPTION:
            result = poeDevGetPowerConsumption(*internal_device_id_ptr, &(attr_list[i].value.u32));
            LOG_PRINT("poeDevGetPowerConsumption, value: %d", attr_list[i].value.u32);
            break;
        case SAI_POE_DEVICE_ATTR_VERSION:
            result = poeDevGetVersion(*internal_device_id_ptr, attr_list[i].value.chardata);
            LOG_PRINT("poeDevGetVersion, value: %s", attr_list[i].value.chardata);
            break;
        case SAI_POE_DEVICE_ATTR_POWER_LIMIT_MODE:
            result = poeDevGetPowerLimitMode(*internal_device_id_ptr, &(attr_list[i].value.s32));
            LOG_PRINT("poeDevGetPowerLimitMode, value: %d", attr_list[i].value.s32);
            break;
        case SAI_SWITCH_ATTR_SWITCH_HARDWARE_INFO:
            result = SAI_STATUS_SUCCESS;
            strncpy(attr_list[i].value.chardata, "poe_hw", strlen("poe_hw")+1);
            LOG_PRINT("hardware info (poe_hw)");
            break;
        case SAI_SWITCH_ATTR_INIT_SWITCH:
            attr_list[i].value.booldata = true;
            result = SAI_STATUS_SUCCESS;
            LOG_PRINT("init switch");
            break;
        default:
            LOG_ERROR("invalid attribute %d", attr_list[i].id);
            return SAI_STATUS_FAILURE;
        }
    }
    
    LOG_PRINT("get_poe_device_attribute result %d\n", result);
    /* poe result to sai result */
    return POE_TO_SAI_RESULT(result);
}

/**
 * @brief Create a POE PSE instance
 *
 * @param[out] poe_pse_id POE PSE ID
 * @param[in] switch_id Switch ID
 * @param[in] attr_count Count
 * @param[in] attr_list Attribute list values
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
static sai_status_t create_poe_pse(_Out_ sai_object_id_t      *poe_pse_id,
                                         _In_ sai_object_id_t        switch_id,
                                         _In_ uint32_t               attr_count,
                                         _In_ const sai_attribute_t *attr_list)
{
    uint32_t                     poe_device_index, poe_pse_index;
    const sai_attribute_value_t *poe_device, *poe_pse;
    sai_object_id_t              poe_device_obj_id;
    sai_status_t                 status;

    status = check_attribs_on_create(attr_count, attr_list, SAI_OBJECT_TYPE_POE_PSE, poe_pse_id);
    
    if (status != SAI_STATUS_SUCCESS) {
        return status;
    }

    status = find_attrib_in_list(attr_count, attr_list, SAI_POE_PSE_ATTR_ID, &poe_pse, &poe_pse_index);
    assert(status == SAI_STATUS_SUCCESS);

    status = find_attrib_in_list(attr_count, attr_list, SAI_POE_PSE_ATTR_DEVICE_ID, &poe_device, &poe_device_index);
    assert(status == SAI_STATUS_SUCCESS);

    rwlock_excl_acquire(&sai_poe_lock); 

    status = create_object(SAI_OBJECT_TYPE_POE_PSE, poe_pse_id, attr_count, attr_list);

    rwlock_excl_release(&sai_poe_lock);

    LOG_PRINT("create_poe_pse success");

    return status;
}

/**
 * @brief Remove POE port object.
 *
 * @param[in] poe_pse_id POE object id
 * @return SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *  error code is returned.
 */
static sai_status_t remove_poe_pse(_In_ sai_object_id_t poe_pse_id)
{
    sai_status_t status;

    assert(NULL != g_sai_db_ptr);
    rwlock_excl_acquire(&sai_poe_lock); 

    status = remove_object(SAI_OBJECT_TYPE_POE_PSE, poe_pse_id);

    rwlock_excl_release(&sai_poe_lock);

    return status;
}

/**
 * @brief Set the attribute of STP port.
 *
 * @param[in] poe_pse_id POE port id
 * @param[in] attr attribute value
 * @return SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *  error code is returned.
 */
static sai_status_t set_poe_pse_attribute(_In_ sai_object_id_t poe_pse_id, _In_ const sai_attribute_t *attr)
{
    /* As of now, no set attributes for PSEs are supported */
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Get the attribute of STP port.
 *
 * @param[in] poe_pse_id POE port id
 * @param[in] attr_count number of the attribute
 * @param[in] attr_list attribute value
 * @return SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *  error code is returned.
 */
static sai_status_t get_poe_pse_attribute(_In_ sai_object_id_t     poe_pse_id,
                                                _In_ uint32_t            attr_count,
                                                _Inout_ sai_attribute_t *attr_list)
{
    LOG_PRINT("get_poe_pse_attribute 0x%" PRIx64, poe_pse_id);
    uint32_t i = 0, pse_id, *internal_pse_id_ptr = 0;
    sai_status_t result; 

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&sai_poe_lock); 
    internal_pse_id_ptr = (uint32_t*)dict_get(poe_object_pse_mapping_ptr, poe_pse_id);
    pse_id = *internal_pse_id_ptr;

    /* TEMPORARY WORKAROUND */
    /* If SONiC calls get/set attribute before creating it then check if the object is in the correct format */
    /* if so, parse the internal id */
    if(internal_pse_id_ptr == NULL) {
        LOG_ERROR("pse entry does not exist in internal mapping");

        poe_object_id_t poe_object_id = SAI_TO_POE_OBJECT(poe_pse_id);

        if(poe_object_id.object_type == SAI_OBJECT_TYPE_POE_PSE) {
            pse_id = poe_object_id.id;
        } 
        else {
            rwlock_excl_release(&sai_poe_lock);
            return SAI_STATUS_FAILURE;
        }
    }

    rwlock_excl_release(&sai_poe_lock);
    
    for(i=0; i<attr_count; i++) {
        LOG_PRINT("for loop %d, id %d", i, attr_list[i].id);
        switch (attr_list[i].id)
        {
        case SAI_POE_PSE_ATTR_SOFTWARE_VERSION:
            result = poePseGetSoftwareVersion(pse_id, attr_list[i].value.chardata);
            break;
        case SAI_POE_PSE_ATTR_HARDWARE_VERSION:
            result = poePseGetHardwareVersion(pse_id, attr_list[i].value.chardata);
            break;
        case SAI_POE_PSE_ATTR_TEMPERATURE:
            result = poePseGetTemperature(pse_id, &(attr_list[i].value.s16));
            LOG_PRINT("poePseGetTemperature %d, result: %d", attr_list[i].value.s16, result);
            break;
        case SAI_POE_PSE_ATTR_STATUS:
            LOG_PRINT("poePseGetStatus PSE index %d", pse_id);
            result = poePseGetStatus(pse_id, &(attr_list[i].value.s16));
            attr_list[i].value.s16 = convertStatusToSai[attr_list[i].value.s16];
            break;
        case SAI_POE_PSE_ATTR_DEVICE_ID:
            attr_list[i].value.oid = ((uint64_t)SAI_OBJECT_TYPE_POE_DEVICE << 32) | (uint32_t)0;
            LOG_PRINT("poePortGetDeviceId, result: 0x%" PRIx64, attr_list[i].value.oid);
            result = SAI_STATUS_SUCCESS;
            break;
        default:
            LOG_ERROR("invalid attribute, %d", attr_list[i].id);
            return SAI_STATUS_FAILURE;
        }
    }
    
    LOG_PRINT("get_poe_pse_attribute success");
    
    /* poe result to sai result */
    return POE_TO_SAI_RESULT(result);
}

/**
 * @brief Create a POE PSE instance
 *
 * @param[out] poe_port_id POE PSE ID
 * @param[in] switch_id Switch ID
 * @param[in] attr_count Count
 * @param[in] attr_list Attribute list values
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
static sai_status_t create_poe_port(_Out_ sai_object_id_t           *poe_port_id,
                                         _In_ sai_object_id_t        switch_id,
                                         _In_ uint32_t               attr_count,
                                         _In_ const sai_attribute_t *attr_list)
{
    uint32_t                     poe_device_index, poe_port_index;
    const sai_attribute_value_t *poe_device, *poe_port;
    sai_object_id_t              poe_device_obj_id;
    sai_status_t                 status;

    status = check_attribs_on_create(attr_count, attr_list, SAI_OBJECT_TYPE_POE_PORT, poe_port_id);
    
    if (status != SAI_STATUS_SUCCESS) {
        return status;
    }

    status = find_attrib_in_list(attr_count, attr_list, SAI_POE_PORT_ATTR_FRONT_PANEL_ID, &poe_port, &poe_port_index);
    assert(status == SAI_STATUS_SUCCESS);

    status = find_attrib_in_list(attr_count, attr_list, SAI_POE_PORT_ATTR_DEVICE_ID, &poe_device, &poe_device_index);
    assert(status == SAI_STATUS_SUCCESS);

    rwlock_excl_acquire(&sai_poe_lock);

    status = create_object(SAI_OBJECT_TYPE_POE_PORT, poe_port_id, attr_count, attr_list);

    rwlock_excl_release(&sai_poe_lock);
    return status;
}

/**
 * @brief Remove POE port object.
 *
 * @param[in] poe_port_id POE object id
 * @return SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *  error code is returned.
 */
static sai_status_t remove_poe_port(_In_ sai_object_id_t poe_port_id)
{
    assert(NULL != g_sai_db_ptr);
    
    rwlock_excl_acquire(&sai_poe_lock); 

    remove_object(SAI_OBJECT_TYPE_POE_PSE, poe_port_id);

    rwlock_excl_release(&sai_poe_lock);

    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Set the attribute of STP port.
 *
 * @param[in] poe_port_id POE port id
 * @param[in] attr attribute value
 * @return SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *  error code is returned.
 */
static sai_status_t set_poe_port_attribute(_In_ sai_object_id_t poe_port_id, _In_ const sai_attribute_t *attr)
{
    sai_status_t result;
    uint32_t port_id, *internal_port_id_ptr = NULL;

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&sai_poe_lock);
    internal_port_id_ptr = (uint32_t*)dict_get(poe_object_port_mapping_ptr, poe_port_id);
    port_id = *internal_port_id_ptr;

    /* TEMPORARY WORKAROUND */
    /* If SONiC calls get/set attribute before creating it then check if the object is in the correct format */
    /* if so, parse the internal id */
    if(internal_port_id_ptr == NULL) {
        LOG_ERROR("port entry does not exist in internal mapping");

        poe_object_id_t poe_object_id = SAI_TO_POE_OBJECT(poe_port_id);

        if(poe_object_id.object_type == SAI_OBJECT_TYPE_POE_PORT) {
            port_id = poe_object_id.id;
        } 
        else {
            rwlock_excl_release(&sai_poe_lock);
            return SAI_STATUS_FAILURE;
        }
    }

    rwlock_excl_release(&sai_poe_lock);

    switch (attr->id)
    {
    case SAI_POE_PORT_ATTR_ADMIN_ENABLED_STATE:
        result = poePortSetAdminEnable(port_id, attr->value.booldata);
        break;
    case SAI_POE_PORT_ATTR_POWER_LIMIT:
        result = poeDevSetPowerLimitMode(port_id, attr->value.u32);
        break;
    case SAI_POE_PORT_ATTR_POWER_PRIORITY:
        result = poePortSetPowerPriority(port_id, attr->value.s32);
        break;
    default:
        result = POE_OP_NOT_SUPPORTED_E;
        break;
    }

    /* poe result to sai result */
    return POE_TO_SAI_RESULT(result);
}

/**
 * @brief Get the attribute of STP port.
 *
 * @param[in] poe_port_id POE port id
 * @param[in] attr_count number of the attribute
 * @param[in] attr_list attribute value
 * @return SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *  error code is returned.
 */
static sai_status_t get_poe_port_attribute(_In_ sai_object_id_t     poe_port_id,
                                                _In_ uint32_t            attr_count,
                                                _Inout_ sai_attribute_t *attr_list)
{
    LOG_PRINT("enter get_poe_port_attribute");
    
    uint32_t i = 0, port_id, *internal_port_id_ptr = NULL;
    sai_status_t result; 

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&sai_poe_lock);
    internal_port_id_ptr = (uint32_t*)dict_get(poe_object_port_mapping_ptr, poe_port_id);
    port_id = *internal_port_id_ptr;

    /* TEMPORARY WORKAROUND */
    /* If SONiC calls get/set attribute before creating it then check if the object is in the correct format */
    /* if so, parse the internal id */
    if(internal_port_id_ptr == NULL) {
        LOG_ERROR("port entry does not exist in internal mapping");

        poe_object_id_t poe_object_id = SAI_TO_POE_OBJECT(poe_port_id);
        // poe_object_id.id = poe_port_id & 0xFFFFFFFF;
        // poe_object_id.object_type = (sai_object_type_t)(poe_port_id >> 32);

        if(poe_object_id.object_type == SAI_OBJECT_TYPE_POE_PORT) {
            port_id = poe_object_id.id;
        } 
        else {
            rwlock_excl_release(&sai_poe_lock);
            return SAI_STATUS_FAILURE;
        }
    }

    rwlock_excl_release(&sai_poe_lock);

    for(i=0; i<attr_count; i++) {
        LOG_PRINT("for loop %d, id %d", i, attr_list[i].id);
        switch (attr_list[i].id)
        {
        case SAI_POE_PORT_ATTR_STANDARD:
            result = poePortGetPortStandard(port_id, &(attr_list[i].value.u32));
            LOG_PRINT("poePortGetPortStandard, value: %d", attr_list[i].value.u32);
            break;
        case SAI_POE_PORT_ATTR_ADMIN_ENABLED_STATE:
            result = poePortGetAdminEnable(port_id, &(attr_list[i].value.booldata));
            LOG_PRINT("poePortGetAdminEnable, value: %d", attr_list[i].value.booldata);
            break;
        case SAI_POE_PORT_ATTR_POWER_LIMIT:
            result = poePortGetPowerLimit(port_id, &(attr_list[i].value.u32));
            LOG_PRINT("poePortGetPowerLimit, value: %d", attr_list[i].value.u32);
            break;
        case SAI_POE_PORT_ATTR_POWER_PRIORITY:
            result = poePortGetPowerPriority(port_id, &(attr_list[i].value.s32));
            LOG_PRINT("poePortGetPriority, value: %d", attr_list[i].value.s32);
            break;
        case SAI_POE_PORT_ATTR_CONSUMPTION:
            result = poePortGetPowerConsumption(port_id, &(attr_list[i].value.portpowerconsumption));
            /* convert v3 values into SAI values */
            attr_list[i].value.portpowerconsumption.active_channel = convertActiveChannelToSai[attr_list[i].value.portpowerconsumption.active_channel];
            attr_list[i].value.portpowerconsumption.signature_type = convertSignatureTypeToSai[attr_list[i].value.portpowerconsumption.signature_type];
            attr_list[i].value.portpowerconsumption.class_method = convertClassMethodToSai[attr_list[i].value.portpowerconsumption.class_method];

            LOG_PRINT("poePortGetPowerConsumption, value: %d", attr_list[i].value.portpowerconsumption.consumption);
            break;
        case SAI_POE_PORT_ATTR_STATUS:
            result = poePortGetStatus(port_id, &(attr_list[i].value.s32));
            /* convert v3 values into SAI values */
            attr_list[i].value.s32 = convertPoePortDetectionToSai[attr_list[i].value.s32];
            LOG_PRINT("poePortGetStatus, value: %d", attr_list[i].value.s32);
            break;
        case SAI_POE_PORT_ATTR_DEVICE_ID:
            attr_list[i].value.oid = ((uint64_t)SAI_OBJECT_TYPE_POE_DEVICE << 32) | (uint32_t)0;
            LOG_PRINT("poePortGetDeviceId, value: 0x%" PRIx64, attr_list[i].value.oid);
            result = SAI_STATUS_SUCCESS;
            break;
        default:
            LOG_ERROR("invalid attribute %d", attr_list[i].id);
            return SAI_STATUS_FAILURE;
        }
    }

    /* poe result to sai result */

    return POE_TO_SAI_RESULT(result);
}

const sai_poe_api_t poe_api = {
    create_poe_device,
    remove_poe_device,
    set_poe_device_attribute,
    get_poe_device_attribute,
    create_poe_pse,
    remove_poe_pse,
    set_poe_pse_attribute,
    get_poe_pse_attribute,
    create_poe_port,
    remove_poe_port,
    set_poe_port_attribute,
    get_poe_port_attribute,
};

sai_status_t create_switch(sai_object_id_t *switch_id,
                            uint32_t attr_count,
                            const sai_attribute_t *attr_list)
{
    LOG_PRINT("create_switch");

    create_poe_device(switch_id, 0, 0, NULL);

    return SAI_STATUS_SUCCESS;
}

sai_status_t remove_switch(_In_ sai_object_id_t switch_id) 
{
    LOG_PRINT("remove_switch");

    return SAI_STATUS_SUCCESS;
}

sai_status_t set_attribute(
        _In_ sai_object_id_t switch_id, 
        _In_ const sai_attribute_t *attr) 
{
    LOG_PRINT("set_attribute");

    return SAI_STATUS_SUCCESS;
}

static sai_status_t get_attribute(
        _In_ const sai_object_id_t switch_id,
        _In_ uint32_t              attr_count,
        _Inout_ sai_attribute_t   *attr_list)
{
    int i;
    for(i=0; i<attr_count; i++) {
        LOG_PRINT("get_attribute %d", attr_list[i].id);
        switch (attr_list[i].id)
        {
            case SAI_SWITCH_ATTR_SWITCH_HARDWARE_INFO:
                strncpy(attr_list[i].value.chardata, "poe_hw", strlen("poe_hw")+1);
                LOG_PRINT("hardware info (poe_hw)");
                break;
            case SAI_SWITCH_ATTR_TYPE:
                attr_list[i].value.s32 = SAI_SWITCH_TYPE_POE;
                LOG_PRINT("switch type (SAI_SWITCH_TYPE_POE)");
                break;
        }

        return SAI_STATUS_SUCCESS;
    }
}

const sai_switch_api_t switch_api = {
    create_switch,
    remove_switch,
    set_attribute,
    get_attribute,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @brief Initialize PoE.
 *
 * @param[in] api flags
 * @param[out] services services
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_api_initialize(_In_ uint64_t flags,
        _In_ const sai_service_method_table_t *services) {

    POE_OP_RESULT_ENT result = poeInitialize();

    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Retrieve a pointer to the C-style method table for desired SAI
 * functionality as specified by the given sai_api_id.
 *
 * @param[in] api SAI API ID
 * @param[out] api_method_table Caller allocated method table. The table must
 * remain valid until the sai_api_uninitialize() is called.
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_api_query(
        _In_ sai_api_t api,
        _Out_ void **api_method_table) {

    switch(api) {
        case SAI_API_POE:
            *api_method_table = (void *)&poe_api;
            break;
        case SAI_API_SWITCH:
            *api_method_table = (void *)&switch_api;
            break;
    }    

    LOG_PRINT("sai_api_query api %d \n", api);
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Uninitialize adapter module. SAI functionalities,
 * retrieved via sai_api_query() cannot be used after this call.
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_api_uninitialize(void) {
    free(g_sai_db_ptr);

    destroy_dictionary(poe_object_device_mapping_ptr);
    destroy_dictionary(poe_object_pse_mapping_ptr);
    destroy_dictionary(poe_object_port_mapping_ptr);

    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Set log level for SAI API module
 *
 * The default log level is #SAI_LOG_LEVEL_WARN.
 *
 * @param[in] api SAI API ID
 * @param[in] log_level Log level
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_log_set(
        _In_ sai_api_t api,
        _In_ sai_log_level_t log_level) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Query SAI object type.
 *
 * @param[in] object_id Object id
 *
 * @return #SAI_OBJECT_TYPE_NULL when sai_object_id is not valid.
 * Otherwise, return a valid SAI object type SAI_OBJECT_TYPE_XXX.
 */
sai_object_type_t sai_object_type_query(
        _In_ sai_object_id_t object_id) {
    
    sai_object_type_t type;
    poe_object_id_t poe_object_id = SAI_TO_POE_OBJECT(object_id);

    switch(poe_object_id.object_type) {
        case SAI_OBJECT_TYPE_POE_DEVICE:
        case SAI_OBJECT_TYPE_POE_PSE:
        case SAI_OBJECT_TYPE_POE_PORT:
            type = poe_object_id.object_type;
            LOG_PRINT("valid poe object type");
            break;
        default:
            LOG_PRINT("non poe sai object");
            type = (sai_object_type_t)(object_id & 0xFFFFFFFF);
    }

    LOG_PRINT("sai_object_type_query (type: %d, id: %d)", type, poe_object_id.id);
    return type;
}

/**
 * @brief Query SAI switch id.
 *
 * @param[in] object_id Object id
 *
 * @return #SAI_NULL_OBJECT_ID when sai_object_id is not valid.
 * Otherwise, return a valid SAI_OBJECT_TYPE_SWITCH object on which
 * provided object id belongs. If valid switch id object is provided
 * as input parameter it should return itself.
 */
sai_object_id_t sai_switch_id_query(
        _In_ sai_object_id_t object_id) {
    LOG_PRINT("sai_switch_id_query");
    return SAI_OBJECT_TYPE_POE_DEVICE;
}

/**
 * @brief Generate dump file. The dump file may include SAI state information and vendor SDK information.
 *
 * @param[in] dump_file_name Full path for dump file
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_dbg_generate_dump(
        _In_ const char *dump_file_name) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Get SAI object type resource availability.
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list List of attributes that to distinguish resource
 * @param[out] count Available objects left
 *
 * @return #SAI_STATUS_SUCCESS if the given object type does not support resource accounting.
 * Otherwise, return #SAI_STATUS_SUCCESS.
 */
sai_status_t sai_object_type_get_availability(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list,
        _Out_ uint64_t *count) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Get maximum number of attributes for an object type
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[out] count Maximum number of attribute for an object type
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_get_maximum_attribute_count(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _Out_ uint32_t *count) {
    
    switch (object_type)
    {
        case SAI_OBJECT_TYPE_POE_DEVICE:
            *count = SAI_POE_DEVICE_ATTR_END;
            break;
        case SAI_OBJECT_TYPE_POE_PSE:
            *count = SAI_POE_PSE_ATTR_END;
            break;
        case SAI_OBJECT_TYPE_POE_PORT:
            *count = SAI_POE_PORT_ATTR_END;
            break;
        default:
            LOG_ERROR("failed to get valid type");
            return SAI_STATUS_FAILURE;
    }

    LOG_PRINT("sai_get_maximum_attribute_count success");
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Get the number of objects present in SAI. Deprecated for backward compatibility.
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[out] count Number of objects in SAI
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_get_object_count(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _Out_ uint32_t *count) {
    LOG_PRINT("sai_get_object_count");

    KeyValuePair kv;
    uint8_t i = 0;
    rwlock_excl_acquire(&sai_poe_lock);
    
    switch (object_type)
    {
        case SAI_OBJECT_TYPE_POE_DEVICE:
            dict_get_first(poe_object_device_mapping_ptr, &kv);
            i++;

            while(dict_get_next(poe_object_device_mapping_ptr, kv.key, &kv)) {
                i++;
            }
            *count = i;
            break;
        case SAI_OBJECT_TYPE_POE_PSE:
            dict_get_first(poe_object_pse_mapping_ptr, &kv);
            i++;

            while(dict_get_next(poe_object_pse_mapping_ptr, kv.key, &kv)) {
                i++;
            }
            *count = i;
            break;
        case SAI_OBJECT_TYPE_POE_PORT:
            dict_get_first(poe_object_port_mapping_ptr, &kv);
            i++;

            while(dict_get_next(poe_object_port_mapping_ptr, kv.key, &kv)) {
                i++;
            }
            *count = i;
            break;
        default:
            LOG_ERROR("failed to get valid type");
            rwlock_excl_release(&sai_poe_lock);
            return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&sai_poe_lock);
    LOG_PRINT("sai_get_object_count success");
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Get the number of and list of object keys present in SAI if enough large
 * list provided, otherwise get the number of object keys only.
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[inout] object_count Number of objects in SAI
 * @param[inout] object_list List of SAI objects or keys
 *
 * @return #SAI_STATUS_SUCCESS on success, #SAI_STATUS_BUFFER_OVERFLOW if list size insufficient, failure status code on error
 */
sai_status_t sai_get_object_key(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _Inout_ uint32_t *object_count,
        _Inout_ sai_object_key_t *object_list) {
    
    LOG_PRINT("sai_get_object_key");
    KeyValuePair kv;
    uint8_t i = 0;
    rwlock_excl_acquire(&sai_poe_lock);

    switch (object_type)
    {
        case SAI_OBJECT_TYPE_POE_DEVICE:
            dict_get_first(poe_object_device_mapping_ptr, &kv);
            object_list[i].key.object_id = kv.key;
            i++;

            while(dict_get_next(poe_object_device_mapping_ptr, object_list[i-1].key.object_id, &kv)) {
                object_list[i].key.object_id = kv.key;
                i++;
            }
            *object_count = i;
            break;
        case SAI_OBJECT_TYPE_POE_PSE:
            dict_get_first(poe_object_pse_mapping_ptr, &kv);
            object_list[i].key.object_id = kv.key;
            i++;

            while(dict_get_next(poe_object_pse_mapping_ptr, object_list[i-1].key.object_id, &kv)) {
                object_list[i].key.object_id = kv.key;
                i++;
            }
            *object_count = i;
            break;
        case SAI_OBJECT_TYPE_POE_PORT:
            dict_get_first(poe_object_port_mapping_ptr, &kv);
            object_list[i].key.object_id = kv.key;
            i++;

            while(dict_get_next(poe_object_port_mapping_ptr, object_list[i-1].key.object_id, &kv)) {
                object_list[i].key.object_id = kv.key;
                i++;
            }
            *object_count = i;
            break;
        default:
            LOG_ERROR("failed to get valid type");
            rwlock_excl_release(&sai_poe_lock);
            return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&sai_poe_lock);
    LOG_PRINT("sai_get_object_key success");
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Get the bulk list of valid attributes for a given list of
 * object keys.
 *
 * Only valid attributes for an object are returned.
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[in] object_count Number of objects
 * @param[in] object_key List of object keys
 * @param[inout] attr_count List of attr_count. Caller passes the number
 *    of attribute allocated in. Callee returns with the actual
 *    number of attributes filled in. If the count is less than
 *    needed, callee fills with the needed count and do not fill
 *    the attributes. Callee also set the corresponding status to
 *    #SAI_STATUS_BUFFER_OVERFLOW.
 *
 * @param[inout] attr_list List of attributes for every object. Caller is
 *    responsible for allocating and freeing buffer for the attributes.
 *    For list based attribute, e.g., s32list, objlist, callee should
 *    assume the caller has not allocated the memory for the list and
 *    should only to fill the count but not list. Then, caller
 *    can use corresponding get_attribute to get the list.
 *
 * @param[inout] object_statuses Status for each object. If the object does
 *    not exist, callee sets the corresponding status to #SAI_STATUS_INVALID_OBJECT_ID.
 *    If the allocated attribute count is not large enough,
 *    set the status to #SAI_STATUS_BUFFER_OVERFLOW.
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_bulk_get_attribute(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ uint32_t object_count,
        _In_ const sai_object_key_t *object_key,
        _Inout_ uint32_t *attr_count,
        _Inout_ sai_attribute_t **attr_list,
        _Inout_ sai_status_t *object_statuses) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Query attribute capability
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[in] attr_id SAI attribute ID
 * @param[out] attr_capability Capability per operation
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_query_attribute_capability(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ sai_attr_id_t attr_id,
        _Out_ sai_attr_capability_t *attr_capability) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Query an enum attribute (enum or enum list) list of implemented enum values
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[in] attr_id SAI attribute ID
 * @param[inout] enum_values_capability List of implemented enum values
 *
 * @return #SAI_STATUS_SUCCESS on success, #SAI_STATUS_BUFFER_OVERFLOW if list size insufficient, failure status code on error
 */
sai_status_t sai_query_attribute_enum_values_capability(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ sai_attr_id_t attr_id,
        _Inout_ sai_s32_list_t *enum_values_capability) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Query statistics capability for statistics bound at object level
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[inout] stats_capability List of implemented enum values, and the statistics modes (bit mask) supported per value
 *
 * @return #SAI_STATUS_SUCCESS on success, #SAI_STATUS_BUFFER_OVERFLOW if lists size insufficient, failure status code on error
 */
sai_status_t sai_query_stats_capability(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _Inout_ sai_stat_capability_list_t *stats_capability) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Bulk objects get statistics.
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type Object type
 * @param[in] object_count Number of objects to get the stats
 * @param[in] object_key List of object keys
 * @param[in] number_of_counters Number of counters in the array
 * @param[in] counter_ids Specifies the array of counter ids
 * @param[in] mode Statistics mode
 * @param[inout] object_statuses Array of status for each object. Length of the array should be object_count. Should be looked only if API return is not SAI_STATUS_SUCCESS.
 * @param[out] counters Array of resulting counter values.
 *    Length of counters array should be object_count*number_of_counters.
 *    Counter value of I object and J counter_id = counter[I*number_of_counters + J]
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_bulk_object_get_stats(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ uint32_t object_count,
        _In_ const sai_object_key_t *object_key,
        _In_ uint32_t number_of_counters,
        _In_ const sai_stat_id_t *counter_ids,
        _In_ sai_stats_mode_t mode,
        _Inout_ sai_status_t *object_statuses,
        _Out_ uint64_t *counters) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Bulk objects clear statistics.
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type Object type
 * @param[in] object_count Number of objects to get the stats
 * @param[in] object_key List of object keys
 * @param[in] number_of_counters Number of counters in the array
 * @param[in] counter_ids Specifies the array of counter ids
 * @param[in] mode Statistics mode
 * @param[inout] object_statuses Array of status for each object. Length of the array should be object_count. Should be looked only if API return is not SAI_STATUS_SUCCESS.
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_bulk_object_clear_stats(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ uint32_t object_count,
        _In_ const sai_object_key_t *object_key,
        _In_ uint32_t number_of_counters,
        _In_ const sai_stat_id_t *counter_ids,
        _In_ sai_stats_mode_t mode,
        _Inout_ sai_status_t *object_statuses) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Query the HW stage of an attribute for the specified object type
 *
 * @param[in] switch_id SAI Switch object id
 * @param[in] object_type SAI object type
 * @param[in] attr_count Count of attributes
 * @param[in] attr_list List of attributes
 * @param[out] stage HW stage of the attributes. Length of the array should be attr_count. Caller must allocate the buffer.
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_query_object_stage(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list,
        _Out_ sai_object_stage_t *stage) {
    return SAI_STATUS_SUCCESS;
}

/**
 * @brief Query of the SAI API version that is running 
 *
 * @param[in] version SAI api version
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
sai_status_t sai_query_api_version(
        _Out_ sai_api_version_t *version) {

    *version = SAI_API_VERSION;
    return SAI_STATUS_SUCCESS;
}