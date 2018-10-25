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

// CEAFSplashScreen
struct EAFCLASS CEAFSplashScreenInfo
{
public:
   BOOL    m_bShow;
   HBITMAP m_hBitmap;
   COLORREF m_TextColor;
   COLORREF m_BgColor;
   CRect m_Rect;

   CEAFSplashScreenInfo()
   {
      m_bShow = FALSE;
      m_hBitmap = 0;
      m_TextColor = BLACK;
      m_BgColor   = WHITE;
      m_Rect      = CRect(0,0,20,200);
   }

   CEAFSplashScreenInfo& operator=(const CEAFSplashScreenInfo& other)
   {
      m_bShow     = other.m_bShow;
      m_hBitmap   = other.m_hBitmap;
      m_TextColor = other.m_TextColor;
      m_BgColor   = other.m_BgColor;
      m_Rect      = other.m_Rect;

      return *this;
   }
};

class EAFCLASS CEAFSplashScreen : public CWnd
{
	DECLARE_DYNAMIC(CEAFSplashScreen)

public:
	CEAFSplashScreen();
	virtual ~CEAFSplashScreen();

   static void SetSplashScreenInfo(const CEAFSplashScreenInfo& info);
   static void ShowSplashScreen(CWnd* pParent,BOOL bShowUntilClosed);
   static BOOL PreTranslateAppMessage(MSG* pMsg);
   static void SetText(const char* strText);
   static void CloseOnNextTimeout();
   static void Close();
   static void SetTimeout(UINT duration);

protected:
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	virtual void PostNcDestroy();
	static CEAFSplashScreenInfo m_Info;
	static CEAFSplashScreen* c_pSplashWnd;
   static BOOL m_bShowUntilClosed;
   static BOOL m_bCloseOnNextTimeout;
   static UINT m_Duration;

// Generated message map functions
protected:
	//{{AFX_MSG(CSplashWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


