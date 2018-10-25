// EAFDocument.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFDocument.h>
#include <EAF\EAFMainFrame.h>

// Logging
#include <iostream>
#include <fstream>
#include <System\Time.h>
#include <MFCTools\VersionInfo.h>

#include "PluginCommandManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CEAFDocument

IMPLEMENT_DYNAMIC(CEAFDocument, CDocument)

CEAFDocument::CEAFDocument()
{
   m_pMainMenu = NULL;
   m_pPluginCommandMgr = new CPluginCommandManager();
}

CEAFDocument::~CEAFDocument()
{
   if ( m_pPluginCommandMgr )
   {
      delete m_pPluginCommandMgr;
      m_pPluginCommandMgr = NULL;
   }

   if ( m_pMainMenu )
   {
      delete m_pMainMenu;
      m_pMainMenu = NULL;
   }
}


BEGIN_MESSAGE_MAP(CEAFDocument, CDocument)
END_MESSAGE_MAP()


BOOL CEAFDocument::OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
   // Do the regular command routing first
   BOOL bResult = CDocument::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
   if ( bResult )
      return bResult;

   // Next, see if any agents registered callback commands
   CComPtr<ICommandCallback> pCallback;
   UINT nAgentCmdID;
   if ( m_pPluginCommandMgr->GetCommandCallback(nID,&nAgentCmdID,&pCallback) )
   {
      // process the callback command
      return pCallback->OnCommandMessage(nAgentCmdID,nCode,pExtra,pHandlerInfo);
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
   return new CEAFMenu;
}

void CEAFDocument::InitToolBars()
{
   // Set up the tool bar mapping stuff
   CEAFMainFrame* pFrame = (CEAFMainFrame*)AfxGetMainWnd();

   CEAFToolBar* pToolBar = pFrame->GetMainToolBar();
   pToolBar->m_pCmdMgr   = m_pPluginCommandMgr;
   pToolBar->m_pToolBar  = &(pFrame->m_wndToolBar);
}

void CEAFDocument::InitMenus()
{
   // Set up the menu mapping stuff before initializing agents
   m_pMainMenu = CreateMainMenu();

   CWnd* pWnd = AfxGetMainWnd();

   m_pMainMenu->SetWindow(pWnd);
   m_pMainMenu->SetPluginCommandManager(m_pPluginCommandMgr);
}

void CEAFDocument::FailSafeLogMessage(const char* msg)
{
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
   CDocument::SetModifiedFlag(bModified);

   CEAFMainFrame* pFrame = (CEAFMainFrame*)AfxGetMainWnd();
   ASSERT_KINDOF(CEAFMainFrame,pFrame);

   pFrame->EnableModifiedFlag(IsModified());
}

void CEAFDocument::InitFailMessage()
{
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
   InitMenus();
   InitToolBars();

   return TRUE;
}

BOOL CEAFDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

   // Initialize the document
   if ( !Init() ) // init menus and toolbars... subclasses do more initialization
      return FALSE;

   SetModifiedFlag(TRUE);

   // update the mainframe title
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   pMainFrame->UpdateFrameTitle("Untitled");

   return TRUE;
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

   BOOL st = OpenTheDocument( lpszPathName );

   // update the mainframe title
   if (st == TRUE)
   {
      CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
      pMainFrame->UpdateFrameTitle(lpszPathName);
   }

   return st;
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
         AfxMessageBox("Bad save");
         // Opps... Couldn't delete it.
         // Alter the user so he's not screwed.
