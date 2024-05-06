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
* @file prvCpssGenericSrvCpuIpcDevCfg.h
*
* @brief Service CPU IPC per-device config
*
* @version   1
********************************************************************************
*/
#ifndef __prvCpssGenericSrvCpuIpcDevCfg_h__
#define __prvCpssGenericSrvCpuIpcDevCfg_h__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <h/ipc/cpssDriverPpHw.h>
#include <h/ipc/prvCpssGenericSrvCpuIpc.h>
#include <h/ipc/mvShmIpc.h>
// #include <cpss/common/srvCpu/prvSrvCpuFirmware.h>
/*#include <cpssDriver/pp/prvCpssDrvPpDefs.h>*/


/********************************************************************/
/**** Indirect support                                           ****/
/********************************************************************/
#define SRVCPU_MAX_IPC_CHANNEL  20
#define SRVCPU_IPC_CHANNEL_ALL  0xFF
#define SRVCPU_ID_DONT_CARE  0xFE
#define SRVCPU_IDX_GET_MAC(cpuIdx)  (cpuIdx == SRVCPU_ID_DONT_CARE)? 0:cpuIdx

typedef struct {
    GT_UINTPTR           base; /* == 0 for indirect */
    GT_UINTPTR           size;
    GT_U32               targetBase;
    GT_U32               shmAddr;
    GT_U32               shmSize;
    GT_UINTPTR           shmResvdRegs;
    CPSS_HW_DRIVER_STC  *drv;
    IPC_SHM_STC          shm;
    GT_BOOL              irqBound;
} PRV_SRVCPU_IPC_CHANNEL_STC;

GT_VOID prvIpcAccessInit(PRV_SRVCPU_IPC_CHANNEL_STC *s, GT_BOOL init);
GT_STATUS prvIpcAccessDestroy(PRV_SRVCPU_IPC_CHANNEL_STC *s);
CPSS_HW_DRIVER_STC *prvSrvCpuRamDirectCreate(
    IN  GT_U8       devNum,
    IN  GT_UINTPTR  virtStart,
    IN  GT_U32      targetStart,
    IN  GT_U32      targetSize
);
CPSS_HW_DRIVER_STC *prvSrvCpuRamIndirectCreate(
    IN  CPSS_HW_DRIVER_STC  *d,
    IN  GT_U32              addrSpace,
    IN  GT_U32              regStart,
    IN  GT_U32              size
);
#ifdef SHARED_MEMORY
GT_VOID cpssHwDriverSrvCpuRamIndirectDrvReload
(
    CPSS_HW_DRIVER_STC *drv
);

GT_VOID cpssHwDriverSrvCpuRamDirectDrvReload
(
    CPSS_HW_DRIVER_STC *drv
);

#endif


/********************************************************************/
/**** Service CPU driver APIs                                    ****/
/********************************************************************/
typedef enum {
    PRV_SRVCPU_OPS_EXISTS_E,
    PRV_SRVCPU_OPS_IS_ON_E,
    PRV_SRVCPU_OPS_PRE_LOAD_E,
    PRV_SRVCPU_OPS_RESET_E,
    PRV_SRVCPU_OPS_UNRESET_E,
    PRV_SRVCPU_OPS_PRE_CHECK_IPC_E,
} PRV_SRVCPU_OPS_ENT;
typedef GT_STATUS (*PRV_SRVCPU_OPS_FUNC)(
    IN  CPSS_HW_INFO_STC    *hwInfo,
    IN  CPSS_HW_DRIVER_STC  *drv,
    IN  GT_U32              scpuId,
    IN  PRV_SRVCPU_OPS_ENT  op,
    OUT void                *ret
);
/* drivers */
GT_STATUS prvSrvCpuOpsMsys(
    IN  CPSS_HW_INFO_STC    *hwInfo,
    IN  CPSS_HW_DRIVER_STC  *drv,
    IN  GT_U32              scpuId,
    IN  PRV_SRVCPU_OPS_ENT  op,
    OUT void                *ret
);
GT_STATUS prvSrvCpuOpsBobK(
    IN  CPSS_HW_INFO_STC    *hwInfo,
    IN  CPSS_HW_DRIVER_STC  *drv,
    IN  GT_U32              scpuId,
    IN  PRV_SRVCPU_OPS_ENT  op,
    OUT void                *ret
);
GT_STATUS prvSrvCpuOpsCM3(
    IN  CPSS_HW_INFO_STC    *hwInfo,
    IN  CPSS_HW_DRIVER_STC  *drv,
    IN  GT_U32              scpuId,
    IN  PRV_SRVCPU_OPS_ENT  op,
    OUT void                *ret
);

GT_STATUS prvSrvCpuOpsCM3_AC5(
    IN  CPSS_HW_INFO_STC    *hwInfo,
    IN  CPSS_HW_DRIVER_STC  *drv,
    IN  GT_U32              scpuId,
    IN  PRV_SRVCPU_OPS_ENT  op,
    OUT void                *ret
);

GT_STATUS prvSrvCpuOpsCM3_AC5P(
    IN  CPSS_HW_INFO_STC    *hwInfo,
    IN  CPSS_HW_DRIVER_STC  *drv,
    IN  GT_U32              scpuId,
    IN  PRV_SRVCPU_OPS_ENT  op,
    OUT void                *ret
);
/*extern PRV_SRVCPU_IPC_CHANNEL_STC* prvIpcDevCfg[PRV_CPSS_MAX_PP_DEVICES_CNS];*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __prvCpssGenericSrvCpuIpcDevCfg_h__ */

