#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestUHPCShear)
	{
	public:
		
      TEST_METHOD(Case1)
      {
         // Test case based on FHWA Prestressed Concrete Design Example
         UHPCShearData data;
         data.Mu = 1402.3 * 12;
         data.Nu = 0;
         data.Vu = 377.3;
         data.Vp = 0;
         data.Aps = 10;
         data.fpo = 189;
         data.ft = 0.85 * 1.2;
         data.Ac = 362.61;
         data.Eps = 28500;
         data.Es = 29000;
         data.Ec = 6933;
         data.AvS = 0.20 / 6;
         data.bv = 3.5;
         data.dv = 4.24 * 12;
         data.fy = 60.0;
         data.ftloc = 1.2;
         data.etloc = 0.004;
         data.etcr = 0.001;
         data.gamma_u = 1.0;

         UHPCShear::ComputeShearResistanceParameters(&data);

         Assert::AreEqual(60.0, data.fv);

         Float64 theta = WBFL::Units::ConvertFromSysUnits(data.Theta, WBFL::Units::Measure::Degree); // convert to degrees
         Assert::AreEqual(30.34975, theta, 0.00001); // FHWA Example 30.35

         Assert::AreEqual(-0.0004223, data.es, 0.00001);
         Assert::AreEqual(-0.0016554, data.e2, 0.00001);
         Assert::AreEqual(0.0025557, data.ev, 0.00001);

         // Test zero reinforcement case
         data.AvS = 0;

         UHPCShear::ComputeShearResistanceParameters(&data);

         Assert::AreEqual(0.0,data.fv);

         theta = WBFL::Units::ConvertFromSysUnits(data.Theta, WBFL::Units::Measure::Degree); // convert to degrees
         Assert::AreEqual(27.13625, theta, 0.00001); // FHWA Example 30.35

         Assert::AreEqual(-0.0004223, data.es, 0.00001);
         Assert::AreEqual(-0.0013178, data.e2, 0.00001);
         Assert::AreEqual(0.0028933, data.ev, 0.00001);
      }


      TEST_METHOD(Case2)
      {
         // Test case based on FHWA Reinforced Concrete Example
         UHPCShearData data;
         data.Mu = 100.4 * 12;
         data.Nu = 0;
         data.Vu = 61.4;
         data.Vp = 0;
         data.Aps = 0;
         data.As = 14.04;
         data.fpo = 0;
         data.ft = 0.85 * 1.2;
         data.Ac = 139.32;
         data.Eps = 28500;
         data.Es = 29000;
         data.Ec = 6933;
         data.AvS = 2 * 0.20 / 6;
         data.bv = 12;
         data.dv = 1.64 * 12;
         data.fy = 60.0;
         data.ftloc = 1.2;
         data.etloc = 0.003;
         data.etcr = 0.001;
         data.gamma_u = 1.0;

         UHPCShear::ComputeShearResistanceParameters(&data);

         // Note FHWA example has some rounding that we don't do here

         Assert::AreEqual(52.386743, data.fv, 0.00001); // FHWA Example 54.2

         Float64 theta = WBFL::Units::ConvertFromSysUnits(data.Theta, WBFL::Units::Measure::Degree); // convert to degrees
         Assert::AreEqual(32.437149, theta, 0.00001); // FHWA Example 31.72

         Assert::AreEqual(0.0000893, data.es, 0.00001);
         Assert::AreEqual(-0.00115, data.e2, 0.00001);
         Assert::AreEqual(0.001806, data.ev, 0.00001);

         // Test zero reinforcement case
         data.AvS = 0;

         UHPCShear::ComputeShearResistanceParameters(&data);

         Assert::AreEqual(0.0, data.fv, 0.00001);

         theta = WBFL::Units::ConvertFromSysUnits(data.Theta, WBFL::Units::Measure::Degree); // convert to degrees
         Assert::AreEqual(30.60244, theta, 0.00001); // FHWA Example 30.35

         Assert::AreEqual(0.0000893, data.es, 0.00001);
         Assert::AreEqual(-0.0009896, data.e2, 0.00001);
         Assert::AreEqual(0.0019658, data.ev, 0.00001);
      }

	};
}
