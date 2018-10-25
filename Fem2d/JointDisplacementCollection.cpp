///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2012  Washington State Department of Transportation
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
// JointDisplacementCollection.cpp : Implementation of CJointDisplacementCollection
#include "stdafx.h"
#include "JointDisplacementCollection.h"
#include "JointDisplacement.h"
#include "ModelEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJointDisplacementCollection

STDMETHODIMP CJointDisplacementCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dJointDisplacementCollection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CJointDisplacementCollection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents,pLoading);
}

STDMETHODIMP CJointDisplacementCollection::Create(/*[in]*/LoadIDType id,  /*[in]*/JointIDType jointID, /*[in]*/Float64 Dx, /*[in]*/Float64 Dy, /*[in]*/Float64 Rz, /*[out, retval]*/ IFem2dJointDisplacement** ppJointDisplacement)
{
   CHECK_RETOBJ(ppJointDisplacement);
   HRESULT hr = E_FAIL;

   // see if a joint load with our id already exists
   ContainerIteratorType it = m_coll.find(id);
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CJointDisplacementCollection, &CLSID_Fem2dJointDisplacementCollection>::Error(IDS_E_JOINT_DISP_WITH_ID_ALREADY_EXISTS, IDH_E_JOINT_DISP_WITH_ID_ALREADY_EXISTS,GetHelpFile(), IID_IFem2dJointDisplacement, FEM2D_E_JOINT_DISP_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new joint load
      CComObject<CJointDisplacement>* pjnt;
      hr = CComObject<CJointDisplacement>::CreateInstance( &pjnt );
      if (FAILED(hr))
         return hr;

      *ppJointDisplacement = pjnt;
      (*ppJointDisplacement)->AddRef(); // for client

      pjnt->Init(m_pModel, m_pEvents, m_pLoading, id, jointID, Dx, Dy, Rz);

      // insert new joint
      std::pair<ContainerIteratorType,bool> st;
      st = m_coll.insert(ContainerValueType(id, CComVariant(*ppJointDisplacement)));
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
         return E_FAIL;
      }

      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnJointDisplacementAdded(id,loadingID);
   }

	return hr;
}

STDMETHODIMP CJointDisplacementCollection::Remove(CollectionIndexType IDorIndex, Fem2dAccessType AccessMethod, LoadIDType* pid)
{
   HRESULT hr = JointDisplacementCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      // send event up the pipe
      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnJointDisplacementRemoved(*pid, loadingID);
   }

   return hr;
}

STDMETHODIMP CJointDisplacementCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = JointDisplacementCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         // send event up the pipe
         LoadCaseIDType loadingID;
         m_pLoading->get_ID(&loadingID);
         m_pEvents->OnJointDisplacementsCleared(loadingID);
      }
      return hr;
   }
   else
      return S_OK;
}