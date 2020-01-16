///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

void CJointLoadCollection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents, pLoading);  // for C++ event handlers
}

STDMETHODIMP CJointLoadCollection::Create(/*[in]*/LoadIDType id,  /*[in]*/JointIDType jointID, /*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz, /*[out, retval]*/ IFem2dJointLoad** ppJointLoad)
{
   CHECK_RETOBJ(ppJointLoad);
   HRESULT hr = E_FAIL;

   // see if a joint load with our id already exists
   ContainerIteratorType it = m_coll.find(id);
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CJointLoadCollection, &CLSID_Fem2dJointLoadCollection>::Error(IDS_E_JOINT_LOAD_WITH_ID_ALREADY_EXISTS, IDH_E_JOINT_LOAD_WITH_ID_ALREADY_EXISTS, GetHelpFile(), IID_IFem2dJointLoad, FEM2D_E_JOINT_LOAD_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new joint load
      CComObject<CJointLoad>* pjnt;
      hr = CComObject<CJointLoad>::CreateInstance( &pjnt );
      if (FAILED(hr))
         return hr;

      *ppJointLoad = pjnt;
      (*ppJointLoad)->AddRef(); // for client

      pjnt->Init(m_pModel, m_pEvents, m_pLoading, id, jointID, Fx, Fy, Mz);

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
   }

	return hr;
}

STDMETHODIMP CJointLoadCollection::Remove(CollectionIndexType IDorIndex, Fem2dAccessType AccessMethod, LoadIDType* pid)
{
   HRESULT hr = JointLoadCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
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