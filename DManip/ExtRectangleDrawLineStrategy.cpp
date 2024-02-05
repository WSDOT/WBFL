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
#include <DManip/ExtRectangleDrawLineStrategy.h>
#include <DManip/LineDisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/Connections.h>
#include <Colors.h>
#include "Helpers.h"

using namespace WBFL::DManip;


void ExtRectangleDrawLineStrategy::Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const
{
   CPoint p1, p2, p3, p4;
   GetDrawRect(pDO,&p1,&p2,&p3,&p4);

   auto display_list = pDO->GetDisplayList();
   auto display_mgr = display_list->GetDisplayMgr();

   COLORREF linecolor = m_crColor;
   COLORREF fillcolor = m_crFillColor;
   if ( pDO->IsSelected() )
   {
      linecolor = display_mgr->GetSelectionLineColor();
      fillcolor = display_mgr->GetSelectionFillColor();
   }

   // draw fill first
   if (m_bFill)
   {
      CPen pen(PS_SOLID,0,linecolor);
      CPen* oldPen = pDC->SelectObject(&pen);

      CBrush brush;
      if ( pDO->IsSelected() )
         brush.CreateHatchBrush(HS_DIAGCROSS,fillcolor);
      else
         brush.CreateSolidBrush(fillcolor);

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

   DrawPerimeter(pDC, m_Style, linecolor, p1, p2, p3, p4);

//   ///////////////////// DEBUG DUMPS
//   CPoint vpOrg = pDC->GetViewportOrg();
//   CPoint wnOrg = pDC->GetWindowOrg();
//   CSize  vpExt = pDC->GetViewportExt();
//   CSize  wnExt = pDC->GetWindowExt();
//
//   TRACE("Viewport Origin:  x = %d,  y = %d\n",vpOrg.x,vpOrg.y);
//   TRACE("Viewport Extent: dx = %d, dy = %d\n",vpExt.cx,vpExt.cy);
//   TRACE("Window Origin:  x = %d,  y = %d\n",wnOrg.x,wnOrg.y);
//   TRACE("Window Extent: dx = %d, dy = %d\n",wnExt.cx,wnExt.cy);
//   CPoint p1d = p1;
//   pDC->LPtoDP(&p1d);
//   TRACE("LP x = %d, y = %d -> DP x = %d, y = %d\n",p1.x,p1.y,p1d.x,p1d.y);
}

void ExtRectangleDrawLineStrategy::DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
}

void ExtRectangleDrawLineStrategy::DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const
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

WBFL::Geometry::Rect2d ExtRectangleDrawLineStrategy::GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   WBFL::Geometry::Point2d pntTL, pntTR, pntBL, pntBR;
   GetPoints(pDO,&pntTL,&pntBL,&pntBR,&pntTR);

   auto [x, y] = pntTL.GetLocation();

   Float64 xmax,ymax,xmin,ymin;
   xmax = x;
   ymax = y;
   xmin = x;
   ymin = y;

   std::tie(x, y) = pntBL.GetLocation();
   xmax = Max(xmax,x);
   ymax = Max(ymax,y);
   xmin = Min(xmin,x);
   ymin = Min(ymin,y);

   std::tie(x, y) = pntBR.GetLocation();
   xmax = Max(xmax,x);
   ymax = Max(ymax,y);
   xmin = Min(xmin,x);
   ymin = Min(ymin,y);

   std::tie(x, y) = pntTR.GetLocation();
   xmax = Max(xmax,x);
   ymax = Max(ymax,y);
   xmin = Min(xmin,x);
   ymin = Min(ymin,y);

   return { xmin,ymin,xmax,ymax };
}

/////////////////////////////////////////////////////////
// iExtRectangleLineDrawStrategy Implementation
void ExtRectangleDrawLineStrategy::SetLeftOffset(Float64 offset)
{
   m_LeftOffset = offset;
}

Float64 ExtRectangleDrawLineStrategy::GetLeftOffset() const
{
   return m_LeftOffset;
}

void ExtRectangleDrawLineStrategy::SetRightOffset(Float64 offset)
{
   m_RightOffset = offset;
}

Float64 ExtRectangleDrawLineStrategy::GetRightOffset() const
{
   return m_RightOffset;
}

void ExtRectangleDrawLineStrategy::SetStartExtension(Float64 ext)
{
   m_StartExtension = ext;
}

Float64 ExtRectangleDrawLineStrategy::GetStartExtension() const
{
   return m_StartExtension;
}

void ExtRectangleDrawLineStrategy::SetEndExtension(Float64 ext)
{
   m_EndExtension = ext;
}

Float64 ExtRectangleDrawLineStrategy::GetEndExtension() const
{
   return m_EndExtension;
}

void ExtRectangleDrawLineStrategy::SetStartSkew(Float64 skew)
{
   m_StartSkew = skew;
}

Float64 ExtRectangleDrawLineStrategy::GetStartSkew() const
{
   return m_StartSkew;
}

void ExtRectangleDrawLineStrategy::SetEndSkew(Float64 skew)
{
   m_EndSkew = skew;
}

Float64 ExtRectangleDrawLineStrategy::GetEndSkew() const
{
   return m_EndSkew;
}

void ExtRectangleDrawLineStrategy::SetLineWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

UINT ExtRectangleDrawLineStrategy::GetLineWidth() const
{
   return m_nWidth;
}

void ExtRectangleDrawLineStrategy::SetColor(COLORREF crColor)
{
   m_crColor = crColor;
}

COLORREF ExtRectangleDrawLineStrategy::GetColor() const
{
   return m_crColor;
}

