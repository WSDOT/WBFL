///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_OUTPUTREPORTVISITOR_H_
#define INCLUDED_REPORTER_OUTPUTREPORTVISITOR_H_
#pragma once

#include <ostream>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportVisitor.h>
#include <Reporter\Report.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptOutputReportVisitor

   An abstract ReportVisitor specialized to send a report to an ostream


DESCRIPTION
   This abstract sets up data to send a report to a class derived from ostream.


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

LOG
   rdp : 03.25.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptOutputReportVisitor : public rptReportVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor 
   rptOutputReportVisitor(std::_tostream* pMyOstream/*, const rptUnitLibrary& MyLib */);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptOutputReportVisitor();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // visit the report
   virtual void VisitReport(rptReport*) = 0;

   //------------------------------------------------------------------------
   // Set new units for the visitor.
   //void SetNewUnits(rptUnitSnapShot* pMySnapShot);

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // Ostream that visitor will send output to
   std::_tostream* m_pOstream;
   //------------------------------------------------------------------------
   // Snapshot of the units to be used in generating the report output
   //rptUnitSnapShot* m_pUnitSnapShot;
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS



   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor is private
   rptOutputReportVisitor();
   //------------------------------------------------------------------------
   // Copying not allowed
   rptOutputReportVisitor(const rptOutputReportVisitor&);
   //------------------------------------------------------------------------
   // Assignment not allowed
   rptOutputReportVisitor& operator=(const rptOutputReportVisitor&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_OUTPUTREPORTVISITOR_H_
