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

         RCBeam beam(10.0, 4.0, 0.9 * 270, 270.0, 60.0, 13.02, 0.0, 7.5, 96.0, 6.0, 0.0, 0.0, 75.133333, 75.133333, 160.0);
         auto solution = RCSolver::Solve(beam);

         Assert::AreEqual(204210.759, solution.GetMn(), 0.001);
         Assert::AreEqual(0.85, solution.GetBeta1(), 0.001);
         Assert::AreEqual(40.090, solution.GetC(), 0.001);
         Assert::AreEqual(229.66, solution.GetFps(), 0.001);
         Assert::AreEqual(0.0026, solution.Get_et(), 0.0001);
      }
	};
}
