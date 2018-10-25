///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TemporaryPierItemCollection.cpp : Implementation of CTemporaryPierItemCollection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "TemporaryPierItemCollection.h"
#include "TemporaryPierItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemporaryPierItemCollection

void CTemporaryPierItemCollection::FinalRelease()
{
   TPICollImpl::Clear(); // Causes all of the TemporaryPierItem object to be Unadvised.
}

void CTemporaryPierItemCollection::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge;

   iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ITemporaryPierItem> item = iter->second.m_T;
      CTemporaryPierItem* pItem = dynamic_cast<CTemporaryPierItem*>(item.p);
      pItem->SetBridge(pBridge);
   }
}

STDMETHODIMP CTemporaryPierItemCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITemporaryPierItemCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTemporaryPierItemCollection::Advise(ITemporaryPierItem* poi,DWORD* pdwCookie)
{
   CComPtr<ITemporaryPierItem> pCP(poi);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ITemporaryPierItemEvents, pdwCookie );
   ATLASSERT(SUCCEEDED(hr));

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CTemporaryPierItemCollection::Unadvise(ITemporaryPierItem* poi,DWORD dwCookie)
{
   ATLASSERT(poi != 0);

   //
   // Disconnection from connection point
   //

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( poi );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ITemporaryPierItemEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));
   return hr;
}

STDMETHODIMP CTemporaryPierItemCollection::Clone(ITemporaryPierItemCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CTemporaryPierItemCollection>* pClone;
   CComObject<CTemporaryPierItemCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IEnumTemporaryPierItems> enumTemporaryPierItems;
   get__EnumTemporaryPierItems(&enumTemporaryPierItems);

   CComPtr<ITemporaryPierItem> tpi;
   while ( enumTemporaryPierItems->Next(1,&tpi,NULL) != S_FALSE )
   {
      CTemporaryPierItem* pTemporaryPierItem = dynamic_cast<CTemporaryPierItem*>(tpi.p);
      CComPtr<ITemporaryPierItem> cloneTemporaryPierItem;
      pTemporaryPierItem->Clone(&cloneTemporaryPierItem);

      ((PersistentTPICollImpl*)pClone)->Add(cloneTemporaryPierItem);

      tpi.Release();
   }

   return S_OK;
}

HRESULT CTemporaryPierItemCollection::OnAfterAdd( StoredType* pVal)
{
   Advise(pVal->second.m_T,&(pVal->first));


   CComPtr<ITemporaryPierItem> item = pVal->second.m_T;
   CTemporaryPierItem* pItem = dynamic_cast<CTemporaryPierItem*>(item.p);
   pItem->SetBridge(m_pBridge);

   Fire_OnTemporaryPierItemAdded(pVal->first);

   return S_OK;
}

HRESULT CTemporaryPierItemCollection::OnBeforeRemove( StoredType* pVal )
{
   Unadvise(pVal->second.m_T,pVal->first);

   return S_OK;
}

HRESULT CTemporaryPierItemCollection::OnAfterRemove(IDType id)
{
   Fire_OnTemporaryPierItemRemoved(id);
   return S_OK;
}

/////////////////////////////////////////////////////////////////////
// ITemporaryPierItemCollection

STDMETHODIMP CTemporaryPierItemCollection::Add(IDType id,Float64 location,BSTR bstrReleaseStage)
{
   CComPtr<IStageCollection> stages;
   m_pBridge->get_Stages(&stages);

   CComPtr<IStage> stage;
   stages->Find(bstrReleaseStage,&stage);
   if ( stage == NULL )
      return Error(IDS_E_STAGE_NOT_FOUND,IID_ITemporaryPierItemCollection,GB_E_STAGE_NOT_FOUND);

   CComObject<CTemporaryPierItem>* ptpi;
   CComObject<CTemporaryPierItem>::CreateInstance(&ptpi);
   ptpi->Init(id,location,bstrReleaseStage);
   CComPtr<ITemporaryPierItem> tpi = ptpi;

   return PersistentTPICollImpl::Add(tpi);
}

STDMETHODIMP CTemporaryPierItemCollection::RemoveByIndex(CollectionIndexType index)
{
   IDType id;
   return PersistentTPICollImpl::RemoveByIndex(index,&id);
}

STDMETHODIMP CTemporaryPierItemCollection::RemoveByID(IDType id)
{
   return PersistentTPICollImpl::RemoveByID(id);
}

STDMETHODIMP CTemporaryPierItemCollection::Clear()
{
   return PersistentTPICollImpl::Clear();
}

STDMETHODIMP CTemporaryPierItemCollection::Find(IDType id,ITemporaryPierItem** pVal)
{
   return PersistentTPICollImpl::Find(id,pVal);
}

STDMETHODIMP CTemporaryPierItemCollection::get__EnumTemporaryPierItems(IEnumTemporaryPierItems* *enumTemporaryPierItems)
{
   return get__EnumElements(enumTemporaryPierItems);
}

////////////////////////////////////////////////////////////////////////
HRESULT CTemporaryPierItemCollection::DoSaveItem(IStructuredSave2* save,ITemporaryPierItem* item)
{
   CComQIPtr<IStructuredStorage2> ssTPI(item);
   return ssTPI->Save(save);
}

HRESULT CTemporaryPierItemCollection::DoLoadItem(IStructuredLoad2* load,ITemporaryPierItem* *ppItem)
{
   CComObject<CTemporaryPierItem>* ptpi;
   CComObject<CTemporaryPierItem>::CreateInstance(&ptpi);
   CComPtr<ITemporaryPierItem> tpi = ptpi;

   CComQIPtr<IStructuredStorage2> ssTPI(tpi);
   HRESULT hr = ssTPI->Load(load);
   if ( FAILED(hr) )
      return hr;

   (*ppItem) = tpi;
   (*ppItem)->AddRef();

   return S_OK;
}
