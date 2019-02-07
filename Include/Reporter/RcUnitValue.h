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

#ifndef INCLUDED_REPORTER_RCUNITVALUE_H_
#define INCLUDED_REPORTER_RCUNITVALUE_H_
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
   rptRcUnitValue

   Abstract base class for united value report content.


DESCRIPTION
   Abstract base class for united value report content.

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcUnitValue : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcUnitValue(bool bShowUnitTag = true);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcUnitValue(const rptRcUnitValue& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcUnitValue();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   rptRcUnitValue& operator=(const rptRcUnitValue& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   //------------------------------------------------------------------------
   // Sets the value for this piece of report content. <i>value</i> is in
   // system units.
   virtual rptReportContent& SetValue(Float64 value) = 0;

   //------------------------------------------------------------------------
   // Returns the value for this piece of report content.  If bConvert is
   // <b>true</b>,  the value is converted to output units, otherwise it is in
   // system units.
   virtual Float64 GetValue(bool bConvert = false) const = 0;

   //------------------------------------------------------------------------
   // Returns the unit tag for the output unit of measure.
   virtual std::_tstring GetUnitTag() const = 0;

   //------------------------------------------------------------------------
   // Returns the report content as a string.  The value is converted to the
   // correct unit of measure and the unit tag is appedned to the string if 
   // required.
   virtual std::_tstring AsString() const;

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
   void MakeCopy(const rptRcUnitValue& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const rptRcUnitValue& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   bool m_bShowUnitTag;
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

#endif // INCLUDED_REPORTER_RCUNITVALUE_H_
