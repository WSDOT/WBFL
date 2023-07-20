///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/EqualSpacingDiaphragmLineFactory.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>

using namespace WBFL::COGO;

void EqualSpacingDiaphragmLineFactory::SetAlignmentID(IDType alignmentID)
{
   m_AlignmentID = alignmentID;
}

IDType EqualSpacingDiaphragmLineFactory::GetAlignmentID() const
{
   return m_AlignmentID;
}

void EqualSpacingDiaphragmLineFactory::SetStationRange(const Station& startStation, const Station& endStation)
{
   m_StartStation = startStation;
   m_EndStation = endStation;
}

std::pair<const Station&, const Station&> EqualSpacingDiaphragmLineFactory::GetStationRange() const
{
   return std::make_pair(m_StartStation, m_EndStation);
}

void EqualSpacingDiaphragmLineFactory::SetDiaphragmLineID(IDType id)
{
   m_ID = id;
}

IDType EqualSpacingDiaphragmLineFactory::GetDiaphragmLineID() const
{
   return m_ID;
}

void EqualSpacingDiaphragmLineFactory::SetDiaphragmLineIDIncrement(IDType idIncrement)
{
   m_IDIncrement = idIncrement;
}

IDType EqualSpacingDiaphragmLineFactory::GetDiaphragmLineIDIncrement() const
{
   return m_IDIncrement;
}

void EqualSpacingDiaphragmLineFactory::SetDivisor(Uint16 divisor)
{
   m_Divisor = divisor;
}

Uint16 EqualSpacingDiaphragmLineFactory::GetDivisor() const
{
   return m_Divisor;
}

void EqualSpacingDiaphragmLineFactory::IsStaggered(bool bIsStaggered)
{
   m_bIsStaggered = bIsStaggered;
}

bool EqualSpacingDiaphragmLineFactory::IsStaggered() const
{
   return m_bIsStaggered;
}

void EqualSpacingDiaphragmLineFactory::SetGirderLineID(SideType side, IDType id)
{
   m_GirderLineID[+side] = id;
}

IDType EqualSpacingDiaphragmLineFactory::GetGirderLineID(SideType side) const
{
   return m_GirderLineID[+side];
}

std::vector<std::shared_ptr<DiaphragmLine>> EqualSpacingDiaphragmLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   std::vector<std::shared_ptr<DiaphragmLine>> diaphragm_lines;

   auto alignment = bridge->GetAlignment(m_AlignmentID);

   auto start_station = alignment->ConvertToNormalizedStation(m_StartStation).GetValue();
   auto end_station = alignment->ConvertToNormalizedStation(m_EndStation).GetValue();

   IDType ID = m_ID;
   for (Uint16 i = 1; i < m_Divisor; i++, ID += m_IDIncrement)
   {
      Float64 station = start_station + (end_station - start_station) * i / m_Divisor;

      auto normal = alignment->GetNormal(station);
      auto point_on_alignment = alignment->LocatePoint(station, OffsetType::Normal, 0.0, 0.0);

      WBFL::Geometry::Line2d line(point_on_alignment, WBFL::Geometry::Vector2d(1.0, normal));

      auto diaphragm_line = DiaphragmLine::Create(bridge, ID, m_GirderLineID[+SideType::Left], m_GirderLineID[+SideType::Right], m_bIsStaggered, line);
      diaphragm_lines.emplace_back(diaphragm_line);
   }

   return diaphragm_lines;
}
