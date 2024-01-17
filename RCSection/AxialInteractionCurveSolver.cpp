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
#include <RCSection\AxialInteractionCurveSolver.h>
#include "AxialInteractionCurveSolverImpl.h"

using namespace WBFL::RCSection;

AxialInteractionCurveSolver::AxialInteractionCurveSolver()
{
   m_pImpl = std::make_unique<AxialInteractionCurveSolverImpl>();
}

AxialInteractionCurveSolver::~AxialInteractionCurveSolver() = default;

void AxialInteractionCurveSolver::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_pImpl->SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& AxialInteractionCurveSolver::GetSection() const
{
   return m_pImpl->GetSection();
}

void AxialInteractionCurveSolver::SetSlices(IndexType nSlices)
{
   m_pImpl->SetSlices(nSlices);
}

IndexType AxialInteractionCurveSolver::GetSlices() const
{
   return m_pImpl->GetSlices();
}

void AxialInteractionCurveSolver::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_pImpl->SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 AxialInteractionCurveSolver::GetSliceGrowthFactor() const
{
   return m_pImpl->GetSliceGrowthFactor();
}

void AxialInteractionCurveSolver::SetTolerance(Float64 tolerance)
{
   m_pImpl->SetTolerance(tolerance);
}

Float64 AxialInteractionCurveSolver::GetTolerance() const
{
   return m_pImpl->GetTolerance();
}

void AxialInteractionCurveSolver::SetMaxIterations(IndexType maxIter)
{
   m_pImpl->SetMaxIterations(maxIter);
}

IndexType AxialInteractionCurveSolver::GetMaxIterations() const
{
   return m_pImpl->GetMaxIterations();
}

const CapacityLimit& AxialInteractionCurveSolver::GetCompressionLimit() const
{
   return m_pImpl->GetCompressionLimit();
}

const CapacityLimit& AxialInteractionCurveSolver::GetTensionLimit() const
{
   return m_pImpl->GetTensionLimit();
}

std::unique_ptr<InteractionCurveSolution> AxialInteractionCurveSolver::Solve(Float64 na, IndexType nFzSteps) const
{
   return m_pImpl->Solve(na, nFzSteps);
}
