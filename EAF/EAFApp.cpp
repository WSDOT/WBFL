///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

// EAFApp.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFDocManager.h>
#include <EAF\EAFPluginManagerBase.h>
#include <EAF\EAFSplashScreen.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFProjectLog.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFDataRecoveryHandler.h>
#include <AgentTools.h>
#include <System\ComCatMgr.h>

#include <MFCTools\Exceptions.h>
#include <MFCTools\VersionInfo.h>
#include <MfcTools\Prompts.h>

#include <EAF\EAFAboutDlg.h>
#include "UnitsDlg.h"
#include "TipDlg.h"
#include "AutoSaveDlg.h"

#include "custsite.h"


#include "EAFHelpWindowThread.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Error handling helpers
void save_doc(CDocument* pDoc,void* pStuff);
void notify_error(CDocument* pDoc,void* pStuff);
void log_error(CDocument* pDoc,void* pStuff);

// Unit configuration helps
WBFL::Units::IndirectMeasure init_si_units();
WBFL::Units::IndirectMeasure init_english_units();

#define ID_REPLACE_FILE (WM_USER+1)


/////////////////////////////////////////////////////////////////////////////
// CEAFApp

IMPLEMENT_DYNAMIC(CEAFApp, CWinApp)

CEAFApp::CEAFApp() :
m_strWindowPlacementFormat("%u,%u,%d,%d,%d,%d,%d,%d,%d,%d")
{
   m_bShowLegalNotice = VARIANT_TRUE;
   m_bTipsEnabled = false;
   m_bUseOnlineDocumentation = TRUE;
   m_bCommandLineMode = FALSE;

   m_bUseHelpWindow = TRUE;
   m_pHelpWindowThread = nullptr;

   m_bAutoSaveEnabled = TRUE;
   m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
   //m_nAutosaveInterval = 5/*minutes*/ * 60/*60seconds per minute*/ * 1000/*1000 milliseconds per second*/; // default is autosave every 5 minutes this is how you would change it

   // if this assert fires, we've used more than commands then are
   // reserved for EAF standard processing
   ATLASSERT(EAF_TOOLBAR_MENU_LAST < EAF_FIRST_USER_COMMAND);
}

CEAFApp::~CEAFApp()
{
}

int CEAFApp::Run() 
{
	int retval = -2;

   try
   {
      retval = CWinApp::Run();
   }
   catch(WBFL::System::XBase& e)
   {
      std::_tstring msg = e.GetErrorMessage();
      AfxMessageBox(msg.c_str(),MB_OK);
      ExitInstance();
   }

   return retval;
}

BOOL CEAFApp::InitInstance()
{
   if (!CWinApp::InitInstance())
   {
      return FALSE;
   }

   // Initialize OLE libraries
	if (!SUCCEEDED(OleInitialize(nullptr)))
	{
		AfxMessageBox(_T("OLE initialization failed. Make sure that the OLE libraries are the correct version."));
		return FALSE;
	}

   m_pCommandLineInfo = new CEAFCommandLineInfo();

   // Get the units system set up 
   InitDisplayUnits();

   // Change the registry key under which our settings are stored.
	SetRegistryKey(GetRegistryKey());
   RegistryInit();

   // more initialization before we can do any work
   GetAppPluginManager()->SetParent(this);
   GetComponentInfoManager()->SetParent(this);
   GetComponentInfoManager()->SetCATID(GetComponentInfoCategoryID());
   m_pDocManager = CreateDocumentManager();
   m_pDocTemplateRegistrar = CreateDocTemplateRegistrar();

   CCustomOccManager *pMgr = new CCustomOccManager;
   AfxEnableControlContainer(pMgr); // for CEAFReportView / IE Web Browser plug-in

   // Parse command line for standard shell commands, DDE, file open
	CEAFCommandLineInfo& cmdInfo = GetCommandLineInfo();
	ParseCommandLine(cmdInfo);


   // Don't display a new window on startup (Q141725)
   if ( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew )
   {
      cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
   }

   // The only default MFC command line options that are supported are Nothing, Open, and RestartByRestartManager
   // Any other options (such as /dde, /p, /pt, etc) should result in the command line usage
   // message being displayed
   if ( cmdInfo.m_nShellCommand != CCommandLineInfo::FileNothing && 
        cmdInfo.m_nShellCommand != CCommandLineInfo::FileOpen &&
        cmdInfo.m_nShellCommand != CCommandLineInfo::RestartByRestartManager
      )
   {
      cmdInfo.m_bError = TRUE;
   }

   if ( cmdInfo.m_bError )
   {
      DisplayCommandLineErrorMessage();
      return FALSE;
   }

   if ( !cmdInfo.m_bCommandLineMode )
   {
      // Show legal notice if not in command line mode
      if ( ShowLegalNoticeAtStartup() == atReject )
         return FALSE; // License was not accepted
   }

   // create main MDI Frame window
   m_pMainWnd = CreateMainFrame();
   if ( !m_pMainWnd )
   {
      return FALSE;
   }

   // Show splash screen (does nothing if splash screen is disabled)
   CEAFSplashScreen::SetSplashScreenInfo(GetSplashScreenInfo());
   if ( !cmdInfo.m_bCommandLineMode && cmdInfo.m_bShowSplash )
   {
      CEAFSplashScreen::Show(m_pMainWnd);
   }

   // Register the document templates... this is where the "plug-ins" get integrated
   // into the application framework
   if ( !RegisterDocTemplates() )
   {
      return FALSE;
   }

   // Give app plugins an opporunity to integrate with the UI
   if ( !AppPluginUIIntegration(true) )
   {
      return FALSE;	
   }

   // Done with splash screen
   CEAFSplashScreen::Hide();

   if ( cmdInfo.m_bUsageMessage )
   {
      ShowUsageMessage();
      return FALSE;
   }
   
   // The main window has been initialized, so show and update it.
   m_pMainWnd->ShowWindow(m_nCmdShow);
   m_pMainWnd->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW);
   m_pMainWnd->UpdateWindow();

   if ( 0 < cmdInfo.m_nParams )
   {
      ProcessCommandLineOptions(cmdInfo);
   }
   else
   {
      LoadDocumentationMap();

      if (!IsFirstRun() && (IsTipOfTheDayEnabled() && !cmdInfo.m_bCommandLineMode))
      {
         ShowTipOfTheDay();
      }

      // Start the help window thread
      if (m_bUseHelpWindow)
      {
         m_pHelpWindowThread = (CEAFHelpWindowThread*)AfxBeginThread(RUNTIME_CLASS(CEAFHelpWindowThread));
      }

      if (IsFirstRun() && !cmdInfo.m_bCommandLineMode)
      {
         OnFirstRun();
      }
   }

	return TRUE;
}

int CEAFApp::ExitInstance()
{
   // if the help window thread exists, tell it to quit
   if ( m_pHelpWindowThread )
   {
      m_pHelpWindowThread->PostThreadMessage(WM_TERMINATE_HELP_WINDOW_THREAD,0,0);
      ::WaitForSingleObject(m_pHelpWindowThread->m_hThread,INFINITE); // wait for the help window thread to terminate, otherwise we will get memory leaks
   }

	int result = CWinApp::ExitInstance(); // must call before UnloadPlugins

   delete m_pCommandLineInfo;

   // the document manager is usually deleted in CWinApp::~CWinApp, however,
   // when the plug in manager unloads the plug-ins, the DLLs from where the
   // document templates were created are unloaded from memory. this causes
   // all sorts of problems when the base class deletes the document manager.
   //
   // delete the document manager here, which will cause the doc templates to
   // be deleted, before the plug-in DLLs are unloaded.
   if ( m_pDocManager )
   {
      delete m_pDocManager;
   }

   m_pDocManager = nullptr;
   
   GetAppPluginManager()->UnloadPlugins();
   m_PluginCommandMgr.Clear();
   GetComponentInfoManager()->UnloadPlugins();

   if ( m_pDocTemplateRegistrar )
   {
      delete m_pDocTemplateRegistrar;
   }

   RegistryExit();

   ::OleUninitialize();

   return result;

}

