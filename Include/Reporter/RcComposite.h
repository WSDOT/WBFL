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

#ifndef INCLUDED_REPORTER_RcComposite_H_
#define INCLUDED_REPORTER_RcComposite_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <string>


class REPORTERCLASS rptRcVisitor;

/// Composite collection of report content
class REPORTERCLASS rptRcComposite : public rptReportContent
{
public:
   using ContentVec = std::vector<std::shared_ptr<rptReportContent>>;
   using ContentIterator = ContentVec::iterator;
   using ConstContentIterator = ContentVec::const_iterator;

   rptRcComposite();

   /// constructor that takes count rptReportContent* arguments
   ///
   /// Example 
   ///
   ///     *pPara << new rptRcComposite(3,color(Blue), new rptRcString(_T("Some Blue Text")), color(Black)) << rptNewLine;
   rptRcComposite(int count, ...);

   rptRcComposite(const rptRcComposite& rRcComposite);

   virtual ~rptRcComposite();

   rptRcComposite& operator=(const rptRcComposite& rRcComposite);

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accepts a visitor and calls VisitRcContent(this)
   virtual void Accept( rptRcVisitor& MyVisitor ) override;

   /// Appends report content. The content object is cloned on insertion.
   virtual void AddContent(const rptReportContent& rContent);

   // Appends report content. Takes ownership of the content and will delete it when it is no longer used.
   virtual void AddContent(rptReportContent* PContent);

   virtual void AddContent(std::shared_ptr<rptReportContent>& pContent);

   /// Returns true if the composite is empty
   bool Empty();

   /// Returns the number of items in the composite
   size_t Count();

   /// Clears the contents of the composite, deleting stored objects
   void ClearContents();


   /// Return STL iterator to const report content contained inside of this composite pointing to beginning.
   ConstContentIterator ConstBegin() const;
   
   /// Return STL iterator to const report content contained inside of this composite pointing to ending.
   ConstContentIterator ConstEnd() const;
   
   /// Return STL iterator to report content contained inside of this composite pointing to beginning.
   ContentIterator Begin();
   
   /// Return STL iterator to report content contained inside of this composite pointing to ending.
   ContentIterator End();

protected:
   /// Copies the content from rRcComposite to this paragraph
   void MakeCopy(const rptRcComposite& rRcComposite);

   /// Assigns the content from oOther to this paragraph
   void MakeAssignment(const rptRcComposite& rOther);

private:
   //------------------------------------------------------------------------
   // Vector of report content.
   // This vector is responsible for deleting what the
   // rptReportContent pointers pointed to. 
   ContentVec     m_ContentVec;
};

#endif
