/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\h\lib\private\prvpdllib.h.
 *
 * @brief   Declares the prvpdllib class
 */

#ifndef __prvPdlLibPdlLibPdlLibh

#define __prvPdlLibPdlLibPdlLibh
/**
********************************************************************************
 * @file prvPdlLib.h
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
 * @brief Platform driver layer - Library private declarations and APIs
 *
 * @version   1
********************************************************************************
*/

#include <pdlib/common/pdlTypes.h>
#include <pdlib/xml/xmlParser.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup Library Library
 * @{Library APIs
 */

/**
 * @enum    PRV_PDLIB_DB_TYPE_ENT
 *
 * @brief   Enumerator for DB types
 */

typedef enum {
    PRV_PDLIB_DB_TYPE_ARRAY_E,
    PRV_PDLIB_DB_TYPE_LIST_E,
    PRV_PDLIB_DB_TYPE_HASH_E,
    PRV_PDLIB_DB_TYPE_LAST_E
} PRV_PDLIB_DB_TYPE_ENT;

/**
 * @struct  PRV_PDL_LIB_STR_TO_ENUM_STC
 *
 * @brief   defines structure used to convert pair name to number
 */

typedef struct {
    /** @brief   The name pointer */
    char                   *namePtr;
    /** @brief   The value */
    UINT_32                 value;
} PRV_PDL_LIB_STR_TO_ENUM_STC;

/**
 * @struct  PRV_PDL_LIB_STR_TO_ENUM_CONVERT_STC
 *
 * @brief   defines structure used to convert enumerations to names
 */

typedef struct {
    /** @brief   The 2 enum */
    PRV_PDL_LIB_STR_TO_ENUM_STC     * str2Enum;
    /** @brief   The size */
    UINT_32                           size;
} PRV_PDL_LIB_STR_TO_ENUM_CONVERT_STC;

/**
 * @struct  PRV_PDLIB_DB_STC
 *
 * @brief   defines structure used by DB APIs
 */

typedef struct {
    /** @brief   Type of the database */
    PRV_PDLIB_DB_TYPE_ENT                 dbType;
    /** @brief   The database pointer */
    void                              * dbPtr;
} PRV_PDLIB_DB_STC;

/**
 * @typedef UINT_32 pdlibArrayKeyToIndex_FUN (void* key)
 *
 * @brief  Array key to index
 */

/**
 * @typedef UINT_32 pdlibArrayKeyToIndex_FUN (void* key)
 *
 * @brief   Defines an alias representing the key
 */

typedef UINT_32 pdlibArrayKeyToIndex_FUN(void* key);

/**
 * @struct  PRV_PDLIB_DB_ARRAY_ATTRIBUTES_STC
 *
 * @brief   defines attributes that should be supplied for array creation
 */

typedef struct {
    /** @brief   Size of the key */
    UINT_32                              keySize;
    /** @brief   Number of entries */
    UINT_32                              numOfEntries;
    /** @brief   Size of the entry */
    UINT_32                              entrySize;
    /** @brief   The key to index function */
    pdlibArrayKeyToIndex_FUN             * keyToIndexFunc;
} PRV_PDLIB_DB_ARRAY_ATTRIBUTES_STC;

/**
 * @struct  PRV_PDLIB_DB_HASH_ATTRIBUTES_STC
 *
 * @brief   defines attributes that should be supplied for hash creation
 */

typedef struct {
    /** @brief   Size of the key */
    UINT_32                         keySize;
    /** @brief   Size of the entry */
    UINT_32                         entrySize;
    /** @brief   The minimum number of entries */
    UINT_32                         minNumOfEntries;
    /** @brief   The maximum number of entries */
    UINT_32                         maxNumOfEntries;
} PRV_PDLIB_DB_HASH_ATTRIBUTES_STC;

/**
 * @struct  PRV_PDLIB_DB_LIST_ATTRIBUTES_STC
 *
 * @brief   defines attributes that should be supplied for list creation
 */

typedef struct {
    /** @brief   Size of the key */
    UINT_32                              keySize;
    /** @brief   Size of the entry */
    UINT_32                              entrySize;
} PRV_PDLIB_DB_LIST_ATTRIBUTES_STC;

/**
 * @union   PRV_PDLIB_DB_ATTRIBUTES_STC
 *
 * @brief   union of all db creation attributes
 */

typedef union {
    /** @brief   The list attributes */
    PRV_PDLIB_DB_LIST_ATTRIBUTES_STC      listAttributes;
    /** @brief   The array attributes */
    PRV_PDLIB_DB_ARRAY_ATTRIBUTES_STC     arrayAttributes;
    /** @brief   The hash attributes */
    PRV_PDLIB_DB_HASH_ATTRIBUTES_STC      hashAttributes;
} PRV_PDLIB_DB_ATTRIBUTES_STC;

/* typedefs used in array of generic db function callbacks */

/**
 * @typedef PDL_STATUS prvPdlibDCreate_FUN ( IN PRV_PDLIB_DB_ATTRIBUTES_STC * dbAttributes, OUT PRV_PDLIB_DB_TYP * dbPtr )
 *
 * @brief   Defines an alias representing the database pointer
 */
typedef void * PRV_PDLIB_DB_TYP;
typedef PDL_STATUS prvPdlibDCreate_FUN(
    IN  PRV_PDLIB_DB_ATTRIBUTES_STC   * dbAttributes,
    OUT PRV_PDLIB_DB_TYP              * dbHandle
);


/*! Add function creation */
#define prvPdlibDAddStubMac(__func_name)             \
    PDL_STATUS __func_name (                        \
    IN  PRV_PDLIB_DB_TYP          dbHandle,           \
    IN  void                  * keyPtr,             \
    IN  void                  * entryPtr,           \
    OUT void                 ** outEntryPtrPtr      \
)


/*! Add function creation */
#define prvPdlibDFindStubMac(__func_name)            \
    PDL_STATUS __func_name (                        \
    IN  PRV_PDLIB_DB_TYP          dbHandle,           \
    IN  void                  * keyPtr,             \
    OUT void                 ** outEntryPtrPtr      \
)


/*! Get next function creation */
#define prvPdlibDGetNextStubMac(__func_name)         \
    PDL_STATUS __func_name (                        \
    IN  PRV_PDLIB_DB_TYP          dbHandle,           \
    IN  void                  * keyPtr,             \
    OUT void                 ** outEntryPtrPtr      \
)

/*! Get next key function creation */
#define prvPdlibDGetNextKeyStubMac(__func_name)      \
    PDL_STATUS __func_name (                        \
    IN  PRV_PDLIB_DB_TYP          dbHandle,           \
    IN  void                  * keyPtr,             \
    OUT void                  * nextKeyPtr          \
)

/*! Get number of entries function creation */
#define prvPdlibDGetNumOfEntriesStubMac(__func_name) \
    PDL_STATUS __func_name (                        \
    IN  PRV_PDLIB_DB_TYP          dbHandle,           \
    OUT UINT_32               * numPtr              \
)

/*! Get first entry function creation */
#define prvPdlibDGetFirstStubMac(__func_name)        \
    PDL_STATUS __func_name (                        \
    IN  PRV_PDLIB_DB_TYP          dbHandle,           \
    OUT void                 ** outEntryPtrPtr      \
)

/*!destroy function creation */
#define prvPdlibDDestroyStubMac(__func_name)         \
    PDL_STATUS __func_name (                        \
    IN  PRV_PDLIB_DB_TYP          dbHandle            \
)

/**
 * @typedef prvPdlibDAddStubMac(prvPdlibDAdd_FUN)
 *
 * @brief  Add to DB function
 */

/**
 * @typedef prvPdlibDAddStubMac(prvPdlibDAdd_FUN)
 *
 * @brief   Defines an alias representing the prv pdl database add fun
 */

typedef prvPdlibDAddStubMac(prvPdlibDAdd_FUN);

/**
 * @typedef prvPdlibDFindStubMac(prvPdlibDFind_FUN)
 *
 * @brief  Find in DB function
 */

/**
 * @typedef prvPdlibDFindStubMac(prvPdlibDFind_FUN)
 *
 * @brief   Defines an alias representing the prv pdl database find fun
 */

typedef prvPdlibDFindStubMac(prvPdlibDFind_FUN);

/**
 * @typedef prvPdlibDGetNextStubMac(prvPdlibDGetNext_FUN)
 *
 * @brief  Gen Next in DB function
 */

/**
 * @typedef prvPdlibDGetNextStubMac(prvPdlibDGetNext_FUN)
 *
 * @brief   Defines an alias representing the prv pdl database get next fun
 */

typedef prvPdlibDGetNextStubMac(prvPdlibDGetNext_FUN);
typedef prvPdlibDGetNextKeyStubMac(prvPdlibDGetNextKey_FUN);

/**
 * @typedef prvPdlibDGetNumOfEntriesStubMac(prvPdlibDGetNumOfEntries_FUN)
 *
 * @brief  Get number of entries function
 */

/**
 * @typedef prvPdlibDGetNumOfEntriesStubMac(prvPdlibDGetNumOfEntries_FUN)
 *
 * @brief   Defines an alias representing the prv pdl database get number of entries fun
 */

typedef prvPdlibDGetNumOfEntriesStubMac(prvPdlibDGetNumOfEntries_FUN);


/**
 * @typedef prvPdlibDGetFirstStubMac(prvPdlibDGetFirstStubMac)
 *
 * @brief   Defines an alias representing the prv pdl database get first
 */

typedef prvPdlibDGetFirstStubMac(prvPdlibDGetFirstStubMac_FUN);

typedef prvPdlibDDestroyStubMac(prvPdlibDDestroy_FUN);


/**
 * @struct  PRV_PDLIB_DB_FUNC_STC
 *
 * @brief   defines functions that MUST be implemented by a pdl db library
 */

typedef struct {
    /** @brief   The database create fun */
    prvPdlibDCreate_FUN            * dbCreateFun;
    /** @brief   The database add fun */
    prvPdlibDAdd_FUN               * dbAddFun;
    /** @brief   The database find fun */
    prvPdlibDFind_FUN              * dbFindFun;
    /** @brief   The database get next fun */
    prvPdlibDGetNext_FUN           * dbGetNextFun;
    /** @brief   The database get number of entries fun */
    prvPdlibDGetNumOfEntries_FUN   * dbGetNumOfEntriesFun;
    prvPdlibDGetFirstStubMac_FUN   * dbGetFirstFun;
    prvPdlibDGetNextKey_FUN        * dbGetNextKeyFun;
    prvPdlibDDestroy_FUN           * dbDestroyFun;
} PRV_PDLIB_DB_FUNC_STC;

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

extern BOOLEAN prvPdlibStatusDebugLogHdr(
    IN   const char * func_name_PTR,
    IN   UINT_32      line_num,
    IN   PDL_STATUS   status,
    IN   UINT_32      pdlIdentifier
);

/**
 * @fn  PDL_STATUS prvPdlibDbCreate ( IN PRV_PDLIB_DB_TYPE_ENT dbType, IN PRV_PDLIB_DB_ATTRIBUTES_STC * dbAttributes, OUT PRV_PDLIB_DB_TYP * dbHandle );
 *
 * @brief   create DB of given type
 *
 * @param [in]  dbType          - db type.
 * @param [in]  dbAttributes    - attributes that are db type specific.
 * @param [out] dbPtr           - pointer to created db structure.
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS prvPdlibDbCreate(
    IN  PRV_PDLIB_DB_TYPE_ENT           dbType,
    IN  PRV_PDLIB_DB_ATTRIBUTES_STC   * dbAttributes,
    OUT PRV_PDLIB_DB_TYP              * dbHandle
);

/**
 * @fn  prvPdlibDAddStubMac (prvPdlibDbAdd);
 *
 * @brief   Add instance to DB
 *
 * @param   parameter1  The first parameter.
 */

prvPdlibDAddStubMac(prvPdlibDbAdd);

/**
 * @fn  prvPdlibDFindStubMac(prvPdlibDFind);
 *
 * @brief   Find instance in DB
 *
 * @param   parameter1  The first parameter.
 */

prvPdlibDFindStubMac(prvPdlibDbFind);

/**
 * @fn  prvPdlibDGetNextStubMac(prvPdlibDbGetNext);
 *
 * @brief   Find next instance in DB
 *
 * @param   parameter1  The first parameter.
 */

prvPdlibDGetNextStubMac(prvPdlibDbGetNext);
prvPdlibDGetNextKeyStubMac(prvPdlibDbGetNextKey);

/**
 * @fn  prvPdlibDGetNumOfEntriesStubMac(prvPdlibDbGetNumOfEntries);
 *
 * @brief   Get DB number of entries
 *
 * @param   parameter1  The first parameter.
 */

prvPdlibDGetNumOfEntriesStubMac(prvPdlibDbGetNumOfEntries);


prvPdlibDGetFirstStubMac(prvPdlibDbGetFirst);

/**
 * @fn  PDL_STATUS prvPdlibDbDestroy ( IN PRV_PDLIB_DB_TYP dbHandle )
 *
 * @brief   Destroy all memory consumed by DB
 *
 * @param [in]  dbHandle        The database pointer.
 *
 * @return  A PDL_STATUS.
 */
prvPdlibDDestroyStubMac(prvPdlibDbDestroy);


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
);

