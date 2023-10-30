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
		}
	};
}
