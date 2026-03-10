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
#include <DManip/NorthArrow.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/DisplayView.h>

#include "Helpers.h"

using namespace WBFL::DManip;

NorthArrow::NorthArrow(IDType id) : DisplayObjectDefaultImpl(id)
{
   CFont font;
   font.CreatePointFont(80,_T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfQuality = ANTIALIASED_QUALITY;
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
void NorthArrow::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   auto pView = GetDisplayList()->GetDisplayMgr()->GetView();

   //   // For debugging... Draw the gravity well
//   CComPtr<iGravityWellStrategy> strategy;
//   GetGravityWellStrategy(&strategy);
//   CRgn rgn;
//   if ( strategy )
//   {
//      strategy->GetGravityWell(this,&rgn);
//   }
//   else
//   {
//      CRect box = GetBoundingBox();
//      rgn.CreateRectRgnIndirect(&box);
//   }
//   CBrush brush;
//   brush.CreateHatchBrush(HS_DIAGCROSS,RGB(127,127,127));
//   pDC->FillRgn(&rgn,&brush);
//   // End of debug code

   CFont font;
   font.CreatePointFontIndirect(&m_Font, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(TA_TOP | TA_CENTER);
   CSize extents = pDC->GetTextExtent("North");
   LONG size = 125*extents.cx/100;

   CRect rClient = pView->GetViewRect();

   CPoint tl;
   tl.x = rClient.left;
   tl.y = rClient.top;

   // size of the north arrow box
   CPoint br(tl);
   br += CSize(size,size);

   CRect box(tl,br);

   CPoint center = box.CenterPoint();

   LONG ox = size/2;
   LONG oy = size/2;

   Float64 c = cos(m_Direction);
   Float64 s = sin(m_Direction);

   CPoint p1(center);
   p1.Offset( int(-ox*c), int(oy*s) );

   CPoint p2(center);
   p2.Offset( int(ox*c), int(-oy*s) );

   pDC->MoveTo(p1);
   pDC->LineTo(p2);

   ox /= 2;
   oy /= 2;

   CPoint p3;
   p3.x = p2.x - LONG(  ox*s + oy*c);
   p3.y = p2.y + LONG( -ox*c + oy*s);

   CPoint p4;
   p4.x = p2.x + LONG( ox*s - oy*c);
   p4.y = p2.y + LONG( ox*c + oy*s);

   DrawArrowHead(pDC,ArrowHeadStyleType::Filled,p3,p2,p4);
   
   pDC->TextOut(box.CenterPoint().x,box.bottom,"North");

   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

void NorthArrow::Highlight(CDC* pDC,bool bHighlight)
{
   Draw(pDC);
}

RECT NorthArrow::GetLogicalBoundingBox() const
{
   auto pView = GetDisplayList()->GetDisplayMgr()->GetView();
   CRect rClient;
   pView->GetClientRect(&rClient);

   CPoint p;
   p.x = rClient.left;
   p.y = rClient.top;

   
   CSize extents(0,0);

   // Find the edges of the text block
   LONG top, left, right, bottom;
   top    = p.y;
   bottom = p.y + extents.cy;
   left   = p.x - extents.cx/2;
   right  = left + extents.cx;
   CRect box(left,top,right,bottom);

   return box;
}

WBFL::Geometry::Rect2d NorthArrow::GetBoundingBox() const
{
   CRect box = GetLogicalBoundingBox(); // logical coordinates

   // map to world coordinates
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   Float64 left,right,top,bottom;
   map->LPtoWP(box.left,box.bottom,&left,&bottom);
   map->LPtoWP(box.right,box.top,&right,&top);

   return { left,bottom,top,right };
}

void NorthArrow::SetText(LPCTSTR lpszText)
{
   if ( m_strText == CString(lpszText) )
      return;

   m_strText = lpszText;

   auto display_list = GetDisplayList();

   if ( display_list )
   {
      auto display_mgr = display_list->GetDisplayMgr();

      if ( display_mgr )
      {
         CRect box = GetLogicalBoundingBox();
         display_mgr->GetView()->InvalidateRect(box);
      }
   }
}

CString NorthArrow::GetText() const
{
   return m_strText;
}

void NorthArrow::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

LOGFONT NorthArrow::GetFont() const
{
   return m_Font;
}

void NorthArrow::SetDirection(Float64 angle)
{
   m_Direction = angle;
}

Float64 NorthArrow::GetDirection() const
{
   return m_Direction;
}

void NorthArrow::SetSize(LONG size)
{
   m_Size = size;
}

LONG NorthArrow::GetSize() const
{
   return m_Size;
}
