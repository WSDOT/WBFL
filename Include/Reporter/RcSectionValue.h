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

#ifndef INCLUDED_REPORTER_RCSECTIONVALUE_H_
#define INCLUDED_REPORTER_RCSECTIONVALUE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <System\NumericFormatTool.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class sysSectionValue;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcSectionValue

   Abstract base class for reporting united section values.


DESCRIPTION
   Abstract base class for reporting united section values.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcSectionValue : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcSectionValue(bool bShowUnitTag = true);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcSectionValue(const rptRcSectionValue& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcSectionValue();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptRcSectionValue& operator = (const rptRcSectionValue& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptRcVisitor& rVisitor );

   // returns true if dual valued
   bool IsDualValued() const; 

   //------------------------------------------------------------------------
   // Returns the report content as a string.  The value is converted to the
   // correct unit of measure and the unit tag is appedned to the string if 
   // required. idx = 0 for first value, idx = 1 for second value
   virtual std::_tstring AsString(int idx) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Assings a new section value to this object
   virtual rptReportContent& SetValue(const sysSectionValue& value) = 0;

   //------------------------------------------------------------------------
   // Returns the section value.
   // If bConvert is <b>true</b>,  the value is converted to output units,
   // otherwise it is in system units.
   virtual sysSectionValue GetValue(bool bConvert = false ) const = 0;

   //------------------------------------------------------------------------
   // Returns the left section value for this piece of report content.  
   // If bConvert is <b>true</b>,  the value is converted to output units,
   // otherwise it is in system units.
   virtual Float64 GetLeftValue(bool bConvert = false) const = 0;

   //------------------------------------------------------------------------
   // Returns the right section value for this piece of report content.  
   // If bConvert is <b>true</b>,  the value is converted to output units,
   // otherwise it is in system units.
   virtual Float64 GetRightValue(bool bConvert = false) const = 0;

   //------------------------------------------------------------------------
   // Returns the unit tag for the output unit of measure.
   virtual std::_tstring GetUnitTag() const = 0;

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

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns <b>true</b> if the unit tag is to be displayed.
   bool ShowUnitTag() const;

   //------------------------------------------------------------------------
   // If <i>bShowUnitTag</i> is <b>true</b>,  the unit tag is to be displayed.
   void ShowUnitTag(bool bShowUnitTag);

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
   //------------------------------------------------------------------------
   void MakeCopy(const rptRcSectionValue& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rptRcSectionValue& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   bool m_bShowUnitTag;
   sysNumericFormatTool::Format m_Format;
   Int16 m_Width;
   Int16 m_Precision;

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

#endif // INCLUDED_REPORTER_RCSECTIONVALUE_H_
