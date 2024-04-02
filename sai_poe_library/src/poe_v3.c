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

#include "inc/poe_v3.h"
#include "../utils/inc/dictionary.h"
#include "../utils/inc/lock.h"

/* global databases */
Dictionary *device_db_ptr = NULL, *pse_db_ptr = NULL, *port_db_ptr = NULL;
/* lock critical sections when reading/writing */
rwlock_excl_t lock;

void main() {
    return;
}   

/**
 * @brief initialize a database for each of the objects (device/pse/port)
 *
 * @return #poe_op_ok_E if operation is successful otherwise a different
 *    error code is returned.
 */
poe_op_result_t database_initialize() 
{
    uint64_t key;
    uint32_t num_of_ports, num_of_pses, num_of_devices, index;

    rwlock_excl_acquire(&lock);
    
    device_db_ptr = create_dictionary(num_of_devices);
    for(index=0; index<num_of_devices; index++) {
        poe_device_db_t *device_db_entry_ptr = (poe_device_db_t*)malloc(sizeof(poe_device_db_t));
        
        if(!device_db_entry_ptr) {
            rwlock_excl_release(&lock);
            return poe_op_failed_E;
        }

        key = device_db_entry_ptr->device_id = 0; /* get hw data */

        if((!device_db_ptr) || (!dict_put(device_db_ptr, key, (void*)(device_db_entry_ptr)))) {
            rwlock_excl_release(&lock);
            return poe_op_failed_E;
        }
    }

    pse_db_ptr = create_dictionary(num_of_pses);
    for(index=0; index<num_of_pses; index++) {
        poe_pse_db_t *pse_db_entry_ptr = (poe_pse_db_t*)malloc(sizeof(poe_pse_db_t));

        if(!pse_db_entry_ptr) {
            rwlock_excl_release(&lock);
            return poe_op_failed_E; 
        }

        key = pse_db_entry_ptr->pse_id = 0; /* get hw data */

        if((!pse_db_ptr) || (!dict_put(pse_db_ptr, key, (void*)(pse_db_entry_ptr)))) {
            rwlock_excl_release(&lock);
            return poe_op_failed_E;
        }
    }

    port_db_ptr = create_dictionary(num_of_ports);
    for(index=0; index<num_of_ports; index++) {
        poe_port_db_t *port_db_entry_ptr = (poe_port_db_t*)malloc(sizeof(poe_port_db_t));

        if(!port_db_entry_ptr) {
            rwlock_excl_release(&lock);
            return poe_op_failed_E;
        }

        key = port_db_entry_ptr->front_panel_index = 0; /* get hw data */
        port_db_entry_ptr->port_standard = poe_port_hw_type_bt_type3_E; /* get hw data */

        if((!port_db_ptr) || (!dict_put(port_db_ptr, key, (void*)(port_db_entry_ptr)))) {
            rwlock_excl_release(&lock);
            return poe_op_failed_E;
        }
    }

    rwlock_excl_release(&lock);

    return poe_op_ok_E;
}

/**
 * @brief General initialize a for the shared memory protocol
 *
 * @return #poe_op_ok_E if operation is successful otherwise a different
 *    error code is returned.
 */
poe_op_result_t shared_memory_initialize() {
    return poe_op_ok_E;
}

/**
 * @brief General initialize for all the PoE components
 *
 * @return #poe_op_ok_E if operation is successful otherwise a different
 *    error code is returned.
 */
poe_op_result_t internal_poe_device_initialize(void) {
    
    poe_op_result_t result = poe_op_ok_E;
    /* init sempahore */
    rwlock_excl_init(&lock);

    rwlock_excl_acquire(&lock);

    /* init databases */
    result = database_initialize();
    if(result != poe_op_ok_E) {
        rwlock_excl_release(&lock);
        return result;
    }

    /* set poe port matrix */
    result = poe_port_matrix_initialize();
    if(result != poe_op_ok_E) {
        rwlock_excl_release(&lock);
        return result;
    }

    /* set poe port standard */
    result = poe_port_standard_initialize();
    if(result != poe_op_ok_E) {
        rwlock_excl_release(&lock);
        return result;
    }

    /* init shared memory */
    result = shared_memory_initialize();
    if(result != poe_op_ok_E) {
        rwlock_excl_release(&lock);
        return result;
    }

    rwlock_excl_release(&lock);

    return poe_op_ok_E;
}

/**
 * @brief Get the first front panel index
 *
 * @param[out] first_front_panel_index first front panel index
 * 
 * @return #true if operation is successful otherwise false
 *
 */
bool poe_port_get_first_index(uint32_t *first_front_panel_index) {
    KeyValuePair key_value;
    if(!dict_get_first(port_db_ptr, &key_value)) {
        return false;
    }

    *first_front_panel_index = key_value.key;
    return true;
}

/**
 * @brief Get the next front panel index
 *
 * @param[out] front_panel_index next front panel index
 * 
 * @return #true if operation is successful otherwise false
 *
 */
