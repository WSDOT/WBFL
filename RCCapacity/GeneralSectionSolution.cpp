///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// GeneralSectionSolution.cpp : Implementation of CGeneralSectionSolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "GeneralSectionSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralSectionSolution
HRESULT CGeneralSectionSolution::FinalConstruct()
{
   return S_OK;
}

void CGeneralSectionSolution::FinalRelease()
{
}


STDMETHODIMP CGeneralSectionSolution::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGeneralSectionSolution,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IGeneralSectionSolution
STDMETHODIMP CGeneralSectionSolution::InitSolution(Float64 fz,Float64 mx,Float64 my,ILine2d* neutralAxis,IPoint2d* cgc,Float64 c,IPoint2d* cgt,Float64 t,IUnkArray* slices,VARIANT_BOOL bExceededStrainLimits)
{
   m_NeutralAxis = neutralAxis;
   m_Fz = fz;
   m_Mx = mx;
   m_My = my;
   m_C  = c;
   m_T  = t;
   m_cgC = cgc;
   m_cgT = cgt;
   m_Slices = slices;
   m_bExceededStrainLimits = bExceededStrainLimits;

   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_NeutralAxis(ILine2d** neutralAxis)
{
   CHECK_RETOBJ(neutralAxis);
   (*neutralAxis) = m_NeutralAxis;
   (*neutralAxis)->AddRef();
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_NeutralAxisDirection(Float64* neutralAxis)
{
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> d;
   m_NeutralAxis->GetExplicit(&p,&d);
   return d->get_Direction(neutralAxis);
}

STDMETHODIMP CGeneralSectionSolution::get_Fz(Float64* fz)
{
   CHECK_RETVAL(fz);
   *fz = m_Fz;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_Mx(Float64* mx)
{
   CHECK_RETVAL(mx);
   *mx = m_Mx;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_My(Float64* my)
{
   CHECK_RETVAL(my);
   *my = m_My;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_CompressionResultant(Float64* c)
{
   CHECK_RETVAL(c);
   *c = m_C;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_TensionResultant(Float64* t)
{
   CHECK_RETVAL(t);
   *t = m_T;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_CompressionResultantLocation(IPoint2d** cgC)
{
   CHECK_RETOBJ(cgC);
   (*cgC) = m_cgC;
   (*cgC)->AddRef();
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_TensionResultantLocation(IPoint2d** cgT)
{
   CHECK_RETOBJ(cgT);
   (*cgT) = m_cgT;
   (*cgT)->AddRef();
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_ExceededStrainLimits(VARIANT_BOOL* pbExceededStrainLimits)
{
   CHECK_RETOBJ(pbExceededStrainLimits);
   *pbExceededStrainLimits = m_bExceededStrainLimits;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::get_SliceCount(IndexType* nSlices)
{
   return m_Slices->get_Count(nSlices);
}

STDMETHODIMP CGeneralSectionSolution::get_Slice(IndexType sliceIdx,IGeneralSectionSlice** pSlice)
{
   IndexType nSlices;
   m_Slices->get_Count(&nSlices);
   if ( sliceIdx < 0 || nSlices <= sliceIdx )
      return E_INVALIDARG;

   CComPtr<IUnknown> punk;
   m_Slices->get_Item(sliceIdx,&punk);
   punk.QueryInterface(pSlice);
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolution::FindSlices(IndexType shapeIdx, IUnkArray** ppSlices)
{
   CHECK_RETOBJ(ppSlices);
   CComPtr<IUnkArray> slices;
   slices.CoCreateInstance(CLSID_UnkArray);

   IndexType nSlices;
   m_Slices->get_Count(&nSlices);
   for (IndexType sliceIdx = 0; sliceIdx < nSlices; sliceIdx++)
   {
      CComPtr<IUnknown> punk;
      m_Slices->get_Item(sliceIdx, &punk);
      CComQIPtr<IGeneralSectionSlice> slice(punk);
      IndexType thisShapeIdx;
      slice->get_ShapeIndex(&thisShapeIdx);
      if (thisShapeIdx == shapeIdx)
      {
         slices->Add(punk);
      }
   }

   return slices.CopyTo(ppSlices);
}
