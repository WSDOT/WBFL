///////////////////////////////////////////////////////////////////////
// ToolsStorage - Test driver for WBFLTools library
// Copyright © 1999-2020  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// StorageTest.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f StorageTestps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>

#if defined _DEBUG
#if defined VBA_BUILD
#if defined _WIN64
#include "x64\VBA_Debug\StorageTest.h"
#else
#include "Win32\VBA_Debug\StorageTest.h"
#endif
#else
#if defined _WIN64
#include "x64\Debug\StorageTest.h"
#else
#include "Win32\Debug\StorageTest.h"
#endif
#endif
#else
#if defined VBA_BUILD
#if defined _WIN64
#include "x64\VBA_Release\StorageTest.h"
#else
#include "Win32\VBA_Release\StorageTest.h"
#endif
#else
#if defined _WIN64
#include "x64\Release\StorageTest.h"
#else
#include "Win32\Release\StorageTest.h"
#endif
#endif
#endif


#if defined _DEBUG
#if defined VBA_BUILD
#if defined _WIN64
#include "x64\VBA_Debug\StorageTest_i.c"
#else
#include "Win32\VBA_Debug\StorageTest_i.c"
#endif
#else
#if defined _WIN64
#include "x64\Debug\StorageTest_i.c"
#else
#include "Win32\Debug\StorageTest_i.c"
#endif
#endif
#else
#if defined VBA_BUILD
#if defined _WIN64
#include "x64\VBA_Release\StorageTest_i.c"
#else
#include "Win32\VBA_Release\StorageTest_i.c"
#endif
#else
#if defined _WIN64
#include "x64\Release\StorageTest_i.c"
#else
#include "Win32\Release\StorageTest_i.c"
#endif
#endif
#endif

#include "PCircle.h"
#include "PCompositeShape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_PCircle, CPCircle)
OBJECT_ENTRY(CLSID_PCompositeShape, CPCompositeShape)
END_OBJECT_MAP()

class CStorageTestApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStorageTestApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CStorageTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CStorageTestApp, CWinApp)
	//{{AFX_MSG_MAP(CStorageTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CStorageTestApp theApp;

BOOL CStorageTestApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_STORAGETESTLib);
    return CWinApp::InitInstance();
}

int CStorageTestApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


