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
* @file cpssTypes.h
* @version   107
********************************************************************************
*/

#ifndef __cpssTypesh
#define __cpssTypesh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************ Includes ********************************************************/
#include <h/ipc/gtGenTypes.h>

/*******************************************************************************
* cpssPortsBmpMemSet
*
* DESCRIPTION:
*       Stores value  converted to an unsigned char in each of the elements
*       of the array of unsigned char beginning at 'portsBmpPtr', with size  of CPSS_PORTS_BMP_STC.
*
* INPUTS:
*       portsBmpPtr  - start address of memory block for setting
*       clear - if equal GT_TRUE then character to store is 0,otherwise 0xFF is the character to store
*
* OUTPUTS:
*       None
*
* RETURNS:
*       Pointer to set memory block
*
* COMMENTS:
*       Should not be called from CPSS.The function is for application use only.
*
*******************************************************************************/
GT_VOID * cpssPortsBmpMemSet
(
    GT_VOID * portsBmpPtr,
    GT_BOOL   clear
);
/*******************************************************************************
* cpssPortsBmpIsZero
*
* DESCRIPTION:
*       Compare  size of CPSS_PORTS_BMP_STC  from the object pointed to by portsBmpPtr  to
*       the object that contain all 0
*
* INPUTS:
*       portsBmpPtr -  memory area to compare
*
* OUTPUTS:
*       None
*
* RETURNS:
*        0  -portsBmpPtr contain only 0
*       1 - otherwise
*
* COMMENTS:
*       Should not be called from CPSS.The function is for application use only.
*
******************************************************************************/
GT_U32  cpssPortsBmpIsZero
(
    GT_VOID * portsBmpPtr
);
/*******************************************************************************
* cpssPortsBmpCmp
*
* DESCRIPTION:
*       Compare  size of CPSS_PORTS_BMP_STC  from the object pointed to by portsBmp1Ptr  to
*       the object pointed to by portsBmp2Ptr
*
* INPUTS:
*       portsBmp1Ptr -  memory area to compare
*       portsBmp2Ptr -  memory area to compare
*
* OUTPUTS:
*       None
*
* RETURNS:
*       > 0  - if portsBmp1Ptr is alphabetic bigger than portsBmp2Ptr
*       == 0 - if portsBmp1Ptr is equal to portsBmp2Ptr
*       < 0  - if portsBmp1Ptr is alphabetic smaller than portsBmp2Ptr
*
* COMMENTS:
*       Should not be called from CPSS.The function is for application use only.
*
*******************************************************************************/
GT_32  cpssPortsBmpCmp
(
    GT_VOID * portsBmp1Ptr,
    GT_VOID * portsBmp2Ptr
);

/* macro to set TBD bookmarks */
#define CPSS_TBD_BOOKMARK

/* macro to set TBD eArch bookmarks */
#define CPSS_TBD_BOOKMARK_EARCH

/* macro to set TBD Lion2 bookmarks */
#define CPSS_TBD_BOOKMARK_LION2

/* macro to set TBD Puma3 bookmarks */
#define CPSS_TBD_BOOKMARK_PUMA3

/* macro to set TBD Bobcat2 bookmarks */
#define CPSS_TBD_BOOKMARK_BOBCAT2

/* macro to set TBD Bobcat2-bobk bookmarks */
#define CPSS_TBD_BOOKMARK_BOBCAT2_BOBK

/* macro to set TBD Bobcat3 bookmarks */
#define CPSS_TBD_BOOKMARK_BOBCAT3

/* macro to set TBD Xcat3 bookmarks */
#define CPSS_TBD_BOOKMARK_XCAT3

/* macro to set TBD Aldrin bookmarks */
#define CPSS_TBD_BOOKMARK_ALDRIN

/* macro to set TBD Aldrin2 bookmarks */
#define CPSS_TBD_BOOKMARK_ALDRIN2

/* macro to set TBD Falcon bookmarks */
#define CPSS_TBD_BOOKMARK_FALCON

/* macro to set TBD Falcon Emulator bookmarks */
#define CPSS_TBD_BOOKMARK_FALCON_EMULATOR

/* macro to set TBD AC5P bookmarks */
#define CPSS_TBD_BOOKMARK_AC5P

/* macro to set TBD AC5P Emulator bookmarks */
#define CPSS_TBD_BOOKMARK_AC5P_EMULATOR

/* macro to set TBD Phoenix bookmarks */
#define CPSS_TBD_BOOKMARK_PHOENIX

/* macro to set TBD Harrier bookmarks */
#define CPSS_TBD_BOOKMARK_HARRIER

/* macro to set TBD Ironman bookmarks */
#define CPSS_TBD_BOOKMARK_IRONMAN

/* macro to set TBD AAS bookmarks */
#define CPSS_TBD_BOOKMARK_AAS

/* macro to set TBD 88E1690 bookmarks */
#define CPSS_TBD_BOOKMARK_88E1690

/* macro to set TBD 'PX family PIPE device' bookmarks */
#define CPSS_TBD_BOOKMARK_PIPE

/* macro to set TBD AC5 bookmarks */
#define CPSS_TBD_BOOKMARK_AC5

/* macro to set TBD AC5 Emulator bookmarks */
#define CPSS_TBD_BOOKMARK_AC5_EMULATOR


/* CPSS API LOG related MACROs. */
/* _funcId - unique number for log creation */
/* _cpssApi - CPSS API name. */
/* _log_enter_args - _funcId & CPSS API arguments */
/* _rc - CPSS API return status */
#if defined(CPSS_LOG_ENABLE) && defined(CPSS_LOG_IN_MODULE_ENABLE)

/* macro for declaring on a function - for getting a unique identifier for it */
#define CPSS_LOG_FUNC_VARIABLE_DECLARE_MAC(_funcId, _func_name) \
    static const GT_U32 funcId = PRV_CPSS_LOG_FUNC_##_func_name##_E
/* macro for creating enter into function log if needed */
#define CPSS_LOG_API_ENTER_MAC(_params) \
    if (PRV_NON_SHARED_GLOBAL_VAR_LOG_GET() == GT_TRUE) prvCpssLogApiEnter _params
/* macro for creating exit from function log if needed */
#define CPSS_LOG_API_EXIT_MAC(_funcId, _rc) \
    if (PRV_NON_SHARED_GLOBAL_VAR_LOG_GET() == GT_TRUE) prvCpssLogApiExit(_funcId, _rc)
/* macro to log function error and exit from function - used in API error return statements */
#define CPSS_LOG_API_ERROR_EXIT_AND_RETURN_MAC(_funcId, _rc) \
    { \
        if (PRV_NON_SHARED_GLOBAL_VAR_LOG_GET() == GT_TRUE) { \
            prvCpssLogError(__FUNCTION__, __FILENAME__, __LINE__, _rc, LOG_ERROR_NO_MSG); \
            prvCpssLogApiExit(_funcId, _rc); \
        } \
        return _rc; \
    }

#else

#define CPSS_LOG_FUNC_VARIABLE_DECLARE_MAC(_funcId, _cpssApi)
#define CPSS_LOG_API_ENTER_MAC(_log_enter_args)
#define CPSS_LOG_API_EXIT_MAC(_funcId, _rc)
/* macro to log function error and exit from function - used in API error return statements */
#define CPSS_LOG_API_ERROR_EXIT_AND_RETURN_MAC(_funcId, _rc) return _rc
#endif

/* MACRO : to check if parameter is in valid range (0..(max-1))
    in case of 'not in range' :
        1. return GT_BAD_PARAM
        2. gives indication to 'ERROR LOG' with values in HEX format (0x%x)
    NOTE:
        1. the return of GT_BAD_PARAM suitable for 'key' parameters
        2. for 'data' parameters --> see macro CPSS_DATA_CHECK_MAX_MAC
*/
#define CPSS_PARAM_CHECK_MAX_MAC(param,max)  \
    if((GT_U32)(param) >= (GT_U32)(max))       \
    {                                        \
        CPSS_LOG_ERROR_AND_RETURN_MAC(GT_BAD_PARAM, " [%s] must be in [0..0x%x] but got[0x%x]", \
            #param,                          \
            (GT_U32)((max)-1),               \
            (GT_U32)(param));                \
    }

/* MACRO : to check if data is in valid range (0..(max-1))
    in case of 'not in range' :
        1. return GT_OUT_OF_RANGE
        2. gives indication to 'ERROR LOG' with values in HEX format (0x%x)
    NOTE:
        1. the return of GT_OUT_OF_RANGE suitable for 'data' parameters
        2. for 'key' parameters --> see macro CPSS_PARAM_CHECK_MAX_MAC
*/
#define CPSS_DATA_CHECK_MAX_MAC(param,max)  \
    if((GT_U32)(param) >= (GT_U32)(max))       \
    {                                        \
        CPSS_LOG_ERROR_AND_RETURN_MAC(GT_OUT_OF_RANGE, " [%s] must be in [0..0x%x] but got[0x%x]", \
            #param,                          \
            (GT_U32)((max)-1),               \
            (GT_U32)(param));                \
    }

/* constant to represent application that not care about specific 'data path' in
    'multi-data-paths' device.

    for non 'multi-data-paths' device - parameter will be ignored anyway.
    for 'multi-data-paths' device - parameter state that action apply
    to all data-paths.

    see also GT_DATA_PATH_BMP
*/
#define CPSS_DATA_PATH_UNAWARE_MODE_CNS 0xFFFFFFFF

/* macro for wrapping dedicated callback. */
/* _callback_args - _funcId (see LOG related MACROs above), CPSS API return status & arguments */
#define CPSS_APP_SPECIFIC_CB_MAC(_callback_args);

/* constant to state that the parameter with this value need to be ignored
    This meaning is given only for fields that explicitly stated to support it */
#define CPSS_PARAM_NOT_USED_CNS 0xFFFFFFFF

/* constant to represent application that not care about specific 'portGroup' in
   'multi-port-groups' device .

   for non 'multi-port-groups' device - parameter will be ignored anyway.
   for 'multi-port-groups' device - parameter state that action apply
   to all active port groups.

   see also GT_PORT_GROUPS_BMP
*/
#define CPSS_PORT_GROUP_UNAWARE_MODE_CNS 0xFFFFFFFF

/* number of max supported port groups in 'multi-port-groups' device */
#define CPSS_MAX_PORT_GROUPS_CNS  8

/* index in array of 'port-groups' for a non 'multi-port-groups' device */
#define CPSS_NON_MULTI_PORT_GROUP_DEVICE_INDEX_CNS        0

/* CPU PORT NUMBER Definition */
#define CPSS_CPU_PORT_NUM_CNS           63

/* maximal number of SDMA CPU ports*/
#define CPSS_MAX_SDMA_CPU_PORTS_CNS      16

/* BC3,Aldrin2 : 4 SDMA CPU ports */
#define CPSS_4_SDMA_CPU_PORTS_CNS      4

/* max ports in device in PPs of Prestera family
   see also PRV_CPSS_MAX_PP_PORTS_NUM_CNS.
   CPSS_MAX_PORTS_NUM_CNS may be defined in .config
        Supported values:
   xCat3, AC5, Falcon, AC5P, AC5X, Harrier, IronMan, AAS - support 128, 256, 512, 1024
   Lion2, Bobcat2, Caelum, Aldrin, AC3X, Bobcat3, Aldrin2 - support 256, 512, 1024
        Falcon, AAS an Bobcat3 use maxNumOfPhyPortsToUse parameter in cpssDxChHwPpPhase1Init.
   Value of CPSS_MAX_PORTS_NUM_CNS must be greater than or equal to maxNumOfPhyPortsToUse for
   these devices.
   */
#ifndef CPSS_MAX_PORTS_NUM_CNS
#define CPSS_MAX_PORTS_NUM_CNS          1024
#endif /* CPSS_MAX_PORTS_NUM_CNS */

/* max ports in device in legacy PPs of Prestera family:
   xCat3, AC5, Lion2. Lion2's capability defines this constant. */
#define CPSS_MAX_SIP_4_PORTS_NUM_CNS    128

/* max ports in device in SIP_5_nn generations of Prestera family:
   Bobcat2, Caelum/Cetus, Aldrin/AC3X, Bobcat3, Aldrin2 .
   Bobcat3 capability defines this constant. */
#define CPSS_MAX_SIP_5_PORTS_NUM_CNS    512


#define CPSS_MAX_PORTS_BMP_NUM_CNS   ((CPSS_MAX_PORTS_NUM_CNS + 31) / 32)

/* NULL Port */
#define CPSS_NULL_PORT_NUM_CNS          62

/* NULL Port for ExMx and ExMxTg devices */
#define CPSS_EXMX_NULL_PORT_NUM_CNS     61

#define CPSS_MAX_SDMA_PORT_NUM_CNS     16


/**
* @enum CPSS_UNICAST_MULTICAST_ENT
 *
 * @brief Unicast / Multicast selection
*/
typedef enum{

    /** Unicast packet */
    CPSS_UNICAST_E            = 0,

    /** Multicast packet */
    CPSS_MULTICAST_E          = 1,

    /** Unicast or Multicast */
    CPSS_UNICAST_MULTICAST_E  = 2

} CPSS_UNICAST_MULTICAST_ENT;

/**
* @enum CPSS_IP_PROTOCOL_STACK_ENT
 *
 * @brief type of IP stack used
*/
typedef enum{

    /** IPv4 stack */
    CPSS_IP_PROTOCOL_IPV4_E     = 0,

    /** IPv6 stack */
    CPSS_IP_PROTOCOL_IPV6_E     = 1,

    /** IPv4/IPv6 stack */
    CPSS_IP_PROTOCOL_IPV4V6_E   = 2,

    /** FCOE stack */
    CPSS_IP_PROTOCOL_FCOE_E     = 3,

    /** IPv4/IPv6/FCOE stack */
    CPSS_IP_PROTOCOL_ALL_E      = 4

} CPSS_IP_PROTOCOL_STACK_ENT;

/**
* @enum CPSS_ADJUST_OPERATION_ENT
 *
 * @brief adjust operation.
*/
typedef enum{

    /** add */
    CPSS_ADJUST_OPERATION_ADD_E,

    /** subtract */
    CPSS_ADJUST_OPERATION_SUBSTRUCT_E

} CPSS_ADJUST_OPERATION_ENT;

/**
* @enum CPSS_SHIFT_OPERATION_ENT
 *
 * @brief shift operation.
*/
typedef enum{

    /** shift left */
    CPSS_SHIFT_OPERATION_SHIFT_LEFT_E,

    /** shift right */
    CPSS_SHIFT_OPERATION_SHIFT_RIGHT_E

} CPSS_SHIFT_OPERATION_ENT;

/**
* @enum CPSS_INTERFACE_TYPE_ENT
 *
 * @brief enumerator for interface
 * To be used for:
 * 1. set mac entry info
 * 2. set next hop info
 * 3. redirect pcl info
 * 4. get new Address info
*/
typedef enum{

    /** the interface is of port type (dev,port) */
    CPSS_INTERFACE_PORT_E = 0,

    /** the interface is of trunk type (trunkId) */
    CPSS_INTERFACE_TRUNK_E,

    /** the interface is of Vidx type (vidx) */
    CPSS_INTERFACE_VIDX_E,

    /** the interface is of Vid type (vlan-id) */
    CPSS_INTERFACE_VID_E,

    /** the interface is device */
    CPSS_INTERFACE_DEVICE_E,

    /** the interface is of Vidx type (fabricVidx) */
    CPSS_INTERFACE_FABRIC_VIDX_E,

    /** the interface index type */
    CPSS_INTERFACE_INDEX_E

} CPSS_INTERFACE_TYPE_ENT;

/**
* @enum CPSS_DIRECTION_ENT
 *
 * @brief This enum defines direction: ingress or egress
*/
typedef enum{

    /** the direction is ingress */
    CPSS_DIRECTION_INGRESS_E,

    /** the direction is egress */
    CPSS_DIRECTION_EGRESS_E,

    /** egress and ingress direction */
    CPSS_DIRECTION_BOTH_E

} CPSS_DIRECTION_ENT;

/*
 * Typedef: GT_SW_DEV_NUM
 *
 * Description: Defines software devNum
 *
 *  the SW devNum is used as 'first parameter' in most of the CPSS APIs,
 *  and identify the managed device.
 *
 */
typedef GT_U32 GT_SW_DEV_NUM;
#define CAST_SW_DEVNUM(devNum)    ((GT_U8)devNum)

/*
 * Typedef: GT_TRUNK_ID
 *
 * Description: Defines trunk id
 *
 *  used as the type for the trunk Id's
 *
 */
typedef GT_U16  GT_TRUNK_ID;


/*
 * Typedef: GT_HW_DEV_NUM
 *
 * Description: Defines HW dev num
 *
 *  used as the type for the hw dev num
 *
 */
typedef GT_U32 GT_HW_DEV_NUM;


/*
 * Typedef: GT_PORT_NUM
 *
 * Description: Defines port num
 *
 *  used as the type for the port num
 *
 */
typedef GT_U32 GT_PORT_NUM;

/*
 * Typedef: U32 GT_PHYSICAL_PORT_NUM
 *
 * Description: Defines physical port num
 *
 *  used as the type for the physical port num
 *
 */
typedef GT_U32 GT_PHYSICAL_PORT_NUM;

/**
* @struct CPSS_TRUNK_MEMBER_STC
 *
 * @brief A structure to hold the info on trunk member : device,port
 * the trunk holds only 'physical' ports
*/
typedef struct{

    /** the physical port number */
    GT_PHYSICAL_PORT_NUM port;

    /** the HW device number */
    GT_HW_DEV_NUM hwDevice;

} CPSS_TRUNK_MEMBER_STC;

/**
* @struct CPSS_HW_ADDR_STC
 *
 * @brief Hardware (bus) address of PP
 * Used for CPSS_CHANNEL_PEX_KERNEL_E driver ONLY
*/
typedef struct{

    /** PCI/PEX busNo */
    GT_U32 busNo;

    /** PCI/PEX deviceNo */
    GT_U32 devSel;

    /** @brief PCI/PEX func
     *  Comments:
     */
    GT_U32 funcNo;

} CPSS_HW_ADDR_STC;

/**
* @struct CPSS_INTERFACE_DEV_PORT_STC
 *
 * @brief Defines the {hwDevNum,portNum} interface
 *
*/
typedef struct{
    /** @brief - the HW device number */
    GT_HW_DEV_NUM   hwDevNum;
    /** @brief - port number (physical port / eport) */
    GT_PORT_NUM     portNum;
}CPSS_INTERFACE_DEV_PORT_STC;


