///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
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

// POIStressPointsItem.cpp : Implementation of CPOIStressPointsItem
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "POIStressPointsItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPOIStressPointsItem

STDMETHODIMP CPOIStressPointsItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPOIStressPointsItem
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPOIStressPointsItem::get_Stage(BSTR *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Stage.Copy();

	return S_OK;
}

STDMETHODIMP CPOIStressPointsItem::get_LeftStressPoints(IStressPoints **pVal)
{
	CHECK_RETOBJ(pVal);
	return m_LeftStressPoints.CopyTo(pVal);
}

STDMETHODIMP CPOIStressPointsItem::get_RightStressPoints(IStressPoints **pVal)
{
	CHECK_RETOBJ(pVal);
	return m_RightStressPoints.CopyTo(pVal);
}


   // IStructuredStorage2
#define MY_VER 1.0
STDMETHODIMP CPOIStressPointsItem::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("StressPointsItem"));
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
      hr = pload->get_Property(_bstr_t("Stage"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t stage(var);
      m_Stage = (LPCTSTR)stage;
      var.Clear();

      CComPtr<IStressPoints> leftsps, rightsps;
      hr = pload->get_Property(_bstr_t("LeftStressPoints"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      hr = _CopyVariantToInterface<IStressPoints>::copy(&leftsps, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      m_LeftStressPoints = leftsps;
      var.Clear();

      hr = pload->get_Property(_bstr_t("RightStressPoints"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      hr = _CopyVariantToInterface<IStressPoints>::copy(&rightsps, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      m_RightStressPoints = rightsps;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CPOIStressPointsItem::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("StressPointsItem"), MY_VER);
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Stage"),_variant_t(m_Stage));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("LeftStressPoints"),_variant_t(m_LeftStressPoints));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("RightStressPoints"),_variant_t(m_RightStressPoints));
   if (FAILED(hr))
      return hr;

   hr = psave->EndUnit();
   return hr;
}
