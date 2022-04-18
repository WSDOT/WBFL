///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include "WBFLLBAM.h"
#include "LoadCombination.h"
#include "LBAMUtils.h"
#include "LBAM.hh"
#include "WBFLComCollections.h"

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
		&IID_ILoadCombination
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
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
      Fire_OnLoadCombinationChanged(this, cgtDescription);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::GetLiveLoadModelCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LiveLoadModelTypes.size();
   return S_OK;
}

STDMETHODIMP CLoadCombination::GetLiveLoadModel(CollectionIndexType index,LiveLoadModelType *pVal)
{
   if ( !IsValidIndex(index,m_LiveLoadModelTypes) )
      return E_INVALIDARG;

   CHECK_RETVAL(pVal);
   *pVal = m_LiveLoadModelTypes[index];
   return S_OK;
}

STDMETHODIMP CLoadCombination::AddLiveLoadModel(LiveLoadModelType newVal)
{
   if (newVal < lltNone || lltPermitSpecialRating < newVal)
      return E_INVALIDARG;

   std::vector<LiveLoadModelType>::iterator iter( m_LiveLoadModelTypes.begin() );
   std::vector<LiveLoadModelType>::iterator iterend( m_LiveLoadModelTypes.end() );
   for (; iter != iterend; iter++ )
   {
      if ( *iter == newVal )
         return S_OK;
   }

   m_LiveLoadModelTypes.push_back(newVal);
   Fire_OnLoadCombinationChanged(this, cgtCombination);

   return S_OK;
}

STDMETHODIMP CLoadCombination::RemoveLiveLoadModel(CollectionIndexType index)
{
   if ( IsValidIndex(index,m_LiveLoadModelTypes) )
      return E_INVALIDARG;

   m_LiveLoadModelTypes.erase(m_LiveLoadModelTypes.begin() + index);
   return S_OK;
}

