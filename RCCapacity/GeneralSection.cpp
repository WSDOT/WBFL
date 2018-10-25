///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IGeneralSection
STDMETHODIMP CGeneralSection::AddShape(IShape* pShape,IStressStrain* pfgMaterial,IStressStrain* pbgMaterial,Float64 ei)
{
   if ( pShape == NULL )
      return E_INVALIDARG;

   SectionItem si;
   si.shape = pShape;
   si.fgMaterial = pfgMaterial;
   si.bgMaterial = pbgMaterial;
   si.ei = ei;

   m_SectionItems.push_back(si);

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ShapeCount(CollectionIndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_SectionItems.size();
   return S_OK;
}

STDMETHODIMP CGeneralSection::get_Shape(CollectionIndexType shapeIdx,IShape** pShape)
{
   CHECK_RETOBJ(pShape);
   CollectionIndexType count = m_SectionItems.size();
   if ( shapeIdx < 0 || count <= shapeIdx )
      return E_INVALIDARG;

   (*pShape) = m_SectionItems[shapeIdx].shape;
   (*pShape)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ForegroundMaterial(CollectionIndexType shapeIdx,IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   CollectionIndexType count = m_SectionItems.size();
   if ( shapeIdx < 0 || count <= shapeIdx )
      return E_INVALIDARG;

   (*pMaterial) = m_SectionItems[shapeIdx].fgMaterial;

   if ( *pMaterial )
      (*pMaterial)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_BackgroundMaterial(CollectionIndexType shapeIdx,IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   CollectionIndexType count = m_SectionItems.size();
   if ( shapeIdx < 0 || count <= shapeIdx )
      return E_INVALIDARG;

   (*pMaterial) = m_SectionItems[shapeIdx].bgMaterial;

   if ( *pMaterial )
      (*pMaterial)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_InitialStrain(CollectionIndexType shapeIdx,Float64* ei)
{
   CHECK_RETVAL(ei);
   CollectionIndexType count = m_SectionItems.size();
   if ( shapeIdx < 0 || count <= shapeIdx )
      return E_INVALIDARG;

   *ei = m_SectionItems[shapeIdx].ei;

   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CGeneralSection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("GeneralSection"),1.0);

   pSave->put_Property(CComBSTR("SectionItemCount"),CComVariant(m_SectionItems.size()));

   std::vector<SectionItem>::iterator iter;
   for ( iter = m_SectionItems.begin(); iter != m_SectionItems.end(); iter++ )
   {
      SectionItem& item = *iter;
      pSave->put_Property(CComBSTR("Shape"),CComVariant(item.shape));
      pSave->put_Property(CComBSTR("FGMaterial"),CComVariant(item.fgMaterial));
      pSave->put_Property(CComBSTR("BGMaterial"),CComVariant(item.bgMaterial));
      pSave->put_Property(CComBSTR("InitialStrain"),CComVariant(item.ei));
   }

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CGeneralSection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("GeneralSection"));

   m_SectionItems.clear();

   CollectionIndexType count;
   if ( FAILED(pLoad->get_Property(CComBSTR("SectionItemCount"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   count = var.iVal;

   for ( CollectionIndexType index = 0; index < count; index++ )
   {
      SectionItem item;

      if ( FAILED(pLoad->get_Property(CComBSTR("Shape"),  &var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      var.punkVal->QueryInterface(&item.shape);

      if ( FAILED(pLoad->get_Property(CComBSTR("FGMaterial"),  &var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      var.punkVal->QueryInterface(&item.fgMaterial);

      if ( FAILED(pLoad->get_Property(CComBSTR("BGMaterial"),  &var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      var.punkVal->QueryInterface(&item.bgMaterial);

      if ( FAILED(pLoad->get_Property(CComBSTR("InitialStrain"),  &var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      item.ei = var.dblVal;

      m_SectionItems.push_back(item);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