/**
* @struct CPSS_INTERFACE_INFO_STC
 *
 * @brief Defines the interface info
 * To be used for:
 * 1. set mac entry info
 * 2. set next hop info
 * 3. redirect pcl info
 * 4. get new Address info
*/
typedef struct{
    /** the interface type */
    CPSS_INTERFACE_TYPE_ENT     type;

    /* !!!! NOTE : next fields treated as UNION !!!! */

    /** info about the {dev,port} - relevant to CPSS_INTERFACE_PORT_E */
    struct{
        /** @brief - the HW device number
         *
         *  NOTE: in 'vPort mode' when the <devPort.portNum> is in the vPorts range ,
         *          the <devPort.hwDevNum> is ignored in most places
         *          so 'Get' API will return devPort.hwDevNum = CPSS_PARAM_NOT_USED_CNS
         *          except for FDB MAC entry APIs (MAC,IPv4MC,IPv6MC entry types)
         *          that supports the <devPort.hwDevNum> also for 'vPort mode' in the vPorts range
         *
        */
        GT_HW_DEV_NUM   hwDevNum;
        /** @brief - port number (physical port / eport) */
        GT_PORT_NUM     portNum;
    }devPort;

    /** @brief - info about the {trunkId}  - relevant to CPSS_INTERFACE_TRUNK_E
     *  NOTE: in FDB entry the <hwDevNum> used in addition to <trunkId>
    */
    GT_TRUNK_ID     trunkId;

    /** info about the {vidx}     - relevant to CPSS_INTERFACE_VIDX_E */
    GT_U32          vidx;

    /** info about the {vid}      - relevant to CPSS_INTERFACE_VID_E */
    GT_U16          vlanId;

    /** info about the {HW device number} - relevant to CPSS_INTERFACE_DEVICE_E
     *  NOTE: in FDB entry the <hwDevNum> used also when type is CPSS_INTERFACE_TRUNK_E
     */
    GT_HW_DEV_NUM   hwDevNum;

    /** info about the {fabricVidx} - relevant to CPSS_INTERFACE_FABRIC_VIDX_E */
    GT_U16          fabricVidx;

    /** info about the {index}  - relevant to CPSS_INTERFACE_INDEX_E */
    GT_U32          index;

}CPSS_INTERFACE_INFO_STC;

/* macro CPSS_PORTS_BMP_PORT_SET_MAC
    to set a port in the bmp of ports

  portsBmpPtr - of type CPSS_PORTS_BMP_STC*
                pointer to the ports bmp
  portNum - the port num to set in the ports bmp
*/
#define CPSS_PORTS_BMP_PORT_SET_MAC(portsBmpPtr,portNum)   \
    if(((portNum) >> 5) < CPSS_MAX_PORTS_BMP_NUM_CNS)      \
        (portsBmpPtr)->ports[(portNum)>>5] |= 1 << ((portNum)& 0x1f)

/* macro CPSS_PORTS_BMP_PORT_CLEAR_MAC
    to clear a port from the bmp of ports

  portsBmpPtr - of type CPSS_PORTS_BMP_STC*
                pointer to the ports bmp
  portNum - the port num to clear from the ports bmp
*/
#define CPSS_PORTS_BMP_PORT_CLEAR_MAC(portsBmpPtr,portNum)   \
    if(((portNum) >> 5) < CPSS_MAX_PORTS_BMP_NUM_CNS)        \
        (portsBmpPtr)->ports[(portNum)>>5] &= ~(1 << ((portNum)& 0x1f))

/* macro CPSS_PORTS_BMP_IS_PORT_SET_MAC
    to check if port is set the bmp of ports (is corresponding bit is 1)

  portsBmpPtr - of type CPSS_PORTS_BMP_STC*
                pointer to the ports bmp
  portNum - the port num to set in the ports bmp

  return 0 -- port not set in bmp
  return 1 -- port set in bmp
*/
#define CPSS_PORTS_BMP_IS_PORT_SET_MAC(portsBmpPtr,portNum)   \
    ((((portNum) >> 5) >= CPSS_MAX_PORTS_BMP_NUM_CNS) ? 0 :   \
    (((portsBmpPtr)->ports[(portNum)>>5] & (1 << ((portNum)& 0x1f)))? 1 : 0))

/* portsBmpTargetPtr = portsBmpSrc1Ptr | portsBmpSrc2Ptr */
#define CPSS_PORTS_BMP_BITWISE_OR_MAC(portsBmpTargetPtr,portsBmpSrc1Ptr,portsBmpSrc2Ptr) \
    {                                                                                    \
        GT_U32  __ii;                                                                    \
        for(__ii = 0 ; __ii < CPSS_MAX_PORTS_BMP_NUM_CNS; __ii++)                        \
            (portsBmpTargetPtr)->ports[__ii] = (portsBmpSrc1Ptr)->ports[__ii] | (portsBmpSrc2Ptr)->ports[__ii];\
    }

/* portsBmpTargetPtr = portsBmpSrc1Ptr & portsBmpSrc2Ptr */
#define CPSS_PORTS_BMP_BITWISE_AND_MAC(portsBmpTargetPtr,portsBmpSrc1Ptr,portsBmpSrc2Ptr) \
    {                                                                                    \
        GT_U32  __ii;                                                                    \
        for(__ii = 0 ; __ii < CPSS_MAX_PORTS_BMP_NUM_CNS; __ii++)                        \
            (portsBmpTargetPtr)->ports[__ii] = (portsBmpSrc1Ptr)->ports[__ii] & (portsBmpSrc2Ptr)->ports[__ii];\
    }

/* portsBmpTargetPtr = portsBmpSrc1Ptr & ~portsBmpSrc2Ptr */
#define CPSS_PORTS_BMP_BITWISE_AND_NOT_MAC(portsBmpTargetPtr,portsBmpSrc1Ptr,portsBmpSrc2Ptr) \
    {                                                                                    \
        GT_U32  __ii;                                                                    \
        for(__ii = 0 ; __ii < CPSS_MAX_PORTS_BMP_NUM_CNS; __ii++)                        \
            (portsBmpTargetPtr)->ports[__ii] = (portsBmpSrc1Ptr)->ports[__ii] & (~(portsBmpSrc2Ptr)->ports[__ii]);\
    }

/* portsBmpTargetPtr = ~ portsBmpSrcPtr */
#define CPSS_PORTS_BMP_BITWISE_NOT_MAC(portsBmpTargetPtr,portsBmpSrcPtr)        \
    {                                                                           \
        GT_U32  __ii;                                                           \
        for(__ii = 0 ; __ii < CPSS_MAX_PORTS_BMP_NUM_CNS; __ii++)               \
            (portsBmpTargetPtr)->ports[__ii] = (~(portsBmpSrcPtr)->ports[__ii]);\
    }
/*NOTE: CPSS_PORTS_BMP_IS_ZERO_MAC and CPSS_PORTS_BMP_PORT_CLEAR_ALL_MAC  \
        should be NOT used from cpss. This is for application use only*/


/* all ii 0.. max --> portsBmpTargetPtr[ii] == 0 */
#define CPSS_PORTS_BMP_IS_ZERO_MAC(portsBmpPtr)     \
    cpssPortsBmpIsZero(portsBmpPtr)

/* set for all ii 0.. max --> portsBmpTargetPtr[ii] = 0 */
#define CPSS_PORTS_BMP_PORT_CLEAR_ALL_MAC(portsBmpPtr)     \
    cpssPortsBmpMemSet(portsBmpPtr,GT_TRUE)

/* macro CPSS_PORTS_BMP_PORT_ENABLE_MAC
    to set or clear a port from the bmp of ports

  portsBmpPtr - of type CPSS_PORTS_BMP_STC*
                pointer to the ports bmp
  portNum - the port num to set the value from the ports bmp
  enable - of type GT_BOOL - GT_TRUE: set GT_FALSE: clear
*/
#define CPSS_PORTS_BMP_PORT_ENABLE_MAC(portsBmpPtr,portNum, enable)   \
    if ((enable) != GT_FALSE)                                         \
    {                                                                 \
        CPSS_PORTS_BMP_PORT_SET_MAC((portsBmpPtr),(portNum));      \
    }                                                                 \
    else                                                              \
    {                                                                 \
        CPSS_PORTS_BMP_PORT_CLEAR_MAC((portsBmpPtr),(portNum));       \
    }

/* macro CPSS_PORTS_BMP_PORT_SET_ALL_MAC
    set all ports in portsBmpPtr

  portsBmpPtr - of type CPSS_PORTS_BMP_STC*
                pointer to the ports bmp
*/

/*NOTE: CPSS_PORTS_BMP_PORT_SET_ALL_MAC and CPSS_PORTS_BMP_ARE_EQUAL_MAC  \
        should be NOT used from cpss. This is for application use only*/

#define CPSS_PORTS_BMP_PORT_SET_ALL_MAC(portsBmpPtr) \
    (cpssPortsBmpMemSet(portsBmpPtr,0xFF))

/* check if ports bmp in portsBmpPtr1 == portsBmpPtr2
    return 1 - equal
    return 0 - NOT equal
*/
#define CPSS_PORTS_BMP_ARE_EQUAL_MAC(portsBmpPtr1,portsBmpPtr2)     \
    (cpssPortsBmpCmp(portsBmpPtr1,portsBmpPtr2))


/**
* @struct CPSS_PORTS_BMP_STC
 *
 * @brief Defines the bmp of ports (up to 1024 ports)
*/
typedef struct{

    GT_U32 ports[CPSS_MAX_PORTS_BMP_NUM_CNS];

} CPSS_PORTS_BMP_STC;

/*
 * Typedef: CPSS_PORTS_SHORT_BMP_STC
 *
 * Description: Defines a bmp of 32 consecutive ports for a device.
 *  usually the ports are 0..31 , but may be specified otherwise by the API.
 *
 *  32 ports represent bits 0..31
 *
 */
typedef GT_U32 CPSS_PORTS_SHORT_BMP_STC;

/*
 * Typedef: CPSS_PX_PORTS_BMP
 *
 * Description: Defines the bmp of ports for PX devices
 *
 *  17 ports represent bits 0..16 (bit 16 is CPU port)
 *
 */
typedef GT_U32 CPSS_PX_PORTS_BMP;


/* support running from the PSS */
#ifndef __gtTypesh

/**
* @union GT_IPADDR
 *
 * @brief Defines the IP address
 *
*/

typedef union{
    /** the IP as single WORD */
    GT_U32 u32Ip;

    GT_U8 arIP[4];

} GT_IPADDR;


/**
* @union GT_IPV6ADDR
 *
 * @brief Defines the IPv6 address
 *
*/

typedef union{
    GT_U32 u32Ip[4];

    GT_U8 arIP[16];

} GT_IPV6ADDR;



/**
* @union GT_IP_ADDR_TYPE_UNT
 *
 * @brief Defines the type of IP address
 *
*/

typedef union{
    /** the IP addr is IPv6 type */
    GT_IPV6ADDR ipv6Addr;

    /** the IP as IPv4 type */
    GT_IPADDR ipv4Addr;

} GT_IP_ADDR_TYPE_UNT;


/**
* @struct GT_ETHERADDR
 *
 * @brief Defines the mac address
*/
typedef struct{

    GT_U8 arEther[6];

} GT_ETHERADDR;

/**
* @struct GT_FCID
 *
 * @brief Defines FC_ID
*/
typedef struct{

    GT_U8 fcid[3];

} GT_FCID;

#define GT_HW_MAC_LOW32(macAddr)                \
                ((macAddr)->arEther[5] |          \
                ((macAddr)->arEther[4] << 8) |    \
                ((macAddr)->arEther[3] << 16) |   \
                ((macAddr)->arEther[2] << 24))

#define GT_HW_MAC_HIGH16(macAddr)           \
        ((macAddr)->arEther[1] | ((macAddr)->arEther[0] << 8))

#define GT_HW_MAC_LOW16(macAddr)            \
        ((macAddr)->arEther[5] | ((macAddr)->arEther[4] << 8))

#define GT_HW_MAC_HIGH32(macAddr)               \
                ((macAddr)->arEther[3] |          \
                ((macAddr)->arEther[2] << 8) |    \
                ((macAddr)->arEther[1] << 16) |   \
                ((macAddr)->arEther[0] << 24))

/* Constant of prefix for the 'Mac Index' format */
#define MAC_INDEX_PREFIX     0xFFFFFFFF

/* This is a service MACRO for the 'Mac Index' format,
   add to the 2 mac index bytes the 4 MAC_INDEX_PREFIX bytes. */
#define GT_ADD_MAC_INDEX_PREFIX(macIndex,macAddrIndex)                   \
                (macAddrIndex)->arEther[5] =  macIndex;                  \
                (macAddrIndex)->arEther[4] = (macIndex >> 8);            \
                (macAddrIndex)->arEther[3] =  MAC_INDEX_PREFIX;          \
                (macAddrIndex)->arEther[2] = (MAC_INDEX_PREFIX >> 8);    \
                (macAddrIndex)->arEther[1] = (MAC_INDEX_PREFIX >> 16);   \
                (macAddrIndex)->arEther[0] = (MAC_INDEX_PREFIX >> 24);

/**
* @struct CPSS_802_1Q_VLAN_TAG_STC
 *
 * @brief This struct defines the format of 4 bytes 802.1q vlan tag.
*/
typedef struct{

    /** TPID (etherType) 16 bits field. */
    GT_U32 TPID;

    /** @brief Priority code point (PCP): the IEEE 802.1p class of service.
     *  3 bits field.
     */
    GT_U32 PCP;

    /** Drop eligible indicator . single bit field. */
    GT_U32 DEI;

    /** @brief VLAN identifier ,specifying the VLAN to which the frame belongs.
     *  12 bits field.
     */
    GT_U32 VID;

} CPSS_802_1Q_VLAN_TAG_STC;

/**
* @struct CPSS_802_1BR_ETAG_STC
 *
 * @brief This struct defines the format of 8 bytes 802.1BR BPE ETAG used between
 * Control bridge and Port Extender.
*/
typedef struct{

    /** TPID (etherType) 16 bits field. */
    GT_U32 TPID;

    /** @brief Priority code point (PCP): the IEEE 802.1p class of service.
     *  3 bits field.
     */
    GT_U32 E_PCP;

    /** @brief this field for Drop eligible indicator
     *  single bit field
     */
    GT_U32 E_DEI;
    /** @brief this field used for Source filtering for
     *  multi-destination traffic performed only on the PE Extender
     *  Ports.
     *  12 bits field.
     */
    GT_U32 Ingress_E_CID_base;

    /** @brief direction
     *  the values for the Direction field are:
     *  0 = Upstream
     *  1 = Downstream
     */
    GT_U32 Direction;

    /** @brief indicate if the packet is data traffic or layer 2 Control packet
     *  The values for the Upstream-Specific field are:
     *  0 = Traffic is load-balanced across Upstream ports (default value).
     *  1 = Traffic is sent to an Upstream port that is specified by the E-Tag ECID (set to 1 by the CPU).
     */
    GT_U32 Upstream_Specific;

    /** @brief indication of groups ranges. 2 bits field.
     *  value 1..3 means MC ranges. value 0 means UC range.
     */
    GT_U32 GRP;

    /** @brief the source ECID on upstream , and the target ECID on UC downstream.
     *  on MC together with GRP hold 14 bits 'MC group'
     *  12 bits field.
     */
    GT_U32 E_CID_base;

    /** extension to Ingress_E_CID_base. 8 bits field. */
    GT_U32 Ingress_E_CID_ext;

    /** extension to E_CID_base. 8 bits field. */
    GT_U32 E_CID_ext;

} CPSS_802_1BR_ETAG_STC;



/*
 * Typedef: GT_PORT_GROUPS_BMP
 *
 * Description: Defines bitmap of up to 32 port groups
 *
 *  used as the type for the 'port groups bitmap'
 *  this relevant only to multi-port groups devices
 *
 *  APPLICABLE DEVICES: Lion2; Bobcat3; Falcon.
 *
 *  NOTE: each CPSS/cpssDriver API that supports the GT_PORT_GROUPS_BMP may
 *        hold specific limitations/conditions on the relevant values for it.
 *        and specific 'APPLICABLE DEVICES:'
 *     For example:
 *      Since Bobcat3 device hold single FDB unit although supports 2 port groups ,
 *      The API parameter 'portGroupsBmp' of cpssDxChBrgFdbPortGroupMacEntrySet(...)
 *      will NOT state Bobcat3 as 'APPLICABLE DEVICES:'
 *
 *******************************
 *
 *  Lion2   : support of 'port groups bmp' of 8 'groups' , 0..7 (or subset)
 *            port group 0 : MAC ports 0..11    (12 ports)
 *            port group 1 : MAC ports 16..27   (12 ports)
 *            port group 2 : MAC ports 32..43   (12 ports)
 *            port group 3 : MAC ports 48..59   (12 ports)
 *            port group 4 : MAC ports 64..75   (12 ports)
 *            port group 5 : MAC ports 80..91   (12 ports)
 *            port group 6 : MAC ports 96..107  (12 ports)
 *            port group 7 : MAC ports 112..123 (12 ports)
 *      (Hooper: 4 first port groups 0..3)
 *
 *  Bobcat3 : support of 'port groups bmp' of 2 'groups' , 0..1
 *            port group 0 : MAC ports  0..35,72   (37 ports) , CPU DMAs 74,75 (2 CPU DMAs)
 *            port group 1 : MAC ports 36..71,73   (37 ports) , CPU DMAs 76,77 (2 CPU DMAs)
 *
 *  Falcon  : 12.8T : support of 'port groups bmp' of 8 'groups' , 0..7
 *             6.4T : support of 'port groups bmp' of 4 'groups' , 0..3
 *           each group supports 32 MAC ports.
 *  AAS     : 12.8T : support of 'port groups bmp' of 2 'groups' : 0..1
 *             6.4T : support of 'port groups bmp' of single 'group' : 0
 *           each group supports up to 140 MAC ports.
 */
typedef GT_U32  GT_PORT_GROUPS_BMP;

/*
 * Typedef: GT_CHIPLETS_BMP
 *
 * Description: Defines bitmap to represent set of Chiplets
 *
 *  APPLICABLE DEVICES: Falcon.
 *
 *******************************
 *
 *  Falcon: 128 MAC ports or 265 MAC ports
 *  MAC ports   0.. 15   CHIPLET  0
 *  MAC ports  15.. 31   CHIPLET  1
 *  MAC ports  32.. 47   CHIPLET  2
 *  MAC ports  48.. 63   CHIPLET  3
 *  MAC ports  64.. 79   CHIPLET  7
 *  MAC ports  80.. 95   CHIPLET  6
 *  MAC ports  96..111   CHIPLET  5
 *  MAC ports 112..127   CHIPLET  4
 *  MAC ports 128..143   CHIPLET  8
 *  MAC ports 144..159   CHIPLET  9
 *  MAC ports 160..175   CHIPLET 10
 *  MAC ports 176..191   CHIPLET 11
 *  MAC ports 192..207   CHIPLET 15
 *  MAC ports 208..223   CHIPLET 14
 *  MAC ports 224..239   CHIPLET 13
 *  MAC ports 240..255   CHIPLET 12
 *
 */
typedef GT_U32 GT_CHIPLETS_BMP;

/*
 * Typedef: GT_TAI_SELECT_BMP
 *
 * Description: Defines bitmap to represent set of TAI selection.
 *
 *  APPLICABLE DEVICES: Ironman.
 *
 *******************************
 *
 *  Ironman: TAI selection bitmap 0..0x1F
 *
 */
typedef GT_U32 GT_TAI_SELECT_BMP;

