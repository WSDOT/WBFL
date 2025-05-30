///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// EAFDocument.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BackDoor.h"
#include <EAF\EAFDocument.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\PluginApp.h>
#include <EAF\DocTemplateRegistrar.h>
#include <EAF\EAFHints.h>
#include <EAF\EAFView.h>
#include <EAF\EAFDataRecoveryHandler.h>

// Logging
#include <iostream>
#include <fstream>
#include <System\Time.h>
#include <MFCTools\VersionInfo.h>

#include <EAF\TxnManager.h>

#include <EAF\PluginCommandManager.h>

#include "StatusCenterDlg.h"

class CMyStatusCenterEventSink : public WBFL::EAF::StatusCenterEventSink
{
public:
   CMyStatusCenterEventSink(CEAFDocument* pDoc)
   {
      m_pDoc = pDoc;
   }

   virtual void OnStatusItemAdded(std::shared_ptr<const WBFL::EAF::StatusItem> pItem)
   {
      m_pDoc->OnStatusChanged();
   }

   virtual void OnStatusItemRemoved(StatusItemIDType id)
   {
      m_pDoc->OnStatusChanged();
   }

private:
   CEAFDocument* m_pDoc;
};

// CEAFDocument

IMPLEMENT_DYNAMIC(CEAFDocument, CDocument)

CEAFDocument::CEAFDocument()
{
   m_PluginCommandMgr = std::make_shared<WBFL::EAF::PluginCommandManager>();

   m_pStatusCenterEventSink = std::make_shared<CMyStatusCenterEventSink>(this);

   m_pStatusCenter = std::make_unique<WBFL::EAF::StatusCenter>();
   m_StatusCenterEventSinkCookie = m_pStatusCenter->RegisterEventSink(m_pStatusCenterEventSink);

   m_pStatusCenterDlg = std::make_unique<CStatusCenterDlg>(*m_pStatusCenter);

   m_DocPluginMgr.SetParent(this);

   CEAFApp* pApp = EAFGetApp();
   pApp->AddUnitModeListener(this);

   m_bUIIntegrated = FALSE;
   m_bEnableSaveBackup = TRUE;

   m_bUIHints = TRUE;
   m_UIHintSettings = EAF_UIHINT_ENABLE_ALL;
}

CEAFDocument::~CEAFDocument()
{
   CHECK( m_MainMenu == nullptr ); // this should have been deleted by now!

   CEAFApp* pApp = EAFGetApp();
   pApp->RemoveUnitModeListener(this);

   m_pStatusCenter->UnregisterEventSink(m_StatusCenterEventSinkCookie);
}


BEGIN_MESSAGE_MAP(CEAFDocument, CDocument)
   ON_UPDATE_COMMAND_UI(EAFID_VIEW_STATUSCENTER, OnUpdateViewStatusCenter)
   ON_COMMAND(EAFID_VIEW_STATUSCENTER,OnViewStatusCenter)
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateUndo)
	ON_COMMAND(ID_EDIT_REDO, OnRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateRedo)
   ON_COMMAND(EAFID_OPTIONS_HINTS, OnOptionsHints)
END_MESSAGE_MAP()


BOOL CEAFDocument::OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
   // Do the regular command routing first
   BOOL bResult = CDocument::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
   if ( bResult )
   {
      return bResult;
   }

   // Next, see if anyone registered callback commands
   auto [bSuccess, nPluginCmdID, pCallback] = m_PluginCommandMgr->GetCommandCallback(nID);
   if ( bSuccess && pCallback )
   {
      // process the callback command
      bResult = pCallback->OnCommandMessage(nPluginCmdID,nCode,pExtra,pHandlerInfo);
      if ( bResult )
      {
         return bResult;
      }
   }

   // normal mfc command routing will get the message to the application plugin if it
   // handles the command (See CEAFApp::OnCmdMsg)

   // the command wasn't handled here!
   return FALSE;
}

void CEAFDocument::OnUpdateError(const CString& errorMsg)
{
   CString my_string = errorMsg;
   OnUpdateAllViews(0,EAF_HINT_UPDATEERROR,(CObject*)&my_string);
}

void CEAFDocument::OnUpdateAllViews(CView* pSender, LPARAM lHint,CObject* pHint)
{
   UpdateAllViews(pSender,lHint,pHint);
}

/////////////////////////////////////////////////////////////////////////////
// CEAFDocument diagnostics

#ifdef _DEBUG
void CEAFDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CEAFDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

void CEAFDocument::Serialize(CArchive& ar)
{
   ASSERT(FALSE); // should never get here... we aren't using CArchive serialization
}
#endif //_DEBUG

// CEAFDocument message handlers

std::shared_ptr<WBFL::EAF::Menu> CEAFDocument::GetMainMenu()
{
   return m_MainMenu;
}

std::shared_ptr<WBFL::EAF::AcceleratorTable> CEAFDocument::GetAcceleratorTable()
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   return pMainFrame->GetAcceleratorTable();
}

HINSTANCE CEAFDocument::GetResourceInstance()
{
   return GetInstanceHandle();
}

void CEAFDocument::UpdateApplicationIcon()
{
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   m_hMainFrameBigIcon = pFrame->GetIcon(TRUE);
   m_hMainFrameSmallIcon = pFrame->GetIcon(FALSE);
   HICON hIcon = ::LoadIcon(GetResourceInstance(),MAKEINTRESOURCE(pTemplate->GetResourceID()));
   if ( hIcon )
   {
      pFrame->SetIcon(hIcon,TRUE);
      pFrame->SetIcon(hIcon,FALSE);
   }
}

