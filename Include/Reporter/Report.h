///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2021  Washington State Department of Transportation
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
// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\Chapter.h>
#include <Reporter\ReportLayoutItem.h>
#include <Reporter\ReportVisitor.h>

#include <System\Checks.h>



// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptReport

   Defines a Report

DESCRIPTION
   This class acts as a container for chapters that make up a report
*****************************************************************************/

class REPORTERCLASS rptReport : public rptReportLayoutItem
{
public:
   typedef std::vector<std::shared_ptr<rptChapter> > ChapterVec;
   typedef ChapterVec::iterator ChapterListIterator;
   typedef ChapterVec::const_iterator ConstChapterListIterator;
   typedef ChapterVec::size_type ChapterListSizeType;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Report with default style and page layout
   rptReport(const std::_tstring& rReportName = _T(""));

   //------------------------------------------------------------------------
   // Report with fully defined style and page layout.
   rptReport(const std::_tstring& rReportName,
             const rptStyleName& rStyleName,
             const rptPageLayout& rLayout);
   
   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptReport();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Stream a pointer to a rptChapter object. NOTE that the Report
   // now becomes responsible for deleting this object
   virtual rptReport& operator << (rptChapter* pChapter );

   //------------------------------------------------------------------------
   // Insert a chapter into a specific location in the report
   // now becomes responsible for deleting this object
   virtual bool InsertChapterAt(ChapterListSizeType location, rptChapter* pChapter );

   //------------------------------------------------------------------------
   // Insert a chapter into a specific location in the report
   // now becomes responsible for deleting this object
   virtual ChapterListSizeType GetChapterCount() const;

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptReportVisitor& MyVisitor );

   //------------------------------------------------------------------------
   // Get the name of the report
   virtual std::_tstring GetName() const {return m_ReportName;}

   //------------------------------------------------------------------------
   // Override the rptReportItem version because having a report with no style
   // will certainly cause a crash. This is because the report is the top of
   // the style chain of responsibility.
   void ClearStyle() {CHECK("Cannnot delete style of a Report");
   }

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Return iterator to Beginning of ReportContent contained inside of Chapter
   ConstChapterListIterator ConstBegin();

   //------------------------------------------------------------------------
   // Return iterator to End of ReportContent contained inside of Chapter
   ConstChapterListIterator ConstEnd();

   //------------------------------------------------------------------------
   // Return iterator to Beginning of ReportContent contained inside of Chapter
   ChapterListIterator Begin();

   //------------------------------------------------------------------------
   // Return iterator to End of ReportContent contained inside of Chapter
   ChapterListIterator End();

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // Title of the report
   std::_tstring m_ReportName;

   //------------------------------------------------------------------------
   // A vector of chapters that make up the report.
   // This vector is responsible for deleting what the
   // rptChapter pointers point to.
   ChapterVec     m_ChapterVec;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Copy constructor is private
   rptReport(const rptReport& rOther);

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator is private
   rptReport& operator = (const rptReport& rOther) = delete;

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_REPORT_H_
