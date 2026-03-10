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

// NUBeam.cpp : Implementation of CNUBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "NUBeam.h"
#include "Point2d.h"
#include "Helper.h"
#include <MathEx.h>


/////////////////////////////////////////////////////////////////////////////
// CNUBeam
HRESULT CNUBeam::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CNUBeam::FinalRelease()
{
}

void CNUBeam::SetShape(const WBFL::Geometry::NUBeam& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CNUBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_INUBeam,
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

STDMETHODIMP CNUBeam::get_W1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW1();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_W1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW1(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_W2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetW2();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_W2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW2(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetD1();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD1(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD2();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD2(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD3();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD3(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD4();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD4(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_D5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetD5();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_D5(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetD5(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_T(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetT();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_T(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetT(newVal);

   return S_OK;
}

STDMETHODIMP CNUBeam::get_EndBlock(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetEndBlockWidth();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_EndBlock(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetEndBlockWidth(newVal);

   return S_OK;
}

STDMETHODIMP CNUBeam::get_R1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetR1();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetR1(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_R2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetR2();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetR2(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_R3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetR3();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetR3(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_R4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetR4();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_R4(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetR4(newVal);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CNUBeam::put_C1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_INUBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);

   return S_OK;
}

STDMETHODIMP CNUBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CNUBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CNUBeam::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CNUBeam::get_AvgWebWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetAvgWebWidth();
   return S_OK;
}

STDMETHODIMP CNUBeam::get_BottomFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetBottomFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_TopFlangeWidth(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetTopFlangeWidth(0);
   return S_OK;
}

STDMETHODIMP CNUBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CNUBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
