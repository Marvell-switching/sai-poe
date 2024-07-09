/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

/**
 * @file-docAll core\ez_bringup\h\init\pdlinit.h.
 *
 * @brief   Declares the pdlinit class
 */

#ifndef __pdlib_pdlInith
#define __pdlib_pdlInith

 *
 * @brief Platform driver layer - Init library
 *
 * @version   1
********************************************************************************
*/

#include <pdlib/common/pdlTypes.h>
#include <pdlib/xml/xmlParser.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _VISUALC
/* Include SIZE_T typedef from VC compiler */
#include <Basetsd.h>
#endif

/**
* @addtogroup Library
* @{
*/


/**
 * @typedef void ( PDLIB_OS_CALLBACK_PRINT_PTR) (const char *format, ...)
 *
 * @brief   @defgroup Init Init
 *          @{Init functions
 */

typedef int (PDLIB_OS_CALLBACK_PRINT_PTR)(const char *format, ...);

/**
 * @typedef void * ( PDLIB_OS_CALLBACK_MEMALLOC_PTR) (SIZE_T size)
 *
 * @brief   Defines an alias representing the size
 */

typedef void *  (PDLIB_OS_CALLBACK_MEMALLOC_PTR)(SIZE_T size);

/**
 * @typedef void ( PDLIB_OS_CALLBACK_MEMFREE_PTR) (void * ptr)
 *
 * @brief   Defines an alias representing the pointer
 */

typedef void (PDLIB_OS_CALLBACK_MEMFREE_PTR)(void * ptr);

/**
 * @typedef void ( PDLIB_OS_CALLBACK_DEBUG_PTR) (const char *func_name_PTR, const char *format, ...)
 *
 * @brief   Defines an alias representing the ...
 */

typedef void (PDLIB_OS_CALLBACK_DEBUG_PTR)(const char *func_name_PTR, const char *format, ...);


typedef BOOLEAN PDLIB_XML_ARCHIVE_UNCOMPRESS_HANDLER_PTR(
    IN  char       *archiveFileNamePtr,
    OUT char       *xmlFileNamePtr,
    OUT char       *signatureFileNamePtr
);

typedef BOOLEAN PLDIB_XML_GET_SIGNATURE_PTR(
    IN  char       *xmlFileNamePtr,
    IN  UINT_32     signatureSize,
    OUT UINT_8     *signaturePtr
);

/**
 * @struct  PDLIB_OS_CALLBACK_API_STCT
 *
 * @brief   A pdl operating system callback API stct.
 */
typedef struct PDLIB_OS_CALLBACK_API_STCT {
    /** @brief   The print string pointer */
    PDLIB_OS_CALLBACK_PRINT_PTR                 * printStringPtr;
    /** @brief   The malloc pointer */
    PDLIB_OS_CALLBACK_MEMALLOC_PTR              * mallocPtr;
    /** @brief   The free pointer */
    PDLIB_OS_CALLBACK_MEMFREE_PTR               * freePtr;
    /** @brief   The debug log pointer */
    PDLIB_OS_CALLBACK_DEBUG_PTR                 * debugLogPtr;
    /* optional xml archive uncompress utility */
    PDLIB_XML_ARCHIVE_UNCOMPRESS_HANDLER_PTR    * arXmlUncompressClbk;
    PLDIB_XML_GET_SIGNATURE_PTR                 * getXmlSignatureClbk;
} PDLIB_OS_CALLBACK_API_STC;


/**
 * @fn  PDL_STATUS pdlibInit ( IN char * xmlFilePathPtr, IN char * xmlTagPrefixPtr, IN PDLIB_OS_CALLBACK_API_STC * callbacksPTR )
 *
 * @brief   initialize PDL
 *
 * @param [in]  xmlFilePathPtr  XML location.
 * @param [in]  xmlTagPrefixPtr XML tag's prefix.
 * @param [in]  callbacksPTR    application-specific implementation for os services.
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS pdlibInit(
    IN char                             * xmlFilePathPtr,
    IN char                             * xmlTagPrefixPtr,
    IN PDLIB_OS_CALLBACK_API_STC        * callbacksPTR,
    OUT XML_PARSER_ROOT_DESCRIPTOR_TYP  * id_PTR
);

/**
 * @fn  PDL_STATUS pdlibLibInit ( IN PDLIB_OS_CALLBACK_API_STC * callbacksPTR )
 *
 * @brief   Pdl library initialize
 *
 * @param [in]  callbacksPTR    If non-null, the callbacks pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS pdlibLibInit(
    IN PDLIB_OS_CALLBACK_API_STC    * callbacksPTR
);
/* @}*/
/* @}*/

#ifdef __cplusplus
}
#endif

#endif
