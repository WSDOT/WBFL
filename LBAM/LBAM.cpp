///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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

// LBAM.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LBAMps.mk in the project directory.
 
#include "stdafx.h"
#include "resource.h"
#include <initguid.h> 
#include "WBFLLBAM.h"
 
#include "WBFLLBAM_i.c" 
#include "WBFLTools_i.c"

#include "StressPoint.h"
#include "StressPoints.h"
#include "CrossSection.h"
#include "Segment.h"
#include "SegmentItem.h"
#include "Segments.h"
#include "FilteredSegmentCollection.h"
#include "SuperstructureMember.h"
#include "SuperstructureMembers.h"
#include "Model.h"
#include "Support.h"
#include "Supports.h"
#include "TemporarySupport.h"
#include "TemporarySupports.h"
#include "Span.h"
#include "Spans.h"
#include "DistributionFactor.h"
#include "POI.h"
#include "POIs.h"
#include "Stage.h"
#include "Stages.h"
#include "PointLoad.h"
#include "PointLoads.h"
#include "DistributedLoad.h"
#include "DistributedLoads.h"
#include "SettlementLoad.h"
#include "SettlementLoads.h"
#include "TemperatureLoad.h"
#include "TemperatureLoads.h"
#include "StrainLoad.h"
#include "StrainLoads.h"
#include "LoadGroup.h"
#include "LoadGroups.h"
#include "LiveLoad.h"
#include "LiveLoadModel.h"
#include "VehicularLoads.h"
#include "VehicularLoad.h"
#include "Axle.h"
#include "Axles.h"
#include "LoadCase.h"
#include "LoadCases.h"
#include "LoadCombination.h"
#include "LoadCombinations.h"
#include "DistributionFactors.h"
#include "DistributionFactorSegment.h"
#include "LinearDistributionFactorSegment.h"
#include "FilteredDfSegmentCollection.h"
#include "POIStressPointsItem.h"
#include "POIStressPoints.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_StressPoint, CStressPoint)
OBJECT_ENTRY(CLSID_StressPoints, CStressPoints)
OBJECT_ENTRY(CLSID_SegmentCrossSection, CSegmentCrossSection)
OBJECT_ENTRY(CLSID_Segment, CSegment)
OBJECT_ENTRY(CLSID_SuperstructureMember, CSuperstructureMember)
OBJECT_ENTRY(CLSID_SuperstructureMembers, CSuperstructureMembers)
OBJECT_ENTRY(CLSID_LBAMModel, CModel)
OBJECT_ENTRY(CLSID_Support, CSupport)
OBJECT_ENTRY(CLSID_Supports, CSupports)
OBJECT_ENTRY(CLSID_TemporarySupport, CTemporarySupport)
OBJECT_ENTRY(CLSID_TemporarySupports, CTemporarySupports)
OBJECT_ENTRY(CLSID_Span, CSpan)
OBJECT_ENTRY(CLSID_Spans, CSpans)
OBJECT_ENTRY(CLSID_POI, CPOI)
OBJECT_ENTRY(CLSID_POIs, CPOIs)
OBJECT_ENTRY(CLSID_Stage, CStage)
OBJECT_ENTRY(CLSID_Stages, CStages)
OBJECT_ENTRY(CLSID_PointLoad, CPointLoad)
OBJECT_ENTRY(CLSID_PointLoads, CPointLoads)
OBJECT_ENTRY(CLSID_DistributedLoad, CDistributedLoad)
OBJECT_ENTRY(CLSID_DistributedLoads, CDistributedLoads)
OBJECT_ENTRY(CLSID_SettlementLoad, CSettlementLoad)
OBJECT_ENTRY(CLSID_SettlementLoads, CSettlementLoads)
OBJECT_ENTRY(CLSID_TemperatureLoad, CTemperatureLoad)
OBJECT_ENTRY(CLSID_TemperatureLoads, CTemperatureLoads)
OBJECT_ENTRY(CLSID_StrainLoad, CStrainLoad)
OBJECT_ENTRY(CLSID_StrainLoads, CStrainLoads)
OBJECT_ENTRY(CLSID_LoadGroup, CLoadGroup)
OBJECT_ENTRY(CLSID_LoadGroups, CLoadGroups)
OBJECT_ENTRY(CLSID_LiveLoad, CLiveLoad)
OBJECT_ENTRY(CLSID_LiveLoadModel, CLiveLoadModel)
OBJECT_ENTRY(CLSID_VehicularLoads, CVehicularLoads)
OBJECT_ENTRY(CLSID_VehicularLoad, CVehicularLoad)
OBJECT_ENTRY(CLSID_Axle, CAxle)
OBJECT_ENTRY(CLSID_Axles, CAxles)
OBJECT_ENTRY(CLSID_LoadCase, CLoadCase)
OBJECT_ENTRY(CLSID_LoadCases, CLoadCases)
OBJECT_ENTRY(CLSID_LoadCombination, CLoadCombination)
OBJECT_ENTRY(CLSID_LoadCombinations, CLoadCombinations)
OBJECT_ENTRY(CLSID_DistributionFactor, CDistributionFactor)
OBJECT_ENTRY(CLSID_DistributionFactors, CDistributionFactors)
OBJECT_ENTRY(CLSID_DistributionFactorSegment, CDistributionFactorSegment)
OBJECT_ENTRY(CLSID_LinearDistributionFactorSegment, CLinearDistributionFactorSegment)
OBJECT_ENTRY(CLSID_FilteredDfSegmentCollection, CFilteredDfSegmentCollection)
OBJECT_ENTRY(CLSID_POIStressPointsItem, CPOIStressPointsItem)
OBJECT_ENTRY(CLSID_POIStressPoints, CPOIStressPoints)
END_OBJECT_MAP()
 
/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLLBAM);
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
