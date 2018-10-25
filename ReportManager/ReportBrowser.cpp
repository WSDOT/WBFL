///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
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

// ReportBrowser.cpp: implementation of the CReportBrowser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\ReportBrowser.h>
#include <ReportManager\ReportBuilder.h>
#include <ReportManager\ReportBuilderManager.h>
#include "WebBrowser.h"
#include "WBCmdGroup.h" // magical cmd_ids for find

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void to_upper( std::string::iterator begin,std::string::iterator end)
{
   while ( begin != end )
   {
      *begin = toupper(*begin);
      begin++;
   }
}

std::string filename_to_URL(const std::string& fname)
{
   //turn into an internet-looking url
   std::string filename(fname);
   int pos;
   while((pos=filename.find("\\")) != std::string::npos)
      filename.replace(pos,1,"/");

   filename = "file://" + filename;
   return filename;
}

class TweakIESettings
{
public:
   TweakIESettings();
   ~TweakIESettings();
private:
   CString m_strPrint, m_strFooter, m_strHeader;
   bool m_bDeletePrint;
   bool m_bDeleteFooter;
   bool m_bDeleteHeader;
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportBrowser::CReportBrowser()
{
   m_pTweakIESettings = new TweakIESettings;
   m_pWebBrowser = new CWebBrowser;
}

CReportBrowser::~CReportBrowser()
{
   // We are done with our HTML file... Delete it
   if (!m_Filename.empty())
      ::DeleteFile( m_Filename.c_str() );

   if ( m_pTweakIESettings )
      delete m_pTweakIESettings;

   if ( m_pWebBrowser )
      delete m_pWebBrowser;
}

void CReportBrowser::UpdateReport(boost::shared_ptr<rptReport>& pReport,bool bRefresh)
{
   std::ofstream ofile( m_Filename.c_str() );
   ATLASSERT( ofile.is_open() == true );

   Uint32 logPixX;
   Uint32 logPixY;
   CDC dc;
   dc.CreateDC(CString("DISPLAY"),NULL,NULL,NULL);
   logPixX = dc.GetDeviceCaps(LOGPIXELSX);
   logPixY = dc.GetDeviceCaps(LOGPIXELSY);

   rptHtmlReportVisitor visitor( &ofile, logPixX, logPixY );
   visitor.VisitReport( pReport.get() );

   if (bRefresh)
      m_pWebBrowser->Refresh();
}

bool CReportBrowser::Initialize(HWND hwnd,CReportBuilderManager* pRptMgr,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<rptReport>& pReport)
{
   // Did you forget something?  This method needs a pointer to a rptReport
   ATLASSERT( pReport != 0 );

   m_pRptMgr = pRptMgr;
   m_pRptSpec = pRptSpec;

   // The window associated with hwnd does not exist!
   ATLASSERT( ::IsWindow(hwnd) );

   // use empty file name as flag that browser has not yet been initialized.
   bool new_file = m_Filename.empty();
   if (new_file)
   {
      MakeFilename();

      CRect rect(0,0,0,0);
      CWnd* pParent = CWnd::FromHandle( hwnd );
      BOOL bCreated = m_pWebBrowser->Create(TEXT("Microsoft Web Browser Control"),
                                            TEXT("Browser Control"),
                                            WS_CHILD | WS_VISIBLE, rect, pParent, 100);
      if ( !bCreated )
      {
         TRACE( TEXT("Failed to create browser") );
         return false;
      }
   }

   UpdateReport(pReport,false);

   if (new_file)
      m_pWebBrowser->Navigate( TEXT(m_Filename.c_str()), 0,0,0,0);
   else
      m_pWebBrowser->Refresh();

   return true;
}

boost::shared_ptr<CReportSpecification> CReportBrowser::GetReportSpecification()
{
   return m_pRptSpec;
}

boost::shared_ptr<rptReport> CReportBrowser::GetReport()
{
   return m_pReport;
}

std::string CReportBrowser::GetReportTitle()
{
   return m_pRptSpec->GetReportTitle();
}

void CReportBrowser::Move(POINT topLeft)
{
   m_pWebBrowser->SetWindowPos(NULL,topLeft.x,topLeft.y,0,0,SWP_NOZORDER | SWP_NOSIZE);
}

void CReportBrowser::Size(SIZE size)
{
   m_pWebBrowser->SetWindowPos(NULL,0,0,size.cx,size.cy,SWP_NOZORDER | SWP_NOMOVE);
}

void CReportBrowser::Print(bool bPrompt)
{
   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if ( S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget ) )
   {
      pIOleCmdTarget->Exec(NULL,OLECMDID_PRINT, bPrompt ? OLECMDEXECOPT_PROMPTUSER : OLECMDEXECOPT_DONTPROMPTUSER, NULL,NULL);
      pIOleCmdTarget->Release();
   }
}

