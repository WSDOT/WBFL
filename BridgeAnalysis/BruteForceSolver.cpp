///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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

#include <BridgeAnalysis\BruteForceSolver.h>
#include <BridgeAnalysis\BridgeModel.h>
#include <BridgeAnalysis\TransientLdEnvelope.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined _DEBUG
dbgFileDumpContext bamBruteForceSolver::ms_Log(_T("BruteForceDump.txt"));
#define LOG(x) bamBruteForceSolver::ms_Log << x << endl
#else
#define LOG(x)
#endif

bamBruteForceSolver::bamBruteForceSolver() :
bamLiveLoadSolver()
{
}

bamBruteForceSolver::~bamBruteForceSolver()
{
}

void bamBruteForceSolver::Solve(bamLiveLoad& ll)
{
   Int32 pointOfInterestCount;
   Int32* poi_list;
   const bamBridgeModel* p_model = m_pBridgeModel;

   // Get the poi's.  We are going to place every axle of the
   // truck on the poi's
   pointOfInterestCount = p_model->GetPointOfInterestCount();
   poi_list = new Int32[pointOfInterestCount];
   p_model->EnumPointsOfInterest(&poi_list,pointOfInterestCount);

   for (Int32 poiIdx = 0; poiIdx < pointOfInterestCount; poiIdx++)
   {
      Solve(ll,poi_list[poiIdx]);
   }

   SolveReactions( ll );
   delete [] poi_list;
}

