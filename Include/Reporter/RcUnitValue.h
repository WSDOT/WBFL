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

#ifndef INCLUDED_REPORTER_RCUNITVALUE_H_
#define INCLUDED_REPORTER_RCUNITVALUE_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <System\NumericFormatTool.h>

/// Abstract base class for report content for values with a physical unit of measure
class REPORTERCLASS rptRcUnitValue : public rptReportContent
{
public:
   rptRcUnitValue(bool bShowUnitTag = true);
   rptRcUnitValue(const rptRcUnitValue& rOther);
   virtual ~rptRcUnitValue();

   rptRcUnitValue& operator=(const rptRcUnitValue& rOther);

   /// Accept a visitor and calls VisitRcUnitValue(this)
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   /// Sets the value and returns a reference to this
   virtual rptReportContent& SetValue(Float64 value) = 0;

   /// Returns the value
   virtual Float64 GetValue(
      bool bConvert = false ///< If true, the returned value is converted into the specifed unit of measure
   ) const = 0;

   /// Returns the unit tag for the output unit of measure.
   virtual const std::_tstring& GetUnitTag() const = 0;

   /// Returns the value as a string. 
   ///
   /// The value is converted to the correct unit of measure and the unit tag is appedned to the string if required.
   virtual std::_tstring AsString() const;

   /// Sets the output format
   void SetFormat(sysNumericFormatTool::Format format);

   /// Returns the output format
   sysNumericFormatTool::Format GetFormat() const;

   /// Sets the output precision
   void SetPrecision(Uint16 precision);

   /// Returns the output precision
   Uint16 GetPrecision() const;

   /// Sets the width of the output
   void SetWidth(Uint16 width);

   /// Returns the width of the output
   Uint16 GetWidth() const;

   /// Returns true if the unit tag is to be included with the output string.
   bool ShowUnitTag() const;

   /// Set the unit tag display objection
   void ShowUnitTag(
      bool bShowUnitTag ///< true if the unit tag is to be included with the output string.
   );

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcUnitValue& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcUnitValue& rOther);

private:
   bool m_bShowUnitTag;
   sysNumericFormatTool::Format m_Format;
   Uint16 m_Precision;
   Uint16 m_Width;

   void Init(); ///< common initialization call by all constructors
};

#endif // INCLUDED_REPORTER_RCUNITVALUE_H_
