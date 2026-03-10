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

// BulbTee2.cpp : Implementation of CBulbTee2
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "BulbTee2.h"
#include "Point2d.h"


/////////////////////////////////////////////////////////////////////////////



// CBulbTee2
HRESULT CBulbTee2::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CBulbTee2::FinalRelease()
{
}

void CBulbTee2::SetShape(const WBFL::Geometry::BulbTee& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CBulbTee2::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IBulbTee2,
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

STDMETHODIMP CBulbTee2::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW1();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW1(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW2();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW3();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW3(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW4();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW4(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW5();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW5(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_W6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW6();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_W6(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetW6(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_C1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_C2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetC2();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_C2(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_IBulbTee2, GEOMETRY_E_DIMENSION);

   m_Beam.SetC2(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD1();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD1(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD2();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD2(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD3();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD3(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD4();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD4(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD5();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD5(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD6();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D6(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD6(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_D7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD7();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_D7(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetD7(newVal);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_T1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetT1();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_T1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetT1(newVal);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_T2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetT2();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_T2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBulbTee2,GEOMETRY_E_DIMENSION);

   m_Beam.SetT2(newVal);

   return S_OK;
}


STDMETHODIMP CBulbTee2::get_n1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetN1();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_n1(Float64 newVal)
{
   m_Beam.SetN1(newVal);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_n2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetN2();
   return S_OK;
}

STDMETHODIMP CBulbTee2::put_n2(Float64 newVal)
{

   m_Beam.SetN2(newVal);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CBulbTee2::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_MinHeight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetMinHeight();
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_MaxHeight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetMaxHeight();
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_CLHeight(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetCLHeight();
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_Height(Float64 *pVal)
{
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetAvgWebWidth();
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetBottomFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CBulbTee2::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetTopFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CBulbTee2::GetTopFlangeThickness(Float64* pHl, Float64* pHc, Float64* pHr)
{
   CHECK_RETVAL(pHl);
   CHECK_RETVAL(pHc);
   CHECK_RETVAL(pHr);
   m_Beam.GetTopFlangeThickness(pHl, pHc, pHr);
   return S_OK;
}

STDMETHODIMP CBulbTee2::GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCL,IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppTopCentral);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   WBFL::Geometry::Point2d leftTop, leftBottom, topCL, topCentral, rightTop, rightBottom;
   m_Beam.GetTopFlangePoints(&leftTop, &leftBottom, &topCL, &topCentral, &rightTop, &rightBottom);
   CreatePoint(leftTop, ppLeftTop);
   CreatePoint(leftBottom, ppLeftBottom);
   CreatePoint(topCL, ppTopCL);
   CreatePoint(topCentral, ppTopCentral);
   CreatePoint(rightTop, ppRightTop);
   CreatePoint(rightBottom, ppRightBottom);
   return S_OK;
}

STDMETHODIMP CBulbTee2::GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   WBFL::Geometry::Point2d leftTop, leftBottom, rightTop, rightBottom;
   m_Beam.GetBottomFlangePoints(&leftTop, &leftBottom, &rightTop, &rightBottom);
   CreatePoint(leftTop, ppLeftTop);
   CreatePoint(leftBottom, ppLeftBottom);
   CreatePoint(rightTop, ppRightTop);
   CreatePoint(rightBottom, ppRightBottom);

   return S_OK;
}

STDMETHODIMP CBulbTee2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CBulbTee2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
