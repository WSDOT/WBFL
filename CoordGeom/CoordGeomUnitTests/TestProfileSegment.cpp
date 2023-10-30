#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestProfileSegment)
	{
	public:
		
		TEST_METHOD(Test)
		{
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(1, profile);

         auto segment = ProfileSegment::Create(ProfilePoint(100, 100), ProfilePoint(200, 200));
         profile->AddProfileElement(segment);

         Assert::IsTrue(IsEqual(segment->GetLength(), 100.0));

         Float64 grade, elevation;
         std::tie(grade, elevation) = segment->ComputeGradeAndElevation(150);
         Assert::IsTrue(IsEqual(grade, tan(M_PI / 4)));
         Assert::IsTrue(IsEqual(elevation, 150.0));
      }
	};
}
