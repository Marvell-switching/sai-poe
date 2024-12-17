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
 * @file-docAll core\ez_bringup\h\button\pdllib.h.
 *
 * @brief   Declares the pdllib class
 */

#ifndef __pdlLibpdlLibh
#define __pdlLibpdlLibh

#ifdef __cplusplus
extern "C" {
#endif

/**
********************************************************************************
 *
 * @brief Platform driver layer - LIB related API
 *
 * @version   1
********************************************************************************
*/

#include <pdlib/common/pdlTypes.h>

/**
* @defgroup LIB
* @{LIB definitions and declarations
*
*/


/**
 * @fn  BOOLEAN pdlibStatusToString ( IN PDL_STATUS pdlStatus, OUT char ** pdlStatusStr)
 *
 * @brief   pdl status codes to string representation
 *
 * @param   pdlStatus             pdl status code
 * @param   pdlStatusStr          identifier for the status type.
 */

extern BOOLEAN pdlibStatusToString(
    IN  PDL_STATUS    pdlStatus,
    OUT char        **pdlStatusStr
);

/**
 * @fn  PDL_STATUS prvPdlstrcicmp
 *
 * @brief   case insensitive string compate
 *
 * @param [in]  a           first string
 * @param [out] b           second string
 *
 * @return  0               strings are identical (case-ignored)
 * @return  anything else   strings aren't identical
 */

UINT_32 prvPdlStrcicmp(
    IN  char const                  * a,
    IN  char const                  * b
);

#define PDL_LIB_MD5_DIGEST_LENGTH_CNS   16

/**
 * @struct  PDL_LIB_MD5_DIGEST_STC
 *
 * @brief   defines structure used to contain MD5 signature
 */
typedef struct {
    /** @brief   MD5 digest value */
    UINT_8          value[PDL_LIB_MD5_DIGEST_LENGTH_CNS];
} PDL_LIB_MD5_DIGEST_STC;

/**
 * @fn  PDL_STATUS pdlLibSwapWord ( IN UINT value )
 *
 * @brief   swap bytes in word
 *
 * @param [in]  value    value to swap
 *
 * @return  swapped value.
 */
extern UINT_32  pdlLibSwapWord (
    IN UINT_32     value
);

/**
* @fn  PDL_STATUS pdlibMd5DigestCompute ( IN void * fdPtr, IN void * msgPtr, IN UINT_32 msgLen, OUT PDL_LIB_MD5_DIGEST_STC *digestPtr )
*
* @brief   Compute MD5 digest of the message contained in specified file or message buffer
*
* @param [in]  fdPtr          If non-null, points to file descriptor of type FILE**, containing the message to compute the digest
* @param [in]  msgPtr         If non-null, points to the first octet of the message to compute the digest
* @param [in]  msgLen         size of the message to 
* @param [out] digestPtr      Computed digest of the message
*
* @return  A PDL_STATUS.
*/
extern PDL_STATUS pdlibMd5DigestCompute (
    IN  void                    *fdPtr,
    IN  UINT_8                  *msgPtr,
    IN  const UINT_32            msgLen,
    OUT PDL_LIB_MD5_DIGEST_STC  *digestPtr
);

/**
* @fn  PDL_STATUS pdlibMd5DigestComputeWithKey ( IN void * fdPtr, IN void * msgPtr, IN UINT_32 msgLen, IN UINT_8* keyPtr, IN UINT_32 keyLen, OUT PDL_LIB_MD5_DIGEST_STC *digestPtr )
*
* @brief   Perform two iterations of MD5 computation:
* 		First  - Compute MD5 digest of the message contained in specified file or message buffer
* 		Second - Append "Key" to digest and compute MD5 digest on <key+digest>
*
* @param [in]  fdPtr          If non-null, points to file descriptor of type FILE**, containing the message to compute the digest
* @param [in]  msgPtr         If non-null, points to the first octet of the message to compute the digest
* @param [in]  msgLen         size of the message to digest
* @param [in]  keyPtr         Key / secret phrase that will be used for  md5 second iteration
* @param [in]  keyLen         length of kety
* @param [out] digestPtr      Computed digest of the message
*
* @return  A PDL_STATUS.
*/
extern PDL_STATUS pdlibMd5DigestComputeWithKey(
	IN  void                    *fdPtr,
	IN  UINT_8                  *msgPtr,
	IN  const UINT_32            msgLen,
	IN  UINT_8                  *keyPtr,
	IN  const UINT_32            keyLen,
	OUT PDL_LIB_MD5_DIGEST_STC  *digestPtr
);
#ifdef __cplusplus
}
#endif

#endif