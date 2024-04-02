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

#ifndef __POE_V3_H__
#define __POE_V3_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct poe_object_id_t {
    uint32_t id;
    uint32_t object_type;
} poe_object_id_t;

/* status */
typedef enum {
    poe_op_failed_E = 0,
    poe_op_ok_E,
    poe_op_not_supported_E,
} poe_op_result_t;

typedef enum {
    poe_port_hw_type_af_E = 0,
    poe_port_hw_type_at_E,
    poe_port_hw_type_60W_E,
    poe_port_hw_type_bt_type3_E,
    poe_port_hw_type_bt_type4_E,
    /* must be last */
    poe_port_hw_type_invalid_E
} poe_port_hw_type_t;

typedef struct _poe_power_management_unit_db_STCT {
    /* set */
    uint32_t                           main_pse_power_mw;
    uint32_t                           main_pse_consumption_power_mw;
    uint32_t                           calculated_power_mw;
    uint32_t                           available_power_mw;
} poe_power_management_unit_db_STC;

typedef uint32_t UnitType_TYP;
#define unitType_None_CNS   	0
#define unitType_PSE_CNS   	1
#define unitType_PD_CNS   	2
#define unitType_PSE_PD_CNS   3

typedef uint8_t powerLimitMode_TYP;
#define powerLimitMode_port_CNS  0
#define powerLimitMode_class_CNS 1

typedef struct poe_device_db_t {
    uint32_t                                       device_id;
    uint32_t                                       total_power;
    uint32_t                                       power_consumption;
    char                                          *version;
    powerLimitMode_TYP                             power_limit_mode;
    uint32_t                                       allocated_power;
    poe_power_management_unit_db_STC               power_management;                                                     
    UnitType_TYP                                   unit_type;
} poe_device_db_t;

typedef uint8_t poe_device_sys_status_TYP;
#define poe_device_sys_status_notPresent_CNS    0
#define poe_device_sys_status_active_CNS        1
#define poe_device_sys_status_i2cFailure_CNS    2

typedef struct poe_pse_db_t {
    uint32_t pse_id;
    char *software_version ;
    char *hardware_version;
    int16_t temperature;                                                     
    poe_device_sys_status_TYP status;
} poe_pse_db_t;

typedef uint16_t poe_v3_btClass_TYP;
#define poe_v3_btClass_noClass_CNS  0
#define poe_v3_btClass_class1_CNS   1
#define poe_v3_btClass_class2_CNS   2
#define poe_v3_btClass_class3_CNS   3
#define poe_v3_btClass_class4_CNS   4
#define poe_v3_btClass_class5_CNS   5
#define poe_v3_btClass_class6_CNS   6
#define poe_v3_btClass_class7_CNS   7
#define poe_v3_btClass_class8_CNS   8
#define poe_v3_btClass_na_CNS       0xFFFF

typedef uint16_t poe_v3_btClassMethod_TYP;
#define poe_v3_btClassMethod_regular_CNS    1
#define poe_v3_btClassMethod_autoClass_CNS  2

typedef struct {
    /* input */
    /* output */
    poe_v3_btClass_TYP     btPortAltASsMeasuredClass;  /* Ss or Ds-Alt-A measured class */
    poe_v3_btClass_TYP     btPortAltASsAssignedClass;  /* Ss or Ds-Alt-A assigned class */
    poe_v3_btClass_TYP     btPortAltBMeasuredClass;    /* Ds-Alt-B measured class */
    poe_v3_btClass_TYP     btPortAltBAssignedClass;    /* Ds-Alt-B assigned class */
    poe_v3_btClassMethod_TYP      btPortClassMethod;
}poe_bt_power_classifications_STC;

/* op_id_get_poe_power_classifications_E */
typedef struct {
    /* input */
    /* output */
    poe_v3_btClass_TYP     pethPsePortPowerClassifications;
}poe_at_power_classifications_STC;

typedef uint16_t poe_v3_btSignatureType_TYP;
#define poe_v3_btSignatureType_single_CNS   1
#define poe_v3_btSignatureType_dual_CNS     2

typedef struct {
    poe_v3_btSignatureType_TYP           signature_type;
    poe_at_power_classifications_STC     poe_at_class;
    poe_bt_power_classifications_STC     poe_bt_class;
}poe_power_classifications_STC;

typedef uint8_t poe_v3_port_active_channel_TYP;
#define poe_v3_port_active_channel_A_CNS   1
#define poe_v3_port_active_channel_B_CNS   2
#define poe_v3_port_active_channel_AB_CNS  3

