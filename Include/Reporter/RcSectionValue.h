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

#ifndef INCLUDED_REPORTER_RCSECTIONVALUE_H_
#define INCLUDED_REPORTER_RCSECTIONVALUE_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <System\NumericFormatTool.h>

class WBFL::System::SectionValue;

/// Abstract base class for reporting section values with units of measure
///
/// Derived classes supply the unit of measure
class REPORTERCLASS rptRcSectionValue : public rptReportContent
{
public:
   rptRcSectionValue(bool bShowUnitTag = true);
   rptRcSectionValue(const rptRcSectionValue& rOther);
   virtual ~rptRcSectionValue();

   rptRcSectionValue& operator=(const rptRcSectionValue& rOther);

   /// Accepts a visitor and calls VisitRcSectionValue(this)
   virtual void Accept( rptRcVisitor& rVisitor );

   /// Returns if the section value has two different values
   bool IsDualValued() const;

   /// Returns the report content as a string.
   ///
   /// The value is converted to the correct unit of measure and the unit tag is appended to the string if required.
   virtual std::_tstring AsString(
      int idx  ///< Section value index (use 0 for the left value and 1 for the right value)
   ) const;

   /// Assigns a section value and returns a reference to this
   virtual rptReportContent& SetValue(const WBFL::System::SectionValue& value) = 0;

   /// Returns the section value.
   virtual WBFL::System::SectionValue GetValue(
      bool bConvert = false ///< If true, the returned value is converted into the specifed unit of measure
   ) const = 0;

   /// Returns the left section value.
   virtual Float64 GetLeftValue(
      bool bConvert = false ///< If true, the returned value is converted into the specifed unit of measure
   ) const = 0;

   /// Returns the right section value.
   virtual Float64 GetRightValue(
      bool bConvert = false ///< If true, the returned value is converted into the specifed unit of measure
   ) const = 0;

   /// Returns the unit tag for the output unit of measure.
   virtual const std::_tstring& GetUnitTag() const = 0;

   /// Sets the output format
   void SetFormat(WBFL::System::NumericFormatTool::Format format);

   /// Returns the output format
   WBFL::System::NumericFormatTool::Format GetFormat() const;

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
   void MakeCopy(const rptRcSectionValue& rOther);

   /// Assigns the content from oOther to this object
   virtual void MakeAssignment(const rptRcSectionValue& rOther);

private:
   bool m_bShowUnitTag;
   WBFL::System::NumericFormatTool::Format m_Format;
   Int16 m_Width;
   Int16 m_Precision;

   void Init(); ///< common initialization call by all constructors
};

#endif // INCLUDED_REPORTER_RCSECTIONVALUE_H_
