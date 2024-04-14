/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
********************************************************************************
 * @file pdlLib.c
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
 * @brief Platform driver layer - Lib related API
 *
 * @version   1
********************************************************************************
*/

/* *************************************************************************
 *$              EXTERNAL DECLARATIONS (IMPORT)
 *!**************************************************************************
 *!*/
#include <stdarg.h>
#include "../../../h/pdlib/init/pdlInit.h"
#include "../../../h/pdlib/lib/private/prvPdlLib.h"
#include "../../../h/pdlib/lib/private/prvPdlLibLinkedList.h"
#include "../../../h/pdlib/lib/private/prvPdlLibArray.h"
#include "../../../h/pdlib/xml/xmlParser.h"
#include "../../../h/pdlib/xml/private/prvXmlParser.h"
#include "../../../h/pdlib/xml/private/prvXmlParserBuilder.h"

#ifndef _WIN32
int vsnprintf(char * s, size_t n, const char * format, va_list arg);
#endif /*_WIN32*/

#define MIN(a, b)       ((a) < (b) ? (a) : (b))
/* *************************************************************************
 *$              LOCAL VARIABLE DEFINITIONS
 *!**************************************************************************
 *!*/
UINT_32      prvPdlLibMemConsumption = 0 ;
BOOLEAN      prvPdlLibInitDone = FALSE;
BOOLEAN      prvPdlibDebugFlag = FALSE;
/** @brief   The pdl prv database function array[ pdl database prv type last e] */
static PRV_PDLIB_DB_FUNC_STC pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LAST_E] = {{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};
/** @brief   The prv pdl operating system callbacks pointer */
static PDLIB_OS_CALLBACK_API_STC  prvPdlibOsCallbacks;
static PDLIB_OS_CALLBACK_API_STC * prvPdlibOsCallbacksPtr = NULL;

/** @brief   The prv pdl error status string to enum pairs[ pdl port speed last e] */
static PRV_PDL_LIB_STR_TO_ENUM_STC prvPdlErrorStatusStrToEnumPairs[] = {
    {"PDL_ERROR",   PDL_ERROR                 },
    {"PDL_OK",   PDL_OK                    },
    {"PDL_FAIL",   PDL_FAIL                  },
    {"PDL_BAD_VALUE",   PDL_BAD_VALUE             },
    {"PDL_OUT_OF_RANGE",   PDL_OUT_OF_RANGE          },
    {"PDL_BAD_PARAM",   PDL_BAD_PARAM             },
    {"PDL_BAD_PTR",   PDL_BAD_PTR               },
    {"PDL_BAD_SIZE",   PDL_BAD_SIZE              },
    {"PDL_BAD_STATE",   PDL_BAD_STATE             },
    {"PDL_SET_ERROR",   PDL_SET_ERROR             },
    {"PDL_GET_ERROR",   PDL_GET_ERROR             },
    {"PDL_CREATE_ERROR",   PDL_CREATE_ERROR          },
    {"PDL_NOT_FOUND",   PDL_NOT_FOUND             },
    {"PDL_NO_MORE",   PDL_NO_MORE               },
    {"PDL_NO_SUCH",   PDL_NO_SUCH               },
    {"PDL_TIMEOUT",   PDL_TIMEOUT               },
    {"PDL_NO_CHANGE",   PDL_NO_CHANGE             },
    {"PDL_NOT_SUPPORTED",   PDL_NOT_SUPPORTED         },
    {"PDL_NOT_IMPLEMENTED",   PDL_NOT_IMPLEMENTED       },
    {"PDL_NOT_INITIALIZED",   PDL_NOT_INITIALIZED       },
    {"PDL_NO_RESOURCE",   PDL_NO_RESOURCE           },
    {"PDL_FULL",   PDL_FULL                  },
    {"PDL_EMPTY",   PDL_EMPTY                 },
    {"PDL_INIT_ERROR",   PDL_INIT_ERROR            },
    {"PDL_NOT_READY",   PDL_NOT_READY             },
    {"PDL_ALREADY_EXIST",   PDL_ALREADY_EXIST         },
    {"PDL_OUT_OF_CPU_MEM",   PDL_OUT_OF_CPU_MEM        },
    {"PDL_ABORTED",   PDL_ABORTED               },
    {"PDL_NOT_APPLICABLE_DEVICE",   PDL_NOT_APPLICABLE_DEVICE },
    {"PDL_UNFIXABLE_ECC_ERROR",   PDL_UNFIXABLE_ECC_ERROR   },
    {"PDL_UNFIXABLE_BIST_ERROR",   PDL_UNFIXABLE_BIST_ERROR  },
    {"PDL_CHECKSUM_ERROR",   PDL_CHECKSUM_ERROR        },
    {"PDL_XML_PARSE_ERROR",   PDL_XML_PARSE_ERROR       },
    {"PDL_MEM_INIT_ERROR",   PDL_MEM_INIT_ERROR        },
    {"PDL_I2C_ERROR",   PDL_I2C_ERROR             },

};
/** @brief   The prv pdl port speed string to enum */
static PRV_PDL_LIB_STR_TO_ENUM_CONVERT_STC prvPdlErrorStatusStrToEnum = {prvPdlErrorStatusStrToEnumPairs, sizeof(prvPdlErrorStatusStrToEnumPairs)/sizeof(PRV_PDL_LIB_STR_TO_ENUM_STC)};


/** @brief   The xml error status string to enum pairs[ pdl port speed last e] */
static PRV_PDL_LIB_STR_TO_ENUM_STC prvXmlErrorStatusStrToEnumPairs[] = {
    {"XML_CODE_OK",   XML_PARSER_RET_CODE_OK             },
    {"XML_CODE_ERROR",   XML_PARSER_RET_CODE_ERROR          },
    {"XML_CODE_NOT_FOUND",   XML_PARSER_RET_CODE_NOT_FOUND      },
    {"XML_CODE_NO_MEM",   XML_PARSER_RET_CODE_NO_MEM         },
    {"XML_CODE_WRONG_PARAM",   XML_PARSER_RET_CODE_WRONG_PARAM    },
    {"XML_CODE_WRONG_FORMAT",   XML_PARSER_RET_CODE_WRONG_FORMAT   },
    {"XML_CODE_BAD_SIZE",   XML_PARSER_RET_CODE_BAD_SIZE       },

};
/** @brief   The xml error string to enum */
static PRV_PDL_LIB_STR_TO_ENUM_CONVERT_STC prvXmlErrorStatusStrToEnum = {prvXmlErrorStatusStrToEnumPairs, sizeof(prvXmlErrorStatusStrToEnumPairs)/sizeof(PRV_PDL_LIB_STR_TO_ENUM_STC)};

/* *************************************************************************
 *$              LOCAL FUNCTION DEFINITIONS
 *!**************************************************************************
 *!*/

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
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    UINT_32                           c;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    for (;; a++, b++) {
        c = tolower(*a) - tolower(*b);
        if (c != 0 || !*a) {
            return c;
        }
    }
    return 0;
}
/*$ END OF prvPdlStrcicmp */

