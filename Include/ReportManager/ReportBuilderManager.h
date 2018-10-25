///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2011  Washington State Department of Transportation
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

#pragma once

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
   boost::shared_ptr<CReportBuilder> GetReportBuilder(LPCTSTR strReportName);
   boost::shared_ptr<CReportBuilder> GetReportBuilder(const std::_tstring& strReportName);
   boost::shared_ptr<CReportBuilder> RemoveReportBuilder(LPCTSTR strReportName);
   boost::shared_ptr<CReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName);
   std::vector<std::_tstring> GetReportNames(bool bIncludeHidden = false) const;
   CReportDescription GetReportDescription(LPCTSTR strReportName);
   CReportDescription GetReportDescription(const std::_tstring& strReportName);
   const CBitmap* GetMenuBitmap(LPCTSTR strReportName);
   const CBitmap* GetMenuBitmap(const std::_tstring& strReportName);
   boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName);
   boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName);
   boost::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const CReportDescription& rptDesc);
   boost::shared_ptr<CReportBrowser> CreateReportBrowser(HWND hwndParent,boost::shared_ptr<CReportSpecification>& pRptSpec);
   Int16 DisplayReportDialog(DWORD flags,boost::shared_ptr<CReportSpecification>& pRptSpec);

private:
   typedef std::map<std::_tstring, boost::shared_ptr<CReportBuilder> > RptBuilderContainer;
   typedef std::pair<std::_tstring, boost::shared_ptr<CReportBuilder> > RptBuilderEntry;
   RptBuilderContainer m_RptBuilders;

   boost::shared_ptr<rptReport> CreateReport(boost::shared_ptr<CReportSpecification>& pRptSpec);
};
