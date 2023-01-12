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

#include <RCSection/RCSectionLib.h>
#include "AxialInteractionCurveSolverImpl.h"
#include <RCSection/XRCSection.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_FAIL 4

using namespace WBFL::RCSection;

void AxialInteractionCurveSolverImpl::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_Solver.SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& AxialInteractionCurveSolverImpl::GetSection() const
{
   return m_Solver.GetSection();
}

void AxialInteractionCurveSolverImpl::SetSlices(IndexType nSlices)
{
   m_Solver.SetSlices(nSlices);
}

IndexType AxialInteractionCurveSolverImpl::GetSlices() const
{
   return m_Solver.GetSlices();
}

void AxialInteractionCurveSolverImpl::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_Solver.SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 AxialInteractionCurveSolverImpl::GetSliceGrowthFactor() const
{
   return m_Solver.GetSliceGrowthFactor();
}

void AxialInteractionCurveSolverImpl::SetTolerance(Float64 tolerance)
{
   m_Solver.SetTolerance(tolerance);
}

Float64 AxialInteractionCurveSolverImpl::GetTolerance() const
{
   return m_Solver.GetTolerance();
}

void AxialInteractionCurveSolverImpl::SetMaxIterations(IndexType maxIter)
{
   m_Solver.SetMaxIterations(maxIter);
}

IndexType AxialInteractionCurveSolverImpl::GetMaxIterations() const
{
   return m_Solver.GetMaxIterations();
}

void AxialInteractionCurveSolverImpl::GetCompressionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const
{
   m_Solver.GetCompressionLimit(Fz, Mx, My, eo);
}

void AxialInteractionCurveSolverImpl::GetTensionLimit(Float64* Fz, Float64* Mx, Float64* My, Float64* eo) const
{
   return m_Solver.GetTensionLimit(Fz, Mx, My, eo);
}

std::unique_ptr<InteractionCurveSolution> AxialInteractionCurveSolverImpl::Solve(Float64 na, IndexType nFzSteps) const
{
   auto solution(std::make_unique<InteractionCurveSolution>());

   Float64 FzMin, FzMax;
   Float64 Mx, My, eo;
   GetTensionLimit(&FzMax, &Mx, &My, &eo);
   GetCompressionLimit(&FzMin, &Mx, &My, &eo);

   if (nFzSteps < 3)
      nFzSteps = 3;

   Float64 stepSize = (FzMax - FzMin) / (nFzSteps - 1);

   for (IndexType i = 0; i < nFzSteps; i++)
   {
      Float64 fz = FzMin + i * stepSize;

      auto moment_capacity_solution = m_Solver.Solve(fz, na, eo, 0.0, MomentCapacitySolver::SolutionMethod::FixedCompressionStrain);
      solution->AddSolutionPoint(std::move(moment_capacity_solution));
   }

   solution->SortByFz();

   return solution;
}
