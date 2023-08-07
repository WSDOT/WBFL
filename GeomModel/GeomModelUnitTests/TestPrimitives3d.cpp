#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestPrimitives3d)
	{
	public:
		TEST_METHOD(TestSize3d)
		{
			Size3d s0_0_0(0, 0, 0), s1_1_1(1, 1, 1), s0_1_4(0, 1, 4), s1_2_3(1, 2, 3);
			Size3d default_size;
			Assert::IsTrue(default_size == s0_0_0);
			Assert::IsTrue(Size3d(1, 2, 5) == (s1_1_1 + s0_1_4));
			Assert::IsTrue(Size3d(1, 1, -1) == (s1_2_3 - s0_1_4));
			Assert::IsTrue(s1_1_1 != (s1_2_3 - s0_1_4));
			auto s = s1_1_1 / 3;
			Assert::IsTrue(s == Size3d(1 / 3., 1 / 3., 1 / 3.));

			Assert::AreEqual(s1_2_3.Magnitude(), sqrt(14));

			Size3d size_from_point(Point3d(1, 2, 3));
			Assert::IsTrue(std::make_tuple<Float64, Float64, Float64>(1, 2, 3) == size_from_point.GetDimensions());
      }

		TEST_METHOD(TestPoint3d)
		{
			Point3d p123(1, 2, 3);
			Assert::IsTrue(std::make_tuple<Float64, Float64, Float64>(1, 2, 3) == p123.GetLocation());

			Point3d p011(0, 1, 1);
			Point2d p11(1, 1);
			Point3d p111(p11, 1);
			Assert::IsTrue(p011 + p111 == Point3d(1, 2, 2));
			Assert::IsTrue(p011 - p111 == Point3d(-1, 0, 0));

			Assert::IsTrue(Point3d() == Point3d(0, 0, 0));

			Assert::IsFalse(p111 == p011);
			Assert::IsTrue(p111 != p011);

			Assert::AreEqual(p111.Magnitude(), sqrt(3));

			auto p555 = p111;
			p555.Scale(5);
			Assert::IsTrue(std::make_tuple<Float64, Float64, Float64>(5, 5, 5) == p555.GetLocation());

			// Move
			auto p(p111);
			p.Move(p123);
			Assert::IsTrue(p == Point3d(1, 2, 3));
			p = p111;
			p.Move(Point2d(1, 1), 10);
			Assert::IsTrue(p == Point3d(1, 1, 10));
			p = p111;
			p.Move(1, 1, 10);
			Assert::IsTrue(p == Point3d(1, 1, 10));

			// Distance
			Assert::AreEqual(p111.Distance(p123), sqrt(5));
			Assert::AreEqual(p123.Distance(p111), sqrt(5));
			Assert::AreEqual(p111.Distance(1,2,3), sqrt(5));

			// Offset
			p = p111;
			p.Offset(1, 1, 1);
			Assert::IsTrue(p == Point3d(2, 2, 2));
			p = p111;
			p.Offset(Size3d(1, 1, 1));
			Assert::IsTrue(p == Point3d(2, 2, 2));

			// OffsetBy
			p = p111;
			Assert::IsTrue(p.OffsetBy(1, 1, 1) == Point3d(2, 2, 2));
			Assert::IsTrue(p == Point3d(1, 1, 1)); // p does not change
			p = p111;
			Assert::IsTrue(p.OffsetBy(Size3d(1, 1, 1)) == Point3d(2, 2, 2));
			Assert::IsTrue(p == Point3d(1, 1, 1)); // p does not change

			p = p123;
			Assert::AreEqual(p.X(), 1.0);
			Assert::AreEqual(p.Y(), 2.0);
			Assert::AreEqual(p.Z(), 3.0);
			p.X() = 10;
			p.Y() = 20;
			p.Z() = 30;
			Assert::AreEqual(p.X(), 10.0);
			Assert::AreEqual(p.Y(), 20.0);
			Assert::AreEqual(p.Z(), 30.0);
		}
	};
}
