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
#include <Reporter\RcUnitValue.h>
#include <Reporter\RcVisitor.h>

rptRcUnitValue::rptRcUnitValue(bool bShowUnitTag) :
rptReportContent(),
m_bShowUnitTag( bShowUnitTag )
{
   Init();
}

rptRcUnitValue::rptRcUnitValue(const rptRcUnitValue& rOther) :
rptReportContent(rOther)
{
   Init();
   MakeCopy(rOther);
}

rptRcUnitValue::~rptRcUnitValue()
{
}

rptRcUnitValue& rptRcUnitValue::operator= (const rptRcUnitValue& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

void rptRcUnitValue::Accept( rptRcVisitor& rVisitor )
{
   rVisitor.VisitRcUnitValue( this );
}

std::_tstring rptRcUnitValue::AsString() const
{
   WBFL::System::NumericFormatTool fmt;
   fmt.SetFormat( m_Format );
   fmt.SetWidth( m_Width );
   fmt.SetPrecision( m_Precision );
   Float64 value = GetValue( true ); // Convert the number
   std::_tstring str = fmt.AsString( value );
   if ( m_bShowUnitTag )
      str += ( _T(" ") + GetUnitTag() );

   return str;   
}

void rptRcUnitValue::SetFormat(WBFL::System::NumericFormatTool::Format format)
{
   m_Format = format;
}

WBFL::System::NumericFormatTool::Format rptRcUnitValue::GetFormat() const
{
   return m_Format;
}

void rptRcUnitValue::SetPrecision(Uint16 precision)
{
   m_Precision = precision;
}

Uint16 rptRcUnitValue::GetPrecision() const
{
   return m_Precision;
}

void rptRcUnitValue::SetWidth(Uint16 width)
{
   m_Width = width;
}

Uint16 rptRcUnitValue::GetWidth() const
{
   return m_Width;
}

bool rptRcUnitValue::ShowUnitTag() const
{
	return m_bShowUnitTag;
}

void rptRcUnitValue::ShowUnitTag(bool bShowUnitTag)
{
	m_bShowUnitTag = bShowUnitTag;
}

void rptRcUnitValue::MakeCopy(const rptRcUnitValue& rOther)
{
   m_bShowUnitTag = rOther.m_bShowUnitTag;
   m_Format       = rOther.m_Format;
   m_Precision    = rOther.m_Precision;
   m_Width        = rOther.m_Width;
}

void rptRcUnitValue::MakeAssignment(const rptRcUnitValue& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

void rptRcUnitValue::Init()
{
   m_Format    = WBFL::System::NumericFormatTool::Format::Automatic;
   m_Precision = 0;
   m_Width     = 0;
}


