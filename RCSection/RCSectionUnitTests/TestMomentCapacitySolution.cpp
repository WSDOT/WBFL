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

		TEST_METHOD(TestDepthComputations)
		{
			// neutral axis is the X-axis. Extreme compression point is 10 units "above" (y=10),
			// extreme tension point is 20 units "below" (y=-20). The compression resultant sits
			// between the neutral axis and the extreme compression point (y=6), and the tension
			// resultant sits between the neutral axis and the extreme tension point (y=-12).
			auto general_solution = std::make_unique<GeneralSectionSolution>();
			general_solution->InitSolution(0.0, 0.0, 0.0, Line2d(Point2d(0, 0), Point2d(10, 0)),
				Point2d(0, 6), 10.0,   // compression resultant location and magnitude
				Point2d(0, -12), 20.0, // tension resultant location and magnitude
				std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);

			MomentCapacitySolution solution;
			solution.InitSolution(Plane3d(), Point2d(0, 10), Point2d(0, -20), 0.0, std::move(general_solution));

			Assert::IsTrue(IsEqual(solution.GetDepthToNeutralAxis(), 10.0));
			Assert::IsTrue(IsEqual(solution.GetDepthToCompressionResultant(), 4.0)); // 10 - 6
			Assert::IsTrue(IsEqual(solution.GetDepthToTensionResultant(), 22.0));    // 10 + 12
			Assert::IsTrue(IsEqual(solution.GetMomentArm(), 18.0));                  // distance from (0,6) to (0,-12)
		}

		TEST_METHOD(TestDepthToCompressionResultantAtExtremePoint)
		{
			// boundary case: the compression resultant coincides with the extreme compression point
			auto general_solution = std::make_unique<GeneralSectionSolution>();
			general_solution->InitSolution(0.0, 0.0, 0.0, Line2d(Point2d(0, 0), Point2d(10, 0)),
				Point2d(0, 10), 10.0,
				Point2d(0, -20), 20.0,
				std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);

			MomentCapacitySolution solution;
			solution.InitSolution(Plane3d(), Point2d(0, 10), Point2d(0, -20), 0.0, std::move(general_solution));

			Assert::IsTrue(IsEqual(solution.GetDepthToCompressionResultant(), 0.0));
		}

		TEST_METHOD(TestGetMAndGeneralSectionSolution)
		{
			auto general_solution = std::make_unique<GeneralSectionSolution>();
			general_solution->InitSolution(10.0, 20.0, 30.0, Line2d(Point2d(0, 0), Point2d(10, 10)), Point2d(10, 10), 10.0, Point2d(20, 20), 20.0, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), false);

			MomentCapacitySolution solution;
			solution.InitSolution(Plane3d(), Point2d(30, 30), Point2d(40, 40), 0.01, std::move(general_solution));

			Assert::IsTrue(IsEqual(solution.GetM(), sqrt(20. * 20. + 30. * 30.)));

			const auto* pGeneralSolution = solution.GetGeneralSectionSolution();
			Assert::IsTrue(pGeneralSolution != nullptr);
			Assert::AreEqual(10.0, pGeneralSolution->GetFz());
		}
	};
}
