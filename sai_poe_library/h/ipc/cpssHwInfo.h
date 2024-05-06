/*******************************************************************************
*              (c), Copyright 2016, Marvell International Ltd.                 *
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
* @file cpssHwInfo.h
*
* @brief HW info structure
*
* @version   1
********************************************************************************
*/
#ifndef __cpssHwInfo_h__
#define __cpssHwInfo_h__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <h/ipc/gtGenTypes.h>
#include <h/ipc/cpssHwDriverAPI.h>

/**
* @enum CPSS_HW_INFO_BUS_TYPE_ENT
 *
 * @brief bus type
*/
typedef enum{

    /** not configured yet */
    CPSS_HW_INFO_BUS_TYPE_NONE_E = 0,

    /** PCI */
    CPSS_HW_INFO_BUS_TYPE_PCI_E,

    /** PEX */
    CPSS_HW_INFO_BUS_TYPE_PEX_E,

    /** SMI */
    CPSS_HW_INFO_BUS_TYPE_SMI_E,

    /** @brief MBus. This is an internal bus that
     *  connects internal CPU cores with other
     *  peripherals including Switching Cores
     */
    CPSS_HW_INFO_BUS_TYPE_MBUS_E,

    /** @brief for check
     *  Note:
     *  Don't modify the order or values of this enum.
     */
    CPSS_HW_INFO_BUS_TYPE_MAX_NUM

} CPSS_HW_INFO_BUS_TYPE_ENT;

#ifndef GT_PHYSICAL_ADDR_DEFINED
#if defined(__GNUC__) || defined(_VISUALC)
  typedef unsigned long long GT_PHYSICAL_ADDR;
#else
  typedef GT_UINTPTR GT_PHYSICAL_ADDR;
#endif
#define GT_PHYSICAL_ADDR_DEFINED
#endif

/*
 * typedef: struct CPSS_HW_INFO_RESOURCE_MAPPING_STC
 *
 * Description: Resource mapping info
 *
 * Fields:
 *
 *   start        - virtual address of resource
 *                  0 means resource not configured
 *   size         - resource size in bytes
 *   phys         - physical address.
 *                  For example SRAM physical address can be used
 *                  to configure SDMA transaction to it
 *                  It is also used in translation
 *                  AP/Micro-init address <=> CPSS virt address
 * Comments:
 *
 */
typedef struct CPSS_HW_INFO_RESOURCE_MAPPING_STCT {
    GT_UINTPTR          start;
    GT_UINTPTR          size;
    GT_PHYSICAL_ADDR    phys;
} CPSS_HW_INFO_RESOURCE_MAPPING_STC;

/*
 * typedef: struct CPSS_HW_INFO_STCT
 *
 * Description: HW info structure
 *
 * Fields:
 *
 *   busType                        - physical bus type
 *   hwAddr                         - hardware (bus) address of device
 *                                    PCI/PEX: (busNo,devSel,funcNo)
 *                                    SMI: (-,deviceId,-)
 *                                    MBUS: (0xff,0xff,0xff), PEX compatible
 *      hwAddr.busNo                - PCI/PEX bus number
 *      hwAddr.devSel               - PCI/PEX device number (deviceId for SMI)
 *      hwAddr.funcNo               - PCI/PEX function number
 *
 *   irq                            - assigned interrupts for extDrvIntConnect
 *                                    This value is used to connect irq handler
 *                                    routine with IRQ
 *                                    The value CPSS_PP_INTERRUPT_VECTOR_NOT_USED_CNS
 *                                    means IRQ not configured/not applicable
 *      irq.switching               - Switching Core interrupt
 *      irq.doorbell                - Doorbell interrupt
 *
 *   intMask                        - Interrupt mask. This value is used to
 *                                    mask/unmask interrupt with extDrvIntEnable
 *      intMask.switching           - Interrupt mask for Switching Core
 *
 *   resource                       - assigned resources (iomem)
 *                                    The value 0 in .start means resource
 *                                    is not configured/doesn't exists
 *      resource.cnm                - Control and management
 *                                    (PCI BAR0, internalPciBase)
 *      resource.switching          - switching core
 *      resource.resetAndInitController
 *                                  - Reset And Init controller
 *      resource.sram               - SRAM. When external CPU is used this
 *                                    resoure points to internal cpu's SRAM
 *      resource.mg1                - BC3's MG1 (MG0 is switching)
 *      resource.mg2                - BC3's MG2
 *      resource.mg3                - BC3's MG3
 *      resource.dragonite          - Dragonite resources
 *         resource.dragonite.itcm  - Instruction area
 *         resource.dragonite.dtcm  - Data
 *  driver                          - A pointer to custom driver instance
 *                                    to access device resources
 *                                    or NULL
 *
 * Comments:
 *
 */
