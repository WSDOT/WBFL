///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <System\NumericFormatTool.h>
#include <string>

/// Report content for a scalar.
class REPORTERCLASS rptRcScalar : public rptReportContent
{
public:
   rptRcScalar();
   rptRcScalar(Float64 value);
   rptRcScalar(const rptRcScalar& rOther);
   virtual ~rptRcScalar();

   rptRcScalar& operator=(const rptRcScalar& rOther);

   /// Accepts a visitor and calls VisitRcScalar(this)
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;
 
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

   /// Sets the zero-tolerance value.
   ///
   /// Any value with absolute value of less than this tolerance will be returned through GetValue as zero and AsString will also return a zero value.
   void SetTolerance(Float64 tol);

   /// Returns the zero-tolerance.
   Float64 GetTolerance() const;

   /// Returns the value
   Float64 GetValue() const;
   
   /// Sets the value to be reported and returns a reference to this
   virtual rptReportContent& SetValue(Float64 v);

   /// Returns the value formatted as a string
   virtual std::_tstring AsString() const;

protected:

protected:
   Float64 m_Value;
   sysNumericFormatTool::Format m_Format; 
   Uint16 m_Precision; ///< Output precision
   Uint16 m_Width; ///< Width of the output field
   Float64 m_Tolerance; ///< Absolute values less than this are taken as zero

   void Init(); ///< common initialization call by all constructors
};

#endif // INCLUDED_REPORTER_RCSCALAR_H_
