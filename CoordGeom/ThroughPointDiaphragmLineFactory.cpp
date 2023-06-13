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
#include <CoordGeom/ThroughPointDiaphragmLineFactory.h>

using namespace WBFL::COGO;

void ThroughPointDiaphragmLineFactory::SetPoint(const WBFL::Geometry::Point2d& point)
{
   m_Point = point;
}

const WBFL::Geometry::Point2d& ThroughPointDiaphragmLineFactory::GetPoint() const
{
   return m_Point;
}

void ThroughPointDiaphragmLineFactory::SetDirection(const Direction& direction)
{
   m_Direction = direction;
}

const Direction& ThroughPointDiaphragmLineFactory::GetDireciton() const
{
   return m_Direction;
}

void ThroughPointDiaphragmLineFactory::SetDiaphragmLineID(IDType id)
{
   m_ID = id;
}

IDType ThroughPointDiaphragmLineFactory::GetDiaphragmLineID() const
{
   return m_ID;
}

void ThroughPointDiaphragmLineFactory::IsStaggered(bool bIsStaggered)
{
   m_bIsStaggered = bIsStaggered;
}

bool ThroughPointDiaphragmLineFactory::IsStaggered() const
{
   return m_bIsStaggered;
}

void ThroughPointDiaphragmLineFactory::SetGirderLineID(SideType side, IDType id)
{
   m_GirderLineID[+side] = id;
}

IDType ThroughPointDiaphragmLineFactory::GetGirderLineID(SideType side) const
{
   return m_GirderLineID[+side];
}

std::vector<std::shared_ptr<DiaphragmLine>> ThroughPointDiaphragmLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   std::vector<std::shared_ptr<DiaphragmLine>> diaphragm_lines;

   WBFL::Geometry::Line2d line(m_Point, WBFL::Geometry::Vector2d(1.0, m_Direction));
   auto diaphragm_line = DiaphragmLine::Create(bridge, m_ID, m_GirderLineID[+SideType::Left], m_GirderLineID[+SideType::Right], m_bIsStaggered, line);
   diaphragm_lines.emplace_back(diaphragm_line);
   return diaphragm_lines;
}

#if defined _UNITTEST
bool ThroughPointDiaphragmLineFactory::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ThroughPointDiaphragmLineFactory");

   TESTME_EPILOG("ThroughPointDiaphragmLineFactory");
}
#endif // _UNITTEST


