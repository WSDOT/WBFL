///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <RCSection\MomentCurvatureSolver.h>
#include "MomentCurvatureSolverImpl.h"

using namespace WBFL::RCSection;

MomentCurvatureSolver::MomentCurvatureSolver()
{
   m_pImpl = std::make_unique<MomentCurvatureSolverImpl>();
}

MomentCurvatureSolver::~MomentCurvatureSolver() = default;

void MomentCurvatureSolver::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_pImpl->SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& MomentCurvatureSolver::GetSection() const
{
   return m_pImpl->GetSection();
}

void MomentCurvatureSolver::SetSlices(IndexType nSlices)
{
   m_pImpl->SetSlices(nSlices);
}

IndexType MomentCurvatureSolver::GetSlices() const
{
   return m_pImpl->GetSlices();
}

void MomentCurvatureSolver::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_pImpl->SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 MomentCurvatureSolver::GetSliceGrowthFactor() const
{
   return m_pImpl->GetSliceGrowthFactor();
}

void MomentCurvatureSolver::SetTolerance(Float64 tolerance)
{
   m_pImpl->SetTolerance(tolerance);
}

Float64 MomentCurvatureSolver::GetTolerance() const
{
   return m_pImpl->GetTolerance();
}

void MomentCurvatureSolver::SetMaxIterations(IndexType maxIter)
{
   m_pImpl->SetMaxIterations(maxIter);
}

IndexType MomentCurvatureSolver::GetMaxIterations() const
{
   return m_pImpl->GetMaxIterations();
}

void MomentCurvatureSolver::SetInitialCurvatureStep(Float64 k)
{
   m_pImpl->SetInitialCurvatureStep(k);
}

Float64 MomentCurvatureSolver::GetInitialCurvatureStep() const
{
   return m_pImpl->GetInitialCurvatureStep();
}

std::unique_ptr<MomentCurvatureSolution> MomentCurvatureSolver::Solve(Float64 Fz, Float64 angle) const
{
   return m_pImpl->Solve(Fz, angle);
}