void CReportBrowser::Edit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   boost::shared_ptr<CReportBuilder> pRptBuilder = m_pRptMgr->GetReportBuilder(m_pRptSpec->GetReportName());
   CReportDescription rptDesc = pRptBuilder->GetReportDescription();

   boost::shared_ptr<CReportSpecificationBuilder> pReportSpecBuilder = pRptBuilder->GetReportSpecificationBuilder();
   boost::shared_ptr<CReportSpecification>        pReportSpec        = pReportSpecBuilder->CreateReportSpec(rptDesc,m_pRptSpec);
   
   // user cancelled.
   if( pReportSpec == NULL )
      return;

   m_pRptSpec = pReportSpec;
   boost::shared_ptr<rptReport> pReport = pRptBuilder->CreateReport( m_pRptSpec );

   UpdateReport(pReport,true);
}

void CReportBrowser::Find()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if ( S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget ) )
   {
      pIOleCmdTarget->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_FIND, 0, NULL,NULL);
      pIOleCmdTarget->Release();
   }
}

void CReportBrowser::SelectAll()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if ( S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget ) )
   {
      pIOleCmdTarget->Exec(NULL,OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, NULL,NULL);
      pIOleCmdTarget->Release();
   }
}

void CReportBrowser::ViewSource()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   LPDISPATCH lpDispatch = m_pWebBrowser->GetDocument();
   IOleCommandTarget* pIOleCmdTarget;
   if ( S_OK == lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&pIOleCmdTarget ) )
   {
      pIOleCmdTarget->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_VIEWSOURCE, 0, NULL,NULL);
      pIOleCmdTarget->Release();
   }
}

void CReportBrowser::Refresh()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_pWebBrowser->Refresh();
}


void CReportBrowser::Back()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_pWebBrowser->GoBack();
}

void CReportBrowser::Forward()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_pWebBrowser->GoForward();
}

void CReportBrowser::NavigateAnchor(long id)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   std::string filename = filename_to_URL(m_Filename);
   CString anc;
   anc.Format("%s#_%d",filename.c_str(),id);
   m_pWebBrowser->Navigate(anc,0,0,0,0);
}


