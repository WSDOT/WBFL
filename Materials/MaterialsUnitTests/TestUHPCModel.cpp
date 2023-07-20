#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestUHPCModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
         UHPCModel model;

         Float64 fc = 151684660.45; // 22 ksi
         Float64 ft_cr = 8273708.7518; // 1.2 ksi
         Float64 ft_loc = ft_cr;
         Float64 et_loc = 0.0045;

         model.SetFc(fc);
         Assert::IsTrue(IsEqual(model.GetFc(), fc));

         model.SetFtcr(ft_cr);
         Assert::IsTrue(IsEqual(model.GetFtcr(), ft_cr));

         model.SetFtloc(ft_loc);
         Assert::IsTrue(IsEqual(model.GetFtloc(), ft_loc));

         model.Set_etloc(et_loc);
         Assert::IsTrue(IsEqual(model.Get_etloc(), et_loc));

         Assert::IsTrue(IsEqual(model.GetAlpha(), 0.85));
         Assert::IsTrue(IsEqual(model.GetGamma(), 1.0));
         Assert::IsTrue(IsEqual(model.GetK1(), 1.0));
         Assert::IsTrue(IsEqual(model.GetModulusOfElasticity(), 47803365821.695671));

         // compute stresses for tension strains

         // elastic region
         auto stress = model.ComputeStress(0.00005);
         Assert::IsTrue(IsEqual(stress.first, 2390168.2910847836) && stress.second == true);

         // plastic region
         stress = model.ComputeStress(0.0010);
         Assert::IsTrue(IsEqual(stress.first, model.GetGamma() * ft_cr) && stress.second == true);

         // after crack localization
         stress = model.ComputeStress(0.0050);
         Assert::IsTrue(IsEqual(stress.first, 0.0) && stress.second == true);

         // compute stresses for compression strains

         // elastic region
         stress = model.ComputeStress(-0.001);
         Assert::IsTrue(IsEqual(stress.first, -47803365.821695670) && stress.second == true);

         // plastic region
         stress = model.ComputeStress(-0.003);
         Assert::IsTrue(IsEqual(stress.first, -0.85 * fc) && stress.second == true); // stress plateau at alpha*f'c

         // after crushing
         stress = model.ComputeStress(-0.004);
         Assert::IsTrue(IsEqual(stress.first, -0.85 * fc) && stress.second == false); // -0.0035 is crushing strain
      }
	};
}