void ExtRectangleDrawLineStrategy::SetFillColor(COLORREF crColor)
{
   m_crFillColor = crColor;
}

COLORREF ExtRectangleDrawLineStrategy::GetFillColor() const
{
   return m_crFillColor;
}

void ExtRectangleDrawLineStrategy::Fill(bool fill)
{
   m_bFill = fill;
}

bool ExtRectangleDrawLineStrategy::Fill() const
{
   return m_bFill;
}

void ExtRectangleDrawLineStrategy::SetLineStyle(LineStyleType style)
{
   m_Style = style;
}

LineStyleType ExtRectangleDrawLineStrategy::GetLineStyle() const
{
   return m_Style;
}

void ExtRectangleDrawLineStrategy::PerimeterGravityWell(bool bPerimeterGravityWell)
{
   m_bPerimeterGravityWell = bPerimeterGravityWell;
}

/////////////////////////////////////////////////////////
// iGravityWellStrategy Implementation
void ExtRectangleDrawLineStrategy::GetGravityWell(std::shared_ptr<const iDisplayObject> pDO,CRgn* pRgn)
{
   auto line = std::dynamic_pointer_cast<const iLineDisplayObject>(pDO);

   CPoint p[4];
   GetDrawRect(line,&p[0],&p[1],&p[2],&p[3]);

   VERIFY(pRgn->CreatePolygonRgn(p,4,ALTERNATE));
}

/////////////////////////////////

WBFL::Geometry::Point2d ExtRectangleDrawLineStrategy::GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetStartPlug();
   return plug->GetSocket()->GetPosition();
}

WBFL::Geometry::Point2d ExtRectangleDrawLineStrategy::GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetEndPlug();
   return plug->GetSocket()->GetPosition();
}

void ExtRectangleDrawLineStrategy::GetPoints(std::shared_ptr<const iLineDisplayObject> pDO,WBFL::Geometry::Point2d* pntTopLeft, WBFL::Geometry::Point2d* pntBottomLeft, WBFL::Geometry::Point2d* pntBottomRight, WBFL::Geometry::Point2d* pntTopRight) const
{
   // This function returns the points in World Space

   // start by getting the points in model space
   auto [pntStart,pntEnd] = pDO->GetEndPoints();

   auto delta = pntEnd - pntStart;

   Float64 angle = atan2(delta.Dy(), delta.Dx());

   // start extension, left side
   Float64 SELx = pntStart.X() - m_StartExtension * cos(angle) - (m_LeftOffset / cos(m_StartSkew)) * cos(angle + m_StartSkew + PI_OVER_2);
   Float64 SELy = pntStart.Y() - m_StartExtension * sin(angle) - (m_LeftOffset / cos(m_StartSkew)) * sin(angle + m_StartSkew + PI_OVER_2);
   
   // start extension, right side
   Float64 SERx = pntStart.X() - m_StartExtension * cos(angle) + (m_RightOffset / cos(m_StartSkew)) * cos(angle + m_StartSkew + PI_OVER_2);
   Float64 SERy = pntStart.Y()  - m_StartExtension * sin(angle) + (m_RightOffset / cos(m_StartSkew)) * sin(angle + m_StartSkew + PI_OVER_2);

   // end extension, left side
   Float64 EELx = pntEnd.X() + m_EndExtension * cos(angle) - (m_LeftOffset / cos(m_EndSkew)) * cos(angle + m_EndSkew + PI_OVER_2);
   Float64 EELy = pntEnd.Y() + m_EndExtension * sin(angle) - (m_LeftOffset / cos(m_EndSkew)) * sin(angle + m_EndSkew + PI_OVER_2);

   // end extension, right side
   Float64 EERx = pntEnd.X() + m_EndExtension*cos(angle) + (m_RightOffset/cos(m_EndSkew))*cos(angle+m_EndSkew+PI_OVER_2);
   Float64 EERy = pntEnd.Y() + m_EndExtension*sin(angle) + (m_RightOffset/cos(m_EndSkew))*sin(angle+m_EndSkew+PI_OVER_2);

   //
   // Map the Model space points into World Space
   //

   // first we need the coordinate mapper
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   map->MPtoWP(SELx,SELy,&SELx,&SELy);
   map->MPtoWP(SERx,SERy,&SERx,&SERy);
   map->MPtoWP(EELx,EELy,&EELx,&EELy);
   map->MPtoWP(EERx,EERy,&EERx,&EERy);

   // this points are all in world space
   pntTopLeft->Move(SELx,SELy);
   pntBottomLeft->Move(SERx,SERy);
   pntBottomRight->Move(EERx,EERy);
   pntTopRight->Move(EELx,EELy);
}

void ExtRectangleDrawLineStrategy::GetDrawRect(std::shared_ptr<const iLineDisplayObject> pDO,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4) const
{
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   WBFL::Geometry::Point2d pntTL, pntTR, pntBL, pntBR;
   GetPoints(pDO,&pntTL,&pntBL,&pntBR,&pntTR); // these points are in world coordinates

   map->WPtoLP(pntTL,&(p1->x),&(p1->y));
   map->WPtoLP(pntBL,&(p2->x),&(p2->y));
   map->WPtoLP(pntBR,&(p3->x),&(p3->y));
   map->WPtoLP(pntTR,&(p4->x),&(p4->y));
}

void ExtRectangleDrawLineStrategy::DrawPerimeter(CDC* pDC, LineStyleType lineStyle, COLORREF color, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4) const
{
   CPen pen;
   CreatePen(lineStyle, m_nWidth, color, pen);
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

