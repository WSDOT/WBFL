///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// RebarLayout.cpp : Implementation of CRebarLayout
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "RebarLayout.h"
#include "RebarSection.h"
#include "RebarSectionItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarLayout
void CRebarLayout::FinalRelease()
{
}

STDMETHODIMP CRebarLayout::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRebarLayout,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRebarLayout::get__EnumRebarLayoutItems(IEnumRebarLayoutItems** enumRebarLayoutItems)
{
   return get__EnumElements(enumRebarLayoutItems);
}

/////////////////////////////////////////////////////////////////
HRESULT CRebarLayout::DoSaveItem(IStructuredSave2* save,IRebarPattern* item)
{
   CComQIPtr<IStructuredStorage2> ssRebarPattern(item);
   return ssRebarPattern->Save(save);
}

HRESULT CRebarLayout::DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem)
{
//   // Create a new span object
//   CComObject<CSpan>* pSpan;
//   CComObject<CSpan>::CreateInstance(&pSpan);
//   CComPtr<ISpan> newSpan = pSpan;
//
//   ATLASSERT(m_pBridge != NULL);
//   pSpan->SetBridge(m_pBridge);
//
//   CComQIPtr<IStructuredStorage2> ssSpan(newSpan);
//   HRESULT hr = ssSpan->Load(load);
//   if ( FAILED(hr) )
//      return hr;
//
//   (*ppItem) = newSpan;
//   (*ppItem)->AddRef();
//
//   return S_OK;

   // Need to polymorphically create rebar pattern item
   return E_FAIL;
}

STDMETHODIMP CRebarLayout::CreateRebarSection(Float64 cutLocation,IRebarSection** section)
{
   CComObject<CRebarSection>* pSection;
   CComObject<CRebarSection>::CreateInstance(&pSection);
   (*section) = pSection;
   (*section)->AddRef();

   CComPtr<IEnumRebarLayoutItems> enumItems;
   get__EnumRebarLayoutItems(&enumItems);
   
   CComPtr<IRebarLayoutItem> rebarLayoutItem;
   while ( enumItems->Next(1,&rebarLayoutItem,NULL) != S_FALSE )
   {
      VARIANT_BOOL bContainsLocation;
      rebarLayoutItem->ContainsLocation(cutLocation,&bContainsLocation);
      if ( bContainsLocation == VARIANT_TRUE )
      {
         CComPtr<IEnumRebarPatterns> enumPatterns;
         rebarLayoutItem->get__EnumRebarPatterns(&enumPatterns);

         Float64 start,length;
         rebarLayoutItem->get_Start(&start);
         rebarLayoutItem->get_Length(&length);

         CComPtr<IRebarPattern> rebarPattern;
         while ( enumPatterns->Next(1,&rebarPattern,NULL) != S_FALSE )
         {
            CComPtr<IRebar> rebar;
            rebarPattern->get_Rebar(&rebar);

            CollectionIndexType nBars;
            rebarPattern->get_Count(&nBars);

            for ( CollectionIndexType barIdx = 0; barIdx < nBars; barIdx++ )
            {
               CComPtr<IPoint2d> point;
               rebarPattern->get_Location(cutLocation-start,barIdx,&point);

               CComObject<CRebarSectionItem>* pSectionItem;
               CComObject<CRebarSectionItem>::CreateInstance(&pSectionItem);
               pSectionItem->Init(point,cutLocation-start,start+length-cutLocation,rebar);

               CComPtr<IRebarSectionItem> section_item = pSectionItem;

               (*section)->Add(section_item);
            }

            rebarPattern.Release();
         }
      }

      rebarLayoutItem.Release();
   }

   return S_OK;
}
