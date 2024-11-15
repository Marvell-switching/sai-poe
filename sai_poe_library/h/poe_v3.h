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
#define __POE_V3_H___CNS

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <SAI/inc/saitypes.h>

/* used by SAI - struct is in SAI coding format */
#pragma pack(push, 1)

typedef struct poe_object_id_t {
    uint32_t id;
    uint32_t object_type;
} poe_object_id_t;

typedef struct {
    bool is_poe_device_initialized;
} global_poe;

/* status */
typedef enum {
    POE_OP_OK_E = 0,
    POE_OP_FAILED_E,
    POE_OP_NOT_SUPPORTED_E,
} POE_OP_RESULT_ENT;

typedef enum {
    POE_PORT_HW_TYPE_AF_E = 0,
    POE_PORT_HW_TYPE_AT_E,
    POE_PORT_HW_TYPE_60W_E,
    POE_PORT_HW_TYPE_BT3_E,
    POE_PORT_HW_TYPE_BT4_E,
    /* must be last */
    POE_PORT_HW_TYPE_INVALID_E
} POE_PORT_HW_TYPE_ENT;

typedef uint32_t UNIT_TYPE;
#define UNIT_TYPE_NONE_CNS 0
#define UNIT_TYPE_PSE_CNS 1
#define UNIT_TYPE_PD_CNS 2
#define UNIT_TYPE_PSE_PD_CNS 3

typedef struct POE_POWER_MANAGEMENT_UNIT_DB_STC {
    /* set */
    uint32_t mainPsePowerMw;
    uint32_t mainPseConsumptionPowerMw;
    uint32_t calculatedPowerMw;
    uint32_t availablePowerMw;
} POE_POWER_MANAGEMENT_UNIT_DB_STC;

typedef uint8_t POWER_LIMIT_MODE;
#define POWER_LIMIT_MODE_PORT_CNS 0
#define POWER_LIMIT_MODE_CLASS_CNS 1

typedef struct POE_DEVICE_DB_STC {
    uint32_t deviceId;
    uint32_t totalPower;
    uint32_t powerConsumption;
    char *version;
    POWER_LIMIT_MODE powerLimitMode;
    uint32_t allocatedPower;
    POE_POWER_MANAGEMENT_UNIT_DB_STC powerManagement;
    UNIT_TYPE unit;
} POE_DEVICE_DB_STC;


typedef uint8_t POE_V3_PSE_STATUS;
#define POE_V3_PSE_STATUS_NR_CNS 0
#define POE_V3_PSE_STATUS_ACTIVE_CNS 1
#define POE_V3_PSE_STATUS_I2C_FAILURE_CNS 2
#define POE_V3_PSE_STATUS_NOT_PRESENT_CNS 0xFF

#define POE_MAX_NUM_OF_PSE_DEVS_IN_UNIT_CNS 16

typedef struct POE_DEVICE_SYS_STATUS {
    union{
        POE_V3_PSE_STATUS pseStatus[POE_MAX_NUM_OF_PSE_DEVS_IN_UNIT_CNS];
        uint8_t hwPseSt[POE_MAX_NUM_OF_PSE_DEVS_IN_UNIT_CNS];
    }param;
} POE_DEVICE_SYS_STATUS;

typedef struct POE_PSE_DB {
    uint32_t pseId;
    char *softwareVersion ;
    char *hardwareVersion;
    int16_t temperature;
    POE_DEVICE_SYS_STATUS status;
} POE_PSE_DB;

typedef uint16_t POE_V3_BT_CLASS;
#define POE_V3_BT_CLASS_NO_CLASS_CNS 0
#define POE_V3_BT_CLASS_CLASS_1_CNS 1
#define POE_V3_BT_CLASS_CLASS_2_CNS 2
#define POE_V3_BT_CLASS_CLASS_3_CNS 3
#define POE_V3_BT_CLASS_CLASS_4_CNS 4
#define POE_V3_BT_CLASS_CLASS_5_CNS 5
#define POE_V3_BT_CLASS_CLASS_6_CNS 6
#define POE_V3_BT_CLASS_CLASS_7_CNS 7
#define POE_V3_BT_CLASS_CLASS_8_CNS 8
#define POE_V3_BT_CLASS_NA_CNS 0xFFFF

typedef uint16_t POE_V3_BT_CLASS_METHOD;
#define POE_V3_BT_CLASS_METHOD_REGULAR_CNS 1
#define POE_V3_BT_CLASS_METHOD_AUTO_CLASS_CNS 2


typedef struct POE_BT_POWER_CLASSIFICATIONS_STC {
    POE_V3_BT_CLASS btPortAltASsMeasuredClass;  /* Ss or Ds-Alt-A measured class */
    POE_V3_BT_CLASS btPortAltASsAssignedClass;  /* Ss or Ds-Alt-A assigned class */
    POE_V3_BT_CLASS btPortAltBMeasuredClass;    /* Ds-Alt-B measured class */
    POE_V3_BT_CLASS btPortAltBAssignedClass;    /* Ds-Alt-B assigned class */
    POE_V3_BT_CLASS_METHOD btPortClassMethod;
} POE_BT_POWER_CLASSIFICATIONS_STC;

typedef struct POE_AT_POWER_CLASSIFICATIONS_STC {
    POE_V3_BT_CLASS pethPsePortPowerClassifications;
} POE_AT_POWER_CLASSIFICATIONS_STC;

typedef uint16_t POE_V3_BT_SIGNATURE;
#define POE_V3_BT_SIGNATURE_SINGLE_CNS 1
#define POE_V3_BT_SIGNATURE_DUAL_CNS 2

typedef struct POE_POWER_CLASSIFICATIONS_STC {
    POE_V3_BT_SIGNATURE signaturee;
    POE_AT_POWER_CLASSIFICATIONS_STC poeAtClass;
    POE_BT_POWER_CLASSIFICATIONS_STC poeBtClass;
} POE_POWER_CLASSIFICATIONS_STC;

