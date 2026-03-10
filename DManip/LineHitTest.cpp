///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

   CRect box = GetHitRect(pDO, s, e);

   return box.PtInRect(point);
}

CRect WBFL::DManip::LineHitTest::GetHitRect(const iDisplayObject* pDO, WBFL::Geometry::Point2d s, WBFL::Geometry::Point2d e)
{
   auto display_list = pDO->GetDisplayList();
   auto display_mgr = display_list->GetDisplayMgr();
   auto map = display_mgr->GetCoordinateMap();

   // convert start and end in to logical space
   auto world_start = map->MPtoWP(s);
   auto world_end = map->MPtoWP(e);

   CPoint cstart, cend;
   map->WPtoLP(world_start, &cstart.x, &cstart.y);
   map->WPtoLP(world_end, &cend.x, &cend.y);

   CRect box(cstart, cend);
   box.InflateRect(4, 4);

   return box;
}
