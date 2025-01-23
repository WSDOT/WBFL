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

// PCIDeckedIBeam.cpp : Implementation of CPCIDeckedIBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PCIDeckedIBeam.h"
#include "Point2d.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCIDeckedIBeam
HRESULT CPCIDeckedIBeam::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CPCIDeckedIBeam::FinalRelease()
{
}

void CPCIDeckedIBeam::SetShape(const WBFL::Geometry::PCIDeckedIBeam& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CPCIDeckedIBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IPCIDeckedIBeam,
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

STDMETHODIMP CPCIDeckedIBeam::get_W1(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW1();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetW1(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W2(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW2();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W2(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W3(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW3();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W3(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetW3(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W4(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW4();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W4(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetW4(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W5(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW5();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W5(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetW5(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_W6(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW6();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_W6(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetW6(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D1(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD1();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD1(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D2(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD2();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D2(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD2(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D3(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD3();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D3(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD3(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D4(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD4();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D4(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD4(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D5(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD5();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D5(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD5(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D6(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD6();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D6(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD6(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D7(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD7();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D7(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD7(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D8(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD8();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D8(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD8(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_D9(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD9();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_D9(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetD9(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_H(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetH();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_H(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetH(newVal);

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_T(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetT();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_T(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetT(newVal);

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_R1(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetR1();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_R1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetR1(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_R2(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetR2();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_R2(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetR2(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_R3(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetR3();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_R3(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetR3(newVal);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_C1(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::put_C1(Float64 newVal)
{
   if (newVal < 0.0)
      return Error(IDS_E_DIMENSION, IID_INUDeckedIBeam, GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);

   return S_OK;
}


STDMETHODIMP CPCIDeckedIBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CPCIDeckedIBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_Height(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetHeight();

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_AvgWebWidth(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetAvgWebWidth();

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_BottomFlangeWidth(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetBottomFlangeWidth(0);

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_TopFlangeWidth(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetTopFlangeWidth(0);

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::GetTopFlangeThickness(Float64* pHl, Float64* pHc, Float64* pHr)
{
   CHECK_RETVAL(pHl);
   CHECK_RETVAL(pHc);
   CHECK_RETVAL(pHr);
   m_Beam.GetTopFlangeThickness(pHl, pHc, pHr);
   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCL, IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppTopCentral);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   WBFL::Geometry::Point2d pntLeftTop;
   WBFL::Geometry::Point2d pntLeftBottom;
   WBFL::Geometry::Point2d pntTopCL;
   WBFL::Geometry::Point2d pntTopCentral;
   WBFL::Geometry::Point2d pntRightTop;
   WBFL::Geometry::Point2d pntRightBottom;

   m_Beam.GetTopFlangePoints(&pntLeftTop, &pntLeftBottom, &pntTopCL, &pntTopCentral, &pntRightTop, &pntRightBottom);

   CreatePoint(pntLeftTop, ppLeftTop);
   CreatePoint(pntLeftBottom, ppLeftBottom);
   CreatePoint(pntTopCL, ppTopCL);
   CreatePoint(pntTopCentral, ppTopCentral);
   CreatePoint(pntRightTop, ppRightTop);
   CreatePoint(pntRightBottom, ppRightBottom);

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom)
{
   CHECK_RETOBJ(ppLeftTop);
   CHECK_RETOBJ(ppLeftBottom);
   CHECK_RETOBJ(ppRightTop);
   CHECK_RETOBJ(ppRightBottom);

   WBFL::Geometry::Point2d pntLeftTop;
   WBFL::Geometry::Point2d pntLeftBottom;
   WBFL::Geometry::Point2d pntRightTop;
   WBFL::Geometry::Point2d pntRightBottom;

   m_Beam.GetBottomFlangePoints(&pntLeftTop, &pntLeftBottom, &pntRightTop, &pntRightBottom);

   CreatePoint(pntLeftTop, ppLeftTop);
   CreatePoint(pntLeftBottom, ppLeftBottom);
   CreatePoint(pntRightTop, ppRightTop);
   CreatePoint(pntRightBottom, ppRightBottom);

   return S_OK;
}

STDMETHODIMP CPCIDeckedIBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CPCIDeckedIBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
