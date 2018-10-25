///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// PierCollection.cpp : Implementation of CPierCollection
#include "stdafx.h"
#include "WBFLGenericBridge.H"
#include "GenericBridgeImpl.h"
#include "PierCollection.h"
#include "Pier.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPierCollection

void CPierCollection::FinalRelease()
{
   Clear(); // Forces all of the pier objects to be unadvised
}

void CPierCollection::SetBridge(IGenericBridge* bridge)
{
   m_pBridge = bridge;

   CComPtr<IEnumPiers> enumPiers;
   get__EnumPiers(&enumPiers);
   CComPtr<IPier> pier;
   while ( enumPiers->Next(1,&pier,NULL) != S_FALSE )
   {
      dynamic_cast<CPier*>(pier.p)->SetBridge(bridge);
      pier.Release();
   };
}

STDMETHODIMP CPierCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPierCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPierCollection::OnBeforeAdd( StoredType* pVal)
{
   return S_OK;
}

HRESULT CPierCollection::OnAfterAdd(StoredType* pVal, PierIndexType index)
{
   // Set up event sink
   DWORD dwCookie;
   HRESULT hr = Advise(pVal->second.m_T,&dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   pVal->first = dwCookie;

   CPier* pPier = dynamic_cast<CPier*>((pVal->second.m_T).p);
   pPier->SetBridge(m_pBridge);

   if ( m_bFireEvent )
      Fire_OnPierAdded(pVal->second.m_T);

   return S_OK;
}

HRESULT CPierCollection::OnBeforeRemove( StoredType* pVal, PierIndexType index)
{
   DWORD dwCookie = pVal->first;
   CComPtr<IPier> pier(pVal->second.m_T);
   HRESULT hr = Unadvise(pier,dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   CPier* pPier = dynamic_cast<CPier*>((pVal->second.m_T).p);
   pPier->SetBridge(NULL);

   return S_OK;
}

HRESULT CPierCollection::OnAfterRemove(PierIndexType index)
{
   Fire_OnPierRemoved(index);
   return S_OK; 
}

HRESULT CPierCollection::OnBeforeReplace( StoredType* pVal, PierIndexType index)
{
   return OnBeforeRemove(pVal,index);
}

HRESULT CPierCollection::OnAfterReplace( StoredType* pVal, PierIndexType index)
{
   return OnAfterAdd(pVal,index);
}

HRESULT CPierCollection::InsertQuietly(PierIndexType index, IPier* pier)
{
   m_bFireEvent = FALSE; // Don't fire the OnPierAdded event
   HRESULT hr = Insert(index,pier);
   m_bFireEvent = TRUE; // Turn events back on
   return hr;
}

STDMETHODIMP CPierCollection::Clone(IPierCollection* *clone)
{
   // Performes a deep copy
   CHECK_RETVAL(clone);

   CComObject<CPierCollection> *pClone;
   CComObject<CPierCollection>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      StoredType* st = *iter;

      // Casting because Clone is current not on the COM interface
      CPier* pPier = dynamic_cast<CPier*>(st->second.m_T.p);
      
      CComPtr<IPier> pierClone;
      pPier->Clone(&pierClone);

      pClone->Add(pierClone);
   }

   return S_OK;
}

PierIndexType CPierCollection::GetPierIndex(IPier* pier)
{
   PierIndexType idx = 0;
   iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      StoredType* st = *iter;
      if ( st->second.m_T.IsEqualObject(pier) )
         return idx;

      idx++;
   }

   ATLASSERT( iter != end() ); // Pier wasn't found
   return ALL_PIERS;
}

void CPierCollection::RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName)
{
   // The name of a stage changed... update the references
	for(iterator it= begin(); it!=end(); it++)
   {
      CComPtr<IPier> pier = it->second.m_T;
      CPier* pPier = dynamic_cast<CPier*>(pier.p);

      pPier->RenameStageReferences(bstrOldName,bstrNewName);
   }
}

void CPierCollection::AddDataForStage(BSTR bstrName)
{
   // Notify each pier of the new stage
	for(iterator it= begin(); it!=end(); it++)
   {
      CComPtr<IPier> pier = it->second.m_T;
      CPier* pPier = dynamic_cast<CPier*>(pier.p);

      pPier->AddDataForStage(bstrName);
   }
}

void CPierCollection::RemoveDataForStage(BSTR bstrName)
{
   // Notify each pier that a stage has been removed
	for(iterator it= begin(); it!=end(); it++)
   {
      CComPtr<IPier> pier = it->second.m_T;
      CPier* pPier = dynamic_cast<CPier*>(pier.p);

      pPier->RemoveDataForStage(bstrName);
   }
}

