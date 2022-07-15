///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MatLib.h>
#include <Materials/PsStrand.h>
#include <Units\Convert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

// precomputed conversions
static const Float64 g_12p70_MM   = WBFL::Units::ConvertToSysUnits( 12.70, WBFL::Units::Measure::Millimeter );
static const Float64 g_98p71_MM2  = WBFL::Units::ConvertToSysUnits( 98.71, WBFL::Units::Measure::Millimeter2 );
static const Float64 g_1725_MPA   =  WBFL::Units::ConvertToSysUnits( 1725., WBFL::Units::Measure::MPa );
static const Float64 g_197000_MPA = WBFL::Units::ConvertToSysUnits( 197000., WBFL::Units::Measure::MPa );

PsStrand::PsStrand() :
m_Name(_T("Unknown"))
{
   m_Grade    = PsStrand::Grade::Gr1725;
   m_Type     = PsStrand::Type::LowRelaxation;
   m_Size     = PsStrand::Size::D1270;
   m_Coating  = PsStrand::Coating::None;
   m_Diameter = g_12p70_MM;
   m_Area     = g_98p71_MM2;
   m_Fpu      = g_1725_MPA;
   m_Fpy      = 0.90 * m_Fpu;
   m_ModE     = g_197000_MPA;
}

PsStrand::PsStrand(const std::_tstring& name,Grade grade,Type type,Coating coating,Size size,
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

bool PsStrand::operator==(const PsStrand& rOther) const
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

bool PsStrand::operator!=(const PsStrand& rOther) const
{
   return !operator==(rOther);
}

void PsStrand::SetName(const std::_tstring& name)
{
   m_Name = name;
}

std::_tstring PsStrand::GetName() const
{
   return m_Name;
}

void PsStrand::SetGrade(Grade grade)
{
   m_Grade = grade;
}

PsStrand::Grade PsStrand::GetGrade() const
{
   return m_Grade;
}

void PsStrand::SetType(Type type)
{
   m_Type = type;
}

PsStrand::Type PsStrand::GetType() const
{
   return m_Type;
}

std::_tstring PsStrand::GetGrade(PsStrand::Grade grade, bool bUnitsUS)
{
   std::_tstring gr;
   switch (grade)
   {
   case PsStrand::Grade::Gr1725:
      gr = (bUnitsUS ? _T("250") : _T("1725"));
      break;

   case PsStrand::Grade::Gr1860:
      gr = (bUnitsUS ? _T("270") : _T("1860"));
      break;

   case PsStrand::Grade::Gr2070:
      gr = (bUnitsUS ? _T("300") : _T("2070"));
      break;
   default:
      ASSERT(false);
   }
   return gr;
}

std::_tstring PsStrand::GetType(PsStrand::Type type)
{
   std::_tstring ty(type == Type::LowRelaxation ? _T("Low Releaxation") : _T("Stress Relieved"));
   return ty;
}

std::_tstring PsStrand::GetCoating(PsStrand::Coating coating)
{
   std::_tstring c;
   switch (coating)
   {
   case Coating::None: c = _T("None"); break;
   case Coating::SmoothEpoxy: c = _T("Smooth"); break;
   case Coating::GritEpoxy: c = _T("GritEpoxy"); break;
   default:
      ASSERT(false);
   }

   return c;
}

std::_tstring PsStrand::GetSize(PsStrand::Size size,bool bUnitsUS)
{
   std::_tstring sz;
   switch( size )
   {
   case PsStrand::Size::D635:
      sz = ( bUnitsUS ? _T("1/4\"") : _T("6.35mm") );
      break;

   case PsStrand::Size::D794:
      sz = ( bUnitsUS ? _T("5/16\"") : _T("7.94mm") );
      break;

   case PsStrand::Size::D953:
      sz = ( bUnitsUS ? _T("3/8\"") : _T("9.53mm") );
      break;

   case PsStrand::Size::D1111:
      sz = ( bUnitsUS ? _T("7/16\"") : _T("11.11mm") );
      break;

   case PsStrand::Size::D1270:
      sz = ( bUnitsUS ? _T("1/2\"") : _T("12.70mm") );
      break;

   case PsStrand::Size::D1320:
      sz = ( bUnitsUS ? _T("1/2\" Special (0.52\")") : _T("1/2\" Special (13.20mm)") );
      break;

   case PsStrand::Size::D1524:
      sz = ( bUnitsUS ? _T("0.6\"") : _T("15.24mm") );
      break;

   case PsStrand::Size::D1575:
      sz = ( bUnitsUS ? _T("0.62\"") : _T("15.75mm") );
      break;

   case PsStrand::Size::D1778:
      sz = ( bUnitsUS ? _T("0.7\"") : _T("17.78mm") );
      break;

   default:
      ASSERT(false); // should never get here (unless there is a new strand type)
   }

   return sz;
}

#if defined _DEBUG
bool PsStrand::AssertValid() const
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

void PsStrand::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for PsStrand") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool PsStrand::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PsStrand");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for PsStrand");
   TESTME_EPILOG("PsStrand");
}
#endif // _UNITTEST