typedef struct CPSS_HW_INFO_STCT {
    CPSS_HW_INFO_BUS_TYPE_ENT           busType;
    // struct {
    //     GT_U32                          busNo;
    //     GT_U32                          devSel;
    //     GT_U32                          funcNo;
    // } hwAddr;
    // struct {
    //     GT_U32                          switching;
    //     GT_U32                          doorbell;
    // } irq;
    // struct {
    //     GT_UINTPTR                      switching;
    // } intMask;
    struct {
        // CPSS_HW_INFO_RESOURCE_MAPPING_STC   cnm;
        // CPSS_HW_INFO_RESOURCE_MAPPING_STC   switching;
        // CPSS_HW_INFO_RESOURCE_MAPPING_STC   resetAndInitController;
        CPSS_HW_INFO_RESOURCE_MAPPING_STC   sram;
        // CPSS_HW_INFO_RESOURCE_MAPPING_STC   mg1;
        // CPSS_HW_INFO_RESOURCE_MAPPING_STC   mg2;
        // CPSS_HW_INFO_RESOURCE_MAPPING_STC   mg3;
        // struct {
        //     CPSS_HW_INFO_RESOURCE_MAPPING_STC   itcm;
        //     CPSS_HW_INFO_RESOURCE_MAPPING_STC   dtcm;
        // } dragonite;
    } resource;
    CPSS_HW_DRIVER_STC *driver;
    GT_U8               devNum;
} CPSS_HW_INFO_STC;

/* an empty CPSS_HW_INFO_STC
 * Should be used as initializer:
 *     CPSS_HW_INFO_STC zzz = CPSS_HW_INFO_STC_DEF
 */
#define CPSS_HW_INFO_RESOURCE_STC_DEF 0,0,0
#define CPSS_HW_INFO_STC_DEF                                            \
{                                                                       \
    CPSS_HW_INFO_BUS_TYPE_NONE_E, /* busType                         */ \
    {                                                                   \
        0,                        /* hwAddr.busNo                    */ \
        0,                        /* hwAddr.devSel                   */ \
        0                         /* hwAddr.funcNo                   */ \
    },                                                                  \
    {                                                                   \
        0,                                     /* irq.switching      */ \
        0                                      /* irq.doorbell       */ \
    },                                                                  \
    {                                                                   \
        0                                      /* intMask.switching  */ \
    },                                                                  \
    {                                                                   \
        { CPSS_HW_INFO_RESOURCE_STC_DEF },              /* resource.cnm                    */ \
        { CPSS_HW_INFO_RESOURCE_STC_DEF },              /* resource.switching              */ \
        { CPSS_HW_INFO_RESOURCE_STC_DEF },              /* resource.resetAndInitController */ \
        { CPSS_HW_INFO_RESOURCE_STC_DEF },              /* resource.sram                   */ \
        { CPSS_HW_INFO_RESOURCE_STC_DEF },              /* resource.mg1                    */ \
        { CPSS_HW_INFO_RESOURCE_STC_DEF },              /* resource.mg2                    */ \
        { CPSS_HW_INFO_RESOURCE_STC_DEF },              /* resource.mg3                    */ \
        {                                                               \
            { CPSS_HW_INFO_RESOURCE_STC_DEF },          /* resource.dragonite.itcm         */ \
            { CPSS_HW_INFO_RESOURCE_STC_DEF }           /* resource.dragonite.dtcm         */ \
        }                                                               \
    },                                                                  \
    NULL                          /* driver                          */ ,\
    0 \
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __cpssHwInfo_h__ */

