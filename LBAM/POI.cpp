///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
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

// POI.cpp : Implementation of CPOI
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "POI.h"
#include "POIStressPoints.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPOI

STDMETHODIMP CPOI::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPOI
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CPOI::FinalRelease()
{
   HRESULT hr;
   if (m_POIStressPoints!=NULL)
   {
      hr = CrUnadvise(m_POIStressPoints, this, IID_IPOIStressPointsEvents, m_POIStressPointsCookie);
      if (FAILED(hr))
         ATLASSERT(0);
   }
}

STDMETHODIMP CPOI::get_ID(PoiIDType *pVal) 
{
   CHECK_RETVAL(pVal);

	*pVal = m_ID;
	return S_OK;
}

STDMETHODIMP CPOI::put_ID(PoiIDType newVal)
{
   if (newVal<0)
   {
      return E_INVALIDARG;
   }
   else if (newVal != m_ID)
   {
      PoiIDType oldval = m_ID;
      m_ID = newVal;
      Fire_OnPOIRenamed(oldval, newVal);
   }

	return S_OK;
}

STDMETHODIMP CPOI::get_MemberType(MemberType *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_MemberType;

	return S_OK;
}

STDMETHODIMP CPOI::put_MemberType(MemberType newVal)
{
   if (newVal != m_MemberType)
   {
      CHECK_MEMBERTYPE(newVal);

      m_MemberType = newVal;
      Fire_OnPOIChanged(this, cgtPOI);
   }

	return S_OK;
}

STDMETHODIMP CPOI::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CPOI::put_MemberID(MemberIDType newVal)
{
	if (newVal<0)
      return E_INVALIDARG;

   if (newVal!=m_MemberID)
   {
      m_MemberID = newVal;
      Fire_OnPOIChanged(this, cgtPOI);
   }

	return S_OK;
}

STDMETHODIMP CPOI::get_Location(Float64 *pVal)
{
	CHECK_RETVAL(pVal);

   *pVal = m_Location;

	return S_OK;
}

STDMETHODIMP CPOI::put_Location(Float64 newVal)
{
	if (newVal<-1.0)
      return E_INVALIDARG;

   if (newVal!=m_Location)
   {
      m_Location = newVal;
      Fire_OnPOIChanged(this, cgtPOI);
   }

	return S_OK;
}

STDMETHODIMP CPOI::putref_POIStressPoints(IPOIStressPoints *poiStressPoints)
{
   HRESULT hr;
   CHECK_IN(poiStressPoints);

   // break existing connection
   if (m_POIStressPoints!=NULL)
   {
      hr = CrUnadvise(m_POIStressPoints, this, IID_IPOIStressPointsEvents, m_POIStressPointsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_POIStressPoints = poiStressPoints;

   // establish cp with new collection
   hr = CrAdvise(m_POIStressPoints, this, IID_IPOIStressPointsEvents, &m_POIStressPointsCookie);
   if (FAILED(hr))
      return hr;

   // assign new collection
   m_POIStressPoints = poiStressPoints;

   Fire_OnPOIChanged(this, cgtStress);

	return S_OK;
}

STDMETHODIMP CPOI::get_POIStressPoints(IPOIStressPoints **poiStressPoints)
{
	CHECK_RETOBJ(poiStressPoints);

   HRESULT hr;

   // create stress point collections on demand if needed
   if (m_POIStressPoints==NULL)
   {
      CComObject<CPOIStressPoints>* pcsp;
      hr = CComObject<CPOIStressPoints>::CreateInstance(&pcsp);
      if (FAILED(hr))
         return hr;

      m_POIStressPoints = pcsp;

      hr = CrAdvise(m_POIStressPoints, this, IID_IPOIStressPointsEvents, &m_POIStressPointsCookie);
      if (FAILED(hr))
         return hr;
   }


   return m_POIStressPoints.CopyTo(poiStressPoints);
}

STDMETHODIMP CPOI::Clone(IPOI **ppCS)
{
   CHECK_RETOBJ(ppCS);

   // create a new stress point collection and fill it up
   CComObject<CPOI>* pnew;
   HRESULT hr = CComObject<CPOI>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IPOI> pscs(pnew); // for reference count

   pnew->m_ID         = m_ID;
   pnew->m_Location   = m_Location;  
   pnew->m_MemberType = m_MemberType;
   pnew->m_MemberID   = m_MemberID;


   if (m_POIStressPoints!=NULL)
   {
      CComPtr<IPOIStressPoints> spclone;
      hr = m_POIStressPoints->Clone(&spclone);
      if (FAILED(hr))
         return hr;

      hr = pscs->putref_POIStressPoints(spclone);
      if (FAILED(hr))
         return hr;
   }

   return pscs.CopyTo(ppCS);
}

HRESULT CPOI::OnPOIStressPointsChanged(IPOIStressPoints*)
{
   Fire_OnPOIChanged(this, cgtStress);
   return S_OK;
}

HRESULT CPOI::OnPOIStressPointsAdded(IPOIStressPointsItem*)
{
   Fire_OnPOIChanged(this, cgtStress);
   return S_OK;
}

HRESULT CPOI::OnPOIStressPointsBeforeRemove(IPOIStressPointsItem*)
{
   Fire_OnPOIChanged(this, cgtStress);
   return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CPOI::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("POI"));
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
      hr = pload->get_Property(_bstr_t("ID"),&var);
      if (FAILED(hr))
         return hr;

      m_ID = var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("Location"),&var);
      if (FAILED(hr))
         return hr;

      m_Location = var;
      var.Clear();

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

      hr = pload->BeginUnit(CComBSTR("POIStressPoints"));
      if (FAILED(hr))
         return hr;

      {
         hr = pload->get_Property(_bstr_t("IsPOIStressPoints"),&var);
         if (FAILED(hr))
            return hr;

         long is_sp = var;

         if (is_sp!=0)
         {
            CComPtr<IPOIStressPoints> sps;
            hr = pload->get_Property(_bstr_t("POIStressPoints"),&var);
            if (FAILED(hr))
               return hr;

            hr = _CopyVariantToInterface<IPOIStressPoints>::copy(&sps, &var);
            if (FAILED(hr))
               return STRLOAD_E_INVALIDFORMAT;

            hr = putref_POIStressPoints(sps);
            if (FAILED(hr))
               return hr;
         }
      }

      VARIANT_BOOL eb;
      hr = pload->EndUnit(&eb);
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

STDMETHODIMP CPOI::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("POI"), MY_VER);
      hr = psave->put_Property(CComBSTR("ID"),_variant_t(m_ID));
      hr = psave->put_Property(CComBSTR("Location"),_variant_t(m_Location));
      _bstr_t type = MemberTypeToString(m_MemberType);

      hr = psave->put_Property(CComBSTR("MemberType"),_variant_t(type));

      hr = psave->put_Property(CComBSTR("MemberID"),_variant_t(m_MemberID));

      {
         // stress points 
         hr = psave->BeginUnit(CComBSTR("POIStressPoints"), MY_VER);

         if (m_POIStressPoints==NULL)
         {
            hr = psave->put_Property(CComBSTR("IsPOIStressPoints"),_variant_t((long)0));
         }
         else
         {
            hr = psave->put_Property(CComBSTR("IsPOIStressPoints"),_variant_t((long)1));

            hr = psave->put_Property(CComBSTR("POIStressPoints"),_variant_t(m_POIStressPoints));
         }

         hr = psave->EndUnit();
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IPOI);
   }

   return S_OK;
}


