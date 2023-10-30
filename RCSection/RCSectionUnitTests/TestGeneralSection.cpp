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
	};
}
