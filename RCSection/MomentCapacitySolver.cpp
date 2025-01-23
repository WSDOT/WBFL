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
#include <RCSection\MomentCapacitySolver.h>
#include "MomentCapacitySolverImpl.h"

using namespace WBFL::RCSection;

MomentCapacitySolver::MomentCapacitySolver()
{
   m_pImpl = std::make_unique<MomentCapacitySolverImpl>();
}

MomentCapacitySolver::~MomentCapacitySolver() = default;

void MomentCapacitySolver::SetSection(const std::shared_ptr<const IGeneralSection>& section)
{
   m_pImpl->SetSection(section);
}

const std::shared_ptr<const IGeneralSection>& MomentCapacitySolver::GetSection() const
{
   return m_pImpl->GetSection();
}

void MomentCapacitySolver::SetSlices(IndexType nSlices)
{
   m_pImpl->SetSlices(nSlices);
}

IndexType MomentCapacitySolver::GetSlices() const
{
   return m_pImpl->GetSlices();
}

void MomentCapacitySolver::SetSliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_pImpl->SetSliceGrowthFactor(sliceGrowthFactor);
}

Float64 MomentCapacitySolver::GetSliceGrowthFactor() const
{
   return m_pImpl->GetSliceGrowthFactor();
}

void MomentCapacitySolver::SetTolerance(Float64 tolerance)
{
   m_pImpl->SetTolerance(tolerance);
}

Float64 MomentCapacitySolver::GetTolerance() const
{
   return m_pImpl->GetTolerance();
}

void MomentCapacitySolver::SetMaxIterations(IndexType maxIter)
{
   m_pImpl->SetMaxIterations(maxIter);
}

IndexType MomentCapacitySolver::GetMaxIterations() const
{
   return m_pImpl->GetMaxIterations();
}

std::unique_ptr<MomentCapacitySolution> MomentCapacitySolver::Solve(Float64 Fz, Float64 angle, Float64 k_or_ec, Float64 strainLocation, SolutionMethod solutionMethod) const
{
   return m_pImpl->Solve(Fz, angle, k_or_ec, strainLocation, solutionMethod);
}

WBFL::Geometry::Point2d MomentCapacitySolver::GetPlasticCentroid() const
{
   return m_pImpl->GetPlasticCentroid();
}

const CapacityLimit& MomentCapacitySolver::GetCompressionLimit() const
{
   return m_pImpl->GetCompressionLimit();
}

const CapacityLimit& MomentCapacitySolver::GetTensionLimit() const
{
   return m_pImpl->GetTensionLimit();
}
