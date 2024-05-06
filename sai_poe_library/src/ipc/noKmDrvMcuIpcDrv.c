/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE IS A REFERENCE CODE FOR MARVELL SWITCH PRODUCTS.  IT IS PROVIDED   *
* "AS IS" WITH NO WARRANTIES, EXPRESSED, IMPLIED OR OTHERWISE, REGARDING ITS   *
* ACCURACY, COMPLETENESS OR PERFORMANCE.                                       *
* CUSTOMERS ARE FREE TO MODIFY IT AND USE IT ONLY IN THEIR PRODUCTION          *
* SOFTWARE RELEASES WITH MARVELL SWITCH CHIPSETS.                              *
*******************************************************************************/
#define _BSD_SOURCE
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
// #include <cpssCommon/cpssPresteraDefs.h>
#include <h/ipc/gtDragoniteDrv.h>
// #include <cpss/common/cpssTypes.h>
// #include <cpss/generic/ipc/mvShmIpc.h>
#include <h/ipc/mvShmIpc.h>

#include <h/ipc/prvCpssGenericSrvCpuLoad.h>
#include <h/ipc/prvCpssGenericSrvCpuIpcDevCfg.h>
// #include <cpssDriver/pp/prvCpssDrvPpDefs.h>

/* Common */
typedef struct EXTDRVIPC_PoE_TX_MESSAGE{
    GT_32     opcode;
    GT_32     data_length;
    GT_U8     data[EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE];
}EXTDRVIPC_PoE_TX_MESSAGE_STC;

typedef struct EXTDRVIPC_PoE_RX_MESSAGE{
    GT_32     opcode;
    GT_32     status;
    GT_32     data_length;
    GT_U8     data[EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE];
}EXTDRVIPC_PoE_RX_MESSAGE_STC;

IPC_SHM_STC *EXTDRVIPC_shm_PTR=NULL;

/*#define EXTDRVIPC_DEBUG*/
#ifdef  EXTDRVIPC_DEBUG
#define EXTDRVIPC_debug_printf(x, ...) printf(x "\n", ##__VA_ARGS__)
#else
#define EXTDRVIPC_debug_printf(x, ...)
#endif

GT_U32 EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec    = 20000;
GT_U32 EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES  = 10;

/* CM3 */
#define EXTDRVIPC_CM3_SRAM_SIZE                (0x20000)   /* 128 KB */
#define EXTDRVIPC_CM3_COMMUNICATION_AREA_SIZE      (2*_1K)     /* 2kB */
#define EXTDRVIPC_CM3_COMMUNICATION_AREA_OFFSET    (EXTDRVIPC_CM3_SRAM_SIZE - EXTDRVIPC_CM3_COMMUNICATION_AREA_SIZE)

PRV_SRVCPU_OPS_FUNC     EXTDRVIPC_CM3_opsFunc = NULL;
CPSS_HW_INFO_STC        *EXTDRVIPC_CM3_hwInfo_PTR = NULL;
CPSS_HW_DRIVER_STC      *EXTDRVIPC_CM3_drv_PTR = NULL;
PRV_SRVCPU_IPC_CHANNEL_STC *EXTDRVIPC_CM3_ipcCh_PTR = NULL;

/* Dragonite */
#define EXTDRVIPC_DRG_DTCM_ACTUAL_SIZE         (32*_1K)
#define EXTDRVIPC_DRG_COMMUNICATION_AREA_SIZE  (2*_1K)
#define EXTDRVIPC_DRG_COMMUNICATION_AREA_OFFSET        (EXTDRVIPC_DRG_DTCM_ACTUAL_SIZE - EXTDRVIPC_DRG_COMMUNICATION_AREA_SIZE)

IPC_SHM_STC EXTDRVIPC_DRG_shm;