typedef struct {
    poe_v3_port_active_channel_TYP           active_channel;
    uint32_t                                 output_voltage;
    uint32_t                                 output_current;
    uint32_t                                 output_power;
} poe_output_data_STC;

typedef uint8_t poe_detection_status_TYP;
#define poe_detection_status_off_CNS                             1
#define poe_detection_status_searching_CNS                       2
#define poe_detection_status_deliveringPower_CNS                 3
#define poe_detection_status_fault_CNS                           4

typedef uint8_t poe_v3_port_status_TYP;
#define poe_v3_port_status_on_ResDetect_CNS                     1
#define poe_v3_port_status_on_CapDetect_CNS                     2
#define poe_v3_port_status_on_4Pair_CNS                         3
#define poe_v3_port_status_on_force_4_pair_CNS                  4
#define poe_v3_port_status_off_VoltHigh_CNS                     5 /* Deprecated */
#define poe_v3_port_status_off_VoltLow_CNS                      6
#define poe_v3_port_status_off_HwPinDisPort_CNS                 7
#define poe_v3_port_status_off_UserDisable_CNS                  8
#define poe_v3_port_status_off_inDetection_CNS                  9
#define poe_v3_port_status_off_PD_NoStandard_CNS                10
#define poe_v3_port_status_off_OverUnderLoad_CNS                11
#define poe_v3_port_status_off_Underload_CNS                    12
#define poe_v3_port_status_off_Overload_CNS                     13
#define poe_v3_port_status_off_pwrBudgExc_CNS                   14
#define poe_v3_port_status_off_VoltInj_CNS                      15
#define poe_v3_port_status_off_CapDetInvSig_CNS                 16
#define poe_v3_port_status_off_Discharged_CNS                   17
#define poe_v3_port_status_on_ForceOn_CNS                       18
#define poe_v3_port_status_off_PwErr_CNS                        19
#define poe_v3_port_status_off_PwBudget_CNS                     20
#define poe_v3_port_status_off_ShortCond_CNS                    21
#define poe_v3_port_status_off_OverTemp_CNS                     22
#define poe_v3_port_status_off_DeviceHot_CNS                    23
#define poe_v3_port_status_off_ClassError_CNS                   24
#define poe_v3_port_status_off_r_low_detect_CNS                 25
#define poe_v3_port_status_off_powerOn_verificationFault_CNS    26
#define poe_v3_port_status_on_NonStd_BTdevice_CNS               27
#define poe_v3_port_status_off_unreachable_CNS                  28
#define poe_v3_port_status_altB_singleSignature_CNS             255

typedef struct {
    /* input */
    /* output */
    bool                                             capacitorSignatureDetected;
    poe_v3_port_status_TYP                poe_pse_hw_PortStatus;      /* PSE side - real port status from HW */
    uint32_t                                             unknownError_internal_status;
    poe_v3_port_status_TYP                poe_pse_hw_PortStatus_altB;
    uint32_t                                             unknownError_internal_status_altB;
} poe_detection_status_STC; 

typedef enum {
    poe_PsePortPowerPriority_critical_E =  1,
    poe_PsePortPowerPriority_high_E =      2,
    poe_PsePortPowerPriority_low_E =       3
} poe_PsePortPowerPriority_ENT;

typedef uint8_t poe_v3_power_mng_mode_TYP;
#define poe_v3_power_mng_mode_dynamic_CNS     0
#define poe_v3_power_mng_mode_static_CNS      1

typedef struct {
    bool                                         pethPsePortAdminEnable;         
    poe_PsePortPowerPriority_ENT        pethPsePortPowerPriority;       
    uint32_t                                         pethPsePortPowerLimit;          
    bool              legacy_support_status;          
    poe_v3_power_mng_mode_TYP             power_mng_status;               
    poe_v3_btClass_TYP                 poePortClassLimit;
    bool        num_of_events;        
} poe_port_configurable_data_t;

typedef struct {
    poe_power_classifications_STC     poe_port_power_classifications;
    poe_output_data_STC               poe_port_output_data;
    poe_detection_status_STC          poe_port_detection_status;
    uint32_t                          port_static_mode_alloc_power;
    uint32_t                          port_bt_primary_alt_alloc_power;
    uint32_t                          port_bt_secondary_alt_alloc_power;
} poe_port_power_consumption_data_db_t;

/* Port POE DB, per physical port */
typedef struct poe_port_db_t {
    /* key */
    uint32_t front_panel_index;
    /* hw related params */
    poe_port_hw_type_t port_standard;
    uint32_t physical_index_a;
    uint32_t physical_index_b;
    /* power related param s*/
    poe_port_power_consumption_data_db_t power_consumption_data; 
    /* set params - user configurable data*/
    poe_port_configurable_data_t configurable_data;
    /* read only params */
    poe_detection_status_TYP status;
    uint32_t max_power_limit;
    bool oper_status;                                                                               
} poe_port_db_t;

