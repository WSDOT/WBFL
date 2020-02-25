///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2020  Washington State Department of Transportation
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

// ReportBrowser.h: interface for the CReportBrowser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTBROWSER_H__461AB263_1A55_405D_BE56_9E516F285506__INCLUDED_)
#define AFX_REPORTBROWSER_H__461AB263_1A55_405D_BE56_9E516F285506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportSpecificationBuilder.h>
#include <Reporter\Reporter.h>


class rptReport;
class CWebBrowser;
class TweakIESettings;
class CReportBuilderManager;

class REPORTMANAGERCLASS CReportBrowser  
{
public:
	CReportBrowser();
	virtual ~CReportBrowser();

   void UpdateReport(std::shared_ptr<rptReport>& pReport,bool bRefresh);
   bool Initialize(HWND hwnd,CReportBuilderManager* pRptMgr, std::shared_ptr<CReportSpecification>& pRptSpec, std::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder, std::shared_ptr<rptReport>& pReport);
   std::shared_ptr<CReportSpecification> GetReportSpecification();
   std::shared_ptr<rptReport> GetReport();
   std::_tstring GetReportTitle();
   void Move(POINT topLeft);
   void Size(SIZE size);
   void Print(bool bPrompt);
   bool Edit(bool bUpdate = true); // returns false if the user cancelled the edit
   void Find();
   void SelectAll();
   void Refresh();
   void ViewSource();
   void Back();
   void Forward();
   void NavigateAnchor(long id);

   CWnd* GetBrowserWnd();

private:
   CWebBrowser* m_pWebBrowser;
   std::_tstring m_Filename;
   std::shared_ptr<CReportSpecification> m_pRptSpec;
   std::shared_ptr<CReportSpecificationBuilder> m_pRptSpecBuilder;
   std::shared_ptr<rptReport> m_pReport;
   CReportBuilderManager* m_pRptMgr;

   void MakeFilename();

};

#endif // !defined(AFX_REPORTBROWSER_H__461AB263_1A55_405D_BE56_9E516F285506__INCLUDED_)