/**** Common APIs ****/ 
/*      IPC_SHM_SYNC_FUNC_MODE_READ_E
*                          - Direct read from target's absolute address
*                            ptr is pointer to store data to
*                            targetPtr is target's address
*                            size is data size to read
*      IPC_SHM_SYNC_FUNC_MODE_WRITE_E
*                          - Direct write to target's absolute address
*                            ptr is pointer to data
*                            targetPtr is target's address
*                            size is data size to write
*/
static void directSyncFunc(
    IN  void*   cookie,
    IN  IPC_SHM_SYNC_FUNC_MODE_ENT mode,
    IN  void*   ptr,
    IN  IPC_UINTPTR_T targetPtr,
    IN  IPC_U32 size
)
{
    IPC_U32 *srcPtr, *dstPtr;

    GT_UNUSED_PARAM(cookie);
    if (mode == IPC_SHM_SYNC_FUNC_MODE_READ_E) {
        srcPtr = (IPC_U32*)targetPtr;
        dstPtr = (IPC_U32*)ptr;
    } else {
        srcPtr = (IPC_U32*)ptr;
        dstPtr = (IPC_U32*)targetPtr;
    }

    for (; (int)size>0; size-=4, srcPtr++, dstPtr++)
        *dstPtr = *srcPtr;
}

/**
* @internal extDrvIpcPoeMsgRead function
* @endinternal
*
* @brief   Marvell PoE protocol compliant for IPC Rx messages
*
* @param[in] msg_opcode               - Opcode of requested msg
* @param[in] msg_request_len          -
* @param[in] msg_request_PTR          - Buffer of max length
*       EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE
*
* @param[out] msg_response_len_PTR    - actual msg len read
* @param[out] msg_response            - the message that was read
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - otherwise.
*/
GT_STATUS extDrvIpcPoeMsgRead(
    IN   GT_32  msg_opcode,
    IN   GT_U32 msg_request_len,
    IN   GT_U8  *msg_request_PTR, /* Buffer of max length EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE */
    OUT  GT_U32 *msg_response_len_PTR,
    OUT  GT_U8  msg_response[EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE]
)
{
    EXTDRVIPC_PoE_TX_MESSAGE_STC tx_msg;
    EXTDRVIPC_PoE_RX_MESSAGE_STC rx_msg;
    unsigned int num_of_retries, send_res;
    int size;
    struct timespec time_before, time_after;

    if (EXTDRVIPC_shm_PTR == NULL)
        return GT_FAIL;

    /* Send Get message */
    tx_msg.opcode = msg_opcode;
    tx_msg.data_length = msg_request_len;
    if (msg_request_len > EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE)
        return GT_FAIL;
    memcpy(tx_msg.data, msg_request_PTR, msg_request_len);

    clock_gettime(CLOCK_MONOTONIC, &time_before);

    send_res = shmIpcSend(EXTDRVIPC_shm_PTR, 1, &tx_msg, EXTDRVIPC_TX_HEADER_SIZE + tx_msg.data_length);
    if (send_res != 0) {
        EXTDRVIPC_debug_printf("Failed to send message with opcode %#x", msg_opcode);
        return GT_FAIL;
    }

    /* Wait for response */
    size = EXTDRVIPC_MAX_MSG_SIZE;
    for (num_of_retries = 0; num_of_retries < EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES; num_of_retries++) {
        usleep(EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec);
        if (shmIpcRxChnReady(EXTDRVIPC_shm_PTR, 1)) {
            clock_gettime(CLOCK_MONOTONIC, &time_after);
            EXTDRVIPC_debug_printf("IPC msg_opcode [%#x] took time in ms: %d, number of tries %d",
                msg_opcode, (time_after.tv_nsec - time_before.tv_nsec)/1000000, num_of_retries+1);
            if (shmIpcRecv(EXTDRVIPC_shm_PTR, 1, &rx_msg, &size)==1) {
                /* Got a response. First make sure that the response matches the requested opcode */
                if (rx_msg.opcode != msg_opcode) {
                    EXTDRVIPC_debug_printf("Received message with opcode %#x, different from requested opcode %#x",
                                           rx_msg.opcode, msg_opcode);
                    return GT_FAIL;
                }
                if (rx_msg.status == GT_FAIL) {
                    EXTDRVIPC_debug_printf("Status of received message is 'failed'");
                    return GT_FAIL;
                }
                if (rx_msg.data_length > (int)EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE) {
                    EXTDRVIPC_debug_printf("Received message is too long");
                    return GT_FAIL;
                }

                /* Got a good response - copy the message */
                *msg_response_len_PTR = rx_msg.data_length;
                memcpy(msg_response, rx_msg.data, rx_msg.data_length);
                return GT_OK;

            }
        }
    }

    EXTDRVIPC_debug_printf("Exceeded number of tries %d", EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES);

    return GT_FAIL;
}

