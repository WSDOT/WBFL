// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__23497475_C954_11D5_B085_00105A9AF985__INCLUDED_)
#define AFX_STDAFX_H__23497475_C954_11D5_B085_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <afxwin.h>
#include <afxdisp.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlconv.h>
#include <comdef.h>

#if !defined INCLUDED_WBFLATLEXT_H_
#include <WbflAtlExt.h> // WBFL ATL Extensions and helpers
#endif // INCLUDED_WBFLATLEXT_H_

#include "LBAMUtility.h"


// macros to help error processing
// short-hand version if consistent naming conventions are used
#include "ComException.h"
#define THROW_LBAMTF(errNam) { ATLASSERT(0); throw CComException(__FILE__,__LINE__, IDS_E_##errNam, LBAMTF_E_##errNam, IDH_E_##errNam);}
#define THROW_LBAMTF_MSG(errNam, msg) { ATLASSERT(0); throw CComException(__FILE__,__LINE__, msg, LBAMTF_E_##errNam, IDH_E_##errNam);}

inline CComBSTR GetHelpFile()
{
   return CComBSTR("WBFLLBAMTestFrame.chm");
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__23497475_C954_11D5_B085_00105A9AF985__INCLUDED)
