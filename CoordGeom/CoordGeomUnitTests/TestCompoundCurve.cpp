#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCompoundCurve)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // Test curve direction
         auto curve = CompoundCurve::Create();

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
      }


      TEST_METHOD(Test1)
      {
         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the right
         // PBT = (0,1000)
         // PI  = (700,1000)
         // PFT = (1000,700)
         // R   = 500
         // Entry Spiral Length = 100
         // Exit Spiral Length = 200
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 200);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         pft.Move(1000, 700);
         curve->SetPFT(pft);
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Entry) == Angle(0.1));
         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Exit) == Angle(0.2));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Entry), 99.900046285613));
         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Exit), 199.20148011396));

         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Entry), 3.3309531383959));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Exit), 13.295286546224));

         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Entry), 0.83303));
         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Exit), 3.32857));

         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Entry), 49.98333));
         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Exit), 99.86681));

         Assert::IsTrue(curve->GetBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetForwardTangentBearing() == Direction(7 * M_PI / 4));

         Assert::IsTrue(curve->GetCurveAngle() == Angle(M_PI / 4));

         Assert::IsTrue(IsEqual(curve->GetBackTangentLength(), 260.96439));
         Assert::IsTrue(IsEqual(curve->GetForwardTangentLength(), 304.82311));

         Assert::IsTrue(curve->GetTS() == WBFL::Geometry::Point2d(439.03561, 1000.));
         Assert::IsTrue(curve->GetST() == WBFL::Geometry::Point2d(915.54248, 784.45751));
         Assert::IsTrue(curve->GetSC() == WBFL::Geometry::Point2d(538.93564, 996.66904));
         Assert::IsTrue(curve->GetCS() == WBFL::Geometry::Point2d(765.28458, 915.91304));

         Assert::IsTrue(IsEqual(curve->GetChord(), 240.32347));

         Assert::IsTrue(curve->GetCircularCurveAngle() == Angle(0.485398));

         Assert::IsTrue(IsEqual(curve->GetTangent(), 123.78966));
         Assert::IsTrue(IsEqual(curve->GetMidOrdinate(), 14.65357));
         Assert::IsTrue(IsEqual(curve->GetExternal(), 15.095991));

         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Entry) == Angle(0.1));
         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Exit) == Angle(0.2));

         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Entry), 66.701620764682));
         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Exit), 133.61377));

         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Entry), 33.365112106495));
         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Exit), 66.92168));

         Assert::IsTrue(curve->GetCC() == WBFL::Geometry::Point2d(439.03561, 307.95062));
         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Entry) == WBFL::Geometry::Point2d(505.73722, 1000));
         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Exit) == WBFL::Geometry::Point2d(821.06328, 878.93671));

         Assert::IsTrue(curve->GetCurveBackTangentBearing() == Direction(6.18318530718));
         Assert::IsTrue(curve->GetCurveForwardTangentBearing() == Direction(5.69778));

         Assert::IsTrue(curve->GetPCI() == WBFL::Geometry::Point2d(662.10687, 984.31070));

         Assert::IsTrue(curve->GetCCC() == WBFL::Geometry::Point2d(489.01894, 499.16696));

         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Entry), 99.95556));
         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Exit), 199.64467));

         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Entry) == Angle(0.0333305));
         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Exit) == Angle(0.0666441));

         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Entry) == Angle(0.0666695));
         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Exit) == Angle(0.1333559));

         Assert::IsTrue(IsEqual(curve->GetCurveLength(), 242.69908));
         Assert::IsTrue(IsEqual(curve->GetTotalLength(), 542.69908));

         //
         // Bearing and Normal
         //

         // Point before curve
         Assert::IsTrue(curve->GetBearing(-1.0) == Direction(0.0));
         Assert::IsTrue(curve->GetNormal(-1.0) == Direction(3 * PI_OVER_2));

         // At SC
         Assert::IsTrue(curve->GetBearing(100.0) == Direction(TWO_PI - 0.1));
         Assert::IsTrue(curve->GetNormal(100.0) == Direction(TWO_PI - 0.1 - PI_OVER_2));

         // At CS
         Assert::IsTrue(curve->GetBearing(100.0 + curve->GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2));
         Assert::IsTrue(curve->GetNormal(100.0 + curve->GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2 - PI_OVER_2));

         // Mid-point of exit spiral
         Assert::IsTrue(curve->GetBearing(100.0 + curve->GetCurveLength() + 200 / 2) == Direction(7 * M_PI / 4 + 0.05));
         Assert::IsTrue(curve->GetNormal(100.0 + curve->GetCurveLength() + 200 / 2) == Direction(7 * M_PI / 4 + 0.05 - PI_OVER_2));

         // Point after curve
         Assert::IsTrue(curve->GetBearing(10000.) == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));

         //
         // Test PointOnCurve
         //
         Assert::IsTrue(curve->PointOnCurve(-100.0) == curve->GetTS().Offset(-100, 0)); // before start of curve
         Assert::IsTrue(curve->PointOnCurve(0.0) == curve->GetTS()); // at start of curve
         Assert::IsTrue(curve->PointOnCurve(50.0) == WBFL::Geometry::Point2d(489.03248, 999.58335)); // half-way between TS and SC
         Assert::IsTrue(curve->PointOnCurve(100.0) == curve->GetSC()); // at SC
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() / 2) == WBFL::Geometry::Point2d(657.03416, 970.09253)); // Half-way around the circular curve
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength()) == curve->GetCS()); // at CS
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() + 200. / 2) == WBFL::Geometry::Point2d(843.67118, 853.97221)); // Half-way along exit spiral
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() + 200.) == curve->GetST()); // at ST
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() + 200 + 100) == curve->GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST

         //
         // Test ProjectPoint
         //
         WBFL::Geometry::Point2d pnt(300, 1100);
         WBFL::Geometry::Point2d prjPoint;
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -139.03560006006825));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(300, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -139.03560006006825));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(500, 1100);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(496.65666, 999.36213));
         Assert::IsTrue(IsEqual(distFromStart, 57.627421617507935));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(500, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(504.21291, 999.07669));
         Assert::IsTrue(IsEqual(distFromStart, 65.189087390899658));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1000, 1300);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(757.96599, 920.67316));
         Assert::IsTrue(IsEqual(distFromStart, 333.96853201394083));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(550, 700);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(634.29003, 977.59805));
         Assert::IsTrue(IsEqual(distFromStart, 197.39671595083021));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(900, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(851.19828, 847.09484));
         Assert::IsTrue(IsEqual(distFromStart, 452.89497474796428));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(800, 800);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(846.70794, 851.213706));
         Assert::IsTrue(IsEqual(distFromStart, 446.80167535907879));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1100, 500);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 874.27207383613154));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(1200, 600);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 874.27207383613154));
         Assert::IsTrue(bOnProjection == true);

         // This point should project onto both tangents.
         // It is nearest the back tangent.
         pnt.Move(200, 0);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(200.0, 1000.0));
         Assert::IsTrue(IsEqual(distFromStart, -239.03560006006825));
         Assert::IsTrue(bOnProjection == true);

         // This point should project onto both tangents.
         // It is nearest the forward tangent.
         pnt.Move(400, 0);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1050.0, 650.0));
         Assert::IsTrue(IsEqual(distFromStart, 732.85071759882192));
         Assert::IsTrue(bOnProjection == true);

         // This point should project onto both spirals.
         // It is nearest the entry spiral.
         pnt.Move(450, 430);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(450.78716, 999.99459));
         Assert::IsTrue(IsEqual(distFromStart, 11.751562356948853));
         Assert::IsTrue(bOnProjection == false);

         // This point should project onto both spirals.
         // It is nearest the exit spiral.
         pnt.Move(470, 400);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(879.50334, 820.18857));
         Assert::IsTrue(IsEqual(distFromStart, 491.94904665119304));
         Assert::IsTrue(bOnProjection == false);
      }

      TEST_METHOD(Test2)
      {
         /////////////////////////////////////////////////////
         // Test a symmetrical curve to the right
         // PBT = (0,1000)
         // PI  = (700,1000)
         // PFT = (1000,700)
         // R   = 500
         // Entry Spiral Length = 100
         // Exit Spiral Length = 0
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 0);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         pft.Move(1000, 700);
         curve->SetPFT(pft);
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Entry) == Angle(0.1));
         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Entry), 99.900046));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Entry), 3.33095));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Exit), 0.0));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Entry), 0.83304));
         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Entry), 49.98334));
         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(curve->GetBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetForwardTangentBearing() == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetCurveAngle() == Angle(M_PI / 4));

         Assert::IsTrue(IsEqual(curve->GetBackTangentLength(), 256.25708337133716));
         Assert::IsTrue(IsEqual(curve->GetForwardTangentLength(), 208.28487168090101));

         Assert::IsTrue(curve->GetTS() == WBFL::Geometry::Point2d(443.7429166, 1000.));
         Assert::IsTrue(curve->GetST() == WBFL::Geometry::Point2d(847.27964518413501, 852.72035481586499));
         Assert::IsTrue(curve->GetSC() == WBFL::Geometry::Point2d(543.64296291427536, 996.66904686160410));
         Assert::IsTrue(curve->GetCS() == WBFL::Geometry::Point2d(847.27964518413501, 852.72035481586499));

         Assert::IsTrue(IsEqual(curve->GetChord(), 336.03044));
         Assert::IsTrue(curve->GetCircularCurveAngle() == Angle(0.685398));
         Assert::IsTrue(IsEqual(curve->GetTangent(), 178.38830241973267));
         Assert::IsTrue(IsEqual(curve->GetMidOrdinate(), 29.074438143756819));

         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Entry) == Angle(0.1));
         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Entry), 66.701620764681550));
         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Entry), 33.365112106495175));
         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(curve->GetCC() == WBFL::Geometry::Point2d(443.74291662866278, 449.18362626039277));

         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Entry) == WBFL::Geometry::Point2d(510.44453739334438, 1000.0));
         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Exit) == WBFL::Geometry::Point2d(847.27964518413501, 852.72035481586499));

         Assert::IsTrue(curve->GetCurveBackTangentBearing() == Direction(6.18318530718));
         Assert::IsTrue(curve->GetCurveForwardTangentBearing() == Direction(7 * M_PI / 4));

         Assert::IsTrue(curve->GetPCI() == WBFL::Geometry::Point2d(721.14006685878576, 978.85993314121424));
         Assert::IsTrue(curve->GetCCC() == WBFL::Geometry::Point2d(493.72625459086026, 499.16696422259037));

         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Entry), 99.955562));
         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Entry) == Angle(0.0333305));
         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Entry) == Angle(0.0666695));
         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(IsEqual(curve->GetCurveLength(), 342.69908169872417));
         Assert::IsTrue(IsEqual(curve->GetTotalLength(), 442.69908169872417));


         //
         // Bearing and Normal
         //

         // Point before curve
         Assert::IsTrue(curve->GetBearing(-1) == Direction(0.0));
         Assert::IsTrue(curve->GetNormal(-1) == Direction(3 * PI_OVER_2));

         // At SC
         Assert::IsTrue(curve->GetBearing(100.0) == Direction(TWO_PI - 0.1));
         Assert::IsTrue(curve->GetNormal(100.0) == Direction(TWO_PI - 0.1 - PI_OVER_2));

         // At CS
         Assert::IsTrue(curve->GetBearing(100.0 + curve->GetCurveLength()) == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetNormal(100.0 + curve->GetCurveLength()) == Direction(7 * M_PI / 4 - PI_OVER_2));

         // Point after curve
         Assert::IsTrue(curve->GetBearing(10000.) == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));

         //
         // Test PointOnCurve
         //

         Assert::IsTrue(curve->PointOnCurve(-100) == curve->GetTS().Offset(-100, 0)); // Before TS
         Assert::IsTrue(curve->PointOnCurve(0.0) == curve->GetTS()); // At TS
         Assert::IsTrue(curve->PointOnCurve(50.0) == WBFL::Geometry::Point2d(493.73979, 999.58335)); // half-way between TS and SC
         Assert::IsTrue(curve->PointOnCurve(100.0) == curve->GetSC()); // At SC
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() / 2) == WBFL::Geometry::Point2d(707.91621, 950.96633)); // Half-way around the circular curve
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength()) == curve->GetCS()); // At CS
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength()) == curve->GetST()); // At ST
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() + 100) == curve->GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST

         //
         // Test ProjectPoint
         //
         WBFL::Geometry::Point2d pnt(300, 1100);
         WBFL::Geometry::Point2d prjPoint;
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -143.74291662866284));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(300, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -143.74291662866284));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(500, 1100);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(497.13371677391137, 999.49259034960562));
         Assert::IsTrue(IsEqual(distFromStart, 53.395140171051025));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(500, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(503.55430627716134, 999.28655987692082));
         Assert::IsTrue(IsEqual(distFromStart, 59.819048643112183));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1000, 1300);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(760.90548936690845, 921.79594631502243));
         Assert::IsTrue(IsEqual(distFromStart, 331.87429448137652));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(550, 700);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(628.63123683543824, 980.62375954859954));
         Assert::IsTrue(IsEqual(distFromStart, 186.59783566077238));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(900, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
         Assert::IsTrue(IsEqual(distFromStart, 446.54624437378743));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(800, 800);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
         Assert::IsTrue(IsEqual(distFromStart, 446.54624437378743));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(1100, 500);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 870.81031308571596));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(1200, 600);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 870.81031308571596));
         Assert::IsTrue(bOnProjection == true);
      }

      TEST_METHOD(Test3)
      {
         /////////////////////////////////////////////////////
         // Test a symmetrical curve to the right
         // PBT = (0,1000)
         // PI  = (700,1000)
         // PFT = (1000,700)
         // R   = 500
         // Entry Spiral Length = 0
         // Exit Spiral Length = 200
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 0);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 200);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         pft.Move(1000, 700);
         curve->SetPFT(pft);
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);


         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Exit) == Angle(0.2));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Entry), 0.0));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Exit), 199.20148));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Exit), 13.29528));

         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Exit), 3.3285754668449599));

         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Exit), 99.866814716429502));

         Assert::IsTrue(curve->GetBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetForwardTangentBearing() == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetCurveAngle() == Angle(M_PI / 4));

         Assert::IsTrue(IsEqual(curve->GetBackTangentLength(), 211.81409775514197));
         Assert::IsTrue(IsEqual(curve->GetForwardTangentLength(), 303.64502043613209));

         Assert::IsTrue(curve->GetTS() == WBFL::Geometry::Point2d(488.18590224485806, 1000.));
         Assert::IsTrue(curve->GetST() == WBFL::Geometry::Point2d(914.70945302391669, 785.29054697608319));
         Assert::IsTrue(curve->GetSC() == WBFL::Geometry::Point2d(488.18590224485803, 1000.0));
         Assert::IsTrue(curve->GetCS() == WBFL::Geometry::Point2d(764.45154833828497, 916.74607711240822));

         Assert::IsTrue(IsEqual(curve->GetChord(), 288.53755888547977));
         Assert::IsTrue(curve->GetCircularCurveAngle() == Angle(0.585398));
         Assert::IsTrue(IsEqual(curve->GetTangent(), 150.67729930386835));
         Assert::IsTrue(IsEqual(curve->GetMidOrdinate(), 21.265711194506100));

         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Exit) == Angle(0.2));

         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Exit), 133.61377246612963));

         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Exit), 66.921685863727987));

         Assert::IsTrue(curve->GetCC() == WBFL::Geometry::Point2d(488.18590224485803, 358.76699619702475));

         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Entry) == WBFL::Geometry::Point2d(488.18590224485803, 1000.0));
         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Exit) == WBFL::Geometry::Point2d(820.23024845320003, 879.76975154679985));

         Assert::IsTrue(curve->GetCurveBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetCurveForwardTangentBearing() == Direction(7 * M_PI / 4 + 0.2));

         Assert::IsTrue(curve->GetPCI() == WBFL::Geometry::Point2d(638.86320154872624, 1000.0));

         Assert::IsTrue(curve->GetCCC() == WBFL::Geometry::Point2d(488.18590224485797, 500.0));

         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Exit), 199.64467016161149));

         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Exit) == Angle(0.0666441));

         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Exit) == Angle(0.1333559));

         Assert::IsTrue(IsEqual(curve->GetCurveLength(), 292.69908169872417));
         Assert::IsTrue(IsEqual(curve->GetTotalLength(), 492.69908169872417));


         //
         // Bearing and Normal
         //

         // Point before curve
         Assert::IsTrue(curve->GetBearing(-1) == Direction(0.0));
         Assert::IsTrue(curve->GetNormal(-1) == Direction(3 * PI_OVER_2));

         // At CS
         Assert::IsTrue(curve->GetBearing(curve->GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2));
         Assert::IsTrue(curve->GetNormal(curve->GetCurveLength()) == Direction(7 * M_PI / 4 + 0.2 - PI_OVER_2));

         // Point after curve
         Assert::IsTrue(curve->GetBearing(10000.) == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));

         //
         // Test PointOnCurve
         //
         Assert::IsTrue(curve->PointOnCurve(-100) == curve->GetTS().Offset(-100, 0)); // Before TS
         Assert::IsTrue(curve->PointOnCurve(0.0) == curve->GetTS()); // At TS
         Assert::IsTrue(curve->PointOnCurve(0.0) == curve->GetSC()); // At SC
         Assert::IsTrue(curve->PointOnCurve(curve->GetCurveLength() / 2) == WBFL::Geometry::Point2d(632.45468, 978.73429)); // Half-way around the circular curve
         Assert::IsTrue(curve->PointOnCurve(curve->GetCurveLength()) == curve->GetCS()); // At CS
         Assert::IsTrue(curve->PointOnCurve(curve->GetCurveLength() + 200. / 2) == WBFL::Geometry::Point2d(842.83815, 854.80525)); // Half-way along exit spiral
         Assert::IsTrue(curve->PointOnCurve(curve->GetCurveLength() + 200.) == curve->GetST()); // At ST
         Assert::IsTrue(curve->PointOnCurve(curve->GetTotalLength() + 100) == curve->GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST


         //
         // Test ProjectPoint
         //
         WBFL::Geometry::Point2d pnt(300, 1100);
         WBFL::Geometry::Point2d prjPoint;
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -188.18590224485803));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(300, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -188.18590224485803));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(500, 1100);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(498.02907578081619, 999.90310254579163));
         Assert::IsTrue(IsEqual(distFromStart, 9.8438094375546967));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(500, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(502.94708752500497, 999.78205991134200));
         Assert::IsTrue(IsEqual(distFromStart, 14.763330356833970));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1000, 1300);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(757.64331368111448, 921.18013179882087));
         Assert::IsTrue(IsEqual(distFromStart, 284.57415999276304));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(550, 700);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(635.83013345708582, 977.70407261164269));
         Assert::IsTrue(IsEqual(distFromStart, 149.87871522359342));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(900, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(851.17791915026055, 847.17749344031427));
         Assert::IsTrue(IsEqual(distFromStart, 404.00109986431255));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(800, 800);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(846.80545046763643, 851.19704221174209));
         Assert::IsTrue(IsEqual(distFromStart, 398.06179503566875));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1100, 500);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 825.45016433048499));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(1200, 600);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 825.45016433048499));
         Assert::IsTrue(bOnProjection == true);
      }

      TEST_METHOD(Test4)
      {
         /////////////////////////////////////////////////////
         // Test a symmetrical curve to the right
         // PBT = (0,1000)
         // PI  = (700,1000)
         // PFT = (1000,700)
         // R   = 500
         // Entry Spiral Length = 0
         // Exit Spiral Length = 0
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 0);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 0);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         pft.Move(1000, 700);
         curve->SetPFT(pft);
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Entry), 0.0));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Exit), 0.0));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(curve->GetBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetForwardTangentBearing() == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetCurveAngle() == Angle(M_PI / 4));

         Assert::IsTrue(IsEqual(curve->GetBackTangentLength(), 207.10678));
         Assert::IsTrue(IsEqual(curve->GetForwardTangentLength(), 207.10678));

         Assert::IsTrue(curve->GetTS() == WBFL::Geometry::Point2d(492.89321881345245, 1000.0));
         Assert::IsTrue(curve->GetST() == WBFL::Geometry::Point2d(846.44660940672622, 853.55339059327366));
         Assert::IsTrue(curve->GetSC() == WBFL::Geometry::Point2d(492.89321881345245, 1000.0));
         Assert::IsTrue(curve->GetCS() == WBFL::Geometry::Point2d(846.44660940672622, 853.55339059327366));

         Assert::IsTrue(IsEqual(curve->GetChord(), 382.68343236508986));
         Assert::IsTrue(curve->GetCircularCurveAngle() == Angle(M_PI / 4));
         Assert::IsTrue(IsEqual(curve->GetTangent(), 207.10678118654752));
         Assert::IsTrue(IsEqual(curve->GetMidOrdinate(), 38.060233744356630));

         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(curve->GetCC() == WBFL::Geometry::Point2d(492.89321881345245, 500.0));

         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Entry) == WBFL::Geometry::Point2d(492.89322, 1000.0));
         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Exit) == WBFL::Geometry::Point2d(846.44661, 853.55339));

         Assert::IsTrue(curve->GetCurveBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetCurveForwardTangentBearing() == Direction(7 * M_PI / 4));

         Assert::IsTrue(curve->GetPCI() == WBFL::Geometry::Point2d(700., 1000.0));

         Assert::IsTrue(curve->GetCCC() == WBFL::Geometry::Point2d(492.89322, 500.0));

         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Entry), 0.0));
         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Exit), 0.0));

         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Entry) == Angle(0.0));
         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Exit) == Angle(0.0));

         Assert::IsTrue(IsEqual(curve->GetCurveLength(), 392.69908169872411));
         Assert::IsTrue(IsEqual(curve->GetTotalLength(), 392.69908169872411));

         //
         // Bearing and Normal
         //

         // Point before curve
         Assert::IsTrue(curve->GetBearing(-1) == Direction(0.0));
         Assert::IsTrue(curve->GetNormal(-1) == Direction(3 * PI_OVER_2));

         // At mid-point of curve
         Assert::IsTrue(curve->GetBearing(curve->GetCurveLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8));
         Assert::IsTrue(curve->GetNormal(curve->GetCurveLength() / 2) == Direction(7 * M_PI / 4 + M_PI / 8 - PI_OVER_2));

         // Point after curve
         Assert::IsTrue(curve->GetBearing(10000.) == Direction(7 * M_PI / 4));
         Assert::IsTrue(curve->GetNormal(10000.) == Direction(7 * M_PI / 4 - PI_OVER_2));


         //
         // Test PointOnCurve
         //
         Assert::IsTrue(curve->PointOnCurve(-100) == curve->GetTS().Offset(-100, 0)); // Before TS
         Assert::IsTrue(curve->PointOnCurve(0.0) == curve->GetTS()); // At TS
         Assert::IsTrue(curve->PointOnCurve(0.0) == curve->GetSC()); // At SC
         Assert::IsTrue(curve->PointOnCurve(curve->GetCurveLength() / 2) == WBFL::Geometry::Point2d(684.23493, 961.93977)); // Half-way around the circular curve
         Assert::IsTrue(curve->PointOnCurve(curve->GetCurveLength()) == curve->GetCS()); // At CS
         Assert::IsTrue(curve->PointOnCurve(curve->GetCurveLength()) == curve->GetST()); // At ST
         Assert::IsTrue(curve->PointOnCurve(curve->GetTotalLength() + 100) == curve->GetST().Offset(100 * sin(M_PI / 4), -100 * cos(M_PI / 4))); // 100 past ST

         //
         // Test ProjectPoint
         //
         WBFL::Geometry::Point2d pnt(300, 1100);
         WBFL::Geometry::Point2d prjPoint;
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -192.89321881345245));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(300, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(300, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -192.89321881345245));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(500, 1100);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(498.81512107569978, 999.96492984393990));
         Assert::IsTrue(IsEqual(distFromStart, 5.9220407208209203));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(500, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(501.77529352889013, 999.92110252390921));
         Assert::IsTrue(IsEqual(distFromStart, 8.8825419271126869));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1000, 1300);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(760.58505570770842, 922.30448785228305));
         Assert::IsTrue(IsEqual(distFromStart, 282.48097189865661));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(550, 700);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(630.17360217890621, 980.78487532682811));
         Assert::IsTrue(IsEqual(distFromStart, 139.06644242357936));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(900, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
         Assert::IsTrue(IsEqual(distFromStart, 397.72433486814077));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(800, 800);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(850.0, 850.0));
         Assert::IsTrue(IsEqual(distFromStart, 397.72433486814077));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(1100, 500);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 821.98840358006942));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(1200, 600);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1150.0, 550.0));
         Assert::IsTrue(IsEqual(distFromStart, 821.98840358006942));
         Assert::IsTrue(bOnProjection == true);
      }

      TEST_METHOD(Test5)
      {
         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the left
         // PBT = (0,1000)
         // PI  = (700,1000)
         // PFT = (1000,1300)
         // R   = 500
         // Entry Spiral Length = 100
         // Exit Spiral Length = 200
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 200);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Entry) == Angle(0.1));
         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Exit) == Angle(0.2));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Entry), 99.900046285613));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Entry), 3.3309531383959));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Exit), 199.20148011396));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Exit), 13.295286546224));

         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Entry), 0.83303));
         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Exit), 3.3285754668449599));

         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Entry), 49.983337962198455));
         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Exit), 99.866814716429502));

         Assert::IsTrue(curve->GetBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetForwardTangentBearing() == Direction(M_PI / 4));
         Assert::IsTrue(curve->GetCurveAngle() == Angle(M_PI / 4));

         Assert::IsTrue(IsEqual(curve->GetBackTangentLength(), 260.96439));
         Assert::IsTrue(IsEqual(curve->GetForwardTangentLength(), 304.82311));

         Assert::IsTrue(curve->GetTS() == WBFL::Geometry::Point2d(439.03560006006825, 1000.0000000000000));
         Assert::IsTrue(curve->GetST() == WBFL::Geometry::Point2d(915.54248880132559, 1215.5424888013256));
         Assert::IsTrue(curve->GetSC() == WBFL::Geometry::Point2d(538.93564634568077, 1003.3309531383959));
         Assert::IsTrue(curve->GetCS() == WBFL::Geometry::Point2d(765.28458411569386, 1084.0869586650006));

         Assert::IsTrue(IsEqual(curve->GetChord(), 240.323477));
         Assert::IsTrue(curve->GetCircularCurveAngle() == Angle(0.48539816339744829));
         Assert::IsTrue(IsEqual(curve->GetTangent(), 123.78966));
         Assert::IsTrue(IsEqual(curve->GetMidOrdinate(), 14.65357));

         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Entry) == Angle(0.1));
         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Exit) == Angle(0.2));

         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Entry), 66.701620764682));
         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Exit), 133.613772));

         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Entry), 33.365112106495));
         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Exit), 66.92168));

         Assert::IsTrue(curve->GetCC() == WBFL::Geometry::Point2d(439.035600, 1692.0493775));

         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Entry) == WBFL::Geometry::Point2d(505.73722, 1000.0));
         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Exit) == WBFL::Geometry::Point2d(821.063284, 1121.06328));

         Assert::IsTrue(curve->GetCurveBackTangentBearing() == Direction(0.1));
         Assert::IsTrue(curve->GetCurveForwardTangentBearing() == Direction(M_PI / 4 - 0.2));

         Assert::IsTrue(curve->GetPCI() == WBFL::Geometry::Point2d(662.10687, 1015.68929));

         Assert::IsTrue(curve->GetCCC() == WBFL::Geometry::Point2d(489.01893, 1500.833035));

         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Entry), 99.95556));
         Assert::IsTrue(IsEqual(curve->GetSpiralChord(CompoundCurve::SpiralLocation::Exit), 199.64467));

         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Entry) == Angle(0.0333305));
         Assert::IsTrue(curve->GetDF(CompoundCurve::SpiralLocation::Exit) == Angle(0.0666441));

         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Entry) == Angle(0.0666695));
         Assert::IsTrue(curve->GetDH(CompoundCurve::SpiralLocation::Exit) == Angle(0.1333559));

         Assert::IsTrue(IsEqual(curve->GetCurveLength(), 242.699081));
         Assert::IsTrue(IsEqual(curve->GetTotalLength(), 542.699081));

         //
         // Bearing and Normal
         //

         // Point before curve
         Assert::IsTrue(curve->GetBearing(-1) == Direction(0.0));
         Assert::IsTrue(curve->GetNormal(-1) == Direction(3 * PI_OVER_2));

         // At SC
         Assert::IsTrue(curve->GetBearing(100.0) == Direction(0.1));
         Assert::IsTrue(curve->GetNormal(100.0) == Direction(3 * PI_OVER_2 + 0.1));

         // At CS
         Assert::IsTrue(curve->GetBearing(100.0 + curve->GetCurveLength()) == Direction(M_PI / 4 - 0.2));
         Assert::IsTrue(curve->GetNormal(100.0 + curve->GetCurveLength()) == Direction(3 * PI_OVER_2 + M_PI / 4 - 0.2));

         // Mid-point of exit spiral
         Assert::IsTrue(curve->GetBearing(100.0 + curve->GetCurveLength() + 200. / 2) == Direction(M_PI / 4 - 0.05));
         Assert::IsTrue(curve->GetNormal(100.0 + curve->GetCurveLength() + 200. / 2) == Direction(3 * PI_OVER_2 + M_PI / 4 - 0.05));

         // Point after curve
         Assert::IsTrue(curve->GetBearing(10000.) == Direction(M_PI / 4));
         Assert::IsTrue(curve->GetNormal(10000.) == Direction(3 * PI_OVER_2 + M_PI / 4));

         //
         // Test PointOnCurve
         //
         Assert::IsTrue(curve->PointOnCurve(-100) == curve->GetTS().Offset(-100, 0)); // Before TS
         Assert::IsTrue(curve->PointOnCurve(0.0) == curve->GetTS()); // At TS
         Assert::IsTrue(curve->PointOnCurve(50.0) == WBFL::Geometry::Point2d(489.03248, 1000.41665)); // half-way between TS and SC
         Assert::IsTrue(curve->PointOnCurve(100.0) == curve->GetSC()); // At SC
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() / 2) == WBFL::Geometry::Point2d(657.034161, 1029.90747)); // Half-way around the circular curve
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength()) == curve->GetCS()); // At CS
         Assert::IsTrue(curve->PointOnCurve(100.0 + curve->GetCurveLength() + 200.0 / 2) == WBFL::Geometry::Point2d(843.67118, 1146.02779)); // Half-way along exit spiral
         Assert::IsTrue(curve->PointOnCurve(curve->GetTotalLength()) == curve->GetST()); // At ST
         Assert::IsTrue(curve->PointOnCurve(curve->GetTotalLength() + 100) == curve->GetST().Offset(100 * sin(M_PI / 4), 100 * cos(M_PI / 4))); // 100 past ST

         //
         // Test ProjectPoint
         //
         WBFL::Geometry::Point2d pnt(400, 1100);
         WBFL::Geometry::Point2d prjPoint;
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(400, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -39.035600060068248));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(400, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(400, 1000));
         Assert::IsTrue(IsEqual(distFromStart, -39.035600060068248));
         Assert::IsTrue(bOnProjection == true);

         pnt.Move(490, 1100);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(492.88607, 1000.52063));
         Assert::IsTrue(IsEqual(distFromStart, 53.855001926422119));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(490, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(487.62895, 1000.38253));
         Assert::IsTrue(IsEqual(distFromStart, 48.596060276031494));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(650, 1100);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(675.36056, 1036.85373));
         Assert::IsTrue(IsEqual(distFromStart, 240.94946090466198));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(650, 900);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(618.41971, 1017.86777));
         Assert::IsTrue(IsEqual(distFromStart, 180.89063696761301));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(850, 1200);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(874.35534, 1174.81344));
         Assert::IsTrue(IsEqual(distFromStart, 484.77395276195659));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1050, 1000);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(877.34833, 1177.71447));
         Assert::IsTrue(IsEqual(distFromStart, 488.94216517574444));
         Assert::IsTrue(bOnProjection == false);

         pnt.Move(1200, 1300);
         std::tie(prjPoint, distFromStart, bOnProjection) = curve->ProjectPoint(pnt);
         Assert::IsTrue(prjPoint == WBFL::Geometry::Point2d(1100.0, 1400.0));
         Assert::IsTrue(IsEqual(distFromStart, 803.56139571747667));
         Assert::IsTrue(bOnProjection == true);
      }

      TEST_METHOD(Test6)
      {
         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the right
         // PBT = (-1000,0)
         // PI  = (0,0)
         // PFT = (937.993610303, -346.652545108)
         // R   = 1000
         // Entry Spiral Length = 350
         // Exit Spiral Length = 150

         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(-1000, 0);
         WBFL::Geometry::Point2d pi(0, 0);
         WBFL::Geometry::Point2d pft(937.993610303, -346.652545108);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(1000);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 350);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 150);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Entry) == Angle(0.175));
         Assert::IsTrue(curve->GetSpiralAngle(CompoundCurve::SpiralLocation::Exit) == Angle(0.075));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Entry), 348.929643656));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Entry), 20.3720487046));

         Assert::IsTrue(IsEqual(curve->GetX(CompoundCurve::SpiralLocation::Exit), 149.91564697));
         Assert::IsTrue(IsEqual(curve->GetY(CompoundCurve::SpiralLocation::Exit), 3.7484935732));

         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Entry), 5.0985876095420));
         Assert::IsTrue(IsEqual(curve->GetQ(CompoundCurve::SpiralLocation::Exit), 0.93731168541681));

         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Entry), 174.82150606254));
         Assert::IsTrue(IsEqual(curve->GetT(CompoundCurve::SpiralLocation::Exit), 74.985939697062));

         Assert::IsTrue(curve->GetBackTangentBearing() == Direction(0.0));
         Assert::IsTrue(curve->GetForwardTangentBearing() == Direction(TWO_PI - 0.354));
         Assert::IsTrue(curve->GetCurveAngle() == Angle(0.354));

         Assert::IsTrue(IsEqual(curve->GetBackTangentLength(), 342.601202));
         Assert::IsTrue(IsEqual(curve->GetForwardTangentLength(), 266.02964));

         Assert::IsTrue(curve->GetTS() == WBFL::Geometry::Point2d(-342.601202, 0.0));
         Assert::IsTrue(curve->GetST() == WBFL::Geometry::Point2d(249.53410, -92.21985));
         Assert::IsTrue(curve->GetSC() == WBFL::Geometry::Point2d(6.32844, -20.37205));
         Assert::IsTrue(curve->GetCS() == WBFL::Geometry::Point2d(107.61475, -43.76727));

         Assert::IsTrue(IsEqual(curve->GetChord(), 103.95313));
         Assert::IsTrue(curve->GetCircularCurveAngle() == Angle(0.104));
         Assert::IsTrue(IsEqual(curve->GetTangent(), 52.04692));
         Assert::IsTrue(IsEqual(curve->GetMidOrdinate(), 1.35169));

         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Entry) == Angle(0.175));
         Assert::IsTrue(curve->GetDE(CompoundCurve::SpiralLocation::Exit) == Angle(0.075));

         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Entry), 233.70873));
         Assert::IsTrue(IsEqual(curve->GetLongTangent(CompoundCurve::SpiralLocation::Exit), 100.02948));

         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Entry), 117.00802));
         Assert::IsTrue(IsEqual(curve->GetShortTangent(CompoundCurve::SpiralLocation::Exit), 50.026801));

         Assert::IsTrue(curve->GetCC() == WBFL::Geometry::Point2d(-342.60120, -1694.45569));

         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Entry) == WBFL::Geometry::Point2d(-108.89246, 0.0));
         Assert::IsTrue(curve->GetSPI(CompoundCurve::SpiralLocation::Exit) == WBFL::Geometry::Point2d(155.70708, -57.54437));

         Assert::IsTrue(curve->GetCurveBackTangentBearing() == Direction(6.10818));
         Assert::IsTrue(curve->GetCurveForwardTangentBearing() == Direction(6.00418));

         Assert::IsTrue(curve->GetPCI() == WBFL::Geometry::Point2d(57.580424, -29.43384));

         Assert::IsTrue(curve->GetCCC() == WBFL::Geometry::Point2d(-167.77969, -1005.09858));
      }

      TEST_METHOD(Test7)
      {
         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the left
         // Spiral lengths overlap
         // PBT = (0,1000)
         // PI  = (700,1000)
         // PFT = (1000,1300)
         // R   = 500
         // Entry Spiral Length = 500
         // Exit Spiral Length = 700

         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 700);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         try
         {
            curve->GetCircularCurveAngle();
         }
         catch (XCoordGeom& e)
         {
            Assert::IsTrue(e.GetReason() == WBFL_COGO_E_SPIRALSOVERLAP);
         }
      }

      TEST_METHOD(Test8a)
      {
         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the left
         // Spiral lengths overlap
         // PBT = (0,1000)
         // PI  = (700,1000)
         // PFT = (1000,1300)
         // R   = 500
         // Entry Spiral Length = 100
         // Exit Spiral Length = 200

         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 200);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         // create a line
         WBFL::Geometry::Line2d line;

         // Important curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(505.64225645686224, 1000.9854331731150));

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, 1124.3794191254133));

         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, 1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(508.67043163106791, 1001.1261389033072));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(809.35182374575743, 1116.5668976835791));

         // intersect circular curve in two places
         // first locate two points on the curve
         auto cp1 = curve->PointOnCurve(110);
         auto cp2 = curve->PointOnCurve(140);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(548.87503670886008, 1004.4287172526595));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(578.53372538212068, 1008.9111895010718));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         cp1 = curve->PointOnCurve(150);
         cp2 = curve->PointOnCurve(151);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(588.35360, 1010.79974));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(589.33347, 1010.99939));

         // line tangent to entry spiral
         auto POC = curve->PointOnCurve(50);
         auto dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(474.03507484100646, 1000.1429151347374));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(484.03375483745350, 1000.3037411037024));

         // line tangent to exit spiral
         Float64 length = curve->GetTotalLength();
         POC = curve->PointOnCurve(length - 50);
         dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(883.61562936445966, 1183.8304112645556));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(890.74331577219289, 1190.8443728455015));

         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(703.20889, 1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pbt, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(813.501198, 1119.948289));

         // again, but don't project back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(813.501198, 1119.948289));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi1, pft);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(507.50055, 1001.07029));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(1000.0, 1300.0));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(507.50055, 1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, 900);
         cp2.Move(700, 900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, 1100);
         cp2.Move(700, 1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(787.96427, 1099.99997));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, 1500);
         cp2.Move(700, 1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1200.0, 1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(800, 1000);
         cp2.Move(1100, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(600, 1000);
         cp2.Move(900, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(617.666636, 1017.666636));

         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(200, 1000);
         cp2.Move(500, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(200.0, 1000.0));

         // again, but don't project curve
         cp1.Move(200, 1000);
         cp2.Move(500, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, 1000);
         cp2.Move(1000, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(1000.0, 1300.0));

         // again, but project only back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, 1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(690, 1000);
         cp2.Move(710, 1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(Test8b)
      {
         // same as Test8a except the direction of the curve is reverse

         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the right
         // Spiral lengths overlap
         // PBT = (1000,1300)
         // PI  = (700,1000)
         // PFT = (0,1000)
         // R   = 500
         // Entry Spiral Length = 200
         // Exit Spiral Length = 100

         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(1000, 1300);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(0, 1000);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 200);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 100);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // create a line
         WBFL::Geometry::Line2d line;

         // Important curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(505.64225645686224, 1000.9854331731150));

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, 1124.3794191254133));

         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, 1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(809.35182374575743, 1116.5668976835791));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(508.67043163106791, 1001.1261389033072));

         // intersect circular curve in two places
         // first locate two points on the curve
         Float64 length = curve->GetTotalLength();
         auto cp1 = curve->PointOnCurve(length - 140);
         auto cp2 = curve->PointOnCurve(length - 110);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(578.53372538212068, 1008.9111895010718));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(548.87503670886008, 1004.4287172526595));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         cp1 = curve->PointOnCurve(length - 151);
         cp2 = curve->PointOnCurve(length - 150);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(589.33347, 1010.99939));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(588.35360, 1010.79974));

         // line tangent to exit spiral
         auto POC = curve->PointOnCurve(length - 50);
         auto dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, 1000.41664));

         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(484.03375483745350, 1000.303741103702));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(474.03507484100646, 1000.142915134737));

         // line tangent to exit spiral
         POC = curve->PointOnCurve(50);
         dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, 1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(890.74331577219289, 1190.8443728455015));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(883.61562929997854, 1183.8304112013670));

         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(703.20889, 1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pft, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(813.50119, 1119.94828));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0.0, 1000.0));

         // again, but don't project back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(813.50119, 1119.94828));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi2, pbt);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, 1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(507.50055, 1001.07029));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(507.50055, 1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, 900);
         cp2.Move(700, 900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, 1100);
         cp2.Move(700, 1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(787.96427, 1099.99997));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, 1500);
         cp2.Move(700, 1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1200.0, 1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(800, 1000);
         cp2.Move(1100, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(600, 1000);
         cp2.Move(900, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(617.66664, 1017.66664));

         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(200, 1000);
         cp2.Move(500, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(200.0, 1000.0));

         // again, but don't project curve
         cp1.Move(200, 1000);
         cp2.Move(500, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, 1000);
         cp2.Move(1000, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, 1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0.0, 1000.0));

         // again, but project only back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, 1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(690, 1000);
         cp2.Move(710, 1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(Test9a)
      {
         // This is the same as Test8a except the curve has been mirrored about the Y axis

         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the right
         // Spiral lengths overlap
         // PBT = (0,1000)
         // PI  = (-700,1000)
         // PFT = (-1000,1300)
         // R   = 500
         // Entry Spiral Length = 100
         // Exit Spiral Length = 200
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(-700, 1000);
         WBFL::Geometry::Point2d pft(-1000, 1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 200);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // create a line
         WBFL::Geometry::Line2d line;

         // get some useful curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, 1000.9854331731151));

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, 1124.3794191254133));


         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, 1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-508.67043163106791, 1001.1261389033072));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-809.35182374575743, 1116.5668976835791));


         // intersect circular curve in two places
         // first locate two points on the curve
         auto cp1 = curve->PointOnCurve(110);
         auto cp2 = curve->PointOnCurve(140);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-548.87503670886008, 1004.4287172526595));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-578.53372538212068, 1008.9111895010718));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         cp1 = curve->PointOnCurve(150);
         cp2 = curve->PointOnCurve(151);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-588.35360, 1010.79974));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-589.33347, 1010.99939));

         // line tangent to entry spiral
         auto POC = curve->PointOnCurve(50);
         auto dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-474.03507484100646, 1000.1429151347374));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-484.03375483745350, 1000.3037411037024));

         // line tangent to exit spiral
         Float64 length = curve->GetTotalLength();
         POC = curve->PointOnCurve(length - 50);
         dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-883.61562936445966, 1183.8304112645556));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-890.74331577219289, 1190.8443728455015));


         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, 1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pbt, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-813.501198, 1119.948289));

         // again, but don't project back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-813.501198, 1119.948289));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi1, pft);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, 900);
         cp2.Move(-700, 900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, 1100);
         cp2.Move(-700, 1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, 1099.99997));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, 1500);
         cp2.Move(-700, 1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, 1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(-800, 1000);
         cp2.Move(-1100, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(-600, 1000);
         cp2.Move(-900, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-617.666636, 1017.666636));


         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(-200, 1000);
         cp2.Move(-500, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-200.0, 1000.0));

         // again, but don't project curve
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, 1000);
         cp2.Move(-1000, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

         // again, but project only back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(-690, 1000);
         cp2.Move(-710, 1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(Test9b)
      {
         // same as Test9a except the direction of the curve is reverse

         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the left
         // Spiral lengths overlap
         // PBT = (-1000,1300)
         // PI  = (-700,1000)
         // PFT = (0,1000)
         // R   = 500
         // Entry Spiral Length = 200
         // Exit Spiral Length = 100
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(-1000, 1300);
         WBFL::Geometry::Point2d pi(-700, 1000);
         WBFL::Geometry::Point2d pft(0, 1000);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 200);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 100);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);


         // create a line
         WBFL::Geometry::Line2d line;

         // get some useful curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, 1000.9854331731151));

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, 1124.3794191254133));

         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, 1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-809.35182374575743, 1116.5668976835791));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-508.67043163106791, 1001.1261389033072));

         // intersect circular curve in two places
         // first locate two points on the curve
         Float64 length = curve->GetTotalLength();
         auto cp1 = curve->PointOnCurve(length - 140);
         auto cp2 = curve->PointOnCurve(length - 110);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-578.53372538212068, 1008.9111895010718));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-548.87503670886008, 1004.4287172526595));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         cp1 = curve->PointOnCurve(length - 151);
         cp2 = curve->PointOnCurve(length - 150);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-589.33347, 1010.99939));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-588.35360, 1010.79974));

         //// line tangent to exit spiral
         auto POC = curve->PointOnCurve(length - 50);
         auto dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, 1000.41664));

         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-484.03375483745350, 1000.3037411037024));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-474.03507484100646, 1000.1429151347374));

         // line tangent to exit spiral
         POC = curve->PointOnCurve(50);
         dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, 1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-890.74331577219289, 1190.8443728455015));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-883.61562929997831, 1183.8304112013673));

         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, 1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pft, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, 1119.94828));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0.0, 1000.0));

         // again, but don't project back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, 1119.94828));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi2, pbt);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-507.50055, 1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, 900);
         cp2.Move(-700, 900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, 1100);
         cp2.Move(-700, 1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, 1099.99997));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, 1500);
         cp2.Move(-700, 1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, 1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(-800, 1000);
         cp2.Move(-1100, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(-600, 1000);
         cp2.Move(-900, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-617.66664, 1017.66664));

         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(-200, 1000);
         cp2.Move(-500, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-200.0, 1000.0));

         // again, but don't project curve
         cp1.Move(-200, 1000);
         cp2.Move(-500, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, 1000);
         cp2.Move(-1000, 1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0, 1000.0));

         // again, but project only back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, 1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, 1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(-690, 1000);
         cp2.Move(-710, 1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(Test10a)
      {
         // same as Test8a except curve has been mirrored about the X axis

         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the right
         // Spiral lengths overlap
         // PBT = (0,-1000)
         // PI  = (700,-1000)
         // PFT = (1000,-1300)
         // R   = 500
         // Entry Spiral Length = 100
         // Exit Spiral Length = 200
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, -1000);
         WBFL::Geometry::Point2d pi(700, -1000);
         WBFL::Geometry::Point2d pft(1000, -1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 200);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // create a line
         WBFL::Geometry::Line2d line;

         // Important curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(505.64225645686224, -1000.9854331731150));

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, -1124.3794191254133));

         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, -1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(508.67043163106791, -1001.1261389033072));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(809.35182374575743, -1116.5668976835791));

         // intersect circular curve in two places
         // first locate two points on the curve
         auto cp1 = curve->PointOnCurve(110);
         auto cp2 = curve->PointOnCurve(140);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(548.87503670886008, -1004.4287172526595));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(578.53372538212068, -1008.9111895010718));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         cp1 = curve->PointOnCurve(150);
         cp2 = curve->PointOnCurve(151);

         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(588.35360, -1010.79974));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(589.33347, -1010.99939));

         // line tangent to entry spiral
         auto POC = curve->PointOnCurve(50);
         auto dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(474.03507484100646, -1000.1429151347374));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(484.03375483745350, -1000.3037411037024));

         // line tangent to exit spiral
         Float64 length = curve->GetTotalLength();
         POC = curve->PointOnCurve(length - 50);
         dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(883.61562936445966, -1183.8304112645556));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(890.74331577219289, -1190.8443728455015));

         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(703.20889, -1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pbt, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(813.501198, -1119.948289));

         // again, but don't project back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(813.501198, -1119.948289));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi1, pft);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(507.50055, -1001.07029));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(1000.0, -1300.0));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(507.50055, -1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, -900);
         cp2.Move(700, -900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, -1100);
         cp2.Move(700, -1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(787.96427, -1099.99997));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, -1500);
         cp2.Move(700, -1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1200.0, -1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(800, -1000);
         cp2.Move(1100, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(600, -1000);
         cp2.Move(900, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(617.666636, -1017.666636));

         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(200, -1000);
         cp2.Move(500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(200.0, -1000.0));

         // again, but don't project curve
         cp1.Move(200, -1000);
         cp2.Move(500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, -1000);
         cp2.Move(1000, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(1000.0, -1300.0));;

         // again, but project only back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, -1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(690, -1000);
         cp2.Move(710, -1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(Test10b)
      {
         // same as Test10a except the direction of the curve is reverse

         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the left
         // Spiral lengths overlap
         // PBT = (1000,-1300)
         // PI  = (700,-1000)
         // PFT = (0,-1000)
         // R   = 500
         // Entry Spiral Length = 200
         // Exit Spiral Length = 100
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(1000, -1300);
         WBFL::Geometry::Point2d pi(700, -1000);
         WBFL::Geometry::Point2d pft(0, -1000);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 200);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 100);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         // create a line
         WBFL::Geometry::Line2d line;

         // Important curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(505.64225645686224, -1000.9854331731150));

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(818.84459859920526, -1124.3794191254133));

         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(684.65428056880842, -1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(809.35182374575743, -1116.5668976835791));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(508.67043163106791, -1001.1261389033072));

         // intersect circular curve in two places
         // first locate two points on the curve
         Float64 length = curve->GetTotalLength();
         auto cp1 = curve->PointOnCurve(length - 140);
         auto cp2 = curve->PointOnCurve(length - 110);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(578.53372538212068, -1008.9111895010718));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(548.87503670886008, -1004.4287172526595));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         cp1 = curve->PointOnCurve(length - 151);
         cp2 = curve->PointOnCurve(length - 150);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(589.33347, -1010.99939));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(588.35360, -1010.79974));

         // line tangent to exit spiral
         auto POC = curve->PointOnCurve(length - 50);
         auto dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(489.03247, -1000.41664));

         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(484.03375483745350, -1000.3037411037024));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(474.03507484100646, -1000.1429151347374));

         // line tangent to exit spiral
         POC = curve->PointOnCurve(50);
         dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(880.04038989655419, -1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(890.74331577219289, -1190.8443728455015));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(883.61562929997842, -1183.8304112013670));

         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(703.20889, -1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pft, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(813.50119, -1119.94828));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(813.50119, -1119.94828));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi2, pbt);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, -1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(507.50056, -1001.07029));

         // again, but don't project back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(507.50056, -1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, -900);
         cp2.Move(700, -900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, -1100);
         cp2.Move(700, -1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(787.96427, -1099.99998));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, -1500);
         cp2.Move(700, -1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1200.0, -1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(800, -1000);
         cp2.Move(1100, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(600, -1000);
         cp2.Move(900, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(617.66664, -1017.66664));

         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(200, -1000);
         cp2.Move(500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(200.0, -1000.0));

         // again, but don't project curve
         cp1.Move(200, -1000);
         cp2.Move(500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, -1000);
         cp2.Move(1000, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, -1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but project only back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(1000.0, -1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(690, -1000);
         cp2.Move(710, -1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(Test11a)
      {
         // same as Test8 except curve has been mirrored about the X axis and the Y axis

         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the left
         // Spiral lengths overlap
         // PBT = (0,-1000)
         // PI  = (-700,-1000)
         // PFT = (-1000,-1300)
         // R   = 500
         // Entry Spiral Length = 100
         // Exit Spiral Length = 200
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(0, -1000);
         WBFL::Geometry::Point2d pi(-700, -1000);
         WBFL::Geometry::Point2d pft(-1000, -1300);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 200);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         // create a line
         WBFL::Geometry::Line2d line;

         // Important curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, -1000.9854331731150));

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, -1124.3794191254133));

         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, -1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-508.67043163106791, -1001.1261389033072));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-809.35182374575743, -1116.5668976835791));

         // intersect circular curve in two places
         // first locate two points on the curve
         auto cp1 = curve->PointOnCurve(110);
         auto cp2 = curve->PointOnCurve(140);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-548.87503670886008, -1004.4287172526595));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-578.53372538212068, -1008.9111895010718));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         cp1 = curve->PointOnCurve(150);
         cp2 = curve->PointOnCurve(151);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-588.35360, -1010.79974));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-589.33347, -1010.99939));

         // line tangent to entry spiral
         auto POC = curve->PointOnCurve(50);
         auto dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-474.03507484100646, -1000.1429151347374));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-484.03375483745350, -1000.3037411037024));

         // line tangent to exit spiral
         Float64 length = curve->GetTotalLength();
         POC = curve->PointOnCurve(length - 50);
         dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-883.61562929997842, -1183.8304112013670));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-890.74331577219289, -1190.8443728455015));

         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, -1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pbt, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));

         // again, but don't project back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi1, pft);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, -900);
         cp2.Move(-700, -900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, -1100);
         cp2.Move(-700, -1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, -1099.99998));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, -1500);
         cp2.Move(-700, -1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, -1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(-800, -1000);
         cp2.Move(-1100, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(-600, -1000);
         cp2.Move(-900, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-617.66664, -1017.66664));

         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(-200, -1000);
         cp2.Move(-500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-200.0, -1000.0));

         // again, but don't project curve
         cp1.Move(-200, -1000);
         cp2.Move(-500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, -1000);
         cp2.Move(-1000, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

         // again, but project only back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(-690, -1000);
         cp2.Move(-710, -1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(Test11b)
      {
         // same as Test10b except the direction of the curve is reverse

         /////////////////////////////////////////////////////
         // Test a non-symmetrical spiral-curve-spiral to the right
         // Spiral lengths overlap
         // PBT = (-1000,-1300)
         // PI  = (-700,-1000)
         // PFT = (0,-1000)
         // R   = 500
         // Entry Spiral Length = 200
         // Exit Spiral Length = 100
         auto curve = CompoundCurve::Create();

         WBFL::Geometry::Point2d pbt(-1000, -1300);
         WBFL::Geometry::Point2d pi(-700, -1000);
         WBFL::Geometry::Point2d pft(0, -1000);

         curve->SetPBT(pbt);
         curve->SetPI(pi);
         curve->SetPFT(pft);

         curve->SetRadius(500);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 200);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 100);

         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Right);

         // create a line
         WBFL::Geometry::Line2d line;

         // Important curve points
         auto cc = curve->GetCC();
         auto spi1 = curve->GetSPI(CompoundCurve::SpiralLocation::Entry);
         auto spi2 = curve->GetSPI(CompoundCurve::SpiralLocation::Exit);

         // make line intersect exit spiral
         line.ThroughPoints(cc, spi2);
         auto vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-505.64225645686224, -1000.9854331731150));

         // make line intersect entry spiral
         line.ThroughPoints(cc, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-818.84459859920526, -1124.3794191254133));

         // make line intersect circular curve
         line.ThroughPoints(cc, pi);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-684.65428056880842, -1040.6952164811710));

         // intersect both spirals at once
         line.ThroughPoints(spi1, spi2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-809.35182374575743, -1116.5668976835791));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-508.67043163106791, -1001.1261389033072));

         // intersect circular curve in two places
         // first locate two points on the curve
         Float64 length = curve->GetTotalLength();
         auto cp1 = curve->PointOnCurve(length - 140);
         auto cp2 = curve->PointOnCurve(length - 110);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-578.53372538212068, -1008.9111895010718));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-548.87503670886008, -1004.4287172526595));

         // intersect circular curve in two places 
         // (again, but make the intersection points really close)
         // first locate two points on the curve
         auto POC = curve->PointOnCurve(length - 50);
         auto dir = curve->GetBearing(length - 50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-489.03247, -1000.41664));


         // intersect entry spiral in 2 locations
         cp1 = curve->PointOnCurve(length - 45);
         cp2 = curve->PointOnCurve(length - 35);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-484.03375483745350, -1000.3037411037024));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-474.03507484100646, -1000.1429151347374));

         // line tangent to exit spiral
         POC = curve->PointOnCurve(50);
         dir = curve->GetBearing(50);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

         // reverse the direction of the tangent line
         dir.Increment(M_PI);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-880.04038989655419, -1180.3350144338078));

         // intersect exit spiral in 2 locations
         cp1 = curve->PointOnCurve(35);
         cp2 = curve->PointOnCurve(45);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-890.74331577219289, -1190.8443728455015));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-883.61562929997842, -1183.8304112013670));


         // line tangent to circular curve
         POC = curve->PointOnCurve(length / 2);
         dir = curve->GetBearing(length / 2);
         line.SetExplicit(POC, WBFL::Geometry::Vector2d(1.0, dir));
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-703.20889, -1049.03367));

         // line intersect back tangent and exit spiral
         line.ThroughPoints(pft, spi1);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but don't project back
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-813.50119, -1119.94828));

         // line intersect fwd tangent and entry spiral
         line.ThroughPoints(spi2, pbt);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));

         // again, but don't project ahead
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-507.50056, -1001.07029));

         // no intersection with line parallel to entry tangent
         // outside of curve
         cp1.Move(0, -900);
         cp2.Move(-700, -900);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(0, -1100);
         cp2.Move(-700, -1100);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-787.96427, -1099.99998));

         // again, but on inside of curve (intersect with ahead tangent projected)
         cp1.Move(0, -1500);
         cp2.Move(-700, -1500);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1200.0, -1500.0));

         // again, but don't project curve
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line parallel to exit tangent
         // outside of curve
         cp1.Move(-800, -1000);
         cp2.Move(-1100, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // again, but on inside of curve (intersect with curve)
         cp1.Move(-600, -1000);
         cp2.Move(-900, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-617.66664, -1017.66664));

         // again, but on inside of curve (intersect with projected tangent)
         cp1.Move(-200, -1000);
         cp2.Move(-500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-200.0, -1000.0));

         // again, but don't project curve
         cp1.Move(-200, -1000);
         cp2.Move(-500, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // no intersection with line that cross both entry/entry tangent (inside of curve)
         cp1.Move(0, -1000);
         cp2.Move(-1000, -1300);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);

         // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
         vPoints = curve->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 2);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));
         Assert::IsTrue(vPoints.back() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but project only back
         vPoints = curve->Intersect(line, false, true);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(0.0, -1000.0));

         // again, but project only ahead
         vPoints = curve->Intersect(line, true, false);
         Assert::IsTrue(vPoints.size() == 1);
         Assert::IsTrue(vPoints.front() == WBFL::Geometry::Point2d(-1000.0, -1300.0));

         // no intersection with line that cross both entry/entry tangent (outside of curve)
         cp1.Move(-690, -1000);
         cp2.Move(-710, -1010);
         line.ThroughPoints(cp1, cp2);
         vPoints = curve->Intersect(line, false, false);
         Assert::IsTrue(vPoints.size() == 0);
      }

      TEST_METHOD(CreateOffsetPath)
      {
         auto curve = CompoundCurve::Create();

         curve->SetPBT(WBFL::Geometry::Point2d(0, 1000));
         curve->SetPI(WBFL::Geometry::Point2d(1000, 1000));
         curve->SetPFT(WBFL::Geometry::Point2d(1000, 1500));
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Entry, 100);
         curve->SetSpiralLength(CompoundCurve::SpiralLocation::Exit, 50);
         curve->SetRadius(1000.0);
         Assert::IsTrue(curve->GetCurveDirection() == CurveDirection::Left);

         // offset to the right (radius increases)
         auto path_elements = curve->CreateOffsetPath(500);
         Assert::AreEqual((size_t)3, path_elements.size());
         auto offset_entry_spiral = std::dynamic_pointer_cast<CubicSpline>(path_elements[0]);
         auto offset_curve = std::dynamic_pointer_cast<CircularCurve>(path_elements[1]);
         auto offset_exit_spiral = std::dynamic_pointer_cast<CubicSpline>(path_elements[2]);
         Assert::IsNotNull(offset_entry_spiral.get());
         Assert::IsNotNull(offset_curve.get());
         Assert::IsNotNull(offset_exit_spiral.get());
         Assert::AreEqual(1500.0, offset_curve->GetRadius());
         Assert::IsTrue(WBFL::Geometry::Point2d(-50.099997964221757, 500.0) == offset_entry_spiral->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(74.864589564469000, 502.29123887380922) == offset_entry_spiral->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(74.864589564469000, 502.29123887380922) == offset_curve->GetPC());
         Assert::IsTrue(WBFL::Geometry::Point2d(1464.6428025222817, 571.83811491332131) == offset_curve->GetPI());
         Assert::IsTrue(WBFL::Geometry::Point2d(1499.4271100720034, 1962.9205355941872) == offset_curve->GetPT());
         Assert::IsTrue(WBFL::Geometry::Point2d(1499.4271100720034, 1962.9205355941872) == offset_exit_spiral->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(1500.0000000000000, 2025.4161086419674) == offset_exit_spiral->GetEndPoint());

         // offset to the left (radius decreases)
         path_elements = curve->CreateOffsetPath(-500);
         Assert::AreEqual((size_t)3, path_elements.size());
         offset_entry_spiral = std::dynamic_pointer_cast<CubicSpline>(path_elements[0]);
         offset_curve = std::dynamic_pointer_cast<CircularCurve>(path_elements[1]);
         offset_exit_spiral = std::dynamic_pointer_cast<CubicSpline>(path_elements[2]);
         Assert::IsNotNull(offset_entry_spiral.get());
         Assert::IsNotNull(offset_curve.get());
         Assert::IsNotNull(offset_exit_spiral.get());
         Assert::AreEqual(500.0, offset_curve->GetRadius());
         Assert::IsTrue(WBFL::Geometry::Point2d(-50.099997964221757, 1500.0) == offset_entry_spiral->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(24.885420293790663, 1501.0414992687756) == offset_entry_spiral->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(24.885420293790663, 1501.0414992687756) == offset_curve->GetPC());
         Assert::IsTrue(WBFL::Geometry::Point2d(488.14482461306159, 1524.2237912819462) == offset_curve->GetPI());
         Assert::IsTrue(WBFL::Geometry::Point2d(499.73959379630071, 1987.9179315089000) == offset_curve->GetPT());
         Assert::IsTrue(WBFL::Geometry::Point2d(499.73959379630071, 1987.9179315089000) == offset_exit_spiral->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(500.0000000000000, 2025.4161086419674) == offset_exit_spiral->GetEndPoint());

         // offset to the left (offset greater than radius - curve degrades to nothing)
         path_elements = curve->CreateOffsetPath(-1500);
         Assert::IsTrue(path_elements.empty());
      }
   };
}
