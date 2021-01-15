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

#include <Reporter\ReporterLib.h>
#include <Reporter\RcDateTime.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rptRcDateTime::rptRcDateTime() :
rptReportContent(),
m_Time(), 
m_Date()
{
   // don't print date with rptTime routine. We'll do it explicitely.
   m_Time.PrintDate(false);

   m_bPrintDate = true;
   m_bPrintTime = true;
}

rptRcDateTime::rptRcDateTime(const rptRcDateTime& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcDateTime::~rptRcDateTime()
{
}

rptRcDateTime& rptRcDateTime::operator= (const rptRcDateTime& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptReportContent* rptRcDateTime::CreateClone() const 
{
   return new rptRcDateTime(*this); 
}

void rptRcDateTime::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcDateTime(this);
}

void rptRcDateTime::MakeCopy(const rptRcDateTime& rOther)
{
   m_Date = rOther.m_Date;
   m_Time = rOther.m_Time;
   m_bPrintDate = rOther.m_bPrintDate;
   m_bPrintTime = rOther.m_bPrintTime;
}

void rptRcDateTime::MakeAssignment(const rptRcDateTime& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}
