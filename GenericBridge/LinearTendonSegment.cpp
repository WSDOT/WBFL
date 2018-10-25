///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// LinearTendonSegment.cpp : Implementation of CLinearTendonSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "LinearTendonSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearTendonSegment
HRESULT CLinearTendonSegment::FinalConstruct()
{
   m_pPrevSegment = nullptr;
   m_pNextSegment = nullptr;

   HRESULT hr;
   hr = m_Start.CoCreateInstance(CLSID_Point3d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_End.CoCreateInstance(CLSID_Point3d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_pTendon = nullptr;

   return S_OK;
}

void CLinearTendonSegment::FinalRelease()
{
}

STDMETHODIMP CLinearTendonSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILinearTendonSegment,
      &IID_ITendonSegment,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// ILinearTendonSegment
STDMETHODIMP CLinearTendonSegment::put_Start(IPoint3d* start)
{
   CHECK_IN(start);
   Float64 x,y,z;
   start->Location(&x,&y,&z);
   m_Start->Move(x,y,z);
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_Start(IPoint3d** start)
{
   CHECK_RETOBJ(start);
   return m_Start->Clone(start);
}

STDMETHODIMP CLinearTendonSegment::put_End(IPoint3d* end)
{
   CHECK_IN(end);
   Float64 x,y,z;
   end->Location(&x,&y,&z);
   m_End->Move(x,y,z);
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_End(IPoint3d** end)
{
   CHECK_RETOBJ(end);
   return m_End->Clone(end);
}

STDMETHODIMP CLinearTendonSegment::putref_PrevTendonSegment(ITendonSegment* pTendonSegment)
{
   CHECK_IN(pTendonSegment);
   m_pPrevSegment = pTendonSegment;
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_PrevTendonSegment(ITendonSegment** ppTendonSegment)
{
   CHECK_RETOBJ(ppTendonSegment);
   (*ppTendonSegment) = m_pPrevSegment;
   if ( *ppTendonSegment )
   {
      (*ppTendonSegment)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::putref_NextTendonSegment(ITendonSegment* pTendonSegment)
{
   CHECK_IN(pTendonSegment);
   m_pNextSegment = pTendonSegment;
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_NextTendonSegment(ITendonSegment** ppTendonSegment)
{
   CHECK_RETVAL(ppTendonSegment);
   CHECK_RETOBJ(ppTendonSegment);
   (*ppTendonSegment) = m_pNextSegment;
   if ( *ppTendonSegment )
   {
      (*ppTendonSegment)->AddRef();
   }
   return S_OK;
}

/////////////////////////////////////////////////////
// ITendonSegment
STDMETHODIMP CLinearTendonSegment::get_Position(TendonMeasure measure,Float64 z,IPoint3d** cg)
{
#pragma Reminder("UPDATE: need to make adjustment for strand being offset in duct if measure is tmTendon")
   CHECK_RETOBJ(cg);

   Float64 x1,y1,z1;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);

   Float64 x2,y2,z2;
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   ATLASSERT(::IsLE(z1,z) && ::IsLE(z,z2));

   z = IsEqual(z,z1) ? z1 : z;
   z = IsEqual(z,z2) ? z2 : z;

   Float64 dx = x2-x1;
   Float64 dy = y2-y1;
   Float64 dz = z2-z1;

   Float64 x = dx*(z-z1)/dz + x1;
   Float64 y = dy*(z-z1)/dz + y1;

   x = IsZero(x) ? 0 : x;
   z = IsZero(z) ? 0 : z;

   CComPtr<IPoint3d> p;
   p.CoCreateInstance(CLSID_Point3d);
   p->Move(x,y,z);
   (*cg) = p;
   (*cg)->AddRef();

   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_Slope(Float64 z,IVector3d** slope)
{
   CHECK_RETOBJ(slope);

   CComPtr<IVector3d> vector;
   vector.CoCreateInstance(CLSID_Vector3d);

   Float64 x1,y1,z1;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);

   Float64 x2,y2,z2;
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   Float64 dx = (x2-x1);
   Float64 dy = (y2-y1);
   Float64 dz = (z2-z1);

   ATLASSERT(!IsZero(dz));

   Float64 sx = dx/dz;
   Float64 sy = dy/dz;

   if ( m_pTendon )
   {
      CComPtr<ISuperstructureMember> ssmbr;
      m_pTendon->get_SuperstructureMember(&ssmbr);
      CComPtr<IAngle> planAngle;
      ssmbr->GetPlanAngle(z,&planAngle);
      Float64 value;
      planAngle->get_Value(&value);

      Float64 a = atan(sx);
      sx = -tan(a+value);
   }

   vector->put_X(sx);
   vector->put_Y(sy);
   vector->put_Z(1.0);

   (*slope) = vector;
   (*slope)->AddRef();

   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_Length(Float64* length)
{
   return m_GeomUtil->Distance(m_Start,m_End,length);
}

STDMETHODIMP CLinearTendonSegment::ProjectedLength(Float64* dx,Float64* dy,Float64* dz)
{
   CHECK_RETVAL(dx);
   CHECK_RETVAL(dy);
   CHECK_RETVAL(dz);

   Float64 x1,y1,z1;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);

   Float64 x2,y2,z2;
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   *dx = x2 - x1;
   *dy = y2 - y1;
   *dz = z2 - z1;

   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_Centerline(TendonMeasure measure,IPoint3dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   CComPtr<IPoint3dCollection> points;
   points.CoCreateInstance(CLSID_Point3dCollection);

#pragma Reminder("UPDATE: need to make adjustment for strand being offset in duct if measure is tmTendon")

   // the collection as add by reference symantics. we don't want anyone messing
   // with our end points so clone them.
   CComPtr<IPoint3d> start;
   m_Start->Clone(&start);

   CComPtr<IPoint3d> end;
   m_End->Clone(&end);

   points->Add(start);
   points->Add(end);
   return points.CopyTo(ppPoints);
}

STDMETHODIMP CLinearTendonSegment::putref_Tendon(ITendon* pTendon)
{
   m_pTendon = pTendon;
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_Tendon(ITendon** ppTendon)
{
   (*ppTendon) = m_pTendon;
   if ( (*ppTendon) )
   {
      (*ppTendon)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_MinimumRadiusOfCurvature(Float64* pMinRadiusOfCurvature)
{
   CHECK_RETVAL(pMinRadiusOfCurvature);

   // http://www.intmath.com/applications-differentiation/8-radius-curvature.php
   // Using Example 2, Method 2 solution

   // Curvature of a straight line is zero so the radius of curvature is infinite. Use
   // the max value.
   Float64 minRadius = DBL_MAX; 

   // If this tendon segment is attached to other linear tendon segments, approximate
   // the radius of curvature using the basic concept of differentiation.
   // dy/dx = (Delta Y)/(Delta X) = m
   // d(dy/dx)/dx = dm/dx
   // r = [(1+m^2)^3/2]/(dm/dx)
   CComPtr<ILinearTendonSegment> prevSegment;
   if (m_pPrevSegment )
   {
      m_pPrevSegment->QueryInterface(&prevSegment);
   }

   if ( prevSegment )
   {
      CComPtr<IPoint3d> start, end;
      prevSegment->get_Start(&start);
      prevSegment->get_End(&end);

      Float64 x1,y1,z1;
      start->Location(&x1,&y1,&z1);

      Float64 x2,y2,z2;
      end->Location(&x2,&y2,&z2);

#if defined _DEBUG
      Float64 X2, Y2, Z2;
      m_Start->Location(&X2,&Y2,&Z2);
      ATLASSERT(IsEqual(x2,X2));
      ATLASSERT(IsEqual(y2,Y2));
      ATLASSERT(IsEqual(z2,Z2));
#endif

      Float64 x3,y3,z3;
      m_End->Location(&x3,&y3,&z3);

      Float64 m1 = (y2-y1)/(z2-z1);
      Float64 m2 = (y3-y2)/(z3-z2);
      Float64 m = (m1 + m2)/2;
      Float64 dm = fabs((m2 - m1)/(z2-z1));

      Float64 r = IsZero(dm) ? DBL_MAX : pow(1+m*m,1.5)/dm;
      minRadius = Min(minRadius,r);
   }

   CComPtr<ILinearTendonSegment> nextSegment;
   if ( m_pNextSegment )
   {
      m_pNextSegment->QueryInterface(&nextSegment);
   }

   if ( nextSegment )
   {
      Float64 x1,y1,z1;
      m_Start->Location(&x1,&y1,&z1);

      Float64 x2,y2,z2;
      m_End->Location(&x2,&y2,&z2);

      CComPtr<IPoint3d> start, end;
      nextSegment->get_Start(&start);
      nextSegment->get_End(&end);
#if defined _DEBUG
      Float64 X2, Y2, Z2;
      start->Location(&X2,&Y2,&Z2);
      ATLASSERT(IsEqual(x2,X2));
      ATLASSERT(IsEqual(y2,Y2));
      ATLASSERT(IsEqual(z2,Z2));
#endif

      Float64 x3,y3,z3;
      end->Location(&x3,&y3,&z3);

      Float64 m1 = (y2-y1)/(z2-z1);
      Float64 m2 = (y3-y2)/(z3-z2);
      Float64 m = (m1 + m2)/2;
      Float64 dm = fabs((m2 - m1)/(z2-z1));

      Float64 r = pow(1+m*m,1.5)/dm;
      minRadius = Min(minRadius,r);
   }

   *pMinRadiusOfCurvature = minRadius;

   return S_OK;
}
/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CLinearTendonSegment::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("LinearTendonSegment"));

   ATLASSERT(false); // not implemented

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("LinearTendonSegment"),1.0);

   ATLASSERT(false); // not implemented

   save->EndUnit();

   return S_OK;
}
