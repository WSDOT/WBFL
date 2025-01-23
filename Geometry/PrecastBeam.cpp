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

// PrecastBeam.cpp : Implementation of CPrecastBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PrecastBeam.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The underlying beam has different dimensions than this beam shape
// The following table maps the dimensions for this beam shape into the
// dimensions of the underlying beam shape. Dimensions not listed map
// one to one between the two beam shapes
//
// This Beam    |   Underlying Beam
// -------------|------------------
//              | W1 = 0
// W1           | W2
// W2           | W3
// W3           | W5
//              |
// D4           | D6
// D6           | D4
// D7           | H-(D1+D2+D3+D4+D5+D6)
// D1 + ... + D7| h


// CPrecastBeam
HRESULT CPrecastBeam::FinalConstruct()
{
   m_Beam.SetD1(0.0);

   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CPrecastBeam::FinalRelease()
{
}

void CPrecastBeam::SetShape(const WBFL::Geometry::PrecastBeam& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CPrecastBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IPrecastBeam,
      &IID_IShape,
      &IID_IXYPosition
   };
   for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP CPrecastBeam::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW2(); // our W1 is tye underlying beam type's W2
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_W1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW3(); // our W2 is the underlying beam type's W3
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_W2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW3(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW5(); // our W3 is the underlying beam's W5
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_W3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW5(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW4();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_W4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW4(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD1();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_D1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD1(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD2();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_D2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD2(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD3();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_D3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD3(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD6(); // D4 is the underlying beam's D6
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_D4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD6(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD5();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_D5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD5(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_D6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD4(); // D6 is the underlying beam's D4
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_D6(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD4(newVal);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_D7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetHeight() - (m_Beam.GetD1() + m_Beam.GetD2() + m_Beam.GetD3() + m_Beam.GetD4() + m_Beam.GetD5() + m_Beam.GetD6());
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_D7(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetHeight(newVal + m_Beam.GetD1() + m_Beam.GetD2() + m_Beam.GetD3() + m_Beam.GetD4() + m_Beam.GetD5() + m_Beam.GetD6());
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_T1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetT1();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_T1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetT1(newVal);

   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_T2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetT2();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_T2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetT2(newVal);

   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::put_C1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IPrecastBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);

   return S_OK;
}


STDMETHODIMP CPrecastBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CPrecastBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetAvgWebWidth();
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetBottomFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetTopFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CPrecastBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CPrecastBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
