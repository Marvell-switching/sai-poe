/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
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
* @file prvCpssDrvPpDefs.h
*
* @brief Includes driver level structs needed for implementing HW related
* functions, and interrupt handling. And common definitions for driver
* level communication.
*
* @version   11
********************************************************************************
*/
#ifndef __prvCpssDrvPpDefsh
#define __prvCpssDrvPpDefsh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <h/ipc/cpssHwDriverAPI.h>
#include <h/ipc/prvCpssGenericSrvCpuIpcDevCfg.h>

#define SHARED_MEMORY 1

/* constant to state that the parameter with this value need to be ignored
    This meaning is given only for fields that explicitly stated to support it */
#define PRV_CPSS_DRV_PARAM_NOT_USED_CNS 0xFFFFFFFF

/* bmp for hw interfaces */
#define PRV_CPSS_DRV_HW_IF_PCI_BMP_CNS      (1 << CPSS_CHANNEL_PCI_E)
#define PRV_CPSS_DRV_HW_IF_SMI_BMP_CNS      (1 << CPSS_CHANNEL_SMI_E)
#define PRV_CPSS_DRV_HW_IF_TWSI_BMP_CNS     (1 << CPSS_CHANNEL_TWSI_E)
#define PRV_CPSS_DRV_HW_IF_PEX_BMP_CNS      (1 << CPSS_CHANNEL_PEX_E)

/*set the HW interface bmp */
#define PRV_CPSS_DRV_HW_IF_BMP_MAC(mngInterfaceType)\
    (1 << (GT_U32)mngInterfaceType)

/* bmp of "PCI" compatible behavior */
#define PRV_CPSS_DRV_HW_IF_PCI_COMPATIBLE_MAC(devNum)\
    ((PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->drvHwIfSupportedBmp &        \
     PRV_CPSS_DRV_HW_IF_PCI_BMP_CNS) ? 1 : 0)

/* bmp of "SMI" compatible behavior */
#define PRV_CPSS_DRV_HW_IF_SMI_COMPATIBLE_MAC(devNum)\
    ((PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->drvHwIfSupportedBmp &        \
     PRV_CPSS_DRV_HW_IF_SMI_BMP_CNS) ? 1 : 0)

/* bmp of "TWSI" compatible behavior */
#define PRV_CPSS_DRV_HW_IF_TWSI_COMPATIBLE_MAC(devNum)\
    ((PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->drvHwIfSupportedBmp &        \
     PRV_CPSS_DRV_HW_IF_TWSI_BMP_CNS) ? 1 : 0)

/* bmp of "PEX" compatible behavior */
#define PRV_CPSS_DRV_HW_IF_PEX_COMPATIBLE_MAC(devNum)\
    ((PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(devNum)->drvHwIfSupportedBmp &        \
     PRV_CPSS_DRV_HW_IF_PEX_BMP_CNS) ? 1 : 0)


#define PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum) \
        ((PRV_CPSS_DRIVER_PP_CONFIG_STC *)(PRV_SHARED_GLOBAL_VAR_GET(commonMod.configDir.dDrvPpConGenInitSrc.prvCpssDrvPpConfig)[_devNum]))

#define PRV_SHARED_CPSS_DRIVER_PP_CONFIG_NO_CAST \
        PRV_SHARED_GLOBAL_VAR_GET(commonMod.configDir.dDrvPpConGenInitSrc.prvCpssDrvPpConfig)

#define PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG_CHECK(_index) \
        do \
        { \
            PRV_SHARED_GLOBAL_VAR_DB_CHECK(); \
            if(NULL == PRV_SHARED_CPSS_DRIVER_PP_CONFIG_NO_CAST[_index])\
            { \
                CPSS_LOG_ERROR_AND_RETURN_MAC(GT_NOT_INITIALIZED, \
                                    "prvCpssDrvPpConfig[%d]==NULL\n", _index);\
            } \
        } \
        while(0)


