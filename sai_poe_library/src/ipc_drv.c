
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

#include <h/gtDragoniteDrv.h>
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
        // return extDrvIpcCm3CreateChannel();
#endif
    return ret;
}
/*$ END OF EXTHWG_POE_IPc_reinit */

/**
 * @brief Initialize the EXTHWG POE IPC module.
 * 
 * @param[in] mcuType The type of MCU for the initialization.
 * @param[in] devNum The device number.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the initialization status.
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcInit(
    ExthwgPoeIpcMcuTypeEnt mcuType,
    uint8_t devNum
)
{
#ifndef _ROS_WM
    uint32_t rc;
#endif
      
    // hwInfoPtr = cpssDrvHwPpHwInfoStcPtrGet(devNum , 0);
    // if (hwInfoPtr == NULL)
    //    return EXTHWG_POE_ret_failed_CNS;

#ifndef _ROS_WM

    if (mcuType == ExthwgPoeIpcMcuTypeDragonite) {
        // not supported
    }
    else if (mcuType == ExthwgPoeIpcMcuTypeCm3) { /* CM3 */

        // rc = extDrvIpcCm3Init(devNum, 2); /* core 2 */
        // if (rc != 0){
        //     return EXTHWG_POE_ret_failed_CNS;
        // }
    }
    else {
        return EXTHWG_POE_ret_failed_CNS;
    }
#endif

    /* save mcu type */
    exthwgPoeIpcMcuType = mcuType;

    return EXTHWG_POE_ret_ok_CNS;
}

/**
 * @brief Read from the EXTHWG POE IPC module.
 * 
 * @param[in] opcode The operation code.
 * @param[in] readRequestDataLen The length of the read request data.
 * @param[in] readRequestDataPtr Pointer to the read request data buffer.
 * @param[out] readResponseDataLenPtr Pointer to store the length of the read response data.
 * @param[out] readResponseDataPtr Pointer to store the read response data.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the read status.
 */
static EXTHWG_POE_ret_TYP exthwpPoeIpcRead(
    uint32_t opcode,
    uint32_t readRequestDataLen,
    uint8_t *readRequestDataPtr,
    uint32_t *readResponseDataLenPtr,
    uint8_t *readResponseDataPtr
)
{
    uint32_t timeBefore = 0, timeAfter = 0, debugIndex;
    uint32_t ret; 

    // if (exthwgPoeIpcDebugMsgTimeEnable == true){
    //     //timeBefore = OSTIMG_ms_clock;
    // }
#ifndef _ROS_WM
    // ret = extDrvIpcPoeMsgRead(opcode, readRequestDataLen, readRequestDataPtr, readResponseDataLenPtr, readResponseDataPtr);
#else
    *readResponseDataLenPtr = 0;
    *readResponseDataPtr = 0;
    ret = 0;
#endif  
    return (ret==0)?EXTHWG_POE_ret_ok_CNS:EXTHWG_POE_ret_failed_CNS;
}
/* END OF EXTHWG_POE_IPc_read */

/**
 * @brief Write to the EXTHWG POE IPC module.
 * 
 * @param[in] opcode The operation code.
 * @param[in] writeRequestDataLen The length of the write request data.
 * @param[in] writeRequestDataPtr Pointer to the write request data buffer.
 * @param[in] isDebug Flag indicating if debug mode is enabled.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the write status.
 */
