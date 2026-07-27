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
// MemberStrain.cpp : Implementation of CMemberStrain
#include "stdafx.h"
#include "MemberStrain.h"
#include "ModelEvents.h"
#include "Loading.h"


#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnMemberStrainChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CMemberStrain

STDMETHODIMP CMemberStrain::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dMemberStrain
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CMemberStrain::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::MemberStrain* pCore)
{
   ATLASSERT(pLoading!=0);
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // C++ event handlers
   m_pLoading = pLoading;
   m_pCore = pCore;
}

STDMETHODIMP CMemberStrain::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CMemberStrain::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetMemberID();

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_MemberID(MemberIDType newVal)
{
   if (m_pCore->SetMemberID(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_AxialStrain(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetAxialStrain();

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_AxialStrain(Float64 newVal)
{
   if (m_pCore->SetAxialStrain(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_CurvatureStrain(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetCurvatureStrain();

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_CurvatureStrain(Float64 newVal)
{
   if (m_pCore->SetCurvatureStrain(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_StartLocation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetStartLocation();

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_StartLocation(Float64 newVal)
{
   if (m_pCore->SetStartLocation(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_EndLocation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetEndLocation();

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_EndLocation(Float64 newVal)
{
   if (m_pCore->SetEndLocation(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
   // via m_pLoading, not m_pCore->GetLoadingID() - see CJointLoad::get_Loading
	return m_pLoading->get_ID(pVal);
}
