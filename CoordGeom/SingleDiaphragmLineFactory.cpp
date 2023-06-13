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
#include <CoordGeom/SingleDiaphragmLineFactory.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>


using namespace WBFL::COGO;

void SingleDiaphragmLineFactory::SetAlignmentID(IDType alignmentID)
{
   m_AlignmentID = alignmentID;
}

IDType SingleDiaphragmLineFactory::GetAlignmentID() const
{
   return m_AlignmentID;
}

void SingleDiaphragmLineFactory::SetStation(const Station& station)
{
   m_Station = station;
}

const Station& SingleDiaphragmLineFactory::GetStation() const
{
   return m_Station;
}

void SingleDiaphragmLineFactory::SetOrientation(const std::_tstring& strOrientation)
{
   m_strOrientation = strOrientation;
}

const std::_tstring& SingleDiaphragmLineFactory::GetOrientation() const
{
   return m_strOrientation;
}

void SingleDiaphragmLineFactory::SetDiaphragmLineID(IDType id)
{
   m_ID = id;
}

IDType SingleDiaphragmLineFactory::GetDiaphragmLineID() const
{
   return m_ID;
}

void SingleDiaphragmLineFactory::IsStaggered(bool bIsStaggered)
{
   m_bIsStaggered = bIsStaggered;
}

bool SingleDiaphragmLineFactory::IsStaggered() const
{
   return m_bIsStaggered;
}

void SingleDiaphragmLineFactory::SetGirderLineID(SideType side, IDType id)
{
   m_GirderLineID[+side] = id;
}

IDType SingleDiaphragmLineFactory::GetGirderLineID(SideType side) const
{
   return m_GirderLineID[+side];
}

std::vector<std::shared_ptr<DiaphragmLine>> SingleDiaphragmLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   std::vector<std::shared_ptr<DiaphragmLine>> diaphragm_lines;

   auto alignment = bridge->GetAlignment(m_AlignmentID);

   auto point = alignment->LocatePoint(m_Station, OffsetType::Normal, 0.0, 0.0);
   auto direction = alignment->GetDirection(m_Station, m_strOrientation);
   WBFL::Geometry::Line2d line(point, WBFL::Geometry::Vector2d(1.0, direction));

   auto diaphragm_line = DiaphragmLine::Create(bridge, m_ID, m_GirderLineID[+SideType::Left], m_GirderLineID[+SideType::Right], m_bIsStaggered, line);

   diaphragm_lines.emplace_back(diaphragm_line);
   return diaphragm_lines;
}

#if defined _UNITTEST
bool SingleDiaphragmLineFactory::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SingleDiaphragmLineFactory");

   TESTME_EPILOG("SingleDiaphragmLineFactory");
}
#endif // _UNITTEST