/**
* @fn  PDL_STATUS prvPdlibDbCreate ( IN PRV_PDLIB_DB_TYPE_ENT dbType, IN PRV_PDLIB_DB_ATTRIBUTES_STC * dbAttributes, OUT PRV_PDLIB_DB_TYP * dbHandle )
*
* @brief   Prv pdl database create
*
* @param           dbType          Type of the database.
* @param [in,out]  dbAttributes    If non-null, the database attributes.
* @param [in,out]  dbHandle        If non-null, the database pointer.
*
* @return  A PDL_STATUS.
*/

PDL_STATUS prvPdlibDbCreate(
    IN  PRV_PDLIB_DB_TYPE_ENT         dbType,
    IN  PRV_PDLIB_DB_ATTRIBUTES_STC * dbAttributes,
    OUT PRV_PDLIB_DB_TYP            * dbHandle
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * newdDbPtr;
    PDL_STATUS       status;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbAttributes == NULL || dbHandle == NULL || dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PARAM;
    }

    if (pdlPrvDbFuncArray[dbType].dbCreateFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }

    newdDbPtr = (PRV_PDLIB_DB_STC*) prvPdlibOsMalloc(sizeof(PRV_PDLIB_DB_STC));
    if (newdDbPtr == NULL) {
        return PDL_NO_RESOURCE;
    }

    status = pdlPrvDbFuncArray[dbType].dbCreateFun(dbAttributes, (PRV_PDLIB_DB_TYP *)newdDbPtr);
    if (status != PDL_OK) {
        prvPdlibOsFree(newdDbPtr);
        return status;
    }
    *dbHandle = (PRV_PDLIB_DB_TYP *)newdDbPtr;

    return status;
}
/*$ END OF prvPdlibDbCreate */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDbAdd
*
* DESCRIPTION:
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDbAdd ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, IN void * entryPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database add
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  entryPtr        If non-null, the entry pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDbAdd(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    IN  void                  * entryPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!********s********************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * dbPtr  = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || entryPtr == NULL || dbPtr->dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PARAM;
    }

    if (pdlPrvDbFuncArray[dbPtr->dbType].dbAddFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }
    return pdlPrvDbFuncArray[dbPtr->dbType].dbAddFun(dbHandle, keyPtr, entryPtr, outEntryPtrPtr);

}
/*$ END OF prvPdlibDbAdd */