#define poe_max_num_of_pse_devs_in_unit_CNS 16

typedef struct {
    union{
        poe_device_sys_status_TYP pse_status[poe_max_num_of_pse_devs_in_unit_CNS];
        uint8_t hw_pse_st[poe_max_num_of_pse_devs_in_unit_CNS];
    }param;
} poe_device_sys_status_STC;

#define poe_get_system_status_stub_create_MAC(__func_name)  \
    BOOLEAN __func_name (                                               \
        BOOLEAN hw_mode,                                                \
        /*!     OUTPUTS:        */                                      \
        poe_device_sys_status_STC *o_sys_status_PTR)

typedef enum {
    poe_vendor_none_E = 0,
    poe_vendor_microchip_E,
    poe_vendor_ti_E, 
    poe_vendor_adi_E,
    poe_vendor_last_E
} poe_vendor_type_ENT;

typedef enum {
    poe_communication_mode_blocking_E = 0,
    poe_communication_mode_non_blocking_E,
    poe_communication_mode_last_E
} poe_communication_mode_ENT;

typedef enum {
    poe_guard_band_mode_not_supported_E = 0,
    poe_guard_band_mode_dynamic_E,
    poe_guard_band_mode_static_E
} poe_guard_band_mode_ENT;

typedef uint8_t HAP_poe_port_bt_sig_type_TYP;
#define HAP_poe_port_bt_sig_type_single_CNS  0
#define HAP_poe_port_bt_sig_type_dual_CNS    1


typedef enum {
    HAP_poe_port_bt_channel_alt_a_E,
    HAP_poe_port_bt_channel_alt_b_E,
    HAP_poe_port_bt_channel_alt_both_E
}HAP_poe_port_bt_channel_alt_ENT;

/* Current Version Constants */
#define poe_v3_dragonite_version_num_CNS    0xe000100 /* November 26th, 2017: Dragonite FW 0xE.0x0.0x1.0x0 */

/**** General parameters ****/
#define poe_v3_max_num_of_pse_CNS           16
#define poe_v3_invalid_temperature_CNS      0x7FFF

#define poe_v3_msg_PortLayer2CDPPSEData_Port_is_On_CDP_CNS          0x2000
#define poe_v3_msg_PortLayer2CDPPSEData_Port_is_On_LLDP_CNS         0x3000

typedef uint8_t poe_v3_dev_hw_version_TYP;
#define poe_v3_dev_hw_version_LTC4291_CNS       0x38 /* 802.3 BT: LTC4291 */

/**** Message parameters ****/
#define EXTDRVIPC_MAX_MSG_SIZE                          256 
#define poe_v3_msg_max_size_CNS             EXTDRVIPC_MAX_MSG_SIZE

#define poe_v3_msg_header_size_CNS          8  /* Bytes */
#define poe_v3_msg_max_data_size_CNS        (poe_v3_msg_max_size_CNS - poe_v3_msg_header_size_CNS)

typedef uint8_t poe_v3_msg_level_TYP;
#define poe_v3_msg_level_system_CNS     0
#define poe_v3_msg_level_port_CNS       1
#define poe_v3_msg_level_cause_CNS      2
#define poe_v3_msg_level_debug_CNS      3
 
typedef uint8_t poe_v3_msg_direction_TYP;
#define poe_v3_msg_dir_get_CNS          0
#define poe_v3_msg_dir_set_CNS          1

typedef struct {
    poe_v3_msg_level_TYP        level;
    poe_v3_msg_direction_TYP    direction;
    uint16_t                                 msg_id_swap;
} poe_v3_msg_opCode_STC;

typedef union {
    poe_v3_msg_opCode_STC params;
    uint32_t op_code_num_32;
} poe_v3_msg_opCode_UNT;

/*** system messages id's ***/
#define poe_v3_sys_msg_portMatrix_CNS           0x1
#define poe_v3_sys_msg_portSupportStandard_CNS  0x2
#define poe_v3_sys_msg_powerBankConfig_CNS      0x4
#define poe_v3_sys_msg_activeRpsPowerBank_CNS   0x10
#define poe_v3_sys_msg_powerLimitMode_CNS       0x20
#define poe_v3_sys_msg_l2AllocSetting_CNS       0x40
#define poe_v3_sys_msg_powerConsumption_CNS     0x80
#define poe_v3_sys_msg_systemVersion_CNS        0x100
#define poe_v3_sys_msg_pseTemperature_CNS       0x101
#define poe_v3_sys_msg_upgReadyStatus_CNS       0x102
#define poe_v3_sys_msg_upgDataTrans_CNS         0x103
#define poe_v3_sys_msg_upgStatus_CNS            0x104
#define poe_v3_sys_msg_serviceNotification_CNS  0x105
#define poe_v3_sys_msg_pseStatus_CNS            0x106
#define poe_v3_sys_msg_firmwareReadiness_CNS    0x107

