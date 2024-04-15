/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\h\xml\private\prvxmlparserbuilder.h.
 *
 * @brief   Declares the prvxmlparserbuilder class
 */

#ifndef __prvPdlLibXmlParserBuilderh

#define __prvPdlLibXmlParserBuilderh
 
#ifdef __cplusplus
extern "C" {
#endif

/**
********************************************************************************
 * @file prvXmlParserBuilder.h
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
 * @brief Private XML library builder apis
 *
 * @version   1
********************************************************************************
*/
/**
* @addtogroup XML
* @{
*/
/**
 * @defgroup XML_builder XML Builder
 * @{XML related functions
*/

#include <pdlib/common/pdlTypes.h>
#include <pdlib/xml/private/prvXmlParserData.h>
#include <pdlib/xml/xmlParser.h>

#ifndef _WIN32
#include <strings.h> /*needed for strcasecmp*/

#define XML_PARSER_FOPEN_MAC(a,b,c)     a = fopen(b,c)

#define XML_PARSER_STRCPY_MAC(a,b)      strcpy(a,b)
#define XML_PARSER_STRDUP_MAC           prvPdlLibStrdup
#define XML_PARSER_SSCANF_MAC           sscanf
#define XML_PARSER_STRICMP_MAC          strcasecmp
#define XML_PARSER_STRCAT_MAC(a,b,c)    prvXmlParserStrcatSafe(a,c,b)
#define XML_PARSER_STRTOK_MAC(a,b,c)    prvPdlLibStrtok_r(a,b,c)

#else /* WM */

#define XML_PARSER_FOPEN_MAC(a,b,c)     fopen_s(&a,b,c)

#define XML_PARSER_STRCPY_MAC(a,b)      strcpy_s(a, strlen(b) + 1, b)
#define XML_PARSER_STRDUP_MAC           prvPdlLibStrdup
#define XML_PARSER_SSCANF_MAC           sscanf_s
#define XML_PARSER_STRICMP_MAC          _stricmp
#define XML_PARSER_STRCAT_MAC(a,b,c)    strcat_s(a,b,c)
#define XML_PARSER_STRTOK_MAC(a,b,c)    strtok_s(a,b,c)
#endif

#ifndef _WIN32
/**
 * @fn  static char * prvXmlParserStrcatSafe ( INOUT char * str,  IN char * strToAppend, IN UINT_32 maxBufLen)
 *
 * @brief   appends "strToAppend" to end of str taking into account str size (limited by maxBufLen)
 *
 * @param [in,out] str   		source string (str)
 * @param [in] strToAppend    the string to append
 * @param [in] maxBufLen      max buffer size of str
 *
 * @return  on success pointer to str, otherwise NULL
 */
char * prvXmlParserStrcatSafe(
	INOUT char * str,
	IN const char * strToAppend,
	IN UINT_32 maxBufLen
);
#endif
/**
 * @fn  extern PRV_XML_PARSER_ROOT_STC * prvXmlParserBuilderRootCreate ( IN char * rootNamePTR, IN char * xmlFilePathPtr );
 *
 * @brief   Allocates memory and initialize data of root node.
 *
 * @param [in]      rootNamePTR     Root node's name.
 * @param [in,out]  xmlFilePathPtr  If non-null, the XML file path pointer.
 *
 * @return  NULL if root node could not be created.
 */

extern PRV_XML_PARSER_ROOT_STC * prvXmlParserBuilderRootCreate(
    IN char * rootNamePTR,
    IN char * tagPefixPtr,
    IN char * xmlFilePathPtr
);

/**
 * @fn  extern XML_PARSER_RET_CODE_TYP prvXmlParserBuildTree( IN PRV_XML_PARSER_ROOT_STC * rootPtr, IN char * xmlFileDataPtr );
 *
 * @brief   Builds database from XML data.
 *
 * @param [in]  rootPtr         Pointer to root of the tree.
 * @param [in]  xmlFileDataPtr  XML data.
 *
 * @return  XML_PARSER_RET_CODE_NOT_FOUND if file could not be opened XML_PARSER_RET_CODE_NO_MEM
 *          if out of memory occurred while building database
 *          XML_PARSER_RET_CODE_WRONG_FORMAT if XML file format is invalid.
 */

extern XML_PARSER_RET_CODE_TYP prvXmlParserBuildTree(
    IN      PRV_XML_PARSER_ROOT_STC * rootPtr,
    IN      char                    * xmlFileDataPtr
);

/**
 * @fn  extern PRV_XML_PARSER_NODE_STC * prvXmlParseFindTagByName(PRV_XML_PARSER_NODE_STC * contextPtr, char * name, BOOLEAN isCaseSensitive);
 *
 * @brief   Find next xml node by name.
 *
 * @param [in]  contextPtr      Search under this node (in tree)
 * @param [in]  name            XML tag to search for.
 * @param       isCaseSensitive True if is case sensitive, false if not.
 *
 * @return  Pointer to xml node or NULL if not found.
 */

extern PRV_XML_PARSER_NODE_STC * prvXmlParseFindTagByName(PRV_XML_PARSER_NODE_STC * contextPtr, char * name, BOOLEAN isCaseSensitive);

/**
 * @fn  extern PRV_XML_PARSER_NODE_STC * prvXmlParseFindChildByName(PRV_XML_PARSER_NODE_STC * contextPtr, char * name, BOOLEAN isCaseSensitive);
 *
 * @brief   Find child xml node by name.
 *
 * @param [in]  contextPtr      Search under this node (in tree)
 * @param [in]  name            XML tag to search for.
 * @param       isCaseSensitive True if is case sensitive, false if not.
 *
 * @return  Pointer to xml node or NULL if not found.
 */

extern PRV_XML_PARSER_NODE_STC * prvXmlParseFindChildByName(PRV_XML_PARSER_NODE_STC * contextPtr, char * name, BOOLEAN isCaseSensitive);

/**
 * @fn  extern XML_PARSER_RET_CODE_TYP prvXmlParserGetTagCount(PRV_XML_PARSER_NODE_STC * contextPtr, char * xmlTagPtr, UINT_32 * countPtr);
 *
 * @brief   Count xml node by name.
 *
 * @param [in]  contextPtr  Search under this node (in tree)
 * @param [in]  xmlTagPtr   XML tag to search for.
 * @param [out] countPtr    - Number of encountered tag's.
 *
 * @return  An XML_PARSER_RET_CODE_TYP.
 */

extern XML_PARSER_RET_CODE_TYP prvXmlParserGetTagCount(PRV_XML_PARSER_NODE_STC * contextPtr,  char  * xmlTagPtr, UINT_32  * countPtr);

/**
* @fn  XML_PARSER_RET_CODE_TYP prvXmlParserResolveTypes(PRV_XML_PARSER_ROOT_STC * rootPtr, BOOLEAN isEzbXml, PRV_XML_PARSER_NODE_STC * typedefsPtr)
 *
 * @brief   Traverse tree, resolve nodes' types and validate node's data.
 *
 * @param [in]  rootPtr     Pointer to tree's root.
 * @param [in]  typedefsPtr Pointer to tree's typedefs section.
 *
 * @return  XML_PARSER_RET_CODE_NO_MEM if memory allocation failed.
 * @return  XML_PARSER_RET_CODE_WRONG_FORMAT if invalid node was found.
 */

XML_PARSER_RET_CODE_TYP prvXmlParserResolveTypes(PRV_XML_PARSER_ROOT_STC * rootPtr, PRV_XML_PARSER_NODE_STC * typedefsPtr);

/**
 * @fn  extern XML_PARSER_RET_CODE_TYP prvXmlParserValidateData(PRV_XML_PARSER_ROOT_STC * rootPtr);
 *
 * @brief   Validate tree data.
 *
 * @param [in,out]  rootPtr If non-null, the root pointer.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_FORMAT if invalid node was found.
 */

extern XML_PARSER_RET_CODE_TYP prvXmlParserValidateData(PRV_XML_PARSER_ROOT_STC * rootPtr);

/**
 * @fn  extern void prvXmlParserDestoryNode(PRV_XML_PARSER_ROOT_STC ** rootPtr);
 *
 * @brief   Free tree memory.
 *
 * @param [in]  rootPtr Pointer to tree's root.
 */

extern void prvXmlParserDestroyNode(PRV_XML_PARSER_ROOT_STC ** rootPtr);

/**
 * @fn  extern char * prvXmlParserStrdup(char * origStringPtr);
 *
 * @brief   Duplicate null-terminated string. This function allocates memory for its operation
 *          that needs to be freed.
 *
 * @param [in]  origStringPtr   string to duplicate.
 *
 * @return  pointer to new string or NULL if no memory or origStringPtr is NULL.
 */

extern char * prvXmlParserStrdup(char * origStringPtr);

/* @}*/
/* @}*/

#ifdef __cplusplus
}
#endif

#endif