HRESULT CPierCollection::Advise(IPier* pier,DWORD* pdwCookie)
{
   CComPtr<IPier> pCP(pier);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_IPierEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with Pier object\n");
      return hr;
   }

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CPierCollection::Unadvise(IPier* pier,DWORD dwCookie)
{
   ATLASSERT(pier != 0);

   //
   // Disconnection from connection point
   //

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( pier );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IPierEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));
   return hr;
}

STDMETHODIMP CPierCollection::get__EnumPiers(IEnumPiers* *enumPiers)
{
   return get__EnumElements(enumPiers);
}

STDMETHODIMP CPierCollection::CopyTo(PierIndexType fromIdx, PierIndexType toIdx)
{
   PierIndexType nPiers;
   get_Count(&nPiers);

   if ( fromIdx < 0 || nPiers <= fromIdx )
      return E_INVALIDARG;

   if ( toIdx < 0 || nPiers <= toIdx )
      return E_INVALIDARG;

   // Save the station of the original pier
   CComPtr<IPier> originalPier;
   get_Item(toIdx,&originalPier);
   CComPtr<IStation> objStation;
   originalPier->get_Station(&objStation);
   Float64 station;
   objStation->get_Value(&station);

   CComPtr<IPier> fromPier;
   get_Item(fromIdx,&fromPier);

   CPier* pFromPier = dynamic_cast<CPier*>(fromPier.p);
   CComPtr<IPier> clonePier;
   pFromPier->Clone(&clonePier);

   objStation.Release();
   clonePier->get_Station(&objStation);
   objStation->put_Value(station);

   putref_Item(toIdx,clonePier);

   // Make sure the span/pier linkage is up to date
   CGenericBridge* pBridge = dynamic_cast<CGenericBridge*>(m_pBridge);
   pBridge->LinkSpansAndPiers();

   // The container framework handles the event firing!!!

   return S_OK;
}

STDMETHODIMP CPierCollection::get_PierIndex(IPier* pier,PierIndexType* index)
{
   CHECK_IN(pier);
   CHECK_RETVAL(index);

   (*index) = GetPierIndex(pier);
   return ( (*index) == ALL_PIERS ) ? S_FALSE : S_OK;
}

/////////////////////////////////////////////////////////////
STDMETHODIMP CPierCollection::Load(IStructuredLoad2 *pload)
{
   m_LoadedPierCount = 0;

   HRESULT hr = PersistentPierCollection::Load(pload);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

HRESULT CPierCollection::DoSaveItem(IStructuredSave2* save,IPier* item)
{
   CComQIPtr<IStructuredStorage2> ss(item);
   HRESULT hr = ss->Save(save);

   return hr;
}

HRESULT CPierCollection::DoLoadItem(IStructuredLoad2* load,IPier* *ppItem)
{
   CComVariant var;

   load->get_Property(CComBSTR("Linked"),&var);
   if ( var.boolVal == VARIANT_TRUE )
   {
      long sourceIndex;
      load->get_Property(CComBSTR("LinkSourceIndex"),&var);
      sourceIndex = var.lVal;

      m_LinkData.push_back( std::make_pair(m_LoadedPierCount++,sourceIndex) );
   }

   CComObject<CPier>* pPier;
   CComObject<CPier>::CreateInstance(&pPier);
   CComPtr<IPier> pier = pPier;

   ATLASSERT(m_pBridge != NULL);
   pPier->SetBridge(m_pBridge);

   CComQIPtr<IStructuredStorage2> ss(pier);
   HRESULT hr = ss->Load(load);
   if ( FAILED(hr) )
      return hr;

   (*ppItem) = pier;
   (*ppItem)->AddRef();

   return S_OK;
}


//#if defined _DEBUG
//void CPierCollection::Dump(CDumpContext& ctx)
//{
//   ctx << "Pier Collection Dump\n";
//   iterator iter;
//   long count = 0;
//   for ( iter = begin(); iter != end(); iter++, count++ )
//   {
//      StoredType* st = *iter;
//      IPier* pier = st->second.m_T;
//      CComPtr<IStation> objStation;
//      pier->get_Station(&objStation);
//     
//      Float64 station;
//      objStation->get_Value(&station);
//
//      ctx << "Pier " << (count+1) << " Station " << station << "\n";
//   }
//}
//#endif // _DEBUG
