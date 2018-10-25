// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__77026798_056A_422B_B5DB_F132FF54D48F__INCLUDED_)
#define AFX_MAINFRM_H__77026798_056A_422B_B5DB_F132FF54D48F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <EAF\EAFExp.h>
#include <EAF\EAFDocTemplate.h>
#include <EAF\EAFToolBar.h>
#include <EAF\EAFStatusBar.h>
#include <memory> // for auto_ptr

class CPluginCommnadManager;
class CEAFDocument;

class EAFCLASS CEAFMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CEAFMainFrame)
public:
	CEAFMainFrame();

// Attributes
public:

// Operations
public:
   CView* CreateOrActivateFrame(CEAFDocTemplate* pTemplate);

	// For customizing the default messages on the status bar
   virtual void GetMessageString(UINT nID, CString& rMessage) const;

   // Creating a window was canceled by a user action.
   // Call this method before creation is complete and
   // the window will be destroyed (as if it was never created).
   void CreateCanceled();

   // Call this method if you don't want the view failed error message displayed.
   BOOL DisableFailCreateMessage() const;
   void DisableFailCreateMessage(BOOL bDisable = TRUE);

   CEAFToolBar* GetMainToolBar();
   CEAFToolBar* CreateToolBar(LPCTSTR lpszName,CPluginCommandManager* pCmdMgr);
   void DestroyToolBar(CEAFToolBar* pToolBar);

   /// Enables/disables the "Modified" flag on the status bar
   void EnableModifiedFlag(BOOL bEnable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEAFMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
   std::auto_ptr<CEAFStatusBar>  m_pStatusBar;
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;

   CEAFToolBar m_ToolBar;
   DWORD m_ToolBarID;

   BOOL m_bDisableFailCreateMsg;
   BOOL m_bCreateCanceled;

   virtual CEAFStatusBar* CreateStatusBar();


// Generated message map functions
protected:
	//{{AFX_MSG(CEAFMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
   afx_msg BOOL OnToolTipText(UINT nID,NMHDR* pTTTStruct,LRESULT* pResult);

   virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
   virtual void UpdateFrameTitle(LPCTSTR lpszDocName);

	DECLARE_MESSAGE_MAP()

   friend CEAFDocument;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__77026798_056A_422B_B5DB_F132FF54D48F__INCLUDED_)
