#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;
using namespace WBFL::Geometry;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestGeneralSectionSolution)
	{
	public:
		
		TEST_METHOD(Test)
		{
			GeneralSectionSolution solution;
			solution.InitSolution(10, 20, 30, Line2d(Point2d(0, 0), Point2d(10, 10)), Point2d(40, 40), 40, Point2d(50, 50), 50, std::move(std::vector<std::unique_ptr<GeneralSectionSlice>>()), true);
			Assert::AreEqual(10., solution.GetFz());
			Assert::AreEqual(20., solution.GetMx());
			Assert::AreEqual(30., solution.GetMy());
			Assert::IsTrue(solution.GetNeutralAxis() == Line2d(Point2d(0, 0), Point2d(10, 10)));
			Assert::AreEqual(M_PI / 4, solution.GetNeutralAxisDirection());
			Assert::IsTrue(solution.GetCompressionResultantLocation() == Point2d(40, 40));
			Assert::AreEqual(40., solution.GetCompressionResultant());
			Assert::IsTrue(solution.GetTensionResultantLocation() == Point2d(50, 50));
			Assert::AreEqual(50., solution.GetTensionResultant());
			Assert::AreEqual((IndexType)0, solution.GetSliceCount());
			Assert::IsTrue(solution.ExceededStrainLimits());

			// GetM() = sqrt(mx^2 + my^2)
			Assert::IsTrue(IsEqual(solution.GetM(), sqrt(20. * 20. + 30. * 30.)));

			// GetMomentArm() = distance between the compression and tension resultant locations
			Assert::IsTrue(IsEqual(solution.GetMomentArm(), Point2d(40, 40).Distance(Point2d(50, 50))));
		}

		TEST_METHOD(TestSlicesAndFindSlices)
		{
			std::vector<std::unique_ptr<GeneralSectionSlice>> slices;
			slices.emplace_back(std::make_unique<GeneralSectionSlice>((IndexType)0, std::shared_ptr<const WBFL::Geometry::Shape>(), 1.0, Point2d(0, 1), 0., 0., 0., 0., 0., std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), false));
			slices.emplace_back(std::make_unique<GeneralSectionSlice>((IndexType)1, std::shared_ptr<const WBFL::Geometry::Shape>(), 2.0, Point2d(0, 2), 0., 0., 0., 0., 0., std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), false));
			slices.emplace_back(std::make_unique<GeneralSectionSlice>((IndexType)0, std::shared_ptr<const WBFL::Geometry::Shape>(), 3.0, Point2d(0, 3), 0., 0., 0., 0., 0., std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), false));

			GeneralSectionSolution solution;
			solution.InitSolution(0, 0, 0, Line2d(Point2d(0, 0), Point2d(10, 10)), Point2d(0, 0), 0, Point2d(0, 0), 0, std::move(slices), false);

			Assert::AreEqual((IndexType)3, solution.GetSliceCount());
			Assert::AreEqual(1.0, solution.GetSlice(0)->GetArea());
			Assert::AreEqual(2.0, solution.GetSlice(1)->GetArea());
			Assert::AreEqual(3.0, solution.GetSlice(2)->GetArea());

			auto shape0Slices = solution.FindSlices(0);
			Assert::AreEqual((size_t)2, shape0Slices.size());
			Assert::AreEqual(1.0, shape0Slices[0]->GetArea());
			Assert::AreEqual(3.0, shape0Slices[1]->GetArea());

			auto shape1Slices = solution.FindSlices(1);
			Assert::AreEqual((size_t)1, shape1Slices.size());
			Assert::AreEqual(2.0, shape1Slices[0]->GetArea());

			auto noMatchSlices = solution.FindSlices(99);
			Assert::AreEqual((size_t)0, noMatchSlices.size());
		}

		TEST_METHOD(TestCopyAndAssign)
		{
			std::vector<std::unique_ptr<GeneralSectionSlice>> slices;
			slices.emplace_back(std::make_unique<GeneralSectionSlice>((IndexType)0, std::shared_ptr<const WBFL::Geometry::Shape>(), 5.0, Point2d(1, 1), 0., 0., 0., 0., 0., std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), false));

			GeneralSectionSolution solution;
			solution.InitSolution(10, 20, 30, Line2d(Point2d(0, 0), Point2d(10, 10)), Point2d(40, 40), 40, Point2d(50, 50), 50, std::move(slices), true);

			// copy constructor
			GeneralSectionSolution copy(solution);
			Assert::AreEqual(solution.GetFz(), copy.GetFz());
			Assert::AreEqual(solution.GetMx(), copy.GetMx());
			Assert::AreEqual(solution.GetMy(), copy.GetMy());
			Assert::AreEqual(solution.GetSliceCount(), copy.GetSliceCount());
			Assert::AreEqual(solution.GetSlice(0)->GetArea(), copy.GetSlice(0)->GetArea());
			Assert::AreEqual(solution.ExceededStrainLimits(), copy.ExceededStrainLimits());

			// assignment operator
			GeneralSectionSolution assigned;
			assigned = solution;
			Assert::AreEqual(solution.GetFz(), assigned.GetFz());
			Assert::AreEqual(solution.GetSliceCount(), assigned.GetSliceCount());
			Assert::AreEqual(solution.GetSlice(0)->GetArea(), assigned.GetSlice(0)->GetArea());
		}
	};
}
