///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2020  Washington State Department of Transportation
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

// Result3D.cpp : Implementation of CResult3D
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "Result3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResult3D

STDMETHODIMP CResult3D::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IResult3D
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CResult3D::get_X(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_X;

	return S_OK;
}

STDMETHODIMP CResult3D::put_X(Float64 newVal)
{
	m_X = newVal;

	return S_OK;
}

STDMETHODIMP CResult3D::get_Y(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Y;

	return S_OK;
}

STDMETHODIMP CResult3D::put_Y(Float64 newVal)
{
	m_Y = newVal;

	return S_OK;
}

STDMETHODIMP CResult3D::get_Z(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Z;

	return S_OK;
}

STDMETHODIMP CResult3D::put_Z(Float64 newVal)
{
	m_Z = newVal;

	return S_OK;
}

STDMETHODIMP CResult3D::Clone(IResult3D **clone)
{
   CHECK_RETOBJ(clone);

   // create a new stress point collection and fill it up
   CComObject<CResult3D>* pnew;
   HRESULT hr = CComObject<CResult3D>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   pnew->m_X  = m_X;
   pnew->m_Y  = m_Y;
   pnew->m_Z  = m_Z;

   *clone = pnew;
   (*clone)->AddRef();

	return S_OK;
}

STDMETHODIMP CResult3D::Sum(Float64 X, Float64 Y, Float64 Z)
{
   m_X  += X;
   m_Y  += Y;
   m_Z  += Z;

	return S_OK;
}


STDMETHODIMP CResult3D::FactorAndSum(IResult3D *res, Float64 factor)
{
   CHECK_IN(res);

   Float64 val;
   res->get_X(&val);
   m_X  += val*factor;

   res->get_Y(&val);
   m_Y  += val*factor;

   res->get_Z(&val);
   m_Z  += val*factor;

	return S_OK;
}


STDMETHODIMP CResult3D::Zero()
{
   m_X  = 0;
   m_Y  = 0;
   m_Z  = 0;

	return S_OK;
}

STDMETHODIMP CResult3D::SetResult(Float64 X, Float64 Y, Float64 Z)
{
   m_X  = X;
   m_Y  = Y;
   m_Z  = Z;

	return S_OK;
}

STDMETHODIMP CResult3D::GetResult(Float64 *X, Float64 *Y, Float64 *Z)
{
   CHECK_RETVAL(X);
   CHECK_RETVAL(Y);
   CHECK_RETVAL(Z);

   *X = m_X;
   *Y = m_Y;
   *Z = m_Z;

	return S_OK;
}

STDMETHODIMP CResult3D::GetSingleResult(ForceEffectType effect, Float64 *val)
{
   CHECK_RETVAL(val);

   if (effect<0 || effect>2)
      return E_INVALIDARG;

   *val  = ForceVec[effect];

	return S_OK;
}

STDMETHODIMP CResult3D::SetSingleResult(ForceEffectType effect, Float64 val)
{
   if (effect<0 || effect>2)
      return E_INVALIDARG;

   ForceVec[effect] = val;

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CResult3D::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("Result3D"));
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
      hr = pload->get_Property(_bstr_t("X"),&var);
      if (FAILED(hr))
         return hr;

      m_X = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Y"),&var);
      if (FAILED(hr))
         return hr;

      m_Y = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Z"),&var);
      if (FAILED(hr))
         return hr;

      m_Z = var;

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CResult3D::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("Result3D"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("X"),_variant_t(m_X));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Y"),_variant_t(m_Y));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Z"),_variant_t(m_Z));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   return hr;
}



