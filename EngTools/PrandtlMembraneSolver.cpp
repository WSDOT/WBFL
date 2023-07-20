///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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


#include <EngTools/EngToolsLib.h>
#include <EngTools/PrandtlMembraneSolver.h>        // class implementation
#include <EngTools/UniformFDMesh.h>
#include <future>
#include <numeric>
#include <System/Threads.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/Plane3d.h>
#include <GeomModel/Vector2d.h>
#include <GeomModel/Vector3d.h>
#include <Math/UnsymmetricBandedMatrix.h>
#include "FDMeshGenerator.h"

using namespace WBFL::EngTools;

/// Builds the finite difference equations.
/// \param[in] mesh the finite difference mesh
/// \param[in,out] matrix the finite difference equations
void BuildMatrix(const std::unique_ptr<UniformFDMesh>& mesh, WBFL::Math::UnsymmetricBandedMatrix& matrix); ///< Builds the finite difference system of equations

/// Creates the finite difference equations for the specified range of rows and stores the coefficients in the matrix
/// \param[in] startMeshRowIdx index of the first mesh row to be processed
/// \param[in] endMeshRowIdx index of the last mesh row to be processed
/// \param[in] mesh the mesh for which the finite difference equations are being generated
/// \param[in] matrix the augmented coefficient matrix for the finite difference equations
void BuildMatrixRow(IndexType startMeshRowIdx, IndexType endMeshRowIdx, const std::unique_ptr<UniformFDMesh>& mesh, WBFL::Math::UnsymmetricBandedMatrix& matrix); ///< Builds an individual row in the matrix, called from multiple threads

/// Computes the membrane volume for a subset of elements in the FD mesh
/// \param[in] startElementIdx index of the first element for which to compute the volume
/// \param[in] endElementIdx index of the last element for which to compute the volume
/// \param[in] mesh the finite difference mesh
/// \param[in] meshValues the solution to the finite difference equations
/// \return tuple containing the volume under the membrane for the specified range of elements, the maximum membrane slope, and the index of the element where the maximum slop occurs
std::tuple<Float64, Float64, IndexType> ComputeVolumeAndMaxSlope(IndexType startElementIdx, IndexType endElementIdx, const std::unique_ptr<UniformFDMesh>& mesh, const std::vector<Float64>& meshValues);


void PrandtlMembraneSolver::Initialize(Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry)
{
   m_DxMin = dxMin;
   m_DyMin = dyMin;
   m_bIgnoreSymmetry = bIgnoreSymmetry;
}

PrandtlMembraneSolution PrandtlMembraneSolver::Solve(const WBFL::Geometry::Shape* shape) const
{
   return Solve(shape, m_DxMin, m_DyMin, m_bIgnoreSymmetry);
}

PrandtlMembraneSolution PrandtlMembraneSolver::Solve(const WBFL::Geometry::Shape* shape, Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry)
{
   FDMeshGenerator mesh_generator(dxMin, dyMin);

   std::unique_ptr<UniformFDMesh> mesh = mesh_generator.GenerateMesh(shape);

   IndexType nInteriorNodes = mesh->GetInteriorNodeCount();
   IndexType bw = 2 * mesh->GetMaxIntriorNodesPerRow() + 1;
   WBFL::Math::UnsymmetricBandedMatrix matrix(nInteriorNodes, bw);
   BuildMatrix(mesh, matrix);

   auto meshValues = matrix.Solve();

   auto nElements = mesh->GetElementCount();

   IndexType nWorkerThreads, nElementsPerThread;
   WBFL::System::Threads::GetThreadParameters(nElements, nWorkerThreads, nElementsPerThread);

   std::vector<std::future<std::tuple<Float64,Float64,IndexType>>> vFutures;
   IndexType startElementIdx = 0;
   for (IndexType i = 0; i < nWorkerThreads; i++)
   {
      IndexType endElementIdx = startElementIdx + nElementsPerThread - 1;
      vFutures.emplace_back(std::async(&ComputeVolumeAndMaxSlope, startElementIdx, endElementIdx, std::ref(mesh), std::ref(meshValues)));
      startElementIdx = endElementIdx + 1;
   }

   auto result = ComputeVolumeAndMaxSlope(startElementIdx, nElements - 1, mesh, meshValues);
   for (auto& future : vFutures)
   {
      auto future_result = future.get();
      std::get<0>(result) += std::get<0>(future_result); // Add J (similar to J += future.J

      // compare maximum slope (stored in element 1 of the tuple)
      if (std::get<1>(result) < std::get<1>(future_result))
      {
         // future_result has a greater maximum slope... assign it to result
         // and assign the corresponding element index
         std::get<1>(result) = std::get<1>(future_result);
         std::get<2>(result) = std::get<2>(future_result);
      }
   }

   if (mesh->HasSymmetry())
   {
      // if there is symmetry, only have the section was modeled
      // so double J to get the full value
      std::get<0>(result) *= 2;
   }

   PrandtlMembraneSolution solution(std::get<0>(result), std::get<1>(result), std::get<2>(result), std::move(mesh), std::move(meshValues));
   return solution;
}

