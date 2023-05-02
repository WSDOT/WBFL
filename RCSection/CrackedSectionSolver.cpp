///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <RCSection\RCSectionLib.h>
#include <RCSection\CrackedSectionSolver.h>
#include "CrackedSectionSolverImpl.h"

using namespace WBFL::RCSection;

CrackedSectionSolver::CrackedSectionSolver()
{
   m_pImpl = std::make_unique<CrackedSectionSolverImpl>();
}

CrackedSectionSolver::~CrackedSectionSolver() = default;

void CrackedSectionSolver::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_pImpl->SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& CrackedSectionSolver::GetSection() const
{
   return m_pImpl->GetSection();
}

void CrackedSectionSolver::SetSlices(IndexType nSlices)
{
   m_pImpl->SetSlices(nSlices);
}

IndexType CrackedSectionSolver::GetSlices() const
{
   return m_pImpl->GetSlices();
}

void CrackedSectionSolver::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_pImpl->SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 CrackedSectionSolver::GetSliceGrowthFactor() const
{
   return m_pImpl->GetSliceGrowthFactor();
}

void CrackedSectionSolver::SetTolerance(Float64 tolerance)
{
   m_pImpl->SetTolerance(tolerance);
}

Float64 CrackedSectionSolver::GetTolerance() const
{
   return m_pImpl->GetTolerance();
}

void CrackedSectionSolver::SetMaxIterations(IndexType maxIter)
{
   m_pImpl->SetMaxIterations(maxIter);
}

IndexType CrackedSectionSolver::GetMaxIterations() const
{
   return m_pImpl->GetMaxIterations();
}

std::unique_ptr<CrackedSectionSolution> CrackedSectionSolver::Solve(Float64 naAngle) const
{
   return m_pImpl->Solve(naAngle);
}

#if defined _UNITTEST
#include <Units/Units.h>
#include <Materials/Materials.h>
#include <GeomModel/GeomModel.h>
bool CrackedSectionSolver::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CrackedSectionSolver");

   TRY_TESTME(TestRectangularBeam(rlog));
   TRY_TESTME(TestTeeBeam1(rlog));
   TRY_TESTME(TestTeeBeam2(rlog));
   TRY_TESTME(TestTeeBeam3(rlog));


   TESTME_EPILOG("CrackedSectionSolver");
}

bool CrackedSectionSolver::TestRectangularBeam(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CrackedSectionSolver::TestRectangularBeam");

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
   TRY_TESTME(IsEqual(pntCG.X(), 0.0));
   TRY_TESTME(IsEqual(pntCG.Y(), 81.755394));

   auto props = solution->GetElasticProperties();
   TRY_TESTME(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

   TRY_TESTME(IsEqual(props.GetEA(), 1435324.2471274068));
   TRY_TESTME(IsEqual(props.GetEIxx(), 1080016839.2639580));

   TESTME_EPILOG("CrackedSectionSolver::TestRectangularBeam");
}

bool CrackedSectionSolver::TestTeeBeam1(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CrackedSectionSolver::TestTeeBeam1");

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
   TRY_TESTME(IsEqual(pntCG.X(), 0.0));
   TRY_TESTME(IsEqual(pntCG.Y(), 101.425427));

   auto props = solution->GetElasticProperties();
   TRY_TESTME(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

   TRY_TESTME(IsEqual(props.GetEA(), 1150707.9739471173));
   TRY_TESTME(IsEqual(props.GetEIxx(), 380133591.91453171));

   TESTME_EPILOG("CrackedSectionSolver::TestTeeBeam1");
}

bool CrackedSectionSolver::TestTeeBeam2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CrackedSectionSolver::TestTeeBeam2");

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
   Float64 radius = sqrt(100*1.27 / M_PI);
   WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(0, 2), radius);

   CrackedSectionSolver solver;
   solver.SetSlices(10);
   //solver.SetSliceGrowthFactor(3);
   solver.SetTolerance(0.001);
   solver.SetSection(section);

   auto solution = solver.Solve(0.0);

   const auto& pntCG = solution->GetCentroid();
   TRY_TESTME(IsEqual(pntCG.X(), 0.0));
   TRY_TESTME(IsEqual(pntCG.Y(), 52.15599));

   auto props = solution->GetElasticProperties();
   TRY_TESTME(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

   TRY_TESTME(IsEqual(props.GetEA(), 9822852.5720759369));
   TRY_TESTME(IsEqual(props.GetEIxx(), 16603253157.345383));

   TESTME_EPILOG("CrackedSectionSolver::TestTeeBeam2");
}

bool CrackedSectionSolver::TestTeeBeam3(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CrackedSectionSolver::TestTeeBeam3");

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
   WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(0, Y-2), radius);

   CrackedSectionSolver solver;
   solver.SetSlices(10);
   //solver.SetSliceGrowthFactor(3);
   solver.SetTolerance(0.001);
   solver.SetSection(section);

   auto solution = solver.Solve(0.0);

   const auto& pntCG = solution->GetCentroid();
   TRY_TESTME(IsEqual(pntCG.X(), 0.0));
   TRY_TESTME(IsEqual(pntCG.Y(), -11.781458));

   auto props = solution->GetElasticProperties();
   TRY_TESTME(IsEqual(pntCG.Y(), props.GetCentroid().Y()));

   TRY_TESTME(IsEqual(props.GetEA(), 1251805.8138490969));
   TRY_TESTME(IsEqual(props.GetEIxx(), 708414513.80776465));

   TESTME_EPILOG("CrackedSectionSolver::TestTeeBeam3");
}

#endif // _UNITTEST
