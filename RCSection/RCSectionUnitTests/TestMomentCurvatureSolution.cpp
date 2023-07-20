#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;
using namespace WBFL::Geometry;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestMomentCurvatureSolution)
	{
	public:
		
		TEST_METHOD(Test)
		{
			auto general_solution1 = std::make_unique<GeneralSectionSolution>();
			general_solution1->InitSolution(10.0, 10.0, 10.0, Line2d(Point2d(0, 0), Point2d(10, 10)), Point2d(0, 0), 0.0, Point2d(0, 0), 0.0, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);
			auto moment_solution1 = std::make_unique<MomentCapacitySolution>();
			moment_solution1->InitSolution(Plane3d(), Point2d(), Point2d(), 0.04, std::move(general_solution1));

			auto general_solution2 = std::make_unique<GeneralSectionSolution>();
			general_solution2->InitSolution(20.0, 20.0, 20.0, Line2d(Point2d(0, 0), Point2d(10, 0)), Point2d(0, 0), 0.0, Point2d(0, 0), 0.00, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);
			auto moment_solution2 = std::make_unique<MomentCapacitySolution>();
			moment_solution2->InitSolution(Plane3d(), Point2d(), Point2d(), 0.01, std::move(general_solution2));

			auto general_solution3 = std::make_unique<GeneralSectionSolution>();
			general_solution3->InitSolution(15.0, 15.0, 15.0, Line2d(Point2d(0, 0), Point2d(10, 5)), Point2d(0, 0), 0.0, Point2d(0, 0), 0.0, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);
			auto moment_solution3 = std::make_unique<MomentCapacitySolution>();
			moment_solution3->InitSolution(Plane3d(), Point2d(), Point2d(), 0.02, std::move(general_solution3));

			MomentCurvatureSolution solution;
			solution.AddPoint(std::move(moment_solution1));
			Assert::AreEqual((IndexType)1, solution.GetPointCount());

    		solution.AddPoint(std::move(moment_solution2));
			solution.AddPoint(std::move(moment_solution3));
			Assert::AreEqual((IndexType)3, solution.GetPointCount());

			Assert::AreEqual(sqrt(800.), solution.GetMaxMoment());
			Assert::AreEqual(0.01, solution.GetMaxMomentCurvature());
			auto p = solution.GetPeakCapacity();
			Assert::AreEqual(solution.GetMaxMoment(), p.first);
			Assert::AreEqual(solution.GetMaxMomentCurvature(), p.second);

			Assert::AreEqual(sqrt(800), solution.GetMoment(0));
			Assert::AreEqual(sqrt(450), solution.GetMoment(1));
			Assert::AreEqual(sqrt(200), solution.GetMoment(2));

			Assert::AreEqual(0.01, solution.GetCurvature(0));
			Assert::AreEqual(0.02, solution.GetCurvature(1));
			Assert::AreEqual(0.04, solution.GetCurvature(2));
		}
	};
}
