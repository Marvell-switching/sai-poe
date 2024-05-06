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
* @file gtGenTypes.h
*
* @note -- next comments relevant for the system that manipulate the CPSS via
* the PSS
* 1. This file name remain gtGenTypes.h (like on PSS)
* 2. This file remain with __gtGenTypesh deliberately in order to be
* duplicate with the PSS --> allowing to call the CPSS from the PSS
* without any compiler warnings
* 3. This file need to be synchronized with the one in the PSS in order
* to get correct behavior (not depended on the order of
* #include <...H file> from CPSS and PSS)
* 4. make sure to replace the #include to:
* #include <extServices/os/gtOs/gtEnvDep.h>
*
*
* @version   18
********************************************************************************
*/

#ifndef __gtGenTypesh
#define __gtGenTypesh

#include <h/ipc/gtEnvDep.h>

#define SHARED_MEMORY 1

typedef GT_UINTPTR CPSS_OS_FILE;
#define CPSS_OS_FILE_INVALID 0
#define CPSS_OS_FILE_STDOUT  1
#define CPSS_OS_FILE_STDERR  2
#define CPSS_OS_FILE_REGULAR 3
#define CPSS_OS_FILE_RAMFS   4

typedef struct CPSS_OS_FILE_TYPE_STC
{
    CPSS_OS_FILE fd;      /* file descriptor */
    CPSS_OS_FILE type;    /* file type */
    GT_VOID     *param;   /* implementation specific fs opaque parameter */
}CPSS_OS_FILE_TYPE_STC;



#ifndef __FUNCTION__
/* __func__ is even newer option can't use it */
#define __FUNCTION__ ""
#endif

/* The gcc is compild with -ansi that is inline is not supported the __inline__ is gcc alternative */
/* The prev #ifdef _VXWORKS has nothing to with it */
#ifndef GT_INLINE
# ifdef __GNUC__
#  define GT_INLINE __inline__
# else
#  ifdef _DIAB_TOOL
#   define GT_INLINE
#  else
#   define GT_INLINE
#  endif
# endif
#endif

#ifndef GT_PACKED
#ifdef __GNUC__
#define GT_PACKED __attribute__ ((packed))
#endif

/* override for VXWORKS && CPU == PPC603 */
#ifdef _VXWORKS
#if (CPU==PPC603)
#undef GT_PACKED
#endif
#endif
#endif

/* all other cases */
#ifndef GT_PACKED
#define GT_PACKED
#endif

#if !defined(GT_UNUSED) && defined(__GNUC__)
# define GT_UNUSED __attribute__ ((unused))
#endif
#ifndef GT_UNUSED
# define GT_UNUSED
#endif


#ifndef NULL
#define NULL ((void*)0)
#endif

#undef IN
#define IN
#undef OUT
#define OUT
#undef INOUT
#define INOUT

#if (!defined(__KERNEL__) && !defined(KERNEL) && !defined(INKERNEL) && !defined(_KERNEL) && !defined(MV_HWS_REDUCED_BUILD))
    typedef void          (*GT_VOIDFUNCPTR) (); /* ptr to function returning void */
    typedef unsigned int  (*GT_INTFUNCPTR)  (); /* ptr to function returning int  */
    typedef void          (*GT_VOIDINTFUNCPTR) (int);/* ptr to function returning void */
#else
    typedef void          (*GT_VOIDFUNCPTR) (void); /* ptr to function returning void */
    typedef unsigned int  (*GT_INTFUNCPTR)  (void); /* ptr to function returning int  */
    typedef void          (*GT_VOIDINTFUNCPTR) (int);/* ptr to function returning void */
#endif
/* memory free function: param is ptr, returns void */
typedef void (*GT_MEMFREEFUNCPTR) (IN GT_VOID* const memblock);


/**
* @enum GT_COMP_RES
 *
 * @brief Values to be returned by compare function
*/
typedef enum{

    GT_EQUAL   = 0,

    GT_GREATER = 1,

    GT_SMALLER = 2

} GT_COMP_RES;


typedef unsigned int GT_STATUS;

/***** generic return codes **********************************/
#define GT_ERROR                 (-1)
#define GT_OK                    (0x00) /* Operation succeeded */
#define GT_FAIL                  (0x01) /* Operation failed    */

#define GT_BAD_VALUE             (0x02) /* Illegal value        */
#define GT_OUT_OF_RANGE          (0x03) /* Value is out of range*/
#define GT_BAD_PARAM             (0x04) /* Illegal parameter in function called  */
#define GT_BAD_PTR               (0x05) /* Illegal pointer value                 */
#define GT_BAD_SIZE              (0x06) /* Illegal size                          */
#define GT_BAD_STATE             (0x07) /* Illegal state of state machine        */
#define GT_SET_ERROR             (0x08) /* Set operation failed                  */
#define GT_GET_ERROR             (0x09) /* Get operation failed                  */
#define GT_CREATE_ERROR          (0x0A) /* Fail while creating an item           */
#define GT_NOT_FOUND             (0x0B) /* Item not found                        */
#define GT_NO_MORE               (0x0C) /* No more items found                   */
#define GT_NO_SUCH               (0x0D) /* No such item                          */
#define GT_TIMEOUT               (0x0E) /* Time Out                              */
#define GT_NO_CHANGE             (0x0F) /* The parameter is already in this value*/
#define GT_NOT_SUPPORTED         (0x10) /* This request is not support           */
#define GT_NOT_IMPLEMENTED       (0x11) /* This request is not implemented       */
#define GT_NOT_INITIALIZED       (0x12) /* The item is not initialized           */
#define GT_NO_RESOURCE           (0x13) /* Resource not available (memory ...)   */
#define GT_FULL                  (0x14) /* Item is full (Queue or table etc...)  */
#define GT_EMPTY                 (0x15) /* Item is empty (Queue or table etc...) */
#define GT_INIT_ERROR            (0x16) /* Error occurred while INIT process     */
#define GT_NOT_READY             (0x1A) /* The other side is not ready yet       */
#define GT_ALREADY_EXIST         (0x1B) /* Tried to create existing item         */
#define GT_OUT_OF_CPU_MEM        (0x1C) /* Cpu memory allocation failed.         */
#define GT_ABORTED               (0x1D) /* Operation has been aborted.           */
#define GT_NOT_APPLICABLE_DEVICE (0x1E) /* API not applicable to device , can
                                           be returned only on devNum parameter  */
#define GT_UNFIXABLE_ECC_ERROR   (0x1F) /* the CPSS detected ECC error that can't
                                           be fixed when reading from the memory which is protected by ECC.
                                           NOTE: relevant only when the table resides in the CSU ,
                                           the ECC is used , and the CPSS emulates the ECC detection
                                           and correction for 'Read entry' operations */
#define GT_UNFIXABLE_BIST_ERROR  (0x20) /* Built-in self-test detected unfixable error */
#define GT_CHECKSUM_ERROR        (0x21) /* checksum doesn't fits received data */
#define GT_DSA_PARSING_ERROR     (0x22) /* DSA tag parsing error */
#define GT_TX_RING_ERROR         (0x23) /* TX descriptors ring broken            */
#define GT_NOT_ALLOWED           (0x24) /* The operation is not allowed          */
#define GT_HW_ERROR_NEED_RESET   (0x25) /* There was HW error that requires HW reset (soft/hard) */
#define GT_LEARN_LIMIT_PORT_ERROR               (0x26)/* FDB manager - learn limit on port reached  */
#define GT_LEARN_LIMIT_TRUNK_ERROR              (0x27)/* FDB manager - learn limit on trunk reached */
#define GT_LEARN_LIMIT_GLOBAL_EPORT_ERROR       (0x28)/* FDB manager - learn limit on global eport reached */
#define GT_LEARN_LIMIT_FID_ERROR                (0x29)/* FDB manager - learn limit on fid reached   */
#define GT_LEARN_LIMIT_GLOBAL_ERROR             (0x2a)/* FDB manager - learn limit globally reached */
#define GT_SHAPER_GRANULARITY_OUT_OF_RANGE      (0x2b)/* Shaper can not be set to such small granularity within given accuracy*/

/* Define the different memory sizes    */
#define _1KB            (0x400)
#define _2KB            (0x800)
#define _4KB            (0x1000)
#define _6KB            (0x1800)
#define _8KB            (0x2000)
#define _10KB           (0x2800)
#define _16KB           (0x4000)
#define _24KB           (0x6000)
#define _32KB           (0x8000)
#define _64KB           (0x10000)
#define _128KB          (0x20000)
#define _256KB          (0x40000)
#define _512KB          (0x80000)
#define _1MB            (0x100000)
#define _2MB            (0x200000)
#define _3MB            (0x300000)
#define _4MB            (0x400000)
#define _6MB            (0x600000)
#define _8MB            (0x800000)
#define _16MB           (0x1000000)
#define _32MB           (0x2000000)
#define _64MB           (0x4000000)
#define _128MB          (0x8000000)
#define _256MB          (0x10000000)
#define _512MB          (0x20000000)
#define _1GB            (0x40000000)

/* Define the different sizes    */
#ifndef _1K
#define _1K            (0x400)
#endif
#define _2K            (0x800)
#define _3K            (0xC00)
#ifndef _4K
#define _4K            (0x1000)
#endif
#define _5K            (0x1400)
#define _6K            (0x1800)
#define _8K            (0x2000)
#define _9K            (0x2400)
#define _10K           (0x2800)
#define _12K           (0x3000)
#define _13K           (13*_1K)
#define _16K           (0x4000)
#define _24K           (0x6000)
#define _28K           (0x7000)
#define _32K           (0x8000)
#define _36K           (0x9000)
#define _48K           (0xc000)

#ifndef _64K
#define _64K           (0x10000)
#endif

#define _128K          (0x20000)
#ifndef _256K
#define _256K          (0x40000)
#endif

#ifndef _512K
#define _512K          (0x80000)
#endif

#ifndef _1M
#define _1M            (0x100000)
#endif

#ifndef _2M
#define _2M            (0x200000)
#endif

#define _3M            (0x300000)

#ifndef _4M
#define _4M            (0x400000)
#endif

#define _6M            (0x600000)

#ifndef _8M
#define _8M            (0x800000)
#endif

#define _12M           (0xC00000)

#ifndef _16M
#define _16M           (0x1000000)
#endif

#define _24M           (0x1800000)
#define _32M           (0x2000000)

#ifndef _64M
#define _64M           (0x4000000)
#endif

#define _128M          (0x8000000)
#define _256M          (0x10000000)
#define _512M          (0x20000000)
#define _1G            (0x40000000)

/* Define single bit masks.             */
#define BIT_0           (0x1)
#define BIT_1           (0x2)
#define BIT_2           (0x4)
#define BIT_3           (0x8)
#define BIT_4           (0x10)
#define BIT_5           (0x20)
#define BIT_6           (0x40)
#define BIT_7           (0x80)
#define BIT_8           (0x100)
#define BIT_9           (0x200)
#define BIT_10          (0x400)
#define BIT_11          (0x800)
#define BIT_12          (0x1000)
#define BIT_13          (0x2000)
#define BIT_14          (0x4000)
#define BIT_15          (0x8000)
#define BIT_16          (0x10000)
#define BIT_17          (0x20000)
#define BIT_18          (0x40000)
#define BIT_19          (0x80000)
#define BIT_20          (0x100000)
#define BIT_21          (0x200000)
#define BIT_22          (0x400000)
#define BIT_23          (0x800000)
#define BIT_24          (0x1000000)
#define BIT_25          (0x2000000)
#define BIT_26          (0x4000000)
#define BIT_27          (0x8000000)
#define BIT_28          (0x10000000)
#define BIT_29          (0x20000000)
#define BIT_30          (0x40000000)
#define BIT_31          (0x80000000)

#endif   /* __gtGenTypesh */



