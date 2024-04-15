/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\h\common\pdltypes.h.
 *
 * @brief   Declares the pdltypes class
 */

#ifndef __pdlLibpdlibPdlTypesh

#define __pdlLibpdlibPdlTypesh
/**
********************************************************************************
 * @file pdlTypes.h
 * @copyright
 *    (c), Copyright (C) 2023, Marvell International Ltd.
 *    THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.
 *    NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT
 *    OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE
 *    DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.
 *    THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,
 *    IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.
********************************************************************************
 *
 * @brief Platform driver layer - main file
 *
 * @version   1
********************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pdlib/common/pdlLibPrefix.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef LINUX
#ifndef ASIC_SIMULATION
/* differ between code that run on linux HW and code that run on linux WM
   and code that run on windows WM */
#define LINUX_HW
#endif /*ASIC_SIMULATION*/
#endif /*LINUX*/

#include <stdint.h> /* for uintptr_t to support pointer casting to integer in 64 bits */
typedef uintptr_t   UINTPTR;
typedef intptr_t   INTPTR;

/* use PDLIB_UNUSED_PARAM to avoid next compilation errors/warnings       */
/* the CPSS compile GCC with very strict compilation warnings as errors */
/* VC10 : warning C4100: 'resultPtr' : unreferenced formal parameter    */
/* GCC error: unused parameter 'resultPtr' [-Werror=unused-parameter]   */
#define PDLIB_UNUSED_PARAM(x) x = x

#define PDLIB_TO_TEXT(_val) #_val

#define PDLIB_CHECK_STATUS_GEN(__pdlLibpdlStatus, __flagId)                                                                 \
    if (__pdlLibpdlStatus != PDL_OK) {                                                                                  \
        if (__flagId) {                                                                                             \
                prvPdlibStatusDebugLogHdr(__FUNCTION__,__LINE__,__pdlLibpdlStatus,PDL_STATUS_ERROR_PRINT_IDENTIFIER);       \
        }                                                                                                           \
    return __pdlLibpdlStatus;                                                                                           \
    }

#define PDLIB_ASSERT_TRUE_GEN(_condition,  __flagId)                                                                        \
    if (!(_condition) ) {                                                                                           \
        if (__flagId) {                                                                                             \
            prvPdlibStatusDebugLogHdr(PDLIB_TO_TEXT(_condition),__LINE__,PDL_FAIL,PDL_STATUS_ERROR_PRINT_IDENTIFIER);   \
        }                                                                                                           \
        return PDL_FAIL;                                                                                            \
    }

#define PDLIB_CHECK_STATUS(__pdlLibpdlStatus) PDLIB_CHECK_STATUS_GEN(__pdlLibpdlStatus, prvPdlibDebugFlag)
/**************************** Constants definitions *****************************/
/**
 *  @addtogroup Library
 *  @{
 */
/**
 *  @defgroup Types Types
 * @{
 */
#if !defined(_WIN32) && !defined(WIN32)
#include <stdint.h>
/**
 * @typedef int8_t INT_8
 *
 * @brief  singed 8 bit integer
 */

/**
 * @typedef int8_t INT_8
 *
 * @brief   Defines an alias representing the int 8
 */

typedef int8_t   INT_8;

/**
 * @typedef int16_t INT_16
 *
 * @brief  singed 16 bit integer
 */

/**
 * @typedef int16_t INT_16
 *
 * @brief   Defines an alias representing the int 16
 */

typedef int16_t  INT_16;

/**
 * @typedef int32_t INT_32
 *
 * @brief  singed 32 bit integer
 */

/**
 * @typedef int32_t INT_32
 *
 * @brief   Defines an alias representing the int 32
 */

typedef int32_t  INT_32;

/**
 * @typedef uint8_t UINT_8
 *
 * @brief  unsigned 8 bit integer
 */

/**
 * @typedef uint8_t UINT_8
 *
 * @brief   Defines an alias representing the 8
 */

typedef uint8_t  UINT_8;

/**
 * @typedef uint16_t UINT_16
 *
 * @brief  unsigned 16 bit integer
 */

/**
 * @typedef uint16_t UINT_16
 *
 * @brief   Defines an alias representing the 16
 */

typedef uint16_t UINT_16;

/**
 * @typedef uint32_t UINT_32
 *
 * @brief  unsigned 32 bit integer
 */

/**
 * @typedef uint32_t UINT_32
 *
 * @brief   Defines an alias representing the 32
 */

typedef uint32_t UINT_32;

/**
 * @#define PDL_PACKED_STRUCT_START
 *
 * @brief  start of packed structure
 */
#define PDL_PACKED_STRUCT_START

/**
 * @#define PDL_PACKED_STRUCT_END
 *
 * @brief  end of packed structure
 */
#define PDL_PACKED_STRUCT_END __attribute__((packed))

/**
 * @#define PDL_PRAGMA_NOALIGN
 *
 * @brief  start of unaligned declarations
 */