void CEAFApp::RegistryInit()
{
	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU) ... make the MRU list be 10 items long
   CString strDefaultLegalNotice = GetLocalMachineString(_T("Settings"),_T("LegalNotice"), _T("On"));

   CString strLegalNotice = GetProfileString(_T("Settings"),_T("LegalNotice"),strDefaultLegalNotice);
   if ( strLegalNotice.CompareNoCase(_T("On")) == 0 )
   {
      m_bShowLegalNotice = VARIANT_TRUE;
   }
   else
   {
      m_bShowLegalNotice = VARIANT_FALSE;
   }

   // the "default" time of last run will be the install time less one day so that if the
   // "LastRun" setting is not in the registry, this will look like there was a new install
   // prior to this run
   WBFL::System::Date install_date = GetInstallDate();
   --install_date;
   WBFL::System::Time default_time(install_date);
   
   WBFL::System::ClockTy last_run = GetProfileInt(_T("Settings"),_T("LastRun"),default_time.Seconds());
   m_LastRunDate = WBFL::System::Time(last_run);

   CString strDocs = GetProfileString(_T("Settings"),_T("Documentation"),_T("Online"));
   m_bUseOnlineDocumentation = (strDocs.CompareNoCase(_T("Online")) == 0 ? TRUE : FALSE);
}

void CEAFApp::RegistryExit()
{
   VERIFY(WriteProfileString( _T("Settings"),_T("LegalNotice"),m_bShowLegalNotice == VARIANT_TRUE ? _T("On") : _T("Off") ));

   WBFL::System::Time time;
   WriteProfileInt(_T("Settings"),_T("LastRun"),time.Seconds());

   WriteProfileString(_T("Settings"),_T("Documentation"),m_bUseOnlineDocumentation == TRUE ? _T("Online") : _T("Offline"));
}

CEAFCommandLineInfo& CEAFApp::GetCommandLineInfo()
{
   return *m_pCommandLineInfo;
}

CString CEAFApp::GetDocumentationURL()
{
   CString strURL;

   CString strExe( m_pszExeName );
   strExe += _T(".exe");

   CVersionInfo verInfo;
   verInfo.Load(strExe);
   
   CString strVersion = verInfo.GetProductVersionAsString(false);

   std::_tstring v(strVersion);
   auto count = std::count(std::begin(v), std::end(v), _T('.'));

   // remove the hot fix and build/release number
   for (auto i = 0; i < count - 1; i++)
   {
      int pos = strVersion.ReverseFind(_T('.')); // find the last '.'
      strVersion = strVersion.Left(pos);
   }

   strURL.Format(_T("%s%s/%s/"),GetDocumentationRootLocation(),m_pszExeName,strVersion);

   return strURL;
}

eafTypes::HelpResult CEAFApp::GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL)
{
   CString strDocSetName(lpszDocSetName);
   if ( GetDocumentationSetName() == strDocSetName )
   {
      // we are looking in our own documentation set
      std::map<UINT,CString>::iterator found(m_HelpTopics.find(nHID));
      if ( found == m_HelpTopics.end() )
      {
         return eafTypes::hrTopicNotFound;
      }

      CString strBaseURL = GetDocumentationURL();
      strURL.Format(_T("%s%s"),strBaseURL,found->second);
      return eafTypes::hrOK;
   }
   else
   {
      // look in the documentation sets of our app plug-ins
      POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
      while ( pos != nullptr )
      {
         CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)m_pDocManager->GetNextDocTemplate( pos );
         CComPtr<IEAFAppPlugin> pAppPlugin;
         pTemplate->GetPlugin(&pAppPlugin);
         if ( pAppPlugin->GetDocumentationSetName() == strDocSetName )
         {
            return pAppPlugin->GetDocumentLocation(lpszDocSetName,nHID,strURL);
         }
      }
   }

   return eafTypes::hrDocSetNotFound;
}

void CEAFApp::UseOnlineDocumentation(BOOL bUseOnLine)
{
   if ( m_bUseOnlineDocumentation != bUseOnLine )
   {
      m_bUseOnlineDocumentation = bUseOnLine;
      
      m_strDocumentationMapFile.Empty();

      // Load the documentation map for the main executable program
      LoadDocumentationMap();

      CEAFDocument* pDoc = EAFGetDocument();
      if ( pDoc )
      {
         pDoc->DocumentationSourceChanged();
         pDoc->LoadDocumentationMap();
      }
   }
}

BOOL CEAFApp::UseOnlineDocumentation() const
{
   return m_bUseOnlineDocumentation;
}

void CEAFApp::HelpWindowNavigate(LPCTSTR lpszURL)
{
   if (m_pHelpWindowThread)
   {
      m_pHelpWindowThread->Navigate(lpszURL);
   }
   else
   {
      ::ShellExecute(m_pMainWnd->GetSafeHwnd(), _T("open"),lpszURL, 0, 0, SW_SHOWDEFAULT);
   }
}

void CEAFApp::ShowUsageMessage()
{
   CEAFCommandLineInfo& cmdInfo = GetCommandLineInfo();
   ASSERT( cmdInfo.m_bUsageMessage );

   CString strUsage;
   strUsage.Format(_T("%s"),cmdInfo.GetUsageMessage());
   
   CollectionIndexType nPlugins = GetAppPluginManager()->GetPluginCount();
   for ( CollectionIndexType idx = 0; idx < nPlugins; idx++ )
   {
      CComPtr<IEAFAppPlugin> appPlugin;
      GetAppPluginManager()->GetPlugin(idx,&appPlugin);

      CComQIPtr<IEAFAppCommandLine> appCmdLine(appPlugin);
      if ( appCmdLine )
      {
         strUsage += _T("\n\n");

         CString strAppName = appPlugin->GetName();
         CString strAppOptions;
         strAppOptions.Format(_T("%s <app options>\n"),strAppName);
         strUsage += strAppOptions;

         CString str = appCmdLine->GetUsageMessage();
         strUsage += str;
      }
   }

   AfxMessageBox(strUsage,MB_OK | MB_ICONINFORMATION);
}

void CEAFApp::DisplayCommandLineErrorMessage()
{
   CEAFCommandLineInfo& cmdInfo = GetCommandLineInfo();
   CString strMsg = cmdInfo.GetErrorMessage();
   AfxMessageBox(strMsg,MB_OK | MB_ICONSTOP);
}

CMDIFrameWnd* CEAFApp::CreateMainFrame()
{
	CEAFMainFrame* pMainFrame = new CEAFMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
   {
      delete pMainFrame;
		return nullptr;
   }

   return pMainFrame;
}

CDocManager* CEAFApp::CreateDocumentManager()
{
   return new CEAFDocManager;
}

CEAFDocTemplateRegistrar* CEAFApp::CreateDocTemplateRegistrar()
{
   return new CEAFDocTemplateRegistrar;
}

CString CEAFApp::GetAppLocation()
{
   TCHAR szBuff[_MAX_PATH];
   ::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH);
   CString filename(szBuff);

   CFileFind finder;
   finder.FindFile(filename);
   finder.FindNextFile();

   CString filePath = finder.GetFilePath();
   filePath.Replace( finder.GetFileName(), _T("") );

   return filePath;
}

void CEAFApp::EnableTipOfTheDay(LPCTSTR lpszTipFile)
{
   if ( lpszTipFile == nullptr )
   {
      m_bTipsEnabled = false;
      m_TipFiles.clear();
   }
   else
   {
      m_bTipsEnabled = true;
      m_TipFiles.push_back(lpszTipFile);
   }
}

void CEAFApp::EnableTipOfTheDay(const std::vector<CString>& vTipFiles)
{
   if ( vTipFiles.size() == 0 )
   {
      m_bTipsEnabled = false;
      m_TipFiles.clear();
   }
   else
   {
      m_bTipsEnabled = true;
      m_TipFiles = vTipFiles;
   }
}

bool CEAFApp::IsTipOfTheDayEnabled()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   BOOL bTipsEnabled = GetProfileInt(_T("Tip"),_T("StartUp"),TRUE);
   return bTipsEnabled && m_bTipsEnabled;
}