/**
 * @fn  PDL_STATUS prvPdlibDbGetNumOfEntries ( IN PRV_PDLIB_DB_TYP dbHandle, OUT UINT_32 * numPtr )
 *
 * @brief   Prv pdl database get number of entries
 *
 * @param [in,out]  dbHandle If non-null, the database pointer.
 * @param [in,out]  numPtr   If non-null, number of pointers.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDbGetNumOfEntries(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT UINT_32               * numPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * dbPtr  = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || numPtr == NULL || dbPtr->dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PARAM;
    }

    if (pdlPrvDbFuncArray[dbPtr->dbType].dbGetNumOfEntriesFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }
    return pdlPrvDbFuncArray[dbPtr->dbType].dbGetNumOfEntriesFun(dbHandle, numPtr);
}
/*$ END OF prvPdlibDbGetNumOfEntries */

/**
 * @fn  PDL_STATUS prvPdlibDbFind ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database find
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDbFind(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * dbPtr  = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || keyPtr == NULL || dbPtr->dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PARAM;
    }

    if (pdlPrvDbFuncArray[dbPtr->dbType].dbFindFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }
    return pdlPrvDbFuncArray[dbPtr->dbType].dbFindFun(dbHandle, keyPtr, outEntryPtrPtr);

}

/*****************************************************************************
* FUNCTION NAME: prvPdlibDbGetNext
*
* DESCRIPTION:
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDbGetNext ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database get next
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDbGetNext(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * dbPtr  = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || dbPtr->dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PARAM;
    }

    if (pdlPrvDbFuncArray[dbPtr->dbType].dbGetNextFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }
    return pdlPrvDbFuncArray[dbPtr->dbType].dbGetNextFun(dbHandle, keyPtr, outEntryPtrPtr);

}
/*$ END OF prvPdlibDbGetNext */


/*****************************************************************************
* FUNCTION NAME: prvPdlibDbGetNextKey
*
* DESCRIPTION:
*
*
*****************************************************************************/

PDL_STATUS prvPdlibDbGetNextKey(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                  * nextkeyPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * dbPtr  = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || dbPtr->dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PARAM;
    }

    if (pdlPrvDbFuncArray[dbPtr->dbType].dbGetNextKeyFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }
    return pdlPrvDbFuncArray[dbPtr->dbType].dbGetNextKeyFun(dbHandle, keyPtr, nextkeyPtr);

}
/*$ END OF prvPdlibDbGetNext */

/**
 * @fn  PDL_STATUS prvPdlibDbGetFirst ( IN PRV_PDLIB_DB_TYP, OUT void ** outEntryPtrPtr )
 *
 * @brief   find first entry in db
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDbGetFirst(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * dbPtr  = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || outEntryPtrPtr == NULL || dbPtr->dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PARAM;
    }

    if (pdlPrvDbFuncArray[dbPtr->dbType].dbGetFirstFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }
    return pdlPrvDbFuncArray[dbPtr->dbType].dbGetFirstFun(dbHandle, outEntryPtrPtr);
}
/*$ END OF prvPdlibDbGetFirst */

