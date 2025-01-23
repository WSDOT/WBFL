///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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

// COGO.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f COGOps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>

#include "WBFLCOGO.h"
#include "WBFLCOGO_i.c"

#include "WBFLTools_i.c"
#include "WBFLGeometry_i.c"
#include "WBFLUnitServer_i.c"

#include "Angle.h"
#include "Direction.h"
#include "CogoModel.h"
#include "ProfilePoint.h"
#include "VerticalCurve.h"
#include "CompoundCurve.h"
#include "ProfileSegment.h"
#include "Profile.h"
#include "PathSegment.h"
#include "Path.h"
#include "Alignment.h"
#include "AngleDisplayUnitFormatter.h"
#include "DirectionDisplayUnitFormatter.h"
#include "Station.h"
#include "CogoEngine.h"
#include "CubicSpline.h"
#include "Widening.h"
#include "Superelevation.h"
#include "SurfaceTemplateSegment.h"
#include "SurfaceTemplate.h"
#include "Surface.h"
#include "SurfacePoint.h"
#include "SurfaceProfile.h"
#include "TransitionCurve.h"
#include "CircularCurve.h"

#include "PierLine.h"
#include "GirderLine.h"

#include "SinglePierLineFactory.h"

#include "AlignmentOffsetLayoutLineFactory.h"
#include "SimpleLayoutLineFactory.h"
#include "UniformSpacingLayoutLineFactory.h"

#include "SingleGirderLineFactory.h"
#include "SimpleGirderLineFactory.h"

#include "EqualSpacingDiaphragmLineFactory.h"
#include "SingleDiaphragmLineFactory.h"
#include "ThroughPointDiaphragmLineFactory.h"

#include "SimpleDeckBoundaryFactory.h"

#include "BridgeGeometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Angle, CAngle)
OBJECT_ENTRY(CLSID_Direction, CDirection)
OBJECT_ENTRY(CLSID_CogoModel, CCogoModel)
OBJECT_ENTRY(CLSID_CogoEngine, CCogoEngine)
OBJECT_ENTRY(CLSID_PathSegment, CPathSegment)
OBJECT_ENTRY(CLSID_ProfilePoint, CProfilePoint)
OBJECT_ENTRY(CLSID_VerticalCurve, CVerticalCurve)
OBJECT_ENTRY(CLSID_CompoundCurve, CCompoundCurve)
OBJECT_ENTRY(CLSID_ProfileSegment, CProfileSegment)
OBJECT_ENTRY(CLSID_Profile, CProfile)
OBJECT_ENTRY(CLSID_Path, CPath)
OBJECT_ENTRY(CLSID_Alignment, CAlignment)
OBJECT_ENTRY(CLSID_AngleDisplayUnitFormatter, CAngleDisplayUnitFormatter)
OBJECT_ENTRY(CLSID_DirectionDisplayUnitFormatter, CDirectionDisplayUnitFormatter)
OBJECT_ENTRY(CLSID_Station, CStation)
OBJECT_ENTRY(CLSID_CogoEngine, CCogoEngine)
OBJECT_ENTRY(CLSID_CubicSpline, CCubicSpline)
OBJECT_ENTRY(CLSID_Widening, CWidening)
OBJECT_ENTRY(CLSID_Superelevation,CSuperelevation)
OBJECT_ENTRY(CLSID_SurfaceTemplateSegment, CSurfaceTemplateSegment)
OBJECT_ENTRY(CLSID_SurfaceTemplate, CSurfaceTemplate)
OBJECT_ENTRY(CLSID_Surface, CSurface)
OBJECT_ENTRY(CLSID_SurfacePoint, CSurfacePoint)
OBJECT_ENTRY(CLSID_SurfaceProfile, CSurfaceProfile)
OBJECT_ENTRY(CLSID_TransitionCurve, CTransitionCurve)
OBJECT_ENTRY(CLSID_CircularCurve, CCircularCurve)

OBJECT_ENTRY_NON_CREATEABLE(CPierLine)
OBJECT_ENTRY_NON_CREATEABLE(CGirderLine)

OBJECT_ENTRY(CLSID_SinglePierLineFactory,CSinglePierLineFactory)

OBJECT_ENTRY(CLSID_AlignmentOffsetLayoutLineFactory,CAlignmentOffsetLayoutLineFactory)
OBJECT_ENTRY(CLSID_SimpleLayoutLineFactory,CSimpleLayoutLineFactory)
OBJECT_ENTRY(CLSID_UniformSpacingLayoutLineFactory,CUniformSpacingLayoutLineFactory)

OBJECT_ENTRY(CLSID_SingleGirderLineFactory,CSingleGirderLineFactory)
OBJECT_ENTRY(CLSID_SimpleGirderLineFactory,CSimpleGirderLineFactory)

OBJECT_ENTRY(CLSID_EqualSpacingDiaphragmLineFactory,CEqualSpacingDiaphragmLineFactory)
OBJECT_ENTRY(CLSID_SingleDiaphragmLineFactory,CSingleDiaphragmLineFactory)
OBJECT_ENTRY(CLSID_ThroughPointDiaphragmLineFactory,CThroughPointDiaphragmLineFactory)

OBJECT_ENTRY(CLSID_SimpleDeckBoundaryFactory,CSimpleDeckBoundaryFactory)

OBJECT_ENTRY(CLSID_BridgeGeometry,CBridgeGeometry)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLCogo);
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
