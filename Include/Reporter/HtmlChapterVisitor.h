///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptHtmlChapterVisitor

   Visitor to output Html chapter information


DESCRIPTION
   This class is a ChapterVisitor that generates HTML for a given chapter and
   sends it to the ostream defined in the constructor

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 04.09.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptHtmlChapterVisitor : public rptOutputChapterVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   //
   // construct with an ostream and a pointer to a unitsnapshot. this class does
   // not own, and will not delete, the unitsnapshot pointer
   //
   rptHtmlChapterVisitor(std::_tostream* pMyOstream, /*const rptUnitSnapShot* MypUnitSnapShot,*/
                        const rptHtmlHelper& rmyHelper,
                        Uint32 logPixelsX, Uint32 logPixelsY);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptHtmlChapterVisitor();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //
   //------------------------------------------------------------------------
   // Visit a chapter
   void VisitChapter(rptChapter*);
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
   const rptHtmlHelper& m_Helper;
   Uint32 m_CurrAnchor;
   Uint32 m_CurrParagraphAnchor; // override default paragraph anchor numbers

   Uint32 m_LogPixelsX;
   Uint32 m_LogPixelsY;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor is private
   rptHtmlChapterVisitor();
   //------------------------------------------------------------------------
   // Copying not allowed
   rptHtmlChapterVisitor(const rptHtmlChapterVisitor&);
   //------------------------------------------------------------------------
   // Assignment not allowed
   rptHtmlChapterVisitor& operator=(const rptHtmlChapterVisitor&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   Uint32 GetNextAnchor() 
   {
      CHECK(m_CurrAnchor<rptHtmlHelper::ParaStart);
      return m_CurrAnchor++;
   }
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_HTMLCHAPTERVISITOR_H_
