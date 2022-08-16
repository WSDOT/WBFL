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
#include <RCSection\MomentInteractionCurveSolver.h>
#include "MomentInteractionCurveSolverImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::RCSection;

MomentInteractionCurveSolver::MomentInteractionCurveSolver()
{
   m_pImpl = std::make_unique<MomentInteractionCurveSolverImpl>();
}

MomentInteractionCurveSolver::~MomentInteractionCurveSolver() = default;

void MomentInteractionCurveSolver::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_pImpl->SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& MomentInteractionCurveSolver::GetSection() const
{
   return m_pImpl->GetSection();
}

void MomentInteractionCurveSolver::SetSlices(IndexType nSlices)
{
   m_pImpl->SetSlices(nSlices);
}

IndexType MomentInteractionCurveSolver::GetSlices() const
{
   return m_pImpl->GetSlices();
}

void MomentInteractionCurveSolver::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_pImpl->SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 MomentInteractionCurveSolver::GetSliceGrowthFactor() const
{
   return m_pImpl->GetSliceGrowthFactor();
}

void MomentInteractionCurveSolver::SetTolerance(Float64 tolerance)
{
   m_pImpl->SetTolerance(tolerance);
}

Float64 MomentInteractionCurveSolver::GetTolerance() const
{
   return m_pImpl->GetTolerance();
}

void MomentInteractionCurveSolver::SetMaxIterations(IndexType maxIter)
{
   m_pImpl->SetMaxIterations(maxIter);
}

IndexType MomentInteractionCurveSolver::GetMaxIterations() const
{
   return m_pImpl->GetMaxIterations();
}

void MomentInteractionCurveSolver::GetCompressionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const
{
   return m_pImpl->GetCompressionLimit(Fz, Mx, My, eo);
}

void MomentInteractionCurveSolver::GetTensionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const
{
   return m_pImpl->GetTensionLimit(Fz, Mx, My, eo);
}

std::unique_ptr<InteractionCurveSolution> MomentInteractionCurveSolver::Solve(Float64 Fz, Float64 startNA, Float64 endNA, IndexType nSteps) const
{
   return m_pImpl->Solve(Fz, startNA, endNA, nSteps);
}

#if defined _UNITTEST
#include <Units/Units.h>
#include <Materials/Materials.h>
#include <GeomModel/GeomModel.h>
#include <RCSection/SectionBuilder.h>
bool MomentInteractionCurveSolver::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("MomentInteractionCurveSolver");

   // This example is from "Reinforced Concrete Design", 4th Edition, Salmon & Wang
   // Example 13.21.3
   // See interaction diagram soluion in Figure 13.21.14. Note that the examples X-Y is different than our X-Y
   // See scanned image in Supporting Documents folder

   // base units of kip and ksi
   WBFL::Units::AutoSystem au;
   WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

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
   // note that this provides a uniform layout of the reinforcing and the bars are slightly non-uniform in the example
   // expect results to differ slightly. also, these calculations use strain compatibility where the textbook uses equivalent stress block
   auto section = SectionBuilder::RectangularColumn(12, 18, 2.38, 4, 4, 0.79, concrete, rebar, true);

   MomentInteractionCurveSolver solver;
   solver.SetSection(section);

   auto solution = solver.Solve(-1000000, 0, PI_OVER_2, 3); // compression force too high
   TRY_TESTME(solution->GetSolutionPointCount() == 0);

   solution = solver.Solve(1000000, 0, PI_OVER_2, 3); // tension force too high
   TRY_TESTME(solution->GetSolutionPointCount() == 0);

   // solve with Fz = 0
   solution = solver.Solve(0, 0, PI_OVER_2, 3); // bending about the horizontal axis

   Float64 tol = solver.GetTolerance();

   static Float64 mx[]{ -2057.163679,-951.68031,0.0 };
   static Float64 my[]{ 0.0,-2759.325957,-3568.871898 };

   auto nPoints = solution->GetSolutionPointCount();
   for (IndexType i = 0; i < nPoints; i++)
   {
      const auto& moment_capacity = solution->GetSolutionPoint(i);
      Float64 P = moment_capacity->GetFz();
      Float64 Mx = moment_capacity->GetMx();
      Float64 My = moment_capacity->GetMy();
      TRY_TESTME(IsZero(P,tol));
      TRY_TESTME(IsEqual(Mx,mx[i]));
      TRY_TESTME(IsEqual(My,my[i]));
   }

   TESTME_EPILOG("MomentInteractionCurveSolver");
}

#endif // _UNITTEST
