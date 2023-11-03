///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include "resource.h"
#include "ReportManager.h"
#include <ReportManager\ReportBrowser.h>
#include <ReportManager\ReportBuilder.h>
#include <ReportManager\ReportBuilderManager.h>

#include "IEReportView.h"
#include "EdgeReportView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace WBFL::Reporting;

void to_upper( std::_tstring::iterator begin,std::_tstring::iterator end)
{
   while ( begin != end )
   {
      *begin = toupper(*begin);
      begin++;
   }
}

std::_tstring filename_to_URL(const std::_tstring& fname)
{
   //turn into an internet-looking url
   std::_tstring filename(fname);
   IndexType pos;
   while((pos=filename.find( _T("\\") )) != std::_tstring::npos)
      filename.replace(pos,1,_T("/"));

   filename = _T("file://") + filename;
   return filename;
}

ReportBrowser::ReportBrowser(Type type)
{
   if (type == Type::IE)
      m_pReportView = std::make_unique<IEReportView>();
   else if (type == Type::Edge)
      m_pReportView = std::make_unique<EdgeReportView>();
   else
      CHECK(false); // is there a new type?
}

ReportBrowser::~ReportBrowser()
{
   // We are done with our HTML file... Delete it
   if (!m_Filename.empty())
   {
      ::DeleteFile( m_Filename.c_str() );
   }
}

void ReportBrowser::UpdateReport(std::shared_ptr<rptReport>& pReport,bool bRefresh)
{
   std::_tofstream ofile( m_Filename.c_str() );
   ATLASSERT( ofile.is_open() == true );

   Uint32 logPixX;
   Uint32 logPixY;
   CDC dc;
   dc.CreateDC(CString("DISPLAY"),nullptr,nullptr,nullptr);
   logPixX = dc.GetDeviceCaps(LOGPIXELSX);
   logPixY = dc.GetDeviceCaps(LOGPIXELSY);

   rptHtmlReportVisitor visitor( &ofile, logPixX, logPixY );
   visitor.VisitReport( pReport.get() );

   if (bRefresh)
   {
      Refresh();
   }
}

bool ReportBrowser::Initialize(HWND hwnd, DWORD dwStyle, const std::shared_ptr<const ReportBuilderManager>& pRptMgr, const std::shared_ptr<ReportSpecification>& pRptSpec, const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder, std::shared_ptr<rptReport>& pReport)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   // Did you forget something?  This method needs a pointer to a rptReport
   ATLASSERT( pReport != nullptr );

   m_pRptMgr = pRptMgr;
   m_pRptSpec = pRptSpec;
   m_pRptSpecBuilder = pRptSpecBuilder;

   // The window associated with hwnd does not exist!
   CHECK( ::IsWindow(hwnd) );

   // use empty file name as flag that browser has not yet been initialized.
   bool bIsNewFile = m_Filename.empty();
   if (bIsNewFile)
   {
      MakeFilename();

      CRect rect(0,0,0,0);
      BOOL bCreated = m_pReportView->Create(TEXT("Browser Control"),
                                            WS_CHILD | WS_VISIBLE | dwStyle, rect, hwnd, IDC_REPORT_WEB_BROWSER);
      if ( !bCreated )
      {
         TRACE( TEXT("Failed to create browser") );
         return false;
      }
   }

   UpdateReport(pReport,false);

   if (bIsNewFile)
   {
      Navigate( m_Filename.c_str());
   }
   else
   {
      Refresh();
   }

   return true;
}

std::shared_ptr<ReportSpecification> ReportBrowser::GetReportSpecification()
{
   return m_pRptSpec;
}

std::shared_ptr<rptReport> ReportBrowser::GetReport()
{
   return m_pReport;
}

std::_tstring ReportBrowser::GetReportTitle()
{
   return m_pRptSpec->GetReportTitle();
}

void ReportBrowser::FitToParent()
{
   m_pReportView->FitToParent();
}

