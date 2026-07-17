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
			Assert::IsTrue(slice.GetShape() == std::shared_ptr<const WBFL::Geometry::Shape>());
			Assert::IsTrue(slice.ExceededStrainLimit());
		}

		TEST_METHOD(TestCopyAndAssign)
		{
			std::shared_ptr<const WBFL::Materials::StressStrainModel> fg(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));
			std::shared_ptr<const WBFL::Materials::StressStrainModel> bg(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete2"), 5.0));
			GeneralSectionSlice slice((IndexType)2, std::shared_ptr<const WBFL::Geometry::Shape>(), 12.0, WBFL::Geometry::Point2d(3, 4), 0.15, 0.25, 0.40, 22.0, 11.0, fg, bg, true);

			// copy constructor
			GeneralSectionSlice copy(slice);
			Assert::AreEqual(slice.GetShapeIndex(), copy.GetShapeIndex());
			Assert::AreEqual(slice.GetArea(), copy.GetArea());
			Assert::IsTrue(slice.GetCentroid() == copy.GetCentroid());
			Assert::AreEqual(slice.GetInitialStrain(), copy.GetInitialStrain());
			Assert::AreEqual(slice.GetIncrementalStrain(), copy.GetIncrementalStrain());
			Assert::AreEqual(slice.GetTotalStrain(), copy.GetTotalStrain());
			Assert::AreEqual(slice.GetForegroundStress(), copy.GetForegroundStress());
			Assert::AreEqual(slice.GetBackgroundStress(), copy.GetBackgroundStress());
			Assert::IsTrue(slice.GetForegroundMaterial() == copy.GetForegroundMaterial());
			Assert::IsTrue(slice.GetBackgroundMaterial() == copy.GetBackgroundMaterial());
			Assert::AreEqual(slice.ExceededStrainLimit(), copy.ExceededStrainLimit());

			// assignment operator
			GeneralSectionSlice assigned;
			assigned = slice;
			Assert::AreEqual(slice.GetShapeIndex(), assigned.GetShapeIndex());
			Assert::AreEqual(slice.GetArea(), assigned.GetArea());
			Assert::IsTrue(slice.GetCentroid() == assigned.GetCentroid());
			Assert::AreEqual(slice.ExceededStrainLimit(), assigned.ExceededStrainLimit());
		}

		TEST_METHOD(TestDefaultConstructAndInitSlice)
		{
			GeneralSectionSlice slice;
			Assert::AreEqual((IndexType)INVALID_INDEX, slice.GetShapeIndex());
			Assert::AreEqual(0.0, slice.GetArea());
			Assert::IsFalse(slice.ExceededStrainLimit());

			slice.InitSlice((IndexType)1, std::shared_ptr<const WBFL::Geometry::Shape>(), 5.0, WBFL::Geometry::Point2d(1, 1), 0.01, 0.02, 0.03, 1.0, 2.0, std::shared_ptr<const WBFL::Materials::StressStrainModel>(), std::shared_ptr<const WBFL::Materials::StressStrainModel>(), false);
			Assert::AreEqual((IndexType)1, slice.GetShapeIndex());
			Assert::AreEqual(5.0, slice.GetArea());
			Assert::IsFalse(slice.ExceededStrainLimit());
		}
	};
}