typedef uint8_t POE_V3_PORT_ACTIVE_CHANNEL;
#define POE_V3_PORT_ACTIVE_CHANNEL_A_CNS 1
#define POE_V3_PORT_ACTIVE_CHANNEL_B_CNS 2
#define POE_V3_PORT_ACTIVE_CHANNEL_AB_CNS 3

typedef struct POE_OUTPUT_DATA_STC {
    POE_V3_PORT_ACTIVE_CHANNEL activeChannel;
    uint32_t outputVoltage;
    uint32_t outputCurrent;
    uint32_t outputPower;
} POE_OUTPUT_DATA_STC;

typedef uint8_t POE_PORT_DETECTION_STATUS;
#define POE_PORT_DETECTION_STATUS_OFF_CNS 1
#define POE_PORT_DETECTION_STATUS_SEARCHING_CNS 2
#define POE_PORT_DETECTION_STATUS_DELIVERING_POWER_CNS 3
#define POE_PORT_DETECTION_STATUS_FAULT_CNS 4

typedef uint8_t POE_V3_PORT_STATUS;
#define POE_V3_PORT_STATUS_ON_RES_DETECT_CNS 1
#define POE_V3_PORT_STATUS_ON_CAP_DETECT_CNS 2
#define POE_V3_PORT_STATUS_ON_4_PAIR_CNS 3
#define POE_V3_PORT_STATUS_ON_FORCE_4_PAIR_CNS 4
#define POE_V3_PORT_STATUS_OFF_VOLT_HIGH_CNS 5 /* Deprecated */
#define POE_V3_PORT_STATUS_OFF_VOLT_LOW_CNS 6
#define POE_V3_PORT_STATUS_OFF_HW_PIN_DIS_PORT_CNS 7
#define POE_V3_PORT_STATUS_OFF_USER_DISABLE_CNS 8
#define POE_V3_PORT_STATUS_OFF_IN_DETECTION_CNS 9
#define POE_V3_PORT_STATUS_OFF_PD_NO_STANDARD_CNS 10
#define POE_V3_PORT_STATUS_OFF_OVER_UNDER_LOAD_CNS 11
#define POE_V3_PORT_STATUS_OFF_UNDERLOAD_CNS 12
#define POE_V3_PORT_STATUS_OFF_OVERLOAD_CNS 13
#define POE_V3_PORT_STATUS_OFF_PWR_BUDG_EXC_CNS 14
#define POE_V3_PORT_STATUS_OFF_VOLT_INJ_CNS 15
#define POE_V3_PORT_STATUS_OFF_CAP_DET_INV_SIG_CNS 16
#define POE_V3_PORT_STATUS_OFF_DISCHARGED_CNS 17
#define POE_V3_PORT_STATUS_ON_FORCE_ON_CNS 18
#define POE_V3_PORT_STATUS_OFF_PW_ERR_CNS 19
#define POE_V3_PORT_STATUS_OFF_PW_BUDGET_CNS 20
#define POE_V3_PORT_STATUS_OFF_SHORT_COND_CNS 21
#define POE_V3_PORT_STATUS_OFF_OVER_TEMP_CNS 22
#define POE_V3_PORT_STATUS_OFF_DEVICE_HOT_CNS 23
#define POE_V3_PORT_STATUS_OFF_CLASS_ERROR_CNS 24
#define POE_V3_PORT_STATUS_OFF_RLOW_DETECT_CNS 25
#define POE_V3_PORT_STATUS_OFF_POWER_ON_VERIFICATION_FAULT_CNS 26
#define POE_V3_PORT_STATUS_ON_NON_STD_BTDEVICE_CNS 27
#define POE_V3_PORT_STATUS_OFF_UNREACHABLE_CNS 28
#define POE_V3_PORT_STATUS_ALT_B_SINGLE_SIGNATURE_CNS 255


typedef struct POE_DETECTION_STATUS_STC {
    /* input */
    /* output */
    bool capacitorSignatureDetected;
    POE_V3_PORT_STATUS poePseHwPortStatus;      /* PSE side - real port status from HW */
    uint32_t unknownErrorInternalStatus;
    POE_V3_PORT_STATUS poePseHwPortStatusAltB;
    uint32_t unknownErrorInternalStatusAltB;
} POE_DETECTION_STATUS_STC;


typedef enum {
    POE_PSE_PORT_POWER_PRIORITY_CRITICAL_E =  1,
    POE_PSE_PORT_POWER_PRIORITY_HIGH_E =      2,
    POE_PSE_PORT_POWER_PRIORITY_LOW_E =       3
} POE_PSE_PORT_POWER_PRIORITY_ENT;

typedef uint8_t POE_V3_POWER_MNG_MODE;
#define POE_V3_POWER_MNG_MODE_DYNAMIC_CNS 0
#define POE_V3_POWER_MNG_MODE_STATIC_CNS 1

typedef struct POE_PORT_CONFIGURABLE_DATA_STC {
    bool pethPsePortAdminEnable;
    POE_PSE_PORT_POWER_PRIORITY_ENT pethPsePortPowerPriority;
    uint32_t pethPsePortPowerLimit;
    bool legacySupportStatus;
    POE_V3_POWER_MNG_MODE powerMngStatus;
    POE_V3_BT_CLASS poePortClassLimit;
    bool numOfEvents;
} POE_PORT_CONFIGURABLE_DATA_STC;

typedef struct POE_PORT_POWER_CONSUMPTION_DATA_DB_STC {
    POE_POWER_CLASSIFICATIONS_STC poePortPowerClassifications;
    POE_OUTPUT_DATA_STC poePortOutputData;
    POE_DETECTION_STATUS_STC poePortDetectionStatus;
    uint32_t portStaticModeAllocPower;
    uint32_t portBtPrimaryAltAllocPower;
    uint32_t portBtSecondaryAltAllocPower;
} POE_PORT_POWER_CONSUMPTION_DATA_DB_STC;

