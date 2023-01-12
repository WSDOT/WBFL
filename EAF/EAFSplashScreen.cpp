///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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
CBitmap CEAFSplashScreen::m_Bitmap;

#define TIMER_ID 1

CEAFSplashScreen::CEAFSplashScreen()
{
	m_pWndParent=nullptr;
	m_strText="";
	m_hRegion = 0;
	m_nBitmapWidth = 0;
	m_nBitmapHeight = 0;
	m_nxPos = 0;
	m_nyPos = 0;

	SetTextDefaultFont();
}

CEAFSplashScreen::~CEAFSplashScreen()
{
	// Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = nullptr;
}


BEGIN_MESSAGE_MAP(CEAFSplashScreen, CWnd)
	//{{AFX_MSG_MAP(CEAFSplashScreen)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
	ON_WM_TIMER()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// CEAFSplashScreen message handlers

void CEAFSplashScreen::SetSplashScreenInfo(const CEAFSplashScreenInfo& info)
{
   m_Info = info;
}

void CEAFSplashScreen::Show(CWnd* pParentWnd)
{
	if (c_pSplashWnd != nullptr)
		return;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CEAFSplashScreen;
	if (!c_pSplashWnd->Create(pParentWnd))
   {
		delete c_pSplashWnd;
   }
	else
   {
      c_pSplashWnd->ShowSplashScreen();
   }
}

void CEAFSplashScreen::Hide()
{
   if ( c_pSplashWnd )
      c_pSplashWnd->HideSplashScreen();

   c_pSplashWnd = nullptr;
}

BOOL CEAFSplashScreen::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == nullptr)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
   if ( m_Info.m_Style & CSS_HIDEONCLICK )
   {
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
   }

	return FALSE;	// message not handled
}

BOOL CEAFSplashScreen::Create(CWnd *pWndParent)
{
	ASSERT(pWndParent!=nullptr);
	m_pWndParent = pWndParent;
	
   m_strText = _T("");
	
	WNDCLASSEX wcx; 

	wcx.cbSize = sizeof(wcx);
	wcx.lpfnWndProc = AfxWndProc;
	wcx.style = CS_DBLCLKS|CS_SAVEBITS;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = AfxGetInstanceHandle();
	wcx.hIcon = nullptr;
	wcx.hCursor = LoadCursor(nullptr,IDC_ARROW);
	wcx.hbrBackground=::GetSysColorBrush(COLOR_WINDOW);
	wcx.lpszMenuName = nullptr;
	wcx.lpszClassName = _T("EAFSplashScreen");
	wcx.hIconSm = nullptr;

	if (m_Info.m_Style & CSS_SHADOW)
		wcx.style|=CS_DROPSHADOW;

	ATOM classAtom = RegisterClassEx(&wcx);
      
	// didn't work? try not using dropshadow (may not be supported)

	if (classAtom == 0)
	{
		if (m_Info.m_Style & CSS_SHADOW)
		{
			wcx.style &= ~CS_DROPSHADOW;
			classAtom = RegisterClassEx(&wcx);
		}
      else
      {
         return FALSE;
      }
	}

	if (!CreateEx(WS_EX_TOOLWINDOW/* | WS_EX_TOPMOST*/,_T("EAFSplashScreen"),nullptr,WS_POPUP,0,0,0,0,pWndParent->m_hWnd,nullptr))
		return FALSE;

   SetBitmap();

   if ( m_Info.m_FontName != nullptr )
   {
      SetTextFont(m_Info.m_FontName,m_Info.m_FontSize,m_Info.m_FontStyle);
   }

	return TRUE;
}

void CEAFSplashScreen::SetText(LPCTSTR strText)
{
	if (c_pSplashWnd == nullptr)
		return;

   c_pSplashWnd->SetText_(strText);
}

