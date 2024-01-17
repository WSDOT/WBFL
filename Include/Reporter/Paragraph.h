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


#pragma once

#include <vector>
#include <Reporter\ReporterExp.h>
#include <Reporter\ParagraphVisitor.h>
#include <Reporter\ReportContent.h>


/// A paragraph in a report
///
/// This class defines a paragraph in a report. For the purposes of the Reporter, 
/// a paragraph is merely a collection of report content. A paragraph may also store some
/// style information for its report content. Paragraphs also always define a line break.
class REPORTERCLASS rptParagraph : public rptReportItem
{
public:

   using ContentVec = std::vector<std::shared_ptr<rptReportContent>>;
   using ParagraphContentIterator = ContentVec::iterator;
   using ConstParagraphContentIterator = ContentVec::const_iterator;

   /// Creates an unnamed paragraph that inherits the style of the parent chapter
   rptParagraph();

   /// Creates an unnamed paragraph with a named style
   rptParagraph( const rptStyleName& rMyStyle);

   rptParagraph(const rptParagraph& rParagraph);

   virtual ~rptParagraph();

   rptParagraph& operator=(const rptParagraph& rParagraph);

   /// less than operator to keep the stl vector happy.
   bool operator< (const rptParagraph&) const {return true;}

   /// == operator to keep the stl vector happy.
   bool operator==(const rptParagraph&) const {return true;}

   /// Insertion operator for report content. The report content is cloned on insertion
   virtual rptParagraph& operator << (const rptReportContent& rContent );

   /// Insertion operator for report content. The paragraph takes ownership of the content and will delete it when it is no longer used.
   virtual rptParagraph& operator << (rptReportContent* pContent );
   
   virtual rptParagraph& operator << (std::shared_ptr<rptReportContent>& pContent);

   rptParagraph& operator << (const std::_tstring& str);
   rptParagraph& operator << (LPCTSTR str);
   rptParagraph& operator << (Int8 value);
   rptParagraph& operator<< (Int16 value);
   rptParagraph& operator<< (Int32 value);
   rptParagraph& operator<< (Int64 value);
   rptParagraph& operator<< (Uint8 value);
   rptParagraph& operator<< (Uint16 value);
   rptParagraph& operator<< (Uint32 value);
   rptParagraph& operator<< (Uint64 value);
   rptParagraph& operator<< (Float32 value);
   rptParagraph& operator<< (Float64 value);

   /// Inserts content at the specified location in the paragraph. The paragraph takes ownership of the content and will delete it when it is no longer used.
   rptParagraph& InsertContent(
      IndexType location, ///< Index of report content in the paragraph at which the new content will be inserted after
      rptReportContent* pContent ///< Report content to be inserted into the paragraph
   );

   /// Returns true if the paragraph does not have any content
   bool IsEmpty() const {return m_ContentVec.empty();}

   /// Accepts a pargraph visitor and calls VisitParagraph(this)
   virtual void Accept( rptParagraphVisitor& MyVisitor );

   /// Creates a clone
   virtual rptParagraph* CreateClone() const;

   /// Returns the paragraph name
   LPCTSTR GetName() const;

   /// Sets the paragraph name
   ///
   /// The paragraph name is used when creating a table of contents
   void SetName(LPCTSTR name);

   /// Return STL iterator to const report content contained inside of paragraph pointing to beginning.
   ConstParagraphContentIterator ConstBegin();

   /// Return STL iterator to const report content contained inside of paragraph pointing to ending.
   ConstParagraphContentIterator ConstEnd();

   /// Return STL iterator to report content contained inside of paragraph pointing to beginning.
   ParagraphContentIterator Begin();

   /// Return STL iterator to report content contained inside of paragraph pointing to ending.
   ParagraphContentIterator End();

protected:
   /// Copies the content from rParagraph to this paragraph
   void MakeCopy(const rptParagraph& rParagraph);
   
   /// Assigns the content from oOther to this paragraph
   void MakeAssignment(const rptParagraph& rOther);

private:
   // Vector of report content.
   // This vector is responsible for deleting what the
   // rptReportContent pointers point to. 
   ContentVec     m_ContentVec;

   std::_tstring m_Name;
};




