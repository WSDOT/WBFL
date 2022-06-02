///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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


/// This Visitor builds an Html report
class REPORTERCLASS rptHtmlReportVisitor : public rptOutputReportVisitor
{
public:
   rptHtmlReportVisitor(
      std::_tostream* pMyOstream,///< output stream to receive the html code
      Uint32 logPixelsX,///< horizontal screen resolution in pixels per inch
      Uint32 logPixelsY///< vertical screen resolution in pixels per inch
   ) :
   rptOutputReportVisitor(pMyOstream)
   {
      m_LogPixelsX = logPixelsX;
      m_LogPixelsY = logPixelsY;
   }

   virtual ~rptHtmlReportVisitor();

   /// Visit a report and generate HTML code
   virtual void VisitReport(rptReport* pReport) override;

private:
   rptHtmlHelper m_Helper;

   // # of logical pixels in the x and y directions (# of pixels per inch)
   // Used for converting report content layed out in inches into Pixels.
   // HTML Likes pixels
   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;

   rptHtmlReportVisitor() = delete;
   rptHtmlReportVisitor(const rptHtmlReportVisitor&) = delete;
   rptHtmlReportVisitor& operator=(const rptHtmlReportVisitor&) = delete;
};

#endif // INCLUDED_REPORTER_HTMLREPORTVISITOR_H_
