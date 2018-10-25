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

// EAFDocument.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFResources.h>
#include <EAF\EAFDocument.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFAppPlugin.h>
#include <EAF\EAFDocTemplateRegistrar.h>
#include <EAF\EAFHints.h>

// Logging
#include <iostream>
#include <fstream>
#include <System\Time.h>
#include <MFCTools\VersionInfo.h>

#include <System\TxnManager.h>

#include <EAF\EAFPluginCommandManager.h>

#include "StatusCenterDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CMyStatusCenterEventSink : public IEAFStatusCenterEventSink
{
public:
   CMyStatusCenterEventSink(CEAFDocument* pDoc)
   {
      m_pDoc = pDoc;
   }

   virtual void OnStatusItemAdded(CEAFStatusItem* pItem)
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
   m_pMainMenu = NULL;
   m_pPluginCommandMgr = new CEAFPluginCommandManager();

   m_pStatusCenterEventSink = new CMyStatusCenterEventSink(this);

   m_pStatusCenter = new CEAFStatusCenter;
   m_pStatusCenter->SinkEvents(m_pStatusCenterEventSink);

   m_pStatusCenterDlg = new CStatusCenterDlg(*m_pStatusCenter);

   m_DocPluginMgr.SetParent(this);

   CEAFApp* pApp = EAFGetApp();
   pApp->AddUnitModeListener(this);

   m_bUIIntegrated = FALSE;
   m_bEnableSaveBackup = TRUE;
}

CEAFDocument::~CEAFDocument()
{
   ATLASSERT( m_pMainMenu == NULL ); // this should have been deleted by now!

   if ( m_pPluginCommandMgr )
   {
      delete m_pPluginCommandMgr;
      m_pPluginCommandMgr = NULL;
   }

   if ( m_pStatusCenterDlg )
   {
      delete m_pStatusCenterDlg;
      m_pStatusCenterDlg = NULL;
   }

   if ( m_pStatusCenter )
   {
      delete m_pStatusCenter;
      m_pStatusCenter = NULL;
   }

   if ( m_pStatusCenterEventSink )
   {
      delete m_pStatusCenterEventSink;
      m_pStatusCenterEventSink = NULL;
   }

   CEAFApp* pApp = EAFGetApp();
   pApp->RemoveUnitModeListener(this);
}


BEGIN_MESSAGE_MAP(CEAFDocument, CDocument)
   ON_UPDATE_COMMAND_UI(EAFID_VIEW_STATUSCENTER, OnUpdateViewStatusCenter)
   ON_COMMAND(EAFID_VIEW_STATUSCENTER,OnViewStatusCenter)
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateUndo)
	ON_COMMAND(ID_EDIT_REDO, OnRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateRedo)
END_MESSAGE_MAP()


BOOL CEAFDocument::OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
   // Do the regular command routing first
   BOOL bResult = CDocument::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
   if ( bResult )
      return bResult;

   // Next, see if anyone registered callback commands
   CComPtr<IEAFCommandCallback> pCallback;
   UINT nPluginCmdID;
   if ( m_pPluginCommandMgr->GetCommandCallback(nID,&nPluginCmdID,&pCallback) && pCallback )
   {
      // process the callback command
      bResult = pCallback->OnCommandMessage(nPluginCmdID,nCode,pExtra,pHandlerInfo);
      if ( bResult )
         return bResult;
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
   ASSERT(FALSE); // should never get here... we aren't using CArcive serialization
}
#endif //_DEBUG

// CEAFDocument message handlers

CEAFMenu* CEAFDocument::GetMainMenu()
{
   return m_pMainMenu;
}

CEAFAcceleratorTable* CEAFDocument::GetAcceleratorTable()
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   return pMainFrame->GetAcceleratorTable();
}

CEAFMenu* CEAFDocument::CreateMainMenu()
{
   return new CEAFMenu(EAFGetMainFrame(),GetPluginCommandManager());
}

CEAFPluginCommandManager* CEAFDocument::GetPluginCommandManager()
{
   return m_pPluginCommandMgr;
}

CEAFDocPluginManager* CEAFDocument::GetDocPluginManager()
{
   return &m_DocPluginMgr;
}

BOOL CEAFDocument::InitMainMenu()
{
   // Set up the menu mapping stuff before initializing agents
   if (m_pMainMenu)
      delete m_pMainMenu;

   m_pMainMenu = CreateMainMenu();
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
      SaveToolbarState();

   DoIntegrateWithUI(bIntegrate);

   // load toolbar state after toolbars are created
   if ( bIntegrate )
      LoadToolbarState();

   m_bUIIntegrated = bIntegrate;
}