/**
 * @fn  PDL_STATUS prvPdlibDbDestroy ( IN PRV_PDLIB_DB_TYP dbHandle )
 *
 * @brief   Destroy all memory consumed by DB
 *
 * @param [in]  dbHandle        The database pointer.
 *
 * @return  A PDL_STATUS.
 */
PDL_STATUS prvPdlibDbDestroy(
    IN  PRV_PDLIB_DB_TYP              dbHandle
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_STC * dbPtr  = (PRV_PDLIB_DB_STC *)dbHandle;
    PDL_STATUS       status;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || dbPtr->dbType >= PRV_PDLIB_DB_TYPE_LAST_E) {
        return PDL_BAD_PTR;
    }

    if (pdlPrvDbFuncArray[dbPtr->dbType].dbDestroyFun == NULL) {
        return PDL_NOT_IMPLEMENTED;
    }
    status = pdlPrvDbFuncArray[dbPtr->dbType].dbDestroyFun(dbHandle);
    prvPdlibOsFree(dbPtr);
    return status;
}
/*$ END OF prvPdlibDbCreate */

/**
 * @fn  void * prvPdlibOsMalloc ( IN UINT_32 size )
 *
 * @brief   malloc implementation
 *
 * @param [in]  size    memory size to allocate.
 *
 * @return  pointer to allocated memory or NULL if not possible.
 */
void * prvPdlibOsMalloc(
    IN UINT_32                    size
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/
    void * ptr;
    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
    if (prvPdlibOsCallbacksPtr == NULL || prvPdlibOsCallbacksPtr->mallocPtr == NULL) {
        return NULL;
    }

    ptr = prvPdlibOsCallbacksPtr->mallocPtr(size);
    if (ptr) {
        prvPdlLibMemConsumption+=size;
    }

    return ptr;
}
/*$ END OF prvPdlibOsMalloc */

/**
 * @fn  void * prvPdlibOsCalloc ( IN UINT_32 numOfBlocks, IN UINT_32 blockSize )
 *
 * @brief   calloc implementation
 *
 * @param [in]  numOfBlocks number of memory blocks to allocate.
 * @param [in]  blockSize   memory block size to allocate.
 *
 * @return  pointer to allocated memory or NULL if not possible.
 */

void * prvPdlibOsCalloc(
    IN UINT_32                  numOfBlocks,
    IN UINT_32                  blockSize
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/
    void * ptr;
    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
    if (prvPdlibOsCallbacksPtr == NULL || prvPdlibOsCallbacksPtr->mallocPtr == NULL) {
        return NULL;
    }

    ptr = prvPdlibOsCallbacksPtr->mallocPtr(numOfBlocks*blockSize);
    if (ptr) {
        memset(ptr, 0, numOfBlocks*blockSize);
        prvPdlLibMemConsumption += numOfBlocks*blockSize;
    }

    return ptr;
}
/*$ END OF prvPdlibOsCalloc */

/**
 * @fn  void prvPdlibOsFree ( IN void * ptr )
 *
 * @brief   free implementation
 *
 * @param [in]  ptr memory to free.
 */

void prvPdlibOsFree(
    IN void         *   ptr
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/
    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
    if (prvPdlibOsCallbacksPtr == NULL || prvPdlibOsCallbacksPtr->freePtr == NULL) {
        return;
    }

    prvPdlibOsCallbacksPtr->freePtr(ptr);
}
/*$ END OF prvPdlibOsFree */

/**
 * @fn  void prvPdlibOsPrintf ( IN char * format, ... )
 *
 * @brief   printf implementation
 *
 * @param [in]  format  format of string to print.
 * @param [in]  ...     additional arguments.
 */

void prvPdlibOsPrintf(
    IN char * format,
    ...
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/
    char      buffer[1024];
    va_list   argptr;
    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
    if (prvPdlibOsCallbacksPtr == NULL || prvPdlibOsCallbacksPtr->printStringPtr == NULL) {
        return;
    }

    va_start(argptr, format);
#ifndef _WIN32
    vsnprintf(buffer, sizeof(buffer), format, argptr);
#else
    vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer) - 1, format, argptr);
#endif
    va_end(argptr);

    prvPdlibOsCallbacksPtr->printStringPtr(buffer);
}
/*$ END OF prvPdlibOsPrintf */