/* Port POE DB, per physical port */
typedef struct POE_PORT_DB_STC {
    /* key */
    uint32_t frontPanelIndex;
    /* hw related params */
    POE_PORT_HW_TYPE_ENT portStandard;
    uint32_t physicalIndexA;
    uint32_t physicalIndexB;
    /* power related param s*/
    POE_PORT_POWER_CONSUMPTION_DATA_DB_STC powerConsumptionData;
    /* set params - user configurable data*/
    POE_PORT_CONFIGURABLE_DATA_STC configurableData;
    /* read only params */
    POE_DETECTION_STATUS_STC status;
    uint32_t maxPowerLimit;
    bool operStatus;
} POE_PORT_DB_STC;


#define poeGetSystemStatusStubCreateMac(__funcName)_CNS \
    BOOLEAN __funcName (                                               \
        BOOLEAN hwMode,                                                \
        /*!     OUTPUTS:        */                                      \
        POE_DEVICE_SYS_STATUS *oSysStatusPtr)

typedef enum {
    POE_COMMUNICATION_MODE_BLOCKING_E = 0,
    POE_COMMUNICATION_MODE_NON_BLOCKING_E,
    POE_COMMUNICATION_MODE_LAST_E
} POE_COMMUNICATION_MODE_ENT;

typedef enum {
    POE_GUARD_BAND_MODE_NOT_SUPPORTED_E = 0,
    POE_GUARD_BAND_MODE_DYNAMIC_E,
    POE_GUARD_BAND_MODE_STATIC_E
} POE_GUARD_BAND_MODE_ENT;

typedef enum {
    POE_PORT_BT_CHANNEL_ALT_A_E,
    POE_PORT_BT_CHANNEL_ALT_B_E,
    POE_PORT_BT_CHANNEL_ALT_BOTH_E
} POE_PORT_BT_CHANNEL_ALT_E;

/* Current Version Constants */
#define POE_V3_DRAGONITE_VERSION_NUM_CNS 0xe000100 /* November 26th, 2017: Dragonite FW 0xE.0x0.0x1.0x0 */

/**** General parameters ****/
#define POE_V3_MAX_NUM_OF_PSE_CNS 16
#define POE_V3_INVALID_TEMPERATURE_CNS 0x7FFF

#define POE_V3_MSG_PORT_LAYER_2_CDP_PSE_DATA_PORT_IS_ON_CDP_CNS 0x2000
#define POE_V3_MSG_PORT_LAYER_2_CDP_PSE_DATA_PORT_IS_ON_LLDP_CNS 0x3000

typedef uint8_t POE_V3_DEV_HW_VERSION;
#define POE_V3_DEV_HW_VERSION_LTC4291_CNS 0x38 /* 802.3 BT: LTC4291 */

/**** Message parameters ****/
#define EXT_DRV_IPC_MAX_MSG_SIZE_CNS 256
#define POE_V3_MSG_MAX_SIZE_CNS EXT_DRV_IPC_MAX_MSG_SIZE_CNS

#define POE_V3_MSG_HEADER_SIZE_CNS 8 /* Bytes */
#define POE_V3_MSG_MAX_DATA_SIZE_CNS (POE_V3_MSG_MAX_SIZE_CNS - POE_V3_MSG_HEADER_SIZE_CNS)

typedef uint8_t POE_V3_MSG_LEVEL;
/* POE_PD69200_MSG_SUB_GLOBAL */
#define POE_V3_MSG_LEVEL_SYSTEM_CNS 0x07
/* POE_PD69200_MSG_SUB_CHANNEL */
#define POE_V3_MSG_LEVEL_PORT_CNS 0x05
#define POE_V3_MSG_LEVEL_CAUSE_CNS 2
#define POE_V3_MSG_LEVEL_DEBUG_CNS 3

typedef uint8_t POE_V3_MSG_DIRECTION;
/* POE_PD69200_MSG_KEY_COMMAND */
#define POE_V3_MSG_DIR_GET_CNS 0x02
/* POE_PD69200_MSG_KEY_REQUEST */
#define POE_V3_MSG_DIR_SET_CNS 0x00

typedef struct POE_V3_MSG_OPCODE_INFO_STC {
    POE_V3_MSG_DIRECTION direction;  /* key */
    uint8_t _unused;  /* echo */
    POE_V3_MSG_LEVEL level;  /* sub */
    uint8_t msgIdSwap;  /* sub1 */
} POE_V3_MSG_OPCODE_INFO_STC;

typedef union POE_V3_MSG_OP_CODE_STC {
    POE_V3_MSG_OPCODE_INFO_STC params;
    uint32_t opCodeNum32;
} POE_V3_MSG_OP_CODE_STC;


/*** system messages id's ***/
#define POE_V3_SYS_MSG_PORT_MATRIX_CNS 0x1
#define POE_V3_SYS_MSG_PORT_SUPPORT_STANDARD_CNS 0x2
#define POE_V3_SYS_MSG_POWER_BANK_CONFIG_CNS 0x4
#define POE_V3_SYS_MSG_ACTIVE_RPS_POWER_BANK_CNS 0x10
#define POE_V3_SYS_MSG_POWER_LIMIT_MODE_CNS 0x20
#define POE_V3_SYS_MSG_L2_ALLOC_SETTING_CNS 0x40
#define POE_V3_SYS_MSG_POWER_CONSUMPTION_CNS        (0x0B)
#define POE_V3_SYS_MSG_POWER_CONSUMPTION_MAIN_CNS   (0x17)
#define POE_V3_SYS_MSG_SYSTEM_VERSION_CNS           (0x1E)
#define POE_V3_SYS_MSG_SYSTEM_VERSION_SOFTWARE_CNS  (0x21)
#define POE_V3_SYS_MSG_PSE_TEMPERATURE_CNS 0x101
#define POE_V3_SYS_MSG_UPG_READY_STATUS_CNS 0x102
#define POE_V3_SYS_MSG_UPG_DATA_TRANS_CNS 0x103
#define POE_V3_SYS_MSG_UPG_STATUS_CNS 0x104
#define POE_V3_SYS_MSG_SERVICE_NOTIFICATION_CNS 0x105
#define POE_V3_SYS_MSG_PSE_STATUS_CNS 0x106
#define POE_V3_SYS_MSG_FIRMWARE_READINESS_CNS 0x107