/*
 * Typedef: GT_CNC_UNIT_BMP
 *
 * Description: Defines bitmap to represent set of CNC units selection.
 *
 *  APPLICABLE DEVICES: AAS.
 *
 *******************************
 *
 *  AAS: 6.4T  : bits 0..3
 *       12.8T : bits 0..3 (tile 0) , 4..7 (tile 1)
 *
 */
typedef GT_U32 GT_CNC_UNITS_BMP;


/* value to configure all CHIPLETS of the device */
#define CPSS_CHIPLETS_UNAWARE_MODE_CNS 0xFFFFFFFF

/* Define maximal number of chiplets */
#define CPSS_CHIPLETS_MAX_NUM_CNS       16

/* Define maximal number of LED units in chain */
#define CPSS_LED_UNITS_MAX_NUM_CNS      16

/*
 * Typedef: GT_DATA_PATH_BMP
 *
 * Description: Defines bitmap of up to 32 Data Paths
 *
 *  APPLICABLE DEVICES: Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman.
 *
 *******************************
 *
 *  Caelum  : support two Data Paths 0 and 1.
 *            Data Path 0 : MAC ports  0..47
 *            Data Path 1 : MAC ports 56..59, 62, 64..71, CPU SDMA Port
 *
 *  Aldrin  : support three Data Paths 0..2.
 *            Data Path 0 : MAC ports  0..11
 *            Data Path 1 : MAC ports 12..23
 *            Data Path 2 : MAC ports 24..32, CPU SDMA Port
 *
 *  Bobcat3 : support six Data Paths 0..5.
 *            Data Path 0 : MAC ports  0..11, CPU SDMA Port (74)
 *            Data Path 1 : MAC ports 12..23, CPU SDMA Port (75)
 *            Data Path 2 : MAC ports 24..35, 72
 *            Data Path 3 : MAC ports 36..47, CPU SDMA Port (76)
 *            Data Path 4 : MAC ports 48..59, CPU SDMA Port (77)
 *            Data Path 5 : MAC ports 60..71, 73
 *
 *  Aldrin2 : support four Data Paths 0..3.
 *            Data Path 0 : MAC ports  0..11, 72, CPU SDMA Port (77)
 *            Data Path 1 : MAC ports 12..23, CPU SDMA Port (75)
 *            Data Path 2 : MAC ports 24..47, CPU SDMA Port (76)
 *            Data Path 3 : MAC ports 48..71, CPU SDMA Port (74)
 *
 *  Falcon : support    a.16  Data Paths 0..15 for Falcon 6.4T.
 *                      b.32  Data Paths 0..31 for Falcon 12.8T.
 *
 *                                          6.4T
 *                                    ==========
 *           Data Path   X : MAC ports            X*8..X*8+7
 *                           CPU network ports    DP 6   MAC 128 (muxed with DMA 132)
 *                                                DP 8   MAC 129 (muxed with DMA 134)
 *                           CPU SDMA ports       DP 4..11   DMA 130..137
 *                                      12.8T
 *                                   ==========
 *           Data Path    X : MAC ports           X*8..X*8+7
 *                           CPU network ports    DP 2   MAC 256
 *                                                DP 4   MAC 257 (muxed with DMA 258)
 *                           CPU SDMA ports       DP 4..11   DMA 258..265
 *                                                DP 20..27  DMA 266..273
 *
 *  AC5P  : support 4 Data Paths 0..3.
 *            Data Path 0 : MAC ports  0..25  , 105-CPU SDMA port
 *            Data Path 1 : MAC ports  26..51 , 104-CPU network port , 106-CPU SDMA port (104,106 are muxed)
 *            Data Path 2 : MAC ports  52..77 , 107-CPU SDMA port
 *            Data Path 3 : MAC ports  78..103, 108-CPU SDMA port
 *
 *  AC5X : single Data Path (so the bmp is ignored !)
 *
 *  Harrier  : support 3 Data Paths 0..2.
 *            Data Path 0 : MAC ports   0, 2, 4, 6, 8,10,12,14 , 40-CPU SDMA port
 *            Data Path 1 : MAC ports  16,18,20,22,24,26,28,30 , 41-CPU SDMA port
 *            Data Path 2 : MAC ports  32,34,36,38
 *            NOTE: odd numbers 1,3,5..39 are the 'preemption DP ports' of the even ports 0,2,4...38
 *
 *  Ironman : single Data Path (so the bmp is ignored !)
 *
 */
typedef GT_U32 GT_DATA_PATH_BMP;

/* support running from the PSS */
#endif /*__gtTypesh*/

/**
* @enum CPSS_PP_FAMILY_TYPE_ENT
 *
 * @brief Defines the different device families that may exist in system.
*/
typedef enum
{

/*start*/  CPSS_PP_FAMILY_START_EXMX_E,

                CPSS_PP_FAMILY_TWISTC_E,
                CPSS_PP_FAMILY_TWISTD_E,
                CPSS_PP_FAMILY_SAMBA_E,
                CPSS_PP_FAMILY_TIGER_E,

/*end*/    CPSS_PP_FAMILY_END_EXMX_E,

/*start*/  CPSS_PP_FAMILY_START_DXSAL_E,

                CPSS_PP_FAMILY_SALSA_E,

/*end*/    CPSS_PP_FAMILY_END_DXSAL_E,

/*start*/  CPSS_PP_FAMILY_START_DXCH_E,

                CPSS_PP_FAMILY_CHEETAH_E,
                CPSS_PP_FAMILY_CHEETAH2_E,
                CPSS_PP_FAMILY_CHEETAH3_E,
                CPSS_PP_FAMILY_DXCH_XCAT_E,
                CPSS_PP_FAMILY_DXCH_XCAT3_E,
                CPSS_PP_FAMILY_DXCH_AC5_E,
                CPSS_PP_FAMILY_DXCH_LION_E,
                CPSS_PP_FAMILY_DXCH_XCAT2_E,
                CPSS_PP_FAMILY_DXCH_LION2_E,
                CPSS_PP_FAMILY_DXCH_LION3_E,
                CPSS_PP_FAMILY_DXCH_BOBCAT2_E,
                CPSS_PP_FAMILY_DXCH_BOBCAT3_E,
                CPSS_PP_FAMILY_DXCH_ALDRIN_E,
                CPSS_PP_FAMILY_DXCH_AC3X_E,
                CPSS_PP_FAMILY_DXCH_ALDRIN2_E,
                CPSS_PP_FAMILY_DXCH_FALCON_E,
                CPSS_PP_FAMILY_DXCH_AC5P_E,
                CPSS_PP_FAMILY_DXCH_AC5X_E,
                CPSS_PP_FAMILY_DXCH_HARRIER_E,
                CPSS_PP_FAMILY_DXCH_IRONMAN_E,
                CPSS_PP_FAMILY_DXCH_AAS_E,

/*end*/    CPSS_PP_FAMILY_END_DXCH_E,


/*start*/  CPSS_PP_FAMILY_START_EXMXPM_E,

                CPSS_PP_FAMILY_PUMA_E,
                CPSS_PP_FAMILY_PUMA3_E,

/*end*/    CPSS_PP_FAMILY_END_EXMXPM_E,

/*start*/  CPSS_PX_FAMILY_START_E,

                CPSS_PX_FAMILY_PIPE_E,

/*end*/    CPSS_PX_FAMILY_END_E,


    CPSS_PP_FAMILY_LAST_E,

    CPSS_MAX_FAMILY = 0x7FFFFFFF
}CPSS_PP_FAMILY_TYPE_ENT;

/**
* @enum CPSS_PP_SUB_FAMILY_TYPE_ENT
 *
 * @brief Defines the different device sub families that may exist in system.
*/
typedef enum{

    /** @brief the device hold no special 'sub family' and the
     *  identified without 'sub family'
     */
    CPSS_PP_SUB_FAMILY_NONE_E,

    /** @brief this is bobk sub family within the bobcat2 family.
     *  relevant only when 'family' is 'bobcat2'
     */
    CPSS_PP_SUB_FAMILY_BOBCAT2_BOBK_E,

    CPSS_MAX_SUB_FAMILY,

    CPSS_BAD_SUB_FAMILY = 0x7FFFFFFF

} CPSS_PP_SUB_FAMILY_TYPE_ENT;

/* device type place holder */
#define PRV_CPSS_DEVICE_TYPE_PLACE_HOLDER_CNS   0xFFEEFFEE

/*
 * Typedef: enumeration CPSS_PP_DEVICE_TYPE
 *
 * Description: Defines the different device type that may exist in system.
 *
 *      known values :
 *
 *  PX - 'Port Extender' devices family :
 *      see devices list and description need the devices.
 *
 */
typedef GT_U32  CPSS_PP_DEVICE_TYPE;

/*******************************/
/* Device Part numbers - Start */
/*******************************/

/**********************/                       /*                                                      */
/* Start PIPE devices */                       /*                                                      */
/**********************/                       /*  SERDESes  10G    10/25G   Device Port Configuration */
#define    CPSS_98PX1008_CNS     0xC40111AB    /*  8+2       8       2       8x10G + 2x25G             */
#define    CPSS_98PX1012_CNS     0xC40011AB    /*  12+4      12      4       12x10GbE + 1x100GbE       */
#define    CPSS_98PX1022_CNS     0xC40311AB    /*  4+2       4       2       2x25GbE-R2 + 2x25GbE-R1   */
#define    CPSS_98PX1024_CNS     0xC40211AB    /*  8+4       8       4       4x25GbE-R2 + 4x25GbE-R1   */
#define    CPSS_98PX1016_CNS     0xC40411AB    /*  12+4      12      4       16x10GbE                  */
#define    CPSS_98PX1015_CNS     0xC40511AB    /*  12+4      12      4       12x5GbE + 4x25GbE         */

/***********************/
/* End Of PIPE devices */
/***********************/

/**************************/                  /*    FE      GE      XG      Stack   Stack   */
/***  xCat3 device start **/                  /*                             GE      XG     */
/**************************/

/* Series: AlleyCat3-FE*/
#define    CPSS_98DX1233_CNS    0xF40811AB    /*     8       0       0        2       0     */
#define    CPSS_98DX1235_CNS    0xF40911AB    /*     24      0       0        4       0     */
#define    CPSS_98DX123S_CNS    0xF50811AB    /*     8       0       0        2       0     */
#define    CPSS_98DX125S_CNS    0xF50911AB    /*     24      0       0        4       0     */

/* Series: AlleyCat3-GE*/
#define    CPSS_98DX3223_1_CNS  0xF40711AB    /*     0       8       0        4       0     */
#define    CPSS_98DX3224_CNS    0xF40611AB    /*     0      16       0        4       0     */
#define    CPSS_98DX3225_CNS    0xF40511AB    /*     0      24       0        4       0     */
#define    CPSS_98DX3226_CNS    0xF40411AB    /*     0      24       0        0       4     */
#define    CPSS_98DX3233_CNS    0xF41311AB    /*     0       8       0        4       0     */
#define    CPSS_98DX3234_CNS    0xF41211AB    /*     0      16       0        4       0     */
#define    CPSS_98DX3235_CNS    0xF41111AB    /*     0      24       0        4       0     */
#define    CPSS_98DX3236_CNS    0xF41011AB    /*     0      24       0        0       4     */
#define    CPSS_98DX223S_CNS    0xF50711AB    /*     0       8       0        4       0     */
#define    CPSS_98DX224S_CNS    0xF50611AB    /*     0      16       0        4       0     */
#define    CPSS_98DX225S_CNS    0xF50511AB    /*     0      24       0        4       0     */
#define    CPSS_98DX226S_CNS    0xF50411AB    /*     0      24       0        0       4     */
#define    CPSS_98DX233S_CNS    0xF51311AB    /*     0       8       0        4       0     */
#define    CPSS_98DX234S_CNS    0xF51211AB    /*     0      16       0        4       0     */
#define    CPSS_98DX235S_CNS    0xF51111AB    /*     0      24       0        4       0     */
#define    CPSS_98DX236S_CNS    0xF51011AB    /*     0      24       0        0       4     */
#define    CPSS_98DXH333_CNS    0xF41411AB    /*     0       8       0        4       0     */
#define    CPSS_98DXT323_CNS    0xF41511AB    /*     0      24       0        4       0     */
#define    CPSS_98DXT321_CNS    0xF41611AB    /*     0      24       0        2       0     */
#define    CPSS_98DXH201_CNS    0xF41D11AB    /*     0      24       0        4       0     */
#define    CPSS_98DXH203_CNS    CPSS_98DX3223_1_CNS  /*     0       8       0        4       0     */
#define    CPSS_98DXH204_CNS    CPSS_98DX3224_CNS    /*     0      16       0        4       0     */
#define    CPSS_98DXH205_CNS    CPSS_98DX3225_CNS    /*     0      24       0        4       0     */
#define    CPSS_98DXH206_CNS    CPSS_98DX3226_CNS    /*     0      24       0        0       4     */

/* Series: AlleyCat3-Plus */
#define    CPSS_98DX3243_CNS    0xF40F11AB    /*     0       8       0        4       0     */
#define    CPSS_98DX3244_CNS    0xF40E11AB    /*     0      16       0        4       0     */
#define    CPSS_98DX3245_CNS    0xF40D11AB    /*     0      24       0        4       0     */
#define    CPSS_98DX3246_CNS    0xF40C11AB    /*     0      24       0        4       0     */
#define    CPSS_98DX3247_CNS    0xF40A11AB    /*     0      24       0        4       0     */

#define    CPSS_98DXC323_CNS    0xF41B11AB    /*     0      24       0        2       2     */

/* Series: PonCat3-FE*/
#define    CPSS_98DX1333_CNS    0xF41811AB    /*     8       0       0        2       0     */
#define    CPSS_98DX1335_CNS    0xF41911AB    /*     24      0       0        4       0     */
#define    CPSS_98DX1336_CNS    0xF41A11AB    /*     24      0       0        0       4     */

/* Series: PonCat3-GE*/
#define    CPSS_98DX3333_CNS    0xF40311AB    /*     0       8       0        4       0     */
#define    CPSS_98DX3334_CNS    0xF40211AB    /*     0      16       0        4       0     */
#define    CPSS_98DX3335_CNS    0xF40111AB    /*     0      24       0        4       0     */
#define    CPSS_98DX3336_CNS    0xF40011AB    /*     0      24       0        0       4     */
#define    CPSS_98DX333S_CNS    0xF50311AB    /*     0       8       0        4       0     */
#define    CPSS_98DX334S_CNS    0xF50211AB    /*     0      16       0        4       0     */
#define    CPSS_98DX335S_CNS    0xF50111AB    /*     0      24       0        4       0     */
#define    CPSS_98DX336S_CNS    0xF50011AB    /*     0      24       0        0       4     */
#define    CPSS_98DXC336_CNS    0xF41C11AB    /*     0      24       0        4       0     */
#define    CPSS_98DXC334_CNS    0xF41E11AB    /*     0      16       0        4       0     */
#define    CPSS_98DXC333_CNS    0xF41F11AB    /*     0       8       0        4       0     */

/* Series: PonCat3S-GE Lite Series*/
#define    CPSS_98DX336E_CNS    0xF50C11AB    /*     0      24       0        4       0     */
#define    CPSS_98DX336R_CNS    0xF50D11AB    /*     0      24       0        2       2     */

/* Series: AlleyCat3-Unmanaged */
#define    CPSS_98DX215S_CNS    0xF51A11AB    /*     0      24       0        4       0     */
#define    CPSS_98DX216S_CNS    0xF51B11AB    /*     0      24       0        0       4     */

/* Series: AlleyCat3-Light */
#define    CPSS_98DXH201_1_CNS  0xF51D11AB    /*     0      24       0        4       0     */

/************************/
/***  xCat3 device end **/
/************************/

/**************************/                  /*    FE      GE      XG      Stack   Stack   */
/***  AC5   device start **/                  /*                             GE      XG     */
/**************************/
/* Series: AlleyCat5+ */
#define    CPSS_98DX2538_CNS    0xB40011AB    /*     0      24       2        0       2     */
#define    CPSS_98DX2535_CNS    0xB40111AB    /*     0      24       0        4       0     */
#define    CPSS_98DX2532_CNS    0xB40211AB    /*     0       8       2        2       0     */
#define    CPSS_98DX2531_CNS    0xB40311AB    /*     0       8       0        4       0     */
#define    CPSS_98DXC251_CNS    CPSS_98DX2531_CNS
                                              /*     0       8       0        4       0     */
#define    CPSS_98DXC258_CNS    CPSS_98DX2538_CNS
                                              /*     0      24       2        0       2     */
#define    CPSS_98DXC255_CNS    CPSS_98DX2535_CNS
                                              /*     0      24       0        4       0     */
#define    CPSS_98DXC232_CNS    0xB40411AB    /*     0       8       2        2       0     */

/* Series: AlleyCat5 */
#define    CPSS_98DX2528_CNS    0xB40811AB    /*     0      24       2        0       2     */
#define    CPSS_98DX2525_CNS    0xB40911AB    /*     0      24       0        4       0     */
#define    CPSS_98DX2522_CNS    0xB40A11AB    /*     0       8       2        2       0     */
#define    CPSS_98DX2521_CNS    0xB40B11AB    /*     0       8       0        4       0     */

#define    CPSS_98DXH258_CNS    0xB40C11AB    /*     0      24       2        0       2     */
#define    CPSS_98DXH255_CNS    0xB40D11AB    /*     0      24       0        4       0     */
#define    CPSS_98DXH252_CNS    0xB40E11AB    /*     0       8       2        2       0     */
#define    CPSS_98DXH251_CNS    0xB40F11AB    /*     0       8       0        4       0     */


/* Series: AlleyCat5-Lite */
#define    CPSS_98DX2518_CNS    0xB41011AB    /*     0      24       2        0       2     */
#define    CPSS_98DX2515_CNS    0xB41111AB    /*     0      24       0        4       0     */
#define    CPSS_98DX2512_CNS    0xB41211AB    /*     0       8       2        2       0     */
#define    CPSS_98DX2511_CNS    0xB41311AB    /*     0       8       0        4       0     */


/************************/
/***  AC5   device end **/
/************************/


/**********************/
/* start Lion2 devices */
/**********************/
/* Lion2 Data Center / Metro devices */
#define    CPSS_98CX8296_CNS    0xEC0511AB
#define    CPSS_98CX8297_CNS    0xEC0211AB
#define    CPSS_98CX8308_CNS    0xEC0811AB
#define    CPSS_98CX8297_1_CNS  0xEC0011AB
/* Fandago2 Switch Fabrics */
#define    CPSS_98FX9287_CNS    0xEC0D11AB
#define    CPSS_98FX9288_CNS    0xEC0C11AB

/***********************/
/* End Of Lion2 devices */
/***********************/

/******************************/
/* start Lion2 Hooper devices */
/******************************/
#define    CPSS_98CX8121_CNS    0x800011AB /* also used as dummy to support distributed Device_ID: in register 0x4c and DFX register - don't delete */
#define    CPSS_98CX8123_CNS    0x800111AB
#define    CPSS_98CX8124_CNS    0x800211AB
#define    CPSS_98CX8129_CNS    0x800311AB

/*******************************/
/* End Of Lion2 Hooper devices */
/*******************************/

