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
* @file gtEnvDep.h
*
* @note The following preprocessor macros are used to control environment:
* UNIX    - Unix-like OS (Linux, FreeBSD, Solaris, ...)
* LINUX    - Linux
* _FreeBSD
* _VISUALC  - MS Visual C
*
* CPU_LE   - CPU is Little Endian
* CPU_BE   - CPU is Big Endian
*
* IS_64BIT_OS
* __WORDSIZE - if == 64 then application is 64bit
*
* CPU_ARM
* PPC_CPU
* POWERPC_CPU
* MIPS_CPU
* MIPS64_CPU
* INTEL_CPU
* INTEL64_CPU
*
*
*
*
*
* @version   16
********************************************************************************
*/
#ifndef __gtEnvDeph
#define __gtEnvDeph

/*******************************************************************************
********************************************************************************
* PART0: autotetect
********************************************************************************
*******************************************************************************/
#if !defined(UNIX) && (defined(unix) || defined(__unix__))
#  define UNIX
#endif
#if !defined(LINUX) && (defined(linux) || defined(__linux__))
#  define LINUX
#endif
#if !defined(_VISUALC) && (defined(_MSC_VER))
#  define _VISUALC
#endif
#if defined(__BYTE_ORDER__)
#  if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) && !defined(CPU_BE)
#    define CPU_BE
#  endif
#endif
#if defined(_VISUALC)
#  if !defined(IS_64BIT_OS) && defined(_WIN64)
#    define IS_64BIT_OS
#  endif
#endif


/*******************************************************************************
********************************************************************************
* PART1: TYPES
*
* The folling types defined in this section:
*   GT_U8, GT_16, GT_32, GT_U8, GT_U16, GT_U32
*   GT_INTPTR, GT_UINTPTR, GT_PTRDIFF, GT_SIZE_T, GT_SSIZE_T
*   GT_CHAR, GT_CHAR_PTR
*   GT_VOID_PTR
*   GT_PTR
*   GT_U64
*   GT_FLOAT32, GT_FLOAT64
*   GT_BOOL
*
********************************************************************************
*******************************************************************************/

/* In c++ compiler typedef void is not allowed therefore define is used */
#define GT_VOID void

typedef void  *GT_VOID_PTR;
typedef char  GT_CHAR, *GT_CHAR_PTR;

/* Add indication for the simulation to know that GT_CHAR is implimented,
   so the simulation will not define it. */
#define IMPL_GT_CHAR


#if defined(UNIX) || defined(__KERNEL__) || defined(_VISUALC) || defined(__MINGW64__)
/* use system defined types */
#  if defined(UNIX) || defined(__KERNEL__)
#    ifndef __KERNEL__
#      include <inttypes.h>
#      include <stddef.h>
#      include <sys/types.h>
#    else
#      include <linux/version.h>
#      include <linux/types.h>
#      if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)
#        ifndef _UINTPTR_T
#          define _UINTPTR_T
#          ifndef __UINTPTR_TYPE__
             typedef unsigned long uintptr_t;
#          else
             typedef __UINTPTR_TYPE__ uintptr_t;
#          endif
#        endif
#      endif
       typedef uintptr_t intptr_t;
#    endif
#  endif /* defined(UNIX) || defined(__KERNEL__) */
#  if defined(_VISUALC)
#    include <stdint.h>
     typedef intptr_t ssize_t;
#  endif
#  if defined(__MINGW64__)
#     include <stdint.h>
#  endif
typedef int8_t      GT_8,   *GT_8_PTR;
typedef uint8_t     GT_U8,  *GT_U8_PTR;
typedef int16_t     GT_16,  *GT_16_PTR;
typedef uint16_t    GT_U16, *GT_U16_PTR;
typedef int32_t     GT_32,  *GT_32_PTR;
typedef uint32_t    GT_U32,  *GT_U32_PTR;
typedef int64_t     GT_L64;
typedef uint64_t    GT_UL64;
typedef uint32_t    GT_TASK;

