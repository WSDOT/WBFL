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

// Model.cpp : Implementation of CModel
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "Model.h"
#include "LBAMUtils.h"
#include "LBAM.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// free functions


/////////////////////////////////////////////////////////////////////////////
// CModel

STDMETHODIMP CModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILBAMModel
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CModel::FinalConstruct( )
{
   HRESULT hr;
   // create a default, empty collection and set up a connection point to it
   hr = m_Spans.CoCreateInstance(CLSID_Spans);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Spans, this, IID_ISpansEvents, &m_SpansCookie);
   if (FAILED(hr))
      return hr;

   hr = m_SuperstructureMembers.CoCreateInstance(CLSID_SuperstructureMembers);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_SuperstructureMembers, this, IID_ISuperstructureMembersEvents, &m_SuperstructureMembersCookie);
   if (FAILED(hr))
      return hr;

   hr = m_Supports.CoCreateInstance(CLSID_Supports);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Supports, this, IID_ISupportsEvents, &m_SupportsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_POIs.CoCreateInstance(CLSID_POIs);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_POIs, this, IID_IPOIsEvents, &m_POIsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_Stages.CoCreateInstance(CLSID_Stages);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Stages, this, IID_IStagesEvents, &m_StagesCookie);
   if (FAILED(hr))
      return hr;

   hr = m_LoadGroups.CoCreateInstance(CLSID_LoadGroups);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_LoadGroups, this, IID_ILoadGroupsEvents, &m_LoadGroupsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_LoadCases.CoCreateInstance(CLSID_LoadCases);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_LoadCases, this, IID_ILoadCasesEvents, &m_LoadCasesCookie);
   if (FAILED(hr))
      return hr;

   hr = m_LoadCombinations.CoCreateInstance(CLSID_LoadCombinations);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_LoadCombinations, this, IID_ILoadCombinationsEvents, &m_LoadCombinationsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_PointLoads.CoCreateInstance(CLSID_PointLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_PointLoads, this, IID_IPointLoadsEvents, &m_PointLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_DistributedLoads.CoCreateInstance(CLSID_DistributedLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_DistributedLoads, this, IID_IDistributedLoadsEvents, &m_DistributedLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_TemperatureLoads.CoCreateInstance(CLSID_TemperatureLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_TemperatureLoads, this, IID_ITemperatureLoadsEvents, &m_TemperatureLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_SettlementLoads.CoCreateInstance(CLSID_SettlementLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_SettlementLoads, this, IID_ISettlementLoadsEvents, &m_SettlementLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_StrainLoads.CoCreateInstance(CLSID_StrainLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_StrainLoads, this, IID_IStrainLoadsEvents, &m_StrainLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_LiveLoad.CoCreateInstance(CLSID_LiveLoad);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_LiveLoad, this, IID_ILiveLoadEvents, &m_LiveLoadCookie);
   if (FAILED(hr))
      return hr;

   hr = m_DistributionFactors.CoCreateInstance(CLSID_DistributionFactors);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_DistributionFactors, this, IID_IDistributionFactorsEvents, &m_DistributionFactorsCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CModel::FinalRelease()
{
   // say goodbye to our broadcasters
   HRESULT hr;

   ATLASSERT(!!m_Spans);
   hr = CrUnadvise(m_Spans, this, IID_ISpansEvents, m_SpansCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_SuperstructureMembers);
   hr = CrUnadvise(m_SuperstructureMembers, this, IID_ISuperstructureMembersEvents, m_SuperstructureMembersCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_Supports);
   hr = CrUnadvise(m_Supports, this, IID_ISupportsEvents, m_SupportsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_POIs);
   hr = CrUnadvise(m_POIs, this, IID_IPOIsEvents, m_POIsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_Stages);
   hr = CrUnadvise(m_Stages, this, IID_IStagesEvents, m_StagesCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_LoadGroups);
   hr = CrUnadvise(m_LoadGroups, this, IID_ILoadGroupsEvents, m_LoadGroupsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_LoadCases);
   hr = CrUnadvise(m_LoadCases, this, IID_ILoadCasesEvents, m_LoadCasesCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_LoadCombinations);
   hr = CrUnadvise(m_LoadCombinations, this, IID_ILoadCombinationsEvents, m_LoadCombinationsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_PointLoads);
   hr = CrUnadvise(m_PointLoads, this, IID_IPointLoadsEvents, m_PointLoadsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_DistributedLoads);
   hr = CrUnadvise(m_DistributedLoads, this, IID_IDistributedLoadsEvents, m_DistributedLoadsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_TemperatureLoads);
   hr = CrUnadvise(m_TemperatureLoads, this, IID_ITemperatureLoadsEvents, m_TemperatureLoadsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_SettlementLoads);
   hr = CrUnadvise(m_SettlementLoads, this, IID_ISettlementLoadsEvents, m_SettlementLoadsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_StrainLoads);
   hr = CrUnadvise(m_StrainLoads, this, IID_IStrainLoadsEvents, m_StrainLoadsCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_LiveLoad);
   hr = CrUnadvise(m_LiveLoad, this, IID_ILiveLoadEvents, m_LiveLoadCookie);
   ATLASSERT(SUCCEEDED(hr));

   ATLASSERT(!!m_DistributionFactors);
   hr = CrUnadvise(m_DistributionFactors, this, IID_IDistributionFactorsEvents, m_DistributionFactorsCookie);
   ATLASSERT(SUCCEEDED(hr));
}


STDMETHODIMP CModel::get_SuperstructureMembers(ISuperstructureMembers **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_SuperstructureMembers.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_SuperstructureMembers(ISuperstructureMembers *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_SuperstructureMembers.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_SuperstructureMembers)
   {
      hr = CrUnadvise(m_SuperstructureMembers, this, IID_ISuperstructureMembersEvents, m_SuperstructureMembersCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_SuperstructureMembers = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_SuperstructureMembers, this, IID_ISuperstructureMembersEvents, &m_SuperstructureMembersCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtStiffness);

	return S_OK;
}

STDMETHODIMP CModel::get_Supports(ISupports **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_Supports.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_Supports(ISupports *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_Supports.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_Supports)
   {
      hr = CrUnadvise(m_Supports, this, IID_ISupportsEvents, m_SupportsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_Supports = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_Supports, this, IID_ISupportsEvents, &m_SupportsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtStiffness);

	return S_OK;
}

STDMETHODIMP CModel::get_Spans(ISpans **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_Spans.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_Spans(ISpans *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_Spans.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_Spans)
   {
      hr = CrUnadvise(m_Spans, this, IID_ISpansEvents, m_SpansCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_Spans = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_Spans, this, IID_ISpansEvents, &m_SpansCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtStiffness);


	return S_OK;
}

STDMETHODIMP CModel::get_POIs(IPOIs **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_POIs.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_POIs(IPOIs *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_POIs.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_POIs)
   {
      hr = CrUnadvise(m_POIs, this, IID_IPOIsEvents, m_POIsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_POIs = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_POIs, this, IID_IPOIsEvents, &m_POIsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtPOI);

	return S_OK;
}


STDMETHODIMP CModel::get_Stages(IStages **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_Stages.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_Stages(IStages *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_Stages.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_Stages)
   {
      hr = CrUnadvise(m_Stages, this, IID_IStagesEvents, m_StagesCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_Stages = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_Stages, this, IID_IStagesEvents, &m_StagesCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtStage);

	return S_OK;
}

STDMETHODIMP CModel::get_LoadGroups(ILoadGroups **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_LoadGroups.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_LoadGroups(ILoadGroups *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_LoadGroups.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_LoadGroups)
   {
      hr = CrUnadvise(m_LoadGroups, this, IID_ILoadGroupsEvents, m_LoadGroupsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_LoadGroups = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_LoadGroups, this, IID_ILoadGroupsEvents, &m_LoadGroupsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtLoads);

	return S_OK;
}

STDMETHODIMP CModel::get_LoadCases(ILoadCases **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_LoadCases.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_LoadCases(ILoadCases *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_LoadCases.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_LoadCases)
   {
      hr = CrUnadvise(m_LoadCases, this, IID_ILoadCasesEvents, m_LoadCasesCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_LoadCases = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_LoadCases, this, IID_ILoadCasesEvents, &m_LoadCasesCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtCombination);

	return S_OK;
}

STDMETHODIMP CModel::get_LoadCombinations(ILoadCombinations **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_LoadCombinations.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_LoadCombinations(ILoadCombinations *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_LoadCombinations.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_LoadCombinations)
   {
      hr = CrUnadvise(m_LoadCombinations, this, IID_ILoadCombinationsEvents, m_LoadCombinationsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_LoadCombinations = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_LoadCombinations, this, IID_ILoadCombinationsEvents, &m_LoadCombinationsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtCombination);

	return S_OK;
}


STDMETHODIMP CModel::get_PointLoads(IPointLoads **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_PointLoads.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_PointLoads(IPointLoads *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_PointLoads.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_PointLoads)
   {
      hr = CrUnadvise(m_PointLoads, this, IID_IPointLoadsEvents, m_PointLoadsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_PointLoads = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_PointLoads, this, IID_IPointLoadsEvents, &m_PointLoadsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtLoads);

	return S_OK;
}

STDMETHODIMP CModel::get_DistributedLoads(IDistributedLoads **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_DistributedLoads.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_DistributedLoads(IDistributedLoads *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_DistributedLoads.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_DistributedLoads)
   {
      hr = CrUnadvise(m_DistributedLoads, this, IID_IDistributedLoadsEvents, m_DistributedLoadsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_DistributedLoads = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_DistributedLoads, this, IID_IDistributedLoadsEvents, &m_DistributedLoadsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtLoads);

	return S_OK;
}

STDMETHODIMP CModel::get_TemperatureLoads(ITemperatureLoads **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_TemperatureLoads.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_TemperatureLoads(ITemperatureLoads *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_TemperatureLoads.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_TemperatureLoads)
   {
      hr = CrUnadvise(m_TemperatureLoads, this, IID_ITemperatureLoadsEvents, m_TemperatureLoadsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_TemperatureLoads = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_TemperatureLoads, this, IID_ITemperatureLoadsEvents, &m_TemperatureLoadsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtLoads);

	return S_OK;
}

STDMETHODIMP CModel::get_SettlementLoads(ISettlementLoads **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_SettlementLoads.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_SettlementLoads(ISettlementLoads *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_SettlementLoads.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_SettlementLoads)
   {
      hr = CrUnadvise(m_SettlementLoads, this, IID_ISettlementLoadsEvents, m_SettlementLoadsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_SettlementLoads = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_SettlementLoads, this, IID_ISettlementLoadsEvents, &m_SettlementLoadsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtLoads);

	return S_OK;
}

STDMETHODIMP CModel::get_StrainLoads(IStrainLoads **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_StrainLoads.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_StrainLoads(IStrainLoads *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_StrainLoads.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_StrainLoads)
   {
      hr = CrUnadvise(m_StrainLoads, this, IID_IStrainLoadsEvents, m_StrainLoadsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_StrainLoads = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_StrainLoads, this, IID_IStrainLoadsEvents, &m_StrainLoadsCookie);
   if (FAILED(hr))
      return hr;

//   // tell the world we've changed
//   FireModelChanged(cgtLoads);

	return S_OK;
}

STDMETHODIMP CModel::get_LiveLoad(ILiveLoad **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_LiveLoad.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_LiveLoad(ILiveLoad *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_LiveLoad.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_LiveLoad)
   {
      hr = CrUnadvise(m_LiveLoad, this, IID_ILiveLoadEvents, m_LiveLoadCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_LiveLoad = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_LiveLoad, this, IID_ILiveLoadEvents, &m_LiveLoadCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnModelChanged(this, cgtLiveLoad);

	return S_OK;
}

STDMETHODIMP CModel::get_DistributionFactors(IDistributionFactors **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_DistributionFactors.CopyTo(pVal);
}

STDMETHODIMP CModel::putref_DistributionFactors(IDistributionFactors *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same collection
   if ( m_DistributionFactors.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old collection if we had one
   HRESULT hr;
   if (!!m_DistributionFactors)
   {
      hr = CrUnadvise(m_DistributionFactors, this, IID_IDistributionFactorsEvents, m_DistributionFactorsCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new collection
   m_DistributionFactors = newVal;

   // establish cp with new collection
   hr = CrAdvise(m_DistributionFactors, this, IID_IDistributionFactorsEvents, &m_DistributionFactorsCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnModelChanged(this, cgtDistributionFactor);

	return S_OK;
}


STDMETHODIMP CModel::get_StructuredStorage(IStructuredStorage2 **pVal)
{
   CHECK_RETOBJ(pVal);
	return this->QueryInterface(IID_IStructuredStorage2, (void**)pVal);
}


// IStructuredStorage2
static const Float64 MY_VER=1.0;

STDMETHODIMP CModel::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);
   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("LBAM_Model"));
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
      // Spans
      hr = pload->get_Property(_bstr_t("Spans"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ISpans> pispans;
      hr = _CopyVariantToInterface<ISpans>::copy(&pispans, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_Spans(pispans);
      if (FAILED(hr))
         return hr;

      // SuperstructureMembers
      var.Clear();
      hr = pload->get_Property(_bstr_t("SuperstructureMembers"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ISuperstructureMembers> pisps;
      hr = _CopyVariantToInterface<ISuperstructureMembers>::copy(&pisps, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_SuperstructureMembers(pisps);
      if (FAILED(hr))
         return hr;

      // supports
      var.Clear();
      hr = pload->get_Property(_bstr_t("Supports"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ISupports> pisup;
      hr = _CopyVariantToInterface<ISupports>::copy(&pisup, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_Supports(pisup);
      if (FAILED(hr))
         return hr;

      // POIs
      var.Clear();
      hr = pload->get_Property(_bstr_t("POIs"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IPOIs> pipoi;
      hr = _CopyVariantToInterface<IPOIs>::copy(&pipoi, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_POIs(pipoi);
      if (FAILED(hr))
         return hr;

      // Stages
      var.Clear();
      hr = pload->get_Property(_bstr_t("Stages"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IStages> pistg;
      hr = _CopyVariantToInterface<IStages>::copy(&pistg, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_Stages(pistg);
      if (FAILED(hr))
         return hr;

      // LoadGroups
      var.Clear();
      hr = pload->get_Property(_bstr_t("LoadGroups"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ILoadGroups> pilg;
      hr = _CopyVariantToInterface<ILoadGroups>::copy(&pilg, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_LoadGroups(pilg);
      if (FAILED(hr))
         return hr;

      // LoadCases
      var.Clear();
      hr = pload->get_Property(_bstr_t("LoadCases"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ILoadCases> pilc;
      hr = _CopyVariantToInterface<ILoadCases>::copy(&pilc, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_LoadCases(pilc);
      if (FAILED(hr))
         return hr;

      // LoadCombinations
      var.Clear();
      hr = pload->get_Property(_bstr_t("LoadCombinations"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ILoadCombinations> pilcb;
      hr = _CopyVariantToInterface<ILoadCombinations>::copy(&pilcb, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_LoadCombinations(pilcb);
      if (FAILED(hr))
         return hr;

      // PointLoads
      var.Clear();
      hr = pload->get_Property(_bstr_t("PointLoads"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IPointLoads> piPointLoad;
      hr = _CopyVariantToInterface<IPointLoads>::copy(&piPointLoad, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_PointLoads(piPointLoad);
      if (FAILED(hr))
         return hr;

      // DistributedLoads
      var.Clear();
      hr = pload->get_Property(_bstr_t("DistributedLoads"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IDistributedLoads> piDistributedLoad;
      hr = _CopyVariantToInterface<IDistributedLoads>::copy(&piDistributedLoad, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_DistributedLoads(piDistributedLoad);
      if (FAILED(hr))
         return hr;

      // TemperatureLoads
      var.Clear();
      hr = pload->get_Property(_bstr_t("TemperatureLoads"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ITemperatureLoads> piTemperatureLoad;
      hr = _CopyVariantToInterface<ITemperatureLoads>::copy(&piTemperatureLoad, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_TemperatureLoads(piTemperatureLoad);
      if (FAILED(hr))
         return hr;

      // SettlementLoads
      var.Clear();
      hr = pload->get_Property(_bstr_t("SettlementLoads"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ISettlementLoads> piSettlementLoad;
      hr = _CopyVariantToInterface<ISettlementLoads>::copy(&piSettlementLoad, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_SettlementLoads(piSettlementLoad);
      if (FAILED(hr))
         return hr;

      // StrainLoads
      var.Clear();
      hr = pload->get_Property(_bstr_t("StrainLoads"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IStrainLoads> piStrainLoad;
      hr = _CopyVariantToInterface<IStrainLoads>::copy(&piStrainLoad, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_StrainLoads(piStrainLoad);
      if (FAILED(hr))
         return hr;

      // LiveLoad
      var.Clear();
      hr = pload->get_Property(_bstr_t("LiveLoad"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<ILiveLoad> piLiveLoad;
      hr = _CopyVariantToInterface<ILiveLoad>::copy(&piLiveLoad, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_LiveLoad(piLiveLoad);
      if (FAILED(hr))
         return hr;

      // DistributionFactors
      var.Clear();
      hr = pload->get_Property(_bstr_t("DistributionFactors"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IDistributionFactors> piDistributionFactors;
      hr = _CopyVariantToInterface<IDistributionFactors>::copy(&piDistributionFactors, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_DistributionFactors(piDistributionFactors);
      if (FAILED(hr))
         return hr;

   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   // tell our clients we're hosed.
   FireModelChanged(cgtClear);

   return S_OK;
}

STDMETHODIMP CModel::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;

   try
   {
      hr = psave->BeginUnit(CComBSTR("LBAM_Model"), MY_VER);
      hr = psave->put_Property(CComBSTR("Spans"),_variant_t(m_Spans));
      hr = psave->put_Property(CComBSTR("SuperstructureMembers"),_variant_t(m_SuperstructureMembers));
      hr = psave->put_Property(CComBSTR("Supports"),_variant_t(m_Supports));
      hr = psave->put_Property(CComBSTR("POIs"),_variant_t(m_POIs));
      hr = psave->put_Property(CComBSTR("Stages"),_variant_t(m_Stages));
      hr = psave->put_Property(CComBSTR("LoadGroups"),_variant_t(m_LoadGroups));
      hr = psave->put_Property(CComBSTR("LoadCases"),_variant_t(m_LoadCases));
      hr = psave->put_Property(CComBSTR("LoadCombinations"),_variant_t(m_LoadCombinations));
      hr = psave->put_Property(CComBSTR("PointLoads"),_variant_t(m_PointLoads));
      hr = psave->put_Property(CComBSTR("DistributedLoads"),_variant_t(m_DistributedLoads));
      hr = psave->put_Property(CComBSTR("TemperatureLoads"),_variant_t(m_TemperatureLoads));
      hr = psave->put_Property(CComBSTR("SettlementLoads"),_variant_t(m_SettlementLoads));
      hr = psave->put_Property(CComBSTR("StrainLoads"),_variant_t(m_StrainLoads));
      hr = psave->put_Property(CComBSTR("LiveLoad"),_variant_t(m_LiveLoad));
      hr = psave->put_Property(CComBSTR("DistributionFactors"),_variant_t(m_DistributionFactors));
      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMModel);
   }

   return S_OK;
}

STDMETHODIMP CModel::OnSuperstructureMembersChanged(ISuperstructureMember* item, BSTR stage, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnSuperstructureMembersAdded(ISuperstructureMember* item, CollectionIndexType index)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSuperstructureMembersBeforeRemove(ISuperstructureMember* item, CollectionIndexType index)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSuperstructureMembersMoveTo(CollectionIndexType from, CollectionIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSuperstructureMembersCopyTo(CollectionIndexType from, CollectionIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSuperstructureMembersReverse()
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSuperstructureMembersOffset()
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}

STDMETHODIMP CModel::OnSupportsChanged(ISupport* item, BSTR stage, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnSupportsAdded(ISupport* item, SupportIndexType index)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSupportsBeforeRemove(ISupport* item, SupportIndexType index)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSupportsMoveTo(SupportIndexType from, SupportIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSupportsCopyTo(SupportIndexType from, SupportIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSupportsReverse()
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}

STDMETHODIMP CModel::OnSpansChanged(ISpan* item, BSTR stage, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnSpansAdded(ISpan* item, SpanIndexType index)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSpansBeforeRemove(ISpan* item, SpanIndexType index)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSpansMoveTo(SpanIndexType from, SpanIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSpansCopyTo(SpanIndexType from, SpanIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnSpansReverse()
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}

STDMETHODIMP CModel::OnPOIsChanged(/*[in]*/IPOI* poi, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnPOIsRenamed(PoiIDType oldID, PoiIDType newID)
{
   FireModelChanged(cgtPOI);
   return S_OK;
}
STDMETHODIMP CModel::OnPOIsAdded(/*[in]*/IPOI* poi)
{
   FireModelChanged(cgtPOI);
   return S_OK;
}
STDMETHODIMP CModel::OnPOIsBeforeRemove(/*[in]*/IPOI* poi)
{
   FireModelChanged(cgtPOI);
   return S_OK;
}


STDMETHODIMP CModel::OnStagesChanged(IStage* item, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnStagesAdded(IStage* item, StageIndexType relPos)
{
   FireModelChanged(cgtStageOrder);
   return S_OK;
}
STDMETHODIMP CModel::OnStagesBeforeRemove(IStage* item, StageIndexType relPos)
{
   FireModelChanged(cgtStageOrder);
   return S_OK;
}
STDMETHODIMP CModel::OnStagesMoveTo(StageIndexType from, StageIndexType to)
{
   FireModelChanged(cgtStageOrder);
   return S_OK;
}
STDMETHODIMP CModel::OnStagesCopyTo(StageIndexType from, StageIndexType to)
{
   FireModelChanged(cgtStageOrder);
   return S_OK;
}
STDMETHODIMP CModel::OnStagesReverse()
{
   FireModelChanged(cgtStageOrder);
   return S_OK;
}


STDMETHODIMP CModel::OnLoadGroupsChanged(ILoadGroup* item, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadGroupsRenamed(BSTR oldName, BSTR newName)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadGroupsAdded(ILoadGroup* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadGroupsBeforeRemove(ILoadGroup* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}


STDMETHODIMP CModel::OnLoadCasesChanged(ILoadCase* item, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadCasesRenamed(BSTR oldName, BSTR newName)
{
   FireModelChanged(cgtCombination);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadCasesAdded(ILoadCase* item)
{
   FireModelChanged(cgtCombination);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadCasesBeforeRemove(ILoadCase* item)
{
   FireModelChanged(cgtCombination);
   return S_OK;
}

STDMETHODIMP CModel::OnLoadCombinationsChanged(ILoadCombination* item, ChangeType change)
{
   FireModelChanged(change);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadCombinationsRenamed(BSTR oldName, BSTR newName)
{
   FireModelChanged(cgtCombination);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadCombinationsAdded(ILoadCombination* item)
{
   FireModelChanged(cgtCombination);
   return S_OK;
}
STDMETHODIMP CModel::OnLoadCombinationsBeforeRemove(ILoadCombination* item)
{
   FireModelChanged(cgtCombination);
   return S_OK;
}


STDMETHODIMP CModel::OnPointLoadsChanged(/*[in]*/IPointLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnPointLoadsAdded(/*[in]*/IPointLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnPointLoadsBeforeRemove(/*[in]*/IPointLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}


STDMETHODIMP CModel::OnDistributedLoadsChanged(/*[in]*/IDistributedLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnDistributedLoadsAdded(/*[in]*/IDistributedLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnDistributedLoadsBeforeRemove(/*[in]*/IDistributedLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}


STDMETHODIMP CModel::OnTemperatureLoadsChanged(/*[in]*/ITemperatureLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnTemperatureLoadsAdded(/*[in]*/ITemperatureLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnTemperatureLoadsBeforeRemove(/*[in]*/ITemperatureLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}


STDMETHODIMP CModel::OnStrainLoadsChanged(/*[in]*/IStrainLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnStrainLoadsAdded(/*[in]*/IStrainLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnStrainLoadsBeforeRemove(/*[in]*/IStrainLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}


STDMETHODIMP CModel::OnSettlementLoadsChanged(/*[in]*/ISettlementLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnSettlementLoadsAdded(/*[in]*/ISettlementLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}
STDMETHODIMP CModel::OnSettlementLoadsBeforeRemove(/*[in]*/ISettlementLoadItem* item)
{
   FireModelChanged(cgtLoads);
   return S_OK;
}


STDMETHODIMP CModel::OnLiveLoadChanged(ILiveLoad* load, LiveLoadModelType lltype)
{
   FireModelChanged(cgtLiveLoad);
   return S_OK;
}

STDMETHODIMP CModel::OnDistributionFactorsChanged()
{
   FireModelChanged(cgtDistributionFactor);
   return S_OK;
}
STDMETHODIMP CModel::OnDistributionFactorsAdded(IDistributionFactorSegment* item, CollectionIndexType idx)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnDistributionFactorsBeforeRemove(IDistributionFactorSegment* item, CollectionIndexType idx)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnDistributionFactorsMoveTo(CollectionIndexType from, CollectionIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnDistributionFactorsCopyTo(CollectionIndexType from, CollectionIndexType to)
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}
STDMETHODIMP CModel::OnDistributionFactorsReverse()
{
   FireModelChanged(cgtStiffness);
   return S_OK;
}


STDMETHODIMP CModel::Clone(ILBAMModel **clone)
{
   CHECK_RETOBJ(clone);

	// basically just a deep clone
   CComObject<CModel>* pnew;
   HRESULT hr = CComObject<CModel>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ILBAMModel> pclone(pnew); // to keep refcnt alive;

   // Spans
   CComPtr<ISpans> pSpans;
   hr = m_Spans->Clone(&pSpans);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_Spans(pSpans);
   if (FAILED(hr))
      return hr;

   // Supports
   CComPtr<ISupports> pSupports;
   hr = m_Supports->Clone(&pSupports);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_Supports(pSupports);
   if (FAILED(hr))
      return hr;

   // SuperstructureMembers
   CComPtr<ISuperstructureMembers> pSuperstructureMembers;
   hr = m_SuperstructureMembers->Clone(&pSuperstructureMembers);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_SuperstructureMembers(pSuperstructureMembers);
   if (FAILED(hr))
      return hr;

   // POIs
   CComPtr<IPOIs> pPOIs;
   hr = m_POIs->Clone(&pPOIs);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_POIs(pPOIs);
   if (FAILED(hr))
      return hr;

   // Stages
   CComPtr<IStages> pStages;
   hr = m_Stages->Clone(&pStages);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_Stages(pStages);
   if (FAILED(hr))
      return hr;

   // LoadGroups
   CComPtr<ILoadGroups> pLoadGroups;
   hr = m_LoadGroups->Clone(&pLoadGroups);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_LoadGroups(pLoadGroups);
   if (FAILED(hr))
      return hr;

   // LoadCases
   CComPtr<ILoadCases> pLoadCases;
   hr = m_LoadCases->Clone(&pLoadCases);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_LoadCases(pLoadCases);
   if (FAILED(hr))
      return hr;
   
   // LoadCombinations
   CComPtr<ILoadCombinations> pLoadCombinations;
   hr = m_LoadCombinations->Clone(&pLoadCombinations);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_LoadCombinations(pLoadCombinations);
   if (FAILED(hr))
      return hr;
   
   // PointLoads
   CComPtr<IPointLoads> pPointLoads;
   hr = m_PointLoads->Clone(&pPointLoads);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_PointLoads(pPointLoads);
   if (FAILED(hr))
      return hr;

   // DistributedLoads
   CComPtr<IDistributedLoads> pDistributedLoads;
   hr = m_DistributedLoads->Clone(&pDistributedLoads);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_DistributedLoads(pDistributedLoads);
   if (FAILED(hr))
      return hr;

   // TemperatureLoads
   CComPtr<ITemperatureLoads> pTemperatureLoads;
   hr = m_TemperatureLoads->Clone(&pTemperatureLoads);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_TemperatureLoads(pTemperatureLoads);
   if (FAILED(hr))
      return hr;

   // SettlementLoads
   CComPtr<ISettlementLoads> pSettlementLoads;
   hr = m_SettlementLoads->Clone(&pSettlementLoads);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_SettlementLoads(pSettlementLoads);
   if (FAILED(hr))
      return hr;

   // StrainLoads
   CComPtr<IStrainLoads> pStrainLoads;
   hr = m_StrainLoads->Clone(&pStrainLoads);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_StrainLoads(pStrainLoads);
   if (FAILED(hr))
      return hr;

   // LiveLoad
   CComPtr<ILiveLoad> pLiveLoad;
   hr = m_LiveLoad->Clone(&pLiveLoad);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_LiveLoad(pLiveLoad);
   if (FAILED(hr))
      return hr;

   // DistributionFactors
   CComPtr<IDistributionFactors> pDistributionFactors;
   hr = m_DistributionFactors->Clone(&pDistributionFactors);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_DistributionFactors(pDistributionFactors);
   if (FAILED(hr))
      return hr;

   // assign to client
   return pclone.CopyTo(clone);
}


STDMETHODIMP CModel::Clear()
{
	m_Spans->Clear();
   m_SuperstructureMembers->Clear();
   m_Supports->Clear();
   m_POIs->Clear();
   m_Stages->Clear();
   m_LoadGroups->Clear();
   m_LoadCases->Clear();
   m_LoadCombinations->Clear();
   m_PointLoads->Clear();
   m_DistributedLoads->Clear();
   m_TemperatureLoads->Clear();
   m_SettlementLoads->Clear();
   m_StrainLoads->Clear();
   m_LiveLoad->Clear();
   m_DistributionFactors->Clear();

   FireModelChanged(cgtClear);

	return S_OK;
}

STDMETHODIMP CModel::RemoveStage(BSTR stage)
{
   CHECK_IN(stage);

	// stages are scattered all over model
   // spans
   SpanIndexType nSpans;
   HRESULT hr = m_Spans->get_Count(&nSpans);
   if (FAILED(hr))
      return hr;

   for (SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++)
   {
      CComPtr<ISpan> its;
      hr = m_Spans->get_Item(spanIdx, &its);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }

      hr = its->RemoveStage(stage);
      if (FAILED(hr))
         ATLASSERT(0);
   }

   // Supports
   SupportIndexType nPiers;
   hr = m_Supports->get_Count(&nPiers);
   if (FAILED(hr))
      return hr;

   for (SupportIndexType pierIdx = 0; pierIdx < nPiers; pierIdx++)
   {
      CComPtr<ISupport> its;
      hr = m_Supports->get_Item(pierIdx, &its);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }

      hr = its->RemoveStage(stage);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }
   }

   // SuperstructureMembers
   CollectionIndexType nSSMbrs;
   hr = m_SuperstructureMembers->get_Count(&nSSMbrs);
   if (FAILED(hr))
      return hr;

   for (CollectionIndexType ssmbrIdx = 0; ssmbrIdx < nSSMbrs; ssmbrIdx++)
   {
      CComPtr<ISuperstructureMember> its;
      hr = m_SuperstructureMembers->get_Item(ssmbrIdx, &its);
      if (FAILED(hr))
      {
         ATLASSERT(0);
         return hr;
      }

      hr = its->RemoveStage(stage);
      if (FAILED(hr))
         ATLASSERT(0);
   }

   hr = m_PointLoads->RemoveStage(stage);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_DistributedLoads->RemoveStage(stage);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_TemperatureLoads->RemoveStage(stage);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_SettlementLoads->RemoveStage(stage);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   hr = m_StrainLoads->RemoveStage(stage);
   if (FAILED(hr))
   {
      ATLASSERT(0);
      return hr;
   }

   // stages collection
   hr = m_Stages->RemoveByName(stage);
   FireModelChanged(cgtClear);  // this is really a bigger change that just a stage edit
   return hr;
}

STDMETHODIMP CModel::RightSupport(SpanIndexType spanIndex, ISupport ** pSupport)
{
	CHECK_RETOBJ(pSupport);

   // both spans and supports have to exist in order to return a valid pointer
   HRESULT hr;

   SpanIndexType numspans;
   hr = m_Spans->get_Count(&numspans);
   if (FAILED(hr))
      return hr;

   SupportIndexType numsupts;
   hr = m_Supports->get_Count(&numsupts);
   if (FAILED(hr))
      return hr;

   if (spanIndex >= numspans)
   {
      *pSupport = 0;
   }
   else
   {
      SupportIndexType supno = spanIndex + 1;
      if (supno >= numsupts || supno < 0)
      {
         *pSupport = 0;
      }
      else
      {
         CComPtr<ISupport> psupt;
         hr = m_Supports->get_Item(supno, &psupt);
         if (FAILED(hr))
            return hr;

         *pSupport = psupt;
         (*pSupport)->AddRef();
      }
   }

	return S_OK;
}

STDMETHODIMP CModel::LeftSupport(SpanIndexType spanIndex, ISupport ** pSupport)
{
	CHECK_RETOBJ(pSupport);

   // both spans and supports have to exist in order to return a valid pointer
   HRESULT hr;

   SpanIndexType numspans;
   hr = m_Spans->get_Count(&numspans);
   if (FAILED(hr))
      return hr;

   SupportIndexType numsupts;
   hr = m_Supports->get_Count(&numsupts);
   if (FAILED(hr))
      return hr;

   if (spanIndex >= numspans)
   {
      *pSupport = 0;
   }
   else
   {
      SupportIndexType supno = spanIndex;
      if (supno >= numsupts || supno < 0)
      {
         *pSupport = 0;
      }
      else
      {
         CComPtr<ISupport> psupt;
         hr = m_Supports->get_Item(supno, &psupt);
         if (FAILED(hr))
            return hr;

         *pSupport = psupt;
         (*pSupport)->AddRef();
      }
   }

	return S_OK;
}

STDMETHODIMP CModel::RightSpan(SupportIndexType supportIndex, ISpan ** pSpan )
{
	CHECK_RETOBJ(pSpan);

   // both spans and supports have to exist in order to return a valid pointer
   HRESULT hr;

   SpanIndexType numspans;
   hr = m_Spans->get_Count(&numspans);
   if (FAILED(hr))
      return hr;

   SupportIndexType numsupts;
   hr = m_Supports->get_Count(&numsupts);
   if (FAILED(hr))
      return hr;

   if (supportIndex >= numsupts-1)
   {
      *pSpan = 0;
   }
   else
   {
      SpanIndexType spano = supportIndex;
      if (spano >= numspans || spano<0)
      {
         *pSpan = 0;
      }
      else
      {
         CComPtr<ISpan> pspan;
         hr = m_Spans->get_Item(spano, &pspan);
         if (FAILED(hr))
            return hr;

         *pSpan = pspan;
         (*pSpan)->AddRef();
      }
   }

	return S_OK;
}

STDMETHODIMP CModel::LeftSpan(SupportIndexType supportIndex, ISpan ** pSpan)
{
	CHECK_RETOBJ(pSpan);

   // both spans and supports have to exist in order to return a valid pointer
   HRESULT hr;

   SpanIndexType numspans;
   hr = m_Spans->get_Count(&numspans);
   if (FAILED(hr))
      return hr;

   SupportIndexType numsupts;
   hr = m_Supports->get_Count(&numsupts);
   if (FAILED(hr))
      return hr;

   if (supportIndex >= numsupts)
   {
      *pSpan = 0;
   }
   else
   {
      SpanIndexType spano = supportIndex-1;
      if (spano >= numspans || spano<0)
      {
         *pSpan = 0;
      }
      else
      {
         CComPtr<ISpan> pspan;
         hr = m_Spans->get_Item(spano, &pspan);
         if (FAILED(hr))
            return hr;

         *pSpan = pspan;
         (*pSpan)->AddRef();
      }
   }

	return S_OK;
}

VOID CModel::FireModelChanged(ChangeType change)
{
   // deal with change - will need to update location data if any significant changes 
   // made to model. Note that this could be more precise.
   if (change != cgtStress &&
       change != cgtCombination &&
       change != cgtPOI &&
       change != cgtStage &&
       change != cgtStageOrder &&
       change != cgtLoads &&
       change != cgtDescription)
   {
      m_LocationCache.Invalidate();
   }

   // fire change out to listeners
   Fire_OnModelChanged(this, change);
}

CModel::LocationCache::LocationCache(CModel* pModel):
m_pModel(pModel)
{
   m_LocationUpdated = false;
   ATLASSERT(pModel);
}

void CModel::LocationCache::Invalidate()
{
   m_LocationUpdated = false;
   m_SpanEnds.clear();
   m_SsmEnds.clear();
}

void CModel::LocationCache::Validate()
{
   // don't do anything if cache is up to date
   if (m_LocationUpdated)
      return;

   // cycle through model and determine locations of span and superstructure ends
   CComPtr<ISpans> spans;
   CHRException hr;
   hr = m_pModel->get_Spans(&spans);

   SpanIndexType span_cnt;
   hr = spans->get_Count(&span_cnt);

   if (span_cnt<=0)
      THROW_LBAM(MUST_HAVE_ONE_SPAN);

   m_SpanEnds.push_back(0.0); // start of first span is always 0.0

   Float64 spanlen=0.0;
   for (SpanIndexType ispan=0; ispan<span_cnt; ispan++)
   {
      Float64 length;
      CComPtr<ISpan> span;
      hr = spans->get_Item(ispan, &span);
      hr = span->get_Length(&length);

      if (length<=0.0)
         THROW_LBAM(SPAN_LENGTH_MUST_BE_GT_ZERO);

      spanlen += length;
      m_SpanEnds.push_back(spanlen);
   }

   // superstructure ends
   CComPtr<ISuperstructureMembers> ssms;
   hr = m_pModel->get_SuperstructureMembers(&ssms);

   CollectionIndexType ssm_cnt;
   hr = ssms->get_Count(&ssm_cnt);

   if (ssm_cnt<=0)
      THROW_LBAM(MUST_HAVE_ONE_SSM);

   Float64 overhang;
   hr = ssms->get_Offset(&overhang);

   m_SsmEnds.push_back(-overhang); // start of first ssm is at - overhang

   Float64 ssmlen=-overhang;
   for (CollectionIndexType issm=0; issm<ssm_cnt; issm++)
   {
      Float64 length;
      CComPtr<ISuperstructureMember> ssm;
      hr = ssms->get_Item(issm, &ssm);

      hr = ssm->get_Length(&length);

      if (length<=0.0)
         THROW_LBAM(SSM_LENGTH_MUST_BE_GT_ZERO);

      ssmlen += length;
      m_SsmEnds.push_back(ssmlen);
   }

   if ( !IsEqual(ssmlen,spanlen) && ssmlen<spanlen)
      THROW_LBAM(SPAN_LENGTH_EXCEEDS_SUPERSTRUCTUREMEMBERS);

   m_LocationUpdated = true;
}

void CModel::LocationCache::ComputeLocation(MemberIDType mbrId, MemberType mbrType, Float64 mbrLocation, Float64 *Xloc, Float64 *Yloc)
{
   // first validate our location cache
   Validate();

   CHRException hr;

   // switch on member type
   switch (mbrType)
   {
   case mtSpan:
      {
         SpanIndexType num_spans = m_SpanEnds.size()-1;
         if (mbrId < 0 || MemberIDType(num_spans) <= mbrId)
         {
            CComBSTR msg = CreateErrorMsg1L(IDS_E_SPAN_NOT_EXIST, mbrId);
            THROW_LBAM_MSG(SPAN_NOT_EXIST,msg);
         }
         // get start and end locations
         Float64 start = m_SpanEnds[mbrId];
         Float64 end   = m_SpanEnds[mbrId+1];
         Float64 length = end - start;

         try
         {
            Float64 loc = GetFracDistance( mbrLocation, length);
            *Xloc = start + loc;
            *Yloc = 0.0;
         }
         catch(...)
         {
            THROW_LBAM(LOCATION_OOR);
         }
      }
      break;

   case mtSuperstructureMember:
      {
         CollectionIndexType num_ssms = m_SsmEnds.size()-1;
         if (mbrId < 0 || MemberIDType(num_ssms) <= mbrId)
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SSM_NOT_EXIST, mbrId);
            THROW_LBAM_MSG(SSM_NOT_EXIST,msg);
         }
         // get start and end locations
         Float64 start = m_SsmEnds[mbrId];
         Float64 end   = m_SsmEnds[mbrId+1];
         Float64 length = end - start;

         try
         {
            Float64 loc = GetFracDistance( mbrLocation, length);
            *Xloc = start + loc;
            *Yloc = 0.0;
         }
         catch(...)
         {
            THROW_LBAM(LOCATION_OOR);
         }
      }
      break;

   case mtSupport:
      {
         // make sure valid support
         CComPtr<ISupports> supports;
         hr = m_pModel->get_Supports(&supports);

         SupportIndexType num_supports;
         hr = supports->get_Count(&num_supports);

         if (mbrId < 0 || MemberIDType(num_supports) <= mbrId)
         {
            CComBSTR msg =CreateErrorMsg1L(IDS_E_SUPPORT_NOT_EXIST, mbrId);
            THROW_LBAM_MSG(SUPPORT_NOT_EXIST,msg);
         }

         // location of top of support
         Float64 xtop = m_SpanEnds[mbrId];
         XyLoc top(xtop, 0.0);

         // location of bottom of support
         CComPtr<ISupport> support;
         hr = supports->get_Item(mbrId, &support);

         Float64 support_length;
         hr = support->get_Length(&support_length);
         if (support_length==0.0)
         {
            // zero length support
            if (mbrLocation>0.0)
            {
               THROW_LBAM(LOCATION_OOR);
            }

            *Xloc = xtop;
            *Yloc = 0.0;

         }
         else
         {
            Float64 support_offset;
            hr = support->get_BottomOffset(&support_offset);

            if (fabs(support_offset)>=support_length)
            {
               CComBSTR msg = ::CreateErrorMsg1L(IDS_E_SUPPORT_OFFSET_GT_LENGTH, mbrId);
               THROW_LBAM_MSG(SUPPORT_OFFSET_GT_LENGTH,msg);
            }

            Float64 support_height = sqrt( support_length*support_length - support_offset*support_offset);
            XyLoc bottom( xtop+support_offset, -support_height );

            Float64 local_dist; // distance along support from bottom of support
            try
            {
               local_dist = GetFracDistance(mbrLocation, support_length);
            }
            catch(FracRes&)
            {
               THROW_LBAM(LOCATION_OOR);
            }

            // compute coordinates of our location in xy
            XyLoc local_loc;
            ComputeSubNodeLocation(bottom, top, local_dist, support_length, &local_loc);

            *Xloc = local_loc.m_X;
            *Yloc = local_loc.m_Y;
         }
      }
      break;
   case mtTemporarySupport:
      {

         // make sure valid support
         CComPtr<ITemporarySupport> temp_support;
         SpanIndexType span_no;
         FindTemporarySupport(m_pModel, mbrId, &temp_support, &span_no);

         if (!temp_support)
         {
            // the support was not found - huck
            CComBSTR msg =CreateErrorMsg1L(IDS_E_TEMPSUPPORT_NOT_EXIST, mbrId);
            THROW_LBAM_MSG(TEMPSUPPORT_NOT_EXIST,msg);
         }

         // location of ends of span where support lies
         Float64 span_start  = m_SpanEnds[span_no];
         Float64 span_end    = m_SpanEnds[span_no+1];
         Float64 span_length = span_end - span_start;

         // location of top of support
         Float64 ts_loc;
         hr = temp_support->get_Location(&ts_loc);

         Float64 top_dist;
         try
         {
            top_dist = GetFracDistance(ts_loc, span_length);
         }
         catch(FracRes&)
         {
            THROW_LBAM(LOCATION_OOR);
         }

         Float64 xtop = span_start + top_dist;
         XyLoc top(xtop, 0.0);

         // location of bottom of support
         Float64 support_length;
         hr = temp_support->get_Length(&support_length);

         if (support_length==0.0)
         {
            // zero length support - all fractional locations are coincident
            if (mbrLocation>0.0)
            {
               THROW_LBAM(LOCATION_OOR);
            }

            *Xloc = xtop;
            *Yloc = 0.0;
         }
         else
         {
            Float64 support_offset;
            hr = temp_support->get_BottomOffset(&support_offset);

            if (fabs(support_offset)>=support_length)
            {
               CComBSTR msg = ::CreateErrorMsg1L(IDS_E_TEMPSUPPORT_OFFSET_GT_LENGTH, mbrId);
               THROW_LBAM_MSG(SUPPORT_OFFSET_GT_LENGTH,msg);
            }

            Float64 support_height = sqrt( support_length*support_length - support_offset*support_offset);
            XyLoc bottom( xtop+support_offset, -support_height );

            Float64 local_dist; // distance along support from bottom of support
            try
            {
               local_dist = GetFracDistance(mbrLocation, support_length);
            }
            catch(FracRes&)
            {
               THROW_LBAM(LOCATION_OOR);
            }

            // compute coordinates of our location in xy
            XyLoc local_loc;
            ComputeSubNodeLocation(bottom, top, local_dist, support_length, &local_loc);

            *Xloc = local_loc.m_X;
            *Yloc = local_loc.m_Y;
         }
      }
      break;
   default:
      THROW_LBAM(INVALID_MEMBERTYPE);
   }
}

STDMETHODIMP CModel::ComputeLocation(MemberIDType mbrID, MemberType mbrType, Float64 mbrLocation, Float64 *Xloc, Float64 *Yloc)
{
   try
   {
      // use utility object to compute
      m_LocationCache.ComputeLocation(mbrID, mbrType, mbrLocation, Xloc, Yloc);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMModel);
   }

	return S_OK;
}