bool poe_port_get_next_index(uint32_t *front_panel_index) {
    KeyValuePair next_key_value;
    
    if(!dict_get_next(port_db_ptr, (uint64_t)(*front_panel_index), &next_key_value)) {
        return false;
    }

    *front_panel_index = next_key_value.key;
    return true;
}

/**
 * @brief Get the poe port hardware type
 *
 * @param[in] front_panel_index front panel index
 * 
 * @return #poe_port_hw_type_t if operation is successful otherwise poe_port_hw_type_invalid_E
 *
 */
poe_port_hw_type_t poe_get_port_poe_hw_type(uint32_t front_panel_index) { 
    poe_port_db_t *value_ptr = (poe_port_db_t*)dict_get(port_db_ptr, (uint64_t)front_panel_index);

    if(value_ptr == NULL) {
        return poe_port_hw_type_invalid_E;
    }

    return value_ptr->port_standard;
}

/**
 * @brief Get the physical port index
 *
 * @param[in] front_panel_index front panel index
 * @param[out] physical_index physical port index
 * 
 * @return #true if operation is successful otherwise false
 *
 */
bool poe_port_get_physical_index(uint32_t front_panel_index, uint32_t *physical_index) {
    poe_port_db_t *value_ptr = (poe_port_db_t*)dict_get(port_db_ptr, (uint64_t)front_panel_index);

    if(value_ptr == NULL) {
        return false;
    }

    *physical_index = value_ptr->physical_index_a;

    return true;
}

/**
 * @brief Get the second physical port index (if it exists)
 *
 * @param[in] front_panel_index front panel index
 * @param[out] physical_index second physical port index
 * 
 * @return #true if operation is successful otherwise false
 *
 */
bool poe_port_get_second_physical_index(uint32_t front_panel_index, uint32_t *physical_index) {
    poe_port_db_t *value_ptr = (poe_port_db_t*)dict_get(port_db_ptr, (uint64_t)front_panel_index);

    if(value_ptr == NULL) {
        return false;
    }

    *physical_index = value_ptr->physical_index_b;

    return true;
}

/**
 * @brief Send/recieve data from the shared memory protocol
 *
 * @param[in] send true if writing data otherwise reading
 * @param[in] op_code operation code
 * @param[in] data_len data length
 * @param[out] data data
 * 
 * @return #true if operation is successful otherwise false
 *
 */
bool EXTHWG_POE_IPc_send_recieve_msg(bool send, uint32_t op_code, uint8_t data_len, uint8_t *data) {
    /* should be implemented in the IPC/shared memory logic */
    return true;
}

/**
 * @brief send/receive message to/from the poe firmware
 *
 * @param[in] msg_level message level (port/system)
 * @param[in] direction get or set
 * @param[in] msg_id message id
 * @param[in] data_len data length
 * @param[out] data_PTR data
 * 
 * @return #true if operation is successful otherwise false
 *
 */
poe_op_result_t poe_v3_send_receive_msg (

    /*!     INPUTS:             */    
    poe_v3_msg_level_TYP        msg_level,
    poe_v3_msg_direction_TYP    direction,
    uint16_t                                 msg_id,
    uint8_t                                  data_len,
    /*!     INPUTS / OUTPUTS:   */
    void*                                   data_PTR
    /*!     OUTPUTS:            */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
    uint8_t  *buf_PTR;
    bool send=(direction==poe_v3_msg_dir_get_CNS)?false:true;
    poe_v3_msg_opCode_UNT op_code;
/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/   
    poe_v3_set_msg_opCode_MAC(op_code, msg_level, direction, msg_id);
    buf_PTR = (uint8_t*)data_PTR;
    if (true != EXTHWG_POE_IPc_send_recieve_msg(send, op_code.op_code_num_32, data_len, buf_PTR)) {
        return poe_op_failed_E;
    }

    return poe_op_ok_E;
} 

/**
 * @brief Intialize port matrix
 * 
 * @return #poe_op_ok_E if operation is successful otherwise a different
 *    error code is returned.
 */
