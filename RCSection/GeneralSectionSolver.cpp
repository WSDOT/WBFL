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
#include <RCSection\GeneralSectionSolver.h>
#include "GeneralSectionSolverImpl.h"

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