void CEAFApp::ShowTipOfTheDay(void)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CTipDlg dlg(m_TipFiles,EAFGetMainFrame());
	dlg.DoModal();
}

void CEAFApp::OnFirstRun()
{
   // Do nothing be default
}

BOOL CEAFApp::IsDocLoaded()
{
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   CEAFDocument* pDoc = pMainFrame->GetDocument();
   return (pDoc == nullptr ? FALSE : TRUE);
}

BEGIN_MESSAGE_MAP(CEAFApp, CWinApp)
	//{{AFX_MSG_MAP(CEAFApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(EAFID_TIPOFTHEDAY, ShowTipOfTheDay)
	ON_COMMAND(EAFID_APP_LEGAL, OnAppLegal)
   ON_COMMAND(EAFID_HELP_SOURCE,OnHelpSource)
   ON_UPDATE_COMMAND_UI(EAFID_HELP_SOURCE,OnUpdateHelpSource)
   ON_COMMAND(EAFID_HELP_VIEWER, OnHelpViewer)

	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)

   // Standard unit mode commands
	ON_COMMAND(EAFID_EDIT_UNITS, OnEditUnits)
   ON_COMMAND(EAFID_UNITS_SI,OnSIUnits)
   ON_UPDATE_COMMAND_UI(EAFID_UNITS_SI, OnUpdateSIUnits)
   ON_COMMAND(EAFID_UNITS_US,OnUSUnits)
   ON_UPDATE_COMMAND_UI(EAFID_UNITS_US, OnUpdateUSUnits)

   ON_COMMAND(EAFID_OPTIONS_AUTOSAVE, OnAutoSave)

	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
   ON_COMMAND(ID_APP_ABOUT, &CEAFApp::OnAppAbout)

   ON_COMMAND(ID_REPLACE_FILE,&CEAFApp::OnReplaceFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFApp message handlers
BOOL CEAFApp::RegisterDocTemplates()
{
   if ( !GetComponentInfoManager()->LoadPlugins(FALSE) ) // always attempt to load
   {
      return FALSE;
   }

   if ( !GetComponentInfoManager()->InitPlugins() )
   {
      return FALSE;
   }

   if ( !CreateApplicationPlugins() )
   {
      return FALSE;
   }

   if ( !GetAppPluginManager()->InitPlugins() )
   {
      return FALSE;
   }
   
   if ( !GetAppPluginManager()->RegisterDocTemplates(this) )
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CEAFApp::AppPluginUIIntegration(BOOL bIntegrate)
{
   if ( bIntegrate )
   {
      CEAFSplashScreen::SetText(_T("Integrating components into the user interface"));
   }

   GetAppPluginManager()->IntegrateWithUI(bIntegrate);
   return TRUE;
}

void CEAFApp::OnAppLegal() 
{
   ShowLegalNotice();	
}

void CEAFApp::OnHelpSource()
{
   UseOnlineDocumentation(!m_bUseOnlineDocumentation);
}

void CEAFApp::OnHelpViewer()
{
   int result = AfxRBChoose(_T("Documentation Viewer"), _T("Select the documentation viewer.\n\nA restart of the application is required for this change to take effect."), _T("Built-in viewer\nDefault web browser"), m_bUseHelpWindow ? 0 : 1, TRUE);
   if (result != -1)
   {
      m_bUseHelpWindow = (result == 0 ? TRUE : FALSE);
   }
}

void CEAFApp::OnUpdateHelpSource(CCmdUI* pCmdUI)
{
   pCmdUI->SetText(m_bUseOnlineDocumentation ? _T("Use local documentation") : _T("Use online documentation"));
}

void CEAFApp::OnFileNew()
{
   // Before creating a new document, save the open document
   // if it is modifed and then close it.
   if ( SaveAllModified() )
   {
      CloseAllDocuments( FALSE );
      CWinApp::OnFileNew();
   }
}

void CEAFApp::OnFileOpen()
{
   // Before creating a new document, save the open document
   // if it is modifed and then close it.
   if ( SaveAllModified() )
   {
      CloseAllDocuments( FALSE );
      CWinApp::OnFileOpen();
   }
}

void CEAFApp::OnEditUnits() 
{
   CUnitsDlg dlg;

   dlg.m_Units = (m_Units == eafTypes::umUS ? 0 : 1);
   if ( dlg.DoModal() )
   {
      eafTypes::UnitMode newunits = dlg.m_Units == 0 ? eafTypes::umUS : eafTypes::umSI;
      SetUnitsMode( newunits );
   }
	
}

void CEAFApp::OnSIUnits()
{
   SetUnitsMode( eafTypes::umSI );
}

void CEAFApp::OnUpdateSIUnits(CCmdUI* pCmdUI)
{
   pCmdUI->SetRadio( m_Units == eafTypes::umSI );
}

void CEAFApp::OnUSUnits()
{
   SetUnitsMode( eafTypes::umUS );
}

void CEAFApp::OnUpdateUSUnits(CCmdUI* pCmdUI)
{
   pCmdUI->SetRadio( m_Units == eafTypes::umUS );
}

void CEAFApp::OnAutoSave()
{
   CAutoSaveDlg dlg;
   dlg.bEnabled = m_bAutoSaveEnabled;
   dlg.interval = GetAutoSaveInterval() / 60000; // value is in milliseconds - we want it in minutes
   if(dlg.DoModal() == IDOK)
   {
      EnableAutoSave(dlg.bEnabled,dlg.interval*60000); // need to set the value in milliseconds
   }
}

CDocument* CEAFApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
   // make sure the document has a valid file extension before opening
   CDocument* pDoc = nullptr;

   CString file_ext;
   CString file_name(lpszFileName);
	int charpos = file_name.ReverseFind('.');
	if (0 <= charpos)
   {
		file_ext = file_name.Right(file_name.GetLength() - charpos);
   }

   bool bExtensionMatched = false;
   int templateIdx = 0; // keep track of which template is assocated with the file that got opened. we'll need to record this in the registry so that the File > Open dialog uses this type next time
   POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
   while ( pos != nullptr )
   {
      CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate( pos );

      CString str;
      if ( pTemplate->GetDocString(str,CDocTemplate::filterExt) )
      {
         int token_pos = 0;
         CString strExt = str.Tokenize(_T(";"),token_pos);
         if ( strExt != _T("") )
         {
            templateIdx++;
         }

         while ( strExt != _T("") )
         {
            if ( file_ext.CompareNoCase(strExt) == 0 )
            {
               bExtensionMatched = true;
               pos = nullptr; // kills the outer while loop
               break; // break out of this while loop
            }

            strExt = str.Tokenize(_T(";"),token_pos);
         }

      }
   }

   if ( bExtensionMatched )
   {
      // The current project must be closed before opening the new one
      if (m_pDocManager && m_pDocManager->SaveAllModified())
      {
         m_pDocManager->CloseAllDocuments(FALSE);
         pDoc = CWinApp::OpenDocumentFile(lpszFileName);

         CEAFApp* pApp = EAFGetApp();
         pApp->WriteProfileInt(_T("Settings"),_T("LastFileType"),templateIdx);
      }
   }
   else
   {
      CString strMsg;
      strMsg.Format(_T("%s is not a valid file for this application. Please select a different file"),lpszFileName);
      ::AfxMessageBox(strMsg,MB_ICONEXCLAMATION|MB_OK);
   }

   return pDoc;
}

void CEAFApp::ReplaceDocumentFile(LPCTSTR lpszFileName)
{
   // Call this method, instead of OpenDocumentFile when you want to close the current file
   // and open a new file. This command posts a message and returns so that the calling
   // function can finish. Once, finished, the ID_REPLACE_FILE command notification is
   // then processed by OnReplaceFile. 
   m_ReplacementFileName = lpszFileName;
   EAFGetMainFrame()->PostMessage(WM_COMMAND,ID_REPLACE_FILE,0);
}

void CEAFApp::OnReplaceFile()
{
   OpenDocumentFile(m_ReplacementFileName);
}

LRESULT CEAFApp::ProcessWndProcException(CException* e, const MSG* pMsg) 
{
   LRESULT lResult = 0L;

	if ( e->IsKindOf(RUNTIME_CLASS(CXShutDown)) || e->IsKindOf(RUNTIME_CLASS(CMemoryException)) )
   {
      std::_tstring error_msg;
      BOOL bAttemptSave;

      if ( e->IsKindOf(RUNTIME_CLASS(CXShutDown)) )
      {
         CXShutDown* pXShutDown = (CXShutDown*)e;
         pXShutDown->GetErrorMessage( &error_msg );
         bAttemptSave = pXShutDown->AttemptSave();
      }
      else
      {
         TCHAR szCause[255];
         CMemoryException* pXMemory = (CMemoryException*)e;
         pXMemory->GetErrorMessage(szCause,255);
         error_msg = szCause;
         bAttemptSave = TRUE;
      }

      CString msg1;
      AfxFormatString1( msg1, IDS_E_PROBPERSISTS, _T("log") ); 
      CString msg2;
      AfxFormatString2( msg2, bAttemptSave ? IDS_FATAL_MSG_SAVE : IDS_FATAL_MSG_NOSAVE, error_msg.c_str(), msg1 );
      int retval = AfxMessageBox( msg2, (bAttemptSave ? MB_YESNO : MB_OK) | MB_ICONEXCLAMATION );
      
      if ( e->IsKindOf(RUNTIME_CLASS(CXShutDown)) )
      {
         CXShutDown* pXShutDown = (CXShutDown*)e;
         ForEachDoc(log_error,(void*)pXShutDown);
      }

      if ( retval == IDYES )
      {
         ForEachDoc( save_doc, nullptr );
      }

      lResult = 1L;
      AfxPostQuitMessage( 0 );
   }
   else if ( e->IsKindOf(RUNTIME_CLASS(CXUnwind) ) )
   {
      CXUnwind* pXUnwind = (CXUnwind*)e;
      std::_tstring error_msg;
      pXUnwind->GetErrorMessage( &error_msg );
      m_LastError = error_msg.c_str();
      AfxMessageBox( error_msg.c_str(),  MB_OK | MB_ICONWARNING );


      ForEachDoc( notify_error, (void*)&m_LastError );
      lResult = 1L;
   }
   else
   {
      lResult = CWinApp::ProcessWndProcException(e, pMsg);
   }

	return lResult;
}

void CEAFApp::ForEachDoc(DocCallback pfn,void* pStuff)
{
   CEAFApp* pApp = EAFGetApp();
   POSITION tplpos = pApp->GetFirstDocTemplatePosition();
   while ( tplpos != nullptr )
   {
      CDocTemplate* pTpl = pApp->GetNextDocTemplate( tplpos );

      POSITION docpos = pTpl->GetFirstDocPosition();
      while ( docpos != nullptr )
      {
         CDocument* pDoc = pTpl->GetNextDoc( docpos );
         (*pfn)(pDoc,pStuff);
      }
   }
}

BOOL CEAFApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
   BOOL bResult = CWinApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

   if ( bResult )
   {
      return bResult; // message was handled
   }

   CComPtr<IEAFCommandCallback> pCallback;
   UINT nPluginCmdID;
   if ( m_PluginCommandMgr.GetCommandCallback(nID,&nPluginCmdID,&pCallback) && pCallback )
   {
      // process the callback command
      bResult = pCallback->OnCommandMessage((UINT)nPluginCmdID,nCode,pExtra,pHandlerInfo);
      if ( bResult )
         return bResult;
   }

   return FALSE; // message was NOT handled, continue routing
}

