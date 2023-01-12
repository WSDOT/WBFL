///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2023  Washington State Department of Transportation
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

// WBFLTools.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f WBFLToolsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLTools.h"

#include "WBFLTools_i.c"
#include "ARPNotice.h"
#include "MohrCircle.h"
#include "StrSave.h"
#include "StrLoad.h"
#include "StructuredSave2.h"
#include "StructuredLoad2.h"
#include "ErrorLog.h"
#include "ProgressMonitorWindow.h"
#include "LngArray.h"
#include "DblArray.h"
#include "BstrArray.h"
#include "UnkArray.h"
#include "IDArray.h"
#include "IndexArray.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_ARPNotice, CARPNotice)
OBJECT_ENTRY(CLSID_MohrCircle, CMohrCircle)
OBJECT_ENTRY(CLSID_StructuredSave, CStrSave)
OBJECT_ENTRY(CLSID_StructuredLoad, CStrLoad)
OBJECT_ENTRY(CLSID_StructuredSave2, CStructuredSave2)
OBJECT_ENTRY(CLSID_StructuredLoad2, CStructuredLoad2)
OBJECT_ENTRY(CLSID_WBFLErrorLog, CErrorLog)
OBJECT_ENTRY(CLSID_ProgressMonitorWindow, CProgressMonitorWindow)
OBJECT_ENTRY(CLSID_LongArray, CLongArray)
OBJECT_ENTRY(CLSID_DblArray, CDblArray)
OBJECT_ENTRY(CLSID_BstrArray, CBstrArray)
OBJECT_ENTRY(CLSID_UnkArray, CUnkArray)
OBJECT_ENTRY(CLSID_IDArray, CIDArray)
OBJECT_ENTRY(CLSID_IndexArray, CIndexArray)
OBJECT_ENTRY(CLSID_LogFile, CLogFile)
END_OBJECT_MAP()

class CWBFLToolsApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWBFLToolsApp)
	public:
    virtual BOOL InitInstance() override;
    virtual int ExitInstance() override;
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWBFLToolsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CWBFLToolsApp, CWinApp)
	//{{AFX_MSG_MAP(CWBFLToolsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CWBFLToolsApp theApp;

BOOL CWBFLToolsApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_WBFLTools);
    return CWinApp::InitInstance();
}

int CWBFLToolsApp::ExitInstance()
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
