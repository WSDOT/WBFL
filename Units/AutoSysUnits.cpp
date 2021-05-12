///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#include <Units\UnitsLib.h>
#include <Units\AutoSysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   unitAutoSysUnits
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
unitAutoSysUnits::unitAutoSysUnits() :
m_Mass( unitSysUnitsMgr::GetMassUnit() ),
m_Length( unitSysUnitsMgr::GetLengthUnit() ),
m_Time( unitSysUnitsMgr::GetTimeUnit() ),
m_Temperature( unitSysUnitsMgr::GetTemperatureUnit() ),
m_Angle( unitSysUnitsMgr::GetAngleUnit() )
{
}

unitAutoSysUnits::unitAutoSysUnits(const unitMass& um,
                                   const unitLength& ul,
                                   const unitTime& ut,
                                   const unitTemperature& uk,
                                   const unitAngle& ua) :
m_Mass( um ),
m_Length( ul ),
m_Time( ut ),
m_Temperature( uk ),
m_Angle( ua )
{
}

unitAutoSysUnits::unitAutoSysUnits(const unitAutoSysUnits& rOther) :
m_Mass( unitSysUnitsMgr::GetMassUnit() ),
m_Length( unitSysUnitsMgr::GetLengthUnit() ),
m_Time( unitSysUnitsMgr::GetTimeUnit() ),
m_Temperature( unitSysUnitsMgr::GetTemperatureUnit() ),
m_Angle( unitSysUnitsMgr::GetAngleUnit() )
{
   MakeCopy(rOther);
}

unitAutoSysUnits::~unitAutoSysUnits()
{
   unitSysUnitsMgr::BeginDamage();
   unitSysUnitsMgr::SetMassUnit( m_Mass );
   unitSysUnitsMgr::SetLengthUnit( m_Length );
   unitSysUnitsMgr::SetTimeUnit( m_Time );
   unitSysUnitsMgr::SetTemperatureUnit( m_Temperature );
   unitSysUnitsMgr::SetAngleUnit( m_Angle );
   unitSysUnitsMgr::EndDamage();
}

//======================== OPERATORS  =======================================
unitAutoSysUnits& unitAutoSysUnits::operator= (const unitAutoSysUnits& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void unitAutoSysUnits::SetMassUnit(const unitMass& u)
{
   m_Mass = u;
}

void unitAutoSysUnits::SetLengthUnit(const unitLength& u)
{
   m_Length = u;
}

void unitAutoSysUnits::SetTimeUnit(const unitTime& u)
{
   m_Time = u;
}

void unitAutoSysUnits::SetTemperatureUnit(const unitTemperature& u)
{
   m_Temperature = u;
}

void unitAutoSysUnits::SetAngleUnit(const unitAngle& u)
{
   m_Angle = u;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool unitAutoSysUnits::AssertValid() const
{
   return true;
}

void unitAutoSysUnits::Dump(dbgDumpContext& os) const
{
   os << "Dump for unitAutoSysUnits" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool unitAutoSysUnits::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("unitAutoSysUnits");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for unitAutoSysUnits");
   TESTME_EPILOG("unitAutoSysUnits");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void unitAutoSysUnits::MakeCopy(const unitAutoSysUnits& rOther)
{
   m_Mass        = rOther.m_Mass;
   m_Length      = rOther.m_Length;
   m_Time        = rOther.m_Time;
   m_Temperature = rOther.m_Temperature;
   m_Angle       = rOther.m_Angle;
}

void unitAutoSysUnits::MakeAssignment(const unitAutoSysUnits& rOther)
{
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