/**
* @internal extDrvIpcPoeMsgWrite function
* @endinternal
*
* @brief   Marvell PoE protocol compliant for IPC Tx messages
*
* @param[in] msg_opcode               - Opcode of requested msg
* @param[in] msg_request_len          -
* @param[in] msg_request_PTR          - Buffer of max length
*       DRAGONITE_DTCM_IPC_MAX_INTERNAL_TX_DATA_MSG_SIZE
*

* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - othersise.
*/

GT_STATUS extDrvIpcPoeMsgWrite(
    IN   GT_32  msg_opcode,
    IN   GT_U32 msg_request_len,
    IN   GT_U8  *msg_request_PTR, /* Buffer with max length EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE */
    IN   GT_BOOL is_debug
)
{
    EXTDRVIPC_PoE_TX_MESSAGE_STC tx_msg;
    EXTDRVIPC_PoE_RX_MESSAGE_STC rx_msg;
    unsigned int num_of_retries, send_res;
    int size;
    struct timespec time_before, time_after;

    if (EXTDRVIPC_shm_PTR == NULL)
        return GT_FAIL;

    /* Send Set message */
    tx_msg.opcode = msg_opcode;
    tx_msg.data_length = msg_request_len;
    if (msg_request_len > EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE)
        return GT_FAIL;
    memcpy(tx_msg.data, msg_request_PTR, msg_request_len);

    clock_gettime(CLOCK_MONOTONIC, &time_before);

    send_res = shmIpcSend(EXTDRVIPC_shm_PTR, 1, &tx_msg, EXTDRVIPC_TX_HEADER_SIZE + tx_msg.data_length/*DRAGONITE_DTCM_IPC_MAX_MSG_SIZE*/);
    EXTDRVIPC_debug_printf("IPC params: header size %#x, data length %#x\n", EXTDRVIPC_TX_HEADER_SIZE, tx_msg.data_length);
    if (send_res != 0)
    {
        EXTDRVIPC_debug_printf("Failed to send message with opcode %#x\n", msg_opcode);
        return GT_FAIL;
    }

    /* Wait for response */
    size = EXTDRVIPC_MAX_MSG_SIZE;
    for (num_of_retries = 0; num_of_retries < EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES; num_of_retries++) {
        usleep(EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec);
        if (shmIpcRxChnReady(EXTDRVIPC_shm_PTR, 1)) {
            clock_gettime(CLOCK_MONOTONIC, &time_after);
            EXTDRVIPC_debug_printf("IPC msg_opcode [%#x] took time in ms: %d, number of tries %d",
                msg_opcode, (time_after.tv_nsec - time_before.tv_nsec)/ 1000000, num_of_retries+1);
            if (shmIpcRecv(EXTDRVIPC_shm_PTR, 1, &rx_msg, &size)==1) {
                /* Got a response. First make sure that the response matches the requested opcode */
                if (rx_msg.opcode != msg_opcode) {
                    EXTDRVIPC_debug_printf("Received message with opcode %#x, different from requested opcode %#x",
                        rx_msg.opcode, msg_opcode);
                    return GT_FAIL;
                }
                if (rx_msg.status == GT_FAIL) {
                    EXTDRVIPC_debug_printf("Status of received message is 'failed'");
                    return GT_FAIL;
                }

                /* Got a good response, for debug : copy the data (not needed) */
                if (is_debug==GT_TRUE){
                    rx_msg.data[rx_msg.data_length] = '\0';
                    sprintf((char*)msg_request_PTR, "%snum of retries %d", rx_msg.data, num_of_retries+1);
                }
                return GT_OK;
            }
        }
    }

    EXTDRVIPC_debug_printf("Exceeded number of tries %d", EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES);

    return GT_FAIL;
}

/**
* @internal extDrvIpcDrgInit function
* @endinternal
*
* @brief   Initialize the IPC messaging driver that communicates with the
*          Dragonite
*
* @param[in] hwInfoPtr            - pointer to a structure contains HW addresses
*
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - othersise.
*/

