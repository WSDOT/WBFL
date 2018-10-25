///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// StageCollection.cpp : Implementation of CStageCollection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "StageCollection.h"
#include "Stage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageCollection

void CStageCollection::FinalRelease()
{
   Clear(); // Causes all of the Stage object to be Unadvised.
}

void CStageCollection::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge;

   CComPtr<IEnumStages> enumStages;
   get__EnumStages(&enumStages);

   CComPtr<IStage> stage;
   while ( enumStages->Next(1,&stage,NULL) != S_FALSE )
   {
      CStage* pStage = dynamic_cast<CStage*>(stage.p);
      pStage->SetBridge(m_pBridge);
      stage.Release();
   }
}

STDMETHODIMP CStageCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStageCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CStageCollection::Advise(IStage* stage,DWORD* pdwCookie)
{
   CComPtr<IStage> pCP(stage);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_IStageEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with Stage object\n");
      return hr;
   }

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CStageCollection::Unadvise(IStage* stage,DWORD dwCookie)
{
   ATLASSERT(stage != 0);

   //
   // Disconnection from connection point
   //

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( stage );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IStageEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));
   return hr;
}

STDMETHODIMP CStageCollection::Clone(IStageCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CStageCollection>* pClone;
   CComObject<CStageCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IEnumStages> enumStages;
   get__EnumStages(&enumStages);

   CComPtr<IStage> stage;
   while ( enumStages->Next(1,&stage,NULL) != S_FALSE )
   {
      CStage* pStage = dynamic_cast<CStage*>(stage.p);
      CComPtr<IStage> cloneStage;
      pStage->Clone(&cloneStage);

      pClone->Add(cloneStage);

      stage.Release();
   }

   return S_OK;
}

STDMETHODIMP CStageCollection::CreateStage( BSTR name, BSTR description)
{
   return CreateStageAt(name,description,-1); // -1 = create at end
}

STDMETHODIMP CStageCollection::CreateStageAt(BSTR bstrName, BSTR bstrDescription, CollectionIndexType pos)
{
   // validate data...
   if ( bstrName == NULL || CComBSTR(bstrName) == CComBSTR("") )
      return E_INVALIDARG;

   CComPtr<IStage> sameName;
   Find(bstrName,&sameName);
   if ( sameName != NULL )
   {
      return Error(IDS_E_DUPLICATENAME,IID_IStageCollection,GB_E_DUPLICATENAME);
   }

   CComObject<CStage>* pStage;
   CComObject<CStage>::CreateInstance(&pStage);
   CComPtr<IStage> stage;
   stage = pStage;

   pStage->Init(bstrName,bstrDescription);
   pStage->SetBridge(m_pBridge);

   if ( pos == INVALID_INDEX )
      return Add(stage);
   else
      return Insert(pos,stage);
}

STDMETHODIMP CStageCollection::MoveStage(CollectionIndexType fromPos,CollectionIndexType toPos)
{
   return MoveTo(fromPos,toPos);
}

STDMETHODIMP CStageCollection::RemoveByIndex(CollectionIndexType index)
{
   return PersistentStageCollImpl::Remove(index);
}

STDMETHODIMP CStageCollection::RemoveByName(BSTR name)
{
   long idx = 0;

   CComBSTR tname(name);
   iterator it;
   for (it = begin(); it != end(); it++)
   {
      CComBSTR bnam;
      HRESULT hr = it->second.m_T->get_Name(&bnam);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }

      if ( tname == bnam )
      {
         break;
      }

      idx++;
   }

   if ( it == end() )
      return Error(IDS_E_STAGE_NOT_FOUND,IID_IStageCollection,GB_E_STAGE_NOT_FOUND);

   return RemoveByIndex(idx);
}

STDMETHODIMP CStageCollection::Find(BSTR name,IStage* *stage)
{
   CHECK_RETOBJ(stage);
   (*stage) = NULL;

   CComBSTR tname(name);
   for (iterator it = begin(); it != end(); it++)
   {
      CComBSTR bnam;
      HRESULT hr = it->second.m_T->get_Name(&bnam);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }

      if ( tname == bnam )
      {
         (*stage) = it->second.m_T;
         (*stage)->AddRef();
         return S_OK;
      }
   }

   return Error(IDS_E_STAGE_NOT_FOUND,IID_IStageCollection,GB_E_STAGE_NOT_FOUND);
}

