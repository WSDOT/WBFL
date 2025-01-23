///////////////////////////////////////////////////////////////////////
// BEToolbox
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <EngTools/UniformFDMesh.h>

//interface IShape;
namespace WBFL
{
   namespace Geometry
   {
      class Shape;
   };

   namespace EngTools
   {
      //////////////////////////////////////////////////
      /// Generates a finite difference mesh for a shape
      //////////////////////////////////////////////////
      class FDMeshGenerator
      {
      public:
         FDMeshGenerator(); ///< Default constructor. Call Initialize() before calling GenerateMesh()
         FDMeshGenerator(Float64 dxMax, Float64 dyMax); ///< Initializes the mesh generator with the maximum element dimensions
         void Initialize(Float64 dxMax, Float64 dyMax); ///< Initializes the mesh generator with the maximum element dimensions

         /// Generates a finite difference mesh, taking advantage of a vertical axis of symmetry if present
         /// \param[in] pShape the shape to generate the mesh for
         /// \param[in] mesh the mesh to be generated
         /// \param[in] bIgnoreSymmetry if true, symmetry of the shape is ignored and a full mesh is generated
         std::unique_ptr<UniformFDMesh> GenerateMesh(const WBFL::Geometry::Shape* shape, bool bIgnoreSymmetry = false) const; ///< Generates a finite difference mesh, taking advantage of a vertical axis of symmetry if present

      private:
         Float64 m_DxMax, m_DyMax;
         static void GenerateMeshRow(IndexType rowIdx, IndexType Nx, Float64 dx, Float64 dy, Float64 tlx, Float64 tly, const WBFL::Geometry::Shape* shape, std::unique_ptr<UniformFDMesh>& mesh);
         static void GenerateMeshRows(IndexType rowStart, IndexType rowEnd, IndexType Nx, Float64 dx, Float64 dy, Float64 tlx, Float64 tly, const WBFL::Geometry::Shape* shape, std::unique_ptr<UniformFDMesh>& mesh);
      };
   };
};
