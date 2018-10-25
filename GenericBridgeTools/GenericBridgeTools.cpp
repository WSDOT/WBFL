///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2017  Washington State Department of Transportation
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

// GenericBridgeTools.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f GenericBridgeToolsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"

#include <WBFLGenericBridgeTools.h>

#include <initguid.h>
#include <WBFLGenericBridgeTools_i.c>

//#include <WBFLGenericBridge.h>
#include <WBFLGenericBridge_i.c>

#include <WBFLCogo_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLSections_i.c>
#include <WBFLTools_i.c>

#include "EffectiveFlangeWidthTool.h"
#include "EffectiveFlangeWidthDetails.h"
#include "BridgeGeometryTool.h"
#include "SectionCutTool.h"
#include "PrecastGirder.h"
#include "StrandGrid.h"

#include "FlexRebarLayoutItem.h"
#include "BridgeDeckRebarLayout.h"
#include "StrandFillTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
   OBJECT_ENTRY(CLSID_EffectiveFlangeWidthTool, CEffectiveFlangeWidthTool)
   OBJECT_ENTRY(CLSID_EffectiveFlangeWidthDetails, CEffectiveFlangeWidthDetails)
   OBJECT_ENTRY(CLSID_BridgeGeometryTool,       CBridgeGeometryTool)
   OBJECT_ENTRY(CLSID_SectionCutTool,           CSectionCutTool)
   OBJECT_ENTRY(CLSID_PrecastGirder,            CPrecastGirder)
   OBJECT_ENTRY(CLSID_StrandGrid, CStrandGrid)
   OBJECT_ENTRY(CLSID_StrandFillTool, CStrandFillTool)
   OBJECT_ENTRY(CLSID_FlexRebarLayoutItem,CFlexRebarLayoutItem)
   OBJECT_ENTRY(CLSID_BridgeDeckRebarLayout,CBridgeDeckRebarLayout)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLGenericBridgeTools);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
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
