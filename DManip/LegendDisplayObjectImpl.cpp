///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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
#include <DManip/LegendDisplayObjectImpl.h>
#include <DManip/LegendEntryImpl.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include <DManip/DisplayView.h>
#include <DManip/TaskFactory.h>
#include <Colors.h>

using namespace WBFL::DManip;

static const int CMENU_BASE = 100; 

// legend item box size
static const long BOX_WIDTH  = 2;
static const long BOX_HEIGHT = 1;

static ColumnIndexType GetNumCols(RowIndexType numRows, RowIndexType Size)
{
   PRECONDITION(0 < numRows);
   return max(1, long((Size-1)/numRows)+1);
}


UINT LegendDisplayObject::ms_cfFormat = ::RegisterClipboardFormat(_T("DManip.LegendDisplayObject"));


LegendDisplayObject::LegendDisplayObject(IDType id) : iLegendDisplayObject(id)
{
   // start with 8 pt font
   CFont font;
   font.CreatePointFont(80, _T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfWeight = FW_NORMAL;
}

void LegendDisplayObject::Draw(CDC* pDC)
{
   Highlight(pDC, IsSelected());
}

void LegendDisplayObject::Highlight(CDC* pDC, bool bHighlite)
{
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   auto [wleft, wtop] = m_Position.GetLocation();

   long lleft, ltop;
   map->WPtoLP(wleft, wtop, &lleft, &ltop);
   CPoint location(lleft, ltop);

   Draw(pDC, map, location, bHighlite);
}

WBFL::Geometry::Rect2d LegendDisplayObject::GetBoundingBox() const
{
   return GetBoundingBoxEx(true);
}

std::_tstring LegendDisplayObject::GetToolTipText() const
{
   return m_Title;
}

bool LegendDisplayObject::OnLButtonDown(UINT nFlags, const POINT& point)
{
   // let event sink handle 
   if (!DisplayObjectDefaultImpl::OnLButtonDown(nFlags,point))
   {
      auto pDispMgr = GetDisplayList()->GetDisplayMgr();

      // If control key is pressed, don't clear current selection
      // (i.e. we want multi-select)
      BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
      if (bMultiSelect)
      {
         pDispMgr->ClearSelectedObjects();
      }

      pDispMgr->SelectObject(shared_from_this(), !bMultiSelect);

      if (m_bIsDraggable)
      {
         // save off offset between clicked point and our anchor (left,top)
         auto rect = GetBoundingBoxEx(false);
         auto wl = rect.Left();
         auto wt = rect.Top();

         auto map = pDispMgr->GetCoordinateMap();
         long ll, lt;
         map->WPtoLP(wl, wt, &ll, &lt);

         m_DragOffset.cx = ll - point.x;
         m_DragOffset.cy = lt - point.y;

         // d&d task
         auto factory = pDispMgr->GetTaskFactory();
         auto task = factory->CreateLocalDragDropTask(pDispMgr, point);
         pDispMgr->SetTask(task);
      }

      return true;
   }

   return false;
}

bool LegendDisplayObject::OnRButtonDown(UINT nFlags, const POINT& point)
{
   if (!DisplayObjectDefaultImpl::OnRButtonDown(nFlags,point))
   {
      auto view = GetDisplayList()->GetDisplayMgr()->GetView();

      POINT screen_point = point;
      view->ClientToScreen(&screen_point);

      RowIndexType nrows = max(m_LegendEntries.size(), m_nRows);

      CMenu menu;
      menu.CreatePopupMenu();
      menu.AppendMenu(MF_STRING | MF_DISABLED, 0, _T("Select Number of Rows"));

      for (RowIndexType it = 1; it <= nrows; it++)
      {
         CString str;
         str.Format(_T("%d"), it);
         UINT iFlags = MF_STRING | MF_ENABLED;
         menu.AppendMenu(iFlags, CMENU_BASE + it, str);
      }

      // need to create a new window in this gui thread in order to catch menu
      // messages
      std::weak_ptr<iContextMenuCommandCallback> listener = std::dynamic_pointer_cast<iContextMenuCommandCallback>(shared_from_this());
      m_pContextMenuMsgWnd = std::make_unique<CContextMenuCommandWnd>(listener);
      m_pContextMenuMsgWnd->Create(nullptr, _T("MessageCatcher\0"), WS_DISABLED, CRect(), view, 0);

      menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, screen_point.x, screen_point.y, m_pContextMenuMsgWnd.get());

      return true;
   }

   return false;
}

