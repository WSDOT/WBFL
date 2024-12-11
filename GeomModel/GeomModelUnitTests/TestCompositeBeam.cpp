#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCompositeBeam)
	{
	public:

		TEST_METHOD(TestPlateGirder)
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


		TEST_METHOD(TestRolledShape)
		{
			// This unit test is for the same beam as the BEToolbox::GirComp program documentation for the W44X335 beam
			CompositeBeam beam;
			beam.SetHaunchDepth(0.5);
			beam.SetGrossSlabDepth(7);
			beam.SetTributarySlabWidth(84.0);
			beam.SetEffectiveSlabWidth(84.0);

			beam.SetBeamE(8.0);
			beam.SetSlabE(1.0);

			GenericShape girder;
			girder.SetArea(98.5);
			girder.SetIxx(31100.0);
			auto centroid = girder.GetCentroid();
			centroid->Move(0, 22.0);
			girder.SetCentroid(centroid);
			girder.SetYtop(22.0);
			girder.SetYbottom(22.0);
			girder.SetXleft(15.9/2);
			girder.SetXright(15.9 / 2);

			beam.SetHaunchWidth(15.9);
			beam.SetBeam(girder);

			auto q = beam.GetQslab();
			Assert::AreEqual(q, 1100.68, 0.01);
			auto props = beam.GetElasticProperties().TransformProperties(beam.GetSlabE());
			Assert::AreEqual(props.GetYtop()-beam.GetGrossSlabDepth()-beam.GetHaunchDepth(), 10.83, 0.01);
			Assert::AreEqual(props.GetYbottom(), 33.17, 0.01);
			Assert::AreEqual(props.GetIxx(), 479813.22, 0.01);

			beam.SetBeamE(16.0);
			q = beam.GetQslab();
			Assert::AreEqual(q, 701.35, 0.01);
			props = beam.GetElasticProperties().TransformProperties(beam.GetSlabE());
			Assert::AreEqual(props.GetYtop() - beam.GetGrossSlabDepth() - beam.GetHaunchDepth(), 14.88, 0.01);
			Assert::AreEqual(props.GetYbottom(), 29.12, 0.01);
			Assert::AreEqual(props.GetIxx(), 791310.62, 0.01);

			beam.SetBeamE(24.0);
			q = beam.GetQslab();
			Assert::AreEqual(q, 514.63, 0.01);
			props = beam.GetElasticProperties().TransformProperties(beam.GetSlabE());
			Assert::AreEqual(props.GetYtop() - beam.GetGrossSlabDepth() - beam.GetHaunchDepth(), 16.78, 0.01);
			Assert::AreEqual(props.GetYbottom(), 27.22, 0.01);
			Assert::AreEqual(props.GetIxx(), 1069425.32, 0.01);
		}
	};
}