poe_op_result_t poe_port_matrix_initialize() {
    uint32_t                          physical_number_a, physical_number_b, front_panel_index, index;;
    poe_port_hw_type_t               poe_port_hw_type;
    poe_v3_msg_sysPortMatrix_STC set_matrix_params;

    /* clean matrix params */
    memset(&set_matrix_params, 0xff, sizeof(poe_v3_msg_sysPortMatrix_STC));
    
    /* for every front panel (logical) poe port in the device, set the correct physical port */
    if(!poe_port_get_first_index(&front_panel_index)) {
        return poe_op_failed_E;
    }

    for (index=0; poe_port_get_next_index(&front_panel_index);) {

        poe_port_hw_type = poe_get_port_poe_hw_type(front_panel_index);

        if(poe_port_hw_type == poe_port_hw_type_invalid_E) {
            return poe_op_failed_E;
        }

         if(!poe_port_get_physical_index(front_panel_index, &physical_number_a)) {
            return poe_op_failed_E;
         }

        set_matrix_params.physic_logical_pair[index].logical_port = (uint8_t)front_panel_index;
        set_matrix_params.physic_logical_pair[index++].phys_port = (uint8_t)physical_number_a;
                
        /* if the port supports two channels, set the second physical port */
        if ((poe_port_hw_type == poe_port_hw_type_60W_E) ||
            (poe_port_hw_type == poe_port_hw_type_bt_type3_E) ||
            (poe_port_hw_type == poe_port_hw_type_bt_type4_E)) {
            
            if(!poe_port_get_second_physical_index(front_panel_index, &physical_number_b)) {
                return poe_op_failed_E;
            }

            set_matrix_params.physic_logical_pair[index].logical_port = (uint8_t)front_panel_index;
            set_matrix_params.physic_logical_pair[index++].phys_port = (uint8_t)physical_number_b;
        }
    }
    
    if (index) {
        return poe_v3_send_receive_msg(
            poe_v3_msg_level_system_CNS, 
            poe_v3_msg_dir_set_CNS,
            poe_v3_sys_msg_portMatrix_CNS,
            sizeof(set_matrix_params),
            (uint8_t*)&set_matrix_params);
    } 

    return poe_op_failed_E;
}

/**
 * @brief intialize port standard
 * 
 * @return #poe_op_ok_E if operation is successful otherwise a different
 *    error code is returned.
 */
poe_op_result_t poe_port_standard_initialize() {
    uint32_t                          front_panel_index, index;
    poe_port_hw_type_t      poe_port_hw_type, system_hw_capability;
    poe_v3_msg_sysPortSupportedStd_STC port_standard_params;
    poe_op_result_t status;

    memset(&port_standard_params, 0xff, sizeof(poe_v3_msg_sysPortSupportedStd_STC));
    
    if(!poe_port_get_first_index(&front_panel_index)) {
        return poe_op_failed_E;
    }

    for (index=0; poe_port_get_next_index(&front_panel_index);) {
        
        poe_port_hw_type = poe_get_port_poe_hw_type(front_panel_index);
        
        port_standard_params.supported_std_data[index].logic_port = (uint8_t)front_panel_index;
        port_standard_params.supported_std_data[index++].portSupportedStd = poe_port_hw_type;
    }

    return poe_v3_send_receive_msg(
            poe_v3_msg_level_system_CNS, 
            poe_v3_msg_dir_set_CNS,
            poe_v3_sys_msg_portSupportStandard_CNS,
            sizeof(port_standard_params),
            (uint8_t*)&port_standard_params);
}

/**
 * @brief Set enable/disable on poe port
 * 
 * @param[in] front_panel_index front panel index
 * @param[in] enable enable/disable
 * 
 * @return #poe_op_ok_E if operation is successful otherwise a different
 *    error code is returned.
 */
poe_op_result_t poe_port_set_admin_enable (
    uint32_t front_panel_index,
    bool enable
)
{
    poe_v3_msg_portEnable_STC   port_params;
    poe_op_result_t result; 

    rwlock_excl_acquire(&lock); 

    memset(&port_params, 0, sizeof(poe_v3_msg_portEnable_STC));
    port_params.logic_port_num = (uint8_t)front_panel_index;
    port_params.port_admin_enable_disable = (enable==true)?poe_v3_port_admin_enable_CNS:poe_v3_port_admin_disable_CNS;

    result = poe_v3_send_receive_msg(poe_v3_msg_level_port_CNS, poe_v3_msg_dir_set_CNS, poe_v3_port_msg_portEnable_CNS, sizeof(port_params), (uint8_t*)&port_params);

    rwlock_excl_release(&lock);

    return result;
} 

/**
 * @brief get poe port enable/disable state
 * 
 * @param[in] front_panel_index front panel index
 * @param[out] enable enable/disable
 * 
 * @return #poe_op_ok_E if operation is successful otherwise a different
 *    error code is returned.
 */
poe_op_result_t poe_port_get_admin_enable (
    uint32_t front_panel_index,
    bool *enable
)
{
    poe_v3_msg_portEnable_STC   port_params;
    poe_op_result_t result;

    rwlock_excl_acquire(&lock);  

    memset(&port_params, 0, sizeof(poe_v3_msg_portEnable_STC));
    port_params.logic_port_num = (uint8_t)front_panel_index;

    result = poe_v3_send_receive_msg(poe_v3_msg_level_port_CNS, poe_v3_msg_dir_get_CNS, poe_v3_port_msg_portEnable_CNS, sizeof(port_params), (uint8_t*)&port_params);

    if(result == poe_op_ok_E) {
        *enable = port_params.port_admin_enable_disable;
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief swap uint16_t
 * 
 * @param[in] value uint16_t value
 * 
 * @return swapped uint16_t value
 * 
 */
uint16_t swap16(uint16_t value) {
    return (value << 8) | (value >> 8);
}