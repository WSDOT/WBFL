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
// JointLoad.cpp : Implementation of CJointLoad
#include "stdafx.h"
#include "JointLoad.h"
#include "ModelEvents.h"
#include "Loading.h"


#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnJointLoadChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CJointLoad
void CJointLoad::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::JointLoad* pCore)
{
   ATLASSERT(pLoading!=0);
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // C++ event handlers
   m_pLoading = pLoading;
   m_pCore = pCore;
}

STDMETHODIMP CJointLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dJointLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CJointLoad::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CJointLoad::get_JointID(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetJointID();

	return S_OK;
}

STDMETHODIMP CJointLoad::put_JointID(JointIDType newVal)
{
   if (m_pCore->SetJointID(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::get_Fx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetFx();

	return S_OK;
}

STDMETHODIMP CJointLoad::put_Fx(Float64 newVal)
{
   if (m_pCore->SetFx(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::get_Fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetFy();

	return S_OK;
}

STDMETHODIMP CJointLoad::put_Fy(Float64 newVal)
{
   if (m_pCore->SetFy(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::get_Mz(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetMz();

	return S_OK;
}

STDMETHODIMP CJointLoad::put_Mz(Float64 newVal)
{
   if (m_pCore->SetMz(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointLoad::SetForce(Float64 Fx, Float64 Fy, Float64 Mz)
{
   m_pCore->SetForce(Fx, Fy, Mz);

   ON_LOAD_CHANGED()
	return S_OK;
}

STDMETHODIMP CJointLoad::GetForce(Float64 *Fx, Float64 *Fy, Float64 *Mz)
{
   CHECK_RETVAL(Fx);
   CHECK_RETVAL(Fy);
   CHECK_RETVAL(Mz);
	m_pCore->GetForce(Fx, Fy, Mz);

	return S_OK;
}

STDMETHODIMP CJointLoad::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
   // via m_pLoading (not m_pCore->GetLoadingID()) so this still works after
   // this load has been removed from its loading - m_pCore is a non-owning
   // pointer that Remove() may have already freed, but the owning CLoading
   // COM wrapper (kept alive by whoever still holds this object) is not
	return m_pLoading->get_ID(pVal);
}