CDataRecoveryHandler *CEAFApp::GetDataRecoveryHandler()
{
   // NOTE: This is a copy/paste from CWinApp::GetDataRecovery handler.
   // we want the exact same implementation, except we want to create our own data recovery handler object
   static BOOL bTriedOnce = FALSE;

   // Since the application restart and application recovery are supported only on Windows
   // Vista and above, we don't need a recovery handler on Windows versions less than Vista.
   if (SupportsRestartManager() || SupportsApplicationRecovery())
   {
      if (!bTriedOnce && m_pDataRecoveryHandler == NULL)
      {
         // WE CHANGED THE RECOVERY HANDLER TYPE HERE!!!
         //m_pDataRecoveryHandler = new CDataRecoveryHandler(m_dwRestartManagerSupportFlags, m_nAutosaveInterval);
         m_pDataRecoveryHandler = new CEAFDataRecoveryHandler(m_dwRestartManagerSupportFlags, m_nAutosaveInterval);
         if (!m_pDataRecoveryHandler->Initialize())
         {
            delete m_pDataRecoveryHandler;
            m_pDataRecoveryHandler = NULL;
         }
      }
   }

   bTriedOnce = TRUE;
   return m_pDataRecoveryHandler;
}

CRecentFileList* CEAFApp::GetRecentFileList()
{
   return m_pRecentFileList;
}

CEAFDocTemplateRegistrar* CEAFApp::GetDocTemplateRegistrar()
{
   return m_pDocTemplateRegistrar;
}

CEAFAppPluginManager* CEAFApp::GetAppPluginManager()
{
   return &m_AppPluginManager;
}

CEAFPluginCommandManager* CEAFApp::GetPluginCommandManager()
{
   return &m_PluginCommandMgr;
}

CEAFComponentInfoManager* CEAFApp::GetComponentInfoManager()
{
   return &m_ComponentInfoManager;
}

void CEAFApp::InitDisplayUnits()
{
   WBFL::Units::System::SetMassUnit( WBFL::Units::Measure::Kilogram );
   WBFL::Units::System::SetLengthUnit( WBFL::Units::Measure::Meter );
   WBFL::Units::System::SetTimeUnit( WBFL::Units::Measure::Second );
   WBFL::Units::System::SetTemperatureUnit( WBFL::Units::Measure::Celsius );
   WBFL::Units::System::SetAngleUnit( WBFL::Units::Measure::Radian );

   m_UnitLibrary.AddEntry(_T("SI"),      init_si_units());
   m_UnitLibrary.AddEntry(_T("English"), init_english_units() );
   SetUnitsMode(eafTypes::umUS);
}

void CEAFApp::UpdateDisplayUnits()
{
   std::_tstring units = (m_Units == eafTypes::umUS ? _T("English") : _T("SI"));
   m_pDisplayUnits = &m_UnitLibrary.GetEntry(units);
}

const WBFL::Units::IndirectMeasure* CEAFApp::GetDisplayUnits() const
{
   return m_pDisplayUnits;
}

eafTypes::UnitMode CEAFApp::GetUnitsMode() const
{
   return m_Units;
}

void CEAFApp::SetUnitsMode(eafTypes::UnitMode newVal)
{
   if ( m_Units != newVal )
   {
      Fire_UnitsChanging();
      m_Units = newVal;
      UpdateDisplayUnits();
      Fire_UnitsChanged();
   }
}

void CEAFApp::AddUnitModeListener(iUnitModeListener* pListener)
{
   m_UnitModeListeners.insert(pListener);
}

void CEAFApp::RemoveUnitModeListener(iUnitModeListener* pListener)
{
   m_UnitModeListeners.erase(pListener);
}

WBFL::System::Date CEAFApp::GetInstallDate()
{
   HKEY hKey = GetUninstallRegistryKey();

   CString strProductCode = GetProductCode();

   CString strDate = GetLocalMachineString(hKey,strProductCode,_T("InstallDate"),_T("191001015"));
   int year  = _ttoi(strDate.Left(4));
   int month = _ttoi(strDate.Mid(4,2));
   int day   = _ttoi(strDate.Right(2));

   WBFL::System::Date date(day,month,year);
   return date;
}

WBFL::System::Date CEAFApp::GetLastRunDate()
{
   return m_LastRunDate;
}

BOOL CEAFApp::IsFirstRun()
{
   return ( GetLastRunDate() < GetInstallDate() ) ? TRUE : FALSE;
}

