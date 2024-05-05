/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
********************************************************************************
 * @file pdlLibLinkedList.c
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
#include <pdlib/lib/private/prvPdlLibLinkedList.h>

/* *************************************************************************
 *$              LOCAL VARIABLE DEFINITIONS
 *!**************************************************************************
 *!*/

/* *************************************************************************
 *$              LOCAL FUNCTION DEFINITIONS
 *!**************************************************************************
 *!*/

/*****************************************************************************
* FUNCTION NAME: prvPdlibDLinkedListCreate
*
* DESCRIPTION:  create a new list
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListCreate ( IN PRV_PDLIB_DB_ATTRIBUTES_STC * dbAttributes, OUT PRV_PDLIB_DB_TYP * dbHandlePtr )
 *
 * @brief   Prv pdl database linked list create
 *
 * @param [in,out]  dbAttributes    If non-null, the database attributes.
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListCreate(
    IN  PRV_PDLIB_DB_ATTRIBUTES_STC   * dbAttributes,
    OUT PRV_PDLIB_DB_TYP              * dbHandlePtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_LIST_ATTRIBUTES_STC          * listAttributesPtr;
    PDLIB_DB_PRV_LIST_STC                     * listDbPtr;
    PRV_PDLIB_DB_STC                          * dbPtr = (PRV_PDLIB_DB_STC *)dbHandlePtr;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    listAttributesPtr = (PRV_PDLIB_DB_LIST_ATTRIBUTES_STC*)&dbAttributes->listAttributes;

    dbPtr->dbType = PRV_PDLIB_DB_TYPE_LIST_E;
    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) prvPdlibOsMalloc(sizeof(PDLIB_DB_PRV_LIST_STC));
    if (listDbPtr == NULL) {
        return PDL_NO_RESOURCE;
    }
    dbPtr->dbPtr = (void*) listDbPtr;
    listDbPtr->dataSize = listAttributesPtr->entrySize;
    listDbPtr->keySize = listAttributesPtr->keySize;
    listDbPtr->headPtr = listDbPtr->tailPtr = NULL;
    listDbPtr->listSize = 0;
    return PDL_OK;
}
/*$ END OF prvPdlibDLinkedListCreate */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDLinkedListAddAllocated
*
* DESCRIPTION:  adds an allocated entry to list
*
*
*****************************************************************************/

/**
 * @fn  static PDL_STATUS prvPdlibDLinkedListAddAllocated ( IN PDLIB_DB_PRV_LIST_STC * listDbPtr, IN void * srcEntryPtr, IN UINT_32 dataSize, OUT PDLIB_DB_PRV_LIST_ENTRY_STC * addedEntryPtr )
 *
 * @brief   Prv pdl database linked list add allocated
 *
 * @param [in,out]  listDbPtr       If non-null, the list database pointer.
 * @param [in,out]  srcEntryPtr     If non-null, source entry pointer.
 * @param           dataSize        Size of the data.
 * @param [in,out]  addedEntryPtr   If non-null, the added entry pointer.
 *
 * @return  A PDL_STATUS.
 */

static PDL_STATUS prvPdlibDLinkedListAddAllocated(
    IN  PDLIB_DB_PRV_LIST_STC         * listDbPtr,
    IN  void                        * srcEntryPtr,
    IN  UINT_32                       dataSize,
    OUT PDLIB_DB_PRV_LIST_ENTRY_STC   * addedEntryPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/

    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (listDbPtr == NULL || srcEntryPtr == NULL || addedEntryPtr == NULL) {
        return PDL_BAD_PTR;
    }
    if (dataSize == 0) {
        return PDL_BAD_PARAM;
    }

    /* add to end of list */
    if (listDbPtr->tailPtr != NULL) {
        listDbPtr->tailPtr->nextPtr = addedEntryPtr;
    }
    listDbPtr->tailPtr = addedEntryPtr;
    /* first entry */
    if (listDbPtr->headPtr == NULL) {
        listDbPtr->headPtr = addedEntryPtr;
    }

    listDbPtr->listSize++;

    return PDL_OK;

}
/*$ END OF prvPdlibDLinkedListAddAllocated */



/*****************************************************************************
* FUNCTION NAME: prvPdlibDLinkedListAdd
*
* DESCRIPTION:  allocate space for entry
*               add entry to end of list
*               return pointer to this entry
*
*
*****************************************************************************/

