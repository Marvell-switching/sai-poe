/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\src\xml\xmlparserappintf.c.
 *
 * @brief   Xmlparserappintf class
 */

#include <pdlib/common/pdlTypes.h>
#include <pdlib/lib/private/prvPdlLib.h>
#include <pdlib/xml/private/prvXmlParserBuilder.h>
#include <pdlib/xml/private/prvXmlParserData.h>
#include <pdlib/xml/xmlParser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char prvXmlParserSpaceSymbol = ' ';

/**
 * @fn  static char * prvXmlParserReadFile ( IN char * xmlFilePathPtr, OUT UINT_32 * sizePtr )
 *
 * @brief   Allocates memory and reads file to that memory.
 *
 * @param [in]  arXmlFilePathPtr archived XML file path &amp; name to read.
 * @param [out] sizePtr          Read file size.
 *
 * @return  Null if it fails, else a pointer to a char.
 */

static char * prvXmlParserReadFile(
    IN  char      * xmlFilePathPtr,
    OUT UINT_32   * sizePtr
)
{
    FILE                          * xmlFilePtr;
    char                          * xmlFileDataPtr;
    UINT_32                         size;


    XML_PARSER_FOPEN_MAC(xmlFilePtr, xmlFilePathPtr, "rb");
    if (!xmlFilePtr) {
        return NULL;
    }

    fseek(xmlFilePtr, 0, SEEK_END);
    *sizePtr = size = ftell(xmlFilePtr);
    xmlFileDataPtr = (char *)prvPdlibOsMalloc((size + 1) * sizeof(char));
    if (!xmlFileDataPtr) {
        fclose(xmlFilePtr);
        return NULL;
    }
    rewind(xmlFilePtr);

    if (size != fread(xmlFileDataPtr, 1, size, xmlFilePtr)) {
        fclose(xmlFilePtr);
        prvPdlibOsFree(xmlFileDataPtr);
        return NULL;
    }

    fclose(xmlFilePtr);

    return xmlFileDataPtr;
}


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
XML_PARSER_RET_CODE_TYP xmlParserUncompressedFileBuild(
    IN  char                              * xmlFilePathPtr,
    IN  char                              * signatureFilePathPtr,
    IN  char                              * tagPefixPtr,
    OUT XML_PARSER_ROOT_DESCRIPTOR_TYP    * rootIdPtr
)
{
    XML_PARSER_RET_CODE_TYP         result = XML_PARSER_RET_CODE_OK;
    PRV_XML_PARSER_ROOT_STC       * rootPtr;
    PRV_XML_PARSER_NODE_STC       * typedefsPtr;
    char                          * xmlFileDataPtr;
    UINT_32                         size = 0, i;

    if (FALSE == prvPdlXmlVerificationHandler(xmlFilePathPtr, signatureFilePathPtr)) {
        *rootIdPtr = NULL;
        return XML_PARSER_RET_CODE_INTEGRITY_FAILED;
    }

    rootPtr = prvXmlParserBuilderRootCreate("ROOT", tagPefixPtr, xmlFilePathPtr);
    if (rootPtr == NULL) {
        return XML_PARSER_RET_CODE_NO_MEM;
    }

    xmlFileDataPtr = prvXmlParserReadFile(xmlFilePathPtr, &size);
    if (xmlFileDataPtr == NULL) {
        if (size == 0) {
            result = XML_PARSER_RET_CODE_NOT_FOUND;
        }
        else {
            result = XML_PARSER_RET_CODE_NO_MEM;
        }
        goto fail;
    }

    xmlFileDataPtr[size] = 0;
    result = prvXmlParserBuildTree(rootPtr, xmlFileDataPtr);
    if (result != XML_PARSER_RET_CODE_OK) {
        goto fail;
    }

    typedefsPtr = prvXmlParseFindTagByName(&rootPtr->node, "typedefs", TRUE);
    if (typedefsPtr == NULL) {
        result = XML_PARSER_RET_CODE_WRONG_FORMAT;
        goto fail;
    }

    result = prvXmlParserResolveTypes(rootPtr, typedefsPtr);
    if (result != XML_PARSER_RET_CODE_OK) {
        goto fail;
    }

    result = prvXmlParserValidateData(rootPtr);
    if (result != XML_PARSER_RET_CODE_OK) {
        goto fail;
    }

    *rootIdPtr = (XML_PARSER_ROOT_DESCRIPTOR_TYP)rootPtr;

    goto success;

fail:
    prvXmlParserDestroyNode(&rootPtr);

success:
    for (i = 0; i < PRV_XML_PARSER_MAX_NUM_OF_OPENED_TREES_CNS; i ++) {
        if (prvXmlParserDebugOpenedDescriptors[i] == 0) {
            prvXmlParserDebugOpenedDescriptors[i] = (XML_PARSER_ROOT_DESCRIPTOR_TYP)rootPtr;
            break;
        }
    }

    if (xmlFileDataPtr)
        prvPdlibOsFree(xmlFileDataPtr);

    return result;
}