void CEAFDocument::DoIntegrateWithUI(BOOL bIntegrate)
{
   CEAFDocPluginManager* pPluginMgr = GetDocPluginManager();
   CollectionIndexType nPlugins = pPluginMgr->GetPluginCount();
   for (CollectionIndexType idx = 0; idx < nPlugins; idx++ )
   {
      CComPtr<IEAFDocumentPlugin> plugin;
      pPluginMgr->GetPlugin(idx,&plugin);
      plugin->IntagrateWithUI(bIntegrate);
   }
}

BOOL CEAFDocument::ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo)
{
   CEAFDocPluginManager* pPluginMgr = GetDocPluginManager();
   CollectionIndexType nPlugins = pPluginMgr->GetPluginCount();
   for (CollectionIndexType idx = 0; idx < nPlugins; idx++ )
   {
      CComPtr<IEAFDocumentPlugin> plugin;
      pPluginMgr->GetPlugin(idx,&plugin);

      CComQIPtr<IEAFDocCommandLine> cmdLinePlugin(plugin);
      if ( cmdLinePlugin )
      {
         if ( cmdLinePlugin->ProcessCommandLineOptions(cmdInfo) )
            return TRUE; // handled
      }
   }

   return FALSE;
}

UINT CEAFDocument::CreateToolBar(LPCTSTR lpszName)
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   return pMainFrame->CreateToolBar(lpszName,GetPluginCommandManager());
}

CEAFToolBar* CEAFDocument::GetToolBar(UINT toolbarID)
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   return pMainFrame->GetToolBar(toolbarID);
}

void CEAFDocument::DestroyToolBar(CEAFToolBar* pToolBar)
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->DestroyToolBar(pToolBar);
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
}

void CEAFDocument::SaveToolbarState()
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->SaveBarState(CString("Toolbars\\")+GetToolbarSectionName());
}

long CEAFDocument::RegisterView(UINT nResourceID,IEAFCommandCallback* pCallback,CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu,int maxViewCount)
{
   if ( hSharedMenu == NULL )
   {
      CEAFMainFrame* pMainFrame = EAFGetMainFrame();
      hSharedMenu = pMainFrame->GetMenu()->GetSafeHmenu();
   }

   CEAFDocTemplate* pNewDocTemplate = new CEAFDocTemplate(nResourceID,pCallback,GetRuntimeClass(),pFrameClass,pViewClass,hSharedMenu,maxViewCount);

   CEAFApp* pApp = EAFGetApp();
   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();

   long key = pRegistrar->AddDocTemplate(pNewDocTemplate);
   return key;
}

void CEAFDocument::RemoveView(long key)
{
   CEAFApp* pApp = EAFGetApp();
   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();
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

   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();
   CEAFDocTemplate*          pTemplate  = pRegistrar->GetDocTemplate(key);
   pTemplate->SetViewCreationData(pData);
   CView*                    pView      = pMainFrame->CreateOrActivateFrame(pTemplate);
   
   // done with the create data, so NULL it out
   pTemplate->SetViewCreationData(NULL);
   pMyTemplate->SetViewCreationData(NULL);

   return pView;
}

void CEAFDocument::FailSafeLogMessage(LPCTSTR msg)
{
   CEAFApp* pApp = EAFGetApp();
   CString strLogFile;
   strLogFile.Format(_T("%s\\%s.log"),pApp->GetAppLocation(),pApp->m_pszExeName);

   std::vector<CString> strings;
   sysTime now;
   now.PrintDate(true);
   CString strTime;
   strTime.Format(_T("Log Opened %s"),now.AsString().c_str());
   strings.push_back(strTime);


   CString strExe = pApp->m_pszAppName;
   strExe += _T(".exe");
   
   CVersionInfo verInfo;
   if ( verInfo.Load(strExe) )
   {
      CString strProduct = verInfo.GetProductName();
      CString strVersion = verInfo.GetProductVersionAsString();

      CString str;
      str.Format(_T("%s Version %s"),strProduct,strVersion);
      strings.push_back(str);
   }
   else
   {
      strings.push_back(CString(_T("Product Version Information not available")));
   }

   strings.push_back(CString(msg));

   now.PrintDate(true);
   CString strTime2;
   strTime2.Format(_T("Log Closed %s"),now.AsString().c_str());
   strings.push_back(strTime2);

   std::_tofstream ofile(strLogFile);
   if ( ofile.is_open() )
   {
      std::vector<CString>::iterator iter(strings.begin());
      std::vector<CString>::iterator end(strings.end());
      for ( ; iter != end; iter++ )
      {
         ofile << (*iter).LockBuffer() << std::endl;
      }
   }
   else
   {
      CString strMsg(_T("An error occured and the log file could not be created.\n\n"));
      std::vector<CString>::iterator iter(strings.begin());
      std::vector<CString>::iterator end(strings.end());
      for ( ; iter != end; iter++ )
      {
         strMsg += (*iter) + CString(_T("\n"));
      }
      AfxMessageBox(strMsg,MB_ICONEXCLAMATION | MB_OK);
   }
}

