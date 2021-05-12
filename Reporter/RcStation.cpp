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

#include <Reporter\ReporterLib.h>
#include <Reporter\RcStation.h>
#include <Reporter\RcVisitor.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcStation
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcStation::rptRcStation(Float64 station,const unitStationFormat* pFormat) :
rptReportContent(),
m_Station( station ),
m_pFormat( pFormat )
{
   ASSERTVALID;
}

rptRcStation::rptRcStation(const rptRcStation& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcStation::~rptRcStation()
{
}

//======================== OPERATORS  =======================================
rptRcStation& rptRcStation::operator= (const rptRcStation& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
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
   const unitLength& unit_of_measure = ( m_pFormat->GetUnitOfMeasure() == unitStationFormat::Meter ) ?
                                         unitMeasure::Meter :
                                         unitMeasure::Feet;

   if ( bConvert )
      value = ::ConvertFromSysUnits( m_Station, unit_of_measure ); 
   else
      value = m_Station;

   return value;
}

std::_tstring rptRcStation::AsString() const
{
   return m_pFormat->AsString( m_Station ); 
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rptRcStation::AssertValid() const
{
   return (m_pFormat != 0) /*&& rptReportContent::AssertValid()*/;
}

void rptRcStation::Dump(dbgDumpContext& os) const
{
   //rptReportContent::Dump( os );
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptRcStation::MakeCopy(const rptRcStation& rOther)
{
   m_Station = rOther.m_Station;
   m_pFormat = rOther.m_pFormat;
   ASSERTVALID;
}

void rptRcStation::MakeAssignment(const rptRcStation& rOther)
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
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


