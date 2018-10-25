///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// StrainLoad.cpp : Implementation of CStrainLoad
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "StrainLoad.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrainLoad

STDMETHODIMP CStrainLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStrainLoad
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStrainLoad::get_MemberType(MemberType *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_MemberType;

	return S_OK;
}

STDMETHODIMP CStrainLoad::put_MemberType(MemberType newVal)
{
   if (newVal != m_MemberType)
   {
      CHECK_MEMBERTYPE(newVal);

      m_MemberType = newVal;
      Fire_OnStrainLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CStrainLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CStrainLoad::put_MemberID(MemberIDType newVal)
{
	if (newVal<0)
      return E_INVALIDARG;

   if (newVal!=m_MemberID)
   {
      m_MemberID = newVal;
      Fire_OnStrainLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CStrainLoad::get_AxialStrain(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_AxialStrain;

	return S_OK;
}

STDMETHODIMP CStrainLoad::put_AxialStrain(Float64 newVal)
{
   if (newVal!=m_AxialStrain)
   {
      m_AxialStrain = newVal;
      Fire_OnStrainLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CStrainLoad::get_CurvatureStrain(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_CurvatureStrain;


	return S_OK;
}

STDMETHODIMP CStrainLoad::put_CurvatureStrain(Float64 newVal)
{
   if (newVal!=m_CurvatureStrain)
   {
      m_CurvatureStrain = newVal;
      Fire_OnStrainLoadChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CStrainLoad::Clone(IStrainLoad **clone)
{
   CHECK_RETOBJ(clone);

   // create a new and fill it up
   CComObject<CStrainLoad>* pnew;
   HRESULT hr = CComObject<CStrainLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IStrainLoad> pscs(pnew); // for reference count

   pnew->m_MemberType  = m_MemberType;
   pnew->m_MemberID    = m_MemberID;

   pnew->m_AxialStrain     = m_AxialStrain;
   pnew->m_CurvatureStrain = m_CurvatureStrain;

   return pscs.CopyTo(clone);
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CStrainLoad::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("StrainLoad"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      _variant_t var;

      hr = pload->get_Property(_bstr_t("MemberType"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t type(var);
      hr = StringToMemberType(type, &m_MemberType);
      if (FAILED(hr))
         return hr;
      
      var.Clear();

      hr = pload->get_Property(_bstr_t("MemberID"),&var);
      if (FAILED(hr))
         return hr;

      m_MemberID = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("AxialStrain"),&var);
      if (FAILED(hr))
         return hr;

      m_AxialStrain = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("CurvatureStrain"),&var);
      if (FAILED(hr))
         return hr;

      m_CurvatureStrain = var;
      var.Clear();
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CStrainLoad::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("StrainLoad"), MY_VER);

      {
         _bstr_t type = MemberTypeToString(m_MemberType);

         hr = psave->put_Property(CComBSTR("MemberType"),_variant_t(type));
         hr = psave->put_Property(CComBSTR("MemberID"),_variant_t(m_MemberID));
         hr = psave->put_Property(CComBSTR("AxialStrain"),_variant_t(m_AxialStrain));
         hr = psave->put_Property(CComBSTR("CurvatureStrain"),_variant_t(m_CurvatureStrain));
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IStrainLoad);
   }

   return hr;
}

