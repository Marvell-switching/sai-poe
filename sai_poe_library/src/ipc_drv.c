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

/*! General definitions */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#include <string.h>
#include <stddef.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <stdbool.h>

#include <h/extIpcDrv.h>
#include <h/ipc_drv.h>
#include <sys/stat.h>

#include <h/utils/log.h>

static bool exthwpPoeIpcFwLoaded = false;
ExthwgPoeIpcMcuTypeEnt exthwgPoeIpcMcuType = ExthwgPoeIpcMcuTypeCm3;

/**
 * @brief Reinitialize the EXTHWG POE IPC module.
 * 
 * @param[in] mcuType The type of MCU for the reinitialization.
 * 
 * @return uint32_t Returns the reinitialization status.
 */
extern uint32_t exthwgPoeIpcReinit (
    ExthwgPoeIpcMcuTypeEnt mcuType
) {
    uint32_t ret = 0;
#ifndef _ROS_WM
    if (mcuType == ExthwgPoeIpcMcuTypeCm3)
        return extDrvIpcCm3CreateChannel();
#endif
    return ret;
}
/*$ END OF EXTHWG_POE_IPc_reinit */

/**
 * @brief Initialize the EXTHWG POE IPC module.
 * 
 * @param[in] mcuType The type of MCU for the initialization.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the initialization status.
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcInit(
    ExthwgPoeIpcMcuTypeEnt mcuType, char* filepath)
{
    uint32_t rc, core = 2;
    EXTHWG_POE_ret_TYP ret = EXTHWG_POE_ret_ok_CNS;
    char *buffer = NULL , fw_file_name[100]={0} ;
    FILE *firmwareFile;

	if (!exthwpPoeIpcFwLoaded){
		/* make the path NULL-terminated */
		fw_file_name[sizeof(fw_file_name)-1] = '\0';
        
        firmwareFile = fopen(filepath, "rb");
        if (!firmwareFile) {
            perror("Error opening firmware file");
            return EXTHWG_POE_ret_failed_CNS;
        }

        /* Get the size of the firmware file */
        fseek(firmwareFile, 0, SEEK_END);
        unsigned firmwareSize = ftell(firmwareFile);
        fseek(firmwareFile, 0, SEEK_SET);

        /* Allocate buffer to hold the firmware */
        buffer = (char*)malloc(firmwareSize);
        if (!buffer) {
            perror("Error allocating memory");
            fclose(firmwareFile);
            return EXTHWG_POE_ret_failed_CNS;
        }

        /* Read the firmware file into the buffer */
        size_t bytesRead = fread(buffer, 1, firmwareSize, firmwareFile);
        if (bytesRead != firmwareSize) {
            perror("Error reading firmware file");
            free(buffer);
            fclose(firmwareFile);
            return EXTHWG_POE_ret_failed_CNS;
        }

        if (mcuType == ExthwgPoeIpcMcuTypeDragonite) {
            // not supported
            return EXTHWG_POE_ret_failed_CNS;
        }
        else if (mcuType == ExthwgPoeIpcMcuTypeCm3) { /* CM3 */
            /* initialize shared memory and load firmware */
            rc = ipc_poe_init(core, buffer, firmwareSize);
            
            if (rc != 0){
                return EXTHWG_POE_ret_failed_CNS;
            }

        }
        else {
            return EXTHWG_POE_ret_failed_CNS;
        }
    }

    /* save mcu type */
    exthwgPoeIpcMcuType = mcuType;

    /* fall through in case ok */
failWriteFree:
    /* Close the firmware file */
    fclose(firmwareFile);

	if (buffer)
		free(buffer);

    return EXTHWG_POE_ret_ok_CNS;
}

typedef struct HALP_config_poe_v3_msg_sysPowerConsumption_STC2 {
    uint32_t                                  powerConsumption_swap;
    uint32_t                                  powerAllocation_swap;
}  HALP_config_poe_v3_msg_sysPowerConsumption_STC2;

uint32_t RSG_swap(uint32_t val)
{
#pragma pack(push, 1)
    union U_TYP {
        uint32_t Word;
        uint8_t  Bytes[4];
    } v1, v2;
#pragma pack(pop)

    v1.Word = val;

    v2.Bytes[0] = v1.Bytes[3];
    v2.Bytes[1] = v1.Bytes[2];
    v2.Bytes[2] = v1.Bytes[1];
    v2.Bytes[3] = v1.Bytes[0];

    return v2.Word;
}

