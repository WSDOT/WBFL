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

// LiveLoad.cpp : Implementation of CLiveLoad
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LiveLoad.h"
#include "LBAMUtils.h"
#include "LiveLoadModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// live load names. Note that this sequence must match the enums in LiveLoadModelType
static LPCTSTR LL_NAMES[]={_T("Deflection"),_T("Design"),_T("Pedestrian"),_T("Fatigue"),_T("Permit"),_T("Special"),
_T("LegalRoutineRating"),_T("LegalSpecialRating"),_T("PermitRoutineRating"),_T("PermitSpecialRating")};

static const int NUM_LLM = sizeof(LL_NAMES)/sizeof(LPCTSTR);

/////////////////////////////////////////////////////////////////////////////
// CLiveLoad

STDMETHODIMP CLiveLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiveLoad
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CLiveLoad::CLiveLoad()
{
   for (int i=0; i<NUM_LLM; i++)
      m_Cookies[i]=0;
}

STDMETHODIMP CLiveLoad::FinalConstruct( )
{
   HRESULT hr;

   for (int i=0; i<NUM_LLM; i++)
   {
   
      CComObject<CLiveLoadModel>* poll;
      hr = CComObject<CLiveLoadModel>::CreateInstance(&poll);
      if (FAILED(hr))
         return hr;

      hr = PutLiveLoadModel((LiveLoadModelType)i, poll, false);
      if (FAILED(hr))
         return hr;
   }

   return S_OK;
}

void CLiveLoad::FinalRelease()
{
   // say goodbye to our models
   HRESULT hr;
   for (int i=0; i<NUM_LLM; i++)
   {
      if (m_Models[i] != NULL)
      {
         hr = CrUnadvise(m_Models[i], this, IID_ILiveLoadModelEvents, m_Cookies[i]);
         ATLASSERT(SUCCEEDED(hr));
      }
      else
         ATLASSERT(0); // should always have valid pointers
   }
}


