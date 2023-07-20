#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSurfacePoint)
	{
	public:
		
		TEST_METHOD(Test)
		{
			auto point = SurfacePoint::Create(500.00, 10.0, 15.0, 30.0, WBFL::Geometry::Point2d(50, 50));
			Assert::IsTrue(point->GetStation() == Station(500));
			Assert::IsTrue(point->GetNormalOffset() == 10.0);
			Assert::IsTrue(point->GetCutlineOffset() == 15.0);
			Assert::IsTrue(point->GetElevation() == 30.0);
			Assert::IsTrue(point->GetLocation() == WBFL::Geometry::Point2d(50, 50));
			Assert::IsTrue(point->GetPoint() == WBFL::Geometry::Point3d(50, 50, 30));
		}
	};
}
