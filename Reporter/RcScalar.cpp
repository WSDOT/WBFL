///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Reporter\RcScalar.h>
#include <Reporter\RcVisitor.h>
#include <sstream>
#include <math.h>

rptRcScalar::rptRcScalar() :
rptReportContent(),
m_Value( 0.0 )
{
   Init();
}

rptRcScalar::rptRcScalar(Float64 value) :
rptReportContent(),
m_Value( value )
{
   Init();
}

rptRcScalar::rptRcScalar(const rptRcScalar& rOther) :
rptReportContent(rOther)
{
   Init();
   m_Value     = rOther.m_Value;
   m_Format    = rOther.m_Format;
   m_Precision = rOther.m_Precision;
   m_Width     = rOther.m_Width;
   m_Tolerance = rOther.m_Tolerance;
}

rptRcScalar::~rptRcScalar()
{
}

rptRcScalar& rptRcScalar::operator= (const rptRcScalar& rOther)
{
   if( this != &rOther )
   {
      m_Value     = rOther.m_Value;
      m_Format    = rOther.m_Format;
      m_Precision = rOther.m_Precision;
      m_Width     = rOther.m_Width;
      m_Tolerance = rOther.m_Tolerance;
   }

   return *this;
}

void rptRcScalar::Accept( rptRcVisitor& rVisitor )
{
   rVisitor.VisitRcScalar( this );
}

rptReportContent* rptRcScalar::CreateClone() const
{
   return new rptRcScalar( *this );
}

void rptRcScalar::SetFormat(WBFL::System::NumericFormatTool::Format format)
{
   m_Format = format;
}

WBFL::System::NumericFormatTool::Format rptRcScalar::GetFormat() const
{
   return m_Format;
}

void rptRcScalar::SetPrecision(Uint16 precision)
{
   m_Precision = precision;
}

Uint16 rptRcScalar::GetPrecision() const
{
   return m_Precision;
}

void rptRcScalar::SetWidth(Uint16 width)
{
   m_Width = width;
}

Uint16 rptRcScalar::GetWidth() const
{
   return m_Width;
}

void rptRcScalar::SetTolerance(Float64 tol)
{
   PRECONDITION(tol>=0.0);
   m_Tolerance = tol;
}

Float64 rptRcScalar::GetTolerance() const
{
   return m_Tolerance;
}

Float64 rptRcScalar::GetValue() const
{
   if (fabs(m_Value)>m_Tolerance)
      return m_Value;
   else
      return 0.0;
}

rptReportContent& rptRcScalar::SetValue(Float64 value)
{
   m_Value = value;
   return *this;
}

std::_tstring rptRcScalar::AsString() const
{
   WBFL::System::NumericFormatTool fmt(m_Format,m_Width,m_Precision);
   return fmt.AsString( GetValue() );
}

void rptRcScalar::Init()
{
   m_Format    = WBFL::System::NumericFormatTool::Format::Automatic;
   m_Precision = 0;
   m_Width     = 0;
   m_Tolerance = 0.0;
}

