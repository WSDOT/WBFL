///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2018  Washington State Department of Transportation
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

// LegendDisplayObject.cpp : Implementation of CLegendDisplayObject
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "LegendDisplayObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int CMENU_BASE = 100; 

// legend item box size
static const long BOX_WIDTH  = 2;
static const long BOX_HEIGHT = 1;

static ColumnIndexType GetNumCols(RowIndexType numRows, RowIndexType Size)
{
   ATLASSERT(numRows>0);

   return max(1, long((Size-1)/numRows)+1);
}

/*
   // erase
   GetBoundingBox(*m_ReusableRect);
   Float64 wl, wr, wt, wb;
   m_ReusableRect->get_Left(&wl);
   m_ReusableRect->get_Right(&wr);
   m_ReusableRect->get_Top(&wt);
   m_ReusableRect->get_Bottom(&wb);

   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   long l,r,t,b;
   pMap->WPtoLP(wl, wt, &l, &t);
   pMap->WPtoLP(wr, wb, &r, &b);

   CRect box(l,t,r,b);
   box.NormalizeRect();
   box.InflateRect(1,1);
   pDispMgr->InvalidateRect(box);
*/

/////////////////////////////////////////////////////////////////////////////
// CLegendDisplayObject
UINT CLegendDisplayObject::ms_cfFormat = ::RegisterClipboardFormat(_T("ManipTools.LegendDisplayObject"));


STDMETHODIMP CLegendDisplayObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iLegendDisplayObject
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CLegendDisplayObject::CLegendDisplayObject():
m_NumRows(1),
m_DoDrawBorder(TRUE),
m_DoFill(TRUE),
m_IsDraggable(TRUE),
m_FillColor( RGB(255,255,128) ) // pale yellow
{
}

