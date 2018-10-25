#if !defined(AFX_EAFCHILDFRAME_H__7924728D_DE8D_4EFB_9A99_CA16C6FF93DD__INCLUDED_)
#define AFX_EAFCHILDFRAME_H__7924728D_DE8D_4EFB_9A99_CA16C6FF93DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// eafchildframe.h : header file
//
#include <EAF\EAFExp.h>

/////////////////////////////////////////////////////////////////////////////
// CEAFChildFrame frame

class EAFCLASS CEAFChildFrame : public CMDIChildWnd
{
	DECLARE_DYNAMIC(CEAFChildFrame)
protected:
	CEAFChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFChildFrame)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CMDIFrameWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEAFChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEAFChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
public:

   // Must over-ride this method and call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before
   // calling base class method
   virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL) = 0;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EAFCHILDFRAME_H__7924728D_DE8D_4EFB_9A99_CA16C6FF93DD__INCLUDED_)