/**
 * @fn  static PDL_STATUS prvPdlibDLinkedListAddWithSize ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, IN void * srcEntryPtr, IN UINT_32 dataSize, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database linked list add with size
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  srcEntryPtr     If non-null, source entry pointer.
 * @param           dataSize        Size of the data.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

static PDL_STATUS prvPdlibDLinkedListAddWithSize(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    IN  void                  * srcEntryPtr,
    IN  UINT_32                 dataSize,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDL_STATUS                            pdlRc;
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PDLIB_DB_PRV_LIST_ENTRY_STC           * addedEntryPtr;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dataSize == 0) {
        return PDL_BAD_PARAM;
    }
    if (dbPtr == NULL || srcEntryPtr == NULL || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }

    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) dbPtr->dbPtr;
    if (listDbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }
    /* allocate entry */
    addedEntryPtr = (PDLIB_DB_PRV_LIST_ENTRY_STC*) prvPdlibOsMalloc(sizeof(PDLIB_DB_PRV_LIST_ENTRY_STC));
    if (addedEntryPtr == NULL) {
        return PDL_NO_RESOURCE;
    }

    /* allocate data for entry */
    addedEntryPtr->dataPtr = prvPdlibOsMalloc(dataSize);
    if (addedEntryPtr->dataPtr == NULL) {
        free(addedEntryPtr);
        return PDL_NO_RESOURCE;
    }

    addedEntryPtr->keyPtr = prvPdlibOsMalloc(listDbPtr->keySize);
    if (addedEntryPtr->keyPtr == NULL) {
        free(addedEntryPtr->dataPtr);
        free(addedEntryPtr);
        return PDL_NO_RESOURCE;
    }

    memcpy(addedEntryPtr->dataPtr, srcEntryPtr, dataSize);
    memcpy(addedEntryPtr->keyPtr, keyPtr, listDbPtr->keySize);
    addedEntryPtr->dataSize = dataSize;
    addedEntryPtr->nextPtr = NULL;

    pdlRc = prvPdlibDLinkedListAddAllocated(listDbPtr, srcEntryPtr, dataSize, addedEntryPtr);
    PDLIB_CHECK_STATUS(pdlRc);
    *outEntryPtrPtr = addedEntryPtr->dataPtr;

    return PDL_OK;
}
/*$ END OF prvPdlibDLinkedListAdd */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDLinkedListAdd
*
* DESCRIPTION:  allocate space for entry
*               add entry to end of list
*               return pointer to this entry
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListAdd ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, IN void * srcEntryPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database linked list add
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  srcEntryPtr     If non-null, source entry pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListAdd(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    IN  void                  * srcEntryPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || srcEntryPtr == NULL || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }
    if (PDL_OK == prvPdlibDLinkedListFind(dbHandle, keyPtr, outEntryPtrPtr)) {
        return PDL_ALREADY_EXIST;
    }
    listDbPtr = (PDLIB_DB_PRV_LIST_STC*)dbPtr->dbPtr;
    return prvPdlibDLinkedListAddWithSize(dbPtr, keyPtr, srcEntryPtr, listDbPtr->dataSize, outEntryPtrPtr);
}
/*$ END OF prvPdlibDLinkedListAdd */