/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserBuild ( IN char * arXmlFilePathPtr, IN char * tagPefixPtr,  IN BOOLEAN isCompress, OUT XML_PARSER_ROOT_DESCRIPTOR_TYP * rootIdPtr );
 *
 * @brief   Builds database from XML file and returns descriptor to that database.
 *
 * @param [in]  arXmlFilePathPtr Pointer to path &amp; name of compressed file.
 * @param [in]  tagPefixPtr      prefix of all tags in xml data
 * @param [in]  isEzbXml         Used to indicate whether to build string&enum conversion tables according to EZB DB or external DBs
 * @param [out] rootIdPtr        XML descriptor.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND    if file could not be opened
 *          XML_PARSER_RET_CODE_NO_MEM       if out of memory occurred while building database
 *          XML_PARSER_RET_CODE_WRONG_FORMAT if XML file format is invalid.
 */
XML_PARSER_RET_CODE_TYP xmlParserBuild(
    IN  char                              * arXmlFilePathPtr,
    IN  char                              * tagPefixPtr,
    OUT XML_PARSER_ROOT_DESCRIPTOR_TYP    * rootIdPtr
)
{
    char xmlFilePathPtr[160], signatureFilePathPtr[160];

    if (FALSE == prvPdlXmlArchiveUncompressHandler(arXmlFilePathPtr, xmlFilePathPtr, signatureFilePathPtr)) {
        *rootIdPtr = NULL;
        return XML_PARSER_RET_CODE_NOT_FOUND;
    }

    return xmlParserUncompressedFileBuild(xmlFilePathPtr, signatureFilePathPtr, tagPefixPtr, rootIdPtr);
}



/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserDestroy ( IN XML_PARSER_ROOT_DESCRIPTOR_TYP * rootIdPtr )
 *
 * @brief   Destroys database and frees all allocated memory
 *
 * @param [in,out]  rootIdPtr   If non-null, the root identifier pointer.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if wrong descriptor used.
 *
 * ### param [in]       rootId  Descriptor which was returned from xmlParserBuild.
 */

XML_PARSER_RET_CODE_TYP xmlParserDestroy(
    IN XML_PARSER_ROOT_DESCRIPTOR_TYP     * rootIdPtr
)
{
    PRV_XML_PARSER_ROOT_STC   ** rootPtr = (PRV_XML_PARSER_ROOT_STC **)rootIdPtr;
    UINT_8                       i;

    /* partial validation of data */
    if (*rootPtr == NULL || (*rootPtr)->typedefsPtr == NULL || (*rootPtr)->filenamePtr == NULL || (*rootPtr)->node.firstChildPtr == NULL) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    for (i = 0; i < PRV_XML_PARSER_MAX_NUM_OF_OPENED_TREES_CNS; i ++) {
        if (prvXmlParserDebugOpenedDescriptors[i] == *rootIdPtr) {
            prvXmlParserDebugOpenedDescriptors[i] = 0;
            break;
        }
    }

    prvXmlParserDestroyNode(rootPtr);

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserFindByName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * xmlTagPtr, OUT XML_PARSER_NODE_DESCRIPTOR_TYP * xmlChildIdPtr )
 *
 * @brief   Search for node by name
 *
 * @param [in]  xmlId           XML node descriptor (search will be conducted under that node)
 * @param [in]  xmlTagPtr       String to search for.
 * @param [out] xmlChildIdPtr   XML node descriptor pointing to location of the searched tag.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if not found.
 */