void bamBruteForceSolver::Solve(bamLiveLoad& ll,Int32 poi)
{
   LOG("Analyzing poi " << poi);

   Float64 axleOffset;
   Float64 axleWeight;
   Float64 axlePosition;
   Float64 truckPosition;
   Float64 pivotOffset;
   Int32 load_case_id = 0;
   Int32 moment_load_case_id;
   Int32 shear_load_case_id1;
   Int32 shear_load_case_id2;
   Int32 spanElementId;
   Float64 offset;
   Float64 absLoc;
   Float64 lane_impact;
   Float64 truck_impact;
   Float64 span_length;
   const bamBridgeModel* p_model = m_pBridgeModel;

   lane_impact  = ll.GetLaneLoadImpact();
   truck_impact = ll.GetTruckLoadImpact();
   
   // We are going to do all of the live load work on a copy
   // of the original model. This copy is just geometry, not loads
   std::auto_ptr<bamBridgeModel>my_model( p_model->Clone() );
   bamLoadFactory& factory = my_model->GetLoadFactory();

   // Use the envelope feature to get the extreme force effects
   Int32 envelope_id = load_case_id++;
   Int32 env_min = load_case_id++;
   Int32 env_max = load_case_id++;
   bamTransientLdEnvelope envelope(envelope_id);

   // Run the trucks up and down the bridge, generating load cases
   for (Int32 direction = 0; direction < 2; direction++)
   {
      LOG(_T("Direction = ") << (direction == 0 ? _T("Forward") : _T("Backwards")));

      p_model->GetPointOfInterest(poi, spanElementId, offset, absLoc);

      const bamSpanElement* pSE = p_model->GetSpanElement( spanElementId );
      span_length = pSE->Length();

      truckPosition = absLoc;

      LOG(_T("****************************************************"));
      LOG(_T("Point of Interest = ") << poi << _T(" Span = ") << spanElementId << _T(" Offset = ") << offset );

      for (Int32 pivotAxle = 0; pivotAxle < ll.GetNumAxles(); pivotAxle++ )
      {
         ll.GetAxle(pivotAxle,pivotOffset,axleWeight);
         if (direction == 1)
         {
            // Reverse the axle positions
            pivotOffset *= -1;
         }

         moment_load_case_id = load_case_id++;
         my_model->CreateLoadCase(moment_load_case_id);
         LOG(_T("Moment Load Case = ") << moment_load_case_id);
         envelope.AddLoading( moment_load_case_id );

         shear_load_case_id1 = load_case_id++;
         my_model->CreateLoadCase(shear_load_case_id1);
         shear_load_case_id2 = load_case_id++;
         my_model->CreateLoadCase(shear_load_case_id2 );
         LOG(_T("Shear Load Cases = ") << shear_load_case_id1 << _T(",") << shear_load_case_id2);
         envelope.AddLoading( shear_load_case_id1 );
         envelope.AddLoading( shear_load_case_id2 );

         // Apply lane load
         // For moment, apply to entire span
         factory.CreateUnifForceY(moment_load_case_id,spanElementId,etSpan,0.00,1.00, -ll.GetLaneLoad() * lane_impact ,true);

         // For shear, apply upto the current poi
         Float64 fra;
         Float64 start,end;
         fra = offset / span_length;
         start = ( direction == 0 ) ? 0.0 : fra;
         end   = ( direction == 0 ) ? fra : 1.0;
         LOG(_T("Shear Lane Load for load case ") << shear_load_case_id1);
         LOG(_T("   Start = ") << start );
         LOG(_T("   End   = ") << end );
         factory.CreateUnifForceY(shear_load_case_id1,spanElementId,etSpan,start,end, -ll.GetLaneLoad() * lane_impact ,true);
         start = ( direction == 0 ) ? fra : 0.0;
         end   = ( direction == 0 ) ? 1.0 : fra;
         LOG(_T("Shear Lane Load for load case ") << shear_load_case_id2);
         LOG(_T("   Start = ") << start );
         LOG(_T("   End   = ") << end );
         factory.CreateUnifForceY(shear_load_case_id2,spanElementId,etSpan,start,end, -ll.GetLaneLoad() * lane_impact ,true);

         // Apply axle loads
         for (Int32 axle = 0; axle < ll.GetNumAxles(); axle++)
         {
            ll.GetAxle(axle,axleOffset,axleWeight);

            if (direction == 1)
            {
               // Reverse the axle positions
               axleOffset *= -1;
            }

            axlePosition = truckPosition - axleOffset + pivotOffset;

            // When the axles are right on the end of the span, the
            // shear envelopes don't come out right. Offset them slightly
            if ( IsZero(axlePosition) )
               axlePosition += 0.0001;

            if ( IsEqual(axlePosition,my_model->GetSpanLength(spanElementId)) )
               axlePosition -= 0.0001;
            
            if (IsZero(axlePosition) || (0 < axlePosition && axlePosition < my_model->GetSpanLength(spanElementId)) || IsEqual(axlePosition,my_model->GetSpanLength(spanElementId)))
            {
               // Axle is on the bridge
               //TRACE("POI = %u dir = %u PivotAxle = %u Axle = %u Axle Position = %f Axle Weight %f\n",poi,direction,pivotAxle,axle,axlePosition,axleWeight);
               LOG(_T("Pivot Axle = ") << pivotAxle << _T(" Axle Position = ") << axlePosition << _T(" Axle Weight = ") << axleWeight);
               factory.CreateConcForceY(moment_load_case_id,spanElementId,etSpan,axlePosition, -axleWeight * truck_impact, false);
               factory.CreateConcForceY(shear_load_case_id1,spanElementId,etSpan,axlePosition, -axleWeight * truck_impact, false);
               factory.CreateConcForceY(shear_load_case_id2,spanElementId,etSpan,axlePosition, -axleWeight * truck_impact, false);
            } // end of if

         } // end of loop : axle

         LOG( _T(" ") );
      } // end of loop : pivot axle
   } // end of loop : direction


   // Create and envelope and stick it in the model
   envelope.SetLoadingIds(env_min,env_max);
   my_model->AddEnvelope(envelope);
   const bamEnvelope* e = my_model->GetEnvelope( envelope_id );

   LOG(_T("Envelope loading id's"));
   LOG(_T( "Min Envelope : ") << e->GetLoadingId( bamEnvelope::Min ) );
   LOG( _T("Max Envelope : ") << e->GetLoadingId( bamEnvelope::Max ) );

   // Do the structural analysis
   my_model->Analyze();

   // Collect results for the cloned model and write them
   // into the original model.
   LOG(_T("********************************************************"));
   LOG(_T("Live Load Envelopes"));

   for ( Int16 i = bamEnvelope::Min; i <= bamEnvelope::Max; i++ )
   {
      LOG(_T(""));
      LOG(_T("Extreme Value Type : ") << (i == bamEnvelope::Min ? _T("Min") : _T("Max") ));

      bamSectionResults sr;

      bamSectionResultsKey from_key( poi, e->GetLoadingId( (bamEnvelope::ExtremeValueType)(i) ) );
      sr = my_model->ReadSectionResults( from_key );
      
      Int32 llid = (i == bamEnvelope::Min ? ll.GetMinLoadingId() : ll.GetMaxLoadingId() );
      bamSectionResultsKey to_key( poi, llid );
      WriteSectionResults( to_key, sr );

      LOG(_T("Loading ") << to_key.LoadingId());
      LOG(_T("POI     ") << to_key.PointOfInterest());
      LOG(_T("Fx      ") << sr.Fx());
      LOG(_T("Fy      ") << sr.Fy());
      LOG(_T("Mz      ") << sr.Mz());
      LOG(_T("Dx      ") << sr.Dx());
      LOG(_T("Dy      ") << sr.Dy());
      LOG(_T("Rz      ") << sr.Rz());

      // For this poi, get the bamPointOfInterest object.  
      // Iterate over each stress point, moving the results from one
      // model to the other.
      const bamPointOfInterest* p_Poi = my_model->GetPointOfInterest( poi );
      CHECK( p_Poi != 0 );
      std::set<bamStressPoint>::const_iterator j;
      for ( j = p_Poi->m_StressPoints.begin(); j != p_Poi->m_StressPoints.end(); j++ )
      {
         const bamStressPoint& stress_point = *j;
         bamSectionStressKey ss_from_key( poi, stress_point.m_ID, e->GetLoadingId( (bamEnvelope::ExtremeValueType)(i) ) );
         bamSectionStress ss = my_model->ReadSectionStress( ss_from_key );

         bamSectionStressKey ss_to_key( poi, stress_point.m_ID, (i==bamEnvelope::Min?ll.GetMinLoadingId():ll.GetMaxLoadingId()) );
         WriteSectionStress( ss_to_key, ss );
      }
   }
   LOG(" ");
}