/**
* @struct PRV_CPSS_DRV_PORT_GROUPS_INFO_STC
 *
 * @brief A structure to hold info about the port groups of a device
 * NOTE: for 'non multi port groups' device
 * isMultiPortGroupDevice = GT_FALSE
 * numOfPortGroups = 1 ,
 * activePortGroupsBmp = 1
 * firstActivePortGroup = 0 (CPSS_NON_MULTI_PORT_GROUP_DEVICE_INDEX_CNS)
 * lastActivePortGroup = 0  (CPSS_NON_MULTI_PORT_GROUP_DEVICE_INDEX_CNS)
*/
typedef struct{

    /** is the device : 'multi */
    GT_BOOL isMultiPortGroupDevice;

    /** @brief The number of port groups that the device support.
     *  NOTE: this number not depend on the number of active port groups ,
     *  for example this value is 4 always for Lion.
     */
    GT_U32 numOfPortGroups;

    /** Bitmap of active port groups */
    GT_U32 activePortGroupsBmp;

    /** The portGroupId of the first active port group id */
    GT_U32 firstActivePortGroup;

    /** @brief The portGroupId of the last active port group id,
     *  Note that there can be non active port groups
     *  between this port group and the firstActivePortGroup
     *  used for loops and for allocations for port groups.
     *  --> used instead of : 'num Of port groups'
     *  dynamic allocate fields that are 'per port group' , according
     *  to (lastValidPortGroup + 1)
     */
    GT_U32 lastActivePortGroup;

    /** @brief this has debug purpose only , to 'force' specific
     *  portGroupId   to check.
     *  used only when != CPSS_PORT_GROUP_UNAWARE_MODE_CNS
     *  NOTE : relevant only for multi-port-groups device.
     */
    GT_U32 debugForcedPortGroupId;

} PRV_CPSS_DRV_PORT_GROUPS_INFO_STC;

/* macro to start a loop on active port group ids */
#define PRV_CPSS_DRV_START_LOOP_PORT_GROUPS_MAC(_devNum, _portGroupId)   \
    for((_portGroupId) = PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.firstActivePortGroup;\
        (_portGroupId) <= PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.lastActivePortGroup;\
        (_portGroupId)++)                                                \
    {                                                                    \
        if(0 == (PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.activePortGroupsBmp & (1<<(_portGroupId))))\
        {                                                                \
            continue;                                                    \
        }

/* macro to end a loop on active port groups */
#define PRV_CPSS_DRV_END_LOOP_PORT_GROUPS_MAC(_devNum, _portGroupId)    \
    }

/*
   macro to check that the given portGroupId is in range of allocated array .
   NOTE: value CPSS_PORT_GROUP_UNAWARE_MODE_CNS is always valid
*/
#define PRV_CPSS_DRV_IS_IN_RANGE_PORT_GROUP_ID_MAC(_devNum, _portGroupId) \
    (((_portGroupId) >= CPSS_MAX_PORT_GROUPS_CNS) ? 0 : 1)

/*
   macro to check that the given portGroupId is valid .
   NOTE: value CPSS_PORT_GROUP_UNAWARE_MODE_CNS is always valid
*/
#define PRV_CPSS_DRV_IS_VALID_PORT_GROUP_ID_MAC(_devNum,_portGroupId)      \
    (((_portGroupId) == CPSS_PORT_GROUP_UNAWARE_MODE_CNS) ? 1 :    \
     (0 == PRV_CPSS_DRV_IS_IN_RANGE_PORT_GROUP_ID_MAC(_devNum,_portGroupId)) ? 0 :            \
     (PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.activePortGroupsBmp & (1<<(_portGroupId))) ? 1 : \
     0)

/* check the need to force portGroupId */
#define PRV_CPSS_DRV_FORCE_PORT_GROUP_ID_CHECK_MAC(_devNum,_portGroupId)               \
    if(PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.debugForcedPortGroupId !=           \
       CPSS_PORT_GROUP_UNAWARE_MODE_CNS)                                                \
        _portGroupId = PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.debugForcedPortGroupId