bool LegendDisplayObject::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if( !DisplayObjectDefaultImpl::OnKeyDown(nChar,nRepCnt,nFlags))
   {
      if (nChar == VK_RIGHT || nChar == VK_LEFT || nChar == VK_UP || nChar == VK_DOWN)
      {
         auto pDispMgr = GetDisplayList()->GetDisplayMgr();

         CRect box = GetLogicalBoundingBox();
         box.InflateRect(1, 1);
         pDispMgr->GetView()->InvalidateRect(box);

         auto rect =  GetBoundingBox();
         auto width = rect.Width();
         auto height = rect.Height();
         Float64 voff = max(width, height) / 4.0;

         switch (nChar)
         {
         case VK_RIGHT:
         case VK_LEFT:
         {
            Float64 xloc = m_Position.X();

            Float64 xoff = nChar == VK_RIGHT ? 1.0 : -1.0;
            xloc += xoff * voff;

            m_Position.X() = xloc;
         }
         break;

         case VK_UP:
         case VK_DOWN:
         {
            Float64 yloc = m_Position.Y();

            Float64 yoff = nChar == VK_UP ? 1.0 : -1.0;
            yloc += yoff * voff;

            m_Position.Y() = yloc;
         }
         }

         box = GetLogicalBoundingBox();
         box.InflateRect(1, 1);
         pDispMgr->GetView()->InvalidateRect(box);

         return true;
      }
   }

   return false;
}


void LegendDisplayObject::SetPosition(const WBFL::Geometry::Point2d& pos,bool bRedraw,bool bFireEvent)
{
   if ( bRedraw )
   {
      // Erase the old graphic
      CRect box = GetLogicalBoundingBox();
      GetDisplayList()->GetDisplayMgr()->GetView()->InvalidateRect(box);
   }
   
   // Set the new position
   auto [currX, currY] = m_Position.GetLocation();
   m_Position = pos;

   if ( bRedraw )
   {
      CRect box = GetLogicalBoundingBox(); // this is a new bounding box, different from above, because m_Position has changed
      GetDisplayList()->GetDisplayMgr()->GetView()->InvalidateRect(box);
   }

   if ( bFireEvent )
   {
      Fire_OnMoved();
   }
}

const WBFL::Geometry::Point2d& LegendDisplayObject::GetPosition() const
{
   return m_Position;
}

void LegendDisplayObject::SetTitle(LPCTSTR lpszTitle)
{
   m_Title = lpszTitle;
}

std::_tstring LegendDisplayObject::GetTitle() const
{
   return m_Title;
}

void LegendDisplayObject::SetFont(const LOGFONT& font)
{
   CHECK(20 < font.lfHeight); // do you really want a 2 point font?
   m_Font = font;
}

const LOGFONT& LegendDisplayObject::GetFont() const
{
   return m_Font;
}

IndexType LegendDisplayObject::GetEntryCount() const
{
   return m_LegendEntries.size();
}

void LegendDisplayObject::AddEntry(std::shared_ptr<iLegendEntry> entry)
{
   m_LegendEntries.emplace_back(entry);
}

void LegendDisplayObject::InsertEntry(IndexType index, std::shared_ptr<iLegendEntry> entry)
{
   PRECONDITION(0 <= index && index <= m_LegendEntries.size());

   if (index == m_LegendEntries.size())
   {
      AddEntry(entry);
   }
   else
   {
      m_LegendEntries.insert(m_LegendEntries.begin() + index, entry);
   }
}

