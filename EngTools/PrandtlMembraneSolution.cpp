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
#include <EngTools/PrandtlMembraneSolution.h>        // class implementation
#include <EngTools/UniformFDMesh.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::EngTools;

PrandtlMembraneSolution::PrandtlMembraneSolution(PrandtlMembraneSolution&& other)
{
   Initialize(other.m_J, other.m_MaxSlope, other.m_ElementIndex, std::move(other.m_Mesh), std::move(other.m_MeshValues));
}

PrandtlMembraneSolution::PrandtlMembraneSolution(Float64 J, Float64 maxSlope, IndexType elementIdx, std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues)
{
   Initialize(J, maxSlope, elementIdx, std::move(mesh), std::move(meshValues));
}

PrandtlMembraneSolution& PrandtlMembraneSolution::operator=(PrandtlMembraneSolution&& other)
{
   Initialize(other.m_J, other.m_MaxSlope, other.m_ElementIndex, std::move(other.m_Mesh), std::move(other.m_MeshValues));
   return *this;
}

void PrandtlMembraneSolution::Initialize(Float64 J, Float64 maxSlope, IndexType elementIdx, std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues)
{
   m_J = J;
   m_MaxSlope = maxSlope;
   m_ElementIndex = elementIdx;
   m_Mesh = std::move(mesh);
   m_MeshValues = std::move(meshValues);
}

Float64 PrandtlMembraneSolution::GetJ() const
{
   return m_J;
}

void PrandtlMembraneSolution::GetMaxSlope(Float64* pMaxSlope, IndexType* pElementIdx) const
{
   *pMaxSlope = m_MaxSlope;
   *pElementIdx = m_ElementIndex;
}

Float64 PrandtlMembraneSolution::GetTmaxPerUnitTorque() const
{
   Float64 J = GetJ();
   Float64 Tmax = m_MaxSlope / (2 * J);
   return Tmax;
}

const std::unique_ptr<UniformFDMesh>& PrandtlMembraneSolution::GetFiniteDifferenceMesh() const
{
   return m_Mesh;
}

const std::unique_ptr<Float64[]>& PrandtlMembraneSolution::GetFiniteDifferenceSolution() const
{
   return m_MeshValues;
}

WBFL::Geometry::Rectangle PrandtlMembraneSolution::GetMeshElement(IndexType elementIdx) const
{
   // top left corner is at (0,0)
   Float64 dx, dy;
   m_Mesh->GetElementSize(&dx, &dy);

   IndexType gridRowIdx, gridRowPositionIdx;
   m_Mesh->GetElementPosition(elementIdx, &gridRowIdx, &gridRowPositionIdx);
   Float64 x = gridRowPositionIdx * dx;
   Float64 y = -1.0 * gridRowIdx * dy;

   WBFL::Geometry::Point2d center(x + dx / 2, y - dy / 2);
   return WBFL::Geometry::Rectangle(center, dx, dy);
}