void CEAFApp::GetAutoSaveInfo(BOOL* pbAutoSave, int* pAutoSaveInterval)
{
   CString strAutoSaveDefault = GetLocalMachineString(_T("Options"), _T("AutoSave"), _T("true"));
   int default_interval = GetLocalMachineInt(_T("Options"), _T("AutoSaveInterval"), 5*60*1000);
   CString strAutoSave = GetProfileString(_T("Options"), _T("AutoSave"), strAutoSaveDefault);
   *pbAutoSave = (strAutoSave == _T("true") ? true : false);
   *pAutoSaveInterval = GetProfileInt(_T("Options"), _T("AutoSaveInterval"), default_interval);
   if (*pAutoSaveInterval < 1 * 60 * 1000)
   {
      *pAutoSaveInterval = 1 * 60 * 1000; // never let autosave interval be less than 1 minute
   }
}

void CEAFApp::SaveAutoSaveInfo(BOOL bAutoSave, int AutoSaveInterval)
{
   VERIFY(WriteProfileString(_T("Options"), _T("AutoSave"), bAutoSave ? _T("true") : _T("false")));
   VERIFY(WriteProfileInt(_T("Options"), _T("AutoSaveInterval"), AutoSaveInterval < 1*60*1000 ? 1*60*1000 : AutoSaveInterval)); // don't save a value less than 1 minute
}

int CEAFApp::GetAutoSaveInterval()
{
   CDataRecoveryHandler* pHandler = GetDataRecoveryHandler();
   if (pHandler)
   {
      return pHandler->GetAutosaveInterval();
   }
   else
   {
      return 5 * 60 * 1000; // 5 minute as default
   }
}

void CEAFApp::EnableAutoSave(BOOL bEnable, int interval)
{
   m_bAutoSaveEnabled = bEnable;
   if (m_bAutoSaveEnabled)
   {
      m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
      RegisterWithRestartManager(SupportsApplicationRecovery(), _T(""));
   }
   else
   {
      m_dwRestartManagerSupportFlags = 0;
      UnregisterApplicationRestart();
      UnregisterApplicationRecoveryCallback();
   }

   CDataRecoveryHandler* pHandler = GetDataRecoveryHandler();
   if (pHandler)
   {
      pHandler->SetAutosaveInterval(interval);// converts minutes to milliseconds
      pHandler->SetSaveDocumentInfoOnIdle(m_bAutoSaveEnabled);
   }

   CEAFDocument* pDocument = EAFGetDocument();
   if (m_bAutoSaveEnabled && pDocument)
   {
      // if we are turning on AutoSave, save the document now
      pDocument->DoFileSave();
   }

   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   if (pMainFrame)
   {
      pMainFrame->GetStatusBar()->AutoSaveEnabled(m_bAutoSaveEnabled);
   }

   SaveAutoSaveInfo(m_bAutoSaveEnabled, interval);
}

BOOL CEAFApp::IsAutoSaveEnabled()
{
   return m_bAutoSaveEnabled;
}

CEAFMDISnapper& CEAFApp::GetMDIWndSnapper()
{
   return m_MDISnapper;
}

void CEAFApp::Fire_UnitsChanging()
{
   for ( const auto& pListener : m_UnitModeListeners)
   {
      pListener->OnUnitsModeChanging();
   }
}

void CEAFApp::Fire_UnitsChanged()
{
   for (const auto& pListener : m_UnitModeListeners)
   {
      pListener->OnUnitsModeChanged(m_Units);
   }
}

void CEAFApp::OnMainFrameClosing()
{
   m_PluginCommandMgr.Clear(); // make sure all the plugin commands are cleared
}

void CEAFApp::OnAppAbout()
{
   OnAbout();
}

void CEAFApp::OnAbout()
{
   CEAFAboutDlg dlg;
   dlg.DoModal();
}

BOOL CEAFApp::PreTranslateMessage(MSG* pMsg)
{
   if ( CEAFSplashScreen::PreTranslateAppMessage(pMsg) )
   {
      return TRUE;
   }

   return CWinApp::PreTranslateMessage(pMsg);
}

void CEAFApp::ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo)
{
   m_bCommandLineMode = TRUE;

   // Give MFC first crack at the command line
	if ( !ProcessShellCommand(cmdInfo) )
   {
      cmdInfo.m_bError = TRUE;
      cmdInfo.m_bCommandLineMode = TRUE; // will cause an application shutdown
   }

   if (cmdInfo.m_nShellCommand == CCommandLineInfo::RestartByRestartManager)
   {
      // don't continue processing the commandline if there was a restart
      return;
   }

   if ( !cmdInfo.m_bError && 1 <= cmdInfo.m_nParams)
   {
      // If a document was opened when processing the shell command, get the doc template
      // and then the app plugin... let the app plugin deal with command line options
      CEAFMainFrame* pMainFrame = EAFGetMainFrame();
      CEAFDocument* pDoc = pMainFrame->GetDocument();
      if ( pDoc )
      {
         ASSERT( cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen );

         // get the template
         CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDoc->GetDocTemplate();

         // get the plugin
         CComPtr<IEAFAppPlugin> appPlugin;
         pTemplate->GetPlugin(&appPlugin);

         CComQIPtr<IEAFAppCommandLine> appCmdLine(appPlugin);
         if ( appCmdLine )
         {
            // let the plugin to deal with the command line
            appCmdLine->ProcessCommandLineOptions(cmdInfo);
            if ( cmdInfo.m_bError )
            {
               cmdInfo.m_bCommandLineMode = TRUE; // will cause an application shutdown
            }
         }
      }
      else
      {
         // otherwise, if no document, try to figure out which app plugin deals with it.
         BOOL bHandled = false;
         if ( cmdInfo.m_bTargetApp )
         {
            // the target app plugin was specified on the command line... find the plugin and
            // let it process the command line...
            CComPtr<IEAFAppPlugin> appPlugin;
            bool bFound = GetAppPluginManager()->FindPlugin(cmdInfo.GetTargetApp(),&appPlugin);
            if ( bFound )
            {
               CComQIPtr<IEAFAppCommandLine> appCmdLine(appPlugin);
               if ( appCmdLine )
               {
                  bHandled = appCmdLine->ProcessCommandLineOptions(cmdInfo);
               }
            }
            else
            {
               // The specified app plug-in wasn't found
               bHandled = true;
               cmdInfo.m_bError = true;
               cmdInfo.m_bCommandLineMode = TRUE;

               // this would be the place to tailor the error message
               // cmdInfo.SetErrorCode(specified app is invalid);
            }
         }
         
         if ( !bHandled && !cmdInfo.m_bError )
         {
            CollectionIndexType nPlugins = GetAppPluginManager()->GetPluginCount();
            for ( CollectionIndexType idx = 0; idx < nPlugins; idx++ )
            {
               CComPtr<IEAFAppPlugin> appPlugin;
               GetAppPluginManager()->GetPlugin(idx,&appPlugin);

               CComQIPtr<IEAFAppCommandLine> appCmdLine(appPlugin);
               if ( appCmdLine )
               {
                  bHandled = appCmdLine->ProcessCommandLineOptions(cmdInfo);
                  if ( bHandled )
                  {
                     break;
                  }
               }
            }
         }

         // none of the plug-ins dealt with it...
         // the parameters are not correct
         if ( !bHandled )
         {
            cmdInfo.m_bError = true;
            cmdInfo.m_bCommandLineMode = TRUE;
         }
      }
   }

   if ( cmdInfo.m_bError )
   {
      DisplayCommandLineErrorMessage();
   }

   m_bCommandLineMode = false;

   // We are doing command line processing, and it should have already happened...
   // At this point, the application is done running.
   // Close the documents and post a WM_QUIT message. This will cause
   // the application to close normally and do all of its necessary cleanup.
   if ( cmdInfo.m_bCommandLineMode )
   {
      CloseAllDocuments(TRUE);
      if ( m_pMainWnd )
      {
         m_pMainWnd->DestroyWindow();
      }
      AfxPostQuitMessage(0);
   }
}

