///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bamBridgeModel           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\BridgeModel.h>
#include <BridgeAnalysis\DeadLoadCase.h>

#include <BridgeAnalysis\BruteForceSolver.h>
#include <BridgeAnalysis\SimpleResultsManager.h>

#include <iomanip>
#include <algorithm>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bamBridgeModel::bamBridgeModel()
{
   m_IsModified = true;
   m_IsAnalyzed = false;

   SetGravityDirection(NegativeY);
   SetGravitionalAcceleration(1.0);

   m_pAnalysisResultsManager = std::auto_ptr<bamAnalysisResultsManager>(new bamSimpleResultsManager);
   m_bShouldDeleteAnalysisResultsManager = true;

   m_pSolver = std::auto_ptr<bamLiveLoadSolver>(new bamBruteForceSolver);
   m_pSolver->SetBridgeModel(this);
   m_bShouldDeleteLiveLoadSolver = true;
} // bamBridgeModel

bamBridgeModel::~bamBridgeModel()
{
   if ( !m_bShouldDeleteAnalysisResultsManager )
      m_pAnalysisResultsManager.release();

   if ( !m_bShouldDeleteLiveLoadSolver )
      m_pSolver.release();
} // ~bamBridgeModel

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bamBridgeModel* bamBridgeModel::Clone() const
{
   bamBridgeModel* pModel = DoClone();
   DeepCopy(pModel);
   return pModel;
}

void bamBridgeModel::SetAnalysisResultsManager(bamAnalysisResultsManager* pAnalysisResultsManager, bool bShouldDelete)
{
   if ( !m_bShouldDeleteAnalysisResultsManager )
      m_pAnalysisResultsManager.release();

   m_pAnalysisResultsManager = std::auto_ptr<bamAnalysisResultsManager>(pAnalysisResultsManager);
   m_bShouldDeleteAnalysisResultsManager = bShouldDelete;
}

bamAnalysisResultsManager* bamBridgeModel::GetAnalysisResultsManager()
{
   return m_pAnalysisResultsManager.get();
}

void bamBridgeModel::SetLiveLoadSolver(bamLiveLoadSolver* pSolver, bool bShouldDelete)
{
   if ( !m_bShouldDeleteLiveLoadSolver )
      m_pSolver.release();

   m_pSolver = std::auto_ptr<bamLiveLoadSolver>(pSolver);
   m_pSolver->SetBridgeModel(this);
   m_bShouldDeleteLiveLoadSolver = bShouldDelete;
}

bamLiveLoadSolver* bamBridgeModel::GetLiveLoadSolver()
{
   return m_pSolver.get();
}

void bamBridgeModel::Analyze(bool bForce)
{
   // Check if the model has previously been analyzed, and that
   // it has not been modified since it was analyzed. If so,
   // get the heck outta here. There is nothing to do. (Unless
   // of course the caller wants to force the analysis to happen)
   if ( !bForce && !IsModified() && IsAnalyzed() )
      return;
   
   DoSetup();
   DoBuildModel();

   LoadCaseIterator loadcase_begin = m_LoadCases.begin();
   LoadCaseIterator loadcase_end   = m_LoadCases.end();
   while ( loadcase_begin != loadcase_end )
   {
      boost::shared_ptr<bamLoadCase>& loadCase = (*loadcase_begin++).second;

      if (loadCase->IsEnabled())
      {
         DoBeginLoadCase(*loadCase);
         loadCase->Apply();
         DoAnalyze();

         // While the load case is still applied to the structure,
         // coenvect the internal element forces.
         CollectLoadCaseResults(*loadCase);

         DoEndLoadCase();
         loadCase->Remove();
      }
   }

   LiveLoadIterator liveload_begin = m_LiveLoads.begin();
   LiveLoadIterator liveload_end   = m_LiveLoads.end();
   while ( liveload_begin != liveload_end )
   {
      bamLiveLoad& env = (*liveload_begin++).second;

      CHECK( m_pSolver.get() != 0 );

      m_pSolver->Solve(env);
   }

   EnvelopeIterator envelope_begin = m_Envelopes.begin();
   EnvelopeIterator envelope_end   = m_Envelopes.end();
   while ( envelope_begin != envelope_end )
   {
      boost::shared_ptr<bamEnvelope>& penvelope = (*envelope_begin++).second;
      penvelope->DoEnvelope();
   }

   LoadCombinationIterator loadcombo_begin = m_LoadCombinations.begin();
   LoadCombinationIterator loadcombo_end   = m_LoadCombinations.end();
   while ( loadcombo_begin != loadcombo_end )
   {
      boost::shared_ptr<bamLoadCombination>& pLoadCombination = (*loadcombo_begin++).second;
      DoLoadCombination( *pLoadCombination );
   }

   DoCleanup();

   SetModifiedFlag(false);
   SetAnalyzedFlag(true);
} // Analyze

void bamBridgeModel::CreateSpanElement(const bamSpanElementInfo& rSpanElementInfo)
{
   PRECONDITION( rSpanElementInfo.m_SegmentCount == 1 ); // we only support 1 segment at this time
   PRECONDITION( rSpanElementInfo.m_pSegmentInfo != 0 ); // there must be some segment info.

   CreateSpanElement(rSpanElementInfo.m_Id,
                     rSpanElementInfo.m_pSegmentInfo[0].m_Ax,
                     rSpanElementInfo.m_pSegmentInfo[0].m_Iz,
                     rSpanElementInfo.m_pSegmentInfo[0].m_ModE,
                     rSpanElementInfo.m_pSegmentInfo[0].m_Density);
   ConnectSpanElement(rSpanElementInfo.m_Id,
                      rSpanElementInfo.m_StartSupportId,
                      rSpanElementInfo.m_EndSupportId);
}

void bamBridgeModel::CreateSpanElement(Int32 spanElementId,Float64 area,Float64 izz,Float64 e,Float64 density)
{
   bamSpanElement* pSpanElement = new bamSpanElement(spanElementId,area,izz,e,density);
   pSpanElement->SetModel(this);
   StoreSpanElement(pSpanElement);

   SetModifiedFlag();
} // CreateSpanElement

