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
#include <string>
#include <vector>

#include <memory>


namespace WBFL
{
   namespace Reporting
   {
      class ChapterBuilder;
      class ReportSpecification;

      /// Information about a Chapter used to populate the user interface elements
      /// and generate a report specification.
      class REPORTMANAGERCLASS ChapterInfo
      {
      public:
         std::_tstring Key{ _T("Bad Chapter Key") }; ///< Identifier key
         std::_tstring Name{ _T("Bad Chapter Name") }; ///< Name of the chapter
         Uint16 MaxLevel{ 0 }; ///< Maximum level
         bool Select{true}; ///< If true, the chapter is to be selected for creation in the user interface

         ChapterInfo() = default;
         ChapterInfo(const ChapterInfo& other) = default;

         bool operator==(const ChapterInfo& other) const
         {
            return (Key == other.Key ? true : false);
         }
      };

      /// Description of a report
      class REPORTMANAGERCLASS ReportDescription  
      {
      public:
	      ReportDescription(const std::_tstring& strRptName);
	      ~ReportDescription() = default;

         /// Returns the report name
         const std::_tstring& GetReportName() const;

         /// Adds a chapter builder to the report description
         void AddChapter(const std::shared_ptr<const ChapterBuilder>& pChapterBuilder);

         /// Returns the chapter information
         std::vector<ChapterInfo> GetChapterInfo() const;

         /// Returns the number of chapters
         IndexType GetChapterCount() const;

         /// Configures the report specification based on the ChapterInfo
         /// \param[out] pRptSpec The report specification. This specification is cleared and reset based on this ReportDescription
         void ConfigureReportSpecification(std::shared_ptr<ReportSpecification>& pRptSpec) const;

         /// Configures the report specification based on the ChapterInfo
         void ConfigureReportSpecification(
            const std::vector<ChapterInfo>& vChInfo, ///<[in] Chapter Information used to configure the specification
            std::shared_ptr<ReportSpecification>& pRptSpec ///<[out] The report specification. This specification is cleared and reset based on this ReportDescription
         ) const;

         /// Configures the report specification based on the ChapterInfo
         void ConfigureReportSpecification(
            const std::vector<std::_tstring>& chList,  ///<[in] List of chapter keys for the chapters to be included in the report specification
            std::shared_ptr<ReportSpecification>& pRptSpec ///<[out] The report specification. This specification is cleared and reset based on this ReportDescription
         ) const;

      private:
         std::_tstring m_ReportName;
         std::vector<std::shared_ptr<const ChapterBuilder>> m_ChapterBuilders;
      };
   };
};
