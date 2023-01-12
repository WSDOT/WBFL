///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// ShapeProperties.cpp : Implementation of CShapeProperties
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "ShapeProperties.h"
#include "Helper.h"
#include <WBFLTools.h> // for Mohr's Circle
#include <MathEx.h>
#include <utility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShapeProperties


STDMETHODIMP CShapeProperties::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IShapeProperties
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CShapeProperties::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Area(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetArea();
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Area(Float64 newVal)
{
   m_Properties.SetArea(newVal);
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Centroid(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Properties.GetCentroid(), pVal);
}

STDMETHODIMP CShapeProperties::put_Centroid(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Float64 x, y; newVal->Location(&x, &y);
   m_Properties.SetCentroid(WBFL::Geometry::Point2d(x, y));

   return S_OK;
}

STDMETHODIMP CShapeProperties::get_I11(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetI11();
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_I22(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetI22();
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_I12Max(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetI12Max();
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_I12Min(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetI12Min();
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ixx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetIxx();
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ixx(Float64 newVal)
{
   m_Properties.SetIxx(newVal);
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Iyy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetIyy();
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Iyy(Float64 newVal)
{
   m_Properties.SetIyy(newVal);
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ixy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetIxy();
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ixy(Float64 newVal)
{
   m_Properties.SetIxy(newVal);
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Xleft(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetXleft();
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Xleft(Float64 newVal)
{
   if (newVal < 0)
      return E_INVALIDARG;

   m_Properties.SetXleft(newVal);
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Xright(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetXright();
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Xright(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Properties.SetXright(newVal);
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ytop(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetYtop();
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ytop(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Properties.SetYtop(newVal);
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ybottom(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Properties.GetYbottom();
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ybottom(Float64 newVal)
{
   if (newVal < 0)
      return E_INVALIDARG;

   m_Properties.SetYbottom(newVal);
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Origin(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreatePoint( m_Properties.GetOrigin(),  pVal );
}

STDMETHODIMP CShapeProperties::put_Origin(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Float64 x, y; newVal->Location(&x, &y);
   m_Properties.SetOrigin(WBFL::Geometry::Point2d(x, y));

   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Orientation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetOrientation();
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Orientation(Float64 newVal)
{
   m_Properties.SetOrientation(newVal);
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_CoordinateSystem(CoordinateSystemType *pVal)
{
   CHECK_RETVAL(pVal);
   WBFL::Geometry::ShapeProperties::CoordSystemType type = m_Properties.GetCoordinateSystem();
   *pVal = (CoordinateSystemType)std::underlying_type_t<CoordinateSystemType>(type);
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_CoordinateSystem(CoordinateSystemType newVal)
{
   m_Properties.SetCoordinateSystem(WBFL::Geometry::ShapeProperties::CoordSystemType(newVal));
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_PrincipleDirection(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Properties.GetPrincipalDirection();
   return S_OK;
}

STDMETHODIMP CShapeProperties::AddProperties(IShapeProperties* props)
{
   CHECK_IN(props);
   CShapeProperties* pProperties = dynamic_cast<CShapeProperties*>(props);
   m_Properties += pProperties->m_Properties;
   return S_OK;
}
