///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Stability/StabilityLib.h>
#include <Stability/UnitTest.h>
#include <Units\Units.h>
#include <Stability/StabilityEngineer.h>
#include <Stability/StabilityProblemImp.h>
#include <Stability/AnalysisPointImp.h>

using namespace WBFL::Stability;

bool UnitTest::TestMe(WBFL::Debug::Log& rlog)
{
   bool bResult = true;
#if defined _UNITTEST
   ::CoInitialize(0);

   TESTME_PROLOGUE("Stability");

   bResult &= UnitTest::PCILiftingExamples(rlog);
   bResult &= UnitTest::PCIHaulingExamples(rlog);
   bResult &= UnitTest::OneEndSeated(rlog);

   TESTME_EPILOG("Stability");

   ::CoUninitialize();
#endif

   return bResult;
}

bool UnitTest::PCILiftingExamples(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCILiftingExamples");

   // Build the basic girder model for the PCI Examples (6.1.x)
   Girder girder;
   Float64 Hg  = WBFL::Units::ConvertToSysUnits(72,WBFL::Units::Measure::Inch);
   Float64 Wtf = WBFL::Units::ConvertToSysUnits(42,WBFL::Units::Measure::Inch);
   Float64 Wbf = WBFL::Units::ConvertToSysUnits(26,WBFL::Units::Measure::Inch);
   
   Float64 Ag = WBFL::Units::ConvertToSysUnits(767,WBFL::Units::Measure::Inch2);
   Float64 Ix = WBFL::Units::ConvertToSysUnits(545894,WBFL::Units::Measure::Inch4);
   Float64 Iy = WBFL::Units::ConvertToSysUnits(37634,WBFL::Units::Measure::Inch4);
   Float64 Ixy = 0;
   Float64 Xleft = Wtf/2;
   Float64 Ytop = WBFL::Units::ConvertToSysUnits(36.6-72,WBFL::Units::Measure::Inch); // want neg because we are in section coordinates
   Float64 L = WBFL::Units::ConvertToSysUnits(136,WBFL::Units::Measure::Feet);
   girder.AddSection(L,Ag,Ix,Iy,Ixy,Xleft,Ytop,Hg,Wtf,Wbf);

   WBFL::Materials::SimpleConcrete concrete;
   Float64 fci = 5.5;
   concrete.SetFc(WBFL::Units::ConvertToSysUnits(fci,WBFL::Units::Measure::KSI));
   concrete.SetDensity(WBFL::Units::ConvertToSysUnits(0.150,WBFL::Units::Measure::KipPerFeet3));
   concrete.SetDensityForWeight(WBFL::Units::ConvertToSysUnits(0.155,WBFL::Units::Measure::KipPerFeet3));
   Float64 Eci = lrfdConcreteUtil::ModE(concrete.GetType(),concrete.GetFc(), concrete.GetDensity(), false);
   concrete.SetE(Eci);
   concrete.SetFlexureFr(WBFL::Units::ConvertToSysUnits(0.24*sqrt(fci),WBFL::Units::Measure::KSI) );

   LiftingStabilityProblem stabilityProblem;
   stabilityProblem.SetConcrete(concrete);

   stabilityProblem.AddAnalysisPoint(std::move(std::make_unique<AnalysisPoint>(0.4 * L))); // harp point

   // Example 6.1.1
   Float64 fpe = WBFL::Units::ConvertToSysUnits(1232.0,WBFL::Units::Measure::Kip);
   stabilityProblem.AddFpe(_T("Prestress"),0.0,fpe,Xleft,-Hg + WBFL::Units::ConvertToSysUnits(5.0,WBFL::Units::Measure::Inch));

   stabilityProblem.SetCamber(WBFL::Units::ConvertToSysUnits(2.92,WBFL::Units::Measure::Inch));

   stabilityProblem.SetSupportLocations(WBFL::Units::ConvertToSysUnits(9,WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(9,WBFL::Units::Measure::Feet));
   stabilityProblem.SetSweepTolerance( 0.000520833333 );
   stabilityProblem.SetSupportPlacementTolerance(WBFL::Units::ConvertToSysUnits(0.25,WBFL::Units::Measure::Inch));
   stabilityProblem.SetLiftAngle(PI_OVER_2);
   stabilityProblem.SetYRollAxis(WBFL::Units::ConvertToSysUnits(0.0,WBFL::Units::Measure::Inch));

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
            TRY_TESTME( ::IsEqual(sectionResult.FScr[+impact][+wind][+sectionResult.MinFScrCorner[+impact][+wind]],1.844,0.001) );

            TRY_TESTME( ::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::TopLeft    ],WBFL::Units::Measure::KSI), 0.113,0.001) );
            TRY_TESTME( ::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::BottomRight],WBFL::Units::Measure::KSI),-3.290,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[+impact][+wind],1.839,0.001) );
      }
   }

   // Example 6.1.1 with eccentric loading due to overhang brackets installed prior to lift
   stabilityProblem.SetAppurtenanceLoading(WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(0.05,WBFL::Units::Measure::KipPerFoot));
   result = engineer.AnalyzeLifting(&girder, &stabilityProblem);
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int j = 0; j < 2; j++)
      {
         WindDirection wind = (WindDirection)j;

         for (const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[+impact][+wind][+sectionResult.MinFScrCorner[+impact][+wind]], 1.235, 0.001));

            TRY_TESTME(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.353, 0.001));
            TRY_TESTME(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.412, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[+impact][+wind], 1.470, 0.001));
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
            TRY_TESTME( ::IsEqual(sectionResult.FScr[+impact][+wind][+sectionResult.MinFScrCorner[+impact][+wind]],impact == ImpactDirection::ImpactDown ? 1.708 : 1.844,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[+impact][+wind],impact == ImpactDirection::ImpactDown ? 1.593 : 1.839,0.001) );
      }
   }

   // Example 6.1.3
   stabilityProblem.SetImpact(0,0);
   stabilityProblem.SetWindLoading(WindType::Pressure,WBFL::Units::ConvertToSysUnits(2.5,WBFL::Units::Measure::PSF));
   result = engineer.AnalyzeLifting(&girder,&stabilityProblem);
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for ( int j = 0; j < 2; j++ )
      {
         WindDirection wind = (WindDirection)j;
         for( const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopLeft],  wind == WindDirection::Left ? 2.541 : 1.578, 0.001));
            TRY_TESTME(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopRight], Float64_Max, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[+impact][+wind], wind == WindDirection::Left ? 2.241 : 1.658, 0.001));
         TRY_TESTME(::IsEqual(result.AdjFsFailure[+impact][+wind], wind == WindDirection::Left ? 2.541 : 1.658, 0.001));
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
            TRY_TESTME(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopLeft], wind == WindDirection::Left ? 2.398 : 1.628, 0.001));
            TRY_TESTME(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopRight], Float64_Max, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[+impact][+wind], wind == WindDirection::Left ? 2.033 : 1.568, 0.001));
         TRY_TESTME(::IsEqual(result.AdjFsFailure[+impact][+wind], wind == WindDirection::Left ? 2.398 : 1.628, 0.001));
      }
   }

   TESTME_EPILOG("PCILiftingExamples");
}

