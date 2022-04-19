///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Plane3d.cpp : Implementation of CPlane3d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Plane3d.h"
#include "Helper.h"
#include <MathEx.h>

#include <GeomModel/Primitives3d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/LineSegment3d.h>
#include <GeomModel/Vector2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlane3d
STDMETHODIMP CPlane3d::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] =
   {
      &IID_IPlane3d
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i], riid))
         return S_OK;
   }
   return S_FALSE;
}


STDMETHODIMP CPlane3d::ThroughPoints(IPoint3d* p1, IPoint3d* p2, IPoint3d* p3)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_IN(p3);

   try
   {
      m_Plane.ThroughPoints(GetPoint(p1), GetPoint(p2), GetPoint(p3));
   }
   catch(...)
   {
      return Error(IDS_E_NOSOLUTIONS, IID_IPlane3d, GEOMETRY_E_NOSOLUTIONS);
   }

   return S_OK;
}

STDMETHODIMP CPlane3d::ThroughLineEx(ILine2d *pLine, IPoint3d *pPnt)
{
   CHECK_IN(pLine);
   CHECK_IN(pPnt);

   Float64 c;
   CComPtr<IVector2d> n;
   pLine->GetImplicit(&c, &n);

   Float64 nx, ny;
   n->get_X(&nx); n->get_Y(&ny);

   Float64 x, y, z;
   pPnt->Location(&x, &y, &z);

   try
   {
      m_Plane.ThroughLine(WBFL::Geometry::Line2d(c, WBFL::Geometry::Vector2d(WBFL::Geometry::Size2d(nx, ny))), WBFL::Geometry::Point3d(x, y, z));
   }
   catch (...)
   {
      return Error(IDS_E_NOSOLUTIONS, IID_IPlane3d, GEOMETRY_E_COLINEAR);
   }
   
   return S_OK;
}

STDMETHODIMP CPlane3d::ThroughAltitude(Float64 altitude)
{
   m_Plane.ThroughAltitude(altitude);
   return S_OK;
}

STDMETHODIMP CPlane3d::GetX(Float64 y, Float64 z, Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   try
   {
      *pVal = m_Plane.GetX(y, z);
   }
   catch (...)
   {
      return Error(IDS_E_NOSOLUTIONS, IID_IPlane3d, GEOMETRY_E_NOSOLUTIONS);
   }
   return S_OK;
}

STDMETHODIMP CPlane3d::GetY(Float64 x, Float64 z, Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   try
   {
      *pVal = m_Plane.GetY(x, z);
   }
   catch (...)
   {
      return Error(IDS_E_NOSOLUTIONS, IID_IPlane3d, GEOMETRY_E_NOSOLUTIONS);
   }
   return S_OK;
}

STDMETHODIMP CPlane3d::GetZ(Float64 x, Float64 y, Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   try
   {
      *pVal = m_Plane.GetZ(x, y);
   }
   catch (...)
   {
      return Error(IDS_E_NOSOLUTIONS, IID_IPlane3d, GEOMETRY_E_NOSOLUTIONS);
   }

	return S_OK;
}

STDMETHODIMP CPlane3d::LineSegmentIntersect(ILineSegment3d* pLineSegment,IPoint3d** ppPoint)
{
   // Reference: http://en.wikipedia.org/wiki/Line-plane_intersection
   CHECK_IN(pLineSegment);
   CHECK_RETVAL(ppPoint);

   CComPtr<IPoint3d> start, end;
   pLineSegment->get_StartPoint(&start);
   pLineSegment->get_EndPoint(&end);

   Float64 Xa,Ya,Za;
   start->Location(&Xa,&Ya,&Za);

   Float64 Xb,Yb,Zb;
   end->Location(&Xb,&Yb,&Zb);

   WBFL::Geometry::Point3d point;
   try
   {
      WBFL::Geometry::LineSegment3d ls(Xa, Ya, Za, Xb, Yb, Zb);
      point = m_Plane.LineSegmentIntersect(ls);
   }
   catch (...)
   {
      return Error(IDS_E_NOSOLUTIONS, IID_IPlane3d, GEOMETRY_E_NOSOLUTIONS);
   }

   return CreatePoint(point, ppPoint);
}

STDMETHODIMP CPlane3d::SortestDistance(IPoint3d* point,Float64* pDistance)
{
   // REFERENCE: http://en.wikipedia.org/wiki/Plane_(geometry)#Distance_from_a_point_to_a_plane
   CHECK_IN(point);
   CHECK_RETVAL(pDistance);

   Float64 x,y,z;
   point->Location(&x,&y,&z);
   try
   {
      *pDistance = m_Plane.ShortestDistance(WBFL::Geometry::Point3d(x, y, z));
   }
   catch (...)
   {
      return E_FAIL;
   }
   return S_OK;
}

STDMETHODIMP CPlane3d::PointOnPlaneNearestOrigin(IPoint3d* pPoint,IPoint3d** ppPoint)
{
   // REFERENCE: http://en.wikipedia.org/wiki/Point_on_plane_closest_to_origin
   CHECK_IN(pPoint);
   CHECK_RETOBJ(ppPoint);

   Float64 x, y, z;
   pPoint->Location(&x, &y, &z);

   return CreatePoint(m_Plane.PointOnPlaneNearest(WBFL::Geometry::Point3d(x, y, z)), ppPoint);
}

STDMETHODIMP CPlane3d::Clone(IPlane3d** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CPlane3d>* pClone;
   CComObject<CPlane3d>::CreateInstance(&pClone);

   pClone->m_Plane = m_Plane;

   (*clone) = pClone;
   (*clone)->AddRef();
   return S_OK;
}