BOOL CEAFSplashScreen::SetBitmap()
{
	BITMAP bm;

   m_Bitmap.Attach(m_Info.m_hBitmap);
   m_Bitmap.GetBitmap(&bm);
	
	m_nBitmapWidth=bm.bmWidth;
	m_nBitmapHeight=bm.bmHeight;
	
	if (m_Info.m_Style & CSS_CENTERSCREEN)
	{
		m_nxPos=(GetSystemMetrics(SM_CXFULLSCREEN)-bm.bmWidth)/2;
		m_nyPos=(GetSystemMetrics(SM_CYFULLSCREEN)-bm.bmHeight)/2;
	}
	else if (m_Info.m_Style & CSS_CENTERAPP)
	{
		CRect rcParentWindow;
		ASSERT(m_pWndParent!=nullptr);
		m_pWndParent->GetWindowRect(&rcParentWindow);
		m_nxPos=rcParentWindow.left+(rcParentWindow.right-rcParentWindow.left-bm.bmWidth)/2;
		m_nyPos=rcParentWindow.top+(rcParentWindow.bottom-rcParentWindow.top-bm.bmHeight)/2;
	}

   m_hRegion=CreateRgnFromBitmap((HBITMAP)m_Bitmap.GetSafeHandle(),m_Info.m_TransparencyColor);
	SetWindowRgn(m_hRegion, TRUE);

	return TRUE;
}

void CEAFSplashScreen::SetTextFont(LPCTSTR szFont,int nSize,int nStyle)
{
	LOGFONT lf;
	m_myFont.DeleteObject();
	m_myFont.CreatePointFont(nSize,szFont);
	m_myFont.GetLogFont(&lf);
	
	if (nStyle & CSS_TEXT_BOLD)
		lf.lfWeight = FW_BOLD;
	else
		lf.lfWeight = FW_NORMAL;
	
	if (nStyle & CSS_TEXT_ITALIC)
		lf.lfItalic=TRUE;
	else
		lf.lfItalic=FALSE;
	
	if (nStyle & CSS_TEXT_UNDERLINE)
		lf.lfUnderline=TRUE;
	else
		lf.lfUnderline=FALSE;

	m_myFont.DeleteObject();
	m_myFont.CreateFontIndirect(&lf);
}

void CEAFSplashScreen::SetTextDefaultFont()
{
	LOGFONT lf;
	CFont *myFont=CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	myFont->GetLogFont(&lf);
	m_myFont.DeleteObject();
	m_myFont.CreateFontIndirect(&lf);
}

void CEAFSplashScreen::SetText_(LPCTSTR szText)
{
	m_strText=szText;
	RedrawWindow();
}

void CEAFSplashScreen::ShowSplashScreen()
{
	SetWindowPos(nullptr,m_nxPos,m_nyPos,m_nBitmapWidth,m_nBitmapHeight,SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);
	ShowWindow(SW_SHOW);
   RedrawWindow();
	
	if (m_Info.m_Duration != 0)
		SetTimer(TIMER_ID,m_Info.m_Duration,nullptr);
}

void CEAFSplashScreen::HideSplashScreen()
{
   ShowWindow(SW_HIDE);
	DestroyWindow();

   m_Bitmap.Detach();

   CEAFMainFrame* pFrame = EAFGetMainFrame();
   if ( pFrame )
	   pFrame->UpdateWindow();
}