/**
 * @brief Send and receive message from the EXTHWG POE IPC module.
 * 
 * @param[in] send Flag indicating whether to send a message.
 * @param[in] opCode32 The operation code.
 * @param[in] dataLen The length of the data.
 * @param[in,out] dataPtr Pointer to the data buffer.
 * 
 * @return bool Returns true if the operation is successful, otherwise false.
 */
bool exthwgPoeIpcSendReceiveMsg(
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
)
{ 
    int32_t returnCode;
    uint32_t responseLen;

    returnCode = ipc_poe_send_receive_message(opCode32, dataLen, dataPtr, &responseLen);
    if (responseLen != dataLen) {
        LOG_ERROR("PoE FW response length is different than the request length\n");
    }

    if (returnCode != 0) {
        return false;
    }

    return true;
}
/* END OF EXTHWG_POE_IPc_send_recieve_msg */

/**
 * @brief Download firmware to the EXTHWG POE IPC module.
 * 
 * @param[in] buf Pointer to the firmware buffer.
 * @param[in] size The size of the firmware buffer.
 * @param[in] mcuType The type of MCU.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the download status.
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcDownloadFirmware(
    void* buf,
    uint32_t size, 
    ExthwgPoeIpcMcuTypeEnt mcuType
)
{
#ifndef _ROS_WM
    if (mcuType==ExthwgPoeIpcMcuTypeDragonite) {
        // not supported
    } else {
        if (extDrvIpcCm3FwDownload(2, buf, size) != 0) { /* for CM3 use core 2 - perpetual PoE support */
            return EXTHWG_POE_ret_failed_CNS;
        }
    }

#endif

    exthwpPoeIpcFwLoaded = true;
    return EXTHWG_POE_ret_ok_CNS;
}
/*$ END OF EXTHWG_POE_IPc_download_firmware */

/**
 * @brief Run IPC firmware
 * 
 * @param[in] mcuType The type of MCU.
 * @param[in] fwFileName Firmware filename.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the firmware run status.
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcRunFirmware(
    ExthwgPoeIpcMcuTypeEnt mcuType,
    char *fwFileName
)
{
 	EXTHWG_POE_ret_TYP ret = EXTHWG_POE_ret_ok_CNS;
    char *buf = NULL , fw_file_name[100]={0} ;
    uint32_t fileSize;
    FILE *firmwareFile;

	if (!exthwpPoeIpcFwLoaded){
		/* make the path NULL-terminated */
		fw_file_name[sizeof(fw_file_name)-1] = '\0';
        
        firmwareFile = fopen(fwFileName, "rb");
        if (!firmwareFile) {
            perror("Error opening firmware file");
            return EXTHWG_POE_ret_failed_CNS;
        }

        /* Get the size of the firmware file */
        fseek(firmwareFile, 0, SEEK_END);
        long firmwareSize = ftell(firmwareFile);
        fseek(firmwareFile, 0, SEEK_SET);

        /* Allocate buffer to hold the firmware */
        char* buffer = (char*)malloc(firmwareSize);
        if (!buffer) {
            perror("Error allocating memory");
            fclose(firmwareFile);
            return EXTHWG_POE_ret_failed_CNS;
        }

        /* Read the firmware file into the buffer */
        size_t bytesRead = fread(buffer, 1, firmwareSize, firmwareFile);
        if (bytesRead != firmwareSize) {
            perror("Error reading firmware file");
            free(buffer);
            fclose(firmwareFile);
            return EXTHWG_POE_ret_failed_CNS;
        }

        /* call to FW download API */
        if (exthwgPoeIpcDownloadFirmware(buf, fileSize, mcuType) != EXTHWG_POE_ret_ok_CNS)
            ret = EXTHWG_POE_ret_failed_CNS;

        /* check the MCU type */
        if (mcuType == ExthwgPoeIpcMcuTypeDragonite){
            /* not supported */
        }
        else if (mcuType == ExthwgPoeIpcMcuTypeCm3){
            if (extDrvIpcCm3UnresetSet(true, 2) != 0) /* core 2*/
                ret = EXTHWG_POE_ret_failed_CNS;
        }
        else {
            LOG_ERROR("Invalid MCU type\n");
        }
	}

/* fall through in case ok */
failWriteFree:
    /* Close the firmware file */
    fclose(firmwareFile);

	if (buf)
		free(buf);

	return ret;
}
/*$ END OF exthwgPoeIpcRunFirmware */


/**
 * @brief Remove the firmware flag indicating if firmware is loaded.
 * 
 * @param[in] None
 */
void exthwgPoeIpcRemoveFwFlagLoaded()
{
    exthwpPoeIpcFwLoaded = false;
}