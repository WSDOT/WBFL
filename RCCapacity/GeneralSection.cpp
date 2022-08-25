///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// GeneralSection.cpp : Implementation of CGeneralSection
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "GeneralSection.h"
#include <WBFLGeometry.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralSection
HRESULT CGeneralSection::FinalConstruct()
{
   m_PrimaryShapeIdx = INVALID_INDEX;
   return S_OK;
}

void CGeneralSection::FinalRelease()
{
	m_SectionItems.clear();
}


STDMETHODIMP CGeneralSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGeneralSection,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IGeneralSection
STDMETHODIMP CGeneralSection::AddShape(BSTR bstrName,IShape* pShape,IStressStrain* pfgMaterial,IStressStrain* pbgMaterial,IPlane3d* initialStrain,Float64 Le,VARIANT_BOOL vbPrimaryShape)
{
   if ( pShape == nullptr )
      return E_INVALIDARG;

   if (IsZero(Le))
      return E_INVALIDARG;

   ATLASSERT(1.0 <= Le); // Le should be 1 for unit or greater...

   m_SectionItems.emplace_back(bstrName,pShape,pfgMaterial,pbgMaterial,initialStrain,Le);
   if (m_SectionItems.back().initialStrain == nullptr)
   {
      m_SectionItems.back().initialStrain.CoCreateInstance(CLSID_Plane3d);
   }

   if (vbPrimaryShape == VARIANT_TRUE)
   {
      m_PrimaryShapeIdx = m_SectionItems.size() - 1;
   }

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ShapeCount(CollectionIndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_SectionItems.size();
   return S_OK;
}

STDMETHODIMP CGeneralSection::put_PrimaryShapeIndex(IndexType shapeIdx)
{
   if (m_SectionItems.size() <= shapeIdx)
      return E_INVALIDARG;

   m_PrimaryShapeIdx = shapeIdx;
   return S_OK;
}

STDMETHODIMP CGeneralSection::get_PrimaryShapeIndex(IndexType* pShapeIdx)
{
   CHECK_RETVAL(pShapeIdx);
   ATLASSERT(m_PrimaryShapeIdx != INVALID_INDEX); // did you forget to designate one shape as the primary???
   *pShapeIdx = m_PrimaryShapeIdx;
   return S_OK;
}

STDMETHODIMP CGeneralSection::put_Name(CollectionIndexType shapeIdx, BSTR bstrName)
{
   CHECK_IN(bstrName);

   if (m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX)
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].bstrName = bstrName;

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_Name(CollectionIndexType shapeIdx, BSTR* pbstrName)
{
   CHECK_RETSTRING(pbstrName);
   if (m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX)
      return E_INVALIDARG;

   return m_SectionItems[shapeIdx].bstrName.CopyTo(pbstrName);
}

STDMETHODIMP CGeneralSection::get_Shape(CollectionIndexType shapeIdx,IShape** pShape)
{
   CHECK_RETOBJ(pShape);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   (*pShape) = m_SectionItems[shapeIdx].shape;
   (*pShape)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::putref_Shape(CollectionIndexType shapeIdx,IShape* pShape)
{
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_IN(pShape);

   m_SectionItems[shapeIdx].shape.Release();
   m_SectionItems[shapeIdx].shape = pShape;
   
   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ForegroundMaterial(CollectionIndexType shapeIdx,IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   (*pMaterial) = m_SectionItems[shapeIdx].fgMaterial;

   if ( *pMaterial )
      (*pMaterial)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::putref_ForegroundMaterial(CollectionIndexType shapeIdx,IStressStrain* pMaterial)
{
   CHECK_IN(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].fgMaterial.Release();
   m_SectionItems[shapeIdx].fgMaterial = pMaterial;

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_BackgroundMaterial(CollectionIndexType shapeIdx,IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   (*pMaterial) = m_SectionItems[shapeIdx].bgMaterial;

   if ( *pMaterial )
      (*pMaterial)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::putref_BackgroundMaterial(CollectionIndexType shapeIdx,IStressStrain* pMaterial)
{
   CHECK_IN(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].bgMaterial.Release();
   m_SectionItems[shapeIdx].bgMaterial = pMaterial;

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_InitialStrain(CollectionIndexType shapeIdx,IPlane3d** pStrainPlane)
{
   CHECK_RETOBJ(pStrainPlane);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   return m_SectionItems[shapeIdx].initialStrain.CopyTo(pStrainPlane);
}

STDMETHODIMP CGeneralSection::putref_InitialStrain(CollectionIndexType shapeIdx,IPlane3d* pStrainPlane)
{
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].initialStrain = pStrainPlane;
   if (m_SectionItems[shapeIdx].initialStrain == nullptr)
   {
      m_SectionItems[shapeIdx].initialStrain.CoCreateInstance(CLSID_Plane3d);
   }

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ElongationLength(CollectionIndexType shapeIdx, Float64* Le)
{
   CHECK_RETVAL(Le);

   if (m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX)
      return E_INVALIDARG;

   *Le = m_SectionItems[shapeIdx].Le;

   return S_OK;
}

STDMETHODIMP CGeneralSection::put_ElongationLength(CollectionIndexType shapeIdx, Float64 Le)
{
   if (m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX)
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].Le = Le;

   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CGeneralSection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("GeneralSection"),1.0);

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CGeneralSection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("GeneralSection"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
