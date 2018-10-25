// EAFApp.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "resource.h"
#include <EAF\EAFApp.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFAboutDlg.h>
#include <EAF\EAFPluginManager.h>
#include <EAF\EAFSplashScreen.h>
#include <System\ComCatMgr.h>

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
   im.SpanLength.Update(      unitMeasure::Meter,                     0.001, 8, 2, sysNumericFormatTool::Fixed );
   im.AlignmentLength.Update( unitMeasure::Meter,                     0.001,16, 4, sysNumericFormatTool::Fixed );
   im.Displacement.Update(    unitMeasure::Millimeter,                0.001, 8, 1, sysNumericFormatTool::Fixed );
   im.Area.Update(            unitMeasure::Millimeter2,               0.001, 8, 0, sysNumericFormatTool::Fixed );
   im.MomentOfInertia.Update( unitMeasure::Millimeter4,               0.001, 7, 0, sysNumericFormatTool::Engineering );
   im.SectModulus.Update(     unitMeasure::Millimeter3,               0.001, 7, 0, sysNumericFormatTool::Engineering );
   im.AvOverS.Update(         unitMeasure::Millimeter2PerMeter,      1.0e-6, 9, 3, sysNumericFormatTool::Fixed );
   im.Stress.Update(          unitMeasure::MPa,                       0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.ModE.Update(            unitMeasure::MPa,                       0.001,12, 0, sysNumericFormatTool::Fixed );
   im.GeneralForce.Update(    unitMeasure::Kilonewton,                0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Shear.Update(           unitMeasure::Kilonewton,                0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Moment.Update(          unitMeasure::KilonewtonMeter,           0.001, 9, 2, sysNumericFormatTool::Fixed );
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
   im.SmallStress.Update(          unitMeasure::MPa,                       0.001, 9, 2, sysNumericFormatTool::Fixed );

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
   im.Shear.Update(           unitMeasure::Kip,             0.001, 9, 2, sysNumericFormatTool::Fixed );
   im.Moment.Update(          unitMeasure::KipFeet,         0.001, 9, 2, sysNumericFormatTool::Fixed );
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
   im.SmallStress.Update(          unitMeasure::KSF,             0.001, 8, 3, sysNumericFormatTool::Fixed );

   return im;
}

/////////////////////////////////////////////////////////////////////////////
// CEAFApp

IMPLEMENT_DYNAMIC(CEAFApp, CWinApp)

CEAFApp::CEAFApp()
{
   m_pDocTemplateRegistrar = new CEAFDocTemplateRegistrar;
}

CEAFApp::~CEAFApp()
{
}

BOOL CEAFApp::InitInstance()
{
   //::CoInitialize(0);
   ::OleInitialize(NULL); // need to use OleInitialize otherwise OLE drag and drop doesn't work

   InitDisplayUnits();
   
   CEAFSplashScreen::SetSplashScreenInfo(GetSplashScreenInfo());
   CEAFSplashScreen::EnableSplashScreen();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

   sysComCatMgr::CreateCategory(GetPluginCategoryName(),GetPluginCategoryID());

   AfxEnableControlContainer(); // for CEAFReportView / IE Web Browser plug-in

   // Change the registry key under which our settings are stored.
	SetRegistryKey(GetRegistryKey());

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)


	// create main MDI Frame window
	CEAFMainFrame* pMainFrame = new CEAFMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;


   // Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
   if ( !m_PluginManager.LoadPlugins(GetPluginCategoryID()) )
      return FALSE;

   RegisterDocTemplates();

   // Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

   // Don't display a new window on startup
   // Q141725
   if ( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew )
      cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

   // files can be opened with drag and drop
   pMainFrame->DragAcceptFiles(TRUE);

   // user can Float64 click on a file to open
   EnableShellOpen();

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

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

   if ( m_pDocTemplateRegistrar )
      delete m_pDocTemplateRegistrar;

   ::CoUninitialize();

   return result;

}

BEGIN_MESSAGE_MAP(CEAFApp, CWinApp)
	//{{AFX_MSG_MAP(CEAFApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
   ON_COMMAND(ID_APP_ABOUT, &CEAFApp::OnAppAbout)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFApp message handlers
void CEAFApp::RegisterDocTemplates()
{
   m_PluginManager.RegisterDocTemplates(this);
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

CDocument* CEAFApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
   CDocument* pDoc = NULL;
   // The current project must be closed before opening the new one
   if (m_pDocManager && m_pDocManager->SaveAllModified())
   {
      m_pDocManager->CloseAllDocuments(FALSE);
      pDoc = CWinApp::OpenDocumentFile(lpszFileName);
   }
   return pDoc;

   // This is the implementation from PGSuper whereby you can open a file or a template to create a new file
   // EAF isn't quite ready for this...

 //  CDocument* pdoc = 0;

 //  // Check to make sure that file is a .pgs or .pgt 
 //  CString file_ext;
 //  CString file_name(lpszFileName);
	//int pos = file_name.ReverseFind('.');
	//if (pos >= 0)
	//	file_ext = file_name.Right(file_name.GetLength() - pos - 1);

 //  if (file_ext.CompareNoCase("pgs")==0 || file_ext.CompareNoCase("pgt")==0 )
 //  {
 //     // The current project must be closed before opening the new one
 //     if (m_pDocManager && m_pDocManager->SaveAllModified())
 //     {
 //        m_pDocManager->CloseAllDocuments(FALSE);
 //        pdoc = CWinApp::OpenDocumentFile(lpszFileName);
 //     }
 //  }
 //  else
 //  {
 //     ::AfxMessageBox("Error Invalid File Type - Valid PGSuper files must have either a .PGS or .PGT extension.",MB_ICONEXCLAMATION|MB_OK);
 //  }

 //  CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
 //  ASSERT( pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)) );
 //  pMainFrame->UpdateStatusBar();

 //  // for template files, we need to rename the file to Untitled
 //  if (pdoc!=0 && file_ext.CompareNoCase("pgt")==0 )
 //  {
 //     pdoc->SetPathName("Untitled",FALSE);
 //     pdoc->SetModifiedFlag(TRUE);
 //     pMainFrame->UpdateFrameTitle("Untitled");
 //  }

 //  return pdoc;
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

CEAFPluginManager* CEAFApp::GetPluginManager()
{
   return &m_PluginManager;
}

void CEAFApp::InitDisplayUnits()
{
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
      //Fire_UnitsChanged( m_Units );
   }
}

void CEAFApp::OnAppAbout()
{
   OnAbout();
}

void CEAFApp::OnAbout()
{
   AfxMessageBox("Over-ride CEAFApp::OnAbout to provide an about dialog");
}

BOOL CEAFApp::PreTranslateMessage(MSG* pMsg)
{
   if ( CEAFSplashScreen::PreTranslateAppMessage(pMsg) )
      return TRUE;

   return CWinApp::PreTranslateMessage(pMsg);
}
