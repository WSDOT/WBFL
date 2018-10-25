///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2016  Washington State Department of Transportation
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

#include <Stability\StabilityLib.h>
#include <Stability\UnitTest.h>
#include <Units\Units.h>
#include <Stability\StabilityEngineer.h>
#include <Stability\StabilityProblemImp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   stbUnitTest
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool stbUnitTest::TestMe(dbgLog& rlog)
{
   bool bResult = true;
#if defined _UNITTEST
   ::CoInitialize(0);

   TESTME_PROLOGUE("Stability");

   bResult &= stbUnitTest::PCILiftingExamples(rlog);
   bResult &= stbUnitTest::PCIHaulingExamples(rlog);

   TESTME_EPILOG("Stability");

   ::CoUninitialize();
#endif

   return bResult;
}

bool stbUnitTest::PCILiftingExamples(dbgLog& rlog)
{
   TESTME_PROLOGUE("PCILiftingExamples");

   // Build the basic girder model for the PCI Examples (6.1.x)
   stbGirder girder;
   Float64 Hg  = ::ConvertToSysUnits(72,unitMeasure::Inch);
   Float64 Wtf = ::ConvertToSysUnits(42,unitMeasure::Inch);
   Float64 Wbf = ::ConvertToSysUnits(26,unitMeasure::Inch);
   
   Float64 Ag = ::ConvertToSysUnits(767,unitMeasure::Inch2);
   Float64 Ix = ::ConvertToSysUnits(545894,unitMeasure::Inch4);
   Float64 Iy = ::ConvertToSysUnits(37634,unitMeasure::Inch4);
   Float64 Yt = ::ConvertToSysUnits(36.6-72,unitMeasure::Inch); // want neg because we are in section coordinates
   Float64 L = ::ConvertToSysUnits(136,unitMeasure::Feet);
   girder.AddSection(L,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf);

   girder.SetDensity(::ConvertToSysUnits(0.155,unitMeasure::KipPerFeet3));

   stbLiftingStabilityProblem stabilityProblem;
   stabilityProblem.AddAnalysisPoint(L*0.4); // harp point

   // Example 6.1.1
   Float64 fpe = ::ConvertToSysUnits(1232.0,unitMeasure::Kip);
   stabilityProblem.AddFpe(0,0,fpe,0);
   girder.SetHarpedStrandLocation(0.0,       -Hg + ::ConvertToSysUnits(5.0,unitMeasure::Inch),
                                  0.4*L,     -Hg + ::ConvertToSysUnits(5.0,unitMeasure::Inch),
                                  (1-0.4)*L, -Hg + ::ConvertToSysUnits(5.0,unitMeasure::Inch),
                                  L,         -Hg + ::ConvertToSysUnits(5.0,unitMeasure::Inch));

   stabilityProblem.SetCamber(true,::ConvertToSysUnits(2.92,unitMeasure::Inch));

   stabilityProblem.SetFr( ::ConvertToSysUnits(0.24*sqrt(5.5),unitMeasure::KSI) );
   stabilityProblem.SetEc( ::ConvertToSysUnits(4765.97,unitMeasure::KSI) );

   stabilityProblem.SetSupportLocations(::ConvertToSysUnits(9,unitMeasure::Feet), ::ConvertToSysUnits(9,unitMeasure::Feet));
   stabilityProblem.SetSweepTolerance( 0.000520833333 );
   stabilityProblem.SetSupportPlacementTolerance(::ConvertToSysUnits(0.25,unitMeasure::Inch));
   stabilityProblem.SetLiftAngle(PI_OVER_2);
   stabilityProblem.SetYRollAxis(::ConvertToSysUnits(0.0,unitMeasure::Inch));

   stabilityProblem.SetImpact( 0.0, 0.0 );
   stabilityProblem.ApplyImpactToTiltedGirder(true);
   stabilityProblem.SetWindPressure( 0.0 );

   stbStabilityEngineer engineer;

   stbLiftingResults result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int impact = 0; impact < 3; impact++ )
   {
      for ( int wind = 0; wind < 2; wind++ )
      {
         BOOST_FOREACH(stbLiftingSectionResult& sectionResult,result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind],1.850,0.001) );

            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][TOP_LEFT    ],unitMeasure::KSI), 0.113,0.001) );
            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][BOTTOM_RIGHT],unitMeasure::KSI),-3.290,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind],1.847,0.001) );
      }
   }

   // Example 6.1.2
   stabilityProblem.SetImpact(0,0.20);
   result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int impact = 0; impact < 3; impact++ )
   {
      for ( int wind = 0; wind < 2; wind++ )
      {
         BOOST_FOREACH(stbLiftingSectionResult& sectionResult,result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind],impact == IMPACT_DOWN ? 1.714 : 1.850,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind],impact == IMPACT_DOWN ? 1.600 : 1.847,0.001) );
      }
   }

   // Example 6.1.3
   stabilityProblem.SetImpact(0,0);
   stabilityProblem.SetWindPressure(::ConvertToSysUnits(2.5,unitMeasure::PSF));
   result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int impact = 0; impact < 3; impact++ )
   {
      for ( int wind = 0; wind < 2; wind++ )
      {
         BOOST_FOREACH(stbLiftingSectionResult& sectionResult,result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind],wind == LEFT ? 2.556 : 1.196/*1.581*/,0.001) );
            TRY_TESTME( sectionResult.CrackedFlange[impact][wind] == (wind == LEFT ? TOP_LEFT : TOP_RIGHT) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind],wind == LEFT ? 2.516 : 1.546,0.001) );
      }
   }

   // Example 6.1.4
   stabilityProblem.SetLiftAngle(M_PI/4);
   result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int impact = 0; impact < 3; impact++ )
   {
      for ( int wind = 0; wind < 2; wind++ )
      {
         BOOST_FOREACH(stbLiftingSectionResult& sectionResult,result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind],wind == LEFT ? 2.425/*2.413*/ : 1.349/*1.633*/,0.001) );
            TRY_TESTME( sectionResult.CrackedFlange[impact][wind] == (wind == LEFT ? TOP_LEFT : TOP_RIGHT) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind],wind == LEFT ? 2.425/*2.259*/ : 1.471/*1.468*/,0.001) );
      }
   }

   TESTME_EPILOG("PCILiftingExamples");
}