GT_STATUS extDrvIpcDrgInit(
    IN CPSS_HW_INFO_STC   *hwInfoPtr
)
{
    // GT_STATUS rc;

    // shmIpcInit(&EXTDRVIPC_DRG_shm,
    //            (void *)(hwInfoPtr->resource.dragonite.dtcm.start +
    //            EXTDRVIPC_DRG_COMMUNICATION_AREA_OFFSET),
    //            EXTDRVIPC_DRG_COMMUNICATION_AREA_SIZE, 1,
    //            /* CLIENT */ directSyncFunc, NULL);

    // EXTDRVIPC_debug_printf(
    //     "IPC init params: Base %#x\n area offset = actual size - area size: %#x = %#x - %#x",
    //     hwInfoPtr->resource.dragonite.dtcm.start,
    //     EXTDRVIPC_DRG_COMMUNICATION_AREA_OFFSET, EXTDRVIPC_DRG_DTCM_ACTUAL_SIZE, EXTDRVIPC_DRG_COMMUNICATION_AREA_SIZE);

    // /* Create channel #1 with 1 buffer for RX and for TX */
    // rc = shmIpcConfigChannel(
    //     &EXTDRVIPC_DRG_shm,
    //     1, /* chn */
    //     1, EXTDRVIPC_MAX_MSG_SIZE,   /* rx */
    //     1, EXTDRVIPC_MAX_MSG_SIZE);  /* tx */
    // if (rc) {
    //     EXTDRVIPC_debug_printf("Failed to configure IPC Channel: %d", rc);
    //     return GT_FAIL;
    // }
    
    // EXTDRVIPC_shm_PTR = &EXTDRVIPC_DRG_shm;
    return GT_OK;
}

/**
+* @internal extDrvIpcCm3CreateChannel function
+* @endinternal
+*
+* @brief   Re-init CM3 IPc driver; only the IPc section (can be used to clear IPc)
+*
+*
+* @retval GT_OK                    - on success.
+* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
+* @retval GT_NO_SUCH               - driver no exists
+* @retval GT_FAIL                  - on error.
+*/
GT_STATUS extDrvIpcCm3CreateChannel(
    void
)
{
    GT_STATUS rc;

    if (EXTDRVIPC_CM3_ipcCh_PTR == NULL)
        return GT_NOT_INITIALIZED;

    /* init IPc as CLIENT */
    prvIpcAccessInit(EXTDRVIPC_CM3_ipcCh_PTR, GT_TRUE);

    /* Create channel #1 with 1 buffer for RX and for TX */
    rc = shmIpcConfigChannel(
        &EXTDRVIPC_CM3_ipcCh_PTR->shm,
        1, /* chn */
        1, EXTDRVIPC_MAX_MSG_SIZE,   /* rx */
        1, EXTDRVIPC_MAX_MSG_SIZE);  /* tx */
    if (rc) {
        EXTDRVIPC_debug_printf("extDrvIpcCm3CreateChannel: Failed to configure IPC Channel: %d\n", rc);
        return GT_FAIL;
    }
    return GT_OK;
}