/////////////////////////////////////////////////////////////////////////////
// Helpers for saving/restoring window state
BOOL CEAFApp::ReadWindowPlacement(const CString& strSection,const CString& strKey,LPWINDOWPLACEMENT pwp)
{
   CString strBuffer = GetProfileString(strSection, strKey);

   if (strBuffer.IsEmpty())
   {
      return FALSE;
   }

   WINDOWPLACEMENT wp;
   int nRead = _stscanf_s(strBuffer, m_strWindowPlacementFormat,
      &wp.flags, &wp.showCmd,
      &wp.ptMinPosition.x, &wp.ptMinPosition.y,
      &wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
      &wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
      &wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);

   if (nRead != 10)
   {
      return FALSE;
   }

   wp.length = sizeof wp;
   *pwp = wp;

   return TRUE;
}

void CEAFApp::WriteWindowPlacement(const CString& strSection,const CString& strKey,LPWINDOWPLACEMENT pwp)
{
   TCHAR szBuffer[sizeof("-32767")*8 + sizeof("65535")*2];

   wsprintf(szBuffer, m_strWindowPlacementFormat,
      pwp->flags, pwp->showCmd,
      pwp->ptMinPosition.x, pwp->ptMinPosition.y,
      pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
      pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
      pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);

   WriteProfileString(strSection, strKey, szBuffer);
}

// returns key for HKEY_LOCAL_MACHINE\Software\Washington State Department of Transportation\PGSuper"
// responsibility of the caller to call RegCloseKey() on the returned HKEY
// key is not created if missing (
HKEY CEAFApp::GetAppLocalMachineRegistryKey(REGSAM samDesired)
{
	ASSERT(m_pszRegistryKey != nullptr);
	ASSERT(m_pszProfileName != nullptr);

	HKEY hAppKey = nullptr;
	HKEY hSoftKey = nullptr;
	HKEY hCompanyKey = nullptr;


   // open the "software" key
   LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("software"), 0, samDesired, &hSoftKey);
	if ( result == ERROR_SUCCESS)
	{
      // open the "Washington State Department of Transportation" key
      result = RegOpenKeyEx(hSoftKey, m_pszRegistryKey, 0, samDesired, &hCompanyKey);
		if (result == ERROR_SUCCESS)
		{
         // Open the "PGSuper" key
			result = RegOpenKeyEx(hCompanyKey, m_pszProfileName, 0, samDesired, &hAppKey);
		}
	}

	if (hSoftKey != nullptr)
   {
		RegCloseKey(hSoftKey);
   }
	
   if (hCompanyKey != nullptr)
   {
		RegCloseKey(hCompanyKey);
   }

	return hAppKey;
}

// returns key for:
//      HKEY_LOCAL_MACHINE\"Software"\Washington State Deparment of Transportation\PGSuper\lpszSection
// responsibility of the caller to call RegCloseKey() on the returned HKEY
HKEY CEAFApp::GetLocalMachineSectionKey(LPCTSTR lpszSection,REGSAM samDesired)
{
	HKEY hAppKey = GetAppLocalMachineRegistryKey(samDesired);
	if (hAppKey == nullptr)
   {
		return nullptr;
   }

   return GetLocalMachineSectionKey(hAppKey,lpszSection,samDesired);
}

HKEY CEAFApp::GetLocalMachineSectionKey(HKEY hAppKey,LPCTSTR lpszSection,REGSAM samDesired)
{
	ASSERT(lpszSection != nullptr);

	HKEY hSectionKey = nullptr;

	LONG result = RegOpenKeyEx(hAppKey, lpszSection, 0, samDesired, &hSectionKey);
	RegCloseKey(hAppKey);
	return hSectionKey;
}

UINT CEAFApp::GetLocalMachineInt(LPCTSTR lpszSection, LPCTSTR lpszEntry,int nDefault)
{
	HKEY hAppKey = GetAppLocalMachineRegistryKey(KEY_READ);
	if (hAppKey == nullptr)
   {
		return nDefault;
   }

   return GetLocalMachineInt(hAppKey,lpszSection,lpszEntry,nDefault);
}

UINT CEAFApp::GetLocalMachineInt(HKEY hAppKey,LPCTSTR lpszSection, LPCTSTR lpszEntry,int nDefault)
{
	ASSERT(lpszSection != nullptr);
	ASSERT(lpszEntry != nullptr);
	ASSERT(m_pszRegistryKey != nullptr);

	HKEY hSecKey = GetLocalMachineSectionKey(hAppKey,lpszSection,KEY_READ);
	if (hSecKey == nullptr)
   {
		return nDefault;
   }

	DWORD dwValue;
	DWORD dwType;
	DWORD dwCount = sizeof(DWORD);
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, nullptr, &dwType,(LPBYTE)&dwValue, &dwCount);

	RegCloseKey(hSecKey);
	if (lResult == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_DWORD);
		ASSERT(dwCount == sizeof(dwValue));
		return (UINT)dwValue;
	}
	return nDefault;
}

CString CEAFApp::GetLocalMachineString(LPCTSTR lpszSection, LPCTSTR lpszEntry,LPCTSTR lpszDefault)
{
	HKEY hAppKey = GetAppLocalMachineRegistryKey(KEY_READ);
	if (hAppKey == nullptr)
   {
		return lpszDefault;
   }

   return GetLocalMachineString(hAppKey,lpszSection,lpszEntry,lpszDefault);
}

CString CEAFApp::GetLocalMachineString(HKEY hAppKey,LPCTSTR lpszSection, LPCTSTR lpszEntry,LPCTSTR lpszDefault)
{
	ASSERT(lpszSection != nullptr);
	ASSERT(lpszEntry != nullptr);
	ASSERT(m_pszRegistryKey != nullptr);
	HKEY hSecKey = GetLocalMachineSectionKey(hAppKey,lpszSection,KEY_READ);
	if (hSecKey == nullptr)
   {
		return lpszDefault;
   }
	CString strValue;
	DWORD dwType, dwCount;
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, nullptr, &dwType, nullptr, &dwCount);
	if (lResult == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_SZ);
		lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, nullptr, &dwType,
			(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
		strValue.ReleaseBuffer();
	}
	RegCloseKey(hSecKey);
	if (lResult == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_SZ);
		return strValue;
	}
	return lpszDefault;
}

HKEY CEAFApp::GetUninstallRegistryKey()
{
	HKEY hSoftKey = nullptr;
	HKEY hCompanyKey = nullptr;
   HKEY hWinKey = nullptr;
   HKEY hCVKey = nullptr;
   HKEY hUninstallKey = nullptr;


   // open the "software" key
   LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("software"), 0, KEY_READ, &hSoftKey);
	if ( result == ERROR_SUCCESS)
	{
      // open the "Microsoft" key
      result = RegOpenKeyEx(hSoftKey, _T("Microsoft"), 0,  KEY_READ, &hCompanyKey);
		if (result == ERROR_SUCCESS)
		{
         // Open the "Windows" key
			result = RegOpenKeyEx(hCompanyKey, _T("Windows"), 0, KEY_READ, &hWinKey);

         if (result == ERROR_SUCCESS)
		   {
            // Open the "CurrentVersion" key
			   result = RegOpenKeyEx(hWinKey, _T("CurrentVersion"), 0, KEY_READ, &hCVKey);
            if (result == ERROR_SUCCESS)
		      {
               // Open the "Uninstall" key
			      result = RegOpenKeyEx(hCVKey, _T("Uninstall"), 0, KEY_READ, &hUninstallKey);
		      }
		   }
		}
	}

	if (hSoftKey != nullptr)
   {
		RegCloseKey(hSoftKey);
   }
	
   if (hCompanyKey != nullptr)
   {
		RegCloseKey(hCompanyKey);
   }
	
   if (hWinKey != nullptr)
   {
		RegCloseKey(hWinKey);
   }
	
   if (hCVKey != nullptr)
   {
		RegCloseKey(hCVKey);
   }

	return hUninstallKey;
}

AcceptanceType CEAFApp::ShowLegalNoticeAtStartup(void)
{
   if ( m_bShowLegalNotice == VARIANT_TRUE )
   {
      return ShowLegalNotice(VARIANT_TRUE);
   }

   return atAccept;
}