XML_PARSER_RET_CODE_TYP xmlParserFindByName(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlId,
    IN  char                              * xmlTagPtr,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlChildIdPtr
)
{
    PRV_XML_PARSER_NODE_STC   *nodePtr;

    nodePtr = prvXmlParseFindTagByName((PRV_XML_PARSER_NODE_STC *)xmlId, xmlTagPtr, TRUE);
    if (nodePtr == NULL) {
        return XML_PARSER_RET_CODE_NOT_FOUND;
    }

    *xmlChildIdPtr = (XML_PARSER_NODE_DESCRIPTOR_TYP)nodePtr;

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserFindChildByName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * xmlTagPtr, OUT XML_PARSER_NODE_DESCRIPTOR_TYP * xmlChildIdPtr )
 *
 * @brief   Search for child node by name
 *
 * @param [in]  xmlId           XML node descriptor (search will be conducted under that node)
 * @param [in]  xmlTagPtr       String to search for.
 * @param [out] xmlChildIdPtr   XML node descriptor pointing to location of the searched tag.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if not found.
 */

XML_PARSER_RET_CODE_TYP xmlParserFindChildByName(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlId,
    IN  char                              * xmlTagPtr,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlChildIdPtr
)
{
    PRV_XML_PARSER_NODE_STC   *nodePtr;

    nodePtr = prvXmlParseFindChildByName((PRV_XML_PARSER_NODE_STC *)xmlId, xmlTagPtr, TRUE);
    if (nodePtr == NULL) {
        return XML_PARSER_RET_CODE_NOT_FOUND;
    }

    *xmlChildIdPtr = (XML_PARSER_NODE_DESCRIPTOR_TYP)nodePtr;

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetFirstChild ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlParent, OUT XML_PARSER_NODE_DESCRIPTOR_TYP * xmlChildPtr )
 *
 * @brief   Gets first child of current tag (walking one level down in tree)
 *
 * @param [in]  xmlParent   XML node descriptor (search will be conducted under that node)
 * @param [out] xmlChildPtr First child of xmlParent.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if this node does not have children.
 */

XML_PARSER_RET_CODE_TYP xmlParserGetFirstChild(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlParent,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlChildPtr
)
{
    PRV_XML_PARSER_NODE_STC   * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlParent;
    if (nodePtr == NULL || nodePtr->firstChildPtr == NULL) {
        return XML_PARSER_RET_CODE_NOT_FOUND;
    }

    *xmlChildPtr = (XML_PARSER_NODE_DESCRIPTOR_TYP)nodePtr->firstChildPtr;

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetNextSibling ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, OUT XML_PARSER_NODE_DESCRIPTOR_TYP * xmlNextIdPtr )
 *
 * @brief   Gets next sibling (brother) of current node (walking the same level in tree)
 *
 * @param [in]  xmlId           XML node descriptor.
 * @param [out] xmlNextIdPtr    Next brother of xmlId.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if this node does not have brothers.
 */

XML_PARSER_RET_CODE_TYP xmlParserGetNextSibling(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP      xmlId,
    OUT XML_PARSER_NODE_DESCRIPTOR_TYP    * xmlNextIdPtr

)
{
    PRV_XML_PARSER_NODE_STC   * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlId;
    if (nodePtr == NULL || nodePtr->nextSiblingPtr == NULL) {
        return XML_PARSER_RET_CODE_NOT_FOUND;
    }

    *xmlNextIdPtr = (XML_PARSER_NODE_DESCRIPTOR_TYP)nodePtr->nextSiblingPtr;

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, INOUT UINT_32 * outputSizePtr, OUT char * outputPtr )
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

XML_PARSER_RET_CODE_TYP xmlParserGetName(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    INOUT   UINT_32                       * outputSizePtr,
    OUT     char                          * outputPtr
)
{
    PRV_XML_PARSER_NODE_STC   * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlId;
    UINT_32                     maxSize = *outputSizePtr;

    if (nodePtr == NULL || nodePtr->namePtr == NULL) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    *outputSizePtr = strlen(nodePtr->namePtr) + 1;

    if (maxSize >= strlen(nodePtr->namePtr) + 1) {
        XML_PARSER_STRCPY_MAC(outputPtr, nodePtr->namePtr);
    }


    return (maxSize >= *outputSizePtr) ? XML_PARSER_RET_CODE_OK : XML_PARSER_RET_CODE_BAD_SIZE;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserIsEqualName ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * namePtr )
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

