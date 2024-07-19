///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright � 1999-2024  Washington State Department of Transportation
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
#include <DManip/ViewTitle.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

ViewTitle::ViewTitle(IDType id) : DisplayObjectDefaultImpl(id)
{
   m_strText = "";

   CFont font;
   font.CreatePointFont(120, _T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 120;
   m_Font.lfQuality = ANTIALIASED_QUALITY;
}

ViewTitle::~ViewTitle()
{
}

// iDisplayObject Implementation
// This are the methods not delegated to the implementation object
void ViewTitle::Draw(CDC* pDC)
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

   CRect rClient = pView->GetViewRect();

   CPoint p;
   p.x = rClient.CenterPoint().x;
   p.y = rClient.top;

   LOGFONT lf = m_Font;
   pView->ScaleFont(lf);

   CFont font;
   font.CreatePointFontIndirect(&lf, pDC);
   CFont* pOldFont = pDC->SelectObject(&font);

   UINT nFlag = pDC->SetTextAlign(TA_TOP | TA_CENTER);

   CStringArray strArray;
   GetTextLines(strArray);

   for ( INT_PTR i = strArray.GetSize()-1; 0 <= i; i-- )
   {
      CString str = strArray.GetAt(i);
      CSize size = pDC->GetOutputTextExtent(str);
      pDC->TextOut(p.x,p.y,str);
      p.y -= size.cy;
   }


   pDC->SelectObject(pOldFont);
   pDC->SetTextAlign(nFlag);
}

void ViewTitle::Highlight(CDC* pDC,bool bHighlight)
{
   Draw(pDC);
}

RECT ViewTitle::GetLogicalBoundingBox() const
{
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();
   auto view = GetDisplayList()->GetDisplayMgr()->GetView();

   CRect rClient;
   view->GetClientRect(&rClient);

   CPoint p;
   p.x = rClient.CenterPoint().x;
   p.y = rClient.top;

   CStringArray strArray;
   GetTextLines(strArray);
   
   CSize extents(0,0);
   for ( int i = 0; i < strArray.GetSize(); i++ )
   {
      CString str = strArray.GetAt(i);
      CSize size = map->GetTextExtent(view, m_Font,str);

      if ( size.cx == 0 || size.cy == 0 )
         size = map->GetTextExtent(view,m_Font,_T("ABCDEFG\0"));

      // capture the width of the widest line of text
      if ( extents.cx < size.cx )
         extents.cx = size.cx;

      // accumulate the total height of all lines of text
      extents.cy += size.cy;
   }

   // Find the edges of the text block
   int top, left, right, bottom;
   top    = p.y;
   bottom = p.y + extents.cy;
   left   = p.x - extents.cx/2;
   right  = left + extents.cx;
   CRect box(left,top,right,bottom);

   return box;
}

WBFL::Geometry::Rect2d ViewTitle::GetBoundingBox() const
{
   CRect box = GetLogicalBoundingBox(); // logical coordinates

   // map to world coordinates
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   Float64 left,right,top,bottom;
   map->LPtoWP(box.left,box.bottom,&left,&bottom);
   map->LPtoWP(box.right,box.top,&right,&top);

   return { left,bottom,right,top };
}

void ViewTitle::SetText(LPCTSTR lpszText)
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

CString ViewTitle::GetText() const
{
   return m_strText;
}

void ViewTitle::SetFont(const LOGFONT& Font)
{
   m_Font = Font;
}

LOGFONT ViewTitle::GetFont() const
{
   return m_Font;
}

void ViewTitle::GetTextLines(CStringArray& strArray) const
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