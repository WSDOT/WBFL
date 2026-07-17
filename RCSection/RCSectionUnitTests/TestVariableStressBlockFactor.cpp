#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestVariableStressBlockFactor)
	{
	public:
		
		TEST_METHOD(Test)
		{
         VariableStressBlockFactor factor;
         factor.SetFc(1);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));

         factor.SetFc(10);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));

         factor.SetFc(12.5);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.80));

         factor.SetFc(15);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.75));

         factor.SetFc(20);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.75));

         Assert::IsTrue(IsEqual(factor.GetDepthFactor(), 0.85));
      }

      TEST_METHOD(TestDefaultConstructed)
      {
         // before SetFc is ever called, m_Fc defaults to 0.0, which is below fc1(10)
         // and clamps to the alpha1/alpha2 range same as the low-end case in Test
         VariableStressBlockFactor factor;
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));
         Assert::IsTrue(IsEqual(factor.GetDepthFactor(), 0.85));
      }

      TEST_METHOD(TestStressBlockParametersRoundTrip)
      {
         VariableStressBlockFactor factor;
         factor.SetStressBlockParameters(0.90, 8.0, 0.65, 18.0, 0.65);

         Float64 alpha1, fc1, alpha2, fc2, beta1;
         factor.GetStressBlockParameters(alpha1, fc1, alpha2, fc2, beta1);
         Assert::IsTrue(IsEqual(alpha1, 0.90));
         Assert::IsTrue(IsEqual(fc1, 8.0));
         Assert::IsTrue(IsEqual(alpha2, 0.65));
         Assert::IsTrue(IsEqual(fc2, 18.0));
         Assert::IsTrue(IsEqual(beta1, 0.65));

         // beta1 is constant (does not vary with fc) - confirm the custom value is honored
         Assert::IsTrue(IsEqual(factor.GetDepthFactor(), 0.65));
      }

      TEST_METHOD(TestGetFc)
      {
         VariableStressBlockFactor factor;
         factor.SetFc(12.5);
         Assert::IsTrue(IsEqual(factor.GetFc(), 12.5));

         factor.SetFc(4.0);
         Assert::IsTrue(IsEqual(factor.GetFc(), 4.0));
      }

      TEST_METHOD(TestDegenerateFc1EqualsFc2)
      {
         // when fc1 == fc2, LinInterp's delta is zero and it always returns alpha1
         // regardless of the requested fc, per its documented zero-delta contract
         VariableStressBlockFactor factor;
         factor.SetStressBlockParameters(0.85, 10.0, 0.75, 10.0, 0.85);

         factor.SetFc(1.0);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));

         factor.SetFc(10.0);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));

         factor.SetFc(20.0);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));
      }

      TEST_METHOD(TestIncreasingAlphaConfiguration)
      {
         // alpha1 < alpha2 (increasing), exercising the Min/Max clamp in the
         // opposite direction from the default decreasing configuration
         VariableStressBlockFactor factor;
         factor.SetStressBlockParameters(0.75, 10.0, 0.85, 15.0, 0.85);

         factor.SetFc(1.0);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.75));

         factor.SetFc(10.0);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.75));

         factor.SetFc(12.5);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.80));

         factor.SetFc(15.0);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));

         factor.SetFc(20.0);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));
      }
	};
}
