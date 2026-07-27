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
// PointLoad.cpp : Implementation of CPointLoad
#include "stdafx.h"
#include "PointLoad.h"
#include "ModelEvents.h"
#include "Loading.h"


#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnPointLoadChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CPointLoad

STDMETHODIMP CPointLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dPointLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CPointLoad::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, WBFL::FEA2D::PointLoad* pCore)
{
   ATLASSERT(pLoading!=0);
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  //for C++ event handlers
   m_pLoading = pLoading;
   m_pCore = pCore;
}

STDMETHODIMP CPointLoad::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CPointLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetMemberID();

	return S_OK;
}

STDMETHODIMP CPointLoad::put_MemberID(MemberIDType newVal)
{
   if (m_pCore->SetMemberID(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::get_Orientation(Fem2dLoadOrientation *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = static_cast<Fem2dLoadOrientation>(m_pCore->GetOrientation());

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Orientation(Fem2dLoadOrientation newVal)
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
      return CComCoClass<CPointLoad,&CLSID_Fem2dPointLoad>::Error(msg, helpid, GetHelpFile(), IID_IFem2dPointLoad, hr);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dPointLoad, IID_IFem2dPointLoad);
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Fx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetFx();

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fx(Float64 newVal)
{
   if (m_pCore->SetFx(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::get_Fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetFy();

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fy(Float64 newVal)
{
   if (m_pCore->SetFy(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::get_Mz(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetMz();

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Mz(Float64 newVal)
{
   if (m_pCore->SetMz(newVal))
   {
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::SetForce(Float64 Fx, Float64 Fy, Float64 Mz)
{
   m_pCore->SetForce(Fx, Fy, Mz);

   ON_LOAD_CHANGED()
	return S_OK;
}

STDMETHODIMP CPointLoad::GetForce(Float64 *Fx, Float64 *Fy, Float64 *Mz)
{
   CHECK_RETVAL(Fx);
   CHECK_RETVAL(Fy);
   CHECK_RETVAL(Mz);
   m_pCore->GetForce(Fx, Fy, Mz);

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Location(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetLocation();

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Location(Float64 newVal)
{
   try
   {
      if (m_pCore->SetLocation(newVal))
      {
         ON_LOAD_CHANGED()
      }
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dPointLoad, IID_IFem2dPointLoad);
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
   // via m_pLoading (not m_pCore->GetLoadingID()) so this still works after
   // this load has been removed from its loading - m_pCore is a non-owning
   // pointer that Remove() may have already freed, but the owning CLoading
   // COM wrapper (kept alive by whoever still holds this object) is not
	return m_pLoading->get_ID(pVal);
}
