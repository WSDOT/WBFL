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
#include "MomentInteractionCurveSolverImpl.h"
#include <RCSection/XRCSection.h>

#define MAX_FAIL 4

using namespace WBFL::RCSection;

void MomentInteractionCurveSolverImpl::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_Solver.SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& MomentInteractionCurveSolverImpl::GetSection() const
{
   return m_Solver.GetSection();
}

void MomentInteractionCurveSolverImpl::SetSlices(IndexType nSlices)
{
   m_Solver.SetSlices(nSlices);
}

IndexType MomentInteractionCurveSolverImpl::GetSlices() const
{
   return m_Solver.GetSlices();
}

void MomentInteractionCurveSolverImpl::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_Solver.SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 MomentInteractionCurveSolverImpl::GetSliceGrowthFactor() const
{
   return m_Solver.GetSliceGrowthFactor();
}

void MomentInteractionCurveSolverImpl::SetTolerance(Float64 tolerance)
{
   m_Solver.SetTolerance(tolerance);
}

Float64 MomentInteractionCurveSolverImpl::GetTolerance() const
{
   return m_Solver.GetTolerance();
}

void MomentInteractionCurveSolverImpl::SetMaxIterations(IndexType maxIter)
{
   m_Solver.SetMaxIterations(maxIter);
}

IndexType MomentInteractionCurveSolverImpl::GetMaxIterations() const
{
   return m_Solver.GetMaxIterations();
}

const CapacityLimit& MomentInteractionCurveSolverImpl::GetCompressionLimit() const
{
   return m_Solver.GetCompressionLimit();
}

const CapacityLimit& MomentInteractionCurveSolverImpl::GetTensionLimit() const
{
   return m_Solver.GetTensionLimit();
}

std::unique_ptr<InteractionCurveSolution> MomentInteractionCurveSolverImpl::Solve(Float64 Fz, Float64 startNA, Float64 endNA, IndexType nSteps) const
{
   auto solution(std::make_unique<InteractionCurveSolution>());

   const auto& tension_capacity_limit = GetTensionLimit();
   const auto& compression_capacity_limit = GetCompressionLimit();
   
   auto FzMax = tension_capacity_limit.Fz;
   auto FzMin = compression_capacity_limit.Fz;
   auto eo = compression_capacity_limit.eo;

   if (!InRange(FzMin, Fz, FzMax))
   {
      return solution;
   }

   if (nSteps < 3)
      nSteps = 3;

   Float64 stepSize = (endNA - startNA) / (nSteps - 1);

   for (IndexType i = 0; i < nSteps; i++)
   {
      Float64 na = startNA + i*stepSize;
      auto moment_capacity_solution = m_Solver.Solve(Fz, na, eo, 0.0, MomentCapacitySolver::SolutionMethod::FixedCompressionStrain);
      solution->AddSolutionPoint(std::move(moment_capacity_solution));
   }

   solution->SortByNeutralAxisDirection();

   return solution;
}
