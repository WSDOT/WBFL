///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2011  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// SettlementLoad.cpp : Implementation of CSettlementLoad
#include "stdafx.h"
#include "WBFLLoading.h"
#include "SettlementLoad.h"
#include "LoadingUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettlementLoad

STDMETHODIMP CSettlementLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ldISettlementLoad
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSettlementLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CSettlementLoad::put_MemberID(MemberIDType newVal)
{
	if (newVal<0)
      return E_INVALIDARG;

   if (newVal!=m_MemberID)
   {
      m_MemberID = newVal;
      Fire_OnSettlementLoadChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CSettlementLoad::get_Dx(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Dx;

	return S_OK;
}

STDMETHODIMP CSettlementLoad::put_Dx(Float64 newVal)
{
   if (newVal!=m_Dx)
   {
      m_Dx = newVal;
      Fire_OnSettlementLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CSettlementLoad::get_Dy(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Dy;

	return S_OK;
}

STDMETHODIMP CSettlementLoad::put_Dy(Float64 newVal)
{
   if (newVal!=m_Dy)
   {
      m_Dy = newVal;
      Fire_OnSettlementLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CSettlementLoad::get_Rz(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Rz;

	return S_OK;
}

STDMETHODIMP CSettlementLoad::put_Rz(Float64 newVal)
{
   if (newVal!=m_Rz)
   {
      m_Rz = newVal;
      Fire_OnSettlementLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CSettlementLoad::Clone(ldISettlementLoad **clone)
{
   CHECK_RETOBJ(clone);

   // create a new and fill it up
   CComObject<CSettlementLoad>* pnew;
   HRESULT hr = CComObject<CSettlementLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldISettlementLoad> pscs(pnew); // for reference count

   pnew->m_MemberID    = m_MemberID;

   pnew->m_Dx = m_Dx;
   pnew->m_Dy = m_Dy;
   pnew->m_Rz = m_Rz;

   return pscs.CopyTo(clone);
}

static const Float64 MY_VER=1.0;
STDMETHODIMP CSettlementLoad::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("SettlementLoad"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      CComVariant var;
      hr = pload->get_Property(CComBSTR("MemberID"),&var);
      if (FAILED(hr))
         return hr;

      m_MemberID = var.iVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("Dx"),&var);
      if (FAILED(hr))
         return hr;

      m_Dx = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("Dy"),&var);
      if (FAILED(hr))
         return hr;

      m_Dy = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("Rz"),&var);
      if (FAILED(hr))
         return hr;

      m_Rz = var.dblVal;

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CSettlementLoad::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("SettlementLoad"), MY_VER);

      {
         hr = psave->put_Property(CComBSTR("MemberID"),CComVariant(m_MemberID));
         hr = psave->put_Property(CComBSTR("Dx"),CComVariant(m_Dx));
         hr = psave->put_Property(CComBSTR("Dy"),CComVariant(m_Dy));
         hr = psave->put_Property(CComBSTR("Rz"),CComVariant(m_Rz));
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldISettlementLoad);
   }

   return S_OK;
}
