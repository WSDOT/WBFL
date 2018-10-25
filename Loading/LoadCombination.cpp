///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2013  Washington State Department of Transportation
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

// LoadCombination.cpp : Implementation of CLoadCombination
#include "stdafx.h"
#include "WBFLLoading.h"
#include "LoadCombination.h"
#include "LoadingUtils.h"
#include "Loading.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCombination

STDMETHODIMP CLoadCombination::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ldILoadCombination
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCombination::get_Name(BSTR *pVal)
{
	CHECK_RETOBJ(pVal);
   *pVal = m_Name.Copy();

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_Name(BSTR newVal)
{
   CHECK_IN(newVal);
   CComBSTR name(newVal);
   if (name.Length() == 0)
      return E_INVALIDARG;

   if (name != m_Name)
   {
      CComBSTR oldnam(m_Name);
      m_Name = name;
      Fire_OnLoadCombinationRenamed(oldnam, newVal);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::get_Description(BSTR *pVal)
{
	CHECK_RETOBJ(pVal);
   *pVal = m_Description.Copy();

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_Description(BSTR newVal)
{
   CHECK_IN(newVal);
   CComBSTR desc(newVal);

   if (desc != m_Description)
   {
      m_Description = desc;
      Fire_OnLoadCombinationChanged(this, ldcgDescription);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::get_LiveLoadModel(ldLiveLoadModelType *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_LiveLoadModelType;

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_LiveLoadModel(ldLiveLoadModelType newVal)
{
	if (newVal != m_LiveLoadModelType)
   {
      if (newVal<ldltNone || newVal>ldltSpecial)
         return E_INVALIDARG;

      m_LiveLoadModelType = newVal;
      Fire_OnLoadCombinationChanged(this, ldcgCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::get_LiveLoadFactor(Float64 *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_LiveLoadFactor;

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_LiveLoadFactor(Float64 newVal)
{
	if (newVal != m_LiveLoadFactor)
   {
      m_LiveLoadFactor = newVal;
      Fire_OnLoadCombinationChanged(this, ldcgCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::get_LoadCaseFactorCount(CollectionIndexType *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_LoadCaseFactors.size();

	return S_OK;
}

STDMETHODIMP CLoadCombination::SetLoadCaseFactor(CollectionIndexType index, BSTR newName, Float64 minFactor, Float64 maxFactor)
{
   CHECK_IN(newName);
   try
   {
      if (index>=0 && index<(CollectionIndexType)m_LoadCaseFactors.size())
      {
         CComBSTR tmp(newName);
         if (tmp.Length()>0)
         {
            LoadCaseFactor& rlc = m_LoadCaseFactors[index];
            rlc.m_LoadCase = newName;
            rlc.m_MinFactor = minFactor;
            rlc.m_MaxFactor = maxFactor;
            Fire_OnLoadCombinationChanged(this, ldcgCombination);
            return S_OK;
         }
         else
         {
            THROW_EXCEPTION(BLANK_NAMES_NOT_ALLOWED);
         }
      }
      else
         return E_INVALIDARG;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldILoadCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::AddLoadCaseFactor(BSTR loadCaseName, Float64 minFactor, Float64 maxFactor)
{
   CHECK_IN(loadCaseName);
   try
   {
      CComBSTR tmp(loadCaseName);
      if (tmp.Length()>0)
      {
	      m_LoadCaseFactors.push_back(LoadCaseFactor(loadCaseName,minFactor, maxFactor));
         Fire_OnLoadCombinationChanged(this, ldcgCombination);
      }
      else
      {
         THROW_EXCEPTION(BLANK_NAMES_NOT_ALLOWED);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldILoadCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::GetLoadCaseFactor(CollectionIndexType index, BSTR *loadCaseName, Float64 *minFactor, Float64 *maxFactor)
{
   CHECK_RETOBJ(loadCaseName);
   CHECK_RETVAL(minFactor);
   CHECK_RETVAL(maxFactor);

   if (index>=0 && index<(CollectionIndexType)m_LoadCaseFactors.size())
   {
       LoadCaseFactor& rlc = m_LoadCaseFactors[index];
       *minFactor = rlc.m_MinFactor;
       *maxFactor = rlc.m_MaxFactor;
       return rlc.m_LoadCase.CopyTo(loadCaseName);
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CLoadCombination::Clear()
{
   if (!m_LoadCaseFactors.empty())
   {
   	m_LoadCaseFactors.clear();
      Fire_OnLoadCombinationChanged(this, ldcgCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::RemoveLoadCaseFactor(CollectionIndexType index)
{
   try
   {
      if (index>=0 && index<(CollectionIndexType)m_LoadCaseFactors.size())
      {
         LoadCaseFactorIterator it=m_LoadCaseFactors.begin();
         it += index;
         m_LoadCaseFactors.erase(it);
         Fire_OnLoadCombinationChanged(this, ldcgCombination);
         return S_OK;
      }
      else
         return E_INVALIDARG;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldILoadCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::Clone(ldILoadCombination**clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CLoadCombination>* pnew;
   HRESULT hr = CComObject<CLoadCombination>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ldILoadCombination> pscs(pnew); // for reference count

   pnew->m_Name                 = m_Name;
   pnew->m_Description          = m_Description;
   pnew->m_ItemData             = m_ItemData;
   pnew->m_LiveLoadModelType    = m_LiveLoadModelType;
   pnew->m_LiveLoadFactor       = m_LiveLoadFactor;
   pnew->m_LoadCaseFactors      = m_LoadCaseFactors;
   pnew->m_LoadCombinationType  = m_LoadCombinationType;

   return pscs.CopyTo(clone);
}

STDMETHODIMP CLoadCombination::get_ItemData(VARIANT *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_ItemData;

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_ItemData(VARIANT newVal)
{
   // don't allow empty variants - the persistence system cannot handle them
   if (newVal.vt==VT_EMPTY)
      return E_INVALIDARG;

   m_ItemData.Copy(&newVal);

   Fire_OnLoadCombinationChanged(this, ldcgUserItemData);

	return S_OK;
}

STDMETHODIMP CLoadCombination::get_LoadCombinationType(ldLoadCombinationType *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_LoadCombinationType;

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_LoadCombinationType(ldLoadCombinationType newVal)
{
	if (newVal != m_LoadCombinationType)
   {
      if (newVal<ldctService || newVal>ldctUserDefined)
         return E_INVALIDARG;

      m_LoadCombinationType = newVal;
      Fire_OnLoadCombinationChanged(this, ldcgCombination);
   }

	return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLoadCombination::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LoadCombination"));
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
      hr = pload->get_Property(CComBSTR("Name"),&var);
      if (FAILED(hr))
         return hr;

      m_Name = var.bstrVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("Description"),&var);
      if (FAILED(hr))
         return hr;

      m_Description = var.bstrVal;

      hr = pload->get_Property(CComBSTR("ItemData"),&m_ItemData);
      if (FAILED(hr))
         return hr;

      var.Clear();
      hr = pload->get_Property(CComBSTR("ldLiveLoadModelType"),&var);
      if (FAILED(hr))
         return hr;

      ldLiveLoadModelType llt = (ldLiveLoadModelType)var.lVal;
      if (llt==ldltNone)
      {
         m_LiveLoadModelType = ldltNone;
      }
		else if (llt==ldltDeflection)
      {
         m_LiveLoadModelType = ldltDeflection;
      }
		else if (llt==ldltDesign)
      {
         m_LiveLoadModelType = ldltDesign;
      }
		else if (llt==ldltPedestrian)
      {
         m_LiveLoadModelType = ldltPedestrian;
      }
		else if (llt==ldltFatigue)
      {
         m_LiveLoadModelType = ldltFatigue;
      }
		else if (llt==ldltPermit)
      {
         m_LiveLoadModelType = ldltPermit;
      }
		else if (llt==ldltSpecial)
      {
         m_LiveLoadModelType = ldltSpecial;
      }
      else
      {
         ATLASSERT(0);
         return STRLOAD_E_INVALIDFORMAT;
      }

      var.Clear();
      hr = pload->get_Property(CComBSTR("LiveLoadFactor"),&var);
      if (FAILED(hr))
         return hr;
   
      m_LiveLoadFactor = var.dblVal;

      var.Clear();
      hr = pload->get_Property(CComBSTR("ldLoadCombinationType"),&var);
      if (FAILED(hr))
         return hr;

      ldLoadCombinationType lct = (ldLoadCombinationType)var.lVal;
      if (lct==ldctService)
      {
         m_LoadCombinationType = ldctService;
      }
      else if (lct==ldctStrength)
      {
         m_LoadCombinationType = ldctStrength;
      }
      else if (lct==ldctExtremeEvent)
      {
         m_LoadCombinationType = ldctExtremeEvent;
      }
      else if (lct==ldctFatigue)
      {
         m_LoadCombinationType = ldctFatigue;
      }
      else if (lct==ldctUserDefined)
      {
         m_LoadCombinationType = ldctUserDefined;
      }
      else
      {
         ATLASSERT(0);
         return STRLOAD_E_INVALIDFORMAT;
      }

      var.Clear();
      hr = pload->get_Property(CComBSTR("Count"),&var);
      if (FAILED(hr))
         return hr;

      CollectionIndexType count = var.iVal;
      m_LoadCaseFactors.clear();
      m_LoadCaseFactors.reserve(count);
      for (CollectionIndexType i=0; i<count; i++)
      {
         hr = pload->BeginUnit(CComBSTR("LoadCaseFactor"));
         if (FAILED(hr))
            return hr;

         LoadCaseFactor lcf;

         var.Clear();
         hr = pload->get_Property(CComBSTR("LoadCase"),&var);
         if (FAILED(hr))
            return hr;

         lcf.m_LoadCase = var.bstrVal;

         var.Clear();
         hr = pload->get_Property(CComBSTR("MinFactor"),&var);
         if (FAILED(hr))
            return hr;

         lcf.m_MinFactor = var.dblVal;

         var.Clear();
         hr = pload->get_Property(CComBSTR("MaxFactor"),&var);
         if (FAILED(hr))
            return hr;

         lcf.m_MaxFactor = var.dblVal;

         VARIANT_BOOL eb;
         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;

         m_LoadCaseFactors.push_back(lcf);
      }
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CLoadCombination::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("LoadCombination"), MY_VER);
      hr = psave->put_Property(CComBSTR("Name"),CComVariant(m_Name));
      hr = psave->put_Property(CComBSTR("Description"),CComVariant(m_Description));
      hr = psave->put_Property(CComBSTR("ItemData"), m_ItemData);
      hr = psave->put_Property(CComBSTR("ldLiveLoadModelType"), CComVariant(m_LiveLoadModelType));
      hr = psave->put_Property(CComBSTR("LiveLoadFactor"), CComVariant(m_LiveLoadFactor));
      hr = psave->put_Property(CComBSTR("ldLoadCombinationType"), CComVariant(m_LoadCombinationType));

      CollectionIndexType count = m_LoadCaseFactors.size();
      hr = psave->put_Property(CComBSTR("Count"),CComVariant(count));

      for (CollectionIndexType i=0; i<count; i++)
      {
         LoadCaseFactor& rcf = m_LoadCaseFactors[i];

         hr = psave->BeginUnit(CComBSTR("LoadCaseFactor"), MY_VER);
         hr = psave->put_Property(CComBSTR("LoadCase"),CComVariant(rcf.m_LoadCase ));
         hr = psave->put_Property(CComBSTR("MinFactor"),CComVariant(rcf.m_MinFactor));
         hr = psave->put_Property(CComBSTR("MaxFactor"),CComVariant(rcf.m_MaxFactor));
         hr = psave->EndUnit();
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ldILoadCombination);
   }

   return S_OK;
}


