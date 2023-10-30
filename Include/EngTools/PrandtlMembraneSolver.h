///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

#include <EngTools/EngToolsExp.h>
#include <EngTools/PrandtlMembraneSolution.h>
#include <EngTools/UniformFDMesh.h>

namespace WBFL
{
   namespace Geometry
   {
      class Shape;
      class Vector2d;
   };

   namespace EngTools
   {
      /// Computes the St Venant torsional constant using the Prandtl membrane analogy by solving the following equation using the finite difference method
      /// \f[ \frac{\partial ^2 z}{\partial x^2} + \frac{\partial ^2 z}{\partial y^2} = -\frac{q}{S} \f]
      /// "Saint-Venant Torsion Constant of Modern Precast Concrete Bridge Girders", Brice R., Pickings R., 2021, PCI Journal, V66, No3, pp23-31
      /// https://doi.org/10.15554/pcij66.3-01
      /// 
      /// "Torsional and Other Properties of Prestressed Concrete Sections", Yoo, C., 2000, PCI Journal , V45, No3, pp66-72
      /// https://doi.org/10.15554/pcij.05012000.66.72
      class ENGTOOLSCLASS PrandtlMembraneSolver
      {
      public:
         PrandtlMembraneSolver() = default;
         PrandtlMembraneSolver(const PrandtlMembraneSolver&) = default;
         ~PrandtlMembraneSolver() = default;
         PrandtlMembraneSolver& operator=(const PrandtlMembraneSolver&) = default;

         /// @brief Initializes the solver
         /// @param dxMin minimum size of a finite difference grid element in the X-direction
         /// @param dyMin minimum size of a finite difference grid element in the Y-direction
         /// @param bIgnoreSymmetry if true, the symmetry of the cross section is ignored and the full grid is used for analysis
         void Initialize(Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry = false);

         /// @brief Solves the governing equation for the shape provided. The shape must be symmetric about the Y-axis
         /// @param shape shape of the section to be analyzed
         /// @return Returns a PrandtlMembraneSolution object
         PrandtlMembraneSolution Solve(const WBFL::Geometry::Shape* shape) const;

         /// @brief  the governing equation for the shape provided. The shape must be symmetric about the Y-axis
         /// @param shape shape of the section to be analyzed
         /// @param dxMin minimum size of a finite difference grid element in the X-direction
         /// @param dyMin minimum size of a finite difference grid element in the Y-direction
         /// @param bIgnoreSymmetry if true, the symmetry of the cross section is ignored and the full grid is used for analysis
         /// @return Returns a PrandtlMembraneSolution object
         static PrandtlMembraneSolution Solve(const WBFL::Geometry::Shape* shape, Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry = false);

         /// @brief Computes the volume, maximum slope, and direction of maximum slope for a solution element
         /// @param elementIndex Index of the element
         /// @param mesh The finite difference mesh
         /// @param meshValues The finite difference solution values
         /// @return A tuple containing Element Volume, Maximum Slope of Membrane Surface, Direction of Maximum Slope
         static std::tuple<Float64,Float64,WBFL::Geometry::Vector2d> GetElementVolumeAndMaxSlope(IndexType elementIndex, const UniformFDMesh* mesh, const std::vector<Float64>& meshValues);

      private:
         Float64 m_DxMin{ 1 };
         Float64 m_DyMin{ 1 };
         bool m_bIgnoreSymmetry{ false };
      };
   };
};