static EXTHWG_POE_ret_TYP exthwpPoeIpcWrite(
    uint32_t opcode,
    uint32_t writeRequestDataLen,
    uint8_t *writeRequestDataPtr,
    bool isDebug
)
{
#ifndef _ROS_WM
    // if (extDrvIpcPoeMsgWrite(opcode, writeRequestDataLen, writeRequestDataPtr, isDebug) == 0)
        // return EXTHWG_POE_ret_ok_CNS;
    // else
    //     return EXTHWG_POE_ret_failed_CNS;
#else
    return EXTHWG_POE_ret_ok_CNS;
#endif
}
/* END OF EXTHWG_POE_IPc_write */


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
    bool send,
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
)
{ 
    int32_t returnCode;
    uint8_t debugBuf[256], readBuf[256];
    uint32_t responseLen, i;
    uint8_t *debugKeepPtr = NULL;
    bool isPrintable=true;
#ifndef _ROS_WM
    // uint32_t origRetries=EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES;
#endif

    if (send==true)
        return false;
        // returnCode = EXTHWP_POE_IPc_write(opCode32, dataLen, dataPtr, false);
    else {
        // returnCode = EXTHWP_POE_IPc_read(opCode32, dataLen, dataPtr, &responseLen, readBuf);
        if (responseLen != dataLen){
            LOG_ERROR("PoE FW response length is different than the request length\n");
        }

        memcpy(dataPtr, readBuf, (responseLen < dataLen ? responseLen : dataLen));
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
        // if (extDrvIpcCm3FwDownload(2, buf, size) != 0) { /* for CM3 use core 2*/
        //     return EXTHWG_POE_ret_failed_CNS;
        // }
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
    char *buf = NULL /*, fw_file_name[100]={0} */;
    uint32_t fileSize;
#ifndef _ROS_WM
    int         i;
#endif
    /* In order to reset DTCM area, which is 0xB00 *words* long - we use a /16
	   buffer - in order not to alloc to much on the thread's stack
	*/
	#define NOF_DTCM_CHUNKS	16
	#define DTCM_CHUNK 	(0xB00*4/NOF_DTCM_CHUNKS)
	uint32_t dtcmBuf[DTCM_CHUNK] = {0xff};
    struct stat st;
    FILE *file;

	if (!exthwpPoeIpcFwLoaded){
		/*remove protection
	    if (GT_OK != extDrvDragoniteProtect(GT_FALSE))
	        ret = EXTHWG_POE_ret_failed_CNS;*/

        // if(pdlPowerPoEAttributesGet(&pdl_poe_params) != PDL_OK) {
        //     // DEBUGG_log_MAC(EXTHWG_POE_debug_fw_flag)
        //     //         (DEBUGG_func_name_MAC(), "PDL failed to read - pdlPowerPoEAttributesGet\n");

        //     return EXTHWG_POE_ret_failed_CNS;
        // }

        // memcpy (&fw_file_name, pdl_poe_params.fwFileName, sizeof(fw_file_name));
		// /* make the path NULL-terminated */
		// fw_file_name[sizeof(fw_file_name)-1] = '\0';
        
        if (stat(fwFileName, &st) == 0){
            fileSize = st.st_size;

            file = fopen(fwFileName, "r");
            if (file == NULL) {
                perror("Error opening file");
                return EXTHWG_POE_ret_failed_CNS;
            }

            buf = (char *)malloc(fileSize);
            if (buf == NULL)
            	return EXTHWG_POE_ret_failed_CNS;

            ssize_t bytesRead = read(file, buf, fileSize);
            if (bytesRead == -1) {
                perror("Error reading file");
                free(buf); // Free allocated memory
                close(file);
                return EXTHWG_POE_ret_failed_CNS;
            }

            // HOSTG_rscode_file_load(fw_file_name, buf);

            // DEBUGG_log_MAC(EXTHWG_POE_debug_fw_flag)(DEBUGG_func_name_MAC(),
            //     "download [%s], file_size = %d", fw_file_name, file_size);

#ifndef _ROS_WM
            /* call to FW download API */
            if (exthwgPoeIpcDownloadFirmware(buf, fileSize, mcuType) != EXTHWG_POE_ret_ok_CNS)
                // OSSYSG_fatal_error("PoE firmware download failed");

            if (mcuType == ExthwgPoeIpcMcuTypeDragonite){
                
                /* Init DTCM with 0xFF */
                // for (i=0; i<NOF_DTCM_CHUNKS; i++)
                    // if (extDrvDragoniteMemWrite(DTCM_DIR, i*DTCM_CHUNK, (GT_8_PTR)DTCM_BUF, sizeof(DTCM_BUF)) != GT_OK)
                    //     goto fail_write_free;
                /*
                if (GT_OK != extDrvDragoniteProtect(GT_TRUE))
                    ret = EXTHWG_POE_ret_failed_CNS;*/

                // if (extDrvDragoniteUnresetSet(GT_TRUE) != GT_OK)
		        //     ret = EXTHWG_POE_ret_failed_CNS;
            
            }
            else if (mcuType == ExthwgPoeIpcMcuTypeCm3){
                
                // if (extDrvIpcCm3UnresetSet(true, 2) != 0) /* core 2*/
                //     ret = EXTHWG_POE_ret_failed_CNS;
            }
            else {
                // OSSYSG_fatal_error("Invalid mcu type");
            }
#endif
        }
        else {
            // DEBUGG_log_MAC(EXTHWG_POE_debug_fw_flag)(DEBUGG_func_name_MAC(),
            //     "Failed to get size of file [%s]", fw_file_name);

            return EXTHWG_POE_ret_failed_CNS;
        }
	}
#ifndef _ROS_WM

/* fall through in case ok */
failWriteFree:
#endif
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
extern void exthwgPoeIpcRemoveFwFlagLoaded(
    void
)
{

    exthwpPoeIpcFwLoaded = false;
}
