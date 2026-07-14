// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <WBFLDebug.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>
#include <iostream>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

