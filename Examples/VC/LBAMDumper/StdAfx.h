// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#pragma once

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#define _ATL_APARTMENT_THREADED

#include <WBFLDebug.h>


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>

#include <iomanip>

#include <WBFLTools.h>
#include <WBFLUnitServer.h>
#include <WBFLLBAM.h>
#include "..\..\..\LBAM\LBAMUtils.h"
#include <WBFLLBAMAnalysis.h>
#include <WBFLLBAMLiveLoader.h>
#include <WBFLLBAMLoadCombiner.h>
#include <WBFLLBAMUtility.h>
#include <WBFLLBAMAnalysisUtility.h>

#include <WbflAtlExt.h>


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

