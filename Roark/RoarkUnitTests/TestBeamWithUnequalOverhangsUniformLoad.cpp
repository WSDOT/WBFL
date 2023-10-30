#include "pch.h"
#include "CppUnitTest.h"
#include <MathEx.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Beams;

namespace RoarkUnitTest
{
	TEST_CLASS(TestBeamWithUnequalOverhangsUniformLoad)
	{
	public:
		
		TEST_METHOD(Test)
		{
         Float64 L = 100;
         Float64 a = 15;
         Float64 c = 15;
         BeamWithUnequalOverhangsUniformLoad beam1(L, a, c, 5, 1);

         Float64 t = 0;
         Assert::IsTrue(0 == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(0 == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(744921.875, beam1.ComputeDeflection(t)));

         t = a / 3;
         Assert::IsTrue(62.5 == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(25 == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(500000., beam1.ComputeDeflection(t)));

         t = a;
         Assert::IsTrue(562.5 == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(75 == beam1.ComputeShear(t).Left());
         Assert::IsTrue(-175 == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(0., beam1.ComputeDeflection(t)));

         t = 30;
         Assert::IsTrue(-1500. == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(-100 == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(751953.125, beam1.ComputeDeflection(t)));

         t = L / 2;
         Assert::IsTrue(-2500. == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(0 == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(1.21862e6, beam1.ComputeDeflection(t), 0.1e6));

         t = L - a;
         Assert::IsTrue(562.5 == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(175 == beam1.ComputeShear(t).Left());
         Assert::IsTrue(-75 == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(0., beam1.ComputeDeflection(t)));

         t = L - c / 3;
         Assert::IsTrue(62.5 == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(-25. == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(500000., beam1.ComputeDeflection(t)));

         t = L;
         Assert::IsTrue(0 == beam1.ComputeMoment(t).Right());
         Assert::IsTrue(0 == beam1.ComputeShear(t).Right());
         Assert::IsTrue(IsEqual(744921.875, beam1.ComputeDeflection(t)));

         // beam based on "Deflection of Beams with Unqeual Overhangs" in Supporting Documents
         BeamWithUnequalOverhangsUniformLoad beam2(223 * 12, 26 * 12, 26 * 12, -0.0865, 4009. * 1524912.);

         Assert::IsTrue(IsEqual(beam2.ComputeRotation(0), -0.00431576));
         Assert::IsTrue(IsEqual(beam2.ComputeRotation(223 * 12), 0.00431576));

         // Left support, 26ft = 312in
         Assert::IsTrue(beam2.ComputeMoment(312) == WBFL::System::SectionValue(-4210.1280));
         Assert::IsTrue(beam2.ComputeShear(312) == WBFL::System::SectionValue(-26.98799, 88.74899));
         Assert::IsTrue(IsEqual(beam2.ComputeRotation(312), -0.004387));
         Assert::IsTrue(IsEqual(beam2.ComputeDeflection(312), 0.00));

         // Mid-span, 115.5ft = 1338in
         Assert::IsTrue(beam2.ComputeMoment(1338) == WBFL::System::SectionValue(41318.109));
         Assert::IsTrue(beam2.ComputeShear(1338) == WBFL::System::SectionValue(0.0, 0.0));
         Assert::IsTrue(IsEqual(beam2.ComputeRotation(1338), 0.0));
         Assert::IsTrue(IsEqual(beam2.ComputeDeflection(1338), -2.90403));

         // Right support, 197ft = 2364in
         Assert::IsTrue(beam2.ComputeMoment(2364) == WBFL::System::SectionValue(-4210.1280));
         Assert::IsTrue(beam2.ComputeShear(2364) == WBFL::System::SectionValue(-88.74899, 26.98799));
         Assert::IsTrue(IsEqual(beam2.ComputeRotation(2364), 0.004387));
         Assert::IsTrue(IsEqual(beam2.ComputeDeflection(2364), 0.00));
      }
	};
}
