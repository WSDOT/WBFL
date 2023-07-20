#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Beams;

namespace RoarkUnitTest
{
	TEST_CLASS(TestCompositeBeam)
	{
	public:
		
		TEST_METHOD(Test)
		{
			CompositeBeam beam(100,1000);
			Assert::AreEqual((IndexType)0, beam.GetBeamCount());

			PPPartialUniformLoad beam1(0, 100, 10, 100, 1000);
			beam.AddBeam(beam1);
			Assert::AreEqual((IndexType)1, beam.GetBeamCount());
			beam.AddBeam(beam1);
			Assert::AreEqual((IndexType)2, beam.GetBeamCount());

			Assert::AreEqual(2 * beam1.ComputeShear(25.0).Left(), beam.ComputeShear(25.0).Left());
			Assert::AreEqual(2 * beam1.ComputeMoment(25.0).Left(), beam.ComputeMoment(25.0).Left());
			Assert::AreEqual(2 * beam1.ComputeRotation(25.0), beam.ComputeRotation(25.0));
			Assert::AreEqual(2 * beam1.ComputeDeflection(25.0), beam.ComputeDeflection(25.0));

			Assert::IsNotNull(beam.GetBeam(0).get());
			Assert::IsNotNull(beam.GetBeam(1).get());

			auto clone = beam.CreateClone();
			Assert::IsNotNull(clone.get());

			Assert::AreEqual(beam.GetReactions().first, clone->GetReactions().first);
			Assert::AreEqual(beam.GetReactions().second, clone->GetReactions().second);

			Assert::AreEqual(beam.GetMoments().first, clone->GetMoments().first);
			Assert::AreEqual(beam.GetMoments().second, clone->GetMoments().second);

			Assert::AreEqual(beam.GetRotations().first, clone->GetRotations().first);
			Assert::AreEqual(beam.GetRotations().second, clone->GetRotations().second);

			Assert::AreEqual(beam.GetDeflections().first, clone->GetDeflections().first);
			Assert::AreEqual(beam.GetDeflections().second, clone->GetDeflections().second);

			beam.RemoveAllBeams();
			Assert::AreEqual((IndexType)0, beam.GetBeamCount());
		}
	};
}
