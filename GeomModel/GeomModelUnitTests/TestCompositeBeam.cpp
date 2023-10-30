#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCompositeBeam)
	{
	public:

		TEST_METHOD(Test)
		{
			PlateGirder girder(Point2d(0, 0), 22.0, 1.25, 22.0, 2.25, 122.0, 4.38);
			CompositeBeam beam;
			beam.SetBeam(girder);
			beam.SetBeamDensity(0.490);
			beam.SetBeamE(29000.0);

			beam.SetTributarySlabWidth(100);
			beam.SetEffectiveSlabWidth(90);
			beam.SetHaunchDepth(6);
			beam.SetHaunchWidth(22);
			beam.SetGrossSlabDepth(8);
			beam.SetSacrificialDepth(0.5);
			beam.SetSlabDensity(0.150);
			beam.SetSlabE(4000.0);

			Assert::IsTrue(*beam.GetHookPoint() == Point2d(0, 0));

			auto q = beam.GetQslab();
			Assert::AreEqual(q, 6888.5900529835726);
			q = beam.GetQ(0);
			Assert::AreEqual(q, 0.);
			q = beam.GetQ(50.0);
			Assert::AreEqual(q, 13169.975577489431);

			auto box = beam.GetBoundingBox(true);
			Assert::IsTrue(IsEqual(box.Left(), -45.0));
			Assert::IsTrue(IsEqual(box.Right(), 45.0));
			Assert::IsTrue(IsEqual(box.Top(), 139.0));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));

			box = beam.GetBoundingBox(false);
			Assert::IsTrue(IsEqual(box.Left(), -50.0));
			Assert::IsTrue(IsEqual(box.Right(), 50.0));
			Assert::IsTrue(IsEqual(box.Top(), 139.5));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));

			auto mass_props = beam.GetMassProperties();
			Assert::AreEqual(mass_props.GetMassPerLength(), 439.36639999999983);
		}
	};
}
