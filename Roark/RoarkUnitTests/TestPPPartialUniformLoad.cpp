#include "pch.h"
#include "CppUnitTest.h"
#include "NumericalTest.h"
#include <MathEx.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Beams;

namespace RoarkUnitTest
{
	TEST_CLASS(TestPPPartialUniformLoad)
	{
	public:
      // When a symmetrically loaded beam is used, the results must be symmetrical
      void Test_Symmetry(Float64 fra)
      {
         Float64 L = 10;
         Float64 La = fra * L;
         Float64 Lb = (1.0 - fra) * L;
         Float64 EI = 1;
         Float64 w = -10;
         Uint16 nPoints = 10;
         Uint16 i;

         PPPartialUniformLoad beam(La, Lb, w, L, EI);
         for (i = 0; i < nPoints / 2; i++)
         {
            WBFL::System::SectionValue lShear, rShear;
            WBFL::System::SectionValue lMoment, rMoment;

            Float64 xl = i * L / nPoints;
            Float64 xr = L - i * L / nPoints;

            lShear = beam.ComputeShear(xl);
            rShear = beam.ComputeShear(xr);
            Assert::IsTrue(IsEqual(lShear.Left(), -rShear.Right()));
            Assert::IsTrue(IsEqual(lShear.Right(), -rShear.Left()));

            lMoment = beam.ComputeMoment(xl);
            rMoment = beam.ComputeMoment(xr);
            Assert::IsTrue(IsEqual(lMoment.Left(), rMoment.Right()));
            Assert::IsTrue(IsEqual(lMoment.Right(), rMoment.Left()));

            Assert::IsTrue(IsEqual(beam.ComputeRotation(xl), -beam.ComputeRotation(xr)));
            Assert::IsTrue(IsEqual(beam.ComputeDeflection(xl), beam.ComputeDeflection(xr)));
         }
      }

		TEST_METHOD(Test)
		{
         Float64 La = 0;
         Float64 Lb = 10;
         Float64 w = -1;
         Float64 l = 10;
         Float64 ei = 1;

         PPPartialUniformLoad beam(La, Lb, w, l, ei);
         auto [Ra, Rb] = beam.GetReactions();
         Assert::IsTrue(IsEqual(Ra, 5.0));
         Assert::IsTrue(IsEqual(Rb, 5.0));

         WBFL::System::SectionValue Mcl = beam.ComputeMoment(5);
         Assert::IsTrue(IsEqual(Mcl.Left(), 12.5) && IsEqual(Mcl.Right(), 12.5));

         WBFL::System::SectionValue Vcl = beam.ComputeShear(5);
         Assert::IsTrue(IsEqual(Vcl.Left(), 0.0) && IsEqual(Vcl.Right(), 0.0));

         WBFL::System::SectionValue V25 = beam.ComputeShear(0.25 * l);
         Assert::IsTrue(IsEqual(V25.Left(), V25.Right()) && IsEqual(V25.Left(), 2.5));

         WBFL::System::SectionValue V75 = beam.ComputeShear(0.75 * l);
         Assert::IsTrue(IsEqual(V75.Left(), V75.Right()) && IsEqual(V75.Left(), -2.5));

         // Check deflections
         Assert::IsTrue(IsZero(beam.ComputeDeflection(0)));
         Assert::IsTrue(IsZero(beam.ComputeDeflection(l)));

         Float64 D50 = beam.ComputeDeflection(5);
         Float64 delta = (5 * w * l * l * l * l) / (384 * ei);
         Assert::IsTrue(IsEqual(D50, delta));

         // Test signs of rotations
         Assert::IsTrue(beam.ComputeRotation(0) < 0);
         Assert::IsTrue(beam.ComputeRotation(l) > 0);

         Test_Symmetry(0.00);
         Test_Symmetry(0.25);
         Test_Symmetry(0.50);

         Test_Numerical(beam);
         Test_Numerical(PPPartialUniformLoad(2, 5, -10, 10, 1));
         Test_Numerical(PPPartialUniformLoad(4, 9, -10, 10, 1));
         Test_Numerical(PPPartialUniformLoad(9, 10, -10, 10, 1));
      }
	};
}
