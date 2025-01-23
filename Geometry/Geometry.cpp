///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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


// Geometry.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f Geometryps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WBFLGeometry.h"

#include "WBFLGeometry_i.c"
#include "WBFLTools_i.c"

#include "Point2d.h"
#include "Size2d.h"
#include "Rect2d.h"
#include "Vector2d.h"
#include "Point2dCollection.h"
#include "LineSegment2d.h"
#include "Line2d.h"
#include "ShapeProperties.h"
#include "PolyShape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "PrecastBeam.h"
#include "PrecastBeam2.h"
#include "TrafficBarrier.h"
#include "Point3d.h"
#include "LineSegment3d.h"
#include "Size3d.h"
#include "Vector3d.h"
#include "Plane3d.h"
#include "Point3dCollection.h"
#include "GeomUtil.h"
#include "CoordinateXform3d.h"
#include "CoordinateXform2d.h"
#include "CircularSegment.h"
#include "PlateGirder.h"
#include "NUBeam.h"
#include "UBeam.h"
#include "BulbTee.h"
#include "BulbTee2.h"
#include "MultiWeb.h"
#include "MultiWeb2.h"
#include "UBeam2.h"
#include "CompositeShape.h"
#include "CompositeShapeItem.h"
#include "VoidedSlab.h"
#include "VoidedSlab2.h"
#include "BoxBeam.h"
#include "DeckedSlabBeam.h"
#include "GenericShape.h"
#include "BeamShapeFactory.h"
#include "NUDeckedIBeam.h"
#include "PCIDeckedIBeam.h"
#include "ElasticProperties.h"
#include "MassProperties.h"
#include "CompositeBeam.h"
#include "CompositeSectionItemEx.h"
#include "CompositeSectionEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module; 

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Point2d, CPoint2d)
OBJECT_ENTRY(CLSID_Size2d, CSize2d)
OBJECT_ENTRY(CLSID_Rect2d, CRect2d)
OBJECT_ENTRY(CLSID_Vector2d, CVector2d)
OBJECT_ENTRY(CLSID_Point2dCollection, CPoint2dCollection)
OBJECT_ENTRY(CLSID_LineSegment2d, CLineSegment2d)
OBJECT_ENTRY(CLSID_Line2d, CLine2d)
OBJECT_ENTRY(CLSID_ShapeProperties, CShapeProperties)
OBJECT_ENTRY(CLSID_PolyShape, CPolyShape)
OBJECT_ENTRY(CLSID_Circle, CCircle)
OBJECT_ENTRY(CLSID_Rect, CRectangle)
OBJECT_ENTRY(CLSID_Triangle, CTriangle)
OBJECT_ENTRY(CLSID_PrecastBeam, CPrecastBeam)
OBJECT_ENTRY(CLSID_PrecastBeam2, CPrecastBeam2)
OBJECT_ENTRY(CLSID_TrafficBarrier, CTrafficBarrier)
OBJECT_ENTRY(CLSID_Point3d, CPoint3d)
OBJECT_ENTRY(CLSID_LineSegment3d, CLineSegment3d)
OBJECT_ENTRY(CLSID_Size3d, CSize3d)
OBJECT_ENTRY(CLSID_Vector3d, CVector3d)
OBJECT_ENTRY(CLSID_Plane3d, CPlane3d)
OBJECT_ENTRY(CLSID_Point3dCollection, CPoint3dCollection)
OBJECT_ENTRY(CLSID_GeomUtil, CGeomUtil)
OBJECT_ENTRY(CLSID_CoordinateXform3d, CCoordinateXform3d)
OBJECT_ENTRY(CLSID_CoordinateXform2d, CCoordinateXform2d)
OBJECT_ENTRY(CLSID_CircularSegment, CCircularSegment)
OBJECT_ENTRY(CLSID_PlateGirder, CPlateGirder)
OBJECT_ENTRY(CLSID_UBeam, CUBeam)
OBJECT_ENTRY(CLSID_NUBeam, CNUBeam)
OBJECT_ENTRY(CLSID_BulbTee, CBulbTee)
OBJECT_ENTRY(CLSID_BulbTee2, CBulbTee2)
OBJECT_ENTRY(CLSID_MultiWeb,CMultiWeb)
OBJECT_ENTRY(CLSID_MultiWeb2,CMultiWeb2)
OBJECT_ENTRY(CLSID_UBeam2,CUBeam2)
OBJECT_ENTRY(CLSID_CompositeShape,CCompositeShape)
OBJECT_ENTRY(CLSID_CompositeShapeItem,CCompositeShapeItem)
OBJECT_ENTRY(CLSID_VoidedSlab,CVoidedSlab)
OBJECT_ENTRY(CLSID_VoidedSlab2,CVoidedSlab2)
OBJECT_ENTRY(CLSID_DeckedSlabBeam,CDeckedSlabBeam)
OBJECT_ENTRY(CLSID_BoxBeam,CBoxBeam)
OBJECT_ENTRY(CLSID_GenericShape, CGenericShape)
OBJECT_ENTRY(CLSID_BeamShapeFactory, CBeamShapeFactory)
OBJECT_ENTRY(CLSID_NUDeckedIBeam,CNUDeckedIBeam)
OBJECT_ENTRY(CLSID_PCIDeckedIBeam,CPCIDeckedIBeam)
OBJECT_ENTRY(CLSID_ElasticProperties, CElasticProperties)
OBJECT_ENTRY(CLSID_MassProperties, CMassProperties)
OBJECT_ENTRY(CLSID_CompositeBeam, CCompositeBeam)
OBJECT_ENTRY(CLSID_CompositeSectionItemEx, CCompositeSectionItemEx)
OBJECT_ENTRY(CLSID_CompositeSectionEx, CCompositeSectionEx)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WBFLGeometry);
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