#define PDL_PRAGMA_NOALIGN   _Pragma ("pack(1)")

/**
 * @#define PDL_PRAGMA_ALIGN
 *
 * @brief  end of unaligned declarations
 */
#define PDL_PRAGMA_ALIGN     _Pragma ("pack()")

#else
/**
 * @typedef char INT_8
 *
 * @brief  singed 8 bit integer
 */

/**
 * @typedef char INT_8
 *
 * @brief   Defines an alias representing the int 8
 */

typedef char  INT_8;

/**
 * @typedef short INT_16
 *
 * @brief  singed 16 bit integer
 */

/**
 * @typedef short INT_16
 *
 * @brief   Defines an alias representing the int 16
 */

typedef short INT_16;

/**
 * @typedef long INT_32
 *
 * @brief  singed 32 bit integer
 */

/**
 * @typedef long INT_32
 *
 * @brief   Defines an alias representing the int 32
 */

typedef int  INT_32;

/**
 * @typedef unsigned char UINT_8
 *
 * @brief  unsigned 8 bit integer
 */

/**
 * @typedef unsigned char UINT_8
 *
 * @brief   Defines an alias representing the 8
 */

typedef unsigned char  UINT_8;

/**
 * @typedef unsigned short UINT_16
 *
 * @brief  unsigned 16 bit integer
 */

/**
 * @typedef unsigned short UINT_16
 *
 * @brief   Defines an alias representing the 16
 */

typedef unsigned short UINT_16;

/**
 * @typedef unsigned long UINT_32
 *
 * @brief  unsigned 32 bit integer
 */

/**
 * @typedef unsigned long UINT_32
 *
 * @brief   Defines an alias representing the 32
 */

typedef unsigned int  UINT_32;


/**
 * @#define PDL_PACKED_STRUCT_START
 *
 * @brief  start of packed structure
 */
#define PDL_PACKED_STRUCT_START

/**
 * @#define PDL_PACKED_STRUCT_END
 *
 * @brief  end of packed structure
 */
#if defined(__MINGW64__) || (defined(_WIN64) && !defined(WIN32))
#define PDL_PACKED_STRUCT_END __attribute__((packed))
#else
#define PDL_PACKED_STRUCT_END
#endif

/**
 * @#define PDL_PRAGMA_NOALIGN
 *
 * @brief  start of unaligned declarations
 */
#if defined(__MINGW64__) || (defined(_WIN64) && !defined(WIN32))
#define PDL_PRAGMA_NOALIGN   _Pragma ("pack(1)")
#else
#define PDL_PRAGMA_NOALIGN   __pragma (pack(1))
#endif

/**
 * @#define PDL_PRAGMA_ALIGN
 *
 * @brief  end of unaligned declarations
 */
#if defined(__MINGW64__) || (defined(_WIN64) && !defined(WIN32))
#define PDL_PRAGMA_ALIGN   _Pragma ("pack()")
#else
#define PDL_PRAGMA_ALIGN     __pragma (pack())
#endif
#endif

#ifndef _VISUALC
/**
 * @typedef size_t SIZE_T
 *
 * @brief  memory size
 */
#ifdef _WIN64
typedef unsigned __int64 SIZE_T;
#else
typedef size_t  SIZE_T;
#endif
#endif

/* the 'GT_' types are CPSS types that should not be defined if already exists */
#ifndef __gtEnvDeph

/**
 * @typedef UINT_8 GT_U8
 *
 * @brief  unsigned 8 bit integer
 */

/**
 * @typedef UINT_8 GT_U8
 *
 * @brief   Defines an alias representing the gt u 8
 */

typedef UINT_8          GT_U8;
typedef UINT_16         GT_U16;

/**
 * @typedef UINT_32 GT_U32
 *
 * @brief   Defines an alias representing the gt u 32
 */

typedef UINT_32         GT_U32;
#endif /*__gtEnvDeph*/
/**
 * @typedef UINT_8 BOOLEAN
 *
 * @brief  Boolean definition
 */

/**
 * @typedef UINT_8 BOOLEAN
 *
 * @brief   Defines an alias representing the boolean
 */

typedef UINT_8 BOOLEAN;

#ifdef TRUE
#undef TRUE
#endif

/*! True Value */
#define TRUE  1

#ifdef FALSE
#undef FALSE
#endif

/*! False Value */
#define FALSE 0

/*max error string length*/
#define MAX_PDL_XML_ERROR_CODE_LEN 25


/*identifier for pdl status*/
#define PDL_STATUS_ERROR_PRINT_IDENTIFIER 0

/*identifier for xml status*/
#define XML_STATUS_ERROR_PRINT_IDENTIFIER 1

/* Standard type constant definitions:   */

/*! Max 8 bit unsigned value */
#define MAX_UINT_8           ((UINT_8) 0xFF)

/*! Max 16 bit unsigned value */
#define MAX_UINT_16          ((UINT_16)0xFFFF)