void BuildMatrix(const std::unique_ptr<UniformFDMesh>& mesh, WBFL::Math::UnsymmetricBandedMatrix& matrix)
{
   auto nElements = mesh->GetElementRowCount(); // this is the number of rows of elements
                                               // we need number of rows of nodes which is one more than the number of elements
                                               // however the top and bottom rows are boundary rows so we don't generate FD equations for them
                                               // nElements + 1 - 2 = nElements - 1
   nElements--;

   IndexType nWorkerThreads, nElementsPerThread;
   WBFL::System::Threads::GetThreadParameters(nElements, nWorkerThreads, nElementsPerThread);

   IndexType startMeshRowIdx = 0;
   std::vector<std::future<void>> vFutures;
   for (IndexType i = 0; i < nWorkerThreads; i++)
   {
      IndexType endMeshRowIdx = startMeshRowIdx + nElementsPerThread - 1;
      vFutures.emplace_back(std::async(&BuildMatrixRow, startMeshRowIdx, endMeshRowIdx, std::ref(mesh), std::ref(matrix)));
      startMeshRowIdx = endMeshRowIdx + 1;
   }

   BuildMatrixRow(startMeshRowIdx, nElements - 1, mesh, matrix);
   for (auto& f : vFutures)
   {
      f.get();
   }
}

void BuildMatrixRow(IndexType startMeshRowIdx, IndexType endMeshRowIdx, const std::unique_ptr<UniformFDMesh>& mesh, WBFL::Math::UnsymmetricBandedMatrix& matrix)
{
   // compute constants that are the same for all rows
   Float64 Dx, Dy;
   mesh->GetElementSize(&Dx, &Dy);
   Float64 R2 = pow(Dy / Dx, 2);
   Float64 K0 = 0.5 * (1 + R2);
   Float64 K13 = -0.25;
   Float64 K24 = -0.25 * R2;
   Float64 K24_Sym = 2 * K24;
   Float64 Dy2 = Dy * Dy;

   bool bIsSymmetric = mesh->HasSymmetry();
   IndexType symmetryIdx = 0;
   if (bIsSymmetric)
   {
      IndexType Nx, Ny;
      std::tie(Nx,Ny) = mesh->GetGridSize();
      symmetryIdx = Nx - 1;
   }

   for (IndexType meshRowIdx = startMeshRowIdx; meshRowIdx <= endMeshRowIdx; meshRowIdx++)
   {
      IndexType gridRowStartIdx, startElementIdx, endElementIdx;
      mesh->GetElementRange(meshRowIdx, &gridRowStartIdx, &startElementIdx, &endElementIdx);
      if (bIsSymmetric)
      {
         // the loop below doesn't cover the last element in the row because, for full grids
         // the right hand side of the last elements in a row are boundary nodes.
         // for meshes with a vertical axis of symmetry, the right hand side of the last
         // elements aren't boundaries. the loop must cover these elements so add one
         // to the end element
         endElementIdx++;
      }


      for (IndexType elementIdx = startElementIdx; elementIdx < endElementIdx; elementIdx++, gridRowStartIdx++)
      {
         const auto* pElement = mesh->GetElement(elementIdx);

         if (pElement->Node[+FDMeshElement::Corner::BottomRight] != INVALID_INDEX)
         {
            matrix.SetCoefficient(pElement->Node[+FDMeshElement::Corner::BottomRight], pElement->Node[+FDMeshElement::Corner::BottomRight], K0);

            const auto* pBelowElement = mesh->GetElementBelow(meshRowIdx, elementIdx - startElementIdx);
            if (pBelowElement && pBelowElement->Node[+FDMeshElement::Corner::BottomRight] != INVALID_INDEX)
            {
               matrix.SetCoefficient(pElement->Node[+FDMeshElement::Corner::BottomRight], pBelowElement->Node[+FDMeshElement::Corner::BottomRight], K13);
            }

            if (pElement->Node[+FDMeshElement::Corner::BottomLeft] != INVALID_INDEX)
            {
               if (bIsSymmetric && gridRowStartIdx == symmetryIdx)
               {
                  matrix.SetCoefficient(pElement->Node[+FDMeshElement::Corner::BottomRight], pElement->Node[+FDMeshElement::Corner::BottomLeft], K24_Sym);
               }
               else
               {
                  matrix.SetCoefficient(pElement->Node[+FDMeshElement::Corner::BottomRight], pElement->Node[+FDMeshElement::Corner::BottomLeft], K24);
               }
            }

            if (pElement->Node[+FDMeshElement::Corner::TopRight] != INVALID_INDEX)
            {
               matrix.SetCoefficient(pElement->Node[+FDMeshElement::Corner::BottomRight], pElement->Node[+FDMeshElement::Corner::TopRight], K13);
            }

            if (!bIsSymmetric || gridRowStartIdx != symmetryIdx)
            {
               const auto* pNextElement = mesh->GetElement(elementIdx + 1);
               if (pNextElement->Node[+FDMeshElement::Corner::BottomRight] != INVALID_INDEX)
               {
                  matrix.SetCoefficient(pElement->Node[+FDMeshElement::Corner::BottomRight], pNextElement->Node[+FDMeshElement::Corner::BottomRight], K24);
               }
            }

            matrix.SetC(pElement->Node[+FDMeshElement::Corner::BottomRight], Dy2);
         }
      }
   }
}

