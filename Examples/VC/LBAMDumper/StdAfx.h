// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__511A1B9C_DDA1_4DE4_B09A_B4FCC95A44F6__INCLUDED_)
#define AFX_STDAFX_H__511A1B9C_DDA1_4DE4_B09A_B4FCC95A44F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_STDAFX_H__511A1B9C_DDA1_4DE4_B09A_B4FCC95A44F6__INCLUDED)
