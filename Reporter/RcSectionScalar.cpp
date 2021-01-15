///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <Reporter\RcSectionScalar.h>
#include <Reporter\RcVisitor.h>
#include <System\EngNotation.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rptRcSectionScalar::rptRcSectionScalar()
{
   Init();
}

rptRcSectionScalar::rptRcSectionScalar(const sysSectionValue& scalar) :
rptReportContent(),
m_Value( scalar )
{
   Init();
}

rptRcSectionScalar::rptRcSectionScalar(const rptRcSectionScalar& rOther) :
rptReportContent(rOther)
{
   Init();
   MakeCopy(rOther);
}

rptRcSectionScalar::~rptRcSectionScalar()
{
}

rptRcSectionScalar& rptRcSectionScalar::operator= (const rptRcSectionScalar& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptReportContent* rptRcSectionScalar::CreateClone() const
{
   return new rptRcSectionScalar( *this );
}

void rptRcSectionScalar::Accept( rptRcVisitor& rVisitor )
{
   rVisitor.VisitRcSectionScalar( this );
}

bool rptRcSectionScalar::IsDualValued() const
{
   return !IsEqual(GetLeftValue(),GetRightValue());
}

std::_tstring rptRcSectionScalar::AsString(int idx) const
{
   sysNumericFormatTool fmt( m_Format, m_Width, m_Precision );
   return fmt.AsString( idx == 0 ? GetLeftValue() : GetRightValue() );
}

rptReportContent& rptRcSectionScalar::SetValue( const sysSectionValue& value )
{
   m_Value = value;
   return *this;
}

const sysSectionValue& rptRcSectionScalar::GetValue() const
{
   return m_Value;
}

Float64 rptRcSectionScalar::GetLeftValue() const
{
   return m_Value.Left();
}

Float64 rptRcSectionScalar::GetRightValue() const
{
   return m_Value.Right();
}

void rptRcSectionScalar::SetFormat(sysNumericFormatTool::Format format)
{
   m_Format = format;
}

sysNumericFormatTool::Format rptRcSectionScalar::GetFormat() const
{
   return m_Format;
}

void rptRcSectionScalar::SetPrecision(Uint16 precision)
{
   m_Precision = precision;
}

Uint16 rptRcSectionScalar::GetPrecision() const
{
   return m_Precision;
}

void rptRcSectionScalar::SetWidth(Uint16 width)
{
   m_Width = width;
}

Uint16 rptRcSectionScalar::GetWidth() const
{
   return m_Width;
}

void rptRcSectionScalar::MakeCopy(const rptRcSectionScalar& rOther)
{
   m_Value        = rOther.m_Value;
   m_Format       = rOther.m_Format;
   m_Precision    = rOther.m_Precision;
   m_Width        = rOther.m_Width;
}

void rptRcSectionScalar::MakeAssignment(const rptRcSectionScalar& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

void rptRcSectionScalar::Init()
{
   m_Format    = sysNumericFormatTool::Automatic;
   m_Precision = 0;
   m_Width     = 0;
}
