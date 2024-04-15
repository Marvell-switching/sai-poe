/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\h\xml\private\prvxmlparser.h.
 *
 * @brief   Declares the prvxmlparser class
 */

#ifndef __prvPdlLibXmlParserh

#define __prvPdlLibXmlParserh

#ifdef __cplusplus
extern "C" {
#endif

/**
********************************************************************************
 * @file prvXmlParser.h
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
 * @brief XML library APIs and declarations for driver level.
 *
 * @version   1
********************************************************************************
*/
#include <pdlib/common/pdlTypes.h>
#include <pdlib/xml/xmlParser.h>
#include <pdlib/xml/private/prvXmlParserData.h>
/**
* @addtogroup XML
* @{
*/

/**
* @defgroup XML_private XML Private
* @{XML related private functions
*/

/*! @def XML_PARSER_ROOT2NODE_CONVERT_MAC(_root)
    @brief A macro converting root descriptor (received from building database) to node descriptor (used from database walking)
*/
#define XML_PARSER_ROOT2NODE_CONVERT_MAC(_root) \
    ((XML_PARSER_NODE_DESCRIPTOR_TYP)(& (((PRV_XML_PARSER_ROOT_STC *)(_root))->node)))

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserBuild ( IN char * arXmlFilePathPtr, IN char * tagPefixPtr, IN BOOLEAN isEzbXml, OUT XML_PARSER_ROOT_DESCRIPTOR_TYP * rootIdPtr );
 *
 * @brief   Builds database from XML file and returns descriptor to that database.
 *
 * @param [in]  arXmlFilePathPtr Pointer to path &amp; name of compressed file.
 * @param [in]  tagPefixPtr      prefix of all tags in xml data
 * @param [in]  isEzbXml         Used to indicate whether to build string&enum conversion tables according to EZB DB or external DBs
 * @param [out] rootIdPtr        XML descriptor.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if file could not be opened XML_PARSER_RET_CODE_NO_MEM
 *          if out of memory occurred while building database
 *          XML_PARSER_RET_CODE_WRONG_FORMAT if XML file format is invalid.
 */
extern XML_PARSER_RET_CODE_TYP xmlParserBuild(
    IN  char                              * arXmlFilePathPtr,
    IN  char                              * tagPefixPtr,
    OUT XML_PARSER_ROOT_DESCRIPTOR_TYP    * rootIdPtr
);


/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserUncompressedFileBuild  ( IN char * arXmlFilePathPtr, IN char * tagPefixPtr,  IN BOOLEAN isCompress, OUT XML_PARSER_ROOT_DESCRIPTOR_TYP * rootIdPtr );
 *
 * @brief   Builds database from XML file and returns descriptor to that database.
 *
 * @param [in]  xmlFilePathPtr   Pointer to path &amp; name of xml file.
 * @param [in] signatureFilePathPtr   Pointer to path &amp; name of signature file.
 * @param [in]  tagPefixPtr      prefix of all tags in xml data
 * @param [out] rootIdPtr        XML descriptor.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND    if file could not be opened
 *          XML_PARSER_RET_CODE_NO_MEM       if out of memory occurred while building database
 *          XML_PARSER_RET_CODE_WRONG_FORMAT if XML file format is invalid.
 */
extern XML_PARSER_RET_CODE_TYP xmlParserUncompressedFileBuild(
    IN  char                              * xmlFilePathPtr,
    IN  char                              * signatureFilePathPtr,
    IN  char                              * tagPefixPtr,
    OUT XML_PARSER_ROOT_DESCRIPTOR_TYP    * rootIdPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserDestroy ( IN XML_PARSER_ROOT_DESCRIPTOR_TYP * rootIdPtr );
 *
 * @brief   Destroys database and frees all allocated memory
 *
 * @param [in,out]  rootIdPtr   If non-null, the root identifier pointer.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if wrong descriptor used.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserDestroy(
    IN XML_PARSER_ROOT_DESCRIPTOR_TYP     * rootIdPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserFindByName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * xmlTagPtr, OUT XML_PARSER_NODE_DESCRIPTOR_TYP * xmlChildIdPtr );
 *
 * @brief   Search for node by name
 *
 * @param [in]  xmlId           XML node descriptor (search will be conducted under that node)
 * @param [in]  xmlTagPtr       String to search for.
 * @param [out] xmlChildIdPtr   XML node descriptor pointing to location of the searched tag.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if not found.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserFindByName(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlId,
    IN  char                              * xmlTagPtr,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlChildIdPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserFindChildByName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * xmlTagPtr, OUT XML_PARSER_NODE_DESCRIPTOR_TYP * xmlChildIdPtr );
 *
 * @brief   Search for child node by name
 *
 * @param [in]  xmlId           XML node descriptor (search will be conducted under that node)
 * @param [in]  xmlTagPtr       String to search for.
 * @param [out] xmlChildIdPtr   XML node descriptor pointing to location of the searched tag.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if not found.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserFindChildByName(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlId,
    IN  char                              * xmlTagPtr,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlChildIdPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetFirstChild ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlParent, OUT XML_PARSER_NODE_DESCRIPTOR_TYP * xmlChildPtr );
 *
 * @brief   Gets first child of current tag (walking one level down in tree)
 *
 * @param [in]  xmlParent   XML node descriptor (search will be conducted under that node)
 * @param [out] xmlChildPtr First child of xmlParent.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if this node does not have children.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserGetFirstChild(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlParent,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlChildPtr
);

/**
* @public xmlParserGetNextSibling
* @brief Gets next sibling (brother) of current node (walking the same level in tree)
* @returns XML_PARSER_RET_CODE_NOT_FOUND if this node does not have brothers
* @param[in] xmlId XML node descriptor
* @param[out] xmlNextIdPtr Next brother of xmlId
*/
extern XML_PARSER_RET_CODE_TYP xmlParserGetNextSibling(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlId,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlNextIdPtr

    /**
     * @property    )
     *
     * @brief   Gets or sets the )
     *
     * @value   .
     */

);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, INOUT UINT_32 * outputSizePtr, OUT char * outputPtr );
 *
 * @brief   Get name of current node
 *
 * @param [in]      xmlId           XML node descriptor.
 * @param [in,out]   outputSizePtr   [IN] MAX size of outputPtr [OUT] actual size of outputPtr.
 * @param [out]     outputPtr       Name of the node.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if invalid node supplied.
 * @return  XML_PARSER_RET_CODE_BAD_SIZE if outputSizePtr parameter is not big enough.
 *          outputSizePtr will be updated to actual value.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserGetName(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    INOUT   UINT_32                       * outputSizePtr,
    OUT     char                          * outputPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserIsEqualName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * namePtr );
 *
 * @brief   Get name of current node
 *
 * @param [in]  xmlId   XML node descriptor.
 * @param [in]  namePtr Expected name of the node (null-terminated string)
 *
 * @return  XML_PARSER_RET_CODE_OK if supplied string name is equal to XML node's name.
 * @return  XML_PARSER_RET_CODE_ERROR if supplied string name is different from XML node's name.
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if invalid node supplied.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserIsEqualName(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    IN      char                          * namePtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetTagCount ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * xmlTagPtr, OUT UINT_32 * countPtr );
 *
 * @brief   Counts all tags with specified name in under xmlId (not including supplied node)
 *
 * @param [in]  xmlId       XML descriptor pointing to a specific tag.
 * @param [in]  xmlTagPtr   NULL-terminated string to search.
 * @param [out] countPtr    Number of encountered tags.
 *
 * @return  An XML_PARSER_RET_CODE_TYP.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserGetTagCount(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    IN  char                          * xmlTagPtr,
    OUT UINT_32                       * countPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetValue ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, INOUT UINT_32 * outputSizePtr, OUT void * outputPtr );
 *
 * @brief   Get value of current node
 *
 * @param [in]      xmlId           XML node descriptor.
 * @param [in,out]   outputSizePtr   [IN] MAX size of outputPtr [OUT] actual size of outputPtr.
 * @param [out]     outputPtr       Value of the node according to typedef in XML file.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if invalid node supplied.
 * @return  XML_PARSER_RET_CODE_BAD_SIZE if outputSizePtr parameter is not big enough.
 *          outputSizePtr will be updated to actual value.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserGetValue(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    INOUT   UINT_32                       * outputSizePtr,
    OUT     void                          * outputPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetIntValue ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, INOUT UINT_32 * outputSizePtr, OUT void * outputPtr )
 *
 * @brief   Get integer value of current node if possible. For enumerations UINT_8 type is used.
 *
 * @param [in]      xmlId           XML node descriptor.
 * @param [in,out]   outputSizePtr   [IN] MAX size of outputPtr [OUT] actual size of outputPtr.
 * @param [out]     outputPtr       Value of the node according to typedef in XML file.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if invalid node supplied.
 * @return  XML_PARSER_RET_CODE_WRONG_FORMAT if node has invalid type (i.e string).
 * @return  XML_PARSER_RET_CODE_BAD_SIZE if outputSizePtr parameter is not big enough.
 *          outputSizePtr will be updated to actual value.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserGetIntValue(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    INOUT   UINT_32                       * outputSizePtr,
    OUT     void                          * outputPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserSetValue ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN UINT_32 inputSize, IN void * inputPtr );
 *
 * @brief   Update value of the current node
 *
 * @param [in]  xmlId       XML node descriptor.
 * @param [in]  inputSize   size of inputPtr.
 * @param [in]  inputPtr    Value of the node according to typedef in XML file.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if invalid node supplied.
 * @return  XML_PARSER_RET_CODE_WRONG_FORMAT if inputPtr does not pass data format validation.
 * @return  XML_PARSER_RET_CODE_NO_MEM if memory allocation failed.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserSetValue(
    IN   XML_PARSER_NODE_DESCRIPTOR_TYP xmlId,
    IN   UINT_32                        inputSize,
    IN   void                         * inputPtr
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserSetIntValue ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN UINT_32 inputSize, IN void * inputPtr )
 *
 * @brief   Update value of the current node if possible. For enumerations UINT_8 type is used.
 *
 * @param [in]  xmlId       XML node descriptor.
 * @param [in]  inputSize   size of inputPtr.
 * @param [in]  inputPtr    Value of the node according to typedef in XML file.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM  if invalid node supplied.
 * @return  XML_PARSER_RET_CODE_WRONG_FORMAT if inputPtr does not pass data format validation.
 * @return  XML_PARSER_RET_CODE_NO_MEM       if memory allocation failed.
 */

extern XML_PARSER_RET_CODE_TYP xmlParserSetIntValue(
    IN   XML_PARSER_NODE_DESCRIPTOR_TYP xmlId,
    IN   UINT_32                        inputSize,
    IN   void                         * inputPtr
);

/* @}*/
/* @}*/

/**
 * @fn  BOOLEAN prvXmlParserDebugGetNextOpenedRoot ( INT_32 * indexPtr );
 *
 * @brief   Update value of the current node
 *
 * @param [in,out]  indexPtr    If non-null, the index pointer.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if invalid node supplied.
 * @return  XML_PARSER_RET_CODE_WRONG_FORMAT if inputPtr does not pass data format validation.
 * @return  XML_PARSER_RET_CODE_NO_MEM if memory allocation failed.
 */

extern BOOLEAN prvXmlParserDebugGetNextOpenedRoot(
    INT_8  * indexPtr
);

/**
 * @fn  BOOLEAN prvXmlParserDebugShowTreeByRoot ( UINT_32 rootIndex, char *tagPtr, BOOLEAN printWithValues );
 *
 * @brief   Update value of the current node
 *
 * @param           rootIndex       Zero-based index of the root.
 * @param [in,out]  tagPtr          If non-null, the tag pointer.
 * @param           printWithValues True to print with values.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if invalid node supplied.
 * @return  XML_PARSER_RET_CODE_WRONG_FORMAT if inputPtr does not pass data format validation.
 * @return  XML_PARSER_RET_CODE_NO_MEM if memory allocation failed.
 */

extern BOOLEAN prvXmlParserDebugShowTreeByRoot(
    UINT_32         rootIndex,
    char           *tagPtr,
    BOOLEAN         printWithValues
);

/**
 * @fn  BOOLEAN xmlParserExternalEnumDbBuild ( IN PRV_XML_PARSER_ROOT_STC * rootPtr )
 *
 * @brief   Build external enum database.
 *
 * @param [in]      rootIdPtr                       XML tree root instance.
 * @param [in]      externalEnumStringArr           external db with all enumerated strings
 * @param [in]      externalEnumStringArrSize       external db size
 * @param [in,out]   externalEnumDbArr               external db that will point to relevant enum information MUST be the size of externalEnumStringArrSize
 *
 * @return  XML_PARSER_RET_CODE_NOT_INITIALIZED if database wasn't initialized
 * @return  XML_PARSER_RET_CODE_NOT_FOUND       if encountered unknown.
 *
 */
XML_PARSER_RET_CODE_TYP xmlParserExternalEnumDbBuild(

    IN    XML_PARSER_NODE_DESCRIPTOR_TYP          rootId,
    IN    char                                 ** externalEnumStringArr,
    IN    UINT_32                                 externalEnumStringArrSize,
    INOUT XML_PARSER_ENUM_DB_STC               ** externalEnumDbArr
);

#ifdef __cplusplus
}
#endif

#endif
