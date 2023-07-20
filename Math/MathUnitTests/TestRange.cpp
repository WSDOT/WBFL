#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestRange)
	{
	public:
		
		TEST_METHOD(Test)
		{
         Range r1;
         Assert::IsTrue(r1.IsNull());
         r1.Set(10, Range::BoundType::Bound, 150, Range::BoundType::Bound);
         Range r2(-220, Range::BoundType::Bound, 100, Range::BoundType::Limit);
         Range r3 = r1.Intersection(r2);
         Range r4 = r2.Intersection(r1);
         Assert::IsTrue(r3 == r4);
         Range r5;
         r5.SetLeftBoundLocation(10);
         r5.SetRightBoundLocation(100);
         r5.SetLeftBoundType(Range::BoundType::Bound);
         r5.SetRightBoundType(Range::BoundType::Limit);
         Assert::IsTrue(r5 == r4);
         r4 = r2.Union(r1);
         r5.SetLeftBoundLocation(-220);
         r5.SetRightBoundLocation(150);
         r5.SetLeftBoundType(Range::BoundType::Bound);
         r5.SetRightBoundType(Range::BoundType::Bound);
         Assert::IsTrue(r5 == r4);
         Assert::IsTrue(r5.GetLeftBoundLocation() == -220);
         Assert::IsTrue(r5.GetRightBoundLocation() == 150);
         Assert::IsTrue(r5.GetLeftBoundType() == Range::BoundType::Bound);
         Assert::IsTrue(r5.GetRightBoundType() == Range::BoundType::Bound);
         r5.SetNull();
         Assert::IsTrue(r5.IsNull());
      }
	};
}
