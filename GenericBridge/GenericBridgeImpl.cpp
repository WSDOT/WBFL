///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// GenericBridgeImpl.cpp : Implementation of CGenericBridge
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "GenericBridgeImpl.h"
#include "PierCollection.h"
#include "Pier.h"
#include "SuperstructureMember.h"
#include <MathEx.h>

#include "FilteredSuperstructureMemberCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericBridge
HRESULT CGenericBridge::FinalConstruct()
{
   CComObject<CPierCollection>* pPiers;
   CComObject<CPierCollection>::CreateInstance(&pPiers);
   m_Piers = pPiers;

   HRESULT hr = m_BridgeGeometry.CoCreateInstance(CLSID_BridgeGeometry);
   ATLASSERT(SUCCEEDED(hr));

   return S_OK;
}

void CGenericBridge::FinalRelease()
{
   m_BridgeGeometry.Release();
   m_Piers.Release();
}

STDMETHODIMP CGenericBridge::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGenericBridge,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CPierCollection* CGenericBridge::GetPierCollection()
{
   return dynamic_cast<CPierCollection*>(m_Piers.p);
}

/////////////////////////////////////////////////////
// IGenericBridge implementation
STDMETHODIMP CGenericBridge::UpdateBridgeModel()
{
   DoUpdateBridgeModel();
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_BridgeGeometry(IBridgeGeometry** bridgeGeometry)
{
   CHECK_RETOBJ(bridgeGeometry);
   return m_BridgeGeometry.CopyTo(bridgeGeometry);
}

STDMETHODIMP CGenericBridge::get_Alignment(IAlignment** ppAlignment)
{
   return m_BridgeGeometry->get_BridgeAlignment(ppAlignment);
}

STDMETHODIMP CGenericBridge::get_Deck(IBridgeDeck** deck)
{
   CHECK_RETOBJ(deck);
   (*deck) = m_Deck;

   if ( *deck ) 
      (*deck)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::putref_Deck(IBridgeDeck* deck)
{
   m_Deck = deck;
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_Piers(IPierCollection* *piers)
{
   CHECK_RETOBJ(piers);

   (*piers) = m_Piers;
   (*piers)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_Length(Float64* length)
{
   CHECK_RETVAL(length);
   PierIndexType nPiers;
   m_Piers->get_Count(&nPiers);
   CComPtr<IPier> objFirstPier, objLastPier;

   m_Piers->get_Item(0,&objFirstPier);
   m_Piers->get_Item(nPiers-1,&objLastPier);

   CComPtr<IStation> objFirstPierStation, objLastPierStation;
   objFirstPier->get_Station(&objFirstPierStation);
   objLastPier->get_Station(&objLastPierStation);

   Float64 first_pier_station, last_pier_station;
   objFirstPierStation->get_Value(&first_pier_station);
   objLastPierStation->get_Value(&last_pier_station);

   (*length) = last_pier_station - first_pier_station;

   ATLASSERT( 0 <= *length );

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_SpanLength(SpanIndexType spanIdx,Float64* length)
{
   CHECK_RETVAL(length);
   PierIndexType startPierIdx = (PierIndexType)spanIdx;
   PierIndexType endPierIdx = startPierIdx + 1;

   CComPtr<IPier> startPier, endPier;
   HRESULT hr = m_Piers->get_Item(startPierIdx,&startPier);
   if ( FAILED(hr) )
      return hr;

   hr = m_Piers->get_Item(endPierIdx,&endPier);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IStation> objStartStation,objEndStation;
   startPier->get_Station(&objStartStation);
   endPier->get_Station(&objEndStation);

   Float64 startStation, endStation;
   objStartStation->get_Value(&startStation);
   objEndStation->get_Value(&endStation);

   *length = endStation - startStation;

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_LeftBarrier(ISidewalkBarrier** barrier)

{
   CHECK_RETOBJ(barrier);
   (*barrier) = m_LeftBarrier;

   if ( *barrier ) 
      (*barrier)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::putref_LeftBarrier(ISidewalkBarrier* barrier)
{
   CHECK_IN(barrier);
   if ( (m_LeftBarrier == NULL && barrier == NULL) || m_LeftBarrier.IsEqualObject(barrier) )
      return S_OK;

   m_LeftBarrier = barrier;
   return S_OK;
}

STDMETHODIMP CGenericBridge::get_RightBarrier(ISidewalkBarrier** barrier)
{
   CHECK_RETOBJ(barrier);
   (*barrier) = m_RightBarrier;

   if ( *barrier ) 
      (*barrier)->AddRef();

   return S_OK;
}

STDMETHODIMP CGenericBridge::putref_RightBarrier(ISidewalkBarrier* barrier)
{
   CHECK_IN(barrier);
   if ( (m_RightBarrier == NULL && barrier == NULL) || m_RightBarrier.IsEqualObject(barrier) )
      return S_OK;

   m_RightBarrier = barrier;
   return S_OK;
}

STDMETHODIMP CGenericBridge::CreateSuperstructureMember(GirderIDType id,LocationType locationType,ISuperstructureMember** ppMbr)
{
   CHECK_RETOBJ(ppMbr);

   CComObject<CSuperstructureMember>* pMbr;
   CComObject<CSuperstructureMember>::CreateInstance(&pMbr);
   pMbr->Init(id,locationType,this);

   CComPtr<ISuperstructureMember> mbr = pMbr;
   m_SuperstructureMembers.insert( std::make_pair(id,mbr) );

   mbr.CopyTo(ppMbr);

   return S_OK;
}

STDMETHODIMP CGenericBridge::get_SuperstructureMember(GirderIDType id,ISuperstructureMember** ppMbr)
{
   std::map<GirderIDType,CAdapt<CComPtr<ISuperstructureMember>>>::iterator found(m_SuperstructureMembers.find(id));
   if ( found == m_SuperstructureMembers.end() )
   {
      (*ppMbr) = NULL;
      return E_FAIL;
   }
   else
   {
      return found->second.m_T.CopyTo(ppMbr);
   }
}

STDMETHODIMP CGenericBridge::get__EnumSuperstructureMembers(IEnumSuperstructureMembers* *enumSSMbrs)
{
   typedef _CopyInterfacePair<ISuperstructureMember,std::pair<const GirderIDType,CAdapt<CComPtr<ISuperstructureMember>>>> _CopyType;

   CComObject<CComEnumOnSTL<IEnumSuperstructureMembers,&IID_IEnumSuperstructureMembers,ISuperstructureMember*,_CopyType,std::map<GirderIDType,CAdapt<CComPtr<ISuperstructureMember>>>>>* pEnum = NULL;
   HRESULT hr = CComObject<CComEnumOnSTL<IEnumSuperstructureMembers,&IID_IEnumSuperstructureMembers,ISuperstructureMember*,_CopyType,std::map<GirderIDType,CAdapt<CComPtr<ISuperstructureMember>>>>>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init(NULL,m_SuperstructureMembers);
   if ( SUCCEEDED(hr) )
      hr = pEnum->QueryInterface(enumSSMbrs);

   if ( FAILED(hr) )
      delete pEnum;

   return hr;
}

STDMETHODIMP CGenericBridge::get_SuperstructureMembersAtStation(Float64 station,IFilteredSuperstructureMemberCollection** ppMbrs)
{
   CComObject<CFilteredSuperstructureMemberCollection>* pCollection;
   CComObject<CFilteredSuperstructureMemberCollection>::CreateInstance(&pCollection);

   (*ppMbrs) = pCollection;
   (*ppMbrs)->AddRef();

   PierIndexType nPiers;
   m_Piers->get_Count(&nPiers);
   CComPtr<IPier> firstPier, lastPier;
   m_Piers->get_Item(0,&firstPier);
   m_Piers->get_Item(nPiers-1,&lastPier);

   CComPtr<IStation> startBridgeStation, endBridgeStation;
   firstPier->get_Station(&startBridgeStation);
   lastPier->get_Station(&endBridgeStation);

   Float64 startBridgeStationValue, endBridgeStationValue;
   startBridgeStation->get_Value(&startBridgeStationValue);
   endBridgeStation->get_Value(&endBridgeStationValue);

   CComPtr<IEnumSuperstructureMembers> enumMbrs;
   get__EnumSuperstructureMembers(&enumMbrs);

   CComPtr<ISuperstructureMember> mbr;
   while ( enumMbrs->Next(1,&mbr,NULL) != S_FALSE )
   {
      CollectionIndexType nSegments;
      mbr->get_SegmentCount(&nSegments);

      CComPtr<ISegment> firstSegment, lastSegment;
      mbr->get_Segment(0,&firstSegment);
      mbr->get_Segment(nSegments-1,&lastSegment);

      CComPtr<IGirderLine> firstGirderLine, lastGirderLine;
      firstSegment->get_GirderLine(&firstGirderLine);
      lastSegment->get_GirderLine(&lastGirderLine);

      CComPtr<IPierLine> firstPierLine, lastPierLine;
      firstGirderLine->get_StartPier(&firstPierLine);
      lastGirderLine->get_EndPier(&lastPierLine);

      CComPtr<IStation> firstStation, lastStation;
      firstPierLine->get_Station(&firstStation);
      lastPierLine->get_Station(&lastStation);

      Float64 firstStationValue, lastStationValue;
      firstStation->get_Value(&firstStationValue);
      lastStation->get_Value(&lastStationValue);

      if ( ::IsEqual(station,startBridgeStationValue) || ::IsEqual(station,endBridgeStationValue) )
      {
         if ( ::InRange(firstStationValue,station,lastStationValue) )
         {
            pCollection->Add(mbr);
         }
      }
      else
      {
         if ( ::IsGE(firstStationValue,station) && station < lastStationValue )
         {
            pCollection->Add(mbr);
         }
      }

      mbr.Release();
   }

   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CGenericBridge::Load(IStructuredLoad2* load)
{
//   // Turn off connection points
//   UnadviseSuperstructureMembers();
//   UnadviseChild(m_Stages,IID_IStageCollectionEvents,m_dwStagesCookie);
//   UnadviseChild(m_Piers,IID_IPierCollectionEvents,m_dwPiersCookie);
//   UnadviseChild(m_Spans,IID_ISpanCollectionEvents,m_dwSpansCookie);
//
//   // Empty containers...
//   dynamic_cast<CPierCollection*>(m_Piers.p)->Clear();
//   dynamic_cast<CSpanCollection*>(m_Spans.p)->Clear();
//   dynamic_cast<CStageCollection*>(m_Stages.p)->Clear();
//
//   // Load the model
//   CComVariant var;
//   
//   CHECK_IN(load);
//   load->BeginUnit(CComBSTR("GenericBridge"));
//
//   load->get_Property(CComBSTR("GirderLineType"),&var);
//   m_GirderLineType = (GirderLineType)(var.lVal);
//
//   CComPtr<IStructuredStorage2> ss;
//
//   ss.Release();
//   m_Stages->QueryInterface(&ss);
//   ss->Load(load);
//
//   ss.Release();
//   m_Piers->QueryInterface(&ss);
//   ss->Load(load);
//
//   ss.Release();
//   m_Spans->QueryInterface(&ss);
//   ss->Load(load);
//
//   LinkSpansAndPiers();
//
//   ss.Release();
//   m_GirderSpacing->QueryInterface(&ss);
//   ss->Load(load);
//
//   VARIANT_BOOL bEnd;
//   load->EndUnit(&bEnd);
//
//   DoUpdateBridgeModel(); // Generate the COGO model
//
//   // Turn on connection points
//   AdviseSuperstructureMembers();
//   AdviseChild(m_Stages,IID_IStageCollectionEvents,&m_dwStagesCookie);
//   AdviseChild(m_Piers,IID_IPierCollectionEvents,&m_dwPiersCookie);
//   AdviseChild(m_Spans,IID_ISpanCollectionEvents,&m_dwSpansCookie);
//
   return S_OK;
}

STDMETHODIMP CGenericBridge::Save(IStructuredSave2* save)
{
   CHECK_IN(save);
//
//   save->BeginUnit(CComBSTR("GenericBridge"),1.0);
//
//   save->put_Property(CComBSTR("GirderLineType"),CComVariant(m_GirderLineType));
//
//   CComPtr<IStructuredStorage2> ss;
//
//   ss.Release();
//   m_Stages->QueryInterface(&ss);
//   ss->Save(save);
//
//   ss.Release();
//   m_Piers->QueryInterface(&ss);
//   ss->Save(save);
//
//   ss.Release();
//   m_Spans->QueryInterface(&ss);
//   ss->Save(save);
//
//   ss.Release();
//   m_GirderSpacing->QueryInterface(&ss);
//   ss->Save(save);
//
//   save->EndUnit();
//
   return S_OK;
}


//#if defined _DEBUG
//void CGenericBridge::Dump(CDumpContext& dc)
//{
//   dc << "Dump Bridge Data\n";
//   dc << "================\n";
//
//   dc << "Dump by span\n";
//   long nSpans;
//   m_Spans->get_Count(&nSpans);
//   for ( long i = 0; i < nSpans; i++ )
//   {
//      CComPtr<ISpan> span;
//      m_Spans->get_Item(i,&span);
//
//      CSpan* pSpan = dynamic_cast<CSpan*>(span.p);
//
//
//      CPier* pPrevPier = pSpan->GetPrevPier();
//      CPier* pNextPier = pSpan->GetNextPier();
//
//      CSpan* pPrevSpan = pNextPier->GetPrevSpan();
//      CSpan* pNextSpan = pPrevPier->GetNextSpan();
//
//      dc << "Prev Pier " << (void*)pPrevPier << " (Next Span " << (void*)pNextSpan << ")\n";
//      dc << "Span " << (i+1) << "                        " << (void*)pSpan << "\n";
//      dc << "Next Pier " << (void*)pNextPier << " (Prev Span " << (void*)pPrevSpan << ")\n";
//   }
//
//   dc << "Dump by pier\n";
//   long nPiers;
//   m_Piers->get_Count(&nPiers);
//   for ( i = 0; i < nPiers; i++ )
//   {
//      CComPtr<IPier> pier;
//      m_Piers->get_Item(i,&pier);
//      CPier* pPier = dynamic_cast<CPier*>(pier.p);
//
//      CSpan* pPrevSpan = pPier->GetPrevSpan();
//      CSpan* pNextSpan = pPier->GetNextSpan();
//
//      CPier* pPrevPier = (pNextSpan ? pNextSpan->GetPrevPier() : NULL);
//      CPier* pNextPier = (pPrevSpan ? pPrevSpan->GetNextPier() : NULL);
//
//      dc << "Prev Span " << (void*)pPrevSpan << " (Next Pier " << (void*)pNextPier << ")\n";
//      dc << "Pier " << (i+1) << "                        " << (void*)pPier << "\n";
//      dc << "Next Span " << (void*)pNextSpan << " (Prev Pier " << (void*)pPrevPier << ")\n";
//   }
//
//   dc << "\n";
//   dc << "Dump of Girder Spacing Data\n";
//   dc << "===========================\n";
//   GetGirderSpacing()->Dump(dc);
//}
//#endif // _DEBUG

void CGenericBridge::DoUpdateBridgeModel()
{
   m_BridgeGeometry->UpdateGeometry();

   ////////////////////////////////
   // Create Pier Objects
   ////////////////////////////////
   CPierCollection* pPiers = GetPierCollection();
   pPiers->Clear();

   PierIndexType nPiers;
   m_BridgeGeometry->get_PierLineCount(&nPiers);
   for ( PierIndexType pierIdx = 0; pierIdx < nPiers; pierIdx++ )
   {
      CComPtr<IPierLine> pierLine;
      m_BridgeGeometry->GetPierLine(pierIdx,&pierLine);

      CComObject<CPier>* pPier;
      CComObject<CPier>::CreateInstance(&pPier);

      pPier->Init(this,pierLine);

      CComPtr<IPier> pier;
      pier = pPier;
      pPiers->Add(pier);
   }
}
