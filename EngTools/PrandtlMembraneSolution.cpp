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
   Initialize(other.m_J, std::move(other.m_Mesh), std::move(other.m_MeshValues));
}

PrandtlMembraneSolution::PrandtlMembraneSolution(Float64 J, std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues)
{
   Initialize(J, std::move(mesh), std::move(meshValues));
}

PrandtlMembraneSolution& PrandtlMembraneSolution::operator=(PrandtlMembraneSolution&& other)
{
   Initialize(other.m_J, std::move(other.m_Mesh), std::move(other.m_MeshValues));
   return *this;
}

void PrandtlMembraneSolution::Initialize(Float64 J, std::unique_ptr<UniformFDMesh>&& mesh, std::unique_ptr<Float64[]>&& meshValues)
{
   m_J = J;
   m_Mesh = std::move(mesh);
   m_MeshValues = std::move(meshValues);
}

Float64 PrandtlMembraneSolution::GetJ() const
{
   return m_J;
}

const std::unique_ptr<UniformFDMesh>& PrandtlMembraneSolution::GetFiniteDifferenceMesh() const
{
   return m_Mesh;
}

const std::unique_ptr<Float64[]>& PrandtlMembraneSolution::GetFiniteDifferenceSolution() const
{
   return m_MeshValues;
}