bool stbUnitTest::PCIHaulingExamples(dbgLog& rlog)
{
   TESTME_PROLOGUE("PCIHaulingExamples");

   // Build the basic girder model for the PCI Examples (6.2.x)
   stbGirder girder;
   stbHaulingStabilityProblem stabilityProblem;
   Float64 Hg  = ::ConvertToSysUnits(72,unitMeasure::Inch);
   Float64 Wtf = ::ConvertToSysUnits(42,unitMeasure::Inch);
   Float64 Wbf = ::ConvertToSysUnits(26,unitMeasure::Inch);
   
   Float64 Ag = ::ConvertToSysUnits(767,unitMeasure::Inch2);
   Float64 Ix = ::ConvertToSysUnits(545894,unitMeasure::Inch4);
   Float64 Iy = ::ConvertToSysUnits(37634,unitMeasure::Inch4);
   Float64 Yt = ::ConvertToSysUnits(36.6-72,unitMeasure::Inch); // want neg because we are in section coordinates
   Float64 L = ::ConvertToSysUnits(136,unitMeasure::Feet);
   girder.AddSection(L,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf);

   girder.SetDensity(::ConvertToSysUnits(0.155,unitMeasure::KipPerFeet3));

   stabilityProblem.AddAnalysisPoint(L*0.4); // harp point

   // Example 6.2.1
   Float64 fpe = ::ConvertToSysUnits(1251.5,unitMeasure::Kip);
   stabilityProblem.AddFpe(0,0,fpe,0);
   girder.SetHarpedStrandLocation(0.0,       -Hg + ::ConvertToSysUnits(7.91,unitMeasure::Inch),
                                  0.4*L,     -Hg + ::ConvertToSysUnits(7.91,unitMeasure::Inch),
                                  (1-0.4)*L, -Hg + ::ConvertToSysUnits(7.91,unitMeasure::Inch),
                                  L,         -Hg + ::ConvertToSysUnits(7.91,unitMeasure::Inch));

   stabilityProblem.SetCamber(true,::ConvertToSysUnits(2.92,unitMeasure::Inch));

   stabilityProblem.SetFr( ::ConvertToSysUnits(0.24*sqrt(7.0),unitMeasure::KSI) );
   stabilityProblem.SetEc( ::ConvertToSysUnits(5164.914,unitMeasure::KSI) );

   stabilityProblem.SetSupportLocations(::ConvertToSysUnits(10,unitMeasure::Feet), ::ConvertToSysUnits(10,unitMeasure::Feet));
   stabilityProblem.SetSweepTolerance( 2*0.000520833333 );
   stabilityProblem.SetSupportPlacementTolerance(::ConvertToSysUnits(1.0,unitMeasure::Inch));
   stabilityProblem.SetYRollAxis(::ConvertToSysUnits(-48.0,unitMeasure::Inch) - Hg); // location of roll axes below top of girder);

   stabilityProblem.SetImpact( 0.0, 0.0 );
   stabilityProblem.ApplyImpactToTiltedGirder(false);
   stabilityProblem.SetWindPressure( 0.0 );

   stabilityProblem.SetTruckRotationalStiffness(::ConvertToSysUnits(40500.,unitMeasure::KipInchPerRadian));
   stabilityProblem.SetSuperelevation(0.06);
   stabilityProblem.SetWheelLineSpacing(::ConvertToSysUnits(72.,unitMeasure::Inch));
   stabilityProblem.SetHeightOfRollAxisAboveRoadway(::ConvertToSysUnits(24.,unitMeasure::Inch));


   stbStabilityEngineer engineer;

   stbHaulingResults result = engineer.AnalyzeHauling(&girder,&stabilityProblem);
   for ( int impact = 0; impact < 3; impact++ )
   {
      for ( int wind = 0; wind < 2; wind++ )
      {
         for ( int cf = 0; cf < 2; cf++ )
         {
            BOOST_FOREACH(stbHaulingSectionResult& sectionResult,result.vSectionResults)
            {
               TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind][cf],1.476/*1.429*/,0.001) );

               TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][cf][TOP_LEFT    ],unitMeasure::KSI), 0.453/*0.466*/,0.001) );
               TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][cf][BOTTOM_RIGHT],unitMeasure::KSI),-3.478/*-3.486*/,0.001) );
            }

            TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind][cf],2.854/*2.857*/,0.001) );
            TRY_TESTME( ::IsEqual(result.FsRollover[impact][wind][cf],2.016/*1.986*/,0.001) );
         }
      }
   }

   // Example 6.2.2
   stabilityProblem.SetTurningRadius(::ConvertToSysUnits(120,unitMeasure::Feet));
   stabilityProblem.SetVelocity(::ConvertToSysUnits(10.,unitMeasure::Mile)/::ConvertToSysUnits(1.0,unitMeasure::Hour));
   stabilityProblem.SetSuperelevation( 0.02 );
   result = engineer.AnalyzeHauling(&girder,&stabilityProblem);
   for ( int impact = 0; impact < 3; impact++ )
   {
      for ( int wind = 0; wind < 2; wind++ )
      {
         for ( int cf = 0; cf < 2; cf++ )
         {
            if ( cf == LEFT ) 
            {
            BOOST_FOREACH(stbHaulingSectionResult& sectionResult,result.vSectionResults)
            {
               TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind][cf],1.002/*0.970*/,0.001) );

               TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][cf][TOP_LEFT    ],unitMeasure::KSI), 0.634/*0.647*/,0.001) );
               TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][cf][BOTTOM_RIGHT],unitMeasure::KSI),-3.590/*-3.598*/,0.001) );
            }

            TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind][cf],2.813/*2.824*/,0.001) );
            TRY_TESTME( ::IsEqual(result.FsRollover[impact][wind][cf],1.903/*1.868*/,0.001) );
            }
         }
      }
   }
   TESTME_EPILOG("PCIHaulingExamples");
}