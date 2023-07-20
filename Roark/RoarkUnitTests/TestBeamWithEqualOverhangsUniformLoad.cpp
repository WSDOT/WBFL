#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Beams;

namespace RoarkUnitTest
{
	TEST_CLASS(TestBeamWithEqualOverhangsUniformLoad)
	{
	public:
		
		TEST_METHOD(Test)
		{
         BeamWithEqualOverhangsUniformLoad beam1(100, 15, 5, 1);
         Float64 t = 5;
         Assert::AreEqual(-62.5, beam1.ComputeMoment(t).Right());
         Assert::AreEqual(25.0, beam1.ComputeShear(t).Right());
         Assert::AreEqual(500000., beam1.ComputeDeflection(t));
         Assert::AreEqual(-49062.5, beam1.ComputeRotation(t));
         t = 15;
         Assert::AreEqual(-562.5, beam1.ComputeMoment(t).Right());
         Assert::AreEqual(-175.0, beam1.ComputeShear(t).Right());
         Assert::AreEqual(0., beam1.ComputeDeflection(t));
         Assert::AreEqual(-51770.833333, beam1.ComputeRotation(t),0.00001);
         t = 30;
         Assert::AreEqual(1500., beam1.ComputeMoment(t).Right());
         Assert::AreEqual(-100., beam1.ComputeShear(t).Right());
         Assert::AreEqual(-751953.125, beam1.ComputeDeflection(t),0.00001);
         Assert::AreEqual(-43333.333333, beam1.ComputeRotation(t),0.00001);
         t = 50;
         Assert::AreEqual(2500., beam1.ComputeMoment(t).Right());
         Assert::AreEqual(0.0, beam1.ComputeShear(t).Right());
         Assert::AreEqual(-1.21862e6, beam1.ComputeDeflection(t), 0.1e6);
         Assert::AreEqual(0., beam1.ComputeRotation(t), 0.00001);
         t = 85;
         Assert::AreEqual(-562.5, beam1.ComputeMoment(t).Right());
         Assert::AreEqual(175., beam1.ComputeShear(t).Left());
         Assert::AreEqual(-75., beam1.ComputeShear(t).Right());
         Assert::AreEqual(0., beam1.ComputeDeflection(t), 0.00001);
         Assert::AreEqual(51770.833333, beam1.ComputeRotation(t), 0.00001);
         t = 99;
         Assert::AreEqual(-2.5, beam1.ComputeMoment(t).Right());
         Assert::AreEqual(-5., beam1.ComputeShear(t).Right());
         Assert::AreEqual(695963.333333, beam1.ComputeDeflection(t), 0.00001);
         Assert::AreEqual(48959.166667, beam1.ComputeRotation(t), 0.00001);
      }
	};
}
