///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include "Point3d.h"
#include "Helper.h"
#include <MathEx.h>
#include <Float.h>

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
		&IID_IPlane3d,
      &IID_IStructuredStorage2
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CPlane3d::ThroughPoints(IPoint3d *p1, IPoint3d *p2, IPoint3d *p3)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_IN(p3);

   m_bIsXYPlane = VARIANT_FALSE;

   const int x = 0;
   const int y = 1;
   const int z = 2;
   Float64 v1[3];
   Float64 v2[3];

   Float64 x1,x2,x3;
   Float64 y1,y2,y3;
   Float64 z1,z2,z3;
   p1->Location(&x1,&y1,&z1);
   p2->Location(&x2,&y2,&z2);
   p3->Location(&x3,&y3,&z3);

   v1[x] = x2 - x1;
   v1[y] = y2 - y1;
   v1[z] = z2 - z1;

   v2[x] = x3 - x1;
   v2[y] = y3 - y1;
   v2[z] = z3 - z1;

   m_A = v1[y]*v2[z] - v1[z]*v2[y];
   m_B = v1[z]*v2[x] - v1[x]*v2[z];
   m_C = v1[x]*v2[y] - v1[y]*v2[x];

   m_D = -1*(m_A*x1 + m_B*y1 + m_C*z1);

#if defined _DEBUG
   Float64 d2 = -1 * (m_A*x2 + m_B*y2 + m_C*z2);
   Float64 d3 = -1 * (m_A*x3 + m_B*y3 + m_C*z3);
   ATLASSERT(IsEqual(m_D, d2, 0.001));
   ATLASSERT(IsEqual(m_D, d3, 0.001));
#endif

   return S_OK;
}

STDMETHODIMP CPlane3d::ThroughLineEx(ILine2d *pLine, IPoint3d *pPnt)
{
   CHECK_IN(pLine);
   CHECK_IN(pPnt);

   // If point is on the line, the plane is undefined
   Float64 z;
   pPnt->get_Z(&z);
   if ( IsZero(z) ) // Point is in XY plane
   {
      CComPtr<IGeomUtil2d> util;
      CreateGeomUtil( &util );

      CComPtr<IPoint2d> pnt2d;
      Float64 x,y;
      pPnt->get_X(&x);
      pPnt->get_Y(&y);
      CreatePoint(x,y,nullptr,&pnt2d);
      VARIANT_BOOL bIsPointOnLine;
      util->DoesLineContainPoint(pLine,pnt2d,1e-6,&bIsPointOnLine);
      if ( bIsPointOnLine == VARIANT_TRUE )
         return Error(IDS_E_POINTONLINE,IID_IPlane3d,GEOMETRY_E_POINTONLINE);
   }

   // get two points on the line
   CComPtr<IPoint2d> p1;
   CComPtr<IVector2d> pv;
   pLine->GetExplicit(&p1,&pv);

   Float64 x,y;
   p1->get_X(&x);
   p1->get_Y(&y);
   CComPtr<IPoint3d> p1_3d;
   CreatePoint(x,y,0.00,nullptr,&p1_3d);

   Float64 dx,dy;
   pv->get_X(&dx);
   pv->get_Y(&dy);

   CComPtr<IPoint3d> p2;
   CreatePoint( x, y, 0.00, nullptr, &p2);
   p2->Offset(dx,dy,0.00);


   return ThroughPoints( p1_3d, p2, pPnt );
}

STDMETHODIMP CPlane3d::ThroughAltitude(Float64 altitude)
{
   m_bIsXYPlane = VARIANT_TRUE;
   m_A = altitude;
   return S_OK;
}

STDMETHODIMP CPlane3d::GetX(Float64 y, Float64 z, Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   if ( m_bIsXYPlane == VARIANT_TRUE && IsEqual(m_A,z) || IsZero(m_A) )
      return Error(IDS_E_INFINITESOLUTIONS,IID_IPlane3d,GEOMETRY_E_INFINITESOLUTIONS);
   else if ( m_bIsXYPlane == VARIANT_TRUE )
      return Error(IDS_E_NOSOLUTIONS,IID_IPlane3d,GEOMETRY_E_NOSOLUTIONS);

   *pVal = (m_B*y + m_C*z + m_D)/(-m_A);
   return S_OK;
}

STDMETHODIMP CPlane3d::GetY(Float64 x, Float64 z, Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   if ( m_bIsXYPlane == VARIANT_TRUE && IsEqual(m_A,z) || IsZero(m_B) )
      return Error(IDS_E_INFINITESOLUTIONS,IID_IPlane3d,GEOMETRY_E_INFINITESOLUTIONS);
   else if ( m_bIsXYPlane == VARIANT_TRUE )
      return Error(IDS_E_NOSOLUTIONS,IID_IPlane3d,GEOMETRY_E_NOSOLUTIONS);

   *pVal = (m_A*x + m_C*z + m_D)/(-m_B);
   return S_OK;
}

