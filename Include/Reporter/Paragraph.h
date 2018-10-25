///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_PARAGRAPH_H_
#define INCLUDED_REPORTER_PARAGRAPH_H_
#pragma once

#include <vector>
#include <Reporter\ReporterExp.h>
#include <Reporter\ParagraphVisitor.h>
#include <Reporter\ReportContent.h>
#include <boost\shared_ptr.hpp>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptParagraph

   A paragraph in a report

DESCRIPTION
   This class defines a chapter in a report. For the purposes of the Reporter, 
   a paragraph is merely a collection of report content. A paragraph may also store some
   style information for its report content. Paragraphs also always define a line break.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class REPORTERCLASS rptParagraph : public rptReportItem
{
public:

   typedef std::vector<boost::shared_ptr<rptReportContent> > ContentVec;
   typedef ContentVec::iterator ParagraphContentIterator;
   typedef ContentVec::const_iterator ConstParagraphContentIterator;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor - uses style of parent chapter
   // name is blank by default
   rptParagraph();

   //------------------------------------------------------------------------
   // construct using an existing style object
   rptParagraph( const rptStyleName& rMyStyle);

   //------------------------------------------------------------------------
   // Copy constructor
   rptParagraph(const rptParagraph& /*rParagraph*/);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptParagraph();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   rptParagraph& operator = (const rptParagraph& /*rParagraph*/);

   //------------------------------------------------------------------------
   // < operator to keep the stl vector happy.
   bool operator< (const rptParagraph&) const {return true;}

   //------------------------------------------------------------------------
   // == operator to keep the stl vector happy.
   bool operator==(const rptParagraph&) const {return true;}

   //------------------------------------------------------------------------
   // stream a rptReportContent object
   virtual rptParagraph& operator << (const rptReportContent& rContent );

   //------------------------------------------------------------------------
   // stream a pointer to a rptReportContent object. NOTE that the paragraph
   // now becomes responsible for deleting this object
   virtual rptParagraph& operator << (rptReportContent* pContent );
   
   //------------------------------------------------------------------------
   rptParagraph& operator << (const std::_tstring& str);
   //------------------------------------------------------------------------
   rptParagraph& operator << (LPCTSTR str);
   //------------------------------------------------------------------------
   rptParagraph& operator << (Int8 value);
   //------------------------------------------------------------------------
   rptParagraph& operator<< (Int16 value);
   //------------------------------------------------------------------------
   rptParagraph& operator<< (Int32 value);
   //------------------------------------------------------------------------
   rptParagraph& operator<< (Uint8 value);
   //------------------------------------------------------------------------
   rptParagraph& operator<< (Uint16 value);
   //------------------------------------------------------------------------
   rptParagraph& operator<< (Uint32 value);
   //------------------------------------------------------------------------
   rptParagraph& operator<< (Float32 value);
   //------------------------------------------------------------------------
   rptParagraph& operator<< (Float64 value);

   // GROUP: OPERATIONS
   //
   //------------------------------------------------------------------------
   // check to see if the paragraph has any content
   bool IsEmpty() const {return m_ContentVec.empty();}

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptParagraphVisitor& MyVisitor );

   //------------------------------------------------------------------------
   // clone thyself
   virtual rptParagraph* CreateClone() const;

   // GROUP: ACCESS

   // Name will be used for table of contents generation
   //------------------------------------------------------------------------
   LPCTSTR GetName() const;

   //------------------------------------------------------------------------
   void SetName(LPCTSTR name);


   //------------------------------------------------------------------------
   // Return iterators to ReportContent contained inside of Paragraph
   // pointing to beginning and end.
   ConstParagraphContentIterator ConstBegin();
   ConstParagraphContentIterator ConstEnd();
   ParagraphContentIterator Begin();
   ParagraphContentIterator End();

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   //

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // utility function to be shared by assignment and copy constructor
   void MakeCopy(const rptParagraph& rParagraph);
   
   //------------------------------------------------------------------------
   // utility function to be used for assignment
   void MakeAssignment(const rptParagraph& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //
   //------------------------------------------------------------------------
   // Vector of report content.
   // This vector is responsible for deleting what the
   // rptReportContent pointers point to. 
   ContentVec     m_ContentVec;

   std::_tstring m_Name;

   // GROUP: LIFECYCLE

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif
