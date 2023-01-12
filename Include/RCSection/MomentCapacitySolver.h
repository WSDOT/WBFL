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
#include <RCSection/GeneralSection.h>
#include <RCSection/MomentCapacitySolution.h>

namespace WBFL
{
   namespace RCSection
   {
      class MomentCapacitySolverImpl;

      /// A moment capacity solver discritizes a GeneralSection object into GeneralSectionSlices and performs a moment capacity analysis by summing the force and moment contribution of each
      // slice, varying the location of the neutral axis, while keep it's direction constant, until equilibrium if satisfied. This is a common fiber based strain compatibility analysis.
      class RCSCLASS MomentCapacitySolver
      {
      public:
         enum class SolutionMethod
         {
            FixedCurvature, ///< A fixed curvature is specified.
            FixedCompressionStrain, ///< A fixed strain at the extreme compression fiber is specified.
            FixedTensionStrain, ///< A fixed strain at the extreme tension fiber is specified.
            FixedStrain ///< A fixed strain and location where the strain occurs is specified.
         };

         MomentCapacitySolver();
         MomentCapacitySolver(const MomentCapacitySolver& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~MomentCapacitySolver();
         
         MomentCapacitySolver& operator=(const MomentCapacitySolver& other) = delete; // can't assign

         /// GeneralSection object to be analyzed
         void SetSection(const std::shared_ptr<const IGeneralSection>& section);
         const std::shared_ptr<const IGeneralSection>& GetSection() const;
         
         /// Number of slices to subdivide the section into for analysis
         void SetSlices(IndexType nSlices);
         IndexType GetSlices() const;

         /// A factor that varies the height of the slices.
         ///
         /// The height of the slice furthest from the compression face is this factor times the height of the first slice.If the slice growth factor is 2, the last slice will be twice as tall as the first slice.
         ///
         ///  Slice heights reduce when the factor is less than 1 and grow if greater than 1. All slices are the same height wht the factor is 1.
         void SetSliceGrowthFactor(Float64 sliceGrowthFactor);
         Float64 GetSliceGrowthFactor() const;

         /// Convergence tolerance for axial force equilibrium
         void SetTolerance(Float64 tolerance);
         Float64 GetTolerance() const;

         /// Maximum number of iterations before solution fails
         void SetMaxIterations(IndexType maxIter);
         IndexType GetMaxIterations() const;

         /// Performs the moment capacity analysis
         ///
         /// The location of the neutral axis is varied until the resultant internal force is equal to the external force Fz.
         /// Compression is assumed to be on the left side of the neutral axis. For a typical bending about the X-axis, use a neutral axis angle of 0.0 for positive moment (compression top - tension bottom)
         /// and PI (180deg) for negative moment (tension top - compression bottom).
         ///
         /// "Positive moments" (compression top - tension bottom) have negative values. The resultant compression force (C) is negative and the resultant tension force (T) is positive. 
         /// At equilibrium T + C = 0 so C = -T. Assume the point (0,0) is at the bottom of the girder. The location of the resultant tension and compression forces are at Yc and Yt, respectively. 
         /// Yc > 0 and Yt > 0 and Yc > Yt. Therefore, Mn = C*Yc + T*Yt = -T*Yc + T*Yt = T*(Yt - Yc). 
         /// With Yc > Yt, Yt - Yc < 0 and T > 0. The product of a positive number and a negative number is negative. "Negative moments" have positive values.
         ///
         /// This analysis adds the initial strains to an incremental strain plane to determine the total state of strains. The total strain at the centroid of each slice is
         /// used to compute the stress and force contribution of the slice. The incremental strain plane is varied until the equilibrium state is found.
         std::unique_ptr<MomentCapacitySolution> Solve(
            Float64 Fz, ///< Externally applied axial force.
            Float64 angle, ///< Direction of the neutral axis (radians), measured counter-clockwise from the X axis
            Float64 k_or_ec, ///< Curvature of the section if solutionMethod is smFixedCurvature, otherwise the strain increment at the extreme compression or tension fiber or at a specified elevation in the section dependon solutionMethod.
            Float64 strainLocation, ///< Distance from a line parallel to the neutral axis passing through (0,0) to the location where strain is specified by k_or_ec. Distance is greater than zero when the strain specified by k_or_ec is on the left side of this line. This parameter is only used if solutionMethod is smFixedStrain.
            SolutionMethod solutionMethod ///< Indicates the method of solution.
         ) const;

         /// Location of the plastic centroid.
         ///
         /// The plastic centroid is computed by determining the location of the resultant force when the entire section is strained uniformly in compression.
         WBFL::Geometry::Point2d GetPlasticCentroid() const;

         /// Compression limit
         ///
         /// The compression limit is the force state for the maximum compression force that can be applied to the section
         void GetCompressionLimit(
            Float64* Fz, ///< Maximum axial compression force
            Float64* Mx, ///< Corresponding moment about the X-axis
            Float64* My, ///< Corresponding moment about the Y-axis
            Float64* eo ///< Strain at (0,0)
         ) const;

         /// Tension limit
         ///
         /// The tension limit is the force state for the maximum tensile force that can be applied to the section
         void GetTensionLimit(
            Float64* Fz, ///< Maximum axial tension force
            Float64* Mx, ///< Corresponding moment about the X-axis
            Float64* My, ///< Corresponding moment about the Y-axis
            Float64* eo ///< Strain at (0,0)
         ) const;

      private:
         std::unique_ptr<MomentCapacitySolverImpl> m_pImpl;

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
      private:
         static bool Test1(WBFL::Debug::Log& rlog);
         static bool Test2(WBFL::Debug::Log& rlog);
         static bool Test3(WBFL::Debug::Log& rlog);
         static bool Test4(WBFL::Debug::Log& rlog);
         static bool Test5(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};