/**********************/                       /*            XAUI/DXAUI                                                          */
/* Start Bobcat2 devices */                    /*           RXAUI/DRXAUI                                                         */
/**********************/                       /*  Serdes     HX/DHX        10G-KR        20G-KR        40G-KR        Interlaken */
#define    CPSS_98DX4251_CNS        0xFC0011AB /*  36            6           24              12              6           1       */
#define    CPSS_98DX4220_CNS        0xFC0311AB /*  20            3           12              6               3           0       */
#define    CPSS_98DX8216_CNS        0xFC0411AB /*  16            4           16              8               4           0       */
#define    CPSS_98DX8224_CNS        0xFC0511AB /*  24            6           24             12               6           0       */
#define    CPSS_98DX4221_CNS        0xFC0211AB /*  26            3           12              6               3           0       */
#define    CPSS_98DX4222_CNS        0xFC0611AB /*  24            3           12              6               3           0       */
#define    CPSS_98DX8219_CNS        0xFC0811AB /*  26            5           20             10               5           0       */
#define    CPSS_98DX4223_CNS        0xFC0911AB /*  36            6           24             12               6           0       */
#define    CPSS_98DX4253_CNS        0xFC0711AB /*  14            4            8              0               0           0       */

#define    CPSS_98DX42XX_CNS        0xABBA11AB /* dummy for simulation - Read from PCI register of GM SIP5 */

/***********************/
/* End Of Bobcat2 devices */
/***********************/
/**********************/                       /*            XAUI/DXAUI                                                          */
/* Start BobK devices */                       /*           RXAUI/DRXAUI                                                         */
/**********************/                       /*  Serdes     HX/DHX        10G-KR        20G-KR        40G-KR        Interlaken */
                        /* dummy for simulation - Caelum */
#define    CPSS_98DX42KK_CNS        0xBE0111AB /*  25            3           12              6               3           0       */
                        /* Caelum */
#define    CPSS_98DX4203_CNS        0xBC0011AB /*  25            3           12              6               3           0       */
#define    CPSS_98DX4204_CNS        0xBC0111AB /*  19            3           12              6               3           0       */
#define    CPSS_98DX4211_CNS        0xBC1011AB /*  25            3           12              6               3           0       */
#define    CPSS_98DX4210_CNS        0xBC1111AB /*  19            3           12              6               3           0       */
#define    CPSS_98DX4212_CNS        0xBC1211AB /*  20            3           12              6               3           0       */

#define    CPSS_98DX3347_CNS        0xBC1711AB /*  25            3           12              6               3           0       */
#define    CPSS_98DX3346_CNS        0xBC1611AB /*  19            3           12              6               3           0       */
#define    CPSS_98DX3345_CNS        0xBC1811AB /*  20            3           12              6               3           0       */

                        /* Cetus */
#define    CPSS_98DX4235_CNS        0xBE0011AB /*  13            3           12              6               3           0       */
#define    CPSS_98DX8212_CNS        0xBE1011AB /*  13            3           12              6               3           0       */
#define    CPSS_98DX8208_CNS        0xBE1111AB /*   9            2            8              4               2           0       */

/***********************/
/* End Of BobK devices */
/***********************/

/************************/                     /*            XAUI/DXAUI                                                          */
/* Start Aldrin devices */                     /*           RXAUI/DRXAUI                                                         */
/************************/                     /*  Serdes     HX/DHX        10G-KR        20G-KR        40G-KR        Interlaken */
#define    CPSS_98DX8308_CNS        0xC81911AB /*   9          2/4           8             4             2             0         */
#define    CPSS_98DX8312_CNS        0xC81C11AB /*   13         3/6           12            6             3             0         */
#define    CPSS_98DX8315_CNS        0xC80E11AB /*   33         2/4           8             4             2             0         */
#define    CPSS_98DX8316_CNS        0xC81D11AB /*   16         4/8           16            8             4             0         */
#define    CPSS_98DX8324_CNS        0xC81E11AB /*   24         6/12          24            12            6             0         */
#define    CPSS_98DX8332_CNS        0xC81F11AB /*   32         8/16          32            16            8             0         */
#define    CPSS_98DXZ832_CNS        0xC81811AB /*   33         8/16          32            16            8             0         */
#define    CPSS_98DX8332_Z0_CNS     0xBC1F11AB /*   25         3             12            6             3             0         */
#define    CPSS_98DXH831_CNS        0xC81511AB /*   16         4/8           16            8             4             0         */
#define    CPSS_98DXH832_CNS        0xC81611AB /*   24         6/12          24            12            6             0         */
#define    CPSS_98DXH833_CNS        0xC81711AB /*   32         8/16          32            16            8             0         */
#define    CPSS_98DXH834_CNS        0xC81A11AB /*   16         4/8           16            8             4             0         */
#define    CPSS_98DXH835_CNS        0xC81B11AB /*   24         6/12          24            12            6             0         */

/***********************/
/* End Of Aldrin devices */
/***********************/

/*************************/                       /*                                                      */
/* Start Bobcat3 devices */                       /*                                                      */
/*************************/                       /*  Serdes    10G    10/25G   Device Port Configuration */
#define    CPSS_98CX8420_CNS        0xD40F11AB    /*  72+2      2      72       48x10/25GE+6x100GE, 36x50GE or 18x100GE */
#define    CPSS_98CX8410_CNS        0xD40011AB    /*  72+2      2      72       48x10/25GE+6x100GE, 36x50GE or 18x100GE */
#define    CPSS_98CX8405_CNS        0xD40111AB    /*  48+2      2      48       48x10/25GE */

/* FakeId for Bobcat3 GM */
#define    CPSS_98CX8420_GM_USED_CNS 0xFF0011AB    /*  12+1      1      12     */

/**************************/
/* End Of Bobcat3 devices */
/**************************/

/***************************/                     /*                                                      */
/* Start Armstrong devices */                     /*                                                      */
/***************************/                     /*  Serdes    10G    10/25G   Device Port Configuration */
#define    CPSS_98EX5410_CNS        0xD40E11AB    /*  72+1     72+1    72       48x10GE+6x40GE        */
#define    CPSS_98EX5420_CNS        0xD40D11AB    /*  72+1     72+1    48/24    48x10GE+6x100GE       */
#define    CPSS_98EX5422_CNS        0xD40C11AB    /*  72+1     72+1    48/24    48x10GE+6x100GE       */
#define    CPSS_98EX5424_CNS        0xD40B11AB    /*  48+1     48+1    8        24x10GE+6x40/2x100GE  */
#define    CPSS_98EX5421_CNS        0xD40811AB    /*  48+1     48+1    8        24x10GE+6x40/2x100GE  */
#define    CPSS_98EX5430_CNS        0xD40A11AB    /*  72+1     72+1    48/24    48x10GE+6x100GE       */
#define    CPSS_98EX5431_CNS        0xD40911AB    /*  72+1     72+1    72       48x10GE+6x40GE        */
#define    CPSS_98EX5432_CNS        0xD40711AB    /*  72+1     24+1    72       48x2.5GE+6x40GE       */

/****************************/
/* End Of Armstrong devices */
/****************************/

/****************************/                     /*                                                       */
/* Start Aldrin2 XL devices */                     /*                                                       */
/****************************/                     /*  Serdes    10G    10/25G   Device Port Configuration  */
#define    CPSS_98DX8572_CNS        0xD40511AB     /*  72+2      2      72       48x25GE+6x100GE            */
/****************************/
/* End Of Aldrin2 XL devices */
/****************************/

/****************************/                     /*                                                      */
/* Start Aldrin2 devices */                        /*                                                      */
/****************************/                     /*  Serdes    10G    10/25G   Device Port Configuration */
#define    CPSS_98EX5520_CNS        0xCC0F11AB     /*  72+1     72+1    24       48x10GE+6x100GE or 48x10G+24x25G */
#define    CPSS_98EX5524_CNS        0xCC0E11AB     /*  48+1     48+1    24       24x10G+6x100G or 24x10G+24x25G */
#define    CPSS_98DX8524_CNS        0xCC1C11AB     /*  48+1     48+1    24       24x10GE+6x40/100GE     */
#define    CPSS_98DX8525_CNS        0xCC1D11AB     /*  24+1     24+1    12       24x25GE                */
#define    CPSS_98DX8515_CNS        0xCC1811AB     /*  16+1     16+1    16       8x1/2.5/5/10/25GE + 8x1/2.5/5/10/25GE / 4x50G-R2 / 2x100G-R4 */
#define    CPSS_98DX8648_CNS        0xCC1911AB     /*  72+1     72+1    24       48x10GE+6x40/100GE   */
#define    CPSS_98DX8548_CNS        0xCC1F11AB     /*  72+1     72+1    24       48x10GE+6x40/100GE   */
#define    CPSS_98DX8548_H_CNS      0xCC1B11AB     /*  72+1     72+1    24       48x10GE+6x40/100GE   */
#define    CPSS_98DX8448_CNS        0xCC1E11AB     /*  72+1     72+1    0        48x10GE+6x40GE  */
#define    CPSS_98DX8410_CNS        0xCC1A11AB     /*  48+1     48+1    0        48x10GE         */

/* Cygnus 2 */
#define    CPSS_98DX4310_CNS        0xCC0011AB     /*  64+1     40+1    4        24x1/2.5G+24x1/2.5/5/10G+4x25G/2x40G/8x10G */
/****************************/
/* End Of Aldrin2 devices   */
/****************************/

/****************************/                     /*                                                      */
/* Start Falcon     devices */                     /*                                                      */
/****************************/                     /*  Serdes     28G     56G  Device Port Configuration  */
#define    CPSS_98CX8520_CNS           0x840911AB  /*  (4 *16)+2   2     4*16    3.2T  */
#define    CPSS_98CX8525_CNS           0x841911AB  /*  (4 *16)+2   2     4*16    3.2T  */

#define    CPSS_98CX8540_CNS           0x840011AB  /*  (8 *16)+2   2     8*16    6.4T  */
#define    CPSS_98CX8540_H_CNS         0x840111AB  /*  (8 *16)+2   2     8*16    6.4T  */
#define    CPSS_98CX8580_CNS           0x860011AB  /*  (16*16)+2   2    16*16    12.8T */
#define    CPSS_98CX8580_E_CNS         0x860111AB  /*  (16*16)+2   2    16*16    12.8T */

#define    CPSS_98CX8522_CNS           0x840411AB  /*  (8 *16)+2   8*16     0    128*25G */
#define    CPSS_98CX8542_CNS           0x860411AB  /*  (16*16)+2   16*16    0    256*25G */

#define    CPSS_98CX8550_CNS           0x860811AB  /*  (10*16)+2   0    10*16    160x50G    8T*/
#define    CPSS_98CX8530_CNS           0x840811AB  /*  ( 5*16)+2   0     5*16     80x50G    4T*/
#define    CPSS_98CX8535_CNS           0x841011AB  /*  ( 5*16)+2   0     5*16     80x50G    4T*/
#define    CPSS_98CX8535_H_CNS         0x841111AB  /*  ( 5*16)+2   0     5*16     80x50G    4T*/
#define    CPSS_98CX8512_CNS           0x841E11AB  /*  ( 5*16)+2   5*16     0     80x25G    2T*/
#define    CPSS_98CX8514_CNS           0x841811AB  /*  ( 5*16)+2   5*16     0     80x25G    2T*/

/* device ids for emulator */

/* value 0x8513 for EMULATOR (+simulation+GM) */
#define    CPSS_98CX8513_CNS           0x851311AB  /*  (4 *16)+1   1     4*16    3.2T  */
/* value 0x8610 for EMULATOR 6.4T */
#define    CPSS_98CX8580_10_CNS        0x861011AB  /*  (16*16)+2   2    16*16    12.8T */

/* device id for simulation */

/* ALL The Falcon devices on the PEX shown without the explicit flavor */
/* for explicit value can be read from MG0 register : 0x1d00004c */
#define    CPSS_FALCON_ON_PEX_CNS      0x840011AB  /*  All 3.2T/ 6.4T / 9.6T/12.8T devices */

/*****************************/
/* End Of Falcon     devices */
/****************************/

/****************************/                     /*                                                      */
/* Start Armstrong2 devices */                     /*                                                      */
/****************************/                     /*  Serdes     28G     56G  Device Port Configuration  */
#define    CPSS_98EX5610_CNS           0x840E11AB  /*  (5 *16)+2  82        0  80x25GE */
#define    CPSS_98EX5614_CNS           0x841611AB  /*  ( 5*16)+2   5*16     0     80x25G    2T*/
#define    CPSS_98EX5630_CNS           0x840611AB  /*  (8 *16)+4  96       32  96x25G+32x50G 4T */
/****************************/
/* End Of Armstrong2 devices */
/****************************/


/****************************/                     /*                                                           */
/* Start AC5P       devices */                     /*                                                           */
/****************************/                     /*  Serdes      10G    25G   100G  400G  Device Port Configuration  */
/* device ID on emulator */
#define    CPSS_98DX9410_CNS           0x941011AB  /*  32+1         1    32    1.6T  */
/* AC5P */
#define    CPSS_98DX4504_CNS           0x940011AB  /*  24           16     8      2     0   16x10G SFP + 8x25G/48x1G + 4x25G + 2x100G-R4 */
#define    CPSS_98DX4510_CNS           0x940111AB  /*  24            0     4      2     0   48x1G + 4x25G + 2x100G-R4 */
#define    CPSS_98DX4530_CNS           0x940211AB  /*  24            0     4      2     0   48x2.5G + 4x25G + 2x100G-R4 */
#define    CPSS_98DX4550_CNS           0x940311AB  /*  24           24     4      2     0   48x5G/24x10G + 4x25G + 2x100G-R4 */

/* AC5P XL */
#define    CPSS_98DX4570_CNS           0x940411AB  /*  32           24     4      4     0   48x5G/24x10G + 4x25G + 4x100G-R4  */
#define    CPSS_98DX4590_CNS           0x940511AB  /*  32           24     0      2     2   48x5G/24x10G + 2x100G-R2 + 2x400G */
#define    CPSS_98DX4580_CNS           0x940611AB  /*  32            0     0      2     2   48x1/2.5G + 2x100G-R2 + 2x400G  */
#define    CPSS_98DX4595_CNS           0x940711AB  /*  32           32    32     16     4   32x50G */

/* AC5P MacSec */
#define    CPSS_98DX4504M_CNS          0x944011AB  /*  24           16     8      2     0   16x10G SFP + 8x25G/48x1G + 4x25G + 2x100G-R4 */
#define    CPSS_98DX4510M_CNS          0x944111AB  /*  24            0     4      2     0   48x1G + 4x25G + 2x100G-R4 */
#define    CPSS_98DX4530M_CNS          0x944211AB  /*  24            0     4      2     0   48x2.5G + 4x25G + 2x100G-R4 */
#define    CPSS_98DX4550M_CNS          0x944311AB  /*  24           24     4      2     0   48x5G/24x10G + 4x25G + 2x100G-R4 */

/* AC5P XL MacSec */
#define    CPSS_98DX4570M_CNS          0x944411AB  /*  32           24     4      4     0   48x5G/24x10G + 4x25G + 4x100G-R4  */
#define    CPSS_98DX4590M_CNS          0x944511AB  /*  32           24     0      2     2   48x5G/24x10G + 2x100G-R2 + 2x400G */
#define    CPSS_98DX4580M_CNS          0x944611AB  /*  32            0     0      2     2   48x1/2.5G + 2x100G-R2 + 2x400G */
#define    CPSS_98DX4595M_CNS          0x944711AB  /*  32           32    32     16     4   32x50G */

/* AC5P-H XL */
#define    CPSS_98DX4590_H_CNS         0x940811AB  /*  32           24     0      2     2   48x5G/24x10G + 2x100G-R2 + 2x400G */

/* AC5P-H XL MacSec */
#define    CPSS_98DX4590M_H_CNS        0x944811AB  /*  32           24     0      2     2   48x5G/24x10G + 2x100G-R2 + 2x400G */

/* AC5P Armstrong2S */
#define    CPSS_98EX5604_CNS           0x942011AB  /*  32            0     24     4     2   24x25G/6x100G + 4x100G-R2/2x400G */
#define    CPSS_98EX5604M_CNS          0x946011AB  /*  32            0     24     4     2   24x25G/6x100G + 4x100G-R2/2x400G */

/* AC5P Aldrin3 */
#define    CPSS_98DX7324_CNS           0x942811AB  /*  24            0     24     2     0   24x25G / 16x25G + 2x100G-R4      */
#define    CPSS_98DX7324M_CNS          0x946811AB  /*  24            0     24     2     0   24x25G / 16x25G + 2x100G-R4      */

#define    CPSS_98DX7325_CNS           0x942911AB  /*  24            0     0     0      0   24x50G                           */
#define    CPSS_98DX7325M_CNS          0x946911AB  /*  24            0     0     0      0   24x50G                           */
#define    CPSS_98DXC725_CNS           0x946D11AB  /*  24            0     0     0      0   24x50G                           */

/* AC5P Aldrin3 XL */
#define    CPSS_98DX7332_CNS           0x942A11AB  /*  32           32     0      0     8   32x25G / 8x100G-R4               */
#define    CPSS_98DX7332M_CNS          0x946A11AB  /*  32           32     0      0     8   32x25G / 8x100G-R4               */

#define    CPSS_98DX7335_CNS           0x942B11AB  /*  32           32     0      0     8   32x25G / 8x100G-R4               */
#define    CPSS_98DX7335M_CNS          0x946B11AB  /*  32            0     0     16     4   32x50G/16x100G-R2/8x100G-R4/8x200G-R2/4x400G-R8  */

/* AC5P-H Aldrin3 XL */
#define    CPSS_98DX7335_H_CNS         0x942C11AB  /*  32           32     0      0     8   32x25G / 8x100G-R4               */
#define    CPSS_98DX7335M_H_CNS        0x946C11AB  /*  32            0     0     16     4   32x50G/16x100G-R2/8x100G-R4/8x200G-R2/4x400G-R8  */

/* ALL The AC5P devices on the PEX shown without the explicit flavor */
/* for explicit value can be read from DFX server register           */
#define    CPSS_AC5P_ON_PEX_CNS      0x940011AB  /*  All AC5P devices */

/***********************/
/* End Of AC5P devices */
/***********************/

/****************************/                      /*                                                          */
/* Start AC5X    devices */                         /*                                                          */
/****************************/                      /*  Serdes      10G/25G   100G   Device Port Configuration    */
/* AC5X (Enerprise) */
#define    CPSS_98DX3500M_CNS          0x980011AB   /*  3*(8)+6         6       0     24x1G + 6x25G              */
#define    CPSS_98DX3501M_CNS          0x980611AB   /*  2*(8)+6         6       0     16x1G + 6x10G              */
#define    CPSS_98DX3510M_CNS          0x980111AB   /*  6*(8)+6         6       0     48x1G + 6x25G              */
#define    CPSS_98DX3520M_CNS          0x980211AB   /*  3*(8)+6         6       0     24x2.5G + 6x25G            */
#define    CPSS_98DX3530M_CNS          0x980311AB   /*  6*(8)+6         6       0     48x2.5G + 6x25G            */
#define    CPSS_98DX3540M_CNS          0x980411AB   /*  3*(4)+6         6       0     12x5G/6x10G + 6x25G        */
#define    CPSS_98DX3550M_CNS          0x980511AB   /*  6*(4)+6         6       0     24x5G/12x10G + 6x25G       */

