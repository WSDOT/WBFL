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

// EAFDocument.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
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

class CMyStatusCenterEventSink : public iStatusCenterEventSink
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

   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   pApp->AddUnitModeListener(this);

   m_bUIIntegrated = FALSE;
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

   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   pApp->RemoveUnitModeListener(this);
}


BEGIN_MESSAGE_MAP(CEAFDocument, CDocument)
   ON_UPDATE_COMMAND_UI(ID_VIEW_STATUSCENTER, OnUpdateViewStatusCenter)
   ON_COMMAND(ID_VIEW_STATUSCENTER,OnViewStatusCenter)
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
   CComPtr<ICommandCallback> pCallback;
   UINT nPluginCmdID;
   if ( m_pPluginCommandMgr->GetCommandCallback(nID,&nPluginCmdID,&pCallback) && pCallback )
   {
      // process the callback command
      bResult = pCallback->OnCommandMessage(nPluginCmdID,nCode,pExtra,pHandlerInfo);
      if ( bResult )
         return bResult;
   }

   // Finally, see if the application plugin object handles it
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   if ( pTemplate )
   {
      CComPtr<IEAFAppPlugin> appPlugin;
      pTemplate->GetPlugin(&appPlugin);

      CCmdTarget* pCmdTarget = appPlugin->GetCommandTarget();
      if ( pCmdTarget )
         bResult = pCmdTarget->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);

      if ( bResult )
         return bResult;
   }

   // the command wasn't handled here!
   return FALSE;
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

CEAFMenu* CEAFDocument::GetMenu()
{
   return m_pMainMenu;
}

CEAFMenu* CEAFDocument::CreateMainMenu()
{
   return new CEAFMenu(AfxGetMainWnd(),GetPluginCommandManager());
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
      InitMainMenu();

   // save toolbar state before they are removed
   CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd();
   if ( !bIntegrate )
      pFrame->SaveBarState(GetToolbarSectionName());

   DoIntegrateWithUI(bIntegrate);

   // load toolbar state after toolbars are created
   if ( bIntegrate )
      pFrame->LoadBarState(GetToolbarSectionName());

   m_bUIIntegrated = bIntegrate;
}

void CEAFDocument::DoIntegrateWithUI(BOOL bIntegrate)
{
   CEAFDocPluginManager* pPluginMgr = GetDocPluginManager();
   UINT nPlugins = pPluginMgr->GetPluginCount();
   for (UINT idx = 0; idx < nPlugins; idx++ )
   {
      CComPtr<IEAFDocumentPlugin> plugin;
      pPluginMgr->GetPlugin(idx,&plugin);
      plugin->IntagrateWithUI(bIntegrate);
   }
}

UINT CEAFDocument::CreateToolBar(LPCTSTR lpszName)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   return pMainFrame->CreateToolBar(lpszName,GetPluginCommandManager());
}

CEAFToolBar* CEAFDocument::GetToolBar(UINT toolbarID)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   return pMainFrame->GetToolBar(toolbarID);
}

void CEAFDocument::DestroyToolBar(CEAFToolBar* pToolBar)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   pMainFrame->DestroyToolBar(pToolBar);
}

void CEAFDocument::DestroyToolBar(UINT toolbarID)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   pMainFrame->DestroyToolBar(toolbarID);
}

long CEAFDocument::RegisterView(CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu,int maxViewCount)
{
   CEAFDocTemplate* pMyTemplate = (CEAFDocTemplate*)(GetDocTemplate());
   CComPtr<IEAFAppPlugin> appPlugin;
   pMyTemplate->GetPlugin(&appPlugin);
   UINT nResourceID = appPlugin->GetDocumentResourceID();

   if ( hSharedMenu == NULL )
   {
      CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
      hSharedMenu = pMainFrame->GetMenu()->GetSafeHmenu();
   }

   CEAFDocTemplate* pNewDocTemplate = new CEAFDocTemplate(nResourceID,GetRuntimeClass(),pFrameClass,pViewClass,hSharedMenu,maxViewCount);

   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();

   long key = pRegistrar->AddDocTemplate(pNewDocTemplate);
   return key;
}

void CEAFDocument::RemoveView(long key)
{
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();
   pRegistrar->RemoveDocTemplate(key);
}

