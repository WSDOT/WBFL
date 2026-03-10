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
#include <DManip/DimensionLine.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include "Helpers.h"
#include "LineHitTest.h"

using namespace WBFL::DManip;

std::shared_ptr<DimensionLine> DimensionLine::Create(IDType id)
{
   auto line = std::shared_ptr<DimensionLine>(new DimensionLine(id));
   line->Init();
   return line;
}

DimensionLine::DimensionLine(IDType id) : DisplayObjectDefaultImpl(id)
{
   SetSelectionType(SelectionType::None);
}

void DimensionLine::Init()
{
   SetConnectorParent(weak_from_this());
   m_EventRelay = NestedDisplayObjectEventRelay::Create(this);
}

DimensionLine::~DimensionLine()
{
   if (m_TextBlock)
   {
      m_TextBlock->UnregisterEventSink();
      m_TextBlock.reset();
   }
}

void DimensionLine::SetDisplayList(std::weak_ptr<iDisplayList> pDL)
{
   __super::SetDisplayList(pDL);

   if ( m_TextBlock )
      m_TextBlock->SetDisplayList(pDL);
}

void DimensionLine::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   UpdateWorkPoints();

   // Draw the left witness line
   pDC->MoveTo(m_ptA);
   pDC->LineTo(m_ptB);

   // Draw the Right witness line
   pDC->MoveTo(m_ptD);
   pDC->LineTo(m_ptE);

   // Draw dimension line
   pDC->MoveTo(m_ptC);
   pDC->LineTo(m_ptF);

   // Draw arrow heads
   DrawArrowHead(pDC,m_Style,m_StartArrow.left,m_StartArrow.tip,m_StartArrow.right);
   DrawArrowHead(pDC,m_Style,m_EndArrow.left,m_EndArrow.tip,m_EndArrow.right);

   if ( m_TextBlock )
      m_TextBlock->Draw(pDC);
}

void DimensionLine::Highlight(CDC* pDC,bool bHighlight)
{
   Draw(pDC);
}