//         CString msg;
//         
//         GET_IFACE( IProjectLog, pLog );
//
//         pLog->LogMessage("");
//         pLog->LogMessage("An error occured while recovering your last successful save.");
//         msg.Format("It is highly likely that the file %s is corrupt.", lpszPathName);
//         pLog->LogMessage( msg );
//         pLog->LogMessage("To recover from this error,");
//         msg.Format("   1. Delete %s", lpszPathName );
//         pLog->LogMessage( msg );
//         msg.Format("   2. Rename %s to %s", strBackup, lpszPathName );
//         pLog->LogMessage( msg );
//         pLog->LogMessage("");
//
//         std::string strLogFileName = pLog->GetName();
//
//         AfxFormatString2( msg, IDS_E_SAVERECOVER1, lpszPathName, CString(strLogFileName.c_str()) );
//         AfxMessageBox(msg );
      }

      if ( bDidDelete )
      {
         // OK, We were able to delete the bad save.
         // Rename the backup to the original name.
         BOOL bDidMove = ::MoveFile( strBackup, lpszPathName ); // Rename the file
         if ( !bDidMove )
         {
            AfxMessageBox("Bad save");
            // Opps... A file with the original name is gone, and we can't
            // rename the backup to the file with the orignal name.
            // Alert the user so he's not screwed.
//            CString msg;
//
//            pLog->LogMessage("");
//            pLog->LogMessage("An error occured while recovering your last successful save.");
//            msg.Format("It is highly likely that the file %s no longer exists.", lpszPathName);
//            pLog->LogMessage( msg );
//            pLog->LogMessage("To recover from this error,");
//            msg.Format("   1. If %s exists, delete it.", lpszPathName );
//            pLog->LogMessage( msg );
//            msg.Format("   2. Rename %s to %s", strBackup, lpszPathName );
//            pLog->LogMessage( msg );
//            pLog->LogMessage("");
//
//            std::string strLogFileName = pLog->GetName();
//
//            AfxFormatString2( msg, IDS_E_SAVERECOVER2, lpszPathName, CString(strLogFileName.c_str()) );
//            AfxMessageBox( msg );
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

   // update title frame
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   pMainFrame->UpdateFrameTitle(lpszPathName);

   return TRUE;
}

void CEAFDocument::OnCloseDocument()
{
   CDocument::OnCloseDocument();
}

BOOL CEAFDocument::OpenTheDocument(LPCTSTR lpszPathName)
{
   {
      // NOTE: this scoping block is here for a reason. The IStructuredLoad must be
      //       destroyed before the file can be deleted.
      _COM_SMARTPTR_TYPEDEF(IStructuredLoad,IID_IStructuredLoad);
      IStructuredLoadPtr pStrLoad;

      HRESULT hr = ::CoCreateInstance( CLSID_StructuredLoad, NULL, 
	      CLSCTX_INPROC_SERVER, IID_IStructuredLoad, (void**)&pStrLoad );
      if ( FAILED(hr) )
      {
         // We are not aggregating so we should CoCreateInstance should
         // never fail with this HRESULT
         ASSERT( hr != CLASS_E_NOAGGREGATION );

         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }

      hr = pStrLoad->Open( lpszPathName );
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

      
      hr = pStrLoad->Close();
      if ( FAILED(hr) )
      {
         HandleOpenDocumentError( hr, lpszPathName );
         return FALSE;
      }
   }

//   if (convert_status==1)
//   {
//      // file was converted and written to a temporary file. delete the temp file
//      VERIFY(::DeleteFile(real_file_name));
//   }
//
//   // sets the status bar indicator for structural analysis type
//   UpdateAnalysisTypeStatusIndicator();
//
//   m_DocUnitSystem->put_UnitMode(GetUnitMode() == pgsTypes::umUS ? umUS : umSI);
	return TRUE;
}

BOOL CEAFDocument::SaveTheDocument(LPCTSTR lpszPathName)
{
   _COM_SMARTPTR_TYPEDEF(IStructuredSave,IID_IStructuredSave);
   IStructuredSavePtr pStrSave;

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

   hr = SaveTheDocument( pStrSave );
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
//   GET_IFACE( IProjectLog, pLog );
//
//   CString log_msg_header;
//   log_msg_header.Format("The following error occured while opening %s",lpszPathName );
//   pLog->LogMessage( log_msg_header );
//
//   CString msg1;
//   switch( hr )
//   {
//   case REGDB_E_CLASSNOTREG:
//      pLog->LogMessage( TEXT("CLSID_StructuredLoad not registered") );
//      msg1.LoadString( IDS_E_BADINSTALL );
//      break;
//
//   case STRLOAD_E_CANTOPEN:
//      pLog->LogMessage( TEXT("Could not open file") );
//      AfxFormatString1( msg1, IDS_E_READ, lpszPathName );
//      break;
//
//   case STRLOAD_E_FILENOTFOUND:
//      pLog->LogMessage( TEXT("File Not Found") );
//      AfxFormatString1( msg1, IDS_E_FILENOTFOUND, lpszPathName );
//      break;
//
//   case STRLOAD_E_INVALIDFORMAT:
//      pLog->LogMessage( TEXT("File does not have valid PGSuper format") );
//      AfxFormatString1( msg1, IDS_E_INVALIDFORMAT, lpszPathName );
//      break;
//
//   case STRLOAD_E_BADVERSION:
//      pLog->LogMessage( TEXT("This file came from a newer version of PGSuper, please upgrade") );
//      AfxFormatString1( msg1, IDS_E_INVALIDVERSION, lpszPathName );
//      break;
//
//   case STRLOAD_E_USERDEFINED:
//      AfxFormatString1( msg1, IDS_E_USERDEFINED, lpszPathName );
//      break;
//
//   default:
//      {
//         CString log_msg;
//         log_msg.Format("An unknown error occured while opening the file (hr = %d)",hr);
//         pLog->LogMessage( log_msg );
//         AfxFormatString1( msg1, IDS_E_READ, lpszPathName );
//      }
//      break;
//   }
//
//   CString msg;
//   CString msg2;
//   std::string strLogFileName = pLog->GetName();
//   AfxFormatString1( msg2, IDS_E_PROBPERSISTS, CString(strLogFileName.c_str()) );
//   AfxFormatString2(msg, IDS_E_FORMAT, msg1, msg2 );
//   AfxMessageBox( msg );
}

void CEAFDocument::HandleSaveDocumentError( HRESULT hr, LPCTSTR lpszPathName )
{
      AfxMessageBox("Error saving document");

//   GET_IFACE( IProjectLog, pLog );
//
//   CString log_msg_header;
//   log_msg_header.Format("The following error occured while saving %s",lpszPathName );
//   pLog->LogMessage( log_msg_header );
//
//   CString msg1;
//   switch( hr )
//   {
//   case REGDB_E_CLASSNOTREG:
//      pLog->LogMessage( TEXT("CLSID_StructuredSave not registered") );
//      msg1.LoadString( IDS_E_BADINSTALL );
//      break;
//
//   case STRSAVE_E_CANTOPEN:
//      pLog->LogMessage( TEXT("Could not open file") );
//      AfxFormatString1( msg1, IDS_E_FILENOTFOUND, lpszPathName );
//      break;
//
//   case STRSAVE_E_BADWRITE:
//      pLog->LogMessage( TEXT("Error Writing to File") );
//      AfxFormatString1( msg1, IDS_E_WRITE, lpszPathName );
//      break;
//
//   default:
//      {
//         CString log_msg;
//         log_msg.Format("An unknown error occured while closing the file (hr = %d)",hr);
//         pLog->LogMessage( log_msg );
//         AfxFormatString1( msg1, IDS_E_WRITE, lpszPathName );
//      }
//      break;
//   }
//
//   CString msg;
//   CString msg2;
//   std::string strLogFileName = pLog->GetName();
//   AfxFormatString1( msg2, IDS_E_PROBPERSISTS, CString(strLogFileName.c_str()) );
//   AfxFormatString2(msg, IDS_E_FORMAT, msg1, msg2 );
//   AfxMessageBox( msg );
}