/*** system messages types ***/
typedef uint8_t poe_v3_portSupStandard_TYP;
#define poe_v3_portSupStandard_af_CNS           1
#define poe_v3_portSupStandard_at_CNS           2
#define poe_v3_portSupStandard_60_CNS           3
#define poe_v3_portSupStandard_bt_type2_CNS     4
#define poe_v3_portSupStandard_bt_type3_CNS     5
#define poe_v3_portSupStandard_bt_type4_CNS     6

typedef uint8_t poe_v3_powerLimitMode_TYP;
#define poe_v3_powerLimitMode_port_CNS  0
#define poe_v3_powerLimitMode_class_CNS 1

typedef uint8_t poe_v3_operation_mode_TYP;
#define poe_v3_operation_mode_independent_CNS    1
#define poe_v3_operation_mode_normal_CNS         2

typedef uint8_t poe_v3_l2AllocPriorty_TYP;
#define poe_v3_l2AllocPriorty_noraml_CNS    0
#define poe_v3_l2AllocPriorty_high_CNS      1

typedef uint8_t poe_v3_l2AllocMngMode_TYP;
#define poe_v3_l2AllocMngMode_asPort_CNS    0
#define poe_v3_l2AllocMngMode_static_CNS    1

typedef uint8_t poe_v3_pseStatus_TYP;
#define poe_v3_pseStatus_NR_CNS             0
#define poe_v3_pseStatus_active_CNS         1
#define poe_v3_pseStatus_i2cFailure_CNS     2
#define poe_v3_pseStatus_notPresent_CNS     0xFF

typedef uint8_t poe_v3_upgReadinesss_TYP;
#define poe_v3_upgReadinesss_refuse_CNS     0
#define poe_v3_upgReadinesss_ready_CNS      1

typedef uint16_t poe_v3_upgBlockType_TYP;
#define poe_v3_upgBlockType_standard_CNS    0
#define poe_v3_upgBlockType_final_CNS       1
#define poe_v3_upgBlockType_unPlTerm_CNS    2   /* unplanned termination */

typedef uint8_t poe_v3_upgStatusCode_TYP;
#define poe_v3_upgStatusCode_success_CNS        0
#define poe_v3_upgBlockType_retryBlock_CNS      1
#define poe_v3_upgBlockType_restart_CNS         2
#define poe_v3_upgBlockType_abort_CNS           3
#define poe_v3_upgBlockType_processing_CNS      4

typedef uint8_t poe_v3_firmwareReadiness_TYP;
#define poe_v3_firmwareReadiness_init_CNS       0
#define poe_v3_firmwareReadiness_ready_CNS      1

#define poe_max_num_of_phys_ports_CNS 48
#define poe_max_num_of_powerBanks_CNS 16

/*** system messages messages structs ***/
typedef struct {
    struct {
        uint8_t  logical_port;
        uint8_t  phys_port;
    }physic_logical_pair[poe_max_num_of_phys_ports_CNS];
} poe_v3_msg_sysPortMatrix_STC;

typedef struct {
    struct{
        uint8_t                                 logic_port;
        poe_v3_portSupStandard_TYP portSupportedStd;
    }supported_std_data[poe_max_num_of_phys_ports_CNS];
} poe_v3_msg_sysPortSupportedStd_STC;

typedef struct {
    uint16_t power_bank_w_swap[poe_max_num_of_powerBanks_CNS];
} poe_v3_msg_sysPowerBank_STC;

typedef struct {
    uint8_t active_rpsPowerBank_index;
} poe_v3_msg_sysActiveRpsPowerBank_STC;

typedef struct {
    poe_v3_powerLimitMode_TYP   limit_mode;
} poe_v3_msg_sysPowerLimitMode_STC;

typedef struct {
    poe_v3_l2AllocPriorty_TYP   priority;
    poe_v3_l2AllocMngMode_TYP   mngMode;
} poe_v3_msg_sysL2AllocSetting_STC;

typedef struct {
    uint32_t                                  powerConsumption_swap;
    uint32_t                                  powerAllocation_swap;
} poe_v3_msg_sysPowerConsumption_STC;