#define    CPSS_98DX3500_CNS           0x982011AB   /*  3*(8)+6         6       0     24x1G + 6x25G              */
#define    CPSS_98DX3501_CNS           0x982611AB   /*  2*(8)+6         6       0     16x1G + 6x10G              */
#define    CPSS_98DX3510_CNS           0x982111AB   /*  6*(8)+6         6       0     48x1G + 6x25G              */
#define    CPSS_98DX3510_H_CNS         0x986111AB   /*  6*(8)+6         6       0     48x1G + 6x25G              */
#define    CPSS_98DX3510M_H_CNS        0x984111AB   /*  6*(8)+6         6       0     48x1G + 6x25G              */
#define    CPSS_98DX3520_CNS           0x982211AB   /*  3*(8)+6         6       0     24x2.5G + 6x25G            */
#define    CPSS_98DX3530_CNS           0x982311AB   /*  6*(8)+6         6       0     48x2.5G + 6x25G            */
#define    CPSS_98DX3530_H_CNS         0x986311AB   /*  6*(8)+6         6       0     48x2.5G + 6x25G            */
#define    CPSS_98DX3530M_H_CNS        0x984311AB   /*  6*(8)+6         6       0     48x2.5G + 6x25G            */
#define    CPSS_98DX3540_CNS           0x982411AB   /*  3*(4)+6         6       0     12x5G/6x10G + 6x25G        */
#define    CPSS_98DX3550_CNS           0x982511AB   /*  6*(4)+6         6       0     24x5G/12x10G + 6x25G       */
#define    CPSS_98DX3511_CNS           0x982711AB   /*  6*(8)+6         6       0     48x1G + 6x25G, no CPU      */

/* Aldrin3S (Connectivity/RAN) */
#define    CPSS_98DX7312_CNS           0x983F11AB   /*   12            12       1     12x25G / 8x25G + 1x100G     */
#define    CPSS_98DX7312M_CNS          0x981F11AB   /*   12            12       1     12x25G / 8x25G + 1x100G     */
#define    CPSS_98DX7308_CNS           0x983E11AB   /*    8             8       0     8x25G                       */
#define    CPSS_98DX7308M_CNS          0x981E11AB   /*    8             8       0     8x25G                       */
#define    CPSS_98DXC712_CNS           0x981D11AB   /*   12            12       1     12x25G / 8x25G + 1x100G     */
#define    CPSS_98DXC708_CNS           0x981C11AB   /*    8             8       0     8x25G                       */

/***********************/
/* End Of AC5X devices */
/***********************/

/****************************/                     /*                                                      */
/* Start Harrier    devices */                     /*                                                      */
/****************************/                     /*  Serdes    25G     50G  Device Port Configuration    */
#define    CPSS_98DXC720_CNS           0x900011AB  /*  20        20       0          500G (0.5T)            */
#define    CPSS_98DXC721_CNS           0x900111AB  /*  20        20      20         1000G (1.0T)            */
#define    CPSS_98DX7320_CNS           0x906011AB  /*  20        20       0          500G (0.5T)            */
#define    CPSS_98DX7321_CNS           0x906111AB  /*  20        20      20         1000G (1.0T)            */
#define    CPSS_98DX7320M_CNS          0x904011AB  /*  20        20       0          500G (0.5T)            */
#define    CPSS_98DX7321M_CNS          0x904111AB  /*  20        20      20         1000G (1.0T)            */

#define    CPSS_98CN106xxS_CNS         0x214111AB  /*  20        20      20         1000G (1.0T)            */

/**************************/
/* End Of Harrier devices */
/**************************/


/****************************/                     /*                                        */
/* Start Ironman    devices */                     /*                                        */
/****************************/                     /*  Serdes  10G-OUSGMII(8x1G)   10G     2.5G      */
/*Ironman*/
#define    CPSS_98DXA010_CNS           0xA01011AB  /*  13            48            5       0         */
#define    CPSS_98DXA000_CNS           0xA00011AB  /*  13            48            5       0         */
/* 48x1G */
#define    CPSS_98DX1528_CNS           0xA00B11AB  /*  12            48            6       0         */
#define    CPSS_98DX1528M_CNS          0xA00311AB  /*  12            48            6       0         */
/* 24x1G */
#define    CPSS_98DX1518_CNS           0xA00C11AB  /*  12            24            6       0         */
#define    CPSS_98DX1518M_CNS          0xA00411AB  /*  12            24            6       0         */
/* 24x1G  */
#define    CPSS_98DX1538_CNS           0xA00A11AB  /*  13            24            4      24         */
#define    CPSS_98DX1538M_CNS          0xA00211AB  /*  13            24            4      24         */
/* 16x1G  */
#define    CPSS_98DX1516_CNS           0xA00D11AB  /*   7            16            4       0         */
#define    CPSS_98DX1516M_CNS          0xA00511AB  /*   7            16            4       0         */
/* 12x10G */
#define    CPSS_98DX1548_CNS           0xA00911AB  /*  13            12            0       0         */
#define    CPSS_98DX1548M_CNS          0xA00111AB  /*  13            12            0       0         */

/* 8x1G */
#define    CPSS_98DX1507_CNS           0xA20911AB  /*   4             8            0       4         */
#define    CPSS_98DX1507M_CNS          0xA20111AB  /*   4             8            0       4         */
#define    CPSS_98DX1508_CNS           0xA20A11AB  /*   4             8            4       0         */
#define    CPSS_98DX1508M_CNS          0xA20211AB  /*   4             8            4       0         */

/* AC5Y */
#define    CPSS_98DXC254_CNS           0xA04611AB  /*  10            16            4       8         */
#define    CPSS_98DX2548_CNS           0xA24811AB  /*   5             8            4       0         */
#define    CPSS_98DX2548M_CNS          0xA24011AB  /*   5             8            4       0         */
#define    CPSS_98DX2556_CNS           0xA04D11AB  /*   7            16            4       0         */
#define    CPSS_98DX2556M_CNS          0xA04511AB  /*   7            16            4       0         */
#define    CPSS_98DX2558_CNS           0xA04C11AB  /*  13            24            6       0         */
#define    CPSS_98DX2558M_CNS          0xA04411AB  /*  13            24            6       0         */
#define    CPSS_98DX2568_CNS           0xA04B11AB  /*  12            48            6       0         */
#define    CPSS_98DX2568M_CNS          0xA04311AB  /*  12            48            6       0         */
#define    CPSS_98DX2578_CNS           0xA04A11AB  /*  13            24            4      24         */
#define    CPSS_98DX2578M_CNS          0xA04211AB  /*  13            24            4      24         */
#define    CPSS_98DX2588_CNS           0xA04911AB  /*  13            12            0       0         */
#define    CPSS_98DX2588M_CNS          0xA04111AB  /*  13            12            0       0         */


/**************************/
/* End Of Ironman devices */
/**************************/

/****************************/
/* Start AAS    devices     */
/****************************/                     /*  Serdes       50G             100G     CPU(50)*/
/* fake 'name' and 'number' */
#define    CPSS_98DX4180_CNS           0x418011AB  /*  80+1          48             32       1      */
#define    CPSS_98DXB100_CNS           0xB10011AB  /* 160+2          96             64       1      */


/**************************/
/* End Of AAS devices     */
/**************************/

/************************/                     /*            XAUI/DXAUI                                                          */
/* Start AC3X devices */                       /*           RXAUI/DRXAUI                                                         */
/************************/                     /*  Serdes     HX/DHX        10G-KR        20G-KR        40G-KR        Interlaken */
#define    CPSS_98DX3255_CNS        0xC80411AB /*  15            0           8               4               2           0       */
#define    CPSS_98DX3256_CNS        0xC80511AB /*  19            3           8               4               2           0       */
#define    CPSS_98DX3257_CNS        0xC80611AB /*  25            6           8               4               2           0       */
#define    CPSS_98DX3258_CNS        0xC80711AB /*  33            0           8               4               2           0       */
#define    CPSS_98DX3259_CNS        0xC80811AB /*  33            0           12              4               2           0       */
#define    CPSS_98DX3265_CNS        0xC80C11AB /*  15            0           8               4               2           0       */
#define    CPSS_98DX3268_CNS        0xC80F11AB /*  33            0           8               4               2           0       */

/***********************/
/* End Of AC3X devices */
/***********************/

/************************/                     /*            XAUI/DXAUI                                                          */
/* Start xCat3+ devices */                     /*           RXAUI/DRXAUI                                                         */
/************************/                     /*  Serdes     HX/DHX        10G-KR        20G-KR        40G-KR        Interlaken */
#define    CPSS_98DX3248_CNS        0xC80111AB /*  33            6           20              10              5           0       */
#define    CPSS_98DX3249_CNS        0xC80011AB /*  33            16          32              16              8           0       */

/***********************/
/* End Of xCat3+ devices */
/***********************/

/*****************************/
/* Device Part numbers - End */
/*****************************/

/* PCI quirks for PEX devices
 * Currently used for Linux only
 */
#define PCI_RESOURCE_PSS_REGS_PCI   1
#define PCI_RESOURCE_PSS_REGS_PEX   2
#define PCI_CONFIG_SIZE (4*1024)
#define PEX_CONFIG_SIZE 0x10000
#define MSYS_CONFIG_SIZE 0x100000
/*
 * Typedef: struct prvPciDeviceQuirks
 *
 * Description: PCI devices quirks
 *
 * Fields:
 *      pciId           Device PCI ID
 *      isPex           Flags that device is PEX connected
 *      configOffset    Some? PEX PP has config started at offset 0x70000 in
 *                      config address space, access to addresses below this
 *                      offset causes to hang system.
 *                      If packet processor is listed here then memory should
 *                      be mapped with offset added for both source(hw) and
 *                      destination (VM) addresses.
 *                      This will protect us from accessing to invalid addresses
 *                      causes just SEGV which can be easy hooked with gdb
 *      configSize      The PEX devices has longer config, so add this value here
 *      pciResourceReg  PCI resource number for registers address space (used by
 *                      mvPpDrv)
 *      hasDfx          The DFX registers are follows PP registers (64MBytes)
 */

/* macro to set PEX entry in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_PEX_ENTRY_MAC(pciId,pexOffset,dfx) \
    { (pciId),  GT_TRUE, pexOffset, PEX_CONFIG_SIZE, PCI_RESOURCE_PSS_REGS_PEX, dfx }

/* macro to set MSYS entry in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(pciId, dfx) \
    { (pciId),  GT_TRUE,  0, MSYS_CONFIG_SIZE, PCI_RESOURCE_PSS_REGS_PEX, dfx }

/* macro to set PEX 0x00000 entry in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_PEX_0x00000_ENTRY_MAC(pciId) \
    PRV_CPSS_DEVICE_QUIRKS_PEX_ENTRY_MAC(pciId,0x00000,GT_FALSE)

/* macro to set PEX 0x40000 entry in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_PEX_0x40000_ENTRY_MAC(pciId) \
    PRV_CPSS_DEVICE_QUIRKS_PEX_ENTRY_MAC(pciId,0x40000,GT_FALSE)

/* macro to set PEX 0x70000 entry in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(pciId) \
    PRV_CPSS_DEVICE_QUIRKS_PEX_ENTRY_MAC(pciId,0x70000,GT_FALSE)


/* PEX address space might be used for MSYS registers access. */

/* macro to set DXCH xCat3 pex devices in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_XCAT3_PEX_MAC \
/* Series: AlleyCat3-FE*/  \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1233_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1235_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX123S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX125S_CNS, GT_TRUE),\
/* Series: AlleyCat3-GE*/  \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3223_1_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3224_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3225_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3226_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3233_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3234_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3235_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3236_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH333_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXT323_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXT321_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC323_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX223S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX224S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX225S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX226S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX233S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX234S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX235S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX236S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH201_CNS, GT_TRUE),\
/* Series: AlleyCat3-Plus */ \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3243_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3244_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3245_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3246_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3247_CNS, GT_TRUE),\
/* Series: PonCat3-FE*/  \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1333_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1335_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1336_CNS, GT_TRUE),\
/* Series: PonCat3-GE*/  \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3333_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3334_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3335_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3336_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX333S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX334S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX335S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX336S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC336_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC334_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC333_CNS, GT_TRUE),\
/* Series: AlleyCat3-Unmanaged */ \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX215S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX216S_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH201_1_CNS, GT_TRUE),\
/* Series: PonCat3S-GE Lite Series*/ \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX336E_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX336R_CNS, GT_TRUE)

/* macro to set DXCH AC5 pex devices in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_AC5_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2538_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2535_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2532_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2531_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2528_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2525_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2522_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2521_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2518_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2515_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2512_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2511_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH258_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH255_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH252_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH251_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC232_CNS, GT_TRUE)

/* macro to set DXCH Lion2 pex devices in the array of prvPciDeviceQuirks[]*/
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_LION2_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8296_CNS),\
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8297_CNS),\
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8308_CNS),\
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8297_1_CNS),\
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8121_CNS),\
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8123_CNS),\
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8124_CNS),\
    PRV_CPSS_DEVICE_QUIRKS_PEX_0x70000_ENTRY_MAC(CPSS_98CX8129_CNS)

/* Bobcat2 PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_BOBCAT2_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4251_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4220_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4221_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4222_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4223_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8216_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8219_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8224_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4253_CNS, GT_TRUE)

/* Bobcat2-bobk PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_BOBK_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX42KK_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4203_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4204_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3346_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3345_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4211_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3347_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4210_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4235_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8212_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8208_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8308_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8312_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8315_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8316_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8324_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8332_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3248_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3249_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3255_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3256_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3257_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3258_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3259_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXZ832_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8332_Z0_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4212_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH831_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH832_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH833_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH834_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXH835_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3265_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3268_CNS, GT_TRUE)

/* Bobcat3 PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_BOBCAT3_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98CX8410_CNS, GT_TRUE) , \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98CX8420_CNS, GT_TRUE) , \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98CX8405_CNS, GT_TRUE) , \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98CX8420_GM_USED_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8572_CNS, GT_TRUE)

/* Armstrong PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_ARMSTRONG_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5410_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5420_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5422_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5424_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5421_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5430_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5431_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5432_CNS, GT_TRUE)

/* Aldrin2 PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_ALDRIN2_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5520_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98EX5524_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8524_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8548_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8548_H_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8648_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8448_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8525_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8515_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX4310_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX8410_CNS, GT_TRUE)

/* Falcon PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_FALCON_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_FALCON_ON_PEX_CNS, GT_TRUE)

/* AC5P PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_AC5P_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_AC5P_ON_PEX_CNS, GT_TRUE)

/* AC5X PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_AC5X_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3500_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3501_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3510_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3511_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3510_H_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3510M_H_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3520_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3530_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3530_H_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3530M_H_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3540_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3550_CNS,  GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3500M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3501M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3510M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3520M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3530M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3540M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX3550M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7312_CNS , GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7312M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7308_CNS , GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7308M_CNS, GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC712_CNS , GT_TRUE),\
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC708_CNS,  GT_TRUE)



/* Harrier PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_HARRIER_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC720_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC721_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7320_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7320M_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7321_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX7321M_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98CN106xxS_CNS, GT_TRUE)


/* Ironman PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_DXCH_IRONMAN_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXA010_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXA000_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1528_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1528M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2568_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2568M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1518_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1518M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1538_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1538M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2558_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2558M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2578_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2578M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1516_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1516M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2556_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2556M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1548_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1548M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2588_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2588M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1507_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1507M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1508_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX1508M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2548_CNS ,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DX2548M_CNS,GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98DXC254_CNS, GT_TRUE)

/* PIPE PEX address space is used for MSYS registers access.
   Use offset 0 to access whole range of MSYS address space. */
#define PRV_CPSS_DEVICE_QUIRKS_PX_PIPE_PEX_MAC \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98PX1008_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98PX1012_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98PX1022_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98PX1024_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98PX1015_CNS, GT_TRUE), \
    PRV_CPSS_DEVICE_QUIRKS_MSYS_ENTRY_MAC(CPSS_98PX1016_CNS, GT_TRUE)


/* macro PRV_PCI_DEVICE_QUIRKS_ARRAY_MAC
 * Defines static PCI quirks array prvPciDeviceQuirks
*/
#define PRV_PCI_DEVICE_QUIRKS_ARRAY_MAC \
static struct prvPciDeviceQuirks { \
    GT_U32      pciId; \
    GT_BOOL     isPex; \
    GT_U32      configOffset; \
    GT_U32      configSize; \
    int         pciResourceReg; \
    GT_BOOL     hasDfx; \
} prvPciDeviceQuirks[] = { \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_LION2_PEX_MAC,/*Lion2 devices*/          \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_BOBCAT2_PEX_MAC,/*Bobcat2 devices*/      \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_BOBK_PEX_MAC,   /*Bobk devices*/         \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_XCAT3_PEX_MAC,/*xcat3 devices*/          \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_AC5_PEX_MAC,  /*Ac5 devices*/            \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_BOBCAT3_PEX_MAC,/*Bobcat3 devices */     \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_ARMSTRONG_PEX_MAC,/* Armstrong devices */\
    PRV_CPSS_DEVICE_QUIRKS_DXCH_ALDRIN2_PEX_MAC,/*Aldrin2 devices */     \
    PRV_CPSS_DEVICE_QUIRKS_PX_PIPE_PEX_MAC,/* PX - Pipe devices */       \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_FALCON_PEX_MAC, /* Falcon devices */     \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_AC5P_PEX_MAC, /* AC5P devices */         \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_AC5X_PEX_MAC, /* AC5X devices */         \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_HARRIER_PEX_MAC, /* Harrier devices */   \
    PRV_CPSS_DEVICE_QUIRKS_DXCH_IRONMAN_PEX_MAC, /* Ironman devices */   \
    /* Default: PCI device */ \
    { 0xffffffff,         GT_FALSE,      0, PCI_CONFIG_SIZE, PCI_RESOURCE_PSS_REGS_PCI, GT_FALSE }  \
};


/* xCat3 devices */

/* xCat3 with 8GE,2stack ports */
#define PRV_CPSS_XCAT3_8GE_2STACK_PORTS_DEVICES \
    CPSS_98DX1233_CNS,                  \
    CPSS_98DX1333_CNS,                  \
    CPSS_98DX123S_CNS

/* xCat3 with 8GE,4stack ports */
#define PRV_CPSS_XCAT3_8GE_4STACK_PORTS_DEVICES \
    CPSS_98DX3223_1_CNS,                \
    CPSS_98DX3233_CNS,                  \
    CPSS_98DX3333_CNS,                  \
    CPSS_98DXH333_CNS,                  \
    CPSS_98DX3243_CNS,                  \
    CPSS_98DX223S_CNS,                  \
    CPSS_98DX233S_CNS,                  \
    CPSS_98DX333S_CNS,                  \
    CPSS_98DXC333_CNS

