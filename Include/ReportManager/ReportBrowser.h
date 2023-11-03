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
#include <ReportManager\ReportSpecificationBuilder.h>
#include <Reporter\Reporter.h>

#include <ReportManager/IReportView.h>

class rptReport;
class TweakIESettings;

namespace WBFL
{
   namespace Reporting
   {
      class ReportBuilderManager;

      /// Class that controls the report browser window
      class REPORTMANAGERCLASS ReportBrowser
      {
      public:
         enum class Type
         {
            IE, // based on IWebBrowser2 control (Internet Explorer)
            Edge// based on WebView2 (Edge)
         };

	      ReportBrowser(Type type);
	      ~ReportBrowser();

         /// Initializes the report browser window
         /// \todo The rptReport should be constant, but can't be until the WBFL::Reporter framework is updated
         bool Initialize(
            HWND hwnd, ///< handle to the parent window
            DWORD dwStyle, ///< additional window styles (WS_CHILD | WS_VISIBLE are provided)
            const std::shared_ptr<const ReportBuilderManager>& pRptMgr, ///< Report builder manager
            const std::shared_ptr<ReportSpecification>& pRptSpec, ///< The report specification
            const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder, ///< The Report specification builder
            std::shared_ptr<rptReport>& pReport ///< The report to display
         );

         /// Updates the browser's content with the new report.
         /// \todo The rptReport should be constant, but can't be until the WBFL::Reporter framework is updated
         void UpdateReport(
            std::shared_ptr<rptReport>& pReport, ///< The new report
            bool bRefresh ///< If true, the browser window is refreshed with the new report content
         );

         /// Returns the report specification
         std::shared_ptr<ReportSpecification> GetReportSpecification();

         /// Returns the report
         /// \todo The rptReport should be constant, but can't be until the WBFL::Reporter framework is updated
         std::shared_ptr<rptReport> GetReport();

         /// Returns the report title
         std::_tstring GetReportTitle();

         /// @brief Resizes the browser window to fit within the parent window
         void FitToParent();

         /// Moves the browser window by locating the top left point
         void Move(POINT topLeft);

         /// Sets the size of the browser window
         void Size(SIZE size);

         /// Prints the content of the browser window
         void Print(
            bool bPrompt ///< If true, the user is prompted to select a printer, otherwise the default printer is used
         );

         /// When called, an interface is presented that allows the user to modify the report content based
         /// \return False if the user canceled the edit, otherwise true
         bool Edit(
            bool bUpdate = true ///< When true, the contents of the report are updated
         ); 

         /// Allows the user to search the report
         void Find();

         /// Selects all of the content of the report
         void SelectAll();

         /// Copies the selected text
         void Copy();

         /// Redraws the contents in the browser window
         void Refresh();

         /// Displays the source code of the browser content
         void ViewSource();

         /// Navigates to the previous content
         void Back();

         /// Navigates ahead
         void Forward();

         /// Navigates to a specific anchor in a report
         void NavigateAnchor(long id);

      private:
         std::unique_ptr<IReportView> m_pReportView;
         std::_tstring m_Filename;
         std::shared_ptr<ReportSpecification> m_pRptSpec;
         std::shared_ptr<const ReportSpecificationBuilder> m_pRptSpecBuilder;
         std::shared_ptr<rptReport> m_pReport;
         std::shared_ptr<const ReportBuilderManager> m_pRptMgr;

         void Navigate(LPCTSTR uri);

         void MakeFilename();
      };
   };
};
