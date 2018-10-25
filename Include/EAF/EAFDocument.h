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
#include <EAF\EAFMenu.h>
#include <EAF\EAFToolBar.h>
#include <EAF\EAFDocPluginManager.h>
#include <EAF\EAFApp.h>
#include <EAF\StatusCenter.h>
#include <WBFLCore.h> // IStructuredSave, IStructuredLoad, et. al.

class CEAFDocTemplate;
class CEAFMainFrame;
class CEAFPluginCommandManager;
class CStatusCenterDlg;
class iStatusCenterEventSink;
class txnTransaction;
class CMyStatusCenterEventSink;

/////////////////////////////////////////////////////////////
// CEAFDocument
//
// Derived from CDocument, the CEAFDocument class is the base class
// for all EAF documents. This document class provides users with
// predefined implementations for an application Status Center,
// Transaction based editing (Undo/Redo), and plug-in components.
//
// Plug-in components can add menus, menu commands to existing menus,
// toolbars, and buttons to existing toolbars.
//
// Use this as the base class for documents that do not use the 
// Agent/Broker architecture

class EAFCLASS CEAFDocument : public CDocument, public iUnitModeListener
{
	DECLARE_DYNAMIC(CEAFDocument)

public:
	CEAFDocument();
	virtual ~CEAFDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
   virtual void Serialize(CArchive& ar);
#endif

   CEAFStatusCenter& GetStatusCenter();

   // iUnitModeListener
   virtual void OnUnitsModeChanged(eafTypes::UnitMode newUnitMode);

   // Transactions
   virtual void Execute(txnTransaction& rTxn);
   virtual void Execute(txnTransaction* pTxn);
   virtual void Undo();
   virtual void Redo();
   virtual void Repeat();
   virtual bool CanUndo();
   virtual bool CanRedo();
   virtual bool CanRepeat();
   virtual std::string UndoName();
   virtual std::string RedoName();
   virtual std::string RepeatName();
   virtual CollectionIndexType GetTxnCount();
   virtual CollectionIndexType GetUndoCount();

   virtual void SetModifiedFlag(BOOL bModified = TRUE);

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFBrokerDocument)

public:
	virtual BOOL OnNewDocument();
   virtual BOOL OnNewDocumentFromTemplate(LPCTSTR lpszPathName);
   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
   virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
   virtual void OnCloseDocument();
   virtual BOOL OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo);

	//}}AFX_VIRTUAL

   /// called when a document is created (New or Open)
   virtual BOOL Init(); 

   /// Called by the framework during document creation. Load any registry settings
   virtual void LoadDocumentSettings();
   /// Called by the framework during document creation. Save any registry settings
   virtual void SaveDocumentSettings();

   /// Use this method to log a message when
   /// the during application start-up
   /// Writes message to file named ("AppName.log")
   virtual void FailSafeLogMessage(const char* msg);

   CEAFMenu* GetMenu();
   
   /// Called to initialize the main menu
   virtual BOOL InitMainMenu();

   /// called by the framework to create the main menu object
   /// over-ride to create sub-classed types
   virtual CEAFMenu* CreateMainMenu();

   CEAFPluginCommandManager* GetPluginCommandManager();

   virtual CEAFDocPluginManager* GetDocPluginManager();

   // Called by the framework to give plug-ins an opportunity to integrated with the
   // user interface of the application. Plug-ins can add toolbars, menu items, and keyboard accelerators
   virtual void DoIntegrateWithUI(BOOL bIntegrate);

   UINT CreateToolBar(LPCTSTR lpszName);
   CEAFToolBar* GetToolBar(UINT toolbarID);
   void DestroyToolBar(CEAFToolBar* pToolBar);
   void DestroyToolBar(UINT toolbarID);

   virtual long RegisterView(CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=NULL,int maxViewCount=-1);
   virtual void RemoveView(long key);
   virtual CView* CreateView(long key,LPVOID pData=0);

   /// called by the framework where there is an initialization failure
   virtual void InitFailMessage();

   // called before the document data is created/loaded
   virtual void OnCreateInitialize();

   // called after the document data is created/loaded
   virtual void OnCreateFinalize();

   virtual BOOL OpenTheDocument(LPCTSTR lpszPathName);
   virtual BOOL SaveTheDocument(LPCTSTR lpszPathName);

   virtual void HandleOpenDocumentError( HRESULT hr, LPCTSTR lpszPathName );
   virtual void HandleSaveDocumentError( HRESULT hr, LPCTSTR lpszPathName );

   virtual HRESULT ConvertTheDocument(LPCTSTR lpszPathName, CString* realFileName);
   virtual void HandleConvertDocumentError( HRESULT hr, LPCTSTR lpszPathName );

   // Called by the framework when the document is to be loaded and saved
   virtual HRESULT WriteTheDocument(IStructuredSave* pStrSave) = 0;
   virtual HRESULT LoadTheDocument(IStructuredLoad* pStrLoad) = 0;

   virtual void OnErrorDeletingBadSave(LPCTSTR lpszPathName,LPCTSTR lpszBackup);
   virtual void OnErrorRemaningSaveBackup(LPCTSTR lpszPathName,LPCTSTR lpszBackup);

   // The toolbar state for each document type is stored in the registry.
   // To keep them separate, each document type must supply a name for the toolbar section
   virtual CString GetToolbarSectionName() = 0;

protected:
   //{{AFX_MSG(CEAFStatusBar)
	afx_msg void OnUpdateViewStatusCenter(CCmdUI* pCmdUI);
	afx_msg void OnViewStatusCenter();
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
   //}}AFX_MSG

   // called by the framework when the status center status changes
   virtual void OnStatusChanged();

   virtual void DeleteContents();

   CEAFDocPluginManager m_DocPluginMgr;
   virtual CATID GetDocumentPluginCATID(); /// over ride this method and return the CATID for your doc plugins
   virtual BOOL LoadDocumentPlugins(); /// called by the framework to load EAFDocumentPlugin objects
   virtual void UnloadDocumentPlugins(); /// called by the framework to remove EAFDocumentPlugin objects

   DECLARE_MESSAGE_MAP()

private:
   CEAFMenu* m_pMainMenu;
   CEAFPluginCommandManager* m_pPluginCommandMgr;

   CEAFStatusCenter*    m_pStatusCenter;
   CStatusCenterDlg* m_pStatusCenterDlg;
   iStatusCenterEventSink* m_pStatusCenterEventSink;

   BOOL m_bUIIntegrated; // true if UI intergration happened


   // called after document is created and initialized (called from CEAFDocTemplate::InitialUpdateFrame with TRUE
   // and OnCloseDocument with FALSE). Encapusulates the overall procedure for UI integration.. Calls
   // DoIntegrateWithUI(bIntegrate) 
   void IntegrateWithUI(BOOL bIntegrate);

   friend CEAFDocTemplate;
   friend CEAFMainFrame;
   friend CMyStatusCenterEventSink;
};


