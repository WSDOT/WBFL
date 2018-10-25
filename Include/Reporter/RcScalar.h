///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_REPORTER_RCSCALAR_H_
#define INCLUDED_REPORTER_RCSCALAR_H_
#pragma once

// SYSTEM INCLUDES
//
#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <System\NumericFormatTool.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcScalar

   Report content for a scalar.


DESCRIPTION
   Report content for a scalar.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcScalar : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcScalar();

   //------------------------------------------------------------------------
   // Constructor
   rptRcScalar(Float64 value);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcScalar(const rptRcScalar& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcScalar();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptRcScalar& operator = (const rptRcScalar& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptRcVisitor& rVisitor );

   //------------------------------------------------------------------------
   // Make a virtual copy
   virtual rptReportContent* CreateClone() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the output format
   void SetFormat(sysNumericFormatTool::Format format);

   //------------------------------------------------------------------------
   // Returns the output format
   sysNumericFormatTool::Format GetFormat() const;

   //------------------------------------------------------------------------
   void SetPrecision(Uint16 precision);

   //------------------------------------------------------------------------
   Uint16 GetPrecision() const;

   //------------------------------------------------------------------------
   void SetWidth(Uint16 width);

   //------------------------------------------------------------------------
   Uint16 GetWidth() const;

   //------------------------------------------------------------------------
   // Set the zero-tolerance value any values with absolute value of less than
   // this value will be returned through GetValue as zero, and AsString will
   // also return a zero value.
   // tol must be >= 0.0
   void SetTolerance(Float64 tol);
   Float64 GetTolerance() const;

   //------------------------------------------------------------------------
   Float64 GetValue() const;
   
   //------------------------------------------------------------------------
   virtual rptReportContent&  SetValue(Float64 v);

   //------------------------------------------------------------------------
   std::_tstring AsString() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Value;
   sysNumericFormatTool::Format m_Format;
   Uint16 m_Precision;
   Uint16 m_Width;
   Float64 m_Tolerance;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_RCSCALAR_H_