XML_PARSER_RET_CODE_TYP xmlParserIsEqualName(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    IN      char                          * namePtr
)
{
    PRV_XML_PARSER_NODE_STC   * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlId;

    if (nodePtr == NULL || nodePtr->namePtr == NULL) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    if (strcmp(namePtr, nodePtr->namePtr)) {
        return XML_PARSER_RET_CODE_ERROR;
    }

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetTagCount ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN char * xmlTagPtr, OUT UINT_32 * countPtr )
 *
 * @brief   Counts all tags with specified name in under xmlId (not including supplied node)
 *
 * @param [in]  xmlId       XML descriptor pointing to a specific tag.
 * @param [in]  xmlTagPtr   NULL-terminated string to search.
 * @param [out] countPtr    Number of encountered tags.
 *
 * @return  An XML_PARSER_RET_CODE_TYP.
 */

XML_PARSER_RET_CODE_TYP xmlParserGetTagCount(
    IN  XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    IN  char                          * xmlTagPtr,
    OUT UINT_32                       * countPtr
)
{
    prvXmlParserGetTagCount((PRV_XML_PARSER_NODE_STC *)xmlId, xmlTagPtr, countPtr);

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserGetValue ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, INOUT UINT_32 * outputSizePtr, OUT void * outputPtr )
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

XML_PARSER_RET_CODE_TYP xmlParserGetValue(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    INOUT   UINT_32                       * outputSizePtr,
    OUT     void                          * outputPtr
)
{
    PRV_XML_PARSER_NODE_STC           * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlId;
    PRV_XML_PARSER_TYPEDEF_NODE_STC   * typedefPtr;
    UINT_32                             maxSize = *outputSizePtr;

    if (nodePtr == NULL || nodePtr->valuePtr == NULL || nodePtr->isValid == FALSE || nodePtr->type != PRV_XML_PARSER_NODE_TYPE_LEAF_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    typedefPtr = nodePtr->auxData.typedefPtr;
    if (typedefPtr->resolvedPtr) {
        typedefPtr = typedefPtr->resolvedPtr;
    }

    if (typedefPtr == NULL || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_NONE_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    memset(outputPtr, 0, *outputSizePtr);
    if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_STRING_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
        *outputSizePtr = strlen(nodePtr->valuePtr) + 1;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_EMPTY_E) {
        *outputSizePtr = 0;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
        *outputSizePtr = sizeof(BOOLEAN);
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
        *outputSizePtr = 1;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E) {
        *outputSizePtr = 2;
    }
    else { /* if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) */
        *outputSizePtr = 4;
    }

    if (maxSize >= *outputSizePtr) {
        if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_STRING_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
            XML_PARSER_STRCPY_MAC((char *)outputPtr, nodePtr->auxData.data.value.strOrIntValue.stringValuePtr);
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E) {
            *(UINT_8 *)outputPtr = nodePtr->auxData.data.value.uint8Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E) {
            *(UINT_16 *)outputPtr = nodePtr->auxData.data.value.uint16Value;
        }
        else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E) {
            *(UINT_32 *)outputPtr = nodePtr->auxData.data.value.uint32Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
            *(INT_8 *)outputPtr = nodePtr->auxData.data.value.int8Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E) {
            *(INT_16 *)outputPtr = nodePtr->auxData.data.value.int16Value;
        }
        else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) {
            *(INT_32 *)outputPtr = nodePtr->auxData.data.value.int32Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
            *(BOOLEAN *)outputPtr = nodePtr->auxData.data.value.boolValue;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BITS_E) {
            *(UINT_32 *)outputPtr = nodePtr->auxData.data.value.strOrIntValue.uint32Value;
        }
    }


    return (maxSize >= *outputSizePtr) ? XML_PARSER_RET_CODE_OK : XML_PARSER_RET_CODE_BAD_SIZE;
}

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

