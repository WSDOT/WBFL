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

// EAFApp.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include <EAF\EAFResources.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFDocManager.h>
#include <EAF\EAFPluginManager.h>
#include <EAF\EAFSplashScreen.h>
#include <System\ComCatMgr.h>

#include <EAF\EAFAboutDlg.h>
#include "UnitsDlg.h"
#include "TipDlg.h"

#include "custsite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


unitmgtIndirectMeasure init_si_units()
{
   unitmgtIndirectMeasure im;
   im.Name = "SI";
   
   im.StationFormat = unitStationFormats::SI;

   im.Scalar.Width = 8;
   im.Scalar.Precision = 3;
   im.Scalar.Format = sysNumericFormatTool::Fixed;

   im.ComponentDim.Update(    unitMeasure::Millimeter,                0.001, 8, 0, sysNumericFormatTool::Fixed );
   im.XSectionDim.Update(     unitMeasure::Meter,                     0.001, 7, 3, sysNumericFormatTool::Fixed );
   im.SpanLength.Update(      unitMeasure::Meter,                     0.001, 9, 3, sysNumericFormatTool::Fixed );
   im.AlignmentLength.Update( unitMeasure::Meter,                     0.001,16, 3, sysNumericFormatTool::Fixed );
   im.Displacement.Update(    unitMeasure::Millimeter,                0.001, 8, 1, sysNumericFormatTool::Fixed );
   im.Area.Update(            unitMeasure::Millimeter2,               0.001, 8, 0, sysNumericFormatTool::Fixed );
   im.MomentOfInertia.Update( unitMeasure::Millimeter4,               0.001, 7, 0, sysNumericFormatTool::Engineering );
   im.SectModulus.Update(     unitMeasure::Millimeter3,               0.001, 7, 0, sysNumericFormatTool::Engineering );
   im.AvOverS.Update(         unitMeasure::Millimeter2PerMeter,      1.0e-6, 9, 3, sysNumericFormatTool::Fixed );
   im.Stress.Update(          unitMeasure::MPa,                       0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.ModE.Update(            unitMeasure::MPa,                       0.001,12, 0, sysNumericFormatTool::Fixed );
   im.GeneralForce.Update(    unitMeasure::Kilonewton,                0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Tonnage.Update(         unitMeasure::Kilonewton,                0.001, 9, 0, sysNumericFormatTool::Fixed );
   im.Shear.Update(           unitMeasure::Kilonewton,                0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Moment.Update(          unitMeasure::KilonewtonMeter,           0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.SmallMoment.Update(     unitMeasure::NewtonMillimeter,          0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Angle.Update(           unitMeasure::Degree,                    0.001, 7, 2, sysNumericFormatTool::Fixed );
   im.RadAngle.Update(        unitMeasure::Radian,                   1.0e-5, 9, 3, sysNumericFormatTool::Fixed );
   im.Density.Update(         unitMeasure::KgPerMeter3,               0.001, 6, 0, sysNumericFormatTool::Fixed );
   im.MassPerLength.Update(   unitMeasure::KgPerMeter,                0.001, 5, 0, sysNumericFormatTool::Fixed );
   im.ForcePerLength.Update(  unitMeasure::KilonewtonPerMeter,        0.001, 8, 2, sysNumericFormatTool::Fixed );
   im.MomentPerAngle.Update(  unitMeasure::KiloNewtonMeterPerRadian,  0.001, 8, 2, sysNumericFormatTool::Fixed );
   im.Time.Update(            unitMeasure::Hour,                      0.001, 5, 0, sysNumericFormatTool::Fixed );
   im.Time2.Update(           unitMeasure::Day,                       0.001, 7, 0, sysNumericFormatTool::Fixed );
   im.ForceLength2.Update(    unitMeasure::KilonewtonMeter2,          0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.SqrtPressure.Update(    unitMeasure::SqrtMPa,                   0.001, 9, 4, sysNumericFormatTool::Fixed );
   im.PerLength.Update( unitMeasure::PerMillimeter, 1.0e-7, 9, 3, sysNumericFormatTool::Scientific);
   im.SmallStress.Update(          unitMeasure::Pa,                       0.001, 9, 2, sysNumericFormatTool::Fixed );

   return im;
}

unitmgtIndirectMeasure init_english_units()
{
   unitmgtIndirectMeasure im;

   im.Name = "English";

   im.StationFormat = unitStationFormats::US;

   im.Scalar.Width = 8;
   im.Scalar.Precision = 3;
   im.Scalar.Format = sysNumericFormatTool::Fixed;

   im.ComponentDim.Update(    unitMeasure::Inch,            0.001, 9, 3, sysNumericFormatTool::Fixed );
   im.XSectionDim.Update(     unitMeasure::Feet,            0.001, 9, 3, sysNumericFormatTool::Fixed );
   im.SpanLength.Update(      unitMeasure::Feet,            0.001, 9, 3, sysNumericFormatTool::Fixed );
   im.AlignmentLength.Update( unitMeasure::Feet,            0.001,16, 4, sysNumericFormatTool::Fixed );
   im.Displacement.Update(    unitMeasure::Inch,            0.001, 8, 3, sysNumericFormatTool::Fixed );
   im.Area.Update(            unitMeasure::Inch2,           0.001,10, 3, sysNumericFormatTool::Fixed );
   im.MomentOfInertia.Update( unitMeasure::Inch4,           0.001,12, 1, sysNumericFormatTool::Fixed );
   im.SectModulus.Update(     unitMeasure::Inch3,           0.001,12, 1, sysNumericFormatTool::Fixed );
   im.Stress.Update(          unitMeasure::KSI,             0.001, 8, 3, sysNumericFormatTool::Fixed );
   im.AvOverS.Update(         unitMeasure::Inch2PerFoot,   1.0e-7, 9, 3, sysNumericFormatTool::Fixed );
   im.ModE.Update(            unitMeasure::KSI,             0.001,14, 0, sysNumericFormatTool::Fixed );
   im.GeneralForce.Update(    unitMeasure::Kip,             0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Tonnage.Update(         unitMeasure::Ton,             0.001, 9, 0, sysNumericFormatTool::Fixed );
   im.Shear.Update(           unitMeasure::Kip,             0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Moment.Update(          unitMeasure::KipFeet,         0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.SmallMoment.Update(     unitMeasure::KipInch,         0.001, 9, 0, sysNumericFormatTool::Fixed );
   im.Angle.Update(           unitMeasure::Degree,          0.001, 7, 2, sysNumericFormatTool::Fixed );
   im.RadAngle.Update(        unitMeasure::Radian,         1.0e-5, 9, 3, sysNumericFormatTool::Fixed );
   im.Density.Update(         unitMeasure::LbfPerFeet3,     0.001, 6, 0, sysNumericFormatTool::Fixed );
   im.MassPerLength.Update(   unitMeasure::LbfPerFeet,      0.001, 5, 0, sysNumericFormatTool::Fixed );
   im.ForcePerLength.Update(  unitMeasure::KipPerFoot,      0.001, 9, 3, sysNumericFormatTool::Fixed );
   im.MomentPerAngle.Update(  unitMeasure::KipInchPerRadian,0.001,10, 2, sysNumericFormatTool::Fixed );
   im.Time.Update(            unitMeasure::Hour,            0.001, 5, 0, sysNumericFormatTool::Fixed );
   im.Time2.Update(           unitMeasure::Day,             0.001, 7, 0, sysNumericFormatTool::Fixed );
   im.ForceLength2.Update(    unitMeasure::KipInch2,        0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.SqrtPressure.Update(    unitMeasure::SqrtKSI,         0.001, 9, 4, sysNumericFormatTool::Fixed );
   im.PerLength.Update( unitMeasure::PerFeet, 1.0e-5, 9, 4, sysNumericFormatTool::Fixed);
   im.SmallStress.Update(          unitMeasure::PSF,             0.001, 8, 3, sysNumericFormatTool::Fixed );

   return im;
}

/////////////////////////////////////////////////////////////////////////////
// CEAFApp

IMPLEMENT_DYNAMIC(CEAFApp, CWinApp)

CEAFApp::CEAFApp() :
m_strWindowPlacementFormat("%u,%u,%d,%d,%d,%d,%d,%d,%d,%d")
{
   m_bShowLegalNotice = VARIANT_TRUE;
   m_bTipsEnabled = false;
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
   catch(sysXBase& e)
   {
      std::string msg;
      e.GetErrorMessage(&msg);
      AfxMessageBox(msg.c_str(),MB_OK);
      ExitInstance();
   }

   return retval;
}

BOOL CEAFApp::InitInstance()
{
   // Initialize OLE libraries
	if (!SUCCEEDED(OleInitialize(NULL)))
	{
		AfxMessageBox("OLE initialization failed. Make sure that the OLE libraries are the correct version.");
		return FALSE;
	}

   // Get the units system set up 
   InitDisplayUnits();

   // Change the registry key under which our settings are stored.
	SetRegistryKey(GetRegistryKey());
   RegistryInit();

   // more initialization before we can do any work
   m_PluginManager.SetParent(this);
   m_ComponentInfoManager.SetParent(this);
   m_pDocManager = CreateDocumentManager();
   m_pDocTemplateRegistrar = CreateDocTemplateRegistrar();

   CCustomOccManager *pMgr = new CCustomOccManager;
   AfxEnableControlContainer(pMgr); // for CEAFReportView / IE Web Browser plug-in

   // Parse command line for standard shell commands, DDE, file open
	CEAFCommandLineInfo& cmdInfo = GetCommandLineInfo();
	ParseCommandLine(cmdInfo);
   if ( cmdInfo.m_bAbort )
   {
      DisplayCommandLineUsage();
      return FALSE;
   }

   if ( !cmdInfo.m_CommandLineMode )
   {
      // Show legal notice if not in command line mode
      if ( ShowLegalNoticeAtStartup() == atReject )
         return FALSE; // License was not accepted
   }

   // Show splash screen (does nothing if splash screen is disabled)
   CEAFSplashScreen::SetSplashScreenInfo(GetSplashScreenInfo());
   CEAFSplashScreen::ShowSplashScreen(NULL,TRUE);

   // Register the document templates... this is where the "plug-ins" get integrated
   // into the application framework
   if ( !RegisterDocTemplates() )
      return FALSE;

   // TODO: Add a method call that causes all app-plugins that need to 
   // check and possibly refresh a cache the opportunity to do so
   // - or do it in RegisterDOcTEmplates... or with the plugin manager

   // create main MDI Frame window
   m_pMainWnd = CreateMainFrame();
   if ( !m_pMainWnd )
      return FALSE;

   // Don't display a new window on startup
   // Q141725
   if ( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew )
      cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
   // This is not a virtual function... it needs to be called so MFC can do its job
   // but somehow we need to direct command line information to the correct
   // app-plugin (based on file extension and keyword parameter)
   // Whatever virtual function get called here, this is where the /Test parameter
   // is processed (see notes in CPGSuperApp
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

   // Done with splash screen
   CEAFSplashScreen::CloseOnNextTimeout();

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// The main window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

   if ( IsTipOfTheDayEnabled() && m_CommandLineInfo.m_bShowSplash )
      ShowTipOfTheDay();

	return TRUE;
}

int CEAFApp::ExitInstance()
{
	int result = CWinApp::ExitInstance(); // must call before UnloadPlugins

   // the document manager is usually deleted in CWinApp::~CWinApp, however,
   // when the plug in manager unloads the plug-ins, the DLLs from where the
   // document templates were created are unloaded from memory. this causes
   // all sorts of problems when the base class deletes the document manager.
   //
   // delete the document manager here, which will cause the doc templates to
   // be deleted, before the plug-in DLLs are unloaded.
   if ( m_pDocManager )
      delete m_pDocManager;

   m_pDocManager = NULL;
   
   m_PluginManager.UnloadPlugins();
   m_ComponentInfoManager.UnloadPlugins();

   if ( m_pDocTemplateRegistrar )
      delete m_pDocTemplateRegistrar;

   RegistryExit();

   //::CoUninitialize();
   ::OleUninitialize();

   return result;

}

void CEAFApp::RegistryInit()
{
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
   CString strDefaultLegalNotice = GetLocalMachineString(_T("Settings"),_T("LegalNotice"), _T("On"));

   CString strLegalNotice = GetProfileString(_T("Settings"),_T("LegalNotice"),strDefaultLegalNotice);
   if ( strLegalNotice.CompareNoCase(_T("On")) == 0 )
      m_bShowLegalNotice = VARIANT_TRUE;
   else
      m_bShowLegalNotice = VARIANT_FALSE;
}

void CEAFApp::RegistryExit()
{
   VERIFY(WriteProfileString( _T("Settings"),_T("LegalNotice"),m_bShowLegalNotice == VARIANT_TRUE ? _T("On") : _T("Off") ));
}

CEAFCommandLineInfo& CEAFApp::GetCommandLineInfo()
{
   return m_CommandLineInfo;
}

void CEAFApp::DisplayCommandLineUsage()
{
   CEAFCommandLineInfo& cmdInfo = GetCommandLineInfo();
   CString strMsg = cmdInfo.GetUsageMessage();
   AfxMessageBox(strMsg,MB_OK | MB_ICONEXCLAMATION);
}

CMDIFrameWnd* CEAFApp::CreateMainFrame()
{
	CEAFMainFrame* pMainFrame = new CEAFMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
   {
      delete pMainFrame;
		return NULL;
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
   filePath.Replace( finder.GetFileName(), "" );

   return filePath;
}

void CEAFApp::EnableTipOfTheDay(LPCTSTR lpszTipFile)
{
   if ( lpszTipFile == NULL )
   {
      m_bTipsEnabled = false;
      m_TipFilePath.Empty();
   }
   else
   {
      m_bTipsEnabled = true;
      m_TipFilePath = lpszTipFile;
   }
}

bool CEAFApp::IsTipOfTheDayEnabled()
{
   BOOL bTipsEnabled = GetProfileInt(_T("Tip"),_T("StartUp"),TRUE);
   return bTipsEnabled && m_bTipsEnabled;
}

void CEAFApp::ShowTipOfTheDay(void)
{
	CTipDlg dlg(m_TipFilePath,AfxGetMainWnd());
	dlg.DoModal();
}

BOOL CEAFApp::IsDocLoaded()
{
   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
   CEAFDocument* pDoc = pMainFrame->GetDocument();
   return (pDoc == NULL ? FALSE : TRUE);
}

BEGIN_MESSAGE_MAP(CEAFApp, CWinApp)
	//{{AFX_MSG_MAP(CEAFApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
	ON_COMMAND(ID_APP_LEGAL, OnAppLegal)

	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)

   // Standard unit mode commands
	ON_COMMAND(ID_EDIT_UNITS, OnEditUnits)
   ON_COMMAND(ID_UNITS_SI,OnSIUnits)
   ON_UPDATE_COMMAND_UI(ID_UNITS_SI, OnUpdateSIUnits)
   ON_COMMAND(ID_UNITS_US,OnUSUnits)
   ON_UPDATE_COMMAND_UI(ID_UNITS_US, OnUpdateUSUnits)

	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
   ON_COMMAND(ID_APP_ABOUT, &CEAFApp::OnAppAbout)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFApp message handlers
BOOL CEAFApp::RegisterDocTemplates()
{
   if ( !m_ComponentInfoManager.LoadPlugins(GetComponentInfoCategoryID()) )
      return FALSE;

   if ( !m_ComponentInfoManager.InitPlugins() )
      return FALSE;

   if ( !CreateApplicationPlugins() )
      return FALSE;

   if ( !m_PluginManager.InitPlugins() )
      return FALSE;
   
   if ( !m_PluginManager.RegisterDocTemplates(this) )
      return FALSE;

   return TRUE;
}

void CEAFApp::OnAppLegal() 
{
   ShowLegalNotice();	
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

CDocument* CEAFApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
   // make sure the document has a valid file extension before opening
   CDocument* pDoc = NULL;

   CString file_ext;
   CString file_name(lpszFileName);
	int charpos = file_name.ReverseFind('.');
	if (0 <= charpos)
   {
		file_ext = file_name.Right(file_name.GetLength() - charpos);
   }

   bool bExtensionMatched = false;
   POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
   while ( pos != NULL )
   {
      CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate( pos );

      CString str;
      if ( pTemplate->GetDocString(str,CDocTemplate::filterExt) )
      {
         int token_pos = 0;
         CString strExt = str.Tokenize(_T(";"),token_pos);
         while ( strExt != _T("") )
         {
            if ( file_ext.CompareNoCase(strExt) == 0 )
            {
               bExtensionMatched = true;
               pos = NULL; // kills the outer while loop
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
      }
   }
   else
   {
      CString strMsg;
      strMsg.Format("%s is not a valid file for this application. Please select a different file",lpszFileName);
      ::AfxMessageBox(strMsg,MB_ICONEXCLAMATION|MB_OK);
   }

   return pDoc;
}

BOOL CEAFApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
   BOOL bResult = CWinApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

   if ( bResult )
      return bResult; // message was handled

   if ( m_PluginManager.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) )
      return TRUE; // message was handled

   return FALSE; // message was NOT handled, continue routing
}

CEAFDocTemplateRegistrar* CEAFApp::GetDocTemplateRegistrar()
{
   return m_pDocTemplateRegistrar;
}

CEAFAppPluginManager* CEAFApp::GetAppPluginManager()
{
   return &m_PluginManager;
}

CEAFComponentInfoManager* CEAFApp::GetComponentInfoManager()
{
   return &m_ComponentInfoManager;
}

void CEAFApp::InitDisplayUnits()
{
   unitSysUnitsMgr::SetMassUnit( unitMeasure::Kilogram );
   unitSysUnitsMgr::SetLengthUnit( unitMeasure::Meter );
   unitSysUnitsMgr::SetTimeUnit( unitMeasure::Second );
   unitSysUnitsMgr::SetTemperatureUnit( unitMeasure::Celcius );
   unitSysUnitsMgr::SetAngleUnit( unitMeasure::Radian );

   m_UnitLibrary.AddEntry("SI",      init_si_units());
   m_UnitLibrary.AddEntry("English", init_english_units() );
   SetUnitsMode(eafTypes::umUS);
}

void CEAFApp::UpdateDisplayUnits()
{
   std::string units = (m_Units == eafTypes::umUS ? "English" : "SI");
   m_pDisplayUnits = &m_UnitLibrary.GetEntry(units);
}

const unitmgtIndirectMeasure* CEAFApp::GetDisplayUnits() const
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

void CEAFApp::Fire_UnitsChanged()
{
   std::set<iUnitModeListener*>::iterator iter;
   for ( iter = m_UnitModeListeners.begin(); iter != m_UnitModeListeners.end(); iter++ )
   {
      iUnitModeListener* pListener = *iter;
      pListener->OnUnitsModeChanged(m_Units);
   }
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
      return TRUE;

   return CWinApp::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// Helpers for saving/restoring window state
BOOL CEAFApp::ReadWindowPlacement(const CString& strKey,LPWINDOWPLACEMENT pwp)
{
   CString strBuffer = AfxGetApp()->GetProfileString(CString((LPCSTR)IDS_REG_SETTINGS), strKey);

   if (strBuffer.IsEmpty())
      return FALSE;

   WINDOWPLACEMENT wp;
   int nRead = sscanf_s(strBuffer, m_strWindowPlacementFormat,
      &wp.flags, &wp.showCmd,
      &wp.ptMinPosition.x, &wp.ptMinPosition.y,
      &wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
      &wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
      &wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);

   if (nRead != 10)
      return FALSE;

   wp.length = sizeof wp;
   *pwp = wp;

   return TRUE;
}

void CEAFApp::WriteWindowPlacement(const CString& strKey,LPWINDOWPLACEMENT pwp)
{
   TCHAR szBuffer[sizeof("-32767")*8 + sizeof("65535")*2];

   wsprintf(szBuffer, m_strWindowPlacementFormat,
      pwp->flags, pwp->showCmd,
      pwp->ptMinPosition.x, pwp->ptMinPosition.y,
      pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
      pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
      pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);

   AfxGetApp()->WriteProfileString(CString((LPCSTR)IDS_REG_SETTINGS), strKey, szBuffer);
}

// returns key for HKEY_LOCAL_MACHINE\Software\Washington State Department of Transportation\PGSuper"
// responsibility of the caller to call RegCloseKey() on the returned HKEY
// key is not created if missing (
HKEY CEAFApp::GetAppLocalMachineRegistryKey()
{
	ASSERT(m_pszRegistryKey != NULL);
	ASSERT(m_pszProfileName != NULL);

	HKEY hAppKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;


   // open the "software" key
   LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("software"), 0, KEY_WRITE|KEY_READ, &hSoftKey);
	if ( result == ERROR_SUCCESS)
	{
      // open the "Washington State Department of Transportation" key
      result = RegOpenKeyEx(hSoftKey, m_pszRegistryKey, 0, KEY_WRITE|KEY_READ, &hCompanyKey);
		if (result == ERROR_SUCCESS)
		{
         // Open the "PGSuper" key
			result = RegOpenKeyEx(hCompanyKey, m_pszProfileName, 0, KEY_WRITE|KEY_READ, &hAppKey);
		}
	}

	if (hSoftKey != NULL)
		RegCloseKey(hSoftKey);
	
   if (hCompanyKey != NULL)
		RegCloseKey(hCompanyKey);

	return hAppKey;
}

// returns key for:
//      HKEY_LOCAL_MACHINE\"Software"\Washington State Deparment of Transportation\PGSuper\lpszSection
// responsibility of the caller to call RegCloseKey() on the returned HKEY
HKEY CEAFApp::GetLocalMachineSectionKey(LPCTSTR lpszSection)
{
	HKEY hAppKey = GetAppLocalMachineRegistryKey();
	if (hAppKey == NULL)
		return NULL;

   return GetLocalMachineSectionKey(hAppKey,lpszSection);
}

HKEY CEAFApp::GetLocalMachineSectionKey(HKEY hAppKey,LPCTSTR lpszSection)
{
	ASSERT(lpszSection != NULL);

	HKEY hSectionKey = NULL;

	LONG result = RegOpenKeyEx(hAppKey, lpszSection, 0, KEY_WRITE|KEY_READ, &hSectionKey);
	RegCloseKey(hAppKey);
	return hSectionKey;
}

UINT CEAFApp::GetLocalMachineInt(LPCTSTR lpszSection, LPCTSTR lpszEntry,int nDefault)
{
	HKEY hAppKey = GetAppLocalMachineRegistryKey();
	if (hAppKey == NULL)
		return nDefault;

   return GetLocalMachineInt(hAppKey,lpszSection,lpszEntry,nDefault);
}

UINT CEAFApp::GetLocalMachineInt(HKEY hAppKey,LPCTSTR lpszSection, LPCTSTR lpszEntry,int nDefault)
{
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(m_pszRegistryKey != NULL);

	HKEY hSecKey = GetLocalMachineSectionKey(hAppKey,lpszSection);
	if (hSecKey == NULL)
		return nDefault;
	DWORD dwValue;
	DWORD dwType;
	DWORD dwCount = sizeof(DWORD);
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
		(LPBYTE)&dwValue, &dwCount);
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
	HKEY hAppKey = GetAppLocalMachineRegistryKey();
	if (hAppKey == NULL)
		return lpszDefault;

   return GetLocalMachineString(hAppKey,lpszSection,lpszEntry,lpszDefault);
}

CString CEAFApp::GetLocalMachineString(HKEY hAppKey,LPCTSTR lpszSection, LPCTSTR lpszEntry,LPCTSTR lpszDefault)
{
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(m_pszRegistryKey != NULL);
	HKEY hSecKey = GetLocalMachineSectionKey(hAppKey,lpszSection);
	if (hSecKey == NULL)
		return lpszDefault;
	CString strValue;
	DWORD dwType, dwCount;
	LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
		NULL, &dwCount);
	if (lResult == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_SZ);
		lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
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
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
   HKEY hWinKey = NULL;
   HKEY hCVKey = NULL;
   HKEY hUninstallKey = NULL;


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

	if (hSoftKey != NULL)
		RegCloseKey(hSoftKey);
	
   if (hCompanyKey != NULL)
		RegCloseKey(hCompanyKey);
	
   if (hWinKey != NULL)
		RegCloseKey(hWinKey);
	
   if (hCVKey != NULL)
		RegCloseKey(hCVKey);

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

////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CEAFPluginApp, CEAFApp)

BOOL CEAFPluginApp::InitInstance()
{
   if ( !CEAFApp::InitInstance() )
      return FALSE;

   // The installer should do this, but just in case it doesn't we'll do it here
   sysComCatMgr::CreateCategory(GetAppPluginCategoryName(),GetAppPluginCategoryID());

   return TRUE;
}

BOOL CEAFPluginApp::CreateApplicationPlugins()
{
   // Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
   if ( !GetAppPluginManager()->LoadPlugins(GetAppPluginCategoryID()) )
      return FALSE;

   return TRUE;
}
