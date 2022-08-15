///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <RCSection/GeneralSectionSolution.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/Plane3d.h>

namespace WBFL
{
   namespace RCSection
   {
      class MomentCapacitySolutionImpl;

      /// Solution to a biaxial moment capacity analysis.
      ///
      /// Check the general section solution to see if the strain limit of any of the materials were exceeded during the analysis.
      class RCSCLASS MomentCapacitySolution
      {
      public:
         MomentCapacitySolution();
         MomentCapacitySolution(const MomentCapacitySolution& other) = delete; // can't copy because of unique_ptr - also don't need copy semantics
         ~MomentCapacitySolution();
         
         MomentCapacitySolution& operator=(const MomentCapacitySolution& other) = delete; // can't assign

         /// Initialize with the solution results
         void InitSolution(
            Float64 fz, ///< Resultant axial force
            Float64 mx, ///< Resultant moment about the horizontal centroidal axis
            Float64 my, ///< Resultant moment about the vertical centroidal axis
            const WBFL::Geometry::Plane3d& strainPlane, ///< Plane3d object representing the strain plane
            const WBFL::Geometry::Line2d& neutralAxis, ///< Line2d object representing the neutral axis
            const WBFL::Geometry::Point2d& cgC, ///< Location of resultant compression force
            Float64 C, ///< Resultant compression force
            const WBFL::Geometry::Point2d& cgT, ///< Location of resultant tension force
            Float64 T, ///< Resultant tension force
            std::unique_ptr<GeneralSectionSolution>&& solution ///< GeneralSectionSolution object corresponding to the resulting strain plane
         );

         /// Resultant axial force
         Float64 GetFz() const;

         /// Resultant moment about the horizontal centroidal axis
         Float64 GetMx() const;

         /// Resultant moment about the vertical centroidal axis
         Float64 GetMy() const;

         /// Plane3d object representing the strain plane
         const WBFL::Geometry::Plane3d& GetStrainPlane() const;

         /// Line2d object representing the neutral axis
         const WBFL::Geometry::Line2d& GetNeutralAxis() const;

         /// Angle of the neutral axis measured in radians, counter-clockwise from the positive X-axis
         Float64 GetNeutralAxisDirection() const;

         /// Resultant compression force
         Float64 GetCompressionResultant() const;

         /// Resultant tension force
         Float64 GetTensionResultant() const;

         /// Location of the resultant compression force
         const WBFL::Geometry::Point2d& GetCompressionResultantLocation() const;

         /// Location of the resultant tension force
         const WBFL::Geometry::Point2d& GetTensionResultantLocation() const;

         /// GeneralSectionSolution object corresponding to the resulting strain plane
         const std::unique_ptr<GeneralSectionSolution>& GetGeneralSectionSolution() const;

      private:
         std::unique_ptr<MomentCapacitySolutionImpl> m_pImpl;

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};