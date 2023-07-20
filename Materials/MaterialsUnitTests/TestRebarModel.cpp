#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestRebarModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
         RebarModel model;

         // elastic-plastic model
         model.SetProperties(60.0, 29000, 0.07);

         Float64 fy, fu, Es, esh, er;
         bool bIsStrainHardening;
         model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
         Assert::IsTrue(bIsStrainHardening == false);

         auto result = model.ComputeStress(0.001);
         Assert::IsTrue(IsEqual(result.first, 29.0) && result.second == true);

         result = model.ComputeStress(-0.001);
         Assert::IsTrue(IsEqual(result.first, -29.0) && result.second == true);

         result = model.ComputeStress(0.1);
         Assert::IsTrue(IsEqual(result.first, 60.0) && result.second == false);

         result = model.ComputeStress(-0.1);
         Assert::IsTrue(IsEqual(result.first, -60.0) && result.second == true);

         // strain-hardening model
         model.SetProperties(fy, fu, Es, esh, er);
         model.GetProperties(&fy, &fu, &Es, &esh, &er, &bIsStrainHardening);
         Assert::IsTrue(bIsStrainHardening == true);

         result = model.ComputeStress(0.001);
         Assert::IsTrue(IsEqual(result.first, 29.0) && result.second == true);

         result = model.ComputeStress(-0.001);
         Assert::IsTrue(IsEqual(result.first, -29.0) && result.second == true);

         result = model.ComputeStress(fy / Es + 0.001);
         Assert::IsTrue(IsEqual(result.first, 60.0) && result.second == true);

         result = model.ComputeStress(-(fy / Es + 0.001));
         Assert::IsTrue(IsEqual(result.first, -60.0) && result.second == true);

         result = model.ComputeStress(esh + 0.001);
         Assert::IsTrue(IsEqual(result.first, 60.930176) && result.second == true);

         result = model.ComputeStress(-(esh + 0.001));
         Assert::IsTrue(IsEqual(result.first, -60.930176) && result.second == true);

         result = model.ComputeStress(10.0);
         Assert::IsTrue(IsEqual(result.first, 90.0) && result.second == false);

         result = model.ComputeStress(-10.0);
         Assert::IsTrue(IsEqual(result.first, -90.0) && result.second == true);
      }
	};
}
