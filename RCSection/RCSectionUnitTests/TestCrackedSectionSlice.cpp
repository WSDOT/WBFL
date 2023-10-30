#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestCrackedSectionSlice)
	{
	public:
		
		TEST_METHOD(Test)
		{
			CrackedSectionSlice slice1(10, std::shared_ptr<WBFL::Geometry::Shape>(), 10.0, WBFL::Geometry::Point2d(10, 10), 500, 1000);
			CrackedSectionSlice slice2;
			slice2.InitSlice(10, std::shared_ptr<WBFL::Geometry::Shape>(), 10.0, WBFL::Geometry::Point2d(10, 10), 500, 1000);

			Assert::IsTrue(slice1.GetShapeIndex() == slice2.GetShapeIndex());
			Assert::IsTrue(slice1.GetCentroid() == slice2.GetCentroid());
			Assert::IsTrue(slice1.GetForegroundE() == slice2.GetForegroundE());
			Assert::IsTrue(slice1.GetBackgroundE() == slice2.GetBackgroundE());
		}
	};
}
