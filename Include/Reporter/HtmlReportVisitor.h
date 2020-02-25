///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_HTMLREPORTVISITOR_H_
#define INCLUDED_REPORTER_HTMLREPORTVISITOR_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\OutputReportVisitor.h>
#include <Reporter\HtmlChapterVisitor.h>
#include <Reporter\HtmlHelper.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptHtmlReportVisitor

   This Visitor builds an Html report


DESCRIPTION
   This Visitor builds an Html report

LOG
   rdp : 04.09.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptHtmlReportVisitor : public rptOutputReportVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   rptHtmlReportVisitor(std::_tostream* pMyOstream,Uint32 logPixelsX,Uint32 logPixelsY) :
   rptOutputReportVisitor(pMyOstream)
   {
      m_LogPixelsX = logPixelsX;
      m_LogPixelsY = logPixelsY;
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptHtmlReportVisitor();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   virtual void VisitReport(rptReport*);
   // GROUP: ACCESS
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
   rptHtmlHelper m_Helper;

   // # of logical pixels in the x and y directions (# of pixels per inch)
   // Used for converting report content layed out in inches into Pixels.
   // HTML Likes pixels
   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;

   // GROUP: LIFECYCLE

   // Default constructor
   rptHtmlReportVisitor();
   // Prevent accidental copying and assignment
   rptHtmlReportVisitor(const rptHtmlReportVisitor&);
   rptHtmlReportVisitor& operator=(const rptHtmlReportVisitor&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_HTMLREPORTVISITOR_H_
