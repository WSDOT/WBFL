///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014  Washington State Department of Transportation
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

// Segment.cpp : Implementation of CSegment
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "Segment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSegment

STDMETHODIMP CSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISegment
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CSegment::FinalRelease()
{
   HRESULT hr;
   if (!!m_pSegmentCrossSection)
   {
      hr = CrUnadvise(m_pSegmentCrossSection, this, IID_ISegmentCrossSectionEvents, m_SegmentCrossSectionCookie);
      ATLASSERT(SUCCEEDED(hr));
   }
}

STDMETHODIMP CSegment::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty collection of stress points and set
   // up a connection point to it
   hr = m_pSegmentCrossSection.CoCreateInstance(CLSID_SegmentCrossSection);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_pSegmentCrossSection, this, IID_ISegmentCrossSectionEvents, &m_SegmentCrossSectionCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}


STDMETHODIMP CSegment::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Length;
	return S_OK;
}

STDMETHODIMP CSegment::put_Length(Float64 newVal)
{
   if (newVal < -1.0)
      return E_INVALIDARG;

   if (newVal != m_Length)
   {
	   m_Length = newVal;
      Fire_OnSegmentChanged(this, cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CSegment::get_SegmentCrossSection(ISegmentCrossSection **pVal)
{
   CHECK_RETOBJ(pVal);

	return m_pSegmentCrossSection.CopyTo(pVal);
}

STDMETHODIMP CSegment::putref_SegmentCrossSection(ISegmentCrossSection *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same section
   if ( m_pSegmentCrossSection.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old section if we had one
   HRESULT hr;
   if (!!m_pSegmentCrossSection)
   {
      hr = CrUnadvise(m_pSegmentCrossSection, this, IID_ISegmentCrossSectionEvents, m_SegmentCrossSectionCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new 
   m_pSegmentCrossSection = newVal;

   // establish cp with new 
   hr = CrAdvise(m_pSegmentCrossSection, this, IID_ISegmentCrossSectionEvents, &m_SegmentCrossSectionCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnSegmentChanged(this, cgtStiffness);

	return S_OK;
}

// ISegmentCrossSectionEvents
STDMETHODIMP CSegment::OnSegmentCrossSectionChanged(ISegmentCrossSection* crossSection, ChangeType change)
{
   Fire_OnSegmentChanged(this, change);
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CSegment::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("Segment"));
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
      hr = pload->get_Property(_bstr_t("Length"),&var);
      if (FAILED(hr))
         return hr;

      m_Length = var;
      var.Clear();


      hr = pload->get_Property(_bstr_t("SegmentCrossSection"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ISegmentCrossSection> pics;
      hr = _CopyVariantToInterface<ISegmentCrossSection>::copy(&pics, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_SegmentCrossSection(pics);
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

STDMETHODIMP CSegment::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("Segment"), MY_VER);
      hr = psave->put_Property(CComBSTR("Length"),_variant_t(m_Length));
      hr = psave->put_Property(CComBSTR("SegmentCrossSection"),_variant_t(m_pSegmentCrossSection));
      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISegment);
   }

   return S_OK;
}

STDMETHODIMP CSegment::Clone(ISegment **pps)
{
   CHECK_RETOBJ(pps);

   // deep copy
   CComObject<CSegment>* pclone;
   HRESULT hr = CComObject<CSegment>::CreateInstance(&pclone);
   if (FAILED(hr))
      return hr;

   CComPtr<ISegment> spseg(pclone); // to keep reference count exception safe

   pclone->m_Length = m_Length;

   CComPtr<ISegmentCrossSection> pcs;
   hr = m_pSegmentCrossSection->Clone(&pcs);
   if (FAILED(hr))
      return hr;

   hr = spseg->putref_SegmentCrossSection(pcs);
   if (FAILED(hr))
      return hr;

   return spseg.CopyTo(pps);
}