XML_PARSER_RET_CODE_TYP xmlParserGetIntValue(
    IN      XML_PARSER_NODE_DESCRIPTOR_TYP  xmlId,
    INOUT   UINT_32                       * outputSizePtr,
    OUT     void                          * outputPtr
)
{
    PRV_XML_PARSER_NODE_STC           * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlId;
    PRV_XML_PARSER_TYPEDEF_NODE_STC   * typedefPtr;
    UINT_32                             maxSize = *outputSizePtr;

    if (nodePtr == NULL || nodePtr->valuePtr == NULL || nodePtr->isValid == FALSE || nodePtr->type != PRV_XML_PARSER_NODE_TYPE_LEAF_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    typedefPtr = nodePtr->auxData.typedefPtr;
    if (typedefPtr->resolvedPtr) {
        typedefPtr = typedefPtr->resolvedPtr;
    }

    if (typedefPtr == NULL || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_NONE_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    memset(outputPtr, 0, *outputSizePtr);
    if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
        *outputSizePtr = 1;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_EMPTY_E) {
        *outputSizePtr = 0;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
        *outputSizePtr = sizeof(BOOLEAN);
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E) {
        *outputSizePtr = 2;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) {
        *outputSizePtr = 4;
    }
    else { /* typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_STRING_E */
        return XML_PARSER_RET_CODE_WRONG_FORMAT;
    }

    if (maxSize >= *outputSizePtr) {
        if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
            *(UINT_8 *)outputPtr = (UINT_8)nodePtr->auxData.data.value.strOrIntValue.uint32Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E) {
            *(UINT_8 *)outputPtr = nodePtr->auxData.data.value.uint8Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
            *(INT_8 *)outputPtr = nodePtr->auxData.data.value.int8Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E) {
            *(UINT_16 *)outputPtr = nodePtr->auxData.data.value.uint16Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E) {
            *(INT_16 *)outputPtr = nodePtr->auxData.data.value.int16Value;
        }
        else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E) {
            *(UINT_32 *)outputPtr = nodePtr->auxData.data.value.uint32Value;
        }
        else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) {
            *(INT_32 *)outputPtr = nodePtr->auxData.data.value.int32Value;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
            *(BOOLEAN *)outputPtr = nodePtr->auxData.data.value.boolValue;
        }
        else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BITS_E) {
            *(UINT_32 *)outputPtr = nodePtr->auxData.data.value.strOrIntValue.uint32Value;
        }
    }


    return (maxSize >= *outputSizePtr) ? XML_PARSER_RET_CODE_OK : XML_PARSER_RET_CODE_BAD_SIZE;
}

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserSetValue ( IN XML_PARSER_NODE_DESCRIPTOR_TYP xmlId, IN UINT_32 inputSize, IN void * inputPtr )
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

