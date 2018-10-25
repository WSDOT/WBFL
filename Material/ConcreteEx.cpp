///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
}

matConcreteEx::matConcreteEx(const std::string& name,Float64 fc,Float64 density,Float64 wDensity,Float64 modE) :
matConcrete( name, fc, density, modE )
{
   m_WeightDensity = wDensity;
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

//======================== OPERATIONS =======================================
matConcrete* matConcreteEx::CreateClone(bool bRegisterListeners) const
{
   std::auto_ptr<matConcreteEx> ap( new matConcreteEx(*this) );
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

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool matConcreteEx::AssertValid() const
{
   return matConcrete::AssertValid();
}

void matConcreteEx::Dump(dbgDumpContext& os) const
{
   matConcrete::Dump( os );
}
#endif // _DEBUG
#if defined _UNITTEST
bool matConcreteEx::TestMe(dbgLog& rlog)
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


