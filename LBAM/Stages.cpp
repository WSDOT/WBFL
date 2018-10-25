///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// Stages.cpp : Implementation of CStages
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "Stages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStages

STDMETHODIMP CStages::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStages
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStages::OnStageChanged(/*[in]*/IStage* pStage, ChangeType change)
{
   Fire_OnStagesChanged(pStage, change);
   return S_OK;
}

STDMETHODIMP CStages::Clone(IStages* *pColl)
{
   CHECK_RETOBJ(pColl);

   // create a new  collection and fill it up
   CComObject<CStages>* pnew;
   HRESULT hr = CComObject<CStages>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<IStages> spisms(pnew);

   // clone properties

   // clone collection
   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<IStage> isp;
      
      // deep clone
      hr = it->second.m_T->Clone(&isp);
      if (FAILED(hr))
         return hr;

      // this call sets up connection points
      hr = spisms->Add(isp);
      if (FAILED(hr))
         return hr;
   }

   return spisms.CopyTo(pColl);
}

STDMETHODIMP CStages::Insert(StageIndexType relPos, IStage *pstage)
{
   CHECK_IN(pstage);

   // need to check for duplicate stage names
   CComBSTR name;
   HRESULT hr = pstage->get_Name(&name);
   if (FAILED(hr))
      return hr;

   IStage* pstg = Find(name);
   if (pstg)
   {
      _bstr_t msg = CreateErrorMsg1S(IDS_DUPLICATE_STAGE, name);
      return AtlReportError(CLSID_Stages, (const wchar_t*)msg, IID_IStages, WCC_E_NAME_ALREADY_EXISTS);
    }
   else
   {
      return PersistentStageCollImpl::Insert(relPos, pstage);
   }

   return S_OK;
}


STDMETHODIMP CStages::Add(IStage *pstage)
{
   CHECK_IN(pstage);

   // need to check for duplicate stage names
   CComBSTR name;
   HRESULT hr = pstage->get_Name(&name);
   if (FAILED(hr))
      return hr;

   IStage* pstg = Find(name);
   if (pstg)
   {
      _bstr_t msg = CreateErrorMsg1S(IDS_DUPLICATE_STAGE, name);
      return AtlReportError(CLSID_Stages, (const wchar_t*)msg, IID_IStages, WCC_E_NAME_ALREADY_EXISTS);
    }
   else
   {
      return PersistentStageCollImpl::Add(pstage);
   }

   return S_OK;
}

STDMETHODIMP CStages::FindIndex(/*[in]*/ BSTR name, /*[out,retval]*/StageIndexType* index)
{
   CHECK_IN(name);
   CHECK_RETVAL(index);

   // linear search
   CComBSTR cnam(name);
   StageIndexType i=0;
   for (iterator it= begin(); it != end(); it++)
   {
      CComBSTR bnam;
      HRESULT hr = it->second.m_T->get_Name(&bnam);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return 0;
      }

      if ( cnam == bnam )
      {
         *index=i;
         return S_OK;
      }
      else
         i++;
   }

   *index = -1;
   return S_OK;
}


IStage* CStages::Find(const CComBSTR& name)
{
   // linear search
   for (iterator it= begin(); it != end(); it++)
   {
      CComBSTR bnam;
      HRESULT hr = it->second.m_T->get_Name(&bnam);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return 0;
      }

      if ( name == bnam )
         return it->second.m_T;
   }

   return 0;
}

STDMETHODIMP CStages::RemoveByIndex(StageIndexType idx)
{
   return PersistentStageCollImpl::Remove(idx);
}

STDMETHODIMP CStages::RemoveByName(BSTR name)
{
   StageIndexType idx = 0;

   CComBSTR tname(name);
   for (iterator it= begin(); it != end(); it++)
   {
      CComBSTR bnam;
      HRESULT hr = it->second.m_T->get_Name(&bnam);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }

      if ( tname == bnam )
      {
         return PersistentStageCollImpl::Remove(idx);
      }

      idx++;
   }

   _bstr_t msg = CreateErrorMsg1S(IDS_E_STAGE_NOT_EXISTS, name);
   return AtlReportError(CLSID_Stages, (const wchar_t*)msg, IID_IStages, LBAM_E_STAGE_NOT_EXISTS);
}