std::shared_ptr<iLegendEntry> LegendDisplayObject::GetEntry(IndexType index)
{
   PRECONDITION(0 <= index && index < m_LegendEntries.size());
   return m_LegendEntries[index];
}

void LegendDisplayObject::RemoveEntry(IndexType index)
{
   PRECONDITION(0 <= index && index < m_LegendEntries.size());
   m_LegendEntries.erase(m_LegendEntries.begin() + index);
}

void LegendDisplayObject::ClearEntries()
{
   m_LegendEntries.clear();
}

IndexType LegendDisplayObject::GetNumRows() const
{
   return m_nRows;
}

void LegendDisplayObject::SetNumRows(IndexType count)
{
   if(count != m_nRows)
   {
      auto pDispMgr = GetDisplayList()->GetDisplayMgr();

      // must invalidate before and after change
      CRect box = GetLogicalBoundingBox();
      box.InflateRect(1,1);
      pDispMgr->GetView()->InvalidateRect(box);

      m_nRows = count;

      box = GetLogicalBoundingBox();
      box.InflateRect(1,1);
      pDispMgr->GetView()->InvalidateRect(box);
   }
}

SIZE LegendDisplayObject::GetCellSize() const
{
   return m_CellSize;
}

void LegendDisplayObject::SetCellSize(const SIZE& size)
{
   m_CellSize = size;
}

SIZE LegendDisplayObject::GetMinCellSize() const
{
   // font size in twips
   long font_twips = m_Font.lfHeight * 2; // height is in 10th points
   CHECK(0.0 < font_twips);

   // Assume that longest title string is biggest (not necesarily the case)
   // Using the map to test eash string would be more accurate, but less efficient
   long numchars = 0;
   long idx=0, max_idx=-1;
   for( auto& entry : m_LegendEntries)
   {
      auto name = entry->GetName();
      auto len = name.length();
      if ( numchars < len)
      {
         numchars = (long)len;
         max_idx = idx;
      }
   }

   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();
   auto view = GetDisplayList()->GetDisplayMgr()->GetView();

   CSize text_size_twips(0,0);
   if (max_idx != -1)
   {
      auto name = m_LegendEntries[max_idx]->GetName();

      auto size = map->GetTextExtent(view, m_Font, name.c_str());

      long cox, coy, cex, cey;
      map->LPtoTP(0, 0, &cox, &coy);
      map->LPtoTP(size.cx, size.cy, &cex, &cey);
      text_size_twips.cx = abs(cex-cox);
      text_size_twips.cy = abs(cey-coy);
   }

   // subject to minimum requirement
   text_size_twips.cx = max(text_size_twips.cx, font_twips*1);
   text_size_twips.cy = max(text_size_twips.cy, font_twips*3/2);

   // minimum width is (1 + BOX_WIDTH + 1 + 1) *font_size + text_size.cx
   SIZE s;
   s.cx = (BOX_WIDTH+3)*font_twips + text_size_twips.cx;
   s.cy = (BOX_HEIGHT+1)*font_twips;
   
   return s;
}

void LegendDisplayObject::DrawBorder(bool bDraw)
{
   m_bDrawBorder = bDraw;
}

bool LegendDisplayObject::DrawBorder() const
{
   return m_bDrawBorder;
}

bool LegendDisplayObject::Fill() const
{
   return m_bFill;
}

void LegendDisplayObject::Fill(bool bFill)
{
   m_bFill = bFill;
}

void LegendDisplayObject::SetFillColor(COLORREF color)
{
   m_FillColor = color;
}

COLORREF LegendDisplayObject::GetFillColor() const
{
   return m_FillColor;
}

bool LegendDisplayObject::IsDraggable() const
{
   return m_bIsDraggable;
}

void LegendDisplayObject::IsDraggable(bool bIsDraggable)
{
   m_bIsDraggable = bIsDraggable;
}

// iDraggable
void LegendDisplayObject::SetDragData(std::shared_ptr<iDragData> dd)
{
   m_pDragData = dd;
}

