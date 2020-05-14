///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// SYSTEM INCLUDES
//
#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class REPORTERCLASS rptRcVisitor;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcComposite

   Composite collection of report content
   
DESCRIPTION
   
*****************************************************************************/

class REPORTERCLASS rptRcComposite : public rptReportContent
{
public:
   typedef std::vector<std::shared_ptr<rptReportContent> > ContentVec;
   typedef ContentVec::iterator ContentIterator;
   typedef ContentVec::const_iterator ConstContentIterator;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructors
   // Start with empty container
   rptRcComposite();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcComposite();

   // GROUP: OPERATORS


   // GROUP: OPERATIONS

   rptReportContent* CreateClone() const;
   virtual void Accept( rptRcVisitor& MyVisitor ) override;

   //------------------------------------------------------------------------
   // append content to collection
   virtual void AddContent(const rptReportContent& rContent);

   // Add pointer. We now own and become responsible for deleting this object
   virtual void AddContent(rptReportContent* PContent);

   bool Empty();
   size_t Count();
   void ClearContents();


   // GROUP: ACCESS
   //
   //------------------------------------------------------------------------
   // Return iterators to ReportContent contained inside of us
   // pointing to beginning and end.
   ConstContentIterator ConstBegin() const;
   ConstContentIterator ConstEnd() const;
   ContentIterator Begin();
   ContentIterator End();

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

   rptRcComposite(const rptRcComposite& rRcComposite);
   rptRcComposite& operator = (const rptRcComposite& rRcComposite);

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // Vector of report content.
   // This vector is responsible for deleting what the
   // rptReportContent pointers pointed to. 
   ContentVec     m_ContentVec;

   // GROUP: LIFECYCLE


   // GROUP: OPERATORS

   // GROUP: OPERATIONS
   void MakeCopy(const rptRcComposite& rRcComposite);
   void MakeAssignment(const rptRcComposite& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif
