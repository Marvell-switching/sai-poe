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

/**
********************************************************************************
* @file extIpcDrv.h
*
* @brief Includes external managment routines.
*
* @version   3
********************************************************************************
*/
#ifndef __extIpcDrvh
#define __extIpcDrvh

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************/
/*  RX / TX     */
/****************/
#define TX_MO_ADDR                      0x50
#define TX_MO_HOST_OWNERSHIP_CODE       0xA0
#define TX_MO_POE_OWNERSHIP_CODE        0x0A

#define RX_MO_ADDR                      0x100
#define RX_MO_HOST_OWNERSHIP_CODE       0xB0
#define RX_MO_POE_OWNERSHIP_CODE        0x0B

#define TX_BUF_ADDR                     0x54
#define RX_BUF_ADDR                     0x104

/****************/
/*  D E B U G   */
/****************/
#define TX_DEBUG_MO_ADDR                0x150
#define TX_DEBUG_MO_HOST_OWNERSHIP      0xC0
#define TX_DEBUG_MO_POE_OWNERSHIP       0x0C

#define RX_DEBUG_MO_ADDR                0x650
#define RX_DEBUG_MO_HOST_OWNERSHIP      0xD0
#define RX_DEBUG_MO_POE_OWNERSHIP       0x0D

#define TX_DEBUG_BUF_ADDR               0x154
#define RX_DEBUG_BUF_ADDR               0x654

/****************/
/*  Management  */
/****************/
#define HOST_PROT_VER_REG_ADDR          0x0
#define PROT_VER_REG_ADDR               0x4
#define MEM_INIT_VAL                    0xFF
#define HOST_INPUT_FROM_POE_REG_ADDR    0x10
#define HOST_OUTPUT_TO_POE_REG_ADDR     0x30
#define HOST_RST_CAUSE_REG_ADDR         0x34

/****************/
/*  MCU IPC     */
/****************/
#define EXTDRVIPC_TX_HEADER_SIZE       (sizeof(int32_t)*2)
#define EXTDRVIPC_RX_HEADER_SIZE   (sizeof(int32_t)*3)
#define EXTDRVIPC_MAX_MSG_SIZE     256
#define EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE    (EXTDRVIPC_MAX_MSG_SIZE - EXTDRVIPC_TX_HEADER_SIZE)
#define EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE    (EXTDRVIPC_MAX_MSG_SIZE - EXTDRVIPC_RX_HEADER_SIZE)

/****************/
/*  Conbtroller     */
/****************/
typedef int8_t EXTHWG_POE_ret_TYP;
#define EXTHWG_POE_ret_ok_CNS			0
#define EXTHWG_POE_ret_not_init_CNS		(-1)
#define EXTHWG_POE_ret_failed_CNS		(-2)
#define EXTHWG_POE_ret_not_owned_CNS	(-3)
#define EXTHWG_POE_ret_timeout_CNS		(-4)

typedef enum {
    EXTHWG_POE_ret_ok_E        = EXTHWG_POE_ret_ok_CNS,
    EXTHWG_POE_ret_not_init_E  = EXTHWG_POE_ret_not_init_CNS,  
    EXTHWG_POE_ret_failed_E    = EXTHWG_POE_ret_failed_CNS,
    EXTHWG_POE_ret_not_owned_E = EXTHWG_POE_ret_not_owned_CNS,
    EXTHWG_POE_ret_timeout_E   = EXTHWG_POE_ret_timeout_CNS,
    EXTHWG_POE_ret_last_E,
} EXTHWG_POE_ret_ENT;
/********************************************************************************
*        These variables can be customized by the user
*********************************************************************************/
/*extern uint32_t EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec;
extern uint32_t EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES;*/

/**
* @internal extDrvIpcPoeMsgRead function
* @endinternal
*
* @brief   Marvell PoE protocol compliant for IPC Rx messages
*
* @param[in] msg_opcode               - Opcode of requested msg
* @param[in] msg_request_len          -
* @param[in] msg_request_PTR          - Buffer of max length
*
* @param[out] msg_response_len_PTR    - actual msg len read
* @param[out] msg_response            - the message that was read
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - otherwise.
*/
bool extDrvIpcPoeMsgRead(
     int32_t  msg_opcode,
     uint32_t msg_request_len,
     uint8_t  *msg_request_PTR, /* Buffer with max length EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE */
     uint32_t *msg_response_len_PTR,
     uint8_t  msg_response[EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE]
);