/*** system messages types ***/
typedef uint8_t POE_V3_PORT_SUP_STANDARD;
#define POE_V3_PORT_SUP_STANDARD_AF_CNS 1
#define POE_V3_PORT_SUP_STANDARD_AT_CNS 2
#define POE_V3_PORT_SUP_STANDARD_60_CNS 3
#define POE_V3_PORT_SUP_STANDARD_BTE2_CNS 4
#define POE_V3_PORT_SUP_STANDARD_BTE3_CNS 5
#define POE_V3_PORT_SUP_STANDARD_BTE4_CNS 6

typedef uint8_t POE_V3_POWER_LIMIT_MODE;
#define POE_V3_POWER_LIMIT_MODE_PORT_CNS 0
#define POE_V3_POWER_LIMIT_MODE_CLASS_CNS 1

typedef uint8_t POE_V3_OPERATION_MODE;
#define POE_V3_OPERATION_MODE_INDEPENDENT_CNS 1
#define POE_V3_OPERATION_MODE_NORMAL_CNS 2
#define POE_V3_OPERATION_MODE_NO_CHANGE         (0xFF)

typedef uint8_t POE_V3_L2_ALLOC_PRIORITY;
#define POE_V3_L2_ALLOC_PRIORITY_NORMAL_CNS 0
#define POE_V3_L2_ALLOC_PRIORITY_HIGH_CNS 1

typedef uint8_t POE_V3_L2_ALLOC_MNG_MODE;
#define POE_V3_L2_ALLOC_MNG_MODE_AS_PORT_CNS 0
#define POE_V3_L2_ALLOC_MNG_MODE_STATIC_CNS 1

typedef uint8_t POE_V3_UPG_READINESS;
#define POE_V3_UPG_READINESS_REFUSE_CNS 0
#define POE_V3_UPG_READINESS_READY_CNS 1

typedef uint16_t POE_V3_UPG_BLOCKE;
#define POE_V3_UPG_BLOCKE_STANDARD_CNS 0
#define POE_V3_UPG_BLOCKE_FINAL_CNS 1
#define POE_V3_UPG_BLOCKE_UN_PL_TERM_CNS 2 /* unplanned termination */

typedef uint8_t POE_V3_UPG_STATUS_CODE;
#define POE_V3_UPG_STATUS_CODE_SUCCESS_CNS 0
#define POE_V3_UPG_BLOCKE_RETRY_BLOCK_CNS 1
#define POE_V3_UPG_BLOCKE_RESTART_CNS 2
#define POE_V3_UPG_BLOCKE_ABORT_CNS 3
#define POE_V3_UPG_BLOCKE_PROCESSING_CNS 4

typedef uint8_t POE_V3_FIRMWARE_READINESS;
#define POE_V3_FIRMWARE_READINESS_INIT_CNS 0
#define POE_V3_FIRMWARE_READINESS_READY_CNS 1

#define POE_MAX_NUM_OF_PHYS_PORTS_CNS 48
#define POE_MAX_NUM_OF_POWER_BANKS_CNS 16

/*** system messages messages structs ***/
typedef struct POE_V3_MSG_SYS_PORT_MATRIX_STC {
    struct {
        uint8_t  logicalPort;
        uint8_t  physPort;
    } physicLogicalPair[POE_MAX_NUM_OF_PHYS_PORTS_CNS];
} POE_V3_MSG_SYS_PORT_MATRIX_STC;

typedef struct POE_V3_MSG_SYS_PORT_SUPPORTED_STD_STC {
    struct {
        uint8_t                                 logicPort;
        POE_V3_PORT_SUP_STANDARD portSupportedStd;
    } supportedStdData[POE_MAX_NUM_OF_PHYS_PORTS_CNS];
} POE_V3_MSG_SYS_PORT_SUPPORTED_STD_STC;

typedef struct POE_V3_MSG_SYS_POWER_BANK_STC {
    uint16_t powerBankWSwap[POE_MAX_NUM_OF_POWER_BANKS_CNS];
} POE_V3_MSG_SYS_POWER_BANK_STC;

typedef struct POE_V3_MSG_SYS_ACTIVE_RPS_POWER_BANK_STC {
    uint8_t activeRpsPowerBankIndex;
} POE_V3_MSG_SYS_ACTIVE_RPS_POWER_BANK_STC;

typedef struct POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC {
    POWER_LIMIT_MODE   limitMode;
} POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC;

typedef struct POE_V3_MSG_SYS_L2_ALLOC_SETTING_STC {
    POE_V3_L2_ALLOC_PRIORITY   priority;
    POE_V3_L2_ALLOC_MNG_MODE   mngMode;
} POE_V3_MSG_SYS_L2_ALLOC_SETTING_STC;

typedef struct POE_V3_MSG_SYS_POWER_SUPPLY_PARAMS_STC {
    uint8_t type;
    uint8_t power_bank;
    uint16_t power_consumption;
    uint16_t total_power;
} POE_V3_MSG_SYS_POWER_SUPPLY_PARAMS_STC;

typedef struct POE_V3_MSG_SYS_SERVICE_NOTIFICATION_STC {
    POE_V3_OPERATION_MODE                        operationMode;
    uint8_t                                     reserved[3];
} POE_V3_MSG_SYS_SERVICE_NOTIFICATION_STC;

typedef struct POE_V3_MSG_SYS_FIRMWARE_READINESS_STC {
    POE_V3_FIRMWARE_READINESS                   firmwareReadiness;
    uint8_t                                     reserved[3];
} POE_V3_MSG_SYS_FIRMWARE_READINESS_STC;

#define POE_FW_VERSION_NUM_OF_BYTES_CNS 4

typedef struct POE_V3_MSG_SYS_SYSTEM_VERSION_STC {
    /* input */
    uint8_t type;
    /* outputs */
    uint8_t prod;
    uint8_t major;
    uint8_t minor;
    uint8_t par;
} POE_V3_MSG_SYS_SYSTEM_VERSION_STC;

typedef struct POE_V3_MSG_SYS_PSE_TEMPERATURE_STC {
    /* outputs */
    int16_t              pseTempSwap[POE_V3_MAX_NUM_OF_PSE_CNS];
} POE_V3_MSG_SYS_PSE_TEMPERATURE_STC;