CView* CEAFDocument::CreateView(long key,LPVOID pData)
{
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();

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

   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();

   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();
   CEAFDocTemplate*          pTemplate  = pRegistrar->GetDocTemplate(key);
   CView*                    pView      = pMainFrame->CreateOrActivateFrame(pTemplate);

   // done with the create data, so NULL it out
   pMyTemplate->SetViewCreationData(NULL);

   return pView;
}

void CEAFDocument::FailSafeLogMessage(const char* msg)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CString strLogFile = AfxGetApp()->m_pszExeName;
   strLogFile += ".log";

   std::ofstream ofile(strLogFile);
   sysTime now;
   now.PrintDate(true);
   ofile << "Log opened " << now << std::endl;

   CString strExe = AfxGetApp()->m_pszAppName;
   strExe += ".exe";
   
   CVersionInfo verInfo;
   if ( verInfo.Load(strExe) )
   {
      CString strProduct = verInfo.GetProductName();
      CString strVersion = verInfo.GetProductVersionAsString();

      ofile << strProduct.LockBuffer() << " Version " << strVersion.LockBuffer() << std::endl;
   }
   else
   {
      ofile << "Product Version Information not available" << std::endl;
   }

   ofile << msg << std::endl;

   ofile << "Log closed" << now << std::endl;
   ofile.close();
}

void CEAFDocument::SetModifiedFlag(BOOL bModified)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CDocument::SetModifiedFlag(bModified);

   CEAFMainFrame* pFrame = (CEAFMainFrame*)AfxGetMainWnd();
   ASSERT_KINDOF(CEAFMainFrame,pFrame);

   pFrame->EnableModifiedFlag(IsModified());
}

void CEAFDocument::InitFailMessage()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CString msg, msg1, msg2;

   CString strLogFile = AfxGetApp()->m_pszExeName;
   strLogFile += ".log";

   AfxFormatString1(msg1, IDS_E_BADINSTALL, AfxGetApp()->m_pszExeName );
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

   if ( GetDocPluginManager()->LoadPlugins(catid) )
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
   str.Format("%s Status Center",m_pStatusCenterDlg->IsWindowVisible() ? "Hide" : "Show");
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
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   pMainFrame->UpdateFrameTitle("Untitled");
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
      CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
      pMainFrame->UpdateFrameTitle(lpszPathName);
   }

   return bDocumentOpened;
}

BOOL CEAFDocument::OnSaveDocument(LPCTSTR lpszPathName)
{
   // Not using MFC Serialization so don't call base class.
   //	return CDocument::OnSaveDocument(lpszPathName);

   //
   // If the file already exists, back it up before we save
   //

   // Make sure this file actually exists before we attempt to back it up
   BOOL bDidCopy = false;
   CString strBackup(lpszPathName);

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
         msg.Format("Cannot save file. The file %s is read-only. Please try to save again to a different file.", lpszPathName);
         AfxMessageBox(msg );
         return FALSE;
      }

      // Create a backup copy of the last good save.
      // Backup filename is orginial filename, except the first
      // letter is a ~.
      int idx = strBackup.ReverseFind( '\\' ); // look for last '\'. 
                                               // This is one character before the 
                                               // beginning of the filename
      ASSERT( idx != -1 ); // '\' wasn't found
      idx++;
      strBackup.SetAt(idx,'~');

      bDidCopy = ::CopyFile( lpszPathName, strBackup, FALSE );
      if ( !bDidCopy && AfxMessageBox(IDS_E_UNSAFESAVE,MB_YESNO) == IDNO )
      {
         return FALSE;
      }
   }

   // Attempt to save the document
   if ( !SaveTheDocument( lpszPathName ) && bDidCopy )
   {
      // Save failed... Restore the backup

      // Delete the bad save
      BOOL bDidDelete = ::DeleteFile( lpszPathName );
      if ( !bDidDelete )
      {
         // Opps... Couldn't delete it.
         // Alter the user so he's not screwed.
         OnErrorDeletingBadSave(lpszPathName,strBackup);
      }

      if ( bDidDelete )
      {
         // OK, We were able to delete the bad save.
         // Rename the backup to the original name.
         BOOL bDidMove = ::MoveFile( strBackup, lpszPathName ); // Rename the file
         if ( !bDidMove )
         {
            // Opps... A file with the original name is gone, and we can't
            // rename the backup to the file with the orignal name.
            // Alert the user so he's not screwed.
            OnErrorRemaningSaveBackup(lpszPathName,strBackup);
         }
      }

      return FALSE;
   }
   else
   {
      // Save was successful... Delete the backup if one was created
      if ( bDidCopy )
         ::DeleteFile( strBackup );
      // It's no big deal if this call fails.  The user is simply left
      // with an out of date backup file on their disk drive.
   }

   SetModifiedFlag( FALSE );
   OnStatusChanged();

   // update title frame
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   pMainFrame->UpdateFrameTitle(lpszPathName);

   return TRUE;
}