typedef struct {
    poe_v3_operation_mode_TYP   operation_mode;
    uint8_t                                  reserved[3];
} poe_v3_msg_sysServiceNotification_STC;

typedef struct {
    poe_v3_firmwareReadiness_TYP   firmware_readiness;
    uint8_t                                     reserved[3];
} poe_v3_msg_sysFirmwareReadiness_STC;

#define poe_fw_version_num_of_bytes_CNS  4

typedef union {
    uint8_t  ver_bytes[poe_fw_version_num_of_bytes_CNS];
    uint32_t ver_num;
} poe_v3_msg_sw_version_UNT;

typedef struct {
    /* outputs */
    poe_v3_msg_sw_version_UNT   poeFwVersion;
    poe_v3_msg_sw_version_UNT   converterSwVersion;
    struct {
        uint8_t                              pseSwVersion;
        uint8_t                              pseHwVersion;
    }pse_version_data[poe_v3_max_num_of_pse_CNS];
} poe_v3_msg_sysSystemVersion_STC;

typedef struct {
    /* outputs */
    int16_t              pse_temp_swap[poe_v3_max_num_of_pse_CNS];
} poe_v3_msg_sysPseTemperature_STC;

typedef struct {
    /* outputs */
    poe_v3_pseStatus_TYP    pse_status[poe_v3_max_num_of_pse_CNS];
} poe_v3_msg_sysPseStatus_STC;

typedef struct {
    uint32_t                                 pseVersionId_swp;
    /* outputs */
    poe_v3_upgReadinesss_TYP    readiness;
    uint8_t                                  reserved;
    uint16_t                                 blockSize_swp;
} poe_v3_msg_sysUpgReadyStatus_STC;

#define poe_v3_msg_upgData_max_size_CNS (poe_v3_msg_max_data_size_CNS-12)

typedef struct {
    uint32_t             pseVersionId_swp;
    uint16_t             block_num_swp;
    uint16_t             block_type_swp;
    uint16_t             checksum_swp;
    uint16_t             reserved;
    uint8_t              data[poe_v3_msg_upgData_max_size_CNS];
} poe_v3_msg_sysUpgDataTrans_STC;

typedef struct {
    uint16_t                                 block_num_swp;
    poe_v3_upgStatusCode_TYP    statusCode;
    bool                                 err_exists;
    char                                    err_msg[32];
} poe_v3_msg_sysUpgStatus_STC;


/*** End of system level ***/

/***************************/

/*** port messages id's ***/
#define poe_v3_port_msg_portEnable_CNS          0x10
#define poe_v3_port_msg_physClassMethod_CNS     0x11
#define poe_v3_port_msg_legacyDetected_CNS      0x12
#define poe_v3_port_msg_AltBEnable_CNS          0x14
#define poe_v3_port_msg_portPowerLimit_CNS      0x20
#define poe_v3_port_msg_portPriority_CNS        0x21
#define poe_v3_port_msg_powerMng_CNS            0x22
#define poe_v3_port_msg_btAutoClass_CNS         0x23
#define poe_v3_port_msg_portClassLimit_CNS      0x24
#define poe_v3_port_msg_l2ReqPowerLldp_CNS      0x40
#define poe_v3_port_msg_l2ReqPowerList_CNS      0x41
#define poe_v3_port_msg_allocPower_CNS          0x42
#define poe_v3_port_msg_btManualAutoClass_CNS   0x43
#define poe_v3_port_msg_powerConsumInfo_CNS     0x80
#define poe_v3_port_msg_portStatus_CNS          0x81
#define poe_v3_port_msg_portCounters_CNS        0x82
#define poe_v3_port_msg_portConfig_CNS          0x83

/*** port messages types ***/

typedef uint8_t poe_v3_port_admin_TYP;
#define poe_v3_port_admin_disable_CNS   0
#define poe_v3_port_admin_enable_CNS    1
#define poe_v3_port_admin_invalid_CNS   0xff

typedef uint8_t poe_v3_physLayerClass_TYP;
#define poe_v3_physLayerClass_1_event_CNS   1
#define poe_v3_physLayerClass_2_event_CNS   2

typedef uint8_t poe_v3_legacyMode_TYP;
#define poe_v3_legacyMode_disable_CNS       0
#define poe_v3_legacyMode_enable_CNS        1
#define poe_v3_legacyMode_auto_CNS          2

typedef uint8_t poe_v3_alt_b_mode_TYP;
#define poe_v3_alt_b_mode_disable_CNS       0
#define poe_v3_alt_b_mode_enable_CNS        1
#define poe_v3_alt_b_mode_forceEnable_CNS   2

