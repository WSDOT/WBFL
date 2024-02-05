///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include "pch.h"
#include "LineHitTest.h"
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/DisplayObject.h>
#include <Math.h>

using namespace WBFL::DManip;

bool LineHitTest::HitTest(const iDisplayObject* pDO, WBFL::Geometry::Point2d s, WBFL::Geometry::Point2d e, const POINT& point)
{
   auto display_list = pDO->GetDisplayList();
   auto display_mgr = display_list->GetDisplayMgr();
   auto map = display_mgr->GetCoordinateMap();

   // Determine the angle of the line
   auto [sx, sy] = s.GetLocation();
   auto [ex, ey] = e.GetLocation();

   Float64 angle = atan2(ey-sy,ex-sx);

   // Rotate end point so that it is on the X-axis and to the right of the start point
   e.Rotate(s, -angle);
   
   auto [rex, rey] = e.GetLocation();

   // convert start and end in to logical space
   auto world_start = map->MPtoWP(s);
   auto world_end = map->MPtoWP(e);

   CPoint start, end;
   map->WPtoLP(world_start,&start.x,&start.y);
   map->WPtoLP(world_end,  &end.x,  &end.y);

   CRect box(start,end);
   box.InflateRect(0,4);

   CPoint testPoint;
   testPoint.x = LONG( (point.x - start.x) * cos(-angle) + (point.y - start.y) * sin(-angle) + start.x);
   testPoint.y = LONG(-(point.y - start.y) * cos(-angle) + (point.x - start.x) * sin(-angle) + start.y);

   return box.PtInRect(testPoint);
}
