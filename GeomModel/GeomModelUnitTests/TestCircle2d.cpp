#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCircle2d)
	{
	public:
		
		TEST_METHOD(ThreePointConstruction)
		{
			// valid 3 point circle
			Circle2d c3p(Point2d(0, 0), Point2d(10, 0), Point2d(5, 5));
			Assert::IsTrue(c3p.GetCenter() == Point2d(5, 0));
			Assert::AreEqual(c3p.GetRadius(),5.0);

			// invalid 3 point circle
			Assert::ExpectException<WBFL::Geometry::XGeometry>([]() {Circle2d c3pi(Point2d(0, 0), Point2d(0, 0), Point2d(0, 0)); });
		}

		TEST_METHOD(TwoPointConstruction)
		{
			Circle2d c2p(Point2d(0, 0), Point2d(10, 0));
			Assert::IsTrue(c2p.GetCenter() == Point2d(5, 0));
			Assert::IsTrue(IsEqual(c2p.GetRadius(), 5.0));
			Assert::IsTrue(c2p.IsPointOnPerimeter(Point2d(5, -5)));
		}
	};
}