XML_PARSER_RET_CODE_TYP xmlParserSetValue(
    IN   XML_PARSER_NODE_DESCRIPTOR_TYP xmlId,
    IN   UINT_32                        inputSize,
    IN   void                         * inputPtr
)
{
    PRV_XML_PARSER_NODE_STC           * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlId;
    PRV_XML_PARSER_TYPEDEF_NODE_STC   * typedefPtr;
    BOOLEAN                             boolValue;
    UINT_8                              uValue8, i;
    UINT_16                             uValue16;
    UINT_32                             uValue32, uTemp32Value;
    INT_8                               iValue8;
    INT_16                              iValue16;
    INT_32                              iValue32;
    char                              * newValuePtr;

    if (nodePtr == NULL || nodePtr->valuePtr == NULL || nodePtr->isValid == FALSE || nodePtr->type != PRV_XML_PARSER_NODE_TYPE_LEAF_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    typedefPtr = nodePtr->auxData.typedefPtr;
    if (typedefPtr->resolvedPtr) {
        typedefPtr = typedefPtr->resolvedPtr;
    }

    if (typedefPtr == NULL || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_NONE_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_EMPTY_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    /* validate input parameter */
    if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_STRING_E) {
        if ((typedefPtr->data.string_value.min || typedefPtr->data.string_value.max) &&
            (inputSize < typedefPtr->data.string_value.min || inputSize > typedefPtr->data.string_value.max)) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
        for (i = 0; i < typedefPtr->data.enum_value.arr_size; i++) {
            if (inputSize == strlen(typedefPtr->data.enum_value.strEnumArr[i]) + 1 &&
                strcmp((char *)inputPtr, typedefPtr->data.enum_value.strEnumArr[i]) == 0) {
                break;
            }
        }
        if (i == typedefPtr->data.enum_value.arr_size) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BITS_E) {
        uTemp32Value = *(UINT_32 *)inputPtr;
        if (inputSize != 4) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
        for (i = 0; i < typedefPtr->data.bits_value.arr_size; i++) {
            uTemp32Value &= ~(1 << typedefPtr->data.bits_value.intBitArr[i]);
        }
        if (uTemp32Value) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
        boolValue = *(BOOLEAN *)inputPtr;
        if (sizeof(BOOLEAN) != inputSize || (boolValue != FALSE && boolValue != TRUE)) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E) {
        uValue8 = *(UINT_8 *)inputPtr;
        if (inputSize != 1 || uValue8 < typedefPtr->data.uint_value.min || uValue8 > typedefPtr->data.uint_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E) {
        uValue16 = *(UINT_16 *)inputPtr;
        if (inputSize != 2 || uValue16 < typedefPtr->data.uint_value.min || uValue16 > typedefPtr->data.uint_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E) {
        uValue32 = *(UINT_32 *)inputPtr;
        if (inputSize != 4 || uValue32 < typedefPtr->data.uint_value.min || uValue32 > typedefPtr->data.uint_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
        iValue8 = *(INT_8 *)inputPtr;
        if (inputSize != 1 || iValue8 < typedefPtr->data.int_value.min || iValue8 > typedefPtr->data.int_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E) {
        iValue16 = *(INT_16 *)inputPtr;
        if (inputSize != 2 || iValue16 < typedefPtr->data.int_value.min || iValue16 > typedefPtr->data.int_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else { /* if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) */
        iValue32 = *(INT_32 *)inputPtr;
        if (inputSize != 4 || iValue32 < typedefPtr->data.int_value.min || iValue32 > typedefPtr->data.int_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }

    if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_STRING_E || typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
        newValuePtr = XML_PARSER_STRDUP_MAC((char *)inputPtr);
        if (newValuePtr == NULL) {
            return XML_PARSER_RET_CODE_NO_MEM;
        }

        prvPdlibOsFree(nodePtr->valuePtr);

        nodePtr->valuePtr = nodePtr->auxData.data.value.strOrIntValue.stringValuePtr = newValuePtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E) {
        nodePtr->auxData.data.value.uint8Value = *(UINT_8 *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E) {
        nodePtr->auxData.data.value.uint16Value = *(UINT_16 *)inputPtr;
    }
    else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E) {
        nodePtr->auxData.data.value.uint32Value = *(UINT_32 *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
        nodePtr->auxData.data.value.int8Value = *(INT_8 *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E) {
        nodePtr->auxData.data.value.int16Value = *(INT_16 *)inputPtr;
    }
    else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) {
        nodePtr->auxData.data.value.int32Value = *(INT_32 *)inputPtr;
    }
    else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
        nodePtr->auxData.data.value.boolValue = *(BOOLEAN *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BITS_E) {
        uTemp32Value = 0;
        for (i = 0; i < typedefPtr->data.bits_value.arr_size; i++) {
            uTemp32Value += strlen(typedefPtr->data.bits_value.strBitArr[i]);
        }
        uTemp32Value += typedefPtr->data.bits_value.arr_size - 1; /* for spaces between values */
        newValuePtr = (char *)prvPdlibOsMalloc((uTemp32Value + 1) * sizeof(char));
        if (newValuePtr == NULL) {
            return XML_PARSER_RET_CODE_NO_MEM;
        }

        newValuePtr[0] = '\0';

        prvPdlibOsFree(nodePtr->valuePtr);

        uValue32 = *(UINT_32 *)inputPtr;
        for (i = 0; i < typedefPtr->data.bits_value.arr_size; i++) {
            if (uValue32 & (1 << typedefPtr->data.bits_value.intBitArr[i])) {
                if (strlen(newValuePtr)) {
                    XML_PARSER_STRCAT_MAC(newValuePtr, uTemp32Value + 1 - strlen(newValuePtr), &prvXmlParserSpaceSymbol);
                }

                XML_PARSER_STRCAT_MAC(newValuePtr, uTemp32Value + 1 - strlen(newValuePtr), typedefPtr->data.bits_value.strBitArr[i]);
            }
        }

        nodePtr->auxData.data.value.strOrIntValue.uint32Value = uValue32;
        nodePtr->valuePtr = nodePtr->auxData.data.value.strOrIntValue.stringValuePtr = newValuePtr;
    }

    return XML_PARSER_RET_CODE_OK;
}

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

XML_PARSER_RET_CODE_TYP xmlParserSetIntValue(
    IN   XML_PARSER_NODE_DESCRIPTOR_TYP xmlId,
    IN   UINT_32                        inputSize,
    IN   void                         * inputPtr
)
{
    PRV_XML_PARSER_NODE_STC           * nodePtr = (PRV_XML_PARSER_NODE_STC *)xmlId;
    PRV_XML_PARSER_TYPEDEF_NODE_STC   * typedefPtr;
    BOOLEAN                             boolValue;
    UINT_8                              uValue8, i;
    UINT_16                             uValue16;
    UINT_32                             uValue32, uTemp32Value;
    INT_8                               iValue8;
    INT_16                              iValue16;
    INT_32                              iValue32;
    char                              * newValuePtr;

    if (nodePtr == NULL || nodePtr->valuePtr == NULL || nodePtr->isValid == FALSE || nodePtr->type != PRV_XML_PARSER_NODE_TYPE_LEAF_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    typedefPtr = nodePtr->auxData.typedefPtr;
    if (typedefPtr->resolvedPtr) {
        typedefPtr = typedefPtr->resolvedPtr;
    }

    if (typedefPtr == NULL ||
        typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_NONE_E ||
        typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_EMPTY_E ||
        typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_STRING_E) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    /* validate input parameter */
    if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
        uValue8 = *(UINT_8 *)inputPtr;
        for (i = 0; i < typedefPtr->data.enum_value.arr_size; i++) {
            if (inputSize == 1 && (uValue8 == typedefPtr->data.enum_value.intEnumArr[i])) {
                break;
            }
        }
        if (i == typedefPtr->data.enum_value.arr_size) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BITS_E) {
        uTemp32Value = uValue32 = *(UINT_32 *)inputPtr;
        if (inputSize != 4) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
        for (i = 0; i < typedefPtr->data.bits_value.arr_size; i++) {
            uTemp32Value &= ~(1 << typedefPtr->data.bits_value.intBitArr[i]);
        }
        if (uTemp32Value) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
        boolValue = *(BOOLEAN *)inputPtr;
        if (sizeof(BOOLEAN) != inputSize || (boolValue != FALSE && boolValue != TRUE)) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E) {
        uValue8 = *(UINT_8 *)inputPtr;
        if (inputSize != 1 || uValue8 < typedefPtr->data.uint_value.min || uValue8 > typedefPtr->data.uint_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E) {
        uValue16 = *(UINT_16 *)inputPtr;
        if (inputSize != 2 || uValue16 < typedefPtr->data.uint_value.min || uValue16 > typedefPtr->data.uint_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E) {
        uValue32 = *(UINT_32 *)inputPtr;
        if (inputSize != 4 || uValue32 < typedefPtr->data.uint_value.min || uValue32 > typedefPtr->data.uint_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
        iValue8 = *(INT_8 *)inputPtr;
        if (inputSize != 1 || iValue8 < typedefPtr->data.int_value.min || iValue8 > typedefPtr->data.int_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E) {
        iValue16 = *(INT_16 *)inputPtr;
        if (inputSize != 2 || iValue16 < typedefPtr->data.int_value.min || iValue16 > typedefPtr->data.int_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }
    else { /* if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) */
        iValue32 = *(INT_32 *)inputPtr;
        if (inputSize != 4 || iValue32 < typedefPtr->data.int_value.min || iValue32 > typedefPtr->data.int_value.max) {
            return XML_PARSER_RET_CODE_WRONG_FORMAT;
        }
    }

    if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
        newValuePtr = XML_PARSER_STRDUP_MAC(typedefPtr->data.enum_value.strEnumArr[i]);
        if (newValuePtr == NULL) {
            return XML_PARSER_RET_CODE_NO_MEM;
        }

        if (nodePtr->valuePtr) {
            prvPdlibOsFree(nodePtr->valuePtr);
        }

        nodePtr->auxData.data.value.strOrIntValue.uint32Value = (UINT_32)*(UINT_8 *)inputPtr;
        nodePtr->valuePtr = nodePtr->auxData.data.value.strOrIntValue.stringValuePtr = newValuePtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E) {
        nodePtr->auxData.data.value.uint8Value = *(UINT_8 *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E) {
        nodePtr->auxData.data.value.uint16Value = *(UINT_16 *)inputPtr;
    }
    else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E) {
        nodePtr->auxData.data.value.uint32Value = *(UINT_32 *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E) {
        nodePtr->auxData.data.value.int8Value = *(INT_8 *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E) {
        nodePtr->auxData.data.value.int16Value = *(INT_16 *)inputPtr;
    }
    else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E) {
        nodePtr->auxData.data.value.int32Value = *(INT_32 *)inputPtr;
    }
    else  if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E) {
        nodePtr->auxData.data.value.boolValue = *(BOOLEAN *)inputPtr;
    }
    else if (typedefPtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_BITS_E) {
        uTemp32Value = 0;
        for (i = 0; i < typedefPtr->data.bits_value.arr_size; i++) {
            uTemp32Value += strlen(typedefPtr->data.bits_value.strBitArr[i]);
        }
        uTemp32Value += typedefPtr->data.bits_value.arr_size - 1; /* for spaces between values */
        newValuePtr = (char *)prvPdlibOsMalloc((uTemp32Value + 1) * sizeof(char));
        if (newValuePtr == NULL) {
            return XML_PARSER_RET_CODE_NO_MEM;
        }

        newValuePtr[0] = '\0';

        prvPdlibOsFree(nodePtr->valuePtr);

        uValue32 = *(UINT_32 *)inputPtr;
        for (i = 0; i < typedefPtr->data.bits_value.arr_size; i++) {
            if (uValue32 & (1 << typedefPtr->data.bits_value.intBitArr[i])) {
                if (strlen(newValuePtr)) {
                    XML_PARSER_STRCAT_MAC(newValuePtr, uTemp32Value + 1 - strlen(newValuePtr), &prvXmlParserSpaceSymbol);
                }

                XML_PARSER_STRCAT_MAC(newValuePtr, uTemp32Value + 1 - strlen(newValuePtr), typedefPtr->data.bits_value.strBitArr[i]);
            }
        }

        nodePtr->auxData.data.value.strOrIntValue.uint32Value = uValue32;
        nodePtr->valuePtr = nodePtr->auxData.data.value.strOrIntValue.stringValuePtr = newValuePtr;
    }

    return XML_PARSER_RET_CODE_OK;
}

/**
 * @fn  BOOLEAN xmlParserExternalEnumDbBuild ( IN PRV_XML_PARSER_ROOT_STC * rootPtr )
 *
 * @brief   Build external enum database.
 *
 * @param [in]      rootId                          XML tree root instance.
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
    IN    UINT_32                                  externalEnumStringArrSize,
    INOUT XML_PARSER_ENUM_DB_STC               ** externalEnumDbArr
)
{
    PRV_XML_PARSER_TYPEDEF_NODE_STC   * typedefNodePtr, * actNodePtr;
    UINT_32                             enumId;
    PRV_XML_PARSER_ROOT_STC           * rootPtr = (PRV_XML_PARSER_ROOT_STC *)rootId;

    if (rootPtr == NULL || rootPtr->typedefsPtr == NULL || rootPtr->filenamePtr == NULL || rootPtr->node.firstChildPtr == NULL) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }

    if (externalEnumDbArr == NULL || externalEnumStringArr == NULL) {
        return XML_PARSER_RET_CODE_WRONG_PARAM;
    }
    typedefNodePtr = rootPtr->typedefsPtr;
    while (typedefNodePtr) {
        actNodePtr = typedefNodePtr;
        if (actNodePtr->resolvedPtr) {
            actNodePtr = actNodePtr->resolvedPtr;
        }
        if (actNodePtr->type == PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E) {
            /* find id by name */
            for (enumId = 0; enumId < externalEnumStringArrSize; enumId ++) {
                if (strcmp(externalEnumStringArr[enumId], actNodePtr->namePtr) == 0) {
                    break;
                }
            }

            if (enumId == externalEnumStringArrSize) {
                prvPdlibOsPrintf("Unregistered enum %s\n", actNodePtr->namePtr);
                return XML_PARSER_RET_CODE_NOT_FOUND;
            }

            externalEnumDbArr[enumId] = (XML_PARSER_ENUM_DB_STC*)&actNodePtr->data.enum_value;
        }
        typedefNodePtr = typedefNodePtr->nextPtr;
    }

    return XML_PARSER_RET_CODE_OK;
}