void bamBruteForceSolver::SolveReactions(bamLiveLoad& ll)
{
   Float64 axleOffset;
   Float64 axleWeight;
   Float64 axlePosition;
   Float64 truckPosition;
   Int32 left_lc_id = 1;
   Int32 right_lc_id = 2;

   Float64 lane_impact;
   Float64 truck_impact;
   Float64 span_length;

   const bamBridgeModel* p_model = m_pBridgeModel;

   Int16 spanElementId = 0;
   const bamSpanElement* pSE = p_model->GetSpanElement( spanElementId );
   span_length = pSE->Length();

   lane_impact  = ll.GetLaneLoadImpact();
   truck_impact = ll.GetTruckLoadImpact();
   
   // We are going to do all of the live load work on a copy
   // of the original model. This copy is just geometry, not loads
   std::auto_ptr<bamBridgeModel>my_model( p_model->Clone() );
   bamLoadFactory& factory = my_model->GetLoadFactory();

   // Use the envelope feature to get the extreme force effects
   Int32 envelope_id = 0;
   Int32 env_min = 4;
   Int32 env_max = 5;
   bamTransientLdEnvelope envelope(envelope_id);

   // Put the truck at the left end of the span (maximum left reaction)
   my_model->CreateLoadCase(left_lc_id);
   LOG(_T("Left Reaction Load Case = ") << left_lc_id);
   envelope.AddLoading( left_lc_id );
      
   // Apply lane load
   factory.CreateUnifForceY(left_lc_id,spanElementId,etSpan,0.00,1.00, -ll.GetLaneLoad() * lane_impact ,true);

   // Apply the truck load
   truckPosition = ll.GetMinLength();
   for (Int32 axle = 0; axle < ll.GetNumAxles(); axle++)
   {
      ll.GetAxle(axle,axleOffset,axleWeight);
      axlePosition = truckPosition - axleOffset;

      // When the axles are right on the end of the span, the
      // shear envelopes don't come out right. Offset them slightly
      if ( IsZero(axlePosition) )
         axlePosition += 0.0001;

      if ( IsEqual(axlePosition,my_model->GetSpanLength(spanElementId)) )
         axlePosition -= 0.0001;
      
      if (IsZero(axlePosition) || (0 < axlePosition && axlePosition < my_model->GetSpanLength(spanElementId)) || IsEqual(axlePosition,my_model->GetSpanLength(spanElementId)))
      {
         // Axle is on the bridge
         LOG(_T("Axle Position = ") << axlePosition << _T(" Axle Weight = ") << axleWeight);
         factory.CreateConcForceY(left_lc_id,spanElementId,etSpan,axlePosition, -axleWeight * truck_impact, false);
      } // end of if

   } // end of loop : axle

   LOG( _T(" ") );


   // Put the truck at the right end of the span (maximum right reaction)
   my_model->CreateLoadCase(right_lc_id);
   LOG(_T("Right Reaction Load Case = ") << right_lc_id);
   envelope.AddLoading( right_lc_id );
      
   // Apply lane load
   factory.CreateUnifForceY(right_lc_id,spanElementId,etSpan,0.00,1.00, -ll.GetLaneLoad() * lane_impact ,true);

   // Apply the truck load
   truckPosition = span_length - ll.GetMinLength();
   for (long axle = 0; axle < ll.GetNumAxles(); axle++)
   {
      ll.GetAxle(axle,axleOffset,axleWeight);
      axleOffset *= -1; // reverse direction
      axlePosition = truckPosition - axleOffset;

      // When the axles are right on the end of the span, the
      // shear envelopes don't come out right. Offset them slightly
      if ( IsZero(axlePosition) )
         axlePosition += 0.0001;

      if ( IsEqual(axlePosition,my_model->GetSpanLength(spanElementId)) )
         axlePosition -= 0.0001;
      
      if (IsZero(axlePosition) || (0 < axlePosition && axlePosition < my_model->GetSpanLength(spanElementId)) || IsEqual(axlePosition,my_model->GetSpanLength(spanElementId)))
      {
         // Axle is on the bridge
         LOG(_T("Axle Position = ") << axlePosition << _T(" Axle Weight = ") << axleWeight);
         factory.CreateConcForceY(right_lc_id,spanElementId,etSpan,axlePosition, -axleWeight * truck_impact, false);
      } // end of if

   } // end of loop : axle

   LOG( _T(" ") );

   // Create and envelope and stick it in the model
   envelope.SetLoadingIds(env_min,env_max);
   my_model->AddEnvelope(envelope);
   const bamEnvelope* e = my_model->GetEnvelope( envelope_id );

   LOG(_T("Envelope loading id's"));
   LOG( _T("Min Envelope : ") << e->GetLoadingId( bamEnvelope::Min ) );
   LOG( _T("Max Envelope : ") << e->GetLoadingId( bamEnvelope::Max ) );

   // Do the structural analysis
   my_model->Analyze();

   // Get reactions that corrospond to the extreme force effects.
   LOG(_T("********************************************************"));
   LOG(_T("Live Load Reactions"));

   Int32 support_count;
   Int32* support_list;
   support_count = my_model->GetSupportElementCount();
   support_list = new Int32[support_count];
   my_model->EnumSupportElements(&support_list,support_count);

   for ( Int16 j = bamEnvelope::Min; j <= bamEnvelope::Max; j++ )
   {
      LOG(_T(""));
      LOG(_T("Extreme Value Type : ") << (j == bamEnvelope::Min ? _T("Min") : _T("Max") ));
      LOG(_T("Support Fx Fy Mz"));
      for (Int32 supportIdx = 0; supportIdx < support_count; supportIdx++)
      {
         bamReactionKey from_key( support_list[supportIdx], e->GetLoadingId( (bamEnvelope::ExtremeValueType)(j) ) );
         bamReaction reaction = my_model->ReadReaction( from_key );
         bamReactionKey to_key( support_list[supportIdx], (j==bamEnvelope::Min?ll.GetMinLoadingId():ll.GetMaxLoadingId()) );

         LOG(supportIdx << _T(" ") << reaction.Fx() << _T(" ") << reaction.Fy() << _T(" ") << reaction.Mz() );

         WriteReaction( to_key, reaction );
      }
   }

   delete[] support_list;
}

void bamBruteForceSolver::SolveStress(bamLiveLoad& ll,Int32 poi,Int32 spid)
{
   const bamPointOfInterest* pPoi = m_pBridgeModel->GetPointOfInterest( poi );
   bamStressPoint find_me;
   find_me.m_ID;
   std::set<bamStressPoint>::const_iterator found;
   found = pPoi->m_StressPoints.find( find_me );
   const bamStressPoint& sp = *found;

   bamSectionResults srMin = ReadSectionResults( bamSectionResultsKey(poi,ll.GetMinLoadingId()) );
   bamSectionResults srMax = ReadSectionResults( bamSectionResultsKey(poi,ll.GetMaxLoadingId()) );
   bamSectionStress fmin( srMin.Mz() / sp.m_S );
   bamSectionStress fmax( srMax.Mz() / sp.m_S );

   WriteSectionStress( bamSectionStressKey(poi,sp.m_ID,ll.GetMinLoadingId()), fmin );
   WriteSectionStress( bamSectionStressKey(poi,sp.m_ID,ll.GetMaxLoadingId()), fmax );
}
