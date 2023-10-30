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
#include "MomentCurvatureSolverImpl.h"
#include <RCSection/XRCSection.h>

#define MAX_FAIL 4

using namespace WBFL::RCSection;

void MomentCurvatureSolverImpl::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_CapacitySolver.SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& MomentCurvatureSolverImpl::GetSection() const
{
   return m_CapacitySolver.GetSection();
}

void MomentCurvatureSolverImpl::SetSlices(IndexType nSlices)
{
   m_CapacitySolver.SetSlices(nSlices);
}

IndexType MomentCurvatureSolverImpl::GetSlices() const
{
   return m_CapacitySolver.GetSlices();
}

void MomentCurvatureSolverImpl::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_CapacitySolver.SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 MomentCurvatureSolverImpl::GetSliceGrowthFactor() const
{
   return m_CapacitySolver.GetSliceGrowthFactor();
}

void MomentCurvatureSolverImpl::SetTolerance(Float64 tolerance)
{
   m_CapacitySolver.SetTolerance(tolerance);
}

Float64 MomentCurvatureSolverImpl::GetTolerance() const
{
   return m_CapacitySolver.GetTolerance();
}

void MomentCurvatureSolverImpl::SetMaxIterations(IndexType maxIter)
{
   m_CapacitySolver.SetMaxIterations(maxIter);
}

IndexType MomentCurvatureSolverImpl::GetMaxIterations() const
{
   return m_CapacitySolver.GetMaxIterations();
}

void MomentCurvatureSolverImpl::SetInitialCurvatureStep(Float64 k)
{
   m_kInitialStep = k;
}

Float64 MomentCurvatureSolverImpl::GetInitialCurvatureStep() const
{
   return m_kInitialStep;
}

std::unique_ptr<MomentCurvatureSolution> MomentCurvatureSolverImpl::Solve(Float64 Fz, Float64 angle) const
{
   auto solution(std::make_unique<MomentCurvatureSolution>());

   Uint32 nFail = 0;
   Float64 k = 0;
   bool bSucceeded = true;
   while (bSucceeded)
   {
      bSucceeded = AnalyzeSection(Fz, angle, k, solution);
      if (!bSucceeded && nFail < MAX_FAIL)
      {
         bSucceeded = true;
         k -= GetCurvatureIncrement(nFail);
         nFail++;
      }
      k += GetCurvatureIncrement(nFail);
   }
   return solution;
}

Float64 MomentCurvatureSolverImpl::GetCurvatureIncrement(Uint32 nFail) const
{
   CHECK(0 < m_kInitialStep);
   return m_kInitialStep / pow(2., Float64(nFail));
}

bool MomentCurvatureSolverImpl::AnalyzeSection(Float64 Fz, Float64 angle, Float64 k, std::unique_ptr<MomentCurvatureSolution>& pCurvatureSolution) const
{
   auto capacity_solution = m_CapacitySolver.Solve(Fz, angle, k, 0.0, MomentCapacitySolver::SolutionMethod::FixedCurvature);
   if (capacity_solution->GetGeneralSectionSolution()->ExceededStrainLimits()) return false;

#if defined _DEBUG
   Float64 Pz = capacity_solution->GetFz();
   Float64 tol = GetTolerance();
   CHECK(IsEqual(Fz, Pz, tol));
#endif

   pCurvatureSolution->AddPoint(std::move(capacity_solution));

   return true;
}
