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
#include <RCSection\MomentInteractionCurveSolver.h>
#include "MomentInteractionCurveSolverImpl.h"

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

const CapacityLimit& MomentInteractionCurveSolver::GetCompressionLimit() const
{
   return m_pImpl->GetCompressionLimit();
}

const CapacityLimit& MomentInteractionCurveSolver::GetTensionLimit() const
{
   return m_pImpl->GetTensionLimit();
}

std::unique_ptr<InteractionCurveSolution> MomentInteractionCurveSolver::Solve(Float64 Fz, Float64 startNA, Float64 endNA, IndexType nSteps) const
{
   return m_pImpl->Solve(Fz, startNA, endNA, nSteps);
}
