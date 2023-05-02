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

#ifndef INCLUDED_REPORTER_CHAPTER_H_
#define INCLUDED_REPORTER_CHAPTER_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\Paragraph.h>
#include <Reporter\ReportLayoutItem.h>
#include <Reporter\ChapterVisitor.h>

/// Defines a chapter in a report
///
/// This class acts as a container for paragraphs. Chapters can also be used to
/// define the page layout of a group of report paragraphs
class REPORTERCLASS rptChapter : public rptReportLayoutItem
{
public:

   using ParagraphVec = std::vector<std::shared_ptr<rptParagraph>>;
   using ChapterParagraphIterator = ParagraphVec::iterator;
   using ConstChapterParagraphIterator = ParagraphVec::const_iterator;

   /// Constructs default chapter with name, style and page layout inherited from the report or to be defined later
   rptChapter();

   /// Constructs default chapter with style and page layout inherited from the report or to be defined later
   rptChapter(
      const std::_tstring& name ///< chapter name
   );

   rptChapter(const std::_tstring& name,  ///< chapter name
              const rptStyleName& rStyleName,  ///< chapter style
              const rptPageLayout& rLayout ///< page layout for the chapter
   );

   virtual ~rptChapter();

   /// Insertion operator for paragraphs.
   ///
   /// A clone of the paragraph is inserted into the chapter
   virtual rptChapter& operator<<(const rptParagraph& rParagraph );

   /// Inseration operator for paragraphs.
   ///
   /// The chapter takes ownership of the paragraph
   virtual rptChapter& operator<<(rptParagraph* pParagraph );

   /// Inserts a clone of a paragraph into the chapter
   void Insert(const rptParagraph& rPara);

   /// Inserts a paragraph into the chapter and takes ownership
   void Insert(rptParagraph* pPara);

   /// Accept a chapter visitor and calls VisitChapter(this)
   virtual void Accept( rptChapterVisitor& MyVisitor );


   /// Returns status of page break
   bool GetEjectPageBreakBefore() const;

   /// Sets status of page break
   void SetEjectPageBreakBefore(
      bool bBreak///< if true, new page will be ejected before this chapter
   );

   /// Return STL iterator to const Paragraph contained inside of Chapter pointing to beginning.
   ConstChapterParagraphIterator ConstBegin();

   /// Return STL iterator to const Paragraph contained inside of Chapter pointing to end.
   ConstChapterParagraphIterator ConstEnd();

   /// Return STL iterator to Paragraph contained inside of Chapter pointing to beginning.
   ChapterParagraphIterator Begin();

   /// Return STL iterator to ReportContent contained inside of Paragraph pointing to end.
   ChapterParagraphIterator End();

   /// Returns the chapter name
   LPCTSTR GetName() const;

   /// Sets the chapter name
   void SetName(LPCTSTR name);


   // GROUP: INQUIRY

protected:
   /// Copy constructure for derived classes
   rptChapter(const rptChapter& rOther);

private:
   // Vector of paragraphs within the chapter.
   // This vector is responsible for deleting what the
   // rptParagraph pointers point to.
   ParagraphVec     m_ParagraphVec;

   std::_tstring m_Name;
   bool m_bEjectPageBefore;

   rptChapter& operator = (const rptChapter& rOther) = delete;
};

#endif // INCLUDED_REPORTER_CHAPTER_H_