STDMETHODIMP CLoadCombination::ClearLiveLoadModel()
{
   m_LiveLoadModelTypes.clear();
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
      Fire_OnLoadCombinationChanged(this, cgtCombination);
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
      if ( IsValidIndex(index,m_LoadCaseFactors) )
      {
         CComBSTR tmp(newName);
         if (tmp.Length()>0)
         {
            LoadCaseFactor& rlc = m_LoadCaseFactors[index];
            rlc.m_LoadCase = newName;
            rlc.m_MinFactor = minFactor;
            rlc.m_MaxFactor = maxFactor;
            Fire_OnLoadCombinationChanged(this, cgtCombination);
            return S_OK;
         }
         else
         {
            THROW_LBAM(BLANK_NAMES_NOT_ALLOWED);
         }
      }
      else
         return E_INVALIDARG;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombination);
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
         Fire_OnLoadCombinationChanged(this, cgtCombination);
      }
      else
      {
         THROW_LBAM(BLANK_NAMES_NOT_ALLOWED);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::FindLoadCaseFactor(BSTR loadCaseName, Float64* minFactor, Float64* maxFactor)
{
   CHECK_RETVAL(minFactor);
   CHECK_RETVAL(maxFactor);

   LoadCaseFactorContainer::iterator iter( m_LoadCaseFactors.begin() );
   LoadCaseFactorContainer::iterator iterend( m_LoadCaseFactors.end() );
   for ( ; iter != iterend; iter++ )
   {
      LoadCaseFactor& lcFactor = *iter;
      if ( lcFactor.m_LoadCase == CComBSTR(loadCaseName) )
      {
         *minFactor = lcFactor.m_MinFactor;
         *maxFactor = lcFactor.m_MaxFactor;

         return S_OK;
      }
   }

   return S_FALSE;
}

STDMETHODIMP CLoadCombination::GetLoadCaseFactor(CollectionIndexType index, BSTR *loadCaseName, Float64 *minFactor, Float64 *maxFactor)
{
   CHECK_RETOBJ(loadCaseName);
   CHECK_RETVAL(minFactor);
   CHECK_RETVAL(maxFactor);

   if ( IsValidIndex(index,m_LoadCaseFactors) )
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
      Fire_OnLoadCombinationChanged(this, cgtCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::RemoveLoadCaseFactor(CollectionIndexType index)
{
   try
   {
      if ( IsValidIndex(index,m_LoadCaseFactors) )
      {
         LoadCaseFactorIterator it( m_LoadCaseFactors.begin() );
         it += index;
         m_LoadCaseFactors.erase(it);
         Fire_OnLoadCombinationChanged(this, cgtCombination);
         return S_OK;
      }
      else
         return E_INVALIDARG;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::Clone(ILoadCombination**clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CLoadCombination>* pnew;
   HRESULT hr = CComObject<CLoadCombination>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILoadCombination> pscs(pnew); // for reference count

   pnew->m_Name                 = m_Name;
   pnew->m_Description          = m_Description;
   pnew->m_ItemData             = m_ItemData;
   pnew->m_LiveLoadModelTypes   = m_LiveLoadModelTypes;
   pnew->m_LiveLoadFactor       = m_LiveLoadFactor;
   pnew->m_LoadCaseFactors      = m_LoadCaseFactors;
   pnew->m_LoadCombinationType  = m_LoadCombinationType;
   pnew->m_LiveLoadModelApplicationType  = m_LiveLoadModelApplicationType;

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

   Fire_OnLoadCombinationChanged(this, cgtUserItemData);

	return S_OK;
}

STDMETHODIMP CLoadCombination::get_LoadCombinationType(LoadCombinationType *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_LoadCombinationType;

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_LoadCombinationType(LoadCombinationType newVal)
{
	if (newVal != m_LoadCombinationType)
   {
      if (newVal<lctService || newVal>lctUserDefined)
         return E_INVALIDARG;

      m_LoadCombinationType = newVal;
      Fire_OnLoadCombinationChanged(this, cgtCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCombination::get_LiveLoadModelApplicationType(LiveLoadModelApplicationType *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_LiveLoadModelApplicationType;

	return S_OK;
}

STDMETHODIMP CLoadCombination::put_LiveLoadModelApplicationType(LiveLoadModelApplicationType newVal)
{
	if (newVal != m_LiveLoadModelApplicationType)
   {
      if (newVal<llmaEnvelope || newVal>llmaSum)
         return E_INVALIDARG;

      m_LiveLoadModelApplicationType = newVal;
      Fire_OnLoadCombinationChanged(this, cgtCombination);
   }

	return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=3.0;
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

   if (ver>MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      _variant_t var;
      hr = pload->get_Property(_bstr_t("Name"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t name(var);
      m_Name = (LPCTSTR)name;

      var.Clear();
      hr = pload->get_Property(_bstr_t("Description"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t desc(var);
      m_Description = (LPCTSTR)desc;

      hr = pload->get_Property(_bstr_t("ItemData"),&m_ItemData);
      if (FAILED(hr))
         return hr;

      if ( ver < 2.0 )
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("LiveLoadModelType"),&var);
         if (FAILED(hr))
            return hr;

         long llt = var;
         if (llt==lltNone)
         {
            m_LiveLoadModelTypes.push_back(lltNone);
         }
		   else if (llt==lltDeflection)
         {
            m_LiveLoadModelTypes.push_back(lltDeflection);
         }
		   else if (llt==lltDesign)
         {
            m_LiveLoadModelTypes.push_back(lltDesign);
         }
		   else if (llt==lltPedestrian)
         {
            m_LiveLoadModelTypes.push_back(lltPedestrian);
         }
		   else if (llt==lltFatigue)
         {
            m_LiveLoadModelTypes.push_back(lltFatigue);
         }
		   else if (llt==lltPermit)
         {
            m_LiveLoadModelTypes.push_back(lltPermit);
         }
		   else if (llt==lltSpecial)
         {
            m_LiveLoadModelTypes.push_back(lltSpecial);
         }
         else if (llt==lltLegalRoutineRating)
         {
            m_LiveLoadModelTypes.push_back(lltLegalRoutineRating);
         }
         else if (llt==lltLegalSpecialRating)
         {
            m_LiveLoadModelTypes.push_back(lltLegalSpecialRating);
         }
         else if (llt==lltPermitRoutineRating)
         {
            m_LiveLoadModelTypes.push_back(lltPermitRoutineRating);
         }
         else if (llt==lltPermitSpecialRating)
         {
            m_LiveLoadModelTypes.push_back(lltPermitSpecialRating);
         }
         else
         {
            ATLASSERT(false);
            return STRLOAD_E_INVALIDFORMAT;
         }
      }
      else
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("LiveLoadModelCount"),&var);
         if ( FAILED(hr) )
            return hr;

         CollectionIndexType count = var.ulVal;
         for ( CollectionIndexType i = 0; i < count; i++ )
         {
            var.Clear();
            hr = pload->get_Property(_bstr_t("LiveLoadModelType"),&var);
            LiveLoadModelType llt = (LiveLoadModelType)(var.lVal);
            m_LiveLoadModelTypes.push_back(llt);
         }
      }

      var.Clear();
      hr = pload->get_Property(_bstr_t("LiveLoadFactor"),&var);
      if (FAILED(hr))
         return hr;
   
      m_LiveLoadFactor = var;

      var.Clear();
      hr = pload->get_Property(_bstr_t("LoadCombinationType"),&var);
      if (FAILED(hr))
         return hr;

      long llt = var;
      m_LoadCombinationType = (LoadCombinationType)llt;

      if ( ver >= 3.0 )
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("LiveLoadModelApplicationType"),&var);
         if (FAILED(hr))
            return hr;

         llt = var;
         m_LiveLoadModelApplicationType = (LiveLoadModelApplicationType)llt;
      }

      var.Clear();
      hr = pload->get_Property(_bstr_t("Count"),&var);
      if (FAILED(hr))
         return hr;

      CollectionIndexType count = var;
      m_LoadCaseFactors.clear();
      m_LoadCaseFactors.reserve(count);
      for (CollectionIndexType i = 0; i<count; i++)
      {
         hr = pload->BeginUnit(CComBSTR("LoadCaseFactor"));
         if (FAILED(hr))
            return hr;

         LoadCaseFactor lcf;

         var.Clear();
         hr = pload->get_Property(_bstr_t("LoadCase"),&var);
         if (FAILED(hr))
            return hr;

         _bstr_t lcname(var);
         lcf.m_LoadCase = (LPCTSTR)lcname;

         var.Clear();
         hr = pload->get_Property(_bstr_t("MinFactor"),&var);
         if (FAILED(hr))
            return hr;

         lcf.m_MinFactor = var;

         var.Clear();
         hr = pload->get_Property(_bstr_t("MaxFactor"),&var);
         if (FAILED(hr))
            return hr;

         lcf.m_MaxFactor = var;

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
      hr = psave->put_Property(CComBSTR("Name"),_variant_t(m_Name));
      hr = psave->put_Property(CComBSTR("Description"),_variant_t(m_Description));
      hr = psave->put_Property(CComBSTR("ItemData"), m_ItemData);

      hr = psave->put_Property(CComBSTR("LiveLoadModelCount"),_variant_t(m_LiveLoadModelTypes.size()));
      for ( CollectionIndexType i = 0; i < (CollectionIndexType)m_LiveLoadModelTypes.size(); i++ )
      {
         hr = psave->put_Property(CComBSTR("LiveLoadModelType"), _variant_t(m_LiveLoadModelTypes[i]));
      }

      hr = psave->put_Property(CComBSTR("LiveLoadFactor"), _variant_t(m_LiveLoadFactor));
      hr = psave->put_Property(CComBSTR("LoadCombinationType"), _variant_t(m_LoadCombinationType));
      hr = psave->put_Property(CComBSTR("LiveLoadModelApplicationType"), _variant_t(m_LiveLoadModelApplicationType)); // Added in Version 3

      CollectionIndexType count = m_LoadCaseFactors.size();
      hr = psave->put_Property(CComBSTR("Count"),_variant_t(count));

      for ( CollectionIndexType i = 0; i<count; i++)
      {
         LoadCaseFactor& rcf = m_LoadCaseFactors[i];

         hr = psave->BeginUnit(CComBSTR("LoadCaseFactor"), MY_VER);
         hr = psave->put_Property(CComBSTR("LoadCase"),_variant_t(rcf.m_LoadCase ));
         hr = psave->put_Property(CComBSTR("MinFactor"),_variant_t(rcf.m_MinFactor));
         hr = psave->put_Property(CComBSTR("MaxFactor"),_variant_t(rcf.m_MaxFactor));
         hr = psave->EndUnit();
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCombination);
   }

   return S_OK;
}


