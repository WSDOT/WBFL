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

#ifndef INCLUDED_REPORTER_RCINT_H_
#define INCLUDED_REPORTER_RCINT_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <sstream>

/// Report content for integer values
class REPORTERCLASS rptRcInt : public rptReportContent
{
public:
   rptRcInt(Int64 MyVal=0,Int32 MyWidth=0);
   rptRcInt(Int64 MyVal, const std::_tstring& HyperTarget);
   rptRcInt(const rptRcInt& rOther);
   virtual ~rptRcInt();

   rptRcInt& operator=(const rptRcInt& rOther);

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accept a visitor and calls VisitRcInt(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Creates a new integer report content object with the specified based on this object
   rptRcInt* Sv(Int64 Myint);

   /// Returns the integer value
   Int64 GetValue() const;

   /// Sets the integer value
   void SetValue(Int64 MyInt);

   /// Returns the number of characters that the integer value is to fit into
   Int32 GetWidth();

   /// Sets the number of characters that the int is to fit into.
   ///
   /// The purpose of the width option is to allow values to be printed like: 007 (i.e., the
   /// int value is left-padded with zeros to fit into the width.
   void SetWidth(Int32 MyWidth);

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcInt& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcInt& rOther);

private:
   Int64 m_Value;
   Int32 m_Width;
};

#endif
