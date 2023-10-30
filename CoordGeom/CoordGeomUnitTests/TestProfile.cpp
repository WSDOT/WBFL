#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestProfile)
	{
	public:

      void TestGrade(const Profile& profile, Float64 results[], long minStation = 440, long maxStation = 1560, long inc = 160)
      {
         auto alignment = profile.GetAlignment();
         long j = 0;
         for (long i = minStation; i <= maxStation; i += inc, j++)
         {
            auto station = alignment->ConvertFromNormalizedStation((Float64)i);
            auto grade = profile.Grade(station);
            Assert::IsTrue(IsEqual(grade * 100, results[j]));
            CHECK(IsEqual(grade * 100, results[j]));
         }
      }

      //#include <iomanip>
      void TestElevation(const Profile& profile, IndexType surfaceIdx, Float64 offset, Float64 results[], long minStation = 440, long maxStation = 1560, long inc = 160)
      {
         auto alignment = profile.GetAlignment();
         long j = 0;
         for (long i = minStation; i <= maxStation; i += inc, j++)
         {
            auto station = alignment->ConvertFromNormalizedStation((Float64)i);
            auto elevation = profile.Elevation(surfaceIdx, station, offset);
            Assert::IsTrue(IsEqual(elevation, results[j]));
            //std::cout << std::fixed << std::setprecision(5);
            //std::cout << elevation << ", " << results[j] << std::endl;
         }
         //std::cout << std::endl;
      }

      void TestCrownSlopes(const Profile& profile, IndexType surfaceIdx, IndexType ridgePointIdx, Float64 results[][2], long minStation = 440, long maxStation = 1560, long inc = 160)
      {
         auto alignment = profile.GetAlignment();
         auto surface = profile.GetSurface(surfaceIdx);

         IndexType leftSegmentIdx = ridgePointIdx - 1;
         IndexType rightSegmentIdx = ridgePointIdx;

         long j = 0;
         for (long i = minStation; i <= maxStation; i += inc, j++)
         {
            auto station = alignment->ConvertFromNormalizedStation((Float64)i);

            auto surface_template = profile.CreateSurfaceTemplateSectionCut(surfaceIdx, station, true);
            auto left = surface_template->GetSegmentSlope(leftSegmentIdx);
            auto right = surface_template->GetSegmentSlope(rightSegmentIdx);

            Assert::IsTrue(IsEqual(left, results[j][0]));
            CHECK(IsEqual(left, results[j][0]));

            Assert::IsTrue(IsEqual(right, results[j][1]));
            CHECK(IsEqual(right, results[j][1]));
         }
      }

      TEST_METHOD(Test1)
      {
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         auto segment = ProfileSegment::Create();
         segment->Move(ProfilePoint(100, 50), ProfilePoint(50, 10));
         profile->AddProfileElement(segment);

         auto vc = VerticalCurve::Create();
         vc->Init(ProfilePoint(200, 250), ProfilePoint(300, 250), ProfilePoint(400, 150), 100, 100);
         profile->AddProfileElement(vc);

         Assert::IsTrue(profile->GetProfileElementCount() == 2);

         Assert::IsTrue(profile->GetProfileElement(0) == segment);
         Assert::IsTrue(profile->GetProfileElement(1) == vc);

         profile->ClearProfileElements();
         Assert::IsTrue(profile->GetProfileElementCount() == 0);

         auto original_surface = Surface::Create();
         profile->AddSurface(0, original_surface);

         auto finished_surface = Surface::Create();
         profile->AddSurface(1, finished_surface);
      }

      TEST_METHOD(Test2)
      {
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         //
         // Test Elevation and Grade
         //
         // Alignment has station equations
         //
         // Station 4+00 back = 8+00 ahead
         // Station 12+00 back = 10+00 ahead
         alignment->AddStationEquation(400, 800);
         alignment->AddStationEquation(1200, 1000);

         // Profile Point: Station 10+00,1 Elev 80.0 (6+00 normalized)
         // Vert Curve: BVC 11+00,1 Elev  85.0 (7+00 normalized)
         //             PVI 12+00,2 Elev 100.0 (10+00 normalized)
         //             EVC 15+00,2 Elev  91.0 (13+00 normalized)
         // Profile Point: Station 16+00,2 Elev 88.0 (14+00 normalized)
         auto seg1 = ProfileSegment::Create();
         seg1->Move(ProfilePoint(600, 80), ProfilePoint(700, 85));
         auto vc = VerticalCurve::Create();
         vc->Init(ProfilePoint(700, 85), ProfilePoint(1000, 100), ProfilePoint(1300, 91), 300, 300);
         auto seg2 = ProfileSegment::Create();
         seg2->Move(ProfilePoint(1300, 91), ProfilePoint(1400, 88));
         profile->AddProfileElement(seg1);
         profile->AddProfileElement(vc);
         profile->AddProfileElement(seg2);

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);
         surface->SetSurfaceTemplateSegmentCount(4);

         auto template430 = surface->CreateSurfaceTemplate(430.0);
         template430->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template700 = surface->CreateSurfaceTemplate(700); // 11+00,1 = 7+00 normalized
         template700->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1000 = surface->CreateSurfaceTemplate(1000); // 12+00,2 = 10+00 normalized
         template1000->UpdateSegmentParameters(0, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(1, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(2, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(3, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1300 = surface->CreateSurfaceTemplate(1300); // 15+00,2 = 13+00 normalized
         template1300->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1600 = surface->CreateSurfaceTemplate(1600);
         template1600->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.06667, -0.06667, -2.2000, -3.0000, -3.0000 };
         TestGrade(*profile, Grades);

         Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.03867, -0.04933}, { -0.03333,-0.06533}, { 0.0200, -0.07600}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes1);

         Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.40666, 95.03333, 92.740, 88.000, 83.200 };
         Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
         Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.52666, 94.04666, 92.180, 87.600, 82.800 };
         TestElevation(*profile, 0, -15, ElevA);
         TestElevation(*profile, 0, -5, ElevB);
         TestElevation(*profile, 0, -2, ElevC);
         TestElevation(*profile, 0, 0, ElevD);
         TestElevation(*profile, 0, 5, ElevE);

         // shift the crown point offset to +5
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.96666, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.30666, 92.600, 88.080, 83.280 };
         Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.20666, 92.660, 88.200, 83.400 };
         Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.08666, 93.55333, 91.900, 87.400, 82.600 };
         TestElevation(*profile, 0, -5, ElevF);
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, 2, ElevH);
         TestElevation(*profile, 0, 5, ElevI);
         TestElevation(*profile, 0, 15, ElevJ);

         // shift the crown point offset back to -5 and reverse all of the segment template segment slopes
         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);

         auto& templates = surface->GetSurfaceTemplates();
         for (auto& surface_template : templates)
         {
            auto nSegments = surface_template->GetCount();
            for (auto i = 0; i < nSegments; i++)
            {
               auto& surface_template_segment = surface_template->GetSegment(i);
               auto slope = surface_template_segment.GetSlope();
               slope *= -1;
               surface_template_segment.SetSlope(slope);
            }
         }

         Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, {  0.03867,  0.04933}, { 0.033333, 0.065333}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes2);

         Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.71333, 92.380, 88.000, 83.200 };
         Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.52667, 94.04667, 92.180, 87.600, 82.800 };
         Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.67467, 94.24267, 92.408, 87.840, 83.040 };
         Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         TestElevation(*profile, 0, -15, ElevK);
         TestElevation(*profile, 0, -5, ElevL);
         TestElevation(*profile, 0, -2, ElevM);
         TestElevation(*profile, 0, 0, ElevN);
         TestElevation(*profile, 0, 5, ElevO);

         // shift the crown point offset to +5, keep the slopes the same
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.20667, 92.660, 88.200, 83.400 };
         Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.85067, 94.440, 92.520, 87.920, 83.120 };
         Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.96667, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.19333, 93.220, 88.600, 83.800 };
         TestElevation(*profile, 0, -5, ElevP);
         TestElevation(*profile, 0, 0, ElevQ);
         TestElevation(*profile, 0, 2, ElevR);
         TestElevation(*profile, 0, 5, ElevS);
         TestElevation(*profile, 0, 15, ElevT);
      }

      TEST_METHOD(Test3)
      {
         //
         // Test Elevation and Grade
         //
         //
         // Vert Curve: BVC  7+00 Elev  85.0
         //             PVI 10+00 Elev 100.0
         //             EVC 13+00 Elev  91.0
         //
         // Profile Point: Station 14+00 Elev 88.0

         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         auto vc = VerticalCurve::Create(ProfilePoint(700, 85), ProfilePoint(1000, 100), ProfilePoint(1300, 91), 300, 300);
         auto seg = ProfileSegment::Create();
         seg->Move(ProfilePoint(1300, 91), ProfilePoint(1400, 88));

         profile->AddProfileElement(vc);
         profile->AddProfileElement(seg);

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);
         surface->SetSurfaceTemplateSegmentCount(4);

         auto template430 = surface->CreateSurfaceTemplate(430.0);
         template430->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template700 = surface->CreateSurfaceTemplate(700); // 11+00,1 = 7+00 normalized
         template700->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1000 = surface->CreateSurfaceTemplate(1000); // 12+00,2 = 10+00 normalized
         template1000->UpdateSegmentParameters(0, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(1, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(2, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(3, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1300 = surface->CreateSurfaceTemplate(1300); // 15+00,2 = 13+00 normalized
         template1300->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1600 = surface->CreateSurfaceTemplate(1600);
         template1600->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.06667, -0.06667, -2.2000, -3.0000, -3.0000 };
         TestGrade(*profile, Grades);

         Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.03867, -0.04933}, { -0.03333,-0.06533}, { 0.0200, -0.07600}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes1);

         Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.40666, 95.03333, 92.740, 88.000, 83.200 };
         Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
         Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.52666, 94.04666, 92.180, 87.600, 82.800 };
         TestElevation(*profile, 0, -15, ElevA);
         TestElevation(*profile, 0, -5, ElevB);
         TestElevation(*profile, 0, -2, ElevC);
         TestElevation(*profile, 0, 0, ElevD);
         TestElevation(*profile, 0, 5, ElevE);

         // shift the crown point offset to +5
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.96666, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.30666, 92.600, 88.080, 83.280 };
         Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.20666, 92.660, 88.200, 83.400 };
         Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.08666, 93.55333, 91.900, 87.400, 82.600 };
         TestElevation(*profile, 0, -5, ElevF);
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, 2, ElevH);
         TestElevation(*profile, 0, 5, ElevI);
         TestElevation(*profile, 0, 15, ElevJ);

         // shift the crown point offset back to -5 and reverse all of the segment template segment slopes
         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);

         auto& templates = surface->GetSurfaceTemplates();
         for (auto& surface_template : templates)
         {
            auto nSegments = surface_template->GetCount();
            for (auto i = 0; i < nSegments; i++)
            {
               auto& surface_template_segment = surface_template->GetSegment(i);
               auto slope = surface_template_segment.GetSlope();
               slope *= -1;
               surface_template_segment.SetSlope(slope);
            }
         }

         Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, {  0.03867,  0.04933}, { 0.033333, 0.065333}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes2);

         Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.71333, 92.380, 88.000, 83.200 };
         Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.52667, 94.04667, 92.180, 87.600, 82.800 };
         Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.67467, 94.24267, 92.408, 87.840, 83.040 };
         Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         TestElevation(*profile, 0, -15, ElevK);
         TestElevation(*profile, 0, -5, ElevL);
         TestElevation(*profile, 0, -2, ElevM);
         TestElevation(*profile, 0, 0, ElevN);
         TestElevation(*profile, 0, 5, ElevO);

         // shift the crown point offset to +5, keep the slopes the same
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.20667, 92.660, 88.200, 83.400 };
         Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.85067, 94.440, 92.520, 87.920, 83.120 };
         Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.96667, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.19333, 93.220, 88.600, 83.800 };
         TestElevation(*profile, 0, -5, ElevP);
         TestElevation(*profile, 0, 0, ElevQ);
         TestElevation(*profile, 0, 2, ElevR);
         TestElevation(*profile, 0, 5, ElevS);
         TestElevation(*profile, 0, 15, ElevT);
      }

      TEST_METHOD(Test4)
      {
         //
         // Test Elevation and Grade
         //
         //
         // Vert Curve: BVC  7+00 Elev  85.0
         //             PVI 10+00 Elev 100.0
         //             EVC 13+00 Elev  91.0
         //
         // Vert Curve: BVC 13+90 Elev  85.0
         //             PVI 14+50 Elev 100.0
         //             EVC 14+90 Elev  91.0

         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         auto vc1 = VerticalCurve::Create(ProfilePoint(700, 85), ProfilePoint(1000, 100), ProfilePoint(1300, 91), 300, 300);
         auto vc2 = VerticalCurve::Create(ProfilePoint(1390, 85), ProfilePoint(1450, 100), ProfilePoint(1490, 91), 60, 40);

         profile->AddProfileElement(vc1);
         profile->AddProfileElement(vc2);

         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);
         surface->SetSurfaceTemplateSegmentCount(4);

         auto template430 = surface->CreateSurfaceTemplate(430.0);
         template430->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template700 = surface->CreateSurfaceTemplate(700); // 11+00,1 = 7+00 normalized
         template700->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1000 = surface->CreateSurfaceTemplate(1000); // 12+00,2 = 10+00 normalized
         template1000->UpdateSegmentParameters(0, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(1, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(2, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(3, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1300 = surface->CreateSurfaceTemplate(1300); // 15+00,2 = 13+00 normalized
         template1300->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1600 = surface->CreateSurfaceTemplate(1600);
         template1600->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.06667, -0.06667, -2.2000, 21.83333, -22.5000 };
         TestGrade(*profile, Grades);

         Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.03867, -0.04933}, { -0.03333,-0.06533}, { 0.0200, -0.07600}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes1);

         Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.40666, 95.03333, 92.740, 87.34167, 75.250 };
         Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 87.74167, 75.650 };
         Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 87.50167, 75.410 };
         Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 87.34167, 75.250 };
         Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.52666, 94.04666, 92.180, 86.94167, 74.850 };
         TestElevation(*profile, 0, -15, ElevA);
         TestElevation(*profile, 0, -5, ElevB);
         TestElevation(*profile, 0, -2, ElevC);
         TestElevation(*profile, 0, 0, ElevD);
         TestElevation(*profile, 0, 5, ElevE);

         // shift the crown point offset to +5
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.96666, 94.540, 92.460,    87.14167, 75.050 };
         Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560,  87.34167, 75.250 };
         Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.30666, 92.600,    87.42167, 75.330 };
         Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.20666, 92.660,    87.54167, 75.450 };
         Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.08666, 93.553333, 91.900, 86.74167, 74.650 };
         TestElevation(*profile, 0, -5, ElevF);
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, 2, ElevH);
         TestElevation(*profile, 0, 5, ElevI);
         TestElevation(*profile, 0, 15, ElevJ);

         // shift the crown point offset back to -5 and reverse all of the crown slopes
         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);

         auto& templates = surface->GetSurfaceTemplates();
         for (auto& surface_template : templates)
         {
            auto nSegments = surface_template->GetCount();
            for (auto i = 0; i < nSegments; i++)
            {
               auto& surface_template_segment = surface_template->GetSegment(i);
               auto slope = surface_template_segment.GetSlope();
               slope *= -1;
               surface_template_segment.SetSlope(slope);
            }
         }

         Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, {  0.03867,  0.04933}, { 0.033333, 0.065333}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes2);

         Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.71333, 92.380,   87.34167, 75.250 };
         Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.52667, 94.04667, 92.180, 86.94167, 74.850 };
         Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.67467, 94.24267, 92.408,  87.18167, 75.090 };
         Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 87.34167, 75.250 };
         Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940,     87.74167, 75.650 };
         TestElevation(*profile, 0, -15, ElevK);
         TestElevation(*profile, 0, -5, ElevL);
         TestElevation(*profile, 0, -2, ElevM);
         TestElevation(*profile, 0, 0, ElevN);
         TestElevation(*profile, 0, 5, ElevO);

         // shift the crown point offset to +5, keep the slopes the same
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.20667, 92.660,   87.54167, 75.450 };
         Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 87.34167, 75.250 };
         Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.85067, 94.440, 92.520,   87.26167, 75.170 };
         Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.96667, 94.540, 92.460,   87.14167, 75.050 };
         Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.19333, 93.220,   87.94167, 75.850 };
         TestElevation(*profile, 0, -5, ElevP);
         TestElevation(*profile, 0, 0, ElevQ);
         TestElevation(*profile, 0, 2, ElevR);
         TestElevation(*profile, 0, 5, ElevS);
         TestElevation(*profile, 0, 15, ElevT);
      }

      TEST_METHOD(Test5)
      {
         //
         // Test Elevation and Grade
         //
         //
         // Profile Point: Station 6+10 Elev 80.5
         // Profile Point: Station 6+50 Elev 82.5
         // Vert Curve: BVC  7+00 Elev  85.0
         //             PVI 10+00 Elev 100.0
         //             EVC 13+00 Elev  91.0
         // Profile Point: Station 14+00 Elev 88.0

         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         auto seg1 = ProfileSegment::Create(ProfilePoint(610, 80.5), ProfilePoint(650, 82.5));
         auto vc = VerticalCurve::Create(ProfilePoint(700, 85), ProfilePoint(1000, 100), ProfilePoint(1300, 91), 300, 300);
         auto seg2 = ProfileSegment::Create(ProfilePoint(1300, 91), ProfilePoint(1400, 88));

         profile->AddProfileElement(seg1);
         profile->AddProfileElement(vc);
         profile->AddProfileElement(seg2);

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);
         surface->SetSurfaceTemplateSegmentCount(4);

         auto template430 = surface->CreateSurfaceTemplate(430.0);
         template430->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template700 = surface->CreateSurfaceTemplate(700); // 11+00,1 = 7+00 normalized
         template700->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1000 = surface->CreateSurfaceTemplate(1000); // 12+00,2 = 10+00 normalized
         template1000->UpdateSegmentParameters(0, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(1, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(2, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(3, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1300 = surface->CreateSurfaceTemplate(1300); // 15+00,2 = 13+00 normalized
         template1300->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1600 = surface->CreateSurfaceTemplate(1600);
         template1600->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.06667, -0.06667, -2.2000, -3.0000, -3.0000 };
         TestGrade(*profile, Grades);

         Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.03867, -0.04933}, { -0.03333,-0.06533}, { 0.0200, -0.07600}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes1);

         Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.40666, 95.03333, 92.740, 88.000, 83.200 };
         Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
         Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.52666, 94.04666, 92.180, 87.600, 82.800 };
         TestElevation(*profile, 0, -15, ElevA);
         TestElevation(*profile, 0, -5, ElevB);
         TestElevation(*profile, 0, -2, ElevC);
         TestElevation(*profile, 0, 0, ElevD);
         TestElevation(*profile, 0, 5, ElevE);

         // shift the crown point offset to +5
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.96666, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.30666, 92.600, 88.080, 83.280 };
         Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.20666, 92.660, 88.200, 83.400 };
         Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.08666, 93.55333, 91.900, 87.400, 82.600 };
         TestElevation(*profile, 0, -5, ElevF);
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, 2, ElevH);
         TestElevation(*profile, 0, 5, ElevI);
         TestElevation(*profile, 0, 15, ElevJ);

         // shift the crown point offset back to -5 and reverse all of the crown slopes
         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);

         auto& templates = surface->GetSurfaceTemplates();
         for (auto& surface_template : templates)
         {
            auto nSegments = surface_template->GetCount();
            for (auto i = 0; i < nSegments; i++)
            {
               auto& surface_template_segment = surface_template->GetSegment(i);
               auto slope = surface_template_segment.GetSlope();
               slope *= -1;
               surface_template_segment.SetSlope(slope);
            }
         }

         Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, {  0.03867,  0.04933}, { 0.033333, 0.065333}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes2);

         Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.71333, 92.380, 88.000, 83.200 };
         Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.52667, 94.04667, 92.180, 87.600, 82.800 };
         Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.67467, 94.24267, 92.408, 87.840, 83.040 };
         Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         TestElevation(*profile, 0, -15, ElevK);
         TestElevation(*profile, 0, -5, ElevL);
         TestElevation(*profile, 0, -2, ElevM);
         TestElevation(*profile, 0, 0, ElevN);
         TestElevation(*profile, 0, 5, ElevO);

         // shift the crown point offset to +5, keep the slopes the same
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.20667, 92.660, 88.200, 83.400 };
         Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.85067, 94.440, 92.520, 87.920, 83.120 };
         Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.96667, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.19333, 93.220, 88.600, 83.800 };
         TestElevation(*profile, 0, -5, ElevP);
         TestElevation(*profile, 0, 0, ElevQ);
         TestElevation(*profile, 0, 2, ElevR);
         TestElevation(*profile, 0, 5, ElevS);
         TestElevation(*profile, 0, 15, ElevT);
      }

      TEST_METHOD(Test6)
      {
         //
         // Test Elevation and Grade
         //
         //
         // Profile Point: Station 6+10 Elev 80.5
         // Profile Point: Station 6+50 Elev 82.5
         // Vert Curve: BVC  7+00 Elev  85.0
         //             PVI 10+00 Elev 100.0
         //             EVC 13+00 Elev  91.0
         // Profile Point: Station 14+00 Elev 88.0
         // Profile Point: Station 14+50 Elev 86.5


         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         auto seg1 = ProfileSegment::Create(ProfilePoint(610, 80.5), ProfilePoint(650, 82.5));
         auto vc = VerticalCurve::Create(ProfilePoint(700, 85), ProfilePoint(1000, 100), ProfilePoint(1300, 91), 300, 300);
         auto seg2 = ProfileSegment::Create(ProfilePoint(1400, 88), ProfilePoint(1450, 86.5));

         profile->AddProfileElement(seg1);
         profile->AddProfileElement(vc);
         profile->AddProfileElement(seg2);

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);
         surface->SetSurfaceTemplateSegmentCount(4);

         auto template430 = surface->CreateSurfaceTemplate(430.0);
         template430->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template700 = surface->CreateSurfaceTemplate(700); // 11+00,1 = 7+00 normalized
         template700->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1000 = surface->CreateSurfaceTemplate(1000); // 12+00,2 = 10+00 normalized
         template1000->UpdateSegmentParameters(0, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(1, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(2, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(3, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1300 = surface->CreateSurfaceTemplate(1300); // 15+00,2 = 13+00 normalized
         template1300->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1600 = surface->CreateSurfaceTemplate(1600);
         template1600->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.06667, -0.06667, -2.2000, -3.0000, -3.0000 };
         TestGrade(*profile, Grades);

         Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.03867, -0.04933}, { -0.03333,-0.06533}, { 0.0200, -0.07600}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes1);

         Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.40666, 95.03333, 92.740, 88.000, 83.200 };
         Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
         Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.52666, 94.04666, 92.180, 87.600, 82.800 };
         TestElevation(*profile, 0, -15, ElevA);
         TestElevation(*profile, 0, -5, ElevB);
         TestElevation(*profile, 0, -2, ElevC);
         TestElevation(*profile, 0, 0, ElevD);
         TestElevation(*profile, 0, 5, ElevE);

         // shift the crown point offset to +5
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.96666, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.30666, 92.600, 88.080, 83.280 };
         Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.20666, 92.660, 88.200, 83.400 };
         Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.08666, 93.55333, 91.900, 87.400, 82.600 };
         TestElevation(*profile, 0, -5, ElevF);
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, 2, ElevH);
         TestElevation(*profile, 0, 5, ElevI);
         TestElevation(*profile, 0, 15, ElevJ);

         // shift the crown point offset back to -5 and reverse all of the crown slopes
         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);

         auto& templates = surface->GetSurfaceTemplates();
         for (auto& surface_template : templates)
         {
            auto nSegments = surface_template->GetCount();
            for (auto i = 0; i < nSegments; i++)
            {
               auto& surface_template_segment = surface_template->GetSegment(i);
               auto slope = surface_template_segment.GetSlope();
               slope *= -1;
               surface_template_segment.SetSlope(slope);
            }
         }

         Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, {  0.03867,  0.04933}, { 0.033333, 0.065333}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes2);

         Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.71333, 92.380, 88.000, 83.200 };
         Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.52667, 94.04667, 92.180, 87.600, 82.800 };
         Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.67467, 94.24267, 92.408, 87.840, 83.040 };
         Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         TestElevation(*profile, 0, -15, ElevK);
         TestElevation(*profile, 0, -5, ElevL);
         TestElevation(*profile, 0, -2, ElevM);
         TestElevation(*profile, 0, 0, ElevN);
         TestElevation(*profile, 0, 5, ElevO);

         // shift the crown point offset to +5, keep the slopes the same
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.20667, 92.660, 88.200, 83.400 };
         Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.85067, 94.440, 92.520, 87.920, 83.120 };
         Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.96667, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.19333, 93.220, 88.600, 83.800 };
         TestElevation(*profile, 0, -5, ElevP);
         TestElevation(*profile, 0, 0, ElevQ);
         TestElevation(*profile, 0, 2, ElevR);
         TestElevation(*profile, 0, 5, ElevS);
         TestElevation(*profile, 0, 15, ElevT);
      }

      TEST_METHOD(Test7)
      {
         // Test a profile with no elements
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         Assert::IsTrue(IsEqual(profile->Elevation(100.00), 0.0));
         Assert::IsTrue(IsEqual(profile->Grade(100.00), 0.0));

         // add a surface and re-test the slopes
         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);
         surface->SetSurfaceTemplateSegmentCount(2);

         auto template0 = surface->CreateSurfaceTemplate(0.0);
         template0->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template0->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template50 = surface->CreateSurfaceTemplate(50.0);
         template50->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template50->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template100 = surface->CreateSurfaceTemplate(100.0);
         template100->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template100->UpdateSegmentParameters(1, 20.0, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template200 = surface->CreateSurfaceTemplate(200.0);
         template200->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template200->UpdateSegmentParameters(1, 20.0, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 0.0, -10), 0.02));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 0.0, 10), -0.02));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 50.0, -10), 0.02));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 50.0, 10), -0.02));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 75.0, -10), 0.03));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 75.0, 10), -0.03));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 100., -10), 0.04));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 100., 10), -0.04));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 150.0, -10), 0.04));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 150.0, 10), -0.04));
      }

      TEST_METHOD(Test8)
      {
         // Test a profile with one point element
         //
         // One point profiles are not allowed in the C++ version
         // This test is originally from the COM version
         // Use a flat profile segment to simulate what the old COM version did
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);
         auto segment = ProfileSegment::Create(ProfilePoint(100, 100), ProfilePoint(200, 100));
         profile->AddProfileElement(segment);

         Assert::IsTrue(IsEqual(profile->Elevation(100.0), 100.0));
         Assert::IsTrue(IsZero(profile->Grade(100.0)));

         // add some cross sections and re-test the crown slopes
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);
         surface->SetSurfaceTemplateSegmentCount(2);

         auto template0 = surface->CreateSurfaceTemplate(0.0);
         template0->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template0->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template50 = surface->CreateSurfaceTemplate(50.0);
         template50->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template50->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template100 = surface->CreateSurfaceTemplate(100.0);
         template100->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template100->UpdateSegmentParameters(1, 20.0, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template200 = surface->CreateSurfaceTemplate(200.0);
         template200->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template200->UpdateSegmentParameters(1, 20.0, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 0.0, -10), 0.02));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 0.0, 10), -0.02));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 50.0, -10), 0.02));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 50.0, 10), -0.02));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 75.0, -10), 0.03));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 75.0, 10), -0.03));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 100., -10), 0.04));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 100., 10), -0.04));

         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 150.0, -10), 0.04));
         Assert::IsTrue(IsEqual(profile->CrossSlope(surface, 150.0, 10), -0.04));
      }

      TEST_METHOD(Test9)
      {
         // Test a profile with one vertical curve element
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         auto vc = VerticalCurve::Create(ProfilePoint(4850, 436.34), ProfilePoint(5250, 432.34), ProfilePoint(5650, 441.14), 400, 400);
         profile->AddProfileElement(vc);

         Assert::IsTrue(IsEqual(profile->Elevation(4700), 437.84));
         Assert::IsTrue(IsEqual(profile->Elevation(4850), 436.34));
         Assert::IsTrue(IsEqual(profile->Elevation(4900), 435.89));
         Assert::IsTrue(IsEqual(profile->Elevation(5000), 435.29));
         Assert::IsTrue(IsEqual(profile->Elevation(5100), 435.09));
         Assert::IsTrue(IsEqual(profile->Elevation(5200), 435.29));
         Assert::IsTrue(IsEqual(profile->Elevation(5300), 435.89));
         Assert::IsTrue(IsEqual(profile->Elevation(5400), 436.89));
         Assert::IsTrue(IsEqual(profile->Elevation(5500), 438.29));
         Assert::IsTrue(IsEqual(profile->Elevation(5600), 440.09));
         Assert::IsTrue(IsEqual(profile->Elevation(5650), 441.14));
         Assert::IsTrue(IsEqual(profile->Elevation(6000), 448.84));
      }

      TEST_METHOD(Test10)
      {
         // Test a profile with one vertical curve element
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         auto vc = VerticalCurve::Create(ProfilePoint(100, 100), ProfilePoint(200, 90), ProfilePoint(300, 100), 50, 50);
         profile->AddProfileElement(vc);

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);
         surface->SetSurfaceTemplateSegmentCount(2);

         auto template50 = surface->CreateSurfaceTemplate(50.0);
         template50->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template50->UpdateSegmentParameters(1, 20.0, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template100 = surface->CreateSurfaceTemplate(100.0);
         template100->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template100->UpdateSegmentParameters(1, 20.0, -0.04, SurfaceTemplateSegment::SlopeType::Horizontal);

         Assert::IsTrue(IsEqual(profile->Elevation(surface, 100, 0.0), 100.00));
         Assert::IsTrue(IsEqual(profile->Elevation(surface, 100, 5.0), 99.80));
         Assert::IsTrue(IsEqual(profile->Elevation(surface, 100, -5.0), 99.90));
      }

      TEST_METHOD(Test11)
      {
         // Test a profile with 3 vertical curve elements
         // Adding this test because I found an error that was
         // not detected by the previous test cases.
         // The elevation at the BVC not computed correctly by the Profile object
         // however, it is computed correctly by the VertCurve object
         // RAB: 11/14/2001
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         ProfilePoint start(100, 50);
         ProfilePoint pvi1(300, 80);
         ProfilePoint pvi2(500, 50);
         ProfilePoint pvi3(700, 80);
         ProfilePoint end(900, 50);

         auto vc1 = VerticalCurve::Create(start, pvi1, pvi2, 50, 50);
         profile->AddProfileElement(vc1);

         auto vc2 = VerticalCurve::Create(pvi1, pvi2, pvi3, 50, 50);
         profile->AddProfileElement(vc2);

         auto vc3 = VerticalCurve::Create(pvi2, pvi3, end, 50, 50);
         profile->AddProfileElement(vc3);

         Assert::IsTrue(IsEqual(profile->Elevation(250), 72.5));
         Assert::IsTrue(IsEqual(profile->Elevation(450), 57.5));
         Assert::IsTrue(IsEqual(profile->Elevation(650), 72.5));
      }

      TEST_METHOD(Test12)
      {
         // Same as Test2, except stations are defined using local station value and stationing zones (Test2 uses normalized values)
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         //
         // Test Elevation and Grade
         //
         // Alignment has station equations
         //
         // Station 4+00 back = 8+00 ahead
         // Station 12+00 back = 10+00 ahead
         alignment->AddStationEquation(400, 800);
         alignment->AddStationEquation(1200, 1000);

         //
         // Profile Point: Station 10+00,1 Elev 80.0 (6+00 normalized)
         // Vert Curve: BVC 11+00,1 Elev  85.0 (7+00 normalized)
         //             PVI 12+00,2 Elev 100.0 (10+00 normalized)
         //             EVC 15+00,2 Elev  91.0 (13+00 normalized)
         // Profile Point: Station 16+00,2 Elev 88.0 (14+00 normalized)
         auto seg1 = ProfileSegment::Create();
         seg1->Move(ProfilePoint(Station(1, 1000), 80), ProfilePoint(Station(1, 1100), 85));
         auto vc = VerticalCurve::Create();
         vc->Init(ProfilePoint(Station(1, 1100), 85), ProfilePoint(Station(2, 1200), 100), ProfilePoint(Station(2, 1500), 91), 300, 300);
         auto seg2 = ProfileSegment::Create();
         seg2->Move(ProfilePoint(Station(2, 1500), 91), ProfilePoint(Station(2, 1600), 88));
         profile->AddProfileElement(seg1);
         profile->AddProfileElement(vc);
         profile->AddProfileElement(seg2);

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);
         surface->SetSurfaceTemplateSegmentCount(4);

         auto template430 = surface->CreateSurfaceTemplate(430.0);
         template430->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template430->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template700 = surface->CreateSurfaceTemplate(Station(1, 1100)); // 11+00,1 = 7+00 normalized
         template700->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(1, 5.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(2, 5.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template700->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1000 = surface->CreateSurfaceTemplate(Station(2, 1200)); // 12+00,2 = 10+00 normalized
         template1000->UpdateSegmentParameters(0, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(1, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(2, 5.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1000->UpdateSegmentParameters(3, 20.0, -0.06, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1300 = surface->CreateSurfaceTemplate(Station(2, 1500)); // 15+00,2 = 13+00 normalized
         template1300->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1300->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template1600 = surface->CreateSurfaceTemplate(Station(1600));
         template1600->UpdateSegmentParameters(0, 20.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(1, 5.0, 0.04, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(2, 5.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1600->UpdateSegmentParameters(3, 20.0, -0.08, SurfaceTemplateSegment::SlopeType::Horizontal);

         Float64 Grades[] = { 5.0000, 5.0000, 4.2000, 2.06667, -0.06667, -2.2000, -3.0000, -3.0000 };
         TestGrade(*profile, Grades);

         Float64 CrownSlopes1[][2] = { { 0.0200, -0.0200}, { 0.0200, -0.0200}, { 0.0040, -0.0280}, { -0.03867, -0.04933}, { -0.03333,-0.06533}, { 0.0200, -0.07600}, { 0.0400, -0.0800}, { 0.0400, -0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes1);

         Float64 ElevA[] = { 71.900, 79.900, 87.860, 93.40666, 95.03333, 92.740, 88.000, 83.200 };
         Float64 ElevB[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         Float64 ElevC[] = { 72.040, 80.040, 87.816, 92.872, 94.504, 92.712, 88.160, 83.360 };
         Float64 ElevD[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevE[] = { 71.900, 79.900, 87.620, 92.52666, 94.04666, 92.180, 87.600, 82.800 };
         TestElevation(*profile, 0, -15, ElevA);
         TestElevation(*profile, 0, -5, ElevB);
         TestElevation(*profile, 0, -2, ElevC);
         TestElevation(*profile, 0, 0, ElevD);
         TestElevation(*profile, 0, 5, ElevE);

         // shift the crown point offset to +5
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevF[] = { 71.900, 79.900, 87.740, 92.96666, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevG[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevH[] = { 72.040, 80.040, 87.768, 92.696, 94.30666, 92.600, 88.080, 83.280 };
         Float64 ElevI[] = { 72.100, 80.100, 87.780, 92.580, 94.20666, 92.660, 88.200, 83.400 };
         Float64 ElevJ[] = { 71.900, 79.900, 87.500, 92.08666, 93.55333, 91.900, 87.400, 82.600 };
         TestElevation(*profile, 0, -5, ElevF);
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, 2, ElevH);
         TestElevation(*profile, 0, 5, ElevI);
         TestElevation(*profile, 0, 15, ElevJ);

         // shift the crown point offset back to -5 and reverse all of the segment template segment slopes
         surface->SetAlignmentPoint(3);
         surface->SetProfileGradePoint(3);

         auto& templates = surface->GetSurfaceTemplates();
         for (auto& surface_template : templates)
         {
            auto nSegments = surface_template->GetCount();
            for (auto i = 0; i < nSegments; i++)
            {
               auto& surface_template_segment = surface_template->GetSegment(i);
               auto slope = surface_template_segment.GetSlope();
               slope *= -1;
               surface_template_segment.SetSlope(slope);
            }
         }

         Float64 CrownSlopes2[][2] = { { -0.0200,  0.0200}, { -0.0200,  0.0200}, { -0.0040,  0.0280}, {  0.03867,  0.04933}, { 0.033333, 0.065333}, { -0.0200,  0.0760}, { -0.0400,  0.0800}, { -0.0400,  0.0800} };
         TestCrownSlopes(*profile, 0, 2, CrownSlopes2);

         Float64 ElevK[] = { 72.100, 80.100, 87.660, 92.140, 93.71333, 92.380, 88.000, 83.200 };
         Float64 ElevL[] = { 71.900, 79.900, 87.620, 92.52667, 94.04667, 92.180, 87.600, 82.800 };
         Float64 ElevM[] = { 71.960, 79.960, 87.704, 92.67467, 94.24267, 92.408, 87.840, 83.040 };
         Float64 ElevN[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevO[] = { 72.100, 80.100, 87.900, 93.020, 94.700, 92.940, 88.400, 83.600 };
         TestElevation(*profile, 0, -15, ElevK);
         TestElevation(*profile, 0, -5, ElevL);
         TestElevation(*profile, 0, -2, ElevM);
         TestElevation(*profile, 0, 0, ElevN);
         TestElevation(*profile, 0, 5, ElevO);

         // shift the crown point offset to +5, keep the slopes the same
         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);

         Float64 ElevP[] = { 72.100, 80.100, 87.780, 92.580, 94.20667, 92.660, 88.200, 83.400 };
         Float64 ElevQ[] = { 72.000, 80.000, 87.760, 92.77333, 94.37333, 92.560, 88.000, 83.200 };
         Float64 ElevR[] = { 71.960, 79.960, 87.752, 92.85067, 94.440, 92.520, 87.920, 83.120 };
         Float64 ElevS[] = { 71.900, 79.900, 87.740, 92.96667, 94.540, 92.460, 87.800, 83.000 };
         Float64 ElevT[] = { 72.100, 80.100, 88.020, 93.460, 95.19333, 93.220, 88.600, 83.800 };
         TestElevation(*profile, 0, -5, ElevP);
         TestElevation(*profile, 0, 0, ElevQ);
         TestElevation(*profile, 0, 2, ElevR);
         TestElevation(*profile, 0, 5, ElevS);
         TestElevation(*profile, 0, 15, ElevT);
      }

      TEST_METHOD(Test13)
      {
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         // Flat profile so we don't have to do anything

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(2);
         surface->SetProfileGradePoint(2);
         surface->SetSurfaceTemplateSegmentCount(4);

         auto template1 = surface->CreateSurfaceTemplate(0.0);
         template1->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1->UpdateSegmentParameters(1, 10.0, 0.01, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1->UpdateSegmentParameters(2, 10.0, -0.01, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template2 = surface->CreateSurfaceTemplate(2000.0);
         template2->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template2->UpdateSegmentParameters(1, 10.0, 0.01, SurfaceTemplateSegment::SlopeType::Horizontal);
         template2->UpdateSegmentParameters(2, 10.0, -0.01, SurfaceTemplateSegment::SlopeType::Horizontal);
         template2->UpdateSegmentParameters(3, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         // check basic elevations before widenings are applied
         Float64 ElevA[] = { 0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000 };
         Float64 ElevB[] = { -0.100, -0.100, -0.100, -0.100, -0.100, -0.100, -0.100, -0.100 };
         Float64 ElevC[] = { -0.500, -0.500, -0.500, -0.500, -0.500, -0.500, -0.500, -0.500 };
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -10, ElevB);
         TestElevation(*profile, 0, 10, ElevB);
         TestElevation(*profile, 0, -30, ElevC);
         TestElevation(*profile, 0, 30, ElevC);
         TestElevation(*profile, 0, -40, ElevC);
         TestElevation(*profile, 0, 40, ElevC);

         // Widen left edge
         auto widening = Widening::Create(500, 500, 1500, 1500, 10.0, 0, INVALID_INDEX);
         surface->AddWidening(widening);

         Float64 ElevD[] = { -0.500, -0.700, -0.700, -0.700, -0.700, -0.700, -0.700, -0.500 };
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -10, ElevB);
         TestElevation(*profile, 0, 10, ElevB);
         TestElevation(*profile, 0, -30, ElevC);
         TestElevation(*profile, 0, 30, ElevC);
         TestElevation(*profile, 0, -40, ElevD);
         TestElevation(*profile, 0, 40, ElevC);

         // Widen right edge
         widening->SetSegment(0, 3);
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -10, ElevB);
         TestElevation(*profile, 0, 10, ElevB);
         TestElevation(*profile, 0, -30, ElevC);
         TestElevation(*profile, 0, 30, ElevC);
         TestElevation(*profile, 0, -40, ElevC);
         TestElevation(*profile, 0, 40, ElevD);

         // Widen left and right in the middle of the section
         widening->SetSegment(0, 1);
         widening->SetSegment(1, 2);
         Float64 ElevE[] = { -0.500, -0.400, -0.400, -0.400, -0.400, -0.400, -0.400, -0.500 };
         Float64 ElevF[] = { -0.500, -0.600, -0.600, -0.600, -0.600, -0.600, -0.600, -0.500 };
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -10, ElevB);
         TestElevation(*profile, 0, 10, ElevB);
         TestElevation(*profile, 0, -30, ElevE);
         TestElevation(*profile, 0, 30, ElevE);
         TestElevation(*profile, 0, -60, ElevF);
         TestElevation(*profile, 0, 60, ElevF);

         // narrow left and right on the outside segments
         widening->SetSegment(0, 0);
         widening->SetSegment(1, 3);
         widening->SetWidening(-10.0);
         Float64 ElevG[] = { -0.500, -0.300, -0.300, -0.300, -0.300, -0.300, -0.300, -0.500 };
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -10, ElevB);
         TestElevation(*profile, 0, 10, ElevB);
         TestElevation(*profile, 0, -30, ElevG);
         TestElevation(*profile, 0, 30, ElevG);
         TestElevation(*profile, 0, -60, ElevG);
         TestElevation(*profile, 0, 60, ElevG);

         // Taper the transitions
         widening->SetBeginFullWidening(700.0);
         widening->SetEndFullWidening(1300.0);
         Float64 ElevH[] = { -0.500, -0.400, -0.300, -0.300, -0.300, -0.300, -0.400, -0.500 };
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -10, ElevB);
         TestElevation(*profile, 0, 10, ElevB);
         TestElevation(*profile, 0, -30, ElevH);
         TestElevation(*profile, 0, 30, ElevH);
         TestElevation(*profile, 0, -60, ElevH);
         TestElevation(*profile, 0, 60, ElevH);
      }

      TEST_METHOD(Test14)
      {
         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         // Flat profile so we don't have to do anything

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);
         surface->SetSurfaceTemplateSegmentCount(2);

         auto template1 = surface->CreateSurfaceTemplate(0.0);
         template1->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template2 = surface->CreateSurfaceTemplate(2000.0);
         template2->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template2->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         // check basic elevations before superelevations are applied
         Float64 ElevA[] = { 0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000 };
         Float64 ElevB[] = { -0.400, -0.400, -0.400, -0.400, -0.400, -0.400, -0.400, -0.400 };
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -20, ElevB);
         TestElevation(*profile, 0, 20, ElevB);

         // Superelevation (curve to the right - pivot on right edge)
         auto superelevation = Superelevation::Create(500, 700, 800, 1000, -0.06, 2, Superelevation::TransitionType::Linear, 0, 0, Superelevation::TransitionType::Linear, 0, 0);
         surface->AddSuperelevation(superelevation);

         Float64 ElevC[] = { 0.000,  0.400,  0.800,  0.320,  0.000,  0.000,  0.000,  0.000 };
         Float64 ElevD[] = { -0.400,  0.800,  2.000,  0.560, -0.400, -0.400, -0.400, -0.400 };
         TestElevation(*profile, 0, 0, ElevC);
         TestElevation(*profile, 0, -20, ElevD);
         TestElevation(*profile, 0, 20, ElevB); // pivot on right edge... elevations don't change

         // Pivot on CL
         superelevation->SetPivotPoint(1);

         Float64 ElevE[] = { -0.400,  0.400,  1.200,  0.240, -0.400, -0.400, -0.400, -0.400 };
         Float64 ElevF[] = { -0.400, -0.800, -1.200, -0.720, -0.400, -0.400, -0.400, -0.400 };
         TestElevation(*profile, 0, 0, ElevA); // pivot on CL... elevations don't change
         TestElevation(*profile, 0, -20, ElevE);
         TestElevation(*profile, 0, 20, ElevF);

         // Pivot on Left edge
         superelevation->SetPivotPoint(0);

         Float64 ElevG[] = { 0.000, -0.800, -1.600, -0.640,  0.000,  0.000,  0.000,  0.000 };
         Float64 ElevH[] = { -0.400, -1.600, -2.800, -1.360, -0.400, -0.400, -0.400, -0.400 };
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, -20, ElevB); // pivot on left edge... elevations don't change
         TestElevation(*profile, 0, 20, ElevH);

         // Curve to left... pivot on right edge
         superelevation->SetRate(0.06);
         superelevation->SetPivotPoint(2);
         TestElevation(*profile, 0, 0, ElevG);
         TestElevation(*profile, 0, -20, ElevH);
         TestElevation(*profile, 0, 20, ElevB); // pivot on right edge... elevations don't change

         // Pivot on CL
         superelevation->SetPivotPoint(1);

         TestElevation(*profile, 0, 0, ElevA); // pivot on CL... elevations don't change
         TestElevation(*profile, 0, -20, ElevF);
         TestElevation(*profile, 0, 20, ElevE);

         // Pivot on Left edge
         superelevation->SetPivotPoint(0);

         TestElevation(*profile, 0, 0, ElevC);
         TestElevation(*profile, 0, -20, ElevB); // pivot on left edge... elevations don't change
         TestElevation(*profile, 0, 20, ElevD);
      }

      TEST_METHOD(Test15)
      {
         // similar to Test14 - using parabolic transitions in superelevation

         auto alignment = Alignment::Create();
         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);

         // Flat profile so we don't have to do anything

         // create roadway surface model
         auto surface = Surface::Create();
         profile->AddSurface(0, surface);

         surface->SetAlignmentPoint(1);
         surface->SetProfileGradePoint(1);
         surface->SetSurfaceTemplateSegmentCount(2);

         auto template1 = surface->CreateSurfaceTemplate(0.0);
         template1->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template1->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto template2 = surface->CreateSurfaceTemplate(2000.0);
         template2->UpdateSegmentParameters(0, 20.0, 0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         template2->UpdateSegmentParameters(1, 20.0, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         // check basic elevations before superelevations are applied
         Float64 ElevA[] = { 0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000 };
         Float64 ElevB[] = { -0.400, -0.400, -0.400, -0.400, -0.400, -0.400, -0.400, -0.400 };
         TestElevation(*profile, 0, 0, ElevA);
         TestElevation(*profile, 0, -20, ElevB);
         TestElevation(*profile, 0, 20, ElevB);

         // Superelevation (curve to the right - pivot on right edge)
         auto superelevation = Superelevation::Create(500, 700, 800, 1000, -0.06, 2, Superelevation::TransitionType::Parabolic, 50, 50, Superelevation::TransitionType::Parabolic, 50, 50);
         surface->AddSuperelevation(superelevation);

         //                   4+25    5+25     6+26      7+25    8+25      9+25      10+25
         Float64 ElevC[] = { 0.000,  0.03333,  0.53333,  0.800,  0.76667,  0.26667,  0.000 };
         Float64 ElevD[] = { -0.400, -0.300,   1.200,    2.000,  1.900,    0.400,   -0.400 };
         TestElevation(*profile, 0, 0, ElevC, 425, 1025, 100);
         TestElevation(*profile, 0, -20, ElevD, 425, 1025, 100);
         TestElevation(*profile, 0, 20, ElevB, 425, 1025, 100); // pivot on right edge... elevations don't change

         // Parabolic transition with zero length parabolas
         superelevation->SetBeginTransitionParameters(0.0, 0.0);
         superelevation->SetEndTransitionParameters(0.0, 0.0);
         Float64 ElevE[] = { 0.000,  0.400,  0.800,  0.320,  0.000,  0.000,  0.000,  0.000 };
         Float64 ElevF[] = { -0.400,  0.800,  2.000,  0.560, -0.400, -0.400, -0.400, -0.400 };
         TestElevation(*profile, 0, 0, ElevE);
         TestElevation(*profile, 0, -20, ElevF);
         TestElevation(*profile, 0, 20, ElevB); // pivot on right edge... elevations don't change

         // Parabolic transition without the linear portion
         // L1 = 100, L2 = 100 (L3 = 0)
         superelevation->SetBeginTransitionParameters(100.0, 100.0);
         superelevation->SetEndTransitionParameters(100.0, 100.0);
         Float64 ElevG[] = { 0.000,  0.025,  0.575,  0.800,  0.775,  0.225,  0.000,  0.000 };
         Float64 ElevH[] = { -0.400, -0.325,  1.325,  2.000,  1.925,  0.275, -0.400, -0.400 };
         TestElevation(*profile, 0, 0, ElevG, 425, 1025, 100);
         TestElevation(*profile, 0, -20, ElevH, 425, 1025, 100);
         TestElevation(*profile, 0, 20, ElevB, 425, 1025, 100); // pivot on right edge... elevations don't change

         // Also test case where L3 < 0 (L1+L2 is too big for transition)
         superelevation->SetBeginTransitionParameters(150.0, 150.0);
         try { profile->Elevation(525, 0, 0.0); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_SUPERTRANSITIONERROR); }
      }

      TEST_METHOD(Test16)
      {
         Station refStation(2336.53);

         auto alignment = Alignment::Create();
         auto pbt = WBFL::Geometry::Point2d(2451859.110, 1005078.896);
         Direction bkTangent(_T("N 02 06 34 E"));
         auto pi = COGO::LocateByDistanceAndDirection(pbt, (2587.80 - refStation.GetValue()), bkTangent, 0.0);
         Direction fwdTangent = bkTangent - Angle(_T("10 01 30 R"));
         auto pft = COGO::LocateByDistanceAndDirection(pi, 5000.0, fwdTangent, 0.0);
         auto curve = CircularCurve::Create(pbt, pi, pft, 2864.79);
         auto pc = curve->GetPC();
         auto back_tangent_segment = PathSegment::Create(pbt, pc);

         alignment->AddPathElement(back_tangent_segment);
         alignment->AddPathElement(curve);
         alignment->SetReferenceStation(refStation);

         auto profile = Profile::Create();
         alignment->AddProfile(0, profile);
         auto vc1 = VerticalCurve::Create(ProfilePoint(2000.61, 289.97), ProfilePoint(2255.97, 293.16), 1.97585 / 100, 0.5187 / 100);
         profile->AddProfileElement(vc1);
         auto vc2 = VerticalCurve::Create(ProfilePoint(2749.94, 295.72), ProfilePoint(2997.77, 297.01), ProfilePoint(3245.63, 295.74), 495.73 / 2, 495.73 / 2);
         profile->AddProfileElement(vc2);

         auto surface = Surface::Create(2, 2, 1); // 2 segments, alignment at ridge point 2, profile at ridge point 1
         profile->AddSurface(0, surface);
         auto surface_template = surface->CreateSurfaceTemplate(refStation);
         surface_template->UpdateSegmentParameters(0, 36, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
         surface_template->UpdateSegmentParameters(1, 16, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

         auto superelevation = Superelevation::Create(2198, 2300, 2770, 2872, -0.04, 1); // pivot at ridge point 1 (at PGL)
         surface->AddSuperelevation(superelevation);

         std::vector<std::tuple<Float64, Float64, Float64, Float64>> vResults1{
            {2000.61000, 290.69000, 289.97000, 289.65000},
            { 2025.51040, 291.16440, 290.44440, 290.12440 },
            { 2050.41080, 291.60360, 290.88360, 290.56360 },
            { 2075.31120, 292.00762, 291.28762, 290.96762 },
            { 2100.21160, 292.37644, 291.65644, 291.33644 },
            { 2125.11200, 292.71007, 291.99007, 291.67007 },
            { 2150.01240, 293.00836, 292.28836, 291.96836 },
            { 2174.91280, 293.27110, 292.55110, 292.23110 },
            { 2199.81320, 293.51106, 292.77826, 292.45257 },
            { 2224.71360, 293.87842, 292.96985, 292.56604 },
            { 2249.61400, 294.21021, 293.12587, 292.64395 },
            { 2274.51440, 294.51621, 293.25611, 292.69606 },
            { 2299.41480, 294.82102, 293.38515, 292.74699 },
            { 2324.31520, 294.95420, 293.51420, 292.87420 },
            { 2349.21560, 295.08325, 293.64325, 293.00325 },
            { 2374.11600, 295.21229, 293.77229, 293.13229 },
            { 2399.01640, 295.34134, 293.90134, 293.26134 },
            { 2423.91680, 295.47038, 294.03038, 293.39038 },
            { 2448.81720, 295.59943, 294.15943, 293.51943 },
            { 2473.71760, 295.72848, 294.28848, 293.64848 },
            { 2498.61800, 295.85752, 294.41752, 293.77752 },
            { 2523.51840, 295.98657, 294.54657, 293.90657 },
            { 2548.41880, 296.11562, 294.67562, 294.03562 },
            { 2573.31920, 296.24466, 294.80466, 294.16466 },
            { 2598.21960, 296.37371, 294.93371, 294.29371 },
            { 2623.12000, 296.50275, 295.06275, 294.42275 },
            { 2648.02040, 296.63180, 295.19180, 294.55180 },
            { 2672.92080, 296.76085, 295.32085, 294.68085 },
            { 2697.82120, 296.88989, 295.44989, 294.80989 },
            { 2722.72160, 297.01894, 295.57894, 294.93894 },
            { 2747.62200, 297.14799, 295.70799, 295.06799 },
            { 2772.52240, 297.25441, 295.83222, 295.20013 },
            { 2797.42280, 297.19006, 295.94363, 295.38967 },
            { 2822.32320, 297.11279, 296.04213, 295.56628 },
            { 2847.22360, 297.02260, 296.12771, 295.72998 },
            { 2872.12400, 296.92037, 296.20037, 295.88037 },
            { 2897.02440, 296.98011, 296.26011, 295.94011 },
            { 2921.92480, 297.02693, 296.30693, 295.98693 },
            { 2946.82520, 297.06084, 296.34084, 296.02084 },
            { 2971.72560, 297.08182, 296.36182, 296.04182 },
            { 2996.62600, 297.08989, 296.36989, 296.04989 },
            { 3021.52640, 297.08503, 296.36503, 296.04503 },
            { 3046.42680, 297.06726, 296.34726, 296.02726 },
            { 3071.32720, 297.03657, 296.31657, 295.99657 },
            { 3096.22760, 296.99296, 296.27296, 295.95296 },
            { 3121.12800, 296.93643, 296.21643, 295.89643 },
            { 3146.02840, 296.86698, 296.14698, 295.82698 },
            { 3170.92880, 296.78462, 296.06462, 295.74462 },
            { 3195.82920, 296.68933, 295.96933, 295.64933 },
            { 3220.72960, 296.58112, 295.86112, 295.54112 }
         };

         for (int i = 0; i < 50; i++)
         {
            Station station(2000.61 + i * (3245.63 - 2000.61) / 50);
            auto elevL = profile->Elevation(surface, station, -52); // 52 ft left of alignment
            auto elevP = profile->Elevation(surface, station, -16); // 16 ft left of alignment
            auto elevR = profile->Elevation(surface, station, 0); // on the alignment

            Assert::IsTrue(station == std::get<0>(vResults1[i]));
            Assert::IsTrue(IsEqual(std::get<1>(vResults1[i]), elevL));
            Assert::IsTrue(IsEqual(std::get<2>(vResults1[i]), elevP));
            Assert::IsTrue(IsEqual(std::get<3>(vResults1[i]), elevR));
         }

         superelevation->SetPivotPoint(0); // pivot about left curb line
         std::vector<std::tuple<Float64, Float64, Float64, Float64>> vResults2{
            {2000.61000, 290.69000, 289.97000, 289.65000},
            { 2025.51040, 291.16440, 290.44440, 290.12440 },
            { 2050.41080, 291.60360, 290.88360, 290.56360 },
            { 2075.31120, 292.00762, 291.28762, 290.96762 },
            { 2100.21160, 292.37644, 291.65644, 291.33644 },
            { 2125.11200, 292.71007, 291.99007, 291.67007 },
            { 2150.01240, 293.00836, 292.28836, 291.96836 },
            { 2174.91280, 293.27110, 292.55110, 292.23110 },
            { 2199.81320, 293.49826, 292.76546, 292.43977 },
            { 2224.71360, 293.68985, 292.78128, 292.37748 },
            { 2249.61400, 293.84587, 292.76154, 292.27961 },
            { 2274.51440, 293.97611, 292.71600, 292.15596 },
            { 2299.41480, 294.10515, 292.66928, 292.03112 },
            { 2324.31520, 294.23420, 292.79420, 292.15420 },
            { 2349.21560, 294.36325, 292.92325, 292.28325 },
            { 2374.11600, 294.49229, 293.05229, 292.41229 },
            { 2399.01640, 294.62134, 293.18134, 292.54134 },
            { 2423.91680, 294.75038, 293.31038, 292.67038 },
            { 2448.81720, 294.87943, 293.43943, 292.79943 },
            { 2473.71760, 295.00848, 293.56848, 292.92848 },
            { 2498.61800, 295.13752, 293.69752, 293.05752 },
            { 2523.51840, 295.26657, 293.82657, 293.18657 },
            { 2548.41880, 295.39562, 293.95562, 293.31562 },
            { 2573.31920, 295.52466, 294.08466, 293.44466 },
            { 2598.21960, 295.65371, 294.21371, 293.57371 },
            { 2623.12000, 295.78275, 294.34275, 293.70275 },
            { 2648.02040, 295.91180, 294.47180, 293.83180 },
            { 2672.92080, 296.04085, 294.60085, 293.96085 },
            { 2697.82120, 296.16989, 294.72989, 294.08989 },
            { 2722.72160, 296.29894, 294.85894, 294.21894 },
            { 2747.62200, 296.42799, 294.98799, 294.34799 },
            { 2772.52240, 296.55222, 295.13002, 294.49793 },
            { 2797.42280, 296.66363, 295.41721, 294.86324 },
            { 2822.32320, 296.76213, 295.69147, 295.21562 },
            { 2847.22360, 296.84771, 295.95282, 295.55509 },
            { 2872.12400, 296.92037, 296.20037, 295.88037 },
            { 2897.02440, 296.98011, 296.26011, 295.94011 },
            { 2921.92480, 297.02693, 296.30693, 295.98693 },
            { 2946.82520, 297.06084, 296.34084, 296.02084 },
            { 2971.72560, 297.08182, 296.36182, 296.04182 },
            { 2996.62600, 297.08989, 296.36989, 296.04989 },
            { 3021.52640, 297.08503, 296.36503, 296.04503 },
            { 3046.42680, 297.06726, 296.34726, 296.02726 },
            { 3071.32720, 297.03657, 296.31657, 295.99657 },
            { 3096.22760, 296.99296, 296.27296, 295.95296 },
            { 3121.12800, 296.93643, 296.21643, 295.89643 },
            { 3146.02840, 296.86698, 296.14698, 295.82698 },
            { 3170.92880, 296.78462, 296.06462, 295.74462 },
            { 3195.82920, 296.68933, 295.96933, 295.64933 },
            { 3220.72960, 296.58112, 295.86112, 295.54112 }
         };

         for (int i = 0; i < 50; i++)
         {
            Station station(2000.61 + i * (3245.63 - 2000.61) / 50);
            auto elevL = profile->Elevation(surface, station, -52); // 52 ft left of alignment
            auto elevP = profile->Elevation(surface, station, -16); // 16 ft left of alignment
            auto elevR = profile->Elevation(surface, station, 0); // on the alignment

            Assert::IsTrue(station == std::get<0>(vResults2[i]));
            Assert::IsTrue(IsEqual(std::get<1>(vResults2[i]), elevL));
            Assert::IsTrue(IsEqual(std::get<2>(vResults2[i]), elevP));
            Assert::IsTrue(IsEqual(std::get<3>(vResults2[i]), elevR));
         }


         superelevation->SetPivotPoint(2); // pivot about right curb line
         std::vector<std::tuple<Float64, Float64, Float64, Float64>> vResults3{
            {2000.61000, 290.69000, 289.97000, 289.65000},
            { 2025.51040, 291.16440, 290.44440, 290.12440 },
            { 2050.41080, 291.60360, 290.88360, 290.56360 },
            { 2075.31120, 292.00762, 291.28762, 290.96762 },
            { 2100.21160, 292.37644, 291.65644, 291.33644 },
            { 2125.11200, 292.71007, 291.99007, 291.67007 },
            { 2150.01240, 293.00836, 292.28836, 291.96836 },
            { 2174.91280, 293.27110, 292.55110, 292.23110 },
            { 2199.81320, 293.51675, 292.78395, 292.45826 },
            { 2224.71360, 293.96222, 293.05366, 292.64985 },
            { 2249.61400, 294.37213, 293.28780, 292.80587 },
            { 2274.51440, 294.75625, 293.49615, 292.93611 },
            { 2299.41480, 295.13919, 293.70332, 293.06515 },
            { 2324.31520, 295.27420, 293.83420, 293.19420 },
            { 2349.21560, 295.40325, 293.96325, 293.32325 },
            { 2374.11600, 295.53229, 294.09229, 293.45229 },
            { 2399.01640, 295.66134, 294.22134, 293.58134 },
            { 2423.91680, 295.79038, 294.35038, 293.71038 },
            { 2448.81720, 295.91943, 294.47943, 293.83943 },
            { 2473.71760, 296.04848, 294.60848, 293.96848 },
            { 2498.61800, 296.17752, 294.73752, 294.09752 },
            { 2523.51840, 296.30657, 294.86657, 294.22657 },
            { 2548.41880, 296.43562, 294.99562, 294.35562 },
            { 2573.31920, 296.56466, 295.12466, 294.48466 },
            { 2598.21960, 296.69371, 295.25371, 294.61371 },
            { 2623.12000, 296.82275, 295.38275, 294.74275 },
            { 2648.02040, 296.95180, 295.51180, 294.87180 },
            { 2672.92080, 297.08085, 295.64085, 295.00085 },
            { 2697.82120, 297.20989, 295.76989, 295.12989 },
            { 2722.72160, 297.33894, 295.89894, 295.25894 },
            { 2747.62200, 297.46799, 296.02799, 295.38799 },
            { 2772.52240, 297.56650, 296.14430, 295.51222 },
            { 2797.42280, 297.42403, 296.17760, 295.62363 },
            { 2822.32320, 297.26864, 296.19798, 295.72213 },
            { 2847.22360, 297.10033, 296.20544, 295.80771 },
            { 2872.12400, 296.92037, 296.20037, 295.88037 },
            { 2897.02440, 296.98011, 296.26011, 295.94011 },
            { 2921.92480, 297.02693, 296.30693, 295.98693 },
            { 2946.82520, 297.06084, 296.34084, 296.02084 },
            { 2971.72560, 297.08182, 296.36182, 296.04182 },
            { 2996.62600, 297.08989, 296.36989, 296.04989 },
            { 3021.52640, 297.08503, 296.36503, 296.04503 },
            { 3046.42680, 297.06726, 296.34726, 296.02726 },
            { 3071.32720, 297.03657, 296.31657, 295.99657 },
            { 3096.22760, 296.99296, 296.27296, 295.95296 },
            { 3121.12800, 296.93643, 296.21643, 295.89643 },
            { 3146.02840, 296.86698, 296.14698, 295.82698 },
            { 3170.92880, 296.78462, 296.06462, 295.74462 },
            { 3195.82920, 296.68933, 295.96933, 295.64933 },
            { 3220.72960, 296.58112, 295.86112, 295.54112 }
         };


         for (int i = 0; i < 50; i++)
         {
            Station station(2000.61 + i * (3245.63 - 2000.61) / 50);
            auto elevL = profile->Elevation(surface, station, -52); // 52 ft left of alignment
            auto elevP = profile->Elevation(surface, station, -16); // 16 ft left of alignment
            auto elevR = profile->Elevation(surface, station, 0); // on the alignment

            Assert::IsTrue(station == std::get<0>(vResults3[i]));
            Assert::IsTrue(IsEqual(std::get<1>(vResults3[i]), elevL));
            Assert::IsTrue(IsEqual(std::get<2>(vResults3[i]), elevP));
            Assert::IsTrue(IsEqual(std::get<3>(vResults3[i]), elevR));
         }
      }
   };
}