/**
 * @fn  void * prvPdlibOsMalloc ( IN UINT_32 size );
 *
 * @brief   malloc implementation
 *
 * @param [in]  size    memory size to allocate.
 *
 * @return  pointer to allocated memory or NULL if not possible.
 */

void * prvPdlibOsMalloc(
    IN UINT_32                    size
);

/**
 * @fn  void * prvPdlibOsCalloc ( IN UINT_32 numOfBlocks, IN UINT_32 blockSize );
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
);

/**
 * @fn  void prvPdlibOsFree ( IN void * ptr );
 *
 * @brief   free implementation
 *
 * @param [in]  ptr memory to free.
 */

void prvPdlibOsFree(
    IN void         *   ptr
);

/**
 * @fn  void prvPdlibOsPrintf ( IN char * format, ... );
 *
 * @brief   printf implementation
 *
 * @param [in]  format  format of string to print.
 * @param [in]  ...     additional arguments.
 */

void prvPdlibOsPrintf(
    IN char * format,
    ...
);

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
);

/**
 * @fn  BOOLEAN prvPdlibDebugLogHdr ( IN const char * func_name_PTR, IN UINT_32 line_num);
 *
 * @brief   printf implementation
 *
 * @param [in]  func_name_PTR   calling function name.
 * @param [in]  line_num        line number.
 * @return true if succeeded.
 */

