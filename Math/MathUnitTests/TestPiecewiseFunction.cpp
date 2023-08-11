#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestPiecewiseFunction)
	{
	public:
		
		TEST_METHOD(Test1)
		{
         PiecewiseFunction fun1;
         Assert::IsTrue(fun1.AddPoint(WBFL::Geometry::Point2d(-4, -2)) == 1);
         Assert::IsTrue(fun1.AddPoint(WBFL::Geometry::Point2d(-3, -1)) == 2);
         Assert::IsTrue(fun1.AddPoint(WBFL::Geometry::Point2d(1, 2)) == 3);
         Assert::IsTrue(fun1.AddPoint(WBFL::Geometry::Point2d(3, -1)) == 4);
         Assert::IsTrue(fun1.GetRange() == Range(-4, Range::BoundType::Bound, 3, Range::BoundType::Bound));
         Assert::IsTrue(fun1.GetPointCount() == 4);
         Assert::IsTrue(fun1.Evaluate(-4) == -2);
         Assert::IsTrue(fun1.Evaluate(-3) == -1);
         Assert::IsTrue(fun1.Evaluate(1) == 2);
         Assert::IsTrue(fun1.Evaluate(3) == -1);
         Assert::IsTrue(IsZero(fun1.Evaluate(-5. / 3.)));
         Assert::IsTrue(IsZero(fun1.Evaluate(7. / 3.)));
         Assert::IsTrue(fun1.Evaluate(0.0) == 1.25);
         Assert::IsTrue(fun1.GetPoint(1) == WBFL::Geometry::Point2d(-3, -1));

         // create another function
         std::vector<WBFL::Geometry::Point2d> pvec;
         pvec.emplace_back(-5, 1);
         pvec.emplace_back(-4.1, 1);
         pvec.emplace_back(-3.4, 1);
         pvec.emplace_back(0.0, 1);
         pvec.emplace_back(2.2, 1);
         pvec.emplace_back(5, 1);
         PiecewiseFunction fun2(pvec);
         Assert::IsTrue(fun2.GetPoints() == pvec);
         Assert::IsTrue(fun2.Evaluate(0.0) == 1);
         Assert::IsTrue(fun2.Evaluate(3.0) == 1);
         try
         {
            fun2.Evaluate(-7); // out of bounds
         }
         catch (XFunction& e)
         {
            Assert::IsTrue(e.GetReasonCode() == XFunction::Reason::Undefined);
         }
         // intersection
         WBFL::Geometry::Point2d ip1, ip2;
         Range r(-3.5, Range::BoundType::Bound, .9, Range::BoundType::Bound);
         Assert::IsTrue(fun1.Intersect(fun2, r, &ip1) == 1);
         Assert::IsTrue(ip1 == WBFL::Geometry::Point2d(-1. / 3., 1));
         Assert::IsTrue(fun2.Intersect(fun1, r, &ip2) == 1);
         Assert::IsTrue(ip1 == ip2);

         r.SetLeftBoundLocation(1);
         r.SetRightBoundLocation(250);
         Assert::IsTrue(fun1.Intersect(fun2, r, &ip1) == 1);
         Assert::IsTrue(fun2.Intersect(fun1, r, &ip2) == 1);
         Assert::IsTrue(ip1 == WBFL::Geometry::Point2d(5. / 3., 1));
         Assert::IsTrue(ip1 == ip2);

         // set where an intersection does not occur
         r.SetLeftBoundLocation(0.9);
         r.SetRightBoundLocation(1.1);
         Assert::IsTrue(fun1.Intersect(fun2, r, &ip1) == 0);
         Assert::IsTrue(fun2.Intersect(fun1, r, &ip2) == 0);

         r.SetLeftBoundLocation(-100);
         r.SetRightBoundLocation(-50);
         Assert::IsTrue(fun1.Intersect(fun2, r, &ip1) == 0);
         Assert::IsTrue(fun2.Intersect(fun1, r, &ip1) == 0);

         r.SetLeftBoundLocation(100);
         r.SetRightBoundLocation(250);
         Assert::IsTrue(fun1.Intersect(fun2, r, &ip1) == 0);
         Assert::IsTrue(fun2.Intersect(fun1, r, &ip1) == 0);

         // GetMaximumsInRange
         Float64 fmin, fmax;
         r.SetLeftBoundLocation(-3.5);
         r.SetRightBoundLocation(1.0);
         fun1.GetMaximumsInRange(r, &fmin, &fmax);
         Assert::IsTrue(fmin == -1.5);
         Assert::IsTrue(fmax == 2.0);

         r.SetLeftBoundLocation(-4.0);
         r.SetRightBoundLocation(3.0);
         fun1.GetMaximumsInRange(r, &fmin, &fmax);
         Assert::IsTrue(fmin == -2.0);
         Assert::IsTrue(fmax == 2.0);

         r.SetLeftBoundLocation(2.0);
         r.SetRightBoundLocation(2.5);
         fun1.GetMaximumsInRange(r, &fmin, &fmax);
         Assert::IsTrue(fmin == -0.25);
         Assert::IsTrue(fmax == 0.5);

         try
         {
            r.SetLeftBoundLocation(2.0);
            r.SetRightBoundLocation(5.0);
            fun1.GetMaximumsInRange(r, &fmin, &fmax);
         }
         catch (XFunction& e)
         {
            Assert::IsTrue(e.GetReasonCode() == XFunction::Reason::Undefined);
         }
      }

      TEST_METHOD(Test2)
      {
         PiecewiseFunction fn;
         try
         {
            auto result = fn.Evaluate(10.0);
            Assert::Fail(); // should not get here
         }
         catch (XFunction& e)
         {
            Assert::IsTrue(e.GetReasonCode() == XFunction::Reason::Undefined);
         }

         fn.AddPoint(0, 20);
         fn.SetOutOfRangeBehavior(PiecewiseFunction::OutOfRangeBehavior::ThrowException);
         try
         {
            auto result = fn.Evaluate(10.0);
            Assert::Fail(); // should not get here
         }
         catch (XFunction& e)
         {
            Assert::IsTrue(e.GetReasonCode() == XFunction::Reason::Undefined);
         }

         fn.SetOutOfRangeBehavior(PiecewiseFunction::OutOfRangeBehavior::ExtendOuterValue);
         try
         {
            auto result = fn.Evaluate(10.0);
            Assert::AreEqual(20.0, result);
         }
         catch ([[maybe_unused]] XFunction& e)
         {
            Assert::Fail(); // should not get here
         }

         fn.AddPoint(20, 40);
         fn.SetOutOfRangeBehavior(PiecewiseFunction::OutOfRangeBehavior::Extrapolate);
         try
         {
            auto result = fn.Evaluate(40.0);
            Assert::AreEqual(60.0, result);
         }
         catch ([[maybe_unused]] XFunction& e)
         {
            Assert::Fail(); // should not get here
         }

      }
	};
}
