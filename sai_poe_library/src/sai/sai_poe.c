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

#include <h/utils/dictionary.h>
#include <h/utils/lock.h>
#include <h/poe_v3.h>
#include <string.h>
#include <h/sai/sai.h>
#include "assert.h"
#include <h/utils/log.h>

#undef  __MODULE__
#define __MODULE__ SAI_POE

/* global sai db pointer */
global_poe *g_sai_db_ptr = NULL;
/* lock critical sections when reading/writing */
rwlock_excl_t lock;
/* dictionaries holding poe devie/pse/port mappings (sai <-> v3 poe) */
Dictionary *poe_object_device_mapping_ptr = NULL, *poe_object_pse_mapping_ptr = NULL, *poe_object_port_mapping_ptr = NULL;

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
    if (NULL == object_id) {
        return SAI_STATUS_INVALID_PARAMETER;
    }

    poe_object_id_t *poe_object_id = (poe_object_id_t*)object_id;
    Dictionary *mapping_db_ptr = NULL;
    uint32_t *mapping_entry_ptr = (uint32_t*)malloc(sizeof(uint32_t));

    switch (type)
    {
        case SAI_OBJECT_TYPE_POE_DEVICE:
            *mapping_entry_ptr = 0;
            mapping_db_ptr = poe_object_device_mapping_ptr;
            break;
        case SAI_OBJECT_TYPE_POE_PSE:
            *mapping_entry_ptr = attr_list[0].value.u32;
            mapping_db_ptr = poe_object_pse_mapping_ptr;
            break;
        case SAI_OBJECT_TYPE_POE_PORT:
            *mapping_entry_ptr = attr_list[0].value.u32;
            mapping_db_ptr = poe_object_port_mapping_ptr;
            break;
        default:
            LOG_ERROR("failed to get valid type");
            return SAI_STATUS_FAILURE;
    }

    /* create object, use the given id and object type to create a unique sai object id */
    memset(poe_object_id, 0, sizeof(*poe_object_id));
    poe_object_id->id = *mapping_entry_ptr;
    poe_object_id->object_type = type;

    /* update the dictionary with the new key value pair */
    if((!mapping_db_ptr) || (!dict_put(mapping_db_ptr, *object_id, (void*)(mapping_entry_ptr)))) {
        LOG_ERROR("failed to input dictionary entry");
        return SAI_STATUS_FAILURE;
    }

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
    sai_status_t status = SAI_STATUS_SUCCESS;;

    if (poe_device_is_initialized()) {
        status = SAI_STATUS_SUCCESS;
        goto exit;
    }

    g_sai_db_ptr = (global_poe*)malloc(sizeof(global_poe));
    g_sai_db_ptr->is_poe_device_initialized = true;

    /* create the dictionaries */
    /* placeholder - max number of entries for now */
    poe_object_device_mapping_ptr = create_dictionary(1);
    if(!poe_object_device_mapping_ptr) {
        LOG_ERROR("failed to create dictionary");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

    poe_object_pse_mapping_ptr = create_dictionary(16);
    if(!poe_object_pse_mapping_ptr) {
        LOG_ERROR("failed to create dictionary");
        status = SAI_STATUS_FAILURE;
        goto exit;
    }

    poe_object_port_mapping_ptr = create_dictionary(48);
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
    sai_status_t status;

    status = check_attribs_on_create(attr_count, attr_list, SAI_OBJECT_TYPE_POE_DEVICE, poe_device_id);
    
    if (status != SAI_STATUS_SUCCESS) {
        return status;
    }

    /* init sempahore */
    rwlock_excl_init(&lock);
    rwlock_excl_acquire(&lock); 
    status = poe_device_initialize();
    
    if (status != SAI_STATUS_SUCCESS) {
        goto exit;
    }

    status = create_object(SAI_OBJECT_TYPE_POE_DEVICE, poe_device_id, attr_count, attr_list);
    if (status != SAI_STATUS_SUCCESS) {
        goto exit;
    }

exit:
    rwlock_excl_release(&lock);
    return status;
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

    rwlock_excl_acquire(&lock); 

    remove_object(SAI_OBJECT_TYPE_POE_DEVICE, poe_device_id);

    rwlock_excl_release(&lock);

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

    rwlock_excl_acquire(&lock);
    internal_device_id_ptr = (uint32_t*)dict_get(poe_object_device_mapping_ptr, poe_device_id);
    
    if(internal_device_id_ptr == NULL) {
        rwlock_excl_release(&lock);
        LOG_ERROR("failed to get valid entry");
        return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&lock);

    /* switch case placeholder, may change to function pointers */
    switch (attr->id)
    {
    case SAI_POE_DEVICE_ATTR_POWER_LIMIT_MODE:
        result = poeDevSetPowerLimitMode(*internal_device_id_ptr, attr->value.s32);
        break;
    default:
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
    sai_status_t result;
    uint32_t i = 0, *internal_device_id_ptr = NULL;

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&lock);
    internal_device_id_ptr = (uint32_t*)dict_get(poe_object_device_mapping_ptr, poe_device_id);

    if(internal_device_id_ptr == NULL) {
        rwlock_excl_release(&lock);
        LOG_ERROR("failed to get valid entry");
        return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&lock);

    for(i=0; i<attr_count; i++) {
        switch (attr_list[i].id)
        {
        case SAI_POE_DEVICE_ATTR_TOTAL_POWER:
            result = poeDevGetTotalPower(*internal_device_id_ptr, &(attr_list[i].value.u32));
            break;
        case SAI_POE_DEVICE_ATTR_POWER_CONSUMPTION:
            result = poeDevGetPowerConsumption(*internal_device_id_ptr, &(attr_list[i].value.u32));
            break;
        case SAI_POE_DEVICE_ATTR_VERSION:
            result = poeDevGetVersion(*internal_device_id_ptr, &(attr_list[i].value.chardata));
            break;
        case SAI_POE_DEVICE_ATTR_POWER_LIMIT_MODE:
            result = poeDevGetPowerLimitMode(*internal_device_id_ptr, &(attr_list[i].value.s32));
            break;
        default:
            LOG_ERROR("invalid attribute");
            return SAI_STATUS_FAILURE;
        }
    }
    
    /* poe result to sai result */
    return SAI_STATUS_SUCCESS;
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

    rwlock_excl_acquire(&lock); 

    status = create_object(SAI_OBJECT_TYPE_POE_PSE, poe_pse_id, attr_count, attr_list);

    rwlock_excl_release(&lock);
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
    assert(NULL != g_sai_db_ptr);
    rwlock_excl_acquire(&lock); 

    remove_object(SAI_OBJECT_TYPE_POE_PSE, poe_pse_id);

    rwlock_excl_release(&lock);

    return SAI_STATUS_SUCCESS;
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
    uint32_t i = 0, *internal_pse_id_ptr = 0;
    sai_status_t result; 

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&lock); 
    internal_pse_id_ptr = (uint32_t*)dict_get(poe_object_pse_mapping_ptr, poe_pse_id);

    if(internal_pse_id_ptr == NULL) {
        rwlock_excl_release(&lock);
        LOG_ERROR("failed to get valid entry");
        return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&lock);
    
    for(i=0; i<attr_count; i++) {
        switch (attr_list[i].id)
        {
        case SAI_POE_PSE_ATTR_PSE_SOFTWARE_VERSION:
            result = poePseGetSoftwareVersion(*internal_pse_id_ptr, &(attr_list[i].value.chardata));
            break;
        case SAI_POE_PSE_ATTR_HARDWARE_VERSION:
            result = poePseGetHardwareVersion(*internal_pse_id_ptr, &(attr_list[i].value.chardata));
            break;
        case SAI_POE_PSE_ATTR_TEMPERATURE:
            result = poePseGetTemperature(*internal_pse_id_ptr, &(attr_list[i].value.s16));
            break;
        case SAI_POE_PSE_ATTR_STATUS:
            result = poePseGetStatus(*internal_pse_id_ptr, &(attr_list[i].value.s32));
            break;
        default:
            LOG_ERROR("invalid attribute");
            return SAI_STATUS_FAILURE;
        }
    }
    
    /* poe result to sai result */
    return result;
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

    rwlock_excl_acquire(&lock);

    status = create_object(SAI_OBJECT_TYPE_POE_PORT, poe_port_id, attr_count, attr_list);

    rwlock_excl_release(&lock);
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
    
    rwlock_excl_acquire(&lock); 

    remove_object(SAI_OBJECT_TYPE_POE_PSE, poe_port_id);

    rwlock_excl_release(&lock);

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
    uint32_t *internal_port_id_ptr = NULL;

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&lock);
    internal_port_id_ptr = (uint32_t*)dict_get(poe_object_port_mapping_ptr, poe_port_id);

    if(internal_port_id_ptr == NULL) {
        rwlock_excl_release(&lock);
        LOG_ERROR("failed to get valid entry");
        return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&lock);

    switch (attr->id)
    {
    case SAI_POE_PORT_ATTR_ADMIN_ENABLED_STATE:
        result = poePortSetAdminEnable(*internal_port_id_ptr, attr->value.booldata);
        break;
    case SAI_POE_PORT_ATTR_POWER_LIMIT:
        result = poeDevSetPowerLimitMode(*internal_port_id_ptr, attr->value.u32);
        break;
    case SAI_POE_PORT_ATTR_POWER_PRIORITY:
        result = poePortSetPowerPriority(*internal_port_id_ptr, attr->value.s32);
        break;
    default:
        break;
    }

    /* poe result to sai result */
    return SAI_STATUS_SUCCESS;
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
    uint32_t i = 0, *internal_port_id_ptr = NULL;
    sai_status_t result; 

    /* switch case placeholder, may change to function pointers */
    rwlock_excl_acquire(&lock);
    internal_port_id_ptr = (uint32_t*)dict_get(poe_object_port_mapping_ptr, poe_port_id);

    if(internal_port_id_ptr == NULL) {
        rwlock_excl_release(&lock);
        LOG_ERROR("failed to get valid entry");
        return SAI_STATUS_FAILURE;
    }

    rwlock_excl_release(&lock);

    for(i=0; i<attr_count; i++) {
        switch (attr_list[i].id)
        {
        case SAI_POE_PORT_ATTR_STANDARD:
            result = poePortGetPortStandard(*internal_port_id_ptr, &(attr_list[i].value.s32));
            break;
        case SAI_POE_PORT_ATTR_ADMIN_ENABLED_STATE:
            result = poePortGetAdminEnable(*internal_port_id_ptr, &(attr_list[i].value.booldata));
            break;
        case SAI_POE_PORT_ATTR_POWER_LIMIT:
            result = poePortGetPowerLimit(*internal_port_id_ptr, &(attr_list[i].value.u32));
            break;
        case SAI_POE_PORT_ATTR_CONSUMPTION:
            result = poePortGetPowerConsumption(*internal_port_id_ptr, &(attr_list[i].value.portpowerconsumption));
            break;
        case SAI_POE_PORT_ATTR_STATUS:
            result = poePortGetStatus(*internal_port_id_ptr, &(attr_list[i].value.s32));
            break;
        default:
            LOG_ERROR("invalid attribute");
            return SAI_STATUS_FAILURE;
        }
    }

    /* poe result to sai result */
    return SAI_STATUS_SUCCESS;
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