/**
* @internal extDrvIpcCm3Init function
* @endinternal
*
* @brief   Init IPc driver in order to 
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
GT_STATUS extDrvIpcCm3Init(
    IN GT_U8                devNum,
    IN GT_U32               coreId
)
{
    GT_STATUS rc;
    /* temp */
    PRV_SRVCPU_OPS_FUNC     EXTDRVIPC_CM3_opsFunc;
    CPSS_HW_INFO_STC        EXTDRVIPC_CM3_hwInfo;
    CPSS_HW_DRIVER_STC      EXTDRVIPC_CM3_drv;

    /* get Pp HW info */
    // EXTDRVIPC_CM3_hwInfo_PTR = cpssDrvHwPpHwInfoStcPtrGet(devNum, 0);
    EXTDRVIPC_CM3_hwInfo_PTR = &EXTDRVIPC_CM3_opsFunc;
    EXTDRVIPC_CM3_hwInfo_PTR->busType = CPSS_HW_INFO_BUS_TYPE_PCI_E;
    EXTDRVIPC_CM3_hwInfo_PTR->devNum = 0;
    if (EXTDRVIPC_CM3_hwInfo_PTR == NULL)
        return GT_FAIL;
    
    /* get HW driver */
    // EXTDRVIPC_CM3_drv_PTR = prvCpssDrvHwPpPortGroupGetDrv(devNum, CPSS_PORT_GROUP_UNAWARE_MODE_CNS);
    EXTDRVIPC_CM3_drv_PTR = &EXTDRVIPC_CM3_drv;
    EXTDRVIPC_CM3_drv_PTR->devNum = 0;
    if (EXTDRVIPC_CM3_drv_PTR == NULL)
        return GT_FAIL;

    /* get operations CB */
    EXTDRVIPC_CM3_opsFunc = &prvSrvCpuOpsCM3_AC5;//prvSrvCpuGetOps(devNum);
    if (EXTDRVIPC_CM3_opsFunc == NULL)
        return GT_NOT_SUPPORTED;

    rc = EXTDRVIPC_CM3_opsFunc(EXTDRVIPC_CM3_hwInfo_PTR, EXTDRVIPC_CM3_drv_PTR, coreId, PRV_SRVCPU_OPS_EXISTS_E, NULL);
    if (rc != GT_OK)
        return GT_NO_SUCH;

    /* get IPc-Channel object*/
    rc = EXTDRVIPC_CM3_opsFunc(EXTDRVIPC_CM3_hwInfo_PTR, EXTDRVIPC_CM3_drv_PTR, coreId, PRV_SRVCPU_OPS_PRE_LOAD_E, &EXTDRVIPC_CM3_ipcCh_PTR);
    if (rc != GT_OK)
        return GT_FAIL;
    
    /* set IPc (shm) base address and size in the IPc object */
    EXTDRVIPC_CM3_ipcCh_PTR->shmSize = EXTDRVIPC_CM3_COMMUNICATION_AREA_SIZE;
    EXTDRVIPC_CM3_ipcCh_PTR->shmAddr = EXTDRVIPC_CM3_COMMUNICATION_AREA_OFFSET;

    EXTDRVIPC_debug_printf("extDrvIpcCm3Init: offset = actual size - area size: %#x = %#x - %#x\n",
        EXTDRVIPC_CM3_COMMUNICATION_AREA_OFFSET, EXTDRVIPC_CM3_SRAM_SIZE, EXTDRVIPC_CM3_COMMUNICATION_AREA_SIZE);

    rc = extDrvIpcCm3CreateChannel();
    if (rc != GT_OK)
        return rc;

    EXTDRVIPC_shm_PTR = &EXTDRVIPC_CM3_ipcCh_PTR->shm;
    
    return GT_OK;
}

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
GT_STATUS extDrvIpcCm3UnresetSet(
    GT_BOOL unresetEnable,
    GT_U32  coreId
)
{

    if (EXTDRVIPC_CM3_opsFunc == NULL || EXTDRVIPC_CM3_hwInfo_PTR == NULL || EXTDRVIPC_CM3_drv_PTR == NULL)
        return GT_NOT_SUPPORTED;

    if (unresetEnable == GT_TRUE){
        if (EXTDRVIPC_CM3_opsFunc(EXTDRVIPC_CM3_hwInfo_PTR, EXTDRVIPC_CM3_drv_PTR, coreId, PRV_SRVCPU_OPS_UNRESET_E, NULL) != GT_OK)
            return GT_FAIL;
    }
    else{
        if (EXTDRVIPC_CM3_opsFunc(EXTDRVIPC_CM3_hwInfo_PTR, EXTDRVIPC_CM3_drv_PTR, coreId, PRV_SRVCPU_OPS_RESET_E, NULL) != GT_OK)
            return GT_FAIL;
    }

    return GT_OK;
}

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
GT_STATUS extDrvIpcCm3FwDownload(
    IN GT_U32   coreId,
    IN GT_VOID  *buf,
    IN GT_U32    size
)
{
    GT_U32    p;

    extDrvIpcCm3UnresetSet(GT_FALSE, coreId);
    EXTDRVIPC_debug_printf("extDrvCm3FwDownload: download CM3 FW, size = %d\n", size);

    for (p=0; p<size; p+=4){
        EXTDRVIPC_CM3_ipcCh_PTR->drv->writeMask(EXTDRVIPC_CM3_ipcCh_PTR->drv, 0, p, buf+p, 1, 0xffffffff);
    }

    return GT_OK;
}

