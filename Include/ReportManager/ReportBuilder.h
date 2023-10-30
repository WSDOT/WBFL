///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <ReportManager\ChapterBuilder.h>
#include <ReportManager\TitlePageBuilder.h>
#include <ReportManager\ReportSpecificationBuilder.h>


class rptReport;

namespace WBFL
{
   namespace Reporting
   {
      /// Creates a rptReport based using the associated ChapterBuilder and ReportSpecification
      class REPORTMANAGERCLASS ReportBuilder  
      {
      public:
	      ReportBuilder(
            LPCTSTR strName, ///< Name of the report
            bool bHidden = false, ///< If true, the report is not displayed in the list of reports presented to the user
            bool bIncludeTimingChapter=false ///< If true, the timing chapter is included in this report
         );
	      virtual ~ReportBuilder() = default;

         /// Sets the status of the Hidden attribute. Report builders may be hidden so that they don't show up in
         /// lists of available reports
         void Hidden(bool bHide);

         /// Returns the status of the Hidden attribute
         bool Hidden() const;

         /// Sets the state of the timing chapter attribute
         void IncludeTimingChapter(bool bInclude=true);

         /// Returns the state of the timing chapter attribute
         bool IncludeTimingChapter() const;

         /// Returns the report name
         LPCTSTR GetName() const;

         /// Adds a title page builder to generate the report's title page
         void AddTitlePageBuilder(std::shared_ptr<TitlePageBuilder> pTitlePageBuilder);

         /// Returns the title page builder
         std::shared_ptr<TitlePageBuilder> GetTitlePageBuilder();

         /// Adds a chapter builder to generate a chapter for the report
         void AddChapterBuilder(std::shared_ptr<ChapterBuilder> pChapterBuilder);

         /// Inserts a chapter builder after the chapter builder with the specified key
         bool InsertChapterBuilder(
            std::shared_ptr<ChapterBuilder> pChapterBuilder, ///< A new chapter builder
            LPCTSTR strKey ///< Chapter builder key of the chapter builder after which the new chapter builder is inserted
         );

         /// Removes a chapter builder with the specified key
         /// \return true if successful
         bool RemoveChapterBuilder(LPCTSTR strKey);

         /// Number of chapter builders
         IndexType GetChapterBuilderCount() const;

         /// Returns a chapter builder at the specified index
         std::shared_ptr<ChapterBuilder> GetChapterBuilder(IndexType idx);
         std::shared_ptr<const ChapterBuilder> GetChapterBuilder(IndexType idx) const;

         /// Returns a chapter builder with the specified key
         std::shared_ptr<ChapterBuilder> GetChapterBuilder(LPCTSTR strKey);
         std::shared_ptr<const ChapterBuilder> GetChapterBuilder(LPCTSTR strKey) const;

         /// Returns the report description
         ReportDescription GetReportDescription() const;

         /// Sets the report specification builder
         void SetReportSpecificationBuilder(std::shared_ptr<ReportSpecificationBuilder> pRptSpecBuilder);

         /// Returns the report specification builder
         std::shared_ptr<ReportSpecificationBuilder> GetReportSpecificationBuilder();
         std::shared_ptr<const ReportSpecificationBuilder> GetReportSpecificationBuilder() const;

         /// Creates a report using the report specification
         virtual std::shared_ptr<rptReport> CreateReport(const std::shared_ptr<const ReportSpecification> pRptSpec) const;

         /// Sets the bitmap object to be displayed on the Report menu
         void SetMenuBitmap(const CBitmap* pBmp);

         /// Gets the bitmap object that is displayed on the Report menu
         const CBitmap* GetMenuBitmap();

         /// Determine if a report needs to be updated
         /// \return true if an updated is needed
         virtual bool NeedsUpdate(
            const std::shared_ptr<const ReportHint>, ///< A hint that indicates what might have changed
            const std::shared_ptr<const ReportSpecification> pRptSpec ///< The specification that would be used to create the report
         ) const;

      private:
         std::_tstring m_Name;
         bool m_bHidden{false};
         bool m_bIncludeTimingChapter{false};
         const CBitmap* m_pBitmap{nullptr};

         std::shared_ptr<TitlePageBuilder> m_pTitlePageBuilder;
         std::shared_ptr<ReportSpecificationBuilder> m_pRptSpecBuilder{std::make_shared<ReportSpecificationBuilder>()};

         using ChapterBuilderContainer = std::vector<std::shared_ptr<ChapterBuilder>>;
         ChapterBuilderContainer m_ChapterBuilders;
      };
   };
};
