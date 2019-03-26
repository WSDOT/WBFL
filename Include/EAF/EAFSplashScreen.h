///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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

// Splash Screen Styles
#define CSS_SHADOW		   0x0001  // Apply a drop shadow
#define CSS_CENTERSCREEN	0x0002  // Center on screen
#define CSS_CENTERAPP		0x0004  // Center on application main window
#define CSS_HIDEONCLICK		0x0008  // Hide the splash screen if it is clicked

// Splash Screen Text Styles
#define CSS_TEXT_NORMAL		0x0000
#define CSS_TEXT_BOLD		0x0001
#define CSS_TEXT_ITALIC		0x0002
#define CSS_TEXT_UNDERLINE	0x0004


// CEAFSplashScreenInfo
// Information for a splash screen
struct EAFCLASS CEAFSplashScreenInfo
{
public:
   UINT m_Style;          // one of the styles above
   UINT m_Duration;       // duration to display splash screen in milliseconds. Use a value of 0 to show until it is closed.
   HBITMAP m_hBitmap;     // handle to the splash screen bitmap
   COLORREF m_TextColor;  // color of the text to be written on the splash screen
   CRect m_TextRect;      // rectangle into which text is written
   UINT m_TextFormat;     // text format (use the DrawText parameters)
   LPCTSTR m_FontName;    // Name of font face
   int m_FontSize;        // Point size
   int m_FontStyle;       // One of the text styles above
   COLORREF m_TransparencyColor; // color for transparancy

   CEAFSplashScreenInfo()
   {
      m_Style = CSS_SHADOW | CSS_CENTERSCREEN | CSS_HIDEONCLICK;
      m_Duration = 0; // // show until closed
      m_hBitmap = 0;
      m_FontName = 0; // use default
      m_FontSize = 0; // use default
      m_FontStyle = 0; // use default
      m_TextColor = BLACK;
      m_TextRect  = CRect(0,0,20,200);
      m_TextFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;
      m_TransparencyColor = HOTPINK;
   }

   CEAFSplashScreenInfo& operator=(const CEAFSplashScreenInfo& other)
   {
      m_Style     = other.m_Style;
      m_Duration  = other.m_Duration;
      m_hBitmap   = other.m_hBitmap;
      m_FontName  = other.m_FontName;
      m_FontSize  = other.m_FontSize;
      m_FontStyle = other.m_FontStyle;
      m_TextColor = other.m_TextColor;
      m_TextRect  = other.m_TextRect;
      m_TextFormat = other.m_TextFormat;
      m_TransparencyColor = other.m_TransparencyColor;

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

   // Set the splash screen information. Must be done before ShowSplashScreen is called
   static void SetSplashScreenInfo(const CEAFSplashScreenInfo& info);

   // Shows the splash screen
   static void Show(CWnd* pParent);

   // close the splash screen
   static void Hide();

   // Sets the text in the rectangle defined in the splash screen information
   static void SetText(LPCTSTR strText);

   static BOOL PreTranslateAppMessage(MSG* pMsg);


protected:
	BOOL Create(CWnd *pWndParent);
   BOOL SetBitmap();

	void ShowSplashScreen();
   void HideSplashScreen();

	void SetText_(LPCTSTR szText);
	void SetTextFont(LPCTSTR szFont,int nSize,int nStyle);
	void SetTextDefaultFont();

protected:	
	CWnd *m_pWndParent;
	CFont m_myFont;
	HRGN m_hRegion;
	
	CString m_strText;

	int m_nBitmapWidth;
	int m_nBitmapHeight;
	int m_nxPos;
	int m_nyPos;
		
	HRGN CreateRgnFromBitmap(HBITMAP hBmp, COLORREF color);
	void DrawWindow(CDC *pDC);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	LRESULT OnPrintClient(WPARAM wParam, LPARAM lParam);
protected:
	virtual void PostNcDestroy();

   static CEAFSplashScreenInfo m_Info;
	static CEAFSplashScreen* c_pSplashWnd;
   static CBitmap m_Bitmap;
};


