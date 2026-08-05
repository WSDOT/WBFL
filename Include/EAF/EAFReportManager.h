///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <ReportManager/ReportBuilder.h>
#include <ReportManager/ReportBrowser.h>

// {61C524E8-7D77-4345-8954-B53539516BEB}
DEFINE_GUID(IID_IEAFReportManager,
   0x61c524e8, 0x7d77, 0x4345, 0x89, 0x54, 0xb5, 0x35, 0x39, 0x51, 0x6b, 0xeb);
/// @brief Registry of the application's reports. An extension agent uses this to add a brand new
/// report, or to look up one of the host's existing reports and modify its chapters (see
/// WBFL::ReportMgr::ReportBuilder::InsertChapterBuilder/RemoveChapterBuilder).
class IEAFReportManager
{
public:
   /// @brief Adds a new report to the application. pReportBuilder is moved-from/emptied by this call.
   virtual void AddReportBuilder(std::shared_ptr<WBFL::ReportMgr::ReportBuilder>&pReportBuilder) = 0;

   /// @brief Number of registered reports
   virtual IndexType GetReportBuilderCount(bool bIncludeHidden = false) const = 0;

   /// @brief Looks up a registered report by name - including reports registered by other
   /// agents/extension agents. Use WBFL::ReportMgr::ReportBuilder::InsertChapterBuilder or
   /// RemoveChapterBuilder on the result to add or remove chapters from an existing report.
   virtual std::shared_ptr<WBFL::ReportMgr::ReportBuilder> GetReportBuilder(LPCTSTR strReportName) = 0;
   /// @copydoc IEAFReportManager::GetReportBuilder(LPCTSTR)
   virtual std::shared_ptr<WBFL::ReportMgr::ReportBuilder> GetReportBuilder(const std::_tstring& strReportName) = 0;

   /// @brief Unregisters and returns a report by name
   virtual std::shared_ptr<WBFL::ReportMgr::ReportBuilder> RemoveReportBuilder(LPCTSTR strReportName) = 0;
   /// @copydoc IEAFReportManager::RemoveReportBuilder(LPCTSTR)
   virtual std::shared_ptr<WBFL::ReportMgr::ReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName) = 0;

   /// @brief Names of all registered reports
   virtual std::vector<std::_tstring> GetReportNames(bool bIncludeHidden = false) const = 0;
   virtual WBFL::ReportMgr::ReportDescription GetReportDescription(LPCTSTR strReportName) = 0;
   virtual WBFL::ReportMgr::ReportDescription GetReportDescription(const std::_tstring& strReportName) = 0;
   virtual const CBitmap* GetMenuBitmap(LPCTSTR strReportName) = 0;
   virtual const CBitmap* GetMenuBitmap(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<WBFL::ReportMgr::ReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName) = 0;
   virtual std::shared_ptr<WBFL::ReportMgr::ReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<WBFL::ReportMgr::ReportSpecificationBuilder> GetReportSpecificationBuilder(const WBFL::ReportMgr::ReportDescription& rptDesc) = 0;
   virtual void SetReportBrowserType(WBFL::ReportMgr::ReportBrowser::Type browserType) = 0;
   virtual WBFL::ReportMgr::ReportBrowser::Type GetReportBrowserType() const = 0;
   virtual std::shared_ptr<WBFL::ReportMgr::ReportBrowser> CreateReportBrowser(HWND hwndParent, DWORD dwStyle,const std::shared_ptr<WBFL::ReportMgr::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::ReportMgr::ReportSpecificationBuilder>& pRptSpecBuilder) = 0;
   virtual INT_PTR DisplayReportDialog(DWORD flags, const std::shared_ptr<WBFL::ReportMgr::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::ReportMgr::ReportSpecificationBuilder>& pRptSpecBuilder) = 0;
};
