///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// VoidedSlab.cpp : Implementation of CVoidedSlab
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "VoidedSlab.h"
#include "Helper.h"
#include "Point2d.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CVoidedSlab
HRESULT CVoidedSlab::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CVoidedSlab::FinalRelease()
{
}

void CVoidedSlab::SetShape(const WBFL::Geometry::VoidedSlab& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CVoidedSlab::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IVoidedSlab,
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

STDMETHODIMP CVoidedSlab::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetWidth();
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_Width(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_Beam.SetWidth(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_Height(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_Beam.SetHeight(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_VoidDiameter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetVoidDiameter();
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_VoidDiameter(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_Beam.SetVoidDiameter( newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_VoidSpacing(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetVoidSpacing();
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_VoidSpacing(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_Beam.SetVoidSpacing(newVal);
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_VoidCount(IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetVoidCount();
   return S_OK;
}

STDMETHODIMP CVoidedSlab::put_VoidCount(IndexType newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IVoidedSlab,GEOMETRY_E_DIMENSION);

   m_Beam.SetVoidCount(newVal);

   return S_OK;
}

STDMETHODIMP CVoidedSlab::GetSlabShape(IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetSlabShape().get(), ppShape);
}

STDMETHODIMP CVoidedSlab::GetVoidShape(IndexType idx, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetVoidShape(idx).get(), ppShape);
}

STDMETHODIMP CVoidedSlab::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CVoidedSlab::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CVoidedSlab::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CVoidedSlab::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