/**
 * @brief main.
 *
 * @return SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *  error code is returned.
 */
void main() {
    int choice;
    sai_object_id_t switch_id = 0, poe_device_id = 0, poe_pse_id[16] = {0}, poe_port_id[48] = {0};
    uint32_t attr_count = 0, value = 0, pse_create_index = 0, port_create_index = 0, port_index, pse_index;
    sai_attribute_t attr_list[10] = {0};
    char exit_choice;

    poeInitialize();
    
    do {
        printf("Choose which sai_poe_api_t to create:\n");
        printf("0. bulk create all objects with default values\n");
        printf("1. create_poe_device\n");
        printf("2. create_poe_pse\n");
        printf("3. create_poe_port\n");
        printf("4. remove_poe_device\n");
        printf("5. set_poe_device_attribute\n");
        printf("6. get_poe_device_attribute\n");
        printf("7. remove_poe_pse\n");
        printf("8. set_poe_pse_attribute\n");
        printf("9. get_poe_pse_attribute\n");
        printf("10. remove_poe_port\n");
        printf("11. set_poe_port_attribute\n");
        printf("12. get_poe_port_attribute\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);

        printf("Enter switch ID: ");
        scanf("%d", &switch_id);
        
        printf("Enter attribute count: ");
        scanf("%u", &attr_count);
        

        switch (choice) {
            case 0:
                switch_id = 1;
                attr_count = 1;
                strcpy(attr_list[0].value.chardata, "integrated-mcu");
                create_poe_device(&poe_device_id, switch_id, attr_count, attr_list);
                attr_list[0].value.u32 = 1;
                attr_list[1].value.oid = poe_device_id;
                attr_count = 2;
                create_poe_pse(&poe_pse_id[pse_create_index], switch_id, attr_count, attr_list);
                attr_list[0].value.u32 = 1;
                attr_list[1].value.oid = poe_device_id;
                attr_count = 2;
                create_poe_port(&poe_port_id[port_create_index], switch_id, attr_count, attr_list);
                pse_create_index++;
                attr_list[0].value.u32 = 2;
                attr_list[1].value.oid = poe_device_id;
                attr_count = 2;
                port_create_index = 1;
                create_poe_port(&poe_port_id[port_create_index], switch_id, attr_count, attr_list);
                pse_create_index++;
            case 1:
                create_poe_device(&poe_device_id, switch_id, attr_count, attr_list);
                break;
            case 2:
                printf("Enter value for attribute %d, pse index: ", 0);
                scanf("%d", &attr_list[0].value.u32);
                attr_list[1].value.oid = poe_device_id;
                create_poe_pse(&poe_port_id[pse_create_index], switch_id, attr_count, attr_list);
                pse_create_index++;
                break;
            case 3:
                printf("Enter value for attribute %d, port index: ", 0);
                scanf("%d", &attr_list[0].value.u32);
                attr_list[1].value.oid = poe_device_id;
                create_poe_port(&poe_port_id[port_create_index], switch_id, attr_count, attr_list);
                break;
            case 4:
                remove_poe_device(poe_device_id);
                break;
            case 5:
                printf("Please choose the attribute:\n"
                          "SAI_POE_DEVICE_ATTR_POWER_LIMIT_MODE = 6\n");
                
                printf("Enter your choice: ");
                scanf("%d", &choice);
                attr_list[0].id = choice;

                printf("Enter your value for the attribute: ");
                scanf("%d", &value);
                attr_list[0].value = (sai_attribute_value_t)value;

                set_poe_device_attribute(poe_device_id, attr_list);
                break;
            case 6:
                printf("Please choose the attribute:\n"
                          "SAI_POE_DEVICE_ATTR_HARDWARE_INFO = 0,\n"
                          "SAI_POE_DEVICE_ATTR_POE_PSE_LIST = 1,\n"
                          "SAI_POE_DEVICE_ATTR_POE_PORT_LIST = 2,\n"
                          "SAI_POE_DEVICE_ATTR_TOTAL_POWER = 3,\n"
                          "SAI_POE_DEVICE_ATTR_POWER_CONSUMPTION = 4,\n"
                          "SAI_POE_DEVICE_ATTR_VERSION = 5,\n"
                          "SAI_POE_DEVICE_ATTR_POWER_LIMIT_MODE = 6\n");


                printf("Enter your choice: ");
                scanf("%d", &choice);
                attr_list[0].id = choice;

                get_poe_device_attribute(poe_device_id, attr_count, attr_list);
                break;
            case 7:
                remove_poe_pse(poe_pse_id[0]);
                break;
            case 8:
                printf("pse does not have any set attributes ");
                set_poe_pse_attribute(poe_pse_id[0], attr_list);
                break;
            case 9:
                printf("Please choose the attribute:\n"
                "SAI_POE_PSE_ATTR_PSE_SOFTWARE_VERSION = 2,\n"
                "SAI_POE_PSE_ATTR_PSE_HARDWARE_VERSION = 3,\n"
                "SAI_POE_PSE_ATTR_TEMPERATURE = 4,\n"
                "SAI_POE_PSE_ATTR_PSE_STATUS = 5\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                attr_list[0].id = choice;
                get_poe_pse_attribute(poe_pse_id[0], attr_count, attr_list);
                break;
            case 10:
                remove_poe_port(poe_port_id[0]);
                break;
            case 11:
                printf("Please choose the attribute:\n"
                    "SAI_POE_PORT_ATTR_ADMIN_ENABLED_STATE = 3,\n"
                    "SAI_POE_PORT_ATTR_POWER_LIMIT = 4,\n"
                    "SAI_POE_PORT_ATTR_POWER_PRIORITY = 5,\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                attr_list[0].id = choice;

                printf("Enter your value for the attribute: ");
                scanf("%d", &value);
                attr_list[0].value = (sai_attribute_value_t)value;

                set_poe_port_attribute(poe_port_id[0], attr_list);
                break;
            case 12:
            printf("Please choose the attribute:\n"
                    "SAI_POE_PORT_ATTR_STANDARD = 2,\n"
                    "SAI_POE_PORT_ATTR_ADMIN_ENABLED_STATE = 3,\n"
                    "SAI_POE_PORT_ATTR_POWER_LIMIT = 4,\n"
                    "SAI_POE_PORT_ATTR_POWER_PRIORITY = 5,\n"
                    "SAI_POE_PORT_ATTR_CONSUMPTION = 6,\n"
                    "SAI_POE_PORT_ATTR_STATUS = 7\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                attr_list[0].id = choice;

                get_poe_port_attribute(poe_port_id[0], attr_count, attr_list);
                break;
            default:
                printf("Invalid choice\n");
                break;
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &exit_choice);
    } while (exit_choice == 'y' || exit_choice == 'Y'); 
}