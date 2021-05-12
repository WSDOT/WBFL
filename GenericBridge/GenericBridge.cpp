///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// GenericBridge.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f GenericBridgeps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLGenericBridge.h"

#include "WBFLGenericBridge_i.c"
#include "WBFLTools_i.c"
#include "WBFLCogo_i.c"
#include "WBFLGeometry_i.c"
#include "WBFLBridgeGeometry_i.c"
#include "WBFLSections_i.c"

#include "GenericBridgeImpl.h"
#include "BridgePier.h"
#include "PierCollection.h"
#include "SuperstructureMember.h"
#include "Segment.h"
#include "PrismaticSuperstructureMemberSegment.h"
#include "FlangedGirderEndBlockSegment.h"
#include "VoidedSlabEndBlockSegment.h"
#include "DeckedSlabBeamEndBlockSegment.h"
#include "BoxBeamEndBlockSegment.h"
#include "UGirderSection2EndBlockSegment.h"
#include "TaperedGirderSegment.h"
#include "ThickenedFlangeBulbTeeSegment.h"
#include "SegmentItem.h"
#include "FilteredSegmentCollection.h"
#include "SuperstructureMemberCollection.h"

#include "Column.h"
#include "ColumnLayout.h"
#include "BearingLayout.h"
#include "LinearCrossBeam.h"
#include "Pier.h"

#include "Material.h"
#include "CastSlab.h"
#include "PrecastSlab.h"
#include "OverlaySlab.h"
#include "AlignmentOffsetStrategy.h"
#include "EdgePathStrategy.h"

#include "GirderSections.h"
#include "UGirderSection.h"
#include "UGirderSection2.h"
#include "MultiWebSection.h"
#include "MultiWebSection2.h"
#include "VoidedSlabSection.h"
#include "VoidedSlabSection2.h"
#include "BoxBeamSection.h"
#include "DeckedSlabBeamSection.h" 

#include "FShapeBarrier.h"
#include "SidewalkBarrier.h"
#include "GenericBarrier.h"

#include "FlangedSplicedGirderSegment.h"
#include "USplicedGirderSegment.h"
#include "NUSplicedGirderSegment.h"

#include "ParabolicTendonSegment.h"
#include "LinearTendonSegment.h"
#include "Tendon.h"
#include "OffsetTendon.h"
#include "TendonCollection.h"

#include "PrestressingStrand.h"

#include "Rebar.h"
#include "RebarLayout.h"
#include "RebarFactory.h"
#include "RebarSectionItem.h"
#include "RebarSection.h"
#include "RebarRowPattern.h"
#include "RebarRowFacePattern.h"
#include "CrossBeamRebarPattern.h"
#include "FixedLengthRebarLayoutItem.h"
#include "BridgeDeckRebarLayoutItem.h"
#include "BridgeDeckRebarPattern.h"
#include "NegativeMomentBridgeDeckRebarLayoutItem.h"