bool DimensionLine::HitTest(const POINT& point) const
{
   UpdateWorkPoints();

   if ( m_TextBlock && m_TextBlock->HitTest(point) )
      return true;

   if ( m_pGravityWellStrategy )
   {
      // Use the default strategy
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

WBFL::Geometry::Rect2d DimensionLine::GetBoundingBox() const
{
   UpdateWorkPoints();

   CRect r(m_ptA,m_ptA);
   IncludePointInRect(m_ptB,&r);
   IncludePointInRect(m_ptC,&r);
   IncludePointInRect(m_ptD,&r);
   IncludePointInRect(m_ptE,&r);
   IncludePointInRect(m_ptF,&r);
   IncludePointInRect(m_ptZ,&r);
   IncludePointInRect(m_StartArrow.tip,&r);
   IncludePointInRect(m_StartArrow.left,&r);
   IncludePointInRect(m_StartArrow.right,&r);
   IncludePointInRect(m_EndArrow.tip,&r);
   IncludePointInRect(m_EndArrow.left,&r);
   IncludePointInRect(m_EndArrow.right,&r);

   if ( m_TextBlock )
   {
      CRect box = m_TextBlock->GetLogicalBoundingBox();
      r.NormalizeRect();
      box.NormalizeRect();
      r.UnionRect(&r,&box);
   }

   // convert to world
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   Float64 left,top, right, bottom;
   map->LPtoWP(r.left, r.top, &left, &top);
   map->LPtoWP(r.right, r.bottom, &right, &bottom);

   return { Min(left,right), Min(top,bottom), Max(left,right), Max(top,bottom) };
}

std::_tstring DimensionLine::GetToolTipText() const
{
   auto strMyTip = __super::GetToolTipText();
   if ( strMyTip.empty() && m_TextBlock)
      return m_TextBlock->GetToolTipText();
   else
      return strMyTip;
}

void DimensionLine::SetMaxTipWidth(INT maxWidth)
{ 
   if ( m_TextBlock )
      m_TextBlock->SetMaxTipWidth(maxWidth);
   else
      __super::SetMaxTipWidth(maxWidth); 
}

INT DimensionLine::GetMaxTipWidth() const
{
   INT width = __super::GetMaxTipWidth();
   if ( m_TextBlock )
      return m_TextBlock->GetMaxTipWidth();
   else
      return width;
}

void DimensionLine::SetTipDisplayTime(INT iTime)
{
   if ( m_TextBlock )
      m_TextBlock->SetTipDisplayTime(iTime);
   else
      __super::SetTipDisplayTime(iTime); 
}

INT DimensionLine::GetTipDisplayTime() const
{
   if ( m_TextBlock )
      return m_TextBlock->GetTipDisplayTime();
   else
      return __super::GetTipDisplayTime();
}

bool DimensionLine::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      m_TextBlock->OnKeyDown(nChar,nRepCnt,nFlags);
      return true;
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnContextMenu(CWnd* pWnd,const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      m_TextBlock->OnContextMenu(pWnd,point);
      return true;
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnLButtonDown(UINT nFlags, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnLButtonDown(nFlags,point);
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnLButtonUp(UINT nFlags, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnLButtonUp(nFlags,point);
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnLButtonDblClk(UINT nFlags, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnLButtonDblClk(nFlags,point);
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnRButtonDown(UINT nFlags, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnRButtonDown(nFlags,point);
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnRButtonUp(UINT nFlags, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnRButtonUp(nFlags,point);
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnRButtonDblClk(UINT nFlags, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnRButtonDblClk(nFlags,point);
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnMouseMove(UINT nFlags, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnMouseMove(nFlags,point);
   }
   else
   {
      return false;
   }
}

bool DimensionLine::OnMouseWheel(UINT nFlags,short zDelta, const POINT& point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnMouseWheel(nFlags,zDelta,point);
   }
   else
   {
      return false;
   }
}

/////////////////////////////////////////////////////////
// iDimensionLine Implementation
void DimensionLine::SetAngle(Float64 angle)
{
   m_Angle = angle;
   m_bAlignWithPlugs = FALSE;
}

Float64 DimensionLine::GetAngle() const
{
   return m_Angle;
}

LONG DimensionLine::GetHiddenWitnessLength() const
{
   return m_HiddenWitnessLength;
}

void DimensionLine::SetHiddenWitnessLength(LONG l)
{
   m_HiddenWitnessLength = l;
}

void DimensionLine::SetWitnessLength(LONG l)
{
   m_LenWitness = l;
}

LONG DimensionLine::GetWitnessLength() const
{
   return m_LenWitness;
}

void DimensionLine::SetWitnessOffset(LONG wOffset)
{
   m_WitnessOffset = wOffset;
}

LONG DimensionLine::GetWitnessOffset() const
{
   return m_WitnessOffset;
}

void DimensionLine::SetArrowHeadSize(CSize size)
{
   m_ArrowWidth = size.cx;
   m_ArrowHeight = size.cy;
}

CSize DimensionLine::GetArrowHeadSize() const
{
   return CSize(m_ArrowWidth,m_ArrowHeight);
}

void DimensionLine::SetArrowHeadStyle(DManip::ArrowHeadStyleType style)
{
   m_Style = style;
}

ArrowHeadStyleType DimensionLine::GetArrowHeadStyle() const
{
   return m_Style;
}

void DimensionLine::EnableAutoText(bool bEnable)
{
   m_bAutoText = bEnable;
}

bool DimensionLine::IsAutoTextEnabled() const
{
   return m_bAutoText;
}

void DimensionLine::SetTextBlock(std::shared_ptr<iTextBlock> pTextBlock)
{
   if ( m_TextBlock )
   {
      m_TextBlock->UnregisterEventSink();
      m_TextBlock = nullptr;
   }

   m_TextBlock = pTextBlock;
   if ( m_TextBlock )
   {
      m_TextBlock->SetDisplayList(GetDisplayList());
      m_TextBlock->RegisterEventSink(m_EventRelay);
   }
}

std::shared_ptr<iTextBlock> DimensionLine::GetTextBlock()
{
   return m_TextBlock;
}

std::shared_ptr<const iTextBlock> DimensionLine::GetTextBlock() const
{
   return m_TextBlock;
}

/////////////////////
void DimensionLine::UpdateWorkPoints() const
{
   // note that work points are in logical units
   auto pStartPoint = GetStartPoint();
   auto pEndPoint = GetEndPoint();

   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   // determine number of logial units/twip in x and y
   LONG dotx, doty, dptx, dpty;
   map->TPtoLP(0,0,&dotx, &doty);
   map->TPtoLP(14400,14400,&dptx, &dpty);
   Float64 stx = fabs(Float64(dotx-dptx))/14400.;  // scale factor
   Float64 sty = fabs(Float64(doty-dpty))/14400.;

   map->WPtoLP(pStartPoint,&m_ptStart.x,&m_ptStart.y);
   map->WPtoLP(pEndPoint,&m_ptEnd.x,&m_ptEnd.y);

   Float64 angle = m_Angle;
   if ( m_bAlignWithPlugs )
   {
      auto size = pEndPoint - pStartPoint;
      angle = atan2(size.Dy(), size.Dx());
   }

   // Determine the angle and length of the dimension line
   Float64 c = cos(angle);
   Float64 s = sin(angle);

   // things must be flipped around if witness length is negative
   Float64 fw = m_LenWitness<0.0 ? -1 : 1;

   // Left witness line
   //

   // Start of Witness Line
   m_ptA.x = m_ptStart.x - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*s*stx*fw);
   m_ptA.y = m_ptStart.y - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*c*sty*fw);

   // End of Witness Line
   m_ptB.x = m_ptStart.x - (LONG)(m_LenWitness*s*stx);
   m_ptB.y = m_ptStart.y - (LONG)(m_LenWitness*c*sty);


   // Right witness line
   //

   // Determine the amount to extend the right witness line
   // Find the point on the line between ptStart and angle
   // that is nearest ptEnd.
   WBFL::Geometry::Point2d p(m_ptStart.x, -m_ptStart.y);
   WBFL::Geometry::Vector2d v(1.0, angle);
   WBFL::Geometry::Line2d line(p, v);

   WBFL::Geometry::Point2d p3(m_ptEnd.x, -m_ptEnd.y);
   auto p4 = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, p3);

   auto [zx, zy] = p4.GetLocation();
   m_ptZ.x = (LONG)(zx);
   m_ptZ.y = (LONG)(-zy);

   CSize extension = m_ptZ - m_ptEnd;

   // Start of Witness Line
   m_ptD.x = m_ptEnd.x - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*s*stx*fw);
   m_ptD.y = m_ptEnd.y - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*c*sty*fw);

   // End of Witness Line
   m_ptE.x = m_ptEnd.x + extension.cx - (LONG)(m_LenWitness*s*stx);
   m_ptE.y = m_ptEnd.y - extension.cy - (LONG)(m_LenWitness*c*sty);

   // Dimension line
   //

   // Start of dimension line (left side)
   m_ptC.x = m_ptStart.x - (LONG)((m_LenWitness - m_DimOffset*fw)*s*stx);
   m_ptC.y = m_ptStart.y - (LONG)((m_LenWitness - m_DimOffset*fw)*c*sty);

   // End of dimension line (right side)
   m_ptF.x = m_ptEnd.x + extension.cx - (LONG)((m_LenWitness - m_DimOffset*fw)*s*stx);
   m_ptF.y = m_ptEnd.y - extension.cy - (LONG)((m_LenWitness - m_DimOffset*fw)*c*sty);

   UpdateArrowHeads(stx, sty);
   UpdateTextBlock();
}

void DimensionLine::UpdateArrowHeads(Float64 stx, Float64 sty) const
{
   CSize dl = m_ptF - m_ptC;
   Float64 angle = atan2((Float64)dl.cy,(Float64)dl.cx);

   m_StartArrow.tip = m_ptC;
   m_StartArrow.left.x = m_StartArrow.tip.x  + (LONG)((m_ArrowHeight*cos(angle) + m_ArrowWidth/2*sin(angle))*stx);
   m_StartArrow.left.y = m_StartArrow.tip.y  + (LONG)((m_ArrowHeight*sin(angle) - m_ArrowWidth/2*cos(angle))*sty);
   m_StartArrow.right.x = m_StartArrow.tip.x + (LONG)((m_ArrowHeight*cos(angle) - m_ArrowWidth/2*sin(angle))*stx);
   m_StartArrow.right.y = m_StartArrow.tip.y + (LONG)((m_ArrowHeight*sin(angle) + m_ArrowWidth/2*cos(angle))*sty);

   m_EndArrow.tip = m_ptF;
   m_EndArrow.left.x = m_EndArrow.tip.x  - (LONG)((m_ArrowHeight*cos(angle) - m_ArrowWidth/2*sin(angle))*stx);
   m_EndArrow.left.y = m_EndArrow.tip.y  - (LONG)((m_ArrowHeight*sin(angle) + m_ArrowWidth/2*cos(angle))*sty);
   m_EndArrow.right.x = m_EndArrow.tip.x - (LONG)((m_ArrowHeight*cos(angle) + m_ArrowWidth/2*sin(angle))*stx);
   m_EndArrow.right.y = m_EndArrow.tip.y - (LONG)((m_ArrowHeight*sin(angle) - m_ArrowWidth/2*cos(angle))*sty);
}

void DimensionLine::UpdateTextBlock() const
{
   if ( m_TextBlock == 0 )
      return;

   // Update position
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   // put the text block above the arrowheads
   Float64 x1,y1;
   map->LPtoWP(m_StartArrow.right.x,m_StartArrow.right.y,&x1,&y1);

   Float64 x2,y2;
   map->LPtoWP(m_EndArrow.left.x,m_EndArrow.left.y,&x2,&y2);

   WBFL::Geometry::Point2d loc;
   loc.Move(0.5*(x1+x2),0.5*(y1+y2));
   m_TextBlock->SetPosition(loc);
   m_TextBlock->SetTextAlign(TA_BOTTOM | TA_CENTER);

   // Compute the angle of the text
   CSize delta = m_ptF - m_ptC;
   Float64 angle = atan(-(Float64)delta.cy/(Float64)delta.cx);

   LONG lAngle = (LONG)(1800.0*angle/M_PI); // tenth of a degree
   m_TextBlock->SetAngle(lAngle);

   if ( m_bAutoText )
   {
      auto start = GetStartPoint();
      auto end = GetEndPoint();

      auto dist = start.Distance(end);

      CString strDist;
      strDist.Format(_T("%f"),dist);

      m_TextBlock->SetText(strDist);
   }
}

void DimensionLine::IncludePointInRect(CPoint p,CRect* pRect) const
{
   if ( p.x < pRect->left )
      pRect->left = p.x;

   if ( pRect->right < p.x )
      pRect->right = p.x;

   if ( p.y < pRect->top )
      pRect->top = p.y;

   if ( pRect->bottom < p.y )
      pRect->bottom = p.y;
}

//////////////////////////////////

WBFL::Geometry::Point2d DimensionLine::GetStartPoint() const
{
   return GetStartPlug()->GetSocket()->GetPosition();
}

WBFL::Geometry::Point2d DimensionLine::GetEndPoint() const
{
   return GetEndPlug()->GetSocket()->GetPosition();
}