typedef struct POE_V3_MSG_SYS_PSE_STATUS_STC {
    /* outputs */
    POE_V3_PSE_STATUS    pseStatus[POE_V3_MAX_NUM_OF_PSE_CNS];
} POE_V3_MSG_SYS_PSE_STATUS_STC;

typedef struct POE_V3_MSG_SYS_UPG_READY_STATUS_STC {
    /* outputs */
    POE_V3_UPG_READINESS    readiness;
    uint8_t                                  reserved;
    uint16_t                                 blockSizeSwp;
} POE_V3_MSG_SYS_UPG_READY_STATUS_STC;

#define POE_V3_MSG_UPG_DATA_MAX_SIZE_CNS (POE_V3_MSG_MAX_DATA_SIZE_CNS-12)

typedef struct POE_V3_MSG_SYS_UPG_DATA_TRANS_STC {
    uint32_t             pseVersionIdSwp;
    uint16_t             blockNumSwp;
    uint16_t             blockeSwp;
    uint16_t             checksumSwp;
    uint16_t             reserved;
    uint8_t              data[POE_V3_MSG_UPG_DATA_MAX_SIZE_CNS];
} POE_V3_MSG_SYS_UPG_DATA_TRANS_STC;

typedef struct {
    uint16_t                                 block_num_swp;
    POE_V3_UPG_STATUS_CODE                   statusCode;
    bool                                     err_exists;
    char                                     err_msg[32];
} POE_V3_MSG_SYS_UPG_STATUS_STC;

/*** End of system level ***/

/***************************/

/*** port messages id's ***/

/* POE_PD69200_MSG_SUB1_EN_DIS */
#define POE_V3_PORT_MSG_PORT_PARAMS_CNS             (0xC0)
/* POE_PD69200_BT_MSG_SUB1_PORTS_CLASS */
#define POE_V3_PORT_MSG_PORT_CLASS_CNS              (0xC4)
#define POE_V3_PORT_MSG_PORT_MEASUREMENT_CNS        (0xC5)
#define POE_V3_PORT_MSG_LEGACY_DETECTED_CNS 0x12
#define POE_V3_PORT_MSG_ALT_B_ENABLE_CNS 0x14
/* POE_PD69200_MSG_SUB1_SUPPLY */
#define POE_V3_PORT_MSG_PORT_POWER_LIMIT_CNS 0x0B
#define POE_V3_PORT_MSG_PORT_PRIORITY_CNS 0x21
#define POE_V3_PORT_MSG_POWER_MNG_CNS 0x22
#define POE_V3_PORT_MSG_BT_AUTO_CLASS_CNS 0x23
#define POE_V3_PORT_MSG_PORT_CLASS_LIMIT_CNS 0x24
#define POE_V3_PORT_MSG_L2_REQ_POWER_LLDP_CNS 0x40
#define POE_V3_PORT_MSG_L2_REQ_POWER_LINS_CNS 0x41
#define POE_V3_PORT_MSG_ALLOC_POWER_CNS 0x42
#define POE_V3_PORT_MSG_BT_MANUAL_AUTO_CLASS_CNS 0x43
#define POE_V3_PORT_MSG_POWER_CONSUM_INFO_CNS 0x80
/* POE_PD69200_BT_MSG_SUB1_PORTS_PARAMETERS */
#define POE_V3_PORT_MSG_PORT_STATUS_CNS 0xC0
#define POE_V3_PORT_MSG_PORT_COUNTERS_CNS 0x82
#define POE_V3_PORT_MSG_PORT_CONFIG_CNS 0x83

/*** port messages types ***/
#define POE_V3_BT_PORT_MODE_NO_CHANGE           (0x0F)
#define POE_V3_BT_PORT_CLASS_ERROR_NO_CHANGE    (0xF0)
#define POE_V3_BT_PORT_MODE_POWER_NO_CHANGE     (0x00)

typedef uint8_t POE_V3_PORT_ADMIN;
#define POE_V3_PORT_ADMIN_DISABLE_CNS   (0x00)
#define POE_V3_PORT_ADMIN_ENABLE_CNS    (0x01)
#define POE_V3_PORT_ADMIN_NO_CHANGE     (0xFF)

typedef uint8_t POE_V3_PHYS_LAYER_CLASS;
#define POE_V3_PHYS_LAYER_CLASS_1_EVENT_CNS   1
#define POE_V3_PHYS_LAYER_CLASS_2_EVENT_CNS   2

typedef uint8_t POE_V3_LEGACY_MODE;
#define POE_V3_LEGACY_MODE_DISABLE_CNS       0
#define POE_V3_LEGACY_MODE_ENABLE_CNS        1
#define POE_V3_LEGACY_MODE_AUTO_CNS          2

typedef uint8_t POE_V3_ALT_B_MODE;
#define POE_V3_ALT_B_MODE_DISABLE_CNS       0
#define POE_V3_ALT_B_MODE_ENABLE_CNS        1
#define POE_V3_ALT_B_MODE_FORCE_ENABLE_CNS   2

typedef uint8_t POE_V3_PORT_PRIORITY;
#define POE_V3_PORT_PRIORITY_LOW_CNS        (0x03)
#define POE_V3_PORT_PRIORITY_HIGH_CNS       (0x02)
#define POE_V3_PORT_PRIORITY_CRITICAL_CNS   (0x01)
#define POE_V3_PORT_PRIORITY_NO_CHANGE      (0xFF)


typedef uint8_t POE_V3_CLASS_LIMIT;
#define POE_V3_CLASS_LIMIT_UNLIMITED_CNS     0
#define POE_V3_CLASS_LIMIT_CLASS3_CNS        3
#define POE_V3_CLASS_LIMIT_CLASS4_CNS        4
#define POE_V3_CLASS_LIMIT_CLASS5_CNS        5
#define POE_V3_CLASS_LIMIT_CLASS6_CNS        6
#define POE_V3_CLASS_LIMIT_CLASS7_CNS        7

