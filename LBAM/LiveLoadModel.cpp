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

// LiveLoadModel.cpp : Implementation of CLiveLoadModel
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "LiveLoadModel.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModel
STDMETHODIMP CLiveLoadModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiveLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLiveLoadModel::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty collection of stress points and set
   // up a connection point to it
   hr = m_VehicularLoads.CoCreateInstance(CLSID_VehicularLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_VehicularLoads, this, IID_IVehicularLoadsEvents, &m_VehicularLoadsCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CLiveLoadModel::FinalRelease()
{
   ATLASSERT(!!m_VehicularLoads);
   HRESULT hr = CrUnadvise(m_VehicularLoads, this, IID_IVehicularLoadsEvents, m_VehicularLoadsCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CLiveLoadModel::get_Name(BSTR *pVal)
{
   CHECK_RETOBJ(pVal);

	*pVal = m_Name.Copy();

	return S_OK;
}

STDMETHODIMP CLiveLoadModel::put_Name(BSTR newVal)
{
   CHECK_IN(newVal);

	if (newVal!=m_Name)
   {
      m_Name = newVal;
      Fire_OnLiveLoadModelChanged(this, cgtDescription);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadModel::get_DistributionFactorType(DistributionFactorType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_DistributionFactorType;

	return S_OK;
}

STDMETHODIMP CLiveLoadModel::put_DistributionFactorType(DistributionFactorType newVal)
{
	if (newVal!=m_DistributionFactorType)
   {
      if (newVal<dftNone || newVal>dftPedestrian)
         return E_INVALIDARG;

      m_DistributionFactorType = newVal;
      Fire_OnLiveLoadModelChanged(this, cgtLiveLoad);
   }

	return S_OK;
}

STDMETHODIMP CLiveLoadModel::Clear()
{
	m_VehicularLoads->Clear();
   m_Name.Empty();
   Fire_OnLiveLoadModelChanged(this, cgtLiveLoad);

	return S_OK;
}

STDMETHODIMP CLiveLoadModel::get_VehicularLoads(IVehicularLoads **pVal)
{
   CHECK_RETOBJ(pVal);

	return m_VehicularLoads.CopyTo(pVal);
}

STDMETHODIMP CLiveLoadModel::putref_VehicularLoads(IVehicularLoads *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_VehicularLoads.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_VehicularLoads)
   {
      hr = CrUnadvise(m_VehicularLoads, this, IID_IVehicularLoadsEvents, m_VehicularLoadsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_VehicularLoads = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_VehicularLoads, this, IID_IVehicularLoadsEvents, &m_VehicularLoadsCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnLiveLoadModelChanged(this, cgtLiveLoad);

	return S_OK;
}

STDMETHODIMP CLiveLoadModel::OnVehicularLoadsChanged(IVehicularLoad* item, ChangeType change)
{
   Fire_OnLiveLoadModelChanged(this,change);
   return S_OK;
}
STDMETHODIMP CLiveLoadModel::OnVehicularLoadsRenamed(BSTR oldName, BSTR newName)
{
   Fire_OnLiveLoadModelChanged(this,cgtLiveLoad);
   return S_OK;
}
STDMETHODIMP CLiveLoadModel::OnVehicularLoadsAdded(IVehicularLoad* item)
{
   Fire_OnLiveLoadModelChanged(this,cgtLiveLoad);
   return S_OK;
}
STDMETHODIMP CLiveLoadModel::OnVehicularLoadsBeforeRemove(IVehicularLoad* item)
{
   Fire_OnLiveLoadModelChanged(this,cgtLiveLoad);
   return S_OK;
}



// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CLiveLoadModel::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LiveLoadModel"));
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

      m_Name = var.bstrVal;

      var.Clear();
      hr = pload->get_Property(_bstr_t("DistributionFactorType"),&var);
      if (FAILED(hr))
         return hr;

      long dt = var;
      if (dt==dftNone)
         m_DistributionFactorType=dftNone;
      else if (dt==dftSingleLane)
         m_DistributionFactorType=dftSingleLane;
	   else if(dt==dftMultipleLane)
         m_DistributionFactorType=dftMultipleLane;
	   else if(dt==dftFatigue)
         m_DistributionFactorType=dftFatigue;
      else if(dt==dftEnvelope)
         m_DistributionFactorType=dftEnvelope;
	   else if(dt==dftPedestrian)
         m_DistributionFactorType=dftPedestrian;
      else
      {
         ATLASSERT(false);
         return STRLOAD_E_INVALIDFORMAT;
      }

      var.Clear();
      hr = pload->get_Property(_bstr_t("VehicularLoads"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IVehicularLoads> pisps;
      hr = _CopyVariantToInterface<IVehicularLoads>::copy(&pisps, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_VehicularLoads(pisps);
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

STDMETHODIMP CLiveLoadModel::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);

   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("LiveLoadModel"), MY_VER);
      hr = psave->put_Property(CComBSTR("Name"),_variant_t(m_Name));
      hr = psave->put_Property(CComBSTR("DistributionFactorType"),_variant_t(m_DistributionFactorType));
      hr = psave->put_Property(CComBSTR("VehicularLoads"),_variant_t(m_VehicularLoads));
      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILiveLoadModel);
   }

   return hr;
}

STDMETHODIMP CLiveLoadModel::Clone(ILiveLoadModel **ppCS)
{
   CHECK_RETOBJ(ppCS);

   // create a new stress point collection and fill it up
   CComObject<CLiveLoadModel>* pnew;
   HRESULT hr = CComObject<CLiveLoadModel>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILiveLoadModel> pscs(pnew); // for reference count

   pnew->m_Name   = m_Name;
   pnew->m_DistributionFactorType  = m_DistributionFactorType;

   CComPtr<IVehicularLoads> psp;
   hr = m_VehicularLoads->Clone(&psp);
   if (FAILED(hr))
      return hr;

   hr = pscs->putref_VehicularLoads(psp);
   if (FAILED(hr))
      return hr;

   return pscs.CopyTo(ppCS);
}