void CEAFDocument::ResetApplicationIcon()
{
   // put the main frame toolbar back the way it was
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();

   // Put the main frame icon back the way it was
   pMainFrame->SetIcon(m_hMainFrameBigIcon,TRUE);
   pMainFrame->SetIcon(m_hMainFrameSmallIcon,FALSE);
}

std::shared_ptr<WBFL::EAF::Menu> CEAFDocument::CreateMainMenu()
{
   return WBFL::EAF::Menu::CreateMenu(EAFGetMainFrame(),GetPluginCommandManager());
}

std::shared_ptr<WBFL::EAF::PluginCommandManager> CEAFDocument::GetPluginCommandManager()
{
   return m_PluginCommandMgr;
}

WBFL::EAF::DocPluginManager* CEAFDocument::GetDocPluginMgr()
{
   return &m_DocPluginMgr;
}

BOOL CEAFDocument::InitMainMenu()
{
   // Set up the menu mapping stuff before initializing agents
   m_MainMenu = CreateMainMenu();
   return TRUE;
}

void CEAFDocument::IntegrateWithUI(BOOL bIntegrate)
{
   ATLASSERT(m_bUIIntegrated != bIntegrate);

   // This function is called from CEAFDocTemplate::OnCreateFinalize() and OnCloseDocument()

   if ( bIntegrate )
   {
      InitMainMenu();
   }

   // save toolbar state before they are removed
   if ( !bIntegrate )
   {
      SaveToolbarState();
   }

   DoIntegrateWithUI(bIntegrate);

   // load toolbar state after toolbars are created
   if ( bIntegrate )
   {
      LoadToolbarState();
   }

   m_bUIIntegrated = bIntegrate;
}

void CEAFDocument::DoIntegrateWithUI(BOOL bIntegrate)
{
   auto* pPluginMgr = GetDocPluginMgr();
   auto nPlugins = pPluginMgr->GetPluginCount();
   for (auto idx = 0; idx < nPlugins; idx++)
   {
      auto plugin = pPluginMgr->GetPlugin(idx);
      plugin->IntegrateWithUI(bIntegrate);
   }
}

BOOL CEAFDocument::ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo)
{
   auto* pPluginMgr = GetDocPluginMgr();
   auto nPlugins = pPluginMgr->GetPluginCount();
   for (auto idx = 0; idx < nPlugins; idx++)
   {
      auto plugin = pPluginMgr->GetPlugin(idx);

      auto cmdLinePlugin = std::dynamic_pointer_cast<WBFL::EAF::IDocCommandLine>(plugin);
      if (cmdLinePlugin)
      {
         if (cmdLinePlugin->ProcessCommandLineOptions(cmdInfo))
         {
            return TRUE; // handled
         }
      }
   }

   return FALSE;
}

UINT CEAFDocument::CreateToolBar(LPCTSTR lpszName)
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   return pMainFrame->CreateToolBar(lpszName,GetPluginCommandManager());
}

std::shared_ptr<WBFL::EAF::ToolBar> CEAFDocument::GetToolBar(UINT toolbarID)
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   return pMainFrame->GetToolBar(toolbarID);
}

void CEAFDocument::DestroyToolBar(UINT toolbarID)
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->DestroyToolBar(toolbarID);
}

void CEAFDocument::LoadToolbarState()
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->LoadBarState(CString("Toolbars\\")+GetToolbarSectionName());
   pMainFrame->ResizeToolBarButtons();
}

void CEAFDocument::SaveToolbarState()
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->SaveBarState(CString("Toolbars\\")+GetToolbarSectionName());
}

long CEAFDocument::RegisterView(UINT nResourceID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass, HMENU hSharedMenu, int maxViewCount)
{
   if (hSharedMenu == nullptr)
   {
      CEAFMainFrame* pMainFrame = EAFGetMainFrame();
      hSharedMenu = pMainFrame->GetMenu()->GetSafeHmenu();
   }

   CEAFDocTemplate* pNewDocTemplate = new CEAFDocTemplate(nResourceID, pCallback, GetRuntimeClass(), pFrameClass, pViewClass, hSharedMenu, maxViewCount);

   CEAFApp* pApp = EAFGetApp();
   auto pRegistrar = pApp->GetDocTemplateRegistrar();

   long key = pRegistrar->AddDocTemplate(pNewDocTemplate);
   return key;
}

void CEAFDocument::RemoveView(long key)
{
   CEAFApp* pApp = EAFGetApp();
   auto pRegistrar = pApp->GetDocTemplateRegistrar();
   pRegistrar->RemoveDocTemplate(key);
}

