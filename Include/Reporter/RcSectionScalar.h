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

#ifndef INCLUDED_REPORTER_RCSECTIONSCALAR_H_
#define INCLUDED_REPORTER_RCSECTIONSCALAR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <System\SectionValue.h>
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
   rptRcSectionScalar

   Report content for scalar section values.


DESCRIPTION
   Report content for scalar section values.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcSectionScalar : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcSectionScalar();
   rptRcSectionScalar(const sysSectionValue& scalar);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcSectionScalar(const rptRcSectionScalar& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcSectionScalar();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptRcSectionScalar& operator = (const rptRcSectionScalar& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptRcVisitor& rVisitor );

   bool IsDualValued() const;

   //------------------------------------------------------------------------
   // Returns the report content as a string.  The value is converted to the
   // correct unit of measure and the unit tag is appedned to the string if 
   // required.
   virtual std::_tstring AsString(int idx) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Assings a new section value to this object
   virtual rptReportContent&  SetValue(const sysSectionValue& value);

   //------------------------------------------------------------------------
   // Returns the section value for this piece of report content.
   virtual sysSectionValue GetValue() const;

   //------------------------------------------------------------------------
   // Returns the left section value for this piece of report content.  
   virtual Float64 GetLeftValue() const;

   //------------------------------------------------------------------------
   // Returns the right section value for this piece of report content.  
   virtual Float64 GetRightValue() const;

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
   void MakeCopy(const rptRcSectionScalar& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rptRcSectionScalar& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   sysSectionValue m_Value;
   sysNumericFormatTool::Format m_Format;
   Uint16 m_Precision;
   Uint16 m_Width;

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

#endif // INCLUDED_REPORTER_RCSECTIONSCALAR_H_