#include "CastingRegion.h"
#include "CastingRegions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
   OBJECT_ENTRY(CLSID_GenericBridge, CGenericBridge)
   OBJECT_ENTRY(CLSID_PrismaticSegment, CSegment)
   OBJECT_ENTRY(CLSID_PrismaticSuperstructureMemberSegment, CPrismaticSuperstructureMemberSegment)
   OBJECT_ENTRY(CLSID_FlangedGirderEndBlockSegment, CFlangedGirderEndBlockSegment)
   OBJECT_ENTRY(CLSID_VoidedSlabEndBlockSegment, CVoidedSlabEndBlockSegment)
   OBJECT_ENTRY(CLSID_UGirderSection2EndBlockSegment, CUGirderSection2EndBlockSegment)
   OBJECT_ENTRY(CLSID_DeckedSlabBeamEndBlockSegment, CDeckedSlabBeamEndBlockSegment)
   OBJECT_ENTRY(CLSID_BoxBeamEndBlockSegment, CBoxBeamEndBlockSegment)
   OBJECT_ENTRY(CLSID_TaperedGirderSegment, CTaperedGirderSegment)
   OBJECT_ENTRY(CLSID_ThickenedFlangeBulbTeeSegment, CThickenedFlangeBulbTeeSegment)
   OBJECT_ENTRY(CLSID_FlangedSplicedGirderSegment, CFlangedSplicedGirderSegment)
   OBJECT_ENTRY(CLSID_USplicedGirderSegment, CUSplicedGirderSegment)
   OBJECT_ENTRY(CLSID_NUSplicedGirderSegment, CNUSplicedGirderSegment)
   OBJECT_ENTRY(CLSID_Material, CMaterial)
   OBJECT_ENTRY(CLSID_CastSlab, CCastSlab)
   OBJECT_ENTRY(CLSID_PrecastSlab, CPrecastSlab)
   OBJECT_ENTRY(CLSID_OverlaySlab, COverlaySlab)
   OBJECT_ENTRY(CLSID_AlignmentOffsetStrategy, CAlignmentOffsetStrategy)
   OBJECT_ENTRY(CLSID_FlangedGirderSection, CFlangedBeam)
   OBJECT_ENTRY(CLSID_FlangedGirderSection2, CFlangedBeam2)
   OBJECT_ENTRY(CLSID_BulbTeeSection,CBulbTeeSection)
   OBJECT_ENTRY(CLSID_NUGirderSection,CNUGirderSection)
   OBJECT_ENTRY(CLSID_UGirderSection,CUGirderSection)
   OBJECT_ENTRY(CLSID_UGirderSection2,CUGirderSection2)
   OBJECT_ENTRY(CLSID_MultiWebSection,CMultiWebSection)
   OBJECT_ENTRY(CLSID_MultiWebSection2,CMultiWebSection2)
   OBJECT_ENTRY(CLSID_VoidedSlabSection,CVoidedSlabSection)
   OBJECT_ENTRY(CLSID_VoidedSlabSection2,CVoidedSlabSection2)
   OBJECT_ENTRY(CLSID_DeckedSlabBeamSection,CDeckedSlabBeamSection)
   OBJECT_ENTRY(CLSID_BoxBeamSection,CBoxBeamSection)
   OBJECT_ENTRY(CLSID_FShapeBarrier,CFShapeBarrier)
   OBJECT_ENTRY(CLSID_SidewalkBarrier,CSidewalkBarrier)
   OBJECT_ENTRY(CLSID_GenericBarrier,CGenericBarrier)
   OBJECT_ENTRY(CLSID_ParabolicTendonSegment,CParabolicTendonSegment)
   OBJECT_ENTRY(CLSID_LinearTendonSegment,CLinearTendonSegment)
   OBJECT_ENTRY(CLSID_Tendon,CTendon)
   OBJECT_ENTRY(CLSID_OffsetTendon,COffsetTendon)
   OBJECT_ENTRY(CLSID_TendonCollection,CTendonCollection)
   OBJECT_ENTRY(CLSID_PrestressingStrand,CPrestressingStrand)
   OBJECT_ENTRY(CLSID_EdgePathStrategy,CEdgePathStrategy)
   OBJECT_ENTRY(CLSID_LinearCrossBeam,CLinearCrossBeam)
   OBJECT_ENTRY(CLSID_Column,CColumn)
   OBJECT_ENTRY(CLSID_ColumnLayout,CColumnLayout)
   OBJECT_ENTRY(CLSID_BearingLayout,CBearingLayout)
   OBJECT_ENTRY(CLSID_Pier,CPier)
   OBJECT_ENTRY(CLSID_SuperstructureMemberCollection,CSuperstructureMemberCollection)
   OBJECT_ENTRY_NON_CREATEABLE(CBridgePier)
   OBJECT_ENTRY_NON_CREATEABLE(CPierCollection)
   OBJECT_ENTRY_NON_CREATEABLE(CSuperstructureMember)
   OBJECT_ENTRY_NON_CREATEABLE(CSegmentItem)
   OBJECT_ENTRY_NON_CREATEABLE(CFilteredSegmentCollection)
   OBJECT_ENTRY(CLSID_Rebar,CRebar)
   OBJECT_ENTRY(CLSID_RebarLayout,CRebarLayout)
   OBJECT_ENTRY(CLSID_RebarFactory,CRebarFactory)
   OBJECT_ENTRY(CLSID_RebarRowPattern,CRebarRowPattern)
   OBJECT_ENTRY(CLSID_RebarRowFacePattern,CRebarRowFacePattern)
   OBJECT_ENTRY(CLSID_CrossBeamRebarPattern,CCrossBeamRebarPattern)
   OBJECT_ENTRY(CLSID_FixedLengthRebarLayoutItem,CFixedLengthRebarLayoutItem)
   OBJECT_ENTRY(CLSID_BridgeDeckRebarLayoutItem,CBridgeDeckRebarLayoutItem)
   OBJECT_ENTRY(CLSID_BridgeDeckRebarPattern,CBridgeDeckRebarPattern)
   OBJECT_ENTRY(CLSID_NegativeMomentBridgeDeckRebarLayoutItem,CNegativeMomentBridgeDeckRebarLayoutItem)
   OBJECT_ENTRY(CLSID_RebarSection,CRebarSection)
   OBJECT_ENTRY(CLSID_RebarSectionItem,CRebarSectionItem)
   OBJECT_ENTRY_NON_CREATEABLE(CCastingRegion)
   OBJECT_ENTRY(CLSID_CastingRegions,CCastingRegions)
END_OBJECT_MAP()


/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLGenericBridge);
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
   return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
   return _Module.UnregisterServer(TRUE);
}
