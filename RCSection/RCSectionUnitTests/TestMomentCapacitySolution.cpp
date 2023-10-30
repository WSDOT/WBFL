#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;
using namespace WBFL::Geometry;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestMomentCapacitySolution)
	{
	public:
		
		TEST_METHOD(Test)
		{
			auto general_solution = std::make_unique<GeneralSectionSolution>();
			general_solution->InitSolution(10.0, 20.0, 30.0, Line2d(Point2d(0, 0), Point2d(10, 10)), Point2d(10, 10), 10.0, Point2d(20, 20), 20.0, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);

			MomentCapacitySolution solution;
			solution.InitSolution(Plane3d(), Point2d(30, 30), Point2d(40, 40), 0.01, std::move(general_solution));
			Assert::AreEqual(10.0, solution.GetFz());
			Assert::AreEqual(20.0, solution.GetMx());
			Assert::AreEqual(30.0, solution.GetMy());
			Assert::AreEqual(0.0, solution.GetIncrementalStrainPlane().GetZ(10, 10));
			Assert::AreEqual(M_PI / 4, solution.GetNeutralAxisDirection());
			Assert::IsTrue(Point2d(10, 10) == solution.GetCompressionResultantLocation());
			Assert::AreEqual(10.0, solution.GetCompressionResultant());
			Assert::IsTrue(Point2d(20, 20) == solution.GetTensionResultantLocation());
			Assert::AreEqual(20.0, solution.GetTensionResultant());
			Assert::AreEqual(0.01, solution.GetCurvature());
			Assert::IsTrue(Point2d(30, 30) == solution.GetExtremeCompressionPoint());
			Assert::IsTrue(Point2d(40, 40) == solution.GetExtremeTensionPoint());
		}
	};
}
