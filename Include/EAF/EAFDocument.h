///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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
class IEAFStatusCenterEventSink;
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
   virtual void OnUnitsModeChanging();
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
   virtual std::_tstring UndoName();
   virtual std::_tstring RedoName();
   virtual std::_tstring RepeatName();
   virtual CollectionIndexType GetTxnCount();
   virtual CollectionIndexType GetUndoCount();

   virtual void SetModifiedFlag(BOOL bModified = TRUE);

   // Sets/Gets the SaveMissingPluginDataFlag
   // When reading a document file, if it contains data from a plugin that is not
   // currently installed, the data for that plugin is saved in a temporary cache.
   // If this flag is set, the data for the missing plugin is saved in the file,
   // otherwise the data is not saved and it is lost forever.
   virtual void SetSaveMissingPluginDataFlag(BOOL bSaveDataFromMissingPlugins = TRUE);
   virtual BOOL GetSaveMissingPluginDataFlag();

   // called by the framework when an unwind exception is thrown
   // Calls OnUpdateAllViews with EAF_HINT_UPDATEERROR
   virtual void OnUpdateError(const CString& errorMsg);

   // MFC's UpdateAllViews is not virtual so there is no way to modify it's behavior
   // This method is virtual and can be over-ridden. It calls UpdateAllViews
   virtual void OnUpdateAllViews(CView* pSender, LPARAM lHint = 0L,CObject* pHint = NULL);

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFDocument)

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

   // Called by the framework during document creation. Load any registry settings.
   // Default implementation saves the UIHints settings
   // This method is pure because you must override it and call AFX_MANAGE_STATE(AfxGetStaticModuleState())
   // before calling into this method
   virtual void LoadDocumentSettings() = 0;
   
   // Called by the framework during document creation. Save any registry settings
   // Default implementation saves the UIHints settings
   // This method is pure because you must override it and call AFX_MANAGE_STATE(AfxGetStaticModuleState())
   // before calling into this method
   virtual void SaveDocumentSettings() = 0;

   // Use this method to log a message
   // during application start-up.
   // Writes message to file named ("AppName.log")
   virtual void FailSafeLogMessage(LPCTSTR msg);

   // returns the main menu object
   CEAFMenu* GetMainMenu();

   // returns the accelerator table
   CEAFAcceleratorTable* GetAcceleratorTable();

   // returns the plug-in command manager
   virtual CEAFPluginCommandManager* GetPluginCommandManager();

   // returns the document plugin manager
   virtual CEAFDocPluginManager* GetDocPluginManager();

   // Called by the framework to give plug-ins an opportunity to integrated with the
   // user interface of the application. Plug-ins can add toolbars, menu items, and keyboard accelerators
   virtual void DoIntegrateWithUI(BOOL bIntegrate);

   // Called by the framework to give plug-ins an opportunity to process command line options
   // Return TRUE if the command line options where handled
   virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo);

   ///////////////////////////////////////////////////////////
   // Toolbars

   // Creates a new toolbar, returns the toolbar id
   UINT CreateToolBar(LPCTSTR lpszName);

   // returns a toolbar for with an ID of toolbarID
   CEAFToolBar* GetToolBar(UINT toolbarID);

   // destroys a previously created toolbar. the toolbar must have been created with CreateToolBar for this document
   // the pointer can't be used after the toolbar is destroyed
   void DestroyToolBar(CEAFToolBar* pToolBar);

   // destroys a toolbar by id
   void DestroyToolBar(UINT toolbarID);

   virtual void LoadToolbarState();
   virtual void SaveToolbarState();

   //////////////////////////////////////////////////////////////
   // Views

   // registers a view with the doc/view model. returns a key value that is used to identify the view
   virtual long RegisterView(UINT nResourceID,IEAFCommandCallback* pCallback,CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=NULL,int maxViewCount=-1);

   // removes a previously registered view
   virtual void RemoveView(long key);

   // creates a view. pass optional creation data to the view through pData
   virtual CView* CreateView(long key,LPVOID pData=0);

   virtual void UpdateRegisteredView(long key,CView* pSender,LPARAM lHint,CObject* pHint);

   virtual std::vector<CView*> GetRegisteredView(long key);

   //////////////////////////////////////////////////////////////
   // Document Initialization

   /// called by the framework where there is an initialization failure
   virtual void InitFailMessage();

   // called before the document data is created/loaded
   virtual void OnCreateInitialize();

   // called after the document data is created/loaded
   virtual void OnCreateFinalize();

   // If true, a copy of the original file is created prior to
   // saving the document. The name of the backup file is
   // ~ilename (first character of original filename is replaced with ~)
   // If an error occurs while saving the file, the backup file is restored.
   void EnableBackupOnSave(BOOL bEnable);
   BOOL EnableBackupOnSave() const;

   virtual BOOL OpenTheDocument(LPCTSTR lpszPathName);
   virtual void HandleOpenDocumentError( HRESULT hr, LPCTSTR lpszPathName );

   virtual BOOL SaveTheDocument(LPCTSTR lpszPathName);
   virtual void HandleSaveDocumentError( HRESULT hr, LPCTSTR lpszPathName );

   virtual HRESULT ConvertTheDocument(LPCTSTR lpszPathName, CString* realFileName);
   virtual void HandleConvertDocumentError( HRESULT hr, LPCTSTR lpszPathName );

   // Called by the framework when the document is to be loaded and saved
   virtual HRESULT WriteTheDocument(IStructuredSave* pStrSave);
   virtual HRESULT LoadTheDocument(IStructuredLoad* pStrLoad);

   // Called by OpenDocumentRootNode to get the root node name
   // By default the root node name is pApp->m_pszAppName with all whitespace removed
   virtual CString GetRootNodeName();

   // Returns the version number of the root data block
   virtual Float64 GetRootNodeVersion();

   // Called before WriteTheDocument to write a root node BeginUnit block
   virtual HRESULT OpenDocumentRootNode(IStructuredSave* pStrSave);
   // Called after WriteTheDocument and after saving of plugin data to write a root node EndUnit block
   virtual HRESULT CloseDocumentRootNode(IStructuredSave* pStrSave);

   // Called before LoadTheDocument to read a root node BeginUnit block
   virtual HRESULT OpenDocumentRootNode(IStructuredLoad* pStrLoad);
   // Called after LoadTheDocument and after loading of plugin data to read a root node EndUnit block
   virtual HRESULT CloseDocumentRootNode(IStructuredLoad* pStrLoad);

   virtual void OnErrorDeletingBadSave(LPCTSTR lpszPathName,LPCTSTR lpszBackup);
   virtual void OnErrorRenamingSaveBackup(LPCTSTR lpszPathName,LPCTSTR lpszBackup);

   // You must override this method and call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before
   // calling __super::GetStatusBarMessageString(nID,rMessage).
   virtual BOOL GetStatusBarMessageString(UINT nID,CString& rMessage) const = 0;

   // You must override this method and call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before
   // calling __super::GetToolTipMessageString(nID,rMessage).
   virtual BOOL GetToolTipMessageString(UINT nID, CString& rMessage) const = 0;

   // The toolbar state for each document type is stored in the registry.
   // To keep them separate, each document type must supply a name for the toolbar section
   virtual CString GetToolbarSectionName() = 0;

   /////////////////////////////////////
   // UIHints
   void UIHints(BOOL bEnable);
   BOOL UIHints() const;
   UINT GetUIHintSettings() const;
   void SetUIHintSettings(UINT settings);
   virtual void ResetUIHints(); // called when all hints are reset/enabled

   /////////////////////////////////////
   // Help/Documentation

   // called by the framework when the documentation source changes
   virtual void DocumentationSourceChanged();

   // Returns the documentation set name for this document
   // The default implentation returns the IEAFAppPlugin's documentation
   // set name
   virtual CString GetDocumentationSetName();

   // Return the root location for application documentation
   // Can be in the form of a WEB URL (http://www.mysite.com/Documentation/")
   // or a file system URL (C:/Program Files/MyApp/Documentation/")
   // Include the last '/'
   // Documents may use this to build their documentation URLs
   virtual CString GetDocumentationRootLocation() = 0;

   // Return the URL for documation for the application
   // Called by GetDocumenentLocation to form the complete
   // documentation URL. The default documentation URL is:
   // For an Online source
   //     GetDocumentationRootLocation() + m_pszExeName + major.minor version number
   // For a local source
   //     GetDocumentationRootLocation() + m_pszExename
   virtual CString GetDocumentationURL();

   // Returns the name of the documentation map file
   virtual CString GetDocumentationMapFile();

   // Causes the documentation map file to be loaded
   virtual void LoadDocumentationMap();

   // Returns the full documentation URL for the given URL
   virtual eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL);


