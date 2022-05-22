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

#ifndef INCLUDED_REPORTER_RCSECTIONSCALAR_H_
#define INCLUDED_REPORTER_RCSECTIONSCALAR_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <System\SectionValue.h>
#include <System\NumericFormatTool.h>

class WBFL::System::SectionValue;

/// Report content for scalar section values.
class REPORTERCLASS rptRcSectionScalar : public rptReportContent
{
public:
   rptRcSectionScalar();
   rptRcSectionScalar(const WBFL::System::SectionValue& scalar);
   rptRcSectionScalar(const rptRcSectionScalar& rOther);
   virtual ~rptRcSectionScalar();

   rptRcSectionScalar& operator=(const rptRcSectionScalar& rOther);

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Accept a visitor and calls VisitRcSectionScalar(this)
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   /// Returns if the section value has two different values
   bool IsDualValued() const;

   /// Returns the report content as a string.
   std::_tstring AsString
   (
      int idx ///< Section value index (use 0 for the left value and 1 for the right value)
   ) const;

   /// Assigns a section value and returns a reference to this
   rptReportContent& SetValue(const WBFL::System::SectionValue& value);

   /// Returns the section value
   const WBFL::System::SectionValue& GetValue() const;

   /// Returns the left section value
   Float64 GetLeftValue() const;

   /// Returns the right section value
   Float64 GetRightValue() const;

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

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcSectionScalar& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcSectionScalar& rOther);

private:
   WBFL::System::SectionValue m_Value;
   WBFL::System::NumericFormatTool::Format m_Format;
   Uint16 m_Precision;
   Uint16 m_Width;

   void Init(); ///< common initialization call by all constructors
};

#endif // INCLUDED_REPORTER_RCSECTIONSCALAR_H_
