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

#pragma once

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportBuilder.h>
#include <ReportManager\ReportBrowser.h>

#include <map>

class rptReport;

namespace WBFL
{
   namespace Reporting
   {
      /// Managers of all the report builders
      class REPORTMANAGERCLASS ReportBuilderManager : public std::enable_shared_from_this<ReportBuilderManager>
      {
      public:
         /// Factory method to create a ReportBuilderManager.
         /// The report builder manager must be a shared pointer, this method ensures proper creation.
         [[nodiscard]] static std::shared_ptr<ReportBuilderManager> Create();
	      ~ReportBuilderManager() = default;

         /// Removes all report builders
         void ClearAll();

         /// Adds a report builder
         void AddReportBuilder(std::shared_ptr<ReportBuilder>& pRptBuilder);

         /// Returns the number of report builders
         IndexType GetReportBuilderCount(
            bool bIncludeHidden = false ///< If true, the count includes hidden report builders
         ) const;

         /// Returns a report builder
         std::shared_ptr<ReportBuilder> GetReportBuilder(LPCTSTR strReportName);
         std::shared_ptr<ReportBuilder> GetReportBuilder(const std::_tstring& strReportName);
         std::shared_ptr<const ReportBuilder> GetReportBuilder(LPCTSTR strReportName) const;
         std::shared_ptr<const ReportBuilder> GetReportBuilder(const std::_tstring& strReportName) const;

         /// Removes a report builder
         std::shared_ptr<ReportBuilder> RemoveReportBuilder(LPCTSTR strReportName);
         std::shared_ptr<ReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName);
         std::vector<std::_tstring> GetReportNames(bool bIncludeHidden = false) const;

         /// Gets the ReportDescription for the specified report
         ReportDescription GetReportDescription(LPCTSTR strReportName) const;
         ReportDescription GetReportDescription(const std::_tstring& strReportName) const;

         /// Returns the bitmap displayed on the Report menu for the specified report
         const CBitmap* GetMenuBitmap(LPCTSTR strReportName);
         const CBitmap* GetMenuBitmap(const std::_tstring& strReportName);

         /// Returns the ReportSpecificationBuilder for the specified report
         std::shared_ptr<ReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName);
         std::shared_ptr<ReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName);
         std::shared_ptr<ReportSpecificationBuilder> GetReportSpecificationBuilder(const ReportDescription& rptDesc);

         void SetReportBrowserType(ReportBrowser::Type browserType);
         ReportBrowser::Type GetReportBrowserType() const;

         /// Creates a ReportBrowser
         std::shared_ptr<ReportBrowser> CreateReportBrowser(
            HWND hwndParent, ///< Handle of the parent window
            DWORD dwStyle, ///< Extra window styles (WS_CHILD | WS_VISIBLE is automatically applied), use 0 if no extra styles are wanted
            const std::shared_ptr<ReportSpecification>& pRptSpec, ///< The report specification for creating the report
            const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder ///< The report specification builder to support editing of the report
         ) const;

         /// Displays a dialog that allows the user to select and create a report
         /// \return IDOK or IDCANCEL
         INT_PTR DisplayReportDialog(
            DWORD flags, ///< Unused
            const std::shared_ptr<ReportSpecification>& pRptSpec, ///< The report specification for creating the report
            const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder ///< The report specification builder to support editing of the report
         );

      private:
         // because this object inherits from enable_shared_from_this, it can only be used with shared pointers
         // however, we sill need the constructor so it is private so client's can't directly create this object
         ReportBuilderManager() = default;

         using RptBuilderContainer = std::map<std::_tstring, std::shared_ptr<ReportBuilder>>;
         using RptBuilderEntry = std::pair<std::_tstring, std::shared_ptr<ReportBuilder>>;
         RptBuilderContainer m_RptBuilders;

         std::shared_ptr<rptReport> CreateReport(const std::shared_ptr<ReportSpecification>& pRptSpec) const;

         ReportBrowser::Type m_BrowserType{ ReportBrowser::Type::IE };
      };
   };
};
