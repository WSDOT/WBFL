///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2016  Washington State Department of Transportation
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
// DistributedLoadCollection.cpp : Implementation of CDistributedLoadCollection
#include "stdafx.h"
#include "DistributedLoadCollection.h"
#include "DistributedLoad.h"
#include "ModelEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDistributedLoadCollection

STDMETHODIMP CDistributedLoadCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dDistributedLoadCollection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CDistributedLoadCollection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading)
{
   ATLASSERT(pLoading!=0);
   m_pLoading = pLoading;

   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent, pEvents, pLoading);  // for C++ event handlers
}

STDMETHODIMP CDistributedLoadCollection::Create(/*[in]*/LoadIDType id, /*[in]*/MemberIDType memberID, /*[in]*/Fem2dLoadDirection direction, /*[in]*/Float64 startLocation,/*[in]*/Float64 endLocation, /*[in]*/Float64 Wstart, /*[in]*/Float64 Wend, /*[in,optional,defaultvalue(lotMember)]*/ Fem2dLoadOrientation orientation,/*[out, retval]*/ IFem2dDistributedLoad** ppDistributedLoad)
{
   CHECK_RETOBJ(ppDistributedLoad);
   HRESULT hr = E_FAIL;

   // see if a load with our id already exists
   ContainerIteratorType it( m_coll.find(id) );
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CDistributedLoadCollection, &CLSID_Fem2dDistributedLoadCollection>::Error(IDS_E_DIST_LOAD_WITH_ID_ALREADY_EXISTS, IDH_E_DIST_LOAD_WITH_ID_ALREADY_EXISTS, GetHelpFile(), IID_IFem2dDistributedLoadCollection, FEM2D_E_DIST_LOAD_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new load
      CComObject<CDistributedLoad>* pdl;
      hr = CComObject<CDistributedLoad>::CreateInstance( &pdl );
      if (FAILED(hr))
         return hr;

      *ppDistributedLoad = pdl;
      (*ppDistributedLoad)->AddRef(); // for client

      pdl->Init(m_pModel, m_pEvents, m_pLoading, id, memberID, direction, startLocation, endLocation, Wstart, Wend, orientation);

      // insert new 
      std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(id, *ppDistributedLoad)) );
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
         return E_FAIL;
      }

      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnDistributedLoadAdded(id,loadingID);
   }

	return hr;
}

STDMETHODIMP CDistributedLoadCollection::Remove(CollectionIndexType IDorIndex, Fem2dAccessType AccessMethod, LoadIDType* pid)
{
   HRESULT hr = DistributedLoadCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      // send event up the pipe
      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnDistributedLoadRemoved(*pid, loadingID);
   }

   return hr;
}

STDMETHODIMP CDistributedLoadCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = DistributedLoadCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         // send event up the pipe
         LoadCaseIDType loadingID;
         m_pLoading->get_ID(&loadingID);
         m_pEvents->OnDistributedLoadsCleared(loadingID);
      }
      return hr;
   }
   else
      return S_OK;
}