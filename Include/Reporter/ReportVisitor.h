///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_REPORTVISITOR_H_
#define INCLUDED_REPORTER_REPORTVISITOR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
#include <Reporter\ReporterExp.h>
#include <Reporter\Report.h>

//
// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class REPORTERCLASS rptReport;


// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptReportVisitor

   Abstract class for top-level report visitor

DESCRIPTION
   Visits a report for a purpose

   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

KEYWORDS
   Reporter

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class REPORTERCLASS rptReportVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptReportVisitor();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptReportVisitor();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Do my job - visit a report
   virtual void VisitReport(rptReport*)=0;

   // GROUP: OPERATIONS
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
   // GROUP: LIFECYCLE

   // Prevent accentidal copying and assignment
   rptReportVisitor(const rptReportVisitor&);
   rptReportVisitor& operator=(const rptReportVisitor&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_REPORTVISITOR_H_
