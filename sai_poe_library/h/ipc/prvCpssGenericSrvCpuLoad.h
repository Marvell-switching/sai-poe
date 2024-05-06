/*******************************************************************************
*              (c), Copyright 2015, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
*/
/**
********************************************************************************
* @file prvCpssGenericSrvCpuLoad.h
*
* @brief Service CPU firmware load/start APIs
*
* @version   1
********************************************************************************
*/
#ifndef __prvCpssGenericSrvCpuLoad_h__
#define __prvCpssGenericSrvCpuLoad_h__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <h/ipc/cpssTypes.h>
#include <h/ipc/cpssHwInfo.h>
#include <h/ipc/prvCpssGenericSrvCpuIpcDevCfg.h>

#define PRV_CPSS_GENERIC_SRV_CPU_USR_PATH_LEN_CNS	128

typedef struct PRV_CPSS_GENERIC_SRV_CPU_IPC_CHANNEL_CONFIG_STCT {
    GT_U8   channel; /* 0xff for end */
    GT_U32  maxrx;
    GT_U32  rxsize;
    GT_U32  maxtx;
    GT_U32  txsize;
} PRV_CPSS_GENERIC_SRV_CPU_IPC_CHANNEL_CONFIG_STC;


/**
*@internal cpssSrvCpuSetOptionalFW function
* @endinternal
*
* @brief Add a FW to be loaded to [dev, srvCpu]
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Cetus; Aldrin;
*         Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
*
* @param[in] devNum                   - device number,
* @param[in] srvCpuId                 - serice CPU ID
* @param[in] fw_id                    - a unique FW id, usually defined in
*      fw_ids.h
* @param[in] name                     - FW name (W/O .fw suffix)
*/
GT_STATUS cpssSrvCpuSetOptionalFW(
    IN GT_U8 devNum,
    IN GT_U8 srvCpuId,
    IN GT_U32 fw_id,
    IN GT_CHAR* name
);


/**
* @internal prvCpssGenericSrvCpuInitCust function
* @endinternal
*
* @brief   Upload firmware to service CPU
*          Start it, initialize IPC
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Cetus; Aldrin; Bobcat3; PIPE;
* @note   NOT APPLICABLE DEVICES:  Lion2;
*
* @param[in] devNum                - Device Number
* @param[in] scpuId                - service CPU id:
*                                    0 - CM3_0
*                                    1 - CM3_1
*                                    ...
*                                    0xfe - MSYS
* @param[in] ipcConfig             - IPC configuration, optional
*                                    should end with channel==0xff
* @param[in] preStartCb            - A custom routine executed before unreset
*                                    service CPU. (optional can be NULL)
* @param[in] preStartCookie        - parameter for preStartCb
* @param[out] fwChannelPtr         - object ID for IPC operations with this
*                                    service CPU. If this pointer is NULL, then
*                                    access object destroyed before return
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
*/
GT_STATUS prvCpssGenericSrvCpuInitCust
(
    IN  GT_U8       devNum,
    IN  GT_U8       scpuId,
    IN  PRV_CPSS_GENERIC_SRV_CPU_IPC_CHANNEL_CONFIG_STC *ipcConfig,
    IN  GT_STATUS (*preStartCb)(GT_UINTPTR  fwChannel, GT_UINTPTR  cookie),
    IN  GT_UINTPTR  preStartCookie,
    OUT GT_UINTPTR *fwChannelPtr
);

/**
* @internal prvCpssGenericSrvCpuInit function
* @endinternal
*
* @brief   Upload firmware to service CPU
*          Start it, initialize IPC
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Cetus; Aldrin; Bobcat3; PIPE;
* @note   NOT APPLICABLE DEVICES:  Lion2;
*
* @param[in] devNum                - device number.
* @param[in] scpuId                - service CPU id:
*                                    0 - CM3_0
*                                    1 - CM3_1
*                                    ...
*                                    0xffffffff - MSYS
* @param[in] ipcConfig             - IPC configuration, optional
*                                    should end with channel==0xff
* @param[in] preStartCb            - A custom routine executed before unreset
*                                    service CPU. (optional can be NULL)
* @param[in] preStartCookie        - parameter for preStartCb
* @param[out] fwChannelPtr         - object ID for IPC operations with this
*                                    service CPU. If this pointer is NULL, then
*                                    access object destroyed before return
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
* @retval GT_ALREADY_EXIST         - Already initialized for given devNum
*/
GT_STATUS prvCpssGenericSrvCpuInit
(
    IN  GT_U8       devNum,
    IN  GT_U8       scpuId,
    IN  PRV_CPSS_GENERIC_SRV_CPU_IPC_CHANNEL_CONFIG_STC *ipcConfig,
    IN  GT_STATUS (*preStartCb)(GT_UINTPTR  fwChannel, GT_UINTPTR  cookie),
    IN  GT_UINTPTR  preStartCookie,
    OUT GT_UINTPTR *fwChannelPtr
);