void CEAFDocument::OnErrorDeletingBadSave(LPCTSTR lpszPathName,LPCTSTR lpszBackup)
{
   CString msg;
   msg.Format("%s\n%s%s%s\n%s\n%s%s\n%s%s%s%s",
              "An error occured while recovering your last successful save.",
              "It is highly likely that the file ", lpszPathName, " is corrupt.",
              "To recover from this error,",
              "   1. Delete ", lpszPathName,
              "   2. Rename ", lpszBackup, " to ", lpszPathName);
   
   AfxMessageBox(msg);
}

void CEAFDocument::OnErrorRemaningSaveBackup(LPCTSTR lpszPathName,LPCTSTR lpszBackup)
{
   CString msg;
   msg.Format("%s\n%s%s%s\n%s\n%s%s%s\n%s%s%s%s",
              "An error occured while recovering your last successful save.",
              "It is highly likely that the file ", lpszPathName, " no longer exists.",
              "To recover from this error,",
              "   1. If ", lpszPathName, " exists, delete it.",
              "   2. Rename ", lpszBackup, " to ", lpszPathName);
   
   AfxMessageBox(msg);
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
   }

   SaveDocumentSettings();

   UnloadDocumentPlugins();

   // put the main frame toolbar back the way it was
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   pMainFrame->ShowMainFrameToolBar();

   // this has to come last as the document deletes itself
   CDocument::OnCloseDocument();

   // DON'T DO ANYTHING ELSE HERE.... Document has deleted itself
   pMainFrame->ResetStatusBar();
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

      hr = LoadTheDocument(pStrLoad);
      if ( FAILED(hr) )
      {
         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }


      // end unit wrapping entire file
      try
      {
         if (S_OK != pStrLoad->EndUnit())
            return E_FAIL;
      }
      catch(...)
      {
         return E_FAIL;
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
   AfxMessageBox("Error converting document");
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

   hr = WriteTheDocument( pStrSave );
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

void CEAFDocument::HandleOpenDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
   AfxMessageBox("Error opening document");
}

void CEAFDocument::HandleSaveDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
   AfxMessageBox("Error saving document");
}

CEAFStatusCenter& CEAFDocument::GetStatusCenter()
{
   return *m_pStatusCenter;
}

void CEAFDocument::OnUnitsModeChanged(eafTypes::UnitMode newUnitMode)
{
   UpdateAllViews(NULL,EAF_HINTS_UNITS_CHANGED,0);
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

std::string CEAFDocument::UndoName()
{
   return txnTxnManager::GetInstance()->UndoName();
}

std::string CEAFDocument::RedoName()
{
   return txnTxnManager::GetInstance()->RedoName();
}

std::string CEAFDocument::RepeatName()
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
      strCommand.Format("Undo %s\tCtrl+Z",UndoName().c_str());
      pCmdUI->SetText(strCommand);
   }
   else
   {
      pCmdUI->SetText("Undo\tCtrl+Z");
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
      strCommand.Format("Redo %s\tCtrl+Y",RedoName().c_str());
      pCmdUI->SetText(strCommand);
   }
   else
   {
      pCmdUI->SetText("Redo\tCtrl+Y");
      pCmdUI->Enable(FALSE);
   }
}

void CEAFDocument::OnStatusChanged()
{
   CEAFMainFrame* pFrame = (CEAFMainFrame*)AfxGetMainWnd();
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