///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/SinglePierLineFactory.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>

using namespace WBFL::COGO;

SinglePierLineFactory::SinglePierLineFactory(IDType pierID, IDType alignmentID, const Station& station, const std::_tstring& strDirection, Float64 length, Float64 offset, const ConnectionGeometry& back, const ConnectionGeometry& ahead) :
   m_ID(pierID),m_AlignmentID(alignmentID),m_Station(station),m_strDirection(strDirection),m_Length(length), m_Offset(offset)
{
   m_Connections[+PierFaceType::Back] = back;
   m_Connections[+PierFaceType::Ahead] = ahead;
}

void SinglePierLineFactory::SetPierLineID(IDType id)
{
   m_ID = id;
}

IDType SinglePierLineFactory::GetPierLineID() const
{
   return m_ID;
}

void SinglePierLineFactory::SetAlignmentID(IDType alignmentID)
{
   m_AlignmentID = alignmentID;
}

IDType SinglePierLineFactory::GetAlignmentID() const
{
   return m_AlignmentID;
}

void SinglePierLineFactory::SetStation(const Station& station)
{
   m_Station = station;
}

const Station& SinglePierLineFactory::GetStation() const
{
   return m_Station;
}

void SinglePierLineFactory::SetDirection(const std::_tstring& strDirection)
{
   m_strDirection = strDirection;
}

const std::_tstring& SinglePierLineFactory::GetDirection() const
{
   return m_strDirection;
}

void SinglePierLineFactory::SetLength(Float64 length)
{
   m_Length = length;
}

Float64 SinglePierLineFactory::GetLength() const
{
   return m_Length;
}

void SinglePierLineFactory::SetOffset(Float64 offset)
{
   m_Offset = offset;
}

Float64 SinglePierLineFactory::GetOffset() const
{
   return m_Offset;
}

void SinglePierLineFactory::SetConnectionGeometry(PierFaceType face, const ConnectionGeometry& connection)
{
   m_Connections[+face] = connection;
}

const ConnectionGeometry& SinglePierLineFactory::GetConnectionGeometry(PierFaceType face) const
{
   return m_Connections[+face];
}

std::vector<std::shared_ptr<PierLine>> SinglePierLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   std::vector<std::shared_ptr<PierLine>> pier_lines;
   auto pier_line = PierLine::Create(bridge, m_ID, m_AlignmentID, m_Station, m_strDirection, m_Length, m_Offset, m_Connections[+PierFaceType::Back], m_Connections[+PierFaceType::Ahead]);
   pier_lines.emplace_back(pier_line);
   return pier_lines;
}
