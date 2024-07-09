/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

/*
 * pdlLibPrefix.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mati
 */

#ifndef PDLIB_H_PDLIB_COMMON_PDLLIBPREFIX_H_
#define PDLIB_H_PDLIB_COMMON_PDLLIBPREFIX_H_

#if defined PDLIBPREFIX
	#define PDLLIB_PASTER(x,y) x ## _ ## y
	#define PDLLIB_EVALUATOR(x,y)  PDLLIB_PASTER(x,y)
	#define PDLLIB_NAME(fun) PDLLIB_EVALUATOR(PDLIBPREFIX, fun)
#else
	#define PDLLIB_NAME(fun) fun
#endif

#define prvXmlParserDebugGetNextOpenedRoot PDLLIB_NAME(prvXmlParserDebugGetNextOpenedRoot)
#define prvXmlParserDebugOpenedDescriptors PDLLIB_NAME(prvXmlParserDebugOpenedDescriptors)
#define prvXmlParserDebugShowTreeByRoot PDLLIB_NAME(prvXmlParserDebugShowTreeByRoot)
#define prvXmlParserDestoryNode PDLLIB_NAME(prvXmlParserDestoryNode)
#define prvXmlParserDestroyNode PDLLIB_NAME(prvXmlParserDestroyNode)
#define prvXmlParserEnumDbBuild PDLLIB_NAME(prvXmlParserEnumDbBuild)
#define xmlParserBuild PDLLIB_NAME(xmlParserBuild)
#define xmlParserDestroy PDLLIB_NAME(xmlParserDestroy)
#define xmlParserFindByPDLLIB_NAME PDLLIB_NAME(xmlParserFindByPDLLIB_NAME)
#define xmlParserFindChildByPDLLIB_NAME PDLLIB_NAME(xmlParserFindChildByPDLLIB_NAME)
#define xmlParserGetFirstChild PDLLIB_NAME(xmlParserGetFirstChild)
#define xmlParserGetIntValue PDLLIB_NAME(xmlParserGetIntValue)
#define xmlParserGetPDLLIB_NAME PDLLIB_NAME(xmlParserGetPDLLIB_NAME)
#define xmlParserGetNextSibling PDLLIB_NAME(xmlParserGetNextSibling)
#define xmlParserGetTagCount PDLLIB_NAME(xmlParserGetTagCount)
#define xmlParserGetValue PDLLIB_NAME(xmlParserGetValue)
#define xmlParserIsEqualPDLLIB_NAME PDLLIB_NAME(xmlParserIsEqualPDLLIB_NAME)
#define xmlParserSetIntValue PDLLIB_NAME(xmlParserSetIntValue)
#define xmlParserSetValue PDLLIB_NAME(xmlParserSetValue)
#define xmlParserUncompressedFileBuild PDLLIB_NAME(xmlParserUncompressedFileBuild)

#define prvPdlibDbDestroy PDLLIB_NAME(prvPdlibDbDestroy)

#endif /* PDLIB_H_PDLIB_COMMON_PDLLIBPREFIX_H_ */