protected:
   //{{AFX_MSG(CEAFDocument)
	afx_msg void OnUpdateViewStatusCenter(CCmdUI* pCmdUI);
	afx_msg void OnViewStatusCenter();
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
   afx_msg void OnOptionsHints();
   //}}AFX_MSG

   virtual HINSTANCE GetResourceInstance();
   virtual void UpdateApplicationIcon();
   virtual void ResetApplicationIcon();

   /// called by the framework to create the main menu object
   virtual CEAFMenu* CreateMainMenu();
   /// Called to initialize the main menu
   virtual BOOL InitMainMenu();

   // called by the framework when the status center status changes
   virtual void OnStatusChanged();

   // called by the framework when the contents of the documents are to be deleted
   virtual void DeleteContents();

   /////////////////////////////////////////////////////////////////////
   // Plugins

   /// If you want to support plugins, over ride this method and return the CATID for your doc plugins
   /// default returns CLSID_NULL. If you are supporting plugins and want to manage them, provide a
   /// command handler that calls EAFManagerPlugins
   virtual CATID GetDocumentPluginCATID(); 

   /// called by the framework to load EAFDocumentPlugin objects
   virtual BOOL LoadDocumentPlugins(); 

   /// called by the framework to remove EAFDocumentPlugin objects
   virtual void UnloadDocumentPlugins(); 

   DECLARE_MESSAGE_MAP()

protected:
   BOOL m_bUIHints;
   UINT m_UIHintSettings;

private:
   CEAFMenu* m_pMainMenu;
   CEAFPluginCommandManager* m_pPluginCommandMgr;
   CEAFDocPluginManager m_DocPluginMgr;

   HICON m_hMainFrameBigIcon;
   HICON m_hMainFrameSmallIcon;

   CEAFStatusCenter*    m_pStatusCenter;
   CStatusCenterDlg* m_pStatusCenterDlg;
   IEAFStatusCenterEventSink* m_pStatusCenterEventSink;

   BOOL m_bUIIntegrated; // true if UI intergration happened


   CString m_strDocumentationMapFile;
   std::map<UINT,CString> m_HelpTopics;

   BOOL m_bEnableSaveBackup; // if true, backup files are created during the save process


   // called after document is created and initialized (called from CEAFDocTemplate::InitialUpdateFrame with TRUE
   // and OnCloseDocument with FALSE). Encapusulates the overall procedure for UI integration.. Calls
   // DoIntegrateWithUI(bIntegrate) 
   void IntegrateWithUI(BOOL bIntegrate);

   friend CEAFDocTemplate;
   friend CEAFMainFrame;
   friend CMyStatusCenterEventSink;
};