STDMETHODIMP CPlane3d::GetZ(Float64 x, Float64 y, Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 z;

   if ( m_bIsXYPlane == VARIANT_TRUE )
   {
      z = m_A;
   }
   else if ( IsZero(m_C) )
   {
      *pVal = 0;
      return Error(IDS_E_NOSOLUTIONS,IID_IPlane3d,GEOMETRY_E_NOSOLUTIONS);
   }
   else
   {
      z = (m_A*x + m_B*y + m_D)/(-m_C);
   }

   *pVal = z;
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

   Float64 Dx = Xb - Xa;
   Float64 Dy = Yb - Ya;
   Float64 Dz = Zb - Za;

   Float64 Q = -m_D - m_A*Xa - m_B*Ya - m_C*Za;
   Float64 R = m_A*Dx + m_B*Dy + m_C*Dz;

   if ( IsZero(R) ) // Line is parallel to plane
      return Error(IDS_E_NOSOLUTIONS,IID_IPlane3d,GEOMETRY_E_NOSOLUTIONS);

   if ( IsZero(Q) && IsZero(R) ) // Line is on plane
      return Error(IDS_E_NOSOLUTIONS,IID_IPlane3d,GEOMETRY_E_NOSOLUTIONS);

   Float64 t = Q/R;

   CComObject<CPoint3d>* pPoint;
   HRESULT hr = CComObject<CPoint3d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   Float64 x = Xa + t*Dx;
   Float64 y = Ya + t*Dy;
   Float64 z = Za + t*Dz;

   *ppPoint = pPoint;
   (*ppPoint)->AddRef();
   (*ppPoint)->Move(x,y,z);

   if ( t < 0 || 1 < t )
      return S_FALSE; // an intersection was found, but it is not between the ends of the line segment

   return S_OK;
}

STDMETHODIMP CPlane3d::SortestDistance(IPoint3d* point,Float64* pDistance)
{
   // REFERENCE: http://en.wikipedia.org/wiki/Plane_(geometry)#Distance_from_a_point_to_a_plane
   CHECK_IN(point);
   CHECK_RETVAL(pDistance);

   Float64 K = m_A*m_A + m_B*m_B + m_C*m_C;
   if ( IsZero(K) )
      return E_FAIL;

   Float64 x,y,z;
   point->Location(&x,&y,&z);

   *pDistance = (m_A*x + m_B*y + m_C*z + m_D)/sqrt(K);

   // distance > 0... point is above plane (on same side as normal)
   // distance < 0... point is below plane

   return S_OK;
}

STDMETHODIMP CPlane3d::PointOnPlaneNearestOrigin(IPoint3d** ppPoint)
{
   // REFERENCE: http://en.wikipedia.org/wiki/Point_on_plane_closest_to_origin
   CHECK_RETOBJ(ppPoint);

   Float64 K = m_A*m_A + m_B*m_B + m_C*m_C;
   if ( IsZero(K) )
      return E_FAIL;

   Float64 x = m_A*m_D/K;
   Float64 y = m_B*m_D/K;
   Float64 z = m_C*m_D/K;


   CComObject<CPoint3d>* pPoint;
   HRESULT hr = CComObject<CPoint3d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   *ppPoint = pPoint;
   (*ppPoint)->AddRef();
   (*ppPoint)->Move(x,y,z);

   return S_OK;
}

STDMETHODIMP CPlane3d::Clone(IPlane3d** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CPlane3d>* pClone;
   CComObject<CPlane3d>::CreateInstance(&pClone);

   pClone->Init(m_A,m_B,m_C,m_D,m_bIsXYPlane);

   (*clone) = pClone;
   (*clone)->AddRef();
   return S_OK;
}

STDMETHODIMP CPlane3d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CPlane3d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CPlane3d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Plane3d"),1.0);
   pSave->put_Property(CComBSTR("A"),CComVariant(m_A));
   pSave->put_Property(CComBSTR("B"),CComVariant(m_B));
   pSave->put_Property(CComBSTR("C"),CComVariant(m_C));
   pSave->put_Property(CComBSTR("D"),CComVariant(m_D));
   pSave->put_Property(CComBSTR("XYPlane"),CComVariant(m_bIsXYPlane));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPlane3d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Plane3d"));
   
   pLoad->get_Property(CComBSTR("A"),&var);
   m_A = var.dblVal;
   
   pLoad->get_Property(CComBSTR("B"),&var);
   m_B = var.dblVal;
   
   pLoad->get_Property(CComBSTR("C"),&var);
   m_C = var.dblVal;
   
   pLoad->get_Property(CComBSTR("D"),&var);
   m_D = var.dblVal;

   pLoad->get_Property(CComBSTR("XYPlane"),&var);
   m_bIsXYPlane = var.boolVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