void bamBridgeModel::ConnectSpanElement(Int32 spanElementId,Int32 startPierId,Int32 endPierId)
{
   bamSpanElement*    pSpanElement  = GetSpanElement( spanElementId );
   bamSupportElement* pStartSupport = GetSupportElement( startPierId );
   bamSupportElement* pEndSupport   = GetSupportElement( endPierId );

   pSpanElement->SetStartSupport( pStartSupport );
   pSpanElement->SetEndSupport( pEndSupport );

   SetModifiedFlag();
} // ConnectSpanElement

void bamBridgeModel::RemoveSpanElement(Int32 spanElementId)
{
   bamSpanElement* pSpanElement = GetSpanElement(spanElementId);
   pSpanElement->OnRemove();
   m_SpanElements.erase(spanElementId);

   SetModifiedFlag();
} // RemoveSpanElement

Int32 bamBridgeModel::GetSpanElementCount() const
{
   return m_SpanElements.size();
} // GetSpanElementCount

void bamBridgeModel::EnumSpanElements(Int32** ppSpanElementId,Int32 count) const
{
   ConstSpanElementIterator begin = m_SpanElements.begin();
   ConstSpanElementIterator end   = m_SpanElements.end();
   Int32 i = 0;

   while( begin != end && (count == 0 || i < count) )
   {
      const boost::shared_ptr<bamSpanElement>& pSpanElement = (*begin++).second;
      (*ppSpanElementId)[i++] = pSpanElement->GetID();
   }
}

void bamBridgeModel::GetSpanElementInfo(bamSpanElementInfo& rSpanElementInfo) const
{
   Int32 num_segments;

   const bamSpanElement* pSpanElement = GetSpanElement( rSpanElementInfo.m_Id );

   CHECK( rSpanElementInfo.m_SegmentCount > 0 ); // this is the number of segments requested
   CHECK( rSpanElementInfo.m_pSegmentInfo != 0); // there must be a place to put the info

   CHECK( rSpanElementInfo.m_SegmentCount == 1); // We only support one segment currently

   num_segments = rSpanElementInfo.m_SegmentCount; // Number of requested segments

   if ( num_segments == 0 )
   {
      // No segments were requested. Return the number of segments
      // in this span element.
      rSpanElementInfo.m_SegmentCount = 1; // Number of actual segments
   }
   else
   {
      // For each segment, fienv out m_pSegmentInfo.
      // There is only one segment in the current implementation
      rSpanElementInfo.m_SegmentCount = 1;
      rSpanElementInfo.m_pSegmentInfo[0].m_Ax = pSpanElement->GetAx();
      rSpanElementInfo.m_pSegmentInfo[0].m_Iz = pSpanElement->GetIz();
      rSpanElementInfo.m_pSegmentInfo[0].m_ModE = pSpanElement->GetModE();
      rSpanElementInfo.m_pSegmentInfo[0].m_Density = pSpanElement->GetDensity();
   }


   bamSupportElement* pSupportElement;
   
   pSupportElement = pSpanElement->GetStartSupport();
   rSpanElementInfo.m_StartSupportId = (pSupportElement) ? pSupportElement->GetID() : -1;

   pSupportElement = pSpanElement->GetEndSupport();
   rSpanElementInfo.m_EndSupportId = (pSupportElement) ? pSupportElement->GetID() : -1;
}

void bamBridgeModel::CreateSupportElement(Int32 supportElementId,
                                                   Float64 location,
                                                   bamSupportFixity fixity)
{
   bamSupportElement* pSupportElement = new bamSupportElement(supportElementId,location,fixity);
   pSupportElement->SetModel(this);
   StoreSupportElement(pSupportElement);

   SetModifiedFlag();
} // CreateSupportElement

void bamBridgeModel::CreateSupportElement(const bamSupportElementInfo& rSupportElementInfo)
{
   bamSupportElement* pSupportElement = new bamSupportElement(rSupportElementInfo);
   pSupportElement->SetModel(this);
   StoreSupportElement(pSupportElement);

   SetModifiedFlag();
}

void bamBridgeModel::RemoveSupportElement(Int32 supportElementId)
{
   bamSupportElement* pSupportElement = GetSupportElement(supportElementId);
   pSupportElement->OnRemove();
   m_SupportElements.erase(supportElementId);

   SetModifiedFlag();
} // RemoveSupportElement

void bamBridgeModel::EnumSupportElements(Int32** ppSupportElementId,Int32 count) const
{
   ConstSupportElementIterator begin = m_SupportElements.begin();
   ConstSupportElementIterator end   = m_SupportElements.end();
   Int32 i = 0;

   while( begin != end && (count == 0 || i < count) )
   {
      const boost::shared_ptr<bamSupportElement>& pSupportElement = (*begin++).second;
      (*ppSupportElementId)[i++] = pSupportElement->GetID();
   }
}

void bamBridgeModel::CreateLoadCase(Int32 lcid)
{
   bamLoadCase* pLoadCase = new bamLoadCase(lcid);
   pLoadCase->SetBridgeModel(this);
   StoreLoadCase(pLoadCase);

   SetModifiedFlag();
} // CreateLoadCase

void bamBridgeModel::CreateDeadLoadCase( Int32 lcid, 
                                         bamElementExcludeInfo* pExcludeList,
                                         Int32 excludeCount )
{
   // Create the new load
   bamDeadLoadCase* pLoadCase = new bamDeadLoadCase(lcid);

   // Setup associations
   pLoadCase->SetBridgeModel(this);

   // Process exclusion list
   for (Int32 idx = 0; idx < excludeCount; idx++)
   {
      switch( pExcludeList[idx].m_ElementType )
      {
      case etSpan:
           pLoadCase->ExcludeSpan( pExcludeList[idx].m_ElementId );
           break;

      case etSupport:
           pLoadCase->ExcludeSupport( pExcludeList[idx].m_ElementId );
           break;
      }
   }

   StoreLoadCase(pLoadCase);
   SetModifiedFlag();
} // CreateDeadLoadCase

void bamBridgeModel::RemoveLoadCase(Int32 loadCaseId)
{
   bamLoadCase* pLoadCase = GetLoadCase( loadCaseId );
   m_LoadCases.erase( loadCaseId );

   SetModifiedFlag();
} // RemoveLoadCase

Int32 bamBridgeModel::AddLoad(Int32 loadCaseId,bamLoad* pLoad)
{
   bamLoadCase* pLoadCase = GetLoadCase(loadCaseId);

   SetModifiedFlag();

   return pLoadCase->AddLoad(pLoad);
} // AddLoad