CView* CEAFDocument::CreateView(long key,LPVOID pData)
{
   CEAFApp* pApp = EAFGetApp();

   // if this assert fires, you probably added AFX_MANAGE_STATE(AfxGetStaticModuleState())
   // in the scope of calling this method
   // Try removing AFX_MANAGE_STATE or re-scoping it
   ASSERT(pApp->IsKindOf(RUNTIME_CLASS(CEAFApp)));

   // the view class will call GetDocument()->GetDocTemplate() in its
   // OnInitialUpdate method. The template that will be returned is pMyTemplate and not
   // the pTemplate pointer we get below.
   //
   // Set the create data into this template
   CEAFDocTemplate* pMyTemplate = (CEAFDocTemplate*)GetDocTemplate();
   pMyTemplate->SetViewCreationData(pData);

   CEAFMainFrame* pMainFrame = EAFGetMainFrame();

   auto pRegistrar = pApp->GetDocTemplateRegistrar();
   CEAFDocTemplate*          pTemplate  = pRegistrar->GetDocTemplate(key);
   pTemplate->SetViewCreationData(pData);
   CView*                    pView      = pMainFrame->CreateOrActivateFrame(pTemplate);
   
   // done with the create data, so nullptr it out
   pTemplate->SetViewCreationData(nullptr);
   pMyTemplate->SetViewCreationData(nullptr);

   return pView;
}

void CEAFDocument::UpdateRegisteredView(long key,CView* pSender,LPARAM lHint,CObject* pHint)
{
   CEAFApp* pApp = EAFGetApp();

   // if this assert fires, you probably added AFX_MANAGE_STATE(AfxGetStaticModuleState())
   // in the scope of calling this method
   // Try removing AFX_MANAGE_STATE or re-scoping it
   ASSERT(pApp->IsKindOf(RUNTIME_CLASS(CEAFApp)));

   auto pRegistrar = pApp->GetDocTemplateRegistrar();
   CEAFDocTemplate*          pTemplate  = pRegistrar->GetDocTemplate(key);
   if ( pTemplate == nullptr )
   {
      // the template was not found.... probably a bad key
      return;
   }

   CRuntimeClass* pViewClass = pTemplate->GetViewClass();

   CEAFMainFrame* pMainFrame = EAFGetMainFrame();

   POSITION pos = GetFirstViewPosition();
   while (pos != nullptr)
   {
      CView* pView = GetNextView(pos);
      if (pView->IsKindOf(pViewClass))
      {
         if ( pView != pSender )
         {
            if ( pView->IsKindOf(RUNTIME_CLASS(CEAFView)) )
            {
               // EAFDocuments can only call OnUpdate on CEAFViews
               // OnUpdate is a protected method so access is restricted
               ((CEAFView*)pView)->OnUpdate(pSender,lHint,pHint);
            }
            else
            {
               // OnInitialUpdate calls OnUpdate, however, the hint parameters can't be sent
               pView->OnInitialUpdate();
            }
         }
      }
   }
}

std::vector<CView*> CEAFDocument::GetRegisteredView(long key)
{
   CEAFApp* pApp = EAFGetApp();
   std::vector<CView*> vViews;

   // if this assert fires, you probably added AFX_MANAGE_STATE(AfxGetStaticModuleState())
   // in the scope of calling this method
   // Try removing AFX_MANAGE_STATE or re-scoping it
   ASSERT(pApp->IsKindOf(RUNTIME_CLASS(CEAFApp)));

   auto pRegistrar = pApp->GetDocTemplateRegistrar();
   CEAFDocTemplate*          pTemplate  = pRegistrar->GetDocTemplate(key);
   if ( pTemplate == nullptr )
   {
      // the template was not found.... probably a bad key
      return vViews;
   }

   CRuntimeClass* pViewClass = pTemplate->GetViewClass();

   CEAFMainFrame* pMainFrame = EAFGetMainFrame();

   POSITION pos = GetFirstViewPosition();
   while (pos != nullptr)
   {
      CView* pView = GetNextView(pos);
      if (pView->IsKindOf(pViewClass))
      {
         vViews.push_back(pView);
      }
   }

   return vViews;
}

void CEAFDocument::SetModifiedFlag(BOOL bModified)
{
   CDocument::SetModifiedFlag(bModified);

   CEAFMainFrame* pFrame = EAFGetMainFrame();

   pFrame->EnableModifiedFlag(IsModified());
}

void CEAFDocument::SetSaveMissingPluginDataFlag(BOOL bSaveDataFromMissingPlugins)
{
   GetDocPluginMgr()->SetSaveMissingPluginDataFlag(bSaveDataFromMissingPlugins);
}

BOOL CEAFDocument::GetSaveMissingPluginDataFlag()
{
   return GetDocPluginMgr()->GetSaveMissingPluginDataFlag();
}

void CEAFDocument::InitFailMessage()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CString msg, msg1, msg2;

   CString strLogFile = EAFGetApp()->m_pszExeName;
   strLogFile += _T(".log");

   AfxFormatString1(msg1, IDS_E_BADINSTALL, EAFGetApp()->m_pszExeName );
   AfxFormatString1( msg2, IDS_E_PROBPERSISTS, strLogFile );
   AfxFormatString2(msg, IDS_E_FORMAT, msg1, msg2 );
   AfxMessageBox( msg );
}

BOOL CEAFDocument::Init()
{
   if ( !LoadDocumentPlugins() )
   {
      return FALSE;
   }

   LoadDocumentSettings();
   LoadDocumentationMap();

   UpdateApplicationIcon();

   return TRUE;
}

void CEAFDocument::LoadDocumentSettings()
{
   if ( m_bUIHints )
   {
      // Loads the UI Hints settings
      // Be sure to call AFX_MANAGE_STATE(AfxGetStaticModuleState())
      // in your class before calling this method
      CWinApp* pApp = AfxGetApp();
      m_UIHintSettings = pApp->GetProfileInt(_T("Settings"),_T("UIHints"),EAF_UIHINT_ENABLE_ALL); // default, all hints enabled
   }
}

