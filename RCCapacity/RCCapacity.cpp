///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// RCCapacity.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f RCCapacityps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLRCCapacity.h"

#include <WBFLRCCapacity_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLSections_i.c>
#include <WBFLUnitServer_i.c>
#include <WBFLTools_i.c>

#include "RCBeam.h"
#include "RCSolution.h"
#include "LRFDSolution.h"
#include "LRFDSolver.h"
#include "LRFDSolver2.h"
#include "LFDSolver.h"
#include "PCISolver.h"
#include "NLSolver.h"
#include "RCBeam2.h"
#include "UnconfinedConcrete.h"
#include "UHPConcrete.h"
#include "PSPowerFormula.h"
#include "LRFDPrestressFormula.h"
#include "RebarModel.h"
#include "StrainHardenedRebarModel.h"
#include "PCISolution.h"
#include "MixedSolver.h"
#include "RCBeam2Ex.h"
#include "RCSolutionEx.h"
#include "LRFDSolutionEx.h"
#include "PCISolutionEx.h"
#include "RoundColumn.h"
#include "GeneralSection.h"
#include "GeneralSectionSlice.h"
#include "GeneralSectionSolver.h"
#include "MomentCurvatureSolution.h"
#include "MomentCurvatureSolver.h"
#include "MomentCapacitySolver.h"
#include "CircularManderSection.h"
#include "ManderModel.h"
#include "InteractionCurveSolution.h"
#include "InteractionCurveSolver.h"
#include "InteractionCapacityCurveSolution.h"
#include "AxialInteractionCurveSolver.h"
#include "MomentInteractionCurveSolver.h"
#include "SectionBuilder.h"
#include "CapacityReductionFactor.h"
#include "CrackedSectionSlice.h"
#include "CrackedSectionSolver.h"
#include "CrackedSectionSolution.h"
#include "RambergOsgoodModel.h"
#include "PCIUHPConcrete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
   OBJECT_ENTRY(CLSID_RCBeam, CRCBeam)
   OBJECT_ENTRY(CLSID_RCSolution, CRCSolution)
   OBJECT_ENTRY(CLSID_LRFDSolution, CLRFDSolution)
   OBJECT_ENTRY(CLSID_LRFDSolver, CLRFDSolver)
   OBJECT_ENTRY(CLSID_LRFDSolver2, CLRFDSolver2)
   OBJECT_ENTRY(CLSID_LFDSolver, CLFDSolver)
   OBJECT_ENTRY(CLSID_PCISolver, CPCISolver)
   OBJECT_ENTRY(CLSID_NLSolver, CNLSolver)
   OBJECT_ENTRY(CLSID_RCBeam2, CRCBeam2)
   OBJECT_ENTRY(CLSID_UnconfinedConcrete, CUnconfinedConcrete)
   OBJECT_ENTRY(CLSID_UHPConcrete, CUHPConcrete)
   OBJECT_ENTRY(CLSID_PSPowerFormula, CPSPowerFormula)
   OBJECT_ENTRY(CLSID_LRFDPrestressFormula, CLRFDPrestressFormula)
   OBJECT_ENTRY(CLSID_RebarModel, CRebarModel)
   OBJECT_ENTRY(CLSID_PCISolution, CPCISolution)
   OBJECT_ENTRY(CLSID_MixedSolver, CMixedSolver)
   OBJECT_ENTRY(CLSID_RCBeam2Ex, CRCBeam2Ex)
   OBJECT_ENTRY(CLSID_RCSolutionEx, CRCSolutionEx)
   OBJECT_ENTRY(CLSID_LRFDSolutionEx, CLRFDSolutionEx)
   OBJECT_ENTRY(CLSID_PCISolutionEx, CPCISolutionEx)
   OBJECT_ENTRY(CLSID_StrainHardenedRebarModel, CStrainHardenedRebarModel)
   OBJECT_ENTRY(CLSID_RoundColumn,CRoundColumn)
   OBJECT_ENTRY(CLSID_GeneralSection,CGeneralSection)
   OBJECT_ENTRY(CLSID_GeneralSectionSlice,CGeneralSectionSlice)
   OBJECT_ENTRY(CLSID_GeneralSectionSolver,CGeneralSectionSolver)
   OBJECT_ENTRY(CLSID_MomentCurvatureSolution,CMomentCurvatureSolution)
   OBJECT_ENTRY(CLSID_MomentCurvatureSolver,CMomentCurvatureSolver)
   OBJECT_ENTRY(CLSID_MomentCapacitySolver,CMomentCapacitySolver)
   OBJECT_ENTRY(CLSID_CircularManderSection,CCircularManderSection)
   OBJECT_ENTRY(CLSID_ManderModel,CManderModel)
   OBJECT_ENTRY(CLSID_InteractionCurveSolution,CInteractionCurveSolution)
   OBJECT_ENTRY(CLSID_InteractionCurveSolver,CInteractionCurveSolver)
   OBJECT_ENTRY(CLSID_InteractionCapacityCurveSolution,CInteractionCapacityCurveSolution)
   OBJECT_ENTRY(CLSID_AxialInteractionCurveSolver,CAxialInteractionCurveSolver)
   OBJECT_ENTRY(CLSID_MomentInteractionCurveSolver,CMomentInteractionCurveSolver)
   OBJECT_ENTRY(CLSID_SectionBuilder,CSectionBuilder)
   OBJECT_ENTRY(CLSID_CapacityReductionFactor,CCapacityReductionFactor)
   OBJECT_ENTRY(CLSID_CrackedSectionSlice,CCrackedSectionSlice)
   OBJECT_ENTRY(CLSID_CrackedSectionSolver,CCrackedSectionSolver)
   OBJECT_ENTRY(CLSID_CrackedSectionSolution,CCrackedSectionSolution)
   OBJECT_ENTRY(CLSID_RambergOsgoodModel, CRambergOsgoodModel)
   OBJECT_ENTRY(CLSID_PCIUHPConcrete,CPCIUHPConcrete)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLRCCapacity);
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
