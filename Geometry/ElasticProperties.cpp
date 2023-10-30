///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ElasticProperties.cpp : Implementation of CElasticProperties
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "ElasticProperties.h"
#include "Helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElasticProperties
HRESULT CElasticProperties::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CElasticProperties::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IElasticProperties
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CElasticProperties::get_EA(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEA();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_EA(Float64 newVal)
{
   m_Props.SetEA(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_Centroid(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Props.GetCentroid(), pVal);
}

STDMETHODIMP CElasticProperties::put_Centroid(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Props.SetCentroid(GetPoint(newVal));
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_EI11(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEI11();
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_EI22(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEI22();
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_EI12Max(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEI12Max();
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_EI12Min(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEI12Min();
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_EIxx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEIxx();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_EIxx(Float64 newVal)
{
   m_Props.SetEIxx(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_EIyy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEIyy();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_EIyy(Float64 newVal)
{
   m_Props.SetEIyy(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_EIxy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetEIxy();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_EIxy(Float64 newVal)
{
   m_Props.SetEIxy(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_Xleft(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetXleft();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_Xleft(Float64 newVal)
{
   if (newVal < 0) return E_INVALIDARG;
   m_Props.SetXleft(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_Xright(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetXright();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_Xright(Float64 newVal)
{
   if (newVal < 0) return E_INVALIDARG;
   m_Props.SetXright(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_Ytop(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetYtop();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_Ytop(Float64 newVal)
{
   if (newVal < 0) return E_INVALIDARG;
   m_Props.SetYtop(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_Ybottom(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetYbottom();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_Ybottom(Float64 newVal)
{
   if (newVal < 0) return E_INVALIDARG;
   m_Props.SetYbottom(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_Origin(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Props.GetOrigin(), pVal);
}

STDMETHODIMP CElasticProperties::put_Origin(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Props.SetOrigin(GetPoint(newVal));
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_Orientation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetOrientation();
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_Orientation(Float64 newVal)
{
   m_Props.SetOrientation(newVal);
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_CoordinateSystem(CoordinateSystemType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = (CoordinateSystemType)(m_Props.GetCoordinateSystem());
   return S_OK;
}

STDMETHODIMP CElasticProperties::put_CoordinateSystem(CoordinateSystemType newVal)
{
   m_Props.SetCoordinateSystem(WBFL::Geometry::ElasticProperties::CoordinateSystemType(newVal));
   return S_OK;
}

STDMETHODIMP CElasticProperties::get_PrincipleDirection(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Props.GetPrincipalDirection();
   return S_OK;
}

STDMETHODIMP CElasticProperties::AddProperties(IElasticProperties* props)
{
   CHECK_IN(props);

   CElasticProperties* pProps = dynamic_cast<CElasticProperties*>(props);
   m_Props += pProps->m_Props;
   return S_OK;
}

STDMETHODIMP CElasticProperties::TransformProperties(Float64 E,IShapeProperties** props)
{
   CHECK_RETOBJ(props);

   CComPtr<IShapeProperties> shapeProps;
   shapeProps.CoCreateInstance(CLSID_ShapeProperties);

   *props = shapeProps;
   (*props)->AddRef();

   if ( E <= 0 )
      return E_INVALIDARG;

   WBFL::Geometry::ShapeProperties shape_props = m_Props.TransformProperties(E);
   shapeProps->put_Area(shape_props.GetArea());

   CComPtr<IPoint2d> cg;
   CreatePoint(shape_props.GetCentroid(), &cg);
   shapeProps->put_Centroid(cg);

   shapeProps->put_Ixx(shape_props.GetIxx());
   shapeProps->put_Iyy(shape_props.GetIyy());
   shapeProps->put_Ixy(shape_props.GetIxy());
   shapeProps->put_Xleft(shape_props.GetXleft());
   shapeProps->put_Xright(shape_props.GetXright());
   shapeProps->put_Ytop(shape_props.GetYtop());
   shapeProps->put_Ybottom(shape_props.GetYbottom());

   return S_OK;
}
