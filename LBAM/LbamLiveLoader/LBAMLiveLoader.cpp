///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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

// LBAMLiveLoader.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LBAMLiveLoaderps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLLBAMLiveLoader.h"
#include <WBFLLBAMLiveLoader_i.c>

#include <WBFLLBAMAnalysis_i.c>
#include <WBFLLBAM_i.c>
#include <WBFLLBAMUtility_i.c>
#include <WBFLTools_i.c>

#include "VehicularAnalysisContext.h"
#include "BasicVehicularResponse.h"
#include "BruteForceVehicularResponse.h"
#include "BruteForceVehicularResponse2.h"
#include "LiveLoadConfiguration.h"
#include "LiveLoadModelResponse.h"
#include "LiveLoadModelSectionResults.h"
#include "LiveLoadModelResults.h"
#include "LiveLoadModelStressResults.h"
#include "EnvelopedVehicularResponseFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VehicularAnalysisContext, CVehicularAnalysisContext)
OBJECT_ENTRY(CLSID_BasicVehicularResponse, CBasicVehicularResponse)
OBJECT_ENTRY(CLSID_BruteForceVehicularResponse, CBruteForceVehicularResponse)
OBJECT_ENTRY(CLSID_BruteForceVehicularResponse2, CBruteForceVehicularResponse2)
OBJECT_ENTRY(CLSID_LiveLoadConfiguration, CLiveLoadConfiguration)
OBJECT_ENTRY(CLSID_LiveLoadModelResponse, CLiveLoadModelResponse)
OBJECT_ENTRY(CLSID_LiveLoadModelSectionResults, CLiveLoadModelSectionResults)
OBJECT_ENTRY(CLSID_LiveLoadModelResults, CLiveLoadModelResults)
OBJECT_ENTRY(CLSID_LiveLoadModelStressResults, CLiveLoadModelStressResults)
OBJECT_ENTRY(CLSID_EnvelopedVehicularResponseFactory,CEnvelopedVehicularResponseFactory)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLLBAMLiveLoader);
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
