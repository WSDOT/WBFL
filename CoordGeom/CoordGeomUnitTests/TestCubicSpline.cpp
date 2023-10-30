#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCubicSpline)
	{
	public:
		
		TEST_METHOD(Test)
		{
         ////////////////////////////////////////////
         ////////////////////////////////////////////
         // Tests Needed
         // PointOnCurve with a point before and after the start/end of spline
         // DistanceFromStart with a point that projects onto the back/ahead tangents
         // Spline with no points (should be an angle point!)
         ////////////////////////////////////////////
         ////////////////////////////////////////////

         auto spline = CubicSpline::Create();

         // test spline by evaluating it against a known solution
         // see http://math.fullerton.edu/mathews/n2003/splines/CubicSplinesMod/Links/CubicSplinesMod_lnk_4.html
         spline->AddPoint(0, 1);
         spline->AddPoint(1, 0);
         spline->AddPoint(2, 0);
         spline->AddPoint(3, 1);
         spline->AddPoint(4, 2);
         spline->AddPoint(5, 2);
         spline->AddPoint(6, 1);
         spline->SetStartDirection(atan2(-0.2, 1));
         spline->SetEndDirection(atan2(-2.5, 1));

         // before the start of the spline->.. the input is the distance along the spline-> before the spline we assume
         // a straight line tangent to the spline-> the distance is measured along the line which is the hypotenuse
         // of a triangle, not the x-direction. this is why the correct answer is a little short of (-1.0,1.2)
         auto p = spline->PointOnCurve(-1);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(-0.98058067569092022, 1.1961161351381839));
         p = spline->PointOnCurve(0);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(0, 1.0));

         // test spline slope (derivative = bearing)
         auto d = spline->GetBearing(-1);
         Assert::IsTrue(IsEqual(tan(d), -0.2));

         d = spline->GetBearing(0);
         Assert::IsTrue(IsEqual(tan(d), -0.2));

         d = spline->GetBearing(50);
         Assert::IsTrue(IsEqual(tan(d), -2.5));

         // spline length
         Assert::IsTrue(IsEqual(spline->GetLength(), 7.8778168718814285));

         // check the normal
         Assert::IsTrue(IsEqual(1 / 0.2, tan(spline->GetNormal(0))));
         Assert::IsTrue(IsEqual(1 / 0.2, tan(spline->GetNormal(-10))));

         // bearing and normal check at end
         Assert::IsTrue(IsEqual(-2.5, tan(spline->GetBearing(spline->GetLength()))));
         Assert::IsTrue(IsEqual(-2.5, tan(spline->GetBearing(spline->GetLength() + 10))));

         Assert::IsTrue(IsEqual(1 / 2.5, tan(spline->GetNormal(spline->GetLength()))));
         Assert::IsTrue(IsEqual(1 / 2.5, tan(spline->GetNormal(spline->GetLength() + 10))));

         // project a point onto the spline
         p.Move(4, 0);

         WBFL::Geometry::Point2d pntOnSpline;
         Float64 distFromStart;
         bool bOnProjection;
         std::tie(pntOnSpline, distFromStart, bOnProjection) = spline->ProjectPoint(p);
         Assert::IsTrue(pntOnSpline == WBFL::Geometry::Point2d(2.9212265014648437, 0.90555618284927675));
         Assert::IsTrue(IsEqual(distFromStart, 3.8186530950157791));
         Assert::IsTrue(bOnProjection == false);

         // project a point before start of spline
         p.Move(-10, 0);
         std::tie(pntOnSpline, distFromStart, bOnProjection) = spline->ProjectPoint(p);
         Assert::IsTrue(pntOnSpline == WBFL::Geometry::Point2d(-9.4230769230769234, 2.8846153846153855));
         Assert::IsTrue(IsEqual(distFromStart, -9.6096906217710174));
         Assert::IsTrue(bOnProjection == true);

         // project a point after start of spline
         p.Move(10, 0);
         std::tie(pntOnSpline, distFromStart, bOnProjection) = spline->ProjectPoint(p);
         Assert::IsTrue(pntOnSpline == WBFL::Geometry::Point2d(6.8965517241379324, -1.2413793103448272));
         Assert::IsTrue(IsEqual(distFromStart, 10.291856268183103));
         Assert::IsTrue(bOnProjection == true);

         // create a line and test intersections
         WBFL::Geometry::Point2d pntStart(-10, 1), pntEnd(10, 1);
         WBFL::Geometry::Line2d line(pntStart, pntEnd);

         auto vPoints = spline->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 3);
         Assert::IsTrue(vPoints[0] == WBFL::Geometry::Point2d(0, 1));
         Assert::IsTrue(vPoints[1] == WBFL::Geometry::Point2d(3, 1));
         Assert::IsTrue(vPoints[2] == WBFL::Geometry::Point2d(6, 1));

         // move the line and test intersections again
         pntStart.Move(-10, 0.5);
         pntEnd.Move(10, 0.5);
         line.ThroughPoints(pntStart, pntEnd);

         vPoints = spline->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 3);
         Assert::IsTrue(vPoints[0] == WBFL::Geometry::Point2d(0.56655, 0.5));
         Assert::IsTrue(vPoints[1] == WBFL::Geometry::Point2d(2.56441, 0.5));
         Assert::IsTrue(vPoints[2] == WBFL::Geometry::Point2d(6.19999, 0.5));

         // move the line and test intersections again
         pntStart.Move(0, 1);
         pntEnd.Move(4, 2);
         line.ThroughPoints(pntStart, pntEnd);

         vPoints = spline->Intersect(line, true, true);
         Assert::IsTrue(vPoints.size() == 3);
         Assert::IsTrue(vPoints[0] == WBFL::Geometry::Point2d(0, 1));
         Assert::IsTrue(vPoints[1] == WBFL::Geometry::Point2d(4, 2));
         Assert::IsTrue(vPoints[2] == WBFL::Geometry::Point2d(4.39108, 2.09777));

         //////////////////////////////////////
         // slope should remain unchanged if the spline is offset/moved
         spline->Clear();
         Float64 offset = 10;
         spline->AddPoint(0 + offset, 1 + offset);
         spline->AddPoint(1 + offset, 0 + offset);
         spline->AddPoint(2 + offset, 0 + offset);
         spline->AddPoint(3 + offset, 1 + offset);
         spline->AddPoint(4 + offset, 2 + offset);
         spline->AddPoint(5 + offset, 2 + offset);
         spline->AddPoint(6 + offset, 1 + offset);
         spline->SetStartDirection(atan2(-0.2, 1));
         spline->SetEndDirection(atan2(-2.5, 1));

         // spline length
         Assert::IsTrue(IsEqual(spline->GetLength(), 7.8778168718814285));

         // check the normal
         Assert::IsTrue(IsEqual(1 / 0.2, tan(spline->GetNormal(0))));
         Assert::IsTrue(IsEqual(1 / 0.2, tan(spline->GetNormal(-10))));

         // bearing and normal check at end
         Assert::IsTrue(IsEqual(-2.5, tan(spline->GetBearing(spline->GetLength()))));
         Assert::IsTrue(IsEqual(-2.5, tan(spline->GetBearing(spline->GetLength() + 10))));

         Assert::IsTrue(IsEqual(1 / 2.5, tan(spline->GetNormal(spline->GetLength()))));
         Assert::IsTrue(IsEqual(1 / 2.5, tan(spline->GetNormal(spline->GetLength() + 10))));

         // now test the spline as a cogo object

         // quarter circle
         Float64 angle;
         spline->Clear();
         Float64 R = 10;
         Float64 cx = 0;
         Float64 cy = 0;
         IndexType nPoints = 5;
         for (IndexType i = 0; i < nPoints; i++)
         {
            angle = (M_PI / 2) * i / (nPoints - 1);
            spline->AddPoint(cx + R * cos(angle), cy + R * sin(angle));
         }
         spline->SetStartDirection(PI_OVER_2);
         spline->SetEndDirection(M_PI);
         Assert::IsTrue(IsEqual(spline->GetLength(), (2 * M_PI * R) / 4, 0.01));

         // straight line
         spline->Clear();

         spline->AddPoint(0, 0);
         spline->AddPoint(10, 0);
         spline->SetStartDirection(0);
         spline->SetEndDirection(0);

         p = spline->PointOnCurve(2.);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(2, 0));


         // curve line
         spline->Clear();

         spline->AddPoint(0, 0);
         spline->AddPoint(10, 10);
         spline->SetStartDirection(0);
         spline->SetEndDirection(M_PI / 4);

         p = spline->PointOnCurve(0.);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(0, 0));

         p = spline->PointOnCurve(2.);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(1.98136, 0.23124));

         p = spline->PointOnCurve(spline->GetLength());
         Assert::IsTrue(p == WBFL::Geometry::Point2d(10, 10));

         // another curve line - this data comes from a real model that didn't work correctly
         // until we fixed the spline object
         spline->Clear();
         spline->AddPoint(25.950838, 47.9880235);
         spline->AddPoint(148.83656, 196.75139);
         spline->SetStartDirection(0.97387);
         spline->SetEndDirection(0.750248);

         p = spline->PointOnCurve(0);
         Assert::IsTrue(p == WBFL::Geometry::Point2d(25.950838, 47.9880235));

         p = spline->PointOnCurve(spline->GetLength());
         Assert::IsTrue(p == WBFL::Geometry::Point2d(148.83656, 196.75139));
      }
	};
}
