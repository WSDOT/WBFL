///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2012  Washington State Department of Transportation
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
#include <Units\SysUnitsMgr.h>
#include <Units\SysUnitsMgrListener.h>
#include <Units\SysUnits.h>
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

unitMass         unitSysUnitsMgr::ms_Mass        = unitMeasure::Kilogram;
unitLength       unitSysUnitsMgr::ms_Length      = unitMeasure::Meter;
unitTime         unitSysUnitsMgr::ms_Time        = unitMeasure::Second;
unitTemperature  unitSysUnitsMgr::ms_Temperature = unitMeasure::Celcius;
unitAngle        unitSysUnitsMgr::ms_Angle       = unitMeasure::Radian;
Float64          unitSysUnitsMgr::ms_Gravity     = 9.80665; //; // m/s^2, not 9.81 as we're taught in school
unitAcceleration unitSysUnitsMgr::ms_GravityUnit = unitMeasure::MeterPerSec2;

bool            unitSysUnitsMgr::ms_IsDamaged   = false;
unitSysUnitsMgr::Listeners unitSysUnitsMgr::ms_Listeners;

void notify_listeners(std::list<unitSysUnitsMgrListener*, std::allocator<unitSysUnitsMgrListener*> >& rList)
{
   std::list<unitSysUnitsMgrListener*, std::allocator<unitSysUnitsMgrListener*> >::iterator iter;
   for ( iter = rList.begin(); iter != rList.end(); iter++ )
   {
      (*iter)->OnUpdate();
   }
}

/****************************************************************************
CLASS
   unitSysUnitsMgr
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
unitSysUnitsMgr::~unitSysUnitsMgr()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void unitSysUnitsMgr::BeginDamage()
{
   ms_IsDamaged = true;
}

void unitSysUnitsMgr::EndDamage()
{
   ms_IsDamaged = false;
   NotifyAllListeners();
}

bool unitSysUnitsMgr::IsDamaged()
{
   return ms_IsDamaged;
}

void unitSysUnitsMgr::RegisterListener(unitSysUnitsMgrListener* pListener)
{
   ms_Listeners.push_back( pListener );
   pListener->OnRegistered();
}

void unitSysUnitsMgr::UnregisterListener(unitSysUnitsMgrListener* pListener)
{
   unitSysUnitsMgr::Listeners::iterator found;
   found = std::find( ms_Listeners.begin(), ms_Listeners.end(), pListener );
   if ( found != ms_Listeners.end() )
   {
      pListener->OnUnregistered();
      ms_Listeners.erase( found );
   }
}

CollectionIndexType unitSysUnitsMgr::ListenerCount()
{
   return ms_Listeners.size();
}

//======================== ACCESS     =======================================
unitMass unitSysUnitsMgr::SetMassUnit(const unitMass& u)
{
   unitMass temp = ms_Mass;
   ms_Mass = u;
   NotifyAllListeners();
   return temp;
}

unitMass unitSysUnitsMgr::GetMassUnit()
{
   return  ms_Mass;
}

unitLength unitSysUnitsMgr::SetLengthUnit(const unitLength& u)
{
   unitLength temp = ms_Length;
   ms_Length = u;
   NotifyAllListeners();
   return temp;
}

unitLength unitSysUnitsMgr::GetLengthUnit()
{
   return ms_Length;
}

unitTime unitSysUnitsMgr::SetTimeUnit(const unitTime& u)
{
   unitTime temp = ms_Time;
   ms_Time = u;
   NotifyAllListeners();
   return temp;
}

unitTime unitSysUnitsMgr::GetTimeUnit() 
{
   return ms_Time;
}

unitTemperature unitSysUnitsMgr::SetTemperatureUnit(const unitTemperature& u)
{
   unitTemperature temp = ms_Temperature;
   ms_Temperature = u;
   NotifyAllListeners();
   return temp;
}

unitTemperature unitSysUnitsMgr::GetTemperatureUnit() 
{
   return ms_Temperature;
}

unitAngle unitSysUnitsMgr::SetAngleUnit(const unitAngle& u)
{
   unitAngle temp = ms_Angle;
   ms_Angle = u;
   NotifyAllListeners();
   return temp;
}

unitAngle unitSysUnitsMgr::GetAngleUnit() 
{
   return ms_Angle;
}

void unitSysUnitsMgr::SetGravitationalAcceleration(Float64 gravity)
{
   // Gravity is always stored in m/s^2.
   // the inbound value is in system units. Convert it now.
   gravity = ::ConvertFromSysUnits( gravity, ms_GravityUnit );
   if ( !IsEqual( ms_Gravity, gravity ) )
   {
      ms_Gravity = gravity;
      NotifyAllListeners();
   }
}

Float64 unitSysUnitsMgr::GetGravitationalAcceleration()
{
   // Gravity is always stored in m/s^2.
   // Convert the outbound value to system units.
   return ::ConvertToSysUnits(ms_Gravity,ms_GravityUnit);
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _UNITTEST
bool unitSysUnitsMgr::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("unitSysUnitsMgr");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for unitSysUnitsMgr");
   TESTME_EPILOG("unitSysUnitsMgr");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void unitSysUnitsMgr::NotifyAllListeners()
{
   if ( !IsDamaged() )
   {
      notify_listeners( ms_Listeners );
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


