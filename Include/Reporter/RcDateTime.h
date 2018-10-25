///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RCDATETIME_H_
#define INCLUDED_REPORTER_RCDATETIME_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <System\Time.h>
#include <System\Date.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcDateTime

   Date and time report content


DESCRIPTION
   This class may be used to put a date and/or time into a report stream. The
   default constructor freezes the time at report build.


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.06.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcDateTime : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   // set time and date to time of construction. by default, the print routines
   // print both the date and the time.
   rptRcDateTime();

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcDateTime(const rptRcDateTime& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcDateTime();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   rptRcDateTime& operator = (const rptRcDateTime& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Clone thyself
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // accept a visitor
   void Accept( rptRcVisitor& MyVisitor );

   //------------------------------------------------------------------------
   // Tell object wheter or not to print the date
   void EnablePrintDate(bool DoIt) {m_PrintDate=DoIt;}

   //------------------------------------------------------------------------
   // ask object wheter or not to print the date
   bool IsPrintDateEnabled() {return m_PrintDate;}

   //------------------------------------------------------------------------
   // Tell object wheter or not to print the time
   void EnablePrintTime(bool DoIt) {m_PrintTime=DoIt;}

   //------------------------------------------------------------------------
   // Ask object wheter or not to print the time
   bool IsPrintTimeEnabled() {return m_PrintTime;}

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   // Get the date
   sysDate GetDate() {return m_Date;}

   //------------------------------------------------------------------------
   // Get the time
   sysTime GetTime() {return m_Time;}

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Function to aid in copying
   void MakeCopy(const rptRcDateTime& rOther);

   //------------------------------------------------------------------------
   // Function to aid in assignment
   void MakeAssignment(const rptRcDateTime& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // Date at constuction time.
   sysDate m_Date;
   //------------------------------------------------------------------------
   // Time at constuction time.
   sysTime m_Time;

   //------------------------------------------------------------------------
   // Flag to tell whether to print date
   bool   m_PrintDate;
   //------------------------------------------------------------------------
   // Flag to tell whether to time
   bool   m_PrintTime;


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

#endif // INCLUDED_REPORTER_RCDATETIME_H_
