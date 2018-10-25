///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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


#include "stdafx.h"
#include <EAF\EAFLicensePlateChildFrame.h>
#include <Colors.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFLicensePlateChildFrame

IMPLEMENT_DYNCREATE(CEAFLicensePlateChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CEAFLicensePlateChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CEAFLicensePlateChildFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFLicensePlateChildFrame construction/destruction

CEAFLicensePlateChildFrame::CEAFLicensePlateChildFrame()
{
   // make border width the same as window menu
   m_LpBorderWidth = GetSystemMetrics(SM_CYMENU);

   // don't show license plate frame by default
   m_Mode = eafTypes::lpfOff;

   // no bitmap for background at load
   m_IsBitmap = false;

   // set a default message
   m_LpMessage = "Current Data is Invalid";

   m_pView = 0;
}

CEAFLicensePlateChildFrame::~CEAFLicensePlateChildFrame()
{
}

void CEAFLicensePlateChildFrame::SetView(CView* pView)
{
   m_pView = pView;
   UpdateOuterRect();
//   PositionView();
}

CView* CEAFLicensePlateChildFrame::GetView()
{
   return m_pView;
}

/////////////////////////////////////////////////////////////////////////////
// CEAFLicensePlateChildFrame diagnostics

#ifdef _DEBUG
void CEAFLicensePlateChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CEAFLicensePlateChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFLicensePlateChildFrame message handlers

int CEAFLicensePlateChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
   UpdateOuterRect();


   return 0;
}

void CEAFLicensePlateChildFrame::OnSize(UINT nType, int cx, int cy) 
{
   CMDIChildWnd::OnSize(nType, cx, cy);

   UpdateOuterRect();

   // put the view where it's supposed to be
   PositionView();
}


BOOL CEAFLicensePlateChildFrame::OnEraseBkgnd(CDC* pDC) 
{
   if ( !IsLicensePlateModeEnabled() )
   	return CMDIChildWnd::OnEraseBkgnd(pDC);
   else
   {
      // document data is invalid - fill background with bitmap or solid red

      CRect rc;
      rc = GetOuterBorder();

      if (m_IsBitmap)
      {
         CDC memdc;
         memdc.CreateCompatibleDC(pDC);
         // clip out the inside area
         CRect clipr = GetInnerBorder();
         memdc.ExcludeClipRect(&clipr);

         // paint the background with the bitmap.
         // only paint top,left,right,bottom
         // corners get painted twice

         CBitmap* pOldBitmap = memdc.SelectObject(&m_bmBackground);
         const CSize& sz = m_szBackground;

         int x,y;
         // top
         for (y=rc.top; y<rc.top+m_LpBorderWidth; y+=sz.cy)
         {
            for (x=rc.left; x<rc.right; x+=sz.cx)
            {
               pDC->BitBlt(x, y, sz.cx, sz.cy, &memdc, 0,0, SRCCOPY);
            }
         }

         // left side
         for (y=rc.top; y<rc.bottom; y+=sz.cy)
         {
            for (x=rc.left; x<rc.left+m_LpBorderWidth; x+=sz.cx)
            {
               pDC->BitBlt(x, y, sz.cx, sz.cy, &memdc, 0,0, SRCCOPY);
            }
         }

         // right side
         int xstrt = (rc.right-m_LpBorderWidth);
         xstrt -= xstrt % sz.cx;

         for (y=rc.top; y<rc.bottom; y+=sz.cy)
         {
            for (x=xstrt; x<rc.right; x+=sz.cx)
            {
               pDC->BitBlt(x, y, sz.cx, sz.cy, &memdc, 0,0, SRCCOPY);
            }
         }

         // bottom
         int ystrt = (rc.bottom-m_LpBorderWidth);
         ystrt -= ystrt % sz.cy;

         for (y=ystrt; y<rc.bottom; y+=sz.cy)
         {
            for (x=rc.left; x<rc.right; x+=sz.cx)
            {
               pDC->BitBlt(x, y, sz.cx, sz.cy, &memdc, 0,0, SRCCOPY);
            }
         }

         memdc.SelectObject(pOldBitmap);

      }
      else
      {
         // no bit map - just fill solid red
         CBrush back(RED);
         pDC->FillRect(&rc, &back);
      }

      // print message at top and bottom of license plate border
      pDC->SetTextColor(RED); // red text on black background
      pDC->SetBkColor(BLACK);
      CSize ts  =  pDC->GetTextExtent(m_LpMessage);

      // top location and text
      CRect trc(rc.left, rc.top, rc.right, rc.top + m_LpBorderWidth);
      CPoint tp = trc.CenterPoint();
      tp.x -= ts.cx/2;
      tp.y -= ts.cy/2;
      pDC->TextOut(tp.x, tp.y, m_LpMessage);

      // bottom text
      tp.y = rc.bottom - m_LpBorderWidth/2 -ts.cy/2;
      pDC->TextOut(tp.x, tp.y, m_LpMessage);
   
	   return true;
   }
}


