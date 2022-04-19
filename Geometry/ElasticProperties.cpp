///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include "WBFLSections.h"
#include "ElasticProperties.h"

#include <WBFLGeometry.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElasticProperties
HRESULT CElasticProperties::FinalConstruct()
{
   HRESULT hr = m_Props.CoCreateInstance(CLSID_ShapeProperties);
   return hr;
}

STDMETHODIMP CElasticProperties::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IElasticProperties,
		&IID_IStructuredStorage2,
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
   return m_Props->get_Area(pVal);
}

STDMETHODIMP CElasticProperties::put_EA(Float64 newVal)
{
   return m_Props->put_Area(newVal);
}

STDMETHODIMP CElasticProperties::get_Centroid(IPoint2d **pVal)
{
   return m_Props->get_Centroid(pVal);
}

STDMETHODIMP CElasticProperties::put_Centroid(IPoint2d *newVal)
{
   return m_Props->put_Centroid(newVal);
}

STDMETHODIMP CElasticProperties::get_EI11(Float64 *pVal)
{
   return m_Props->get_I11(pVal);
}

STDMETHODIMP CElasticProperties::get_EI22(Float64 *pVal)
{
   return m_Props->get_I22(pVal);
}

STDMETHODIMP CElasticProperties::get_EI12Max(Float64 *pVal)
{
   return m_Props->get_I12Max(pVal);
}

STDMETHODIMP CElasticProperties::get_EI12Min(Float64 *pVal)
{
   return m_Props->get_I12Min(pVal);
}

STDMETHODIMP CElasticProperties::get_EIxx(Float64 *pVal)
{
   return m_Props->get_Ixx(pVal);
}

STDMETHODIMP CElasticProperties::put_EIxx(Float64 newVal)
{
   return m_Props->put_Ixx(newVal);
}

STDMETHODIMP CElasticProperties::get_EIyy(Float64 *pVal)
{
   return m_Props->get_Iyy(pVal);
}

STDMETHODIMP CElasticProperties::put_EIyy(Float64 newVal)
{
   return m_Props->put_Iyy(newVal);
}

STDMETHODIMP CElasticProperties::get_EIxy(Float64 *pVal)
{
   return m_Props->get_Ixy(pVal);
}

STDMETHODIMP CElasticProperties::put_EIxy(Float64 newVal)
{
   return m_Props->put_Ixy(newVal);
}

STDMETHODIMP CElasticProperties::get_Xleft(Float64 *pVal)
{
   return m_Props->get_Xleft(pVal);
}

STDMETHODIMP CElasticProperties::put_Xleft(Float64 newVal)
{
   return m_Props->put_Xleft(newVal);
}

STDMETHODIMP CElasticProperties::get_Xright(Float64 *pVal)
{
   return m_Props->get_Xright(pVal);
}

STDMETHODIMP CElasticProperties::put_Xright(Float64 newVal)
{
   return m_Props->put_Xright(newVal);
}

STDMETHODIMP CElasticProperties::get_Ytop(Float64 *pVal)
{
   return m_Props->get_Ytop(pVal);
}

STDMETHODIMP CElasticProperties::put_Ytop(Float64 newVal)
{
   return m_Props->put_Ytop(newVal);
}

STDMETHODIMP CElasticProperties::get_Ybottom(Float64 *pVal)
{
   return m_Props->get_Ybottom(pVal);
}

STDMETHODIMP CElasticProperties::put_Ybottom(Float64 newVal)
{
   return m_Props->put_Ybottom(newVal);
}

STDMETHODIMP CElasticProperties::get_Origin(IPoint2d **pVal)
{
   return m_Props->get_Origin(pVal);
}

STDMETHODIMP CElasticProperties::put_Origin(IPoint2d *newVal)
{
   return m_Props->put_Origin(newVal);
}

STDMETHODIMP CElasticProperties::get_Orientation(Float64 *pVal)
{
   return m_Props->get_Orientation(pVal);
}

STDMETHODIMP CElasticProperties::put_Orientation(Float64 newVal)
{
   return m_Props->put_Orientation(newVal);
}

STDMETHODIMP CElasticProperties::get_CoordinateSystem(CoordinateSystemType *pVal)
{
   return m_Props->get_CoordinateSystem(pVal);
}

STDMETHODIMP CElasticProperties::put_CoordinateSystem(CoordinateSystemType newVal)
{
   return m_Props->put_CoordinateSystem(newVal);
}

STDMETHODIMP CElasticProperties::get_PrincipleDirection(Float64 *pVal)
{
   return m_Props->get_PrincipleDirection(pVal);
}

STDMETHODIMP CElasticProperties::AddProperties(IElasticProperties* props)
{
   CHECK_IN(props);

   CComPtr<IShapeProperties> shapeProps;
   props->TransformProperties(1.0,&shapeProps);

   return m_Props->AddProperties(shapeProps);
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

   Float64   area;
   CComPtr<IPoint2d> centroid;
   Float64   Ixx;
   Float64   Iyy;
   Float64   Ixy;
   Float64   Xleft, Xright;
   Float64   Ytop, Ybottom;

   // Make sure we are in centroidal coordinates
   // That is the default for a new shape properties object
   m_Props->put_CoordinateSystem(csCentroidal);

   m_Props->get_Area(&area);
   area /= E;
   shapeProps->put_Area(area);

   m_Props->get_Centroid(&centroid);
   shapeProps->put_Centroid(centroid);

   m_Props->get_Ixx(&Ixx);
   Ixx /= E;
   shapeProps->put_Ixx(Ixx);

   m_Props->get_Ixy(&Ixy);
   Ixy /= E;
   shapeProps->put_Ixy(Ixy);

   m_Props->get_Iyy(&Iyy);
   Iyy /= E;
   shapeProps->put_Iyy(Iyy);

   m_Props->get_Xleft(&Xleft);
   shapeProps->put_Xleft(Xleft);

   m_Props->get_Xright(&Xright);
   shapeProps->put_Xright(Xright);

   m_Props->get_Ytop(&Ytop);
   shapeProps->put_Ytop(Ytop);

   m_Props->get_Ybottom(&Ybottom);
   shapeProps->put_Ybottom(Ybottom);

   return S_OK;
}

STDMETHODIMP CElasticProperties::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CElasticProperties::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("ElasticProperties"),1.0);
   pSave->put_Property(CComBSTR("Properties"),CComVariant(m_Props));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CElasticProperties::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("ElasticProperties"));

   pLoad->get_Property(CComBSTR("Properties"),&var);
   if ( FAILED( _CopyVariantToInterface<IShapeProperties>::copy(&m_Props,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