void bamBridgeModel::RemoveLoad(Int32 loadCaseId, Int32 loadIdx)
{
   bamLoadCase* pLoadCase = GetLoadCase(loadCaseId);
   pLoadCase->RemoveLoad(loadIdx);

   SetModifiedFlag();
}

Int32 bamBridgeModel::GetLoadCaseCount() const
{
   return m_LoadCases.size();
}

void bamBridgeModel::EnumLoadCases(Int32** ppLoadCaseId,Int32 count) const
{
   ConstLoadCaseIterator begin = m_LoadCases.begin();
   ConstLoadCaseIterator end   = m_LoadCases.end();
   Int32 i = 0;

   while( begin != end && (count == 0 || i < count) )
   {
      const boost::shared_ptr<bamLoadCase>& pLoadCase = (*begin++).second;
      (*ppLoadCaseId)[i++] = pLoadCase->GetID();
   }
}

Int32 bamBridgeModel::GetLoadCount(Int32 loadCaseId) const
{
   const bamLoadCase* pLoadCase = GetLoadCase(loadCaseId);
   return pLoadCase->GetLoadCount();
}

void bamBridgeModel::EnableLoadCase(Int32 loadCaseId)
{
   bamLoadCase* pLoadCase = GetLoadCase( loadCaseId );
   pLoadCase->Enable();
}

void bamBridgeModel::DisableLoadCase(Int32 loadCaseId)
{
   bamLoadCase* pLoadCase = GetLoadCase( loadCaseId );
   pLoadCase->Disable();
}

bool bamBridgeModel::IsLoadCaseEnabled(Int32 loadCaseId) const
{
   const bamLoadCase* pLoadCase = GetLoadCase( loadCaseId );
   return pLoadCase->IsEnabled();
}

void bamBridgeModel::AddLoadCombination(const bamLoadCombination& rLoadCombination)
{
   bamLoadCombination* pClone = rLoadCombination.Clone();
   pClone->SetBridgeModel(this);
   StoreLoadCombination( pClone );

   // If we are adding a load combination after the model has been
   // analyzed (and if the model hasn't been modified) then aenv of
   // the results are correct and there is no reason why this new
   // combination can't be performed. So do it!!!
   if ( !IsModified() && IsAnalyzed() )
      DoLoadCombination( *pClone );
}

void bamBridgeModel::RemoveLoadCombination(Int32 id)
{
   bamLoadCombination* pLoadCombination = GetLoadCombination( id );
   m_LoadCombinations.erase( id );
}

const bamLoadCombination* bamBridgeModel::GetLoadCombination(Int32 id) const
{
   PRECONDITION( IsValidLoadCombinationId(id) );

   const bamLoadCombination* pLoadCombination;

   ConstLoadCombinationIterator iter = m_LoadCombinations.find(id);
   if ( iter == m_LoadCombinations.end() )
      pLoadCombination = 0;
   else 
      pLoadCombination = (*iter).second.get();

   return pLoadCombination;
}

void bamBridgeModel::AddEnvelope(const bamEnvelope& rEnvelope)
{
   boost::shared_ptr<bamEnvelope> pEnvelope( rEnvelope.CreateClone() );

   m_Envelopes.insert(std::make_pair(pEnvelope->GetID(),pEnvelope));

   pEnvelope->SetBridgeModel(this);

   // If we are adding an envelope after the model has been
   // analyzed (and if the model hasn't been modified) then aenv of
   // the results are correct and there is no reason why this new
   // envelope can't be created. So do it!!!
   if ( !IsModified() && IsAnalyzed() )
      pEnvelope->DoEnvelope();
}

void bamBridgeModel::RemoveEnvelope(Int32 id)
{
   m_Envelopes.erase( id );
}

const bamEnvelope* bamBridgeModel::GetEnvelope(Int32 id) const
{
   ConstEnvelopeIterator found = m_Envelopes.find(id);
   WARN( found == m_Envelopes.end(), "Envelope not found" );
   if ( found == m_Envelopes.end() )
      return 0;

   return (*found).second.get();
}

void bamBridgeModel::AddLiveLoad(const bamLiveLoad& ll)
{
   StoreLiveLoad( ll );
}

void bamBridgeModel::RemoveLiveLoad(Int32 id)
{
   m_LiveLoads.erase(id);
}

const bamLiveLoad* bamBridgeModel::GetLiveLoad(Int32 id) const
{
   ConstLiveLoadIterator found = m_LiveLoads.find( id );
   WARN( found == m_LiveLoads.end(), "Live Load Not Found" );
   if ( found == m_LiveLoads.end() )
      return 0;

   return &(*found).second;
}

Int32 bamBridgeModel::GetLoadingCount() const
{
   Int32 count;

   count = m_LoadCases.size();
   count += m_LoadCombinations.size();

   // :TODO: rab 02.03.97: Update if LiveLoad implementation is changed
   // :METHOD: bamBridgeModel::GetLoadingCount()
   //
   // If LiveLoad is changed to have optional result loadings,
   // change this to get the actual count
   count += m_LiveLoads.size() * 12;

   return count;
}

void bamBridgeModel::EnumLoadings(Int32** ppLoadingId,Int32 count) const
{
   Int32 i = 0;
   ConstLoadCaseIterator loadcase_begin = m_LoadCases.begin();
   ConstLoadCaseIterator loadcase_end   = m_LoadCases.end();

   while ( loadcase_begin != loadcase_end && ( count == 0 || i < count ) )
   {
      const boost::shared_ptr<bamLoadCase>& pLoadCase = (*loadcase_begin++).second;
      (*ppLoadingId)[i++] = pLoadCase->GetID();
   }

   ConstLoadCombinationIterator loadcombo_begin = m_LoadCombinations.begin();
   ConstLoadCombinationIterator loadcombo_end   = m_LoadCombinations.end();
   while ( loadcombo_begin != loadcombo_end && ( count == 0 || i < count ) )
   {
      const boost::shared_ptr<bamLoadCombination>& pLoadCombination = (*loadcombo_begin++).second;
      (*ppLoadingId)[i++] = pLoadCombination->GetID();
   }

   ConstLiveLoadIterator liveload_begin = m_LiveLoads.begin();
   ConstLiveLoadIterator liveload_end   = m_LiveLoads.end();
   while ( liveload_begin != liveload_end && ( count == 0 || i < count ) )
   {
      const bamLiveLoad& env = (*liveload_begin++).second;
      Int32 loadingId;
      loadingId = env.GetMinLoadingId();
      (*ppLoadingId)[i++] = loadingId;
      loadingId = env.GetMaxLoadingId();
      (*ppLoadingId)[i++] = loadingId;
   }

   ConstEnvelopeIterator env_begin = m_Envelopes.begin();
   ConstEnvelopeIterator env_end   = m_Envelopes.end();
   while ( env_begin != env_end && ( count == 0 || i < count ) )
   {
      const boost::shared_ptr<bamEnvelope>& penv = (*env_begin++).second;
      Int32 loadingId;
      loadingId = penv->GetLoadingId( bamEnvelope::Min );
      (*ppLoadingId)[i++] = loadingId;
      loadingId = penv->GetLoadingId( bamEnvelope::Max );
      (*ppLoadingId)[i++] = loadingId;
   }
}