void CEAFDocument::SetModifiedFlag(BOOL bModified)
{
   CDocument::SetModifiedFlag(bModified);

   CEAFMainFrame* pFrame = EAFGetMainFrame();

   pFrame->EnableModifiedFlag(IsModified());
}

void CEAFDocument::SetSaveMissingPluginDataFlag(BOOL bSaveDataFromMissingPlugins)
{
   GetDocPluginManager()->SetSaveMissingPluginDataFlag(bSaveDataFromMissingPlugins);
}

BOOL CEAFDocument::GetSaveMissingPluginDataFlag()
{
   return GetDocPluginManager()->GetSaveMissingPluginDataFlag();
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
      return FALSE;

   LoadDocumentSettings();

   return TRUE;
}

void CEAFDocument::LoadDocumentSettings()
{
   // Does nothing by default
}

void CEAFDocument::SaveDocumentSettings()
{
   // Does nothing by default
}

CATID CEAFDocument::GetDocumentPluginCATID()
{
   return CLSID_NULL;
}

BOOL CEAFDocument::LoadDocumentPlugins()
{
   CATID catid = GetDocumentPluginCATID();
   if ( catid == CLSID_NULL )
      return TRUE; // no plugins for this document type

   GetDocPluginManager()->SetCATID(catid);

   if ( GetDocPluginManager()->LoadPlugins() )
   {
      GetDocPluginManager()->InitPlugins();
   }

   return TRUE;
}

void CEAFDocument::UnloadDocumentPlugins()
{
   GetDocPluginManager()->UnloadPlugins();
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

BOOL CEAFDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

   // Initialize the document
   if ( !Init() ) // init menus and toolbars... subclasses do more initialization
      return FALSE;

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
   if ( !OnNewDocument() )
      return FALSE;

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
   CWaitCursor cursor;

   // we want to totally replace the default functionality
	//if (!CDocument::OnOpenDocument(lpszPathName))
	//	return FALSE;
	
   // Initialize the document
   if ( !Init() ) // init menus and toolbars... subclasses do more initialization
      return FALSE;

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
         ::FindClose(hFile); // don't want no stinkin resource leaks.
        
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
         // Backup filename is orginial filename, except the first
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
         // Opps... Couldn't delete it.
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
            // Opps... A file with the original name is gone, and we can't
            // rename the backup to the file with the orignal name.
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
         ::DeleteFile( strBackupFile );
      // It's no big deal if this call fails.  The user is simply left
      // with an out of date backup file on their disk drive.
   }

   SetModifiedFlag( FALSE );
   OnStatusChanged();

   // update title frame
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->UpdateFrameTitle(lpszPathName);

   return TRUE;
}

void CEAFDocument::OnErrorDeletingBadSave(LPCTSTR lpszPathName,LPCTSTR lpszBackup)
{
   CString msg;
   msg.Format(_T("%s\n%s%s%s\n%s\n%s%s\n%s%s%s%s"),
              _T("An error occured while recovering your last successful save."),
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
              _T("An error occured while recovering your last successful save."),
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
      hr = ::CoCreateInstance( CLSID_StructuredLoad, NULL, CLSCTX_INPROC_SERVER, IID_IStructuredLoad, (void**)&pStrLoad );
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

      hr = LoadTheDocument(pStrLoad);
      if ( FAILED(hr) )
      {
         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }

      // If this document type supports plugins, load the plug in data
      if ( GetDocumentPluginCATID() != CLSID_NULL )
      {
         hr = GetDocPluginManager()->LoadPluginData( pStrLoad );
         if ( FAILED(hr) )
         {
            HandleOpenDocumentError( hr, lpszPathName );
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
   }

   if ( hr_convert == S_OK )
   {
      // file was converted and written to a temporary file. delete the temp file
      VERIFY(::DeleteFile(real_file_name));
   }

   SetModifiedFlag(FALSE);
   OnStatusChanged();

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
   strMsg.Format(_T("An error occured while converting %s (%d)"),lpszPathName,hr);
   AfxMessageBox(strMsg,MB_OK | MB_ICONEXCLAMATION);
}

void CEAFDocument::HandleOpenDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
   CString strMsg;
   strMsg.Format(_T("An error occured while opening %s (%d)"),lpszPathName,hr);
   AfxMessageBox(strMsg,MB_OK | MB_ICONEXCLAMATION);
}

void CEAFDocument::HandleSaveDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
   CString strMsg;
   strMsg.Format(_T("An error occured while saving %s (%d)"),lpszPathName,hr);
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
   return pStrLoad->BeginUnit(GetRootNodeName());
}

