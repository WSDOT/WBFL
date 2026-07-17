#include "pch.h"
#include "CppUnitTest.h"
#include <GeomModel/GeomModel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestRCSolver)
	{
	public:
		
      TEST_METHOD(Test1)
      {
         // base units of kip and ksi
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         RCBeam beam(10.0, 4.0, 0.9 * 270, 270.0, 60.0, 13.02, 0.0, 7.5, 96.0, 6.0, 0.0, 0.0, 75.133333, 75.133333);
         auto solution = RCSolver::Solve(beam);

         Assert::AreEqual(204210.759, solution.GetMn(), 0.001);
         Assert::AreEqual(0.85, solution.GetBeta1(), 0.001);
         Assert::AreEqual(40.090, solution.GetC(), 0.001);
         Assert::AreEqual(229.66, solution.GetFps(), 0.001);
         Assert::AreEqual(0.0026, solution.Get_et(), 0.0001);
      }

      TEST_METHOD(TestMixedReinforcement)
      {
         // T-section behavior with BOTH prestressing strand and mild reinforcement present
         // (RCCapacity's TestSolver.cpp::Test2 W74G scenario has no direct RCSection equivalent
         // prior to this test - this closes that migration-parity gap)
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         RCBeam beam(4.0, 4.0, 0.9 * 270, 270.0, 60.0, 13.02, 2.0, 7.5, 96.0, 6.0, 70.0, 70.0, 75.0, 75.0);
         auto solution = RCSolver::Solve(beam);

         Assert::AreEqual(0.85, solution.GetAlpha1(), 0.001);
         Assert::AreEqual(0.85, solution.GetBeta1(), 0.001);
         Assert::AreEqual(43.999244, solution.GetC(), 0.01);
         Assert::IsTrue(solution.GetC() > 7.5); // confirms the T-section branch was taken
         Assert::AreEqual(225.648763, solution.GetFps(), 0.01);
         Assert::AreEqual(205872.8056, solution.GetMn(), 1.0);
         Assert::AreEqual(0.0021137, solution.Get_et(), 0.0001);
      }

      TEST_METHOD(TestRectangularSectionBranch)
      {
         // small prestressed-only reinforcement relative to a wide flange - the T-section-assumed
         // c comes out negative, forcing the rectangular-section branch (c < hf)
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         RCBeam beam(4.0, 4.0, 0.9 * 270, 270.0, 60.0, 1.0, 0.0, 7.5, 96.0, 6.0, 0.0, 0.0, 70.0, 70.0);
         auto solution = RCSolver::Solve(beam);

         Assert::AreEqual(0.85, solution.GetAlpha1(), 0.001);
         Assert::AreEqual(0.85, solution.GetBeta1(), 0.001);
         Assert::AreEqual(0.969410, solution.GetC(), 0.001);
         Assert::IsTrue(solution.GetC() < 7.5); // confirms the rectangular branch was taken
         Assert::AreEqual(268.953037, solution.GetFps(), 0.01);
         Assert::AreEqual(18715.904, solution.GetMn(), 1.0);
         Assert::AreEqual(0.213627, solution.Get_et(), 0.001);
      }

      TEST_METHOD(TestMildSteelOnly)
      {
         // Aps == 0 exercises the divide-by-zero guard that forces dps to 1.0 before it is
         // used as a denominator
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         RCBeam beam(4.0, 4.0, 0.9 * 270, 270.0, 60.0, 0.0, 4.0, 7.5, 96.0, 6.0, 20.0, 20.0, 0.0, 0.0);
         auto solution = RCSolver::Solve(beam);

         Assert::AreEqual(0.85, solution.GetAlpha1(), 0.001);
         Assert::AreEqual(0.85, solution.GetBeta1(), 0.001);
         Assert::AreEqual(0.865052, solution.GetC(), 0.001);
         Assert::AreEqual(0.0, solution.GetFps(), 0.001); // no prestressing steel present
         Assert::AreEqual(4711.765, solution.GetMn(), 1.0);
         Assert::AreEqual(0.066360, solution.Get_et(), 0.001);
      }

      TEST_METHOD(TestNoReinforcement)
      {
         // no mild steel and no prestressing - matches RCCapacity's "no reinforcement, no
         // capacity" scenario (RCCapacity\RCCapacityUnitTests\TestSolver.cpp)
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         RCBeam beam(4.0, 4.0, 0.9 * 270, 270.0, 60.0, 0.0, 0.0, 7.5, 96.0, 6.0, 0.0, 0.0, 0.0, 0.0);
         auto solution = RCSolver::Solve(beam);

         Assert::AreEqual(0.0, solution.GetMn());
         Assert::AreEqual(0.0, solution.GetC());
         Assert::AreEqual(0.0, solution.GetAlpha1());
         Assert::AreEqual(0.0, solution.GetBeta1());
         Assert::AreEqual(0.0, solution.GetFps());
         Assert::AreEqual(0.0, solution.Get_et());
      }
	};
}
