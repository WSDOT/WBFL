#include "pch.h"
#include "CppUnitTest.h"
#include <GeomModel/GeomModel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestCrackedSectionSolver)
	{
	public:
		
		TEST_METHOD(TestRectangularBeam)
		{
         // work in KSI units
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         // Get a general section
         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

         //
         // materials
         //

         // concrete
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

         // rebar
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

         //
         // shapes
         //

         // main beam
         Float64 H = 100;
         Float64 W = 20;
         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(H);
         beam.SetWidth(W);
         
         // move bottom center of beam to (0,0)
         beam.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::BottomCenter, WBFL::Geometry::Point2d(0, 0));

         // 4 - #10 rebar @ 2" from bottom
         Float64 radius = sqrt(1.27 / M_PI);
         WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(0, 2), radius);
         WBFL::Geometry::Circle bar2(WBFL::Geometry::Point2d(0, 2), radius);
         WBFL::Geometry::Circle bar3(WBFL::Geometry::Point2d(0, 2), radius);
         WBFL::Geometry::Circle bar4(WBFL::Geometry::Point2d(0, 2), radius);

         section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);
         section->AddShape(_T("Bar 1"), bar1, rebar, nullptr, nullptr, 1.0);
         section->AddShape(_T("Bar 2"), bar2, rebar, nullptr, nullptr, 1.0);
         section->AddShape(_T("Bar 3"), bar3, rebar, nullptr, nullptr, 1.0);
         section->AddShape(_T("Bar 4"), bar4, rebar, nullptr, nullptr, 1.0);

         CrackedSectionSolver solver;
         solver.SetSlices(10);
         solver.SetSliceGrowthFactor(3);
         solver.SetTolerance(0.001);
         solver.SetSection(section);

         auto solution = solver.Solve(0.0);

         const auto& pntCG = solution->GetCentroid();
         Assert::IsTrue(IsEqual(pntCG.X(), 0.0));
         Assert::IsTrue(IsEqual(pntCG.Y(), 81.755394));

         auto props = solution->GetElasticProperties();
         Assert::IsTrue(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

         Assert::IsTrue(IsEqual(props.GetEA(), 1435324.2471274068));
         Assert::IsTrue(IsEqual(props.GetEIxx(), 1080016839.2639580));
      }

		TEST_METHOD(TestTeeBeam1)
		{
         // work in KSI units
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);


         // Get a general section
         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

         //
         // materials
         //

         // concrete
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> slab_concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Slab"), 4.0));
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> beam_concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Beam"), 10.0));

         // rebar
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));


         //
         // shapes
         //

         // slab
         Float64 Wtf = 48;
         Float64 Ttf = 8;
         WBFL::Geometry::Rectangle slab;
         slab.SetHeight(Ttf);
         slab.SetWidth(Wtf);

         // main beam
         Float64 H = 100;
         Float64 W = 20;
         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(H);
         beam.SetWidth(W);
         
         // move bottom center of beam to (0,0)
         beam.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::BottomCenter, WBFL::Geometry::Point2d(0, 0));

         // move bottom center of slab to top center of beam
         slab.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::BottomCenter, beam.GetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::TopCenter));

         // #10 rebar @ 2" from bottom
         Float64 radius = sqrt(1.27 / M_PI);
         WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(0, 2), radius);

         section->AddShape(_T("Slab"), slab, slab_concrete, nullptr, nullptr, 1.0);
         section->AddShape(_T("Beam"), beam, beam_concrete, nullptr, nullptr, 1.0, true);
         section->AddShape(_T("Bar 1"), bar1, rebar, nullptr, nullptr, 1.0);

         CrackedSectionSolver solver;
         solver.SetSlices(10);
         //solver.SetSliceGrowthFactor(3);
         solver.SetTolerance(0.001);
         solver.SetSection(section);

         auto solution = solver.Solve(0.0);

         const auto& pntCG = solution->GetCentroid();
         Assert::IsTrue(IsEqual(pntCG.X(), 0.0));
         Assert::IsTrue(IsEqual(pntCG.Y(), 101.42542686661658));

         auto props = solution->GetElasticProperties();
         Assert::IsTrue(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

         Assert::IsTrue(IsEqual(props.GetEA(), 1150707.9739471427));
         Assert::IsTrue(IsEqual(props.GetEIxx(), 380133591.91452026));
      }
		
      TEST_METHOD(TestTeeBeam2)
		{
         // work in KSI units
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);


         // Get a general section
         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

         //
         // materials
         //

         // concrete
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> slab_concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Slab"), 4.0));
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> beam_concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Beam"), 10.0));

         // rebar
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));


         //
         // shapes
         //

         // slab
         Float64 Wtf = 48;
         Float64 Ttf = 8;
         WBFL::Geometry::Rectangle slab;
         slab.SetHeight(Ttf);
         slab.SetWidth(Wtf);

         // main beam
         Float64 H = 100;
         Float64 W = 20;
         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(H);
         beam.SetWidth(W);

         // move bottom center of beam to (0,0)
         beam.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::BottomCenter, WBFL::Geometry::Point2d(0, 0));

         // move bottom center of slab to top center of beam
         slab.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::BottomCenter, beam.GetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::TopCenter));

         // 100 - #10 rebar @ 2" from bottom
         Float64 radius = sqrt(100 * 1.27 / M_PI);
         WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(0, 2), radius);

         section->AddShape(_T("Slab"), slab, slab_concrete, nullptr, nullptr, 1.0);
         section->AddShape(_T("Beam"), beam, beam_concrete, nullptr, nullptr, 1.0, true);
         section->AddShape(_T("Bar 1"), bar1, rebar, nullptr, nullptr, 1.0);

         CrackedSectionSolver solver;
         solver.SetSlices(10);
         //solver.SetSliceGrowthFactor(3);
         solver.SetTolerance(0.001);
         solver.SetSection(section);

         auto solution = solver.Solve(0.0);

         const auto& pntCG = solution->GetCentroid();
         Assert::IsTrue(IsEqual(pntCG.X(), 0.0));
         Assert::IsTrue(IsEqual(pntCG.Y(), 52.155990490558963));

         auto props = solution->GetElasticProperties();
         Assert::IsTrue(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

         Assert::IsTrue(IsEqual(props.GetEA(), 9822852.5720759388));
         Assert::IsTrue(IsEqual(props.GetEIxx(), 16603253157.345387));
      }

		TEST_METHOD(TestTeeBeam3)
		{
         // work in KSI units
         WBFL::Units::AutoSystem as;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);


         // Get a general section
         std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

         //
         // materials
         //

         // concrete
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> slab_concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Slab"), 4.0));
         std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> beam_concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Beam"), 10.0));

         // rebar
         std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));


         //
         // shapes
         //

         // slab
         Float64 Wtf = 48;
         Float64 Ttf = 8;
         WBFL::Geometry::Rectangle slab;
         slab.SetHeight(Ttf);
         slab.SetWidth(Wtf);

         // main beam
         Float64 H = 100;
         Float64 W = 20;
         WBFL::Geometry::Rectangle beam;
         beam.SetHeight(H);
         beam.SetWidth(W);

         // move bottom center of beam to (0,0)
         beam.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::BottomCenter, WBFL::Geometry::Point2d(0, 0));

         // move bottom center of slab to top center of beam
         slab.SetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::BottomCenter, beam.GetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::TopCenter));

         // 2 - #10 rebar @ 2" from top
         Float64 radius = sqrt(2 * 1.27 / M_PI);
         Float64 Y = slab.GetLocatorPoint(WBFL::Geometry::Shape::LocatorPoint::TopCenter).Y();
         WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(0, Y - 2), radius);

         section->AddShape(_T("Slab"), slab, slab_concrete, nullptr, nullptr, 1.0);
         section->AddShape(_T("Beam"), beam, beam_concrete, nullptr, nullptr, 1.0, true);
         section->AddShape(_T("Bar 1"), bar1, rebar, nullptr, nullptr, 1.0);

         CrackedSectionSolver solver;
         solver.SetSlices(10);
         //solver.SetSliceGrowthFactor(3);
         solver.SetTolerance(0.001);
         solver.SetSection(section);

         auto solution = solver.Solve(0.0);

         auto pntCG = solution->GetCentroid();
         Assert::IsTrue(IsEqual(pntCG.X(), 0.0));
         Assert::IsTrue(IsEqual(pntCG.Y(), 107.04622433399285));

         auto props = solution->GetElasticProperties();
         Assert::IsTrue(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

         Assert::IsTrue(IsEqual(props.GetEA(), 235238.51006959871));
         Assert::IsTrue(IsEqual(props.GetEIxx(), 144517.55768585205));
      }
	};
}
