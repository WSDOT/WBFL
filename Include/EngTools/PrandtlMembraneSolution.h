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

      // Solution to the Prandtl Membrane analysis for the torsion constant problem
      class ENGTOOLSCLASS PrandtlMembraneSolution
      {
      public:
         PrandtlMembraneSolution() = default; ///< Call Initialize to initialize the solution
         PrandtlMembraneSolution(PrandtlMembraneSolution&& other);
         PrandtlMembraneSolution(Float64 J, std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues);
         PrandtlMembraneSolution& operator=(PrandtlMembraneSolution&& other);

         /// Initializes the solution
         ///
         /// \param J torsion constant
         /// \param mesh the finite difference mesh used to solve the problem
         /// \param meshValues the mesh ordinate values for the solution
         void Initialize(Float64 J, std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues);

         /// Returns the torsion constant
         Float64 GetJ() const;

         /// Returns the finite diffence mesh
         const std::unique_ptr<UniformFDMesh>& GetFiniteDifferenceMesh() const;

         /// Returns the finite difference solution
         const std::unique_ptr<Float64[]>& GetFiniteDifferenceSolution() const;

      private:
         Float64 m_J{ 0 };
         std::unique_ptr<UniformFDMesh> m_Mesh;
         std::unique_ptr<Float64[]> m_MeshValues;
      };
   };
};
