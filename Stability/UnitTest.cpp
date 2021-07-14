///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include <Stability\AnalysisPointImp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Stability;

/****************************************************************************
CLASS
   UnitTest
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool UnitTest::TestMe(dbgLog& rlog)
{
   bool bResult = true;
#if defined _UNITTEST
   ::CoInitialize(0);

   TESTME_PROLOGUE("Stability");

   bResult &= UnitTest::PCILiftingExamples(rlog);
   bResult &= UnitTest::PCIHaulingExamples(rlog);

   TESTME_EPILOG("Stability");

   ::CoUninitialize();
#endif

   return bResult;
}

bool UnitTest::PCILiftingExamples(dbgLog& rlog)
{
   TESTME_PROLOGUE("PCILiftingExamples");

   // Build the basic girder model for the PCI Examples (6.1.x)
   Girder girder;
   Float64 Hg  = ::ConvertToSysUnits(72,unitMeasure::Inch);
   Float64 Wtf = ::ConvertToSysUnits(42,unitMeasure::Inch);
   Float64 Wbf = ::ConvertToSysUnits(26,unitMeasure::Inch);
   
   Float64 Ag = ::ConvertToSysUnits(767,unitMeasure::Inch2);
   Float64 Ix = ::ConvertToSysUnits(545894,unitMeasure::Inch4);
   Float64 Iy = ::ConvertToSysUnits(37634,unitMeasure::Inch4);
   Float64 Ixy = 0;
   Float64 Xleft = Wtf/2;
   Float64 Ytop = ::ConvertToSysUnits(36.6-72,unitMeasure::Inch); // want neg because we are in section coordinates
   Float64 L = ::ConvertToSysUnits(136,unitMeasure::Feet);
   girder.AddSection(L,Ag,Ix,Iy,Ixy,Xleft,Ytop,Hg,Wtf,Wbf);

   matConcreteEx concrete;
   Float64 fci = 5.5;
   concrete.SetFc(::ConvertToSysUnits(fci,unitMeasure::KSI));
   concrete.SetDensity(::ConvertToSysUnits(0.150,unitMeasure::KipPerFeet3));
   concrete.SetDensityForWeight(::ConvertToSysUnits(0.155,unitMeasure::KipPerFeet3));
   Float64 Eci = lrfdConcreteUtil::ModE(concrete.GetType(),concrete.GetFc(), concrete.GetDensity(), false);
   concrete.SetE(Eci);
   concrete.SetFlexureFr(::ConvertToSysUnits(0.24*sqrt(fci),unitMeasure::KSI) );

   LiftingStabilityProblem stabilityProblem;
   stabilityProblem.SetConcrete(concrete);

   stabilityProblem.AddAnalysisPoint(new AnalysisPoint(L*0.4)); // harp point

   // Example 6.1.1
   Float64 fpe = ::ConvertToSysUnits(1232.0,unitMeasure::Kip);
   stabilityProblem.AddFpe(_T("Prestress"),0.0,fpe,Xleft,-Hg + ::ConvertToSysUnits(5.0,unitMeasure::Inch));

   stabilityProblem.SetCamber(::ConvertToSysUnits(2.92,unitMeasure::Inch));

   stabilityProblem.SetSupportLocations(::ConvertToSysUnits(9,unitMeasure::Feet), ::ConvertToSysUnits(9,unitMeasure::Feet));
   stabilityProblem.SetSweepTolerance( 0.000520833333 );
   stabilityProblem.SetSupportPlacementTolerance(::ConvertToSysUnits(0.25,unitMeasure::Inch));
   stabilityProblem.SetLiftAngle(PI_OVER_2);
   stabilityProblem.SetYRollAxis(::ConvertToSysUnits(0.0,unitMeasure::Inch));

   stabilityProblem.SetImpact( 0.0, 0.0 );

   StabilityEngineer engineer;

   LiftingResults result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int j = 0; j < 2; j++ )
      {
         WindDirection wind = (WindDirection)j;

         for(const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind][sectionResult.MinFScrCorner[impact][wind]],1.844,0.001) );

            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][TopLeft    ],unitMeasure::KSI), 0.113,0.001) );
            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][BottomRight],unitMeasure::KSI),-3.290,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind],1.839,0.001) );
      }
   }

   // Example 6.1.1 with eccentric loading due to overhang brackets installed prior to lift
   stabilityProblem.SetAppurtenanceLoading(::ConvertToSysUnits(1.0,unitMeasure::Feet), ::ConvertToSysUnits(0.05,unitMeasure::KipPerFoot));
   result = engineer.AnalyzeLifting(&girder, &stabilityProblem);
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int j = 0; j < 2; j++)
      {
         WindDirection wind = (WindDirection)j;

         for (const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[impact][wind][sectionResult.MinFScrCorner[impact][wind]], 1.235, 0.001));

            TRY_TESTME(::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][TopLeft], unitMeasure::KSI), 0.353, 0.001));
            TRY_TESTME(::IsEqual(::ConvertFromSysUnits(sectionResult.f[impact][wind][BottomRight], unitMeasure::KSI), -3.412, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[impact][wind], 1.470, 0.001));
      }
   }
   stabilityProblem.SetAppurtenanceLoading(0.0, 0.0); // remove eccentric load

   // Example 6.1.2
   stabilityProblem.SetImpact(0,0.20);
   result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int j = 0; j < 2; j++ )
      {
         WindDirection wind = (WindDirection)j;
         for(const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[impact][wind][sectionResult.MinFScrCorner[impact][wind]],impact == ImpactDown ? 1.708 : 1.844,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[impact][wind],impact == ImpactDown ? 1.593 : 1.839,0.001) );
      }
   }

   // Example 6.1.3
   stabilityProblem.SetImpact(0,0);
   stabilityProblem.SetWindLoading(Pressure,::ConvertToSysUnits(2.5,unitMeasure::PSF));
   result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int j = 0; j < 2; j++ )
      {
         WindDirection wind = (WindDirection)j;
         for( const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[impact][wind][TopLeft],  wind == Left ? 2.541 : 1.578, 0.001));
            TRY_TESTME(::IsEqual(sectionResult.FScr[impact][wind][TopRight], Float64_Max, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[impact][wind], wind == Left ? 2.241 : 1.658, 0.001));
         TRY_TESTME(::IsEqual(result.AdjFsFailure[impact][wind], wind == Left ? 2.541 : 1.658, 0.001));
      }
   }

   // Example 6.1.4
   stabilityProblem.SetLiftAngle(M_PI/4);
   result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int j = 0; j < 2; j++ )
      {
         WindDirection wind = (WindDirection)j;
         for(const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[impact][wind][TopLeft], wind == Left ? 2.398 : 1.628, 0.001));
            TRY_TESTME(::IsEqual(sectionResult.FScr[impact][wind][TopRight], Float64_Max, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[impact][wind], wind == Left ? 2.033 : 1.568, 0.001));
         TRY_TESTME(::IsEqual(result.AdjFsFailure[impact][wind], wind == Left ? 2.398 : 1.628, 0.001));
      }
   }

   TESTME_EPILOG("PCILiftingExamples");
}

bool UnitTest::PCIHaulingExamples(dbgLog& rlog)
{
   TESTME_PROLOGUE("PCIHaulingExamples");

   // Build the basic girder model for the PCI Examples (6.2.x)
   Girder girder;
   HaulingStabilityProblem stabilityProblem;
   Float64 Hg  = ::ConvertToSysUnits(72,unitMeasure::Inch);
   Float64 Wtf = ::ConvertToSysUnits(42,unitMeasure::Inch);
   Float64 Wbf = ::ConvertToSysUnits(26,unitMeasure::Inch);
   
   Float64 Ag = ::ConvertToSysUnits(767,unitMeasure::Inch2);
   Float64 Ix = ::ConvertToSysUnits(545894,unitMeasure::Inch4);
   Float64 Iy = ::ConvertToSysUnits(37634,unitMeasure::Inch4);
   Float64 Ixy = 0;
   Float64 Xleft = Wtf/2;
   Float64 Ytop = ::ConvertToSysUnits(36.6-72,unitMeasure::Inch); // want neg because we are in section coordinates
   Float64 L = ::ConvertToSysUnits(136,unitMeasure::Feet);
   girder.AddSection(L,Ag,Ix,Iy, Ixy, Xleft,Ytop,Hg,Wtf,Wbf);

   matConcreteEx concrete;
   Float64 fc = 7.0;
   concrete.SetFc(::ConvertToSysUnits(fc,unitMeasure::KSI));
   concrete.SetDensity(::ConvertToSysUnits(0.150,unitMeasure::KipPerFeet3));
   concrete.SetDensityForWeight(::ConvertToSysUnits(0.155,unitMeasure::KipPerFeet3));
   Float64 Ec = lrfdConcreteUtil::ModE(concrete.GetType(),concrete.GetFc(), concrete.GetDensity(), false);
   concrete.SetE(Ec);
   concrete.SetFlexureFr( ::ConvertToSysUnits(0.24*sqrt(fc),unitMeasure::KSI) );
   stabilityProblem.SetConcrete(concrete);

   stabilityProblem.AddAnalysisPoint(new AnalysisPoint(L*0.4)); // harp point

   // Example 6.2.1
   Float64 fpe = ::ConvertToSysUnits(1251.5,unitMeasure::Kip);
   stabilityProblem.AddFpe(_T("Prestress"),0.0,fpe,Xleft,-Hg + ::ConvertToSysUnits(7.91,unitMeasure::Inch));

   stabilityProblem.SetCamber(::ConvertToSysUnits(2.92,unitMeasure::Inch));


   stabilityProblem.SetSupportLocations(::ConvertToSysUnits(10,unitMeasure::Feet), ::ConvertToSysUnits(10,unitMeasure::Feet));
   stabilityProblem.SetSweepTolerance( 2*0.000520833333 );
   stabilityProblem.SetSweepGrowth(::ConvertToSysUnits(1.0, unitMeasure::Inch));
   stabilityProblem.SetSupportPlacementTolerance(::ConvertToSysUnits(1.0,unitMeasure::Inch));
   stabilityProblem.SetYRollAxis(::ConvertToSysUnits(-48.0,unitMeasure::Inch) - Hg); // location of roll axes below top of girder);

   stabilityProblem.SetImpact( 0.0, 0.0 );
   stabilityProblem.SetImpactUsage(Both);

   stabilityProblem.SetTruckRotationalStiffness(::ConvertToSysUnits(40500.,unitMeasure::KipInchPerRadian));
   stabilityProblem.SetCrownSlope(0.06);
   stabilityProblem.SetSuperelevation(0.06);
   stabilityProblem.SetWheelLineSpacing(::ConvertToSysUnits(72.,unitMeasure::Inch));
   stabilityProblem.SetHeightOfRollAxisAboveRoadway(::ConvertToSysUnits(24.,unitMeasure::Inch));


   StabilityEngineer engineer;

   HaulingResults result = engineer.AnalyzeHauling(&girder,&stabilityProblem);
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int j = 0; j < 2; j++ )
      {
         WindDirection wind = (WindDirection)j;
         for(const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[Superelevation][impact][wind][TopLeft],1.428,0.001) );

            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[Superelevation][impact][wind][TopLeft    ],unitMeasure::KSI), 0.466,0.001) );
            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[Superelevation][impact][wind][BottomRight],unitMeasure::KSI),-3.486,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[Superelevation][impact][wind],2.825,0.001) );
         TRY_TESTME( ::IsEqual(result.FsRollover[Superelevation][impact][wind],1.994,0.001) );
      }
   }


   // Example 6.2.1 with eccentric load due to overhang brackets
   stabilityProblem.SetAppurtenanceLoading(::ConvertToSysUnits(1.0, unitMeasure::Feet), ::ConvertToSysUnits(0.05, unitMeasure::KipPerFoot));
   result = engineer.AnalyzeHauling(&girder, &stabilityProblem);
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int j = 0; j < 2; j++)
      {
         WindDirection wind = (WindDirection)j;
         for (const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[Superelevation][impact][wind][TopLeft], 1.276, 0.001));

            TRY_TESTME(::IsEqual(::ConvertFromSysUnits(sectionResult.f[Superelevation][impact][wind][TopLeft], unitMeasure::KSI), 0.501, 0.001));
            TRY_TESTME(::IsEqual(::ConvertFromSysUnits(sectionResult.f[Superelevation][impact][wind][BottomRight], unitMeasure::KSI), -3.482, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[Superelevation][impact][wind], 2.595, 0.001));
         TRY_TESTME(::IsEqual(result.FsRollover[Superelevation][impact][wind], 1.845, 0.001));
      }
   }
   stabilityProblem.SetAppurtenanceLoading(0.0, 0.0); // remove eccentric load

   // Example 6.2.2
   stabilityProblem.SetTurningRadius(::ConvertToSysUnits(120,unitMeasure::Feet));
   stabilityProblem.SetVelocity(::ConvertToSysUnits(10.,unitMeasure::Mile)/::ConvertToSysUnits(1.0,unitMeasure::Hour));
   stabilityProblem.SetCentrifugalForceType(Adverse);
   stabilityProblem.SetCrownSlope( 0.02 );
   stabilityProblem.SetSuperelevation( 0.02 );
   result = engineer.AnalyzeHauling(&girder,&stabilityProblem);
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int j = 0; j < 2; j++ )
      {
         WindDirection wind = (WindDirection)j;
         for(const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME( ::IsEqual(sectionResult.FScr[Superelevation][impact][wind][TopLeft],0.970,0.001) );

            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[Superelevation][impact][wind][TopLeft    ],unitMeasure::KSI), 0.647,0.001) );
            TRY_TESTME( ::IsEqual(::ConvertFromSysUnits(sectionResult.f[Superelevation][impact][wind][BottomRight],unitMeasure::KSI),-3.598,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[Superelevation][impact][wind],2.787,0.001) );
         TRY_TESTME( ::IsEqual(result.FsRollover[Superelevation][impact][wind],1.835,0.001) );
      }
   }
   TESTME_EPILOG("PCIHaulingExamples");
}