std::tuple<Float64, Float64, WBFL::Geometry::Vector2d> PrandtlMembraneSolver::GetElementVolumeAndMaxSlope(IndexType elementIndex, const UniformFDMesh* mesh, const std::vector<Float64>& meshValues)
{
   Float64 area = mesh->GetElementArea();
   static std::array<Float64, 5> area_factor{ 0, 1. / 3., 0.5, 5. / 6., 1.0 }; // factors for computing volume based on number of non-boundary nodes

   Float64 maxSlope = -Float64_Max;
   WBFL::Geometry::Vector2d shear_stress_direction;

   Float64 dx, dy;
   mesh->GetElementSize(&dx, &dy);

   const auto* pElement = mesh->GetElement(elementIndex);
   auto nInteriorNodes = std::count_if(pElement->Node.begin(), pElement->Node.end(), [](auto idx) {return idx != INVALID_INDEX; });
   if (nInteriorNodes == 0)
   {
      CHECK(false); // not sure if this should ever happen
      return std::tuple<Float64, Float64, WBFL::Geometry::Vector2d>(0, 0, WBFL::Geometry::Vector2d(1, 0));
   }

   Float64 sum_values = std::accumulate(pElement->Node.begin(), pElement->Node.end(), 0.0, [&pElement, &meshValues](Float64 sum, IndexType idx) { return sum + (idx == INVALID_INDEX ? 0.0 : meshValues[idx]); });
   Float64 avg_value = sum_values / nInteriorNodes;

   Float64 V = area_factor[nInteriorNodes] * area * avg_value;

   Float64 center_value = sum_values / 4;
   // For purposes of computing the shear stress and slope of the mesh element planes, 
   // if there is only one result take the value at the center of the mesh element to be zero.
   if (nInteriorNodes == 1)
      center_value = 0.0;

   // Slopes are computed based on 4 planes derived from the mesh element corners taken 2 at a time plus the center point of the mesh element.
   // This array holds the corners on the boundary of the mesh element used to create each plane. The third point is always the center.
   // Points are defined counter-clockwise so the surface normal is outward from the membrane bubble surface
   //
   //  4                  3
   //   +-----------------+
   //   |                 |  ^
   //   |                 |  |
   //   |        C        |  dy
   //   |                 |  |
   //   |                 |  v
   //   +-----------------+
   //  1      <-- dx -->  2
   using ElementCorners = std::pair<FDMeshElement::Corner, FDMeshElement::Corner>;
   static std::array<ElementCorners, 4> elementCorners{                                      // Order of points for defining planes
      ElementCorners(FDMeshElement::Corner::BottomLeft, FDMeshElement::Corner::BottomRight), // 1->2->C
      ElementCorners(FDMeshElement::Corner::BottomRight, FDMeshElement::Corner::TopRight),   // 2->3->C
      ElementCorners(FDMeshElement::Corner::TopRight, FDMeshElement::Corner::TopLeft),       // 3->4->C
      ElementCorners(FDMeshElement::Corner::TopLeft, FDMeshElement::Corner::BottomLeft)      // 4->1->C
   };

   // This array holds the coordinates of the 2 boundary points used to create each of the 4 planes.
   using PlanePoints = std::pair<WBFL::Geometry::Point3d, WBFL::Geometry::Point3d>;
   std::array<PlanePoints, 4> planePoints{
      PlanePoints({0.,0.,0.},{dx,0.,0.}),
      PlanePoints({dx,0.,0.},{dx,dy,0.}),
      PlanePoints({dx,dy,0.},{0.,dy,0.}),
      PlanePoints({0.,dy,0.},{0.,0.,0.})
   };

   WBFL::Geometry::Plane3d plane;
   WBFL::Geometry::Point3d p0, p1, p2(dx/2,dy/2, center_value); // p2 is the center point

   for (long i = 0; i < 4; i++) // loop over the four planes
   {
      // three points to make a plane... the z value at all these points is set to zero
      p0 = planePoints[i].first;
      p1 = planePoints[i].second;

      // set the z value based on the mesh results
      p0.Z() = pElement->Node[+elementCorners[i].first]  == INVALID_INDEX ? 0.0 : meshValues[pElement->Node[+elementCorners[i].first]];
      p1.Z() = pElement->Node[+elementCorners[i].second] == INVALID_INDEX ? 0.0 : meshValues[pElement->Node[+elementCorners[i].second]];

      // create a plane through the points
      plane.ThroughPoints(p0, p1, p2);

      // get the vector normal to the plane and normalize it (need unit vectors for dot product calculation)
      auto normal = plane.NormalVector();
      normal.Normalize();

      // the direction of the max slope is the normal vector projected onto the horizontal plane
      auto max_slope_direction = normal;
      max_slope_direction.Z() = 0; // set z to creates the vector in the horizontal plane

      // if max_direction is a zero vector, then the plane is horizontal and normal is in the Z direction only
      // for that case, take cosine of the slope to be 0 (so angle with normal vector is Pi/2)
      // slope will then be 0 after the taking the arc-cosine and adjusting for normal vector orientation

      Float64 cos_angle = 0; // cosine of angle between vectors
      if (max_slope_direction.IsZero())
      {
         max_slope_direction.X() = 1.0; // if there isn't a clear direction, make it to the left but skip the calculations that are in the else-block
      }
      else
      {
         max_slope_direction.Normalize();

         // dot product of the two unit vectors is the cos of the angle between the vectors
         cos_angle = normal.Dot(max_slope_direction);
      }

      // get the angle...
      Float64 angle = acos(cos_angle);
      angle = PI_OVER_2 - angle; // rotate by Pi/2 since the angle is with the normal vector, not the vector in the plane

      Float64 slope = tan(angle); // make the angle a slope

      if (maxSlope < slope)
      {
         // capture the maximum slope and record the element where it occurs
         maxSlope = slope;
         
         shear_stress_direction.X() = max_slope_direction.X();
         shear_stress_direction.Y() = max_slope_direction.Y();

         // this is the direction of the maximum slope.... 
         // the direction of the shear stress is 90 degrees to this direction, 
         // in the direction of the shear stress contour line (line of constant elevation on the membrane bubble)
         shear_stress_direction.Rotate(PI_OVER_2);
      }
   }

   return std::tuple<Float64, Float64, WBFL::Geometry::Vector2d>(V, maxSlope, shear_stress_direction);
}

std::tuple<Float64, Float64, IndexType> ComputeVolumeAndMaxSlope(IndexType startElementIdx, IndexType endElementIdx, const std::unique_ptr<UniformFDMesh>& mesh, const std::vector<Float64>& meshValues)
{
   std::tuple<Float64, Float64, IndexType> result{ 0,-Float64_Max,INVALID_INDEX };

   for (IndexType elementIdx = startElementIdx; elementIdx <= endElementIdx; elementIdx++)
   {
      auto element_result = PrandtlMembraneSolver::GetElementVolumeAndMaxSlope(elementIdx, mesh.get(), meshValues);
      std::get<0>(result) += std::get<0>(element_result); // += Volume

      if (std::get<1>(result) < std::get<1>(element_result))
      {
         // element maxSlope is greater than overall max slope
         std::get<1>(result) = std::get<1>(element_result);
         std::get<2>(result) = elementIdx;
      }
   }
   return result;
}
