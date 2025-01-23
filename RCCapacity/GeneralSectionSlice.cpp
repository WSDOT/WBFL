///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// GeneralSectionSlice.cpp : Implementation of CGeneralSectionSlice
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "GeneralSectionSlice.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralSectionSlice
HRESULT CGeneralSectionSlice::FinalConstruct()
{
   return S_OK;
}

void CGeneralSectionSlice::FinalRelease()
{
}


STDMETHODIMP CGeneralSectionSlice::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGeneralSectionSlice,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IGeneralSectionSlice
STDMETHODIMP CGeneralSectionSlice::InitSlice(IndexType shapeIdx,IShape* pShape,Float64 A,Float64 cgX,Float64 cgY,Float64 initialStrain, Float64 incrementalStrain, Float64 totalStrain,Float64 fgStress,Float64 bgStress,IStressStrain* pfgMaterial,IStressStrain* pbgMaterial, VARIANT_BOOL vbExceededStrainLimit)
{
   ATLASSERT(::IsEqual(initialStrain + incrementalStrain, totalStrain));
   m_ShapeIdx = shapeIdx;
   m_Shape = pShape;
   m_Area = A;
   m_cgX = cgX;
   m_cgY = cgY;
   m_InitialStrain = initialStrain;
   m_IncrementalStrain = incrementalStrain;
   m_TotalStrain = totalStrain;
   m_fgStress = fgStress;
   m_bgStress = bgStress;
   m_fgMaterial = pfgMaterial;
   m_bgMaterial = pbgMaterial;
   m_vbExceededStrainLimit = vbExceededStrainLimit;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_Area(Float64* pArea)
{
   CHECK_RETVAL(pArea);
   *pArea = m_Area;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_CG(IPoint2d** pCG)
{
   CHECK_RETOBJ(pCG);
   CComPtr<IPoint2d> cg;
   cg.CoCreateInstance(CLSID_Point2d);
   cg->Move(m_cgX,m_cgY);
   (*pCG) = cg;
   (*pCG)->AddRef();
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_InitialStrain(Float64* pStrain)
{
   CHECK_RETVAL(pStrain);
   *pStrain = m_InitialStrain;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_IncrementalStrain(Float64* pStrain)
{
   CHECK_RETVAL(pStrain);
   *pStrain = m_IncrementalStrain;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_TotalStrain(Float64* pStrain)
{
   CHECK_RETVAL(pStrain);
   *pStrain = m_TotalStrain;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_ForegroundStress(Float64* pfgStress)
{
   CHECK_RETVAL(pfgStress);
   *pfgStress = m_fgStress;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_BackgroundStress(Float64* pbgStress)
{
   CHECK_RETVAL(pbgStress);
   *pbgStress = m_bgStress;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_ForegroundMaterial(IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   *pMaterial = m_fgMaterial;
   if ( *pMaterial )
      (*pMaterial)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_BackgroundMaterial(IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   *pMaterial = m_bgMaterial;
   if ( *pMaterial )
      (*pMaterial)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_Shape(IShape** pShape)
{
   CHECK_RETOBJ(pShape);
   (*pShape) = m_Shape;
   (*pShape)->AddRef();
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::get_ShapeIndex(IndexType* pShapeIdx)
{
   CHECK_RETVAL(pShapeIdx);
   *pShapeIdx = m_ShapeIdx;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSlice::ExceededStrainLimit(VARIANT_BOOL* pvbExceededStrainLimit)
{
   CHECK_RETVAL(pvbExceededStrainLimit);
   *pvbExceededStrainLimit = m_vbExceededStrainLimit;
   return S_OK;
}