// private function for putting model
HRESULT CLiveLoad::PutLiveLoadModel(LiveLoadModelType modelType, ILiveLoadModel *newVal, bool doFire)
{
	CHECK_IN(newVal);
   int mt = modelType;
   ATLASSERT(mt>=0 && mt<NUM_LLM);

   // don't bother if someone is assigning same collection
   if ( m_Models[mt].IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (m_Models[mt] != NULL)
   {
      hr = CrUnadvise(m_Models[mt], this, IID_ILiveLoadModelEvents, m_Cookies[mt]);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_Models[mt] = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_Models[mt], this, IID_ILiveLoadModelEvents, &m_Cookies[mt]);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   if (doFire)
      Fire_OnLiveLoadChanged(this, modelType);

   return S_OK;
}

STDMETHODIMP CLiveLoad::get_Design(ILiveLoadModel **pVal)
{
	return m_Models[lltDesign].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_Design(ILiveLoadModel *newVal)
{
   return PutLiveLoadModel(lltDesign, newVal);
}

STDMETHODIMP CLiveLoad::get_Deflection(ILiveLoadModel **pVal)
{
	return m_Models[lltDeflection].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_Deflection(ILiveLoadModel *newVal)
{
   return PutLiveLoadModel(lltDeflection, newVal);
}

STDMETHODIMP CLiveLoad::get_Fatigue(ILiveLoadModel **pVal)
{
	return m_Models[lltFatigue].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_Fatigue(ILiveLoadModel *newVal)
{
   return PutLiveLoadModel(lltFatigue, newVal);
}

STDMETHODIMP CLiveLoad::get_Permit(ILiveLoadModel **pVal)
{
	return m_Models[lltPermit].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_Permit(ILiveLoadModel *newVal)
{
   return PutLiveLoadModel(lltPermit, newVal);
}

STDMETHODIMP CLiveLoad::get_Special(ILiveLoadModel **pVal)
{
	return m_Models[lltSpecial].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_Special(ILiveLoadModel *newVal)
{
   return PutLiveLoadModel(lltSpecial, newVal);
}

STDMETHODIMP CLiveLoad::get_Pedestrian(ILiveLoadModel **pVal)
{
	return m_Models[lltPedestrian].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_Pedestrian(ILiveLoadModel *newVal)
{
   return PutLiveLoadModel(lltPedestrian, newVal);
}

STDMETHODIMP CLiveLoad::get_LegalRoutineRating(ILiveLoadModel* *pVal)
{
   return m_Models[lltLegalRoutineRating].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_LegalRoutineRating(ILiveLoadModel* newVal)
{
   return PutLiveLoadModel(lltLegalRoutineRating,newVal);
}

STDMETHODIMP CLiveLoad::get_LegalSpecialRating(ILiveLoadModel* *pVal)
{
   return m_Models[lltLegalSpecialRating].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_LegalSpecialRating(ILiveLoadModel* newVal)
{
   return PutLiveLoadModel(lltLegalSpecialRating,newVal);
}

STDMETHODIMP CLiveLoad::get_PermitRoutineRating(ILiveLoadModel* *pVal)
{
   return m_Models[lltPermitRoutineRating].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_PermitRoutineRating(ILiveLoadModel* newVal)
{
   return PutLiveLoadModel(lltPermitRoutineRating,newVal);
}

STDMETHODIMP CLiveLoad::get_PermitSpecialRating(ILiveLoadModel* *pVal)
{
   return m_Models[lltPermitSpecialRating].CopyTo(pVal);
}

STDMETHODIMP CLiveLoad::putref_PermitSpecialRating(ILiveLoadModel* newVal)
{
   return PutLiveLoadModel(lltPermitSpecialRating,newVal);
}

STDMETHODIMP CLiveLoad::Clear()
{
   for (int i=0; i<NUM_LLM; i++)
   {
      m_Models[i]->Clear();
      Fire_OnLiveLoadChanged(this, (LiveLoadModelType)i );
   }
	return S_OK;
}

STDMETHODIMP CLiveLoad::OnLiveLoadModelChanged(/*[in]*/ILiveLoadModel* model, ChangeType change)
{
   bool found=false;
   for (int i=0; i<NUM_LLM; i++)
   {
      if (m_Models[i].IsEqualObject(model))
      {
         // tell the world we've changed
         Fire_OnLiveLoadChanged(this, (LiveLoadModelType)i );
         found=true;
      }
   }

   ATLASSERT(found); // we should only be listening to our parts

   return S_OK;
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CLiveLoad::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LiveLoad"));
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

      // loop over llm types
      for (int i=0; i<NUM_LLM; i++)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t(LL_NAMES[i]),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<ILiveLoadModel> pisps;
         hr = _CopyVariantToInterface<ILiveLoadModel>::copy(&pisps, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         hr = PutLiveLoadModel( (LiveLoadModelType)i, pisps);
         if (FAILED(hr))
            return hr;
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

STDMETHODIMP CLiveLoad::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   HRESULT hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("LiveLoad"), MY_VER);
      if (FAILED(hr))
         return hr;

      for (int i=0; i<NUM_LLM; i++)
      {
         hr = psave->put_Property(CComBSTR(LL_NAMES[i]),_variant_t(m_Models[i]));
         if (FAILED(hr))
            return hr;
      }

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoad);
   }

   return hr;
}

STDMETHODIMP CLiveLoad::Clone(ILiveLoad **clone)
{
   CHECK_RETOBJ(clone);

   // create a new live load and fill it up
   CComObject<CLiveLoad>* pnew;
   HRESULT hr = CComObject<CLiveLoad>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILiveLoad> pscs(pnew); // for reference count

   // live load models
   for (int i=0; i<NUM_LLM; i++)
   {
      CComPtr<ILiveLoadModel> psp;
      hr = m_Models[i]->Clone(&psp);
      if (FAILED(hr))
         return hr;

      hr = PutLiveLoadModel( (LiveLoadModelType)i, psp);
      if (FAILED(hr))
         return hr;
   }

   return pscs.CopyTo(clone);
}

