#include "pch.h"
#include "CppUnitTest.h"
#include "NumericalTest.h"
#include <MathEx.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Beams;

namespace RoarkUnitTest
{
	TEST_CLASS(TestPPIntermediateLoad)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // Intermediate load at mid-span
         Float64 w = -10;
         Float64 La = 5;
         Float64 l = 10;
         Float64 ei = 1;
         PPIntermediateLoad beam(w, La, l, ei);

         auto [Ra, Rb] = beam.GetReactions();
         Assert::IsTrue(IsEqual(Ra, 5.0));
         Assert::IsTrue(IsEqual(Rb, 5.0));

         WBFL::System::SectionValue Mcl = beam.ComputeMoment(5);
         Assert::IsTrue(IsEqual(Mcl.Left(), 25.0) && IsEqual(Mcl.Right(), 25.0));

         WBFL::System::SectionValue Vcl = beam.ComputeShear(5);
         Assert::IsTrue(IsEqual(Vcl.Left(), 5.0) && IsEqual(Vcl.Right(), -5.0));

         WBFL::System::SectionValue Va = beam.ComputeShear(0);
         Assert::IsTrue(IsEqual(Va.Left(), 0.0) && IsEqual(Va.Right(), 5.0));

         WBFL::System::SectionValue Vb = beam.ComputeShear(l);
         Assert::IsTrue(IsEqual(Vb.Left(), -5.0) && IsEqual(Vb.Right(), 0.0));

         Assert::IsTrue(IsZero(beam.ComputeDeflection(0)));
         Assert::IsTrue(IsZero(beam.ComputeDeflection(l)));

         Float64 D50 = beam.ComputeDeflection(5);
         Float64 delta = (w * l * l * l) / (48 * ei);
         Assert::IsTrue(IsEqual(D50, delta));

         // Test signs of rotations
         Assert::IsTrue(beam.ComputeRotation(0) < 0);
         Assert::IsTrue(beam.ComputeRotation(l) > 0);

         // Test for symmetry
         Uint16 nPoints = 10;
         Uint16 j;
         for (j = 0; j < nPoints / 2; j++)
         {
            WBFL::System::SectionValue lShear, rShear;
            WBFL::System::SectionValue lMoment, rMoment;

            Float64 xl = j * l / nPoints;
            Float64 xr = l - j * l / nPoints;

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

         Test_Numerical(beam);
         Test_Numerical(PPIntermediateLoad(-5, 3, 10, 1));
         Test_Numerical(PPIntermediateLoad(-5, 7, 10, 1));
      }
	};
}
