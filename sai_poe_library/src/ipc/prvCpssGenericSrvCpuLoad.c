// /*******************************************************************************
// *              (c), Copyright 2015, Marvell International Ltd.                 *
// * THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
// * NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
// * OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
// * DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
// * THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
// * IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
// ********************************************************************************
// */
// /**
// ********************************************************************************
// * @file prvCpssGenericSrvCpuLoad.c
// *
// * @brief Service CPU firmware load/start APIs
// *
// * @version   1
// ********************************************************************************
// */

#include <h/ipc/gtGenTypes.h>
#include <h/ipc/cpssHwInfo.h>
#include <h/ipc/cpssHwDriverAPI.h>
#include <h/ipc/prvCpssGenericSrvCpuIpcDevCfg.h>

// #define FW_DEFAULT_PATH         "/opt/marvell/firmware"
// #define SRVCPU_ID_ALL           0xFF
// #define ARRAY_SIZE(x)           ((sizeof(x)) / (sizeof(x[0])))
// #define DEV_FMLY_SUB_FMLY(x)    (PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(x)->devSubFamily<<16 |\
//                                  PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(x)->devFamily)
// #ifdef CPU_BE
//   #define LE_SWAP_32BIT(x) (x)
//   #define LE_SWAP_16BIT(x) (x)
// #else
//   #define LE_SWAP_32BIT(x) CPSS_BYTE_SWAP_32BIT(x)
//   #define LE_SWAP_16BIT(x) CPSS_BYTE_SWAP_16BIT(x)
// #endif

// PRV_SRVCPU_OPS_FUNC prvSrvCpuGetOps(
//     IN  GT_U8   devNum
// )
// {
//     GT_U32 i;
//     GT_U16 deviceId; /* PCI device Id */

//     i = PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->devType;
//     deviceId = (i >> 16) & 0xffff;

//     for (i = 0; prvSrvCpuDescr[i].ops; i++)
//     {
//         if ((deviceId & prvSrvCpuDescr[i].devIdMask) == (prvSrvCpuDescr[i].devId & prvSrvCpuDescr[i].devIdMask))
//             break;
//     }

//     if(prvSrvCpuDescr[i].ops == NULL)
//     {
//         CPSS_LOG_ERROR_MAC("The deviceId[0x%4.4x] not defined as 'supporting' Service CPU (see prvSrvCpuDescr[])",
//             deviceId);
//     }
//     return prvSrvCpuDescr[i].ops;
// }

// /*******************************************************************************
// * prvCpssDrvHwPpPortGroupGetDrv
// *
// * DESCRIPTION:
// *       Read a register value from the given PP.
// *       in the specific port group in the device
// * INPUTS:
// *       devNum      - The PP to read from.
// *       portGroupId - The port group id. relevant only to 'multi-port-groups'
// *                     devices. Supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
// *                          (APPLICABLE DEVICES: Lion2)
// *
// * OUTPUTS:
// *       None
// *
// * RETURNS:
// *       pointer to device driver or NULL
// *
// * COMMENTS:
// *       None.
// *
// *******************************************************************************/
// CPSS_HW_DRIVER_STC* prvCpssDrvHwPpPortGroupGetDrv
// (
//     IN GT_U8    devNum,
//     IN GT_U32   portGroupId
// )
// {
//     PRV_CPSS_DRV_PORT_GROUPS_INFO_STC *pgInfo;

//     if (PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum) == NULL )
//        return 0;
//     pgInfo = &(PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->portGroupsInfo);
//     if(pgInfo->isMultiPortGroupDevice == GT_TRUE)
//     {
//         if(pgInfo->debugForcedPortGroupId != CPSS_PORT_GROUP_UNAWARE_MODE_CNS)
//             portGroupId = pgInfo->debugForcedPortGroupId;

