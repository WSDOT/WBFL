#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;
using namespace WBFL::Geometry;

namespace EngToolsUnitTests
{
	TEST_CLASS(TestBiaxialBeamStrain)
	{
	public:
		
		TEST_METHOD(Test)
		{
         Point2d p1(1, 2), p2(3, 1), p3(3, 4);
         Line2d naline(p1, p2);
         BiaxialBeamStrain bs(naline, p3, .2);

         Point2d tp1(4, 4), tp2(-4, -4);
         Assert::AreEqual(.2333, bs.GetAxialStrain(tp1), 0.001);
         Assert::AreEqual(-.56667, bs.GetAxialStrain(tp2), 0.001);
         Float64 x, y;
         Assert::IsTrue(bs.GetXStrainLocation(-.56667, -4., x));
         Assert::IsTrue(bs.GetYStrainLocation(0.23333, 4., y));
         Assert::AreEqual(-4., x, 0.001);
         Assert::AreEqual(4., y, 0.001);
         // flip line around and test again
         naline.ThroughPoints(p2, p1);
         bs.SetStrainPlane(naline, p3, .2);
         Assert::AreEqual(.2333, bs.GetAxialStrain(tp1), 0.001);
         Assert::AreEqual(-.56667, bs.GetAxialStrain(tp2), 0.001);
         Assert::IsTrue(bs.GetXStrainLocation(-.56667, -4., x));
         Assert::IsTrue(bs.GetYStrainLocation(0.23333, 4., y));
         Assert::AreEqual(-4., x, 0.001);
         Assert::AreEqual(4., y, 0.001);
      }
	};
}