void bamBridgeModel::AddPointOfInterest(Int32 poiId,Float64 absLoc)
{
   Int32 spanId;
   Float64 distFromStart;

   AbsLocationToRelLocation( absLoc, spanId, distFromStart );
   AddPointOfInterest( poiId, spanId, distFromStart, absLoc );
}

void bamBridgeModel::AddPointOfInterest(Int32 poiId,Int32 spanId,Float64 distFromStart)
{
   Float64 absLoc;

   RelLocationToAbsLocation( spanId, distFromStart, absLoc );
   AddPointOfInterest( poiId, spanId, distFromStart, absLoc );
}

void bamBridgeModel::GeneratePointsOfInterest(Int32 startPoi,Int32 nPoi,Int32 spanId,Int32 poiInc)
{
   bamSpanElement* spanElement = GetSpanElement(spanId);
   Float64 span_length = spanElement->Length();
   Float64 offset = 0;
   Float64 delta = span_length / (nPoi - 1);

   for (Int32 i = 0; i < nPoi; i++)
   {
      AddPointOfInterest(startPoi,
                         spanId,
                         offset);

      offset += delta;
      startPoi += poiInc;
   }

   SetModifiedFlag();
}


Int32 bamBridgeModel::GetPointOfInterestCount() const
{
   return m_PointsOfInterest.size();
}

void bamBridgeModel::EnumPointsOfInterest(Int32** ppPoi,Int32 count) const
{
   ConstPoiIterator begin = m_PointsOfInterest.begin();
   ConstPoiIterator end   = m_PointsOfInterest.end();
   Int32 poi = 0;

   while ( begin != end && poi < count )
   {
      const bamPointOfInterest& pnt_of_interest = *begin++;
      (*ppPoi)[poi++] = pnt_of_interest.m_ID;
   }
}

const bamPointOfInterest* bamBridgeModel::GetPointOfInterest(Int32 id) const
{
   ConstPoiIterator begin = m_PointsOfInterest.begin();
   ConstPoiIterator end   = m_PointsOfInterest.end();

   while ( begin != end )
   {
      const bamPointOfInterest& pnt_of_interest = *begin++;
      if ( pnt_of_interest.m_ID == id )
         return &pnt_of_interest;
   }
   return 0;
}

bamPointOfInterest* bamBridgeModel::GetPointOfInterest(Int32 id)
{
   PoiIterator begin = m_PointsOfInterest.begin();
   PoiIterator end   = m_PointsOfInterest.end();

   while ( begin != end )
   {
      bamPointOfInterest& pnt_of_interest = *begin++;
      if ( pnt_of_interest.m_ID == id )
         return &pnt_of_interest;
   }
   return 0;
}

void bamBridgeModel::GetPointOfInterest(Int32 poi,Int32& spanId,Float64& offset,Float64& absLoc) const
{
   bamPointOfInterest pnt_of_interest;
   ConstPoiIterator begin = m_PointsOfInterest.begin();
   ConstPoiIterator end   = m_PointsOfInterest.end();

   while ( begin != end )
   {
      pnt_of_interest = *begin++;

      if (pnt_of_interest.m_ID == poi)
      {
         spanId = pnt_of_interest.m_SpanId;
         offset = pnt_of_interest.m_Offset;
         absLoc = pnt_of_interest.m_AbsLocation;
         break;
      }
   }
}

void bamBridgeModel::AddStressPoint(Int32 poi,Int32 idx,Float64 S)
{
   bamPointOfInterest* pPoi = GetPointOfInterest( poi );
   pPoi->AddStressPoint( idx, S );
   OnNewStressPoint( *pPoi, idx );
}

void bamBridgeModel::RemoveStressPoint(Int32 poi,Int32 idx)
{
   CHECKX(false,"Not implemented");
}

