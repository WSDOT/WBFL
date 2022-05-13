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

#include <Reporter\ReporterLib.h>
#include <Reporter\RcStation.h>
#include <Reporter\RcVisitor.h>
#include <Units\Convert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rptRcStation::rptRcStation(Float64 station,const WBFL::Units::StationFormat* pFormat) :
rptReportContent(),
m_Station( station ),
m_pFormat( pFormat )
{
}

rptRcStation::rptRcStation(const rptRcStation& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcStation::~rptRcStation()
{
}

rptRcStation& rptRcStation::operator= (const rptRcStation& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

void rptRcStation::Accept( rptRcVisitor& rVisitor )
{
   rVisitor.VisitRcStation( this );
}

rptReportContent* rptRcStation::CreateClone() const
{
   return new rptRcStation( *this );
}

rptReportContent& rptRcStation::SetStation(Float64 station)
{
   m_Station = station;
   return *this;
}

Float64 rptRcStation::GetStation(bool bConvert) const
{
   Float64 value;
   const WBFL::Units::Length& unit_of_measure = ( m_pFormat->GetUnitOfMeasure() == WBFL::Units::StationFormat::UnitOfMeasure::Meter) ?
                                         WBFL::Units::Measure::Meter :
                                         WBFL::Units::Measure::Feet;

   value = bConvert ? WBFL::Units::ConvertFromSysUnits( m_Station, unit_of_measure ) : m_Station;
   return value;
}

std::_tstring rptRcStation::AsString() const
{
   return m_pFormat->AsString( m_Station ); 
}

void rptRcStation::MakeCopy(const rptRcStation& rOther)
{
   m_Station = rOther.m_Station;
   m_pFormat = rOther.m_pFormat;
}

void rptRcStation::MakeAssignment(const rptRcStation& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}
