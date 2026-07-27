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
// DistributedLoad.cpp : Implementation of CDistributedLoad
#include "stdafx.h"
#include "DistributedLoad.h"
#include "ModelEvents.h"
#include "Loading.h"


#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnDistributedLoadChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CDistributedLoad

STDMETHODIMP CDistributedLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dDistributedLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CDistributedLoad::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::DistributedLoad* pCore)
{
   ATLASSERT(pLoading!=0);
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  //for C++ event handlers
   m_pLoading = pLoading;
   m_pCore = pCore;
}

STDMETHODIMP CDistributedLoad::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetMemberID();

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_MemberID(MemberIDType newVal)
{
   if (m_pCore->SetMemberID(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_Orientation(Fem2dLoadOrientation *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = static_cast<Fem2dLoadOrientation>(m_pCore->GetOrientation());

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Orientation(Fem2dLoadOrientation newVal)
{
   try
   {
      CheckLoadOrientation(newVal);
      if (m_pCore->SetOrientation(static_cast<WBFL::FEA2D::LoadOrientation>(newVal)))
      {
         ON_LOAD_CHANGED()
      }
   }
   catch (CComException& re)
   {
      CComBSTR msg(re.GetErrorMessage());
      HRESULT hr = re.GetHresult();
      DWORD helpid = re.GetHelpID();
      return CComCoClass<CDistributedLoad,&CLSID_Fem2dDistributedLoad>::Error(msg, helpid, GetHelpFile(), IID_IFem2dDistributedLoad, hr);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dDistributedLoad, IID_IFem2dDistributedLoad);
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_Direction(Fem2dLoadDirection *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = static_cast<Fem2dLoadDirection>(m_pCore->GetDirection());

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Direction(Fem2dLoadDirection newVal)
{
   if (m_pCore->SetDirection(static_cast<WBFL::FEA2D::LoadDirection>(newVal)))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_StartLocation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetStartLocation();

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_StartLocation(Float64 newVal)
{
   try
   {
      if (m_pCore->SetStartLocation(newVal))
      {
         ON_LOAD_CHANGED()
      }
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dDistributedLoad, IID_IFem2dDistributedLoad);
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_EndLocation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetEndLocation();

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_EndLocation(Float64 newVal)
{
   try
   {
      if (m_pCore->SetEndLocation(newVal))
      {
         ON_LOAD_CHANGED()
      }
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dDistributedLoad, IID_IFem2dDistributedLoad);
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_WStart(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetWStart();

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WStart(Float64 newVal)
{
   if (m_pCore->SetWStart(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_WEnd(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetWEnd();

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WEnd(Float64 newVal)
{
   if (m_pCore->SetWEnd(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
   // via m_pLoading, not m_pCore->GetLoadingID() - see CJointLoad::get_Loading
	return m_pLoading->get_ID(pVal);
}
