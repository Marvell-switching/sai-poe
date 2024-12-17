/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
 * @file-docAll core\ez_bringup\h\xml\xmlparser.h.
 *
 * @brief   Declares the xmlparser class
 */

#ifndef __xmlParserh

#define __xmlParserh

#ifdef __cplusplus
extern "C" {
#endif

/**
********************************************************************************
 * @file xmlParser.h
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
 * @brief XML library APIs and declarations for application level.
 *
 * @version   1
********************************************************************************
*/
#include <pdlib/common/pdlTypes.h>

/**
 * @defgroup XML XML
 * @{XML related functions
*/
/**
 * @brief   used to indentify uninitialized variables
 * */
#define XML_PARSER_NOT_INITIALIZED_CNS (0xFBADBADF)
/*! @var typedef void * XML_PARSER_ROOT_DESCRIPTOR_TYP
    @brief A type definition for root descriptor used for building, saving and destroying xml database
*/

/**
 * @typedef void * XML_PARSER_ROOT_DESCRIPTOR_TYP
 *
 * @brief   Defines an alias representing the XML parser root descriptor typ
 */

typedef void * XML_PARSER_ROOT_DESCRIPTOR_TYP;

/*! @var typedef void * XML_PARSER_NODE_DESCRIPTOR_TYP
    @brief A type definition for node descriptor used for walking and manipulating xml database
*/

/**
 * @typedef void * XML_PARSER_NODE_DESCRIPTOR_TYP
 *
 * @brief   Defines an alias representing the XML parser node descriptor typ
 */

typedef void * XML_PARSER_NODE_DESCRIPTOR_TYP;

/**
 * @typedef UINT_32 XML_PARSER_RET_CODE_TYP
 *
 * @brief   Defines an alias representing the XML parser ret code typ
 */

typedef UINT_32 XML_PARSER_RET_CODE_TYP;        /*!< Return code                */

#define XML_PARSER_RET_CODE_OK               (0)     /*!< Operation succeeded            */
#define XML_PARSER_RET_CODE_ERROR            (1)     /*!< Operation failed               */
#define XML_PARSER_RET_CODE_NOT_FOUND        (2)     /*!< Item was not found             */
#define XML_PARSER_RET_CODE_NO_MEM           (3)     /*!< Out of  memory                 */
#define XML_PARSER_RET_CODE_WRONG_PARAM      (4)     /*!< Wrong parameter supplied       */
#define XML_PARSER_RET_CODE_WRONG_FORMAT     (5)     /*!< Wrong format encountered       */
#define XML_PARSER_RET_CODE_BAD_SIZE         (6)     /*!< Supplied size if not enough    */
#define XML_PARSER_RET_CODE_NOT_INITIALIZED  (7)     /*!< Database was not initialized   */
#define XML_PARSER_RET_CODE_INTEGRITY_FAILED (8)     /*!< XML file integrity is compromised   */

#define XML_CHECK_STATUS(__xmlStatus)                       \
            if (__xmlStatus != XML_PARSER_RET_CODE_OK) {    \
                return PDL_XML_PARSE_ERROR;                 \
            }

typedef enum {
    XML_PARSER_ENUM_ID_I2C_ACCESS_TYPE_E,
    XML_PARSER_ENUM_ID_MPP_PIN_MODE_TYPE_E,
    XML_PARSER_ENUM_ID_MPP_PIN_INIT_VALUE_TYPE_E,
    XML_PARSER_ENUM_ID_INTERFACE_TYPE_E,
    XML_PARSER_ENUM_ID_SMI_XSMI_TYPE_TYPE_E,
    XML_PARSER_ENUM_ID_PANEL_GROUP_ORDERING_TYPE_E,
    XML_PARSER_ENUM_ID_SPEED_TYPE_E,
    XML_PARSER_ENUM_ID_TRANSCEIVER_TYPE_E,
    XML_PARSER_ENUM_ID_CONNECTOR_TYPE_TYPE_E,
    XML_PARSER_ENUM_ID_L1_INTERFACE_MODE_TYPE_E,
    XML_PARSER_ENUM_ID_FAN_ROLE_TYPE_E,
    XML_PARSER_ENUM_ID_HW_FAN_OPERATION_TYPE_E,
    XML_PARSER_ENUM_ID_FAN_ADT7476_FAULT_DETECTION_TYPE_E,
    XML_PARSER_ENUM_ID_FAN_TYPE_E,
    XML_PARSER_ENUM_ID_BANK_SOURCE_TYPE_E,
    XML_PARSER_ENUM_ID_PSEPORT_TYPE_E,
    XML_PARSER_ENUM_ID_POWER_STATUS_TYPE_E,
    XML_PARSER_ENUM_ID_PHY_TYPE_TYPE_E,
    XML_PARSER_ENUM_ID_PHY_FIRMWARE_DOWNLOAD_METHOD_TYPE_E,
    XML_PARSER_ENUM_ID_COLOR_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STATE_TYPE_E,
    XML_PARSER_ENUM_ID_LED_GPIO_I2C_PP_REG_INTERFACE_TYPE_E,
    XML_PARSER_ENUM_ID_LED_GPIO_I2C_PHY_INTERFACE_TYPE_E,
    XML_PARSER_ENUM_ID_LED_GPIO_I2C_PHY_PP_INTERFACE_TYPE_E,
    XML_PARSER_ENUM_ID_CPU_TYPE_TYPE_E,
    XML_PARSER_ENUM_ID_BUTTON_TYPE_E,
    XML_PARSER_ENUM_ID_SENSOR_HW_TYPE_E,
    XML_PARSER_ENUM_ID_THRESHOLD_TYPE_E,
    XML_PARSER_ENUM_ID_I2C_TRANSACTION_TYPE_E,
    XML_PARSER_ENUM_ID_PSE_TYPE_E,
    XML_PARSER_ENUM_ID_PHY_SMI_XSML_ROLE_TYPE_E,
    XML_PARSER_ENUM_ID_PORT_LED_SUPPORTED_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_ORDER_MODE_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_BLINK_DUTY_CYCLE_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_BLINK_DURATION_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_PULSE_STRETCH_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_CLASS5_SELECT_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_CLASS13_SELECT_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_CLOCK_OUT_FREQUENCY_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_BLINK_SELECT_TYPE_E,
    XML_PARSER_ENUM_ID_LED_STREAM_PORT_TYPE_E,
    XML_PARSER_ENUM_ID_POE_HARDWARE_TYPE_E,
    XML_PARSER_ENUM_ID_POE_MAPPING_METHOD_TYPE_E,
    XML_PARSER_ENUM_ID_POE_POWERED_PD_PORTS_TYPE_E,
    XML_PARSER_ENUM_ID_POE_MCU_TYPE_E,
    XML_PARSER_ENUM_ID_POE_COMMUNICATION_TYPE_E,
    XML_PARSER_ENUM_ID_POE_HOST_SERIAL_CHANNEL_TYPE_E,
    XML_PARSER_ENUM_ID_LAST_E
} XML_PARSER_ENUM_ID_ENT;

typedef struct {
    /** @brief   Size of the array */
    UINT_32         arr_size;
    /** @brief   Array of string enums values */
    char         ** strEnumArr;
    /** @brief   Array of integer enums values */
    UINT_8       *  intEnumArr;
} XML_PARSER_ENUM_DB_STC;

typedef struct {
    /** @brief   Size of the array */
    UINT_32         arr_size;
    /** @brief   Array of string bit values */
    char         ** strBitArr;
    /** @brief   Array of integer bit values */
    UINT_32      *  intBitArr;
} XML_PARSER_BITS_DB_STC;

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserSave ( IN XML_PARSER_ROOT_DESCRIPTOR_TYP rootId );
 *
 * @brief   Save changes to XML filename which was used to build the database
 *
 * @param [in]  rootId  Descriptor that was returned from xmlParserBuild function.
 *
 * @return  XML_PARSER_RET_CODE_WRONG_PARAM if rootId if invalid XML_PARSER_RET_CODE_ERROR if
 *          could not save the file.
 */

XML_PARSER_RET_CODE_TYP xmlParserSave(
    IN  XML_PARSER_ROOT_DESCRIPTOR_TYP  rootId
);

/**
 * @fn  XML_PARSER_RET_CODE_TYP xmlParserSaveAs ( IN XML_PARSER_ROOT_DESCRIPTOR_TYP rootId, IN char * xmlFilePathPtr );
 *
 * @brief   Save changes to XML filename which was used to build the database
 *
 * @param [in]  rootId          Descriptor that was returned from xmlParserBuild function.
 * @param [in]  xmlFilePathPtr  Descriptor that was returned from xmlParserBuild function.
 *
 * @return  XML_PARSER_RET_CODE_ERROR if could not save the file.
 */

XML_PARSER_RET_CODE_TYP xmlParserSaveAs(
    IN  XML_PARSER_ROOT_DESCRIPTOR_TYP  rootId,
    IN  char                          * xmlFilePathPtr
);

/* @}*/

#ifdef __cplusplus
}
#endif

#endif