//         if((portGroupId) == CPSS_PORT_GROUP_UNAWARE_MODE_CNS)
//         {   /*use the first active port group */
//             portGroupId = pgInfo->firstActivePortGroup;
//         }
//         else if(0 == PRV_CPSS_DRV_IS_IN_RANGE_PORT_GROUP_ID_MAC(devNum,portGroupId) ||
//                (0 == (pgInfo->activePortGroupsBmp & (1<<(portGroupId)))))
//         {   /* non active port group */
//             return NULL;
//         }
//     }
//     else  /*use the only 'active port group' */
//     {
//         portGroupId = pgInfo->firstActivePortGroup;
//     }
//     return PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->drivers[portGroupId];
// }

// /*******************************************************************************
// * cpssDrvHwPpHwInfoStcPtrGet
// *
// * DESCRIPTION:
// *       Read pointer to CPSS_HW_INFO_STC for a given devNum/portGroupId
// *
// * INPUTS:
// *       devNum  - The PP device number to read from.
// *       portGroupId  - The port group Id. relevant only to 'multi-port-groups' devices.
// *                          (APPLICABLE DEVICES: Lion2)
// *                 supports value CPSS_PORT_GROUP_UNAWARE_MODE_CNS
// *
// * OUTPUTS:
// *       None
// *
// * RETURNS:
// *       Pointer to CPSS_HW_INFO_STC
// *       NULL - if not set/invalid parameter
// *
// * COMMENTS:
// *       None.
// *
// *******************************************************************************/
// CPSS_HW_INFO_STC* cpssDrvHwPpHwInfoStcPtrGet
// (
//     IN  GT_U8   devNum,
//     IN GT_U32   portGroupId
// )
// {
//     if (devNum >= PRV_CPSS_MAX_PP_DEVICES_CNS)
//         return NULL;
//     if (PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum) == NULL)
//         return NULL;
//     if (portGroupId == CPSS_PORT_GROUP_UNAWARE_MODE_CNS)
//         portGroupId = 0;
//     if (portGroupId >= CPSS_MAX_PORT_GROUPS_CNS)
//         return NULL;
//     if (PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->hwInfo[portGroupId].busType == CPSS_HW_INFO_BUS_TYPE_NONE_E)
//         return NULL;
//     return &(PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->hwInfo[portGroupId]);
// }

// void prvIpcSync
// (
//     IN  void*   cookie,
//     IN  IPC_SHM_SYNC_FUNC_MODE_ENT mode,
//     IN  void*   ptr,
//     IN  IPC_UINTPTR_T targetPtr,
//     IN  IPC_U32 size
// )
// {
//     PRV_SRVCPU_IPC_CHANNEL_STC   *d = (PRV_SRVCPU_IPC_CHANNEL_STC*)cookie;
// #ifdef SHARED_MEMORY
//     CPSS_HW_DRIVER_STC localDrv;
// #endif
//     CPSS_HW_DRIVER_STC  *drv =d->drv;

// #ifdef SHARED_MEMORY
//     localDrv.type = drv->type;
//     prvCpssDrvHwDrvReload(&localDrv);
//     drv = &localDrv;
// #endif
//     size = (size+3) & 0xfffffffc; /* align size to 4byte*/
//     if (mode == IPC_SHM_SYNC_FUNC_MODE_READ_E)
//     {
//         drv->read(d->drv, 0, targetPtr, (GT_U32*)ptr, size/4);
//     }
//     else
//     {
//         /* IPC_SHM_SYNC_FUNC_MODE_WRITE_E */
//         drv->writeMask(d->drv, 0, targetPtr, (GT_U32*)ptr, size/4, 0xffffffff);
//     }
// }

// GT_VOID prvIpcAccessInit(PRV_SRVCPU_IPC_CHANNEL_STC *s, GT_BOOL init)
// {
//     s->shmResvdRegs = (GT_UINTPTR)(s->targetBase+(s->size-4));
//     if (init == GT_TRUE)
//     {
//         shmIpcInit(&(s->shm), (void*)((GT_UINTPTR)(s->shmAddr)), s->shmSize,
//                    1, prvIpcSync, s);
//         return;
//     }
//     /* init == GT_FALSE, probe */
//     s->shm.shmLen = s->shmSize;
//     s->shm.server = 1;
//     s->shm.shm = s->shmAddr;
//     s->shm.syncFunc = prvIpcSync;
//     s->shm.syncCookie = s;
// }