void CEAFDocument::SaveDocumentSettings()
{
   if ( m_bUIHints )
   {
      // Saves the UI Hints settings
      // Be sure to call AFX_MANAGE_STATE(AfxGetStaticModuleState())
      // in your class before calling this method
      CWinApp* pApp = AfxGetApp();
      VERIFY(pApp->WriteProfileInt(_T("Settings"),_T("UIHints"),m_UIHintSettings));
   }
}

CATID CEAFDocument::GetDocumentPluginCATID()
{
   return CLSID_NULL;
}

BOOL CEAFDocument::LoadDocumentPlugins()
{
   CATID catid = GetDocumentPluginCATID();
   if ( catid == CLSID_NULL )
   {
      return TRUE; // no plugins for this document type
   }

   GetDocPluginMgr()->SetCATID(catid);
   if (GetDocPluginMgr()->LoadPlugins())
   {
      GetDocPluginMgr()->InitPlugins();
   }

   return TRUE;
}

void CEAFDocument::UnloadDocumentPlugins()
{
   GetDocPluginMgr()->UnloadPlugins();
}

void CEAFDocument::OnUpdateViewStatusCenter(CCmdUI* pCmdUI)
{
   CString str;
   str.Format(_T("%s Status Center"),m_pStatusCenterDlg->IsWindowVisible() ? _T("Hide") : _T("Show"));
   pCmdUI->SetText(str);
}

void CEAFDocument::OnViewStatusCenter()
{
   m_pStatusCenterDlg->ShowWindow(m_pStatusCenterDlg->IsWindowVisible() ? SW_HIDE : SW_SHOW);
}

BOOL CEAFDocument::SaveModified()
{
   // called when a document is closing. if autosave is enabled, we want to
   // always save a modified document unless the document is new and has not yet saved (pathname is empty).
   if (!m_strPathName.IsEmpty() && IsModified() && AfxGetApp() && AfxGetApp()->SupportsAutosaveAtInterval())
   {
      DoFileSave();
   }

   return __super::SaveModified();
}

BOOL CEAFDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
   {
		return FALSE;
   }

   // Initialize the document
   if ( !Init() ) // init menus and toolbars... subclasses do more initialization
   {
      return FALSE;
   }

   SetModifiedFlag(TRUE);
   OnStatusChanged();

   // update the mainframe
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->UpdateFrameTitle(_T("Untitled"));
   pMainFrame->EnableModifiedFlag( IsModified() );

   return TRUE;
}

BOOL CEAFDocument::OnNewDocumentFromTemplate(LPCTSTR lpszPathName)
{
   CString msg;
   msg.Format(_T("New document from template: %s"), lpszPathName);
   WBFL::System::Logger::Info((LPCTSTR)msg);

   if ( !OnNewDocument() )
   {
      return FALSE;
   }

   if ( OpenTheDocument( lpszPathName ) )
   {
      SetModifiedFlag(TRUE);
      return TRUE;
   }

   return FALSE;
}

void CEAFDocument::EnableBackupOnSave(BOOL bEnable)
{
   m_bEnableSaveBackup = bEnable;
}

BOOL CEAFDocument::EnableBackupOnSave() const
{
   return m_bEnableSaveBackup;
}

BOOL CEAFDocument::OnOpenDocument(LPCTSTR lpszPathName)
{
   CString msg;
   msg.Format(_T("Opening document: %s"), lpszPathName);
   WBFL::System::Logger::Info((LPCTSTR)msg);

   CWaitCursor cursor;

   // don't call the base class method
   // we want to totally replace the default functionality
   //if (!CDocument::OnOpenDocument(lpszPathName))
   //	return FALSE;
	
   // Initialize the document
   if ( !Init() ) // init menus and toolbars... subclasses do more initialization
   {
      return FALSE;
   }

   BOOL bDocumentOpened = OpenTheDocument( lpszPathName );

   // update the mainframe title
   if (bDocumentOpened == TRUE)
   {
      SetPathName(lpszPathName);

      CEAFMainFrame* pMainFrame = EAFGetMainFrame();
      pMainFrame->UpdateFrameTitle(lpszPathName);
   }

   return bDocumentOpened;
}

