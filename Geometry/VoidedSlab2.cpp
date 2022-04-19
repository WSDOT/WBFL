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

// VoidedSlab2.cpp : Implementation of CVoidedSlab2
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "VoidedSlab2.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

// CVoidedSlab2
HRESULT CVoidedSlab2::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CVoidedSlab2::FinalRelease()
{
}

void CVoidedSlab2::SetShape(const WBFL::Geometry::VoidedSlab2& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CVoidedSlab2::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IVoidedSlab2,
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

STDMETHODIMP CVoidedSlab2::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetWidth();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_Width(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetWidth(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_Height(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetHeight(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_C1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC1();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_C1(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetC1(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_C2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC2();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_C2(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetC2(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_C3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetC3();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_C3(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetC3(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   m_Beam.SetLeftBlockout(bLeftBlockOut == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = MakeBool(m_Beam.GetLeftBlockout());
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   m_Beam.SetRightBlockout(bRightBlockOut == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = MakeBool(m_Beam.GetRightBlockout());
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_ExteriorVoidDiameter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetExteriorVoidDiameter();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_ExteriorVoidDiameter(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetExteriorVoidDiameter(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_InteriorVoidDiameter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetInteriorVoidDiameter();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_InteriorVoidDiameter(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetInteriorVoidDiameter(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_ExteriorVoidSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetExteriorVoidSpacing();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_ExteriorVoidSpacing(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetExteriorVoidSpacing(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_InteriorVoidSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetInteriorVoidSpacing();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_InteriorVoidSpacing(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetInteriorVoidSpacing(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_ExteriorVoidElevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetExteriorVoidElevation();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_ExteriorVoidElevation(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetExteriorVoidElevation(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_InteriorVoidElevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetInteriorVoidElevation();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_InteriorVoidElevation(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetInteriorVoidElevation(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_VoidCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetVoidCount();
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::put_VoidCount(CollectionIndexType newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab2,GEOMETRY_E_DIMENSION);

   m_Beam.SetVoidCount(newVal);

   return S_OK;
}

STDMETHODIMP CVoidedSlab2::GetSlabShape(IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetSlabShape().get(), ppShape);
}

STDMETHODIMP CVoidedSlab2::GetVoidShape(IndexType idx, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetVoidShape(idx).get(), ppShape);
}

STDMETHODIMP CVoidedSlab2::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CVoidedSlab2::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CVoidedSlab2::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CVoidedSlab2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
