#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestVerticalCurve)
	{
	public:
      TEST_METHOD(Test1)
      {
         Test1(true);
         Test1(false);
      }

      void Test1(bool bStandAlone)
      {
         auto vc = VerticalCurve::Create();

         if (!bStandAlone)
         {
            auto alignment = Alignment::Create();
            auto profile = Profile::Create();
            alignment->AddProfile(0, profile);
            profile->AddProfileElement(vc);
         }

         ProfilePoint pbg;
         ProfilePoint pvi;
         ProfilePoint pfg;


         // Sag curve
         pbg.Move(100, 100);
         pvi.Move(200, 50);
         pfg.Move(400, 100);

         vc->Init(pbg, pvi, pfg, 100, 200);

         Assert::IsTrue(IsEqual(vc->GetEntryGrade(), -0.5));
         Assert::IsTrue(IsEqual(vc->GetExitGrade(), 0.25));
         Assert::IsTrue(IsEqual(vc->GetLength(), 300.0));

         Assert::IsTrue(IsEqual(vc->GetElevation(150), 81.25));
         Assert::IsTrue(IsEqual(vc->GetElevation(200), 75.0));
         Assert::IsTrue(IsEqual(vc->GetElevation(250), 76.5625));

         Assert::IsTrue(IsEqual(vc->GetGrade(150), -0.25));
         Assert::IsTrue(IsEqual(vc->GetGrade(200), 0.0));
         Assert::IsTrue(IsEqual(vc->GetGrade(250), 0.0625));
         Assert::IsTrue(IsEqual(vc->GetGrade(0), -0.5));
         Assert::IsTrue(IsEqual(vc->GetGrade(600), 0.25));

         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(100, 100)); // high point at start
         Assert::IsTrue(vc->GetLowPoint() == ProfilePoint(200, 75.0)); // low point between ends

         // adjust the curve so the high point is at the end
         pfg.SetElevation(200);
         vc->SetPFG(pfg);
         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(400, 200)); // high point at end

         // make a crest curve
         pbg.Move(100, 100);
         pvi.Move(200, 150);
         pfg.Move(300, 50);
         vc->SetPBG(pbg);
         vc->SetPVI(pvi);
         vc->SetPFG(pfg);
         vc->SetLength(100, 100);

         // high point between ends
         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(166.66667, 116.66667));

         // low point at end
         Assert::IsTrue(vc->GetLowPoint() == ProfilePoint(300, 50));

         // adjust the curve so the low point at start
         pbg.SetElevation(10);
         vc->SetPBG(pbg);
         Assert::IsTrue(vc->GetLowPoint() == ProfilePoint(100, 10));

         // From "Fundamentals of Surveying" Schmidt and Wong, Third Edition
         // PWS Engineering Press, 1985, ISBN 0-534-04161-2, pg 453, Example 12.3
         pbg.Move(4850, 436.34);
         pvi.Move(5250, 432.34);
         pfg.Move(5650, 441.14);
         vc->SetPBG(pbg);
         vc->SetPVI(pvi);
         vc->SetPFG(pfg);
         vc->SetLength(400, 400);

         Assert::IsTrue(IsEqual(vc->GetElevation(4700), 437.84));
         Assert::IsTrue(IsEqual(vc->GetElevation(4850), 436.34));
         Assert::IsTrue(IsEqual(vc->GetElevation(4900), 435.89));
         Assert::IsTrue(IsEqual(vc->GetElevation(5000), 435.29));
         Assert::IsTrue(IsEqual(vc->GetElevation(5100), 435.09));
         Assert::IsTrue(IsEqual(vc->GetElevation(5200), 435.29));
         Assert::IsTrue(IsEqual(vc->GetElevation(5300), 435.89));
         Assert::IsTrue(IsEqual(vc->GetElevation(5400), 436.89));
         Assert::IsTrue(IsEqual(vc->GetElevation(5500), 438.29));
         Assert::IsTrue(IsEqual(vc->GetElevation(5600), 440.09));
         Assert::IsTrue(IsEqual(vc->GetElevation(5650), 441.14));
         Assert::IsTrue(IsEqual(vc->GetElevation(6000), 448.84));

         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(5650, 441.14));
         Assert::IsTrue(vc->GetLowPoint() == ProfilePoint(5100, 435.09));

         Float64 L, L1, L2;
         std::tie(L, L1, L2) = vc->GetCurveLengths();

         Float64 g1 = vc->GetEntryGrade();
         Float64 g2 = vc->GetExitGrade();

         Float64 A = vc->GetA();
         Assert::IsTrue(IsEqual(A, g2 - g1));
         Assert::IsTrue(IsEqual(vc->GetK1(), A / L));
         Assert::IsTrue(IsEqual(vc->GetK2(), A / L));
         Assert::IsTrue(IsEqual(vc->GetH(), A * L1 * L2 / (2 * L)));
         Assert::IsTrue(IsEqual(vc->GetE(0), 0.0));
         Assert::IsTrue(IsEqual(vc->GetE(L), 0.0));
         Assert::IsTrue(IsEqual(vc->GetE(L1), vc->GetH()));
         Assert::IsTrue(IsEqual(vc->GetE(L1 / 2), 0.8));
         Assert::IsTrue(IsEqual(vc->GetE(L1 + L2 / 2), 0.8));

         // put the points out of order
         vc->SetPBG(pfg);
         vc->SetPVI(pvi);
         vc->SetPFG(pbg);
         try { vc->GetLength(); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_VERTCURVEPOINTS); }
      }

      TEST_METHOD(Test2)
      {
         auto vc = VerticalCurve::Create();

         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);
         profile->AddProfileElement(vc);

         ProfilePoint pbg;
         ProfilePoint pvi;
         ProfilePoint pfg;

         // create station equation
         alignment->AddStationEquation(150, 250);
         alignment->AddStationEquation(400, 200);

         // Sag curve
         pbg.Move(100, 100);
         pvi.Move(Station(1, 300), 50); // Station 3+00 in Station Equation Zone 1
         pfg.Move(400, 100);

         vc->Init(pbg, pvi, pfg, 100, 200);

         Assert::IsTrue(IsEqual(vc->GetEntryGrade(), -0.5));
         Assert::IsTrue(IsEqual(vc->GetExitGrade(), 0.25));
         Assert::IsTrue(IsEqual(vc->GetLength(), 300.));

         auto station = alignment->ConvertFromNormalizedStation(150);
         Assert::IsTrue(IsEqual(vc->GetElevation(station), 81.25));
         Assert::IsTrue(IsEqual(vc->GetGrade(station), -0.25));

         station = alignment->ConvertFromNormalizedStation(200);
         Assert::IsTrue(IsEqual(vc->GetElevation(station), 75.0));
         Assert::IsTrue(IsEqual(vc->GetGrade(station), 0.0));

         station = alignment->ConvertFromNormalizedStation(250);
         Assert::IsTrue(IsEqual(vc->GetElevation(station), 76.5625));
         Assert::IsTrue(IsEqual(vc->GetGrade(station), 0.0625));

         station = alignment->ConvertFromNormalizedStation(0);
         Assert::IsTrue(IsEqual(vc->GetElevation(station), 150.));
         Assert::IsTrue(IsEqual(vc->GetGrade(station), -0.50));

         station = alignment->ConvertFromNormalizedStation(600);
         Assert::IsTrue(IsEqual(vc->GetElevation(station), 150.0));
         Assert::IsTrue(IsEqual(vc->GetGrade(station), 0.25));

         // high point at start
         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(Station(0, 100), 100.0));

         // low point between ends
         Assert::IsTrue(vc->GetLowPoint() == ProfilePoint(Station(1, 300), 75.0));

         // high point at end
         pfg.SetElevation(200);
         vc->SetPFG(pfg);
         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(Station(2, 300), 200.0));
      }

      TEST_METHOD(Test3)
      {
         Test3(true);
         Test3(false);
      }

      void Test3(bool bStandAlone)
      {
         // This is same as Test1, except that instead of PBG and PFG being points off the curve, 
         // they are the BVC and EVC. We input grades instead of lengths (PVI gets computed)
         auto vc = VerticalCurve::Create();

         if (!bStandAlone)
         {
            auto alignment = Alignment::Create();
            auto profile = Profile::Create();
            alignment->AddProfile(0, profile);
            profile->AddProfileElement(vc);
         }


         ProfilePoint pbg;
         ProfilePoint pfg;


         // Sag curve
         pbg.Move(100, 100);
         pfg.Move(400, 100);
         vc->Init(pbg, pfg, -0.5, 0.25);

         Float64 l, l1, l2;
         std::tie(l, l1, l2) = vc->GetCurveLengths();
         Assert::IsTrue(IsEqual(l, 300.0));
         Assert::IsTrue(IsEqual(l1, 100.0));
         Assert::IsTrue(IsEqual(l2, 200.0));

         Assert::IsTrue(IsEqual(vc->GetElevation(150), 81.25));
         Assert::IsTrue(IsEqual(vc->GetElevation(200), 75.0));
         Assert::IsTrue(IsEqual(vc->GetElevation(250), 76.5625));

         Assert::IsTrue(IsEqual(vc->GetGrade(150), -0.25));
         Assert::IsTrue(IsEqual(vc->GetGrade(200), 0.0));
         Assert::IsTrue(IsEqual(vc->GetGrade(250), 0.0625));
         Assert::IsTrue(IsEqual(vc->GetGrade(0), -0.5));
         Assert::IsTrue(IsEqual(vc->GetGrade(600), 0.25));

         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(100, 100)); // high point at start
         Assert::IsTrue(vc->GetLowPoint() == ProfilePoint(200, 75.0)); // low point between ends

         // adjust the curve so the high point is at the end
         pfg.SetElevation(200);
         vc->SetPFG(pfg);
         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(400, 200)); // high point at end

         // high point at end
         pfg.SetElevation(200);
         vc->SetPFG(pfg);
         vc->SetExitGrade(0.75);
         Assert::IsTrue(vc->GetHighPoint() == ProfilePoint(400, 200)); // high point at end
      }
   };
}
