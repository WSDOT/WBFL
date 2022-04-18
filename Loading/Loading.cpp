///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2022  Washington State Department of Transportation
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

// Loading.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f Loadingps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLLoading.h"

#include "WBFLLoading_i.c"

#include "PointLoad.h"
#include "PointLoads.h"
#include "DistributedLoad.h"
#include "DistributedLoads.h"
#include "SettlementLoad.h"
#include "SettlementLoads.h"
#include "StrainLoad.h"
#include "StrainLoads.h"
#include "TemperatureLoad.h"
#include "TemperatureLoads.h"
#include "Axle.h"
#include "Axles.h"
#include "VehicularLoad.h"
#include "VehicularLoads.h"
#include "LoadGroup.h"
#include "LoadGroups.h"
#include "LoadCase.h"
#include "LoadCases.h"
#include "LoadCombination.h"
#include "LoadCombinations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
   OBJECT_ENTRY(CLSID_ldPointLoad, CPointLoad)
   OBJECT_ENTRY(CLSID_ldPointLoads, CPointLoads)
   OBJECT_ENTRY(CLSID_ldDistributedLoad, CDistributedLoad)
   OBJECT_ENTRY(CLSID_ldDistributedLoads, CDistributedLoads)
   OBJECT_ENTRY(CLSID_ldSettlementLoad, CSettlementLoad)
   OBJECT_ENTRY(CLSID_ldSettlementLoads, CSettlementLoads)
   OBJECT_ENTRY(CLSID_ldStrainLoad, CStrainLoad)
   OBJECT_ENTRY(CLSID_ldStrainLoads, CStrainLoads)
   OBJECT_ENTRY(CLSID_ldTemperatureLoad, CTemperatureLoad)
   OBJECT_ENTRY(CLSID_ldTemperatureLoads, CTemperatureLoads)
   OBJECT_ENTRY(CLSID_ldAxle, CAxle)
   OBJECT_ENTRY(CLSID_ldAxles, CAxles)
   OBJECT_ENTRY(CLSID_ldVehicularLoad, CVehicularLoad)
   OBJECT_ENTRY(CLSID_ldVehicularLoads, CVehicularLoads)
   OBJECT_ENTRY(CLSID_ldLoadGroup, CLoadGroup)
   OBJECT_ENTRY(CLSID_ldLoadGroups, CLoadGroups)
   OBJECT_ENTRY(CLSID_ldLoadCase, CLoadCase)
   OBJECT_ENTRY(CLSID_ldLoadCases, CLoadCases)
   OBJECT_ENTRY(CLSID_ldLoadCombination, CLoadCombination)
   OBJECT_ENTRY(CLSID_ldLoadCombinations, CLoadCombinations)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLLoading);
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

