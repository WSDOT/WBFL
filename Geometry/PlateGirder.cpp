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

// PlateGirder.cpp : Implementation of CPlateGirder
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PlateGirder.h"
#include "Helper.h"
#include "Point2d.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlateGirder
HRESULT CPlateGirder::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CPlateGirder::FinalRelease()
{
}

void CPlateGirder::SetShape(const WBFL::Geometry::PlateGirder& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CPlateGirder::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPlateGirder,
      &IID_IShape,
      &IID_IXYPosition
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPlateGirder::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetTopFlangeWidth();
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_TopFlangeWidth(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_Beam.SetTopFlangeWidth(newVal);
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_TopFlangeThickness(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetTopFlangeThickness();
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_TopFlangeThickness(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_Beam.SetTopFlangeThickness(newVal);
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetBottomFlangeWidth();
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_BottomFlangeWidth(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_Beam.SetBottomFlangeWidth(newVal);
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_BottomFlangeThickness(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetBottomFlangeThickness();
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_BottomFlangeThickness(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_Beam.SetBottomFlangeThickness(newVal);

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_WebHeight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetWebHeight();
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_WebHeight(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_Beam.SetWebHeight(newVal);

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_WebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetWebWidth();;
	return S_OK;
}

STDMETHODIMP CPlateGirder::put_WebWidth(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPlateGirder,GEOMETRY_E_DIMENSION);

   m_Beam.SetWebWidth(newVal);

	return S_OK;
}

STDMETHODIMP CPlateGirder::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_QTopFlange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetQTopFlange();
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_QBottomFlange(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetQBottomFlange();
	return S_OK;
}

STDMETHODIMP CPlateGirder::get_HookPoint(IPoint2d **hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CPlateGirder::putref_HookPoint(IPoint2d *hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CPlateGirder::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CPlateGirder::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
