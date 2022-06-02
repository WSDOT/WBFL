///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

/// Date and time report content
///
/// This class may be used to put a date and/or time into a report stream. The default constructor freezes the time at report build.
class REPORTERCLASS rptRcDateTime : public rptReportContent
{
public:
   /// set time and date to time of construction. by default, the print routines
   /// print both the date and the time.
   rptRcDateTime();

   rptRcDateTime(const rptRcDateTime& rOther);

   virtual ~rptRcDateTime();

   rptRcDateTime& operator=(const rptRcDateTime& rOther);

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accept a visitor and calls VisitRcDateTime(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Enables printing of the date.
   void EnablePrintDate(bool bPrint) {m_bPrintDate= bPrint;}

   /// Returns the status of date printing
   bool IsPrintDateEnabled() {return m_bPrintDate;}

   /// Enables printing of the time.
   void EnablePrintTime(bool bPrint) {m_bPrintTime= bPrint;}

   /// Returns the status of time printing
   bool IsPrintTimeEnabled() {return m_bPrintTime;}

   /// Returns the date
   sysDate GetDate() {return m_Date;}

   /// Returns the time
   sysTime GetTime() {return m_Time;}

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcDateTime& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcDateTime& rOther);

private:
   sysDate m_Date;
   sysTime m_Time;

   bool   m_bPrintDate;
   bool   m_bPrintTime;
};

#endif // INCLUDED_REPORTER_RCDATETIME_H_