bamLoadFactory& bamBridgeModel::GetLoadFactory()
{
   if (m_pLoadFactory.get() == 0)
      m_pLoadFactory = std::auto_ptr<bamLoadFactory>(CreateLoadFactory());

   return *m_pLoadFactory;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
bamSectionResults bamBridgeModel::ReadSectionResults(const bamSectionResultsKey& key) const
{
   return m_pAnalysisResultsManager->ReadSectionResults( key );
}

bamSectionStress bamBridgeModel::ReadSectionStress(const bamSectionStressKey& key) const
{
   return m_pAnalysisResultsManager->ReadSectionStress( key );
}

bamReaction bamBridgeModel::ReadReaction(const bamReactionKey& key) const
{
   return m_pAnalysisResultsManager->ReadReaction(key);
}

Int32 bamBridgeModel::GetSupportElementCount() const
{
   return m_SupportElements.size();
} // GetSupportElementCount

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamBridgeModel::DeepCopy(bamBridgeModel* pModel) const
{
   // Only copy the model geometry, not the loads

   // Copy support stuff
   Int32 support_count = GetSupportElementCount();
   Int32* support_id = new Int32[support_count];
   EnumSupportElements( &support_id, support_count );
   for ( Int16 support = 0; support < support_count; support++ )
   {
      const bamSupportElement* p_support_element = GetSupportElement( support_id[support] );
      pModel->StoreSupportElement( p_support_element->Clone() );
   }
   delete[] support_id;
   
   // Copy span stuff
   Int32 span_count = GetSpanElementCount();
   Int32* span_id = new Int32[span_count];
   EnumSpanElements( &span_id, span_count );
   for ( Int16 span = 0; span < span_count; span++ )
   {
      const bamSpanElement* p_span_element = GetSpanElement( span_id[span] );
      pModel->StoreSpanElement( p_span_element->Clone() );
   }
   // delete[] span_id; // defered to below

   // Now, link up the spans and supports in the clone.
   for ( Int16 span = 0; span < span_count; span++ )
   {
      const bamSpanElement* p_span_element = GetSpanElement( span_id[span] );
      pModel->ConnectSpanElement( p_span_element->GetID(),
                                  p_span_element->StartSupport().GetID(),
                                  p_span_element->EndSupport().GetID() );

   }
   delete[] span_id;

   // Copy Gravity stuff
   pModel->m_Gravity = m_Gravity;
   pModel->m_GravityDirection = m_GravityDirection;

   // Copy points of interest
   ConstPoiIterator poi_iter;
   for ( poi_iter = m_PointsOfInterest.begin(); poi_iter != m_PointsOfInterest.end(); poi_iter++ )
   {
      const bamPointOfInterest& poi = *poi_iter;
      pModel->m_PointsOfInterest.push_back(poi);
   }
}

//======================== ACCESS     =======================================

const bamSpanElement* bamBridgeModel::GetSpanElement(Int32 spanElementId) const
{
   PRECONDITION( IsValidSpanId(spanElementId) );

   ConstSpanElementIterator iter = m_SpanElements.find( spanElementId );

   const bamSpanElement* pSpanElement;

   if ( iter == m_SpanElements.end() )
      pSpanElement = 0;
   else
      pSpanElement = (*iter).second.get();

   return pSpanElement;
} // GetSpanElement

bamSpanElement* bamBridgeModel::GetSpanElement(Int32 spanElementId)
{
   PRECONDITION( IsValidSpanId(spanElementId) );

   SpanElementIterator iter = m_SpanElements.find( spanElementId );

   bamSpanElement* pSpanElement;

   if ( iter == m_SpanElements.end() )
      pSpanElement = 0;
   else
      pSpanElement = (*iter).second.get();

   return pSpanElement;
} // GetSpanElement

const bamSupportElement* bamBridgeModel::GetSupportElement(Int32 supportElementId) const
{
   PRECONDITION( IsValidSupportId(supportElementId) );

   ConstSupportElementIterator iter = m_SupportElements.find( supportElementId );
   const bamSupportElement* pSupportElement;

   if ( iter == m_SupportElements.end() )
      pSupportElement = 0;
   else
      pSupportElement = (*iter).second.get();

   return pSupportElement;
} // GetSupportElement

bamSupportElement* bamBridgeModel::GetSupportElement(Int32 supportElementId)
{
   PRECONDITION( IsValidSupportId(supportElementId) );

   SupportElementIterator iter = m_SupportElements.find( supportElementId );
   bamSupportElement* pSupportElement;

   if ( iter == m_SupportElements.end() )
      pSupportElement = 0;
   else
      pSupportElement = (*iter).second.get();

   return pSupportElement;
} // GetSupportElement

bamLoadCase* bamBridgeModel::GetLoadCase(Int32 loadCaseId)
{
   LoadCaseIterator begin = m_LoadCases.begin();
   LoadCaseIterator end   = m_LoadCases.end();
   while ( begin != end )
   {
      boost::shared_ptr<bamLoadCase>& loadCase = (*begin++).second;
      if (loadCase->GetID() == loadCaseId)
         return loadCase.get();
   }

   return 0;
} // GetLoadCase

const bamLoadCase* bamBridgeModel::GetLoadCase(Int32 loadCaseId) const
{
   ConstLoadCaseIterator begin = m_LoadCases.begin();
   ConstLoadCaseIterator end   = m_LoadCases.end();
   while ( begin != end )
   {
      const boost::shared_ptr<bamLoadCase>& loadCase = (*begin++).second;
      if (loadCase->GetID() == loadCaseId)
         return loadCase.get();
   }

   return 0;
} // GetLoadCase

bamLoadCombination* bamBridgeModel::GetLoadCombination(Int32 id)
{
   PRECONDITION( IsValidLoadCombinationId(id) );

   bamLoadCombination* pLoadCombination;

   LoadCombinationIterator iter = m_LoadCombinations.find(id);
   if ( iter == m_LoadCombinations.end() )
      pLoadCombination = 0;
   else 
      pLoadCombination = (*iter).second.get();

   return pLoadCombination;
}

//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamBridgeModel::WriteSectionResults(const bamSectionResultsKey& key,const bamSectionResults& sr)
{
   m_pAnalysisResultsManager->WriteSectionResults( key, sr );
}

void bamBridgeModel::WriteSectionStress(const bamSectionStressKey& key,const bamSectionStress& sr)
{
   m_pAnalysisResultsManager->WriteSectionStress( key, sr );
}

void bamBridgeModel::WriteReaction(const bamReactionKey& key,const bamReaction& reaction)
{
   m_pAnalysisResultsManager->WriteReaction( key, reaction );
}

void bamBridgeModel::StoreSpanElement(bamSpanElement* pSpanElement)
{
   // Automatically replaces the entry if a dupiclate key was found
   m_SpanElements.insert( std::make_pair(pSpanElement->GetID(),boost::shared_ptr<bamSpanElement>(pSpanElement)) );
} // StoreSpanElement

void bamBridgeModel::StoreSupportElement(bamSupportElement* pSupportElement)
{
   // Automatically replaces the entry if a dupiclate key was found
   m_SupportElements.insert( std::make_pair(pSupportElement->GetID(), boost::shared_ptr<bamSupportElement>(pSupportElement)) );
} // StoreSupportElement

void bamBridgeModel::StoreLoadCase(bamLoadCase* pLoadCase)
{
   // Automatically replaces the entry if a dupiclate key was found
   m_LoadCases.insert( std::make_pair(pLoadCase->GetID(),boost::shared_ptr<bamLoadCase>(pLoadCase)) );
} // StoreLoadCase

void bamBridgeModel::StoreLoadCombination(bamLoadCombination* pLoadCombination)
{
   // Automatically replaces the entry if a dupiclate key was found
   m_LoadCombinations.insert( std::make_pair(pLoadCombination->GetID(),
                              boost::shared_ptr<bamLoadCombination>(pLoadCombination) ));
} // StoreLoadCombination

void bamBridgeModel::StoreLiveLoad(const bamLiveLoad& ll)
{
   // Automatically replaces the entry if a dupiclate key was found
   m_LiveLoads.insert( std::pair<Int32,bamLiveLoad>( ll.GetID(), ll ) );
}

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

void bamBridgeModel::DoSetup()
{
   // Does nothing by default
}

void bamBridgeModel::DoCleanup()
{
   // Does nothing by default
}

void bamBridgeModel::CollectLoadCaseResults(bamLoadCase& lc)
{
   m_pAnalysisResultsManager->DestroyStorage( lc.GetID() );
   m_pAnalysisResultsManager->CreateStorage( lc.GetID() );

   // POI Results
   ConstPoiIterator poi_iter;
   for ( poi_iter = m_PointsOfInterest.begin(); poi_iter != m_PointsOfInterest.end(); poi_iter++ )
   {
      const bamPointOfInterest& poi = *poi_iter;
      CollectLoadCaseResults( lc, poi );
   }

   // Reactions
   SupportElementIterator begin = m_SupportElements.begin();
   SupportElementIterator end   = m_SupportElements.end();
   while ( begin != end )
   {
      boost::shared_ptr<bamSupportElement>& pSupportElement = (*begin++).second;
      bamReaction reaction;

      DoCollectReactions(pSupportElement->GetID(),
                         reaction );
      m_pAnalysisResultsManager->WriteReaction( bamReactionKey( pSupportElement->GetID(), lc.GetID() ),
                                                 reaction);
   }
}

void bamBridgeModel::CollectLoadCaseResults( bamLoadCase& rLoadCase, const bamPointOfInterest& poi )
{
   bamSectionResults sr;
   bamSectionResultsKey key( poi.m_ID, rLoadCase.GetID() );

   DoCollectResults( poi.m_ID, sr );
   WriteSectionResults( key, sr );

   std::set<bamStressPoint>::const_iterator stress_point_iter;
   for ( stress_point_iter = poi.m_StressPoints.begin(); 
         stress_point_iter != poi.m_StressPoints.end(); 
         stress_point_iter++ )
   {
      const bamStressPoint& stress_point = *stress_point_iter;
      LoadCaseStress( rLoadCase, sr, poi, stress_point );
   }
}

void bamBridgeModel::LoadCaseStress(bamLoadCase& rLoadCase, const bamPointOfInterest& poi, const bamStressPoint& sp )
{
   bamSectionResults sr;
   bamSectionResultsKey key( poi.m_ID, rLoadCase.GetID() );

   sr = ReadSectionResults( key );
   LoadCaseStress( rLoadCase, sr, poi,sp );
}

void bamBridgeModel::LoadCaseStress(bamLoadCase& rLoadCase, const bamSectionResults& sr,const bamPointOfInterest& poi, const bamStressPoint& sp )
{
   sysSectionValue f = sr.Mz() / sp.m_S;
   WriteSectionStress( bamSectionStressKey(poi.m_ID, sp.m_ID, rLoadCase.GetID()), bamSectionStress( f ) );
}

Float64 bamBridgeModel::GetBridgeLength() const
{
   Float64 length = 0;

   ConstSpanElementIterator begin = m_SpanElements.begin();
   ConstSpanElementIterator end   = m_SpanElements.end();

   while ( begin != end )
   {
      const boost::shared_ptr<bamSpanElement>& pSpanElement = (*begin++).second;
      length += pSpanElement->Length();
   }

   return length;
} // GetBridgeLength

Float64 bamBridgeModel::GetSpanLength(Int32 spanId) const
{
   return GetSpanElement(spanId)->Length();
}

void bamBridgeModel::Draw(HDC hDC,RECT rect,grlibPointMapper::MapMode mapMode) const
{
   Float64 length = GetBridgeLength();
   grlibPointMapper mapper;

   mapper.SetMappingMode(mapMode);
   mapper.SetDeviceOrg(rect.left,(rect.top+rect.bottom)/2);
   mapper.SetDeviceExt(rect.right-rect.left, rect.bottom-rect.top);
   mapper.SetWorldOrg(0,0);
   mapper.SetWorldExt(length,0);

   ConstSpanElementIterator begin_span = m_SpanElements.begin();
   ConstSpanElementIterator end_span   = m_SpanElements.end();
   while ( begin_span != end_span )
   {
      const boost::shared_ptr<bamSpanElement>& pSpanElement = (*begin_span++).second;
      pSpanElement->Draw(hDC,mapper);
   }

   ConstSupportElementIterator begin_support = m_SupportElements.begin();
   ConstSupportElementIterator end_support   = m_SupportElements.end();
   while ( begin_support != end_support )
   {
      const boost::shared_ptr<bamSupportElement>& pSupportElement = (*begin_support++).second;
      pSupportElement->Draw(hDC,mapper);
   }
}

void bamBridgeModel::SetAnalyzedFlag(bool flag)
{
   if (flag == m_IsAnalyzed)
      return;

   m_IsAnalyzed = flag;
} // SetAnalyzedFlag

void bamBridgeModel::SetModifiedFlag(bool flag)
{
   if (flag == m_IsModified)
      return;

   m_IsModified = flag;

   if (m_IsModified)
      SetAnalyzedFlag(false);
} // SetModifiedFlag

bool bamBridgeModel::IsModified() const
{
   return m_IsModified;
} // IsModified

bool bamBridgeModel::IsAnalyzed() const
{
   return m_IsAnalyzed;
}

void bamBridgeModel::SetGravityDirection(bamGravityDirection gravityDir)
{
   m_GravityDirection = gravityDir;

   SetModifiedFlag();
} // SetGravityDirection

void bamBridgeModel::SetGravitionalAcceleration(Float64 gravity)
{
   m_Gravity = gravity;

   SetModifiedFlag();
} // SetGravationalAcceleration

bamGravityDirection bamBridgeModel::GetGravityDirection() const
{
   return m_GravityDirection;
} // GetGravityDirection

Float64 bamBridgeModel::GetGravitionalAcceleration() const
{
   return m_Gravity;
} // GetGravationalAcceleration

void bamBridgeModel::AbsLocationToRelLocation(Float64 absLoc,Int32& spanId,Float64& offset) const
{
   Float64 start_loc, end_loc;
   ConstSpanElementIterator begin = m_SpanElements.begin();
   ConstSpanElementIterator end   = m_SpanElements.end();

   // Scan through aenv span elements and find the one where absLoc
   // is between the start and the end of the span element.
   while ( begin != end )
   {
      const boost::shared_ptr<bamSpanElement>& pSpanElement = (*begin++).second;
      start_loc = pSpanElement->StartSupport().GetLocation();
      end_loc   = pSpanElement->EndSupport().GetLocation();

      if ( InRange(start_loc, absLoc, end_loc) ||
           InRange(end_loc,   absLoc, start_loc) )
      {
         spanId = pSpanElement->GetID();
         offset = absLoc - min( start_loc, end_loc ); 
         break;
      }
   }

}

void bamBridgeModel::RelLocationToAbsLocation(Int32 spanId,Float64 offset,Float64& absLoc) const
{
   const bamSpanElement* pSpanElement = GetSpanElement(spanId);

   if ( pSpanElement->StartSupport().GetLocation() <
        pSpanElement->EndSupport().GetLocation() )
   {
      // Span goes left to right between supports
      absLoc = pSpanElement->StartSupport().GetLocation() + offset;
   }
   else
   {
      // Span goes right to left between supports
      absLoc = pSpanElement->StartSupport().GetLocation() - offset;
   }
}

bool bamBridgeModel::IsValidSpanId(Int32 spanId) const
{
   return m_SpanElements.find(spanId) == m_SpanElements.end() ? false : true;
}

bool bamBridgeModel::IsValidSupportId(Int32 supportId) const
{
   return m_SupportElements.find(supportId) == m_SupportElements.end() ? false : true;
}

bool bamBridgeModel::IsValidLoadCaseId(Int32 id) const
{
   return m_LoadCases.find(id) == m_LoadCases.end() ? false : true;
}

bool bamBridgeModel::IsValidLoadCombinationId(Int32 id) const
{
   return m_LoadCombinations.find(id) == m_LoadCombinations.end() ? false : true;
}

bool bamBridgeModel::IsValidLiveLoadId(Int32 id) const
{
   // Check the associated loading id's for every live load
   // until a match is found

   ConstLiveLoadIterator begin = m_LiveLoads.begin();
   ConstLiveLoadIterator end   = m_LiveLoads.end();

   while ( begin != end )
   {
      const bamLiveLoad& env = (*begin++).second;
      if ( env.GetMinLoadingId() == id ||
           env.GetMaxLoadingId() == id )
         return true;
   }

   return false;
}

bool bamBridgeModel::IsValidEnvelopeId(Int32 id) const
{
   // Check the associated loading id's for every envelope
   // until a match is found

   ConstEnvelopeIterator begin = m_Envelopes.begin();
   ConstEnvelopeIterator end   = m_Envelopes.end();

   while ( begin != end )
   {
      const boost::shared_ptr<bamEnvelope>& penv = (*begin++).second;
      if ( penv->GetLoadingId( bamEnvelope::Min ) == id ||
           penv->GetLoadingId( bamEnvelope::Max ) == id )
         return true;
   }

   return false;
}

bool bamBridgeModel::IsLoadingIdUsed(Int32 id) const
{
   // If it is a valid id for any of the loadings
   // then the subject id has already been used.
   return ( !IsValidLoadCaseId(id)        &&
            !IsValidLoadCombinationId(id) &&
            !IsValidLiveLoadId(id)        &&
            !IsValidEnvelopeId(id) ) ? true : false;
}

void bamBridgeModel::DoLoadCombination(bamLoadCombination& rCombo)
{
   m_pAnalysisResultsManager->DestroyStorage( rCombo.GetID() );
   m_pAnalysisResultsManager->CreateStorage( rCombo.GetID() );

   // Points Of Interest
   //
   ConstPoiIterator poi_iter;
   for ( poi_iter = m_PointsOfInterest.begin(); poi_iter != m_PointsOfInterest.end(); poi_iter++ )
   {
      const bamPointOfInterest& poi = *poi_iter;
      DoLoadCombination( rCombo, poi );
   }

   // Reactions
   //
   SupportElementIterator begin = m_SupportElements.begin();
   SupportElementIterator end   = m_SupportElements.end();
   while ( begin != end )
   {
      boost::shared_ptr<bamSupportElement>& pSupportElement = (*begin++).second;
      bamReaction reaction;

      reaction = rCombo.CombineReactions( pSupportElement->GetID() );
      m_pAnalysisResultsManager->WriteReaction( bamReactionKey( pSupportElement->GetID(), rCombo.GetID() ),
                                                reaction );
   }
}

void bamBridgeModel::DoLoadCombination(bamLoadCombination& rCombo, const bamPointOfInterest& poi)
{
   bamSectionResults sr;
   bamSectionResultsKey key( poi.m_ID, rCombo.GetID() );
   sr = rCombo.CombineSectionResults( poi.m_ID );
   WriteSectionResults( key, sr );

   std::set<bamStressPoint>::const_iterator stress_point_iter;
   for ( stress_point_iter = poi.m_StressPoints.begin(); stress_point_iter != poi.m_StressPoints.end(); stress_point_iter++ )
   {
      const bamStressPoint& stress_point = *stress_point_iter;
      DoLoadCombinationStress( rCombo, poi, stress_point );
   }
}

void bamBridgeModel::DoLoadCombinationStress(bamLoadCombination& rCombo, const bamPointOfInterest& poi,const bamStressPoint& sp)
{
   bamSectionStress ss = rCombo.CombineSectionStress( poi.m_ID, sp.m_ID );
   bamSectionStressKey ss_key( poi.m_ID, sp.m_ID, rCombo.GetID() );
   WriteSectionStress( ss_key, ss );
}

void bamBridgeModel::AddPointOfInterest(Int32 poiId,Int32 spanId,Float64 distFromStart,Float64 absLoc)
{
   const bamPointOfInterest& poi = StorePointOfInterest( poiId, spanId, distFromStart, absLoc );
   OnNewPointOfInterest(poi);
}

const bamPointOfInterest& bamBridgeModel::StorePointOfInterest(Int32 poi,Int32 spanId,Float64 offset,Float64 absLoc)
{
   bamPointOfInterest pnt_of_interest;

   pnt_of_interest.m_ID          = poi;
   pnt_of_interest.m_SpanId      = spanId;
   pnt_of_interest.m_Offset      = offset;
   pnt_of_interest.m_AbsLocation = absLoc;

   m_PointsOfInterest.push_back( pnt_of_interest );

   return m_PointsOfInterest[m_PointsOfInterest.size()-1];
}

void bamBridgeModel::OnNewPointOfInterest(const bamPointOfInterest& poi)
{
   if ( !IsModified() && IsAnalyzed() )
   {
      // Compute load case results at the new point of interest
      LoadCaseIterator loadcase_begin = m_LoadCases.begin();
      LoadCaseIterator loadcase_end   = m_LoadCases.end();
      while ( loadcase_begin != loadcase_end )
      {
         boost::shared_ptr<bamLoadCase>& loadCase = (*loadcase_begin++).second;

         DoBeginLoadCase(*loadCase);
         loadCase->Apply();
         DoAnalyze();

         CollectLoadCaseResults( *loadCase, poi );

         DoEndLoadCase();
         loadCase->Remove();
      }

      // Live Loads
      LiveLoadIterator liveload_begin = m_LiveLoads.begin();
      LiveLoadIterator liveload_end   = m_LiveLoads.end();
      while ( liveload_begin != liveload_end )
      { 
         bamLiveLoad& ll = (*liveload_begin++).second;
         m_pSolver->Solve( ll, poi.m_ID );
      }


      // Envelopes
      EnvelopeIterator envelope_begin = m_Envelopes.begin();
      EnvelopeIterator envelope_end   = m_Envelopes.end();
      while ( envelope_begin != envelope_end )
      {
         boost::shared_ptr<bamEnvelope>& penvelope = (*envelope_begin++).second;
         penvelope->DoEnvelope(poi.m_ID);
      }

      // Combinations
      LoadCombinationIterator loadcombo_begin = m_LoadCombinations.begin();
      LoadCombinationIterator loadcombo_end   = m_LoadCombinations.end();
      while ( loadcombo_begin != loadcombo_end )
      {
         boost::shared_ptr<bamLoadCombination>& pLoadCombination = (*loadcombo_begin++).second;
         DoLoadCombination( *pLoadCombination, poi );
      }
   }
}

void bamBridgeModel::OnNewStressPoint(const bamPointOfInterest& poi,Int32 spid)
{
   if ( !IsModified() && IsAnalyzed() )
   {
      std::set<bamStressPoint>::const_iterator found;
      bamStressPoint find_me;
      find_me.m_ID = spid;
      found = poi.m_StressPoints.find( find_me );
      const bamStressPoint& sp = *found;

      // Compute load case results at the new point of interest
      LoadCaseIterator loadcase_begin = m_LoadCases.begin();
      LoadCaseIterator loadcase_end   = m_LoadCases.end();
      while ( loadcase_begin != loadcase_end )
      {
         boost::shared_ptr<bamLoadCase>& loadCase = (*loadcase_begin++).second;

         DoBeginLoadCase(*loadCase);
         loadCase->Apply();

         LoadCaseStress( *loadCase, poi, sp );

         DoEndLoadCase();
         loadCase->Remove();
      }

      // Live Loads
      LiveLoadIterator liveload_begin = m_LiveLoads.begin();
      LiveLoadIterator liveload_end   = m_LiveLoads.end();
      while ( liveload_begin != liveload_end )
      { 
         bamLiveLoad& ll = (*liveload_begin++).second;
         m_pSolver->SolveStress( ll, poi.m_ID, sp.m_ID );
      }


      // Envelopes
      EnvelopeIterator envelope_begin = m_Envelopes.begin();
      EnvelopeIterator envelope_end   = m_Envelopes.end();
      while ( envelope_begin != envelope_end )
      {
         boost::shared_ptr<bamEnvelope>& penvelope = (*envelope_begin++).second;
         penvelope->DoEnvelopeSectionStress( poi.m_ID, sp.m_ID );
      }

      // Combinations
      LoadCombinationIterator loadcombo_begin = m_LoadCombinations.begin();
      LoadCombinationIterator loadcombo_end   = m_LoadCombinations.end();
      while ( loadcombo_begin != loadcombo_end )
      {
         boost::shared_ptr<bamLoadCombination>& pLoadCombination = (*loadcombo_begin++).second;
         DoLoadCombinationStress( *pLoadCombination, poi, sp );
      }
   }
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamBridgeModel::AssertValid() const
{
   return true;
}

void bamBridgeModel::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamBridgeModel" << endl;

   SpanElementContainer::const_iterator spanIter;
   for ( spanIter = m_SpanElements.begin(); spanIter != m_SpanElements.end(); spanIter++ )
   {
      (*spanIter).second->Dump(os);
      os << endl;
   }

   os << endl;

   SupportElementContainer::const_iterator suppIter;
   for ( suppIter = m_SupportElements.begin(); suppIter != m_SupportElements.end(); suppIter++ )
   {
      (*suppIter).second->Dump(os);
      os << endl;
   }

   os << endl;

   PoiContainer::const_iterator poiIter;
   for ( poiIter = m_PointsOfInterest.begin(); poiIter != m_PointsOfInterest.end(); poiIter++ )
   {
      (*poiIter).Dump(os);
      os << endl;
   }

   os << endl;

   LoadCaseContainer::const_iterator lcaseIter;
   for ( lcaseIter = m_LoadCases.begin(); lcaseIter != m_LoadCases.end(); lcaseIter++ )
   {
      (*lcaseIter).second->Dump(os);
      os << endl;
   }

   os << endl;

   LiveLoadContainer::const_iterator llIter;
   for ( llIter = m_LiveLoads.begin(); llIter != m_LiveLoads.end(); llIter++ )
   {
      (*llIter).second.Dump(os);
      os << endl;
   }

   os << endl;

//   LoadCombinationContainer::const_iterator lcIter;
//   for ( lcIter = m_LoadCombinations.begin(); lcIter != m_LoadCombinations.end(); lcIter++ )
//   {
//      (*lcIter).second->Dump(os);
//      os << endl;
//   }
//
//   os << endl;
//
//   EnvelopeContainer::const_iterator envIter;
//   for ( envIter = m_Envelopes.begin(); envIter != m_Envelopes.end(); envIter++ )
//   {
//      (*envIter).second->Dump(os);
//      os << endl;
//   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamBridgeModel::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamBridgeModel");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamBridgeModel");

   TESTME_EPILOG("BridgeModel");
}
#endif // _UNITTEST
