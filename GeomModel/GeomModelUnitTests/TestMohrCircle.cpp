#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <GeomModel/MohrCircle.h>

using namespace WBFL::Geometry;

namespace GeomModelUnitTests
{
	TEST_CLASS(TestMohrCircle)
	{
	public:

      TEST_METHOD(Test0)
      {
       
         MohrCircle ct(64, 16, -32);

         auto principal_direction = ct.GetPrincipalDirection();
         Assert::AreEqual(principal_direction, ToRadians(-26.57), 0.01);
         Assert::AreEqual(ct.GetSmax(), 80.0, 0.01);
         Assert::AreEqual(ct.GetSmin(), 0.0, 0.01);
         Assert::AreEqual(ct.GetTmax(), 40.0, 0.01);

         // should be able to get principals from princ angle
         Float64 sii, sjj, sij;
         std::tie(sii, sjj, sij) = ct.ComputeState(principal_direction);
         Assert::AreEqual(sii, 80.0, 0.01);
         Assert::AreEqual(sjj, 0.0, 0.01);
         Assert::AreEqual(sij, 0.0, 0.01);
      }

      TEST_METHOD(Test1)
      {
         // Example 1.1 pg 13 from Ugural and Fenster
         MohrCircle c1(80, 40, 30);

         Assert::AreEqual(c1.GetSmax(), 96.05, 0.01);
         Assert::AreEqual(c1.GetSmin(), 23.95, 0.01);
         Assert::AreEqual(c1.GetTmax(), 36.05, 0.01);
         Assert::AreEqual(c1.GetPrincipalDirection(), ToRadians(28.15), 0.01);
      }

      TEST_METHOD(Test2)
      {
         // Example 1.2 pg 15 from Ugural and Fenster
         MohrCircle c2(-14, 28, 0);

         Float64 sii, sjj, sij;
         std::tie(sii, sjj, sij) = c2.ComputeState(ToRadians(30.0));
         Assert::AreEqual(sii, -3.5, 0.1);
         Assert::AreEqual(sjj, 17.5, 0.1);
         Assert::AreEqual(sij, 18.186, 0.001);
      }

      TEST_METHOD(Test3)
      {
         // Problem 1.3 pg 27 from Ugural and Fenster
         MohrCircle c3(100, -50, -60);

         Assert::AreEqual(c3.GetSmax(), 121.0, 0.1);
         Assert::AreEqual(c3.GetSmin(), -71.0, 0.1);
         Assert::AreEqual(c3.GetTmax(), 96.0, 0.1);
         Assert::AreEqual(c3.GetPrincipalDirection(), ToRadians(-19.33), 0.1);
      }

      TEST_METHOD(Test4)
      {
         MohrCircle c4(150, 0, 100);

         Assert::AreEqual(c4.GetSmax(), 200.0, 0.1);
         Assert::AreEqual(c4.GetSmin(), -50.0, 0.1);
         Assert::AreEqual(c4.GetTmax(), 125.0, 0.1);
         Assert::AreEqual(c4.GetPrincipalDirection(), ToRadians(26.57), 0.1);
      }

      TEST_METHOD(Test5)
      {
         // From "Statics", Merriam, Pge 373
         MohrCircle c5(18.167, 10.167, -7.5);
         Assert::AreEqual(c5.GetSmax(), 22.67, 0.1);
         Assert::AreEqual(c5.GetSmin(), 5.67, 0.1);
         Assert::AreEqual(c5.GetPrincipalDirection(), ToRadians(-30.96), 0.01);
      }

      TEST_METHOD(Test6)
      {
         // From Beer & Johnston, Mechanics of Materials, page 306
         MohrCircle c6(100, 60, 48);
         Assert::AreEqual(c6.GetSmax(), 132., 0.1);
         Assert::AreEqual(c6.GetSmin(), 28., 0.1);
         Assert::AreEqual(c6.GetPrincipalDirection(), ToRadians(33.7), 0.1);

         Float64 sii, sjj, sij;
         std::tie(sii, sjj, sij) = c6.ComputeState(ToRadians(30.0));
         Assert::AreEqual(sii, 131.57, 0.1);
         Assert::AreEqual(sjj, 28.43, 0.1);
         Assert::AreEqual(sij, 6.68, 0.1);
      }

      TEST_METHOD(Test7)
      {
         MohrCircle c7(50, -10, 40);
         Assert::AreEqual(c7.GetSmax(), 70., 0.1);
         Assert::AreEqual(c7.GetSmin(), -30., 0.1);
         Assert::AreEqual(c7.GetPrincipalDirection(), ToRadians(26.56), 0.1);
      }

      TEST_METHOD(Test8)
      {
         MohrCircle c8(4.18, 3.25, 2.87);
         Assert::AreEqual(c8.GetSmax(), 6.63, 0.1);
         Assert::AreEqual(c8.GetSmin(), 0.81, 0.1);
         Assert::AreEqual(c8.GetPrincipalDirection(), ToRadians(40.4), 0.1);
      }

      TEST_METHOD(Test9)
      {
         MohrCircle c9(10.38, 6.97, -6.56);
         Assert::AreEqual(c9.GetSmax(), 15.45, 0.1);
         Assert::AreEqual(c9.GetSmin(), 1.897, 0.1);
         Assert::AreEqual(c9.GetPrincipalDirection(), ToRadians(-37.7), 0.1);
      }

      TEST_METHOD(Test10)
      {
         // Ported from the former WBFLTools COM MohrCircle test suite
         MohrCircle c10(12, 4, 3);
         Assert::AreEqual(c10.GetCenter(), 8.0, 0.001);
         Assert::AreEqual(c10.GetRadius(), 5.0, 0.001);
         Assert::AreEqual(c10.GetSmax(), 13.0, 0.001);
         Assert::AreEqual(c10.GetSmin(), 3.0, 0.001);
         Assert::AreEqual(c10.GetTmax(), 5.0, 0.001);
         Assert::AreEqual(c10.GetPrincipalDirection(), ToRadians(18.43), 0.02);

         Float64 sii, sjj, sij;
         std::tie(sii, sjj, sij) = c10.ComputeState(ToRadians(15.0));
         Assert::AreEqual(sii, 12.964, 0.002);
         Assert::AreEqual(sjj, 3.036, 0.002);
         Assert::AreEqual(sij, 0.598, 0.002);
      }

      TEST_METHOD(Test11)
      {
         // Ported from the former WBFLTools COM MohrCircle test suite.
         // Special case: zero radius (Sii == Sjj, Sij == 0) - principal direction is defined to be 0.
         MohrCircle c11(10, 10, 0);
         Assert::AreEqual(c11.GetRadius(), 0.0, 0.001);
         Assert::AreEqual(c11.GetPrincipalDirection(), 0.0, 0.001);
      }
	};
}
