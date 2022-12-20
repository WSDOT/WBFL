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

#include <EngTools\EngToolsExp.h>


namespace WBFL
{
   namespace EngTools
   {
      class UniformFDMesh;

      /// Solution to the Prandtl Membrane analysis for the torsion constant problem
      class ENGTOOLSCLASS PrandtlMembraneSolution
      {
      public:
         PrandtlMembraneSolution() = default; ///< Call Initialize to initialize the solution
         PrandtlMembraneSolution(PrandtlMembraneSolution&& other);
         PrandtlMembraneSolution(Float64 J, Float64 maxSlope,IndexType elementIdx,std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues);
         PrandtlMembraneSolution& operator=(PrandtlMembraneSolution&& other);

         /// Initializes the solution
         ///
         /// @param J torsion constant
         /// @param maxSlope Maximum slope on the membrane surface
         /// @param elementIdx Index of the element where the maximum slope occurs
         /// @param mesh the finite difference mesh used to solve the problem
         /// @param meshValues the mesh ordinate values for the solution
         void Initialize(Float64 J, Float64 maxSlope, IndexType elementIdx, std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues);

         /// Returns the torsion constant
         Float64 GetJ() const;

         /// @brief Returns the maximum slope on the membrane surface
         /// @param[out] pMaxSlope Maximum slope
         /// @param[out] pElementIdx Element where the maximum slope occurs
         void GetMaxSlope(Float64* pMaxSlope, IndexType* pElementIdx) const;

         /// @brief Returns the maximum shear stress per unit torque
         /// @return Max shear stress per unit torque
         Float64 GetTmaxPerUnitTorque() const;

         /// Returns the finite difference mesh
         const std::unique_ptr<UniformFDMesh>& GetFiniteDifferenceMesh() const;

         /// Returns the finite difference solution.
         ///
         /// The FD solution is the elevation of the Prandtl Membrane at each of the nodes of
         /// the FD mesh.The array index is the node index of the FD model.
         /// 
         /// Access a FD solution value with GetFiniteDifferenceMesh()->GetElement(elementIndex)->Node[corner], where corner
         /// is one of the FDMeshElement::Corner enum values.
         const std::unique_ptr<Float64[]>& GetFiniteDifferenceSolution() const;

      private:
         Float64 m_J{ 0 }; // torsion constant
         Float64 m_MaxSlope{ 0 }; // maximum slope on the membrane surface
         IndexType m_ElementIndex{ INVALID_INDEX }; // element where the maximum slope occurs
         std::unique_ptr<UniformFDMesh> m_Mesh; // finite difference mesh
         std::unique_ptr<Float64[]> m_MeshValues; // solution (ordinate values at the mesh nodes)
      };
   };
};