/* xCat3 with 16GE,4stack ports */
#define PRV_CPSS_XCAT3_16GE_4STACK_PORTS_DEVICES   \
    CPSS_98DX3334_CNS,                  \
    CPSS_98DX3224_CNS,                  \
    CPSS_98DX3234_CNS,                  \
    CPSS_98DX3244_CNS,                  \
    CPSS_98DX334S_CNS,                  \
    CPSS_98DX224S_CNS,                  \
    CPSS_98DX234S_CNS,                  \
    CPSS_98DX3244_CNS,                  \
    CPSS_98DXC334_CNS

/* xCat3 with 24GE,2stack ports */
#define PRV_CPSS_XCAT3_24GE_2STACK_PORTS_DEVICES   \
        CPSS_98DXT321_CNS

/* xCat3 with 24GE,4stack ports */
#define PRV_CPSS_XCAT3_24GE_4STACK_PORTS_DEVICES   \
    CPSS_98DX1235_CNS,                    \
    CPSS_98DX1335_CNS,                    \
    CPSS_98DX1336_CNS,                    \
    CPSS_98DX3235_CNS,                    \
    CPSS_98DX3236_CNS,                    \
    CPSS_98DX3225_CNS,                    \
    CPSS_98DX3226_CNS,                    \
    CPSS_98DX3335_CNS,                    \
    CPSS_98DX3336_CNS,                    \
    CPSS_98DXT323_CNS,                    \
    CPSS_98DXC323_CNS,                    \
    CPSS_98DX3245_CNS,                    \
    CPSS_98DX3246_CNS,                    \
    CPSS_98DX3247_CNS,                    \
    CPSS_98DXH201_CNS,                    \
    CPSS_98DX125S_CNS,                    \
    CPSS_98DX235S_CNS,                    \
    CPSS_98DX236S_CNS,                    \
    CPSS_98DX225S_CNS,                    \
    CPSS_98DX226S_CNS,                    \
    CPSS_98DX335S_CNS,                    \
    CPSS_98DX336S_CNS,                    \
    CPSS_98DXC336_CNS,                    \
    CPSS_98DX215S_CNS,                    \
    CPSS_98DX216S_CNS,                    \
    CPSS_98DXH201_1_CNS,                  \
    CPSS_98DX336E_CNS,                    \
    CPSS_98DX336R_CNS

#define PRV_CPSS_DXCH_XCAT3_GE_DEVICES_CASES_MAC    \
    /*caller start with 'case' */                   \
         CPSS_98DX3223_1_CNS:                       \
    case CPSS_98DX3224_CNS:                         \
    case CPSS_98DX3225_CNS:                         \
    case CPSS_98DX3226_CNS:                         \
    case CPSS_98DX3233_CNS:                         \
    case CPSS_98DX3234_CNS:                         \
    case CPSS_98DX3235_CNS:                         \
    case CPSS_98DX3236_CNS:                         \
    case CPSS_98DX3333_CNS:                         \
    case CPSS_98DX3334_CNS:                         \
    case CPSS_98DX3335_CNS:                         \
    case CPSS_98DXH333_CNS:                         \
    case CPSS_98DX3336_CNS:                         \
    case CPSS_98DXT323_CNS:                         \
    case CPSS_98DXT321_CNS:                         \
    case CPSS_98DXC323_CNS:                         \
    case CPSS_98DX3243_CNS:                         \
    case CPSS_98DX3244_CNS:                         \
    case CPSS_98DX3245_CNS:                         \
    case CPSS_98DX3246_CNS:                         \
    case CPSS_98DX3247_CNS:                         \
    case CPSS_98DXH201_CNS:                         \
    case CPSS_98DX223S_CNS:                         \
    case CPSS_98DX224S_CNS:                         \
    case CPSS_98DX225S_CNS:                         \
    case CPSS_98DX226S_CNS:                         \
    case CPSS_98DX233S_CNS:                         \
    case CPSS_98DX234S_CNS:                         \
    case CPSS_98DX235S_CNS:                         \
    case CPSS_98DX236S_CNS:                         \
    case CPSS_98DX333S_CNS:                         \
    case CPSS_98DX334S_CNS:                         \
    case CPSS_98DX335S_CNS:                         \
    case CPSS_98DX336S_CNS:                         \
    case CPSS_98DXC336_CNS:                         \
    case CPSS_98DXC334_CNS:                         \
    case CPSS_98DXC333_CNS:                         \
    case CPSS_98DX215S_CNS:                         \
    case CPSS_98DX216S_CNS:                         \
    case CPSS_98DXH201_1_CNS:                       \
    case CPSS_98DX336E_CNS:                         \
    case CPSS_98DX336R_CNS  /*caller end with ':' */

#define PRV_CPSS_DXCH_XCAT3_FE_DEVICES_CASES_MAC    \
    /*caller start with 'case' */                   \
         CPSS_98DX1233_CNS:                         \
    case CPSS_98DX1235_CNS:                         \
    case CPSS_98DX1333_CNS:                         \
    case CPSS_98DX1335_CNS:                         \
    case CPSS_98DX1336_CNS:                         \
    case CPSS_98DX123S_CNS:                         \
    case CPSS_98DX125S_CNS  /*caller end with ':' */


/* xCat3 all devices case */
#define PRV_CPSS_DXCH_XCAT3_DEVICES_CASES_MAC                       \
    /*caller start with 'case' */                                   \
    PRV_CPSS_DXCH_XCAT3_FE_DEVICES_CASES_MAC:                   \
    case PRV_CPSS_DXCH_XCAT3_GE_DEVICES_CASES_MAC /*caller end with ':' */

/* AC5 with 24GE, 4 stack ports */
#define PRV_CPSS_AC5_24GE_4STACK_PORTS_DEVICES       \
    CPSS_98DX2538_CNS                               ,\
    CPSS_98DX2528_CNS                               ,\
    CPSS_98DX2518_CNS                               ,\
    CPSS_98DX2535_CNS                               ,\
    CPSS_98DX2525_CNS                               ,\
    CPSS_98DX2515_CNS                               ,\
    CPSS_98DXH258_CNS                               ,\
    CPSS_98DXH255_CNS

/* AC5 with 8GE, 4 stack ports */
#define PRV_CPSS_AC5_8GE_4STACK_PORTS_DEVICES        \
    CPSS_98DX2532_CNS                               ,\
    CPSS_98DX2522_CNS                               ,\
    CPSS_98DX2512_CNS                               ,\
    CPSS_98DX2531_CNS                               ,\
    CPSS_98DX2521_CNS                               ,\
    CPSS_98DX2511_CNS                               ,\
    CPSS_98DXH252_CNS                               ,\
    CPSS_98DXH251_CNS                               ,\
    CPSS_98DXC232_CNS

#define PRV_CPSS_DXCH_AC5_24GE_4_DEVICES_CASES_MAC  \
    /*caller start with 'case' */                   \
         CPSS_98DX2538_CNS:                         \
    case CPSS_98DX2528_CNS:                         \
    case CPSS_98DX2518_CNS:                         \
    case CPSS_98DX2535_CNS:                         \
    case CPSS_98DX2525_CNS:                         \
    case CPSS_98DX2515_CNS:                         \
    case CPSS_98DXH258_CNS:                         \
    case CPSS_98DXH255_CNS  /*caller end with ':' */

#define PRV_CPSS_DXCH_AC5_8GE_4_DEVICES_CASES_MAC   \
    /*caller start with 'case' */                   \
         CPSS_98DX2532_CNS:                         \
    case CPSS_98DX2522_CNS:                         \
    case CPSS_98DX2512_CNS:                         \
    case CPSS_98DX2531_CNS:                         \
    case CPSS_98DX2521_CNS:                         \
    case CPSS_98DX2511_CNS:                         \
    case CPSS_98DXH252_CNS:                         \
    case CPSS_98DXH251_CNS:                         \
    case CPSS_98DXC232_CNS  /*caller end with ':' */

/* AC5 all devices case */
#define PRV_CPSS_DXCH_AC5_DEVICES_CASES_MAC                         \
    /*caller start with 'case' */                                   \
         PRV_CPSS_DXCH_AC5_24GE_4_DEVICES_CASES_MAC:                \
    case PRV_CPSS_DXCH_AC5_8GE_4_DEVICES_CASES_MAC  /*caller end with ':' */


/* lion2 devices with port groups 0,1,2,3,4,5,6,7 */
#define    CPSS_LION2_PORT_GROUPS_01234567_CNS   \
    CPSS_98CX8296_CNS                      ,\
    CPSS_98CX8297_CNS                      ,\
    CPSS_98CX8308_CNS                      ,\
    CPSS_98FX9287_CNS                      ,\
    CPSS_98FX9288_CNS                      ,\
    CPSS_98CX8297_1_CNS

/* lion2 Hooper devices with port groups 0,1,2,3 */
#define    CPSS_LION2_HOOPER_PORT_GROUPS_0123_CNS   \
    CPSS_98CX8121_CNS                      ,\
    CPSS_98CX8123_CNS                      ,\
    CPSS_98CX8124_CNS                      ,\
    CPSS_98CX8129_CNS

/* lion2 devices with 3 mini-gop's per port group */
#define    CPSS_LION_2_THREE_MINI_GOPS_DEVICES_CASES_MAC  \
         CPSS_98CX8296_CNS:                                 \
    case CPSS_98CX8308_CNS

/* lion2 devices with 4 mini-gop's per port group */
#define    CPSS_LION_2_FOUR_MINI_GOPS_DEVICES_CASES_MAC   \
         CPSS_98CX8297_CNS:                                 \
    case CPSS_98FX9287_CNS:                                 \
    case CPSS_98FX9288_CNS:                                 \
    case CPSS_98CX8121_CNS:                                 \
    case CPSS_98CX8123_CNS:                                 \
    case CPSS_98CX8124_CNS:                                 \
    case CPSS_98CX8129_CNS:                                 \
    case CPSS_98CX8297_1_CNS /*caller end with ':' */

/* lion2 devices with port groups 0,1,2,3,4,5,6,7 -- for switch-case*/
#define CPSS_LION2_PORT_GROUPS_01234567_DEVICES_CASES_MAC  \
    /*caller start with 'case' */                          \
         CPSS_98CX8296_CNS:                                \
    case CPSS_98CX8297_CNS:                                \
    case CPSS_98CX8308_CNS:                                \
    case CPSS_98FX9287_CNS:                                \
    case CPSS_98FX9288_CNS:                                \
    case CPSS_98CX8297_1_CNS/*caller end with ':' */

/* lion2 Hooper devices with port groups 0,1,2,3 -- for switch-case*/
#define CPSS_LION2_HOOPER_PORT_GROUPS_0123_DEVICES_CASES_MAC  \
    /*caller start with 'case' */                          \
         CPSS_98CX8121_CNS:                                \
    case CPSS_98CX8123_CNS:                                \
    case CPSS_98CX8124_CNS:                                \
    case CPSS_98CX8129_CNS /*caller end with ':' */

/* Bobcat2 devices */
#define PRV_CPSS_BOBCAT2_DEVICES \
    CPSS_98DX42XX_CNS,           \
    CPSS_98DX4251_CNS,           \
    CPSS_98DX4220_CNS,           \
    CPSS_98DX4221_CNS,           \
    CPSS_98DX4222_CNS,           \
    CPSS_98DX4223_CNS,           \
    CPSS_98DX8216_CNS,           \
    CPSS_98DX8219_CNS,           \
    CPSS_98DX8224_CNS,           \
    CPSS_98DX4253_CNS

/* Bobk Caelum devices */
#define PRV_CPSS_BOBK_CAELUM_DEVICES \
    CPSS_98DX42KK_CNS,               \
    CPSS_98DX4203_CNS,               \
    CPSS_98DX4204_CNS,               \
    CPSS_98DX3346_CNS,               \
    CPSS_98DX3345_CNS,               \
    CPSS_98DX4211_CNS,               \
    CPSS_98DX3347_CNS,               \
    CPSS_98DX4210_CNS,               \
    CPSS_98DX4212_CNS,               \
    CPSS_98DX8332_Z0_CNS

/* Bobk Cetus devices */
#define PRV_CPSS_BOBK_CETUS_DEVICES \
    CPSS_98DX4235_CNS,              \
    CPSS_98DX8212_CNS,              \
    CPSS_98DX8208_CNS

/* Aldrin devices */
#define PRV_CPSS_ALDRIN_DEVICES \
    CPSS_98DX8308_CNS,               \
    CPSS_98DX8312_CNS,               \
    CPSS_98DX8315_CNS,               \
    CPSS_98DX8316_CNS,               \
    CPSS_98DX8324_CNS,               \
    CPSS_98DX8332_CNS,               \
    CPSS_98DX3248_CNS,               \
    CPSS_98DX3249_CNS,               \
    CPSS_98DXZ832_CNS,               \
    CPSS_98DXH831_CNS,               \
    CPSS_98DXH832_CNS,               \
    CPSS_98DXH833_CNS,               \
    CPSS_98DXH834_CNS,               \
    CPSS_98DXH835_CNS


/* AC3X devices */
#define PRV_CPSS_AC3X_DEVICES \
    CPSS_98DX3255_CNS,               \
    CPSS_98DX3256_CNS,               \
    CPSS_98DX3257_CNS,               \
    CPSS_98DX3258_CNS,               \
    CPSS_98DX3259_CNS,               \
    CPSS_98DX3265_CNS,               \
    CPSS_98DX3268_CNS

/* Bobk devices */
#define PRV_CPSS_BOBK_DEVICES \
    PRV_CPSS_BOBK_CAELUM_DEVICES,   \
    PRV_CPSS_BOBK_CETUS_DEVICES

/* bobcat2 all devices case */
#define CPSS_BOBCAT2_ALL_DEVICES_CASES_MAC        \
    /*caller start with 'case' */                 \
          CPSS_98DX4251_CNS:                      \
     case CPSS_98DX4220_CNS:                      \
     case CPSS_98DX4221_CNS:                      \
     case CPSS_98DX4222_CNS:                      \
     case CPSS_98DX4223_CNS:                      \
     case CPSS_98DX42XX_CNS:                      \
     case CPSS_98DX8216_CNS:                      \
     case CPSS_98DX8219_CNS:                      \
     case CPSS_98DX8224_CNS:                      \
     case CPSS_98DX4253_CNS    /*caller end with ':' */

/* BobK Caelum devices case */
#define CPSS_BOBK_CAELUM_DEVICES_CASES_MAC    \
    /*caller start with 'case' */                   \
         CPSS_98DX42KK_CNS:                         \
    case CPSS_98DX4203_CNS:                         \
    case CPSS_98DX4204_CNS:                         \
    case CPSS_98DX3346_CNS:                         \
    case CPSS_98DX3345_CNS:                         \
    case CPSS_98DX4211_CNS:                         \
    case CPSS_98DX3347_CNS:                         \
    case CPSS_98DX4210_CNS:                         \
    case CPSS_98DX4212_CNS:                         \
    case CPSS_98DX8332_Z0_CNS /*caller end with ':' */

/* BobK Cetus devices case */
#define CPSS_BOBK_CETUS_DEVICES_CASES_MAC    \
    /*caller start with 'case' */                   \
         CPSS_98DX8208_CNS:                         \
    case CPSS_98DX4235_CNS:                         \
    case CPSS_98DX8212_CNS /*caller end with ':' */

/* Aldrin devices case */
#define CPSS_ALDRIN_DEVICES_CASES_MAC    \
         CPSS_98DX8308_CNS:               \
    case CPSS_98DX8312_CNS:               \
    case CPSS_98DX8315_CNS:               \
    case CPSS_98DX8316_CNS:               \
    case CPSS_98DX8324_CNS:               \
    case CPSS_98DX8332_CNS:               \
    case CPSS_98DX3248_CNS:               \
    case CPSS_98DX3249_CNS:               \
    case CPSS_98DX3255_CNS:               \
    case CPSS_98DX3256_CNS:               \
    case CPSS_98DX3257_CNS:               \
    case CPSS_98DX3258_CNS:               \
    case CPSS_98DX3259_CNS:               \
    case CPSS_98DXZ832_CNS:               \
    case CPSS_98DXH831_CNS:               \
    case CPSS_98DXH832_CNS:               \
    case CPSS_98DXH833_CNS:               \
    case CPSS_98DXH834_CNS:               \
    case CPSS_98DXH835_CNS:               \
    case CPSS_98DX3265_CNS:               \
    case CPSS_98DX3268_CNS/*caller end with ':' */

/* bobk all devices case */
#define CPSS_BOBK_ALL_DEVICES_CASES_MAC             \
    /*caller start with 'case' */                   \
         CPSS_BOBK_CAELUM_DEVICES_CASES_MAC:  \
    case CPSS_BOBK_CETUS_DEVICES_CASES_MAC /*caller end with ':' */

/* xCat3 all devices case */
#define CPSS_XCAT3_ALL_DEVICES_CASES_MAC              \
    /*caller start with 'case' */                    \
         CPSS_98DX1233_CNS:                          \
    case CPSS_98DX1235_CNS:                          \
    case CPSS_98DX3223_1_CNS:                        \
    case CPSS_98DX3224_CNS:                          \
    case CPSS_98DX3225_CNS:                          \
    case CPSS_98DX3226_CNS:                          \
    case CPSS_98DX3233_CNS:                          \
    case CPSS_98DX3234_CNS:                          \
    case CPSS_98DX3235_CNS:                          \
    case CPSS_98DX3236_CNS:                          \
    case CPSS_98DXH333_CNS:                          \
    case CPSS_98DXT323_CNS:                          \
    case CPSS_98DXT321_CNS:                          \
    case CPSS_98DX3243_CNS:                          \
    case CPSS_98DX3244_CNS:                          \
    case CPSS_98DX3245_CNS:                          \
    case CPSS_98DX3246_CNS:                          \
    case CPSS_98DX3247_CNS:                          \
    case CPSS_98DXC323_CNS:                          \
    case CPSS_98DX1333_CNS:                          \
    case CPSS_98DX1335_CNS:                          \
    case CPSS_98DX1336_CNS:                          \
    case CPSS_98DX3333_CNS:                          \
    case CPSS_98DX3334_CNS:                          \
    case CPSS_98DX3335_CNS:                          \
    case CPSS_98DX3336_CNS:                          \
    case CPSS_98DXH201_CNS:                          \
    case CPSS_98DX123S_CNS:                          \
    case CPSS_98DX125S_CNS:                          \
    case CPSS_98DX223S_CNS:                          \
    case CPSS_98DX224S_CNS:                          \
    case CPSS_98DX225S_CNS:                          \
    case CPSS_98DX226S_CNS:                          \
    case CPSS_98DX233S_CNS:                          \
    case CPSS_98DX234S_CNS:                          \
    case CPSS_98DX235S_CNS:                          \
    case CPSS_98DX236S_CNS:                          \
    case CPSS_98DX333S_CNS:                          \
    case CPSS_98DX334S_CNS:                          \
    case CPSS_98DX335S_CNS:                          \
    case CPSS_98DX336S_CNS:                          \
    case CPSS_98DXC336_CNS:                          \
    case CPSS_98DXC334_CNS:                          \
    case CPSS_98DXC333_CNS:                          \
    case CPSS_98DX215S_CNS:                          \
    case CPSS_98DX216S_CNS:                          \
    case CPSS_98DXH201_1_CNS:                        \
    case CPSS_98DX336E_CNS:                          \
    case CPSS_98DX336R_CNS  /*caller end with ':' */

