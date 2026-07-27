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
// JointDeflection.cpp : Implementation of CJointDeflection
#include "stdafx.h"
#include "JointDisplacement.h"
#include "ModelEvents.h"
#include "Loading.h"


#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnJointDeflectionChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CJointDeflection
void CJointDeflection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::JointDisplacement* pCore)
{
   ATLASSERT(pLoading!=0);
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // C++ event handlers
   m_pLoading = pLoading;
   m_pCore = pCore;
}

STDMETHODIMP CJointDeflection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dJointDeflection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CJointDeflection::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CJointDeflection::get_JointID(JointIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetJointID();

	return S_OK;
}

STDMETHODIMP CJointDeflection::put_JointID(JointIDType newVal)
{
   if (m_pCore->SetJointID(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDeflection::get_Dx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetDx();

	return S_OK;
}

STDMETHODIMP CJointDeflection::put_Dx(Float64 newVal)
{
   if (m_pCore->SetDx(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDeflection::get_Dy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetDy();

	return S_OK;
}

STDMETHODIMP CJointDeflection::put_Dy(Float64 newVal)
{
   if (m_pCore->SetDy(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDeflection::get_Rz(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetRz();

	return S_OK;
}

STDMETHODIMP CJointDeflection::put_Rz(Float64 newVal)
{
   if (m_pCore->SetRz(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CJointDeflection::SetDeflection(Float64 Dx, Float64 Dy, Float64 Rz)
{
   m_pCore->SetDeflection(Dx, Dy, Rz);

   ON_LOAD_CHANGED()
	return S_OK;
}

STDMETHODIMP CJointDeflection::GetDeflection(Float64 *Dx, Float64 *Dy, Float64 *Rz)
{
   CHECK_RETVAL(Dx);
   CHECK_RETVAL(Dy);
   CHECK_RETVAL(Rz);
	m_pCore->GetDeflection(Dx, Dy, Rz);

	return S_OK;
}

STDMETHODIMP CJointDeflection::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
   // via m_pLoading, not m_pCore->GetLoadingID() - see CJointLoad::get_Loading
	return m_pLoading->get_ID(pVal);
}
