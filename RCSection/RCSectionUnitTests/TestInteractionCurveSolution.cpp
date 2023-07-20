#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;
using namespace WBFL::Geometry;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestInteractionCurveSolution)
	{
	public:
		
		TEST_METHOD(Test)
		{
			auto general_solution1 = std::make_unique<GeneralSectionSolution>();
			general_solution1->InitSolution(10.0, 0.0, 0.0, Line2d(Point2d(0, 0), Point2d(10, 10)), Point2d(0, 0), 0.0, Point2d(0, 0), 0.0, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);
			auto moment_solution1 = std::make_unique<MomentCapacitySolution>();
			moment_solution1->InitSolution(Plane3d(), Point2d(), Point2d(), 0.0, std::move(general_solution1));

			auto general_solution2 = std::make_unique<GeneralSectionSolution>();
			general_solution2->InitSolution(20.0, 0.0, 0.0, Line2d(Point2d(0, 0), Point2d(10, 0)), Point2d(0, 0), 0.0, Point2d(0, 0), 0.00, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);
			auto moment_solution2 = std::make_unique<MomentCapacitySolution>();
			moment_solution2->InitSolution(Plane3d(), Point2d(), Point2d(), 0.01, std::move(general_solution2));

			auto general_solution3 = std::make_unique<GeneralSectionSolution>();
			general_solution3->InitSolution(15.0, 0.0, 0.0, Line2d(Point2d(0, 0), Point2d(10, 5)), Point2d(0, 0), 0.0, Point2d(0, 0), 0.0, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);
			auto moment_solution3 = std::make_unique<MomentCapacitySolution>();
			moment_solution3->InitSolution(Plane3d(), Point2d(), Point2d(), 0.0, std::move(general_solution3));

			InteractionCurveSolution solution;
			solution.AddSolutionPoint(std::move(moment_solution1));
			Assert::AreEqual((IndexType)1, solution.GetSolutionPointCount());

			solution.AddSolutionPoint(std::move(moment_solution2));
			Assert::AreEqual((IndexType)2, solution.GetSolutionPointCount());

			solution.AddSolutionPoint(std::move(moment_solution3));
			Assert::AreEqual((IndexType)3, solution.GetSolutionPointCount());

			// Initially the solution is not sorted
			Assert::AreEqual(10.0, solution.GetFz(0));
			Assert::AreEqual(20.0, solution.GetFz(1));
			Assert::AreEqual(15.0, solution.GetFz(2));

			// Sort by Fz
			solution.SortByFz();
			Assert::AreEqual(10.0, solution.GetFz(0));
			Assert::AreEqual(15.0, solution.GetFz(1));
			Assert::AreEqual(20.0, solution.GetFz(2));

			// Sort by neutral axis direction
			solution.SortByNeutralAxisDirection();
			Assert::AreEqual(20.0, solution.GetFz(0));
			Assert::AreEqual(15.0, solution.GetFz(1));
			Assert::AreEqual(10.0, solution.GetFz(2));

			const auto& sp = solution.GetSolutionPoint(0);
			Assert::AreEqual(20.0, sp.GetFz());
			Assert::AreEqual(0.01, sp.GetCurvature());
		}
	};
}
