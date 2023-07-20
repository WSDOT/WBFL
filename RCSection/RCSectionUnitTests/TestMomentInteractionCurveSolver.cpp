#include "pch.h"
#include "CppUnitTest.h"
#include <GeomModel/GeomModel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestMomentInteractionCurveSolver)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // This example is from "Reinforced Concrete Design", 4th Edition, Salmon & Wang
         // Example 13.21.3
         // See interaction diagram solution in Figure 13.21.14. Note that the examples X-Y is different than our X-Y
         // See scanned image in Supporting Documents folder

         // base units of kip and ksi
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         //
         // materials
         //

         // concrete
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

         // rebar
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

         //
         // shapes
         //
         // note that this provides a uniform layout of the reinforcing and the bars are slightly non-uniform in the example
         // expect results to differ slightly. also, these calculations use strain compatibility where the textbook uses equivalent stress block
         auto section = SectionBuilder::RectangularColumn(12, 18, 2.38, 4, 4, 0.79, concrete, rebar, true);

         MomentInteractionCurveSolver solver;
         solver.SetSection(section);

         auto solution = solver.Solve(-1000000, 0, PI_OVER_2, 3); // compression force too high
         Assert::IsTrue(solution->GetSolutionPointCount() == 0);

         solution = solver.Solve(1000000, 0, PI_OVER_2, 3); // tension force too high
         Assert::IsTrue(solution->GetSolutionPointCount() == 0);

         // solve with Fz = 0
         solution = solver.Solve(0, 0, PI_OVER_2, 3); // bending about the horizontal axis

         Float64 tol = solver.GetTolerance();

         static Float64 mx[]{ -2057.163679,-951.68031,0.0 };
         static Float64 my[]{ 0.0,-2759.325957,-3568.871898 };

         auto nPoints = solution->GetSolutionPointCount();
         for (IndexType i = 0; i < nPoints; i++)
         {
            const auto& moment_capacity = solution->GetSolutionPoint(i);
            Float64 P = moment_capacity.GetFz();
            Float64 Mx = moment_capacity.GetMx();
            Float64 My = moment_capacity.GetMy();
            Assert::IsTrue(IsZero(P, tol));
            Assert::IsTrue(IsEqual(Mx, mx[i]));
            Assert::IsTrue(IsEqual(My, my[i]));
         }
      }
	};
}