AcceptanceType CEAFApp::ShowLegalNotice(VARIANT_BOOL bGiveChoice)
{
   CComPtr<IARPNotice> pNotice;
   if ( FAILED(pNotice.CoCreateInstance(CLSID_ARPNotice) ) )
   {
      // There was an error creating the legal notice
      m_bShowLegalNotice = VARIANT_TRUE;
      return atAccept;
   }

   pNotice->put_ShowAgain( m_bShowLegalNotice );
   AcceptanceType accept;
   pNotice->Show(bGiveChoice,ltAROSL,&accept);
   pNotice->get_ShowAgain(&m_bShowLegalNotice);

   return accept;
}

CString CEAFApp::GetDocumentationSetName()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   return AfxGetAppName();
}

CString CEAFApp::GetDocumentationMapFile()
{
   if ( UseOnlineDocumentation() && !m_strOnlineDocumentationMapFile.IsEmpty() )
   {
      // if we are using online documentation and we have the file name, no need to get it again
      m_strDocumentationMapFile = m_strOnlineDocumentationMapFile;
   }

   if ( m_strDocumentationMapFile.IsEmpty() )
   {
      m_strDocumentationMapFile = EAFGetDocumentationMapFile(GetDocumentationSetName(),GetDocumentationURL());

      if ( UseOnlineDocumentation() )
      {
         m_strOnlineDocumentationMapFile = m_strDocumentationMapFile;
      }
   }

   return m_strDocumentationMapFile;
}

void CEAFApp::LoadDocumentationMap()
{
   CString mapFileName(GetDocumentationMapFile());
   VERIFY(EAFLoadDocumentationMap(mapFileName,m_HelpTopics));
}


////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CEAFPluginApp, CEAFApp)

BOOL CEAFPluginApp::InitInstance()
{
   GetPluginManager()->SetParent(this);

   if ( !CEAFApp::InitInstance() )
   {
      return FALSE;
   }

   // The installer should do this, but just in case it doesn't we'll do it here
   WBFL::System::ComCatMgr::CreateCategory(GetAppPluginCategoryName(),GetAppPluginCategoryID());

   return TRUE;
}

BEGIN_MESSAGE_MAP(CEAFPluginApp, CEAFApp)
	//{{AFX_MSG_MAP(CEAFPluginApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(EAFID_MANAGE_APP_PLUGINS, OnManageApplicationPlugins)
	ON_UPDATE_COMMAND_UI(EAFID_MANAGE_APP_PLUGINS, OnUpdateManageApplicationPlugins)
END_MESSAGE_MAP()


CEAFPluginManager* CEAFPluginApp::GetPluginManager()
{
   return &m_PluginManager;
}

void CEAFPluginApp::OnUpdateManageApplicationPlugins(CCmdUI* pCmdUI)
{
   pCmdUI->SetText(_T("Project Types"));
}

void CEAFPluginApp::OnManageApplicationPlugins()
{
   std::vector<CEAFPluginState> pluginStates = EAFManageApplicationPlugins(_T("Manage Project Types"),nullptr,GetAppPluginCategoryID(),EAFGetMainFrame());
   for ( const auto& state : pluginStates)
   {
      CEAFAppPluginManager* pPluginMgr = GetAppPluginManager();

      if ( state.StateChanged() )
      {
         if ( state.InitiallyEnabled() )
         {
            // was initially enabled, now it is disabled
            CComPtr<IEAFAppPlugin> plugin;
            pPluginMgr->GetPlugin( state.GetCLSID(), &plugin);
            plugin->IntegrateWithUI(FALSE);
            
            pPluginMgr->RemovePlugin(state.GetCLSID());

            // find all document templates associated with this plugin and remove them
            POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
            while ( pos != nullptr )
            {
               POSITION current_pos = pos;
               CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)(m_pDocManager->GetNextDocTemplate( pos ));
               CComPtr<IEAFAppPlugin> my_plugin;
               pTemplate->GetPlugin(&my_plugin);
               if ( my_plugin.IsEqualObject(plugin) )
               {
                  ((CEAFDocManager*)m_pDocManager)->RemoveDocTemplate(current_pos);
               }
            }

            WriteProfileString(_T("Plugins"),state.GetCLSIDString(),_T("Disabled"));
         }
         else
         {
            // was not initially enabled, but it is now enabled
            CComPtr<IEAFAppPlugin> plugin;
            if ( SUCCEEDED(plugin.CoCreateInstance(state.GetCLSID())) )
            {
               pPluginMgr->AddPlugin( state.GetCLSID(), plugin );
               plugin->IntegrateWithUI(TRUE); // must come after AddPlugin

               std::vector<CEAFDocTemplate*> vDocTemplates = plugin->CreateDocTemplates();
               for ( const auto& pDocTemplate : vDocTemplates)
               {
                  if ( pDocTemplate )
                  {
                     pDocTemplate->SetPlugin(plugin);
                     m_pDocManager->AddDocTemplate( pDocTemplate );
                  }
               }

               WriteProfileString(_T("Plugins"),state.GetCLSIDString(),_T("Enabled"));
            }
            else
            {
               AfxMessageBox(_T("Error creating plugin"));
            }
         }
      }
   }
}

