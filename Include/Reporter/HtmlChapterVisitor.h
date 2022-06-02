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

#ifndef INCLUDED_REPORTER_HTMLCHAPTERVISITOR_H_
#define INCLUDED_REPORTER_HTMLCHAPTERVISITOR_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\OutputChapterVisitor.h>
#include <Reporter\HtmlParagraphVisitor.h>
#include <Reporter\HtmlHelper.h>


class REPORTERCLASS rptHtmlHelper;

/// Visitor to output Html chapter information
///
/// This class is a ChapterVisitor that generates HTML for a given chapter and sends it to the ostream defined in the constructor
class REPORTERCLASS rptHtmlChapterVisitor : public rptOutputChapterVisitor
{
public:
   /// Constructor
   rptHtmlChapterVisitor(std::_tostream* pMyOstream, ///< output stream to receive the HTML code
                        const rptHtmlHelper& rmyHelper, ///< helper object for generating HTML code
                        Uint32 logPixelsX, ///< horizontal screen resolution in pixels per inch
                        Uint32 logPixelsY ///< vertical screen resolution in pixels per inch
   );

   virtual ~rptHtmlChapterVisitor();

   /// Visit a chapter
   virtual void VisitChapter(rptChapter* pChapter) override;

private:
   const rptHtmlHelper& m_Helper;
   Uint32 m_CurrAnchor;
   Uint32 m_CurrParagraphAnchor; // override default paragraph anchor numbers

   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;

   rptHtmlChapterVisitor() = delete;
   rptHtmlChapterVisitor(const rptHtmlChapterVisitor&) = delete;
   rptHtmlChapterVisitor& operator=(const rptHtmlChapterVisitor&) = delete;

   Uint32 GetNextAnchor() 
   {
      CHECK(m_CurrAnchor<rptHtmlHelper::ParaStart);
      return m_CurrAnchor++;
   }
};

#endif // INCLUDED_REPORTER_HTMLCHAPTERVISITOR_H_