/**
* @internal prvCpssGenericSrvCpuProbeCust function
* @endinternal
*
* @brief   Probe Service CPU
*          Start it, initialize IPC
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Cetus; Aldrin; Bobcat3; PIPE;
* @note   NOT APPLICABLE DEVICES:  Lion2;
*
* @param[in] devNum                - Device Number
* @param[in] drv                   - CPSS_HW_DRIVER_STC* or NULL
* @param[in] scpuId                - service CPU id:
*                                    0 - CM3_0
*                                    1 - CM3_1
*                                    ...
*                                    0xffffffff - MSYS
* @param[in] hasIPC                - GT_TRUE if IPC should be probed on this
*                                    serviceCPU
* @param[in] checkIpcCb            - A custom routine executed when IPC structure
*                                    detected. Could be used for check transaction
*                                    Returns GT_TRUE if success
* @param[in] checkIpcCookie        - parameter for checkIpcCb
* @param[out] fwChannelPtr         - object ID for IPC operations with this
*                                    service CPU. If this pointer is NULL, then
*                                    access object destroyed before return
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
* @retvel GT_NOT_INITIALIZED       - not initialized. FW chould be reloaded
*/
GT_STATUS prvCpssGenericSrvCpuProbeCust
(
    IN  GT_U8       devNum,
    IN  GT_U32      scpuId,
    IN  GT_BOOL     hasIPC,
    IN  GT_BOOL (*checkIpcCb)(GT_UINTPTR  fwChannel, GT_UINTPTR  cookie),
    IN  GT_UINTPTR checkIpcCookie,
    OUT GT_UINTPTR *fwChannelPtr
);

/**
* @internal prvCpssGenericSrvCpuProbe function
* @endinternal
*
* @brief   Probe Service CPU
*          Start it, initialize IPC
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Cetus; Aldrin; Bobcat3; PIPE;
* @note   NOT APPLICABLE DEVICES:  Lion2;
*
* @param[in] devNum                - device number.
* @param[in] scpuId                - service CPU id:
*                                    0 - CM3_0
*                                    1 - CM3_1
*                                    ...
*                                    0xffffffff - MSYS
* @param[in] hasIPC                - GT_TRUE if IPC should be probed on this
*                                    serviceCPU
* @param[in] checkIpcCb            - A custom routine executed when IPC structure
*                                    detected. Could be used for check transaction
*                                    Returns GT_TRUE if success
* @param[in] checkIpcCookie        - parameter for checkIpcCb
* @param[out] fwChannelPtr         - object ID for IPC operations with this
*                                    service CPU. If this pointer is NULL, then
*                                    access object destroyed before return
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
* @retvel GT_NOT_INITIALIZED       - not initialized. FW chould be reloaded
* @retval GT_ALREADY_EXIST         - Already initialized for given devNum
*/
GT_STATUS prvCpssGenericSrvCpuProbe
(
    IN  GT_U8       devNum,
    IN  GT_U8       scpuId,
    IN  GT_BOOL     hasIPC,
    IN  GT_BOOL (*checkIpcCb)(GT_UINTPTR  fwChannel, GT_UINTPTR  cookie),
    IN  GT_UINTPTR checkIpcCookie,
    OUT GT_UINTPTR *fwChannelPtr
);

/**
* @internal prvCpssDbaToSrvCpuLoad function
* @endinternal
*
* @brief   Upload DBA FW to second service CPU
*
* @note   APPLICABLE DEVICES:      Bobcat3;
* @note   NOT APPLICABLE DEVICES:  AC3; Bobcat2; Caelum; Cetus; Aldrin;
*
* @param[in] devNum                - device number.
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
*/
GT_STATUS prvCpssDbaToSrvCpuLoad
(
    IN GT_U8    devNum
);

