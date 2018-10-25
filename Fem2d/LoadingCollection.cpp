///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

void CLoadingCollection::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents)
{
   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents);  // for C++ event handlers
}

STDMETHODIMP CLoadingCollection::Create(/*[in]*/LoadCaseIDType id,IFem2dLoading* *ppLoading)
{
   CHECK_RETOBJ(ppLoading);
   HRESULT hr = E_FAIL;

   // see if a joint load with our id already exists
   ContainerIteratorType it( m_coll.find(id) );
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CLoadingCollection, &CLSID_Fem2dLoadingCollection>::Error(IDS_E_LOADING_WITH_ID_ALREADY_EXISTS, IDH_E_LOADING_WITH_ID_ALREADY_EXISTS, GetHelpFile(), IID_IFem2dLoading, FEM2D_E_LOADING_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new loading
      CComObject<CLoading>* ploading;
      hr = CComObject<CLoading>::CreateInstance( &ploading );
      if (FAILED(hr))
         return hr;

      *ppLoading = ploading;
      (*ppLoading)->AddRef(); // for client

      hr = ploading->OnCreate(m_pModel,m_pEvents, id);
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
   }

	return hr;
}

STDMETHODIMP CLoadingCollection::Remove(CollectionIndexType IDorIndex, Fem2dAccessType AccessMethod, LoadCaseIDType* pid)
{
   HRESULT hr = LoadingCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
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
         // send event up the pipe
         m_pEvents->OnLoadingsCleared();
      }
      return hr;
   }

   return S_OK;
}