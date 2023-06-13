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
#include <CoordGeom/SimpleDeckBoundaryFactory.h>

using namespace WBFL::COGO;

void SimpleDeckBoundaryFactory::SetTransverseEdgeID(EndType endType, IDType id)
{
   m_TransverseEdgeID[+endType] = id;
}

IDType SimpleDeckBoundaryFactory::GetTransverseEdgeID(EndType endType) const
{
   return m_TransverseEdgeID[+endType];
}

void SimpleDeckBoundaryFactory::SetTransverseEdgeType(EndType endType, TransverseEdgeType type)
{
   m_TransverseEdgeType[+endType] = type;
}

TransverseEdgeType SimpleDeckBoundaryFactory::GetTransverseEdgeType(EndType endType) const
{
   return m_TransverseEdgeType[+endType];
}

void SimpleDeckBoundaryFactory::SetEdgeID(SideType sideType, IDType id)
{
   m_EdgeID[+sideType] = id;
}

IDType SimpleDeckBoundaryFactory::GetEdgeID(SideType sideType)
{
   return m_EdgeID[+sideType];
}

void SimpleDeckBoundaryFactory::SetEdgeBreakID(SideType sideType, IDType id)
{
   m_EdgeBreakID[+sideType] = id;
}

IDType SimpleDeckBoundaryFactory::GetEdgeBreakID(SideType sideType)
{
   return m_EdgeBreakID[+sideType];
}

void SimpleDeckBoundaryFactory::SetBreakEdge(EndType endType, SideType sideType, bool bBreak)
{
   m_bBreakEdge[+endType][+sideType] = bBreak;
}

bool SimpleDeckBoundaryFactory::GetBreakEdge(EndType endType, SideType sideType) const
{
   return m_bBreakEdge[+endType][+sideType];
}

std::shared_ptr<DeckBoundary> SimpleDeckBoundaryFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   return DeckBoundary::Create(bridge, m_TransverseEdgeID, m_TransverseEdgeType, m_EdgeID, m_EdgeBreakID, m_bBreakEdge);
}

#if defined _UNITTEST
bool SimpleDeckBoundaryFactory::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SimpleDeckBoundaryFactory");

   TESTME_EPILOG("SimpleDeckBoundaryFactory");
}
#endif // _UNITTEST


