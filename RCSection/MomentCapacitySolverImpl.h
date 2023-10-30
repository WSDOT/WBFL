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
#pragma once

#include <RCSection/RCSectionExp.h>
#include <RCSection/GeneralSectionSolver.h>
#include <RCSection/GeneralSectionSolution.h>
#include <RCSection/MomentCapacitySolution.h>
#include <RCSection/MomentCapacitySolver.h>
#include <GeomModel/Primitives3d.h>

namespace WBFL
{
   namespace RCSection
   {
      class RCSCLASS MomentCapacitySolverImpl
      {
      public:
         MomentCapacitySolverImpl() = default;
         MomentCapacitySolverImpl(const MomentCapacitySolverImpl& other) = default;
         ~MomentCapacitySolverImpl() = default;
         
         MomentCapacitySolverImpl& operator=(const MomentCapacitySolverImpl& other) = default;

         void SetSection(const std::shared_ptr<const IGeneralSection>& section);
         const std::shared_ptr<const IGeneralSection>& GetSection() const;
         
         void SetSlices(IndexType nSlices);
         IndexType GetSlices() const;

         void SetSliceGrowthFactor(Float64 sliceGrowthFactor);
         Float64 GetSliceGrowthFactor() const;

         void SetTolerance(Float64 tolerance);
         Float64 GetTolerance() const;

         void SetMaxIterations(IndexType maxIter);
         IndexType GetMaxIterations() const;

         std::unique_ptr<MomentCapacitySolution> Solve(Float64 Fz,Float64 angle,Float64 k_or_ec,Float64 strainLocation,MomentCapacitySolver::SolutionMethod solutionMethod) const;

         WBFL::Geometry::Point2d GetPlasticCentroid() const;

         const CapacityLimit& GetCompressionLimit() const;
         const CapacityLimit& GetTensionLimit() const;

      private:
         mutable GeneralSectionSolver m_GeneralSolver;
         mutable std::unique_ptr<GeneralSectionSolution> m_GeneralSolution;
         mutable std::unique_ptr<GeneralSectionSolution> m_TensionSolution;
         mutable std::unique_ptr<GeneralSectionSolution> m_CompressionSolution;
         mutable WBFL::Geometry::Plane3d m_IncrementalStrainPlane;
         mutable WBFL::Geometry::Point3d m_P1, m_P2, m_P3;
         Float64 m_AxialTolerance{0.01};
         IndexType m_MaxIter{50};
         mutable bool m_bAnalysisPointUpdated{false};
         mutable WBFL::Geometry::Point2d m_ExtremeCompressionPoint; // this is compression side point furthest from the neutral axis
         mutable WBFL::Geometry::Point2d m_ExtremeTensionPoint; // this is the tension side point furthest from the neutral axis
         mutable WBFL::Geometry::Point2d m_ControlPoint; // this point is varied in the Z direction to manipulate the strain plane
         mutable WBFL::Geometry::Point2d m_FixedPoint; // this point is the fixed control point (like the point of -0.003 compression strain at the top of a section)

         mutable bool m_bUpdateLimits{true};
         mutable CapacityLimit m_TensionCapacityLimit;
         mutable CapacityLimit m_CompressionCapacityLimit;
         void UpdateLimits() const;

         void UpdateStrainPlane(Float64 angle, Float64 k_or_ec, Float64 strainLocation, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 eo) const;
         void UpdateAnalysisPoints(Float64 angle, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 strainLocation) const;
         void UpdateControlPoints(Float64 angle, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 strainLocation) const;
         void GetNeutralAxisParameterRange(Float64 k_or_ec, Float64 strainLocation, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 angle, Float64 Fz, Float64* peo_lower, Float64* peo_upper, Float64* pFz_lower, Float64* pFz_upper) const;
         std::unique_ptr<MomentCapacitySolution> AnalyzeSection(Float64 Fz, Float64 angle, Float64 k_or_ec, MomentCapacitySolver::SolutionMethod solutionMethod, Float64 strainLocation) const;
         std::unique_ptr<MomentCapacitySolution> CreateMomentCapacitySolution() const;
      };
   };
};