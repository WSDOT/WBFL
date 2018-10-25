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

#ifndef INCLUDED_REPORTER_CHAPTER_H_
#define INCLUDED_REPORTER_CHAPTER_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\Paragraph.h>
#include <Reporter\ReportLayoutItem.h>
#include <Reporter\ChapterVisitor.h>
#include <boost\shared_ptr.hpp>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptChapter

   Defines a chapter in a report

DESCRIPTION
   This class acts as a container for paragraphs. Chapters can also be used to
   define the page layout of a group of report paragraphs

   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class REPORTERCLASS rptChapter : public rptReportLayoutItem
{
public:

   typedef std::vector<boost::shared_ptr<rptParagraph> > ParagraphVec;
   typedef ParagraphVec::iterator ChapterParagraphIterator;
   typedef ParagraphVec::const_iterator ConstChapterParagraphIterator;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // chapter with sytle and page layout to be defined by report or to
   // be defined later.
   //
   rptChapter();

   //------------------------------------------------------------------------
   rptChapter(const std::_tstring& name);

   //------------------------------------------------------------------------
   // chapter with fully defined style and page layout.
   //
   rptChapter(const std::_tstring& name, const rptStyleName& rStyleName, 
              const rptPageLayout& rLayout);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptChapter();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   //
   // stream a rptParagraph object
   //
   virtual rptChapter& operator << (const rptParagraph& rParagraph );

   //------------------------------------------------------------------------
   // stream a pointer to a rptParagraph object. NOTE that the Chapter
   // now becomes responsible for deleting this object
   //
   virtual rptChapter& operator << (rptParagraph* pParagraph );

   void Insert(const rptParagraph& rPara);
   void Insert(rptParagraph* pPara);

   // GROUP: OPERATIONS
   
   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptChapterVisitor& MyVisitor );


   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Return STL iterator to const Paragraph contained inside of Chapter
   // pointing to beginning.
   //
   ConstChapterParagraphIterator ConstBegin();
   //------------------------------------------------------------------------
   // Return STL iterator to const Paragraph contained inside of Chapter
   // pointing to end.
   //
   ConstChapterParagraphIterator ConstEnd();
   //------------------------------------------------------------------------
   // Return STL iterator to Paragraph contained inside of Chapter
   // pointing to beginning.
   //
   ChapterParagraphIterator Begin();
   //------------------------------------------------------------------------
   // Return STL iterator to ReportContent contained inside of Paragraph
   // pointing to end.
   //
   ChapterParagraphIterator End();

   //------------------------------------------------------------------------
   LPCTSTR GetName() const;

   //------------------------------------------------------------------------
   void SetName(LPCTSTR name);


   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Copy constructor is protected
   rptChapter(const rptChapter& rOther);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // Vector of paragraphs within the chapter.
   // This vector is responsible for deleting what the
   // rptParagraph pointers point to.
   ParagraphVec     m_ParagraphVec;

   //------------------------------------------------------------------------
   // Name of the chapter
   std::_tstring m_Name;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator is private
   rptChapter& operator = (const rptChapter& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_CHAPTER_H_
