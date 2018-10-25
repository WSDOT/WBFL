///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2011  Washington State Department of Transportation
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

// LBAMAnalysis.cpp : Implementation of DLL Exports.

// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LBAMAnalysisps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLLBAMAnalysis.h"

#include "WBFLLBAMAnalysis_i.c"

#include <WBFLLBAM_i.c>
#include <WBFLLBAMUtility_i.c>
#include <WBFLTools_i.c>
#include <WBFLLoading_i.c>
#include <WBFLGeometry_i.c>

//#include <WBFLFem2d_i.c>
// RAB: I can't get this DLL to link unless this CLSID is defined explicitly here
//      If the CLSID for Fem2dModel changes, it must be changed here as well
DEFINE_GUID(CLSID_Fem2dModel,0x807A6236,0xAE89,0x11D4,0xAF,0x38,0x00,0x10,0x5A,0x9A,0xF9,0x85);

#include "LoadGroupResponse.h"
#include "Result3Ds.h"
#include "SectionResult3Ds.h"
#include "LoadGroupDeflectionResponse.h"
#include "LoadGroupForceResponse.h"
#include "InfluenceLine.h"
#include "StressResult.h"
#include "StressResults.h"
#include "SectionStressResult.h"
#include "SectionStressResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap) 
OBJECT_ENTRY(CLSID_SectionResult3D, CSectionResult3D)
OBJECT_ENTRY(CLSID_Result3D, CResult3D)
OBJECT_ENTRY(CLSID_SectionResult3Ds, CSectionResult3Ds)
OBJECT_ENTRY(CLSID_Result3Ds, CResult3Ds)
OBJECT_ENTRY(CLSID_LoadGroupDeflectionResponse, CLoadGroupDeflectionResponse)
OBJECT_ENTRY(CLSID_LoadGroupForceResponse, CLoadGroupForceResponse)
OBJECT_ENTRY(CLSID_InfluenceLine, CInfluenceLine)
OBJECT_ENTRY(CLSID_StressResult, CStressResult)
OBJECT_ENTRY(CLSID_StressResults, CStressResults)
OBJECT_ENTRY(CLSID_SectionStressResult, CSectionStressResult)
OBJECT_ENTRY(CLSID_SectionStressResults, CSectionStressResults)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLLBAMAnalysis);
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