HRESULT CEAFDocument::CloseDocumentRootNode(IStructuredLoad* pStrLoad)
{
   return pStrLoad->EndUnit();
}

BOOL CEAFDocument::SaveTheDocument(LPCTSTR lpszPathName)
{
   CComPtr<IStructuredSave> pStrSave;

   HRESULT hr = ::CoCreateInstance( CLSID_StructuredSave, NULL, 
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
      hr = GetDocPluginManager()->SavePluginData( pStrSave );
      if ( FAILED(hr) )
      {
         HandleSaveDocumentError( hr, lpszPathName );
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
		if (lpsz != NULL)
			*lpsz = '\0';

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
         rMessage = string.Mid(pos+1);

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

void CEAFDocument::OnCloseDocument()
{
   SetModifiedFlag(FALSE);
   OnStatusChanged();

   // remove ui elements that plug-ins provided
   if ( m_bUIIntegrated )
   {
      ATLASSERT(m_pMainMenu != NULL);
      IntegrateWithUI(FALSE);
      GetPluginCommandManager()->Clear();
   }

   SaveDocumentSettings();

   UnloadDocumentPlugins();

   // put the main frame toolbar back the way it was
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   pMainFrame->ShowMainFrameToolBar();

   // this has to come last as the document deletes itself
   CDocument::OnCloseDocument();

   // DON'T DO ANYTHING ELSE HERE.... Document has deleted itself

   // need to clean up the status bar
   CEAFStatusBar* pStatusBar = pMainFrame->GetStatusBar();
   if ( pStatusBar )
      pStatusBar->Reset();
}

CEAFStatusCenter& CEAFDocument::GetStatusCenter()
{
   return *m_pStatusCenter;
}

void CEAFDocument::OnUnitsModeChanged(eafTypes::UnitMode newUnitMode)
{
   OnUpdateAllViews(NULL,EAF_HINT_UNITS_CHANGED,0);
}

void CEAFDocument::Execute(txnTransaction& rTxn)
{
   txnTxnManager::GetInstance()->Execute(rTxn);
}

void CEAFDocument::Execute(txnTransaction* pTxn)
{
   txnTxnManager::GetInstance()->Execute(pTxn);
}

void CEAFDocument::Undo()
{
   txnTxnManager::GetInstance()->Undo();
}

void CEAFDocument::Redo()
{
   txnTxnManager::GetInstance()->Redo();
}

void CEAFDocument::Repeat()
{
   txnTxnManager::GetInstance()->Repeat();
}

bool CEAFDocument::CanUndo()
{
   return txnTxnManager::GetInstance()->CanUndo();
}

bool CEAFDocument::CanRedo()
{
   return txnTxnManager::GetInstance()->CanRedo();
}

bool CEAFDocument::CanRepeat()
{
   return txnTxnManager::GetInstance()->CanRepeat();
}

std::_tstring CEAFDocument::UndoName()
{
   return txnTxnManager::GetInstance()->UndoName();
}

std::_tstring CEAFDocument::RedoName()
{
   return txnTxnManager::GetInstance()->RedoName();
}

std::_tstring CEAFDocument::RepeatName()
{
   return txnTxnManager::GetInstance()->RepeatName();
}

CollectionIndexType CEAFDocument::GetTxnCount()
{
   return txnTxnManager::GetInstance()->GetTxnCount();
}

CollectionIndexType CEAFDocument::GetUndoCount()
{
   return txnTxnManager::GetInstance()->GetUndoCount();
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

void CEAFDocument::OnStatusChanged()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   pFrame->OnStatusChanged();
}

void CEAFDocument::DeleteContents()
{
   CDocument::DeleteContents();

   if ( m_pMainMenu )
   {
      delete m_pMainMenu;
      m_pMainMenu = NULL;
   }
}

void CEAFDocument::OnCreateInitialize()
{
   // does nothing by default
}

void CEAFDocument::OnCreateFinalize()
{
   IntegrateWithUI(TRUE);
   OnStatusChanged();
}