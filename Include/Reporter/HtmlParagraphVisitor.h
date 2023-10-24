///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_HTMLPARAGRAPHVISITOR_H_
#define INCLUDED_REPORTER_HTMLPARAGRAPHVISITOR_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\OutputParagraphVisitor.h>

class REPORTERCLASS rptPageLayout;
class REPORTERCLASS rptHtmlHelper;

/// Visitor to generate HTML from a paragraph.
///
/// This class visits a paragraph, generates HTML and sends it to the ostream defined in the constructor.
class REPORTERCLASS rptHtmlParagraphVisitor : public rptOutputParagraphVisitor
{
public:
   /// Constructor
   rptHtmlParagraphVisitor(std::_tostream* pMyOstream, ///< output stream to receive the html code
                           const rptPageLayout*   pPageLayout, ///< page layout information
                           const rptHtmlHelper&   myHelper, ///< helper object for generating HTML code
                           Uint32 logPixelsX,///< horizontal screen resolution in pixels per inch
                           Uint32 logPixelsY///< vertical screen resolution in pixels per inch
   );

   virtual ~rptHtmlParagraphVisitor();


   /// visit a paragraph and generate Html
   virtual void VisitParagraph(rptParagraph* pParagraph) override;

   /// visit a heading and generate Html
   virtual void VisitHeading(rptParagraph* pHeader) override;

   /// Returns the last anchor number
   Uint32 GetLastAnchor()            {return m_CurrAnchor;}

   /// Sets the last anchor number
   void SetLastAnchor(Uint32 anchor) {m_CurrAnchor=anchor;}



private:
   // Page layout for this paragraph. This is typically passed in from the 
   // chapter that owns the paragraph
   const rptPageLayout* m_pPageLayout;
   const rptHtmlHelper& m_Helper;
   Uint32 m_CurrAnchor;

   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;


   rptHtmlParagraphVisitor() = delete;
   rptHtmlParagraphVisitor(const rptHtmlParagraphVisitor&) = delete;
   rptHtmlParagraphVisitor& operator=(const rptHtmlParagraphVisitor&) = delete;

   // generate html for heading or paragraph
   virtual void GenerateHtmlHelper(rptParagraph* pPara, std::_tstring& tag);

   Uint32 GetNextAnchor() 
   {
      return m_CurrAnchor++;
   }
};

#endif // INCLUDED_REPORTER_HTMLPARAGRAPHVISITOR_H_
