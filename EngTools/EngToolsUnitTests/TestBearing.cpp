#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;

namespace EngToolsUnitTests
{
	TEST_CLASS(TestBearing)
	{
	public:
		
		TEST_METHOD(Test)
		{
         
            Bearing brg;
            brg.SetLength(WBFL::Units::ConvertToSysUnits(11.0, WBFL::Units::Measure::Inch));
            brg.SetWidth(WBFL::Units::ConvertToSysUnits(27.0, WBFL::Units::Measure::Inch));

            Assert::IsTrue(IsEqual(brg.GetLength(), WBFL::Units::ConvertToSysUnits(11.0, WBFL::Units::Measure::Inch)));
            Assert::IsTrue(IsEqual(brg.GetWidth(), WBFL::Units::ConvertToSysUnits(27.0, WBFL::Units::Measure::Inch)));
            Assert::IsTrue(IsEqual(brg.GetWidth(), WBFL::Units::ConvertToSysUnits(27, WBFL::Units::Measure::Inch)));
            Assert::IsTrue(IsEqual(brg.GetShearModulusMinimum(), WBFL::Units::ConvertToSysUnits(140, WBFL::Units::Measure::PSI)));
            Assert::IsTrue(IsEqual(brg.GetShearModulusMaximum(), WBFL::Units::ConvertToSysUnits(190, WBFL::Units::Measure::PSI)));
            Assert::IsTrue(IsEqual(brg.GetIntermediateLayerThickness(), WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch)));
            Assert::IsTrue(IsEqual(brg.GetCoverThickness(), WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch)));
            Assert::IsTrue(IsEqual(brg.GetSteelShimThickness(), WBFL::Units::ConvertToSysUnits(0.0747, WBFL::Units::Measure::Inch)));
            Assert::IsTrue(IsEqual(brg.GetYieldStrength(), WBFL::Units::ConvertToSysUnits(36, WBFL::Units::Measure::KSI)));
            Assert::IsTrue(IsEqual(brg.GetFatigueThreshold(), WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::KSI)));
            Assert::IsTrue(IsEqual(brg.GetNumIntLayers(), 4));
            Assert::IsTrue(IsEqual(brg.GetDensityElastomer(), WBFL::Units::ConvertToSysUnits(74.93, WBFL::Units::Measure::LbfPerFeet3)));
            Assert::IsTrue(IsEqual(brg.GetDensitySteel(), WBFL::Units::ConvertToSysUnits(490.0, WBFL::Units::Measure::LbfPerFeet3)));
            Assert::IsTrue(IsEqual(brg.GetArea(), WBFL::Units::ConvertToSysUnits(297, WBFL::Units::Measure::Inch2)));
            Assert::IsTrue(IsEqual(brg.GetTotalElastomerThickness(), WBFL::Units::ConvertToSysUnits(2.50, WBFL::Units::Measure::Inch)));
            Assert::IsTrue(IsEqual(brg.GetTotalSteelShimThickness(), WBFL::Units::ConvertToSysUnits(0.374, WBFL::Units::Measure::Inch), 0.001));
            Assert::IsTrue(IsEqual(brg.GetTotalSteelShims(), 5));
            Assert::IsTrue(IsEqual(brg.GetShapeFactor(), 7.82, 0.01));

      }
	};
}