/*
   macro to check that the given portGroupId is valid .
   NOTE:
    1. value CPSS_PORT_GROUP_UNAWARE_MODE_CNS is always valid
    2. for 'non multi-port-groups' device , the portGroupId is
        set to be the 'only' port group.
*/
#define PRV_CPSS_DRV_CHECK_PORT_GROUP_ID_MAC(_devNum,_portGroupId)                   \
    if(PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.isMultiPortGroupDevice == GT_TRUE)\
    {                                                                                \
        PRV_CPSS_DRV_FORCE_PORT_GROUP_ID_CHECK_MAC(_devNum,_portGroupId);            \
                                                                                     \
        if(0 == PRV_CPSS_DRV_IS_VALID_PORT_GROUP_ID_MAC(_devNum,_portGroupId))       \
        {                                                                            \
            CPSS_LOG_ERROR_AND_RETURN_MAC(GT_BAD_PARAM,                              \
                prvCpssLogErrorMsgPortGroupNotValid, _devNum,_portGroupId);          \
        }                                                                            \
    }                                                                                \
    else                                                                             \
        _portGroupId = PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.firstActivePortGroup


/*
   macro to check that the given portGroup is active , for a 'read' operation.
   macro will update the portGroupId , when portGroupId = CPSS_PORT_GROUP_UNAWARE_MODE_CNS
   or when device is non multi-port-group device.
   NOTE: value CPSS_PORT_GROUP_UNAWARE_MODE_CNS is valid --> converted to
            PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.firstActivePortGroup

*/
#define PRV_CPSS_DRV_CHECK_ACTIVE_PORT_GROUP_ID_FOR_READ_OPERATION_MAC(_devNum,_portGroupId)     \
    if(PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.isMultiPortGroupDevice == GT_TRUE)            \
    {                                                                                            \
        PRV_CPSS_DRV_FORCE_PORT_GROUP_ID_CHECK_MAC(_devNum,_portGroupId);                        \
                                                                                                 \
        if((_portGroupId) == CPSS_PORT_GROUP_UNAWARE_MODE_CNS)                                   \
        {   /*use the first active port group */                                                 \
            _portGroupId = PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.firstActivePortGroup;     \
        }                                                                                        \
        else if(0 == PRV_CPSS_DRV_IS_IN_RANGE_PORT_GROUP_ID_MAC(_devNum,_portGroupId) ||         \
               (0 == (PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.activePortGroupsBmp & (1<<(_portGroupId)))))\
        {   /* non active port group */                                                          \
            CPSS_LOG_ERROR_AND_RETURN_MAC(GT_BAD_PARAM,                                          \
                prvCpssLogErrorMsgPortGroupNotActive, _devNum, _portGroupId);                    \
        }                                                                                        \
    }                                                                                            \
    else  /*use the only 'active port group' */                                                  \
        _portGroupId = PRV_SHARED_GLOBAL_VAR_CPSS_DRIVER_PP_CONFIG(_devNum)->portGroupsInfo.firstActivePortGroup

// /**
// * @struct PRV_CPSS_DRIVER_PP_CONFIG_STC
//  *
//  * @brief Includes all driver level configuration info, for HW access,
//  * interrupt handling.
// */
// typedef struct{

//     /** The PP's HW device number. */
//     GT_HW_DEV_NUM hwDevNum;

//     /** The PP's device type. */
//     CPSS_PP_DEVICE_TYPE devType;

//     /** number of ports in device */
//     GT_U32 numOfPorts;

//     /** @brief number of tiles.
//       * Falcon : 1/2/4
//       * Other devices : 0/1 (meaning no tile concept)
//     */
//     GT_U32                                     numOfTiles;

//     /** CPSS's device family that current device belongs to. */
//     CPSS_PP_FAMILY_TYPE_ENT devFamily;

