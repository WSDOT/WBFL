///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfLrFixedZone
****************************************************************************/

#include <BridgeModeling\LrFixedZone.h>
#include <BridgeModeling\Girder.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfLrFixedZone::bmfLrFixedZone() :
bmfLrZone(),
m_ZoneStart(0.0),
m_ZoneLength(0.0)
{
}

bmfLrFixedZone::bmfLrFixedZone(Float64 startLocation, Float64 length):
bmfLrZone(),
m_ZoneStart(startLocation),
m_ZoneLength(length)
{
   ASSERTVALID;
}



bmfLrFixedZone::bmfLrFixedZone(const bmfLrFixedZone& rOther) :
bmfLrZone(rOther)
{
   MakeCopy(rOther);
}

bmfLrFixedZone::~bmfLrFixedZone()
{
}

//======================== OPERATORS  =======================================
bmfLrFixedZone& bmfLrFixedZone::operator= (const bmfLrFixedZone& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

bmfLrZone* bmfLrFixedZone::CreateClone() const
{
   return new bmfLrFixedZone(*this);
}

//======================== ACCESS     =======================================
void bmfLrFixedZone::GetZoneLocation(Float64* zoneStart, Float64* zoneLength)const
{
   ASSERTVALID;
   *zoneLength = m_ZoneLength;
   *zoneStart  = m_ZoneStart;
}

void bmfLrFixedZone::SetZoneLocation(Float64 zoneStart, Float64 zoneLength)
{
   ASSERTVALID;
   m_ZoneLength = zoneLength;
   m_ZoneStart  = zoneStart;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfLrFixedZone::MakeCopy(const bmfLrFixedZone& rOther)
{
   m_ZoneStart  = rOther.m_ZoneStart;
   m_ZoneLength = rOther. m_ZoneLength;
}

void bmfLrFixedZone::MakeAssignment(const bmfLrFixedZone& rOther)
{
   bmfLrZone::MakeAssignment( rOther );
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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bmfLrFixedZone::AssertValid() const
{
   if (m_ZoneLength<0.0)
      return false;

   return bmfLrZone::AssertValid();
}

void bmfLrFixedZone::Dump(dbgDumpContext& os) const
{
   bmfLrZone::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfLrFixedZone::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfLrFixedZone");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfLrFixedZone");

   TESTME_EPILOG("LrFixedZone");
}
#endif // _UNITTEST
