/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */

/*!**************************************************RND Template version 4.1
 *!                      P A C K A G E   B O D Y
 *!==========================================================================
 *$ TITLE: Dragonite driver
 *!--------------------------------------------------------------------------
 *$ FILENAME: poe_controler/ipc/src/ipc_drv.c
 *!--------------------------------------------------------------------------
 *$ SYSTEM, SUBSYSTEM: <SysName>
 *!--------------------------------------------------------------------------
 *$ AUTHORS: 
 *!--------------------------------------------------------------------------
 *$ LATEST UPDATE: 
 *!**************************************************************************
 *!
 *!**************************************************************************
 *!
 *$ GENERAL DESCRIPTION:
 *!
 *$ PROCESS AND ALGORITHM: (local)
 *!
 *$ PACKAGE GLOBAL SERVICES:
 *!     (A list of package global services).
 *!
 *$ PACKAGE LOCAL SERVICES:  (local)
 *!     (A list of package local services).
 *!
 *$ PACKAGE USAGE:
 *!     (How to use the package services,
 *!     routines calling order, restrictions, etc.)
 *!
 *$ ASSUMPTIONS:
 *!
 *$ SIDE EFFECTS:
 *!
 *$ RELATED DOCUMENTS:     (local)
 *!
 *$ REMARKS:               (local)
 *!
 *!**************************************************************************
 *!*/

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

#include <h/ipc/gtDragoniteDrv.h>
//#include <terminal/asterm/exp/asterm.h>
#include <h/ipc/ipc_drv.h>
#include <h/ipc/dragonite_prv.h>
#include <h/ipc/cpssDriverPpHw.h>
#include <sys/stat.h>
// #include <inf/host/exp/host.h>

/*!**************************************************************************
 *$              EXTERNAL DECLARATIONS (IMPORT AND EXPORT)
 *!**************************************************************************
 *!*/

/*!**************************************************************************
 *$              EXTERNAL DECLARATIONS (IMPORT)
 *!**************************************************************************
 *!*/
// #include <inc/ipc_drv_prv.h>
// #include <inf/sysconfinf/exp/sysconfinf.h>
// #include <inf/sysconfinf/auto/exp/sysconfparse.h>
// #include <lib/string/exp/string.h>
// #include <pdl/power_supply/pdlPower.h>