std::shared_ptr<iDragData> LegendDisplayObject::GetDragData()
{
   return m_pDragData;
}

UINT LegendDisplayObject::Format()
{
   return ms_cfFormat;
}

void LegendDisplayObject::PrepareDrag(std::shared_ptr<iDragDataSink> pSink)
{
   pSink->CreateFormat(ms_cfFormat);

   // position
   auto [x, y] = m_Position.GetLocation();
   pSink->Write(ms_cfFormat,&x,sizeof(Float64));
   pSink->Write(ms_cfFormat,&y,sizeof(Float64));

   // Title. Strings are tricky
   IndexType len = m_Title.length();
   pSink->Write(ms_cfFormat,&len,sizeof(IndexType));
   if (0 < len)
   {
      auto str = m_Title.c_str();
      pSink->Write(ms_cfFormat,(void*)str, (UINT)len * sizeof(TCHAR)); // next comes string data
   }

   pSink->Write(ms_cfFormat,&m_Font,sizeof(LOGFONT));
   pSink->Write(ms_cfFormat,&m_nRows,sizeof(RowIndexType));
   pSink->Write(ms_cfFormat,&m_bDrawBorder,sizeof(bool));
   pSink->Write(ms_cfFormat,&m_bFill,sizeof(bool));
   pSink->Write(ms_cfFormat,&m_FillColor,sizeof(COLORREF));
   pSink->Write(ms_cfFormat,&m_CellSize,sizeof(SIZE));

   // legend items are polymorphic
   len = m_LegendEntries.size();
   pSink->Write(ms_cfFormat,&len,sizeof(IndexType));
   for(auto& entry : m_LegendEntries)
   {
      entry->WriteDragData(pSink, ms_cfFormat);
   }

   if ( m_pDragData )
      m_pDragData->PrepareForDrag(shared_from_this(), pSink);
}

void LegendDisplayObject::OnDrop(std::shared_ptr<iDragDataSource> pSource)
{
   // Tell the source we are about to read from our format
   pSource->PrepareFormat(ms_cfFormat);

   // position
   Float64 x,y;
   pSource->Read(ms_cfFormat,&x,sizeof(Float64));
   pSource->Read(ms_cfFormat,&y,sizeof(Float64));
   m_Position.Move(x,y);

   // Title
   long len;
   pSource->Read(ms_cfFormat,&len,sizeof(long));
   wchar_t* wstr = new wchar_t[len+1];

   if (0 < len)
      pSource->Read(ms_cfFormat,wstr,len*sizeof(wchar_t)); 

   wstr[len] = _T('\0');
   m_Title = wstr;
   delete[] wstr;

   pSource->Read(ms_cfFormat,&m_Font,sizeof(LOGFONT));
   pSource->Read(ms_cfFormat,&m_nRows,sizeof(long));
   pSource->Read(ms_cfFormat,&m_bDrawBorder,sizeof(bool));
   pSource->Read(ms_cfFormat,&m_bFill,sizeof(bool));
   pSource->Read(ms_cfFormat,&m_FillColor,sizeof(COLORREF));
   pSource->Read(ms_cfFormat,&m_CellSize,sizeof(SIZE));

   // legend entries
   m_LegendEntries.clear();
   pSource->Read(ms_cfFormat,&len,sizeof(long));
   for (long ii = 0; ii<len; ii++)
   {
      auto entry = LegendEntry::Create();
      entry->ReadDragData(pSource, ms_cfFormat);
      m_LegendEntries.emplace_back(entry);
   }


  if ( m_pDragData )
     m_pDragData->OnDrop(shared_from_this(), pSource);

}

void LegendDisplayObject::OnDragMoved(const WBFL::Geometry::Size2d& offset)
{
   auto pDispMgr = GetDisplayList()->GetDisplayMgr();

   CRect box = GetLogicalBoundingBox();
   box.InflateRect(1,1);
   pDispMgr->GetView()->InvalidateRect(box);

   m_Position.Offset(offset);
         
   box = GetLogicalBoundingBox();
   box.InflateRect(1,1);
   pDispMgr->GetView()->InvalidateRect(box);

   Fire_OnDragMoved(offset);
}

