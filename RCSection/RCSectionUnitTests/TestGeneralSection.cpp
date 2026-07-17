#include "pch.h"
#include "CppUnitTest.h"
#include <GeomModel/GeomModel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestGeneralSection)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // work in KSI units
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

         // Materials

         // concrete
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

         // rebar
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

         // Shapes

         // main beam
         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(8 * 12);
         beam.SetWidth(4 * 12);

         // #6 rebar
         WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(22, 46), 0.37424);
         WBFL::Geometry::Circle bar2(WBFL::Geometry::Point2d(-22, 46), 0.37424);
         WBFL::Geometry::Circle bar3(WBFL::Geometry::Point2d(-22, -46), 0.37424);
         WBFL::Geometry::Circle bar4(WBFL::Geometry::Point2d(22, -46), 0.37424);

         section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);
         section->AddShape(_T("Bar 1"), bar1, rebar, concrete, nullptr, 1.0);
         section->AddShape(_T("Bar 2"), bar2, rebar, concrete, nullptr, 1.0);
         section->AddShape(_T("Bar 3"), bar3, rebar, concrete, nullptr, 1.0);
         section->AddShape(_T("Bar 4"), bar4, rebar, concrete, nullptr, 1.0);

         Assert::IsTrue(section->GetShapeCount() == 5);
         Assert::IsTrue(section->GetName(3) == std::_tstring(_T("Bar 3")));
      }

      TEST_METHOD(TestPrimaryShapeIndex)
      {
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(8 * 12);
         beam.SetWidth(4 * 12);

         WBFL::Geometry::Circle bar(WBFL::Geometry::Point2d(22, 46), 0.37424);

         // no primary shape has been designated yet
         Assert::IsTrue(section->GetPrimaryShapeIndex() == INVALID_INDEX);

         section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);
         Assert::IsTrue(section->GetPrimaryShapeIndex() == 0);

         // "last one wins" - designating a later shape as primary supersedes the earlier one
         section->AddShape(_T("Bar"), bar, concrete, concrete, nullptr, 1.0, true);
         Assert::IsTrue(section->GetPrimaryShapeIndex() == 1);

         // explicit SetPrimaryShapeIndex overrides whatever AddShape set
         section->SetPrimaryShapeIndex(0);
         Assert::IsTrue(section->GetPrimaryShapeIndex() == 0);
      }

      TEST_METHOD(TestAddShapeSharedPtrOverload)
      {
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

         std::shared_ptr<const WBFL::Geometry::Shape> beam(std::make_shared<WBFL::Geometry::Rectangle>(WBFL::Geometry::Point2d(0, 0), 4 * 12, 8 * 12));

         section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);

         Assert::IsTrue(section->GetShapeCount() == 1);
         Assert::IsTrue(section->GetName(0) == std::_tstring(_T("Beam")));
         // the shared_ptr overload stores the shape by reference (no clone) - confirm it's the same object
         Assert::IsTrue(&section->GetShape(0) == beam.get());
      }

      TEST_METHOD(TestAccessorRoundTrip)
      {
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(8 * 12);
         beam.SetWidth(4 * 12);

         std::shared_ptr<WBFL::Geometry::Plane3d> initialStrain(std::make_shared<WBFL::Geometry::Plane3d>());

         section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);

         // foreground material
         Assert::IsTrue(section->GetForegroundMaterial(0) == concrete);
         section->SetForegroundMaterial(0, rebar);
         Assert::IsTrue(section->GetForegroundMaterial(0) == rebar);

         // background material
         Assert::IsTrue(section->GetBackgroundMaterial(0) == nullptr);
         section->SetBackgroundMaterial(0, concrete);
         Assert::IsTrue(section->GetBackgroundMaterial(0) == concrete);

         // initial strain
         Assert::IsTrue(section->GetInitialStrain(0) == nullptr);
         section->SetInitialStrain(0, initialStrain);
         Assert::IsTrue(section->GetInitialStrain(0) == initialStrain);

         // elongation length
         Assert::IsTrue(IsEqual(section->GetElongationLength(0), 1.0));
         section->SetElongationLength(0, 0.5);
         Assert::IsTrue(IsEqual(section->GetElongationLength(0), 0.5));

         // shape
         std::shared_ptr<const WBFL::Geometry::Shape> newShape(std::make_shared<WBFL::Geometry::Rectangle>(WBFL::Geometry::Point2d(0, 0), 1.0, 1.0));
         section->SetShape(0, newShape);
         Assert::IsTrue(&section->GetShape(0) == newShape.get());
      }

      TEST_METHOD(TestEmptySection)
      {
         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());
         Assert::IsTrue(section->GetShapeCount() == 0);
         Assert::IsTrue(section->GetPrimaryShapeIndex() == INVALID_INDEX);
      }
	};
}
