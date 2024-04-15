/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\h\lib\private\prvpdlliblinkedlist.h.
 *
 * @brief   Declares the prvpdlliblinkedlist class
 */

#ifndef __prvPdlLibPdlLibLinkedListLinkedListh

#define __prvPdlLibPdlLibLinkedListLinkedListh
/**
********************************************************************************
 * @file prvPdlLibLinkedList.h
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
#include <pdlib/lib/private/prvPdlLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup Library
 * @{Library APIs
 */

/**
 * @defgroup Library_linked_list Linked List
 * @{Library APIs
 */

/**
 * @struct  PDLIB_DB_PRV_LIST_ENTRY_STCT
 *
 * @brief   defines structure for linked list entry
 */

typedef struct PDLIB_DB_PRV_LIST_ENTRY_STCT {

    /**
     * @struct  PDLIB_DB_PRV_LIST_ENTRY_STCT*
     *
     * @brief   A pdl database prv list entry stct*.
     */

    struct PDLIB_DB_PRV_LIST_ENTRY_STCT   * nextPtr;
    /** @brief   The data pointer */
    void                                * dataPtr;
    /** @brief   The key pointer */
    void                                * keyPtr;
    /** @brief   Size of the data */
    UINT_32                               dataSize;
} PDLIB_DB_PRV_LIST_ENTRY_STC;

/**
 * @struct  PDLIB_DB_PRV_LIST_STC
 *
 * @brief   defines structure for linked list
 */

typedef struct  {
    /** @brief   The list name pointer */
    char                              * listNamePtr;  /* name - for debug */
    /** @brief   Size of the data */
    UINT_32                             dataSize;       /* size of entry, excluding next/prev pointers or other additional */
    /** @brief   Size of the key */
    UINT_32                             keySize;
    /** @brief   The head pointer */
    PDLIB_DB_PRV_LIST_ENTRY_STC         * headPtr;
    /** @brief   The tail pointer */
    PDLIB_DB_PRV_LIST_ENTRY_STC         * tailPtr;
    /** @brief   Size of the list */
    UINT_32                             listSize;       /* number of entries in the list*/
} PDLIB_DB_PRV_LIST_STC;

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListGetNumOfEntries ( IN PRV_PDLIB_DB_TYP dbHandle, OUT UINT_32 * numPtr );
 *
 * @brief   Get Linked List size (number of entries)
 *
 * @param [in]  dbHandle - pointer to Linked List.
 * @param [out] numPtr   - num of entries in linked list.
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListGetNumOfEntries(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT UINT_32               * numPtr
);

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListCreate ( IN PRV_PDLIB_DB_ATTRIBUTES_STC * dbAttributes, OUT PRV_PDLIB_DB_TYP * dbHandle );
 *
 * @brief   Get Linked List size (number of entries)
 *
 * @param [in]  dbAttributes    - Linked list attributes.
 * @param [out] dbHandle        - pointer to created db structure.
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListCreate(
    IN  PRV_PDLIB_DB_ATTRIBUTES_STC   * dbAttributes,
    OUT PRV_PDLIB_DB_TYP              * dbHandle
);

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListAdd ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, IN void * srcEntryPtr, OUT void ** outEntryPtrPtr );
 *
 * @brief   Add instance to linked list DB
 *
 * @param [in]  dbHandle        - pointer to DB.
 * @param [in]  keyPtr          - key pointer.
 * @param [in]  srcEntryPtr     - entry pointer.
 * @param [out] outEntryPtrPtr  - pointer to inserted entry.
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListAdd(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    IN  void                  * srcEntryPtr,
    OUT void                 ** outEntryPtrPtr
);

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListFind ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr );
 *
 * @brief   Find instance in linked list DB
 *
 * @param [in]  dbHandle        - pointer to DB.
 * @param [in]  keyPtr          - pointer to searched key.
 * @param [out] outEntryPtrPtr  - pointer entry found in DB (or NULL if not found)
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListFind(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
);

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListGetNext ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr );
 *
 * @brief   Find next instance in linked list DB
 *
 * @param [in]  dbHandle        - pointer to DB.
 * @param [in]  keyPtr          - pointer to searched key (or NULL to get first entry)
 * @param [out] outEntryPtrPtr  - pointer entry found in DB (or NULL if not found)
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListGetNext(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
);

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListGetFirst ( IN PRV_PDLIB_DB_TYP dbHandle, OUT void ** outEntryPtrPtr )
 *
 * @brief   find first entry in linked list
 *
 * @param [in]   dbHandle        the database pointer.
 * @param [out]  outEntryPtrPtr  the first entry in DB.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListGetFirst(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT void                 ** outEntryPtrPtr
);

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListGetNextKey ( IN PRV_PDLIB_DB_TYP dbHandle, IN  void * keyPtr, OUT void * nextKeyPtr )
 *
 * @brief   find the key of the next entry
 *
 * @param [in]  dbHandle    the database pointer.
 * @param [in]  keyPtr      If non-null, the key to start from. if null - next will be first
 * @param [out] nextKeyPtr  next entry key
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListGetNextKey(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                  * nextKeyPtr
);


/**
 * @fn  PDL_STATUS prvPdlibDLinkedListDestroy ( IN PRV_PDLIB_DB_TYP dbHandle )
 *
 * @brief   free memory used by list db
 *
 * @param [in]  dbHandle        If non-null, the database pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListDestroy(
    IN  PRV_PDLIB_DB_TYP          dbHandle
);


/* @}*/
/* @}*/

#ifdef __cplusplus
}
#endif

#endif