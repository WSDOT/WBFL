// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__FF18985F_F484_4470_82BC_88603EE38124__INCLUDED_)
#define AFX_STDAFX_H__FF18985F_F484_4470_82BC_88603EE38124__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

// target platform is Win2000 or later
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxctl.h>
#include <afxcview.h>

#include <WBFLDebug.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>
#include <COMDEF.H>
#include "WbflAtlExt.h"
#include "LBAMViewerGUID.c"

#include <DManip\DManip.h>
#include "DManipTools\DManipTools.h"

#include <WBFLTools.h>
#include <WBFLUnitServer.h>
#include <WBFLGeometry.h>
#include <WBFLLBAM.h>
#include <WBFLLBAMAnalysis.h>
#include <WBFLLBAMLiveLoader.h>
#include <WBFLLBAMLoadCombiner.h>
#include <WBFLLBAMUtility.h>
#include <WBFLLBAMAnalysisUtility.h>

#include <Checks.h>

#define THROW_HR(hr) { ATLASSERT(0); throw hr;}
#define PROCESS_HR(hr) if (FAILED(hr)||hr==S_FALSE){ THROW_HR(hr) }


	#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CLBAMViewerModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	DWORD dwThreadID;
};
extern CLBAMViewerModule _Module;
#include <atlcom.h>


// simple, exception-safe class for blocking events
class SimpleMutex
{
public:
   SimpleMutex(bool& flag):
   m_Flag(flag)
   {
      m_Flag = false;
   }

   ~SimpleMutex()
   {
      m_Flag = true;
   }
private:
   bool& m_Flag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FF18985F_F484_4470_82BC_88603EE38124__INCLUDED_)
