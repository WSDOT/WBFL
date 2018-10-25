///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2017  Washington State Department of Transportation
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

// StaticSplitter.cpp : implementation file
//

#include "stdafx.h"
#include <MfcTools\StaticSplitter.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// http://www.codeproject.com/Articles/256/CUsefulSplitterWnd-an-extension-to-CSplitterWnd

IMPLEMENT_DYNCREATE(CUsefulSplitterWnd, CSplitterWnd)

CUsefulSplitterWnd::CUsefulSplitterWnd()
{
	m_bBarLocked=FALSE;
}

CUsefulSplitterWnd::~CUsefulSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CUsefulSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CUsefulSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUsefulSplitterWnd message handlers

void CUsefulSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bBarLocked)
		CSplitterWnd::OnLButtonDown(nFlags, point);
}

void CUsefulSplitterWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bBarLocked)
		CSplitterWnd::OnMouseMove(nFlags, point);
	else
		CWnd::OnMouseMove(nFlags, point);
}

BOOL CUsefulSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bBarLocked)
		return CWnd::OnSetCursor(pWnd, nHitTest, message);

	return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CUsefulSplitterWnd::ReplaceView(int row, int col,CRuntimeClass * pViewClass/*,SIZE size*/)
{
  CCreateContext context;
  BOOL bSetActive;
	       
   
  if ((GetPane(row,col)->IsKindOf(pViewClass))==TRUE)
       return FALSE;
				    
   
   // Get pointer to CDocument object so that it can be used in the creation 
   // process of the new view
   CDocument * pDoc= ((CView *)GetPane(row,col))->GetDocument();
   CView * pActiveView=GetParentFrame()->GetActiveView();
   if (pActiveView==NULL || pActiveView==GetPane(row,col))
      bSetActive=TRUE;
   else
      bSetActive=FALSE;

    CRect wndRect;
    ((CView *) GetPane(row,col))->GetWindowRect(&wndRect);
    CSize size = wndRect.Size();

    // set flag so that document will not be deleted when view is destroyed
	pDoc->m_bAutoDelete=FALSE;    
    // Delete existing view 
   ((CView *) GetPane(row,col))->DestroyWindow();
    // set flag back to default 
    pDoc->m_bAutoDelete=TRUE;

 
    // Create new view                      
   
   context.m_pNewViewClass=pViewClass;
   context.m_pCurrentDoc=pDoc;
   context.m_pNewDocTemplate=NULL;
   context.m_pLastView=NULL;
   context.m_pCurrentFrame=NULL;
   
   CreateView(row,col,pViewClass,size, &context);
   
   CView * pNewView= (CView *)GetPane(row,col);

   pNewView->SendMessage(WM_INITIALUPDATE,0,0);
   
   if (bSetActive==TRUE)
      GetParentFrame()->SetActiveView(pNewView);
   
   RecalcLayout(); 
   GetPane(row,col)->SendMessage(WM_PAINT);
   
   return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CDynamicSplitter, CUsefulSplitterWnd)

CDynamicSplitter::CDynamicSplitter() :
m_FirstPaneFraction(.50)
{
}

CDynamicSplitter::~CDynamicSplitter()
{
}

BEGIN_MESSAGE_MAP(CDynamicSplitter, CUsefulSplitterWnd)
	//{{AFX_MSG_MAP(CDynamicSplitter)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynamicSplitter message handlers
//

void CDynamicSplitter::SetFirstPaneFraction(Float64 frac)
{
   ASSERT(frac<=1.0); 
   ASSERT(frac>=0.0);
   m_FirstPaneFraction = frac;
}

Float64  CDynamicSplitter::GetFirstPaneFraction() const
{
   return m_FirstPaneFraction;
}

void CDynamicSplitter::OnSize(UINT nType, int cx, int cy)
{
   if ( cy > 0 )
   {
      int hPane1;
      int hPane2;
      int hPaneMin;

      GetRowInfo(0,hPane1,hPaneMin);
      GetRowInfo(1,hPane2,hPaneMin);

      int h = hPane1 + hPane2 + m_cySplitterGap + 2*m_cyBorder;

      hPane1 *= cy;
      hPane1 /= h;

      hPane2 *= cy;
      hPane2 /= h;

      if ( 0 < hPane1 && 0 < hPane2 )
      {
         SetRowInfo(0,hPane1,hPaneMin);
         SetRowInfo(1,hPane2,hPaneMin);
      }
   }

   CUsefulSplitterWnd::OnSize(nType, cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitter

IMPLEMENT_DYNCREATE(CStaticSplitter, CDynamicSplitter)

CStaticSplitter::CStaticSplitter()
{
}

CStaticSplitter::~CStaticSplitter()
{
}

BEGIN_MESSAGE_MAP(CStaticSplitter, CDynamicSplitter)
	//{{AFX_MSG_MAP(CStaticSplitter)
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitter message handlers
//
LRESULT CStaticSplitter::OnNcHitTest(CPoint point)
{
   return HTNOWHERE;
}

void CStaticSplitter::OnSize(UINT nType, int cx, int cy) 
{
   if ( cy > 0 )
   {
      int hPane1 = int(GetFirstPaneFraction() * cy);
      int hPane2 = cy - hPane1;
	
      SetRowInfo(0,hPane1,3*hPane1/8);   
      SetRowInfo(1,hPane2,3*hPane2/8);   

      // There is no need to call RecalcLayout() because the OnSize call below
      // will call it.
   }

   //CDynamicSplitter::OnSize(nType, cx, cy);
   CSplitterWnd::OnSize(nType, cx, cy);
}