STDMETHODIMP CStageCollection::get__EnumStages(IEnumStages* *enumStages)
{
   return get__EnumElements(enumStages);
}

STDMETHODIMP CStageCollection::Compare(BSTR name1,BSTR name2,long* cmp)
{
   // Return S_FALSE if name1 or name2 is not a stage... cmp is undefined in this case
   // Return -1 if name1 comes before name2, 1 if name1 comes after name2, and
   // 0 if name1 and name2 are the same stage or not a stage at all
   CHECK_RETVAL(cmp);
   CHECK_IN(name1);
   CHECK_IN(name2);

   long idx1 = -1;
   long idx2 = -1;
   long index = 0;
   for (iterator it = begin(); it != end(); it++, index++)
   {
      CComBSTR name;
      it->second.m_T->get_Name(&name);

      if ( CComBSTR(name1) == name )
         idx1 = index;

      if ( CComBSTR(name2) == name )
         idx2 = index;
   }

   if (idx1 == -1 || idx2 == -1 )
   {
      *cmp = 0;
      return S_FALSE;
   }

   if ( idx1 < idx2 )
      *cmp = -1;
   else if ( idx2 < idx1 )
      *cmp = 1;
   else if ( idx1 == idx2 )
      *cmp = 0;
      

   return S_OK;

}

HRESULT CStageCollection::OnAfterAdd( StoredType* pVal, StageIndexType index)
{
   Advise(pVal->second.m_T,&(pVal->first));

   CStage* pStage = dynamic_cast<CStage*>(pVal->second.m_T.p);
   pStage->SetBridge(m_pBridge);

   Fire_OnStageAdded(index);

   return S_OK;
}

HRESULT CStageCollection::OnBeforeRemove( StoredType* pVal, StageIndexType index)
{
   Unadvise(pVal->second.m_T,pVal->first);

   // The event for stage removal sends the name of the stage that was removed
   // The event is fired from OnAfterRemove. The stage name is not available there
   // The stage name is captured here
   pVal->second.m_T->get_Name(&m_bstrLastStageRemoved);

   CStage* pStage = dynamic_cast<CStage*>(pVal->second.m_T.p);
   pStage->SetBridge(NULL);

   return S_OK;
}

HRESULT CStageCollection::OnAfterRemove( StageIndexType index)
{
   Fire_OnStageRemoved(index,m_bstrLastStageRemoved);

   m_bstrLastStageRemoved.Empty();

   return S_OK;
}

HRESULT CStageCollection::OnAfterMoveTo( StageIndexType from, StageIndexType to)
{
   CComPtr<IStage> stage;
   get_Item(to,&stage);

   CComBSTR bstrName;
   stage->get_Name(&bstrName);

   Fire_OnStageMoved(bstrName,from,to);
   return S_OK;
}

HRESULT CStageCollection::OnAfterCopyTo( StageIndexType from, StageIndexType to)
{
   ATLASSERT(FALSE); // Should never get here CopyTo not offered on the container interface
   return S_OK;
}

HRESULT CStageCollection::OnAfterReverse()
{
   ATLASSERT(FALSE); // Should never get here Reverse not offered on the container interface
   return S_OK;
}

HRESULT CStageCollection::DoSaveItem(IStructuredSave2* save,IStage* item)
{
   CComQIPtr<IStructuredStorage2> ssStage(item);
   return ssStage->Save(save);
}

HRESULT CStageCollection::DoLoadItem(IStructuredLoad2* load,IStage* *ppItem)
{
   CComObject<CStage>* pStage;
   CComObject<CStage>::CreateInstance(&pStage);
   CComPtr<IStage> stage = pStage;

   CComQIPtr<IStructuredStorage2> ssStage(stage);
   HRESULT hr = ssStage->Load(load);
   if ( FAILED(hr) )
      return hr;

   (*ppItem) = stage;
   (*ppItem)->AddRef();
   return S_OK;
}
