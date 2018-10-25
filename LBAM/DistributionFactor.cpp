///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2012  Washington State Department of Transportation
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

// DistributionFactor.cpp : Implementation of CDistributionFactor
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "DistributionFactor.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDistributionFactor

STDMETHODIMP CDistributionFactor::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDistributionFactor
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDistributionFactor::get_GPMSgl(Float64 *pVal)
{
  CHECK_RETVAL(pVal);

	*pVal = m_GPMSgl;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GPMSgl(Float64 newVal)
{
   return PutVal(newVal, m_GPMSgl);
}

STDMETHODIMP CDistributionFactor::get_GPMMul(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GPMMul;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GPMMul(Float64 newVal)
{
   return PutVal(newVal, m_GPMMul);
}

STDMETHODIMP CDistributionFactor::get_GNMSgl(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GNMSgl;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GNMSgl(Float64 newVal)
{
   return PutVal(newVal, m_GNMSgl);
}

STDMETHODIMP CDistributionFactor::get_GNMMul(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GNMMul;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GNMMul(Float64 newVal)
{
   return PutVal(newVal, m_GNMMul);
}

STDMETHODIMP CDistributionFactor::get_GVSgl(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_GVSgl;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GVSgl(Float64 newVal)
{
	return PutVal(newVal, m_GVSgl);
}

STDMETHODIMP CDistributionFactor::get_GVMul(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GVMul;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GVMul(Float64 newVal)
{
	return PutVal(newVal, m_GVMul);
}

STDMETHODIMP CDistributionFactor::get_GDSgl(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GDSgl;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GDSgl(Float64 newVal)
{
	return PutVal(newVal, m_GDSgl);
}

STDMETHODIMP CDistributionFactor::get_GDMul(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GDMul;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GDMul(Float64 newVal)
{
   return PutVal(newVal, m_GDMul);
}

STDMETHODIMP CDistributionFactor::get_GTSgl(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GTSgl;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GTSgl(Float64 newVal)
{
   return PutVal(newVal, m_GTSgl);
}

STDMETHODIMP CDistributionFactor::get_GTMul(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GTMul;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GTMul(Float64 newVal)
{
   return PutVal(newVal, m_GTMul);
}

STDMETHODIMP CDistributionFactor::get_GRSgl(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GRSgl;
	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GRSgl(Float64 newVal)
{
   return PutVal(newVal, m_GRSgl);
}

STDMETHODIMP CDistributionFactor::get_GRMul(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GRMul;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GRMul(Float64 newVal)
{
   return PutVal(newVal, m_GRMul);
}

STDMETHODIMP CDistributionFactor::get_GFat(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_GFat;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::put_GFat(Float64 newVal)
{
	return PutVal(newVal, m_GFat);
}

STDMETHODIMP CDistributionFactor::SetG(Float64 PMSgl, Float64 PMMul, Float64 NMSgl, Float64 NMMul, 
                                       Float64 VSgl, Float64 VMul, Float64 DSgl, Float64 DMul, 
                                       Float64 RSgl, Float64 RMul, Float64 TSgl, Float64 TMul,
                                       Float64 Fat)
{
   bool dofire = false;
	HRESULT hr;
   hr = PutVal2(PMSgl, m_GPMSgl, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(PMMul, m_GPMMul, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(NMSgl, m_GNMSgl, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(NMMul, m_GNMMul, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(VSgl, m_GVSgl, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(VMul, m_GVMul, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(DSgl, m_GDSgl, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(DMul, m_GDMul, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(RSgl, m_GRSgl, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(RMul, m_GRMul, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(TSgl, m_GTSgl, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(TMul, m_GTMul, dofire);
   if (FAILED(hr))
      return hr;

   hr = PutVal2(Fat, m_GFat, dofire);
   if (FAILED(hr))
      return hr;

   if (dofire)
      Fire_OnDistributionFactorChanged(this);


	return S_OK;
}

STDMETHODIMP CDistributionFactor::GetG(Float64* PMSgl, Float64* PMMul, Float64* NMSgl, Float64* NMMul, 
                                       Float64* VSgl, Float64* VMul, Float64* DSgl, Float64* DMul, 
                                       Float64* RSgl, Float64* RMul, Float64* TSgl, Float64* TMul,
                                       Float64* Fat)
{
	CHECK_IN(PMSgl);
	CHECK_IN(PMMul);
	CHECK_IN(NMSgl);
	CHECK_IN(NMMul);
	CHECK_IN(VSgl);
	CHECK_IN(VMul);
	CHECK_IN(DSgl);
	CHECK_IN(DMul);
	CHECK_IN(RSgl);
	CHECK_IN(RMul);
	CHECK_IN(TSgl);
	CHECK_IN(TMul);
	CHECK_IN(Fat);
   
   *PMSgl = m_GPMSgl;
	*PMMul = m_GPMMul;
	*NMSgl = m_GNMSgl;
	*NMMul = m_GNMMul;
	*VSgl  = m_GVSgl;
	*VMul  = m_GVMul;
	*DSgl  = m_GDSgl;
	*DMul  = m_GDMul;
	*RSgl  = m_GRSgl;
	*RMul  = m_GRMul;
	*TSgl  = m_GTSgl;
	*TMul  = m_GTMul;
	*Fat   = m_GFat;

	return S_OK;
}

STDMETHODIMP CDistributionFactor::Clone(IDistributionFactor ** pVal)
{
   CHECK_RETOBJ(pVal);

   CComObject<CDistributionFactor>* pclone;
   HRESULT hr =CComObject<CDistributionFactor>::CreateInstance(&pclone);
   if (FAILED(hr))
      return hr;

   pclone->m_GPMSgl = m_GPMSgl;
   pclone->m_GPMMul = m_GPMMul;
   pclone->m_GNMSgl = m_GNMSgl;
   pclone->m_GNMMul = m_GNMMul;
   pclone->m_GVSgl  = m_GVSgl;
   pclone->m_GVMul  = m_GVMul;
   pclone->m_GDSgl  = m_GDSgl;
   pclone->m_GDMul  = m_GDMul;
   pclone->m_GRSgl  = m_GRSgl;
   pclone->m_GRMul  = m_GRMul;
   pclone->m_GTSgl  = m_GTSgl;
   pclone->m_GTMul  = m_GTMul;
   pclone->m_GFat   = m_GFat;

   *pVal = pclone;
   (*pVal)->AddRef();

	return S_OK;
}

HRESULT CDistributionFactor::PutVal(Float64 newVal, Float64& G)
{
   bool dofire = false;
   HRESULT hr = PutVal2(newVal, G, dofire);
   if (FAILED(hr))
      return hr;

   if (dofire)
      Fire_OnDistributionFactorChanged(this);

   return S_OK;
}

HRESULT CDistributionFactor::PutVal2(Float64 newVal, Float64& G, bool& dofire)
{
   if (newVal <0.0) 
      return E_INVALIDARG;
   if (newVal != G)
   { 
      G = newVal; 
      dofire = true;
   }
   return S_OK;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CDistributionFactor::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("DistributionFactor"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      hr = GetProp(pload, _bstr_t("GFat"), m_GFat);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GRMul"), m_GRMul);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GRSgl"), m_GRSgl);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GTSgl"), m_GTSgl);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GTMul"), m_GTMul);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GDMul"), m_GDMul);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GDSgl"), m_GDSgl);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GVMul"), m_GVMul);
      if (FAILED(hr))
         return hr;
      hr = GetProp(pload, _bstr_t("GVSgl"), m_GVSgl);
      if (FAILED(hr))
         return hr;
      hr = GetProp(pload, _bstr_t("GNMMul"), m_GNMMul);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GNMSgl"), m_GNMSgl);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GPMMul"), m_GPMMul);
      if (FAILED(hr))
         return hr;

      hr = GetProp(pload, _bstr_t("GPMSgl"), m_GPMSgl);
      if (FAILED(hr))
         return hr;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CDistributionFactor::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("DistributionFactor"), MY_VER);
      if (FAILED(hr))
         return hr;


         hr = psave->put_Property(CComBSTR("GFat"), _variant_t(m_GFat));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GRMul"), _variant_t(m_GRMul));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GRSgl"), _variant_t(m_GRSgl));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GTSgl"), _variant_t(m_GTSgl));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GTMul"), _variant_t(m_GTMul));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GDMul"), _variant_t(m_GDMul));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GDSgl"), _variant_t(m_GDSgl));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GVMul"), _variant_t(m_GVMul));
         if (FAILED(hr))
            return hr;
         hr = psave->put_Property(CComBSTR("GVSgl"), _variant_t(m_GVSgl));
         if (FAILED(hr))
            return hr;
         hr = psave->put_Property(CComBSTR("GNMMul"), _variant_t(m_GNMMul));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GNMSgl"), _variant_t(m_GNMSgl));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GPMMul"), _variant_t(m_GPMMul));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("GPMSgl"), _variant_t(m_GPMSgl));
         if (FAILED(hr))
            return hr;

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IDistributionFactor);
   }

   return hr;
}

HRESULT CDistributionFactor::GetProp(IStructuredLoad2 *pload, BSTR name, Float64& prop)
{
   CHECK_IN(pload);
   CHECK_IN(name);

      _variant_t var;
      HRESULT hr = pload->get_Property(name,&var);
      if (FAILED(hr))
         return hr;

      prop = var;
      return S_OK;
}

