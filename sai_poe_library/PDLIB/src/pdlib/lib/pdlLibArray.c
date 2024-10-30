/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
********************************************************************************
 * @file pdlLibArray.c
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
#include <pdlib/lib/private/prvPdlLibArray.h>

/* *************************************************************************
 *$              LOCAL VARIABLE DEFINITIONS
 *!**************************************************************************
 *!*/

/* *************************************************************************
 *$              LOCAL FUNCTION DEFINITIONS
 *!**************************************************************************
 *!*/

/*****************************************************************************
* FUNCTION NAME: prvPdlibDArrayCreate
*
* DESCRIPTION:  create a new array
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDArrayCreate ( IN PRV_PDLIB_DB_ATTRIBUTES_STC * dbAttributes, OUT PRV_PDLIB_DB_TYP * dbHandlePtr )
 *
 * @brief   Prv pdl database array create
 *
 * @param [in,out]  dbAttributes    If non-null, the database attributes.
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayCreate(
    IN  PRV_PDLIB_DB_ATTRIBUTES_STC   * dbAttributes,
    OUT PRV_PDLIB_DB_TYP              * dbHandlePtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    UINT_32                                   i, alignedKeySize, alignedEntrySize;
    PRV_PDLIB_DB_ARRAY_ATTRIBUTES_STC         * attributesPtr;
    PRV_PDLIB_DB_PRV_ARRAY_STC                * arrDbPtr;
    PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC          * entryPtr;
    PRV_PDLIB_DB_STC                          * dbPtr = (PRV_PDLIB_DB_STC *)dbHandlePtr;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    attributesPtr = (PRV_PDLIB_DB_ARRAY_ATTRIBUTES_STC*)&dbAttributes->listAttributes;

    dbPtr->dbType = PRV_PDLIB_DB_TYPE_ARRAY_E;
    arrDbPtr = (PRV_PDLIB_DB_PRV_ARRAY_STC*) prvPdlibOsCalloc(sizeof(PRV_PDLIB_DB_PRV_ARRAY_STC), 1);
    if (arrDbPtr == NULL) {
        return PDL_NO_RESOURCE;
    }
    dbPtr->dbPtr = arrDbPtr;

    arrDbPtr->keyToIndexFuncPtr = attributesPtr->keyToIndexFunc;
    arrDbPtr->numOfEntries = attributesPtr->numOfEntries;
    arrDbPtr->keySize = attributesPtr->keySize;
    arrDbPtr->entrySize = attributesPtr->entrySize;

    arrDbPtr->entriesPtr = (PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC *) prvPdlibOsMalloc(sizeof(PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC) * arrDbPtr->numOfEntries);
    if (arrDbPtr->entriesPtr == NULL) {
        free(arrDbPtr);
        return PDL_NO_RESOURCE;
    }

    alignedEntrySize = PDL_ALIGN_ARCH_WORD(attributesPtr->entrySize);
    alignedKeySize = PDL_ALIGN_ARCH_WORD(attributesPtr->keySize);
    arrDbPtr->memoryPtr = (UINT_8 *) prvPdlibOsMalloc((alignedKeySize + alignedEntrySize) * arrDbPtr->numOfEntries);
    if (arrDbPtr->memoryPtr == NULL) {
        free(arrDbPtr->entriesPtr);
        free(arrDbPtr);
        return PDL_NO_RESOURCE;
    }

    for (i = 0; i < arrDbPtr->numOfEntries; i ++) {
        entryPtr = &arrDbPtr->entriesPtr[i];
        entryPtr->isValid = FALSE;
        entryPtr->keyPtr = arrDbPtr->memoryPtr + (alignedKeySize + alignedEntrySize) * i;
        entryPtr->entryPtr = arrDbPtr->memoryPtr + (alignedKeySize + alignedEntrySize) * i + alignedKeySize;
    }

    return PDL_OK;
}
/*$ END OF prvPdlibDArrayCreate */


