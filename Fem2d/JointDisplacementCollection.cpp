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
// JointDeflectionCollection.cpp : Implementation of CJointDeflectionCollection
#include "stdafx.h"
#include "JointDisplacementCollection.h"
#include "JointDisplacement.h"
#include "ModelEvents.h"


/////////////////////////////////////////////////////////////////////////////
// CJointDeflectionCollection

STDMETHODIMP CJointDeflectionCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dJointDeflectionCollection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CJointDeflectionCollection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::Loading* pCoreLoading)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents,pLoading,pCoreLoading);
}

void CJointDeflectionCollection::AdoptCore(WBFL::FEA2D::JointDisplacement* pCore)
{
   ATLASSERT(pCore!=0);

   CComObject<CJointDeflection>* pjnt;
   HRESULT hr = CComObject<CJointDeflection>::CreateInstance( &pjnt );
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IFem2dJointDeflection> item(pjnt);

   pjnt->Init(m_pModel, m_pEvents, m_pLoading, pCore);

   std::pair<ContainerIteratorType,bool> st;
   st = m_coll.insert(ContainerValueType(pCore->GetID(), item));
   ATLASSERT(st.second);
}

STDMETHODIMP CJointDeflectionCollection::Create(/*[in]*/LoadIDType id,  /*[in]*/JointIDType jointID, /*[in]*/Float64 Dx, /*[in]*/Float64 Dy, /*[in]*/Float64 Rz, /*[out, retval]*/ IFem2dJointDeflection** ppJointDeflection)
{
   CHECK_RETOBJ(ppJointDeflection);

   WBFL::FEA2D::JointDisplacement* pCore;
   try
   {
      pCore = &m_pCoreLoading->CreateJointDisplacement(id, jointID, Dx, Dy, Rz);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dJointDeflectionCollection, IID_IFem2dJointDeflection);
   }

   // create the COM wrapper
   CComObject<CJointDeflection>* pjnt;
   HRESULT hr = CComObject<CJointDeflection>::CreateInstance( &pjnt );
   if (FAILED(hr))
      return hr;

   *ppJointDeflection = pjnt;
   (*ppJointDeflection)->AddRef(); // for client

   pjnt->Init(m_pModel, m_pEvents, m_pLoading, pCore);

   // insert new joint
   std::pair<ContainerIteratorType,bool> st;
   st = m_coll.insert(ContainerValueType(id, *ppJointDeflection));
   if (!st.second)
   {
      ATLASSERT(false); // insert failed - better check why
      return E_FAIL;
   }

   LoadCaseIDType loadingID;
   m_pLoading->get_ID(&loadingID);
   m_pEvents->OnJointDeflectionAdded(id,loadingID);

	return S_OK;
}

STDMETHODIMP CJointDeflectionCollection::Remove(IndexType IDorIndex, Fem2dAccessType AccessMethod, LoadIDType* pid)
{
   HRESULT hr = JointDeflectionCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      m_pCoreLoading->RemoveJointDisplacement(*pid);

      // send event up the pipe
      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnJointDeflectionRemoved(*pid, loadingID);
   }

   return hr;
}

STDMETHODIMP CJointDeflectionCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = JointDeflectionCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         m_pCoreLoading->ClearJointDisplacements();

         // send event up the pipe
         LoadCaseIDType loadingID;
         m_pLoading->get_ID(&loadingID);
         m_pEvents->OnJointDeflectionsCleared(loadingID);
      }
      return hr;
   }
   else
      return S_OK;
}