typedef intptr_t    GT_INTPTR;
typedef uintptr_t   GT_UINTPTR;
typedef ptrdiff_t   GT_PTRDIFF;
typedef size_t      GT_SIZE_T;
typedef ssize_t     GT_SSIZE_T;
#define __CPSS_BASIC_TYPES_DEFINED
#endif /* defined(UNIX) || defined(__KERNEL__) */



#if !defined(__CPSS_BASIC_TYPES_DEFINED)
/* fallback: not linux/unix/_visualc */
#define VAR_32BIT   int
#define VAR_64BIT   long long

typedef char                GT_8,   *GT_8_PTR;
typedef unsigned char       GT_U8,  *GT_U8_PTR;
typedef short               GT_16,  *GT_16_PTR;
typedef unsigned short      GT_U16, *GT_U16_PTR;
typedef VAR_32BIT           GT_32,  *GT_32_PTR;
typedef unsigned VAR_32BIT  GT_U32, *GT_U32_PTR;
typedef VAR_64BIT           GT_L64;
typedef unsigned VAR_64BIT  GT_UL64;

#ifndef IS_64BIT_OS
typedef VAR_32BIT           GT_INTPTR;
typedef unsigned VAR_32BIT  GT_UINTPTR;
typedef VAR_32BIT           GT_PTRDIFF;
typedef unsigned VAR_32BIT  GT_SIZE_T;
typedef VAR_32BIT           GT_SSIZE_T;
#else /* IS_64BIT_OS */
typedef VAR_64BIT           GT_INTPTR;
typedef unsigned VAR_64BIT  GT_UINTPTR;
typedef VAR_64BIT           GT_PTRDIFF;
typedef unsigned VAR_64BIT  GT_SIZE_T;
typedef VAR_64BIT           GT_SSIZE_T;
#endif /* IS_64BIT_OS */

#define __CPSS_BASIC_TYPES_DEFINED
#endif /* !defined(__CPSS_BASIC_TYPES_DEFINED) */

/* type for strings , allow 'CPSS-API call' to distinguish from other GT_CHAR usages */
typedef char* GT_STRING;

typedef void   *GT_PTR;

typedef struct
{
    GT_U32  l[2];
}GT_U64;

typedef unsigned long long GT_U64_BIT;

/* definitions for floating point types:
 GT_FLOAT32 - Single precision - exponent 8 bits, significand (mantissa) 23 bits
 GT_FLOAT64 - Double precision - exponent 11 bits, significand (mantissa) 52 bits */
typedef float GT_FLOAT32, *GT_FLOAT32_PTR;
typedef double GT_FLOAT64, *GT_FLOAT64_PTR;

/**
* @enum GT_BOOL
 *
 * @brief Enumeration of boolean.
*/
typedef enum{

    /** false. */
    GT_FALSE = 0,

    /** true. */
    GT_TRUE  = 1

} GT_BOOL;


/*******************************************************************************
********************************************************************************
* PART2: compiler related
*
* Disable some warnings for VC
* define VC macro to be used for preprocessor warning
*
********************************************************************************
*******************************************************************************/

#ifdef _VISUALC

/* Disable warning messages for VC W4 warnings level */

/* warning of casting of void * to function's pointer :
warning C4055: 'type cast' :
from data pointer 'void *' to function pointer
         'unsigned int (__cdecl *)(int ,unsigned long ,unsigned long *)'
*/
#pragma warning( disable : 4055 )


/* warning for code like " while(1) {....}":
  warning C4127: conditional expression is constant*/
#pragma warning( disable : 4127 )

/* clear warning on : GT_FLOAT64            txQPort64Bandwidth;
   in PRV_CPSS_MAIN_PP_DRV_MOD_DXCH_PORT_DIR_SHARED_PORT_PA_SRC_GLOBAL_DB

    warning C4121: '<unnamed-tag>' : alignment of a member was sensitive to packing
*/
#pragma warning( disable : 4121 )


/* define macro to be used for preprocessor warning
 * Usage:
 *    #pragma message (__LOC_WARN__ "the warning message")
 */
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC_WARN__ __FILE__ "("__STR1__(__LINE__)") : warning: "


#endif /* _VISUALC */


