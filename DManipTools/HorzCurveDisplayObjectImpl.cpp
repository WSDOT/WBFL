///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2021  Washington State Department of Transportation
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

// HorzCurveDisplayObjectImpl.cpp : Implementation of CHorzCurveDisplayObjectImpl
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "HorzCurveDisplayObjectImpl.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CHorzCurveDisplayObjectImpl
UINT CHorzCurveDisplayObjectImpl::ms_cfFormat = ::RegisterClipboardFormat(_T("ManipTools.HorzCurveDisplayObject"));


CHorzCurveDisplayObjectImpl::CHorzCurveDisplayObjectImpl()
{
   m_DrawMode = hcCurveWithTangents;
}

STDMETHODIMP CHorzCurveDisplayObjectImpl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iHorzCurveDisplayObject
	};

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CHorzCurveDisplayObjectImpl::FinalConstruct()
{
   SetDisplayObject(this); // Must be called from FinalConstruct and not c'tor

   // start with 8 pt font
   CFont font;
   font.CreatePointFont(80,_T("Arial"));
   font.GetLogFont(&m_Font);
   m_Font.lfHeight = 80;
   m_Font.lfWeight = FW_NORMAL;

   return S_OK;
}

void::CHorzCurveDisplayObjectImpl::FinalRelease()
{
   CDisplayObjectDefaultImpl::Do_FinalRelease();
}

STDMETHODIMP_(CString) CHorzCurveDisplayObjectImpl::GetToolTipText()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   return CString("Horz Curve");
}

STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::putref_HorzCurve(IHorzCurve* hc,BOOL bRedraw,BOOL bFireEvent)
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
   
   m_HorzCurve = hc;

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
      Fire_OnMoved();
   }
}

STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::get_HorzCurve(IHorzCurve* *hc)
{
   (*hc) = m_HorzCurve;
   if ( m_HorzCurve )
      (*hc)->AddRef();
}

STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::put_DrawMode(HorzCurveDrawMode mode)
{
   m_DrawMode = mode;
}

STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::get_DrawMode(HorzCurveDrawMode* mode)
{
   *mode = m_DrawMode;
}

STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::put_Font(const LOGFONT& Font)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (Font.lfHeight>20) // 20 is arbitrary, but who wants a 2 point font?
   {
      m_Font = Font;
   }
   else
      // we expect point fonts here
      ATLASSERT(false);
}

STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::get_Font(LOGFONT* pFont)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   *pFont = m_Font;
}

// iDrawPointStrategy
STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::Draw(CDC* pDC)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   Highlite(pDC, IsSelected());
}

//STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::DrawDragImage(CDC* pDC, iCoordinateMap* pMap, const CPoint& dragStart, const CPoint& dragPoint)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//
//   // offset our dragged image to match selected point
//   CPoint drag_point(dragPoint.x+m_DragOffset.cx, dragPoint.y+m_DragOffset.cy);
//
//   Draw(pDC, pMap, drag_point, FALSE, TRUE);
//}
//
STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if ( !m_HorzCurve )
      return;

   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // Draw entry spiral


   // Draw circular curve
   CurveDirectionType direction;
   m_HorzCurve->get_Direction(&direction);

   CComPtr<IPoint2d> ts, sc, cs, st, pi, cc, ccc;
   m_HorzCurve->get_TS(&ts);
   m_HorzCurve->get_SC(&sc);
   m_HorzCurve->get_CS(&cs);
   m_HorzCurve->get_ST(&st);
   m_HorzCurve->get_PI(&pi);
   m_HorzCurve->get_CC(&cc);
   m_HorzCurve->get_CCC(&ccc);

   // convert to world space
   Float64 ts_x, ts_y, sc_x, sc_y, cs_x, cs_y, st_x, st_y, pi_x, pi_y, cc_x, cc_y, ccc_x, ccc_y;
   pMap->MPtoWP(ts,&ts_x,&ts_y);
   pMap->MPtoWP(sc,&sc_x,&sc_y);
   pMap->MPtoWP(cs,&cs_x,&cs_y);
   pMap->MPtoWP(st,&st_x,&st_y);
   pMap->MPtoWP(pi,&pi_x,&pi_y);
   pMap->MPtoWP(cc,&cc_x,&cc_y);
   pMap->MPtoWP(ccc,&ccc_x,&ccc_y);

   // convert to logical space
   CPoint pntTS,pntSC,pntCS,pntST,pntPI,pntCC,pntCCC;
   pMap->WPtoLP(ts_x,ts_y,&pntTS.x,&pntTS.y);
   pMap->WPtoLP(sc_x,sc_y,&pntSC.x,&pntSC.y);
   pMap->WPtoLP(cs_x,cs_y,&pntCS.x,&pntCS.y);
   pMap->WPtoLP(st_x,st_y,&pntST.x,&pntST.y);
   pMap->WPtoLP(pi_x,pi_y,&pntPI.x,&pntPI.y);
   pMap->WPtoLP(cc_x,cc_y,&pntCC.x,&pntCC.y);
   pMap->WPtoLP(ccc_x,ccc_y,&pntCCC.x,&pntCCC.y);

   // get curve radius in logical space
   Float64 radius;
   m_HorzCurve->get_Radius(&radius);

   long rx,ry;
   pMap->WPtoLP(radius+ccc_x,radius+ccc_y,&rx,&ry);
   rx -= pntCCC.x;
   ry -= pntCCC.y;

   if ( m_DrawMode == hcCurveWithTangents || m_DrawMode == hcFull )
   {
      // Tangent Lines
      pDC->MoveTo(pntTS);
      pDC->LineTo(pntPI);
      pDC->LineTo(pntST);
   }

   if ( m_DrawMode == hcFull )
   {
      // Radius Lines
      pDC->MoveTo(pntTS);
      pDC->LineTo(pntCC);
      pDC->LineTo(pntST);
   }

   CRect rect;
   rect.left   = pntCCC.x - rx;
   rect.right  = pntCCC.x + rx;
   rect.top    = pntCCC.y - ry;
   rect.bottom = pntCCC.y + ry;


   int arcDir = pDC->SetArcDirection(direction == cdLeft ? AD_COUNTERCLOCKWISE : AD_CLOCKWISE);
   pDC->Arc(rect,pntSC,pntCS);
   pDC->SetArcDirection(arcDir);

   // Draw Exit Spiral

   //
