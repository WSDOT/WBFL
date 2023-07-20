#include "pch.h"
#include "CppUnitTest.h"
#include "NumericalTest.h"
#include <MathEx.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Beams;

namespace RoarkUnitTest
{
   void Test_Numerical(const WBFL::Beams::RoarkBeam& beam)
   {
      Uint16 nIntSteps = 100;
      Uint16 nCheckPnts = 10;
      Float64 sumShear = 0;  // cummulated area under the shear diagram
      Float64 sumMoment = 0; // cummulated area under the moment diagram
      Float64 sumRotation = 0; // cummulated area under the rotation diagram
      Float64 EI = beam.GetEI();
      Float64 Ma, Mb;
      Float64 ra, rb;
      Float64 ya, yb;

      Ma = beam.ComputeMoment(0).Right();
      Mb = beam.ComputeMoment(beam.GetL()).Left();
      ra = beam.ComputeRotation(0);
      rb = beam.ComputeRotation(beam.GetL());
      ya = beam.ComputeDeflection(0);
      yb = beam.ComputeDeflection(beam.GetL());

      Float64 dx = beam.GetL() / nIntSteps;
      Float64 sumx = 0;

      for (Uint16 i = 0; i < nIntSteps; i++)
      {
         Float64 x = i * dx;
         Float64 x_dx = x + dx;

         WBFL::System::SectionValue V = beam.ComputeShear(x);
         WBFL::System::SectionValue V_dV = beam.ComputeShear(x_dx);
         sumShear += (V.Right() + V_dV.Left()) * dx / 2;

         WBFL::System::SectionValue M = beam.ComputeMoment(x);
         WBFL::System::SectionValue M_dM = beam.ComputeMoment(x_dx);
         sumMoment += (M.Right() + M_dM.Left()) * dx / 2;

         Float64 r = beam.ComputeRotation(x);
         Float64 r_dr = beam.ComputeRotation(x_dx);
         sumRotation += (r + r_dr) * dx / 2;

         if (i % nCheckPnts == 0)
         {
            WBFL::System::SectionValue tstM = beam.ComputeMoment(x_dx);
            Assert::IsTrue(IsEqual(tstM.Left(), sumShear + Ma, 0.1));

            Float64 tstR = beam.ComputeRotation(x_dx);
            Assert::IsTrue(IsEqual(tstR, sumMoment / EI + ra, 0.1));

            Float64 tstDelta = beam.ComputeDeflection(x_dx);
            Assert::IsTrue(IsEqual(tstDelta, sumRotation + ya, 0.1));
         }
      }

      Float64 yl, yr;
      std::tie(yl, yr) = beam.GetDeflections();
      Assert::IsTrue(IsZero(yl));
      Assert::IsTrue(IsZero(yr));
   }
}