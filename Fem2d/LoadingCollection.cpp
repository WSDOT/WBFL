///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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
// LoadingCollection.cpp : Implementation of CLoadingCollection
#include "stdafx.h"
#include "LoadingCollection.h"
#include "Loading.h"
#include "ModelEvents.h"


/////////////////////////////////////////////////////////////////////////////
// CLoadingCollection

STDMETHODIMP CLoadingCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dLoadingCollection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CLoadingCollection::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::Model* pCoreModel)
{
   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents,pCoreModel);  // for C++ event handlers
}

CLoading* CLoadingCollection::AdoptCore(WBFL::FEA2D::Loading* pCore)
{
   ATLASSERT(pCore!=0);

   CComObject<CLoading>* ploading;
   HRESULT hr = CComObject<CLoading>::CreateInstance( &ploading );
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IFem2dLoading> item(ploading);

   hr = ploading->OnCreate(m_pModel, m_pEvents, pCore);
   ATLASSERT(SUCCEEDED(hr));

   std::pair<ContainerIteratorType,bool> st ( m_coll.insert(ContainerValueType(pCore->GetID(), item)) );
   ATLASSERT(st.second);

   return ploading;
}

STDMETHODIMP CLoadingCollection::Create(/*[in]*/LoadCaseIDType id,IFem2dLoading* *ppLoading)
{
   CHECK_RETOBJ(ppLoading);

   WBFL::FEA2D::Loading* pCore;
   try
   {
      pCore = &m_pCoreModel->CreateLoading(id);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dLoadingCollection, IID_IFem2dLoading);
   }

   // create the COM wrapper
   CComObject<CLoading>* ploading;
   HRESULT hr = CComObject<CLoading>::CreateInstance( &ploading );
   if (FAILED(hr))
      return hr;

   *ppLoading = ploading;
   (*ppLoading)->AddRef(); // for client

   hr = ploading->OnCreate(m_pModel,m_pEvents, pCore);
   if (FAILED(hr))
      return hr;

   // insert new joint
   std::pair<ContainerIteratorType,bool> st ( m_coll.insert(ContainerValueType(id, *ppLoading)) );
   if (!st.second)
   {
      ATLASSERT(false); // insert failed - better check why
      return E_FAIL;
   }

   m_pEvents->OnLoadingAdded(id);

	return S_OK;
}

STDMETHODIMP CLoadingCollection::Remove(IndexType IDorIndex, Fem2dAccessType AccessMethod, LoadCaseIDType* pid)
{
   HRESULT hr = LoadingCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      m_pCoreModel->RemoveLoading(*pid);

      // send event up the pipe
      m_pEvents->OnLoadingRemoved(*pid);
   }

   return hr;
}

STDMETHODIMP CLoadingCollection::RemoveIDLessThan(LoadCaseIDType idMax)
{
   // erase if id < idMax
   ContainerType::iterator it(m_coll.begin());
   ContainerType::iterator itend(m_coll.end());
   while(it!=itend)
   {
      LoadCaseIDType id = it->first;
      if (id < idMax)
      {
         // Release element before erasing it
         it->second.Release();
         it = m_coll.erase(it);

         m_pCoreModel->RemoveLoading(id);

         // send event up the pipe
         m_pEvents->OnLoadingRemoved(id);
      }
      else
      {
         it++;
      }
   }

   return S_OK;
}

STDMETHODIMP CLoadingCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = LoadingCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         m_pCoreModel->ClearLoadings();

         // send event up the pipe
         m_pEvents->OnLoadingsCleared();
      }
      return hr;
   }

   return S_OK;
}
