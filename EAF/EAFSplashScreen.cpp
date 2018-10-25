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

// EAFSplashScreen.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFSplashScreen.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFUtilities.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CEAFSplashScreen

IMPLEMENT_DYNAMIC(CEAFSplashScreen, CWnd)

CEAFSplashScreen* CEAFSplashScreen::c_pSplashWnd;
CEAFSplashScreenInfo CEAFSplashScreen::m_Info;
BOOL CEAFSplashScreen::m_bShowUntilClosed = FALSE;
BOOL CEAFSplashScreen::m_bCloseOnNextTimeout = FALSE;
UINT CEAFSplashScreen::m_Duration = 2000;
CImageList CEAFSplashScreen::m_ImageList;
CBitmap CEAFSplashScreen::m_Bitmap;

CEAFSplashScreen::CEAFSplashScreen()
{
   m_Info.m_bShow = FALSE;
}

CEAFSplashScreen::~CEAFSplashScreen()
{
	// Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}


BEGIN_MESSAGE_MAP(CEAFSplashScreen, CWnd)
	//{{AFX_MSG_MAP(CEAFSplashScreen)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// CEAFSplashScreen message handlers

void CEAFSplashScreen::SetSplashScreenInfo(const CEAFSplashScreenInfo& info)
{
   m_Info = info;
}

void CEAFSplashScreen::ShowSplashScreen(CWnd* pParentWnd,BOOL bShowUntilClosed)
{
	if (!m_Info.m_bShow || c_pSplashWnd != NULL)
		return;

   m_bShowUntilClosed = bShowUntilClosed;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CEAFSplashScreen;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}

BOOL CEAFSplashScreen::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;	// message handled here
	}

	return FALSE;	// message not handled
}

BOOL CEAFSplashScreen::Create(CWnd* pParentWnd /*= NULL*/)
{
   m_Bitmap.Attach(m_Info.m_hBitmap);
	BITMAP bm;
	m_Bitmap.GetBitmap(&bm);

	BOOL bResult = CreateEx(0,
		AfxRegisterWndClass(0, EAFGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);

   return bResult;
}

void CEAFSplashScreen::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
   m_Bitmap.Detach();
   m_ImageList.DeleteImageList();

	DestroyWindow();
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   if ( pFrame )
	   pFrame->UpdateWindow();
}

void CEAFSplashScreen::PostNcDestroy()
{
	// Free the C++ class.
	delete this;
}

int CEAFSplashScreen::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	BITMAP bm;
	m_Bitmap.GetBitmap(&bm);
   m_ImageList.Create(bm.bmWidth,bm.bmHeight,TRUE,1,1);
   m_ImageList.Add(&m_Bitmap,m_Info.m_TransparencyColor);

	// Center the window.
	CenterWindow();

	// Set a timer to destroy the splash screen.
	SetTimer(1, m_Duration, NULL);

	return 0;
}

void CEAFSplashScreen::OnPaint()
{
	CPaintDC dc(this);

   CPoint pt(0,0);
   m_ImageList.Draw(&dc,0,pt,ILD_NORMAL);
}

void CEAFSplashScreen::OnTimer(UINT nIDEvent)
{
	// Destroy the splash screen window.
   if ( m_bShowUntilClosed && !m_bCloseOnNextTimeout )
	   SetTimer(1, m_Duration, NULL);
   else
	   HideSplashScreen();
}

void CEAFSplashScreen::CloseOnNextTimeout()
{
   m_bCloseOnNextTimeout = TRUE;
}

void CEAFSplashScreen::Close()
{
   if ( c_pSplashWnd )
      c_pSplashWnd->HideSplashScreen();
}

void CEAFSplashScreen::SetTimeout(UINT duration)
{
   m_Duration = duration;
}

void CEAFSplashScreen::SetText(LPCTSTR strText)
{
	if (c_pSplashWnd == NULL)
		return;

   CClientDC dc(c_pSplashWnd);
   dc.SetBkColor(TRANSPARENT);

   // erase background
   CPen   pen(PS_SOLID,1,m_Info.m_BgColor);
   CBrush brush(m_Info.m_BgColor);
   CPen* pOldPen = dc.SelectObject(&pen);
   CBrush* pOldBrush = dc.SelectObject(&brush);
   dc.Rectangle(m_Info.m_Rect);

   // draw the text
   CFont font;
   font.CreatePointFont(80,_T("Arial"),&dc);
   CFont* pOldFont = dc.SelectObject(&font);

   dc.SetBkColor(m_Info.m_BgColor);
   dc.SetTextColor(m_Info.m_TextColor);
   size_t extra = 4; // DrawText can add up to 4 more characters
   size_t size = _tcslen(strText)+extra;
   LPTSTR pText = new TCHAR[size];
   memset((void*)pText,0,size);
   _tcscpy_s(pText,size,strText);
   dc.DrawText(pText,-1,m_Info.m_Rect,DT_MODIFYSTRING | DT_END_ELLIPSIS);
   delete[] pText;

   dc.SelectObject(pOldBrush);
   dc.SelectObject(pOldPen);
   dc.SelectObject(pOldFont);
}