void ReportBrowser::Move(POINT topLeft)
{
   m_pReportView->Move(topLeft);
}

void ReportBrowser::Size(SIZE size)
{
   m_pReportView->Size(size);
}

void ReportBrowser::Print(bool bPrompt)
{
   m_pReportView->Print(bPrompt);
}

bool ReportBrowser::Edit(bool bUpdate)
{
   auto pRptBuilder = m_pRptMgr->GetReportBuilder(m_pRptSpec->GetReportName());
   ReportDescription rptDesc = pRptBuilder->GetReportDescription();

   std::shared_ptr<const ReportSpecificationBuilder> pReportSpecBuilder(m_pRptSpecBuilder);
   if ( m_pRptSpecBuilder == nullptr )
   {
      pReportSpecBuilder = pRptBuilder->GetReportSpecificationBuilder();
   }

   auto pReportSpec = pReportSpecBuilder->CreateReportSpec(rptDesc,m_pRptSpec);
   
   // user cancelled.
   if( pReportSpec == nullptr )
   {
      return false;
   }

   m_pRptSpec = pReportSpec;

   if ( bUpdate )
   {
      std::shared_ptr<rptReport> pReport = pRptBuilder->CreateReport( m_pRptSpec );
      UpdateReport(pReport,true);
   }

   return true;
}

void ReportBrowser::Find()
{
   m_pReportView->Find();
}

void ReportBrowser::SelectAll()
{
   m_pReportView->SelectAll();
}

void ReportBrowser::Copy()
{
   m_pReportView->Copy();
}

void ReportBrowser::ViewSource()
{
   m_pReportView->ViewSource();
}

void ReportBrowser::Refresh()
{
   m_pReportView->Refresh();
}

void ReportBrowser::Back()
{
   m_pReportView->Back();
}

void ReportBrowser::Forward()
{
   m_pReportView->Forward();
}

void ReportBrowser::NavigateAnchor(long id)
{
   std::_tstring filename = filename_to_URL(m_Filename);
   CString anc;
   anc.Format(_T("%s#_%d"),filename.c_str(),id);
   Navigate(anc);
}

void ReportBrowser::Navigate(LPCTSTR uri)
{
   m_pReportView->Navigate(uri);
}

void ReportBrowser::MakeFilename()
{
   TCHAR temp_path[ _MAX_PATH ];
   TCHAR temp_file[ _MAX_PATH ];
   bool should_delete = true;

   if ( ::GetTempPath( _MAX_PATH, temp_path ) == 0 )
      _tcscpy_s(temp_path,_MAX_PATH,_T("C:\\")); // Couldn't establish a temp path, just use the root drive.

   //
   // Make sure the temp path actually exists
   // We do this by looking for any file in the directory.  If nothing shows up, then the
   // path doesn't exist. (Well, this isn't exactly true, but its the best I can come up
   // with).
   CFileFind finder;
   BOOL bExist;
   CString path(temp_path);
   if ( path[path.GetLength()-1] != _T('\\') )
      path += _T("\\");

   path += _T("*.*");

   bExist = finder.FindFile(path);
   if ( !bExist )
      _tcscpy_s( temp_path,_MAX_PATH, _T("C:\\") );

   // This creates a file called "temp_file".TMP
   if ( ::GetTempFileName( temp_path, _T("tmp"), 0, temp_file ) == 0 )
   {
      // We could not get a temp name, so just use this default
      // (Use a tmp extension so it is in the same format as the one
      //  the OS would have created for us)
      _tcscpy_s( temp_file, _MAX_PATH, _T("wbfl_report.tmp") );
      should_delete = false;
   }

   // Replace the TMP extension with HTM
   m_Filename.assign( temp_file );
   m_Filename.replace( m_Filename.end() - 3, m_Filename.end(), _T("HTM") );

   // We don't want the file Windows created for us
   if ( should_delete )
      ::DeleteFile( temp_file );

   to_upper( m_Filename.begin(), m_Filename.end() );
}
