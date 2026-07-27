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

// MemberCollection.cpp : Implementation of CMemberCollection
#include "stdafx.h"
#include "MemberCollection.h"
#include "Member.h"
#include "ModelEvents.h"


/////////////////////////////////////////////////////////////////////////////
// CMemberCollection

STDMETHODIMP CMemberCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dMemberCollection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CMemberCollection::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::Model* pCoreModel)
{
   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents,pCoreModel);  // have to save to get at C++ event handlers
}

void CMemberCollection::AdoptCore(WBFL::FEA2D::Member* pCore)
{
   ATLASSERT(pCore!=0);

   CComObject<CMember>* pmbr;
   HRESULT hr = CComObject<CMember>::CreateInstance( &pmbr );
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IFem2dMember> item(pmbr);

   pmbr->OnCreate(m_pModel, m_pEvents, pCore);

   std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(pCore->GetID(), item)) );
   ATLASSERT(st.second);
}

STDMETHODIMP CMemberCollection::Create(MemberIDType id, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI, IFem2dMember **ppMember)
{
   CHECK_RETOBJ(ppMember);

   if (EA<0.0)
      return E_INVALIDARG;

   if (EI<0.0)
      return E_INVALIDARG;

   WBFL::FEA2D::Member* pCore;
   try
   {
      pCore = &m_pCoreModel->CreateMember(id, startJoint, endJoint, EA, EI);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      if (ex.GetReasonCode() == WBFL::FEA2D::ReasonCode::MemberHasSameJoints)
      {
         return DuplicateJointError(id);
      }
      return ReportFem2dError(ex, CLSID_Fem2dMemberCollection, IID_IFem2dMember);
   }

   // create the COM wrapper
   CComObject<CMember>* pmbr;
   HRESULT hr = CComObject<CMember>::CreateInstance( &pmbr );
   if (FAILED(hr))
      return hr;

   *ppMember = pmbr;
   (*ppMember)->AddRef(); // for client

   pmbr->OnCreate(m_pModel,m_pEvents,pCore);

   // insert new member
   std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(id, *ppMember)) );
   if (!st.second)
   {
      ATLASSERT(false); // insert failed - better check why
      return E_POINTER;
   }

   m_pEvents->OnMemberAdded(id);

	return S_OK;
}

STDMETHODIMP CMemberCollection::Remove(IndexType IDorIndex, Fem2dAccessType AccessMethod, MemberIDType* pid)
{
   HRESULT hr = MemberCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      m_pCoreModel->RemoveMember(*pid);

      // send event up the pipe
      m_pEvents->OnMemberRemoved(*pid);
   }

   return hr;
}

STDMETHODIMP CMemberCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = MemberCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         m_pCoreModel->ClearMembers();

         // send event up the pipe
         m_pEvents->OnMembersCleared();
      }
      return hr;
   }

   return S_OK;
}

HRESULT CMemberCollection::DuplicateJointError(JointIDType id)
{
   CComBSTR msg(::CreateErrorMsg1(IDS_E_MEMBER_HAS_SAME_JOINTS, id));
   return CComCoClass<CMemberCollection, &CLSID_Fem2dMemberCollection>::Error(msg, IDH_E_MEMBER_HAS_SAME_JOINTS, GetHelpFile(), IID_IFem2dMember, FEM2D_E_MEMBER_HAS_SAME_JOINTS);
}
