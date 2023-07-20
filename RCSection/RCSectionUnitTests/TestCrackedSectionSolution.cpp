#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;
using namespace WBFL::Geometry;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestCrackedSectionSolution)
	{
	public:
		
		TEST_METHOD(Test)
		{
			CrackedSectionSolution solution1;
			Assert::IsTrue(solution1.GetCentroid() == Point2d(0, 0));
			Assert::AreEqual((IndexType)0, solution1.GetSliceCount());

			std::vector<std::unique_ptr<CrackedSectionSlice>> slices;
			slices.emplace_back(std::make_unique<CrackedSectionSlice>(0, std::shared_ptr<Shape>(), 10.0, Point2d(0, 0), 100, 200));
			slices.emplace_back(std::make_unique<CrackedSectionSlice>(0, std::shared_ptr<Shape>(), 10.0, Point2d(0, 1), 200, 400));
			slices.emplace_back(std::make_unique<CrackedSectionSlice>(0, std::shared_ptr<Shape>(), 10.0, Point2d(0, 2), 300, 600));
			solution1.InitSolution(Point2d(10, 10), std::move(slices));
			Assert::IsTrue(solution1.GetCentroid() == Point2d(10, 10));
			Assert::AreEqual((IndexType)3, solution1.GetSliceCount());

			slices.emplace_back(std::make_unique<CrackedSectionSlice>(0, std::shared_ptr<Shape>(), 10.0, Point2d(0, 0), 100, 200));
			slices.emplace_back(std::make_unique<CrackedSectionSlice>(0, std::shared_ptr<Shape>(), 10.0, Point2d(0, 1), 200, 400));
			slices.emplace_back(std::make_unique<CrackedSectionSlice>(0, std::shared_ptr<Shape>(), 10.0, Point2d(0, 2), 300, 600));
			CrackedSectionSolution solution2(Point2d(50, 50), std::move(slices));
			Assert::IsTrue(solution2.GetCentroid() == Point2d(50, 50));
			Assert::AreEqual((IndexType)3, solution2.GetSliceCount());
		}
	};
}
