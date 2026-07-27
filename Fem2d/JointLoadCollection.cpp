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
// JointLoadCollection.cpp : Implementation of CJointLoadCollection
#include "stdafx.h"
#include "JointLoadCollection.h"
#include "JointLoad.h"
#include "ModelEvents.h"


/////////////////////////////////////////////////////////////////////////////
// CJointLoadCollection

STDMETHODIMP CJointLoadCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dJointLoadCollection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CJointLoadCollection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::Loading* pCoreLoading)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents, pLoading, pCoreLoading);  // for C++ event handlers
}

void CJointLoadCollection::AdoptCore(WBFL::FEA2D::JointLoad* pCore)
{
   ATLASSERT(pCore!=0);

   CComObject<CJointLoad>* pjnt;
   HRESULT hr = CComObject<CJointLoad>::CreateInstance( &pjnt );
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IFem2dJointLoad> item(pjnt);

   pjnt->Init(m_pModel, m_pEvents, m_pLoading, pCore);

   std::pair<ContainerIteratorType,bool> st;
   st = m_coll.insert(ContainerValueType(pCore->GetID(), item ));
   ATLASSERT(st.second);
}

STDMETHODIMP CJointLoadCollection::Create(/*[in]*/LoadIDType id,  /*[in]*/JointIDType jointID, /*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz, /*[out, retval]*/ IFem2dJointLoad** ppJointLoad)
{
   CHECK_RETOBJ(ppJointLoad);

   WBFL::FEA2D::JointLoad* pCore;
   try
   {
      pCore = &m_pCoreLoading->CreateJointLoad(id, jointID, Fx, Fy, Mz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dJointLoadCollection, IID_IFem2dJointLoad);
   }

   // create the COM wrapper
   CComObject<CJointLoad>* pjnt;
   HRESULT hr = CComObject<CJointLoad>::CreateInstance( &pjnt );
   if (FAILED(hr))
      return hr;

   *ppJointLoad = pjnt;
   (*ppJointLoad)->AddRef(); // for client

   pjnt->Init(m_pModel, m_pEvents, m_pLoading, pCore);

   // insert new joint
   std::pair<ContainerIteratorType,bool> st;
   st = m_coll.insert(ContainerValueType(id, *ppJointLoad ));
   if (!st.second)
   {
      ATLASSERT(false); // insert failed - better check why
      return E_FAIL;
   }

   LoadCaseIDType loadingID;
   m_pLoading->get_ID(&loadingID);
   m_pEvents->OnJointLoadAdded(id,loadingID);

	return S_OK;
}

STDMETHODIMP CJointLoadCollection::Remove(IndexType IDorIndex, Fem2dAccessType AccessMethod, LoadIDType* pid)
{
   HRESULT hr = JointLoadCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      m_pCoreLoading->RemoveJointLoad(*pid);

      // send event up the pipe
      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnJointLoadRemoved(*pid, loadingID);
   }

   return hr;
}

STDMETHODIMP CJointLoadCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = JointLoadCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         m_pCoreLoading->ClearJointLoads();

         // send event up the pipe
         LoadCaseIDType loadingID;
         m_pLoading->get_ID(&loadingID);
         m_pEvents->OnJointLoadsCleared(loadingID);
      }
      return hr;
   }
   else
      return S_OK;
}
