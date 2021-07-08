///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2021  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// DManipTools.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f DManipToolsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"

#include <WBFLTools_i.c>
#include <WBFLGeometry_i.c>
#include <DManip\DManip_clsid.cpp>

#include <WBFLDManip_i.c>
#include <WBFLDManipTools_i.c>

#include "DataPointDrawStrategy.h"
#include "DataPointEvents.h"

#include "GraphXyDisplayObjectImpl.h"
#include "LegendDisplayObject.h"
#include "LegendEntryImpl.h"
#include "DataSet2dImpl.h"
#include "LegendEntryImpl.h"
#include "DManipToolsDisplayObjectFactory.h"
#include "GraphXyDataProvider.h"
#include "PolyLineDisplayObjectImpl.h"
#include "CompoundCurveDisplayObjectImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
   OBJECT_ENTRY(CLSID_GraphXyDisplayObject, CGraphXyDisplayObject)
   OBJECT_ENTRY(CLSID_DataSet2d, CDataSet2dImpl)
   OBJECT_ENTRY(CLSID_LegendDisplayObject, CLegendDisplayObject)
   OBJECT_ENTRY(CLSID_LegendEntry, CLegendEntryImpl)
   OBJECT_ENTRY(CLSID_DManipToolsDisplayObjectFactory, CDManipToolsDisplayObjectFactory)
   OBJECT_ENTRY(CLSID_GraphXyDataProvider, CGraphXyDataProvider)
   OBJECT_ENTRY(CLSID_PolyLineDisplayObject, CPolyLineDisplayObjectImpl)
   OBJECT_ENTRY(CLSID_CompoundCurveDisplayObject, CCompoundCurveDisplayObjectImpl)
END_OBJECT_MAP()

class CDManipToolsApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDManipToolsApp)
	public:
    virtual BOOL InitInstance() override;
    virtual int ExitInstance() override;
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDManipToolsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CDManipToolsApp, CWinApp)
	//{{AFX_MSG_MAP(CDManipToolsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDManipToolsApp theApp;

BOOL CDManipToolsApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_WBFLDManipTools);
    return CWinApp::InitInstance();
}

int CDManipToolsApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
   LONG cLock = _Module.GetLockCount();
   bool bCanUnload = ( cLock == 0 );
	return ( bCanUnload ) ? S_OK : S_FALSE;
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
    return _Module.RegisterServer(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(FALSE);
}
