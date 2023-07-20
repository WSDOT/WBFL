#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSurfaceTemplate)
	{
	public:
		
		TEST_METHOD(Test)
		{
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         Float64 elev = 100.0;
         auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
         profile->AddProfileElement(segment); // flat profile at elevation 100
         auto surface = Surface::Create(4, 2, 2);
         profile->AddSurface(0, surface);
         alignment->AddProfile(0, profile);

         auto surface_template = surface->CreateSurfaceTemplate(0.00);
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         Assert::IsTrue(IsEqual(surface_template->GetRidgePointElevationChange(0, 4), 0.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointElevationChange(0, 1), 0.4));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointElevationChange(1, 2), 0.2));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointElevationChange(2, 3), -0.2));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointElevationChange(3, 4), -0.4));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointElevationChange(0, 2), 0.6));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointElevationChange(2, 4), -0.6));

         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(0, -5.0), 0.0));
         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(0, 5.0), 0.2));
         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(1, -5.0), -0.2));
         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(1, 5.0), 0.1));
         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(4, -5.0), 0.2));
         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(4, 5.0), 0.0));
         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(2, -5.0), -0.1));
         Assert::IsTrue(IsEqual(surface_template->GetElevationChange(2, 5.0), -0.1));

         Assert::IsTrue(IsEqual(surface_template->GetSlope(0, -5.0), 0.0));
         Assert::IsTrue(IsEqual(surface_template->GetSlope(0, 5.0), 0.04));
         Assert::IsTrue(IsEqual(surface_template->GetSlope(1, -5.0), 0.04));
         Assert::IsTrue(IsEqual(surface_template->GetSlope(1, 5.0), 0.02));
         Assert::IsTrue(IsEqual(surface_template->GetSlope(4, -5.0), -0.04));
         Assert::IsTrue(IsEqual(surface_template->GetSlope(4, 5.0), 0.0));
         Assert::IsTrue(IsEqual(surface_template->GetSlope(2, -5.0), 0.02));
         Assert::IsTrue(IsEqual(surface_template->GetSlope(2, 5.0), -0.02));

         Assert::IsTrue(IsEqual(surface_template->GetSegmentSlope(0), 0.04));
         Assert::IsTrue(IsEqual(surface_template->GetSegmentSlope(1), 0.02));
         Assert::IsTrue(IsEqual(surface_template->GetSegmentSlope(2), -0.02));
         Assert::IsTrue(IsEqual(surface_template->GetSegmentSlope(3), -0.04));

         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(0, 4), 40.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(4, 0), -40.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(0, 1), 10.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(1, 2), 10.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(2, 3), 10.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(3, 4), 10.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(0, 2), 20.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(2, 4), 20.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(4, 2), -20.0));
         Assert::IsTrue(IsEqual(surface_template->GetRidgePointOffset(2, 2), 0.0));

         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(0, 0) == std::make_pair(0.0, elev - 0.6));
         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(0, 4) == std::make_pair(40.0, elev - 0.6));
         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(0, 1) == std::make_pair(10.0, elev - 0.2));
         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(1, 0) == std::make_pair(-10.0, elev - 0.6));
         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(2, 4) == std::make_pair(20.0, elev - 0.6));
         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(4, 2) == std::make_pair(-20.0, elev));
         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(2, 3) == std::make_pair(10.0, elev - 0.2));
         Assert::IsTrue(surface_template->GetRidgePointOffsetAndElevation(3, 4) == std::make_pair(10.0, elev - 0.6));
      }
	};
}
