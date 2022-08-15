///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <RCSection\GeneralSectionSolver.h>
#include "GeneralSectionSolverImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::RCSection;

GeneralSectionSolver::GeneralSectionSolver()
{
   m_pImpl = std::make_unique<GeneralSectionSolverImpl>();
}

GeneralSectionSolver::~GeneralSectionSolver() = default;

void GeneralSectionSolver::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_pImpl->SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& GeneralSectionSolver::GetSection() const
{
   return m_pImpl->GetSection();
}

void GeneralSectionSolver::SetSlices(IndexType nSlices)
{
   m_pImpl->SetSlices(nSlices);
}

IndexType GeneralSectionSolver::GetSlices() const
{
   return m_pImpl->GetSlices();
}

void GeneralSectionSolver::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_pImpl->SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 GeneralSectionSolver::GetSliceGrowthFactor() const
{
   return m_pImpl->GetSliceGrowthFactor();
}

std::unique_ptr<GeneralSectionSolution> GeneralSectionSolver::Solve(const WBFL::Geometry::Plane3d& incrementalStrainPlane) const
{
   return m_pImpl->Solve(incrementalStrainPlane);
}

#if defined _UNITTEST
#include <Units/Units.h>
#include <Materials/Materials.h>
#include <GeomModel/GeomModel.h>
bool GeneralSectionSolver::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("GeneralSectionSolver");

   // work in KSI units
   WBFL::Units::AutoSystem as;
   WBFL::Units::System::SetBaseUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

   std::shared_ptr<GeneralSection> section(std::make_shared<GeneralSection>());

   // Materials

   // concrete
   std::shared_ptr<WBFL::Materials::UnconfinedConcreteModel> concrete(std::make_shared<WBFL::Materials::UnconfinedConcreteModel>(_T("Concrete"), 4.0));

   // rebar
   std::shared_ptr<WBFL::Materials::RebarModel> rebar(std::make_shared<WBFL::Materials::RebarModel>(_T("Rebar"), 60.0, 29000.0, 0.11));

   // Shapes

   // main beam
   WBFL::Geometry::Rectangle beam;
   beam.SetHeight(8 * 12);
   beam.SetWidth(4 * 12);

   // #6 rebar
   WBFL::Geometry::Circle bar1(WBFL::Geometry::Point2d(22, 46), 0.37424);
   WBFL::Geometry::Circle bar2(WBFL::Geometry::Point2d(-22, 46), 0.37424);
   WBFL::Geometry::Circle bar3(WBFL::Geometry::Point2d(-22, -46), 0.37424);
   WBFL::Geometry::Circle bar4(WBFL::Geometry::Point2d(22, -46), 0.37424);

   section->AddShape(_T("Beam"), beam, concrete, nullptr, nullptr, 1.0, true);
   section->AddShape(_T("Bar 1"), bar1, rebar, concrete, nullptr, 1.0);
   section->AddShape(_T("Bar 2"), bar2, rebar, concrete, nullptr, 1.0);
   section->AddShape(_T("Bar 3"), bar3, rebar, concrete, nullptr, 1.0);
   section->AddShape(_T("Bar 4"), bar4, rebar, concrete, nullptr, 1.0);

   WBFL::Geometry::Point3d p1(-1000, 0, 0); // neutral axis
   WBFL::Geometry::Point3d p2(1000, 0, 0); // neutral axis
   WBFL::Geometry::Point3d p3(0, 48, -0.003); // -0.003 at top face of beam

   WBFL::Geometry::Plane3d strainPlane(p1, p2, p3);

   GeneralSectionSolver solver;
   solver.SetSlices(10);
   solver.SetSection(section);
   auto solution = solver.Solve(strainPlane);

   TRY_TESTME(IsEqual(solution->GetFz(), -6989.5380720604908));
   TRY_TESTME(IsEqual(solution->GetMx(), -199028.63168431941));
   TRY_TESTME(IsEqual(solution->GetMy(), 0.0));
   TRY_TESTME(IsEqual(solution->GetCompressionResultant(), -7042.3377809023850));
   TRY_TESTME(IsEqual(solution->GetTensionResultant(), 52.799708841892233));

   // solve again with a different number of slices
   solver.SetSlices(20);
   solution = solver.Solve(strainPlane);

   TRY_TESTME(IsEqual(solution->GetFz(), -6952.5633140647860));
   TRY_TESTME(IsEqual(solution->GetMx(), -199133.42342670338));
   TRY_TESTME(IsEqual(solution->GetMy(), 0.0));
   TRY_TESTME(IsEqual(solution->GetCompressionResultant(), -7005.3630229066785));
   TRY_TESTME(IsEqual(solution->GetTensionResultant(), 52.799708841892233));

   // solve with new section
   solver.SetSection(nullptr); // this should clear out the current section
   solver.SetSection(section); // set the section back, but to the solver it is a new section
   solution = solver.Solve(strainPlane);

   TRY_TESTME(IsEqual(solution->GetFz(), -6952.5633140647860));
   TRY_TESTME(IsEqual(solution->GetMx(), -199133.42342670338));
   TRY_TESTME(IsEqual(solution->GetMy(), 0.0));
   TRY_TESTME(IsEqual(solution->GetCompressionResultant(), -7005.3630229066785));
   TRY_TESTME(IsEqual(solution->GetTensionResultant(), 52.799708841892233));

   TESTME_EPILOG("GeneralSectionSolver");
}
#endif // _UNITTEST