typedef uint8_t poe_v3_port_priority_TYP;
#define poe_v3_port_priority_low_CNS        0
#define poe_v3_port_priority_high_CNS       1
#define poe_v3_port_priority_critical_CNS   2

typedef uint8_t poe_v3_classLimit_TYP;
#define poe_v3_classLimit_unlimited_CNS     0
#define poe_v3_classLimit_class3_CNS        3
#define poe_v3_classLimit_class4_CNS        4
#define poe_v3_classLimit_class5_CNS        5
#define poe_v3_classLimit_class6_CNS        6
#define poe_v3_classLimit_class7_CNS        7

typedef uint8_t poe_v3_port_power_alloc_by_TYP;
#define poe_v3_port_power_alloc_by_hw_CNS     0
#define poe_v3_port_power_alloc_by_lldp_CNS   1
#define poe_v3_port_power_alloc_by_cdp_CNS    2

#define poe_v3_port_status_max_status_CNS poe_v3_port_status_off_unreachable_CNS /* must be updated whenever a new status added above */

typedef uint8_t poe_v3_btAutoClass_TYP;
#define poe_v3_btAutoClass_disabled_CNS     0
#define poe_v3_btAutoClass_auto_CNS         1
#define poe_v3_btAutoClass_force_CNS        2

typedef uint8_t poe_v3_btAutoClassAction_TYP;
#define poe_v3_btAutoClassAction_doNothing_CNS  0
#define poe_v3_btAutoClassAction_initCalc_CNS   1

#define poe_v3_powerRequest_NR_CNS          MAX_uint32_t

/*** port level messages structs ***/
typedef struct {    
    uint8_t                              logic_port_num;
    poe_v3_port_admin_TYP   port_admin_enable_disable;
    uint8_t                              reserved[2];
} poe_v3_msg_portEnable_STC;

typedef struct {    
    uint8_t                                  logic_port_num;
    poe_v3_physLayerClass_TYP   numOfEvents;
    uint8_t                                  reserved[2];
} poe_v3_msg_portPhysLayerClassMethod_STC;

typedef struct {
    uint8_t                              logic_port_num;
    poe_v3_legacyMode_TYP   legacyMode;
} poe_v3_msg_portLegacy_STC;

typedef struct {
    uint8_t                              logic_port_num;
    poe_v3_alt_b_mode_TYP   altb_mode;
    uint8_t                              reserved[2];
} poe_v3_msg_portAltB_STC;

typedef struct {
    uint8_t                              logic_port_num;
    uint8_t                              reserved[3];
    uint32_t                             powerLimit_mw_swap;
} poe_v3_msg_portPowerLimit_STC;

typedef struct {
    uint8_t                                  logic_port_num;
    poe_v3_port_priority_TYP    portPriority;
    uint8_t                                  reserved[2];
} poe_v3_msg_portPriority_STC;

typedef struct {
    uint8_t                              logic_port_num;
    poe_v3_power_mng_mode_TYP mng_mode;
    uint8_t                              reserved[2];
} poe_v3_msg_portPowerMngMode_STC;

typedef struct {
    uint8_t                              logic_port_num;
    poe_v3_classLimit_TYP   class_limit_val;
    uint8_t                              reserved[2];
} poe_v3_msg_portClassLimit_STC;

typedef struct {
    uint8_t                              logic_port_num;
    uint8_t                              reserved[3];
    uint32_t                             powerRequest_mW_swap;
    uint32_t                             powerRequestB_mW_swap;
} poe_v3_msg_portSetL2PowerReqLldp_STC;

typedef struct {
    uint8_t              logic_port_num;
    uint8_t              reserved[3];
    uint32_t             powerRequest_mW_swap[4];
} poe_v3_msg_portSetL2PowerReqList_STC;

typedef struct {
    uint8_t                                      logic_port_num;
    poe_v3_port_power_alloc_by_TYP     allocBy;
    uint8_t                                      reserved[2];
    uint32_t                                     powerAlloc_mw_swap;
    uint32_t                                     powerSupplied_mw_swap;
    uint32_t                                     powerAllocB_mw_swap;
    uint32_t                                     powerSuppliedB_mw_swap;
} poe_v3_msg_portGetAllocPower_STC;

typedef struct {
    uint8_t                                      logic_port_num;
    uint8_t                                      reserved[3];
    uint8_t                                      state; /* admin enable/disable */
    poe_v3_physLayerClass_TYP        num_of_events;
    poe_v3_legacyMode_TYP            legacy_support;
    poe_v3_alt_b_mode_TYP            altB_mode;
    poe_v3_port_priority_TYP         priority;
    poe_v3_port_priority_TYP         mng_mode;
    poe_v3_btAutoClass_TYP           auto_class;
    poe_v3_classLimit_TYP            class_limit;
    uint32_t                                     power_limit_swap;
} poe_v3_msg_portGetConfig_STC;

