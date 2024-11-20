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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define POE_PD69200_MSG_N                   (0x4E)
#define POE_PD69200_MSG_KEY_COMMAND         (0x00)
#define POE_PD69200_MSG_KEY_PROGRAM         (0x01)
#define POE_PD69200_MSG_KEY_REQUEST         (0x02)
#define POE_PD69200_MSG_KEY_TELEMETRY       (0x03)
#define POE_PD69200_MSG_KEY_TEST            (0x04)
#define POE_PD69200_MSG_KEY_REPORT          (0x52)

#define POE_PD69200_MSG_SUB_CHANNEL         (0x05)
#define POE_PD69200_MSG_SUB_E2              (0x06)
#define POE_PD69200_MSG_SUB_GLOBAL          (0x07)
#define POE_PD69200_MSG_SUB_RESOTRE_FACT    (0x2D)
#define POE_PD69200_MSG_SUB_USER_BYTE       (0x41)
#define POE_PD69200_MSG_SUB_FLASH           (0xFF)

#define POE_PD69200_MSG_SUB1_PRIORITY       (0x0A)
#define POE_PD69200_MSG_SUB1_SUPPLY         (0x0B)
#define POE_PD69200_MSG_SUB1_EN_DIS         (0x0C)
#define POE_PD69200_MSG_SUB1_PORT_STATUS    (0x0E)
#define POE_PD69200_MSG_SUB1_SAVE_CONFIG    (0x0F)
#define POE_PD69200_MSG_SUB1_VERSIONZ       (0x1E)

#define POE_PD69200_BT_MSG_SUB1_PORTS_PARAMETERS    (0xC0)
#define POE_PD69200_BT_MSG_SUB1_PORTS_CLASS         (0xC4)
#define POE_PD69200_BT_MSG_SUB1_PORTS_MEASUREMENT   (0xC5)
#define POE_PD69200_MSG_SUB2_MAIN           (0x17)

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
bool poeUartSendReceiveMsg(
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
);

/* FIXME: refactor */
bool uartSetPortTempMatrix(uint8_t logic_port, uint8_t physicalNumberA, uint8_t physicalNumberB);
bool uartSetActiveMatrix();

/**
 * @brief Initialize POE IPC.
 *
 * @param[in] mcuType The type of MCU for the initialization.
 * @param[in] fielpath The path to the POE firmware file.
 *
 * @return int Returns the initialization status.
 */
int poeUartInit();