typedef uint8_t POE_V3_PORT_POWER_ALLOC_BY;
#define POE_V3_PORT_POWER_ALLOC_BY_HW_CNS     0
#define POE_V3_PORT_POWER_ALLOC_BY_LLDP_CNS   1
#define POE_V3_PORT_POWER_ALLOC_BY_CDP_CNS    2

#define POE_V3_PORT_STATUS_MAX_STATUS_CNS POE_V3_PORT_STATUS_OFF_UNREACHABLE_CNS

typedef uint8_t POE_V3_BT_AUTO_CLASS;
#define POE_V3_BT_AUTO_CLASS_DISABLED_CNS     0
#define POE_V3_BT_AUTO_CLASS_AUTO_CNS         1
#define POE_V3_BT_AUTO_CLASS_FORCE_CNS        2

typedef uint8_t POE_V3_BT_AUTO_CLASS_ACTION;
#define POE_V3_BT_AUTO_CLASS_ACTION_DO_NOTHING_CNS  0
#define POE_V3_BT_AUTO_CLASS_ACTION_INIT_CALC_CNS   1

#define POE_V3_POWER_REQUEST_NR_CNS          MAX_UINT32_T

typedef struct POE_V3_MSG_PORT_PARAMS_SET_STC {
    uint8_t logic_port;
    uint8_t enable;
    uint8_t port_mode;
    uint8_t opmode;
    uint8_t power_mode;
    uint8_t priority;
} POE_V3_MSG_PORT_PARAMS_SET_STC;

typedef struct POE_V3_MSG_PORT_PARAMS_GET_STC {
    uint8_t logic_port;
    uint8_t status;
    uint8_t enable;
    uint8_t opmode;
    uint8_t priority;
} POE_V3_MSG_PORT_PARAMS_GET_STC;

typedef struct POE_V3_MSG_PORT_PHYS_LAYER_CLASS_METHOD_STC {
    uint8_t                                  logicPortNum;
    POE_V3_PHYS_LAYER_CLASS   numOfEvents;
    uint8_t                                  reserved[2];
} POE_V3_MSG_PORT_PHYS_LAYER_CLASS_METHOD_STC;

typedef struct POE_V3_MSG_PORT_LEGACY_STC {
    uint8_t                              logicPortNum;
    POE_V3_LEGACY_MODE   legacyMode;
} POE_V3_MSG_PORT_LEGACY_STC;

typedef struct POE_V3_MSG_PORT_ALT_B_STC {
    uint8_t                              logicPortNum;
    POE_V3_ALT_B_MODE                        altbMode;
    uint8_t                              reserved[2];
} POE_V3_MSG_PORT_ALT_B_STC;

typedef struct POE_V3_MSG_PORT_CLASS_STC {
    uint8_t                              logicPortNum;
    uint8_t                              measured_class;
    uint8_t                              assigned_class;
    uint16_t                             powerLimitW;
} POE_V3_MSG_PORT_CLASS_STC;

typedef struct POE_V3_MSG_PORT_PRIORITY_STC {
    uint8_t                                  logicPortNum;
    POE_V3_PORT_PRIORITY                        portPriority;
    uint8_t                                  reserved[2];
} POE_V3_MSG_PORT_PRIORITY_STC;

typedef struct POE_V3_MSG_PORT_POWER_MNG_MODE_STC {
    uint8_t                              logicPortNum;
    POE_V3_POWER_MNG_MODE mngMode;
    uint8_t                              reserved[2];
} POE_V3_MSG_PORT_POWER_MNG_MODE_STC;

typedef struct POE_V3_MSG_PORT_CLASS_LIMIT_STC {
    uint8_t                              logicPortNum;
    POE_V3_CLASS_LIMIT   classLimitVal;
    uint8_t                              reserved[2];
} POE_V3_MSG_PORT_CLASS_LIMIT_STC;

typedef struct POE_V3_MSG_PORT_SET_L2_POWER_REQ_LLDP_STC {
    uint8_t                              logicPortNum;
    uint8_t                              reserved[3];
    uint32_t                             powerRequestMwSwap;
    uint32_t                             powerRequestBMwSwap;
} POE_V3_MSG_PORT_SET_L2_POWER_REQ_LLDP_STC;

typedef struct POE_V3_MSG_PORT_SET_L2_POWER_REQ_LIST_STC {
    uint8_t              logicPortNum;
    uint8_t              reserved[3];
    uint32_t             powerRequestMwSwap[4];
} POE_V3_MSG_PORT_SET_L2_POWER_REQ_LIST_STC;

typedef struct POE_V3_MSG_PORT_GET_ALLOC_POWER_STC {
    uint8_t                                      logicPortNum;
    POE_V3_PORT_POWER_ALLOC_BY     allocBy;
    uint8_t                                      reserved[2];
    uint32_t                                     powerAllocMwSwap;
    uint32_t                                     powerSuppliedMwSwap;
    uint32_t                                     powerAllocBMwSwap;
    uint32_t                                     powerSuppliedBMwSwap;
} POE_V3_MSG_PORT_GET_ALLOC_POWER_STC;

typedef struct POE_V3_MSG_PORT_GET_CONFIG_STC {
    uint8_t                                      logicPortNum;
    uint8_t                                      reserved[3];
    uint8_t                                      state; /* admin enable/disable */
    POE_V3_PHYS_LAYER_CLASS                          numOfEvents;
    POE_V3_LEGACY_MODE                              legacySupport;
    POE_V3_ALT_B_MODE                                altBMode;
    POE_V3_PORT_PRIORITY                            priority;
    POE_V3_PORT_PRIORITY                            mngMode;
    POE_V3_BT_AUTO_CLASS                             autoClass;
    POE_V3_CLASS_LIMIT                              classLimit;
    uint32_t                                     powerLimitSwap;
} POE_V3_MSG_PORT_GET_CONFIG_STC;