BOOL CEAFDocument::OnSaveDocument(LPCTSTR lpszPathName)
{
   // Not using MFC Serialization so don't call base class.
   //	return CDocument::OnSaveDocument(lpszPathName);

   BOOL bDidCreateBackup = FALSE;
   CString strBackupFile(lpszPathName);
   if ( m_bEnableSaveBackup )
   {
      //
      // If the file already exists, back it up before we save
      //

      // Make sure this file actually exists before we attempt to back it up
      HANDLE hFile;
      WIN32_FIND_DATA find_file_data;
      hFile = ::FindFirstFile( lpszPathName, &find_file_data );
      if ( hFile != INVALID_HANDLE_VALUE )
      {
         ::FindClose(hFile); // don't want no stinking resource leaks.
        
         // OK, The file exists.
         // check to make sure it's not read-only
	      DWORD dwAttrib = GetFileAttributes(lpszPathName);
	      if (dwAttrib & FILE_ATTRIBUTE_READONLY)
         {
            CString msg;
            msg.Format(_T("Cannot save file. The file %s is read-only. Please try to save again to a different file."), lpszPathName);
            AfxMessageBox(msg );
            return FALSE;
         }

         // Create a backup copy of the last good save.
         // Backup filename is original filename, except the first
         // letter is a ~.
         int idx = strBackupFile.ReverseFind( _T('\\') ); // look for last '\'. 
                                                  // This is one character before the 
                                                  // beginning of the filename
         ASSERT( idx != -1 ); // '\' wasn't found
         idx++;
         strBackupFile.SetAt(idx,_T('~'));

         bDidCreateBackup = ::CopyFile( lpszPathName, strBackupFile, FALSE );
         if ( !bDidCreateBackup && AfxMessageBox(IDS_E_UNSAFESAVE,MB_YESNO) == IDNO )
         {
            return FALSE;
         }
      }
   }

   // Attempt to save the document
   if ( !SaveTheDocument( lpszPathName ) && bDidCreateBackup )
   {
      // Save failed... Restore the backup (if it was created)

      // Delete the bad save
      BOOL bDidDelete = ::DeleteFile( lpszPathName );
      if ( !bDidDelete )
      {
         // Oops... Couldn't delete it.
         // Alter the user so he's not screwed.
         OnErrorDeletingBadSave(lpszPathName,strBackupFile);
      }

      if ( bDidDelete )
      {
         // OK, We were able to delete the bad save.
         // Rename the backup to the original name.
         BOOL bDidMove = ::MoveFile( strBackupFile, lpszPathName ); // Rename the file
         if ( !bDidMove )
         {
            // Oops... A file with the original name is gone, and we can't
            // rename the backup to the file with the original name.
            // Alert the user so he's not screwed.
            OnErrorRenamingSaveBackup(lpszPathName,strBackupFile);
         }
      }

      return FALSE;
   }
   else
   {
      // Save was successful... Delete the backup if one was created
      if ( bDidCreateBackup )
      {
         ::DeleteFile( strBackupFile );
      }
      // It's no big deal if this call fails.  The user is simply left
      // with an out of date backup file on their disk drive.
   }

   SetModifiedFlag( FALSE );
   OnStatusChanged();

   // update title frame if this is not an autosave document
   CEAFApp* pApp = EAFGetApp();
   CEAFDataRecoveryHandler* pHandler = (CEAFDataRecoveryHandler*)(pApp->GetDataRecoveryHandler());
   if (!pHandler->IsAutosaving())
   {
      CEAFMainFrame* pMainFrame = EAFGetMainFrame();
      pMainFrame->UpdateFrameTitle(lpszPathName);
   }

   return TRUE;
}

void CEAFDocument::OnErrorDeletingBadSave(LPCTSTR lpszPathName,LPCTSTR lpszBackup)
{
   CString msg;
   msg.Format(_T("%s\n%s%s%s\n%s\n%s%s\n%s%s%s%s"),
              _T("An error occurred while recovering your last successful save."),
              _T("It is highly likely that the file "), lpszPathName, _T(" is corrupt."),
              _T("To recover from this error,"),
              _T("   1. Delete "), lpszPathName,
              _T("   2. Rename "), lpszBackup, _T(" to "), lpszPathName);
   
   AfxMessageBox(msg);
}

void CEAFDocument::OnErrorRenamingSaveBackup(LPCTSTR lpszPathName,LPCTSTR lpszBackup)
{
   CString msg;
   msg.Format(_T("%s\n%s%s%s\n%s\n%s%s%s\n%s%s%s%s"),
              _T("An error occurred while recovering your last successful save."),
              _T("It is highly likely that the file "), lpszPathName, _T(" no longer exists."),
              _T("To recover from this error,"),
              _T("   1. If "), lpszPathName, _T(" exists, delete it."),
              _T("   2. Rename "), lpszBackup, _T(" to "), lpszPathName);
   
   AfxMessageBox(msg);
}

BOOL CEAFDocument::OpenTheDocument(LPCTSTR lpszPathName)
{
   HRESULT hr = S_OK;

   CString real_file_name; // name of actual file to be read may be different than lpszPathName
   HRESULT hr_convert = ConvertTheDocument(lpszPathName, &real_file_name);
   // convert document. if file was converted, then we need to delete the converted file at the end
   if ( FAILED(hr_convert) )
   {
      HandleConvertDocumentError(hr_convert,lpszPathName);
      return FALSE;
   }

   {
      // NOTE: this scoping block is here for a reason. The IStructuredLoad must be
      //       destroyed before the file can be deleted.
      CComPtr<IStructuredLoad> pStrLoad;
      hr = ::CoCreateInstance( CLSID_StructuredLoad, nullptr, CLSCTX_INPROC_SERVER, IID_IStructuredLoad, (void**)&pStrLoad );
      if ( FAILED(hr) )
      {
         // We are not aggregating so we should CoCreateInstance should
         // never fail with this HRESULT
         ASSERT( hr != CLASS_E_NOAGGREGATION );

         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }

      hr = pStrLoad->Open( real_file_name );
      if ( FAILED(hr) )
      {
         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }

      hr = OpenDocumentRootNode(pStrLoad);
      if ( FAILED(hr) )
      {
         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }

      HRESULT hrLoad = LoadTheDocument(pStrLoad);
      if ( FAILED(hrLoad) )
      {
         HandleOpenDocumentError( hrLoad, lpszPathName );
         return FALSE;
      }

      // If this document type supports plugins, load the plug in data
      if ( GetDocumentPluginCATID() != CLSID_NULL )
      {
         hr = GetDocPluginMgr()->LoadPluginData(pStrLoad);
         if (FAILED(hr))
         {
            HandleOpenDocumentError(hr, lpszPathName);
            return FALSE;
         }
      }

      hr = CloseDocumentRootNode(pStrLoad);
      if ( FAILED(hr) )
      {
         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }
      
      hr = pStrLoad->Close();
      if ( FAILED(hr) )
      {
         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }

      SetModifiedFlag(hrLoad == S_FALSE ? TRUE : FALSE);
      OnStatusChanged();
   }

   if ( hr_convert == S_OK )
   {
      // file was converted and written to a temporary file. delete the temp file
      VERIFY(::DeleteFile(real_file_name));
   }

   return TRUE;
}

