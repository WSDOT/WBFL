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

// ReportBuilderManager.h: interface for the CReportBuilderManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTBUILDERMANAGER_H__5723C896_5744_4C31_8992_6BFCD03EEECC__INCLUDED_)
#define AFX_REPORTBUILDERMANAGER_H__5723C896_5744_4C31_8992_6BFCD03EEECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportBuilder.h>
#include <ReportManager\ReportBrowser.h>
#include <boost\shared_ptr.hpp>
#include <map>

class rptReport;

class REPORTMANAGERCLASS CReportBuilderManager  
{
public:
	CReportBuilderManager();
	virtual ~CReportBuilderManager();
   virtual void ClearAll();  // deletes all report builders

   void AddReportBuilder(CReportBuilder* pRptBuilder);
   void AddReportBuilder(boost::shared_ptr<CReportBuilder>& pRptBuilder);
   Uint32 GetReportBuilderCount(bool bIncludeHidden = false) const;
   boost::shared_ptr<CReportBuilder> GetReportBuilder(const char* strReportName);
   boost::shared_ptr<CReportBuilder> GetReportBuilder(const std::string& strReportName);
   boost::shared_ptr<CReportBuilder> RemoveReportBuilder(const char* strReportName);
   boost::shared_ptr<CReportBuilder> RemoveReportBuilder(const std::string& strReportName);
   std::vector<std::string> GetReportNames(bool bIncludeHidden = false) const;
   CReportDescription GetReportDescription(const char* strReportName);
   CReportDescription GetReportDescription(const std::string& strReportName);
   boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const char* strReportName);
   boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const std::string& strReportName);
   boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const CReportDescription& rptDesc);
   boost::shared_ptr<CReportBrowser> CreateReportBrowser(HWND hwndParent,boost::shared_ptr<CReportSpecification>& pRptSpec);
   Int16 DisplayReportDialog(DWORD flags,boost::shared_ptr<CReportSpecification>& pRptSpec);

private:
   typedef std::map<std::string, boost::shared_ptr<CReportBuilder> > RptBuilderContainer;
   typedef std::pair<std::string, boost::shared_ptr<CReportBuilder> > RptBuilderEntry;
   RptBuilderContainer m_RptBuilders;

   boost::shared_ptr<rptReport> CreateReport(boost::shared_ptr<CReportSpecification>& pRptSpec);
};

#endif // !defined(AFX_REPORTBUILDERMANAGER_H__5723C896_5744_4C31_8992_6BFCD03EEECC__INCLUDED_)
