#include "pch.h"
#include "CppUnitTest.h"
#include <GeomModel/GeomModel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestGeneralSectionSolver)
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

         WBFL::Geometry::Point3d p1(-1000, 0, 0); // neutral axis
         WBFL::Geometry::Point3d p2(1000, 0, 0); // neutral axis
         WBFL::Geometry::Point3d p3(0, 48, -0.003); // -0.003 at top face of beam

         WBFL::Geometry::Plane3d strainPlane(p1, p2, p3);

         GeneralSectionSolver solver;
         solver.SetSlices(10);
         solver.SetSection(section);
         auto solution = solver.Solve(strainPlane);

         Assert::IsTrue(IsEqual(solution->GetFz(), -6989.5380720604908));
         Assert::IsTrue(IsEqual(solution->GetMx(), -199028.63168431941));
         Assert::IsTrue(IsEqual(solution->GetMy(), 0.0));
         Assert::IsTrue(IsEqual(solution->GetCompressionResultant(), -7042.3377809023850));
         Assert::IsTrue(IsEqual(solution->GetTensionResultant(), 52.799708841892233));

         // solve again with a different number of slices
         solver.SetSlices(20);
         solution = solver.Solve(strainPlane);

         Assert::IsTrue(IsEqual(solution->GetFz(), -6952.5633140647860));
         Assert::IsTrue(IsEqual(solution->GetMx(), -199133.42342670338));
         Assert::IsTrue(IsEqual(solution->GetMy(), 0.0));
         Assert::IsTrue(IsEqual(solution->GetCompressionResultant(), -7005.3630229066785));
         Assert::IsTrue(IsEqual(solution->GetTensionResultant(), 52.799708841892233));

         // solve with new section
         solver.SetSection(nullptr); // this should clear out the current section
         solver.SetSection(section); // set the section back, but to the solver it is a new section
         solution = solver.Solve(strainPlane);

         Assert::IsTrue(IsEqual(solution->GetFz(), -6952.5633140647860));
         Assert::IsTrue(IsEqual(solution->GetMx(), -199133.42342670338));
         Assert::IsTrue(IsEqual(solution->GetMy(), 0.0));
         Assert::IsTrue(IsEqual(solution->GetCompressionResultant(), -7005.3630229066785));
         Assert::IsTrue(IsEqual(solution->GetTensionResultant(), 52.799708841892233));
      }
	};
}
