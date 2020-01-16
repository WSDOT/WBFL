///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

// precomputed conversions
static const Float64 g_12p70_MM   = ::ConvertToSysUnits( 12.70, unitMeasure::Millimeter );
static const Float64 g_98p71_MM2  = ::ConvertToSysUnits( 98.71, unitMeasure::Millimeter2 );
static const Float64 g_1725_MPA   =  ::ConvertToSysUnits( 1725., unitMeasure::MPa );
static const Float64 g_197000_MPA = ::ConvertToSysUnits( 197000., unitMeasure::MPa );

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matPsStrand::matPsStrand() :
m_Name(_T("Unknown"))
{
   m_Grade    = Gr1725;
   m_Type     = LowRelaxation;
   m_Size     = D1270;
   m_Coating  = None;
   m_Diameter = g_12p70_MM;
   m_Area     = g_98p71_MM2;
   m_Fpu      = g_1725_MPA;
   m_Fpy      = 0.90 * m_Fpu;
   m_ModE     = g_197000_MPA;
}

matPsStrand::matPsStrand(const std::_tstring& name,Grade grade,Type type,Coating coating,Size size,
                         Float64 fpu,Float64 fpy,Float64 modE,
                         Float64 d, Float64 a) :
m_Name( name )
{
   m_Grade    = grade;
   m_Type     = type;
   m_Coating  = coating;
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

   if ( m_Coating != rOther.m_Coating )
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

void matPsStrand::SetName(const std::_tstring& name)
{
   m_Name = name;
}

std::_tstring matPsStrand::GetName() const
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

std::_tstring matPsStrand::GetSize(matPsStrand::Size size,bool bUnitsUS)
{
   std::_tstring sz;
   switch( size )
   {
   case matPsStrand::D635:
      sz = ( bUnitsUS ? _T("1/4\"") : _T("6.35mm") );
      break;

   case matPsStrand::D794:
      sz = ( bUnitsUS ? _T("5/16\"") : _T("7.94mm") );
      break;

   case matPsStrand::D953:
      sz = ( bUnitsUS ? _T("3/8\"") : _T("9.53mm") );
      break;

   case matPsStrand::D1111:
      sz = ( bUnitsUS ? _T("7/16\"") : _T("11.11mm") );
      break;

   case matPsStrand::D1270:
      sz = ( bUnitsUS ? _T("1/2\"") : _T("12.70mm") );
      break;

   case matPsStrand::D1320:
      sz = ( bUnitsUS ? _T("1/2\" Special (0.52\")") : _T("1/2\" Special (13.20mm)") );
      break;

   case matPsStrand::D1524:
      sz = ( bUnitsUS ? _T("0.6\"") : _T("15.24mm") );
      break;

   case matPsStrand::D1575:
      sz = ( bUnitsUS ? _T("0.62\"") : _T("15.75mm") );
      break;

   case matPsStrand::D1778:
      sz = ( bUnitsUS ? _T("0.7\"") : _T("17.78mm") );
      break;

   default:
      ASSERT(false); // should never get here (unless there is a new strand type)
   }

   return sz;
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
   os << _T("Dump for matPsStrand") << endl;
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
   m_Coating  = rOther.m_Coating;
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


