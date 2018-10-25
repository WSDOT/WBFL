///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

class REPORTERCLASS rptPageLayout;
class REPORTERCLASS rptHtmlHelper;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptHtmlParagraphVisitor

   Visitor to generate Html from a paragraph.


DESCRIPTION
   This class visits a paragraph, generates HTML and sends it to the ostream 
   defined in the constructor.

LOG
   rdp : 04.09.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptHtmlParagraphVisitor : public rptOutputParagraphVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   rptHtmlParagraphVisitor(std::_tostream* pMyOstream, 
                           const rptPageLayout*   MypPageLayout,
                           const rptHtmlHelper&   rmyHelper,
                           Uint32 logPixelsX,
                           Uint32 logPixelsY);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptHtmlParagraphVisitor();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // visit a paragraph and generate Html
   //
   void VisitParagraph(rptParagraph*);
   // GROUP: ACCESS
   // anchor numbering
   Uint32 GetLastAnchor()            {return m_CurrAnchor;}
   void SetLastAnchor(Uint32 anchor) {m_CurrAnchor=anchor;}

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
   // Page layout for this paragraph. This is typically passed in from the 
   // chapter that owns the paragraph
   const rptPageLayout* m_pPageLayout;
   const rptHtmlHelper& m_Helper;
   Uint32 m_CurrAnchor;

   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment and Default constructor
   rptHtmlParagraphVisitor();
   rptHtmlParagraphVisitor(const rptHtmlParagraphVisitor&);
   rptHtmlParagraphVisitor& operator=(const rptHtmlParagraphVisitor&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   Uint32 GetNextAnchor() 
   {
      return m_CurrAnchor++;
   }
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_HTMLPARAGRAPHVISITOR_H_