/**
* @internal extDrvIpcPoeMsgWrite function
* @endinternal
*
* @brief   Marvell PoE protocol compliant for IPC Tx messages
*
* @param[in] msg_opcode               - Opcode of requested msg
* @param[in] msg_request_len          -
* @param[in] msg_request_PTR          - Buffer of max length
*

* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - othersise.
*/
bool extDrvIpcPoeMsgWrite(
     int32_t  msg_opcode,
     uint32_t msg_request_len,
     uint8_t  *msg_request_PTR, /* Buffer with max length EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE */
     bool is_debug
);

/**
* @internal extDrvIpcCm3CreateChannel function
* @endinternal
*
* @brief   Re-init CM3 IPc driver; only the IPc section (can be used to clear IPc)
*
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - driver no exists
* @retval GT_FAIL                  - on error.
*/
bool extDrvIpcCm3CreateChannel(
    void
);

/**
* @internal extDrvIpcCm3Init function
* @endinternal
*
* @brief   Init IPc driver order to 
*          communicate with CM3 FW
*
* @param[in] devNum                - Device Number
* @param[in] coreId                - CM3 core ID
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - driver no exists
* @retval GT_FAIL                  - on error.
*/
extern bool extDrvIpcCm3Init(
    uint8_t                devNum,
    uint32_t               coreId
);

/**
* @internal extDrvIpcCm3UnresetSet function
* @endinternal
*
* @brief   Reset/Unreset CM3.
*
* @param[in] unresetEnable            - GT_TRUE - set to un-reset state
*                                       GT_FALSE - set to reset state
* @param[in] coreId                   - CM3 core ID
* @retval                               GT_OK if successful, or
*                                       GT_FAIL otherwise.
*/
bool extDrvIpcCm3UnresetSet(
    bool unresetEnable,
    uint32_t  coreId
);

/**
* @internal extDrvIpcCm3FwDownload function
* @endinternal
*
* @brief   Download FW to CM3 SRAM
*
* @param[in] coreId  - CM3 core ID
* @param[in] buf  - pointer to FW buffer
* @param[in] size - size of FW
*
*/
bool extDrvIpcCm3FwDownload
(
    uint32_t   coreId,
    void  *buf,
    uint32_t      size
);

/**
* @internal extDrvIpc15ByteMsgWrite function
* @endinternal
*
* @brief   CM3 IPc "15 Bytes" message write
*
* @param[in] msg_PTR          - pointer to message buffer
*/
bool extDrvIpc15ByteMsgWrite(
    void *msg_PTR
);

/**
* @internal extDrvIpc15BytesMsgRead function
* @endinternal
*
* @brief   CM3 IPc "15 Bytes" message read
*
* @param[in] msg_PTR          - pointer to message buffer
*/
bool extDrvIpc15BytesMsgRead(
    void *msg_PTR
);

typedef unsigned int GT_STATUS;
typedef uint8_t     GT_U8;
typedef uint32_t     GT_U32;
typedef uint32_t    GT_PHYSICAL_PORT_NUM;
#define IN

/**
* @internal internal_cpssPortManagerStatClear
* @endinternal
*
* @brief  clear portManager statistic db
*
* @param[in]  devNum               - device number
* @param[in]  portNum              - port number
*
* @retval GT_OK                    - on success
* @retval GT_BAD_PARAM             - on wrong port number or device
*
*
*/
extern GT_STATUS internal_cpssPortManagerStatClear
(
    IN GT_U8                    devNum,
    IN GT_PHYSICAL_PORT_NUM     portNum
);

GT_STATUS cpssDxChPortManagerStatusGet
(
    IN  GT_U8                           devNum,
    IN  GT_PHYSICAL_PORT_NUM            portNum,
    IN void    *portStagePtr
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __extIpcDrvh */




