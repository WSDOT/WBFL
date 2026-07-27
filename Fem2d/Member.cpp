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
// Member.cpp : Implementation of CMember
#include "stdafx.h"
#include "Member.h"
#include "Model.h"
#include "Joint.h"
#include "Loading.h"

#include <MathEx.h>

#define ON_MBR_CHANGED() ATLASSERT(m_pModel!=0); m_pModel->OnMemberChanged(this);

/////////////////////////////////////////////////////////////////////////////
// CMember
CMember::CMember():
m_pModel(0),
m_pCore(0)
{
}

CMember::~CMember()
{
}

void CMember::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::Member* pCore)
{
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // C++ event handlers
   m_pCore = pCore;
}

STDMETHODIMP CMember::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dMember
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMember::get_ID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CMember::get_StartJoint(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetStartJoint();

	return S_OK;
}

STDMETHODIMP CMember::put_StartJoint(JointIDType newVal)
{
   if (m_pCore->SetStartJoint(newVal))
   {
      ON_MBR_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CMember::get_EndJoint(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pCore->GetEndJoint();

	return S_OK;
}

STDMETHODIMP CMember::put_EndJoint(JointIDType newVal)
{
   if (m_pCore->SetEndJoint(newVal))
   {
      ON_MBR_CHANGED();
   }
	return S_OK;
}

STDMETHODIMP CMember::get_EA(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetEA();

	return S_OK;
}

STDMETHODIMP CMember::put_EA(Float64 newVal)
{
   try
   {
      if (m_pCore->SetEA(newVal))
      {
         ON_MBR_CHANGED();
      }
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dMember, IID_IFem2dMember);
   }
	return S_OK;
}

STDMETHODIMP CMember::get_EI(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetEI();

	return S_OK;
}

STDMETHODIMP CMember::put_EI(Float64 newVal)
{
   try
   {
      if (m_pCore->SetEI(newVal))
      {
         ON_MBR_CHANGED();
      }
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dMember, IID_IFem2dMember);
   }
	return S_OK;
}

STDMETHODIMP CMember::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   try
   {
      *pVal = m_pCore->GetLength();
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dMember, IID_IFem2dMember);
   }

	return S_OK;
}

STDMETHODIMP CMember::IsReleased(Fem2dMbrEndType end,Fem2dMbrReleaseType releaseType, VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_pCore->IsReleased(static_cast<WBFL::FEA2D::MemberEndType>(end), static_cast<WBFL::FEA2D::MemberReleaseType>(releaseType)) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMember::ReleaseEnd(Fem2dMbrEndType end, Fem2dMbrReleaseType releaseType)
{
   m_pCore->ReleaseEnd(static_cast<WBFL::FEA2D::MemberEndType>(end), static_cast<WBFL::FEA2D::MemberReleaseType>(releaseType));
   ON_MBR_CHANGED();
	return S_OK;
}

Float64 CMember::GetRealLocation(Float64 length, Float64 loc)
{
   return WBFL::FEA2D::Member::GetRealLocation(length, loc);
}

Float64 CMember::GetRealLocation(Float64 loc)
{
   return m_pCore->GetRealLocation(loc);
}

bool CMember::operator == (const CMember &mbr) const
{
   return m_pCore->operator==(*mbr.m_pCore);
}
