///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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


#include <EngTools/EngToolsLib.h>
#include <EngTools/PrandtlMembraneSolver.h>        // class implementation
#include <EngTools/UniformFDMesh.h>
#include <future>
#include <System/Threads.h>
#include <Math/UnsymmetricBandedMatrix.h>
#include "FDMeshGenerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::EngTools;

/// Builds the finite difference equations.
/// \param[in] mesh the finite differnce mesh
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
/// \return the volume under the membrane for the specified range of elements
Float64 ComputeVolume(IndexType startElementIdx, IndexType endElementIdx, const std::unique_ptr<UniformFDMesh>& mesh, const std::unique_ptr<Float64[]>& meshValues);


void PrandtlMembraneSolver::Initialize(Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry)
{
   m_DxMin = dxMin;
   m_DyMin = dyMin;
   m_bIgnoreSymmetry = bIgnoreSymmetry;
}

PrandtlMembraneSolution PrandtlMembraneSolver::Solve(const std::unique_ptr<WBFL::Geometry::Shape>& shape) const
{
   return Solve(shape, m_DxMin, m_DyMin, m_bIgnoreSymmetry);
}

PrandtlMembraneSolution PrandtlMembraneSolver::Solve(const std::unique_ptr<WBFL::Geometry::Shape>& shape, Float64 dxMin, Float64 dyMin, bool bIgnoreSymmetry)
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

   std::vector<std::future<Float64>> vFutures;
   IndexType startElementIdx = 0;
   for (IndexType i = 0; i < nWorkerThreads; i++)
   {
      IndexType endElementIdx = startElementIdx + nElementsPerThread - 1;
      vFutures.emplace_back(std::async(&ComputeVolume, startElementIdx, endElementIdx, std::ref(mesh), std::ref(meshValues)));
      startElementIdx = endElementIdx + 1;
   }

   Float64 J = ComputeVolume(startElementIdx, nElements - 1, mesh, meshValues);
   for (auto& result : vFutures)
   {
      J += result.get();
   }

   if (mesh->HasSymmetry())
   {
      J *= 2;
   }

   PrandtlMembraneSolution solution(J, std::move(mesh), std::move(meshValues));
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
      mesh->GetGridSize(&Nx, &Ny);
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

         if (pElement->Node[FDMeshElement::BottomRight] != INVALID_INDEX)
         {
            matrix(pElement->Node[FDMeshElement::BottomRight], pElement->Node[FDMeshElement::BottomRight]) = K0;

            const auto* pBelowElement = mesh->GetElementBelow(meshRowIdx, elementIdx - startElementIdx);
            if (pBelowElement && pBelowElement->Node[FDMeshElement::BottomRight] != INVALID_INDEX)
            {
               matrix(pElement->Node[FDMeshElement::BottomRight], pBelowElement->Node[FDMeshElement::BottomRight]) = K13;
            }

            if (pElement->Node[FDMeshElement::BottomLeft] != INVALID_INDEX)
            {
               if (bIsSymmetric && gridRowStartIdx == symmetryIdx)
               {
                  matrix(pElement->Node[FDMeshElement::BottomRight], pElement->Node[FDMeshElement::BottomLeft]) = K24_Sym;
               }
               else
               {
                  matrix(pElement->Node[FDMeshElement::BottomRight], pElement->Node[FDMeshElement::BottomLeft]) = K24;
               }
            }

            if (pElement->Node[FDMeshElement::TopRight] != INVALID_INDEX)
            {
               matrix(pElement->Node[FDMeshElement::BottomRight], pElement->Node[FDMeshElement::TopRight]) = K13;
            }

            if (!bIsSymmetric || gridRowStartIdx != symmetryIdx)
            {
               const auto* pNextElement = mesh->GetElement(elementIdx + 1);
               if (pNextElement->Node[FDMeshElement::BottomRight] != INVALID_INDEX)
               {
                  matrix(pElement->Node[FDMeshElement::BottomRight], pNextElement->Node[FDMeshElement::BottomRight]) = K24;
               }
            }

            matrix[pElement->Node[FDMeshElement::BottomRight]] = Dy2;
         }
      }
   }
}

Float64 ComputeVolume(IndexType startElementIdx, IndexType endElementIdx, const std::unique_ptr<UniformFDMesh>& mesh, const std::unique_ptr<Float64[]>& meshValues)
{
   Float64 V = 0;
   Float64 area = mesh->GetElementArea();
   static std::array<Float64, 5> area_factor{ 0, 1. / 3., 0.5, 5. / 6., 1.0 };
   for (IndexType elementIdx = startElementIdx; elementIdx <= endElementIdx; elementIdx++)
   {
      const auto* pElement = mesh->GetElement(elementIdx);
      IndexType nInteriorNodes = 0;
      Float64 sum_values = 0;
      for (long i = 0; i < 4; i++)
      {
         if (pElement->Node[i] != INVALID_INDEX)
         {
            sum_values += meshValues[pElement->Node[i]];
            nInteriorNodes++;
         }
      }

      // if there are no interior nodes, all nodes are on the boundary and
      // their values are zero so no contribution to the volume under the membrane
      if (nInteriorNodes != 0)
      {
         Float64 avg_value = sum_values / nInteriorNodes;
         Float64 dV = area_factor[nInteriorNodes] * area * avg_value;
         V += dV;
      }
   }

   return V;
}

#if defined _UNITTEST
#include <GeomModel/GeomModel.h>
#include <MathEx.h>
bool PrandtlMembraneSolver::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PrandtlMembraneSolver");

   auto beam = std::make_unique<WBFL::Geometry::PrecastBeam>();
   beam->SetC1(1);
   beam->SetD1(3);
   beam->SetD2(3);
   beam->SetD3(3);
   beam->SetD4(3);
   beam->SetD5(4.5);
   beam->SetD6(5.125);
   beam->SetHeight(100);
   beam->SetT1(6.125);
   beam->SetT2(6.125);
   beam->SetW1(6);
   beam->SetW2(18.4375);
   beam->SetW3(3);
   beam->SetW4(3);
   beam->SetW5(13.125);

   std::unique_ptr<WBFL::Geometry::Shape> shape(std::move(beam));

   // use symmetry
   PrandtlMembraneSolution solution = PrandtlMembraneSolver::Solve(shape, 0.25, 0.25);
   TRY_TESTME(IsEqual(solution.GetJ(), 18506.51360));
   TRY_TESTME(IsEqual(solution.GetFiniteDifferenceMesh()->GetMeshArea(), 1109.25));

   // ignore symmetry
   solution = PrandtlMembraneSolver::Solve(shape, 0.25, 0.25, false);
   TRY_TESTME(IsEqual(solution.GetJ(), 18506.51360));
   TRY_TESTME(IsEqual(solution.GetFiniteDifferenceMesh()->GetMeshArea(), 1109.25));

   // use a solver object
   PrandtlMembraneSolver solver;
   solver.Initialize(0.25, 0.25);
   solution = solver.Solve(shape);
   TRY_TESTME(IsEqual(solution.GetJ(), 18506.51360));
   TRY_TESTME(IsEqual(solution.GetFiniteDifferenceMesh()->GetMeshArea(), 1109.25));

   TESTME_EPILOG("PrandtlMembraneSolver");
}

#endif // _UNITTEST


