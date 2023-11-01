///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_REPORT_H_
#define INCLUDED_REPORTER_REPORT_H_

#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\Chapter.h>
#include <Reporter\ReportLayoutItem.h>
#include <Reporter\ReportVisitor.h>
#include <string>
#include <System\Checks.h>

/// Defines a Report
///
/// A report acts as a container for chapters that make up a report
class REPORTERCLASS rptReport : public rptReportLayoutItem
{
public:
   using ChapterVec = std::vector<std::shared_ptr<rptChapter>>;
   using ChapterListIterator = ChapterVec::iterator;
   using ConstChapterListIterator = ChapterVec::const_iterator;
   using ChapterListSizeType = ChapterVec::size_type;

   /// Report with default style and page layout
   rptReport(const std::_tstring& rReportName = _T(""));

   /// Report with fully defined style and page layout.
   rptReport(const std::_tstring& rReportName, ///< Report name
             const rptStyleName& rStyleName, ///< Report style
             const rptPageLayout& rLayout ///< Page layout information
   );
   
   virtual ~rptReport();

   // GROUP: OPERATORS

   /// Inseration operator for chapters.
   ///
   /// The report takes ownership of the chapter
   virtual rptReport& operator<<(rptChapter* pChapter );

   /// Insert a chapter into a specific location in the report and takes ownership of the chapter
   virtual bool InsertChapterAt(
      IndexType location, ///< Index of chapter in the report at which the new chapter will be inserted after
      rptChapter* pChapter ///< The chapter to insert
   );

   /// Returns the number of chapters
   IndexType GetChapterCount() const;

   // Enables Heading Numbers
   virtual void EnableHeadingNumbers(bool enabled) {m_enableHeadingNumbers = enabled;}

   // Indicates if header numbers are to be used
   virtual bool HeadingNumbersEnabled() const { return m_enableHeadingNumbers;}

   // Accepts a visitor and calls VisitReport(this)
   virtual void Accept( rptReportVisitor& MyVisitor );

   /// Returns the name of the report
   virtual const std::_tstring& GetName() const {return m_ReportName;}

   // GROUP: ACCESS

   /// Return STL iterator to const Chapter contained inside of Report pointing to beginning.
   ConstChapterListIterator ConstBegin();

   /// Return STL iterator to const Chapter contained inside of Report pointing to ending.
   ConstChapterListIterator ConstEnd();

   /// Return STL iterator to Chapter contained inside of Report pointing to beginning.
   ChapterListIterator Begin();

   /// Return STL iterator to Chapter contained inside of Report pointing to ending.
   ChapterListIterator End();

private:
   rptReport(const rptReport& rOther) = delete;
   rptReport& operator=(const rptReport& rOther) = delete;

   std::_tstring m_ReportName;

   bool m_enableHeadingNumbers{false};

   // A vector of chapters that make up the report.
   // This vector is responsible for deleting what the
   // rptChapter pointers point to.
   ChapterVec     m_ChapterVec;
};

#endif // INCLUDED_REPORTER_REPORT_H_