void LegendDisplayObject::OnMoved()
{
   Fire_OnMoved();
}

void LegendDisplayObject::OnCopied()
{
   Fire_OnCopied();
}

void LegendDisplayObject::DrawDragImage(CDC* pDC, std::shared_ptr<const iCoordinateMap> pMap, const POINT& dragStart, const POINT& dragPoint)
{
      // offset our dragged image to match selected point
      CPoint drag_point(dragPoint.x + m_DragOffset.cx, dragPoint.y + m_DragOffset.cy);
      Draw(pDC, pMap, drag_point, false, true);
}

void LegendDisplayObject::OnMessage(UINT msg)
{
   int nrows = msg - MC_MSG_BASE;
   auto view = GetDisplayList()->GetDisplayMgr()->GetView();
   CDManipClientDC dc(view);
   SetNumRows(nrows);
   m_pContextMenuMsgWnd->DestroyWindow();
}


void LegendDisplayObject::Draw(CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& location, bool bHighlite, bool bBeingDragged) const
{
   // get logical units per twip
   long lox, loy, lex, ley;
   map->TPtoLP(0, 0, &lox, &loy);
   map->TPtoLP(1000, 1000, &lex, &ley);

   Float64 lx_per_twip = (lex - lox) / 1000.0;
   Float64 ly_per_twip = (ley - loy) / 1000.0;

   // cell sizes in twips then device
   auto csize_twips = GetCellSize();

   LONG lcwidth = LONG(csize_twips.cx * lx_per_twip);
   LONG lcheight = LONG(csize_twips.cy * ly_per_twip);

   // total width and height of legend box in logical coords
   IndexType num_entries = m_LegendEntries.size();
   ColumnIndexType num_cols = GetNumCols(m_nRows, num_entries);

   LONG lwidth = (LONG)(num_cols * lcwidth);
   LONG lheight = (LONG)(m_nRows * lcheight);

   // fill backgrgound if asked
   COLORREF old_col = pDC->GetBkColor();
   if (m_bFill)
   {
      pDC->SetBkColor(m_FillColor);
      CBrush brush(m_FillColor);
      CPen back_pen(PS_SOLID, 1, m_FillColor);
      CBrush* pold_brush = pDC->SelectObject(&brush);
      CPen* pold_pen = pDC->SelectObject(&back_pen);

      pDC->Rectangle(location.x, location.y, location.x + lwidth, location.y - lheight);

      pDC->SelectObject(pold_brush);
      pDC->SelectObject(pold_pen);
      pDC->SetBkColor(old_col);
   }

   // set up pen in black or hilite color
   auto pDispMgr = GetDisplayList()->GetDisplayMgr();
   COLORREF bcolor = (bHighlite) ? pDispMgr->GetSelectionLineColor() : GREY4;
   CPen main_pen(PS_SOLID, 1, bcolor);
   CPen* porig_pen = pDC->SelectObject(&main_pen);

   // title
   UINT old_align = pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);

   auto pView = GetDisplayList()->GetDisplayMgr()->GetView();

   if (0 < m_Title.length() && !bBeingDragged) // dont' draw text if we are being dragged
   {
      // make title font darker and bigger
      LOGFONT lf = m_Font;
      lf.lfWeight = m_Font.lfWeight > 700 ? FW_BLACK : m_Font.lfWeight + 200;
      lf.lfHeight = m_Font.lfHeight + 10;

      CSize str_size = map->GetTextExtent(pView, lf, m_Title.c_str());

      LONG tx = location.x + lwidth / 2 - str_size.cx / 2;
      LONG ty = location.y + lcheight / 8;

      pView->ScaleFont(lf);

      CFont tfont;
      tfont.CreatePointFontIndirect(&lf, pDC);
      CFont* pold_font = pDC->SelectObject(&tfont);

      pDC->TextOut(tx, ty, m_Title.c_str());

      pDC->SelectObject(pold_font);
   }

   // draw border
   if (m_bDrawBorder || bHighlite)
   {
      pDC->MoveTo(location.x, location.y);
      pDC->LineTo(location.x, location.y - lheight);
      pDC->LineTo(location.x + lwidth, location.y - lheight);
      pDC->LineTo(location.x + lwidth, location.y);
      pDC->LineTo(location.x, location.y);
   }

   // legend item draw rect is factor of font size
   LONG font_twips = m_Font.lfHeight * 2; // height is in 10th points

   LONG ldraw_box_width = LONG(BOX_WIDTH * font_twips * lx_per_twip);
   LONG ldraw_box_height = LONG(BOX_HEIGHT * font_twips * ly_per_twip);

   // get minimum cell size so we can center our entries in the existing cells
   auto min_size_twips = GetMinCellSize();

   LONG min_cwidth = LONG(min_size_twips.cx * lx_per_twip);
   LONG min_cheight = LONG(min_size_twips.cy * ly_per_twip);

   // horizontal alignment depends if we can be centered without overlap
   LONG lx_datum;
   if (min_cwidth < lcwidth)
   {
      lx_datum = (lcwidth - min_cwidth) / 2;
   }
   else
   {
      lx_datum = LONG(font_twips * lx_per_twip);
   }

   // draw legend items - fill row-wise
   CFont lfont;
   lfont.CreatePointFontIndirect(&m_Font, pDC);
   CFont* pold_font = pDC->SelectObject(&lfont);
   pDC->SetBkColor(m_FillColor);

   CRect draw_box;
   ColumnIndexType ientry = 0;
   for (ColumnIndexType icol = 0; icol < num_cols; icol++)
   {
      draw_box.left = location.x + lx_datum + lcwidth * (LONG)icol;
      draw_box.right = draw_box.left + ldraw_box_width;

      draw_box.top = LONG(location.y - (lcheight - min_cheight) / 2 - font_twips * ly_per_twip / 2);
      draw_box.bottom = draw_box.top - ldraw_box_height;

      for (RowIndexType irow = 0; irow < m_nRows; irow++)
      {
         if (num_entries <= ientry)
         {
            // hit last entry
            break;
         }
         else
         {
            auto entry = m_LegendEntries[ientry];

            // draw legend symbol
            entry->Draw(pDC, draw_box, bBeingDragged);

            // legend item text
            if (!bBeingDragged)
            {
               auto name = entry->GetName();
               pDC->TextOut(int(draw_box.right + font_twips * lx_per_twip), draw_box.bottom, name.c_str());
            }

            draw_box.top -= lcheight;
            draw_box.bottom -= lcheight;

            ientry++;
         }
      }
   }

   pDC->SetTextAlign(old_align);
   pDC->SelectObject(pold_font);
   pDC->SetBkColor(old_col);
   pDC->SelectObject(porig_pen);
}

WBFL::Geometry::Rect2d LegendDisplayObject::GetBoundingBoxEx(bool bIncludeTitle) const
{
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   // cell size in twips
   auto csize = GetCellSize();

   // cell size in world
   Float64 wox, woy, wex, wey;
   map->TPtoWP(0, 0, &wox, &woy);
   map->TPtoWP(csize.cx, csize.cy, &wex, &wey);

   Float64 wcwidth = wex - wox;
   Float64 wcheight = wey - woy;

   ColumnIndexType num_cols = GetNumCols(m_nRows, m_LegendEntries.size());
   bool is_title = (bIncludeTitle && m_Title.length() != 0) ? true : false;

   auto [px, py] = m_Position.GetLocation();

   Float64 bottom = py - wcheight * m_nRows;

   // adjust top for title
   if (is_title)
   {
      py += wcheight * 2 / 3;
   }

   WBFL::Geometry::Rect2d bounding_box;
   bounding_box.Left() = px;
   bounding_box.Top() = py;
   bounding_box.Right() = px + wcwidth * num_cols;
   bounding_box.Bottom() = bottom;

   return bounding_box;
}
