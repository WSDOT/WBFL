// EAFChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFChildFrame.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFChildFrame

IMPLEMENT_DYNAMIC(CEAFChildFrame, CMDIChildWnd)

CEAFChildFrame::CEAFChildFrame()
{
}

CEAFChildFrame::~CEAFChildFrame()
{
}
#ifdef _DEBUG
void CEAFChildFrame::AssertValid() const
{
   // Make sure the module state is that for the CWinApp class
   // before diving down into MFC (if the module state isn't
   // correct, all sorts of asserts will fire)   
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CMDIChildWnd::AssertValid();
}

void CEAFChildFrame::Dump(CDumpContext& dc) const
{
   CMDIChildWnd::Dump(dc);
}
#endif


BEGIN_MESSAGE_MAP(CEAFChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CEAFChildFrame)
	//}}AFX_MSG_MAP
   ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFChildFrame message handlers
void CEAFChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if (bAddToTitle && (GetStyle() & FWS_ADDTOTITLE) == 0)
   {
      // By turning off the default MFC-defined FWS_ADDTOTITLE style,
      // the framework will use first string in the document template
      // STRINGTABLE resource instead of the document name. We want
      // to append a view count to the end of the window title.  
		TCHAR szText[256+_MAX_PATH];
      CString window_text;
      CString window_title;
      GetWindowText(window_text);

      // Look for the last :
      // The text to the left of the last : is the window title
      int idx = window_text.ReverseFind(':');
      if (idx != -1) // -1 meams : was not found
         window_title = window_text.Left(idx);
      else
         window_title = window_text;

		lstrcpy(szText,window_title);
//		if (m_nWindow > 0)
//			wsprintf(szText + lstrlen(szText), _T(":%d"), m_nWindow);

		// set title if changed, but don't remove completely
		AfxSetWindowText(m_hWnd, szText);
   }
   else
   {
      CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
   }
}

BOOL CEAFChildFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   // :TRICKY: rab 11.23.96 : Modifying default behavior
	// By turning off the default MFC-defined FWS_ADDTOTITLE style,
	// the framework will use first string in the document template
	// STRINGTABLE resource instead of the document name.
	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}

BOOL CEAFChildFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	return CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

BOOL CEAFChildFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
   //AFX_MANAGE_STATE(AfxGetAppModuleState());
   // Don't set the module state for the EAF DLL Module. This function has been made pure-virtual
   // so that base classes must implement and set the module state for their DLL module.
   return CMDIChildWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}
