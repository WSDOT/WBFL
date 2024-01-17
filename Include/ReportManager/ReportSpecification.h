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
#include <ReportManager\ReportDescription.h>

namespace WBFL
{
   namespace Reporting
   {
      /// Used by the ReportBuilder to create a report. 
      /// A ReportSpecification defines the chapters that are to be included in a report and the reporting level.
      /// This specification also specifies heading and footer text for the report. 
      /// The right header is always the Date and the right footer is always Page # of #. 
      /// The Left and Center header and footer text are user specified.
      class REPORTMANAGERCLASS ReportSpecification
      {
      public:
         ReportSpecification(const std::_tstring& strReportName);
         ReportSpecification(const ReportSpecification& other) = default;
	      virtual ~ReportSpecification() = default;

         /// Sets the report name
         /// Example: "Details Report"
         void SetReportName(const std::_tstring&);

         /// Gets the report name
         const std::_tstring& GetReportName() const;

         /// Sets the report title
         /// Example: "Details Report for Span 1, Girder A"
         /// \return A string built up from GetReportName() + " For " + GetReportContextString()
         virtual std::_tstring GetReportTitle() const;

         /// A string representing the context of report 
         /// Example: "Span 1, Girder A"
         /// The default implementation returns an empty string
         virtual std::_tstring GetReportContextString() const;

         /// Adds a chapter to the report, creating a ChapterInfo record
         void AddChapter(LPCTSTR strName,LPCTSTR strKey,Uint16 level);

         /// Sets the ChapterInfo for the report
         void SetChapterInfo(const std::vector<ChapterInfo>& chInfo);

         /// Returns the ChapterInfo
         const std::vector<ChapterInfo>& GetChapterInfo() const;

         /// Returns the number of chapters in the report
         IndexType GetChapterCount() const;

         /// Clears all chapters from the specification
         void ClearChapters();

         /// Sets the left header text
         void SetLeftHeader(const std::_tstring& text);
         /// Gets the left header text
         const std::_tstring& GetLeftHeader() const;
         /// Sets the center header text
         void SetCenterHeader(const std::_tstring& text);
         /// Returns the center header text
         const std::_tstring& GetCenterHeader() const;
         /// Sets the left footer text
         void SetLeftFooter(const std::_tstring& text);
         /// Returns the left footer text
         const std::_tstring& GetLeftFooter() const;
         /// Sets the center footer text
         void SetCenterFooter(const std::_tstring& text);
         /// Returns the center footer text
         const std::_tstring& GetCenterFooter() const;

         /// A self-validation check of the specification.
         /// The default implemention returns true. Override this method to provide
         /// application speicific validation
         /// \return true if the specification is valid
         virtual bool IsValid() const;

      private:
         std::_tstring m_ReportName;
         std::vector<ChapterInfo> m_Chapters; /// chapter info for the chapters that are used in the report and the level at which to report

         std::_tstring m_LeftHeader;
         std::_tstring m_CenterHeader;
         std::_tstring m_LeftFooter;
         std::_tstring m_CenterFooter;
      };
   };
};
