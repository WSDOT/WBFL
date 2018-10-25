#pragma once
#include <EAF\EAFExp.h>


// CEAFSplashScreen
struct EAFCLASS CEAFSplashScreenInfo
{
public:
   HBITMAP m_hBitmap;
   COLORREF m_TextColor;
   COLORREF m_BgColor;
   CRect m_Rect;

   CEAFSplashScreenInfo& operator=(const CEAFSplashScreenInfo& other)
   {
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
	virtual void PostNcDestroy();

   static void EnableSplashScreen(BOOL bEnable=TRUE);
   static void SetSplashScreenInfo(const CEAFSplashScreenInfo& info);
   static void ShowSplashScreen(CWnd* pParent,BOOL bShowUntilClosed);
   static BOOL PreTranslateAppMessage(MSG* pMsg);
   static void SetText(LPCSTR strText);
   static void CloseOnNextTimeout();
   static void SetTimeout(UINT duration);

protected:
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	static BOOL c_bShowSplashWnd;
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