/***********************************************************/
/************* IPC for PoE '15 Bytes' protocol *************/
/***********************************************************/
#define EXTDRVIPC_15B_MSG_LEN  15

/**
* @internal extDrvIpc15ByteMsgWrite function
* @endinternal
*
* @brief   IPc "15 Bytes" message write
*
* @param[in] msg_PTR          - pointer to message buffer
*/
GT_STATUS extDrvIpc15ByteMsgWrite
(
    INOUT GT_U8 *msg_PTR
)
{
    GT_U8 tx_msg[EXTDRVIPC_15B_MSG_LEN];
    GT_U8 rx_msg[EXTDRVIPC_15B_MSG_LEN];
    unsigned int num_of_retries, send_res;
    int size=EXTDRVIPC_15B_MSG_LEN;
    struct timespec time_before, time_after;

    if (EXTDRVIPC_shm_PTR == NULL)
        return GT_FAIL;

    if (msg_PTR == NULL)
        return GT_BAD_PARAM;

    clock_gettime(CLOCK_MONOTONIC, &time_before);
    memcpy(tx_msg, msg_PTR, EXTDRVIPC_15B_MSG_LEN);
    send_res = shmIpcSend(EXTDRVIPC_shm_PTR, 1, tx_msg, EXTDRVIPC_15B_MSG_LEN);
    if (send_res != 0)
    {
        EXTDRVIPC_debug_printf("Failed to send message\n");
        return GT_FAIL;
    }

    for (num_of_retries = 0; num_of_retries < EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES; num_of_retries++) {
        usleep(EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec);
        if (shmIpcRxChnReady(EXTDRVIPC_shm_PTR, 1)) {
            clock_gettime(CLOCK_MONOTONIC, &time_after);
            
            if (shmIpcRecv(EXTDRVIPC_shm_PTR, 1, rx_msg, &size)==1) {
                /* Got a response. copy it to the in/out buffer */
                memcpy(msg_PTR, rx_msg, EXTDRVIPC_15B_MSG_LEN);
                return GT_OK;
            }
        }
    }
    return GT_FAIL;
}

/**
* @internal extDrvIpc15BytesMsgRead function
* @endinternal
*
* @brief   IPc "15 Bytes" message read
*
* @param[in] msg_PTR          - pointer to message buffer
*/
GT_STATUS extDrvIpc15BytesMsgRead(
    INOUT GT_U8 *msg_PTR
)
{
    unsigned int num_of_retries, send_res;
    int size=EXTDRVIPC_15B_MSG_LEN;
    GT_U8 tx_msg[EXTDRVIPC_15B_MSG_LEN];
    GT_U8 rx_msg[EXTDRVIPC_15B_MSG_LEN];
    struct timespec time_before, time_after;

    if (EXTDRVIPC_shm_PTR == NULL)
        return GT_FAIL;

    if (msg_PTR == NULL)
        return GT_BAD_PARAM;
    
    clock_gettime(CLOCK_MONOTONIC, &time_before);
    memcpy(tx_msg, msg_PTR, EXTDRVIPC_15B_MSG_LEN);
    send_res = shmIpcSend(EXTDRVIPC_shm_PTR, 1, tx_msg, EXTDRVIPC_15B_MSG_LEN);
    if (send_res != 0) {
        EXTDRVIPC_debug_printf("Failed to send message. rc: %d", send_res);
        return GT_FAIL;
    }

    /* Wait for response */
    for (num_of_retries = 0; num_of_retries < EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES; num_of_retries++) {
        usleep(EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec);
        if (shmIpcRxChnReady(EXTDRVIPC_shm_PTR, 1)) {
            clock_gettime(CLOCK_MONOTONIC, &time_after);
            
            if (shmIpcRecv(EXTDRVIPC_shm_PTR, 1, rx_msg, &size)==1) {
                /* Got a good response - copy the message */
                memcpy(msg_PTR, rx_msg, EXTDRVIPC_15B_MSG_LEN);
                return GT_OK;
            }
        }
    }

    EXTDRVIPC_debug_printf("Exceeded number of tries %d", EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES);

    return GT_FAIL;
}
