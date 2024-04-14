/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */
/**
********************************************************************************
 * @file pdlInit.c
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
 * @brief Platform driver layer - PDL driver initialization
 *
 * @version   1
********************************************************************************
*/
/* *************************************************************************
 *$              EXTERNAL DECLARATIONS (IMPORT)
 *!**************************************************************************
 *!*/
#include "../../../h/pdlib/xml/private/prvXmlParser.h"
#include "../../../h/pdlib/xml/private/prvXmlParser.h"
#include "../../../h/pdlib/lib/private/prvPdlLib.h"
#include "../../../h/pdlib/init/pdlInit.h"

/* *************************************************************************
 *$              LOCAL VARIABLE DEFINITIONS
 *!**************************************************************************
 *!*/
/* *************************************************************************
 *$              LOCAL FUNCTION DEFINITIONS
 *!**************************************************************************
 *!*/

/**
 * @fn  PDL_STATUS pdlibInit ( IN char * xmlFilePathPtr, IN char * xmlTagPrefixPtr, IN PDLIB_OS_CALLBACK_API_STC * callbacksPTR )
 *
 * @brief   initialize PDLIB
 *
 * @param [in]  xmlFilePathPtr  XML location.
 * @param [in]  xmlTagPrefixPtr XML tag's prefix.
 * @param [in]  callbacksPTR    application-specific implementation for os services.
 *
 * @return  PDL_STATUS.
 */

PDL_STATUS pdlibInit(
    IN char                             * xmlFilePathPtr,
    IN char                             * xmlTagPrefixPtr,
    IN PDLIB_OS_CALLBACK_API_STC        * callbacks_PTR,
    OUT XML_PARSER_ROOT_DESCRIPTOR_TYP  * id_PTR
)
{
    /* ***************************************************************************/
    /* L O C A L   D E C L A R A T I O N S   A N D   I N I T I A L I Z A T I O N */
    /* ***************************************************************************/
    PDL_STATUS                              rc;
    XML_PARSER_RET_CODE_TYP                 xmlStatus;
    /* ***************************************************************************/
    /*                      F U N C T I O N   L O G I C                          */
    /* ***************************************************************************/
    rc = pdlibLibInit(callbacks_PTR);
    PDLIB_CHECK_STATUS(rc);

    xmlStatus = xmlParserBuild(xmlFilePathPtr, xmlTagPrefixPtr, id_PTR);
    XML_CHECK_STATUS(xmlStatus);


    return PDL_OK;
}
/*$ END OF pdlibInit */