HRESULT CLegendDisplayObject::FinalConstruct()
{
   SetDisplayObject(this); // Must be called from FinalConstruct and not c'tor

   m_Position.CoCreateInstance(CLSID_Point2d);

   // start with 8 pt font
   CFont font;
   font.CreatePointFont(80,_T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfWeight = FW_NORMAL;

   m_CellSize = CSize(12*80*2, 3*80*2);  // proportional to font size (twips)

   return S_OK;
}

void::CLegendDisplayObject::FinalRelease()
{
   CDisplayObjectDefaultImpl::Do_FinalRelease();
}

STDMETHODIMP_(CString) CLegendDisplayObject::GetToolTipText()
{
   return CString(m_Title);
}


STDMETHODIMP_(void) CLegendDisplayObject::put_Position(IPoint2d* pos,BOOL bRedraw,BOOL bFireEvent)
{
   if ( bRedraw )
   {
      // Erase the old graphic
      CComPtr<iDisplayList> pDL;
      GetDisplayList(&pDL);

      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      CRect box = GetBoundingBox();
      pDispMgr->InvalidateRect(box);
   }
   
   // Set the new position
   Float64 currX, currY;
   m_Position->get_X(&currX);
   m_Position->get_Y(&currY);
   m_Position =  pos;

   if ( bRedraw )
   {
      CComPtr<iDisplayList> pDL;
      GetDisplayList(&pDL);

      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      CRect box = GetBoundingBox();
      pDispMgr->InvalidateRect(box);
   }

   if ( bFireEvent )
   {
      // Compute the amount moved
      Float64 x,y;
      m_Position->get_X(&x);
      m_Position->get_Y(&y);

      CComPtr<ISize2d> offset;
      offset.CoCreateInstance(CLSID_Size2d);
      offset->put_Dx(x - currX);
      offset->put_Dy(y - currY);

      Fire_OnMoved();
   }
}

STDMETHODIMP_(void) CLegendDisplayObject::get_Position(IPoint2d* *pos)
{
   m_Position.CopyTo(pos);
}

STDMETHODIMP_(void) CLegendDisplayObject::get_Title(BSTR *pVal)
{
   m_Title.CopyTo(pVal);
}

STDMETHODIMP_(void) CLegendDisplayObject::put_Title(BSTR newVal)
{
   m_Title = newVal;
}

STDMETHODIMP_(void) CLegendDisplayObject::put_Font(const LOGFONT& Font)
{
   if (Font.lfHeight>20) // 20 is arbitrary, but who wants a 2 point font?
   {
      m_Font = Font;
   }
   else
      // we expect point fonts here
      ATLASSERT(false);
}

STDMETHODIMP_(void) CLegendDisplayObject::get_Font(LOGFONT* pFont)
{
   *pFont = m_Font;
}

STDMETHODIMP_(void) CLegendDisplayObject::get_NumEntries(CollectionIndexType* count)
{
   *count = m_Container.size();
}

STDMETHODIMP_(void) CLegendDisplayObject::AddEntry(iLegendEntry* entry)
{
   m_Container.push_back(ContainerItem( entry ));
}

STDMETHODIMP_(HRESULT) CLegendDisplayObject::InsertEntry(CollectionIndexType index, iLegendEntry* entry)
{
   if (index<0 || index>m_Container.size()+1)
      return E_INVALIDARG;

   if (index==m_Container.size())

      AddEntry(entry);
   else
   {
      ContainerIterator it = m_Container.begin();
      it += index;
      m_Container.insert(it, ContainerItem(entry));
   }

   return S_OK;
}

STDMETHODIMP_(HRESULT) CLegendDisplayObject::get_Entry(CollectionIndexType index, iLegendEntry* *entry)
{
   (*entry) = 0;
   if ( index < 0 || m_Container.size() <= index )
      return E_FAIL;

   ContainerItem ppt = m_Container[index];
   return ppt.m_T.CopyTo(entry);
}

STDMETHODIMP_(HRESULT) CLegendDisplayObject::RemoveEntry(CollectionIndexType index)
{
   if (index<0 || index>m_Container.size()-1)
      return E_INVALIDARG;

      ContainerIterator it = m_Container.begin();
      it += index;
      m_Container.erase(it);

      return S_OK;
}

STDMETHODIMP_(void) CLegendDisplayObject::ClearEntries()
{
   m_Container.clear();
}

STDMETHODIMP_(void) CLegendDisplayObject::get_NumRows(CollectionIndexType* count)
{
   *count = m_NumRows;
}

STDMETHODIMP_(void) CLegendDisplayObject::put_NumRows(CollectionIndexType count)
{
   if (count>0 && m_NumRows!=count)
   {
      CComPtr<iDisplayList> pDL;
      GetDisplayList(&pDL);
      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      // must invalidate before and after change
      CRect box = GetBoundingBox();
      box.InflateRect(1,1);
      pDispMgr->InvalidateRect(box);

      m_NumRows = count;

      box = GetBoundingBox();
      box.InflateRect(1,1);
      pDispMgr->InvalidateRect(box);

   }
   else if (count<1)
      ATLASSERT(false);
}

STDMETHODIMP_(void) CLegendDisplayObject::get_CellSize(CSize* size)
{
   *size = m_CellSize;
}

STDMETHODIMP_(void) CLegendDisplayObject::put_CellSize(CSize size)
{
   m_CellSize = size;
}

STDMETHODIMP_(void) CLegendDisplayObject::GetMinCellSize(CSize* size)
{
   // font size in twips
   long font_twips = m_Font.lfHeight * 2; // height is in 10th points
   ATLASSERT(font_twips>0.0);

   // Assume that longest title string is biggest (not necesarily the case)
   // Using the map to test eash string would be more accurate, but less efficient
   long numchars = 0;
   long idx=0, max_idx=-1;
   for (Container::iterator it = m_Container.begin(); it!=m_Container.end(); it++)
   {
      CComBSTR str;
      it->m_T->get_Name(&str);
      long len = str.Length();
      if ( len> numchars)
      {
         numchars = len;
         max_idx = idx;
      }

      idx++;
   }

   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CSize text_size_twips(0,0);
   if (max_idx != -1)
   {
      CComBSTR str;
      m_Container[max_idx].m_T->get_Name(&str);
      CString text(str.m_str);

      CSize size = pMap->GetTextExtent(m_Font, text);

      long cox, coy, cex, cey;
      pMap->LPtoTP(0, 0, &cox, &coy);
      pMap->LPtoTP(size.cx, size.cy, &cex, &cey);
      text_size_twips.cx = abs(cex-cox);
      text_size_twips.cy = abs(cey-coy);
   }

   // subject to minimum requirement
   text_size_twips.cx = max(text_size_twips.cx, font_twips*1);
   text_size_twips.cy = max(text_size_twips.cy, font_twips*3/2);

   // minimum width is (1 + BOX_WIDTH + 1 + 1) *font_size + text_size.cx
   size->cx = (BOX_WIDTH+3)*font_twips + text_size_twips.cx;
   size->cy = (BOX_HEIGHT+1)*font_twips;
}

STDMETHODIMP_(void) CLegendDisplayObject::get_DoDrawBorder(BOOL* doDraw)
{
   *doDraw = m_DoDrawBorder;
}

STDMETHODIMP_(void) CLegendDisplayObject::put_DoDrawBorder(BOOL doDraw)
{
   m_DoDrawBorder = doDraw==FALSE ? FALSE:TRUE;
}

STDMETHODIMP_(void) CLegendDisplayObject::get_IsDraggable(BOOL* doDraw)
{
   *doDraw = m_IsDraggable;
}

STDMETHODIMP_(void) CLegendDisplayObject::put_IsDraggable(BOOL doDraw)
{
   m_IsDraggable = doDraw==FALSE ? FALSE:TRUE;
}


STDMETHODIMP_(void) CLegendDisplayObject::put_DoFill(BOOL doDraw)
{
   m_DoFill = doDraw==FALSE ? FALSE:TRUE;
}

STDMETHODIMP_(void) CLegendDisplayObject::get_DoFill(BOOL* doDraw)
{
   *doDraw = m_DoFill;
}

STDMETHODIMP_(void) CLegendDisplayObject::put_FillColor(COLORREF doDraw)
{
   m_FillColor = doDraw==FALSE ? FALSE:TRUE;
}

STDMETHODIMP_(COLORREF) CLegendDisplayObject::get_FillColor()
{
   return m_FillColor;
}


// iDrawPointStrategy
STDMETHODIMP_(void) CLegendDisplayObject::Draw(CDC* pDC)
{
   Highlite(pDC, IsSelected());
}

STDMETHODIMP_(void) CLegendDisplayObject::DrawDragImage(CDC* pDC, iCoordinateMap* pMap, const CPoint& dragStart, const CPoint& dragPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   // offset our dragged image to match selected point
   CPoint drag_point(dragPoint.x+m_DragOffset.cx, dragPoint.y+m_DragOffset.cy);

   Draw(pDC, pMap, drag_point, FALSE, TRUE);
}

STDMETHODIMP_(void) CLegendDisplayObject::Highlite(CDC* pDC,BOOL bHighlite)
{
   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CComPtr<IPoint2d> pos;
   this->get_Position(&pos);
   Float64 wleft, wtop;
   pos->get_X(&wleft);
   pos->get_Y(&wtop);

   long lleft, ltop;
   pMap->WPtoLP(wleft,wtop,&lleft,&ltop);
   CPoint location(lleft, ltop);

   Draw(pDC, pMap, location, bHighlite);

}

void CLegendDisplayObject::Draw(CDC* pDC, iCoordinateMap* pMap, const CPoint& location, BOOL bHighlite, BOOL beingDragged)
{
   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   // get logical units per twip
   long lox, loy, lex, ley;
   pMap->TPtoLP(0, 0, &lox, &loy);
   pMap->TPtoLP(1000, 1000, &lex, &ley);

   Float64 lx_per_twip = (lex-lox)/1000.0;
   Float64 ly_per_twip = (ley-loy)/1000.0;

   // cell sizes in twips then device
   CSize csize_twips;
   get_CellSize(&csize_twips);

   LONG lcwidth  = LONG(csize_twips.cx * lx_per_twip);
   LONG lcheight = LONG(csize_twips.cy * ly_per_twip);

   // total width and height of legend box in logical coords
   CollectionIndexType num_entries = m_Container.size();
   ColumnIndexType num_cols = GetNumCols(m_NumRows, num_entries);

   LONG lwidth  = (LONG)(num_cols  * lcwidth);
   LONG lheight = (LONG)(m_NumRows * lcheight);

   // fill backgrgound if asked
   COLORREF old_col = pDC->GetBkColor();
   if (m_DoFill!=FALSE)
   {
      pDC->SetBkColor(m_FillColor);
      CBrush brush(m_FillColor);
      CPen back_pen(PS_SOLID, 1, m_FillColor);
      CBrush* pold_brush = pDC->SelectObject(&brush);
      CPen* pold_pen = pDC->SelectObject(&back_pen);

      pDC->Rectangle(location.x,location.y, location.x+lwidth, location.y-lheight);

      pDC->SelectObject(pold_brush);
      pDC->SelectObject(pold_pen);
      pDC->SetBkColor(old_col);
   }

   // set up pen in black or hilite color
   COLORREF bcolor = (bHighlite==FALSE) ? RGB(10,10,10) : pDispMgr->GetSelectionLineColor();
   CPen main_pen(PS_SOLID, 1, bcolor);
   CPen* porig_pen = pDC->SelectObject(&main_pen);

   // title
   UINT old_align = pDC->SetTextAlign(TA_LEFT|TA_BOTTOM);

   if (m_Title.Length() >0 && !beingDragged) // dont' draw text if we are being dragged
   {
      // make title font darker and bigger
      LONG old_wt = m_Font.lfWeight;
      m_Font.lfWeight = old_wt>700 ? FW_BLACK : old_wt+200;
      LONG old_ht = m_Font.lfHeight;
      m_Font.lfHeight += 10; 

      CString str(m_Title);
      CSize str_size = pMap->GetTextExtent(m_Font, str);

      LONG tx = location.x + lwidth/2 - str_size.cx/2;
      LONG ty = location.y  + lcheight/8;

      CFont tfont;
      tfont.CreatePointFontIndirect(&m_Font, pDC);
      CFont* pold_font = pDC->SelectObject(&tfont);

      pDC->TextOut(tx,ty, str);

      pDC->SelectObject(pold_font);
      m_Font.lfWeight = old_wt;
      m_Font.lfHeight = old_ht;
   }

   // draw border
   if (m_DoDrawBorder!=FALSE || bHighlite!=FALSE)
   {
      pDC->MoveTo(location.x, location.y);
      pDC->LineTo(location.x       , location.y-lheight);
      pDC->LineTo(location.x+lwidth, location.y-lheight);
      pDC->LineTo(location.x+lwidth, location.y);
      pDC->LineTo(location.x       , location.y);
   }

   // legend item draw rect is factor of font size
   LONG font_twips = m_Font.lfHeight * 2; // height is in 10th points

   LONG ldraw_box_width  = LONG(BOX_WIDTH*font_twips * lx_per_twip);
   LONG ldraw_box_height = LONG(BOX_HEIGHT*font_twips * ly_per_twip);

   // get minimum cell size so we can center our entries in the existing cells
   CSize min_size_twips;
   this->GetMinCellSize(&min_size_twips);

   LONG min_cwidth  = LONG(min_size_twips.cx * lx_per_twip);
   LONG min_cheight = LONG(min_size_twips.cy * ly_per_twip);

   // horizontal alignment depends if we can be centered without overlap
   LONG lx_datum;
   if (lcwidth > min_cwidth)
   {
      lx_datum = (lcwidth - min_cwidth)/2;
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
   for (ColumnIndexType icol = 0; icol<num_cols; icol++)
   {
      draw_box.left = location.x + lx_datum + lcwidth*(LONG)icol;
      draw_box.right = draw_box.left + ldraw_box_width;

      draw_box.top    = LONG(location.y - (lcheight-min_cheight)/2 - font_twips*ly_per_twip/2);
      draw_box.bottom = draw_box.top - ldraw_box_height;

      for (RowIndexType irow = 0; irow<m_NumRows; irow++)
      {
         if (num_entries <= ientry)
         {
            // hit last entry
            break;
         }
         else
         {
            ContainerItem& entry = m_Container[ientry];

            // draw legend symbol
            entry.m_T->Draw(pDC, draw_box, beingDragged);

            // legend item text
            if (!beingDragged)
            {
               CComBSTR bstr;
               entry.m_T->get_Name(&bstr);

               pDC->TextOut(int(draw_box.right + font_twips*lx_per_twip), draw_box.bottom, CString(bstr));
            }

            draw_box.top    -= lcheight;
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

STDMETHODIMP_(void) CLegendDisplayObject::GetBoundingBox(IRect2d** rect)
{
   GetBoundingBoxEx(rect,true);
}

void CLegendDisplayObject::GetBoundingBoxEx(IRect2d** rect, bool includeTitle)
{
   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // cell size in twips
   CSize csize;
   get_CellSize(&csize);

   // cell size in world
   Float64 wox, woy, wex, wey;
   pMap->TPtoWP(0, 0, &wox, &woy);
   pMap->TPtoWP(csize.cx, csize.cy, &wex, &wey);

   Float64 wcwidth  = wex-wox;
   Float64 wcheight = wey-woy;

   ColumnIndexType num_cols = GetNumCols(m_NumRows, m_Container.size());
   bool is_title = ( includeTitle && m_Title.Length()!=0 ) ? true : false;

   CComPtr<IPoint2d> pos;
   this->get_Position(&pos);
   Float64 px, py;
   pos->get_X(&px);
   pos->get_Y(&py);

   Float64 bottom = py - wcheight*m_NumRows;

   // adjust top for title
   if (is_title)
   {
      py += wcheight*2/3;
   }

   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   bounding_box->put_Left(px);
   bounding_box->put_Top(py);
   bounding_box->put_Right(px+wcwidth*num_cols);
   bounding_box->put_Bottom(bottom);

   (*rect) = bounding_box;
   (*rect)->AddRef();
}

// idraggable
STDMETHODIMP_(void) CLegendDisplayObject::SetDragData(iDragData* dd)
{
   m_pDragData = dd;
}

STDMETHODIMP_(void) CLegendDisplayObject::GetDragData(iDragData** dd)
{
   *dd = m_pDragData;
   (*dd)->AddRef();
}

STDMETHODIMP_(UINT) CLegendDisplayObject::Format()
{
   return ms_cfFormat;
}

STDMETHODIMP_(void) CLegendDisplayObject::PrepareDrag(iDragDataSink* pSink)
{
   pSink->CreateFormat(ms_cfFormat);

   // position
   Float64 x,y;
   m_Position->get_X(&x);
   m_Position->get_Y(&y);
   pSink->Write(ms_cfFormat,&x,sizeof(Float64));
   pSink->Write(ms_cfFormat,&y,sizeof(Float64));

   // Title. Strings are tricky
   CollectionIndexType len = m_Title.Length();
   pSink->Write(ms_cfFormat,&len,sizeof(CollectionIndexType));
   if (len>0)
   {
      BSTR tstr = m_Title.m_str;
      pSink->Write(ms_cfFormat,tstr,(UINT)len*sizeof(BSTR)); // next comes string data
   }

   pSink->Write(ms_cfFormat,&m_Font,sizeof(LOGFONT));
   pSink->Write(ms_cfFormat,&m_NumRows,sizeof(RowIndexType));
   pSink->Write(ms_cfFormat,&m_DoDrawBorder,sizeof(BOOL));
   pSink->Write(ms_cfFormat,&m_DoFill,sizeof(BOOL));
   pSink->Write(ms_cfFormat,&m_FillColor,sizeof(COLORREF));
   pSink->Write(ms_cfFormat,&m_CellSize,sizeof(CSize));

   // legend items are polymorphic
   len = m_Container.size();
   pSink->Write(ms_cfFormat,&len,sizeof(CollectionIndexType));
   for (ContainerIterator it = m_Container.begin(); it!=m_Container.end(); it++)
   {
      ContainerItem item = *it;

      // clsid is needed to reconstitute objects later
      CLSID guid;
      it->m_T->GetClassID(&guid);
      pSink->Write(ms_cfFormat,&guid,sizeof(CLSID));

      it->m_T->WriteDragData(pSink, ms_cfFormat);
   }

   if ( m_pDragData )
      m_pDragData->PrepareForDrag(this,pSink);
}

STDMETHODIMP_(void) CLegendDisplayObject::OnDrop(iDragDataSource* pSource)
{
   // Tell the source we are about to read from our format
   pSource->PrepareFormat(ms_cfFormat);

   // position
   Float64 x,y;
   pSource->Read(ms_cfFormat,&x,sizeof(Float64));
   pSource->Read(ms_cfFormat,&y,sizeof(Float64));
   m_Position->put_X(x);
   m_Position->put_Y(y);

   // Title
   long len;
   pSource->Read(ms_cfFormat,&len,sizeof(long));
   wchar_t* wstr = new wchar_t[len+1];

   if (len>0)
      pSource->Read(ms_cfFormat,wstr,len*sizeof(wchar_t)); 

   wstr[len] = _T('\0');
   m_Title = wstr;
   delete[] wstr;

   pSource->Read(ms_cfFormat,&m_Font,sizeof(LOGFONT));
   pSource->Read(ms_cfFormat,&m_NumRows,sizeof(long));
   pSource->Read(ms_cfFormat,&m_DoDrawBorder,sizeof(BOOL));
   pSource->Read(ms_cfFormat,&m_DoFill,sizeof(BOOL));
   pSource->Read(ms_cfFormat,&m_FillColor,sizeof(COLORREF));
   pSource->Read(ms_cfFormat,&m_CellSize,sizeof(CSize));

   // legend entries
   m_Container.clear();
   pSource->Read(ms_cfFormat,&len,sizeof(long));
   for (long ii = 0; ii<len; ii++)
   {
      CLSID guid;
      pSource->Read(ms_cfFormat,&guid,sizeof(CLSID));

      CComPtr<iLegendEntry> entry;
      HRESULT hr = entry.CoCreateInstance(guid);
      ATLASSERT(SUCCEEDED(hr));

      entry->ReadDragData(pSource, ms_cfFormat);

      m_Container.push_back( ContainerItem(entry) );
   }


  if ( m_pDragData )
     m_pDragData->OnDrop(this,pSource);

}

STDMETHODIMP_(void) CLegendDisplayObject::OnDragMoved(ISize2d* offset)
{
   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CRect box = GetBoundingBox();
   box.InflateRect(1,1);
   pDispMgr->InvalidateRect(box);

   m_Position->OffsetEx(offset);
         
   box = GetBoundingBox();
   box.InflateRect(1,1);
   pDispMgr->InvalidateRect(box);

   Fire_OnDragMoved(offset);
}

STDMETHODIMP_(void) CLegendDisplayObject::OnMoved()
{
   // This display object got moved onto another drop target
   Fire_OnMoved();
}

STDMETHODIMP_(void) CLegendDisplayObject::OnCopied()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   // This display object got copied onto another drop target
   Fire_OnCopied();
}

bool CLegendDisplayObject::OnLButtonDblClk(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDblClk(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CLegendDisplayObject::OnLButtonDown(UINT nFlags,CPoint point)
{
   // let event sink handle 
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonDown(this,nFlags,point);
   }
   else
   {
      CComPtr<iDisplayList> pDL;
      GetDisplayList(&pDL);
      CComPtr<iDisplayMgr> dispMgr;
      pDL->GetDisplayMgr(&dispMgr);
      CComPtr<iCoordinateMap> pMap;
      dispMgr->GetCoordinateMap(&pMap);

      // If control key is pressed, don't clear current selection
      // (i.e. we want multi-select)
      BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
      if ( bMultiSelect )
      {
         dispMgr->ClearSelectedObjects();
      }

      dispMgr->SelectObject(this,!bMultiSelect);

      if (m_IsDraggable)
      {
         // save off offset between clicked point and our anchor (left,top)
         CComPtr<IRect2d> rect;
         GetBoundingBoxEx(&rect, false);
         Float64 wl, wt;
         rect->get_Left(&wl);
         rect->get_Top(&wt);
         long ll, lt;
         pMap->WPtoLP(wl, wt, &ll, &lt);

         m_DragOffset.cx = ll-point.x;
         m_DragOffset.cy = lt-point.y;

         // d&d task
         CComPtr<iTaskFactory> factory;
         dispMgr->GetTaskFactory(&factory);
         CComPtr<iTask> task;
         factory->CreateLocalDragDropTask(dispMgr,point,&task);
         dispMgr->SetTask(task);
      }

      return true;
   }
}

bool CLegendDisplayObject::OnLButtonUp(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnLButtonUp(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CLegendDisplayObject::OnRButtonDown(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDown(this,nFlags,point);
   }
   else
   {
      CComPtr<iDisplayList> pDL;
      GetDisplayList(&pDL);
      CComPtr<iDisplayMgr> dispMgr;
      pDL->GetDisplayMgr(&dispMgr);
      CDisplayView* view = dispMgr->GetView();
      view->ClientToScreen(&point);

      RowIndexType nrows = max(m_Container.size(), m_NumRows);

      CMenu menu;
      menu.CreatePopupMenu();
      menu.AppendMenu(MF_STRING|MF_DISABLED, 0, _T("Select Number of Rows"));

      for (RowIndexType it=1; it<=nrows; it++)
      {
         CString str;
         str.Format(_T("%d"), it);
         UINT iFlags = MF_STRING | MF_ENABLED;
         menu.AppendMenu( iFlags, CMENU_BASE + it, str);
      }

      // need to create a new window in this gui thread in order to catch menu
      // messages
      m_pMessageCatcher = std::make_unique<CLegendMessageCatcher>(this);
      m_pMessageCatcher->Create(nullptr, _T("MessageCatcher\0"), WS_DISABLED, CRect(), view, 0);

      menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, m_pMessageCatcher.get());

//      m_pDlg = new CLegendRowsDlg(point, nrows, this);
//      m_pDlg->Create(IDD_LEGEND_ROWS, nullptr);
//      m_pDlg->ShowWindow(SW_SHOW);

//      CLegendRowsDlg dlg(point, nrows, this);
//      dlg.DoModal();

      return true;
   }
}

bool CLegendDisplayObject::OnRButtonUp(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonUp(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CLegendDisplayObject::OnRButtonDblClk(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnRButtonDblClk(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CLegendDisplayObject::OnMouseMove(UINT nFlags,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnMouseMove(this,nFlags,point);
   }
   else
   {
      return false;
   }
}

bool CLegendDisplayObject::OnMouseWheel(UINT nFlags,short zDelta,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnMouseWheel(this,nFlags,zDelta,point);
   }
   else
   {
      return false;
   }
}

bool CLegendDisplayObject::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnKeyDown(this,nChar,nRepCnt,nFlags);
   }
   else
   {
      if (nChar==VK_RIGHT || nChar==VK_LEFT || nChar==VK_UP || nChar==VK_DOWN)
      {
         CComPtr<iDisplayList> pDL;
         this->GetDisplayList(&pDL);
         CComPtr<iDisplayMgr> pDispMgr;
         pDL->GetDisplayMgr(&pDispMgr);

         CRect box = GetBoundingBox();
         box.InflateRect(1,1);
         pDispMgr->InvalidateRect(box);

         CComPtr<IRect2d> rect;
         GetBoundingBox(&rect);
         Float64 width, height;
         rect->get_Width(&width);
         rect->get_Height(&height);
         Float64 voff = max(width,height)/4.0;

         switch(nChar)
         {
            case VK_RIGHT:
            case VK_LEFT:
               {
                  Float64 xloc;
                  m_Position->get_X(&xloc);

                  Float64 xoff = nChar==VK_RIGHT ? 1.0 : -1.0;
                  xloc += xoff * voff;

                  m_Position->put_X(xloc);
               }
               break;

            case VK_UP:
            case VK_DOWN:
               {
                  Float64 yloc;
                  m_Position->get_Y(&yloc);

                  Float64 yoff = nChar==VK_UP ? 1.0 : -1.0;
                  yloc += yoff * voff;

                  m_Position->put_Y(yloc);
               }
         }

         box = GetBoundingBox();
         box.InflateRect(1,1);
         pDispMgr->InvalidateRect(box);
         return true;
      }

      return false;
   }
}

bool CLegendDisplayObject::OnContextMenu(CWnd* pWnd,CPoint point)
{
   if ( m_EventSink )
   {
      return m_EventSink->OnContextMenu(this,pWnd,point);
   }
   else
   {
      return false;
   }
}

void CLegendDisplayObject::OnCaughtMessage(int nrows)
{
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> dispMgr;
   pDL->GetDisplayMgr(&dispMgr);
   CDisplayView* view = dispMgr->GetView();
   CDManipClientDC dc(view);

   this->put_NumRows(nrows);

   m_pMessageCatcher->DestroyWindow();
}
