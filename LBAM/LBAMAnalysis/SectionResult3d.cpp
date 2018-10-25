///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2018  Washington State Department of Transportation
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

// SectionResult3D.cpp : Implementation of CSectionResult3D
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "SectionResult3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSectionResult3D

STDMETHODIMP CSectionResult3D::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISectionResult3D
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
} 

STDMETHODIMP CSectionResult3D::get_XLeft(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_XLeft;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::put_XLeft(Float64 newVal)
{
	m_XLeft = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::get_XRight(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_XRight;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::put_XRight(Float64 newVal)
{
	m_XRight = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::get_YLeft(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_YLeft;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::put_YLeft(Float64 newVal)
{
	m_YLeft = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::get_YRight(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_YRight;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::put_YRight(Float64 newVal)
{
	m_YRight = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::get_ZLeft(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_ZLeft;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::put_ZLeft(Float64 newVal)
{
	m_ZLeft = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::get_ZRight(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_ZRight;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::put_ZRight(Float64 newVal)
{
	m_ZRight = newVal;

	return S_OK;
}


STDMETHODIMP CSectionResult3D::SetResult(Float64 XLeft, Float64 YLeft, Float64 ZLeft, Float64 XRight,  Float64 YRight, Float64 ZRight)
{
	m_XLeft  = XLeft;
	m_XRight = XRight;
	m_YLeft  = YLeft;
	m_YRight = YRight;
	m_ZLeft  = ZLeft;
	m_ZRight = ZRight;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::GetResult(Float64 *XLeft, Float64 *YLeft, Float64 *ZLeft, Float64 *XRight, Float64 *YRight, Float64 *ZRight)
{
	CHECK_RETVAL(XLeft);
	CHECK_RETVAL(XRight);
	CHECK_RETVAL(YLeft);
	CHECK_RETVAL(YRight);
	CHECK_RETVAL(ZLeft);
	CHECK_RETVAL(ZRight);

	*XLeft  = m_XLeft;
	*XRight = m_XRight;
	*YLeft  = m_YLeft;
	*YRight = m_YRight;
	*ZLeft  = m_ZLeft;
	*ZRight = m_ZRight;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::Clone(ISectionResult3D **clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSectionResult3D>* pnew;
   HRESULT hr = CComObject<CSectionResult3D>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   pnew->m_XLeft  = m_XLeft;
   pnew->m_XRight = m_XRight;
   pnew->m_YLeft  = m_YLeft;
   pnew->m_YRight = m_YRight;
   pnew->m_ZLeft  = m_ZLeft;
   pnew->m_ZRight = m_ZRight;

   *clone = pnew;
   (*clone)->AddRef();

	return S_OK;
}


STDMETHODIMP CSectionResult3D::GetSingleResult(/*[in]*/ForceEffectType effect, /*[out]*/ Float64 *leftVal, /*[out]*/ Float64 *rightVal)
{
   CHECK_RETVAL(leftVal);
   CHECK_RETVAL(rightVal);

   if (effect<0 || effect>2)
      return E_INVALIDARG;

   *leftVal  = ForceVec[effect];
   *rightVal = ForceVec[effect+3];

   return S_OK;
}

STDMETHODIMP CSectionResult3D::SetSingleResult(/*[in]*/ForceEffectType effect, /*[in]*/ Float64 leftVal, /*[in]*/ Float64 rightVal)
{
   if (effect<0 || effect>2)
      return E_INVALIDARG;

   ForceVec[effect]   = leftVal;
   ForceVec[effect+3] = rightVal;

   return S_OK;
}

STDMETHODIMP CSectionResult3D::Sum(Float64 XLeft, Float64 YLeft, Float64 ZLeft, Float64 XRight,  Float64 YRight, Float64 ZRight)
{
	m_XLeft  += XLeft;
	m_XRight += XRight;
	m_YLeft  += YLeft;
	m_YRight += YRight;
	m_ZLeft  += ZLeft;
	m_ZRight += ZRight;

	return S_OK;
}

STDMETHODIMP CSectionResult3D::FactorAndSum(ISectionResult3D *res, Float64 leftFactor, Float64 rightFactor)
{
   CHECK_IN(res);

   Float64 val;
   res->get_XLeft(&val);
	m_XLeft  += (val * leftFactor);

   res->get_XRight(&val);
	m_XRight  += (val * rightFactor);

   res->get_YLeft(&val);
	m_YLeft  += (val * leftFactor);

   res->get_YRight(&val);
	m_YRight  += (val * rightFactor);

   res->get_ZLeft(&val);
	m_ZLeft  += (val * leftFactor);

   res->get_ZRight(&val);
	m_ZRight  += (val * rightFactor);

	return S_OK;
}


STDMETHODIMP CSectionResult3D::Zero()
{
	m_XLeft  = 0.0;
	m_XRight = 0.0;
	m_YLeft  = 0.0;
	m_YRight = 0.0;
	m_ZLeft  = 0.0;
	m_ZRight = 0.0;

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CSectionResult3D::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("SectionResult3D"));
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
      hr = pload->get_Property(_bstr_t("XLeft"),&var);
      if (FAILED(hr))
         return hr;

      m_XLeft = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("XRight"),&var);
      if (FAILED(hr))
         return hr;

      m_XRight = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("YLeft"),&var);
      if (FAILED(hr))
         return hr;

      m_YLeft = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("YRight"),&var);
      if (FAILED(hr))
         return hr;

      m_YRight = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("ZLeft"),&var);
      if (FAILED(hr))
         return hr;

      m_ZLeft = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("ZRight"),&var);
      if (FAILED(hr))
         return hr;

      m_ZRight = var;

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CSectionResult3D::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("SectionResult3D"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("XLeft"),_variant_t(m_XLeft));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("XRight"),_variant_t(m_XRight));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("YLeft"),_variant_t(m_YLeft));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("YRight"),_variant_t(m_YRight));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("ZLeft"),_variant_t(m_ZLeft));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("ZRight"),_variant_t(m_ZRight));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   return hr;
}