/* xCat3s all devices case */
#define CPSS_XCAT3S_ALL_DEVICES_CASES_MAC            \
    /*caller start with 'case' */                    \
         CPSS_98DX123S_CNS:                          \
    case CPSS_98DX125S_CNS:                          \
    case CPSS_98DX223S_CNS:                          \
    case CPSS_98DX224S_CNS:                          \
    case CPSS_98DX225S_CNS:                          \
    case CPSS_98DX226S_CNS:                          \
    case CPSS_98DX233S_CNS:                          \
    case CPSS_98DX234S_CNS:                          \
    case CPSS_98DX235S_CNS:                          \
    case CPSS_98DX236S_CNS:                          \
    case CPSS_98DX333S_CNS:                          \
    case CPSS_98DX334S_CNS:                          \
    case CPSS_98DX335S_CNS:                          \
    case CPSS_98DX336S_CNS:                          \
    case CPSS_98DX215S_CNS:                          \
    case CPSS_98DX216S_CNS:                          \
    case CPSS_98DXH201_1_CNS:                        \
    case CPSS_98DX336E_CNS:                          \
    case CPSS_98DX336R_CNS/*caller end with ':' */


/* AC5 all devices case */
#define CPSS_AC5_ALL_DEVICES_CASES_MAC                              \
    /*caller start with 'case' */                                   \
         PRV_CPSS_DXCH_AC5_24GE_4_DEVICES_CASES_MAC:                \
    case PRV_CPSS_DXCH_AC5_8GE_4_DEVICES_CASES_MAC  /*caller end with ':' */


/* Bobcat3 devices */
#define PRV_CPSS_BOBCAT3_ALL_DEVICES \
    CPSS_98CX8410_CNS,               \
    CPSS_98CX8420_CNS,               \
    CPSS_98CX8405_CNS,               \
    CPSS_98CX8420_GM_USED_CNS,       \
    CPSS_98DX8572_CNS

/* Bobcat3 all devices case */
#define CPSS_BOBCAT3_ALL_DEVICES_CASES_MAC          \
    /*caller start with 'case' */                   \
         CPSS_98CX8410_CNS :                        \
    case CPSS_98CX8420_CNS :                        \
    case CPSS_98CX8405_CNS :                        \
    case CPSS_98CX8420_GM_USED_CNS:                 \
    case CPSS_98DX8572_CNS /*caller end with ':' */

/* ARMSTRONG devices */
#define PRV_CPSS_ARMSTRONG_ALL_DEVICES \
    CPSS_98EX5410_CNS,                 \
    CPSS_98EX5420_CNS,                 \
    CPSS_98EX5422_CNS,                 \
    CPSS_98EX5424_CNS,                 \
    CPSS_98EX5421_CNS,                 \
    CPSS_98EX5430_CNS,                 \
    CPSS_98EX5431_CNS,                 \
    CPSS_98EX5432_CNS

/* ARMSTRONG all devices case */
#define CPSS_ARMSTRONG_ALL_DEVICES_CASES_MAC        \
    /*caller start with 'case' */                   \
         CPSS_98EX5410_CNS:                         \
    case CPSS_98EX5420_CNS:                         \
    case CPSS_98EX5422_CNS:                         \
    case CPSS_98EX5424_CNS:                         \
    case CPSS_98EX5421_CNS:                         \
    case CPSS_98EX5430_CNS:                         \
    case CPSS_98EX5431_CNS:                         \
    case CPSS_98EX5432_CNS/*caller end with ':' */

/* ALDRIN2 devices 72 ports */
#define PRV_CPSS_ALDRIN2_72_PORTS_DEVICES \
    CPSS_98EX5520_CNS, \
    CPSS_98DX8448_CNS, \
    CPSS_98DX8548_CNS, \
    CPSS_98DX8548_H_CNS, \
    CPSS_98DX8648_CNS

/* ALDRIN2 devices 64 ports */
#define PRV_CPSS_ALDRIN2_64_PORTS_DEVICES \
    CPSS_98DX4310_CNS

/* ALDRIN2 devices 48 ports */
#define PRV_CPSS_ALDRIN2_48_PORTS_DEVICES \
    CPSS_98EX5524_CNS,  \
    CPSS_98DX8524_CNS,  \
    CPSS_98DX8410_CNS

/* ALDRIN2 devices 24 ports */
#define PRV_CPSS_ALDRIN2_24_PORTS_DEVICES \
    CPSS_98DX8525_CNS

/* ALDRIN2 devices 16 ports */
#define PRV_CPSS_ALDRIN2_16_PORTS_DEVICES \
    CPSS_98DX8515_CNS

/* ALDRIN2 all devices */
#define PRV_CPSS_ALDRIN2_ALL_DEVICES        \
    PRV_CPSS_ALDRIN2_72_PORTS_DEVICES,      \
    PRV_CPSS_ALDRIN2_64_PORTS_DEVICES,      \
    PRV_CPSS_ALDRIN2_48_PORTS_DEVICES,      \
    PRV_CPSS_ALDRIN2_24_PORTS_DEVICES,      \
    PRV_CPSS_ALDRIN2_16_PORTS_DEVICES

/* Falcon devices */
#define PRV_CPSS_FALCON_ALL_DEVICES \
    CPSS_98CX8513_CNS       ,\
    CPSS_98CX8520_CNS       ,\
    CPSS_98CX8525_CNS       ,\
    CPSS_98CX8540_CNS       ,\
    CPSS_98CX8540_H_CNS     ,\
    CPSS_98CX8580_10_CNS    ,\
    CPSS_98CX8580_CNS       ,\
    CPSS_98CX8580_E_CNS     ,\
    CPSS_98CX8550_CNS       ,\
    CPSS_98CX8522_CNS       ,\
    CPSS_98CX8542_CNS       ,\
    CPSS_98CX8530_CNS       ,\
    CPSS_98CX8535_CNS       ,\
    CPSS_98CX8535_H_CNS     ,\
    CPSS_98CX8512_CNS       ,\
    CPSS_98CX8514_CNS       ,\
    CPSS_98EX5610_CNS       ,\
    CPSS_98EX5614_CNS       ,\
    CPSS_98EX5630_CNS

/* Falcon all devices case : limited values only for PEX recognition !  */
#define CPSS_FALCON_ON_PEX_ALL_DEVICES_CASES_MAC     \
    /*caller start with 'case' */                    \
         CPSS_FALCON_ON_PEX_CNS /*caller end with ':' */


/* AC5P 98DX4504 device */
#define PRV_CPSS_AC5P_98DX4504_DEVICE \
    CPSS_98DX4504_CNS,  \
    CPSS_98DX4504M_CNS

/* AC5P 98DX7324 device */
#define PRV_CPSS_AC5P_98DX7324_DEVICE \
    CPSS_98DX7324_CNS,      \
    CPSS_98DX7324M_CNS

/* AC5P common devices */
#define PRV_CPSS_AC5P_COMMON_DEVICES \
    CPSS_98DX4510_CNS,      \
    CPSS_98DX4510M_CNS,     \
    CPSS_98DX4530_CNS,      \
    CPSS_98DX4530M_CNS,     \
    CPSS_98DX4550_CNS,      \
    CPSS_98DX4550M_CNS,     \
    CPSS_98DX4570_CNS,      \
    CPSS_98DX4570M_CNS,     \
    CPSS_98DX7325_CNS,      \
    CPSS_98DX7325M_CNS,     \
    CPSS_98DXC725_CNS

/* AC5P devices with extended memories */
#define PRV_CPSS_AC5P_EXTENDED_DEVICES \
    CPSS_98DX9410_CNS,      \
    CPSS_98DX4580_CNS,      \
    CPSS_98DX4580M_CNS,     \
    CPSS_98DX4590_CNS,      \
    CPSS_98DX4590M_CNS,     \
    CPSS_98DX4590_H_CNS,    \
    CPSS_98DX4590M_H_CNS,   \
    CPSS_98DX4595_CNS,      \
    CPSS_98DX4595M_CNS,     \
    CPSS_98EX5604_CNS,      \
    CPSS_98EX5604M_CNS,     \
    CPSS_98DX7332_CNS,      \
    CPSS_98DX7332M_CNS,     \
    CPSS_98DX7335_CNS,      \
    CPSS_98DX7335M_CNS,     \
    CPSS_98DX7335_H_CNS,    \
    CPSS_98DX7335M_H_CNS

/* AC5P-XL all devices case */
#define CPSS_AC5P_XL_DEVICES_CASES_MAC         \
    /*caller start with 'case' */              \
         CPSS_98DX9410_CNS             :       \
    case CPSS_98DX4570_CNS             :       \
    case CPSS_98DX4570M_CNS            :       \
    case CPSS_98DX4580_CNS             :       \
    case CPSS_98DX4580M_CNS            :       \
    case CPSS_98DX4590_CNS             :       \
    case CPSS_98DX4590M_CNS            :       \
    case CPSS_98DX4590_H_CNS           :       \
    case CPSS_98DX4590M_H_CNS          :       \
    case CPSS_98DX4595_CNS             :       \
    case CPSS_98DX4595M_CNS            :       \
    case CPSS_98DX7332_CNS             :       \
    case CPSS_98DX7332M_CNS            :       \
    case CPSS_98DX7335_CNS             :       \
    case CPSS_98DX7335M_CNS            :       \
    case CPSS_98DX7335_H_CNS           :       \
    case CPSS_98DX7335M_H_CNS /*caller end with ':' */

/* AC5X devices */
#define PRV_CPSS_AC5X_ALL_DEVICES \
    CPSS_98DX3500_CNS,  \
    CPSS_98DX3501_CNS,  \
    CPSS_98DX3510_CNS,  \
    CPSS_98DX3511_CNS,  \
    CPSS_98DX3510_H_CNS,\
    CPSS_98DX3510M_H_CNS,\
    CPSS_98DX3520_CNS,  \
    CPSS_98DX3530_CNS,  \
    CPSS_98DX3530_H_CNS,  \
    CPSS_98DX3530M_H_CNS,  \
    CPSS_98DX3540_CNS,  \
    CPSS_98DX3550_CNS,  \
    CPSS_98DX3500M_CNS, \
    CPSS_98DX3501M_CNS, \
    CPSS_98DX3510M_CNS, \
    CPSS_98DX3520M_CNS, \
    CPSS_98DX3530M_CNS, \
    CPSS_98DX3540M_CNS, \
    CPSS_98DX3550M_CNS, \
    CPSS_98DX7312_CNS , \
    CPSS_98DX7312M_CNS, \
    CPSS_98DX7308_CNS , \
    CPSS_98DX7308M_CNS, \
    CPSS_98DXC712_CNS , \
    CPSS_98DXC708_CNS

/* AC5X devices with reduced exact match table */
#define PRV_CPSS_AC5X_EM_REDUCED_DEVICES \
         CPSS_98DX3500_CNS:              \
    case CPSS_98DX3501_CNS:              \
    case CPSS_98DX3510_CNS:              \
    case CPSS_98DX3511_CNS:              \
    case CPSS_98DX3510_H_CNS:            \
    case CPSS_98DX3510M_H_CNS:           \
    case CPSS_98DX3520_CNS:              \
    case CPSS_98DX3530_CNS:              \
    case CPSS_98DX3530_H_CNS:            \
    case CPSS_98DX3530M_H_CNS:           \
    case CPSS_98DX3500M_CNS:             \
    case CPSS_98DX3501M_CNS:             \
    case CPSS_98DX3510M_CNS:             \
    case CPSS_98DX3520M_CNS:             \
    case CPSS_98DX3530M_CNS:             \
    case CPSS_98DX7308_CNS :             \
    case CPSS_98DX7308M_CNS:             \
    case CPSS_98DXC708_CNS  /*caller end with ':' */

/* AC5X devices with reduced exact match table */
#define PRV_CPSS_AC5X_TCAM_REDUCED_DEVICES \
         CPSS_98DX3501_CNS:              \
    case CPSS_98DX3501M_CNS:             \
    case CPSS_98DX7308_CNS :             \
    case CPSS_98DX7308M_CNS:             \
    case CPSS_98DXC708_CNS  /*caller end with ':' */

/* AC5X all devices case : limited values only for PEX recognition !  */
#define CPSS_AC5X_ALL_DEVICES_CASES_MAC     \
         CPSS_98DX3500_CNS:  \
    case CPSS_98DX3501_CNS:  \
    case CPSS_98DX3510_CNS:  \
    case CPSS_98DX3511_CNS:  \
    case CPSS_98DX3510_H_CNS:   \
    case CPSS_98DX3510M_H_CNS:  \
    case CPSS_98DX3520_CNS:  \
    case CPSS_98DX3530_CNS:  \
    case CPSS_98DX3530_H_CNS:   \
    case CPSS_98DX3530M_H_CNS:  \
    case CPSS_98DX3540_CNS:  \
    case CPSS_98DX3550_CNS:  \
    case CPSS_98DX3500M_CNS: \
    case CPSS_98DX3501M_CNS: \
    case CPSS_98DX3510M_CNS: \
    case CPSS_98DX3520M_CNS: \
    case CPSS_98DX3530M_CNS: \
    case CPSS_98DX3540M_CNS: \
    case CPSS_98DX3550M_CNS: \
    case CPSS_98DX7312_CNS:  \
    case CPSS_98DX7312M_CNS: \
    case CPSS_98DX7308_CNS:  \
    case CPSS_98DX7308M_CNS: \
    case CPSS_98DXC712_CNS:  \
    case CPSS_98DXC708_CNS  /*caller end with ':' */

/* Harrier devices */
#define PRV_CPSS_HARRIER_ALL_DEVICES \
    CPSS_98DXC720_CNS ,\
    CPSS_98DXC721_CNS ,\
    CPSS_98DX7320_CNS ,\
    CPSS_98DX7321_CNS ,\
    CPSS_98DX7320M_CNS ,\
    CPSS_98DX7321M_CNS ,\
    CPSS_98CN106xxS_CNS

/*  Ironman devices with integrated PHY */
#define PRV_CPSS_IRONMAN_M_DEVICES      \
    CPSS_98DX1507_CNS,                  \
    CPSS_98DX1507M_CNS,                 \
    CPSS_98DX1508_CNS,                  \
    CPSS_98DX1508M_CNS

/*  Ironman devices without integrated PHY */
#define PRV_CPSS_IRONMAN_L_DEVICES      \
    CPSS_98DXA010_CNS,                  \
    CPSS_98DXA000_CNS,                  \
    CPSS_98DX1516_CNS ,                 \
    CPSS_98DX1516M_CNS,                 \
    CPSS_98DX1518_CNS ,                 \
    CPSS_98DX1518M_CNS,                 \
    CPSS_98DX1528_CNS ,                 \
    CPSS_98DX1528M_CNS,                 \
    CPSS_98DX1538_CNS ,                 \
    CPSS_98DX1538M_CNS,                 \
    CPSS_98DX1548_CNS ,                 \
    CPSS_98DX1548M_CNS

#define PRV_CPSS_IRONMAN_DEVICES        \
    PRV_CPSS_IRONMAN_M_DEVICES,         \
    PRV_CPSS_IRONMAN_L_DEVICES

/*  Ironman AC5Y devices with integrated PHY */
#define PRV_CPSS_AC5Y_M_DEVICES         \
    CPSS_98DX2548_CNS,                  \
    CPSS_98DX2548M_CNS

/*  Ironman AC5Y devices without integrated PHY */
#define PRV_CPSS_AC5Y_L_DEVICES         \
    CPSS_98DXC254_CNS ,                 \
    CPSS_98DX2556_CNS ,                 \
    CPSS_98DX2556M_CNS,                 \
    CPSS_98DX2558_CNS ,                 \
    CPSS_98DX2558M_CNS,                 \
    CPSS_98DX2568_CNS ,                 \
    CPSS_98DX2568M_CNS,                 \
    CPSS_98DX2578_CNS ,                 \
    CPSS_98DX2578M_CNS,                 \
    CPSS_98DX2588_CNS ,                 \
    CPSS_98DX2588M_CNS

#define PRV_CPSS_AC5Y_DEVICES           \
    PRV_CPSS_AC5Y_M_DEVICES,            \
    PRV_CPSS_AC5Y_L_DEVICES


/* Ironman devices */
#define PRV_CPSS_IRONMAN_ALL_DEVICES    \
    CPSS_98DXA010_CNS,                  \
    CPSS_98DXA000_CNS,                  \
    PRV_CPSS_IRONMAN_DEVICES,           \
    PRV_CPSS_AC5Y_DEVICES

#define CPSS_IRONMAN_DEVICES_CASES_MAC              \
    /*caller start with 'case' */                   \
         CPSS_98DXA000_CNS  :                       \
    case CPSS_98DXA010_CNS  :                       \
    case CPSS_98DX1507_CNS  :                       \
    case CPSS_98DX1507M_CNS :                       \
    case CPSS_98DX1508_CNS  :                       \
    case CPSS_98DX1508M_CNS :                       \
    case CPSS_98DX1516_CNS  :                       \
    case CPSS_98DX1516M_CNS :                       \
    case CPSS_98DX1518_CNS  :                       \
    case CPSS_98DX1518M_CNS :                       \
    case CPSS_98DX1528_CNS  :                       \
    case CPSS_98DX1528M_CNS :                       \
    case CPSS_98DX1538_CNS  :                       \
    case CPSS_98DX1538M_CNS :                       \
    case CPSS_98DX1548_CNS  :                       \
    case CPSS_98DX1548M_CNS   /*caller end with ':' */

#define CPSS_AC5Y_DEVICES_CASES_MAC                 \
    /*caller start with 'case' */                   \
         CPSS_98DX2548_CNS  :                       \
    case CPSS_98DX2548M_CNS :                       \
    case CPSS_98DX2556_CNS  :                       \
    case CPSS_98DX2556M_CNS :                       \
    case CPSS_98DX2558_CNS  :                       \
    case CPSS_98DX2558M_CNS :                       \
    case CPSS_98DX2568_CNS  :                       \
    case CPSS_98DX2568M_CNS :                       \
    case CPSS_98DX2578_CNS  :                       \
    case CPSS_98DX2578M_CNS :                       \
    case CPSS_98DX2588_CNS  :                       \
    case CPSS_98DX2588M_CNS :                       \
    case CPSS_98DXC254_CNS  /*caller end with ':' */

/* Ironman all devices case */
#define CPSS_IRONMAN_ALL_DEVICES_CASES_MAC          \
    /*caller start with 'case' */                   \
         CPSS_IRONMAN_DEVICES_CASES_MAC :           \
    case CPSS_AC5Y_DEVICES_CASES_MAC /*caller end with ':' */