static bool EXTHWP_POE_IPc_FW_loaded = FALSE;
bool EXTHWG_POE_IPc_debug_msg_time_enable = FALSE;
EXTHWG_POE_IPc_MCU_Type_ENT EXTHWG_POE_IPc_mcu_type = EXTHWG_POE_IPc_MCU_Type_dragonite_E;

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_reinit
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
extern GT_STATUS EXTHWG_POE_IPc_reinit (

    /*!     INPUTS:             */
    EXTHWG_POE_IPc_MCU_Type_ENT mcu_type
    /*!     INPUTS / OUTPUTS:   */

    /*!     OUTPUTS:            */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
    GT_STATUS ret = GT_OK;
/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/
#ifndef _ROS_WM
    if (mcu_type == EXTHWG_POE_IPc_MCU_Type_cm3_E)
        return extDrvIpcCm3CreateChannel();
#endif
    return ret;
}
/*$ END OF EXTHWG_POE_IPc_reinit */

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_init
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
extern EXTHWG_POE_ret_TYP EXTHWG_POE_IPc_init(
    /*!     INPUTS:             */
    EXTHWG_POE_IPc_MCU_Type_ENT mcu_type,
    GT_U8                       devNum
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
#ifndef _ROS_WM
    GT_STATUS          rc;
#endif
    CPSS_HW_INFO_STC   *hwInfoPtr;
/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/
      
    // hwInfoPtr = cpssDrvHwPpHwInfoStcPtrGet(devNum , 0);
    // if (hwInfoPtr == NULL)
    //    return EXTHWG_POE_ret_failed_CNS;

#ifndef _ROS_WM

    if (mcu_type == EXTHWG_POE_IPc_MCU_Type_dragonite_E) {

        // rc = extDrvDragoniteDriverInit(
        //     hwInfoPtr, 
        //     (void*)(GT_UINTPTR)devNum,
        //     (DRAGONITE_HW_WRITE_MASKED_FUNC)prvDrvCpssWriteMasked);
        // if (rc != GT_OK){
        //     // OSIOG_printf("%s: return from extDrvDragoniteDriverInit with error %d\n", DEBUGG_func_name_MAC(), rc);
        //     return EXTHWG_POE_ret_failed_CNS;
        // }

        // rc = extDrvDragoniteDevInit();
        // if (rc != GT_OK){
        //     // OSIOG_printf("%s: return from extDrvDragoniteDevInit with error %d\n", DEBUGG_func_name_MAC(), rc);
        //     return EXTHWG_POE_ret_failed_CNS;
        // }

        // rc = extDrvDragoniteCtrlRegWrite(extDrvDrgReg_maskIrq, 0xFFFFFFFF, EXTHWG_POE_DRG_MASK_VAL_CNS);
        // if (rc != GT_OK){
        //     // OSIOG_printf("%s: return from extDrvDragoniteCtrlRegWrite with error %d\n", DEBUGG_func_name_MAC(), rc);
        //     return EXTHWG_POE_ret_failed_CNS;
        // }
    }
    
    /* change IPC timeout and number of retries */
    // EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec = EXTHWG_POE_DRG_IPc_WAIT_FOR_RESPONSE_TIMEOUT_uSec_CNS;
    // EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES = EXTHWG_POE_DRG_IPc_WAIT_FOR_RESPONSE_NUM_OF_RETRIES_CNS;

    if (mcu_type == EXTHWG_POE_IPc_MCU_Type_dragonite_E){
        // if (extDrvIpcDrgInit(hwInfoPtr) != GT_OK)
            // return EXTHWG_POE_ret_failed_CNS;
    }
    else if (mcu_type == EXTHWG_POE_IPc_MCU_Type_cm3_E) { /* CM3 */

        // DEBUGG_log_MAC(EXTHWG_POE_IPc_debug_msg_flag)
        //     (DEBUGG_func_name_MAC(), "call to CM3 IPC init");

        rc = extDrvIpcCm3Init(devNum, 2); /* core 2 */
        if (rc != GT_OK){
            // OSIOG_printf("%s: return from extDrvIpcCm3Init with error %d\n", DEBUGG_func_name_MAC(), rc);
            return EXTHWG_POE_ret_failed_CNS;
        }
    }
    else {
        // DEBUGG_log_MAC(EXTHWG_POE_IPc_debug_msg_flag)
        //     (DEBUGG_func_name_MAC(), "invalid mcu type");
        return EXTHWG_POE_ret_failed_CNS;
    }
#endif

    /* save mcu type */
    EXTHWG_POE_IPc_mcu_type = mcu_type;

    return EXTHWG_POE_ret_ok_CNS;
}
/* END OF EXTHWG_POE_IPc_init */

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_read
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
static EXTHWG_POE_ret_TYP EXTHWP_POE_IPc_read(
	/*!     INPUTS:             */
    uint32_t opcode,
    uint32_t read_request_data_len,
    uint8_t  *read_request_data_PTR /* Buffer with max length EXTHWG_POE_DRG_IPc_MAX_REQUEST_MESSAGE_SIZE */,

	/*!     INPUTS / OUTPUTS:   */
	/*!     OUTPUTS:            */
    uint32_t *read_response_data_len_PTR,
    uint8_t  *read_response_data_PTR /* Buffer with max length EXTHWG_POE_DRG_IPc_MAX_RESPONSE_MESSAGE_SIZE */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
    uint32_t    time_before = 0, time_after = 0, debug_index;
    GT_STATUS  ret; 
/*!*************************************************************************/
/*!                      F U N C T I O N   L O G I C                       */
/*!*************************************************************************/
    if (EXTHWG_POE_IPc_debug_msg_time_enable == TRUE){
        //time_before = OSTIMG_ms_clock;
    }
#ifndef _ROS_WM
    ret = extDrvIpcPoeMsgRead(opcode, read_request_data_len, read_request_data_PTR, read_response_data_len_PTR, read_response_data_PTR);
#else
    *read_response_data_len_PTR = 0;
    *read_response_data_PTR = 0;
    ret = GT_OK;
#endif	
    if (EXTHWG_POE_IPc_debug_msg_time_enable == TRUE){
        debug_index = EXTHWG_POE_IPc_debug_msg_time_calcIndex(opcode);
        if (debug_index < 50){
            //time_after = OSTIMG_ms_clock;
            //EXTHWG_POE_IPc_debug_time_db[debug_index].num_of_elements++;
           // EXTHWG_POE_IPc_debug_time_db[debug_index].sum+=(time_after-time_before);
        }
    }
    return (ret==GT_OK)?EXTHWG_POE_ret_ok_CNS:EXTHWG_POE_ret_failed_CNS;
}
/* END OF EXTHWG_POE_IPc_read */


