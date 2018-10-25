///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2016  Washington State Department of Transportation
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

// LoadCase.cpp : Implementation of CLoadCase
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LoadCase.h"
#include "LBAMUtils.h"
#include "LBAM.hh"

#include "WBFLComCollections.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadCase

STDMETHODIMP CLoadCase::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCase
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLoadCase::get_Name(BSTR *pVal)
{
	CHECK_RETOBJ(pVal);

   *pVal = m_Name.Copy();
   
	return S_OK;
}

STDMETHODIMP CLoadCase::put_Name(BSTR newVal)
{
   CHECK_IN(newVal);

   CComBSTR name(newVal);
   if (name.Length() == 0)
      return E_INVALIDARG;

   if (name != m_Name)
   {
      CComBSTR oldnam(m_Name);
      m_Name = name;
      Fire_OnLoadCaseRenamed(oldnam, newVal);
   }

	return S_OK;
}

STDMETHODIMP CLoadCase::get_Description(BSTR *pVal)
{
	CHECK_RETOBJ(pVal);
   *pVal = m_Description.Copy();

	return S_OK;
}

STDMETHODIMP CLoadCase::put_Description(BSTR newVal)
{
   CHECK_IN(newVal);

   CComBSTR desc(newVal);

   if (desc != m_Description)
   {
      m_Description = desc;
      Fire_OnLoadCaseChanged(this, cgtDescription);
   }

	return S_OK;
}

STDMETHODIMP CLoadCase::get_ItemData(VARIANT *pVal)
{
	CHECK_RETVAL(pVal);
   *pVal = m_ItemData;

	return S_OK;
}

STDMETHODIMP CLoadCase::put_ItemData(VARIANT newVal)
{
   // don't allow empty variants - the persistence system cannot handle them
   if (newVal.vt==VT_EMPTY)
      return E_INVALIDARG;

   m_ItemData.Copy(&newVal);

   Fire_OnLoadCaseChanged(this, cgtUserItemData);

	return S_OK;
}

STDMETHODIMP CLoadCase::Clear()
{
   if (!m_LoadGroups.empty())
   {
   	m_LoadGroups.clear();
      Fire_OnLoadCaseChanged(this, cgtCombination);
   }

	return S_OK;
}

STDMETHODIMP CLoadCase::get_LoadGroupCount(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
	
   *pVal = m_LoadGroups.size();

	return S_OK;
}

STDMETHODIMP CLoadCase::AddLoadGroup(BSTR loadGroupName)
{
   try
   {
      CComBSTR tmp(loadGroupName);
      if (tmp.Length()>0)
      {
	      m_LoadGroups.push_back(loadGroupName);
         Fire_OnLoadCaseChanged(this, cgtCombination);
      }
      else
      {
         THROW_LBAM(BLANK_NAMES_NOT_ALLOWED);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCase);
   }

	return S_OK;
}

STDMETHODIMP CLoadCase::GetLoadGroup(CollectionIndexType index, BSTR *loadGroupName)
{
   CHECK_RETOBJ(loadGroupName);

   if ( IsValidIndex(index,m_LoadGroups) )
   {
      return m_LoadGroups[index].CopyTo(loadGroupName);
   }
   else
      return E_INVALIDARG;
}

STDMETHODIMP CLoadCase::SetLoadGroup(CollectionIndexType index, BSTR newName)
{
   CHECK_IN(newName);

   try
   {
   if ( IsValidIndex(index,m_LoadGroups) )
      {
         CComBSTR tmp(newName);
         if (tmp.Length()>0)
         {
            m_LoadGroups[index] = tmp;
            Fire_OnLoadCaseChanged(this, cgtCombination);
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
      return DealWithExceptions(this, IID_ILoadCase);
   }

	return S_OK;
}

STDMETHODIMP CLoadCase::RemoveLoadGroup(BSTR loadGroupName)
{
   CHECK_IN(loadGroupName);

	CComBSTR tmp(loadGroupName);

   bool found = false;
   LoadGroupIterator it( m_LoadGroups.begin() );
   LoadGroupIterator itend( m_LoadGroups.end() );
   for (; it!=itend; it++)
   {
      if (tmp==*it)
      {
         m_LoadGroups.erase(it);
         found = true;
         break;
      }
   }

   if (found)
   {
      Fire_OnLoadCaseChanged(this, cgtCombination);
   	return S_OK;
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CLoadCase::RemoveLoadGroupByIndex(CollectionIndexType index)
{
   try
   {
      if ( IsValidIndex(index,m_LoadGroups) )
      {
         LoadGroupIterator it(m_LoadGroups.begin());
         it += index;
         m_LoadGroups.erase(it);
         Fire_OnLoadCaseChanged(this, cgtCombination);
         return S_OK;
      }
      else
         return E_INVALIDARG;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCase);
   }

	return S_OK;
}

STDMETHODIMP CLoadCase::Clone(ILoadCase** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CLoadCase>* pnew;
   HRESULT hr = CComObject<CLoadCase>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILoadCase> pscs(pnew); // for reference count

   pnew->m_Name                 = m_Name;
   pnew->m_Description          = m_Description;
   pnew->m_LoadGroups           = m_LoadGroups;
   pnew->m_ItemData             = m_ItemData;

   return pscs.CopyTo(clone);
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CLoadCase::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LoadCase"));
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

      var.Clear();
      hr = pload->get_Property(_bstr_t("Count"),&var);
      if (FAILED(hr))
         return hr;

      CollectionIndexType count = var;
      m_LoadGroups.clear();
      m_LoadGroups.reserve(count);
      for (CollectionIndexType i=0; i<count; i++)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("LoadGroup"),&var);
         if (FAILED(hr))
            return hr;

         _bstr_t lgname(var);
         m_LoadGroups.push_back((LPCTSTR)lgname);
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

STDMETHODIMP CLoadCase::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("LoadCase"), MY_VER);
      hr = psave->put_Property(CComBSTR("Name"),_variant_t(m_Name));
      hr = psave->put_Property(CComBSTR("Description"),_variant_t(m_Description));
      hr = psave->put_Property(CComBSTR("ItemData"), m_ItemData);

      CollectionIndexType count = m_LoadGroups.size();
      hr = psave->put_Property(CComBSTR("Count"),_variant_t(count));

      for (CollectionIndexType i=0; i<count; i++)
      {
         hr = psave->put_Property(CComBSTR("LoadGroup"),_variant_t(m_LoadGroups[i]));
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILoadCase);
   }

   return S_OK;
}