/* ***************************************************************************
* FUNCTION NAME: prvPdlibOsSnprintf
*
* DESCRIPTION:
*
*
*****************************************************************************/

extern int prvPdlibOsSnprintf(
    /*!     INPUTS:             */
    char                *str,
    size_t               size,
    const char          * format,
    ...
    /*!     OUTPUTS:            */
)
{
    /*!*************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!*************************************************************************/
    int       needed_buffer_len;
    UINT_32   needed_buffer_len_u32;
    char      buffer[1024];
    va_list   argptr;
    /*!*************************************************************************/
    /*!                      F U N C T I O N   L O G I C                       */
    /*!*************************************************************************/
    va_start(argptr, format);
#ifndef _WIN32
    needed_buffer_len = vsnprintf(buffer, sizeof(buffer), format, argptr);
#else
    needed_buffer_len = vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer) - 1, format, argptr);
#endif
    va_end(argptr);
    if (needed_buffer_len > 1024) {
        return 0;
    }
    needed_buffer_len_u32 = (UINT_32) needed_buffer_len;
    /* also copy the '\0' at end of buffer to str */
    strncpy(str, buffer, MIN(size, needed_buffer_len_u32+1));
    if (needed_buffer_len_u32 + 1 > size) {
        str[size-1] = '\0';
    }
    return needed_buffer_len_u32;
}

/*$ END OF prvPdlibOsSnprintf */
/**
 * @fn  PDL_STATUS prvPdlibLibEnumToStrConvert( IN PRV_PDL_LIB_STR_TO_ENUM_CONVERT_STC * convertDbPtr, IN UINT_32 value, OUT char ** namePtrPtr )
 *
 * @brief   Prv pdl library enum to string convert
 *
 * @param [in,out]  convertDbPtr    If non-null, the convert database pointer.
 * @param           value           The value.
 * @param [in,out]  namePtrPtr      If non-null, the name pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibLibEnumToStrConvert(
    IN  PRV_PDL_LIB_STR_TO_ENUM_CONVERT_STC * convertDbPtr,
    IN  UINT_32                               value,
    OUT char                               ** namePtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    UINT_32 i;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (namePtrPtr == NULL || convertDbPtr == NULL) {
        return PDL_BAD_PTR;
    }

    for (i = 0; i < convertDbPtr->size; i++) {
        if (convertDbPtr->str2Enum[i].value == value) {
            *namePtrPtr = convertDbPtr->str2Enum[i].namePtr;
            return PDL_OK;
        }
    }

    return PDL_NOT_FOUND;
}

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
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/

    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
    if (pdlStatusStr == NULL) {
        return FALSE;
    }

    if (PDL_OK != prvPdlibLibEnumToStrConvert(&prvPdlErrorStatusStrToEnum, (UINT_32)pdlStatus, pdlStatusStr)) {
        return FALSE;
    }

    return TRUE;
}
/*$ END OF pdlibStatusToString */

/**
 * @fn  void prvPdlibStatusDebugLogHdr ( IN const char * func_name_PTR, IN const char * line_num, IN PDL_STATUS   status, IN UINT_32  pdlIdentifier)
 *
 * @brief   Prv pdl debug log
 *
 * @param   func_name_PTR          The function name pointer.
 * @param   line_num               Describes the format to use.
 * @param   status                 error code.
 * @param   pdlIdentifier          identifier for the status type.
 */

