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
#include <DManip/TextBlockImpl.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

TextBlock::TextBlock(IDType id) : iTextBlock(id)
{
   CFont font;
   font.CreatePointFont(80, _T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfQuality = ANTIALIASED_QUALITY;
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
void TextBlock::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

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

   LONG lx,ly;
   GetPositionInLogicalSpace(&lx,&ly);


   CFont font;
   CreateFont(font,pDC);
//   font.CreatePointFontIndirect(&m_Font, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(m_TextAlign);

   CStringArray strArray;
   GetTextLines(strArray);

   int bkMode = pDC->SetBkMode(m_BkMode);
   COLORREF bgColor = pDC->SetBkColor(m_BgColor);
   COLORREF fgColor = pDC->SetTextColor(m_FgColor);

   Float64 textAngle = ::ToRadians(m_Font.lfEscapement/10.0);
   Float64 sin_textAngle = sin(textAngle);
   Float64 cos_textAngle = cos(textAngle);
   for ( INT_PTR i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = pDC->GetOutputTextExtent(str);
      pDC->TextOut(lx,ly,str);


      LONG dx = (LONG)((Float64)size.cy*sin_textAngle);
      LONG dy = (LONG)((Float64)size.cy*cos_textAngle);
      lx += dx;
      ly += dy;
   }

   pDC->SetBkMode(bkMode);
   pDC->SetBkColor(bgColor);
   pDC->SetTextColor(fgColor);


   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

void TextBlock::Highlight(CDC* pDC,bool bHighlight)
{
   Draw(pDC);
}

RECT TextBlock::GetLogicalBoundingBox() const
{
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   LONG lx,ly;
   GetPositionInLogicalSpace(&lx,&ly);

   CStringArray strArray;
   GetTextLines(strArray);

   auto pView = GetDisplayList()->GetDisplayMgr()->GetView();
   
   CSize extents(0,0);
   for ( INT_PTR i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = map->GetTextExtent(pView, m_Font,str);

      if ( size.cx == 0 || size.cy == 0 )
         size = map->GetTextExtent(pView, m_Font,_T("ABCDEFG\0"));

      // capture the width of the widest line of text
      if ( extents.cx < size.cx )
         extents.cx = size.cx;

      // accumulate the total height of all lines of text
      extents.cy += size.cy;
   }

   // Find the edges of the text block
   LONG top, left, right, bottom;
   CPoint crotate; // center of rotation
   if ( (m_TextAlign&TA_BOTTOM)==TA_BOTTOM || 
        (m_TextAlign&TA_BASELINE)==TA_BASELINE)
   {
      bottom = ly;
      top    = ly - extents.cy;
      crotate.y = bottom;
   }
   else
   {
      top    = ly;
      bottom = ly + extents.cy;
      crotate.y = top;
   }

   if ( (m_TextAlign&TA_CENTER)==TA_CENTER )
   {
      left  = lx - extents.cx/2;
      right = left + extents.cx;
      crotate.x = (left+right)/2;
   }
   else if ( (m_TextAlign&TA_RIGHT)==TA_RIGHT )
   {
      right = lx;
      left  = lx - extents.cx;
      crotate.x = right;
   }
   else
   {
      left  = lx;
      right = lx + extents.cx;
      crotate.x = left;
   }

   // rotate the 
   CRect box(left,top,right,bottom);
   CPoint tl(box.left,box.top);
   CPoint tr(box.right,box.top);
   CPoint bl(box.left,box.bottom);
   CPoint br(box.right,box.bottom);
   LONG langle = GetAngle(); // in 10ths of a degree
   Float64 angle = langle*M_PI/1800.;

   Float64 c = cos(angle);
   Float64 s = sin(angle);

   CPoint p1( int((tl.x - crotate.x)*c + (tl.y - crotate.y)*s + crotate.x), int(-(tl.x - crotate.x)*s + (tl.y - crotate.y)*c + crotate.y) );
   CPoint p2( int((tr.x - crotate.x)*c + (tr.y - crotate.y)*s + crotate.x), int(-(tr.x - crotate.x)*s + (tr.y - crotate.y)*c + crotate.y) );
   CPoint p3( int((bl.x - crotate.x)*c + (bl.y - crotate.y)*s + crotate.x), int(-(bl.x - crotate.x)*s + (bl.y - crotate.y)*c + crotate.y) );
   CPoint p4( int((br.x - crotate.x)*c + (br.y - crotate.y)*s + crotate.x), int(-(br.x - crotate.x)*s + (br.y - crotate.y)*c + crotate.y) );

   box.left   = Min( p1.x, p2.x, p3.x, p4.x );
   box.right  = Max( p1.x, p2.x, p3.x, p4.x );
   box.bottom = Max( p1.y, p2.y, p3.y, p4.y );
   box.top    = Min( p1.y, p2.y, p3.y, p4.y );

   return box;
}

WBFL::Geometry::Rect2d TextBlock::GetBoundingBox() const
{
   CRect box = GetLogicalBoundingBox(); // logical coordinates

   // map to world coordinates
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   Float64 left,right,top,bottom;
   map->LPtoWP(box.left,box.bottom,&left,&bottom);
   map->LPtoWP(box.right,box.top,&right,&top);

   return { left,bottom,right,top };
}

void TextBlock::SetPosition(const WBFL::Geometry::Point2d& pos)
{
   m_Position.Move(pos);
}

const WBFL::Geometry::Point2d& TextBlock::GetPosition() const
{
   return m_Position;
}

void TextBlock::SetTextAlign(UINT nFlags)
{
   m_TextAlign = nFlags;
}

UINT TextBlock::GetTextAlign() const
{
   return m_TextAlign;
}

void TextBlock::SetAngle(LONG angle)
{
   m_Font.lfEscapement  = angle;
   m_Font.lfOrientation = angle;
}

LONG TextBlock::GetAngle() const
{
   return m_Font.lfEscapement;
}

void TextBlock::SetPointSize(LONG pointSize)
{
   m_Font.lfHeight = pointSize;
}

LONG TextBlock::GetPointSize() const
{
   return m_Font.lfHeight;
}

void TextBlock::SetText(LPCTSTR lpszText)
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

CString TextBlock::GetText() const
{
   return m_strText;
}

void TextBlock::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

LOGFONT TextBlock::GetFont() const
{
   return m_Font;
}

void TextBlock::SetTextColor(COLORREF color)
{
   m_FgColor = color;
}

COLORREF TextBlock::GetTextColor() const
{
   return m_FgColor;
}

void TextBlock::SetBkColor(COLORREF color)
{
   m_BgColor = color;
}

COLORREF TextBlock::GetBkColor() const
{
   return m_BgColor;
}

void TextBlock::SetBkMode(int bkMode)
{
   m_BkMode = bkMode;
}

int TextBlock::GetBkMode() const
{
   return m_BkMode;
}

void TextBlock::GetTextLines(CStringArray& strArray) const
{
   // deal with multiline text because TextOut doesn't know what to do with "\n"
   CString strText = GetText();

   int position = 0;
   int length = strText.GetLength();
   while ( true )
   {
      int next_position = strText.Find(_T("\n"),position);
      if ( next_position == -1 )
      {
         strArray.Add(strText.Mid(position));
         break;
      }
      else
      {
         strArray.Add(strText.Mid(position,next_position-position));
         position = next_position+1;
      }
   }
}

void TextBlock::GetPositionInLogicalSpace(LONG* lx,LONG* ly) const
{
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();
   auto wp = map->MPtoWP(m_Position);
   map->WPtoLP(wp,lx,ly);
}

void TextBlock::CreateFont(CFont& font,CDC* pDC)
{
   // this font accounts for the rotation between Model and World space

   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();
   auto mapping = std::dynamic_pointer_cast<const iMapping>(map);

   auto [center,angle] = mapping->GetRotation();

   angle *= 1800/M_PI; // convert to angle degrees (in 10ths of a degree)

   LOGFONT lfFont = m_Font;
   LONG text_angle = lfFont.lfEscapement;

   text_angle += (LONG)angle;

   text_angle = (900 < text_angle  && text_angle  < 2700 ) ? text_angle-1800  : text_angle;

   if ( -2700 <= text_angle && text_angle <= -900 )
      text_angle += 1800;

   lfFont.lfEscapement  = text_angle;
   lfFont.lfOrientation = text_angle;

   auto view = GetDisplayList()->GetDisplayMgr()->GetView();
   view->ScaleFont(lfFont);

   font.CreatePointFontIndirect(&lfFont, pDC);
}