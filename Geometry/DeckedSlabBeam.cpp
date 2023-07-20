///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// DeckedSlabBeam.cpp : Implementation of CDeckedSlabBeam
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "DeckedSlabBeam.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// CDeckedSlabBeam
HRESULT CDeckedSlabBeam::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Beam.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CDeckedSlabBeam::FinalRelease()
{
}

void CDeckedSlabBeam::SetShape(const WBFL::Geometry::DeckedSlabBeam& shape)
{
   m_Beam = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Beam.GetHookPoint());
}

STDMETHODIMP CDeckedSlabBeam::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IDeckedSlabBeam,
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


STDMETHODIMP CDeckedSlabBeam::get_A(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetA();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_A(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetA( newVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_B(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetB();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_B(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetB(newVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_C(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetC();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_C(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetC(newVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_W(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetW();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_W(Float64 newVal)
{
   if ( newVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetW(newVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_F(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetF();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_F(Float64 neFVal)
{
   if ( neFVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetF(neFVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_Tt(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetTt();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_Tt(Float64 neTtVal)
{
   if ( neTtVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetTt(neTtVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_Tb(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetTb();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_Tb(Float64 neTbVal)
{
   if ( neTbVal < 0.0 )
      return Error(IDS_E_DIMENSION,IID_IDeckedSlabBeam,GEOMETRY_E_DIMENSION);

   m_Beam.SetTb(neTbVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_LeftBlockOut(VARIANT_BOOL bLeftBlockOut)
{
   m_Beam.SetLeftBlockout(bLeftBlockOut == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_LeftBlockOut(VARIANT_BOOL* pbLeftBlockOut)
{
   CHECK_RETVAL(pbLeftBlockOut);
   *pbLeftBlockOut = MakeBool(m_Beam.GetLeftBlockout());
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_RightBlockOut(VARIANT_BOOL bRightBlockOut)
{
   m_Beam.SetRightBlockout(bRightBlockOut == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_RightBlockOut(VARIANT_BOOL* pbRightBlockOut)
{
   CHECK_RETVAL(pbRightBlockOut);
   *pbRightBlockOut = MakeBool(m_Beam.GetRightBlockout());
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_VoidCount(IndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Beam.GetVoidCount();;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::put_VoidCount(IndexType newVal)
{
   // Void count can be 0 or 1
   try
   {
      m_Beam.SetVoidCount(newVal);
   }
   catch (...)
   {
      return Error(IDS_E_DIMENSION, IID_IVoidedSlab, GEOMETRY_E_DIMENSION);
   }
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_Height(Float64* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Beam.GetHeight();
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::GetSlabShape(IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetSlabShape().get(), ppShape);
}

STDMETHODIMP CDeckedSlabBeam::GetVoidShape(IndexType idx, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);
   return ConvertShape(m_Beam.GetVoidShape(idx).get(), ppShape);
}

STDMETHODIMP CDeckedSlabBeam::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CDeckedSlabBeam::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Beam.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeam::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CDeckedSlabBeam::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
