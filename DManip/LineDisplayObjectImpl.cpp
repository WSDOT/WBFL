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
#include <DManip/LineDisplayObjectImpl.h>
#include <DManip/DrawLineStrategy.h>
#include <DManip/DisplayMgr.h>
#include "LineHitTest.h"

using namespace WBFL::DManip;

LineDisplayObject::LineDisplayObject(IDType id) : iLineDisplayObject(id)
{
}


bool LineDisplayObject::HitTest(const POINT& point) const
{
   if ( m_pGravityWellStrategy )
   {
      // If there is a gravity well, use the default hit test implementation
      return __super::HitTest(point);
   }
   else
   {
      // otherwise, use this strategy
      auto start = GetStartPoint();
      auto end = GetEndPoint();
      return LineHitTest::HitTest(this,start,end,point);
   }

   return FALSE;
}

void LineDisplayObject::Draw(CDC* pDC)
{
   if (!IsVisible()) return; // don't draw if not visible

   if (m_DrawStrategy)
   {
      auto dispObj = std::dynamic_pointer_cast<iLineDisplayObject>(shared_from_this());
      m_DrawStrategy->Draw(dispObj, pDC);
   }
}

void LineDisplayObject::Highlight(CDC* pDC, bool bHighlight)
{
   if (!IsVisible()) return; // don't draw if not visible

   if (m_DrawStrategy)
   {
      auto dispObj = std::dynamic_pointer_cast<iLineDisplayObject>(shared_from_this());
      m_DrawStrategy->DrawHighlight(dispObj, pDC, bHighlight);
   }
}


WBFL::Geometry::Rect2d LineDisplayObject::GetBoundingBox() const
{
   if ( m_DrawStrategy )
   {
      auto line_display_object = std::dynamic_pointer_cast<const iLineDisplayObject>(shared_from_this());
      return m_DrawStrategy->GetBoundingBox(line_display_object);
   }
   else
   {
      // the end points of this line are in Model Space
      // the need to be converted to World Space for the bounding box


      // start by getting the coordinate mapper
      auto display_list = GetDisplayList();
      auto display_mgr = display_list->GetDisplayMgr();
      auto map = display_mgr->GetCoordinateMap();

      // get the points
      auto start = GetStartPoint();
      auto end = GetEndPoint();

      // convert them to world space
      auto world_start = map->MPtoWP(start);
      auto world_end = map->MPtoWP(end);
      auto [sx, sy] = world_start.GetLocation();
      auto [ex, ey] = world_end.GetLocation();

      WBFL::Geometry::Rect2d bounding_box(Min(sx, ex), Min(sy, ey), Max(sx, ex), Max(sy, ey));
      return bounding_box;
   }
}

/////////////////////////////////////////////////////////
// iLineDisplayObject Implementation
/////////////////////////////////////////////////////////

void LineDisplayObject::SetDrawLineStrategy(std::shared_ptr<iDrawLineStrategy> pStrategy)
{
   m_DrawStrategy = pStrategy;

   // If the drawing strategy implements a gravity well, use it.
   auto gravity_well = std::dynamic_pointer_cast<iGravityWellStrategy>(pStrategy);
   if ( gravity_well )
      SetGravityWellStrategy(gravity_well);
}

std::shared_ptr<iDrawLineStrategy> LineDisplayObject::GetDrawLineStrategy()
{
   return m_DrawStrategy;
}

std::pair<CPoint,CPoint> LineDisplayObject::GetLogicalEndPoints() const
{
   auto [start, end] = GetEndPoints(); // world coordinate end points

   auto pDL = GetDisplayList();
   auto dispMgr = pDL->GetDisplayMgr();
   auto map = dispMgr->GetCoordinateMap();

   CPoint logical_start;
   map->WPtoLP(start,&logical_start.x,&logical_start.y);

   CPoint logical_end;
   map->WPtoLP(end,&logical_end.x,&logical_end.y);

   return { logical_start,logical_end };
}

std::pair<WBFL::Geometry::Point2d,WBFL::Geometry::Point2d> LineDisplayObject::GetEndPoints() const
{
   return { GetStartPoint(), GetEndPoint() };
}

//////////////////////////////////

WBFL::Geometry::Point2d LineDisplayObject::GetStartPoint() const
{
   auto plug = GetStartPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}

WBFL::Geometry::Point2d LineDisplayObject::GetEndPoint() const
{
   auto plug = GetEndPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}
