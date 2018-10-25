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
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// ILinearTendonSegment
STDMETHODIMP CLinearTendonSegment::putref_Start(IPoint3d* start)
{
   CHECK_IN(start);
   m_Start = start;
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_Start(IPoint3d** start)
{
   CHECK_RETOBJ(start);
   (*start) = m_Start;
   (*start)->AddRef();
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::putref_End(IPoint3d* end)
{
   CHECK_IN(end);
   m_End = end;
   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_End(IPoint3d** end)
{
   CHECK_RETOBJ(end);
   (*end) = m_End;
   (*end)->AddRef();
   return S_OK;
}

/////////////////////////////////////////////////////
// ITendonSegment
STDMETHODIMP CLinearTendonSegment::get_Position(Float64 x,IPoint3d** cg)
{
   CHECK_RETOBJ(cg);

   Float64 x1,y1,z1;
   Float64 x2,y2,z2;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   Float64 dx = x2-x1;
   Float64 dy = y2-y1;
   Float64 dz = z2-z1;

   Float64 y = dy*(x-x1)/dx + y1;
   Float64 z = dz*(x-x1)/dx + z1;

   CComPtr<IPoint3d> p;
   p.CoCreateInstance(CLSID_Point3d);
   p->Move(x,y,z);
   (*cg) = p;
   (*cg)->AddRef();

   return S_OK;
}

STDMETHODIMP CLinearTendonSegment::get_Slope(Float64 x,IVector3d** slope)
{
   CHECK_RETOBJ(slope);

   CComPtr<IVector3d> vector;
   vector.CoCreateInstance(CLSID_Vector3d);

   Float64 x1,y1,z1;
   Float64 x2,y2,z2;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);
   m_End->get_X(&x2);
   m_End->get_Y(&y2);
   m_End->get_Z(&z2);

   vector->put_X(x2-x1);
   vector->put_Y(y2-y1);
   vector->put_Z(z2-z1);
   vector->Normalize();
#if defined _DEBUG
   Float64 mag;
   vector->get_Magnitude(&mag);
   ATLASSERT(IsEqual(mag,1.0));
#endif
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
   Float64 x2,y2,z2;
   m_Start->get_X(&x1);
   m_Start->get_Y(&y1);
   m_Start->get_Z(&z1);
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