bool UnitTest::PCIHaulingExamples(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIHaulingExamples");

   // Build the basic girder model for the PCI Examples (6.2.x)
   Girder girder;
   HaulingStabilityProblem stabilityProblem;
   Float64 Hg  = WBFL::Units::ConvertToSysUnits(72,WBFL::Units::Measure::Inch);
   Float64 Wtf = WBFL::Units::ConvertToSysUnits(42,WBFL::Units::Measure::Inch);
   Float64 Wbf = WBFL::Units::ConvertToSysUnits(26,WBFL::Units::Measure::Inch);
   
   Float64 Ag = WBFL::Units::ConvertToSysUnits(767,WBFL::Units::Measure::Inch2);
   Float64 Ix = WBFL::Units::ConvertToSysUnits(545894,WBFL::Units::Measure::Inch4);
   Float64 Iy = WBFL::Units::ConvertToSysUnits(37634,WBFL::Units::Measure::Inch4);
   Float64 Ixy = 0;
   Float64 Xleft = Wtf/2;
   Float64 Ytop = WBFL::Units::ConvertToSysUnits(36.6-72,WBFL::Units::Measure::Inch); // want neg because we are in section coordinates
   Float64 L = WBFL::Units::ConvertToSysUnits(136,WBFL::Units::Measure::Feet);
   girder.AddSection(L,Ag,Ix,Iy, Ixy, Xleft,Ytop,Hg,Wtf,Wbf);

   WBFL::Materials::SimpleConcrete concrete;
   Float64 fc = 7.0;
   concrete.SetFc(WBFL::Units::ConvertToSysUnits(fc,WBFL::Units::Measure::KSI));
   concrete.SetDensity(WBFL::Units::ConvertToSysUnits(0.150,WBFL::Units::Measure::KipPerFeet3));
   concrete.SetDensityForWeight(WBFL::Units::ConvertToSysUnits(0.155,WBFL::Units::Measure::KipPerFeet3));
   Float64 Ec = lrfdConcreteUtil::ModE(concrete.GetType(),concrete.GetFc(), concrete.GetDensity(), false);
   concrete.SetE(Ec);
   concrete.SetFlexureFr( WBFL::Units::ConvertToSysUnits(0.24*sqrt(fc),WBFL::Units::Measure::KSI) );
   stabilityProblem.SetConcrete(concrete);

   stabilityProblem.AddAnalysisPoint(std::move(std::make_unique<AnalysisPoint>(0.4 * L))); // harp point

   // Example 6.2.1
   Float64 fpe = WBFL::Units::ConvertToSysUnits(1251.5,WBFL::Units::Measure::Kip);
   stabilityProblem.AddFpe(_T("Prestress"),0.0,fpe,Xleft,-Hg + WBFL::Units::ConvertToSysUnits(7.91,WBFL::Units::Measure::Inch));

   stabilityProblem.SetCamber(WBFL::Units::ConvertToSysUnits(2.92,WBFL::Units::Measure::Inch));


   stabilityProblem.SetSupportLocations(WBFL::Units::ConvertToSysUnits(10,WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(10,WBFL::Units::Measure::Feet));
   stabilityProblem.SetSweepTolerance( 2*0.000520833333 );
   stabilityProblem.SetSweepGrowth(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch));
   stabilityProblem.SetSupportPlacementTolerance(WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Inch));
   stabilityProblem.SetYRollAxis(WBFL::Units::ConvertToSysUnits(-48.0,WBFL::Units::Measure::Inch) - Hg); // location of roll axes below top of girder);

   stabilityProblem.SetImpact( 0.0, 0.0 );
   stabilityProblem.SetImpactUsage(HaulingImpact::Both);

   stabilityProblem.SetRotationalStiffness(WBFL::Units::ConvertToSysUnits(40500., WBFL::Units::Measure::KipInchPerRadian));
   stabilityProblem.SetSupportSlope(0.06);
   stabilityProblem.SetSuperelevation(0.06);
   stabilityProblem.SetSupportWidth(WBFL::Units::ConvertToSysUnits(72., WBFL::Units::Measure::Inch));
   stabilityProblem.SetHeightOfRollAxis(WBFL::Units::ConvertToSysUnits(24., WBFL::Units::Measure::Inch));


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
            TRY_TESTME( ::IsEqual(sectionResult.FScr[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft],1.428,0.001) );

            TRY_TESTME( ::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft    ],WBFL::Units::Measure::KSI), 0.466,0.001) );
            TRY_TESTME( ::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::BottomRight],WBFL::Units::Measure::KSI),-3.486,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[+HaulingSlope::Superelevation][+impact][+wind],2.825,0.001) );
         TRY_TESTME( ::IsEqual(result.FsRollover[+HaulingSlope::Superelevation][+impact][+wind],1.994,0.001) );
      }
   }


   // Example 6.2.1 with eccentric load due to overhang brackets
   stabilityProblem.SetAppurtenanceLoading(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(0.05, WBFL::Units::Measure::KipPerFoot));
   result = engineer.AnalyzeHauling(&girder, &stabilityProblem);
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int j = 0; j < 2; j++)
      {
         WindDirection wind = (WindDirection)j;
         for (const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], 1.276, 0.001));

            TRY_TESTME(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.501, 0.001));
            TRY_TESTME(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.482, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[+HaulingSlope::Superelevation][+impact][+wind], 2.596, 0.001));
         TRY_TESTME(::IsEqual(result.FsRollover[+HaulingSlope::Superelevation][+impact][+wind], 1.845, 0.001));
      }
   }
   stabilityProblem.SetAppurtenanceLoading(0.0, 0.0); // remove eccentric load

   // Example 6.2.2
   stabilityProblem.SetTurningRadius(WBFL::Units::ConvertToSysUnits(120,WBFL::Units::Measure::Feet));
   stabilityProblem.SetVelocity(WBFL::Units::ConvertToSysUnits(10.,WBFL::Units::Measure::Mile)/WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Hour));
   stabilityProblem.SetCentrifugalForceType(CFType::Adverse);
   stabilityProblem.SetSupportSlope( 0.02 );
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
            TRY_TESTME( ::IsEqual(sectionResult.FScr[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft],0.970,0.001) );

            TRY_TESTME( ::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft    ],WBFL::Units::Measure::KSI), 0.647,0.001) );
            TRY_TESTME( ::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::BottomRight],WBFL::Units::Measure::KSI),-3.598,0.001) );
         }

         TRY_TESTME( ::IsEqual(result.FsFailure[+HaulingSlope::Superelevation][+impact][+wind],2.787,0.001) );
         TRY_TESTME( ::IsEqual(result.FsRollover[+HaulingSlope::Superelevation][+impact][+wind],1.835,0.001) );
      }
   }
   TESTME_EPILOG("PCIHaulingExamples");
}

