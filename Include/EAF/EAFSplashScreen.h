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

#pragma once
#include <EAF\EAFExp.h>
#include <Colors.h>

// CEAFSplashScreenInfo
// Information for a splash screen
struct EAFCLASS CEAFSplashScreenInfo
{
public:
   BOOL    m_bShow;       // show the splash screen if TRUE
   HBITMAP m_hBitmap;     // handle to the splash screen bitman
   COLORREF m_TextColor;  // color of the text to be written on the splash screen
   COLORREF m_BgColor;    // text background color
   COLORREF m_TransparencyColor; // color for transparancy
   CRect m_Rect;          // rectangle into which text is written

   CEAFSplashScreenInfo()
   {
      m_bShow = FALSE;
      m_hBitmap = 0;
      m_TextColor = BLACK;
      m_BgColor   = WHITE;
      m_TransparencyColor = HOTPINK;
      m_Rect      = CRect(0,0,20,200);
   }

   CEAFSplashScreenInfo& operator=(const CEAFSplashScreenInfo& other)
   {
      m_bShow     = other.m_bShow;
      m_hBitmap   = other.m_hBitmap;
      m_TextColor = other.m_TextColor;
      m_BgColor   = other.m_BgColor;
      m_TransparencyColor = other.m_TransparencyColor;
      m_Rect      = other.m_Rect;

      return *this;
   }
};

// CEAFSplashScreen
// Displays a splash screen at application startup
class EAFCLASS CEAFSplashScreen : public CWnd
{
	DECLARE_DYNAMIC(CEAFSplashScreen)

public:
	CEAFSplashScreen();
	virtual ~CEAFSplashScreen();

   // Set the splash screen informatin. Must be done before ShowSplashScreen is called
   static void SetSplashScreenInfo(const CEAFSplashScreenInfo& info);

   // Shows the splash screen
   static void ShowSplashScreen(CWnd* pParent,BOOL bShowUntilClosed);

   // Sets the text in the rectangle defined in the splash screen information
   static void SetText(LPCTSTR strText);

   // close the splash screen next time the timer times out
   static void CloseOnNextTimeout();

   // close the splash screen now
   static void Close();

   // Set the timeout duration
   static void SetTimeout(UINT duration);

   static BOOL PreTranslateAppMessage(MSG* pMsg);

protected:
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	virtual void PostNcDestroy();
	static CEAFSplashScreenInfo m_Info;
	static CEAFSplashScreen* c_pSplashWnd;
   static BOOL m_bShowUntilClosed;
   static BOOL m_bCloseOnNextTimeout;
   static UINT m_Duration;
   static CImageList m_ImageList;
   static CBitmap m_Bitmap;

// Generated message map functions
protected:
	//{{AFX_MSG(CSplashWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