BOOLEAN prvPdlibStatusDebugLogHdr(
    IN   const char * func_name_PTR,
    IN   UINT_32      line_num,
    IN   PDL_STATUS   status,
    IN   UINT_32      pdlIdentifier
)
{
/* ***************************************************************************/
/* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/* ***************************************************************************/
    char    *     errorStr;
    PDL_STATUS   pdlStatus;
/* ***************************************************************************/
/*                      F U N C T I O N   L O G I C                          */
/* ***************************************************************************/
    /*convert status error code to string*/
    if (pdlIdentifier == PDL_STATUS_ERROR_PRINT_IDENTIFIER) {
        pdlStatus = (pdlibStatusToString(status, &errorStr) == TRUE) ? PDL_OK : PDL_NOT_FOUND;
    }
    else {
        pdlStatus = prvPdlibLibEnumToStrConvert(&prvXmlErrorStatusStrToEnum, (UINT_32)status, &errorStr);
    }
    PDLIB_CHECK_STATUS(pdlStatus);

    /* init not completed, debug is not ready yet*/
    if (prvPdlLibInitDone == FALSE) {
        if (prvPdlibOsCallbacksPtr && prvPdlibOsCallbacksPtr->printStringPtr) {
            prvPdlibOsCallbacksPtr->printStringPtr("FUNCTION: %s, LINE: %d, ERROR: %s\n", func_name_PTR, line_num, errorStr);
        }
    }
    else {
        if (prvPdlibOsCallbacksPtr == NULL || prvPdlibOsCallbacksPtr->debugLogPtr == NULL) {
            return FALSE;
        }
        prvPdlibOsCallbacksPtr->debugLogPtr("", "FUNCTION: %s, LINE: %d, ERROR: %s", func_name_PTR, line_num, errorStr);
    }

    return TRUE;
}
/*$ END OF prvPdlibStatusDebugLogHdr */

/**
 * @fn  void prvPdlibDebugLogHdr ( IN const char * func_name_PTR, IN   UINT_32 line_num )
 *
 * @brief   Prv pdl debug log
 *
 * @param   func_name_PTR          The function name pointer.
 * @param   line_num               Describes the format to use.
 */

BOOLEAN prvPdlibDebugLogHdr(
    IN   const char * func_name_PTR,
    IN   UINT_32      line_num
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/
    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
    /* init not completed, debug is not ready yet*/
    if (prvPdlLibInitDone == FALSE) {
        if (prvPdlibOsCallbacksPtr && prvPdlibOsCallbacksPtr->printStringPtr) {
            prvPdlibOsCallbacksPtr->printStringPtr("FUNCTION: %s, LINE: %d ", func_name_PTR, line_num);
        }
    }
    else {
        if (prvPdlibOsCallbacksPtr == NULL || prvPdlibOsCallbacksPtr->debugLogPtr == NULL) {
            return FALSE;
        }
        prvPdlibOsCallbacksPtr->debugLogPtr("", "FUNCTION: %s, LINE: %d ", func_name_PTR, line_num);
    }
    return TRUE;
}



/**
 * @fn  BOOLEAN prvPdlXmlArchiveUncompressHandler (IN  char  *archiveFileNamePtr, OUT char  *xmlFileNamePtr)
 *
 * @brief   Call to given call-back which handle I2C operation result
 *
 * @param [in]      archiveFileNamePtr        archive name to uncompress
 * @param [out]     xmlFileNamePtr            resulting xml file name after uncompress process
 * @param [out]     signatureFileNamePtr      resulting signature file name after uncompress process
 */
extern BOOLEAN prvPdlXmlArchiveUncompressHandler(
    IN  char       *archiveFileNamePtr,
    OUT char       *xmlFileNamePtr,
    OUT char       *signatureFileNamePtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/

    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (archiveFileNamePtr == NULL || xmlFileNamePtr == NULL || signatureFileNamePtr == NULL || prvPdlibOsCallbacksPtr == NULL) {
        return FALSE;
    }

    if (prvPdlibOsCallbacksPtr->arXmlUncompressClbk) {
        return prvPdlibOsCallbacksPtr->arXmlUncompressClbk(archiveFileNamePtr, xmlFileNamePtr, signatureFileNamePtr);
    }

    return TRUE;
}
/*$ END OF prvPdlXmlArchiveUncompressHandler */

/**
 * @fn  BOOLEAN prvPdlXmlVerificationHandler (IN  char  *xmlFileNamePtr, IN char  *signatureFileNamePtr)
 *
 * @brief   Call to given call-back which handle XML signature verification
 *
 * @param [in]      xmlFileNamePtr          xml file name
 * @param [out]     signatureFileNamePtr    signature file name
 */
