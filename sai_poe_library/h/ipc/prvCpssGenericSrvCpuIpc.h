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
* @file prvCpssGenericSrvCpuIpc.h
*
* @brief Service CPU IPC APIs
*
* @version   1
********************************************************************************
*/
#ifndef __prvCpssGenericSrvCpuIpc_h__
#define __prvCpssGenericSrvCpuIpc_h__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <h/ipc/cpssTypes.h>

/**
* @internal prvCpssGenericSrvCpuIpcUsedTxBuffLengthGet function
* @endinternal
*
* @brief   This API allows the application to get used TX IPC
*         buffer length.
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] fwChannel             - object ID for IPC operations, returned by rvCpssGenericSrvCpuInit
* @param[in] channel               - channel number
* @param[out] lengthPtr            - (pointer to) used IPC TX buffer length
* @param[out] sizePtr              - (pointer to) total size of IPC TX buffer
*
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuIpcUsedTxBuffLengthGet
(
    IN  GT_UINTPTR fwChannel,
    IN  GT_U32   channel,
    OUT GT_U32   *lengthPtr,
    OUT GT_U32   *sizePtr
);

/**
* @internal prvCpssGenericSrvCpuIpcMessageSend function
* @endinternal
*
* @brief   This API allows the application to send a message to other side,
*         using a buffer it was previously fetched from the IPC (by using the
*         Buffer-Get API)
*         It may choose to send asynchrony or synchronic and in case
*         synchronic how much tome to wait for processing.
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] fwChannel             - object ID for IPC operations, returned by
*                                    prvCpssGenericSrvCpuInit
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuIpcMessageSend
(
    IN  GT_UINTPTR fwChannel,
    IN  GT_U32   channel,
    IN  GT_U8   *msgData,
    IN  GT_U32   msgDataSize
);

/**
* @internal prvCpssGenericSrvCpuIpcMessageSendCpuId function
* @endinternal
*
* @brief   This API allows the application to send a message to other side,
*         using a buffer it was previously fetched from the IPC (by using the
*         Buffer-Get API)
*         It may choose to send asynchrony or synchronic and in case
*         synchronic how much tome to wait for processing.
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] devNum             - The PP to write to.
* @param[in] scpuId             - cpu ID for IPC operations
* @param[in] channel            - the channel id
* @param[in] msgData            - msg data
* @param[in] msgDataSize        - msg size
*
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuIpcMessageSendCpuId
(
    IN  GT_U8    devNum,
    IN  GT_U8    scpuId,
    IN  GT_U32   channel,
    IN  GT_U8   *msgData,
    IN  GT_U32   msgDataSize
);

/**
* @internal prvCpssGenericSrvCpuIpcMessageRecv function
* @endinternal
*
* @brief   This API allows the application to fetch message sent by the other
*         side. Application may choose to wait for incoming message or not
*         (if application wish to use polling it can loop with no waiting).
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] fwChannel             - object ID for IPC operations, returned by
*                                    prvCpssGenericSrvCpuInit
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NO_MORE               - no messages ready.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuIpcMessageRecv
(
    IN  GT_UINTPTR fwChannel,
    IN  GT_U32   channel,
    OUT GT_U8   *msgData,
    OUT GT_U32  *msgDataSize
);

/**
* @internal prvCpssGenericSrvCpuIpcMessageRecvCpuId function
* @endinternal
*
* @brief   This API allows the application to fetch message sent by the other
*         side. Application may choose to wait for incoming message or not
*         (if application wish to use polling it can loop with no waiting).
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] devNum             - The PP to write to.
* @param[in] scpuId             - cpu ID for IPC operations
* @param[in] channel            - the channel id
* @param[out] msgData            - msg data
* @param[out] msgDataSize        - msg size
*
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NO_MORE               - no messages ready.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuIpcMessageRecvCpuId
(
    IN  GT_U8    devNum,
    IN  GT_U8    scpuId,
    IN  GT_U32   channel,
    OUT GT_U8   *msgData,
    OUT GT_U32  *msgDataSize
);

/**
* @internal prvCpssGenericSrvCpuWrite function
* @endinternal
*
* @brief   Write to Service CPU "firmware section"
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] fwChannel             - object ID for IPC operations, returned by
*                                    prvCpssGenericSrvCpuInit
* @param[in] srvCpuAddr            - The srvCpu internal address
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuWrite
(
    IN  GT_UINTPTR fwChannel,
    IN  GT_U32   srvCpuAddr,
    IN  void    *data,
    IN  GT_U32   size
);

/**
* @internal prvCpssGenericSrvCpuWriteCpuId function
* @endinternal
*
* @brief   Write to Service CPU "firmware section"
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] devNum             - The PP to write to.
* @param[in] scpuId             - cpu ID for IPC operations
* @param[in] srvCpuAddr         - cpu address
* @param[in] data               - data
* @param[in] size               - size
*
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuWriteCpuId
(
    IN  GT_U8    devNum,
    IN  GT_U8    scpuId,
    IN  GT_U32   srvCpuAddr,
    IN  void    *data,
    IN  GT_U32   size
);

/**
* @internal prvCpssGenericSrvCpuRead function
* @endinternal
*
* @brief   Read from Service CPU "firmware section"
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] fwChannel             - object ID for IPC operations, returned by
*                                    prvCpssGenericSrvCpuInit
* @param[in] srvCpuAddr               - The srvCpu internal address
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuRead
(
    IN  GT_UINTPTR fwChannel,
    IN  GT_U32   srvCpuAddr,
    OUT void    *data,
    IN  GT_U32   size
);

/**
* @internal prvCpssGenericSrvCpuReadCpuId function
* @endinternal
*
* @brief   Read from Service CPU "firmware section"
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] devNum             - The PP to write to.
* @param[in] scpuId             - cpu ID for IPC operations
* @param[in] srvCpuAddr          - The srvCpu internal address
* @param[out] data               - data
* @param[in] size               - size
*
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuReadCpuId
(
    IN  GT_U8    devNum,
    IN  GT_U8    scpuId,
    IN  GT_U32   srvCpuAddr,
    OUT void    *data,
    IN  GT_U32   size
);

/**
* @internal prvCpssGenericSrvCpuRegisterWriteFwChannel function
* @endinternal
*
* @brief   Read a service CPU IPC register value
*
* @note   APPLICABLE DEVICES:      AC3; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Pipe.
* @note   NOT APPLICABLE DEVICES:  Lion2.
*
* @param[in] fwChannel             - object ID for IPC operations, returned by
*                                    prvCpssGenericSrvCpuInit
* @param[in] regAddr               - The The register's address to write to
* @param[in] data                  - The value to be written
* @retval GT_OK                    - on success.
* @retval GT_FAIL                  - on error.
* @retval GT_NOT_INITIALIZED       - srvCpu IPC not initialized for this device
*/
GT_STATUS prvCpssGenericSrvCpuRegisterWriteFwChannel
(
    IN GT_UINTPTR   fwChannel,
    IN GT_U32       regAddr,
    IN GT_U32       value
);


/**
* @internal prvCpssGenericSrvCpuRegisterClearOnRead function
* @endinternal
*
* @brief   Reads a service CPU IPC register value and clears it
*          right after
* @param[in] devNum                - The PP to read from.
* @param[in] portGroupId           - The port group id. Not used
* @param[in] regAddr               - The register's address to read from.
*                                    Note - regAddr should be < 0x1000000
*
* @param[out] dataPtr              - Includes the register value.
*
* @retval GT_OK                    - on success
* @retval GT_FAIL                  - on hardware error
* @retval GT_NOT_INITIALIZED       - if the driver was not initialized
*/
GT_STATUS prvCpssGenericSrvCpuRegisterClearOnRead
(
    IN  GT_U8    devNum,
    IN  GT_U32   portGroupId,
    IN  GT_U32   regAddr,
    OUT GT_U32   *dataPtr
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __prvCpssGenericSrvCpuIpc_h__ */

