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

// BoxBeam.cpp : Implementation of CBoxBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "BoxBeam.h"
#include "Point2d.h"
#include "Helper.h"


/////////////////////////////////////////////////////////////////////////////



// CBoxBeam
HRESULT CBoxBeam::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CBoxBeam::FinalRelease()
{
}

void CBoxBeam::SetShape(const WBFL::Geometry::BoxBeam& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CBoxBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IBoxBeam,
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

STDMETHODIMP CBoxBeam::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW1();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW1(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW2();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_W3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW3();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW3(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_W4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW4();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_W4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW4(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH1();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetH1(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH2();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetH2(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH3();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetH3(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH4();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetH4(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH5();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetH5(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H6(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH6();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H6(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetH6(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_H7(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetH7();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_H7(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetH7(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_F1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetF1();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_F1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetF1(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_F2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetF2();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_F2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetF2(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_C1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_VoidCount(IndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetVoidCount();
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_VoidCount(IndexType newVal)
{
   // can only have 0 or 1 void
   if ( newVal < 0 || newVal>1)
      return Error(IDS_E_DIMENSION,IID_IBoxBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetVoidCount(newVal);

   return S_OK;
}

STDMETHODIMP CBoxBeam::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   m_Beam.SetLeftBlockout(bLeftBlockOut == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = MakeBool(m_Beam.GetLeftBlockout());
   return S_OK;
}

STDMETHODIMP CBoxBeam::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   m_Beam.SetRightBlockout(bRightBlockOut == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = MakeBool(m_Beam.GetRightBlockout());
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_WebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetWebWidth();
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_BottomFlangeWidth(Float64* pLeft, Float64* pRight)
{
   CHECK_RETVAL(pLeft);
   CHECK_RETVAL(pRight);
   m_Beam.GetBottomFlangeWidth(pLeft, pRight);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_TopFlangeWidth(Float64* pLeft, Float64* pRight)
{
   CHECK_RETVAL(pLeft);
   CHECK_RETVAL(pRight);
   m_Beam.GetTopFlangeWidth(pLeft, pRight);
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_Width(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetWidth();
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_Height(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CBoxBeam::GetBoundaryPoints(IPoint2d ** ppLeftTop, IPoint2d ** ppLeftBottom, IPoint2d ** ppRightTop, IPoint2d ** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   WBFL::Geometry::Point2d leftTop, leftBottom, rightTop, rightBottom;
   m_Beam.GetBoundaryPoints(&leftTop, &leftBottom, &rightTop, &rightBottom);
   CreatePoint(leftTop, ppLeftTop);
   CreatePoint(leftBottom, ppLeftBottom);
   CreatePoint(rightTop, ppRightTop);
   CreatePoint(rightBottom, ppRightBottom);

   return S_OK;
}

STDMETHODIMP CBoxBeam::GetBoxShape(IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetBoxShape().get(), ppShape);
}

STDMETHODIMP CBoxBeam::GetVoidShape(IndexType idx, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetVoidShape(idx).get(), ppShape);
}


STDMETHODIMP CBoxBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CBoxBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CBoxBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CBoxBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