HRESULT CEAFDocument::ConvertTheDocument(LPCTSTR lpszPathName, CString* realFileName)
{
   // default - do nothing
   *realFileName = CString(lpszPathName);
   return S_FALSE; // did not convert
}

void CEAFDocument::HandleConvertDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
   CString strMsg;
   strMsg.Format(_T("An error occurred while converting %s (%d)"),lpszPathName,hr);
   AfxMessageBox(strMsg,MB_OK | MB_ICONEXCLAMATION);
}

void CEAFDocument::HandleOpenDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
   CString strMsg;
   strMsg.Format(_T("An error occurred while opening %s (%d)"),lpszPathName,hr);
   AfxMessageBox(strMsg,MB_OK | MB_ICONEXCLAMATION);
}

void CEAFDocument::HandleSaveDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
   CString strMsg;
   strMsg.Format(_T("An error occurred while saving %s (%d)"),lpszPathName,hr);
   AfxMessageBox(strMsg,MB_OK | MB_ICONEXCLAMATION);
}

HRESULT CEAFDocument::WriteTheDocument(IStructuredSave* pStrSave)
{
   // Do nothing by default
   return S_OK;
}

HRESULT CEAFDocument::LoadTheDocument(IStructuredLoad* pStrLoad)
{
   // Do nothing by default
   return S_OK;
}

CString CEAFDocument::GetRootNodeName()
{
   CEAFApp* pApp = EAFGetApp();
   CString str = pApp->m_pszAppName;
   str.Trim();
   str.Replace(_T(" "),_T(""));
   return str;
}

Float64 CEAFDocument::GetRootNodeVersion()
{
   return 1.0;
}

HRESULT CEAFDocument::OpenDocumentRootNode(IStructuredSave* pStrSave)
{
   // Open the unit around the entire file
   return pStrSave->BeginUnit(GetRootNodeName(),GetRootNodeVersion());
}

HRESULT CEAFDocument::CloseDocumentRootNode(IStructuredSave* pStrSave)
{
   // close the unit around the entire file
   return pStrSave->EndUnit();
}

HRESULT CEAFDocument::OpenDocumentRootNode(IStructuredLoad* pStrLoad)
{
   HRESULT hr = pStrLoad->BeginUnit(GetRootNodeName());
   if ( FAILED(hr))
   {
      return hr;
   }

   Float64 version;
   pStrLoad->get_Version(&version);
   if ( GetRootNodeVersion() < version )
   {
      return STRLOAD_E_BADVERSION;
   }

   return S_OK;
}

HRESULT CEAFDocument::CloseDocumentRootNode(IStructuredLoad* pStrLoad)
{
   return pStrLoad->EndUnit();
}

BOOL CEAFDocument::SaveTheDocument(LPCTSTR lpszPathName)
{
   CComPtr<IStructuredSave> pStrSave;

   HRESULT hr = ::CoCreateInstance( CLSID_StructuredSave, nullptr, 
	   CLSCTX_INPROC_SERVER, IID_IStructuredSave, (void**)&pStrSave );
   if ( FAILED(hr) )
   {
      // We are not aggregating so we should CoCreateInstance should
      // never fail with this HRESULT
      ASSERT( hr != CLASS_E_NOAGGREGATION );

      HandleSaveDocumentError( hr, lpszPathName );
      return FALSE;
   }

   hr = pStrSave->Open( lpszPathName );
   if ( FAILED(hr) )
   {
      HandleSaveDocumentError( hr, lpszPathName );
      return FALSE;
   }

   hr = OpenDocumentRootNode( pStrSave );
   if ( FAILED(hr) )
   {
      HandleSaveDocumentError( hr, lpszPathName );
      return FALSE;
   }

   hr = WriteTheDocument( pStrSave );
   if ( FAILED(hr) )
   {
      HandleSaveDocumentError( hr, lpszPathName );
      return FALSE;
   }

   // If this document type supports plugins, save the plug in data
   if ( GetDocumentPluginCATID() != CLSID_NULL )
   {
      hr = GetDocPluginMgr()->SavePluginData(pStrSave);
      if (FAILED(hr))
      {
         HandleSaveDocumentError(hr, lpszPathName);
         return FALSE;
      }
   }


   hr = CloseDocumentRootNode( pStrSave );
   if ( FAILED(hr) )
   {
      HandleSaveDocumentError( hr, lpszPathName );
      return FALSE;
   }

   hr = pStrSave->Close();
   if ( FAILED(hr) )
   {
      HandleSaveDocumentError( hr, lpszPathName );
      return FALSE;
   }
	
	return TRUE;
}

