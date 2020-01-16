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
#include <Reporter\RcSectionValue.h>
#include <Reporter\RcVisitor.h>
#include <System\SectionValue.h>
#include <System\NumericFormatTool.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcSectionValue
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcSectionValue::rptRcSectionValue(bool bShowUnitTag) :
rptReportContent(),
m_bShowUnitTag( bShowUnitTag )
{
   Init();
}

rptRcSectionValue::rptRcSectionValue(const rptRcSectionValue& rOther) :
rptReportContent(rOther)
{
   Init();
   MakeCopy(rOther);
}

rptRcSectionValue::~rptRcSectionValue()
{
}

//======================== OPERATORS  =======================================
rptRcSectionValue& rptRcSectionValue::operator= (const rptRcSectionValue& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void rptRcSectionValue::Accept( rptRcVisitor& rVisitor )
{
   rVisitor.VisitRcSectionValue( this );
}

bool rptRcSectionValue::IsDualValued() const
{
   return !IsEqual(GetLeftValue(false),GetRightValue(false));
}

std::_tstring rptRcSectionValue::AsString(int idx) const
{
   sysNumericFormatTool fmt;
   fmt.SetFormat( m_Format );
   fmt.SetWidth( m_Width );
   fmt.SetPrecision( m_Precision );
   Float64 value = (idx == 0 ? GetLeftValue(true) : GetRightValue(true));
   std::_tstring str = fmt.AsString( value );
   if ( m_bShowUnitTag )
      str += ( _T(" ") + GetUnitTag() );

   return str;   
}

//======================== ACCESS     =======================================

void rptRcSectionValue::SetFormat(sysNumericFormatTool::Format format)
{
   m_Format = format;
}

sysNumericFormatTool::Format rptRcSectionValue::GetFormat() const
{
   return m_Format;
}

void rptRcSectionValue::SetPrecision(Uint16 precision)
{
   m_Precision = precision;
}

Uint16 rptRcSectionValue::GetPrecision() const
{
   return m_Precision;
}

void rptRcSectionValue::SetWidth(Uint16 width)
{
   m_Width = width;
}

Uint16 rptRcSectionValue::GetWidth() const
{
   return m_Width;
}

//======================== INQUIRY    =======================================
bool rptRcSectionValue::ShowUnitTag() const
{
   return m_bShowUnitTag;
}

void rptRcSectionValue::ShowUnitTag(bool bShowUnitTag)
{
   m_bShowUnitTag = bShowUnitTag;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool rptRcSectionValue::AssertValid() const
{
   return true; // rptReportContent::AssertValid();
}

void rptRcSectionValue::Dump(dbgDumpContext& os) const
{
   //rptReportContent::Dump( os );
   os << AsString(0).c_str() << " "  << AsString(1).c_str() << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptRcSectionValue::MakeCopy(const rptRcSectionValue& rOther)
{
   m_bShowUnitTag = rOther.m_bShowUnitTag;
   m_Format       = rOther.m_Format;
   m_Precision    = rOther.m_Precision;
   m_Width        = rOther.m_Width;
}

void rptRcSectionValue::MakeAssignment(const rptRcSectionValue& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptRcSectionValue::Init()
{
   m_Format    = sysNumericFormatTool::Automatic;
   m_Precision = 0;
   m_Width     = 0;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


