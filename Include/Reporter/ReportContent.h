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

#if !defined INCLUDED_REPORTER_REPORTCONTENT_H_
#define INCLUDED_REPORTER_REPORTCONTENT_H_
#pragma once

// SYSTEM INCLUDES
//
#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportItem.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class REPORTERCLASS rptRcVisitor;
class REPORTERCLASS rptHyperLinkDefinition;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptReportContent

   This abstract class represents the 'content' of a report. 


DESCRIPTION
   This class is an abstract base class representing the low-level 'matter' that
   makes up a report (e.g., strings, paragraphs, font control, numbers...)

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class REPORTERCLASS rptReportContent : public rptReportItem
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptReportContent();

   //------------------------------------------------------------------------
   // Copy constructor
   rptReportContent(const rptReportContent& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptReportContent();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   virtual rptReportContent& operator = (const rptReportContent& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Is report content a hyperlink
   bool IsHyperLink() const;

   //------------------------------------------------------------------------
   // If content is a hyperlink - return target string
   std::string GetHyperTarget() const;

   //------------------------------------------------------------------------
   // Make report content a hyperlink and point it to HyperTarget
   void SetHyperLink(const std::string& HyperTarget);

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptRcVisitor& MyVisitor )=0;

   //------------------------------------------------------------------------
   // virtual way to make a copy.
   virtual rptReportContent* CreateClone() const = 0;


   //
   // GROUP: ACCESS
   // GROUP: INQUIRY
 
protected:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // pointer to hypertext link information. Pointer is non-null if this 
   // piece of report content is a hyperlink
   rptHyperLinkDefinition* m_pHyperLink;

   //
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // copy internal data
   void MakeCopy(const rptReportContent& rContent);

   void MakeAssignment(const rptReportContent& rOther);


   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //
   // pointer to parent for chain of responsibility
   //
   //
   // The current paragraph style.
   //

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   //------------------------------------------------------------------------

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif
