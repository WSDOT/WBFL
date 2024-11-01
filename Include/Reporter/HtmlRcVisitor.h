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

#ifndef INCLUDED_REPORTER_HTMLRCVISITOR_H_
#define INCLUDED_REPORTER_HTMLRCVISITOR_H_
#pragma once

#include <ostream>
#include <strstream>
#include <Reporter\ReporterExp.h>
#include <Reporter\OutputRcVisitor.h>
#include <Reporter\PageLayout.h>

class REPORTERCLASS rptHtmlHelper;

/// Generates HTML code from report content
///
/// This class generates HTML from all of the different types of report content and sends the HTML to the ostream defined in the constructor.
class REPORTERCLASS rptHtmlRcVisitor : public rptOutputRcVisitor
{
public:
   /// Constructor
   rptHtmlRcVisitor(std::_tostream* pMyOstream, ///< output stream to receive the HTML code
                   const rptPageLayout* pPageLayout, ///< page layout information
                   const rptHtmlHelper&   rmyHelper,///< helper object for generating HTML code
                   Uint32 logPixelsX, ///< horizontal screen resolution in pixels per inch
                   Uint32 logPixelsY ///< vertical screen resolution in pixels per inch
   );

   virtual ~rptHtmlRcVisitor();

   /// Visit a Table
   void VisitRcTable(rptRcTable*);

   /// Visit a String
   void VisitRcString(rptRcString*);

   /// Visit a Literal String
   void VisitRcStringLiteral(rptRcStringLiteral*);

   /// Visit an Int
   void VisitRcInt(rptRcInt*);
   
   /// Visit an Unsigned
   void VisitRcUnsigned(rptRcUnsigned*);

   /// Visit a flow modifier
   void VisitRcFlowModifier(rptRcFlowModifier*);
   
   /// Visit a Font Modifier
   void VisitRcFontModifier(rptRcFontModifier*);
   
   /// Visit a color modifier
   void VisitRcColor(rptRcColor*);

   /// Visit a background color modifier
   void VisitRcBgColor(rptRcBgColor*);
   
   /// Visit a Date and Time string
   void VisitRcDateTime(rptRcDateTime*);

   /// Visit a hypertarget
   void VisitRcHyperTarget(rptRcHyperTarget*);
   
   /// Visit an image
   void VisitRcImage(rptRcImage*);

   /// Visit a symbol
   void VisitRcSymbol(rptRcSymbol*);

   /// Visit a scalar
   void VisitRcScalar(rptRcScalar*);

   /// Visit a percentage
   void VisitRcPercentage(rptRcPercentage*);

   /// Visit a unit tag
   void VisitRcUnitTag(rptRcUnitTag*);

   /// Visit a unit value
   void VisitRcUnitValue(rptRcUnitValue*);

   /// Visit a section value
   void VisitRcSectionValue(rptRcSectionValue*);

   /// Visit a section scalar
   void VisitRcSectionScalar(rptRcSectionScalar*);

   /// Visit a station
   void VisitRcStation(rptRcStation* pRC);

   /// Visit a composite report content object
   void VisitRcComposite(rptRcComposite*);

private:
   const rptPageLayout* m_pPageLayout;
   const rptHtmlHelper& m_Helper;

   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;

   rptHtmlRcVisitor() = delete;
   rptHtmlRcVisitor(const rptHtmlRcVisitor&) = delete;
   rptHtmlRcVisitor& operator=(const rptHtmlRcVisitor&) = delete;

   // Convert border type to pixel thickness
   Uint16 BorderToPixels( rptRiStyle::BorderStyle BStyle);

   // start hyperlink tag
   void HyperStart(const rptReportContent* pC);

   // end hyperlink tag
   void HyperEnd(const rptReportContent* pC);
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_HTMLRCVISITOR_H_