HRGN CEAFSplashScreen::CreateRgnFromBitmap(HBITMAP hBmp, COLORREF color)
{
	// this code is written by Davide Pizzolato

	if (!hBmp) return nullptr;

	BITMAP bm;
	GetObject( hBmp, sizeof(BITMAP), &bm );	// get bitmap attributes

	CDC dcBmp;
	dcBmp.CreateCompatibleDC(GetDC());	//Creates a memory device context for the bitmap
	dcBmp.SelectObject(hBmp);			//selects the bitmap in the device context

	const DWORD RDHDR = sizeof(RGNDATAHEADER);
	const DWORD MAXBUF = 40;		// size of one block in RECTs
	// (i.e. MAXBUF*sizeof(RECT) in bytes)
	LPRECT	pRects;								
	DWORD	cBlocks = 0;			// number of allocated blocks

	INT		i, j;					// current position in mask image
	INT		first = 0;				// left position of current scan line
	// where mask was found
	bool	wasfirst = false;		// set when if mask was found in current scan line
	bool	ismask;					// set when current color is mask color

	// allocate memory for region data
	RGNDATAHEADER* pRgnData = (RGNDATAHEADER*)new BYTE[ RDHDR + ++cBlocks * MAXBUF * sizeof(RECT) ];
	memset( pRgnData, 0, RDHDR + cBlocks * MAXBUF * sizeof(RECT) );
	// fill it by default
	pRgnData->dwSize	= RDHDR;
	pRgnData->iType		= RDH_RECTANGLES;
	pRgnData->nCount	= 0;
	for ( i = 0; i < bm.bmHeight; i++ )
		for ( j = 0; j < bm.bmWidth; j++ ){
			// get color
			ismask=(dcBmp.GetPixel(j,bm.bmHeight-i-1)!=color);
			// place part of scan line as RECT region if transparent color found after mask color or
			// mask color found at the end of mask image
			if (wasfirst && ((ismask && (j==(bm.bmWidth-1)))||(ismask ^ (j<bm.bmWidth)))){
				// get offset to RECT array if RGNDATA buffer
				pRects = (LPRECT)((LPBYTE)pRgnData + RDHDR);
				// save current RECT
				pRects[ pRgnData->nCount++ ] = CRect( first, bm.bmHeight - i - 1, j+(j==(bm.bmWidth-1)), bm.bmHeight - i );
				// if buffer full reallocate it
				if ( pRgnData->nCount >= cBlocks * MAXBUF ){
					LPBYTE pRgnDataNew = new BYTE[ RDHDR + ++cBlocks * MAXBUF * sizeof(RECT) ];
					memcpy( pRgnDataNew, pRgnData, RDHDR + (cBlocks - 1) * MAXBUF * sizeof(RECT) );
					delete[] pRgnData;
					pRgnData = (RGNDATAHEADER*)pRgnDataNew;
				}
				wasfirst = false;
			} else if ( !wasfirst && ismask ){		// set wasfirst when mask is found
				first = j;
				wasfirst = true;
			}
		}
		dcBmp.DeleteDC();	//release the bitmap
		// create region
		/*  Under WinNT the ExtCreateRegion returns nullptr (by Fable@aramszu.net) */
		//	HRGN hRgn = ExtCreateRegion( nullptr, RDHDR + pRgnData->nCount * sizeof(RECT), (LPRGNDATA)pRgnData );
		/* ExtCreateRegion replacement { */
		HRGN hRgn=CreateRectRgn(0, 0, 0, 0);
		ASSERT( hRgn!=nullptr );
		pRects = (LPRECT)((LPBYTE)pRgnData + RDHDR);
		for(i = 0;i<(int)pRgnData->nCount;i++)
		{
			HRGN hr=CreateRectRgn(pRects[i].left, pRects[i].top, pRects[i].right, pRects[i].bottom);
			VERIFY(CombineRgn(hRgn, hRgn, hr, RGN_OR)!=ERROR);
			if (hr) DeleteObject(hr);
		}
		ASSERT( hRgn!=nullptr );
		/* } ExtCreateRegion replacement */

		delete[] pRgnData;
		return hRgn;
}

void CEAFSplashScreen::DrawWindow(CDC *pDC)
{
	CDC memDC;
	CBitmap *pOldBitmap;
	
	// Blit Background
	memDC.CreateCompatibleDC(pDC);
	pOldBitmap=memDC.SelectObject(&m_Bitmap);
	pDC->BitBlt(0,0,m_nBitmapWidth,m_nBitmapHeight,&memDC,0,0,SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	// Draw Text
	CFont *pOldFont;
	pOldFont=pDC->SelectObject(&m_myFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_Info.m_TextColor);

	pDC->DrawText(m_strText,-1,m_Info.m_TextRect,m_Info.m_TextFormat);

	pDC->SelectObject(pOldFont);

}

BOOL CEAFSplashScreen::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CEAFSplashScreen::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawWindow(&dc);
}

LRESULT CEAFSplashScreen::OnPrintClient(WPARAM wParam, LPARAM lParam)
{
	CDC* pDC = CDC::FromHandle((HDC)wParam);
	DrawWindow(pDC);
	return 1;
}

void CEAFSplashScreen::OnTimer(UINT_PTR nIDEvent)
{
	// Destroy the splash screen window.
   HideSplashScreen();
   KillTimer(TIMER_ID);
}

void CEAFSplashScreen::PostNcDestroy()
{
	CWnd::PostNcDestroy();
	delete this;
}