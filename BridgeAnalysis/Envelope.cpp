///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bamEnvelope           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeAnalysis\Envelope.h>              // class implementation
#include <BridgeAnalysis\BridgeModel.h>
#include <BridgeAnalysis\Reaction.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////
DIAG_DEFINE_GROUP( bamEnvelope, DIAG_GROUP_DISABLE, MAX_DIAG_GROUP_LEVEL );
#define ENV_TRACE 50

//======================== LIFECYCLE  =======================================
bamEnvelope::bamEnvelope(IDType id)
{
   m_Id = id;
   m_pBridgeModel = 0;
   m_MinId = -1;
   m_MaxId = -1;
}

bamEnvelope::bamEnvelope(const bamEnvelope& rOther)
{
   MakeCopy( rOther );
} // bamEnvelope

bamEnvelope::~bamEnvelope()
{
} // ~bamEnvelope

//======================== OPERATORS  =======================================

bamEnvelope& bamEnvelope::operator = (const bamEnvelope& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
} // operator =

//======================== OPERATIONS =======================================
bamEnvelope* bamEnvelope::CreateClone() const
{
   return new bamEnvelope( *this );
}

void bamEnvelope::AddLoading(IDType loadingId)
{
   m_Loadings.push_back(loadingId);
}

void bamEnvelope::AddLoading(std::vector<IDType>& loadingIds)
{
   m_Loadings.insert( m_Loadings.end(), loadingIds.begin(), loadingIds.end() );
}
void bamEnvelope::SetBridgeModel(bamBridgeModel* pModel)
{
   m_pBridgeModel = pModel;
}

void bamEnvelope::DoEnvelope() const
{
   PRECONDITION(m_pBridgeModel != 0);
   PRECONDITION(m_Id != -1);

   DoEnvelopeSectionResults();
   DoEnvelopeSectionStress();
   DoEnvelopeReactions();
}

void bamEnvelope::DoEnvelope(PoiIDType poi) const
{
   DoEnvelopeSectionResults(poi);
   DoEnvelopeSectionStress(poi);
}

void bamEnvelope::DoEnvelopeSectionStress(PoiIDType poi,CollectionIndexType srid) const
{
   // Read the enveloped moment and compute the stress using it.
   bamSectionResultsKey min_key( poi, m_MinId );
   bamSectionResults sr_min = m_pBridgeModel->ReadSectionResults( min_key );

   bamSectionResultsKey max_key( poi, m_MaxId );
   bamSectionResults sr_max = m_pBridgeModel->ReadSectionResults( max_key );

   WATCHX( bamEnvelope, ENV_TRACE, _T("Max Moment = ") << sr_max.Mz() );
   WATCHX( bamEnvelope, ENV_TRACE, _T("Min Moment = ") << sr_min.Mz() );

   const bamPointOfInterest* pPoi = m_pBridgeModel->GetPointOfInterest( poi );
   CHECK( pPoi != 0 );

   bamStressPoint find_me;
   find_me.m_ID = srid;
   std::set<bamStressPoint>::const_iterator sp_iter = pPoi->m_StressPoints.find( find_me );
   const bamStressPoint& stress_point = *sp_iter;
   DoEnvelopeSectionStress( *pPoi, sr_min, sr_max, stress_point );
}

//======================== ACCESS     =======================================
IDType bamEnvelope::GetID() const
{
   return m_Id;
}

void bamEnvelope::SetID(IDType id)
{
   m_Id = id;
}

void bamEnvelope::SetLoadingIds(IDType minId,IDType maxId)
{
   m_MinId = minId;
   m_MaxId = maxId;
}

