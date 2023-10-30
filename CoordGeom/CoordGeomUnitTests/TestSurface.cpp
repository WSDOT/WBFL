#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSurface)
	{
	public:
		
		TEST_METHOD(BasicSurface)
      {
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         Float64 elev = 100.0;
         auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
         profile->AddProfileElement(segment); // flat profile at elevation 100
         auto surface = Surface::Create(4, 2, 2);
         profile->AddSurface(0, surface);
         alignment->AddProfile(0, profile);

         Assert::IsTrue(surface->GetSurfaceTemplateSegmentCount() == 4);

         auto surface_template = surface->CreateSurfaceTemplate(0.00); // Template at Station 0+00
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         surface_template = surface->CreateSurfaceTemplate(50.00); // Template at Station 0+50
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         surface_template = surface->CreateSurfaceTemplate(100.00); // Template at Station 1+00
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         std::shared_ptr<SurfaceTemplate> st1, st2;
         std::tie(st1, st2) = surface->GetBoundingTemplates(25.0);
         Assert::IsTrue(st1->GetStation() == Station(0.00));
         Assert::IsTrue(st2->GetStation() == Station(50.00));

         std::tie(st1, st2) = surface->GetBoundingTemplates(75.0);
         Assert::IsTrue(st1->GetStation() == Station(50.00));
         Assert::IsTrue(st2->GetStation() == Station(100.00));

         std::tie(st1, st2) = surface->GetBoundingTemplates(-50);
         Assert::IsTrue(st1->GetStation() == Station(0.00));
         Assert::IsTrue(st2->GetStation() == Station(0.00));

         std::tie(st1, st2) = surface->GetBoundingTemplates(200);
         Assert::IsTrue(st1->GetStation() == Station(100.00));
         Assert::IsTrue(st2->GetStation() == Station(100.00));

         Assert::IsTrue(surface->ContainsStation(0.0) == true);
         Assert::IsTrue(surface->ContainsStation(50.0) == true);
         Assert::IsTrue(surface->ContainsStation(100.0) == true);
         Assert::IsTrue(surface->ContainsStation(-100.0) == false);
         Assert::IsTrue(surface->ContainsStation(500.0) == false);

         Station s1, s2;
         std::tie(s1, s2) = surface->GetStationRange();
         Assert::IsTrue(s1 == Station(0.0));
         Assert::IsTrue(s2 == Station(100.0));
      }

      TEST_METHOD(WidenedSurface)
      {
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         Float64 elev = 100.0;
         auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
         profile->AddProfileElement(segment); // flat profile at elevation 100
         auto surface = Surface::Create(4, 2, 2);
         profile->AddSurface(0, surface);
         alignment->AddProfile(0, profile);

         auto surface_template = surface->CreateSurfaceTemplate(0.00); // Template at Station 0+00
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         surface_template = surface->CreateSurfaceTemplate(100.00); // Template at Station 1+00
         surface_template->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto widening = Widening::Create();
         surface->AddWidening(widening);
         widening->SetSegment(0, 0);
         widening->SetSegment(1, 3);
         widening->SetWidening(10.0);
         widening->SetBeginTransition(10.0);
         widening->SetBeginFullWidening(40.0);
         widening->SetEndFullWidening(60.0);
         widening->SetEndTransition(90.0);

         auto template_cut = surface->CreateSurfaceTemplateSectionCut(-50.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(25.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 15.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 15.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 20.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 20.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(75.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 15.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 15.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(150.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

         widening->SetSegment(0, 1);
         widening->SetSegment(1, 2);

         template_cut = surface->CreateSurfaceTemplateSectionCut(25.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 15.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 15.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 20.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 20.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(75.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 15.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 15.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

         widening->SetWidening(-10);
         template_cut = surface->CreateSurfaceTemplateSectionCut(25.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 5.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 5.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 0.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 0.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));

         template_cut = surface->CreateSurfaceTemplateSectionCut(75.0, false);
         Assert::IsTrue(IsEqual(template_cut->GetSegment(0).GetWidth(), 10.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(1).GetWidth(), 5.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(2).GetWidth(), 5.0));
         Assert::IsTrue(IsEqual(template_cut->GetSegment(3).GetWidth(), 10.0));
      }

      TEST_METHOD(SuperelevatedSurface)
      {
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         Float64 elev = 100.0;
         auto segment = ProfileSegment::Create(ProfilePoint(0.0, elev), ProfilePoint(100.0, elev));
         profile->AddProfileElement(segment); // flat profile at elevation 100
         auto surface = Surface::Create(4, 2, 2);
         profile->AddSurface(0, surface);
         alignment->AddProfile(0, profile);

         auto surface_template1 = surface->CreateSurfaceTemplate(0.00); // Template at Station 0+00
         surface_template1->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template1->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template1->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template1->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto surface_template2 = surface->CreateSurfaceTemplate(100.00); // Template at Station 1+00
         surface_template2->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template2->UpdateSegmentParameters(1, 10, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template2->UpdateSegmentParameters(2, 10, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template2->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto superelevation = Superelevation::Create(0.0, 40, 60, 100, 0.06, 2); // pivot about center
         surface->AddSuperelevation(superelevation);

         auto template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(0), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(3), 0.06));

         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(0), 98.8));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(1), 99.4));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(2), 100.0));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(3), 100.6));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(4), 101.2));

         // pivot about left edge
         superelevation->SetPivotPoint(0);
         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(0), 99.4));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(1), 100.0));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(2), 100.6));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(3), 101.2));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(4), 101.8));

         // pivot about right edge
         superelevation->SetPivotPoint(4);
         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(0), 97.0));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(1), 97.6));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(2), 98.2));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(3), 98.8));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(4), 99.4));

         // Fix the slope of the outside so it isn't changed by superelevation
         surface_template1->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
         surface_template2->UpdateSegmentParameters(0, 10, 0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
         surface_template1->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
         surface_template2->UpdateSegmentParameters(3, 10, -0.04, SurfaceTemplateSegment::SlopeType::FixedHorizontal);
         superelevation->SetPivotPoint(2); // pivot about center
         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(0), 0.04));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(3), -0.04));

         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(0), 99.0));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(1), 99.4));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(2), 100.0));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(3), 100.6));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(4), 100.2));

         superelevation->SetPivotPoint(0); // pivot about left edge
         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(0), 0.04));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(3), -0.04));

         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(0), 99.4));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(1), 99.8));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(2), 100.4));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(3), 101.0));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(4), 100.6));

         superelevation->SetPivotPoint(4); // pivot about right edge
         template_cut = surface->CreateSurfaceTemplateSectionCut(50.0, true);
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(0), 0.04));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(1), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(2), 0.06));
         Assert::IsTrue(IsEqual(template_cut->GetSegmentSlope(3), -0.04));

         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(0), 98.2));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(1), 98.6));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(2), 99.2));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(3), 99.8));
         Assert::IsTrue(IsEqual(template_cut->GetRidgePointElevation(4), 99.4));
      }
   };
}
