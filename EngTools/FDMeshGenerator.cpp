///////////////////////////////////////////////////////////////////////
// BEToolbox
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

#include <EngTools/EngToolsLib.h>
#include "FDMeshGenerator.h"

#include <GeomModel/Shape.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/ShapeProperties.h>
#include <System/Threads.h>

#include <vector>
#include <future>

using namespace WBFL::EngTools;

FDMeshGenerator::FDMeshGenerator()
{
}

FDMeshGenerator::FDMeshGenerator(Float64 dxMax, Float64 dyMax) :
   m_DxMax(dxMax), m_DyMax(dyMax)
{
}

void FDMeshGenerator::Initialize(Float64 dxMax, Float64 dyMax)
{
   m_DxMax = dxMax;
   m_DyMax = dyMax;
}

std::unique_ptr<UniformFDMesh> FDMeshGenerator::GenerateMesh(const WBFL::Geometry::Shape* shape, bool bIgnoreSymmetry) const
{
   std::unique_ptr<UniformFDMesh> mesh = std::make_unique<UniformFDMesh>();

   auto bbox = shape->GetBoundingBox();
   Float64 width = bbox.Width();
   Float64 height = bbox.Height();

   auto props = shape->GetProperties();

   Float64 Ixy = props.GetIxy();
   if (IsZero(Ixy) && !bIgnoreSymmetry)
   {
      // shape is symmetric (assume about the vertical axis)
      width /= 2;
      mesh->HasSymmetry(true);
   }

   IndexType Nx = IndexType(width / m_DxMax);
   IndexType Ny = IndexType(height / m_DyMax);

   if (mesh->HasSymmetry() && ::IsOdd(Nx))
   {
      // for a symmetric mesh the rows must have an even number of elements
      Nx++;
   }

   Float64 Dx = width / Nx;
   Float64 Dy = height / Ny;

   mesh->SetElementSize(Dx, Dy);

   auto pntTopLeft = bbox.TopLeft();
   Float64 tlx, tly;
   std::tie(tlx,tly) = pntTopLeft.GetLocation();

   mesh->AllocateElementRows(Ny); // preallocate the rows so we can add them in any order

   IndexType nWorkerThreads, nElementsPerThread;
   WBFL::System::Threads::GetThreadParameters(Ny, nWorkerThreads, nElementsPerThread);
   std::vector<std::future<void>> vFutures;
   IndexType rowStart = 0;
   for (IndexType t = 0; t < nWorkerThreads; t++)
   {
      IndexType rowEnd = rowStart + nElementsPerThread;
      vFutures.emplace_back(std::async(&FDMeshGenerator::GenerateMeshRows, rowStart, rowEnd, Nx, Dx, Dy, tlx, tly, shape, std::ref(mesh)));
      rowStart = rowEnd;
   }
   GenerateMeshRows(rowStart, Ny, Nx, Dx, Dy, tlx, tly, shape, mesh);

   for (auto& f : vFutures)
   {
      f.get();
   }

   return mesh;
}

void FDMeshGenerator::GenerateMeshRows(IndexType rowStart, IndexType rowEnd, IndexType Nx, Float64 dx, Float64 dy, Float64 tlx, Float64 tly, const WBFL::Geometry::Shape* shape, std::unique_ptr<UniformFDMesh>& mesh)
{
   for (IndexType row = rowStart; row < rowEnd; row++)
   {
      GenerateMeshRow(row, Nx, dx, dy, tlx, tly, shape, mesh);
   }
}

void FDMeshGenerator::GenerateMeshRow(IndexType row, IndexType Nx, Float64 dx, Float64 dy, Float64 tlx, Float64 tly, const WBFL::Geometry::Shape* shape, std::unique_ptr<UniformFDMesh>& mesh)
{
   Float64 cy = tly - row * dy - dy / 2;

   // Work left to right across the row until there is a grid point within the shape.
   // Then work right to left across the row until there is a grid point within the shape.
   // The indices of these row elements defines the range of mesh elements in the row
   // This assumes there aren't interior voids in the shape

   WBFL::Geometry::Point2d pnt;
   IndexType startElementIdx = INVALID_INDEX;
   for (IndexType col = 0; col < Nx; col++)
   {
      Float64 cx = tlx + col * dx + dx / 2;
      pnt.Move(cx, cy);
      bool bContainsPoint = shape->PointInShape(pnt);
      if (bContainsPoint)
      {
         // found the element where the row starts
         startElementIdx = col;
         break;
      }
   }

   if (startElementIdx == INVALID_INDEX)
   {
      // The row doesn't have any elements that meet the meshing criteria
      // however, the row can't be empty. add one element
      mesh->AddElements(row, Nx - 1, 1);
      return;
   }

   for (IndexType col = Nx - 1; col >= startElementIdx; col--)
   {
      Float64 cx = tlx + col * dx + dx / 2;
      pnt.Move(cx, cy);
      bool bContainsPoint = shape->PointInShape(pnt);
      if (bContainsPoint)
      {
         IndexType nElementsInRow = col - startElementIdx + 1;
         mesh->AddElements(row, startElementIdx, nElementsInRow);
         return;
      }
   }
}
