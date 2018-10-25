// EAFSplashScreen.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFSplashScreen.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CEAFSplashScreen

IMPLEMENT_DYNAMIC(CEAFSplashScreen, CWnd)

BOOL CEAFSplashScreen::c_bShowSplashWnd;
CEAFSplashScreen* CEAFSplashScreen::c_pSplashWnd;
CEAFSplashScreenInfo CEAFSplashScreen::m_Info;
BOOL CEAFSplashScreen::m_bShowUntilClosed = FALSE;
BOOL CEAFSplashScreen::m_bCloseOnNextTimeout = FALSE;
UINT CEAFSplashScreen::m_Duration = 2000;

CEAFSplashScreen::CEAFSplashScreen()
{

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

void CEAFSplashScreen::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}

void CEAFSplashScreen::SetSplashScreenInfo(const CEAFSplashScreenInfo& info)
{
   m_Info = info;
}

void CEAFSplashScreen::ShowSplashScreen(CWnd* pParentWnd,BOOL bShowUntilClosed)
{
	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
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
	BITMAP bm;
   CBitmap bmp;
   bmp.Attach( m_Info.m_hBitmap );
	bmp.GetBitmap(&bm);

	BOOL bResult = CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);

   bmp.Detach();
   return bResult;
}

void CEAFSplashScreen::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();

   //// Show the 'Tip of the Day'
   //CPGSuperApp* pApp = (CPGSuperApp*)AfxGetApp();
   //pApp->ShowTipAtStartup();
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

	// Center the window.
	CenterWindow();

	// Set a timer to destroy the splash screen.
	SetTimer(1, m_Duration, NULL);

	return 0;
}

void CEAFSplashScreen::OnPaint()
{
	CPaintDC dc(this);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
   CBitmap bmp;
   bmp.Attach(m_Info.m_hBitmap);
   bmp.GetBitmap(&bm);

	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&bmp);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);

   bmp.Detach();
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

void CEAFSplashScreen::SetTimeout(UINT duration)
{
   m_Duration = duration;
}

void CEAFSplashScreen::SetText(LPCSTR strText)
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
   dc.DrawText(strText,m_Info.m_Rect,DT_END_ELLIPSIS);
   dc.TextOut(m_Info.m_Rect.left,m_Info.m_Rect.top,strText);

   dc.SelectObject(pOldBrush);
   dc.SelectObject(pOldPen);
   dc.SelectObject(pOldFont);
}
