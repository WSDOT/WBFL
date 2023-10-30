#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// This test class tests the internal MohrCircle from the GeomModel DLL
// This class is not exported so it is a little more complicated to test
// The following was done to set up the testing
// 1. Added the MohrCircle.obj file to the project
//    See https://learn.microsoft.com/en-us/visualstudio/test/how-to-write-unit-tests-for-cpp-dlls?view=vs-2022#objectRef
//    "To link the tests to the object or library files"
// 2. This created an LNK2011 error.
//    https://learn.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-error-lnk2011
//    The solution was to also link to main.obj, which is generated with the precompiled header information
// 3. This created LNK2005 and LNK1169 errors
//    https://learn.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-error-lnk1169
//    The solution was to use the /FORCE:MULTIPLE option on the linker
//    There are still LNK4006 warnings, but they seem to be incidental
//
// To see the linker settings, Right click on GeomModelUnitTest project and select Properties.
// Configuration Properties > Linker > General > Additional Library Directories: Added $(ARPDIR)\WBFL\GeomModel\$(Platform)\$(Configuration)
// Configuration Properties > Linker > Input > Additional Dependencies: Added main.obj;MohrCircle.obj
// Configuraiton Properties > Linker > Command Line: Added /FORCE:MULTIPLE

#include "..\GeomModel\MohrCircle.h"

namespace GeomModelUnitTest
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
	};
}
