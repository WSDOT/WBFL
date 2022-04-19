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

// MultiWeb2.cpp : Implementation of CMultiWeb2
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "MultiWeb2.h"
#include "Point2d.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMultiWeb2
HRESULT CMultiWeb2::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CMultiWeb2::FinalRelease()
{
}

void CMultiWeb2::SetShape(const WBFL::Geometry::MultiWeb2& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CMultiWeb2::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IMultiWeb2,
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

STDMETHODIMP CMultiWeb2::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW1();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_W1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW1(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW2();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_W2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_H1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH1();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_H1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetH1(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_H2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH2();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_H2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetH2(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_H3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH3();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_H3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetH3(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT1();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetT1(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT2();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetT2(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT3();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetT3( newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT4();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetT4(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_T5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetT5();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_T5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetT5(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_F1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetF1();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_F1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetF1(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_F2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetF2();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_F2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetF2(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_C1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetC1( newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_C2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC2();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_C2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IMultiWeb2,GEOMETRY_E_DIMENSION);

   m_Beam.SetC2(newVal);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_WebCount(WebIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetWebCount();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_WebCount(WebIndexType newVal)
{
   try
   {
      m_Beam.SetWebCount(newVal);
   }
   catch (...)
   {
      return Error(IDS_E_DIMENSION, IID_IMultiWeb2, GEOMETRY_E_DIMENSION);
   }

   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   m_Beam.SetLeftBlockout(bLeftBlockOut == VARIANT_TRUE ? true : false);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = MakeBool(m_Beam.GetLeftBlockout());
   return S_OK;
}

STDMETHODIMP CMultiWeb2::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   m_Beam.SetRightBlockout(bRightBlockOut == VARIANT_TRUE ? true : false);
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = MakeBool(m_Beam.GetRightBlockout());;
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_WebLocation(WebIndexType webIdx,Float64* location)
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

STDMETHODIMP CMultiWeb2::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetTopFlangeWidth();
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_AvgWebWidth(WebIndexType webIdx,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   try
   {
      *pVal = m_Beam.GetAvgWebWidth(webIdx);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }

   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CMultiWeb2::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CMultiWeb2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CMultiWeb2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
