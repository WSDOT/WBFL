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
#include <DManip/RectangleDrawLineStrategy.h>
#include <DManip/LineDisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include <DManip/Connections.h>
#include <Colors.h>
#include "DManipDebug.h"
#include "Helpers.h"

using namespace WBFL::DManip;

void RectangleDrawLineStrategy::Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const
{
   CPoint p1, p2, p3, p4;
   GetDrawRect(pDO,&p1,&p2,&p3,&p4);

   auto disp_mgr = pDO->GetDisplayList()->GetDisplayMgr();

   // draw fill first
   if (m_bFill)
   {
      COLORREF fill_color = pDO->IsSelected() ? disp_mgr->GetSelectionFillColor() : m_crFillColor;
      CPen pen(PS_SOLID,0,fill_color);
      CPen* oldPen = pDC->SelectObject(&pen);

      CBrush brush;
      if ( pDO->IsSelected() )
      {
         brush.CreateHatchBrush(HS_DIAGCROSS,fill_color);
      }
      else
      {
         brush.CreateSolidBrush(fill_color);
      }
      CBrush* oldBrush = pDC->SelectObject(&brush);

      POINT points[4];
      points[0] = p1;
      points[1] = p2;
      points[2] = p3;
      points[3] = p4;

      pDC->Polygon(points, 4);

      pDC->SelectObject(oldPen);
      pDC->SelectObject(&oldBrush);
   }

   COLORREF color = m_crColor;
   if ( pDO->IsSelected() )
      color = disp_mgr->GetSelectionLineColor();

   DrawPerimeter(pDC, m_Style, color, p1, p2, p3, p4);

   ///////////////////// DEBUG DUMPS
   CPoint vpOrg = pDC->GetViewportOrg();
   CPoint wnOrg = pDC->GetWindowOrg();
   CSize  vpExt = pDC->GetViewportExt();
   CSize  wnExt = pDC->GetWindowExt();

   WATCHX(DManip,1,_T("Viewport Origin:  x = ") << vpOrg.x  << _T(" y = ") << vpOrg.y);
   WATCHX(DManip,1,_T("Viewport Extent:  x = ") << vpExt.cx << _T(" y = ") << vpExt.cy);
   WATCHX(DManip,1,_T("Window   Origin:  x = ") << wnOrg.x  << _T(" y = ") << wnOrg.y);
   WATCHX(DManip,1,_T("Window   Extent:  x = ") << wnExt.cx << _T(" y = ") << wnExt.cy);
   CPoint p1d = p1;
   pDC->LPtoDP(&p1d);
   WATCHX(DManip,1,_T("LP x = ") << p1.x << _T(" y = ") << p1.y << _T(" -> DP x = ") << p1d.x << _T(" y = ") << p1d.y);
}

void RectangleDrawLineStrategy::DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
}

void RectangleDrawLineStrategy::DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const
{
   CPoint p1, p2, p3, p4;
   GetDrawRect(pDO,&p1,&p2,&p3,&p4);

   if ( bHighlight )
   {
      DrawPerimeter(pDC, LineStyleType::Solid, ORANGE1, p1, p2, p3, p4);
   }
   else
   {
      DrawPerimeter(pDC, m_Style, m_crColor, p1, p2, p3, p4);
   }
}

WBFL::Geometry::Rect2d RectangleDrawLineStrategy::GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   WBFL::Geometry::Point2d pntTL, pntTR, pntBL, pntBR;
   GetPoints(pDO,&pntTL,&pntBL,&pntBR,&pntTR);

   auto xmin = Min(pntTL.X(), pntBL.X(), pntBR.X(), pntTR.X());
   auto ymin = Min(pntTL.Y(), pntBL.Y(), pntBR.Y(), pntTR.Y());
   auto xmax = Max(pntTL.X(), pntBL.X(), pntBR.X(), pntTR.X());
   auto ymax = Max(pntTL.Y(), pntBL.Y(), pntBR.Y(), pntTR.Y());

   return { xmin,ymin,xmax,ymax };
}

/////////////////////////////////////////////////////////
// iRectangleLineDrawStrategy Implementation
void RectangleDrawLineStrategy::SetWidth(Float64 width)
{
   m_RectWidth = width;
}

