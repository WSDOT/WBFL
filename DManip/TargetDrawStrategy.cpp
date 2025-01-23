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
#include <DManip/TargetDrawStrategy.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/PointDisplayObject.h>
#include <Colors.h>

using namespace WBFL::DManip;

void TargetDrawStrategy::SetRadius(LONG radius)
{
   m_Radius = radius;
}

LONG TargetDrawStrategy::GetRadius() const
{
   return m_Radius;
}

void TargetDrawStrategy::SetFgColor(COLORREF crColor)
{
   m_FgColor = crColor;
}

COLORREF TargetDrawStrategy::GetFgColor() const
{
   return m_FgColor;
}

void TargetDrawStrategy::SetBgColor(COLORREF crColor)
{
   m_BgColor = crColor;
}

COLORREF TargetDrawStrategy::GetBgColor() const
{
   return m_BgColor;
}

void TargetDrawStrategy::Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC) const
{
   if ( pDO->IsSelected() )
      m_Color = pDO->GetDisplayList()->GetDisplayMgr()->GetSelectionLineColor();
   else
      m_Color = m_FgColor;

   DrawMe(pDO,pDC);
}

void TargetDrawStrategy::DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,bool bHighlight) const
{
   m_Color = LIME;
   DrawMe(pDO,pDC);
}

void TargetDrawStrategy::DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
   m_CachePoint = map->LPtoWP(dragPoint.x, dragPoint.y);
   m_Color = BLUE;
   DrawMe(pDO,pDC);
}

WBFL::Geometry::Rect2d TargetDrawStrategy::GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   const auto& point = pDO->GetPosition();

   auto [px, py] = point.GetLocation();

   // make 4x4 logical size
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   Float64 xo,yo;
   map->LPtoWP(0,0,&xo,&yo);
   Float64 x2,y2;
   map->LPtoWP(m_Radius,m_Radius,&x2,&y2);

   Float64 wid = fabs(x2-xo);
   Float64 hgt = fabs(y2-yo);

   return { (px - wid),(py - hgt),(px + wid),(py + hgt) };
}

void TargetDrawStrategy::DrawMe(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC) const
{
   CRect rect = pDO->GetLogicalBoundingBox();

   // Draw the background
   CPen bgpen(PS_SOLID,1,m_BgColor);
   CPen* pOldPen = pDC->SelectObject(&bgpen);

   CBrush bgbrush(m_BgColor);
   CBrush* pOldBrush = pDC->SelectObject(&bgbrush);

   pDC->Ellipse(rect);

   // Draw the foreground
   CPen fgpen(PS_SOLID,1,m_Color);
   CBrush fgbrush(m_Color);

   pDC->SelectObject(&fgpen);
   pDC->SelectObject(&fgbrush);

   CPoint center = rect.CenterPoint();
   pDC->Pie(rect.left,rect.top, rect.right, rect.bottom, center.x, rect.top,    rect.left,  center.y);
   pDC->Pie(rect.left,rect.top, rect.right, rect.bottom, center.x, rect.bottom, rect.right, center.y);

   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}
