///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
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

#pragma once

#include <ReportManager\ReportManager.h>


// {61C524E8-7D77-4345-8954-B53539516BEB}
DEFINE_GUID(IID_IReportManager, 
0x61c524e8, 0x7d77, 0x4345, 0x89, 0x54, 0xb5, 0x35, 0x39, 0x51, 0x6b, 0xeb);
interface IReportManager : IUnknown
{
   virtual void AddReportBuilder(std::shared_ptr<WBFL::Reporting::ReportBuilder>& pReportBuilder) = 0;
   virtual IndexType GetReportBuilderCount(bool bIncludeHidden = false) const = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> GetReportBuilder(LPCTSTR strReportName) = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> GetReportBuilder(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> RemoveReportBuilder(LPCTSTR strReportName) = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName) = 0;
   virtual std::vector<std::_tstring> GetReportNames(bool bIncludeHidden = false) const = 0;
   virtual WBFL::Reporting::ReportDescription GetReportDescription(LPCTSTR strReportName) = 0;
   virtual WBFL::Reporting::ReportDescription GetReportDescription(const std::_tstring& strReportName) = 0;
   virtual const CBitmap* GetMenuBitmap(LPCTSTR strReportName) = 0;
   virtual const CBitmap* GetMenuBitmap(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName) = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportSpecificationBuilder> GetReportSpecificationBuilder(const WBFL::Reporting::ReportDescription& rptDesc) = 0;
   virtual void SetReportBrowserType(WBFL::Reporting::ReportBrowser::Type browserType) = 0;
   virtual std::shared_ptr<WBFL::Reporting::ReportBrowser> CreateReportBrowser(HWND hwndParent, DWORD dwStyle,const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder) = 0;
   virtual INT_PTR DisplayReportDialog(DWORD flags, const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder) = 0;
};
