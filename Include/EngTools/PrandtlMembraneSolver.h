///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2022  Washington State Department of Transportation
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

class mathUnsymmetricBandedMatrix;

namespace WBFL
{
   namespace Geometry
   {
      class Shape;
   };

   namespace EngTools
   {
      class UniformFDMesh;

      /// Computes the St Venant torisional constant using the Prandtl membrane analogy
      ///
      /// \f$ \frac{\partial ^2 z}{\partial x^2} + \frac{\partial ^2 z}{\partial y^2} = -\frac{q}{S} \f$
      class ENGTOOLSCLASS PrandtlMembraneSolver
      {
      public:
         PrandtlMembraneSolver();
         ~PrandtlMembraneSolver();

         /// Computes the torsional constant, J
         /// \param[in] mesh a finite difference mesh
         /// \param[out] meshValues the finite difference solution.
         /// \return Torsional constant, J
         //Float64 ComputeJ(const UniformFDMesh& mesh, std::unique_ptr<Float64[]>& meshValues) const;

         void Initialize(Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry = false);
         PrandtlMembraneSolution Solve(const std::unique_ptr<WBFL::Geometry::Shape>& shape) const;
         static PrandtlMembraneSolution Solve(const std::unique_ptr<WBFL::Geometry::Shape>& shape, Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry = false);
      private:
         Float64 m_DxMin{ 1 };
         Float64 m_DyMin{ 1 };
         bool m_bIgnoreSymmetry{ false };
         static void BuildMatrix(const std::unique_ptr<UniformFDMesh>& mesh, mathUnsymmetricBandedMatrix& matrix); ///< Builds the finite difference system of equations
         static void BuildMatrixRow(IndexType startMeshRowIdx, IndexType endMeshRowIdx, const std::unique_ptr<UniformFDMesh>& mesh, mathUnsymmetricBandedMatrix& matrix); ///< Builds an individual row in the matrix, called from multiple threads
         static Float64 ComputeVolume(IndexType startElementIdx, IndexType endElementIdx, const std::unique_ptr<UniformFDMesh>& mesh, const std::unique_ptr<Float64[]>& meshValues);
      };
   };
};
