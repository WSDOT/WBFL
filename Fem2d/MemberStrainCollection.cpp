///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2022  Washington State Department of Transportation
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
// MemberStrainCollection.cpp : Implementation of CMemberStrainCollection
#include "stdafx.h"
#include "MemberStrainCollection.h"
#include "MemberStrain.h"
#include "ModelEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemberStrainCollection

STDMETHODIMP CMemberStrainCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dMemberStrainCollection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CMemberStrainCollection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading)
{
   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents,pLoading);  // for C++ event handlers
}

STDMETHODIMP CMemberStrainCollection::Create(/*[in]*/LoadIDType id,  /*[in]*/MemberIDType memberID, /*[in]*/Float64 start,/*[in]*/ Float64 end,/*[in]*/Float64 axialStrain, /*[in]*/Float64 curvatureStrain, /*[out, retval]*/ IFem2dMemberStrain** ppMemberStrain)
{
   CHECK_RETOBJ(ppMemberStrain);
   HRESULT hr = E_FAIL;

   // see if a joint load with our id already exists
   ContainerIteratorType it( m_coll.find(id) );
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CMemberStrainCollection, &CLSID_Fem2dMemberStrainCollection>::Error(IDS_E_MEMBER_STRAIN_WITH_ID_ALREADY_EXISTS, IDH_E_MEMBER_STRAIN_WITH_ID_ALREADY_EXISTS, GetHelpFile(), IID_IFem2dMemberStrain, FEM2D_E_MEMBER_STRAIN_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new joint load
      CComObject<CMemberStrain>* pstrn;
      hr = CComObject<CMemberStrain>::CreateInstance( &pstrn );
      if (FAILED(hr))
         return hr;

      *ppMemberStrain = pstrn;
      (*ppMemberStrain)->AddRef(); // for client

      pstrn->Init(m_pModel, m_pEvents, m_pLoading, id, memberID, start, end, axialStrain, curvatureStrain);

      // insert new load
      std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(id, *ppMemberStrain )) );
      if (!st.second)
      {
         ATLASSERT(false); // insert failed - better check why
         return E_FAIL;
      }

      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnMemberStrainAdded(id,loadingID);
   }

	return hr;
}

STDMETHODIMP CMemberStrainCollection::Remove(CollectionIndexType IDorIndex, Fem2dAccessType AccessMethod, LoadIDType* pid)
{
   HRESULT hr = MemberStrainCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      // send event up the pipe
      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnMemberStrainRemoved(*pid, loadingID);
   }

   return hr;
}

STDMETHODIMP CMemberStrainCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = MemberStrainCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         // send event up the pipe
         LoadCaseIDType loadingID;
         m_pLoading->get_ID(&loadingID);
         m_pEvents->OnMemberStrainsCleared(loadingID);
      }
      return hr;
   }
   else
      return S_OK;
}