BOOL CEAFDocument::GetStatusBarMessageString(UINT nID,CString& rMessage) const
{
	// load appropriate string
   BOOL bHandled = FALSE;

	LPTSTR lpsz = rMessage.GetBuffer(255);
	if (AfxLoadString(nID, lpsz) != 0)
	{
		// first newline terminates actual string
		lpsz = _tcschr(lpsz, '\n');
		if (lpsz != nullptr)
      {
			*lpsz = '\0';
      }

      bHandled = TRUE;
	}
	else
	{
		// not found
		TRACE(traceAppMsg, 0, "Warning (CEAFDocument): no message line prompt for ID %d.\n", nID);
      bHandled = FALSE;
	}
	rMessage.ReleaseBuffer();

   return bHandled;
}

BOOL CEAFDocument::GetToolTipMessageString(UINT nID, CString& rMessage) const
{
   CString string;
   // load appropriate string
   BOOL bHandled = FALSE;

   if ( string.LoadString(nID) )
	{
		// tip is after first newline 
      int pos = string.Find('\n');
      if ( 0 < pos )
      {
         rMessage = string.Mid(pos+1);
      }

      bHandled = TRUE;
	}
	else
	{
		// not found
		TRACE1("Warning (CEAFDocument): no tool tip for ID %d.\n", nID);
      bHandled = FALSE;
	}

   return bHandled;
}

void CEAFDocument::EnableUIHints(BOOL bEnable)
{
   m_bUIHints = bEnable;
}

BOOL CEAFDocument::EnableUIHints() const
{
   return m_bUIHints;
}

UINT CEAFDocument::GetUIHintSettings() const
{
   return m_UIHintSettings;
}

void CEAFDocument::SetUIHintSettings(UINT settings)
{
   m_UIHintSettings = settings;
   if ( m_UIHintSettings == EAF_UIHINT_ENABLE_ALL )
   {
      OnUIHintsReset();
   }
}

void CEAFDocument::OnUIHintsReset()
{
   // Does nothing by default
}

void CEAFDocument::DocumentationSourceChanged()
{
   m_strDocumentationMapFile.Empty();
}

CString CEAFDocument::GetDocumentationSetName()
{
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   auto pluginApp = pTemplate->GetPluginApp();
   return pluginApp->GetDocumentationSetName();
}

CString CEAFDocument::GetDocumentationURL()
{
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   auto pluginApp = pTemplate->GetPluginApp();
   return pluginApp->GetDocumentationURL();
}

CString CEAFDocument::GetDocumentationMapFile()
{
   if ( m_strDocumentationMapFile.IsEmpty() )
   {
      m_strDocumentationMapFile = EAFGetDocumentationMapFile(GetDocumentationSetName(),GetDocumentationURL());
   }
   return m_strDocumentationMapFile;
}

void CEAFDocument::LoadDocumentationMap()
{
   CString mapFileName(GetDocumentationMapFile());
   VERIFY(EAFLoadDocumentationMap(mapFileName,m_HelpTopics));
}

std::pair<WBFL::EAF::HelpResult,CString> CEAFDocument::GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID)
{
   CString strDocSetName(lpszDocSetName);
   if ( GetDocumentationSetName() == strDocSetName )
   {
      // help topic is supposed to be part of this documentation set
      CString strBaseURL = GetDocumentationURL();

      std::map<UINT,CString>::iterator found(m_HelpTopics.find(nHID));
      if ( found == m_HelpTopics.end() )
      {
         return { WBFL::EAF::HelpResult::TopicNotFound,CString() };
      }

      CString strURL;
      strURL.Format(_T("%s%s"),strBaseURL,found->second);
      return { WBFL::EAF::HelpResult::OK,strURL };
   }
   else
   {
      // check to see of the help topic and documentation set belongs to one of our plug-ins
      auto* pDocPluginMgr = GetDocPluginMgr();
      auto nPlugins = pDocPluginMgr->GetPluginCount();
      for (auto pluginIdx = 0; pluginIdx < nPlugins; pluginIdx++)
      {
         auto pDocPlugin = pDocPluginMgr->GetPlugin(pluginIdx);
         CHECK(pDocPlugin != nullptr);

         if (pDocPlugin->GetDocumentationSetName() == strDocSetName)
         {
            return pDocPlugin->GetDocumentLocation(lpszDocSetName, nHID);
         }
      }
   }

   // if we got this far, the help topic still wasn't found... kick it up to our
   // parent app plug-in
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   auto pluginApp = pTemplate->GetPluginApp();
   return pluginApp->GetDocumentLocation(lpszDocSetName,nHID);
}

void CEAFDocument::OnCloseDocument()
{
   SetModifiedFlag(FALSE);
   OnStatusChanged();

   // remove ui elements that plug-ins provided
   if ( m_bUIIntegrated )
   {
      CHECK(m_MainMenu != nullptr);
      IntegrateWithUI(FALSE);
      GetPluginCommandManager()->Clear();
   }

   SaveDocumentSettings();

   UnloadDocumentPlugins();

   ResetApplicationIcon();

   // this has to come last as the document deletes itself
   CDocument::OnCloseDocument();

   // DON'T DO ANYTHING ELSE HERE WITH THE DOCUMENT.... Document has deleted itself

   // this must come after OnCloseDocument we the menus reset if there is a start page

   // put the main frame toolbar back the way it was
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->ShowMainFrameToolBar();
   pMainFrame->ShowStartPage();
   pMainFrame->OnUpdateFrameTitle(FALSE); // now that the document is closed, set the frame title to its default state

   // need to clean up the status bar
   CEAFStatusBar* pStatusBar = pMainFrame->GetStatusBar();
   if ( pStatusBar )
   {
      pStatusBar->Reset();
   }
}