/*****************************************************************************
* FUNCTION NAME: prvPdlibDArrayGetEntry
*
* DESCRIPTION:  find an entry based on key
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDArrayGetEntry ( IN PRV_PDLIB_DB_PRV_ARRAY_STC * arrDbPtr, IN void * keyPtr, OUT PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC **outEntryPtrPtr )
 *
 * @brief   Prv pdl database array get entry
 *
 * @param [in,out]  arrDbPtr        If non-null, the array database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayGetEntry(
    IN  PRV_PDLIB_DB_PRV_ARRAY_STC        * arrDbPtr,
    IN  void                            * keyPtr,
    OUT PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC  **outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    UINT_32     index;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (arrDbPtr->keyToIndexFuncPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }
    index = arrDbPtr->keyToIndexFuncPtr(keyPtr);

    if (index >= arrDbPtr->numOfEntries) {
        return PDL_OUT_OF_RANGE;
    }

    *outEntryPtrPtr = &arrDbPtr->entriesPtr[index];

    return PDL_OK;
}
/*$ END OF prvPdlibDArrayGetEntry */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDArrayAdd
*
* DESCRIPTION:  copy entry data to array
*               return pointer to this entry
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDArrayAdd ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, IN void * srcEntryPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database array add
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  srcEntryPtr     If non-null, source entry pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayAdd(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    IN  void                  * srcEntryPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDL_STATUS                          result;
    PRV_PDLIB_DB_PRV_ARRAY_STC          * arrDbPtr;
    PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC    * entryPtr;
    PRV_PDLIB_DB_STC                    * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || (dbPtr->dbType != PRV_PDLIB_DB_TYPE_ARRAY_E) || srcEntryPtr == NULL || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }

    if (dbPtr->dbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    arrDbPtr = (PRV_PDLIB_DB_PRV_ARRAY_STC *)dbPtr->dbPtr;

    if (arrDbPtr->validCount == arrDbPtr->numOfEntries) {
        return PDL_FULL;
    }

    result = prvPdlibDArrayGetEntry(arrDbPtr, keyPtr, &entryPtr);
    if (result != PDL_OK) {
        return result;
    }

    if (entryPtr->isValid) {
        return PDL_ALREADY_EXIST;
    }

    entryPtr->isValid = TRUE;
    memcpy(entryPtr->keyPtr, keyPtr, arrDbPtr->keySize);
    memcpy(entryPtr->entryPtr, srcEntryPtr, arrDbPtr->entrySize);
    *outEntryPtrPtr = entryPtr->entryPtr;
    arrDbPtr->validCount ++;

    return PDL_OK;
}
/*$ END OF prvPdlibDArrayAdd */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDArrayFind
*
* DESCRIPTION:  find an entry based on index
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDArrayFind ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database array find
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayFind(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PDL_STATUS                          result;
    PRV_PDLIB_DB_PRV_ARRAY_STC          * arrDbPtr;
    PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC    * entryPtr;
    PRV_PDLIB_DB_STC                    * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || (dbPtr->dbType != PRV_PDLIB_DB_TYPE_ARRAY_E) || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }

    if (dbPtr->dbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    arrDbPtr = (PRV_PDLIB_DB_PRV_ARRAY_STC *)dbPtr->dbPtr;

    if (arrDbPtr->validCount == 0) {
        return PDL_EMPTY;
    }

    result = prvPdlibDArrayGetEntry(arrDbPtr, keyPtr, &entryPtr);
    if (result != PDL_OK) {
        return result;
    }

    if (entryPtr->isValid == FALSE) {
        return PDL_NO_SUCH;
    }

    if (memcmp(entryPtr->keyPtr, keyPtr, arrDbPtr->keySize)) {
        return PDL_NO_SUCH;
    }

    *outEntryPtrPtr = entryPtr->entryPtr;

    return PDL_OK;
}
/*$ END OF prvPdlibDArrayFind */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDArrayGetNext
*
* DESCRIPTION:  find next entry based on index
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDArrayGetNext ( IN PRV_PDLIB_DB_TYP dbHandle, IN void * keyPtr, OUT void ** outEntryPtrPtr )
 *
 * @brief   Prv pdl database array get next
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  keyPtr          If non-null, the key pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayGetNext(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    IN  void                  * keyPtr,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    UINT_32                             i;
    PRV_PDLIB_DB_PRV_ARRAY_STC          * arrDbPtr;
    PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC    * entryPtr;
    PRV_PDLIB_DB_STC                    * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || (dbPtr->dbType != PRV_PDLIB_DB_TYPE_ARRAY_E) || outEntryPtrPtr == NULL) {
        return PDL_BAD_PTR;
    }

    if (dbPtr->dbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    arrDbPtr = (PRV_PDLIB_DB_PRV_ARRAY_STC *)dbPtr->dbPtr;

    entryPtr = NULL;

    if (keyPtr == NULL) {
        i = 0;
    }
    else {
        i = arrDbPtr->keyToIndexFuncPtr(keyPtr) + 1;
    }
    for (; i < arrDbPtr->numOfEntries; i++) {
        if (arrDbPtr->entriesPtr[i].isValid) {
            entryPtr = &arrDbPtr->entriesPtr[i];
            break;
        }
    }

    if (entryPtr == NULL) {
        return PDL_NO_MORE;
    }

    *outEntryPtrPtr = entryPtr->entryPtr;
    return PDL_OK;
}
/*$ END OF prvPdlibDArrayGetNext */

