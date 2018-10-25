///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2015  Washington State Department of Transportation
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

// LoadGroupResponse.cpp : Implementation of CLoadGroupResponse
#include "stdafx.h"
#include "WBFLLBAMAnalysis.h"
#include "LoadGroupResponse.h"

#include "LBAMUtils.h"
#include "LBAMAnalysis.hh"

#include "InfluenceLine.h"
#include "Result3Ds.h"
#include "SectionResult3Ds.h"
#include "SectionStressResults.h"

#include <atlconv.h>
#include <boost\scoped_array.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// handle dealing with cancel from progress monitor
#define LGR_HANDLE_CANCEL_PROGRESS() if (this->CheckForCancel()) throw S_FALSE;

/////////////////////////////////////////////////////////////////////////////
// CLoadGroupResponse

// we can have up to this many temporary supports in a model
static const LoadCaseIDType TS_LIMIT = 10000;

STDMETHODIMP CLoadGroupResponse::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadGroupResponse
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLoadGroupResponse::Init(ILBAMModel* model)
{
   // connect to our model and wire up events
   m_pLBAM = model;

   HRESULT hr;
   hr = CrAdvise(m_pLBAM, this, IID_ILBAMModelEvents, &m_ModelCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_Spans(&m_Spans);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Spans, this, IID_ISpansEvents, &m_SpansCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_SuperstructureMembers(&m_SuperstructureMembers);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_SuperstructureMembers, this, IID_ISuperstructureMembersEvents, &m_SuperstructureMembersCookie);
   if (FAILED(hr))
      return hr;
      
   hr = m_pLBAM->get_Supports(&m_Supports);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Supports, this, IID_ISupportsEvents, &m_SupportsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_POIs(&m_POIs);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_POIs, this, IID_IPOIsEvents, &m_POIsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_Stages(&m_Stages);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_Stages, this, IID_IStagesEvents, &m_StagesCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_LoadGroups(&m_LoadGroups);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_LoadGroups, this, IID_ILoadGroupsEvents, &m_LoadGroupsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_PointLoads(&m_PointLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_PointLoads, this, IID_IPointLoadsEvents, &m_PointLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_DistributedLoads(&m_DistributedLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_DistributedLoads, this, IID_IDistributedLoadsEvents, &m_DistributedLoadsCookie);
   if (FAILED(hr))
      return hr;
      
   hr = m_pLBAM->get_TemperatureLoads(&m_TemperatureLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_TemperatureLoads, this, IID_ITemperatureLoadsEvents, &m_TemperatureLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_SettlementLoads(&m_SettlementLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_SettlementLoads, this, IID_ISettlementLoadsEvents, &m_SettlementLoadsCookie);
   if (FAILED(hr))
      return hr;

   hr = m_pLBAM->get_StrainLoads(&m_StrainLoads);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_StrainLoads, this, IID_IStrainLoadsEvents, &m_StrainLoadsCookie);
   if (FAILED(hr))
      return hr;

   // reset f.e. model
   m_ChangeManager.OnModelHosed();

   return S_OK;
}

HRESULT CLoadGroupResponse::FinalConstruct()
{

   return S_OK;
}

void CLoadGroupResponse::FinalRelease()
{
   // say goodbye to our broadcasters
   HRESULT hr;

   // only do so if model is valid
   if (m_pLBAM)
   {

      hr = CrUnadvise(m_pLBAM, this, IID_ILBAMModelEvents, m_ModelCookie);
      ATLASSERT(SUCCEEDED(hr));

      ATLASSERT(!!m_Spans);
      hr = CrUnadvise(m_Spans, this, IID_ISpansEvents, m_SpansCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_Spans = NULL;

      ATLASSERT(!!m_SuperstructureMembers);
      hr = CrUnadvise(m_SuperstructureMembers, this, IID_ISuperstructureMembersEvents, m_SuperstructureMembersCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_SuperstructureMembers = NULL;

      ATLASSERT(!!m_Supports);
      hr = CrUnadvise(m_Supports, this, IID_ISupportsEvents, m_SupportsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_Supports = NULL;

      ATLASSERT(!!m_POIs);
      hr = CrUnadvise(m_POIs, this, IID_IPOIsEvents, m_POIsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_POIs = NULL;

      ATLASSERT(!!m_Stages);
      hr = CrUnadvise(m_Stages, this, IID_IStagesEvents, m_StagesCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_Stages = NULL;

      ATLASSERT(!!m_LoadGroups);
      hr = CrUnadvise(m_LoadGroups, this, IID_ILoadGroupsEvents, m_LoadGroupsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_LoadGroups = NULL;

      ATLASSERT(!!m_PointLoads);
      hr = CrUnadvise(m_PointLoads, this, IID_IPointLoadsEvents, m_PointLoadsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_PointLoads = NULL;

      ATLASSERT(!!m_DistributedLoads);
      hr = CrUnadvise(m_DistributedLoads, this, IID_IDistributedLoadsEvents, m_DistributedLoadsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_DistributedLoads = NULL;

      ATLASSERT(!!m_TemperatureLoads);
      hr = CrUnadvise(m_TemperatureLoads, this, IID_ITemperatureLoadsEvents, m_TemperatureLoadsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_TemperatureLoads = NULL;

      ATLASSERT(!!m_SettlementLoads);
      hr = CrUnadvise(m_SettlementLoads, this, IID_ISettlementLoadsEvents, m_SettlementLoadsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_SettlementLoads = NULL;

      ATLASSERT(!!m_StrainLoads);
      hr = CrUnadvise(m_StrainLoads, this, IID_IStrainLoadsEvents, m_StrainLoadsCookie);
      ATLASSERT(SUCCEEDED(hr));
      m_StrainLoads = NULL;
   }
}

//////////////////////////
///////   Event Handlers
//////////////////////////

STDMETHODIMP CLoadGroupResponse::OnModelChanged(ILBAMModel* me, ChangeType change)
{
   // this event is going to percolate up for every single event given below. We only pay attention if things are hosed
   if (change == cgtClear || change==cgtUnknown)
      m_ChangeManager.OnModelHosed();

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnSuperstructureMembersChanged(ISuperstructureMember* item, BSTR stage, ChangeType change)
{
   if (change == cgtStress)
      m_ChangeManager.OnStressCalcChanged();
   else
      m_ChangeManager.OnModelHosed();

   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSuperstructureMembersAdded(ISuperstructureMember* item, CollectionIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSuperstructureMembersBeforeRemove(ISuperstructureMember* item, CollectionIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSuperstructureMembersMoveTo(CollectionIndexType from, CollectionIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSuperstructureMembersCopyTo(CollectionIndexType from, CollectionIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSuperstructureMembersReverse()
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSuperstructureMembersOffset()
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnSupportsChanged(ISupport* item, BSTR stage, ChangeType change)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSupportsAdded(ISupport* item, SupportIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSupportsBeforeRemove(ISupport* item, SupportIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSupportsMoveTo(SupportIndexType from, SupportIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSupportsCopyTo(SupportIndexType from, SupportIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSupportsReverse()
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSpansChanged(ISpan* item, BSTR stage, ChangeType change)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSpansAdded(ISpan* item, SpanIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSpansBeforeRemove(ISpan* item, SpanIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSpansMoveTo(SpanIndexType from, SpanIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSpansCopyTo(SpanIndexType from, SpanIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnSpansReverse()
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnPOIsChanged(/*[in]*/IPOI* poi, ChangeType change)
{
   PoiIDType id;
   HRESULT hr = poi->get_ID(&id);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnPOIChanged(id);
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnPOIsRenamed(PoiIDType oldID, PoiIDType newID)
{
   m_ChangeManager.OnPOIRenamed(oldID, newID);
   return S_OK;
}
STDMETHODIMP CLoadGroupResponse::OnPOIsAdded(/*[in]*/IPOI* poi)
{
   PoiIDType id;
   HRESULT hr = poi->get_ID(&id);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnPOIAdded(id);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnPOIsBeforeRemove(/*[in]*/IPOI* poi)
{
   PoiIDType id;
   HRESULT hr = poi->get_ID(&id);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnPOIRemoved(id);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStagesChanged(IStage* item, ChangeType change)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStagesAdded(IStage* item, StageIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStagesBeforeRemove(IStage* item, StageIndexType index)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStagesMoveTo(StageIndexType from, StageIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStagesCopyTo(StageIndexType from, StageIndexType to)
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStagesReverse()
{
   m_ChangeManager.OnModelHosed();
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnLoadGroupsChanged(ILoadGroup* item, ChangeType change)
{
   if (change == cgtDescription)
      ; // do nothing
   else
      m_ChangeManager.OnModelHosed();

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnLoadGroupsRenamed(BSTR oldName, BSTR newName)
{
   m_ChangeManager.OnLoadGroupRenamed(oldName, newName);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnLoadGroupsAdded(ILoadGroup* item)
{
   CComBSTR name;
   HRESULT hr = item->get_Name(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupAdded(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnLoadGroupsBeforeRemove(ILoadGroup* item)
{
   CComBSTR name;
   HRESULT hr = item->get_Name(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupRemoved(name);

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnPointLoadsChanged(/*[in]*/IPointLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnPointLoadsAdded(/*[in]*/IPointLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnPointLoadsBeforeRemove(/*[in]*/IPointLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnDistributedLoadsChanged(/*[in]*/IDistributedLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnDistributedLoadsAdded(/*[in]*/IDistributedLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnDistributedLoadsBeforeRemove(/*[in]*/IDistributedLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnTemperatureLoadsChanged(/*[in]*/ITemperatureLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnTemperatureLoadsAdded(/*[in]*/ITemperatureLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnTemperatureLoadsBeforeRemove(/*[in]*/ITemperatureLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStrainLoadsChanged(/*[in]*/IStrainLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStrainLoadsAdded(/*[in]*/IStrainLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnStrainLoadsBeforeRemove(/*[in]*/IStrainLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnSettlementLoadsChanged(/*[in]*/ISettlementLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnSettlementLoadsAdded(/*[in]*/ISettlementLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::OnSettlementLoadsBeforeRemove(/*[in]*/ISettlementLoadItem* item)
{
   CComBSTR name;
   HRESULT hr = item->get_LoadGroup(&name);
   if (FAILED(hr))
      return hr;

   m_ChangeManager.OnLoadGroupChanged(name);
   return S_OK;
}

/////////////////////
// ChangeManager
//////////////////
void CLoadGroupResponse::ChangeManager::Init()
{
   m_ModelHosed        = true;
   m_StressCalcHosed   = true;
   m_UpdatedInfluenceLoadStages.clear();
   m_ModelUpdated      = false;
   m_IsOrderingUpdated = false;

   m_LoadGroupsEvents.clear();
   m_POIsEvents.clear();
}

void CLoadGroupResponse::ChangeManager::OnModelHosed()
{
   Init();
}

void CLoadGroupResponse::ChangeManager::OnModelUpdated()
{
   Init();
   m_ModelHosed = false;
   m_ModelUpdated = true;
   m_StressCalcHosed = false;
}

void CLoadGroupResponse::ChangeManager::OnOrderingUpdated()
{
   m_IsOrderingUpdated = true;
}

void CLoadGroupResponse::ChangeManager::OnStressCalcChanged()
{
   m_StressCalcHosed = true;
}

void CLoadGroupResponse::ChangeManager::OnInfluenceLoadDataChanged()
{
   // all influence stages are invalid
   m_UpdatedInfluenceLoadStages.clear();
}

bool CLoadGroupResponse::ChangeManager::IsInfluenceCalcHosed(BSTR stage)
{
   if ( IsModelHosed() || HavePOIsChanged())
   {
      m_UpdatedInfluenceLoadStages.clear();
      return true;
   }

   InfluenceStageIterator it( m_UpdatedInfluenceLoadStages.find(stage) );
   return it==m_UpdatedInfluenceLoadStages.end();
}

void CLoadGroupResponse::ChangeManager::OnInfluenceCalcUpdated(BSTR stage)
{
   ATLASSERT(!HavePOIsChanged()); // these must have been fixed before this can be called
   m_UpdatedInfluenceLoadStages.insert(stage);
}


void CLoadGroupResponse::ChangeManager::OnLoadGroupChanged(BSTR loadgroup)
{
   AddLoadGroupEvent(loadgroup, leChanged);
   m_ModelUpdated = false;
}
void CLoadGroupResponse::ChangeManager::OnLoadGroupRenamed(BSTR oldName, BSTR newName)
{
   AddLoadGroupEvent(oldName, leRemoved);
   AddLoadGroupEvent(newName, leAdded);
   m_ModelUpdated = false;
}
void CLoadGroupResponse::ChangeManager::OnLoadGroupAdded(BSTR loadgroup)
{
   AddLoadGroupEvent(loadgroup, leAdded);
   m_ModelUpdated = false;
}
void CLoadGroupResponse::ChangeManager::OnLoadGroupRemoved(BSTR loadgroup)
{
   AddLoadGroupEvent(loadgroup, leRemoved);
   m_ModelUpdated = false;
}

void CLoadGroupResponse::ChangeManager::OnPOIChanged(PoiIDType POI)
{
   AddPOIEvent(POI, leChanged);
   m_ModelUpdated = false;
}
void CLoadGroupResponse::ChangeManager::OnPOIRenamed(PoiIDType oldID, PoiIDType newID)
{
   AddPOIEvent(oldID, leRemoved);
   AddPOIEvent(newID, leAdded);
   m_ModelUpdated = false;
}
void CLoadGroupResponse::ChangeManager::OnPOIAdded(PoiIDType POI)
{
   AddPOIEvent(POI, leAdded);
   m_ModelUpdated = false;
}
void CLoadGroupResponse::ChangeManager::OnPOIRemoved(PoiIDType POI)
{
   AddPOIEvent(POI, leRemoved);
   m_ModelUpdated = false;
}

// accessor functions which help to determine what to do with changes

bool CLoadGroupResponse::ChangeManager::IsModelHosed()
{
   return m_ModelHosed;
}

bool CLoadGroupResponse::ChangeManager::IsModelUpdated()
{
   return m_ModelUpdated;
}

bool CLoadGroupResponse::ChangeManager::IsOrderingUpdated()
{
   return m_IsOrderingUpdated;
}

bool CLoadGroupResponse::ChangeManager::IsStressCalcHosed()
{
   return m_StressCalcHosed;
}

bool CLoadGroupResponse::ChangeManager::HaveLoadGroupsChanged()
{
   ATLASSERT(!m_ModelHosed); // shouldn't be asking if this is the case

   return !m_LoadGroupsEvents.empty();
}

bool CLoadGroupResponse::ChangeManager::HavePOIsChanged()
{
   ATLASSERT(!m_ModelHosed); // shouldn't be asking if this is the case

   return !m_POIsEvents.empty();
}

CLoadGroupResponse::ChangeManager::NameList CLoadGroupResponse::ChangeManager::LoadGroupsForEvent(EventType event)
{
   ATLASSERT(!m_ModelHosed); // shouldn't be asking if this is the case

   NameList list;
   NameEventListIterator it( m_LoadGroupsEvents.begin() );
   NameEventListIterator itend( m_LoadGroupsEvents.end() );
   for (; it!=itend; it++)
   {
      if (it->second == event)
      {
         list.insert(it->first);
      }
   }

   return list;
}

CLoadGroupResponse::ChangeManager::IntegerList CLoadGroupResponse::ChangeManager::POIsForEvent(EventType event)
{
   ATLASSERT(!m_ModelHosed); // shouldn't be asking if this is the case

   IntegerList list;
   IntegerEventListIterator it( m_POIsEvents.begin() );
   IntegerEventListIterator itend( m_POIsEvents.end() );
   for (; it!=itend; it++)
   {
      if (it->second == event)
      {
         list.insert(it->first);
      }
   }

   return list;
}



////////////////////////////////////
///// CAnalysisController Class
////////////////////////////////////

StageIndexType CLoadGroupResponse::CAnalysisController::StageCount()
{
   return m_Stages.size();
}

CComBSTR CLoadGroupResponse::CAnalysisController::Stage(StageIndexType index)
{
   ATLASSERT(index< StageCount());
   return CComBSTR( m_Stages[index] );
}

bool CLoadGroupResponse::CAnalysisController::GetStageIndex(BSTR stage,StageIndexType* pStageIdx)
{
   CComBSTR bstg(stage);
   StageIndexType stageIdx = 0;
   StagesTypeIterator it( m_Stages.begin() );
   StagesTypeIterator itend( m_Stages.end() );
   for (; it != itend; it++)
   {
      if (*it == bstg)
      {
         *pStageIdx = stageIdx;
         return true;
      }

      stageIdx++;
   }

   *pStageIdx = INVALID_INDEX;
   return false;
}

StageIndexType CLoadGroupResponse::CAnalysisController::CheckedStageOrder(BSTR stage)
{
   if (::SysStringLen(stage)==0)
      THROW_LBAMA(BLANK_STAGE_NAMES_NOT_ALLOWED);

   StageIndexType stageIdx;
   if ( !GetStageIndex(stage,&stageIdx) )
   {
      CComBSTR msg =CreateErrorMsg1S(IDS_E_STAGE_NOT_FOUND, stage);
      THROW_LBAMA_MSG(STAGE_NOT_FOUND,msg);
   }

   return stageIdx;
}

void CLoadGroupResponse::CAnalysisController::Update(ILBAMModel* pLBAM)
{
   UpdateStageOrder(pLBAM);

   UpdateLoadGroupOrder(pLBAM);

   UpdateTemporarySupportLoadings(pLBAM);
}

void CLoadGroupResponse::CAnalysisController::UpdateStageOrder(ILBAMModel* pLBAM)
{
   // walk over stages in model and assign a unique integer to each
   CHRException hr;

   m_Stages.clear();

   CComPtr<IStages> stages;
   hr = pLBAM->get_Stages(&stages);
   StageIndexType nStages;
   hr = stages->get_Count(&nStages);
   for (StageIndexType i = 0; i < nStages; i++)
   {
      CComPtr<IStage> stage;
      hr = stages->get_Item(i,&stage);

      CComBSTR name;
      hr = stage->get_Name(&name);

      StageIndexType stageIdx;
      if ( !GetStageIndex(name,&stageIdx) )
      {
         m_Stages.push_back(name);
      }
      else
      {
         // could not insert - stage name is duplicate
         CComBSTR msg = CreateErrorMsg1S(IDS_E_DUPLICATE_STAGE_NAMES, name);
         THROW_LBAMA_MSG(DUPLICATE_STAGE_NAMES, msg);
      }
   }
}

void CLoadGroupResponse::CAnalysisController::UpdateLoadGroupOrder(ILBAMModel* pLBAM)
{
   // walk over load groups in model and assign a unique fem loading id for each.
   // these are the primary load groups. we will also have fe loadings for temporary support reactions.
   CHRException hr;

   m_LastFemLoadCase = 0;
   m_LoadGroups.clear();

   CComPtr<ILoadGroups> loadgroups;
   hr = pLBAM->get_LoadGroups(&loadgroups);
   CollectionIndexType cnt;
   hr = loadgroups->get_Count(&cnt);
   for (CollectionIndexType i=0; i<cnt; i++)
   {
      CComPtr<ILoadGroup> loadgroup;
      hr = loadgroups->get_Item(i,&loadgroup);

      CComBSTR name;
      hr = loadgroup->get_Name(&name);

      VARIANT_BOOL ist;
      hr = loadgroup->get_Transient(&ist);

      // load cases are incremented by TS_LIMIT. This way we can create one load case for every
      // temporary support, up to TS_LIMIT, for each load case.
      m_LastFemLoadCase += TS_LIMIT;

      std::pair<LoadGroupsTypeIterator, bool> tst ( m_LoadGroups.insert(LoadGroupsType::value_type( (BSTR)name, LoadGroupInfo(m_LastFemLoadCase,ist==VARIANT_TRUE))) );
      if (!tst.second)
      {
         // could not insert - loadgroup name is duplicate
         CComBSTR msg = CreateErrorMsg1S(IDS_E_DUPLICATE_LOADGROUP_NAMES, name);
         THROW_LBAMA_MSG(DUPLICATE_LOADGROUP_NAMES, msg);
      }
   }
}

void CLoadGroupResponse::CAnalysisController::UpdateTemporarySupportLoadings(ILBAMModel* pLBAM)
{
   m_TemporarySupportInfo.clear();

   // loop over spans and find all temporary supports. then assign unique load case id to
   // every temporary support that will be removed in the lifetime of the model.
   CHRException hr;
   CComPtr<ISpans> spans;
   hr = pLBAM->get_Spans(&spans);

   SpanIndexType nSpans;
   hr = spans->get_Count(&nSpans);

   for (SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++)
   {
      CComPtr<ISpan> span;
      hr = spans->get_Item(spanIdx, &span);

      CComPtr<ITemporarySupports> temporarySupports;
      hr = span->get_TemporarySupports(&temporarySupports);

      SupportIndexType nTemporarySupports;
      hr = temporarySupports->get_Count(&nTemporarySupports);

      for (SupportIndexType tempSupportIdx = 0; tempSupportIdx < nTemporarySupports; tempSupportIdx++)
      {
         CComPtr<ITemporarySupport> temporarySupport;
         hr = temporarySupports->get_Item(tempSupportIdx, &temporarySupport);

         SupportIDType tempSupportID;
         hr = temporarySupport->get_ID(&tempSupportID);

         CComBSTR bstrRemovalStage;
         hr = temporarySupport->get_StageRemoved(&bstrRemovalStage);

         StageIndexType removalStageIdx;
         if ( GetStageIndex(bstrRemovalStage,&removalStageIdx) )
         {
            m_TemporarySupportInfo.push_back(TemporarySupportInfo(tempSupportID, removalStageIdx));
         }

         //if ( !GetStageIndex(bstrRemovalStage,&removalStageIdx) )
         //{
         //   CComBSTR msg(::CreateErrorMsg1S(IDS_E_NO_REM_STAGE_FOR_TS, bstrRemovalStage));
         //   THROW_LBAMA_MSG(NO_REM_STAGE_FOR_TS,msg);
         //}

         //m_TemporarySupportInfo.push_back(TemporarySupportInfo(tempSupportID, removalStageIdx));
      }
   }
}

void CLoadGroupResponse::CAnalysisController::Clear()
{
   m_LastFemLoadCase = 0;
   m_Stages.clear();
   m_LoadGroups.clear();
}

CollectionIndexType CLoadGroupResponse::CAnalysisController::LoadGroupCount()
{
   return m_LoadGroups.size();
}

CComBSTR CLoadGroupResponse::CAnalysisController::LoadGroup(CollectionIndexType index)
{
   CollectionIndexType cnt=0;
   LoadGroupsTypeIterator it( m_LoadGroups.begin() );
   LoadGroupsTypeIterator itend( m_LoadGroups.end() );
   for (; it!=itend; it++)
   {
      if (cnt==index)
         return it->first;

      cnt++;
   }

   ATLASSERT(false); // invalid index
   return CComBSTR();
}

void CLoadGroupResponse::CAnalysisController::GetLoadGroupInfoByIndex(CollectionIndexType loadGroupIdx, LoadGroupIDType* femLgId, bool* isTransient)
{
   CollectionIndexType currentLoadGroupIdx = 0;
   LoadGroupsTypeIterator it( m_LoadGroups.begin() );
   LoadGroupsTypeIterator itend( m_LoadGroups.end() );
   for (; it != itend; it++)
   {
      if (currentLoadGroupIdx == loadGroupIdx)
      {
         *femLgId     = it->second.m_FemLoadCaseID;
         *isTransient = it->second.m_IsTransient;
         return;
      }
      currentLoadGroupIdx++;
   }

   ATLASSERT(false); // invalid index;
}

void CLoadGroupResponse::CAnalysisController::GetLoadGroupInfo(BSTR loadGroup, LoadCaseIDType* femLoadCaseID, bool* bIsTransient)
{
   // this version throws if there is a problem
   if (::SysStringLen(loadGroup)==0)
      THROW_LBAMA(BLANK_LOADGROUP_NAMES_NOT_ALLOWED);

   LoadGroupsTypeIterator it( m_LoadGroups.find(loadGroup) );
   if (it != m_LoadGroups.end())
   {
      *femLoadCaseID = it->second.m_FemLoadCaseID;
      *bIsTransient   = it->second.m_IsTransient;
   }
   else
   {
      CComBSTR msg = CreateErrorMsg1S(IDS_E_LOADGROUP_NOT_FOUND, loadGroup);
      THROW_LBAMA_MSG(LOADGROUP_NOT_FOUND,msg);
   }
}

SupportIndexType CLoadGroupResponse::CAnalysisController::TemporarySupportCount()
{
   return m_TemporarySupportInfo.size();
}

SupportIndexType CLoadGroupResponse::CAnalysisController::GetTemporarySupportIndex(SupportIDType tsID)
{
   std::vector<TemporarySupportInfo>::iterator iter(m_TemporarySupportInfo.begin());
   std::vector<TemporarySupportInfo>::iterator iterEnd(m_TemporarySupportInfo.end());
   for ( ; iter != iterEnd; iter++ )
   {
      if ( iter->m_ID == tsID )
      {
         return std::distance(m_TemporarySupportInfo.begin(),iter);
      }
   }
   return INVALID_INDEX;
}

SupportIDType CLoadGroupResponse::CAnalysisController::GetTemporarySupportID(SupportIndexType tempSupportIdx)
{
   ATLASSERT(tempSupportIdx < TemporarySupportCount());
   return m_TemporarySupportInfo[tempSupportIdx].m_ID;
}

StageIndexType CLoadGroupResponse::CAnalysisController::TemporarySupportRemovalStageIndex( SupportIndexType tempSupportIdx)
{
   ATLASSERT(tempSupportIdx < TemporarySupportCount());
   return m_TemporarySupportInfo[tempSupportIdx].m_RemovalStageIdx;
}


void CLoadGroupResponse::CAnalysisController::GetResponseControlInfo(BSTR loadGroup, BSTR stage, ResultsSummationType summType,
                            TemporarySupportLoadInfoColl& tempSuppportLoadInfo)
{
   // get load group info
   LoadCaseIDType femLoadCaseID;
   bool bIsTransient;
   this->GetLoadGroupInfo(loadGroup, &femLoadCaseID, &bIsTransient);

   // get stage sequencing
   StageIndexType startStageIdx = 0; // assume cumulative through stages
   StageIndexType endStageIdx = CheckedStageOrder(stage);
   if (summType == rsIncremental || bIsTransient)
   {
      startStageIdx = endStageIdx;
   }

   // we have primary load group information, so set it
   tempSuppportLoadInfo.clear();

   for (StageIndexType stageIdx = startStageIdx; stageIdx <= endStageIdx; stageIdx++)
   {
      tempSuppportLoadInfo.push_back(TemporarySupportLoadInfo(femLoadCaseID, stageIdx));
   }
}

void CLoadGroupResponse::CAnalysisController::SetLoadGroupAsActive(BSTR loadGroup)
{
   // this version throws if there is a problem
   if (::SysStringLen(loadGroup)==0)
      THROW_LBAMA(BLANK_LOADGROUP_NAMES_NOT_ALLOWED);

   LoadGroupsTypeIterator it( m_LoadGroups.find(loadGroup) );
   if (it != m_LoadGroups.end())
   {
      it->second.m_IsLoaded =true ;
   }
   else
   {
      CComBSTR msg =CreateErrorMsg1S(IDS_E_LOADGROUP_NOT_FOUND, loadGroup);
      THROW_LBAMA_MSG(LOADGROUP_NOT_FOUND,msg);
   }
}

IBstrArray* CLoadGroupResponse::CAnalysisController::GetActiveLoadGroups()
{
   // get active loadgroup names
   CollectionIndexType ttlsize = m_LoadGroups.size();
   CComPtr<IBstrArray> names;
   names.CoCreateInstance(CLSID_BstrArray);
   names->Reserve(ttlsize);

   LoadGroupsTypeIterator it( m_LoadGroups.begin() );
   LoadGroupsTypeIterator itend( m_LoadGroups.end() );
   for (; it!=itend; it++ )
   {
      if (it->second.m_IsLoaded)
      {
         names->Add( it->first );
      }
   }

   return names.Detach();

}
/////////////////////////////////////////////////////
////// Internal Implementation
/////////////////////////////////////////////////////

void CLoadGroupResponse::ValidateInfluenceCalc(BSTR stage)
{
   try
   {
      bool do_val = m_ChangeManager.IsInfluenceCalcHosed(stage); // have to call before ValidateModels to capture true state

      // make sure our underlying model is good
      ValidateModels();

      if (do_val)
      {
         // clear out our cache
         m_CachedForceInfluenceLines.clear();
         m_CachedDeflectionInfluenceLines.clear();
         m_CachedReactionInfluenceLines.clear();
         m_CachedSupportDeflectionInfluenceLines.clear();

         // clear out loadings in fem model
         StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);

         boost::shared_ptr<CAnalysisModel> pAnalysisModel = m_Models[stg_idx];
         pAnalysisModel->ClearInfluenceLoads();

         // determine all influence loading locations and,
         // generate influence loads and their fem loadings
         pAnalysisModel->GenerateInfluenceLoads();
      }

      // we are up to date now
      m_ChangeManager.OnInfluenceCalcUpdated(stage);

   }
   catch(...)
   {
      ATLASSERT(false);
      ClearModels();
      throw;
   }
}

void CLoadGroupResponse::ValidateModels()
{
   try
   {
      // logic in this function mostly deals with events
      // see if model needs to be updated
      if (! m_ChangeManager.IsModelUpdated())
      {
         if (!m_pLBAM)
            THROW_LBAMA(MODEL_DOES_NOT_EXIST);

         if (m_ChangeManager.IsModelHosed())
         {
            // model is completely hosed - rebuild from ground up
            ClearModels();

            // first update stage and loadgroup ordering
            m_AnalysisController.Update(m_pLBAM);
            m_ChangeManager.OnOrderingUpdated();

            // loop over stages and create model geometries for each stage
            StageIndexType nStages = m_AnalysisController.StageCount();
            for (StageIndexType stageIdx = 0; stageIdx < nStages; stageIdx++)
            {
               CComBSTR bstrStage = m_AnalysisController.Stage(stageIdx);
               boost::shared_ptr<CAnalysisModel> pAnalysisModel(
                        new CAnalysisModel(m_pLBAM, bstrStage, &m_AnalysisController, &m_AnalysisController, 
                                           m_MinSpanPoiIncrement, m_MinCantileverPoiIncrement,
                                           m_ForForces) );
               
               m_Models.push_back( pAnalysisModel );

               pAnalysisModel->BuildModel(bstrStage);
            }

            // Next need to apply reaction forces for temporary supports in
            // their support removal stages. Applied reaction force for each load group
            // is equal to the sum of the reaction forces up to the removal stage.
            ValidateTemporarySupportForces();

            // tell the change manager we're up to date
            m_ChangeManager.OnModelUpdated();

         }
         else
         {
            // changes were made, but model is not completely hosed
            if (m_ChangeManager.HaveLoadGroupsChanged() 
                || m_ChangeManager.HavePOIsChanged() 
                || m_ChangeManager.IsStressCalcHosed())
            {
               if (m_ChangeManager.HaveLoadGroupsChanged())
               {
                  // clear out all loads and rebuild them. 
                  // This is pretty harsh since we have better information about what changed, but it's easy
                  m_AnalysisController.Update(m_pLBAM);
                  m_ChangeManager.OnOrderingUpdated();

                  // loop over stages and rebuild loads for each stage
                  StageIndexType nStages = m_AnalysisController.StageCount();
                  for (StageIndexType stageIdx = 0; stageIdx < nStages; stageIdx++)
                  {
                     boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];
                     pFemModel->ClearLoads();
                     pFemModel->GenerateLoads();
                  }

                  // Apply reaction forces for temporary supports
                  ValidateTemporarySupportForces();
               }

               if (m_ChangeManager.HavePOIsChanged() || m_ChangeManager.IsStressCalcHosed())
               {
                  // clear out all POIs and rebuild them. 
                  // This is pretty harsh since we have better information about what changed, but it's easy
                  StageIndexType nStages = m_AnalysisController.StageCount();
                  for (StageIndexType stageIdx = 0; stageIdx < nStages; stageIdx++)
                  {
                     boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];
                     pFemModel->ClearPOIs();
                     pFemModel->GeneratePOIs();
                  }
               }
            }
            else
            {
               ATLASSERT(false); // type of change not handled properly
            }

            // tell the change manager we're up to date
            // must do this outside of the if-else block... if one or more of the
            // change types have to be processed, processing the first one would
            // and then calling m_ChangeManager.OnModelUpdated() caused processing
            // of the subsequent change times to be skipped. An example is model that
            // has the load group changed and POI changed. The load group would get
            // processed, but the poi would not.
            // moving this call here, solves that problem
            m_ChangeManager.OnModelUpdated();
         }
      }
   }
   catch(...)
   {
      // something got screwed and we're not coming back to dig up the bones
      // blast the models
      ATLASSERT(false);
      ClearModels();
      throw;
   }
}

void CLoadGroupResponse::ValidateTemporarySupportForces()
{
   CollectionIndexType nLoadGroups   = m_AnalysisController.LoadGroupCount();
   SupportIndexType nTempSupports = m_AnalysisController.TemporarySupportCount();

   CComPtr<ITemporarySupports> tempSupports;
   m_pLBAM->get_TemporarySupports(&tempSupports);

   for (CollectionIndexType loadGroupIdx = 0; loadGroupIdx < nLoadGroups; loadGroupIdx++)
   {
      LoadGroupIDType lg_fe;
      bool is_transient;
      m_AnalysisController.GetLoadGroupInfoByIndex(loadGroupIdx, &lg_fe, &is_transient);

      // temporary support reactions are only computed for non-transient (permanent)
      // load groups.
      if (!is_transient)
      {
         for (SupportIndexType tempSupportIdx = 0; tempSupportIdx < nTempSupports; tempSupportIdx++)
         {
            Float64 fx=0.0, fy=0.0, mz = 0.0;

            SupportIDType tempSupportID = m_AnalysisController.GetTemporarySupportID(tempSupportIdx);

            CComPtr<ITemporarySupport> ts;
            tempSupports->Find(tempSupportID,&ts);

            VARIANT_BOOL bOmitReaction;
            ts->get_OmitReaction(&bOmitReaction);

            if ( bOmitReaction == VARIANT_FALSE )
            {
               // sum to removal stage
               StageIndexType removalStageIdx = m_AnalysisController.TemporarySupportRemovalStageIndex(tempSupportIdx);
               CAnalysisModel& rfemModel_AfterRemoval = *(m_Models[removalStageIdx]);
               for (StageIndexType stageIdx = 0; stageIdx < removalStageIdx; stageIdx++)
               {
                  // get fem model for this stage
                  CAnalysisModel& rfemModel = *(m_Models[stageIdx]);

                  Float64 lfx, lfy, lmz;
                  rfemModel.GetTemporarySupportReaction(lg_fe, tempSupportID, &lfx, &lfy, &lmz);
                  rfemModel_AfterRemoval.ApplyTemporarySupportReaction(lg_fe,tempSupportID,-lfx,-lfy,-lmz);
               }
            }
         }
      }
   }
}

void CLoadGroupResponse::ClearModels()
{
   // clear out all data related to models
   m_Models.clear();
   m_AnalysisController.Clear();
   m_ChangeManager.OnModelHosed();
}

///////////////////////////////////////////////////////////////
////// IDependOnLBAM
///////////////////////////////////////////////////////////////

STDMETHODIMP CLoadGroupResponse::get_Model(ILBAMModel **pVal)
{
	CHECK_RETOBJ(pVal);
   try
   {
      if (!m_pLBAM)
      {
         //THROW_LBAMA(MODEL_DOES_NOT_EXIST);
         *pVal = 0;
      }
      else
      {
         *pVal = m_pLBAM;
         (*pVal)->AddRef();
      }
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }


	return S_OK;
}

STDMETHODIMP CLoadGroupResponse::putref_Model(ILBAMModel *newVal)
{
   CHECK_IN(newVal);

   // release connection points
	if (m_pLBAM)
      FinalRelease();

   HRESULT hr = Init(newVal);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

	return S_OK;
}

///////////////////////////////////////////////////////////////
// ISupportProgressMonitor
///////////////////////////////////////////////////////////////
STDMETHODIMP CLoadGroupResponse::InitializeProgressMonitor(IProgressMonitor * newVal, LONG cookie)
{
   m_pProgressMonitor = newVal;
   m_ProgressCookie = cookie;

   return S_OK;
}


///////////////////////////////////////////////////////////////
////// ILoadGroupResponse
///////////////////////////////////////////////////////////////

STDMETHODIMP CLoadGroupResponse::ComputeForces(BSTR LoadGroup, IIDArray* poiIDs, BSTR Stage, 
                                          ResultsOrientation orientation, ResultsSummationType summType,
                                          ISectionResult3Ds **results)
{
   CHECK_IN(poiIDs);
   CHECK_RETOBJ(results);

   try
   {
      CHRException hr;

      // first validate our models
      ValidateModels();

      // let's see how many pois we have to return results for
      CollectionIndexType nPOIs;
      hr = poiIDs->get_Count(&nPOIs);

      // create our results collection 
      CComObject<CSectionResult3Ds>* pcresults;
      hr = CComObject<CSectionResult3Ds>::CreateInstance(&pcresults);
      CComPtr<ISectionResult3Ds> the_results(pcresults);
      hr = the_results->Reserve(nPOIs);

      // get staging and loading control info from analysis controller
      CAnalysisController::TemporarySupportLoadInfoColl tempSupportLoadInfo;
      m_AnalysisController.GetResponseControlInfo(LoadGroup, Stage, summType, tempSupportLoadInfo);

      LGR_HANDLE_CANCEL_PROGRESS();  // could put this in poi loop, but might cause performance problems

      // loop over stages and poi's
      Float64 fx_left, fx_right, fy_left, fy_right, mz_left, mz_right;
      for (CollectionIndexType poiIdx = 0; poiIdx < nPOIs; poiIdx++)
      {
         PoiIDType poiID;
         hr = poiIDs->get_Item(poiIdx, &poiID);

         if (poiID < 0 && summType==rsCumulative)
         {
            // cannot request cumulative results for internally generated pois
            THROW_LBAMA(TEMP_POIS_CUMMULATIVE);
         }

         // create results object and add it to the collection
         CComObject<CSectionResult3D>* presult;
         hr = CComObject<CSectionResult3D>::CreateInstance(&presult);
         CComPtr<ISectionResult3D> the_result(presult);

         hr = the_results->Add(the_result);

         // loop over stages to and load cases associated with the request
         CAnalysisController::TemporarySupportLoadInfoIterator iter(tempSupportLoadInfo.begin() );
         CAnalysisController::TemporarySupportLoadInfoIterator iterend(tempSupportLoadInfo.end() );
         for (; iter != iterend; iter++)
         {
            const CAnalysisController::TemporarySupportLoadInfo& tempSupportLoadInfo = *iter;
            boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[tempSupportLoadInfo.m_StageIdx];

            // compute the load group results
            pFemModel->GetForce(tempSupportLoadInfo.m_FemLoadCaseID, poiID, orientation, &fx_left, &fy_left, &mz_left, &fx_right, &fy_right, &mz_right);

            // sum results 
            hr = the_result->Sum(fx_left, fy_left, mz_left, fx_right, fy_right, mz_right);
         }
      }

      LGR_HANDLE_CANCEL_PROGRESS(); 

      hr = the_results.CopyTo(results);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeDeflections(BSTR LoadGroup, IIDArray* poiIDs, BSTR Stage, 
                                                    ResultsSummationType summType, ISectionResult3Ds **results)
{
   CHECK_RETOBJ(results);

   try
   {
     CHRException hr;

      // first validate our models
      ValidateModels();

      // let's see how many pois we have to return results for
      CollectionIndexType nPOIs;
      hr = poiIDs->get_Count(&nPOIs);

      // create our results collection 
      CComObject<CSectionResult3Ds>* pcresults;
      hr = CComObject<CSectionResult3Ds>::CreateInstance(&pcresults);
      CComPtr<ISectionResult3Ds> the_results(pcresults);
      hr = the_results->Reserve(nPOIs);

      // get staging and loading control info from analysis controller
      CAnalysisController::TemporarySupportLoadInfoColl tempSupportLoadInfo;
      m_AnalysisController.GetResponseControlInfo(LoadGroup, Stage, summType, tempSupportLoadInfo);

      LGR_HANDLE_CANCEL_PROGRESS();  // could put this in poi loop, but might cause performance problems

      // loop over stages and poi's
      Float64 ldx, ldy, lrz, rdx, rdy, rrz;
      for (CollectionIndexType poiIdx = 0; poiIdx < nPOIs; poiIdx++)
      {
         PoiIDType poiID;
         hr = poiIDs->get_Item(poiIdx, &poiID);

         if (poiID < 0 && summType == rsCumulative)
         {
            // cannot request cumulative results for internally generated pois
            THROW_LBAMA(TEMP_POIS_CUMMULATIVE);
         }

         // create results object and add it to the collection
         CComObject<CSectionResult3D>* presult;
         hr = CComObject<CSectionResult3D>::CreateInstance(&presult);

         CComPtr<ISectionResult3D> the_result(presult);
         hr = the_results->Add(the_result);

         // loop over stages to and load cases associated with the request
         CAnalysisController::TemporarySupportLoadInfoIterator iter( tempSupportLoadInfo.begin() );
         CAnalysisController::TemporarySupportLoadInfoIterator iterend( tempSupportLoadInfo.end() );
         for (; iter != iterend; iter++)
         {
            const CAnalysisController::TemporarySupportLoadInfo& tempSupportLoadInfo = *iter;
            boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[tempSupportLoadInfo.m_StageIdx];

            // compute the load group results
            pFemModel->GetDeflection(tempSupportLoadInfo.m_FemLoadCaseID, poiID, &ldx, &ldy, &lrz, &rdx, &rdy, &rrz);

            // sum results from temporary support removal forces
            hr = the_result->Sum( ldx, ldy, lrz, rdx, rdy, rrz);
         }
      }

      LGR_HANDLE_CANCEL_PROGRESS(); 

      *results = the_results;
      (*results)->AddRef(); // for client
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeReactions(BSTR LoadGroup, IIDArray* supportIDs, BSTR Stage, ResultsSummationType summType, IResult3Ds** results)
{
   CHECK_RETOBJ(results);

   try
   {
      CHRException hr;

      // first validate our models
      ValidateModels();

      // let's see how many supports we have to return results for
      CollectionIndexType nSupportIDs;
      hr = supportIDs->get_Count(&nSupportIDs);

      // create our results collection 
      CComObject<CResult3Ds>* pcresults;
      hr = CComObject<CResult3Ds>::CreateInstance(&pcresults);
      CComPtr<IResult3Ds> the_results(pcresults);
      hr = the_results->Reserve(nSupportIDs);

      // get staging and loading control info from analysis controller
      CAnalysisController::TemporarySupportLoadInfoColl tempSupportLoadInfo;
      m_AnalysisController.GetResponseControlInfo(LoadGroup, Stage, summType, tempSupportLoadInfo);

      LGR_HANDLE_CANCEL_PROGRESS(); 

      // loop over stages and supports
      Float64 fx, fy, mz;
      for (CollectionIndexType supportIDIdx = 0; supportIDIdx < nSupportIDs; supportIDIdx++)
      {
         SupportIDType supportID;
         hr = supportIDs->get_Item(supportIDIdx, &supportID);

         SupportIndexType tempSupportIdx = m_AnalysisController.GetTemporarySupportIndex(supportID);
         if ( tempSupportIdx != INVALID_INDEX )
         {
            StageIndexType tempSupportRemovalStageIdx = m_AnalysisController.TemporarySupportRemovalStageIndex(tempSupportIdx);

            StageIndexType thisStageIdx = m_AnalysisController.CheckedStageOrder(Stage);
            if ( tempSupportRemovalStageIdx <= thisStageIdx )
            {
               // this support is a temporary support and it has already been removed... report
               // its cumulative and incremental reaction as zero

               // create results object and add it to the collection
               CComObject<CResult3D>* presult;
               hr = CComObject<CResult3D>::CreateInstance(&presult);

               CComPtr<IResult3D> the_result(presult);
               hr = the_results->Add(the_result);
               the_result->Sum(0,0,0);
               continue; // next support
            }
         }

         // create results object and add it to the collection
         CComObject<CResult3D>* presult;
         hr = CComObject<CResult3D>::CreateInstance(&presult);

         CComPtr<IResult3D> the_result(presult);
         hr = the_results->Add(the_result);

         // loop over stages and load cases associated with the request
         CAnalysisController::TemporarySupportLoadInfoIterator iter( tempSupportLoadInfo.begin() );
         CAnalysisController::TemporarySupportLoadInfoIterator iterend( tempSupportLoadInfo.end() );
         for (; iter != iterend; iter++)
         {
            const CAnalysisController::TemporarySupportLoadInfo& tempSupportLoadInfo = *iter;
            boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[tempSupportLoadInfo.m_StageIdx];

            // compute the load group results
            pFemModel->GetReaction(tempSupportLoadInfo.m_FemLoadCaseID, supportID,  &fx, &fy, &mz);

            // sum results from temporary support removal forces
            hr = the_result->Sum( fx, fy, mz);
         }
      }

      LGR_HANDLE_CANCEL_PROGRESS(); 

      *results = the_results;
      (*results)->AddRef(); // for client

   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeStresses(BSTR LoadGroup, IIDArray* poiIDs, BSTR Stage, 
                                                 ResultsSummationType summ,
                                                 ISectionStressResults **results)
{
   CHECK_RETOBJ(results);

   try
   {
      CHRException hr;
      HRESULT hrr;

      // first validate our models
      ValidateModels();

      // let's see how many pois we have to return results for
      CollectionIndexType nPOIs;
      hr = poiIDs->get_Count(&nPOIs);

      // create our results collection 
      CComObject<CSectionStressResults>* pcresults;
      hr = CComObject<CSectionStressResults>::CreateInstance(&pcresults);
      CComPtr<ISectionStressResults> the_results(pcresults);
      hr = the_results->Reserve(nPOIs);

      // get staging and loading control info from analysis controller
      CAnalysisController::TemporarySupportLoadInfoColl tempSupportLoadInfo;
      m_AnalysisController.GetResponseControlInfo(LoadGroup, Stage, summ, tempSupportLoadInfo);

      LGR_HANDLE_CANCEL_PROGRESS(); 

      // loop over stages and poi's
      for (CollectionIndexType poiIdx = 0; poiIdx < nPOIs; poiIdx++)
      {
         PoiIDType poiID;
         hr = poiIDs->get_Item(poiIdx, &poiID);

         if (poiID < 0 && summ == rsCumulative)
         {
            // cannot request cumulative results for internally generated pois
            THROW_LBAMA(TEMP_POIS_CUMMULATIVE);
         }

         // create results object and add it to the collection
         CComObject<CSectionStressResult>* presult;
         hr = CComObject<CSectionStressResult>::CreateInstance(&presult);

         CComPtr<ISectionStressResult> the_result(presult);
         hr = the_results->Add(the_result);

         CComPtr<IHpSectionStressResult> hp_result(presult);

         // loop over stages to and load cases associated with the request
         bool was_computed=false;
         bool first=true;
         std::vector<Float64> s_left, s_right;
         CAnalysisController::TemporarySupportLoadInfoIterator iter( tempSupportLoadInfo.begin() );
         CAnalysisController::TemporarySupportLoadInfoIterator iterend( tempSupportLoadInfo.end() );
         for (; iter != iterend; iter++)
         {
            const CAnalysisController::TemporarySupportLoadInfo& tempSupportLoadInfo = *iter;
            boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[tempSupportLoadInfo.m_StageIdx];

            // compute stress for this increment
            bool was_computed_for_this_load_case;
            pFemModel->GetStress(tempSupportLoadInfo.m_FemLoadCaseID, poiID, s_left, s_right, &was_computed_for_this_load_case);

            was_computed |= was_computed_for_this_load_case;

            CollectionIndexType left_size  = s_left.size();
            CollectionIndexType right_size = s_right.size();

            // we have to pass data into the results object using arrays
            // of data... use a smart array pointer so we are exception safe
            boost::scoped_array<Float64> pLeft(new Float64[left_size]);
            boost::scoped_array<Float64> pRight(new Float64[right_size]);
            for ( CollectionIndexType i = 0; i < left_size; i++ )
               pLeft[i] = s_left[i];

            for ( CollectionIndexType i = 0; i < right_size; i++ )
               pRight[i] = s_right[i];


            if (first)
            {
               first = false;
               hr = hp_result->HpSetResults(left_size, pLeft.get(), right_size, pRight.get());
            }
            else
            {
               hrr = hp_result->HpSumResults(left_size, pLeft.get(), right_size, pRight.get());
               if (hrr==E_INVALIDARG)
               {
                  // number of stress points is mismatched through stages
                  CComBSTR msg = CreateErrorMsg1L(IDS_E_MM_STRESSPOINTS, poiID);
                  THROW_LBAMA_MSG(MM_STRESSPOINTS,msg);
               }
            }
         }

         // make sure stress was really computed for least one increment
         if (!was_computed)
         {
            CComBSTR msg = CreateErrorMsg1L(IDS_E_STRESS_NC, poiID);
            THROW_LBAMA_MSG(STRESS_NC,msg);
         }
      }

      LGR_HANDLE_CANCEL_PROGRESS(); 

      *results = the_results;
      (*results)->AddRef(); // for client
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeSupportDeflections(BSTR LoadGroup, IIDArray* supportIDs, BSTR Stage, ResultsSummationType summType, IResult3Ds** results)
{
   CHECK_RETOBJ(results);

   try
   {
      CHRException hr;

      // first validate our models
      ValidateModels();

      // let's see how many supports we have to return results for
      CollectionIndexType nSupportIDs;
      hr = supportIDs->get_Count(&nSupportIDs);

      // create our results collection 
      CComObject<CResult3Ds>* pcresults;
      hr = CComObject<CResult3Ds>::CreateInstance(&pcresults);
      CComPtr<IResult3Ds> the_results(pcresults);
      hr = the_results->Reserve(nSupportIDs);

      // get staging and loading control info from analysis controller
      CAnalysisController::TemporarySupportLoadInfoColl tempSupportLoadInfo;
      m_AnalysisController.GetResponseControlInfo(LoadGroup, Stage, summType, tempSupportLoadInfo);

      LGR_HANDLE_CANCEL_PROGRESS(); 

      // loop over stages and supports
      Float64 dx, dy, rz;
      for (CollectionIndexType supportIDIdx = 0; supportIDIdx < nSupportIDs; supportIDIdx++)
      {
         SupportIDType supportID;
         hr = supportIDs->get_Item(supportIDIdx, &supportID);

         // create results object and add it to the collection
         CComObject<CResult3D>* presult;
         hr = CComObject<CResult3D>::CreateInstance(&presult);

         CComPtr<IResult3D> the_result(presult);
         hr = the_results->Add(the_result);

         // loop over stages and load cases associated with the request
         CAnalysisController::TemporarySupportLoadInfoIterator iter( tempSupportLoadInfo.begin() );
         CAnalysisController::TemporarySupportLoadInfoIterator iterend( tempSupportLoadInfo.end() );
         for (; iter != iterend; iter++)
         {
            const CAnalysisController::TemporarySupportLoadInfo& tempSupportLoadInfo = *iter;
            boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[tempSupportLoadInfo.m_StageIdx];

            // compute the load group results
            pFemModel->GetSupportDeflection(tempSupportLoadInfo.m_FemLoadCaseID, supportID,  &dx, &dy, &rz);

            // sum results from temporary support removal forces
            hr = the_result->Sum( dx, dy, rz);
         }
      }

      LGR_HANDLE_CANCEL_PROGRESS(); 

      *results = the_results;
      (*results)->AddRef(); // for client
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::DumpFEMModels()
{
   ModelsIterator modelIter(m_Models.begin());
   ModelsIterator modelIterEnd(m_Models.end());
   for ( ; modelIter != modelIterEnd; modelIter++)
   {
      boost::shared_ptr<CAnalysisModel>& analysisModel(*modelIter);
      analysisModel->DumpFEMModel();
   }
   return S_OK;
}


///////////////////////////////////////////////////////////////
////// IUnitLoadReponse
///////////////////////////////////////////////////////////////
// 
STDMETHODIMP CLoadGroupResponse::ComputeForces(IIDArray* poiIDs,PoiIDType ldPoiID,BSTR bstrStage,ForceEffectType forceEffectType,ResultsOrientation orientation,ISectionResult3Ds** results)
{
   ATLASSERT(forceEffectType == fetFy || forceEffectType == fetMz);

   CHECK_IN(poiIDs);
   CHECK_RETOBJ(results);

   try
   {
      CHRException hr;

      ValidateInfluenceCalc(bstrStage);

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(bstrStage);
      boost::shared_ptr<CAnalysisModel> pAnalysisModel = m_Models[stageIdx];


      // let's see how many pois we have to return results for
      CollectionIndexType nPOIs;
      hr = poiIDs->get_Count(&nPOIs);

      // create our results collection 
      CComObject<CSectionResult3Ds>* pcresults;
      hr = CComObject<CSectionResult3Ds>::CreateInstance(&pcresults);
      CComPtr<ISectionResult3Ds> the_results(pcresults);
      hr = the_results->Reserve(nPOIs);

      LGR_HANDLE_CANCEL_PROGRESS();  // could put this in poi loop, but might cause performance problems

      // loop over stages and poi's
      Float64 fx_left, fx_right, fy_left, fy_right, mz_left, mz_right;
      for (CollectionIndexType poiIdx = 0; poiIdx < nPOIs; poiIdx++)
      {
         PoiIDType poiID;
         hr = poiIDs->get_Item(poiIdx, &poiID);

         // create results object and add it to the collection
         CComObject<CSectionResult3D>* presult;
         hr = CComObject<CSectionResult3D>::CreateInstance(&presult);
         CComPtr<ISectionResult3D> the_result(presult);

         hr = the_results->Add(the_result);

         pAnalysisModel->GetUnitLoadResponse(poiID,ldPoiID,forceEffectType,orientation, &fx_left, &fy_left, &mz_left, &fx_right, &fy_right, &mz_right);

         // sum results 
         hr = the_result->Sum(fx_left, fy_left, mz_left, fx_right, fy_right, mz_right);
      }

      LGR_HANDLE_CANCEL_PROGRESS(); 

      hr = the_results.CopyTo(results);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

///////////////////////////////////////////////////////////////
////// IInfluenceLineResponse
///////////////////////////////////////////////////////////////
// 
STDMETHODIMP CLoadGroupResponse::SetZeroTolerance(Float64 forceTol, Float64 deflTol)
{
   if (forceTol<0.0)
      return E_INVALIDARG;

   if (deflTol<0.0)
      return E_INVALIDARG;

   m_ForceInfluenceZeroTolerance      = forceTol;
   m_DeflectionInfluenceZeroTolerance = deflTol;

	return S_OK;
}

STDMETHODIMP CLoadGroupResponse::GetZeroTolerance(Float64* forceTol, Float64* deflTol)
{
   CHECK_RETVAL(forceTol);
   CHECK_RETVAL(deflTol);

	*forceTol = m_ForceInfluenceZeroTolerance;
	*deflTol  = m_DeflectionInfluenceZeroTolerance;

	return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeForceInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType forceEffect, ResultsOrientation orientation, IInfluenceLine** leftInfl, IInfluenceLine** rightInfl)
{
   CHECK_RETOBJ(leftInfl);
   CHECK_RETOBJ(rightInfl);
   CHRException hr;

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateInfluenceCalc(stage);

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);

      // check to see if we've already stored our influence line
      DvInfluenceLineCacheIterator it( m_CachedForceInfluenceLines.find( DvInfluenceLineKeeper(poiID, stageIdx, forceEffect, orientation, NULL, NULL) ) );

      LGR_HANDLE_CANCEL_PROGRESS(); 

      if (it != m_CachedForceInfluenceLines.end())
      {
         // we've got it in our cache
         hr = it->LeftInfluenceLine.CopyTo(leftInfl);
         hr = it->RightInfluenceLine.CopyTo(rightInfl);
      }
      else
      {
         // need to compute it
         hr = CacheInfluenceLines(poiID,stage,orientation);

         LGR_HANDLE_CANCEL_PROGRESS(); 

         DvInfluenceLineCacheIterator it ( m_CachedForceInfluenceLines.find( DvInfluenceLineKeeper(poiID, stageIdx, forceEffect, orientation, NULL, NULL) ) );

         ATLASSERT(it != m_CachedForceInfluenceLines.end());
         hr = it->LeftInfluenceLine.CopyTo(leftInfl);
         hr = it->RightInfluenceLine.CopyTo(rightInfl);
      }
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return hr;
}

STDMETHODIMP CLoadGroupResponse::ComputeDeflectionInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType deflectionEffect, IInfluenceLine** leftInfl, IInfluenceLine** rightInfl)
{
   CHECK_RETOBJ(leftInfl);
   CHECK_RETOBJ(rightInfl);
   CHRException hr;

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateInfluenceCalc(stage);

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);

      LGR_HANDLE_CANCEL_PROGRESS(); 

      // check to see if we've already stored our influence line
      DvInfluenceLineCacheIterator it( m_CachedDeflectionInfluenceLines.find( DvInfluenceLineKeeper(poiID, stageIdx, deflectionEffect, roGlobal, NULL,NULL) ) );

      if (it != m_CachedDeflectionInfluenceLines.end())
      {
         // we've got it in our cache
         hr = it->LeftInfluenceLine.CopyTo(leftInfl);
         hr = it->RightInfluenceLine.CopyTo(rightInfl);
      }
      else
      {
         // need to compute it
         hr = CacheInfluenceLines(poiID,stage,roMember);

         LGR_HANDLE_CANCEL_PROGRESS(); 

         DvInfluenceLineCacheIterator it( m_CachedDeflectionInfluenceLines.find( DvInfluenceLineKeeper(poiID, stageIdx, deflectionEffect, roGlobal, NULL, NULL) ) );

         ATLASSERT(it != m_CachedDeflectionInfluenceLines.end());
         hr = it->LeftInfluenceLine.CopyTo(leftInfl);
         hr = it->RightInfluenceLine.CopyTo(rightInfl);
      }
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeReactionInfluenceLine(SupportIDType supportID, BSTR stage, ForceEffectType ReactionEffect, IInfluenceLine** newVal)
{
   CHECK_RETOBJ(newVal);
   CHRException hr;

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateInfluenceCalc(stage);

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);

      LGR_HANDLE_CANCEL_PROGRESS(); 

      // check to see if we've already stored our influence line
      SvInfluenceLineCacheIterator it( m_CachedReactionInfluenceLines.find( SvInfluenceLineKeeper(supportID, stageIdx, ReactionEffect, roGlobal, NULL) ) );

      if (it != m_CachedReactionInfluenceLines.end())
      {
         // we've got it in our cache
         return it->InfluenceLine.CopyTo(newVal);
      }
      else
      {

         boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];

         CComObject<CInfluenceLine>* infl_line;
         hr = CComObject<CInfluenceLine>::CreateInstance(&infl_line);
         CComPtr<IInfluenceLine> pinfl(infl_line);

         pFemModel->GetReactionInfluenceLine(supportID, ReactionEffect, infl_line);

         infl_line->SetZeroTolerance(m_ForceInfluenceZeroTolerance);

         m_CachedReactionInfluenceLines.insert( SvInfluenceLineKeeper(supportID, stageIdx, ReactionEffect, roGlobal, pinfl) );

         LGR_HANDLE_CANCEL_PROGRESS(); 

         return pinfl.CopyTo(newVal);
      }
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}


STDMETHODIMP CLoadGroupResponse::ComputeSupportDeflectionInfluenceLine(SupportIDType supportID, BSTR stage, ForceEffectType SupportDeflectionEffect, IInfluenceLine** newVal)
{
   CHECK_RETOBJ(newVal);
   CHRException hr;

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateInfluenceCalc(stage);

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);

      LGR_HANDLE_CANCEL_PROGRESS(); 

      // check to see if we've already stored our influence line
      SvInfluenceLineCacheIterator it( m_CachedSupportDeflectionInfluenceLines.find( SvInfluenceLineKeeper(supportID, stageIdx, SupportDeflectionEffect, roGlobal, NULL) ) );

      if (it != m_CachedSupportDeflectionInfluenceLines.end())
      {
         // we've got it in our cache
         return it->InfluenceLine.CopyTo(newVal);
      }
      else
      {
         boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];

         CComObject<CInfluenceLine>* infl_line;
         hr = CComObject<CInfluenceLine>::CreateInstance(&infl_line);
         CComPtr<IInfluenceLine> pinfl(infl_line);

         pFemModel->GetSupportDeflectionInfluenceLine(supportID, SupportDeflectionEffect, infl_line);

         infl_line->SetZeroTolerance(m_DeflectionInfluenceZeroTolerance);

         m_CachedSupportDeflectionInfluenceLines.insert( SvInfluenceLineKeeper(supportID, stageIdx, SupportDeflectionEffect, roGlobal, pinfl) );

         LGR_HANDLE_CANCEL_PROGRESS(); 

         return pinfl.CopyTo(newVal);
      }
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeContraflexureLocations(BSTR stage, IDblArray* *locations)
{
   CHECK_RETVAL(locations);

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateModels();

      LGR_HANDLE_CANCEL_PROGRESS(); 

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);
      boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];

      pFemModel->GetContraflexureLocations(locations);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

	return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeContraflexureResponse(BSTR stage, ForceEffectType effect, IInfluenceLine **results)
{
   CHECK_RETOBJ(results);
   CHRException hr;

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateModels();

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);
      boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];

      LGR_HANDLE_CANCEL_PROGRESS(); 

      // create our results collection 
      CComObject<CInfluenceLine>* response;
      hr = CComObject<CInfluenceLine>::CreateInstance(&response);
      CComPtr<IInfluenceLine> the_results(response); // ref cnt
      pFemModel->GetContraflexureForce(effect, response);

      LGR_HANDLE_CANCEL_PROGRESS(); 

      *results = the_results;
      (*results)->AddRef(); // for client
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

	return S_OK;
}

STDMETHODIMP CLoadGroupResponse::get_IsPOIInContraflexureZone(PoiIDType poiID, BSTR stage, InZoneType* isInZone)
{
   CHECK_RETVAL(isInZone);

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateModels();

      LGR_HANDLE_CANCEL_PROGRESS(); 

      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);
      boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];

      pFemModel->IsPOIInContraflexureZone(poiID, isInZone);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

	return S_OK;
}

///////////////////////////////////////////////////////////////
////// ILiveLoadNegativeMomentRegion
///////////////////////////////////////////////////////////////

STDMETHODIMP CLoadGroupResponse::get_IsPOIInNegativeLiveLoadMomentZone(PoiIDType poiID, BSTR stage, InZoneType* isInZone)
{
   CHECK_RETVAL(isInZone);

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateModels();

      LGR_HANDLE_CANCEL_PROGRESS(); 

      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);

      rfemModel.IsPOIInNegativeLiveLoadMomentZone(poiID, isInZone);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

	return S_OK;
}

STDMETHODIMP CLoadGroupResponse::ComputeNegativeMomentRegions(BSTR stage, IDblArray* *locations)
{
   CHECK_RETVAL(locations);

   try
   {
      LGR_HANDLE_CANCEL_PROGRESS(); 

      ValidateModels();

      LGR_HANDLE_CANCEL_PROGRESS(); 

      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);

      rfemModel.GetNegativeMomentRegions(locations);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

	return S_OK;
}

///////////////////////////////////////////////////////////////
////// IGetFemForLoadGroupResponse
///////////////////////////////////////////////////////////////

STDMETHODIMP CLoadGroupResponse::SaveFem2D(BSTR Stage, IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   try
   {
      // first validate our models
      ValidateModels();

      // get stage sequencing
      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(Stage);

      // get fem model for this stage
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);

      rfemModel.SaveModel(pSave);

   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}


///////////////////////////////////////////////////////////////
////// IAnalysisPOIs
///////////////////////////////////////////////////////////////

STDMETHODIMP CLoadGroupResponse::get_SpanPoiIncrement(PoiIDType *pVal)
{
   *pVal = m_MinSpanPoiIncrement;
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::put_SpanPoiIncrement(PoiIDType newVal)
{
   if (newVal != m_MinSpanPoiIncrement)
   {
      m_MinSpanPoiIncrement = newVal;

      // rebuild all models - lazy way
      m_ChangeManager.OnModelHosed();
   }
   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::get_CantileverPoiIncrement(PoiIDType *pVal)
{
   *pVal = m_MinCantileverPoiIncrement;

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::put_CantileverPoiIncrement(PoiIDType newVal)
{
   if (newVal != m_MinCantileverPoiIncrement)
   {
      m_MinCantileverPoiIncrement = newVal;

      // rebuild all models - lazy way
      m_ChangeManager.OnModelHosed();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::GetSuperstructurePois(BSTR stage, IIDArray* *poiIDs, IDblArray* *poiLocations)
{
   try
   {
      // first validate our models
      ValidateModels();

      // get stage sequencing
      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);

      // get fem model for this stage
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);

      rfemModel.GetSuperstructurePois(poiIDs, poiLocations);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::GetPoiInfo(BSTR stage, PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLocation)
{
   HRESULT hr = S_OK;
   try
   {
      // first validate our models
      ValidateModels();

      // get stage sequencing
      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);

      // get fem model for this stage
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);

      hr = rfemModel.GetPoiInfo(poiID, lbamMemberType, memberID, memberLocation);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return hr;
}

///////////////////////////////////////////////////////////////
////// IGetActiveLoadGroups
///////////////////////////////////////////////////////////////
STDMETHODIMP CLoadGroupResponse::GetActiveLoadGroups(IBstrArray* *pVal)
{
   try
   {
      // first validate our models
      ValidateModels();

      *pVal = m_AnalysisController.GetActiveLoadGroups();
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }
   return S_OK;
}

///////////////////////////////////////////////////////////////
// IGetSegmentCrossSections
///////////////////////////////////////////////////////////////
STDMETHODIMP CLoadGroupResponse::GetSegmentCrossSectionAtPOI(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/ISegmentCrossSection* *leftCs,  /*[out]*/ISegmentCrossSection* *rightCs)
{
   try
   {
      // first validate our models
      ValidateModels();

      // get stage sequencing
      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);

      // get fem model for this stage
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);

      rfemModel.GetSegmentCrossSectionAtPOI(poiID, leftCs, rightCs);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }
   return S_OK;
}

///////////////////////////////////////////////////////////////
// IGetStressPointss
///////////////////////////////////////////////////////////////
STDMETHODIMP CLoadGroupResponse::GetStressPointsAtPOI(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftCs,  /*[out]*/IStressPoints* *rightCs)
{
   try
   {
      // first validate our models
      ValidateModels();

      // get stage sequencing
      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);

      // get fem model for this stage
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);

      rfemModel.GetStressPointsAtPOI(poiID, leftCs, rightCs);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }
   return S_OK;
}
///////////////////////////////////////////////////////////////
////// IGetDistributionFactors
///////////////////////////////////////////////////////////////

// IGetDistributionFactors
HRESULT CLoadGroupResponse::GetPOIDistributionFactor(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, IDistributionFactor* *leftFactor, IDistributionFactor* *rightFactor)
{
   CHECK_RETOBJ(leftFactor);
   CHECK_RETOBJ(rightFactor);

   try
   {
      // first validate our models
      ValidateModels();

      // get stage sequencing
      StageIndexType stageIdx = m_AnalysisController.CheckedStageOrder(stage);

      // get fem model for this stage
      boost::shared_ptr<CAnalysisModel> pFemModel = m_Models[stageIdx];
      pFemModel->GetPOIDistributionFactor(poiID, leftFactor, rightFactor);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

STDMETHODIMP CLoadGroupResponse::GetSupportDistributionFactor(SupportIDType supportID, BSTR Stage, IDistributionFactor **Factor)
{
   CHECK_RETOBJ(Factor);
   try
   {
      // first validate our models
      ValidateModels();

      // get stage sequencing
      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(Stage);

      // get fem model for this stage
      CAnalysisModel& rfemModel = *(m_Models[stg_idx]);
      rfemModel.GetSupportDistributionFactor(supportID, Factor);
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return S_OK;
}

HRESULT CLoadGroupResponse::CacheInfluenceLines(PoiIDType poiID, BSTR stage,ResultsOrientation orientation)
{
   HRESULT hr = S_OK;
   try
   {
      StageIndexType stg_idx = m_AnalysisController.CheckedStageOrder(stage);
      boost::shared_ptr<CAnalysisModel> pAnalysisModel = m_Models[stg_idx];

      CComPtr<IInfluenceLine> ilFx[2], ilFy[2], ilMz[2], ilDx[2], ilDy[2], ilRz[2];

      pAnalysisModel->GetInfluenceLines(poiID, 
                                        orientation, m_ForceInfluenceZeroTolerance, m_DeflectionInfluenceZeroTolerance, 
                                        &ilFx[0], &ilFx[1],
                                        &ilFy[0], &ilFy[1],
                                        &ilMz[0], &ilMz[1],
                                        &ilDx[0], &ilDx[1],
                                        &ilDy[0], &ilDy[1],
                                        &ilRz[0], &ilRz[1]);

      // cache it and return it
      m_CachedForceInfluenceLines.insert( DvInfluenceLineKeeper(poiID, stg_idx, fetFx, orientation, ilFx[0], ilFx[1]) );
      m_CachedForceInfluenceLines.insert( DvInfluenceLineKeeper(poiID, stg_idx, fetFy, orientation, ilFy[0], ilFy[1]) );
      m_CachedForceInfluenceLines.insert( DvInfluenceLineKeeper(poiID, stg_idx, fetMz, orientation, ilMz[0], ilMz[1]) );

      m_CachedDeflectionInfluenceLines.insert( DvInfluenceLineKeeper(poiID, stg_idx, fetDx, roGlobal, ilDx[0], ilDx[1]) );
      m_CachedDeflectionInfluenceLines.insert( DvInfluenceLineKeeper(poiID, stg_idx, fetDy, roGlobal, ilDy[0], ilDy[1]) );
      m_CachedDeflectionInfluenceLines.insert( DvInfluenceLineKeeper(poiID, stg_idx, fetRz, roGlobal, ilRz[0], ilRz[1]) );
   }
   catch(...)
   {
      return DealWithMyExceptions();
   }

   return hr;
}
