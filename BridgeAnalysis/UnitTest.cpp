///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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

/****************************************************************************
CLASS
   bamUnitTest
****************************************************************************/

#include <BridgeAnalysis\UnitTest.h>

#include <BridgeAnalysis\AxleSpacing.h>
#include <BridgeAnalysis\BridgeModelImp.h>

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined _UNITTEST
bool bridge_model_test(dbgLog& rlog);
#endif // _UNITTEST

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool bamUnitTest::TestMe(dbgLog& rlog)
{
   bool bPassed = true;

#if defined _UNITTEST
   bPassed &= bamAxleSpacing::TestMe(rlog);
   bPassed &= bridge_model_test(rlog);
#endif

   return bPassed;
}

#if defined _UNITTEST
bool bridge_model_test(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamUnitTest - bridge_model_test");

   bamBridgeModelImp model;

   //         1000 N/m   
   //  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
   //  ========================================
   //  ^                                      o
   //  |                                      |
   //  |<-------------- 30.863 m ------------>|

   Float64 w = -1000.;
   Float64 L = 30.863;
   Float64 E = 10;
   Float64 I = 10;
   Float64 A = 10;
   Float64 Density = 10;

   //
   // Build the analysis model
   //

   // Setup the model geometry
   model.CreateSpanElement(0,A,I,E,Density);
   model.CreateSupportElement(1,0.0,Pin);
   model.CreateSupportElement(2,L,HRoller);
   model.ConnectSpanElement(0,1,2);

   // Setup the load case
   Int32 lcid = 1;
   model.CreateLoadCase(lcid);
   
   // Apply the loading
   bamLoadFactory& factory = model.GetLoadFactory();
   factory.CreateUnifForceY(lcid,0,etSpan,0.0,1.0,w,true);

   // Create a live load model
   Int32 llid  = 1;
   Int32 llminId = 2;  // starts with 2 because lcid = 1
   Int32 llmaxId = 3;
   bamLiveLoad ll(llid,llminId,llmaxId);

   bamTruck truck;

   truck.AddAxle(  35000., bamAxleSpacing() );
   truck.AddAxle( 145000., bamAxleSpacing( 4.300, 4.300, bamAxleSpacing::Fixed ) );
   truck.AddAxle( 145000., bamAxleSpacing( 4.300, 9.000, bamAxleSpacing::Bounded ) );

//   truck.AddAxle(  0., bamAxleSpacing() );
//   truck.AddAxle(  0., bamAxleSpacing( 4.300, 4.300, bamAxleSpacing::Fixed ) );
//   truck.AddAxle(  0., bamAxleSpacing( 4.300, 9.000, bamAxleSpacing::Bounded ) );

   ll.AddTruck( truck );
   ll.SetLaneLoad( 9300. );
   ll.SetTruckLoadImpact( 1.33 );
   ll.SetLaneLoadImpact( 1.00 );

   model.AddLiveLoad(ll);

   // Points of interest
   model.GeneratePointsOfInterest(0,11,0);
   Int32 left_end_poi  =  0;
   Int32 mid_span_poi  =  5;
   Int32 right_end_poi = 10;


   //
   // Do the structural analysis
   //
   model.Analyze();

   //
   // Check the reactions, end shears and midspan moment
   //
   bamAnalysisResultsManager* pARM = model.GetAnalysisResultsManager();
   Float64 rot = (w*L*L*L)/(24*E*I);
   Float64 delta = (5*w*L*L*L*L)/(384*E*I);

   // Reactions
   bamReaction left_reaction = pARM->ReadReaction( bamReactionKey(1,lcid) );
   TRY_TESTME( IsEqual(left_reaction.Fx(),0.0) );
   TRY_TESTME( IsEqual(left_reaction.Fy(),-w*L/2) );
   TRY_TESTME( IsEqual(left_reaction.Mz(),0.0) );
   TRY_TESTME( IsEqual(left_reaction.Dx(),0.0) );
   TRY_TESTME( IsEqual(left_reaction.Dy(),0.0) );
   TRY_TESTME( IsEqual(left_reaction.Rz(), rot) );

   bamReaction right_reaction = pARM->ReadReaction( bamReactionKey(2,lcid) );
   TRY_TESTME( IsEqual(right_reaction.Fx(),0.0) );
   TRY_TESTME( IsEqual(right_reaction.Fy(),-w*L/2) );
   TRY_TESTME( IsEqual(right_reaction.Mz(),0.0) );
   TRY_TESTME( IsEqual(right_reaction.Dx(),0.0) );
   TRY_TESTME( IsEqual(right_reaction.Dy(),0.0) );
   TRY_TESTME( IsEqual(right_reaction.Rz(),-rot) );

   // Shears at ends of beam and moments at midspan
   bamSectionResults left_end = pARM->ReadSectionResults(bamSectionResultsKey(left_end_poi,lcid));
   TRY_TESTME( IsEqual(left_end.Fx().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(left_end.Fx().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(left_end.Fy().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(left_end.Fy().Right(),-w*L/2 ) );
   TRY_TESTME( IsEqual(left_end.Mz().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(left_end.Mz().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(left_end.Dx().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(left_end.Dx().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(left_end.Dy().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(left_end.Dy().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(left_end.Rz().Left(),  rot ) );
   TRY_TESTME( IsEqual(left_end.Rz().Right(), rot ) );

   bamSectionResults mid_span = pARM->ReadSectionResults(bamSectionResultsKey(mid_span_poi,lcid));
   TRY_TESTME( IsEqual(mid_span.Fx().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(mid_span.Fx().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(mid_span.Fy().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(mid_span.Fy().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(mid_span.Mz().Left(), -w*L*L/8 ) );
   TRY_TESTME( IsEqual(mid_span.Mz().Right(),-w*L*L/8 ) );
   TRY_TESTME( IsEqual(mid_span.Dx().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(mid_span.Dx().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(mid_span.Dy().Left(),  delta ) );
   TRY_TESTME( IsEqual(mid_span.Dy().Right(), delta ) );
   TRY_TESTME( IsEqual(mid_span.Rz().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(mid_span.Rz().Right(), 0.0 ) );

   bamSectionResults right_end = pARM->ReadSectionResults(bamSectionResultsKey(right_end_poi,lcid));
   TRY_TESTME( IsEqual(right_end.Fx().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(right_end.Fx().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(right_end.Fy().Left(), w*L/2 ) );
   TRY_TESTME( IsEqual(right_end.Fy().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(right_end.Mz().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(right_end.Mz().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(right_end.Dx().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(right_end.Dx().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(right_end.Dy().Left(),  0.0 ) );
   TRY_TESTME( IsEqual(right_end.Dy().Right(), 0.0 ) );
   TRY_TESTME( IsEqual(right_end.Rz().Left(),  -rot ) );
   TRY_TESTME( IsEqual(right_end.Rz().Right(), -rot ) );

   // Check max live load envelope
   bamSectionResults llmax = pARM->ReadSectionResults(bamSectionResultsKey(left_end_poi,llmaxId));
   TRY_TESTME( IsEqual(llmax.Fx().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmax.Fx().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmax.Fy().Left(),   535922., 1.0 ) );
   TRY_TESTME( IsEqual(llmax.Fy().Right(),  535922., 1.0 ) );
   TRY_TESTME( IsEqual(llmax.Mz().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmax.Mz().Right(),       0. ) );

   llmax = pARM->ReadSectionResults(bamSectionResultsKey(mid_span_poi,llmaxId));
   TRY_TESTME( IsEqual(llmax.Fx().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmax.Fx().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmax.Fy().Left(),   212163.,1.0 ) );
   TRY_TESTME( IsEqual(llmax.Fy().Right(),  212163.,1.0 ) );
   TRY_TESTME( IsEqual(llmax.Mz().Left(),  3927733.,1.0 ) );
   TRY_TESTME( IsEqual(llmax.Mz().Right(), 3927733.,1.0 ) );

   llmax = pARM->ReadSectionResults(bamSectionResultsKey(right_end_poi,llmaxId));
   TRY_TESTME( IsEqual(llmax.Fx().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmax.Fx().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmax.Fy().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmax.Fy().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmax.Mz().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmax.Mz().Right(),       0. ) );

   bamSectionResults llmin = pARM->ReadSectionResults(bamSectionResultsKey(left_end_poi,llminId));
   TRY_TESTME( IsEqual(llmin.Fx().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmin.Fx().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmin.Fy().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmin.Fy().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmin.Mz().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmin.Mz().Right(),       0. ) );

   llmin = pARM->ReadSectionResults(bamSectionResultsKey(mid_span_poi,llminId));
   TRY_TESTME( IsEqual(llmin.Fx().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmin.Fx().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmin.Fy().Left(),  -212163.,1.0 ) );
   TRY_TESTME( IsEqual(llmin.Fy().Right(), -212163.,1.0 ) );
   TRY_TESTME( IsEqual(llmin.Mz().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmin.Mz().Right(),       0. ) );

   llmin = pARM->ReadSectionResults(bamSectionResultsKey(right_end_poi,llminId));
   TRY_TESTME( IsEqual(llmin.Fx().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmin.Fx().Right(),       0. ) );
   TRY_TESTME( IsEqual(llmin.Fy().Left(),  -535922.,1.0 ) );
   TRY_TESTME( IsEqual(llmin.Fy().Right(), -535922.,1.0 ) );
   TRY_TESTME( IsEqual(llmin.Mz().Left(),        0. ) );
   TRY_TESTME( IsEqual(llmin.Mz().Right(),       0. ) );

   TESTME_EPILOG("bamUnitTest - bridge_model_test");
}
#endif // _UNITTEST
