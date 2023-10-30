#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSurfaceProfile)
	{
	public:
		
		TEST_METHOD(Test)
		{
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         Float64 station1 = 0.0;
         Float64 station2 = 100.0;
         Float64 elev1 = 10.0;
         Float64 elev2 = 20.0;
         auto segment = ProfileSegment::Create(ProfilePoint(station1, elev1), ProfilePoint(station2, elev2));
         profile->AddProfileElement(segment); // uphill profile with a 10 ft rise over 100 ft
         auto surface = Surface::Create(4, 2, 2);
         profile->AddSurface(0, surface);
         alignment->AddProfile(0, profile);

         auto surface_template = surface->CreateSurfaceTemplate(station1);
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         surface_template = surface->CreateSurfaceTemplate(station2);
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         // cut with a 45 degree right skew
         Float64 cut_station = (station1 + station2) / 2;
         auto surface_profile = surface->CreateSurfaceProfileSectionCut(cut_station, M_PI / 4, true);
         Assert::IsTrue(surface_profile->GetSurface() == surface);
         Assert::IsTrue(surface_profile->GetSkewAngle() == Angle(M_PI / 4));
         Assert::IsTrue(surface_profile->GetDirection() == Direction(M_PI / 4));

         auto surface_point = surface_profile->GetSurfacePoint(0);
         Assert::IsTrue(surface_point->GetSurface() == surface);
         Assert::IsTrue(surface_point->GetStation() == Station(70.0));
         Assert::IsTrue(IsEqual(surface_point->GetNormalOffset(), -20.0));
         Assert::IsTrue(IsEqual(surface_point->GetCutlineOffset(), -28.284271247461902));
         Assert::IsTrue(IsEqual(surface_point->GetElevation(), 16.4));
         Assert::IsTrue(surface_point->GetPoint() == WBFL::Geometry::Point3d(70, 20, 16.4));

         surface_point = surface_profile->GetSurfacePoint(4);
         Assert::IsTrue(surface_point->GetSurface() == surface);
         Assert::IsTrue(surface_point->GetStation() == Station(30.0));
         Assert::IsTrue(IsEqual(surface_point->GetNormalOffset(), 20.0));
         Assert::IsTrue(IsEqual(surface_point->GetCutlineOffset(), 28.284271247461902));
         Assert::IsTrue(IsEqual(surface_point->GetElevation(), 12.4));
         Assert::IsTrue(surface_point->GetPoint() == WBFL::Geometry::Point3d(30, -20, 12.4));

         // cut with a 45 degree left skew
         surface_profile = surface->CreateSurfaceProfileSectionCut(cut_station, -M_PI / 4, true);
         Assert::IsTrue(surface_profile->GetSurface() == surface);
         Assert::IsTrue(surface_profile->GetSkewAngle() == Angle(-M_PI / 4));
         Assert::IsTrue(surface_profile->GetDirection() == Direction(3 * M_PI / 4));

         surface_point = surface_profile->GetSurfacePoint(0);
         Assert::IsTrue(surface_point->GetSurface() == surface);
         Assert::IsTrue(surface_point->GetStation() == Station(30.0));
         Assert::IsTrue(IsEqual(surface_point->GetNormalOffset(), -20.0));
         Assert::IsTrue(IsEqual(surface_point->GetCutlineOffset(), -28.284271247461902));
         Assert::IsTrue(IsEqual(surface_point->GetElevation(), 12.4));
         Assert::IsTrue(surface_point->GetPoint() == WBFL::Geometry::Point3d(30, 20, 12.4));

         surface_point = surface_profile->GetSurfacePoint(4);
         Assert::IsTrue(surface_point->GetSurface() == surface);
         Assert::IsTrue(surface_point->GetStation() == Station(70.0));
         Assert::IsTrue(IsEqual(surface_point->GetNormalOffset(), 20.0));
         Assert::IsTrue(IsEqual(surface_point->GetCutlineOffset(), 28.284271247461902));
         Assert::IsTrue(IsEqual(surface_point->GetElevation(), 16.4));
         Assert::IsTrue(surface_point->GetPoint() == WBFL::Geometry::Point3d(70, -20, 16.4));
      }
	};
}
