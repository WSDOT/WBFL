///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// CoordinateXform2d.cpp : Implementation of CCoordinateXform2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CoordinateXform2d.h"
#include "Helper.h"
#include "Point2d.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoordinateXform2d

HRESULT CCoordinateXform2d::FinalConstruct()
{
   CComObject<CPoint2d>* origin;
   HRESULT hr = CComObject<CPoint2d>::CreateInstance( &origin );
   if ( FAILED(hr) ) return hr;

//   origin->put_X(0.0);
//   origin->put_Y(0.0);

   origin->QueryInterface( &m_Origin );

   m_Angle = 0.0;

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICoordinateXform2d,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCoordinateXform2d::get_NewOrigin(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   m_Origin->QueryInterface( pVal );

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::putref_NewOrigin(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   m_Origin = newVal;

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::get_RotationAngle(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Angle;

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::put_RotationAngle(Float64 newVal)
{
   m_Angle = newVal;
   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::Xform(IPoint2d** point,XformType type)
{
   CHECK_INOUT(point);

   HRESULT hr = S_OK;
   if ( type == xfrmOldToNew )
      hr = OldToNew( *point );
   else
      hr = NewToOld( *point );

   return hr;
}

STDMETHODIMP CCoordinateXform2d::XformEx(IPoint2d* point, XformType type, IPoint2d** result)
{
   CHECK_IN(point);
   CHECK_RETOBJ(result);
   CreatePoint(point,NULL,result);
   return Xform(result,type);
}

STDMETHODIMP CCoordinateXform2d::OldToNew(IPoint2d* point)
{
   Float64 x,y;
   GetCoordinates(point,&x,&y);

   Float64 xo,yo;
   GetCoordinates(m_Origin,&xo,&yo);

   Float64 x1,y1;

   x1 =  (x-xo)*cos(m_Angle) + (y-yo)*sin(m_Angle);
   y1 = -(x-xo)*sin(m_Angle) + (y-yo)*cos(m_Angle);

   point->Move(x1,y1);

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::NewToOld(IPoint2d* point)
{
   Float64 x,y;
   GetCoordinates(point,&x,&y);

   Float64 xo,yo;
   GetCoordinates(m_Origin,&xo,&yo);

   Float64 x1,y1;

   x1 = x*cos(m_Angle) - y*sin(m_Angle) + xo;
   y1 = x*sin(m_Angle) + y*cos(m_Angle) + yo;

   point->put_X(x1);
   point->put_Y(y1);

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CCoordinateXform2d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CCoordinateXform2d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CoordinateXform2d"),1.0);

   // Save the offset constant
   pSave->put_Property(CComBSTR("Angle"),CComVariant(m_Angle));
   pSave->put_Property(CComBSTR("Origin"),CComVariant(m_Origin));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CoordinateXform2d"));
   
   pLoad->get_Property(CComBSTR("Angle"),&var);
   m_Angle = var.dblVal;

   pLoad->get_Property(CComBSTR("Origin"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_Origin,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
