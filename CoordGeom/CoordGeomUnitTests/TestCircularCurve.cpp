#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCircularCurve)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // Test curve direction
         auto curve = CircularCurve::Create();

         // Forward Tangent Bearing = N 45 E
         curve->SetPBT(WBFL::Geometry::Point2d(0, 1000));
         curve->SetPI(WBFL::Geometry::Point2d(1000, 1000));
         curve->SetPFT(WBFL::Geometry::Point2d(1000, 1500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         curve->SetPFT(WBFL::Geometry::Point2d(1000, 500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // Forward Tangent Bearing = N 45 W
         curve->SetPBT(WBFL::Geometry::Point2d(0, 1000));
         curve->SetPI(WBFL::Geometry::Point2d(1000, 1000));
         curve->SetPFT(WBFL::Geometry::Point2d(-1000, 1500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         curve->SetPFT(WBFL::Geometry::Point2d(-1000, 500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // Forward Tangent Bearing = S 45 W
         curve->SetPBT(WBFL::Geometry::Point2d(0, 1000));
         curve->SetPI(WBFL::Geometry::Point2d(-1000, -1000));
         curve->SetPFT(WBFL::Geometry::Point2d(-1000, -1500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         curve->SetPFT(WBFL::Geometry::Point2d(-1000, -500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // Forward Tangent Bearing = S 45 E
         curve->SetPBT(WBFL::Geometry::Point2d(0, 1000));
         curve->SetPI(WBFL::Geometry::Point2d(1000, -1000));
         curve->SetPFT(WBFL::Geometry::Point2d(1000, -500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         curve->SetPFT(WBFL::Geometry::Point2d(1000, -1500));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // Test symmetrical curve to the right
         curve->SetPBT(WBFL::Geometry::Point2d(0, 1000));
         curve->SetPI(WBFL::Geometry::Point2d(700, 1000));
         curve->SetPFT(WBFL::Geometry::Point2d(1000, 1300));
         curve->SetRadius(500);
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);
         curve->SetPFT(WBFL::Geometry::Point2d(1000, 700));
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         Assert::IsTrue(curve->GetBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetForwardTangentBearing() == Direction(7 * M_PI / 4));

         Assert::IsTrue(curve->GetPC() == WBFL::Geometry::Point2d(492.89322, 1000));
         Assert::IsTrue(curve->GetPT() == WBFL::Geometry::Point2d(846.44661, 853.55339));

         Assert::IsTrue(IsEqual(curve->GetChord(), 382.68343));
         Assert::IsTrue(IsEqual(curve->GetTangent(), 207.10678));
         Assert::IsTrue(IsEqual(curve->GetMidOrdinate(), 38.06023));
         Assert::IsTrue(IsEqual(curve->GetLength(), 392.69908));
         Assert::IsTrue(curve->GetCenter() == WBFL::Geometry::Point2d(492.89322, 500));

         // Bearing and normal
         // Point before curve
         Assert::IsTrue(curve->GetBearing(-1) == Direction(0.0));
         Assert::IsTrue(curve->GetNormal(-1) == Direction(3 * PI_OVER_2));

         // Mid-point of curve
         Assert::IsTrue(curve->GetBearing(curve->GetLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8));
         Assert::IsTrue(curve->GetNormal(curve->GetLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8 - PI_OVER_2));

         // Point after curve
         Assert::IsTrue(curve->GetBearing(10000) == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetNormal(10000) == Direction(7 * M_PI / 4 - PI_OVER_2));

         // PointOnCurve
         Assert::IsTrue(curve->PointOnCurve(-100) == curve->GetPC().Offset(-100, 0)); // Before PC
         Assert::IsTrue(curve->PointOnCurve(0) == curve->GetPC()); // At PC
         Assert::IsTrue(curve->PointOnCurve(curve->GetLength() / 2) == WBFL::Geometry::Point2d(684.23493, 961.93977)); // Half-way around the curve
         Assert::IsTrue(curve->PointOnCurve(curve->GetLength()) == curve->GetPT()); // At PT
         Assert::IsTrue(curve->PointOnCurve(curve->GetLength() + 100) == curve->GetPT().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4)));

         // ProjectPoint
         WBFL::Geometry::Point2d point(300, 1100);
         WBFL::Geometry::Point2d p;
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -192.89321881345245));
         Assert::IsTrue(bOnProjection == true);

         point.Move(300, 900);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -192.89321881345245));
         Assert::IsTrue(bOnProjection == true);

         point.Move(500, 1100);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(498.81512, 999.96493));
         Assert::IsTrue(IsEqual(distFromStart, 5.9220407208210313));
         Assert::IsTrue(bOnProjection == false);

         point.Move(500, 900);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(501.775293, 999.92110));
         Assert::IsTrue(IsEqual(distFromStart, 8.8825419271125750));
         Assert::IsTrue(bOnProjection == false);

         point.Move(1000, 1300);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(760.585055, 922.304487));
         Assert::IsTrue(IsEqual(distFromStart, 282.48097189865649));
         Assert::IsTrue(bOnProjection == false);

         point.Move(550, 700);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(630.173602, 980.784875));
         Assert::IsTrue(IsEqual(distFromStart, 139.06644242357913));
         Assert::IsTrue(bOnProjection == false);

         point.Move(900, 900);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(850, 850));
         Assert::IsTrue(IsEqual(distFromStart, 397.72433486814077));
         Assert::IsTrue(bOnProjection == true);

         point.Move(800, 800);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(850, 850));
         Assert::IsTrue(IsEqual(distFromStart, 397.72433486814077));
         Assert::IsTrue(bOnProjection == true);

         point.Move(1100, 500);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(1150, 550));
         Assert::IsTrue(IsEqual(distFromStart, 821.98840358006942));
         Assert::IsTrue(bOnProjection == true);

         point.Move(1200, 600);
         std::tie(p, distFromStart, bOnProjection) = curve->ProjectPoint(point);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(1150, 550));
         Assert::IsTrue(IsEqual(distFromStart, 821.98840358006942));
         Assert::IsTrue(bOnProjection == true);
      }

      TEST_METHOD(CreateOffsetPath)
      {
         auto curve = CircularCurve::Create();

         curve->SetPBT(WBFL::Geometry::Point2d(0, 1000));
         curve->SetPI(WBFL::Geometry::Point2d(1000, 1000));
         curve->SetPFT(WBFL::Geometry::Point2d(1000, 1500));
         Assert::AreEqual(1000.0, curve->GetRadius());
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         // offset to the right (radius increases)
         auto path_elements = curve->CreateOffsetPath(500);
         Assert::AreEqual((size_t)1, path_elements.size());
         auto element = path_elements.back();
         auto offset_curve = std::dynamic_pointer_cast<CircularCurve>(element);
         Assert::AreEqual(1500.0, offset_curve->GetRadius());
         Assert::IsTrue(WBFL::Geometry::Point2d(0,500) == offset_curve->GetPC());
         Assert::IsTrue(WBFL::Geometry::Point2d(1500,500) == offset_curve->GetPI());
         Assert::IsTrue(WBFL::Geometry::Point2d(1500,2000) == offset_curve->GetPT());

         // offset to the left (radius decreases)
         path_elements = curve->CreateOffsetPath(-500);
         Assert::AreEqual((size_t)1, path_elements.size());
         element = path_elements.back();
         offset_curve = std::dynamic_pointer_cast<CircularCurve>(element);
         Assert::AreEqual(500.0, offset_curve->GetRadius());
         Assert::IsTrue(WBFL::Geometry::Point2d(0, 1500) == offset_curve->GetPC());
         Assert::IsTrue(WBFL::Geometry::Point2d(500, 1500) == offset_curve->GetPI());
         Assert::IsTrue(WBFL::Geometry::Point2d(500, 2000) == offset_curve->GetPT());

         // offset to the left (offset greater than radius - curve degrades to nothing)
         path_elements = curve->CreateOffsetPath(-1500);
         Assert::IsTrue(path_elements.empty());
      }
	};
}
