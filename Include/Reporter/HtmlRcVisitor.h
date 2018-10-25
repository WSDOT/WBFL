///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

class REPORTERCLASS rptHtmlHelper;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptHtmlRcVisitor

   Generate Html from report content


DESCRIPTION
   This class generates HTML from all of the different types of report content 
   and sends the HTML to the ostream defined in the constructor.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 04.09.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptHtmlRcVisitor : public rptOutputRcVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructor
   //
   rptHtmlRcVisitor(std::_tostream* pMyOstream, /*const rptUnitSnapShot* MypUnitSnapShot,*/
                  const rptPageLayout* MypPageLayout, const rptHtmlHelper&   rmyHelper,
                  Uint32 logPixelsX, Uint32 logPixelsY);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptHtmlRcVisitor();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Visit a Table
   void VisitRcTable(rptRcTable*);
   //------------------------------------------------------------------------
   // Visit a String
   void VisitRcString(rptRcString*);
   //------------------------------------------------------------------------
   // Visit an Int
   void VisitRcInt(rptRcInt*);
   //------------------------------------------------------------------------
   // Visit an Unsigned
   void VisitRcUnsigned(rptRcUnsigned*);
   //------------------------------------------------------------------------
   // Visit a flow modifier
   void VisitRcFlowModifier(rptRcFlowModifier*);
   //------------------------------------------------------------------------
   // Visit a Font Modifier
   void VisitRcFontModifier(rptRcFontModifier*);
   //------------------------------------------------------------------------
   // Visit a color modifier
   void VisitRcColor(rptRcColor*);
   //------------------------------------------------------------------------
   // Visit a Date and Time string
   void VisitRcDateTime(rptRcDateTime*);
   //------------------------------------------------------------------------
   // Visit a hypertarget
   void VisitRcHyperTarget(rptRcHyperTarget*);
   // Visit an image
   void VisitRcImage(rptRcImage*);
   //------------------------------------------------------------------------
   // Visit a symbol
   void VisitRcSymbol(rptRcSymbol*);

   void VisitRcScalar(rptRcScalar*);
   void VisitRcUnitTag(rptRcUnitTag*);
   void VisitRcUnitValue(rptRcUnitValue*);
   void VisitRcSectionValue(rptRcSectionValue*);
   void VisitRcSectionScalar(rptRcSectionScalar*);
   void VisitRcStation(rptRcStation* pRC);

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
   //------------------------------------------------------------------------
   // The current page layout
   const rptPageLayout* m_pPageLayout;
   const rptHtmlHelper& m_Helper;

   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor is private
   rptHtmlRcVisitor();
   //------------------------------------------------------------------------
   // Copying not allowed
   rptHtmlRcVisitor(const rptHtmlRcVisitor&);
   //------------------------------------------------------------------------
   // Assignment not allowed
   rptHtmlRcVisitor& operator=(const rptHtmlRcVisitor&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Convert border type to pixel thickness
   Uint16 BorderToPixels( rptRiStyle::BorderStyle BStyle);

   //------------------------------------------------------------------------
   // start hyperlink tag
   void HyperStart(const rptReportContent* pC);

   //------------------------------------------------------------------------
   // end hyperlink tag
   void HyperEnd(const rptReportContent* pC);

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_HTMLRCVISITOR_H_
