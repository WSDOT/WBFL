#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestProfilePoint)
	{
	public:
		
		TEST_METHOD(Test)
		{
         Station s(100.0);
         ProfilePoint p(s, 200);
         Station x;
         Float64 y;
         std::tie(x, y) = p.GetLocation();
         Assert::IsTrue(s == x);
         Assert::IsTrue(IsEqual(y, 200.));

         ProfilePoint z;
         Assert::IsTrue(z.GetStation() == 0.0);
         Assert::IsTrue(IsZero(z.GetElevation()));

         ProfilePoint zz(z);
         Assert::IsTrue(zz == z);

         Assert::IsTrue(p != z);
      }
	};
}