/* Ironman L all devices case */
#define CPSS_IRONMAN_L_DEVICES_CASES_MAC            \
    /* caller starts with 'case' */                 \
         CPSS_98DXC254_CNS  :                       \
    case CPSS_98DX2556_CNS  :                       \
    case CPSS_98DX2556M_CNS :                       \
    case CPSS_98DX2558_CNS  :                       \
    case CPSS_98DX2558M_CNS :                       \
    case CPSS_98DX2568_CNS  :                       \
    case CPSS_98DX2568M_CNS :                       \
    case CPSS_98DX2578_CNS  :                       \
    case CPSS_98DX2578M_CNS :                       \
    case CPSS_98DX2588_CNS  :                       \
    case CPSS_98DX2588M_CNS :                       \
    case CPSS_98DXA000_CNS  :                       \
    case CPSS_98DXA010_CNS  :                       \
    case CPSS_98DX1516_CNS  :                       \
    case CPSS_98DX1516M_CNS :                       \
    case CPSS_98DX1518_CNS  :                       \
    case CPSS_98DX1518M_CNS :                       \
    case CPSS_98DX1528_CNS  :                       \
    case CPSS_98DX1528M_CNS :                       \
    case CPSS_98DX1538_CNS  :                       \
    case CPSS_98DX1538M_CNS :                       \
    case CPSS_98DX1548_CNS  :                       \
    case CPSS_98DX1548M_CNS  /* caller ends with ':' */


/* Ironman M all devices case */
#define CPSS_IRONMAN_M_DEVICES_CASES_MAC            \
    /* caller starts with 'case' */                 \
         CPSS_98DX2548_CNS  :                       \
    case CPSS_98DX2548M_CNS :                       \
    case CPSS_98DX1507_CNS  :                       \
    case CPSS_98DX1507M_CNS :                       \
    case CPSS_98DX1508_CNS  :                       \
    case CPSS_98DX1508M_CNS  /* caller ends with ':' */


/* AAS devices (single tile) */
#define PRV_CPSS_AAS_ALL_DEVICES \
    CPSS_98DX4180_CNS

/* Seahawk with 2 tiles devices */
#define PRV_CPSS_AAS_2_TILES_ALL_DEVICES \
    CPSS_98DXB100_CNS

/* ALDRIN2 all devices case */
#define CPSS_ALDRIN2_ALL_DEVICES_CASES_MAC    \
    /*caller start with 'case' */             \
         CPSS_98EX5520_CNS:                   \
    case CPSS_98EX5524_CNS:                   \
    case CPSS_98DX8524_CNS:                   \
    case CPSS_98DX8525_CNS:                   \
    case CPSS_98DX8515_CNS:                   \
    case CPSS_98DX8548_CNS:                   \
    case CPSS_98DX8548_H_CNS:                 \
    case CPSS_98DX8648_CNS:                   \
    case CPSS_98DX8448_CNS:                   \
    case CPSS_98DX8410_CNS:                   \
    case CPSS_98DX4310_CNS       /*caller end with ':' */

/* Falcon all devices case */
#define CPSS_FALCON_ALL_DEVICES_CASES_MAC       \
    /*caller start with 'case' */               \
         CPSS_98CX8513_CNS       :              \
    case CPSS_98CX8520_CNS       :              \
    case CPSS_98CX8525_CNS       :              \
    case CPSS_98CX8540_CNS       :              \
    case CPSS_98CX8540_H_CNS     :              \
    case CPSS_98CX8580_10_CNS    :              \
    case CPSS_98CX8580_CNS       :              \
    case CPSS_98CX8580_E_CNS     :              \
    case CPSS_98CX8550_CNS       :              \
    case CPSS_98CX8522_CNS       :              \
    case CPSS_98CX8542_CNS       :              \
    case CPSS_98CX8530_CNS       :              \
    case CPSS_98CX8535_CNS       :              \
    case CPSS_98CX8535_H_CNS     :              \
    case CPSS_98CX8512_CNS       :              \
    case CPSS_98CX8514_CNS       :              \
    case CPSS_98EX5610_CNS       :              \
    case CPSS_98EX5614_CNS       :              \
    case CPSS_98EX5630_CNS /*caller end with ':' */

/* AC5P all devices case */
#define CPSS_AC5P_ALL_DEVICES_CASES_MAC         \
    /*caller start with 'case' */               \
         CPSS_98DX9410_CNS              :       \
    case CPSS_98DX4504_CNS              :       \
    case CPSS_98DX4504M_CNS             :       \
    case CPSS_98DX4510_CNS              :       \
    case CPSS_98DX4510M_CNS             :       \
    case CPSS_98DX4530_CNS              :       \
    case CPSS_98DX4530M_CNS             :       \
    case CPSS_98DX4550_CNS              :       \
    case CPSS_98DX4550M_CNS             :       \
    case CPSS_98DX4570_CNS              :       \
    case CPSS_98DX4570M_CNS             :       \
    case CPSS_98DX4580_CNS              :       \
    case CPSS_98DX4580M_CNS             :       \
    case CPSS_98DX4590_CNS              :       \
    case CPSS_98DX4590M_CNS             :       \
    case CPSS_98DX4590_H_CNS            :       \
    case CPSS_98DX4590M_H_CNS           :       \
    case CPSS_98DX4595_CNS              :       \
    case CPSS_98DX4595M_CNS             :       \
    case CPSS_98EX5604_CNS              :       \
    case CPSS_98EX5604M_CNS             :       \
    case CPSS_98DX7324_CNS              :       \
    case CPSS_98DX7324M_CNS             :       \
    case CPSS_98DX7325_CNS              :       \
    case CPSS_98DX7325M_CNS             :       \
    case CPSS_98DXC725_CNS              :       \
    case CPSS_98DX7332_CNS              :       \
    case CPSS_98DX7332M_CNS             :       \
    case CPSS_98DX7335_CNS              :       \
    case CPSS_98DX7335M_CNS             :       \
    case CPSS_98DX7335_H_CNS            :       \
    case CPSS_98DX7335M_H_CNS /*caller end with ':' */

/* Phoenix all devices case */
#define CPSS_PHOENIX_ALL_DEVICES_CASES_MAC          \
    /*caller start with 'case' */                   \
            CPSS_98DX3500M_CNS              :       \
       case CPSS_98DX3501M_CNS              :       \
       case CPSS_98DX3510M_CNS              :       \
       case CPSS_98DX3520M_CNS              :       \
       case CPSS_98DX3530M_CNS              :       \
       case CPSS_98DX3540M_CNS              :       \
       case CPSS_98DX3550M_CNS              :       \
       case CPSS_98DX3500_CNS               :       \
       case CPSS_98DX3501_CNS               :       \
       case CPSS_98DX3510_CNS               :       \
       case CPSS_98DX3511_CNS               :       \
       case CPSS_98DX3510_H_CNS             :       \
       case CPSS_98DX3510M_H_CNS            :       \
       case CPSS_98DX3520_CNS               :       \
       case CPSS_98DX3530_CNS               :       \
       case CPSS_98DX3530_H_CNS             :       \
       case CPSS_98DX3530M_H_CNS            :       \
       case CPSS_98DX3540_CNS               :       \
       case CPSS_98DX3550_CNS               :       \
       case CPSS_98DX7312_CNS               :       \
       case CPSS_98DX7312M_CNS              :       \
       case CPSS_98DX7308_CNS               :       \
       case CPSS_98DX7308M_CNS              :       \
       case CPSS_98DXC712_CNS               :       \
       case CPSS_98DXC708_CNS /*caller end with ':' */


/* Harrier all devices case */
#define CPSS_HARRIER_ALL_DEVICES_CASES_MAC       \
    /*caller start with 'case' */                \
         CPSS_98DXC720_CNS:                      \
    case CPSS_98DXC721_CNS:                      \
    case CPSS_98DX7320_CNS:                      \
    case CPSS_98DX7321_CNS:                      \
    case CPSS_98DX7320M_CNS:                     \
    case CPSS_98DX7321M_CNS:                     \
    case CPSS_98CN106xxS_CNS /*caller end with ':' */

/* PIPE devices */
#define PRV_CPSS_PIPE_ALL_DEVICES                   \
    CPSS_98PX1008_CNS,                              \
    CPSS_98PX1012_CNS,                              \
    CPSS_98PX1022_CNS,                              \
    CPSS_98PX1024_CNS,                              \
    CPSS_98PX1015_CNS,                              \
    CPSS_98PX1016_CNS

/* PIPE all devices case */
#define CPSS_PIPE_ALL_DEVICES_CASES_MAC             \
    /*caller start with 'case' */                   \
         CPSS_98PX1008_CNS:                         \
    case CPSS_98PX1012_CNS:                         \
    case CPSS_98PX1022_CNS:                         \
    case CPSS_98PX1024_CNS:                         \
    case CPSS_98PX1015_CNS:                         \
    case CPSS_98PX1016_CNS   /*caller end with ':' */


/* check if family is sip5 and above */
#define CPSS_DXCH_ALL_SIP5_FAMILY_MAC(devFamily)                \
       (((devFamily) == CPSS_PP_FAMILY_DXCH_BOBCAT2_E ||        \
         (devFamily) == CPSS_PP_FAMILY_DXCH_BOBCAT3_E ||        \
         (devFamily) == CPSS_PP_FAMILY_DXCH_ALDRIN_E  ||        \
         (devFamily) == CPSS_PP_FAMILY_DXCH_AC3X_E    ||        \
         (devFamily) == CPSS_PP_FAMILY_DXCH_ALDRIN2_E ||        \
         CPSS_DXCH_ALL_SIP6_FAMILY_MAC(devFamily)) ?  1 : 0)

/* check if family is sip6 and above */
#define CPSS_DXCH_ALL_SIP6_FAMILY_MAC(devFamily)                \
       (((devFamily) == CPSS_PP_FAMILY_DXCH_FALCON_E  ||        \
         (devFamily) == CPSS_PP_FAMILY_DXCH_AC5P_E    ||        \
         (devFamily) == CPSS_PP_FAMILY_DXCH_HARRIER_E    ||     \
         (devFamily) == CPSS_PP_FAMILY_DXCH_IRONMAN_E    ||     \
         (devFamily) == CPSS_PP_FAMILY_DXCH_AC5X_E       ||     \
         CPSS_DXCH_ALL_SIP7_FAMILY_MAC(devFamily) ) ?  1 : 0)

/* check if family is sip7 and above */
#define CPSS_DXCH_ALL_SIP7_FAMILY_MAC(devFamily)                \
       (((devFamily) == CPSS_PP_FAMILY_DXCH_AAS_E ) ?  1 : 0)

/* check if family is sip5 and above (for switch-case)*/
#define CPSS_DXCH_ALL_SIP5_FAMILY_CASES_MAC         \
    /*caller start with 'case' */                   \
             CPSS_PP_FAMILY_DXCH_BOBCAT2_E :        \
        case CPSS_PP_FAMILY_DXCH_BOBCAT3_E :        \
        case CPSS_PP_FAMILY_DXCH_ALDRIN_E  :        \
        case CPSS_PP_FAMILY_DXCH_AC3X_E    :        \
        case CPSS_PP_FAMILY_DXCH_ALDRIN2_E :        \
        case CPSS_PP_FAMILY_DXCH_FALCON_E  :        \
        case CPSS_PP_FAMILY_DXCH_AC5P_E    :        \
        case CPSS_PP_FAMILY_DXCH_HARRIER_E :        \
        case CPSS_PP_FAMILY_DXCH_IRONMAN_E :        \
        case CPSS_PP_FAMILY_DXCH_AC5X_E    :        \
        case CPSS_DXCH_ALL_SIP7_FAMILY_CASES_MAC /*caller end with ':' */

/* check if family is sip7 and above (for switch-case)*/
#define CPSS_DXCH_ALL_SIP7_FAMILY_CASES_MAC         \
    /*caller start with 'case' */                   \
             CPSS_PP_FAMILY_DXCH_AAS_E  /*caller end with ':' */

/* AAS devices (single tile) */
#define CPSS_AAS_ALL_DEVICES_CASES_MAC              \
    /*caller start with 'case' */                   \
         CPSS_98DX4180_CNS              /*caller end with ':' */

/* Seahawk with 2 tiles devices */
#define CPSS_AAS_2_TILES_ALL_DEVICES_CASES_MAC              \
    /*caller start with 'case' */                   \
         CPSS_98DXB100_CNS              /*caller end with ':' */

/* Falcon 2T/4T devices case */
#define CPSS_FALCON_2T_4T_PACKAGE_DEVICES_CASES_MAC \
             CPSS_98CX8525_CNS:                     \
        case CPSS_98CX8514_CNS:                     \
        case CPSS_98EX5614_CNS:                     \
        case CPSS_98CX8535_CNS:                     \
        case CPSS_98CX8535_H_CNS  /*caller end with ':' */

#define CPSS_FALCON_REDUCED_2T_4T_3_2T_DEVICES_CASES_MAC         \
    /*caller start with 'case' */                   \
             CPSS_98CX8530_CNS:                     \
        case CPSS_98CX8512_CNS:                     \
        case CPSS_98EX5610_CNS:                     \
        case CPSS_98CX8520_CNS  /*caller end with ':' */

#define CPSS_FALCON_REDUCED_2T_4T_3_2T_DEVICES_CHECK_MAC(deviceId)  \
        (CPSS_98CX8530_CNS == deviceId ||                           \
         CPSS_98CX8512_CNS == deviceId ||                           \
         CPSS_98EX5610_CNS == deviceId ||                           \
         CPSS_98CX8520_CNS == deviceId)

#define CPSS_FALCON_8T_DEVICES_CASES_MAC                            \
    /*caller start with 'case' */                                   \
             CPSS_98CX8550_CNS      /*caller end with ':' */

#define CPSS_AC5X_ALL_DEVICES_CHECK_MAC(deviceId)                    \
        ( CPSS_98DX3500_CNS == deviceId ||                           \
          CPSS_98DX3501_CNS == deviceId ||                           \
          CPSS_98DX3510_CNS == deviceId ||                           \
          CPSS_98DX3511_CNS == deviceId ||                           \
          CPSS_98DX3510_H_CNS == deviceId ||                         \
          CPSS_98DX3510M_H_CNS == deviceId ||                        \
          CPSS_98DX3520_CNS == deviceId ||                           \
          CPSS_98DX3530_CNS == deviceId ||                           \
          CPSS_98DX3530_H_CNS == deviceId ||                         \
          CPSS_98DX3530M_H_CNS == deviceId ||                        \
          CPSS_98DX3540_CNS == deviceId ||                           \
          CPSS_98DX3550_CNS == deviceId ||                           \
          CPSS_98DX3500M_CNS == deviceId ||                          \
          CPSS_98DX3501M_CNS == deviceId ||                          \
          CPSS_98DX3510M_CNS == deviceId ||                          \
          CPSS_98DX3520M_CNS == deviceId ||                          \
          CPSS_98DX3530M_CNS == deviceId ||                          \
          CPSS_98DX3540M_CNS == deviceId ||                          \
          CPSS_98DX3550M_CNS == deviceId ||                          \
          CPSS_98DX7312_CNS == deviceId ||                           \
          CPSS_98DX7312M_CNS == deviceId ||                          \
          CPSS_98DX7308_CNS == deviceId ||                           \
          CPSS_98DX7308M_CNS == deviceId ||                          \
          CPSS_98DXC712_CNS == deviceId ||                           \
          CPSS_98DXC708_CNS == deviceId)

#define CPSS_AC5P_98DX4504_DEVICES_CHECK_MAC(deviceId)               \
        ( CPSS_98DX4504_CNS == deviceId ||                           \
          CPSS_98DX4504M_CNS == deviceId)


#define CPSS_QUIRKS_DXCH_HARRIER_PEX_DEVICES_CHECK_MAC(deviceId)     \
        ( CPSS_98DXC720_CNS == deviceId ||                           \
          CPSS_98DXC721_CNS == deviceId ||                           \
          CPSS_98DX7320_CNS == deviceId ||                           \
          CPSS_98DX7321_CNS == deviceId ||                           \
          CPSS_98DX7320M_CNS == deviceId ||                          \
          CPSS_98DX7321M_CNS == deviceId ||                          \
          CPSS_98CN106xxS_CNS == deviceId)

#define CPSS_QUIRKS_DXCH_IRONMAN_PEX_DEVICES_CHECK_MAC(deviceId)    \
        ( CPSS_98DXA010_CNS  == deviceId ||                         \
          CPSS_98DXA000_CNS  == deviceId ||                         \
          CPSS_98DX1528_CNS  == deviceId ||                         \
          CPSS_98DX1528M_CNS == deviceId ||                         \
          CPSS_98DX2568_CNS  == deviceId ||                         \
          CPSS_98DX2568M_CNS == deviceId ||                         \
          CPSS_98DX1518_CNS  == deviceId ||                         \
          CPSS_98DX1518M_CNS == deviceId ||                         \
          CPSS_98DX1538_CNS  == deviceId ||                         \
          CPSS_98DX1538M_CNS == deviceId ||                         \
          CPSS_98DX2558_CNS  == deviceId ||                         \
          CPSS_98DX2558M_CNS == deviceId ||                         \
          CPSS_98DX2578_CNS  == deviceId ||                         \
          CPSS_98DX2578M_CNS == deviceId ||                         \
          CPSS_98DX1516_CNS  == deviceId ||                         \
          CPSS_98DX1516M_CNS == deviceId ||                         \
          CPSS_98DX2556_CNS  == deviceId ||                         \
          CPSS_98DX2556M_CNS == deviceId ||                         \
          CPSS_98DX1548_CNS  == deviceId ||                         \
          CPSS_98DX1548M_CNS == deviceId ||                         \
          CPSS_98DX2588_CNS  == deviceId ||                         \
          CPSS_98DX2588M_CNS == deviceId ||                         \
          CPSS_98DX1507_CNS  == deviceId ||                         \
          CPSS_98DX1507M_CNS == deviceId ||                         \
          CPSS_98DX1508_CNS  == deviceId ||                         \
          CPSS_98DX1508M_CNS == deviceId ||                         \
          CPSS_98DX2548_CNS  == deviceId ||                         \
          CPSS_98DX2548M_CNS == deviceId ||                         \
          CPSS_98DXC254_CNS  == deviceId)

/* specific error codes */
#define CPSS_PRESTERA_ERROR_BASE_CNS  0x10000

/* support running from the PSS */
#ifndef __gtTypesh

#define GT_HW_ERROR         (CPSS_PRESTERA_ERROR_BASE_CNS | (0x17))/* Hardware error*/
/* Transmit operation not succeeded */
#define GT_TX_ERROR         (CPSS_PRESTERA_ERROR_BASE_CNS | (0x18))
/* Receive operation not succeeded  */
#define GT_RCV_ERROR        (CPSS_PRESTERA_ERROR_BASE_CNS | (0x19))
/* Re-perform the interrupt handling */
#define GT_REDO             (CPSS_PRESTERA_ERROR_BASE_CNS | (0x1E))
/* PP memory allocation failed.          */
#define GT_OUT_OF_PP_MEM    (CPSS_PRESTERA_ERROR_BASE_CNS | (0x1D))
/* interrupts cannot be processed and should not be unmasked */
#define GT_STOP_INT         (CPSS_PRESTERA_ERROR_BASE_CNS | (0x1F))

/* support running from the PSS */
#endif /* ! defined __gtTypesh */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif   /* __cpssTypesh */

