#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestGeneralSectionSlice)
	{
	public:
		
		TEST_METHOD(Test)
		{
			GeneralSectionSlice slice((IndexType)0, std::shared_ptr<const WBFL::Geometry::Shape>(), 10.0, WBFL::Geometry::Point2d(0, 0), 0.1, 0.2, 0.3, 20., 10., std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), true);
			Assert::AreEqual((IndexType)0, slice.GetShapeIndex());
			Assert::AreEqual(10.0, slice.GetArea());
			Assert::IsTrue(slice.GetCentroid() == WBFL::Geometry::Point2d(0, 0));
			Assert::AreEqual(0.1, slice.GetInitialStrain());
			Assert::AreEqual(0.2, slice.GetIncrementalStrain());
			Assert::AreEqual(0.3, slice.GetTotalStrain());
			Assert::AreEqual(20.0, slice.GetForegroundStress());
			Assert::AreEqual(10.0, slice.GetBackgroundStress());
			Assert::IsTrue(std::shared_ptr<const WBFL::Materials::StressStrainModel>() == slice.GetForegroundMaterial());
			Assert::IsTrue(std::shared_ptr<const WBFL::Materials::StressStrainModel>() == slice.GetBackgroundMaterial());
		}
	};
}
