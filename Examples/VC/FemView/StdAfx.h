// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BCB8A0E9_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_STDAFX_H__BCB8A0E9_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxctl.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>
#include <DManip\DManip.h>
#include <WBFLDebug.h>

#include <WBFLFem2d.h>
#include "JointDrawStrategy.h"
#include "PointLoadDrawStrategy.h"
#include "PointLoadEvents.h"
#include "Fea2dGuid.c"
#include <afxdlgs.h>

#include <WBFLDManip.h>
#include <DManip\DisplayObjectEvents.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BCB8A0E9_E659_11D4_8B81_006097C68A9C__INCLUDED_)