bool UnitTest::OneEndSeated(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("OneEndSeated");
   Girder girder;
   OneEndSeatedStabilityProblem stabilityProblem;

   // base units of kip and inch
   WBFL::Units::AutoSystem au;
   WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Radian);

   Float64 Hg = WBFL::Units::ConvertToSysUnits(72, WBFL::Units::Measure::Inch);
   Float64 Wtf = WBFL::Units::ConvertToSysUnits(42, WBFL::Units::Measure::Inch);
   Float64 Wbf = WBFL::Units::ConvertToSysUnits(26, WBFL::Units::Measure::Inch);

   Float64 Ag = WBFL::Units::ConvertToSysUnits(767, WBFL::Units::Measure::Inch2);
   Float64 Ix = WBFL::Units::ConvertToSysUnits(545894, WBFL::Units::Measure::Inch4);
   Float64 Iy = WBFL::Units::ConvertToSysUnits(37634, WBFL::Units::Measure::Inch4);
   Float64 Ixy = 0;
   Float64 Xleft = Wtf / 2;
   Float64 Ytop = WBFL::Units::ConvertToSysUnits(36.6 - 72, WBFL::Units::Measure::Inch); // want neg because we are in section coordinates
   Float64 L = WBFL::Units::ConvertToSysUnits(136, WBFL::Units::Measure::Feet);
   girder.AddSection(L, Ag, Ix, Iy, Ixy, Xleft, Ytop, Hg, Wtf, Wbf);

   WBFL::Materials::SimpleConcrete concrete;
   Float64 fc = 7.0;
   concrete.SetFc(WBFL::Units::ConvertToSysUnits(fc, WBFL::Units::Measure::KSI));
   concrete.SetDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
   concrete.SetDensityForWeight(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
   Float64 Ec = lrfdConcreteUtil::ModE(concrete.GetType(), concrete.GetFc(), concrete.GetDensity(), false);
   concrete.SetE(Ec);
   concrete.SetFlexureFr(WBFL::Units::ConvertToSysUnits(0.24 * sqrt(fc), WBFL::Units::Measure::KSI));
   stabilityProblem.SetConcrete(concrete);

   stabilityProblem.AddAnalysisPoint(std::move(std::make_unique<AnalysisPoint>(0.4 * L))); // harp point

   // Example 6.2.1
   Float64 fpe = WBFL::Units::ConvertToSysUnits(1251.5, WBFL::Units::Measure::Kip);
   stabilityProblem.AddFpe(_T("Prestress"), 0.0, fpe, Xleft, -Hg + WBFL::Units::ConvertToSysUnits(7.91, WBFL::Units::Measure::Inch));

   stabilityProblem.SetCamber(WBFL::Units::ConvertToSysUnits(2.92, WBFL::Units::Measure::Inch));


   stabilityProblem.SetSupportLocations(WBFL::Units::ConvertToSysUnits(10, WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(10, WBFL::Units::Measure::Feet));
   stabilityProblem.SetSeatedEnd(GirderSide::Left); // seated at left end, hanging from right end
   stabilityProblem.SetSweepTolerance(2 * 0.000520833333);
   stabilityProblem.SetSweepGrowth(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch));
   stabilityProblem.SetSupportPlacementTolerance(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch));
   stabilityProblem.SetYRollAxis(WBFL::Units::ConvertToSysUnits(-48.0, WBFL::Units::Measure::Inch) - Hg); // roll axis is 48" below top of girder

   stabilityProblem.SetImpact(0.0, 0.0);

   stabilityProblem.SetRotationalStiffness(WBFL::Units::ConvertToSysUnits(40500., WBFL::Units::Measure::KipInchPerRadian));
   stabilityProblem.SetRotationalStiffnessAdjustmentFactor(0.50);
   stabilityProblem.SetSupportSlope(0.02);
   stabilityProblem.SetSupportWidth(WBFL::Units::ConvertToSysUnits(72., WBFL::Units::Measure::Inch));
   stabilityProblem.SetHeightOfRollAxis(WBFL::Units::ConvertToSysUnits(24., WBFL::Units::Measure::Inch));


   StabilityEngineer engineer;

   OneEndSeatedResults result = engineer.AnalyzeOneEndSeated(&girder, &stabilityProblem);
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int j = 0; j < 2; j++)
      {
         WindDirection wind = (WindDirection)j;
         for (const auto& sectionResult : result.vSectionResults)
         {
            TRY_TESTME(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopLeft], 3.010, 0.001));

            TRY_TESTME(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.0095, 0.001));
            TRY_TESTME(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.203, 0.001));
         }

         TRY_TESTME(::IsEqual(result.FsFailure[+impact][+wind], 3.637, 0.001));
         TRY_TESTME(::IsEqual(result.FsRollover[+impact][+wind], 2.975, 0.001));
      }
   }

   TESTME_EPILOG("OneEndSeated");
}