//   CComPtr<IPoint2d> pos;
//   this->get_Position(&pos);
//   Float64 wleft, wtop;
//   pos->get_X(&wleft);
//   pos->get_Y(&wtop);
//
//   long lleft, ltop;
//   pMap->WPtoLP(wleft,wtop,&lleft,&ltop);
//   CPoint location(lleft, ltop);
//
//   Draw(pDC, pMap, location, bHighlite);
//
}
//
//void CHorzCurveDisplayObjectImpl::Draw(CDC* pDC, iCoordinateMap* pMap, const CPoint& location, BOOL bHighlite, BOOL beingDragged)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//
//   CComPtr<iDisplayList> pDL;
//   this->GetDisplayList(&pDL);
//   CComPtr<iDisplayMgr> pDispMgr;
//   pDL->GetDisplayMgr(&pDispMgr);
//
//   // get logical units per twip
//   long lox, loy, lex, ley;
//   pMap->TPtoLP(0, 0, &lox, &loy);
//   pMap->TPtoLP(1000, 1000, &lex, &ley);
//
//   Float64 lx_per_twip = (lex-lox)/1000.0;
//   Float64 ly_per_twip = (ley-loy)/1000.0;
//
//   // cell sizes in twips then device
//   CSize csize_twips;
//   get_CellSize(&csize_twips);
//
//   long lcwidth  = csize_twips.cx * lx_per_twip;
//   long lcheight = csize_twips.cy * ly_per_twip;
//
//   // total width and height of legend box in logical coords
//   long num_entries = m_Container.size();
//   long num_cols = GetNumCols(m_NumRows, num_entries);
//
//   long lwidth  = num_cols  * lcwidth;
//   long lheight = m_NumRows * lcheight;
//
//   // fill backgrgound if asked
//   COLORREF old_col = pDC->GetBkColor();
//   if (m_DoFill!=FALSE)
//   {
//      pDC->SetBkColor(m_FillColor);
//      CBrush brush(m_FillColor);
//      CPen back_pen(PS_SOLID, 1, m_FillColor);
//      CBrush* pold_brush = pDC->SelectObject(&brush);
//      CPen* pold_pen = pDC->SelectObject(&back_pen);
//
//      pDC->Rectangle(location.x,location.y, location.x+lwidth, location.y-lheight);
//
//      pDC->SelectObject(pold_brush);
//      pDC->SelectObject(pold_pen);
//      pDC->SetBkColor(old_col);
//   }
//
//   // set up pen in black or hilite color
//   COLORREF bcolor = (bHighlite==FALSE) ? RGB(10,10,10) : pDispMgr->GetSelectionColor();
//   CPen main_pen(PS_SOLID, 1, bcolor);
//   CPen* porig_pen = pDC->SelectObject(&main_pen);
//
//   // title
//   UINT old_align = pDC->SetTextAlign(TA_LEFT|TA_BOTTOM);
//
//   if (m_Title.Length() >0 && !beingDragged) // dont' draw text if we are being dragged
//   {
//      // make title font darker and bigger
//      long old_wt = m_Font.lfWeight;
//      m_Font.lfWeight = old_wt>700 ? FW_BLACK : old_wt+200;
//      long old_ht = m_Font.lfHeight;
//      m_Font.lfHeight += 10; 
//
//      CString str(m_Title);
//      CSize str_size = pMap->GetTextExtent(m_Font, str);
//
//      long tx = location.x + lwidth/2 - str_size.cx/2;
//      long ty = location.y  + lcheight/8;
//
//      CFont tfont;
//      tfont.CreatePointFontIndirect(&m_Font, pDC);
//      CFont* pold_font = pDC->SelectObject(&tfont);
//
//      pDC->TextOut(tx,ty, str);
//
//      pDC->SelectObject(pold_font);
//      m_Font.lfWeight = old_wt;
//      m_Font.lfHeight = old_ht;
//   }
//
//   // draw border
//   if (m_DoDrawBorder!=FALSE || bHighlite!=FALSE)
//   {
//      pDC->MoveTo(location.x, location.y);
//      pDC->LineTo(location.x       , location.y-lheight);
//      pDC->LineTo(location.x+lwidth, location.y-lheight);
//      pDC->LineTo(location.x+lwidth, location.y);
//      pDC->LineTo(location.x       , location.y);
//   }
//
//   // legend item draw rect is factor of font size
//   long font_twips = m_Font.lfHeight * 2; // height is in 10th points
//
//   long ldraw_box_width  = BOX_WIDTH*font_twips * lx_per_twip;
//   long ldraw_box_height = BOX_HEIGHT*font_twips * ly_per_twip;
//
//   // get minimum cell size so we can center our entries in the existing cells
//   CSize min_size_twips;
//   this->GetMinCellSize(&min_size_twips);
//
//   long min_cwidth  = min_size_twips.cx * lx_per_twip;
//   long min_cheight = min_size_twips.cy * ly_per_twip;
//
//   // horizontal alignment depends if we can be centered without overlap
//   long lx_datum;
//   if (lcwidth > min_cwidth)
//   {
//      lx_datum = (lcwidth - min_cwidth)/2;
//   }
//   else
//   {
//      lx_datum = font_twips * lx_per_twip;
//   }
//
//   // draw legend items - fill row-wise
//   CFont lfont;
//   lfont.CreatePointFontIndirect(&m_Font, pDC);
//   CFont* pold_font = pDC->SelectObject(&lfont);
//   pDC->SetBkColor(m_FillColor);
//
//   CRect draw_box;
//   long ientry = 0;
//   for (long icol = 0; icol<num_cols; icol++)
//   {
//      draw_box.left = location.x + lx_datum + lcwidth*icol;
//      draw_box.right = draw_box.left + ldraw_box_width;
//
//      draw_box.top    = location.y - (lcheight-min_cheight)/2 - font_twips*ly_per_twip/2;
//      draw_box.bottom = draw_box.top - ldraw_box_height;
//
//      for (long irow = 0; irow<m_NumRows; irow++)
//      {
//         if (ientry>num_entries-1)
//         {
//            // hit last entry
//            break;
//         }
//         else
//         {
//            ContainerItem& entry = m_Container[ientry];
//
//            // draw legend symbol
//            entry.m_T->Draw(pDC, draw_box, beingDragged);
//
//            // legend item text
//            if (!beingDragged)
//            {
//               CComBSTR bstr;
//               entry.m_T->get_Name(&bstr);
//
//               pDC->TextOut(draw_box.right + font_twips*lx_per_twip, draw_box.bottom, CString(bstr));
//            }
//
//            draw_box.top    -= lcheight;
//            draw_box.bottom -= lcheight;
//
//            ientry++;
//         }
//      }
//   }
//
//   pDC->SetTextAlign(old_align);
//   pDC->SelectObject(pold_font);
//   pDC->SetBkColor(old_col);
//   pDC->SelectObject(porig_pen);
//}
//
STDMETHODIMP_(void) CHorzCurveDisplayObjectImpl::GetBoundingBox(IRect2d** rect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if ( !m_HorzCurve )
      return;

   CComPtr<IPoint2d> ts, pi, st, cc;
   m_HorzCurve->get_TS(&ts);
   m_HorzCurve->get_PI(&pi);
   m_HorzCurve->get_ST(&st);
   m_HorzCurve->get_CC(&cc);

   Float64 ts_x, ts_y;
   Float64 pi_x, pi_y;
   Float64 st_x, st_y;
   Float64 cc_x, cc_y;
   ts->get_X(&ts_x);
   ts->get_Y(&ts_y);

   pi->get_X(&pi_x);
   pi->get_Y(&pi_y);

   st->get_X(&st_x);
   st->get_Y(&st_y);

   cc->get_X(&cc_x);
   cc->get_Y(&cc_y);

   CComPtr<iDisplayList> pDL;
   this->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   pMap->MPtoWP(ts_x,ts_y,&ts_x,&ts_y);
   pMap->MPtoWP(pi_x,pi_y,&pi_x,&pi_y);
   pMap->MPtoWP(st_x,st_y,&st_x,&st_y);
   pMap->MPtoWP(cc_x,cc_y,&cc_x,&cc_y);

   Float64 left, right, top, bottom;

   if (m_DrawMode == hcFull )
   {
      left   = Min(ts_x,pi_x,st_x,cc_x);
      right  = Max(ts_x,pi_x,st_x,cc_x);
      top    = Max(ts_y,pi_y,st_y,cc_y);
      bottom = Min(ts_y,pi_y,st_y,cc_y);
   }
   else
   {
      left   = Min(ts_x,pi_x,st_x);
      right  = Max(ts_x,pi_x,st_x);
      top    = Max(ts_y,pi_y,st_y);
      bottom = Min(ts_y,pi_y,st_y);
   }

   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   bounding_box->put_Left(left);
   bounding_box->put_Right(right);
   bounding_box->put_Top(top);
   bounding_box->put_Bottom(bottom);

   (*rect) = bounding_box;
   (*rect)->AddRef();
}
//
//void CHorzCurveDisplayObjectImpl::GetBoundingBoxEx(IRect2d& rect, bool includeTitle)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//
//   CComPtr<iDisplayList> pDL;
//   this->GetDisplayList(&pDL);
//   CComPtr<iDisplayMgr> pDispMgr;
//   pDL->GetDisplayMgr(&pDispMgr);
//   CComPtr<iCoordinateMap> pMap;
//   pDispMgr->GetCoordinateMap(&pMap);
//
//   // cell size in twips
//   CSize csize;
//   get_CellSize(&csize);
//
//   // cell size in world
//   Float64 wox, woy, wex, wey;
//   pMap->TPtoWP(0, 0, &wox, &woy);
//   pMap->TPtoWP(csize.cx, csize.cy, &wex, &wey);
//
//   Float64 wcwidth  = wex-wox;
//   Float64 wcheight = wey-woy;
//
//   long num_cols = GetNumCols(m_NumRows, m_Container.size());
//   long is_title = ( includeTitle && m_Title.Length()!=0 ) ? 1 : 0;
//
//   CComPtr<IPoint2d> pos;
//   this->get_Position(&pos);
//   Float64 px, py;
//   pos->get_X(&px);
//   pos->get_Y(&py);
//
//   Float64 bottom = py - wcheight*m_NumRows;
//
//   // adjust top for title
//   if (is_title!=0)
//   {
//      py += wcheight*2/3;
//   }
//
//   rect.put_Left(px);
//   rect.put_Top(py);
//   rect.put_Right(px+wcwidth*num_cols);
//   rect.put_Bottom(bottom);
//}
