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

// UBeam2.cpp : Implementation of CUBeam2 
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "UBeam2.h"
#include "Helper.h"
#include <MathEx.h>
#include <float.h>
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUBeam2
HRESULT CUBeam2::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CUBeam2::FinalRelease()
{
}

void CUBeam2::SetShape(const WBFL::Geometry::UBeam2& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CUBeam2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUBeam2,
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

STDMETHODIMP CUBeam2::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW1();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW1(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW2();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW3();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW3(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW4();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW4(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW5();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW5(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW6();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W6(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW6(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_W7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW7();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_W7(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW7(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD1();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD1(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD2();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD2( newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD3();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD3(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD4();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD4(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD5();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD5(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_D6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD6();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_D6(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD6( newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CUBeam2::put_C1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IUBeam2,GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);
   return S_OK;
}

STDMETHODIMP CUBeam2::put_UseOutlineOnly(VARIANT_BOOL bUseOutlineOnly)
{
   m_Beam.UseOutlineOnly(bUseOutlineOnly == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_UseOutlineOnly(VARIANT_BOOL* pUseOutlineOnly)
{
   CHECK_RETVAL(pUseOutlineOnly);
   *pUseOutlineOnly = MakeBool(m_Beam.UseOutlineOnly());
   return S_OK;
}

STDMETHODIMP CUBeam2::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT();
   return S_OK;
}

STDMETHODIMP CUBeam2::get_Slope(WebIndexType webIdx,Float64* slope)
{
   CHECK_RETVAL(slope);
   try
   {
      *slope = m_Beam.GetSlope(webIdx);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CUBeam2::get_TopWidth(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_Beam.GetTopWidth();
   return S_OK;
}

STDMETHODIMP CUBeam2::get_TopFlangeWidth(Float64* width)
{
   CHECK_RETVAL(width);
   *width = m_Beam.GetTopFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CUBeam2::get_WebLocation(WebIndexType webIdx,Float64* location)
{
   CHECK_RETVAL(location);
   try
   {
      *location = m_Beam.GetWebLocation(webIdx);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

STDMETHODIMP CUBeam2::get_WebSpacing(Float64* spacing)
{
   CHECK_RETVAL(spacing);
   *spacing = m_Beam.GetWebSpacing();
   return S_OK;
}

STDMETHODIMP CUBeam2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CUBeam2::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CUBeam2::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
	return S_OK;
}

STDMETHODIMP CUBeam2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CUBeam2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
