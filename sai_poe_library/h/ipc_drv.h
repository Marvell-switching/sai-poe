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

#include <h/extIpcDrv.h>

#define EXTHWG_POE_IPC_MAX_REQUEST_MESSAGE_SIZE_CNS 248
#define EXTHWG_POE_IPC_MAX_RESPONSE_MESSAGE_SIZE_CNS 244

#define EXTHWG_POE_IPC_MEM_BLOCK_SIZE_CNS 512

extern uint32_t EXTHWG_POE_Ipc_WAIT_FOR_RESPONSE_TIME_uSec;
extern uint32_t EXTHWG_POE_Ipc_WAIT_FOR_RESPONSE_NUM_OF_RETRIES;

typedef enum {
    ExthwgPoeIpcMcuTypeDragonite,
    ExthwgPoeIpcMcuTypeCm3,
    ExthwgPoeIpcMcuTypeLast
} ExthwgPoeIpcMcuTypeEnt;

#define exthwg_poe_ipc_debug_msg_time_calcdex(_msg_op_code)    \
    ((0x10 * (_msg_op_code>>24)) + (_msg_op_code & 0xFF))


/**
 * @brief 
 * 
 * @param[in] send
 * @param[in] opCode32
 * @param[in] dataLen
 * @param[in] dataPtr
 * 
 * @return 
 */
bool exthwgPoeIpcSendReceiveMsg(
    bool send,
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
);

/**
 * @brief 
 * 
 * @param[in] buf
 * @param[in] size
 * @param[in] mcuType
 * 
 * @return 
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcDownloadFirmware(
    void *buf,
    uint32_t size, 
    ExthwgPoeIpcMcuTypeEnt mcuType
);

/**
 * @brief 
 * 
 * @param[in] mcuType
 * @param[in] fwFileName
 * 
 * @return 
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcRunFirmware(
    ExthwgPoeIpcMcuTypeEnt mcuType,
    char *fwFileName
);

extern void exthwgPoeIpcRemoveFwFlagLoaded(void);

/**
 * @brief Initialize the EXTHWG POE IPC module.
 * 
 * @param[in] mcuType The type of MCU for the initialization.
 * @param[in] devNum The device number.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the initialization status.
 */
EXTHWG_POE_ret_TYP exthwgPoeIpcInit(
    ExthwgPoeIpcMcuTypeEnt mcuType,
    uint8_t devNum
);