BOOL CEAFPluginApp::CreateApplicationPlugins()
{
   // Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
   GetAppPluginManager()->SetCATID(GetAppPluginCategoryID());
   if ( !GetAppPluginManager()->LoadPlugins() )
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CEAFPluginApp::CreatePlugins()
{
   GetPluginManager()->SetCATID(GetPluginCategoryID());
   if ( !GetPluginManager()->LoadPlugins() )
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CEAFPluginApp::RegisterDocTemplates()
{
   if ( !CreatePlugins() )
   {
      return FALSE;
   }

   if ( !GetPluginManager()->InitPlugins() )
   {
      return FALSE;
   }

   return CEAFApp::RegisterDocTemplates();
}

BOOL CEAFPluginApp::AppPluginUIIntegration(BOOL bIntegrate)
{
   CEAFApp::AppPluginUIIntegration(bIntegrate);
   GetPluginManager()->IntegrateWithUI(bIntegrate);
   return TRUE;
}

void CEAFPluginApp::LoadDocumentationMap()
{
   CEAFApp::LoadDocumentationMap();

   GetPluginManager()->LoadDocumentationMaps();
}

eafTypes::HelpResult CEAFPluginApp::GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL)
{
   eafTypes::HelpResult result = CEAFApp::GetDocumentLocation(lpszDocSetName,nHID,strURL);
   if ( result == eafTypes::hrDocSetNotFound )
   {
      result = GetPluginManager()->GetDocumentLocation(lpszDocSetName,nHID,strURL);
   }
   return result;
}

void save_doc(CDocument* pDoc,void* pStuff)
{
   if ( pDoc->IsModified() )
   {
      pDoc->DoFileSave();
   }
}

void notify_error(CDocument* pDoc,void* pStuff)
{
   if ( pDoc->IsKindOf(RUNTIME_CLASS(CEAFDocument)) )
   {
      CEAFDocument* pEAFDoc = (CEAFDocument*)pDoc;
      pEAFDoc->OnUpdateError(*((CString*)pStuff));
   }
}

void log_error(CDocument* pDoc,void* pStuff)
{
   CXShutDown* pXShutDown = (CXShutDown*)pStuff;
   if ( pDoc->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
   {
      CEAFBrokerDocument* pBrokerDoc = (CEAFBrokerDocument*)pDoc;

      CComPtr<IBroker> pBroker;
      pBrokerDoc->GetBroker(&pBroker);

      GET_IFACE2(pBroker,IEAFProjectLog,pLog);

      std::_tstring error_message;
      pXShutDown->GetErrorMessage( &error_message );

      CString msg;
      msg.Format(_T("%s\nFile : %s\nLine : %d\n"), error_message.c_str(), pXShutDown->GetFile().c_str(), pXShutDown->GetLine() );

      pLog->LogMessage( msg );
   }
}



WBFL::Units::IndirectMeasure init_si_units()
{
   WBFL::Units::IndirectMeasure im;
   im.Name = _T("SI");
   
   im.StationFormat = WBFL::Units::StationFormats::SI;

   im.Scalar.Width = 8;
   im.Scalar.Precision = 3;
   im.Scalar.Format = WBFL::System::NumericFormatTool::Format::Fixed;

   im.Percentage.Width = 7;
   im.Percentage.Precision = 2;
   im.Percentage.Format = WBFL::System::NumericFormatTool::Format::Fixed;

   im.ComponentDim.Update(    WBFL::Units::Measure::Millimeter,                0.001, 8, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.XSectionDim.Update(     WBFL::Units::Measure::Meter,                     0.001, 7, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.SpanLength.Update(      WBFL::Units::Measure::Meter,                     0.001, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.AlignmentLength.Update( WBFL::Units::Measure::Meter,                     0.001,16, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Deflection.Update(    WBFL::Units::Measure::Millimeter,                  0.001, 8, 1, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Area.Update(            WBFL::Units::Measure::Millimeter2,               0.001, 8, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.MomentOfInertia.Update( WBFL::Units::Measure::Millimeter4,               0.001, 7, 0, WBFL::System::NumericFormatTool::Format::Engineering );
   im.SectModulus.Update(     WBFL::Units::Measure::Millimeter3,               0.001, 7, 0, WBFL::System::NumericFormatTool::Format::Engineering );
   im.AvOverS.Update(         WBFL::Units::Measure::Millimeter2PerMeter,      1.0e-6, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Stress.Update(          WBFL::Units::Measure::MPa,                       0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.ModE.Update(            WBFL::Units::Measure::MPa,                       0.001,13, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.GeneralForce.Update(    WBFL::Units::Measure::Kilonewton,                0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Tonnage.Update(         WBFL::Units::Measure::Kilonewton,                0.001, 9, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Shear.Update(           WBFL::Units::Measure::Kilonewton,                0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Moment.Update(          WBFL::Units::Measure::KilonewtonMeter,           0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.SmallMoment.Update(     WBFL::Units::Measure::NewtonMillimeter,          0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Angle.Update(           WBFL::Units::Measure::Degree,                    0.001, 7, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.RadAngle.Update(        WBFL::Units::Measure::Radian,                   1.0e-5, 9, 5, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Density.Update(         WBFL::Units::Measure::KgPerMeter3,               0.001, 6, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.MassPerLength.Update(   WBFL::Units::Measure::KgPerMeter,                0.001, 5, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.ForcePerLength.Update(  WBFL::Units::Measure::KilonewtonPerMeter,        0.001, 8, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.MomentPerAngle.Update(  WBFL::Units::Measure::KiloNewtonMeterPerRadian,  0.001, 8, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Time.Update(            WBFL::Units::Measure::Hour,                      0.001, 5, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Time2.Update(           WBFL::Units::Measure::Day,                       0.001, 9, 0, WBFL::System::NumericFormatTool::Format::Automatic);
   im.Time3.Update(           WBFL::Units::Measure::Day,                       0.001, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.ForceLength2.Update(    WBFL::Units::Measure::KilonewtonMeter2,          0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.SqrtPressure.Update(    WBFL::Units::Measure::SqrtMPa,                   0.001, 9, 4, WBFL::System::NumericFormatTool::Format::Fixed );
   im.PerLength.Update(       WBFL::Units::Measure::PerMeter,                 1.0e-9,14, 8, WBFL::System::NumericFormatTool::Format::Fixed);
   im.Curvature.Update(       WBFL::Units::Measure::PerMillimeter,            1.0e-9,14, 8, WBFL::System::NumericFormatTool::Format::Fixed);
   im.SmallStress.Update(     WBFL::Units::Measure::Pa,                        0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.WindPressure.Update(    WBFL::Units::Measure::Pa,                        0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Velocity.Update(        WBFL::Units::Measure::KilometerPerHour,          0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed);

   return im;
}

WBFL::Units::IndirectMeasure init_english_units()
{
   WBFL::Units::IndirectMeasure im;

   im.Name = _T("English");

   im.StationFormat = WBFL::Units::StationFormats::US;

   im.Scalar.Width = 8;
   im.Scalar.Precision = 3;
   im.Scalar.Format = WBFL::System::NumericFormatTool::Format::Fixed;

   im.Percentage.Width = 7;
   im.Percentage.Precision = 2;
   im.Percentage.Format = WBFL::System::NumericFormatTool::Format::Fixed;

   im.ComponentDim.Update(    WBFL::Units::Measure::Inch,            0.001, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.XSectionDim.Update(     WBFL::Units::Measure::Feet,            0.001, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.SpanLength.Update(      WBFL::Units::Measure::Feet,            0.001, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.AlignmentLength.Update( WBFL::Units::Measure::Feet,            0.001,16, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Deflection.Update(      WBFL::Units::Measure::Inch,            0.001, 8, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Area.Update(            WBFL::Units::Measure::Inch2,           0.001,10, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.MomentOfInertia.Update( WBFL::Units::Measure::Inch4,           0.001,12, 1, WBFL::System::NumericFormatTool::Format::Fixed );
   im.SectModulus.Update(     WBFL::Units::Measure::Inch3,           0.001,12, 1, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Stress.Update(          WBFL::Units::Measure::KSI,            1.0e-5, 8, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.AvOverS.Update(         WBFL::Units::Measure::Inch2PerFoot,   1.0e-7, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.ModE.Update(            WBFL::Units::Measure::KSI,            1.0e-5,10, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.GeneralForce.Update(    WBFL::Units::Measure::Kip,            1.0e-5, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Tonnage.Update(         WBFL::Units::Measure::Ton,             0.001, 9, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Shear.Update(           WBFL::Units::Measure::Kip,            1.0e-5, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Moment.Update(          WBFL::Units::Measure::KipFeet,        1.0e-5, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.SmallMoment.Update(     WBFL::Units::Measure::KipInch,        1.0e-5, 9, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Angle.Update(           WBFL::Units::Measure::Degree,          0.001, 7, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.RadAngle.Update(        WBFL::Units::Measure::Radian,         1.0e-5, 9, 5, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Density.Update(         WBFL::Units::Measure::KipPerFeet3,     0.001, 6, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.MassPerLength.Update(   WBFL::Units::Measure::LbfPerFeet,      0.001, 5, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.ForcePerLength.Update(  WBFL::Units::Measure::KipPerFoot,     1.0e-5, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.MomentPerAngle.Update(  WBFL::Units::Measure::KipInchPerRadian,0.001,10, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Time.Update(            WBFL::Units::Measure::Hour,            0.001, 5, 0, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Time2.Update(           WBFL::Units::Measure::Day,             0.001, 9, 0, WBFL::System::NumericFormatTool::Format::Automatic);
   im.Time3.Update(           WBFL::Units::Measure::Day,             0.001, 9, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.ForceLength2.Update(    WBFL::Units::Measure::KipInch2,        0.001, 9, 2, WBFL::System::NumericFormatTool::Format::Fixed );
   im.SqrtPressure.Update(    WBFL::Units::Measure::SqrtKSI,         0.001, 9, 4, WBFL::System::NumericFormatTool::Format::Fixed );
   im.PerLength.Update(       WBFL::Units::Measure::PerFeet,        1.0e-5, 9, 4, WBFL::System::NumericFormatTool::Format::Fixed);
   im.Curvature.Update(       WBFL::Units::Measure::PerInch,        1.0e-9,14, 8, WBFL::System::NumericFormatTool::Format::Fixed);
   im.SmallStress.Update(     WBFL::Units::Measure::KSF,            1.0e-5, 8, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.WindPressure.Update(    WBFL::Units::Measure::PSF,            1.0e-5, 8, 3, WBFL::System::NumericFormatTool::Format::Fixed );
   im.Velocity.Update(        WBFL::Units::Measure::MilePerHour,    1.0e-5, 8, 2, WBFL::System::NumericFormatTool::Format::Fixed );

   return im;
}