/*! Max 32 bit unsigned value */
#define MAX_UINT_32          ((UINT_32)0xFFFFFFFF)

/*! brief indicates this is an input parameter */
#define IN

/*! indicates this is an output parameter */
#define OUT

/*! indicates this is an input and output parameter */
#define INOUT

/*! Maximum number of Packet Processors */
#define PDL_MAX_PP_NUM              8

/*! 32 bits mask */
#define PDL_MASK_32_BIT             0xFFFFFFFF

#define PDL_ALIGN_ARCH_WORD(_size)   \
            (((_size) + (sizeof(UINTPTR) - 1L)) & ~(sizeof(UINTPTR) - 1L))


/**
 * @typedef unsigned int PDL_STATUS
 *
 * @brief   Defines an alias representing the pdl status
 */

typedef unsigned int PDL_STATUS;

/***** generic return codes **********************************/
/* return codes are equal to CPSS GT_STATUS codes are equal up to 0x1000 after it, PDL specific return code are used */


/*! general error */
#define PDL_ERROR                 (-1)

/*! Operation succeeded */
#define PDL_OK                    (0x00)

/*! Operation failed    */
#define PDL_FAIL                  (0x01)

/*! Illegal value         */
#define PDL_BAD_VALUE             (0x02)

/*! Value is out of range */
#define PDL_OUT_OF_RANGE          (0x03)

/*! Illegal parameter in function called   */
#define PDL_BAD_PARAM             (0x04)

/*! Illegal pointer value                  */
#define PDL_BAD_PTR               (0x05)

/*! Illegal size                           */
#define PDL_BAD_SIZE              (0x06)

/*! Illegal state of state machine         */
#define PDL_BAD_STATE             (0x07)

/*! Set operation failed                   */
#define PDL_SET_ERROR             (0x08)

/*! Get operation failed                   */
#define PDL_GET_ERROR             (0x09)

/*! Fail while creating an item            */
#define PDL_CREATE_ERROR          (0x0A)

/*! Item not found                         */
#define PDL_NOT_FOUND             (0x0B)

/*! No more items found                    */
#define PDL_NO_MORE               (0x0C)

/*! No such item                           */
#define PDL_NO_SUCH               (0x0D)

/*! Time Out                               */
#define PDL_TIMEOUT               (0x0E)

/*! The parameter is already in this value */
#define PDL_NO_CHANGE             (0x0F)

/*! This request is not support            */
#define PDL_NOT_SUPPORTED         (0x10)

/*! This request is not implemented        */
#define PDL_NOT_IMPLEMENTED       (0x11)

/*! The item is not initialized            */
#define PDL_NOT_INITIALIZED       (0x12)

/*! Resource not available (memory ...)    */
#define PDL_NO_RESOURCE           (0x13)

/*! Item is full (Queue or table etc...)   */
#define PDL_FULL                  (0x14)

/*! Item is empty (Queue or table etc...)  */
#define PDL_EMPTY                 (0x15)

/*! Error occurred while INIT process      */
#define PDL_INIT_ERROR            (0x16)

/*! The other side is not ready yet        */
#define PDL_NOT_READY             (0x1A)

/*! Tried to create existing item          */
#define PDL_ALREADY_EXIST         (0x1B)

/*! Cpu memory allocation failed.          */
#define PDL_OUT_OF_CPU_MEM        (0x1C)

/*! Operation has been aborted.            */
#define PDL_ABORTED               (0x1D)

/*! API not applicable to device , can be returned only on devNum parameter  */
#define PDL_NOT_APPLICABLE_DEVICE (0x1E)
/*!  the CPSS detected ECC error that can't
    be fixed when reading from the memory which is protected by ECC.
    NOTE: relevant only when the table resides in the CSU ,
    the ECC is used , and the CPSS emulates the ECC detection
    and correction for 'Read entry' operations */

#define PDL_UNFIXABLE_ECC_ERROR   (0x1F)

/*! Built-in self-test detected unfix able error */
#define PDL_UNFIXABLE_BIST_ERROR  (0x20)

/*! checksum doesn't fits received data */
#define PDL_CHECKSUM_ERROR        (0x21)

/**
 *@note return codes are equal to CPSS GT_STATUS codes are equal up to 0x1000 after it, PDL specific return code are used
*/
/*! XSL parsing error */
#define PDL_XML_PARSE_ERROR       (0x1000)
/*! Memory initialization error */
#define PDL_MEM_INIT_ERROR        (0x1001)
/*! I2C error */
#define PDL_I2C_ERROR             (0x1002)

/*! Maximum length of a tag/field name in XML file */
#define PDL_XML_MAX_TAG_LEN 256

/*! Indicate value present */
#define PDL_FIELD_HAS_VALUE_CNS 1

extern BOOLEAN prvPdlibDebugFlag;
/* @}*/
/* @}*/

#ifdef __cplusplus
}
#endif

#endif