typedef struct POE_V3_MSG_PORT_POWER_CONSUM_INFO_STC {
    uint8_t                                      logicPortNum;
    POE_V3_PORT_ACTIVE_CHANNEL                       activeChannel;
    uint8_t                                      reserved[2];
    uint32_t                                     voltageInVoltsSwap;
    uint32_t                                     currentInMaSwap;
    uint32_t                                     powerInMwSwap;
    uint32_t                                     classificationSwap;
} POE_V3_MSG_PORT_POWER_CONSUM_INFO_STC;

typedef struct POE_V3_MSG_PORT_STATUS_STC {
    uint8_t                          logicPortNum;
    uint8_t                          reserved[3];
    POE_V3_PORT_STATUS                              portStatusA;
    POE_V3_PORT_STATUS                              portStatusB;
} POE_V3_MSG_PORT_STATUS_STC;

typedef struct POE_V3_MSG_PORT_COUNTERS_STC {
    uint8_t                          logicPortNum;
    uint8_t                          reserved[3];
    uint32_t                         invalidSinatureSwap;
    uint32_t                         invalidSinatureASwap;
    uint32_t                         invalidSinatureBSwap;
    uint32_t                         powerDeniedSwap;
    uint32_t                         powerDeniedASwap;
    uint32_t                         powerDeniedBSwap;
    uint32_t                         overloadSwap;
    uint32_t                         overloadASwap;
    uint32_t                         overloadBSwap;
    uint32_t                         shortSwap;
    uint32_t                         absentSwap;
    uint32_t                         absentASwap;
    uint32_t                         absentBSwap;
} POE_V3_MSG_PORT_COUNTERS_STC;

/** BT **/
typedef struct POE_V3_MSG_PORT_BT_AUTO_CLASS_STC {
    uint8_t                              logicPortNum;
    POE_V3_BT_AUTO_CLASS  autoClassStatus;
    uint16_t                             reserved;
} POE_V3_MSG_PORT_BT_AUTO_CLASS_STC;

typedef struct POE_V3_MSG_PORT_BT_AUTO_CLASS_ACTION_STC {
    uint8_t                                      logicPortNum;
    POE_V3_BT_AUTO_CLASS_ACTION                       action;
    uint16_t                                     reserved;
} POE_V3_MSG_PORT_BT_AUTO_CLASS_ACTION_STC;

typedef struct POE_V3_MSG_PORT_MEASUREMENTS_STC {
    uint8_t  logicPortNum;
    uint16_t current;
    uint16_t power_consumption;
    uint16_t voltage;
} POE_V3_MSG_PORT_MEASUREMENTS_STC;

/*** End of port level ***/

/***************************/

/*** cause messages id's ***/
#define POE_V3_CAUSE_PORT_STATUS_CNS 0x80

typedef struct POE_V3_MSG_CAUSE_PORT_STATUS_STC {
    union{
        uint8_t          portStatusChangeBitmap[8];
        uint64_t         portChangeNum;
    };
} POE_V3_MSG_CAUSE_PORT_STATUS_STC;

/* messages union */
typedef union {
    uint8_t                                              data[POE_V3_MSG_MAX_DATA_SIZE_CNS];
    /* system level */
    POE_V3_MSG_SYS_PORT_MATRIX_STC            sysPortMatrixParams;
    POE_V3_MSG_SYS_PORT_SUPPORTED_STD_STC      sysPortSupportStdParams;
    POE_V3_MSG_SYS_POWER_BANK_STC             sysPowerBankParams;
    POE_V3_MSG_SYS_ACTIVE_RPS_POWER_BANK_STC    sysActiveRpsPowerBankParams;
    POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC        sysPowerLimitModeParams;
    POE_V3_MSG_SYS_L2_ALLOC_SETTING_STC        sysL2AllocSettingParams;
    POE_V3_MSG_SYS_POWER_SUPPLY_PARAMS_STC      sysPowerSupplyParams;
    POE_V3_MSG_SYS_SYSTEM_VERSION_STC         sysSystemVerionParams;
    POE_V3_MSG_SYS_PSE_TEMPERATURE_STC        sysPseTemperatureParams;
    POE_V3_MSG_SYS_PSE_STATUS_STC             sysPseStatusParams;
    POE_V3_MSG_SYS_UPG_READY_STATUS_STC        sysUpgReadyStatusParams;
    POE_V3_MSG_SYS_UPG_DATA_TRANS_STC          sysUpgDataTransParams;
    POE_V3_MSG_SYS_UPG_STATUS_STC             sysUpgStatusParams;
    POE_V3_MSG_SYS_SERVICE_NOTIFICATION_STC   sysServiceNotificationParams;
    POE_V3_MSG_SYS_FIRMWARE_READINESS_STC     sysFirmwareReadinessParams;

    /* port level */
    POE_V3_MSG_PORT_PARAMS_GET_STC              portParamsGet;
    POE_V3_MSG_PORT_PARAMS_SET_STC              portParamsSet;
    POE_V3_MSG_PORT_PHYS_LAYER_CLASS_METHOD_STC portPhysClassParams;
    POE_V3_MSG_PORT_LEGACY_STC               portLegacyParams;
    POE_V3_MSG_PORT_ALT_B_STC                 portAltbParams;
    POE_V3_MSG_PORT_CLASS_STC                   portClassParams;
    POE_V3_MSG_PORT_PRIORITY_STC             portPriorityParams;
    POE_V3_MSG_PORT_POWER_MNG_MODE_STC         portPowerMngModeParams;
    POE_V3_MSG_PORT_CLASS_LIMIT_STC           portClassLimitParams;
    POE_V3_MSG_PORT_SET_L2_POWER_REQ_LLDP_STC    portL2PowerReqLldpSetParams;
    POE_V3_MSG_PORT_SET_L2_POWER_REQ_LIST_STC    portL2PowerReqListSetParams;
    POE_V3_MSG_PORT_GET_ALLOC_POWER_STC       portAllocPowerGetParams;
    POE_V3_MSG_PORT_POWER_CONSUM_INFO_STC     portPowerConsumInfoParams;
    POE_V3_MSG_PORT_STATUS_STC              portStatusParams;
    POE_V3_MSG_PORT_COUNTERS_STC            portCountersParams;
    POE_V3_MSG_PORT_GET_CONFIG_STC           portConfigGetParams;
    /* port level - BT */
    POE_V3_MSG_PORT_BT_AUTO_CLASS_STC         portBtAutoClassParams;
    POE_V3_MSG_PORT_BT_AUTO_CLASS_ACTION_STC    portBtAutoClassActionParams;
    POE_V3_MSG_PORT_MEASUREMENTS_STC            portBtPowerMeasurements;
    /* cause level */
    POE_V3_MSG_CAUSE_PORT_STATUS_STC         causePortStatusParams;
} POE_V3_MSG_UNT_STC;