/*******************************************************************************
********************************************************************************
* PART3: target related
*
* define GT_SYNC
*
********************************************************************************
*******************************************************************************/


/* added macro for memory barrier synchronize   */

#if defined(PPC_CPU) || defined(POWERPC_CPU)
#ifdef __GNUC__
#ifdef _FreeBSD
#define GT_SYNC __asm __volatile (" eieio")
#else
#define GT_SYNC __asm__("   eieio")
#endif
#else
#ifdef _DIAB_TOOL
#define GT_SYNC asm(" eieio ")
#else
#error
#endif
#endif
#endif

#define GT_SYNC_MIPS                        \
        __asm__ __volatile__(                        \
                ".set        push\n\t"                \
                ".set        noreorder\n\t"                \
                ".set        mips2\n\t"                \
                "sync\n\t"                        \
                ".set        pop"                        \
                : /* no output */                \
                : /* no input */                \
                : "memory")


#define GT_SYNC_INTEL64 \
  {int tmp; __asm__ __volatile__("cpuid" : "=a" (tmp) \
   : "0" (1) : "ebx", "ecx", "edx", "memory"); }

#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 404)
#  define GT_SYNC_INTEL64_32  __sync_synchronize()
#else
#  define GT_SYNC_INTEL64_32 sync_core()
#endif

#ifdef MIPS_CPU
#define GT_SYNC GT_SYNC_MIPS
#endif

#ifdef MIPS64_CPU
#define GT_SYNC GT_SYNC_MIPS
#endif

#ifdef INTEL_CPU
#define GT_SYNC
#endif

#ifdef INTEL64_CPU
# ifdef GT_SYNC
#  undef GT_SYNC
# endif
# if defined(IS_64BIT_OS)
#  define GT_SYNC GT_SYNC_INTEL64
# else
#  ifdef __WORDSIZE
#   if __WORDSIZE == 64
#    define GT_SYNC GT_SYNC_INTEL64
#   endif
#  endif
# endif
# ifndef GT_SYNC
#  define GT_SYNC GT_SYNC_INTEL64_32
# endif
#endif

#ifdef CPU_ARM
#define GT_SYNC
#endif

#ifndef GT_SYNC
#define GT_SYNC
#endif

#ifdef _VISUALC
#  define __THREAD_LOCAL __declspec(thread)
#else
#  if defined(__GNUC__) || defined(__MINGW64__)
#    define __THREAD_LOCAL __thread
#  endif
#endif
/* __THREAD_LOCAL not supported on PPC (ELDK toolkit) */
#if defined(PPC_CPU) || defined(POWERPC_CPU) || defined(LINUX_NOKM)
# undef __THREAD_LOCAL
#endif
#ifndef __THREAD_LOCAL
#  define __THREAD_LOCAL
#endif

#ifndef  GT_ATTR_FALLTHROUGH
/* macro for GCC > 7.3.0 for acknowledging switch-case fallthrough */
#if defined(__GNUC__) && __GNUC__ >= 7
#define GT_ATTR_FALLTHROUGH  __attribute__ ((fallthrough))
#else
#define GT_ATTR_FALLTHROUGH  ((GT_VOID)0)
#endif
#endif

#ifndef  GT_UNUSED_PARAM
#define GT_UNUSED_PARAM(x) (GT_VOID)x
#endif
/*mingw64 porting*/
/*Additional errorno*/
#ifndef EBADMSG
#define EBADMSG 104
#endif

#ifndef EIDRM
#define EIDRM 111
#endif

#ifndef ENODATA
#define ENODATA 120
#endif

#ifndef ENOLINK
#define ENOLINK 121
#endif

#ifndef ENOMSG
#define ENOMSG 122
#endif

#ifndef ENOSR
#define ENOSR 124
#endif

#ifndef ENOSTR
#define ENOSTR 125
#endif

#ifndef ENOTRECOVERABLE
#define ENOTRECOVERABLE 127
#endif

#ifndef ETIME
#define ETIME 137
#endif

#ifndef ETXTBSY
#define ETXTBSY 139
#endif
/*mingw64 porting*/

#endif   /* __gtEnvDeph */