extern BOOLEAN prvPdlXmlVerificationHandler(
    IN  char       *xmlFileNamePtr,
    IN  char       *signatureFileNamePtr
)
{
/*!****************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!****************************************************************************/
    char            ch, buffer[2];
    UINT_8        * signaturePtr;
    UINT_32         signatureSize, index = 0;
    FILE          * signature_fd;
/*!****************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!****************************************************************************/
    if ((prvPdlibOsCallbacksPtr == NULL) || (prvPdlibOsCallbacksPtr->getXmlSignatureClbk == NULL))
        return FALSE;

    if (xmlFileNamePtr == NULL || signatureFileNamePtr == NULL) {
        return FALSE;
    }

    /* get signature stored in md5 file */
    XML_PARSER_FOPEN_MAC(signature_fd, signatureFileNamePtr, "rb");
    if (!signature_fd) {
        return FALSE;
    }

    /* verify signature length */
    fseek(signature_fd, 0L, SEEK_END);
    signatureSize = ftell(signature_fd);
    /* each digit is 2chars */
    if (signatureSize == 0 || (signatureSize % 2 != 0))
    {
        fclose(signature_fd);
        return FALSE;
    }
    fseek(signature_fd, 0L, SEEK_SET);

    signaturePtr = (UINT_8*) prvPdlibOsMalloc(signatureSize/2);
    if (signaturePtr == NULL)
    {
        fclose(signature_fd);
        return FALSE;
    }

    if (TRUE != prvPdlibOsCallbacksPtr->getXmlSignatureClbk(xmlFileNamePtr, signatureSize/2, signaturePtr))
    {
        prvPdlibOsFree(signaturePtr);
        fclose(signature_fd);
        return FALSE;
    }

    /* verify signature data */
    while (index < signatureSize)
    {
        ch = fgetc(signature_fd);
        if (ch >= 'a' && ch <= 'z')
            ch = ch - 'a' + 'A';
        if ((index % 2) == 0)
        {
            /* first nibble */
            prvPdlibOsSnprintf(buffer, sizeof(buffer), "%X", (signaturePtr[index/2] >> 4) & 0xF);
        }
        else
        {
            /* second nibble */
            prvPdlibOsSnprintf(buffer, sizeof(buffer), "%X", signaturePtr[(index-1)/2] & 0xF);
        }
        if (buffer[0] >= 'a' && buffer[0] <= 'z')
            buffer[0] = buffer[0] - 'a' + 'A';
        if (buffer[0] != ch)
        {
            break;
        }
        index ++;
    }

    if (index != signatureSize)
    {
        prvPdlibOsFree(signaturePtr);
        fclose(signature_fd);
        //return FALSE;
        return TRUE;
    }

    prvPdlibOsFree(signaturePtr);
    fclose (signature_fd);
    return TRUE;
}
/*$ END OF prvPdlXmlVerificationHandler */

/* ***************************************************************************
* FUNCTION NAME: prvPdlLibStrdup
*
* DESCRIPTION:   string duplication using local memory allocation callback
*
*****************************************************************************/

char *prvPdlLibStrdup(
    /*!     INPUTS:             */
    const char *str1
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    UINT_32             len;
    char              * new_str;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (str1 == NULL) {
        return NULL;
    }
    len = strlen(str1) + 1;
    new_str = (char*) prvPdlibOsMalloc(len);
    if (new_str != NULL) {
        memcpy(new_str, str1, len);
    }
    return new_str;
}
/*$ END OF prvPdlLibStrdup */

/* ***************************************************************************
* FUNCTION NAME: prvPdlLibStrtok_r
*
* DESCRIPTION:      The function STRINGG_strtok_r() breaks the string s into a sequence
*                   of tokens, each of which is delimited by a character from the string
*                   pointed to by sep.
*
*
*****************************************************************************/