/* PSE FW update - PSE FW header*/
typedef struct
{
    uint8_t              headerSize;    /* header size, include this byte */
    uint32_t             versionIdSwap;
} POE_V3_PSE_UPDATE_FW_HEADER_STC;


/**** Messages MACROs ****/
#define poeV3SetMsgOpCodeMac(_opcode, _level, _dir, _id) \
    memset(&_opcode, 0, sizeof(_opcode));                                   \
    _opcode.params.level = _level;                                          \
    _opcode.params.direction = _dir;                                        \
    _opcode.params.msgIdSwap = (_id);

#define poeConvertHwToDetectionStatusMac(_portStatus, _detectionStatus) \
    _detectionStatus = poeDetectionStatusOffCNS;                \
    switch (_portStatus) {                                                             \
        case poeV3PortStatusOffInDetectionCNS:                  \
        case poeV3PortStatusOffCapDetInvSigCNS:               \                   \
            _detectionStatus = poeDetectionStatusSearchingCNS;       \
            break;                                                                      \
        case poeV3PortStatusOnCapDetectCNS:                         \
        case poeV3PortStatusOnResDetectCNS:                         \
        case poeV3PortStatusOn4PairCNS:                                \
        case poeV3PortStatusOnNonStdBTdeviceCNS:                        \
            _detectionStatus = poeDetectionStatusDeliveringPowerCNS; \
            break;                                                                      \
        case poeV3PortStatusOffUserDisableCNS:                      \
            _detectionStatus = poeDetectionStatusOffCNS;        \
            break;                                                                      \                                                                    \                                                                     \
        default:                                                                        \
            _detectionStatus = poeDetectionStatusFaultCNS;      \
            break;                                                                      \
    }

POE_OP_RESULT_ENT InternalCreateObject(poe_object_id_t *poeObjectId);
POE_OP_RESULT_ENT poeInitialize(void);
bool poePortGetFirstIndex(uint32_t *frontPanelIndex);
bool poePortGetNextIndex(uint32_t *frontPanelIndex);
POE_PORT_HW_TYPE_ENT poeGetPortpoeHwe(uint32_t frontPanelIndex);
bool poePortGetPhysicalIndex(uint32_t frontPanelIndex, uint32_t *physicalIndex);
bool poePortGetSecondPhysicalIndex(uint32_t frontPanelIndex, uint32_t *physicalIndex);
bool exthwgpoeIpcSendRecieveMsg(bool send, uint32_t opCode, uint8_t dataLen, uint8_t *data);
POE_OP_RESULT_ENT poeV3SendReceiveMsg(POE_V3_MSG_LEVEL msge, POE_V3_MSG_DIRECTION direction, uint16_t msgId, uint8_t dataLen, uint8_t *dataPtr);
POE_OP_RESULT_ENT poePortMatrixInitialize();
POE_OP_RESULT_ENT poePortStandardInitialize();
POE_OP_RESULT_ENT poePowerBankInitialize();
POE_OP_RESULT_ENT poeDevGetTotalPower(int32_t poeDevNum, int32_t *totalPowerPtr);
POE_OP_RESULT_ENT poeDevGetPowerConsumption(int32_t poeDevNum, int32_t *powerConsumptionMwPtr);
POE_OP_RESULT_ENT poeDevGetVersion(int32_t poeDevNum, char *versionPtr);
POE_OP_RESULT_ENT poeDevGetPowerLimitMode(uint32_t poeDevNum, uint32_t *powerLimitPtr);
POE_OP_RESULT_ENT poeDevSetPowerLimitMode(uint32_t poeDevNum, uint32_t powerLimitPtr);
POE_OP_RESULT_ENT poePseGetSoftwareVersion(int32_t poePseNum, char *versionPtr);
POE_OP_RESULT_ENT poePseGetHardwareVersion(int32_t poePseNum, char *versionPtr);
POE_OP_RESULT_ENT poePseGetTemperature(int32_t poePseNum, int16_t *temperaturePtr);
POE_OP_RESULT_ENT poePseGetStatus(int32_t poePseNum, int16_t *statusPtr);
POE_OP_RESULT_ENT poePortGetPortStandard(uint32_t frontPanelIndex, uint32_t *portStandardPtr);
POE_OP_RESULT_ENT poePortSetAdminEnable(uint32_t frontPanelIndex, const bool enable);
POE_OP_RESULT_ENT poePortGetAdminEnable(uint32_t frontPanelIndex, bool *enablePtr);
POE_OP_RESULT_ENT poePortSetPowerLimit(uint32_t frontPanelIndex, const uint32_t powerLimit);
POE_OP_RESULT_ENT poePortGetPowerLimit(uint32_t frontPanelIndex, uint32_t *powerLimitPtr);
POE_OP_RESULT_ENT poePortSetPowerPriority(uint32_t frontPanelIndex, const uint32_t powerPriority);
POE_OP_RESULT_ENT poePortGetPowerConsumption(uint32_t frontPanelIndex, sai_poe_port_power_consumption_t *powerConsumptionPtr);
POE_OP_RESULT_ENT poePortGetStatus (uint32_t frontPanelIndex, uint32_t *statusPtr);
POE_OP_RESULT_ENT poePortGetPowerPriority (uint32_t frontPanelIndex, uint32_t *statusPtr);
uint16_t swap16(uint16_t value);
uint32_t swap32(uint32_t value);
uint32_t getNumOfPse();
uint32_t getNumOfPorts();
uint32_t getNumOfDevices();

#pragma pack(pop)

#endif /** __POE_V3_H__ */