IDType bamEnvelope::GetLoadingId(bamEnvelope::ExtremeValueType ev) const
{
   return ev == Min ? m_MinId : m_MaxId;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamEnvelope::MakeCopy(const bamEnvelope& rOther)
{
   m_Id = rOther.m_Id;
   
   m_pBridgeModel = rOther.m_pBridgeModel;
   m_MinId = rOther.m_MinId;
   m_MaxId = rOther.m_MaxId;

   m_Loadings = rOther.m_Loadings;
}

void bamEnvelope::MakeAssignment(const bamEnvelope& rOther)
{
   //Base::MakeAssignment( rOther );
   MakeCopy( rOther );
}

void bamEnvelope::InitEnvelope(bamSectionResults* pMin, bamSectionResults* pMax) const
{
   pMin->Fx() = Float64_Max;
   pMin->Fy() = Float64_Max;
   pMin->Mz() = Float64_Max;
   pMin->Dx() = Float64_Max;
   pMin->Dy() = Float64_Max;
   pMin->Rz() = Float64_Max;

   pMax->Fx() = -Float64_Max;
   pMax->Fy() = -Float64_Max;
   pMax->Mz() = -Float64_Max;
   pMax->Dx() = -Float64_Max;
   pMax->Dy() = -Float64_Max;
   pMax->Rz() = -Float64_Max;
}

void bamEnvelope::InitEnvelope(bamSectionStress* pMin, bamSectionStress* pMax) const
{
   pMin->F() = Float64_Max;
   pMax->F() = -Float64_Max;
}

void bamEnvelope::InitEnvelope(bamReaction* pMin,bamReaction* pMax) const
{
   pMin->Fx() = Float64_Max;
   pMin->Fy() = Float64_Max;
   pMin->Mz() = Float64_Max;
   pMin->Dx() = Float64_Max;
   pMin->Dy() = Float64_Max;
   pMin->Rz() = Float64_Max;

   pMax->Fx() = -Float64_Max;
   pMax->Fy() = -Float64_Max;
   pMax->Mz() = -Float64_Max;
   pMax->Dx() = -Float64_Max;
   pMax->Dy() = -Float64_Max;
   pMax->Rz() = -Float64_Max;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamEnvelope::DoEnvelopeSectionResults() const
{
   WATCHX( bamEnvelope, ENV_TRACE, "Beginning DoEnvelopeSectionResults()" );

   // bamEnvelope results at Points of interest
   CollectionIndexType poi_count;
   PoiIDType* poi_list;
   poi_count = m_pBridgeModel->GetPointOfInterestCount();
   poi_list = new PoiIDType[poi_count];
   m_pBridgeModel->EnumPointsOfInterest(&poi_list,poi_count);

   for (CollectionIndexType poiIdx = 0; poiIdx < poi_count; poiIdx++)
   {
      DoEnvelope( poi_list[poiIdx] );
   } // end of poi loop
   delete[] poi_list;

   WATCHX( bamEnvelope, ENV_TRACE, "Ending DoEnvelopeSectionResults()" );
}

void bamEnvelope::DoEnvelopeSectionResults(PoiIDType poi) const
{
   bamSectionResults min_results, max_results;

   // Initialize enveloped results
   InitEnvelope(&min_results,&max_results);

   // For each loading to be considered in this envelope
   ConstLoadingIterator begin = m_Loadings.begin();
   ConstLoadingIterator end   = m_Loadings.end();
   while ( begin != end )
   {
      IDType loadingId = *begin++;

      WATCHX( bamEnvelope, ENV_TRACE, "**** Section Results ****" );
      WATCHX( bamEnvelope, ENV_TRACE, "Poi " << poi << " Loading " << loadingId);

      bamSectionResults current_results = m_pBridgeModel->ReadSectionResults( bamSectionResultsKey( poi, loadingId ) );

      WATCHX( bamEnvelope, ENV_TRACE, "Fx " << current_results.Fx().Left() << " / " << current_results.Fx().Right() );
      WATCHX( bamEnvelope, ENV_TRACE, "Fy " << current_results.Fy().Left() << " / " << current_results.Fy().Right() );
      WATCHX( bamEnvelope, ENV_TRACE, "Mz " << current_results.Mz().Left() << " / " << current_results.Mz().Right() );
      WATCHX( bamEnvelope, ENV_TRACE, "Dx " << current_results.Dx().Left() << " / " << current_results.Dx().Right() );
      WATCHX( bamEnvelope, ENV_TRACE, "Dy " << current_results.Dy().Left() << " / " << current_results.Dy().Right() );
      WATCHX( bamEnvelope, ENV_TRACE, "Rz " << current_results.Rz().Left() << " / " << current_results.Rz().Right() );

      if ( current_results.Fx().Left()  > max_results.Fx().Left() )    max_results.Fx().Left() = current_results.Fx().Left();
      if ( current_results.Fy().Left()  > max_results.Fy().Left() )    max_results.Fy().Left() = current_results.Fy().Left();
      if ( current_results.Mz().Left()  > max_results.Mz().Left() )    max_results.Mz().Left() = current_results.Mz().Left();
      if ( current_results.Dx().Left()  > max_results.Dx().Left() )    max_results.Dx().Left() = current_results.Dx().Left();
      if ( current_results.Dy().Left()  > max_results.Dy().Left() )    max_results.Dy().Left() = current_results.Dy().Left();
      if ( current_results.Rz().Left()  > max_results.Rz().Left() )    max_results.Rz().Left() = current_results.Rz().Left();
      if ( current_results.Fx().Right() > max_results.Fx().Right() )   max_results.Fx().Right() = current_results.Fx().Right();
      if ( current_results.Fy().Right() > max_results.Fy().Right() )   max_results.Fy().Right() = current_results.Fy().Right();
      if ( current_results.Mz().Right() > max_results.Mz().Right() )   max_results.Mz().Right() = current_results.Mz().Right();
      if ( current_results.Dx().Right() > max_results.Dx().Right() )   max_results.Dx().Right() = current_results.Dx().Right();
      if ( current_results.Dy().Right() > max_results.Dy().Right() )   max_results.Dy().Right() = current_results.Dy().Right();
      if ( current_results.Rz().Right() > max_results.Rz().Right() )   max_results.Rz().Right() = current_results.Rz().Right();

      if ( current_results.Fx().Left()  < min_results.Fx().Left() )    min_results.Fx().Left() = current_results.Fx().Left();
      if ( current_results.Fy().Left()  < min_results.Fy().Left() )    min_results.Fy().Left() = current_results.Fy().Left();
      if ( current_results.Mz().Left()  < min_results.Mz().Left() )    min_results.Mz().Left() = current_results.Mz().Left();
      if ( current_results.Dx().Left()  < min_results.Dx().Left() )    min_results.Dx().Left() = current_results.Dx().Left();
      if ( current_results.Dy().Left()  < min_results.Dy().Left() )    min_results.Dy().Left() = current_results.Dy().Left();
      if ( current_results.Rz().Left()  < min_results.Rz().Left() )    min_results.Rz().Left() = current_results.Rz().Left();
      if ( current_results.Fx().Right() < min_results.Fx().Right() )   min_results.Fx().Right() = current_results.Fx().Right();
      if ( current_results.Fy().Right() < min_results.Fy().Right() )   min_results.Fy().Right() = current_results.Fy().Right();
      if ( current_results.Mz().Right() < min_results.Mz().Right() )   min_results.Mz().Right() = current_results.Mz().Right();
      if ( current_results.Dx().Right() < min_results.Dx().Right() )   min_results.Dx().Right() = current_results.Dx().Right();
      if ( current_results.Dy().Right() < min_results.Dy().Right() )   min_results.Dy().Right() = current_results.Dy().Right();
      if ( current_results.Rz().Right() < min_results.Rz().Right() )   min_results.Rz().Right() = current_results.Rz().Right();
   }  // end of while

   // Since this is enveloping, left and right should be the same
   max_results.Fx() = max_results.Fx().Left() > max_results.Fx().Right() ? max_results.Fx().Left() : max_results.Fx().Right();
   max_results.Fy() = max_results.Fy().Left() > max_results.Fy().Right() ? max_results.Fy().Left() : max_results.Fy().Right();
   max_results.Mz() = max_results.Mz().Left() > max_results.Mz().Right() ? max_results.Mz().Left() : max_results.Mz().Right();
   max_results.Dx() = max_results.Dx().Left() > max_results.Dx().Right() ? max_results.Dx().Left() : max_results.Dx().Right();
   max_results.Dy() = max_results.Dy().Left() > max_results.Dy().Right() ? max_results.Dy().Left() : max_results.Dy().Right();
   max_results.Rz() = max_results.Rz().Left() > max_results.Rz().Right() ? max_results.Rz().Left() : max_results.Rz().Right();

   min_results.Fx() = min_results.Fx().Left() < min_results.Fx().Right() ? min_results.Fx().Left() : min_results.Fx().Right();
   min_results.Fy() = min_results.Fy().Left() < min_results.Fy().Right() ? min_results.Fy().Left() : min_results.Fy().Right();
   min_results.Mz() = min_results.Mz().Left() < min_results.Mz().Right() ? min_results.Mz().Left() : min_results.Mz().Right();
   min_results.Dx() = min_results.Dx().Left() < min_results.Dx().Right() ? min_results.Dx().Left() : min_results.Dx().Right();
   min_results.Dy() = min_results.Dy().Left() < min_results.Dy().Right() ? min_results.Dy().Left() : min_results.Dy().Right();
   min_results.Rz() = min_results.Rz().Left() < min_results.Rz().Right() ? min_results.Rz().Left() : min_results.Rz().Right();

   // Add the analysis results to the model
   m_pBridgeModel->WriteSectionResults( bamSectionResultsKey( poi, m_MinId ), min_results );
   m_pBridgeModel->WriteSectionResults( bamSectionResultsKey( poi, m_MaxId ), max_results );
}

void bamEnvelope::DoEnvelopeSectionStress() const
{
   WATCHX( bamEnvelope, ENV_TRACE, "Beginning DoEnvelopeSectionStress()" );

   // bamEnvelope results at Points of interest
   CollectionIndexType poi_count;
   PoiIDType* poi_list;
   poi_count = m_pBridgeModel->GetPointOfInterestCount();
   poi_list = new PoiIDType[poi_count];
   m_pBridgeModel->EnumPointsOfInterest(&poi_list,poi_count);

   for (CollectionIndexType poiIdx = 0; poiIdx < poi_count; poiIdx++)
   {
      DoEnvelopeSectionStress(poi_list[poiIdx]);
   } // end of poi loop
   delete[] poi_list;

   WATCHX( bamEnvelope, ENV_TRACE, "Ending DoEnvelopeSectionResults()" );
}

void bamEnvelope::DoEnvelopeSectionStress(PoiIDType poi) const
{
   const bamPointOfInterest* pPoi = m_pBridgeModel->GetPointOfInterest(poi);
   std::set<bamStressPoint>::const_iterator sp_iter;
   for ( sp_iter = pPoi->m_StressPoints.begin(); sp_iter != pPoi->m_StressPoints.end(); sp_iter++ )
   {
      const bamStressPoint& stress_point = *sp_iter;
      DoEnvelopeSectionStress( poi,stress_point.m_ID);
   }  // end of while stress point
}

void bamEnvelope::DoEnvelopeSectionStress(const bamPointOfInterest& poi,const bamSectionResults& srMin,const bamSectionResults& srMax,const bamStressPoint& sp) const
{
   bamSectionStress min_results, max_results;
      
   max_results.F() = srMax.Mz() / sp.m_S;
   min_results.F() = srMin.Mz() / sp.m_S;

   // Add the analysis results to the model
   m_pBridgeModel->WriteSectionStress( bamSectionStressKey( poi.m_ID, sp.m_ID, m_MinId ), min_results );
   m_pBridgeModel->WriteSectionStress( bamSectionStressKey( poi.m_ID, sp.m_ID, m_MaxId ), max_results );
}

void bamEnvelope::DoEnvelopeReactions() const
{
   // bamEnvelope reactions at each support
   CollectionIndexType support_count;
   IDType* support_list;
   support_count = m_pBridgeModel->GetSupportElementCount();
   support_list = new IDType[support_count];
   m_pBridgeModel->EnumSupportElements(&support_list,support_count);
   for (CollectionIndexType supportIdx = 0; supportIdx < support_count; supportIdx++)
   {
      bamReaction min_reaction;
      bamReaction max_reaction;

      InitEnvelope( &min_reaction, &max_reaction );

      ConstLoadingIterator begin = m_Loadings.begin();
      ConstLoadingIterator end   = m_Loadings.end();
      while ( begin != end )
      {
         bamReaction reaction;
         IDType loadingId = *begin++;
         reaction = m_pBridgeModel->ReadReaction( bamReactionKey(support_list[supportIdx],loadingId) );

         if ( reaction.Fx() < min_reaction.Fx() )  min_reaction.Fx() = reaction.Fx();
         if ( reaction.Fy() < min_reaction.Fy() )  min_reaction.Fy() = reaction.Fy();
         if ( reaction.Mz() < min_reaction.Mz() )  min_reaction.Mz() = reaction.Mz();
         if ( reaction.Dx() < min_reaction.Dx() )  min_reaction.Dx() = reaction.Dx();
         if ( reaction.Dy() < min_reaction.Dy() )  min_reaction.Dy() = reaction.Dy();
         if ( reaction.Rz() < min_reaction.Rz() )  min_reaction.Rz() = reaction.Rz();

         if ( reaction.Fx() > max_reaction.Fx() )  max_reaction.Fx() = reaction.Fx();
         if ( reaction.Fy() > max_reaction.Fy() )  max_reaction.Fy() = reaction.Fy();
         if ( reaction.Mz() > max_reaction.Mz() )  max_reaction.Mz() = reaction.Mz();
         if ( reaction.Dx() > max_reaction.Dx() )  max_reaction.Dx() = reaction.Dx();
         if ( reaction.Dy() > max_reaction.Dy() )  max_reaction.Dy() = reaction.Dy();
         if ( reaction.Rz() > max_reaction.Rz() )  max_reaction.Rz() = reaction.Rz();
      } // end of while

      // write results
      m_pBridgeModel->WriteReaction( bamReactionKey( support_list[supportIdx], m_MinId ), min_reaction );
      m_pBridgeModel->WriteReaction( bamReactionKey( support_list[supportIdx], m_MaxId ), max_reaction );
   } // end of supportIdx loop

   delete[] support_list;
}

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