WBFL::EAF::StatusCenter& CEAFDocument::GetStatusCenter()
{
   return *m_pStatusCenter;
}

void CEAFDocument::OnUnitsModeChanging()
{
   OnUpdateAllViews(nullptr,EAF_HINT_UNITS_CHANGING,0);
}

void CEAFDocument::OnUnitsModeChanged(WBFL::EAF::UnitMode newUnitMode)
{
   OnUpdateAllViews(nullptr,EAF_HINT_UNITS_CHANGED,0);
}

void CEAFDocument::Execute(const WBFL::EAF::Transaction& rTxn)
{
   CWaitCursor wait;
   WBFL::EAF::TxnManager::GetInstance().Execute(rTxn);
}

void CEAFDocument::Execute(std::unique_ptr<WBFL::EAF::Transaction>&& pTxn)
{
   CWaitCursor wait;
   WBFL::EAF::TxnManager::GetInstance().Execute(std::move(pTxn));
}

void CEAFDocument::Undo()
{
   CWaitCursor wait;
   WBFL::EAF::TxnManager::GetInstance().Undo();
}

void CEAFDocument::Redo()
{
   CWaitCursor wait;
   WBFL::EAF::TxnManager::GetInstance().Redo();
}

void CEAFDocument::Repeat()
{
   CWaitCursor wait;
   WBFL::EAF::TxnManager::GetInstance().Repeat();
}

bool CEAFDocument::CanUndo() const
{
   return WBFL::EAF::TxnManager::GetInstance().CanUndo();
}

bool CEAFDocument::CanRedo() const
{
   return WBFL::EAF::TxnManager::GetInstance().CanRedo();
}

bool CEAFDocument::CanRepeat() const
{
   return WBFL::EAF::TxnManager::GetInstance().CanRepeat();
}

std::_tstring CEAFDocument::UndoName() const
{
   return WBFL::EAF::TxnManager::GetInstance().UndoName();
}

std::_tstring CEAFDocument::RedoName() const
{
   return WBFL::EAF::TxnManager::GetInstance().RedoName();
}

std::_tstring CEAFDocument::RepeatName() const
{
   return WBFL::EAF::TxnManager::GetInstance().RepeatName();
}

IndexType CEAFDocument::GetTxnCount() const
{
   return WBFL::EAF::TxnManager::GetInstance().GetTxnCount();
}

IndexType CEAFDocument::GetUndoCount() const
{
   return WBFL::EAF::TxnManager::GetInstance().GetUndoCount();
}

void CEAFDocument::OnUndo() 
{
   Undo();
}

void CEAFDocument::OnUpdateUndo(CCmdUI* pCmdUI) 
{
   if ( CanUndo() )
   {
      pCmdUI->Enable(TRUE);
      CString strCommand;
      strCommand.Format(_T("Undo %s\tCtrl+Z"),UndoName().c_str());
      pCmdUI->SetText(strCommand);
   }
   else
   {
      pCmdUI->SetText(_T("Undo\tCtrl+Z"));
      pCmdUI->Enable(FALSE);
   }
}

void CEAFDocument::OnRedo() 
{
   ASSERT( CanRedo() );
   Redo();
}

void CEAFDocument::OnUpdateRedo(CCmdUI* pCmdUI) 
{
   if ( CanRedo() )
   {
      pCmdUI->Enable(TRUE);
      CString strCommand;
      strCommand.Format(_T("Redo %s\tCtrl+Y"),RedoName().c_str());
      pCmdUI->SetText(strCommand);
   }
   else
   {
      pCmdUI->SetText(_T("Redo\tCtrl+Y"));
      pCmdUI->Enable(FALSE);
   }
}

void CEAFDocument::ResetUIHints(bool bPrompt)
{
   if (bPrompt)
   {
      CString strText;
      strText = _T("Reset all user interface hints?");
      int result = AfxMessageBox(strText, MB_YESNO);
      if (result == IDNO)
      {
         return;
      }
   }

   UINT hintSettings = GetUIHintSettings();
   hintSettings = EAF_UIHINT_ENABLE_ALL;
   SetUIHintSettings(hintSettings);
}

void CEAFDocument::OnOptionsHints()
{
   ResetUIHints();
}

void CEAFDocument::OnStatusChanged()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   pFrame->OnStatusChanged();
}

void CEAFDocument::DeleteContents()
{
   CDocument::DeleteContents();
   m_MainMenu = nullptr;
   WBFL::EAF::TxnManager::ShutDown();
}

void CEAFDocument::OnCreateInitialize()
{
   // does nothing by default
}

void CEAFDocument::OnCreateFinalize()
{
   IntegrateWithUI(TRUE);
   // If the document is in an error state, present the status center to the user
   if (m_pStatusCenter && m_pStatusCenter->GetSeverity() == WBFL::EAF::StatusSeverityType::Error)
   {
      OnViewStatusCenter();
   }
   OnStatusChanged();

   // Sets the AutoSave state on the status bar
   CEAFStatusBar* pStatusBar = EAFGetMainFrame()->GetStatusBar();
   pStatusBar->AutoSaveEnabled(EAFGetApp()->IsAutoSaveEnabled());
}