/**
* @internal prvCpssFlowManagerToSrvCpuLoad function
* @endinternal
*
* @brief   Upload Flow Manager FW to second service CPU
*
* @note   APPLICABLE DEVICES:      Aldrin2;
* @note   NOT APPLICABLE DEVICES:  AC3; Bobcat2; Caelum; Cetus; Aldrin;
*
* @param[in] devNum                - device number.
* @param[in] sCpuId                - service CPU ID.
* @param[out] fwChannel            - IPC channel.
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
*/
GT_STATUS prvCpssFlowManagerToSrvCpuLoad
(
    IN  GT_U8      devNum,
    IN  GT_U32     sCpuId,
    OUT GT_UINTPTR *fwChannel
);

/**
* @internal prvCpssIpfixManagerSrvCpuLoad function
* @endinternal
*
* @brief   Upload Ipfix Manager FW to second service CPU
*
* @note   APPLICABLE DEVICES:      Falcon;
*
* @param[in] devNum                - device number.
* @param[in] sCpuId                - service CPU ID.
* @param[out] fwChannel            - IPC channel.
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
*/
GT_STATUS prvCpssIpfixManagerToSrvCpuLoad
(
    IN  GT_U8      devNum,
    IN  GT_U32     sCpuId,
    OUT GT_UINTPTR *fwChannel
);

/**
* @internal prvCpssIpfixFwToSrvCpuLoad function
* @endinternal
*
* @brief   Upload IPFIX FW to service CPU
*
* @note   APPLICABLE DEVICES:      AC5X, AC5P;
*
* @param[in] devNum                - device number.
* @param[in] sCpuId                - service CPU ID.
* @param[out] fwChannel            - IPC channel.
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
*/
GT_STATUS prvCpssIpfixFwToSrvCpuLoad
(
    IN  GT_U8      devNum,
    IN  GT_U32     sCpuId,
    OUT GT_UINTPTR *fwChannel
);

/**
* @internal prvCpssGenericSrvCpuRemove function
* @endinternal
*
* @brief   Cleanup service CPU resources while cpssDxChCfgDevRemove
*
* @note   APPLICABLE DEVICES:       AC3; Bobcat2; Caelum; Cetus; Aldrin; Bobcat3.
* @note   NOT APPLICABLE DEVICES:   Lion2.
*
* @param[in] devNum                - device number.
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
*/
GT_STATUS prvCpssGenericSrvCpuRemove
(
    IN GT_U8    devNum,
    IN GT_U8    scpuId
);

/**
* @internal cpssGenericSrvCpuResetUnreset function
* @endinternal
*
* @brief   API to reset \ unreset  service CPU,
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Cetus; Aldrin; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] devNum                - device number
* @param[in] sCpuId                - service CPU ID.
* @param[in] resetOp               - reset - 0 , unreset - 1
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - scpuId not applicable for this PP
*                                    or firmare not found
* @retval GT_FAIL                  - on error.
*/
GT_STATUS cpssGenericSrvCpuResetUnreset
(
    IN  GT_U8   devNum,
    IN  GT_U8   scpuId,
    IN  GT_U8   resetOp
);

/**
* @internal cpssGenericSrvCpuFWUpgrade function
* @endinternal
*
* @brief   Send buffer with FW upgrade to service CPU,
*         to be programmed on flash, using boot channel.
*         buffer size is limited to 240 bytes.
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Cetus; Aldrin; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] devNum                   - device number,
* @param[in] bufBmp                   - bitmap of the FW:
*                                      0x01 - primary SuperImage
*                                      0x02 - secondary SuperImage,
*                                      0x03 - both.
* @param[in] bufNum                   - block number,
* @param[in] bufSize                  - buffer size:
*                                      must be: 32B < fwBufSize < 240B,
*                                      last bufSize=bufSize|0x100)
* @param[in] bufPtr                   - FW data ptr,
*
* @param[out] status                   - microInit boot channel retCode.
*
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_BAD_PARAM             - wrong devNum or flowId.
* @retval GT_BAD_PTR               - one of the parameters is NULL pointer.
* @retval GT_NOT_APPLICABLE_DEVICE - on not applicable device.
*/
GT_STATUS cpssGenericSrvCpuFWUpgrade
(
    IN  GT_U8   devNum,
    IN  GT_U32  bufBmp,
    IN  GT_U32  bufNum,
    IN  GT_U32  bufSize,
    IN  GT_U8  *bufPtr,
    IN  GT_U8   scpuId,
    OUT GT_U32 *status
);

PRV_SRVCPU_OPS_FUNC prvSrvCpuGetOps(
    IN  GT_U8   devNum
);


GT_VOID prvCpssGenericSrvCpuDestroy(GT_VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __prvCpssGenericSrvCpuLoad_h__ */