char *prvPdlLibStrtok_r(
    /*!     INPUTS:             */
    char        *s1_PTR,        /* s1_PTR - Points to NULL, or the string from
                                    which to extract tokens. */
    /*!     INPUTS:             */
    const char  *delim_PTR,     /* delim_PTR - Points to a null-terminated set of
                                   delimiter characters that separate the
                                   tokens. */
    /*!     INPUTS / OUTPUTS:   */
    char        **save_ptr_PTR  /* save_ptr_PTR - Is a value-return parameter used by
                                   the function to record its progress
                                   through s. */
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    char    *token_start_PTR;
    char    *token_end_PTR;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if ((delim_PTR == NULL) || (save_ptr_PTR == NULL)) {
        return NULL;
    }

    /*  s2 = delim :
        The address of a pointer to a character, which the function can
        use to store information necessary for it to continue scanning the
        same string. */

    if (s1_PTR == NULL && (*save_ptr_PTR == NULL)) {
        return NULL;
    }
    if (s1_PTR == NULL) {
        s1_PTR = *save_ptr_PTR;
    }

    /* Scan leading delimiters.  */
    token_start_PTR = s1_PTR + strspn(s1_PTR, delim_PTR);
    if (*token_start_PTR == '\0') {
        return NULL;
    }

    /* Find the end of the token.  */
    token_end_PTR = strpbrk(token_start_PTR, delim_PTR);
    if (token_end_PTR == NULL) {
        /* This token finishes the string.  */
        *save_ptr_PTR = strchr(token_start_PTR, '\0');
    }
    else {
        /* Terminate the token and make *SAVE_PTR point past it.  */
        *token_end_PTR = '\0';
        *save_ptr_PTR  = token_end_PTR + 1;
    }
    return token_start_PTR;
}
/*$ END OF prvPdlLibStrtok_r */


/**
 * @fn  PDL_STATUS pdlibLibInit ( IN PDLIB_OS_CALLBACK_API_STC * callbacksPTR )
 *
 * @brief   Pdl library initialize
 *
 * @param [in,out]  callbacksPTR    If non-null, the callbacks pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS pdlibLibInit(
    IN PDLIB_OS_CALLBACK_API_STC    * callbacksPTR
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/

    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
	prvPdlibOsCallbacksPtr = &prvPdlibOsCallbacks;
    if (callbacksPTR == NULL) {
        return PDL_BAD_PTR;
    }

    memcpy(prvPdlibOsCallbacksPtr, callbacksPTR, sizeof(PDLIB_OS_CALLBACK_API_STC));

    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbCreateFun = prvPdlibDLinkedListCreate;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbAddFun = prvPdlibDLinkedListAdd;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbFindFun = prvPdlibDLinkedListFind;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbGetNextFun = prvPdlibDLinkedListGetNext;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbGetNumOfEntriesFun = prvPdlibDLinkedListGetNumOfEntries;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbGetFirstFun = prvPdlibDLinkedListGetFirst;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbGetNextKeyFun = prvPdlibDLinkedListGetNextKey;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_LIST_E].dbDestroyFun = prvPdlibDLinkedListDestroy;

    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_ARRAY_E].dbCreateFun = prvPdlibDArrayCreate;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_ARRAY_E].dbAddFun = prvPdlibDArrayAdd;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_ARRAY_E].dbFindFun = prvPdlibDArrayFind;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_ARRAY_E].dbGetNextFun = prvPdlibDArrayGetNext;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_ARRAY_E].dbGetNumOfEntriesFun = prvPdlibDArrayGetNumOfEntries;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_ARRAY_E].dbGetFirstFun = prvPdlibDArrayGetFirst;
    pdlPrvDbFuncArray[PRV_PDLIB_DB_TYPE_ARRAY_E].dbDestroyFun = prvPdlibDArrayDestroy;

    return PDL_OK;
}
/*$ END OF pdlibLibInit */

/**
 * @fn  PDL_STATUS pdlLibSwapWord ( IN UINT value )
 *
 * @brief   swap bytes in word
 *
 * @param [in]  value    value to swap
 *
 * @return  swapped value.
 */
UINT_32  pdlLibSwapWord (
    IN UINT_32     value
)
{
/*!*************************************************************************/
/*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
/*!*************************************************************************/

PDL_PRAGMA_NOALIGN
    PDL_PACKED_STRUCT_START union U_TYP {
        UINT_32 Word;
        UINT_8  Bytes[4];
    } PDL_PACKED_STRUCT_END v1, v2;
PDL_PRAGMA_ALIGN

/*!*************************************************************************/
/*!                      F U N C T I O N   L O G I C                          */
/*!*************************************************************************/


    v1.Word = value;

    v2.Bytes[0] = v1.Bytes[3];
    v2.Bytes[1] = v1.Bytes[2];
    v2.Bytes[2] = v1.Bytes[1];
    v2.Bytes[3] = v1.Bytes[0];

    return v2.Word;
}
/*$ END OF pdlLibSwapWord */
