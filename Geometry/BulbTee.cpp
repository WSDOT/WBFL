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

// BulbTee.cpp : Implementation of CBulbTee
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "BulbTee.h"
#include "Point2d.h"
#include <MathEx.h>


/////////////////////////////////////////////////////////////////////////////



// CBulbTee
HRESULT CBulbTee::FinalConstruct()
{
   m_Beam.SetC2(0);
   m_Beam.SetN1(0);
   m_Beam.SetN2(0);

   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CBulbTee::FinalRelease()
{
}

void CBulbTee::SetShape(const WBFL::Geometry::BulbTee& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CBulbTee::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IBulbTee,
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

STDMETHODIMP CBulbTee::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW1();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_W1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetW1(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW2();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_W2(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW3();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_W3(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetW3(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW4();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_W4(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetW4(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_W5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   // our W5 + W6 is the underlying beam's W5
   Float64 w5 = m_Beam.GetW5();
   Float64 w6 = m_Beam.GetW6();
   *pVal = w5 + w6;
   return S_OK;
}

STDMETHODIMP CBulbTee::put_W5(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee, GEOMETRY_E_DIMENSION);

   Float64 w5 = newVal / 2;
   Float64 w6 = newVal / 2;
   m_Beam.SetW5(w5);
   m_Beam.SetW6(w6);

   return S_OK;
}

STDMETHODIMP CBulbTee::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_C1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD1();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_D1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetD1(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD2();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_D2(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetD2(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD3();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_D3(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetD3(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD4();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_D4(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetD4(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD5();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_D5(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetD5(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_D6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD6();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_D6(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetD6(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_D7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD7();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_D7(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetD7(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_T1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT1();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_T1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetT1(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_T2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT2();
   return S_OK;
}

STDMETHODIMP CBulbTee::put_T2(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetT2(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CBulbTee::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CBulbTee::get_Height(Float64 *pVal)
{
#if defined _DEBUG
   // this type of bulb tee doesn't have the crown point in the top flange
   // verify that the dimensions are set correctly
   Float64 Hmin = m_Beam.GetMinHeight();
   Float64 Hmax = m_Beam.GetMaxHeight();
   Float64 Hcl = m_Beam.GetCLHeight();
   ATLASSERT(IsEqual(Hmin, Hmax));
   ATLASSERT(IsEqual(Hmin, Hcl));
#endif
   *pVal = m_Beam.GetMinHeight();
   return S_OK;
}

STDMETHODIMP CBulbTee::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetAvgWebWidth();
   return S_OK;
}

STDMETHODIMP CBulbTee::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetBottomFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetTopFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CBulbTee::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CBulbTee::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