/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_write
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
static EXTHWG_POE_ret_TYP EXTHWP_POE_IPc_write(
	/*!     INPUTS:             */
    uint32_t opcode,
    uint32_t write_request_data_len,
    uint8_t  *write_request_data_PTR, /* Buffer with max length EXTHWG_POE_IPc_MAX_REQUEST_MESSAGE_SIZE */
    bool is_debug

	/*!     INPUTS / OUTPUTS:   */
	/*!     OUTPUTS:            */  
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/
#ifndef _ROS_WM
	if (extDrvIpcPoeMsgWrite(opcode, write_request_data_len, write_request_data_PTR, is_debug) == GT_OK)
        return EXTHWG_POE_ret_ok_CNS;
    else
        return EXTHWG_POE_ret_failed_CNS;
#else
    return EXTHWG_POE_ret_ok_CNS;
#endif
}
/* END OF EXTHWG_POE_IPc_write */

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_send_recieve_msg
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
bool EXTHWG_POE_IPc_send_recieve_msg(
    /*!     INPUTS:             */
    bool                             send,
    uint32_t                             op_code_32,
    uint8_t                              data_len,
    /*!     INPUTS / OUTPUTS:   */
    uint8_t                              *data_PTR
    /*!     OUTPUTS:            */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/    
    int32_t          return_code;
    uint8_t          debug_buf[256], read_buf[256];
    uint32_t         response_len, i;
    uint8_t          *debug_keep_PTR = NULL;
    // DEBUGG_id_TYP   debug_flag;
    bool         is_printable=TRUE;
#ifndef _ROS_WM
    uint32_t orig_retries=EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES;
#endif
/*!*************************************************************************/
/*!                      F U N C T I O N   L O G I C                       */
/*!*************************************************************************/

    // debug_flag = (DEBUGG_is_active_MAC(EXTHWG_POE_IPc_debug_setMsg_flag)&&send==TRUE)?EXTHWG_POE_IPc_debug_setMsg_flag:EXTHWG_POE_IPc_debug_msg_flag;
    // DEBUGG_log_MAC(debug_flag)
    //     (DEBUGG_func_name_MAC(), "Start, op_code_num_32 [%#x], level [%#x], dir [%#x], id [%#x]", 
    //     op_code_32, op_code_32&0xff, (op_code_32>>8)&0xff, RSG_swap16_MAC(((UINT_16)(op_code_32>>16))));

//     if (DEBUGG_is_active_MAC(debug_flag)) {
//         memset(debug_buf, 0, sizeof(debug_buf));

//         memcpy(debug_buf, data_PTR, data_len);

//         debug_keep_PTR = data_PTR;
//         data_PTR = debug_buf;

//         OSIOG_printf("Row data of the message:\n"); 
//         for (i=0; i<data_len; i++){
//             OSIOG_printf(" %#x", data_PTR[i]);
//         }
//         OSIOG_printf("\n");
// #ifndef _ROS_WM
//         EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES = 100;
//         /*OSIOG_printf("\n\n  EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES = %d\n", EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES);*/
// #endif
//     }

    if (send==TRUE)
        return_code = EXTHWP_POE_IPc_write(op_code_32, data_len, data_PTR, FALSE);
    else {
        return_code = EXTHWP_POE_IPc_read(op_code_32, data_len, data_PTR, &response_len, read_buf);
        if (response_len != data_len){
            // DEBUGG_log_MAC(debug_flag)
            //     (DEBUGG_func_name_MAC(), "original data_len=[%d], response_len=[%d]",
            //     data_len, response_len);
        }

        // if (HALP_config_poe_v3_debug_no_fw == TRUE && DEBUGG_is_active_MAC(debug_flag)){
        //     memcpy(data_PTR, read_buf, response_len);
        // }
        // else {
        //     memcpy(data_PTR, read_buf, MIN(response_len, data_len));
        // }

        memcpy(data_PTR, read_buf, (response_len < data_len ? response_len : data_len));
    }

    if (return_code != 0) {
        // DEBUGG_log_MAC(debug_flag)(DEBUGG_func_name_MAC(), "IPC returned error %d; %s operation; opcode: %#x\n",
        //     return_code, (send==TRUE)?"WRITE":"READ", 
        //     op_code_32);
        return FALSE;
    }

//     if (DEBUGG_is_active_MAC(debug_flag)) {
//         if (send==FALSE){
//             OSIOG_printf("Data from PoE FW:\n");
//             for (i=0; i<response_len; i++){
//                 OSIOG_printf(" %#x ", debug_buf[i]);
//                 if (!STRINGG_is_valid_xml_char_MAC(debug_buf[i]))
//                     is_printable = FALSE;

//             }
//             OSIOG_printf("\n\n");

//             if (is_printable)
//                 OSIOG_printf("(GET) message from PoE FW in string: %s\n", debug_buf);
//             else 
//                 OSIOG_printf("(GET) message from PoE FW in not printable\n");
            
//             if (debug_keep_PTR != NULL) {
//                 memcpy(debug_keep_PTR, read_buf, MIN(response_len, data_len));
//             }
//         } 
//         else{
//             DEBUGG_log_MAC(debug_flag)
//                 (DEBUGG_func_name_MAC(), "message from PoE FW in string: %s\n", data_PTR);
//         }
// #ifndef _ROS_WM
//         EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES = orig_retries;
// #endif
//     }

    return TRUE;
}
/* END OF EXTHWG_POE_IPc_send_recieve_msg */

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_download_firmware
*
* DESCRIPTION: Supply the MCU a user-defined FW (not the default)
*      
*
*****************************************************************************/
extern EXTHWG_POE_ret_TYP EXTHWG_POE_IPc_download_firmware(
	/*!     INPUTS:             */
	void*       buf,
	uint32_t     size, 
    EXTHWG_POE_IPc_MCU_Type_ENT mcuType
	/*!     INPUTS / OUTPUTS:   */
	/*!     OUTPUTS:            */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/
    
#ifndef _ROS_WM
    if (mcuType==EXTHWG_POE_IPc_MCU_Type_dragonite_E) {
        // DEBUGG_log_MAC(EXTHWG_POE_debug_fw_flag)(DEBUGG_func_name_MAC(),
        //     "Call to extDrvDragoniteFwDownload with FW size %d Bytes", size);
        // if (extDrvDragoniteFwDownload(buf, size) != GT_OK) {
        //     return EXTHWG_POE_ret_failed_CNS;
        // }
    } else {
        // DEBUGG_log_MAC(EXTHWG_POE_debug_fw_flag)(DEBUGG_func_name_MAC(),
        //     "Call to extDrvCm3FwDownload with FW size %d Bytes", size);
        if (extDrvIpcCm3FwDownload(2, buf, size) != GT_OK) { /* for CM3 use core 2*/
            return EXTHWG_POE_ret_failed_CNS;
        }
    }

#endif

    EXTHWP_POE_IPc_FW_loaded = TRUE;
    return EXTHWG_POE_ret_ok_CNS;
}
/*$ END OF EXTHWG_POE_IPc_download_firmware */

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_run_firmware
*
* DESCRIPTION:  1. Loads FW - if not already loaded
*               2. Starts the dragonite
*
*      Must be called after EXTHWG_POE_IPc_init
*
*****************************************************************************/
extern EXTHWG_POE_ret_TYP EXTHWG_POE_IPc_run_firmware(
    /*!     INPUTS:             */
    EXTHWG_POE_IPc_MCU_Type_ENT mcuType,
    char *fw_file_name
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
	EXTHWG_POE_ret_TYP ret = EXTHWG_POE_ret_ok_CNS;
    char *buf = NULL /*, fw_file_name[100]={0} */;
    uint32_t     file_size;
#ifndef _ROS_WM
    int         i;
#endif
    /* In order to reset DTCM area, which is 0xB00 *words* long - we use a /16
	   buffer - in order not to alloc to much on the thread's stack
	*/
	#define NOF_DTCM_CHUNKS	16
	#define DTCM_CHUNK 	(0xB00*4/NOF_DTCM_CHUNKS)
	uint32_t DTCM_BUF[DTCM_CHUNK] = {0xff};
    
/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/
    struct stat st;
    FILE *file;

	if (!EXTHWP_POE_IPc_FW_loaded){
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
        
        if (stat(fw_file_name, &st) == 0){
            file_size = st.st_size;

            file = fopen(fw_file_name, "r");
            if (file == NULL) {
                perror("Error opening file");
                return EXTHWG_POE_ret_failed_CNS;
            }

            buf = (char *)malloc(file_size);
            if (buf == NULL)
            	return EXTHWG_POE_ret_failed_CNS;

            ssize_t bytes_read = read(file, buf, file_size);
            if (bytes_read == -1) {
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
            if (EXTHWG_POE_IPc_download_firmware(buf, file_size, mcuType) != EXTHWG_POE_ret_ok_CNS)
                // OSSYSG_fatal_error("PoE firmware download failed");

            if (mcuType == EXTHWG_POE_IPc_MCU_Type_dragonite_E){
                
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
            else if (mcuType == EXTHWG_POE_IPc_MCU_Type_cm3_E){
                
                if (extDrvIpcCm3UnresetSet(GT_TRUE, 2) != GT_OK) /* core 2*/
                    ret = EXTHWG_POE_ret_failed_CNS;
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
fail_write_free:
#endif
	if (buf)
		free(buf);

	return ret;
}
/*$ END OF EXTHWG_POE_IPc_run_firmware */

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_remove_FW_flag_loaded
*
* DESCRIPTION:   if FW need to be reloaded, need to call this API before EXTHWG_POE_IPc_run_firmware is called
*
*
*****************************************************************************/
extern void EXTHWG_POE_IPc_remove_FW_flag_loaded(
    /*!     INPUTS:             */
    void
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/

/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/
	EXTHWP_POE_IPc_FW_loaded = FALSE;
}
/*$ END OF EXTHWG_POE_IPc_remove_FW_flag_loaded */

