#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestLineSegment3d)
	{
	public:

      TEST_METHOD(Test)
      {
         //
         // Test Length property
         //
         LineSegment3d seg(10, 10, 10, 20, 20, 20);
         Float64 length = seg.Length();
         Assert::IsTrue(IsEqual(length, 17.320508));

         //
         // Test Offset method
         //
         seg.Offset(-10, -10, 0);
         Assert::IsTrue(IsEqual(seg.GetStartPoint().X(), 0.0));
         Assert::IsTrue(IsEqual(seg.GetStartPoint().Y(), 0.0));
         Assert::IsTrue(IsEqual(seg.GetStartPoint().Z(), 10.0));
         Assert::IsTrue(IsEqual(seg.GetEndPoint().X(), 10.0));
         Assert::IsTrue(IsEqual(seg.GetEndPoint().Y(), 10.0));
         Assert::IsTrue(IsEqual(seg.GetEndPoint().Z(), 20.0));

         seg.ThroughPoints(Point3d(10, 10, 10), Point3d(20, 20, 20));

         auto midpoint = seg.GetMidPoint();
         Assert::IsTrue(IsEqual(midpoint.X(), 15.0));
         Assert::IsTrue(IsEqual(midpoint.Y(), 15.0));
         Assert::IsTrue(IsEqual(midpoint.Z(), 15.0));
      }
	};
}