//     /** CPSS's device sub */
//     CPSS_PP_SUB_FAMILY_TYPE_ENT devSubFamily;

//     /** @brief bmp of supported Management interface types.
//      *  this BMP allow to support "old" hw if with it's
//      *  newer protocol version, like in the case of "PCI"
//      *  and "PEX"(PCI Express)
//      */
//     GT_U32 drvHwIfSupportedBmp;

//     /** @brief the management interface SMI/PCI/TWSI/PEX
//      *  hwInfo[] - HW info (bus type, bus address, mappings, interrupts, etc)
//      *  hwCtrl[] - (Array of) A struct containing control fields for the hw access
//      *  functions.
//      *  index in the array is the 'port group'.
//      *  for 'non-multi-port-groups' device use index CPSS_NON_MULTI_PORT_GROUP_DEVICE_INDEX_CNS.
//      *  drivers[] - (Array of) Array of pointer to PP drivers
//      *  index in the array is the 'port group'.
//      *  for 'non-multi-port-groups' device use index CPSS_NON_MULTI_PORT_GROUP_DEVICE_INDEX_CNS.
//      */
//     CPSS_PP_INTERFACE_CHANNEL_ENT mngInterfaceType;

//     CPSS_HW_INFO_STC hwInfo[CPSS_MAX_PORT_GROUPS_CNS];

//     PRV_CPSS_DRV_STRUCT_PP_PORT_GROUP_HW_STC hwCtrl[CPSS_MAX_PORT_GROUPS_CNS];

//     CPSS_HW_DRIVER_STC* drivers[CPSS_MAX_PORT_GROUPS_CNS];

//     /** Interrupt control struct. */
//     PRV_CPSS_DRV_INT_CTRL_STC intCtrl;

//     /** @brief info about what Errata should be fixed in the CPSS driver for
//      *  the device (depend on : revision , devType)
//      */
//     PRV_CPSS_DRV_SHARED_ERRATA_STC errata;

//     /** @brief Info about the port groups of the device
//      *  NOTE: relevant also to the 'non multi port groups' devices
//      */
//     PRV_CPSS_DRV_PORT_GROUPS_INFO_STC portGroupsInfo;

//     PRV_SRVCPU_IPC_CHANNEL_STC* ipcDevCfg[SRVCPU_MAX_IPC_CHANNEL];

//     CPSS_HW_DRIVER_STC* chipletDrivers[16];/* up to 16 Ravens per device */

//     /** the bitmap of active Ravens in Falcon device: 0xF - default for 3.2T, 0xFF - default for 6.4T, 0xFFFF - default for 12.8 */
//     GT_U32  activeRavensBitmap;

//     /** the bitmap of Data Paths with enabled MACSec units */
//     GT_U32  enabledMacSecDpBitmap;

//     /** vendor ID register address */
//     GT_U32  vendorIdRegAddress;

// } PRV_CPSS_DRIVER_PP_CONFIG_STC;


/* flag allowing memory access trace */
extern GT_BOOL memoryAccessTraceOn;

/**
* @struct PRV_CPSS_HW_DRIVER_LIST_NODE_STC
 *
 * @brief Driver list node info for HW driver access.
*/
typedef struct PRV_CPSS_HW_DRIVER_LIST_NODE_STCT {
    /** the name of the HW driver */
    char               *name;
    /** pointer to HW driver object */
    CPSS_HW_DRIVER_STC *drv;
    /** pointer to alias */
    struct PRV_CPSS_HW_DRIVER_LIST_NODE_STCT *alias;
    /** pointer to next node */
    struct PRV_CPSS_HW_DRIVER_LIST_NODE_STCT *next;
    /** pointer to child nodes */
    struct PRV_CPSS_HW_DRIVER_LIST_NODE_STCT *childs;
} PRV_CPSS_HW_DRIVER_LIST_NODE_STC;



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __prvCpssDrvPpDefsh */