void CEAFLicensePlateChildFrame::SetLicensePlateMode(eafTypes::LpFrameMode mode)
{
   if ( mode != m_Mode )
   {
      m_Mode = mode;
      PositionView();
      Invalidate();
      UpdateWindow();
   }
}

eafTypes::LpFrameMode CEAFLicensePlateChildFrame::GetLicensePlateMode()
{
   return m_Mode;
}

void CEAFLicensePlateChildFrame::Toggle()
{
   if ( m_Mode == eafTypes::lpfOn )
      SetLicensePlateMode( eafTypes::lpfOff );
   else
      SetLicensePlateMode( eafTypes::lpfOn );
}

bool CEAFLicensePlateChildFrame::IsLicensePlateModeEnabled() const
{
   return m_Mode == eafTypes::lpfOn;
}

void CEAFLicensePlateChildFrame::SetLicensePlateText(const CString& Message)
{
   // only update if message has changed.
   if (Message != m_LpMessage)
   {
      m_LpMessage = Message;
      Invalidate();
      UpdateWindow();
   }
}

void CEAFLicensePlateChildFrame::SetBackground(UINT BitMapID)
{
   // free the existing background
   m_bmBackground.DeleteObject();

   // load up new background
   if (BitMapID)
   {
      m_IsBitmap = true;
      VERIFY(m_bmBackground.LoadBitmap(BitMapID));
      BITMAP bm;
      VERIFY(m_bmBackground.GetBitmap(&bm));
      m_szBackground = CSize(bm.bmWidth, bm.bmHeight);
   }
   else 
   {
      CHECKX(0,"Invalid bitmap id");
      m_IsBitmap = false;
   }

   Invalidate();
   UpdateWindow();
}

void CEAFLicensePlateChildFrame::PositionView()
{
   CView* p_active_view;
   if ( m_pView == 0 )
      p_active_view = GetActiveView();
   else
      p_active_view = m_pView;

   if ( p_active_view )
   {
      CRect rect;
      p_active_view->GetClientRect( rect );

      if ( IsLicensePlateModeEnabled() )
      {
         CRect inner_rect = GetInnerBorder();

         if ( inner_rect != rect )
         {
            p_active_view->SetWindowPos(0,
                                        inner_rect.TopLeft().x, 
                                        inner_rect.TopLeft().y, 
                                        inner_rect.Width(), 
                                        inner_rect.Height(), 
                                        SWP_NOZORDER );
         }
      }
      else
      {
         CRect outer_rect = GetOuterBorder();

         if ( outer_rect != rect )
         {
            p_active_view->SetWindowPos(0,
                                        outer_rect.TopLeft().x, 
                                        outer_rect.TopLeft().y, 
                                        outer_rect.Width(), 
                                        outer_rect.Height(), 
                                        SWP_NOZORDER );
         }
      }
   }
}

CString CEAFLicensePlateChildFrame::GetLicensePlateText()
{
   return m_LpMessage;
}

void CEAFLicensePlateChildFrame::UpdateOuterRect()
{
   // The outer border is the rect that bounds the view that is to be
   // framed (the active view).

   if ( m_pView == 0 )
   {
      // A view hasn't be specifically associated with the frame...
      GetClientRect( m_OuterRect );
   }
   else
   {
      // OK, the outer border is what ever is left after removing the rects
      // of all child windows except the view we want to frame.
      CRect rect;
      GetClientRect( rect );
      ClientToScreen( rect );

      CWnd* p_child = GetWindow(GW_CHILD);
      for ( ; p_child != 0; p_child = p_child->GetWindow( GW_HWNDNEXT ) )
      {
         if ( p_child != m_pView )
         {
            // this is a little buggy.... only works for child windows on top and left edges
            CRect child_window_rect;
            p_child->GetWindowRect( child_window_rect );

            if ( child_window_rect.bottom != rect.bottom )
               rect.top = max( rect.top,    child_window_rect.bottom );

            if ( child_window_rect.right != rect.right )
               rect.left = max (rect.left, child_window_rect.right );
         }
      }

      ScreenToClient( rect );

      m_OuterRect = rect;
   }
}

CRect& CEAFLicensePlateChildFrame::GetOuterBorder()
{
   return m_OuterRect;
}

CRect CEAFLicensePlateChildFrame::GetInnerBorder()
{
   CRect rect = GetOuterBorder();
   rect.DeflateRect( m_LpBorderWidth, m_LpBorderWidth );
   return rect;
}