typedef struct {
    uint8_t                                      logic_port_num;
    poe_v3_port_active_channel_TYP    active_channel;
    uint8_t                                      reserved[2];
    uint32_t                                     voltage_in_volts_swap;
    uint32_t                                     current_in_ma_swap;
    uint32_t                                     power_in_mw_swap;
    uint32_t                                     classification_swap;
} poe_v3_msg_portPowerConsumInfo_STC;

typedef struct {
    uint8_t                              logic_port_num;
    poe_v3_port_status_TYP   port_status_a;
    poe_v3_port_status_TYP   port_status_b;
    uint8_t                              reserved;
} poe_v3_msg_portStatus_STC;

typedef struct {
    uint8_t                          logic_port_num;
    uint8_t                          reserved[3];
    uint32_t                         invalid_sinature_swap;
    uint32_t                         invalid_sinature_a_swap;
    uint32_t                         invalid_sinature_b_swap;
    uint32_t                         power_denied_swap;
    uint32_t                         power_denied_a_swap;
    uint32_t                         power_denied_b_swap;
    uint32_t                         overload_swap;
    uint32_t                         overload_a_swap;
    uint32_t                         overload_b_swap;
    uint32_t                         short_swap;
    uint32_t                         absent_swap;
    uint32_t                         absent_a_swap;
    uint32_t                         absent_b_swap;
} poe_v3_msg_portCounters_STC;

/** BT **/
typedef struct {
    uint8_t                              logic_port_num;
    poe_v3_btAutoClass_TYP  autoClass_status;
    uint16_t                             reserved;
} poe_v3_msg_portBtAutoClass_STC;

typedef struct {
    uint8_t                                      logic_port_num;
    poe_v3_btAutoClassAction_TYP    action;
    uint16_t                                     reserved;
} poe_v3_msg_portBtAutoClassAction_STC;

typedef struct {
    uint8_t                                      logic_port_num;
    poe_v3_port_active_channel_TYP   active_channel;
    uint8_t                                      reserved[2];
    uint32_t                                     volt_v_swap;
    uint32_t                                     current_ma_swap;
    uint32_t                                     consump_mw_swap;
    poe_v3_btSignatureType_TYP      signature_type_swap;
    poe_v3_btClassMethod_TYP        class_method_swap;
    uint16_t                                     measured_class_a_swap;
    uint16_t                                     assigned_class_a_swap;
    uint16_t                                     measured_class_b_swap;
    uint16_t                                     assigned_class_b_swap;
} poe_v3_msg_portBtPowerConsumInfo_STC;


/*** End of port level ***/

/***************************/

/*** cause messages id's ***/
#define poe_v3_cause_portStatus_CNS             0x80

typedef struct {    
    union{
        uint8_t          port_status_change_bitmap[8];
        uint64_t         port_change_num;
    };
} poe_v3_msg_causePortStatus_STC;

/* messages union */
typedef union {
    uint8_t                                              data[poe_v3_msg_max_data_size_CNS];
    /* system level */
    poe_v3_msg_sysPortMatrix_STC            sysPortMatrix_params;
    poe_v3_msg_sysPortSupportedStd_STC      sysPortSupportStd_params;
    poe_v3_msg_sysPowerBank_STC             sysPowerBank_params;
    poe_v3_msg_sysActiveRpsPowerBank_STC    sysActiveRpsPowerBank_params;
    poe_v3_msg_sysPowerLimitMode_STC        sysPowerLimitMode_params;
    poe_v3_msg_sysL2AllocSetting_STC        sysL2AllocSetting_params;
    poe_v3_msg_sysPowerConsumption_STC      sysPowerConsumption_params;
    poe_v3_msg_sysSystemVersion_STC         sysSystemVerion_params;
    poe_v3_msg_sysPseTemperature_STC        sysPseTemperature_params;
    poe_v3_msg_sysPseStatus_STC             sysPseStatus_params;
    poe_v3_msg_sysUpgReadyStatus_STC        sysUpgReadyStatus_params;
    poe_v3_msg_sysUpgDataTrans_STC          sysUpgDataTrans_params;
    poe_v3_msg_sysUpgStatus_STC             sysUpgStatus_params;
    poe_v3_msg_sysServiceNotification_STC   sysServiceNotification_params;
    poe_v3_msg_sysFirmwareReadiness_STC     sysFirmwareReadiness_params;

    /* port level */
    poe_v3_msg_portEnable_STC               portEnaleDisable_params;
    poe_v3_msg_portPhysLayerClassMethod_STC portPhysClass_params;
    poe_v3_msg_portLegacy_STC               portLegacy_params;
    poe_v3_msg_portAltB_STC                 portAltb_params;
    poe_v3_msg_portPowerLimit_STC           portPowerLimit_params;
    poe_v3_msg_portPriority_STC             portPriority_params;
    poe_v3_msg_portPowerMngMode_STC         portPowerMngMode_params;
    poe_v3_msg_portClassLimit_STC           portClassLimit_params;
    poe_v3_msg_portSetL2PowerReqLldp_STC    portL2PowerReqLldpSet_params;
    poe_v3_msg_portSetL2PowerReqList_STC    portL2PowerReqListSet_params;
    poe_v3_msg_portGetAllocPower_STC        portAllocPowerGet_params;
    poe_v3_msg_portPowerConsumInfo_STC      portPowerConsumInfo_params;
    poe_v3_msg_portStatus_STC               portStatus_params;
    poe_v3_msg_portCounters_STC             portCounters_params;
    poe_v3_msg_portGetConfig_STC            portConfigGet_params;
    /* port level - BT */
    poe_v3_msg_portBtAutoClass_STC          portBtAutoClass_params;
    poe_v3_msg_portBtAutoClassAction_STC    portBtAutoClassAction_params;
    poe_v3_msg_portBtPowerConsumInfo_STC    portBtPowerConsumInfo_params;
    /* cause level */
    poe_v3_msg_causePortStatus_STC          causePortStatus_params;
} poe_v3_msg_UNT;

