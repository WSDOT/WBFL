///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2024  Washington State Department of Transportation
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