BOOLEAN prvPdlibDebugLogHdr(
    IN const char    * func_name_PTR,
    IN UINT_32         line_num
);

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
);

/**
 * @fn  BOOLEAN prvPdlibDebugRawLog ( IN const char * func_name_PTR, IN UINT_32 line_num);
 *
 * @brief   printf implementation
 *
 * @param [in]  func_name_PTR   calling function name.
 * @param [in]  line_num        line number.
 * @return true if succeeded.
 */

void prvPdlibDebugRawLog(
    IN const char * func_name_PTR,
    IN UINT_32      line,
    IN const char * format,
    IN ...
);

/**
 * @fn  void prvPdlDebugLog ( IN const char * func_name_PTR, IN const char * format, IN ... );
 *
 * @brief   debug log implementation
 *
 * @param [in]  func_name_PTR   calling function name.
 * @param [in]  format          format of string to print.
 * @param [in]  ...             additional arguments.
 */

void prvPdlDebugLog(
    IN const char * func_name_PTR,
    IN const char * format,
    IN ...
);

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
);
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
);

/*$ END OF prvPdlXmlVerificationHandler */

/* ***************************************************************************
* FUNCTION NAME: prvPdlLibStrdup
*
* DESCRIPTION:   string duplication using local memory allocation callback
*
*****************************************************************************/

extern char *prvPdlLibStrdup(
    /*!     INPUTS:             */
    const char *str1
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
);

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
);

/*$ END OF prvPdlLibStrtok_r */

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
);

/* @}*/

#ifdef __cplusplus
}
#endif

#endif
