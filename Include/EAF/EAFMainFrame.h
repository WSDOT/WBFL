///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <EAF\EAFMenu.h>
#include <EAF\EAFToolBar.h>
#include <EAF\EAFStatusBar.h>
#include <EAF\EAFAcceleratorTable.h>
#include <vector>

// The following control bar id's are reserved by MFC. (see AFXRES.h)
// We must start numbering our control bars after 0xE803
//#define AFX_IDW_TOOLBAR                 0xE800  // main Toolbar for window
//#define AFX_IDW_STATUS_BAR              0xE801  // Status bar window
//#define AFX_IDW_PREVIEW_BAR             0xE802  // PrintPreview Dialog Bar
//#define AFX_IDW_RESIZE_BAR              0xE803  // OLE in-place resize bar
#define ID_MAINFRAME_TOOLBAR              0xE804

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
   CEAFDocument* GetDocument();
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

   CEAFMenu* GetMainMenu();
   CEAFAcceleratorTable* GetAcceleratorTable();
   CEAFStatusBar* GetStatusBar();
   void SetStatusBar(CEAFStatusBar* pStatusBar);

   void HideMainFrameToolBar();
   void ShowMainFrameToolBar();

   UINT CreateToolBar(LPCTSTR lpszName,CEAFPluginCommandManager* pCmdMgr);
   CEAFToolBar* GetToolBar(UINT toolbarID);
   void DestroyToolBar(CEAFToolBar* pToolBar);
   void DestroyToolBar(UINT toolbarID);

   /// Enables/disables the "Modified" flag on the status bar
   void EnableModifiedFlag(BOOL bEnable);

   virtual void UpdateFrameTitle(LPCTSTR lpszDocName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
   virtual void OnClose();
   virtual void OnDestroy();

public:
   BOOL PreCreateWindow(CREATESTRUCT& cs);
   BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

   // called by the framework when the status center status changes
   virtual void OnStatusChanged();

// Implementation
public:
	virtual ~CEAFMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  
   // Factory method for creating the main frame main menu object
   virtual CEAFMenu* CreateMainMenu();
   CEAFMenu* m_pMainMenu;

   // control bar embedded members
   CEAFStatusBar*  m_pStatusBar;
   CToolBar* m_pMainFrameToolBar;
   BOOL m_bDisableHideMainToolBar;

   struct CEAFToolBarInfo
   {
      CEAFToolBar* m_pEAFToolBar;
      CToolBar* m_pMFCToolBar;
      UINT m_ToolBarID;

      bool operator<(const CEAFToolBarInfo& other) const
      { return m_ToolBarID < other.m_ToolBarID; }

      bool operator==(const CEAFToolBarInfo& other) const
      { return m_ToolBarID == other.m_ToolBarID; }
   };

   typedef std::vector<CEAFToolBarInfo> ToolBarInfo;
   ToolBarInfo m_ToolBarInfo;
   std::vector<UINT> m_ToolBarIDs;
   void SetToolBarState(CToolBar* pToolBar,BOOL bShow);
   UINT GetNextToolBarID();
   void RecycleToolBarID(UINT id);

   BOOL m_bDisableFailCreateMsg;
   BOOL m_bCreateCanceled;

   virtual CEAFStatusBar* CreateStatusBar();
   virtual CToolBar* CreateMainFrameToolBar();


// Generated message map functions
protected:
	//{{AFX_MSG(CEAFMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	afx_msg void OnDropFiles(HDROP hDropInfo);
   afx_msg void OnHelpFinder();
   afx_msg void OnHelp();
   afx_msg void OnViewToolBar();
   afx_msg void OnUpdateViewToolBar(CCmdUI* pCmdUI);
   afx_msg void OnToolbarMenuSelected(UINT id);
	//}}AFX_MSG
   afx_msg BOOL OnToolTipText(UINT nID,NMHDR* pTTTStruct,LRESULT* pResult);
   afx_msg BOOL OnToolbarDropDown(UINT nID,NMHDR* pnmhdr,LRESULT* plr);

   virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
   void UpdateFrameTitleForDocument(LPCTSTR lpszDocName);

	DECLARE_MESSAGE_MAP()

   friend CEAFDocument;

private:
   void DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf);
   std::vector<BOOL> GetToolBarStates();
   std::vector<CString> GetToolBarNames();
   int GetToolBarIndex(UINT nID);
   void SetToolBarStates(const std::vector<BOOL>& vStates);
   void ToggleToolBarState(UINT idx);
	void LoadBarState(LPCTSTR lpszProfileName);
	void SaveBarState(LPCTSTR lpszProfileName) const;

   BOOL m_bShowToolTips;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__77026798_056A_422B_B5DB_F132FF54D48F__INCLUDED_)