/*****************************************************************************
* FUNCTION NAME: pdlPrvDbLinkedListGetSize
*
* DESCRIPTION:
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListGetNumOfEntries ( IN PRV_PDLIB_DB_TYP dbHandle, OUT UINT_32 * numPtr )
 *
 * @brief   Prv pdl database linked list get number of entries
 *
 * @param [in,out]  dbHandle If non-null, the database pointer.
 * @param [in,out]  numPtr   If non-null, number of pointers.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListGetNumOfEntries(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT UINT_32               * numPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL) {
        return PDL_BAD_PTR;
    }
    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) dbPtr->dbPtr;
    if (listDbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }
    *numPtr = listDbPtr->listSize;

    return PDL_OK;
}
/*$ END OF pdlPrvDbLinkedListGetSize */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDLinkedListFind
*
* DESCRIPTION:  find an entry based on key comparison (entry MUST include key at start)
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListFind ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database linked list find
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListFind(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PDLIB_DB_PRV_LIST_ENTRY_STC           * entryPtr = NULL;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || keyPtr == NULL || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }
    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) dbPtr->dbPtr;
    if (listDbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    entryPtr = listDbPtr->headPtr;
    while (entryPtr) {
        if (memcmp(entryPtr->keyPtr, keyPtr, listDbPtr->keySize) == 0) {
            break;
        }
        entryPtr = entryPtr->nextPtr;
    }

    if (entryPtr == NULL) {
        *outEntryPtrPtr = NULL;
        return PDL_NOT_FOUND;
    }
    *outEntryPtrPtr = entryPtr->dataPtr;
    return PDL_OK;
}
/*$ END OF prvPdlibDLinkedListFind */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDLinkedListGetNext
*
* DESCRIPTION:  find an entry based on key comparison (entry MUST include key at start)
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListGetNext ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database linked list get next
 *
 * @param [in,out]  dbPtr           If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListGetNext(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PDLIB_DB_PRV_LIST_ENTRY_STC           * entryPtr = NULL;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/

    if (dbPtr == NULL || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }

    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) dbPtr->dbPtr;
    if (listDbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    entryPtr = listDbPtr->headPtr;

    if (keyPtr) {
        while (entryPtr) {
            if (memcmp(entryPtr->keyPtr, keyPtr, listDbPtr->keySize) == 0) {
                entryPtr = entryPtr->nextPtr;
                break;
            }
            entryPtr = entryPtr->nextPtr;
        }
    }

    if (entryPtr == NULL) {
        *outEntryPtrPtr = NULL;
        return PDL_NO_MORE;
    }

    *outEntryPtrPtr = entryPtr->dataPtr;
    return PDL_OK;
}
/*$ END OF prvPdlibDLinkedListGetNext */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDLinkedListGetNextKey
*
* DESCRIPTION:  find the key of the next entry
*
*
*****************************************************************************/

PDL_STATUS prvPdlibDLinkedListGetNextKey(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                  * nextKeyPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PDLIB_DB_PRV_LIST_ENTRY_STC           * entryPtr = NULL;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/

    if (dbPtr == NULL || nextKeyPtr == NULL) {
        return PDL_BAD_PTR;
    }

    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) dbPtr->dbPtr;
    if (listDbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    entryPtr = listDbPtr->headPtr;

    if (keyPtr) {
        while (entryPtr) {
            if (memcmp(entryPtr->keyPtr, keyPtr, listDbPtr->keySize) == 0) {
                entryPtr = entryPtr->nextPtr;
                break;
            }
            entryPtr = entryPtr->nextPtr;
        }
    }

    if (entryPtr == NULL) {
        return PDL_NO_MORE;
    }

    memcpy(nextKeyPtr, entryPtr->keyPtr, listDbPtr->keySize);
    return PDL_OK;
}

/*$ END OF prvPdlibDLinkedListGetNextKey */

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListGetFirst ( IN PRV_PDLIB_DB_TYP dbHandle, OUT void ** outEntryPtrPtr )
 *
 * @brief   find first entry in linked list
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListGetFirst(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PDLIB_DB_PRV_LIST_ENTRY_STC           * entryPtr = NULL;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/

    if (dbPtr == NULL || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }

    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) dbPtr->dbPtr;
    if (listDbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    entryPtr = listDbPtr->headPtr;
    if (entryPtr != NULL) {
        *outEntryPtrPtr = entryPtr->dataPtr;
        return PDL_OK;
    }

    return PDL_NOT_FOUND;
}
/*$ END OF prvPdlibDLinkedListGetFirst */

/**
 * @fn  PDL_STATUS prvPdlibDLinkedListDestroy ( IN PRV_PDLIB_DB_TYP dbHandle )
 *
 * @brief   free memory used by list db
 *
 * @param [in,out]  dbHandle           If non-null, the database pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDLinkedListDestroy(
    IN  PRV_PDLIB_DB_TYP          dbHandle
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDLIB_DB_PRV_LIST_STC                 * listDbPtr;
    PDLIB_DB_PRV_LIST_ENTRY_STC           * entryPtr = NULL, * nextEntryPtr = NULL;
    PRV_PDLIB_DB_STC                      * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL) {
        return PDL_BAD_PTR;
    }

    listDbPtr = (PDLIB_DB_PRV_LIST_STC*) dbPtr->dbPtr;
    if (listDbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    entryPtr = listDbPtr->headPtr;
    while (entryPtr) {
        nextEntryPtr = entryPtr->nextPtr;

        prvPdlibOsFree(entryPtr->dataPtr);
        prvPdlibOsFree(entryPtr->keyPtr);
        prvPdlibOsFree(entryPtr);
        entryPtr = nextEntryPtr;
    }

    prvPdlibOsFree(listDbPtr);
    dbPtr->dbPtr = NULL;
    return PDL_OK;
}

/*$ END OF prvPdlibDLinkedListDestroy */