Float64 RectangleDrawLineStrategy::GetWidth() const
{
   return m_RectWidth;
}

void RectangleDrawLineStrategy::SetLineWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

UINT RectangleDrawLineStrategy::GetLineWidth() const
{
   return m_nWidth;
}

void RectangleDrawLineStrategy::SetColor(COLORREF crColor)
{
   m_crColor = crColor;
}

COLORREF RectangleDrawLineStrategy::GetColor() const
{
   return m_crColor;
}

void RectangleDrawLineStrategy::SetFillColor(COLORREF crColor)
{
   m_crFillColor = crColor;
}

COLORREF RectangleDrawLineStrategy::GetFillColor() const
{
   return m_crFillColor;
}

void RectangleDrawLineStrategy::Fill(bool fill)
{
   m_bFill = fill;
}

bool RectangleDrawLineStrategy::Fill() const
{
   return m_bFill;
}

void RectangleDrawLineStrategy::SetLineStyle(LineStyleType style)
{
   m_Style = style;
}

LineStyleType RectangleDrawLineStrategy::GetLineStyle() const
{
   return m_Style;
}

void RectangleDrawLineStrategy::PerimeterGravityWell(bool bPerimeterGravityWell)
{
   m_bPerimeterGravityWell = bPerimeterGravityWell;
}

/////////////////////////////////////////////////////////
// iGravityWellStrategy Implementation
void RectangleDrawLineStrategy::GetGravityWell(std::shared_ptr<const iDisplayObject> pDO,CRgn* pRgn)
{
   auto line = std::dynamic_pointer_cast<const iLineDisplayObject>(pDO);
   CHECK(line);

   CPoint p[4];
   GetDrawRect(line,&p[0],&p[1],&p[2],&p[3]);

   VERIFY(pRgn->CreatePolygonRgn(p,4,ALTERNATE));
}

/////////////////////////////////

WBFL::Geometry::Point2d RectangleDrawLineStrategy::GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetStartPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}

WBFL::Geometry::Point2d RectangleDrawLineStrategy::GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetEndPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}

void RectangleDrawLineStrategy::GetPoints(std::shared_ptr<const iLineDisplayObject> pDO,WBFL::Geometry::Point2d* pntTopLeft, WBFL::Geometry::Point2d* pntBottomLeft, WBFL::Geometry::Point2d* pntBottomRight, WBFL::Geometry::Point2d* pntTopRight) const
{
   auto [start, end] = pDO->GetEndPoints();

   auto size = end - start;

   Float64 angle = atan2(size.Dy(),size.Dx());

   Float64 wx = m_RectWidth*sin(angle)/2;
   Float64 wy = m_RectWidth*cos(angle)/2;

   pntTopLeft->Move(start.X()-wx,start.Y()+wy);
   pntBottomLeft->Move(start.X() + wx, start.Y() - wy);
   pntBottomRight->Move(end.X() + wx, end.Y() - wy);
   pntTopRight->Move(end.X() - wx,end.Y() + wy);
}

void RectangleDrawLineStrategy::GetDrawRect(std::shared_ptr<const iLineDisplayObject> pDO,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4) const
{
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   WBFL::Geometry::Point2d pntTL, pntTR, pntBL, pntBR;
   GetPoints(pDO,&pntTL,&pntBL,&pntBR,&pntTR);

   map->WPtoLP(pntTL,&(p1->x),&(p1->y));
   map->WPtoLP(pntBL,&(p2->x),&(p2->y));
   map->WPtoLP(pntBR,&(p3->x),&(p3->y));
   map->WPtoLP(pntTR,&(p4->x),&(p4->y));
}

void RectangleDrawLineStrategy::DrawPerimeter(CDC* pDC,LineStyleType lineStyle, COLORREF color, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4) const
{
   CPen pen;
   CreatePen(lineStyle, m_nWidth, color,pen);
   CPen* oldPen = pDC->SelectObject(&pen);

   // Draw the rectangle
   pDC->MoveTo(p1);
   pDC->LineTo(p2);
   pDC->LineTo(p3);
   pDC->LineTo(p4);
   pDC->LineTo(p1);

   // Cleanup
   pDC->SelectObject(oldPen);

}