void CReportBrowser::MakeFilename()
{
   char temp_path[ _MAX_PATH ];
   char temp_file[ _MAX_PATH ];
   bool should_delete = true;

   if ( ::GetTempPath( _MAX_PATH, temp_path ) == 0 )
      strcpy_s(temp_path,_MAX_PATH,"C:\\"); // Couldn't establish a temp path, just use the root drive.

   //
   // Make sure the temp path actually exists
   // We do this by looking for any file in the directory.  If nothing shows up, then the
   // path doesn't exist. (Well, this isn't exactly true, but its the best I can come up
   // with).
   CFileFind finder;
   BOOL bExist;
   CString path(temp_path);
   if ( path[path.GetLength()-1] != '\\' )
      path += "\\";
   path += "*.*";
   bExist = finder.FindFile(path);
   if ( !bExist )
      strcpy_s( temp_path,_MAX_PATH, "C:\\" );

   // This creates a file called "temp_file".TMP
   if ( ::GetTempFileName( temp_path, "tmp", 0, temp_file ) == 0 )
   {
      // We could not get a temp name, so just use this default
      // (Use a tmp extension so it is in the same format as the one
      //  the OS would have created for us)
      strcpy_s( temp_file, _MAX_PATH, "wbfl_report.tmp" );
      should_delete = false;
   }

   // Replace the TMP extension with HTM
   m_Filename.assign( temp_file );
   m_Filename.replace( m_Filename.end() - 3, m_Filename.end(), "HTM" );

   // We don't want the file Windows created for us
   if ( should_delete )
      ::DeleteFile( temp_file );

   to_upper( m_Filename.begin(), m_Filename.end() );
}


TweakIESettings::TweakIESettings()
{
   CRegKey hkSoftware, hkMicrosoft, hkIE, hkMain, hkPageSetup;
   LONG result = hkSoftware.Open(HKEY_CURRENT_USER,"Software");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkMicrosoft.Open(hkSoftware,"Microsoft");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkIE.Open(hkMicrosoft,"Internet Explorer");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkMain.Open(hkIE,"Main");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkPageSetup.Open(hkIE,"PageSetup");
   ATLASSERT(result == ERROR_SUCCESS);

   char strPrint[10];
   DWORD dwCount = 10;
   result = hkMain.QueryStringValue("Print_Background",strPrint,&dwCount);
   bool bDeletePrint = (result != ERROR_SUCCESS);

   char strFooter[256];
   dwCount = 256;
   result = hkPageSetup.QueryStringValue("footer",strFooter,&dwCount);
   bool bDeleteFooter = (result != ERROR_SUCCESS);

   char strHeader[256];
   dwCount = 256;
   result = hkPageSetup.QueryStringValue("header",strHeader,&dwCount);
   bool bDeleteHeader = (result != ERROR_SUCCESS);

   result = hkMain.SetStringValue("Print_Background","yes");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkPageSetup.SetStringValue("footer","&b&b&d");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkPageSetup.SetStringValue("header","&w&bPage &p of &P");
   ATLASSERT(result == ERROR_SUCCESS);

   m_bDeletePrint  = bDeletePrint;
   m_bDeleteFooter = bDeleteFooter;
   m_bDeleteHeader = bDeleteHeader;

   m_strPrint  = strPrint;
   m_strFooter = strFooter;
   m_strHeader = strHeader;
}

TweakIESettings::~TweakIESettings()
{
   CRegKey hkSoftware, hkMicrosoft, hkIE, hkMain, hkPageSetup;
   LONG result = hkSoftware.Open(HKEY_CURRENT_USER,"Software");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkMicrosoft.Open(hkSoftware,"Microsoft");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkIE.Open(hkMicrosoft,"Internet Explorer");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkMain.Open(hkIE,"Main");
   ATLASSERT(result == ERROR_SUCCESS);

   result = hkPageSetup.Open(hkIE,"PageSetup");
   ATLASSERT(result == ERROR_SUCCESS);

   if ( m_bDeletePrint )
      result = hkMain.DeleteValue("Print_Background");
   else
      result = hkMain.SetStringValue("Print_Background",m_strPrint);

   ATLASSERT(result == ERROR_SUCCESS);

   if ( m_bDeleteFooter )
      result = hkPageSetup.DeleteValue("footer");
   else
      result = hkPageSetup.SetStringValue("footer",m_strFooter);

   ATLASSERT(result == ERROR_SUCCESS);

   if ( m_bDeleteHeader )
      result = hkPageSetup.DeleteValue("header");
   else
      result = hkPageSetup.SetStringValue("header",m_strHeader);

   ATLASSERT(result == ERROR_SUCCESS);
}
