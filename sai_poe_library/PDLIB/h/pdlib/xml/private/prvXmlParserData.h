/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\h\xml\private\prvxmlparserdata.h.
 *
 * @brief   Declares the prvxmlparserdata class
 */

#ifndef __prvPdlLibXmlParserDatah

#define __prvPdlLibXmlParserDatah

#ifdef __cplusplus
extern "C" {
#endif

/**
********************************************************************************
 * @file prvXmlParserData.h
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
 * @brief Private XML library data structures
 *
 * @version   1
********************************************************************************
*/


/**
* @addtogroup XML
* @{
*/

/**
 * @enum    PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENT
 *
 * @brief   @defgroup XML_Data XML Data
 *          @{
 */

typedef enum {
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_NONE_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_EMPTY_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_BOOLEAN_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT8_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT16_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_UINT32_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT8_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT16_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_INT32_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_STRING_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENUM_E,
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_BITS_E
} PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENT;

/**
 * @union   _PRV_XML_PARSER_TYPEDEF_DATA_UNT
 *
 * @brief   A prv XML parser typedef data unt.
 */

typedef union _PRV_XML_PARSER_TYPEDEF_DATA_UNT {
    /**
     * @struct  int_value
     *
     * @brief   An int value.
     */

    struct {
        /** @brief   The minimum */
        UINT_32     min;
        /** @brief   The maximum */
        UINT_32     max;
    } uint_value;

    struct {
        /** @brief   The minimum */
        INT_32      min;
        /** @brief   The maximum */
        INT_32      max;
    } int_value;

    /**
     * @struct  string_value
     *
     * @brief   A string value.
     */

    struct {
        /** @brief   The minimum */
        UINT_32     min;
        /** @brief   The maximum */
        UINT_32     max;
    } string_value;

    /**
     * @struct  enum_value
     *
     * @brief   An enum value.
     */

    XML_PARSER_ENUM_DB_STC  enum_value;

    /**
     * @struct  bits_value
     *
     * @brief   Single bit value.
     */

    XML_PARSER_BITS_DB_STC  bits_value;
} PRV_XML_PARSER_TYPEDEF_DATA_UNT;

/**
 * @struct  _PRV_XML_PARSER_TYPEDEF_NODE_STCT
 *
 * @brief   A prv XML parser typedef node stct.
 */

typedef struct _PRV_XML_PARSER_TYPEDEF_NODE_STCT {
    /** @brief   The name pointer */
    char                                      * namePtr;
    /** @brief   The type */
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_ENT         type;
    /** @brief   The data */
    PRV_XML_PARSER_TYPEDEF_DATA_UNT             data;

    /**
     * @struct  _PRV_XML_PARSER_TYPEDEF_NODE_STCT*
     *
     * @brief   A prv XML parser typedef node stct*.
     */

    struct _PRV_XML_PARSER_TYPEDEF_NODE_STCT  * resolvedPtr;

    /**
     * @struct  _PRV_XML_PARSER_TYPEDEF_NODE_STCT*
     *
     * @brief   A prv XML parser typedef node stct*.
     */

    struct _PRV_XML_PARSER_TYPEDEF_NODE_STCT  * nextPtr;
} PRV_XML_PARSER_TYPEDEF_NODE_STC;

/**
 * @enum    PRV_XML_PARSER_SIMPLE_DATA_TYPE_FORMAT_ENT
 *
 * @brief   Values that represent prv XML parser simple data type format ents
 */

typedef enum {
    PRV_XML_PARSER_SIMPLE_DATA_FORMAT_DECIMAL_E,
    PRV_XML_PARSER_SIMPLE_DATA_FORMAT_HEX_E
} PRV_XML_PARSER_SIMPLE_DATA_TYPE_FORMAT_ENT;

/**
 * @union   _PRV_XML_PARSER_LEAF_DATA_UNT
 *
 * @brief   A prv XML parser leaf data unt.
 */

typedef union _PRV_XML_PARSER_LEAF_DATA_UNT {
    /** @brief   The 8 value */
    UINT_8                  uint8Value;
    /** @brief   The 16 value */
    UINT_16                 uint16Value;
    /** @brief   The 32 value */
    UINT_32                 uint32Value;
    /** @brief   The 8 signed value */
    INT_8                   int8Value;
    /** @brief   The 16 signed value */
    INT_16                  int16Value;
    /** @brief   The 32 signed value */
    INT_32                  int32Value;
    /** @brief   True to value */
    BOOLEAN                 boolValue;
    /** @brief   The string value pointer */
    struct {
        char                  * stringValuePtr;
        /** @brief   The 8 value */
        UINT_32                 uint32Value;
    } strOrIntValue;
} PRV_XML_PARSER_LEAF_DATA_UNT;

/**
 * @struct  _PRV_XML_PARSER_LEAF_VALUE_STCT
 *
 * @brief   A prv XML parser leaf value stct.
 */

typedef struct _PRV_XML_PARSER_LEAF_VALUE_STCT {
    /** @brief   The value */
    PRV_XML_PARSER_LEAF_DATA_UNT                    value;
    /** @brief   Describes the format to use */
    PRV_XML_PARSER_SIMPLE_DATA_TYPE_FORMAT_ENT      format;
} PRV_XML_PARSER_LEAF_VALUE_STC;

/**
 * @struct  _LEAF_DATA_STC
 *
 * @brief   A leaf data stc.
 */

typedef struct _LEAF_DATA_STC {
    /** @brief   The attribute name pointer */
    char                                  * attrNamePtr;
    /** @brief   The data */
    PRV_XML_PARSER_LEAF_VALUE_STC           data;
    /** @brief   The typedef pointer */
    PRV_XML_PARSER_TYPEDEF_NODE_STC       * typedefPtr;
} PRV_XML_PARSER_AUX_DATA_STC;

/**
 * @enum    PRV_XML_PARSER_NODE_TYPE_ENT
 *
 * @brief   Values that represent prv XML parser node type ents
 */

typedef enum {
    PRV_XML_PARSER_NODE_TYPE_NONE_E,
    PRV_XML_PARSER_NODE_TYPE_GROUP_E,
    PRV_XML_PARSER_NODE_TYPE_LEAF_E,
    PRV_XML_PARSER_NODE_TYPE_TYPE_E
} PRV_XML_PARSER_NODE_TYPE_ENT;

/**
 * @struct  PRV_XML_PARSER_NODE_STCT
 *
 * @brief   A prv XML parser node stct.
 */

typedef struct PRV_XML_PARSER_NODE_STCT {
    /** @brief   The name pointer */
    char                              * namePtr;        /*!< XML node name                                              */
    /** @brief   The value pointer */
    char                              * valuePtr;       /*!< String value of the tag                                    */
    /** @brief   The type */
    PRV_XML_PARSER_NODE_TYPE_ENT        type;           /*!< XML node type                                              */
    /** @brief   Information describing the auxiliary */
    PRV_XML_PARSER_AUX_DATA_STC         auxData;        /*!< Aux data (depends on node type)                            */
    /** @brief   True if is valid, false if not */
    BOOLEAN                             isValid;        /*!< Did this node passed validation check                      */

    /**
     * @struct  PRV_XML_PARSER_NODE_STCT*
     *
     * @brief   A prv XML parser node stct*.
     */

    struct PRV_XML_PARSER_NODE_STCT   * firstChildPtr;  /*!< First child of the node (level down in tree)               */

    /**
     * @struct  PRV_XML_PARSER_NODE_STCT*
     *
     * @brief   A prv XML parser node stct*.
     */

    struct PRV_XML_PARSER_NODE_STCT   * lastChildPtr;   /*!< Last child  of the node                                    */

    /**
     * @struct  PRV_XML_PARSER_NODE_STCT*
     *
     * @brief   A prv XML parser node stct*.
     */

    struct PRV_XML_PARSER_NODE_STCT   * nextSiblingPtr; /*!< Next sibling (brother) of the node (same level in tree)    */

    /**
     * @struct  PRV_XML_PARSER_NODE_STCT*
     *
     * @brief   A prv XML parser node stct*.
     */

    struct PRV_XML_PARSER_NODE_STCT   * parentPtr;      /*!< Parent node of this XML node                               */
} PRV_XML_PARSER_NODE_STC;

/**
 * @struct  PRV_XML_PARSER_XML_ROOT_STCT
 *
 * @brief   A prv XML parser XML root stct.
 */

typedef struct PRV_XML_PARSER_XML_ROOT_STCT {
    /** @brief   The filename pointer */
    char                               *filenamePtr;        /*!< Filename of XML data           */
    /** @brief   The required prefix for each tag (format: prefix:tag) */
    char                               *tagPefixPtr;
    /** @brief   The typedefs pointer */
    PRV_XML_PARSER_TYPEDEF_NODE_STC    *typedefsPtr;        /*!< Typedefs section of XML data   */
    /** @brief   The node */
    PRV_XML_PARSER_NODE_STC             node;               /*!< First node of the XML tree     */
} PRV_XML_PARSER_ROOT_STC;

/**
 * @enum    PRV_XML_PARSER_CALL_ORDER_ENT
 *
 * @brief   Values that represent prv XML parser call order ents
 */

typedef enum {
    PRV_XML_PARSER_CALL_ON_ENTER_E,
    PRV_XML_PARSER_CALL_ON_EXIT_E,
} PRV_XML_PARSER_CALL_ORDER_ENT;

#define PRV_XML_PARSER_MAX_NUM_OF_OPENED_TREES_CNS  100

/**
 * @brief   The prv XML parser debug opened descriptors[ prv XML parser maximum number of opened
 *          trees cns]
 */

extern XML_PARSER_ROOT_DESCRIPTOR_TYP prvXmlParserDebugOpenedDescriptors[PRV_XML_PARSER_MAX_NUM_OF_OPENED_TREES_CNS];

/**
 * @struct  PRV_XML_PARSER_SEARCH_INFO_STCT
 *
 * @brief   A prv XML parser search information stct.
 */

typedef struct PRV_XML_PARSER_SEARCH_INFO_STCT {
    /** @brief   The context pointer */
    PRV_XML_PARSER_NODE_STC   * contextPtr;
    /** @brief   The pointer */
    char                      * strPtr;
    /** @brief   True to print with values */
    BOOLEAN                     printWithValues;
    /** @brief   True if is case sensitive, false if not */
    BOOLEAN                     isCaseSensitive;
    /** @brief   maximum depth to go when searching, -1 for unlimited */
    INT_32                      depth;
} PRV_XML_PARSER_SEARCH_INFO_STC;

/* @}*/
/* @}*/

#ifdef __cplusplus
}
#endif

#endif
