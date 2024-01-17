///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2024  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

void CMemberCollection::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents)
{
   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents);  // have to save to get at C++ event handlers
}


STDMETHODIMP CMemberCollection::Create(MemberIDType id, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI, IFem2dMember **ppMember)
{
   CHECK_RETOBJ(ppMember);

   if (EA<0.0)
      return E_INVALIDARG;

   if (EI<0.0)
      return E_INVALIDARG;

   if (startJoint == endJoint)
      return DuplicateJointError(id);

   // see if a joint with our id already exists
   ContainerIteratorType it( m_coll.find(id) );
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CMemberCollection, &CLSID_Fem2dMemberCollection>::Error(IDS_E_MEMBER_WITH_ID_ALREADY_EXISTS, IDH_E_MEMBER_WITH_ID_ALREADY_EXISTS, GetHelpFile(), IID_IFem2dMember, FEM2D_E_MEMBER_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new Member
      CComObject<CMember>* pmbr;
      HRESULT hr = CComObject<CMember>::CreateInstance( &pmbr );
      if (FAILED(hr))
         return hr;

      *ppMember = pmbr;
      (*ppMember)->AddRef(); // for client

      pmbr->OnCreate(m_pModel,m_pEvents,id,startJoint,endJoint,EA,EI);

      // insert new member
      std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(id, *ppMember)) );
      if (!st.second)
      {
         ATLASSERT(false); // insert failed - better check why
         return E_POINTER;
      }
   }

   m_pEvents->OnMemberAdded(id);

	return S_OK;
}

STDMETHODIMP CMemberCollection::Remove(IndexType IDorIndex, Fem2dAccessType AccessMethod, MemberIDType* pid)
{
   HRESULT hr = MemberCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
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
