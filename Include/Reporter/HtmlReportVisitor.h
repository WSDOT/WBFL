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
      Uint32 logPixelsY,///< vertical screen resolution in pixels per inch
      rptHtmlHelper::BrowserType browserType
   ) :
   rptOutputReportVisitor(pMyOstream), m_Helper(browserType)
   {
      m_LogPixelsX = logPixelsX;
      m_LogPixelsY = logPixelsY;
   }

   virtual ~rptHtmlReportVisitor();

   /// Visit a report and generate HTML code
   virtual void VisitReport(rptReport* pReport) override;

   // Table of Contents for context menu for Edge browser
   // The IE browser builds its table of contents from the HTML DOM in custsite.cpp
   // The Edge WebView2 object does not have a C++ interface to the DOM, and the only browser-based method is really 
   // messy asyncronous jscript calls, that will result in nasty bugs, I beleive.
   // So we will build the TOC directly in C++ and pass it to the edge browser view
   struct TocItem
   {
      TocItem() : m_ID(0) { ; }
      TocItem(LPCTSTR name, Uint32 id) : m_Title(name), m_ID(id) { ; }

      std::_tstring m_Title; // TOC title
      Uint32 m_ID; // ID used to generate html for navigation to anchor
   };

   struct ChapterTocItem
   {
      ChapterTocItem() = default;

      TocItem m_TocItem;
      std::vector <TocItem> m_ParagraphTOCItems;// hapters can contain nested paragraphs
   };

   static std::vector< ChapterTocItem> GenerateTOC(rptReport* pReport);

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
