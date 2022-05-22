///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\ConcreteEx.h>
#include <MathEx.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matConcreteEx
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matConcreteEx::matConcreteEx() :
matConcrete()
{
   m_WeightDensity = 0;
   m_FrShear = 0;
   m_FrFlexure = 0;
}

matConcreteEx::matConcreteEx(const std::_tstring& name,Float64 fc,Float64 density,Float64 wDensity,Float64 modE,Float64 frShear,Float64 frFlexure) :
matConcrete( name, fc, density, modE )
{
   m_WeightDensity = wDensity;
   m_FrShear = frShear;
   m_FrFlexure = frFlexure;
}

matConcreteEx::matConcreteEx(const matConcreteEx& rOther) :
matConcrete(rOther)
{
   MakeCopy(rOther);
}

matConcreteEx::~matConcreteEx()
{
}

//======================== OPERATORS  =======================================
matConcreteEx& matConcreteEx::operator= (const matConcreteEx& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

bool matConcreteEx::operator==(const matConcreteEx& rOther) const
{
   if ( !matConcrete::operator==(rOther) )
      return false;

   if ( !::IsEqual(m_WeightDensity,rOther.m_WeightDensity) )
      return false;
   
   if ( !::IsEqual(m_FrShear,rOther.m_FrShear) )
      return false;
   
   if ( !::IsEqual(m_FrFlexure,rOther.m_FrFlexure) )
      return false;

   return true;
}

bool matConcreteEx::operator!=(const matConcreteEx& rOther) const
{
   return !operator==(rOther);
}

//======================== OPERATIONS =======================================
matConcrete* matConcreteEx::CreateClone(bool bRegisterListeners) const
{
   std::unique_ptr<matConcreteEx> ap( new matConcreteEx(*this) );
   if ( bRegisterListeners )
      RegisterListenersWithOther( ap.get() );

   return ap.release();
}

//======================== ACCESS     =======================================
void matConcreteEx::SetDensityForWeight(Float64 d)
{
   if ( !IsEqual( m_WeightDensity, d ) )
   {
      m_WeightDensity = d;
      NotifyAllListeners();
   }
}

Float64 matConcreteEx::GetDensityForWeight() const
{
   return m_WeightDensity;
}

void matConcreteEx::SetShearFr(Float64 fr)
{
   m_FrShear = fr;
}

Float64 matConcreteEx::GetShearFr() const
{
   return m_FrShear;
}

void matConcreteEx::SetFlexureFr(Float64 fr)
{
   m_FrFlexure = fr;
}

Float64 matConcreteEx::GetFlexureFr() const
{
   return m_FrFlexure;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool matConcreteEx::AssertValid() const
{
   return matConcrete::AssertValid();
}

void matConcreteEx::Dump(WBFL::Debug::LogContext& os) const
{
   matConcrete::Dump( os );
}
#endif // _DEBUG
#if defined _UNITTEST
bool matConcreteEx::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("matConcreteEx");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matConcreteEx");
   TESTME_EPILOG("matConcreteEx");
}
#endif // _UNITTEST


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void matConcreteEx::MakeCopy(const matConcreteEx& rOther)
{
   m_WeightDensity = rOther.m_WeightDensity;
   m_FrShear = rOther.m_FrShear;
   m_FrFlexure = rOther.m_FrFlexure;
}

void matConcreteEx::MakeAssignment(const matConcreteEx& rOther)
{
   MakeCopy( rOther );
   matConcrete::MakeAssignment( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


