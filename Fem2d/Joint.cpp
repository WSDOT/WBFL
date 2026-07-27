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
// Joint.cpp : Implementation of CJoint
#include "stdafx.h"
#include "Joint.h"
#include "Model.h"
#include "Member.h"
#include "JointLoad.h"
#include "JointDisplacement.h"

#include <MathEx.h>



#define ON_JNT_CHANGED() ATLASSERT(m_pModel!=0); m_pModel->OnJointChanged(this);


/////////////////////////////////////////////////////////////////////////////
// CJoint
CJoint::CJoint():
m_pModel(0),
m_pCoreModel(0),
m_pCore(0)
{
}

CJoint::~CJoint()
{
}

void CJoint::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::Model* pCoreModel, WBFL::FEA2D::Joint* pCore)
{
   ATLASSERT(pCoreModel!=0);
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  //  C++ event handlers
   m_pCoreModel = pCoreModel;
   m_pCore = pCore;
}

STDMETHODIMP CJoint::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dJoint
	};
	for (long i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CJoint::get_ID(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CJoint::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pCore->GetX();

	return S_OK;
}

STDMETHODIMP CJoint::put_X(Float64 newVal)
{
   if (m_pCore->SetX(newVal))
   {
      ON_JNT_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CJoint::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetY();

	return S_OK;
}

STDMETHODIMP CJoint::put_Y(Float64 newVal)
{
   if (m_pCore->SetY(newVal))
   {
      ON_JNT_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CJoint::IsDofReleased(Fem2dJointReleaseType rel, VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pCore->IsDofReleased(static_cast<WBFL::FEA2D::JointReleaseType>(rel)) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CJoint::IsDofSupported(Fem2dJointReleaseType rel, VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pCore->IsDofSupported(static_cast<WBFL::FEA2D::JointReleaseType>(rel)) ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}


STDMETHODIMP CJoint::IsSupport(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pCore->IsSupport() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CJoint::Support()
{
   if (m_pCore->Support())
   {
      ON_JNT_CHANGED();
   }

	return S_OK;
}

STDMETHODIMP CJoint::Free()
{
   if (m_pCore->Free())
   {
      ON_JNT_CHANGED();
   }

	return S_OK;
}

STDMETHODIMP CJoint::get_Members(IIDArray* *ppMemberIDs)
{
   CHECK_RETOBJ(ppMemberIDs);
   HRESULT hr = S_OK;

   // create collection
   CComPtr<IIDArray> pcoll;
   hr = pcoll.CoCreateInstance(CLSID_IDArray);
   ATLASSERT(SUCCEEDED(hr));
   if (FAILED(hr))
      return hr;

   // prep for client
   *ppMemberIDs = pcoll;
   (*ppMemberIDs)->AddRef();

   std::vector<MemberIDType> attachedMembers = m_pCoreModel->GetAttachedMembers(m_pCore->GetID());
   for (const auto& mbrID : attachedMembers)
   {
      pcoll->Add(mbrID);
   }

	return hr;
}


STDMETHODIMP CJoint::ReleaseDof(Fem2dJointReleaseType rel)
{
   if (m_pCore->ReleaseDof(static_cast<WBFL::FEA2D::JointReleaseType>(rel)))
   {
      ON_JNT_CHANGED();
   }

	return S_OK;
}