/*****************************************************************************
* FUNCTION NAME: prvPdlibDArrayGetNumOfEntries
*
* DESCRIPTION:
*
*
*****************************************************************************/

/**
 * @fn  PDL_STATUS prvPdlibDArrayGetNumOfEntries ( IN PRV_PDLIB_DB_TYP dbHandle, OUT UINT_32 * numPtr )
 *
 * @brief   Prv pdl database array get number of entries
 *
 * @param [in,out]  dbHandle If non-null, the database pointer.
 * @param [in,out]  numPtr   If non-null, number of pointers.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayGetNumOfEntries(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT UINT_32               * numPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_PRV_ARRAY_STC          * arrDbPtr;
    PRV_PDLIB_DB_STC                    * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || (dbPtr->dbType != PRV_PDLIB_DB_TYPE_ARRAY_E)) {
        return PDL_BAD_PTR;
    }

    if (dbPtr->dbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    arrDbPtr = (PRV_PDLIB_DB_PRV_ARRAY_STC*) dbPtr->dbPtr;

    *numPtr = arrDbPtr->validCount;

    return PDL_OK;
}
/*$ END OF prvPdlibDArrayGetNumOfEntries */

/**
 * @fn  PDL_STATUS prvPdlibDArrayGetFirst ( IN PRV_PDLIB_DB_TYP dbHandle, OUT void ** outEntryPtrPtr )
 *
 * @brief   find first entry in array
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 * @param [in,out]  outEntryPtrPtr  If non-null, the out entry pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayGetFirst(
    IN  PRV_PDLIB_DB_TYP          dbHandle,
    OUT void                 ** outEntryPtrPtr
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    UINT_32                             i;
    PRV_PDLIB_DB_PRV_ARRAY_STC          * arrDbPtr;
    PRV_PDLIB_DB_PRV_ARRAY_ENTRY_STC    * entryPtr = NULL;
    PRV_PDLIB_DB_STC                    * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL || (dbPtr->dbType != PRV_PDLIB_DB_TYPE_ARRAY_E)) {
        return PDL_BAD_PTR;
    }

    if (dbPtr->dbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    arrDbPtr = (PRV_PDLIB_DB_PRV_ARRAY_STC*) dbPtr->dbPtr;

    for (i = 0; i < arrDbPtr->numOfEntries; i++) {
        if (arrDbPtr->entriesPtr[i].isValid) {
            entryPtr = &arrDbPtr->entriesPtr[i];
            break;
        }
    }
    if (entryPtr == NULL) {
        return PDL_NOT_FOUND;
    }

    *outEntryPtrPtr = entryPtr->entryPtr;
    return PDL_OK;
}

/*$ END OF prvPdlibDArrayGetFirst */

/**
 * @fn  PDL_STATUS prvPdlibDArrayDestroy ( IN PRV_PDLIB_DB_TYP dbHandle )
 *
 * @brief   free memory used by array db
 *
 * @param [in,out]  dbHandle        If non-null, the database pointer.
 *
 * @return  A PDL_STATUS.
 */

PDL_STATUS prvPdlibDArrayDestroy(
    IN  PRV_PDLIB_DB_TYP          dbHandle
)
{
    /*!****************************************************************************/
    /*! L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /*!****************************************************************************/
    PRV_PDLIB_DB_PRV_ARRAY_STC          * arrDbPtr;
    PRV_PDLIB_DB_STC                    * dbPtr = (PRV_PDLIB_DB_STC *)dbHandle;
    /*!****************************************************************************/
    /*!                      F U N C T I O N   L O G I C                          */
    /*!****************************************************************************/
    if (dbPtr == NULL) {
        return PDL_BAD_PTR;
    }

    if (dbPtr->dbPtr == NULL) {
        return PDL_NOT_INITIALIZED;
    }

    arrDbPtr = (PRV_PDLIB_DB_PRV_ARRAY_STC *)dbPtr->dbPtr;
    prvPdlibOsFree(arrDbPtr->entriesPtr);
    prvPdlibOsFree(arrDbPtr->memoryPtr);
    prvPdlibOsFree(arrDbPtr);

    dbPtr->dbPtr = NULL;

    return PDL_OK;
}

/*$ END OF prvPdlibDArrayDestroy */
