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
#include <Material\PsStrand.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matPsStrand
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matPsStrand::matPsStrand() :
m_Name("Unknown")
{
   m_Grade    = Gr1725;
   m_Type     = LowRelaxation;
   m_Size     = D1270;
   m_Diameter = ::ConvertToSysUnits( 12.70, unitMeasure::Millimeter );
   m_Area     = ::ConvertToSysUnits( 98.71, unitMeasure::Millimeter2 );
   m_Fpu      = ::ConvertToSysUnits( 1725., unitMeasure::MPa );
   m_Fpy      = 0.90 * m_Fpu;
   m_ModE     = ::ConvertToSysUnits( 197000., unitMeasure::MPa );
}

matPsStrand::matPsStrand(const std::string& name,Grade grade,Type type,Size size,
                         Float64 fpu,Float64 fpy,Float64 modE,
                         Float64 d, Float64 a) :
m_Name( name )
{
   m_Grade    = grade;
   m_Type     = type;
   m_Size     = size;
   m_Diameter = d;
   m_Area     = a;
   m_Fpu      = fpu;
   m_Fpy      = fpy;
   m_ModE     = modE;
}

matPsStrand::matPsStrand(const matPsStrand& rOther)
{
   MakeCopy(rOther);
}

matPsStrand::~matPsStrand()
{
}

//======================== OPERATORS  =======================================
matPsStrand& matPsStrand::operator= (const matPsStrand& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

bool matPsStrand::operator==(const matPsStrand& rOther) const
{
   if ( m_Name != rOther.m_Name )
      return false;

   if ( m_Grade != rOther.m_Grade )
      return false;

   if ( m_Type != rOther.m_Type )
      return false;

   if ( m_Size != rOther.m_Size )
      return false;

   if ( !IsEqual( m_Diameter, rOther.m_Diameter ) )
      return false;

   if ( !IsEqual( m_Area, rOther.m_Area ) )
      return false;

   if ( !IsEqual( m_Fpu, rOther.m_Fpu ) )
      return false;

   if ( !IsEqual( m_Fpy, rOther.m_Fpy ) )
      return false;

   if ( !IsEqual( m_ModE, rOther.m_ModE ) )
      return false;

   return true;
}

bool matPsStrand::operator!=(const matPsStrand& rOther) const
{
   return !operator==(rOther);
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================

void matPsStrand::SetName(const std::string& name)
{
   m_Name = name;
}

std::string matPsStrand::GetName() const
{
   return m_Name;
}

void matPsStrand::SetGrade(Grade grade)
{
   m_Grade = grade;
}

matPsStrand::Grade matPsStrand::GetGrade() const
{
   return m_Grade;
}

void matPsStrand::SetType(Type type)
{
   m_Type = type;
}

matPsStrand::Type matPsStrand::GetType() const
{
   return m_Type;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool matPsStrand::AssertValid() const
{
   if ( m_Fpy > m_Fpu )
      return false;

   if ( m_Diameter <= 0 )
      return false;

   if ( m_Area <= 0 )
      return false;

   if ( m_ModE <= 0 )
      return false;

   return true;
}

void matPsStrand::Dump(dbgDumpContext& os) const
{
   os << "Dump for matPsStrand" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matPsStrand::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matPsStrand");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matPsStrand");
   TESTME_EPILOG("matPsStrand");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void matPsStrand::MakeCopy(const matPsStrand& rOther)
{
   m_Name     = rOther.m_Name;
   m_Grade    = rOther.m_Grade;
   m_Type     = rOther.m_Type;
   m_Size     = rOther.m_Size;
   m_Diameter = rOther.m_Diameter;
   m_Area     = rOther.m_Area;
   m_Fpu      = rOther.m_Fpu;
   m_Fpy      = rOther.m_Fpy;
   m_ModE     = rOther.m_ModE;
}

void matPsStrand::MakeAssignment(const matPsStrand& rOther)
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