/* PSE FW update - PSE FW header*/
typedef struct
{
    uint8_t              header_size;    /* header size, include this byte */
    uint32_t             version_id_swap;
} poe_v3_pseUpdate_fw_header_STC;

/**** Messages MACROs ****/
#define poe_v3_set_msg_opCode_MAC(_opcode, _level, _dir, _id)   \
    memset(&_opcode, 0, sizeof(_opcode));                                   \
    _opcode.params.level = _level;                                          \
    _opcode.params.direction = _dir;                                        \
    _opcode.params.msg_id_swap = swap16(_id);

#define poe_convert_hw_to_detection_status_MAC(_port_status, _detection_status)   \
    _detection_status = poe_detection_status_off_CNS;                \
    switch (_port_status) {                                                             \
        case poe_v3_port_status_off_inDetection_CNS:                  \
        case poe_v3_port_status_off_CapDetInvSig_CNS:               \                   \
            _detection_status = poe_detection_status_searching_CNS;       \
            break;                                                                      \
        case poe_v3_port_status_on_CapDetect_CNS:                         \
        case poe_v3_port_status_on_ResDetect_CNS:                         \
        case poe_v3_port_status_on_4Pair_CNS:                                \
        case poe_v3_port_status_on_NonStd_BTdevice_CNS:                        \
            _detection_status = poe_detection_status_deliveringPower_CNS; \
            break;                                                                      \
        case poe_v3_port_status_off_UserDisable_CNS:                      \
            _detection_status = poe_detection_status_off_CNS;        \
            break;                                                                      \                                                                    \                                                                     \
        default:                                                                        \
            _detection_status = poe_detection_status_fault_CNS;      \
            break;                                                                      \
    }

poe_op_result_t internal_create_object(poe_object_id_t *poe_object_id);
poe_op_result_t internal_poe_device_initialize(void);
bool poe_port_get_first_index(uint32_t *front_panel_index);
bool poe_port_get_next_index(uint32_t *front_panel_index);
poe_port_hw_type_t poe_get_port_poe_hw_type(uint32_t front_panel_index);
bool poe_port_get_physical_index(uint32_t front_panel_index, uint32_t *physical_index);
bool poe_port_get_second_physical_index(uint32_t front_panel_index, uint32_t *physical_index);
bool EXTHWG_POE_IPc_send_recieve_msg(bool send, uint32_t op_code, uint8_t data_len, uint8_t *data);
poe_op_result_t poe_v3_send_receive_msg(poe_v3_msg_level_TYP msg_type, poe_v3_msg_direction_TYP direction, uint16_t msg_id, uint8_t data_len, void *data_PTR);
poe_op_result_t poe_port_matrix_initialize();
poe_op_result_t poe_port_standard_initialize();
poe_op_result_t poe_port_set_admin_enable(uint32_t front_panel_index, bool enable);
poe_op_result_t poe_port_get_admin_enable(uint32_t front_panel_index, bool *enable);
uint16_t swap16(uint16_t value);

typedef struct {
    bool is_poe_device_initialized;
} global_poe;

#endif /** __POE_V3_H_ */