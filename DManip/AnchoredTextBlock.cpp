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
#include <DManip/AnchoredTextBlock.h>
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

AnchoredTextBlock::AnchoredTextBlock(IDType id) : DisplayObjectDefaultImpl(id)
{
   m_strText = "";
   m_Location.x = 0;
   m_Location.y = 0;

   CFont font;
   font.CreatePointFont(80, _T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfQuality = ANTIALIASED_QUALITY;
}

AnchoredTextBlock::~AnchoredTextBlock()
{
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
void AnchoredTextBlock::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   auto pDL = GetDisplayList();
   auto pDM = pDL->GetDisplayMgr();
   CDisplayView* pView = pDM->GetView();
   CRect rClient = pView->GetViewRect();
   CPoint topLeft = rClient.TopLeft();

   LOGFONT lf = m_Font;
   pView->ScaleFont(lf);

   CFont font;
   font.CreatePointFontIndirect(&lf, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(TA_TOP | TA_LEFT);

   CStringArray strArray;
   GetTextLines(strArray);

   CPoint p(m_Location);
   for ( INT_PTR i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = pDC->GetOutputTextExtent(str);
      pDC->TextOut(topLeft.x + p.x,topLeft.y + p.y,str);
      p.y += size.cy;
   }


   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

void AnchoredTextBlock::Highlight(CDC* pDC,bool bHighlight)
{
   Draw(pDC);
}

RECT AnchoredTextBlock::GetLogicalBoundingBox() const
{
   auto display_list = GetDisplayList();
   auto display_mgr = display_list->GetDisplayMgr();
   auto map = display_mgr->GetCoordinateMap();

   const CDisplayView* pView = display_mgr->GetView();

   CStringArray strArray;
   GetTextLines(strArray);
   
   CSize extents(0,0);
   for ( int i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = map->GetTextExtent(pView,m_Font,str);

      if ( size.cx == 0 || size.cy == 0 )
         size = map->GetTextExtent(pView,m_Font,_T("ABCDEFG\0"));

      // capture the width of the widest line of text
      if ( extents.cx < size.cx )
         extents.cx = size.cx;

      // accumulate the total height of all lines of text
      extents.cy += size.cy;
   }

   CRect rClient = pView->GetViewRect();
   CPoint topLeft = rClient.TopLeft();

   // Find the edges of the text block
   int top, left, right, bottom;
   top    = topLeft.y + m_Location.y;
   bottom = top + extents.cy;
   left   = topLeft.x + m_Location.x;
   right  = left + extents.cx;
   CRect box(left,top,right,bottom);

   return box;
}

WBFL::Geometry::Rect2d AnchoredTextBlock::GetBoundingBox() const
{
   CRect box = GetLogicalBoundingBox(); // logical coordinates

   // map to world coordinates
   auto display_list = GetDisplayList();
   auto display_mgr = display_list->GetDisplayMgr();
   auto map = display_mgr->GetCoordinateMap();

   Float64 left,right,top,bottom;
   map->LPtoWP(box.left,box.bottom,&left,&bottom);
   map->LPtoWP(box.right,box.top,&right,&top);

   return { left,bottom,right,top };
}

void AnchoredTextBlock::SetLocation(const POINT& point)
{
   m_Location = point;
}

POINT AnchoredTextBlock::GetLocation() const
{
   return m_Location;
}

void AnchoredTextBlock::SetText(LPCTSTR lpszText)
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

CString AnchoredTextBlock::GetText() const
{
   return m_strText;
}

void AnchoredTextBlock::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

LOGFONT AnchoredTextBlock::GetFont() const
{
   return m_Font;
}

void AnchoredTextBlock::GetTextLines(CStringArray& strArray) const
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
