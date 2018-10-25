///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// ParabolicTendonSegment.cpp : Implementation of CParabolicTendonSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "ParabolicTendonSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParabolicTendonSegment
HRESULT CParabolicTendonSegment::FinalConstruct()
{
   HRESULT hr;
   hr = m_Start.CoCreateInstance(CLSID_Point3d);
   if ( FAILED(hr) )
      return hr;

   hr = m_End.CoCreateInstance(CLSID_Point3d);
   if ( FAILED(hr) )
      return hr;

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
      return hr;

   m_Slope = 0;
   m_SlopeEnd = qcbLeft;

   return S_OK;
}

void CParabolicTendonSegment::FinalRelease()
{
}

STDMETHODIMP CParabolicTendonSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IParabolicTendonSegment,
      &IID_ITendonSegment,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// IParabolicTendonSegment
STDMETHODIMP CParabolicTendonSegment::put_Start(IPoint3d* start)
{
   CHECK_IN(start);
   Float64 x,y,z;
   start->Location(&x,&y,&z);
   m_Start->Move(x,y,z);
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Start(IPoint3d** start)
{
   CHECK_RETOBJ(start);
   return m_Start->Clone(start);
}

STDMETHODIMP CParabolicTendonSegment::put_End(IPoint3d* end)
{
   CHECK_IN(end);
   Float64 x,y,z;
   end->Location(&x,&y,&z);
   m_End->Move(x,y,z);
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_End(IPoint3d** end)
{
   CHECK_RETOBJ(end);
   return m_End->Clone(end);
}

STDMETHODIMP CParabolicTendonSegment::put_Slope(Float64 slope)
{
   m_Slope = slope;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Slope(Float64* slope)
{
   CHECK_RETVAL(slope);
   *slope = m_Slope;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::put_SlopeEnd(DirectionType end)
{
   m_SlopeEnd = end;
   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_SlopeEnd(DirectionType* end)
{
   CHECK_RETVAL(end);
   *end = m_SlopeEnd;
   return S_OK;
}

/////////////////////////////////////////////////////
// ITendonSegment
STDMETHODIMP CParabolicTendonSegment::get_Position(Float64 z,IPoint3d** cg)
{
   CHECK_RETOBJ(cg);

   Float64 x1,y1,z1;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);

   Float64 x2,y2,z2;
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   ATLASSERT( ::InRange(z1,z,z2) );

   Float64 dx = x2-x1;
   Float64 dy = y2-y1;
   Float64 dz = z2-z1;

   mathPolynomial2d parabolaX = GetParabolaX();
   mathPolynomial2d parabolaY = GetParabolaY();

   Float64 x = parabolaX.Evaluate(z);
   Float64 y = parabolaY.Evaluate(z);

   CComPtr<IPoint3d> p;
   p.CoCreateInstance(CLSID_Point3d);
   p->Move(x,y,z);
   (*cg) = p;
   (*cg)->AddRef();

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Slope(Float64 z,IVector3d** slope)
{
   CHECK_RETOBJ(slope);

   mathPolynomial2d parabolaX = GetParabolaX();
   mathPolynomial2d parabolaY = GetParabolaY();
   mathPolynomial2d slope_fn_x = parabolaX.GetDerivative();
   mathPolynomial2d slope_fn_y = parabolaY.GetDerivative();

   Float64 sx = slope_fn_x.Evaluate(z);
   Float64 sy = slope_fn_y.Evaluate(z);

   CComPtr<IVector3d> vector;
   vector.CoCreateInstance(CLSID_Vector3d);

   vector->put_X(sx);
   vector->put_Y(sy);
   vector->put_Z(1);

   (*slope) = vector;
   (*slope)->AddRef();

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::get_Length(Float64* length)
{
   ATLASSERT(false); // need to compute the distance along the arc?
   return m_GeomUtil->Distance(m_Start,m_End,length);
}

STDMETHODIMP CParabolicTendonSegment::ProjectedLength(Float64* dx,Float64* dy,Float64* dz)
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

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CParabolicTendonSegment::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("ParabolicTendonSegment"));

   ATLASSERT(false); // not implemented

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CParabolicTendonSegment::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("ParabolicTendonSegment"),1.0);

   ATLASSERT(false); // not implemented

   save->EndUnit();

   return S_OK;
}

mathPolynomial2d CParabolicTendonSegment::GetParabolaX()
{
   Float64 x1,y1,z1;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);

   Float64 x2,y2,z2;
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   Float64 dx = x2-x1;
   Float64 dy = y2-y1;
   Float64 dz = z2-z1;

   Float64 A, B, C;
   if ( m_SlopeEnd == qcbLeft )
   {
      // Slope is known at the left end
      A = (dx - dz*m_Slope)/(dz*dz);
      B = m_Slope - 2*A*z1;
      C = x1 - A*z1*z1 - B*z1;
   }
   else
   {
      A = -(dx - dz*m_Slope)/(dz*dz);
      B = m_Slope - 2*A*z2;
      C = x1 - A*z1*z1 - B*z1;
   }

   std::vector<Float64> coefficients;
   coefficients.push_back(A); // x = Az^2 + Bz + C
   coefficients.push_back(B);
   coefficients.push_back(C);

   return mathPolynomial2d(coefficients);
}

mathPolynomial2d CParabolicTendonSegment::GetParabolaY()
{
   Float64 x1,y1,z1;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);

   Float64 x2,y2,z2;
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   Float64 dx = x2-x1;
   Float64 dy = y2-y1;
   Float64 dz = z2-z1;

   Float64 A, B, C;
   if ( m_SlopeEnd == qcbLeft )
   {
      // Slope is known at the left end
      A = (dy - dz*m_Slope)/(dz*dz);
      B = m_Slope - 2*A*z1;
      C = y1 - A*z1*z1 - B*z1;
   }
   else
   {
      A = -(dy - dz*m_Slope)/(dz*dz);
      B = m_Slope - 2*A*z2;
      C = y1 - A*z1*z1 - B*z1;
   }

   std::vector<Float64> coefficients;
   coefficients.push_back(A); // y = Az^2 + Bz + C
   coefficients.push_back(B);
   coefficients.push_back(C);

   return mathPolynomial2d(coefficients);
}
