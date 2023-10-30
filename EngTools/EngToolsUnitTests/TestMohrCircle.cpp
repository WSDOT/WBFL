#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;

namespace EngToolsUnitTests
{
	TEST_CLASS(TestMohrCircle)
	{
	public:
		
		TEST_METHOD(Test)
		{
         Float64 sii, sjj, sij;
         Float64 temp;

         MohrCircle ct(64, 16, -32);

         temp = ct.GetPrincipalDirection();
         Assert::IsTrue(IsEqual(ct.GetSmax(), 80., 0.01));
         Assert::IsTrue(IsEqual(ct.GetSmin(), 0., 0.01));
         Assert::IsTrue(IsEqual(ct.GetTmax(), 40., 0.01));
         Assert::IsTrue(IsEqual(temp, ToRadians(26.57), 0.01));

         // should be able to get principals from princ angle
         ct.ComputeState(&sii, &sjj, &sij, temp);
         Assert::IsTrue(IsEqual(sii, 80.));
         Assert::IsTrue(IsEqual(sjj, 0.));
         Assert::IsTrue(IsEqual(sij, 0.));

         // Test 1
         // Example 1.1 pg 13 from Ugural and Fenster
         MohrCircle c1(80, 40, 30);

         Assert::IsTrue(IsEqual(c1.GetSmax(), 96.05, 0.01));
         Assert::IsTrue(IsEqual(c1.GetSmin(), 23.95, 0.01));
         Assert::IsTrue(IsEqual(c1.GetTmax(), 36.05, 0.01));
         Assert::IsTrue(IsEqual(c1.GetPrincipalDirection(), ToRadians(-28.15), 0.01));

         // Test 2
         // Example 1.2 pg 15 from Ugural and Fenster
         MohrCircle c2(-14, 28, 0);

         c2.ComputeState(&sii, &sjj, &sij, ToRadians(30.));
         Assert::IsTrue(IsEqual(sii, -3.5, 0.1));
         Assert::IsTrue(IsEqual(sjj, 17.5, 0.1));
         Assert::IsTrue(IsEqual(sij, -18.186, 0.001));

         // Test 2
         // Problem 1.3 pg 27 from Ugural and Fenster
         MohrCircle c3(100, -50, -60);

         Assert::IsTrue(IsEqual(c3.GetSmax(), 121.0, 0.1));
         Assert::IsTrue(IsEqual(c3.GetSmin(), -71.0, 0.1));
         Assert::IsTrue(IsEqual(c3.GetTmax(), 96.0, 0.1));
         Assert::IsTrue(IsEqual(c3.GetPrincipalDirection(), ToRadians(19.33), 0.1));

         MohrCircle c4(150, 0, 100);

         Assert::IsTrue(IsEqual(c4.GetSmax(), 200.0, 0.1));
         Assert::IsTrue(IsEqual(c4.GetSmin(), -50.0, 0.1));
         Assert::IsTrue(IsEqual(c4.GetTmax(), 125.0, 0.1));
         Assert::IsTrue(IsEqual(c4.GetPrincipalDirection(), ToRadians(-26.57), 0.1));

         // From "Statics", Merriam, Pg 373
         MohrCircle c5(18.167, 10.167, -7.5);

         Assert::IsTrue(IsEqual(c5.GetSmax(), 22.67, 0.1));
         Assert::IsTrue(IsEqual(c5.GetSmin(), 5.67, 0.1));
         Assert::IsTrue(IsEqual(c5.GetPrincipalDirection(), ToRadians(30.96), 0.01));

         // From Beer & Johnston, Mechanics of Materials, page 306
         MohrCircle c6(100, 60, 48);
         Assert::IsTrue(IsEqual(c6.GetSmax(), 132., 0.1));
         Assert::IsTrue(IsEqual(c6.GetSmin(), 28., 0.1));
         Assert::IsTrue(IsEqual(c6.GetPrincipalDirection(), ToRadians(-33.7), 0.1));

         c6.ComputeState(&sii, &sjj, &sij, ToRadians(30.));
         Assert::IsTrue(IsEqual(sii, 48.4, 0.1));
         Assert::IsTrue(IsEqual(sjj, 111.6, 0.1));
         Assert::IsTrue(IsEqual(sij, 41.3, 0.1));

         MohrCircle c7(50, -10, 40);
         Assert::IsTrue(IsEqual(c7.GetSmax(), 70., 0.1));
         Assert::IsTrue(IsEqual(c7.GetSmin(), -30., 0.1));
         Assert::IsTrue(IsEqual(c7.GetPrincipalDirection(), ToRadians(-26.56), 0.1));

         MohrCircle c8(4.18, 3.25, 2.87);
         Assert::IsTrue(IsEqual(c8.GetSmax(), 6.63, 0.1));
         Assert::IsTrue(IsEqual(c8.GetSmin(), 0.81, 0.1));
         Assert::IsTrue(IsEqual(c8.GetPrincipalDirection(), ToRadians(-40.4), 0.1));
      }
	};
}
