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
#include <Units\StationFormat.h>
#include <Units\SysUnits.h>
#include <Units\Measure.h>
#include <Units\XUnit.h>
#include <MathEx.h>
#include <ctype.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool contains_alpha(const std::_tstring& s);
bool parse_station(const std::_tstring& station,Int16 nSepDigits,Float64* pX,Float64* pY,Float64* pZ);

/****************************************************************************
CLASS
   unitStationFormat
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
unitStationFormat::unitStationFormat()
{
   m_UnitOfMeasure = Meter;
}

unitStationFormat::unitStationFormat(UnitOfMeasure unitOfMeasure)
{
   m_UnitOfMeasure = unitOfMeasure;
}

unitStationFormat::unitStationFormat(const unitStationFormat& rOther)
{
   MakeCopy(rOther);
}

unitStationFormat::~unitStationFormat()
{
}

//======================== OPERATORS  =======================================
unitStationFormat& unitStationFormat::operator= (const unitStationFormat& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 unitStationFormat::FromString(const std::_tstring& station) const
{
   Float64 x,y,z;
   Int16 nSepDigits = (m_UnitOfMeasure == Meter) ? 3 : 2;
   if ( !parse_station(station,nSepDigits,&x,&y,&z) )
      THROW(unitXUnit,BadStationFormat);

   return (x * (m_UnitOfMeasure==Meter?1000.:100.)) + y + z;
}

std::_tstring unitStationFormat::AsString(Float64 station) const
{
   int sign = BinarySign(station);
   station = fabs(station);
   Int16 plus_seperator;
   Int16 num_decimal_places;
   Float64 value;

   // Convert station from system units to meters or feet
   // Setup the station formatting parameters.

   if ( m_UnitOfMeasure == Meter )
   {
      plus_seperator     = 3;
      num_decimal_places = 3;
      value = ::ConvertFromSysUnits( station, unitMeasure::Meter );
   }
   else
   {
      plus_seperator     = 2;
      num_decimal_places = 2;
      value = ::ConvertFromSysUnits( station, unitMeasure::Feet );
   }

   TCHAR buffer[65];
   Float64 shifter = pow(10.0,plus_seperator);
   Int16   num_full_stations = (Int16)floor(value/shifter);
   Float64 num_fra_station   = value - num_full_stations*shifter;

   // Check to make sure that v2 is not basically the same as shifter
   // If station = 69500.00000, we sometimes get 694+100.00 instead of
   // 695+00.
   if ( IsZero(num_fra_station-shifter,pow(10.0,-(num_decimal_places+1))) )
   {
      num_fra_station = 0;
      num_full_stations++;
   }


   CHECK( 0 <= num_fra_station && num_fra_station < shifter );

   Int16   width = plus_seperator + num_decimal_places + 1;

   _stprintf_s(buffer,65,_T("%s%d+%0*.*f"),(sign<0?_T("-"):_T("")),num_full_stations,width,num_decimal_places,num_fra_station);
   return buffer;
}

//======================== ACCESS     =======================================
void unitStationFormat::SetUnitOfMeasure(UnitOfMeasure unitOfMeasure)
{
   m_UnitOfMeasure = unitOfMeasure;
}

unitStationFormat::UnitOfMeasure unitStationFormat::GetUnitOfMeasure() const
{
   return m_UnitOfMeasure;
}

//======================== INQUIRY    =======================================
bool unitStationFormat::IsValidString(const std::_tstring& station) const
{
   Float64 x,y,z;
   Int16 nSepDigits = (m_UnitOfMeasure == Meter) ? 3 : 2;
   return parse_station( station, nSepDigits, &x, &y, &z );
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool unitStationFormat::AssertValid() const
{
   return true;
}

void unitStationFormat::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for unitStationFormat") << endl;
   os << _T("Unit of Measure = ") << ((m_UnitOfMeasure == Meter) ? _T("meter") : _T("feet")) 
      << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void unitStationFormat::MakeCopy(const unitStationFormat& rOther)
{
   m_UnitOfMeasure = rOther.m_UnitOfMeasure;
}

void unitStationFormat::MakeAssignment(const unitStationFormat& rOther)
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

/****************************************************************************
CLASS
   unitStationFormats
****************************************************************************/

const unitStationFormat unitStationFormats::SI(unitStationFormat::Meter);
const unitStationFormat unitStationFormats::US(unitStationFormat::Feet);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
unitStationFormats::~unitStationFormats()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

bool contains_alpha(const std::_tstring& s)
{
   std::_tstring::const_iterator i;
   for ( i = s.begin(); i != s.end(); i++ )
   {
      if ( isalpha(*i) )
         return true;
   }

   return false;
}

bool parse_station(const std::_tstring& station,Int16 nSepDigits,Float64* pX,Float64* pY,Float64* pZ)
{
   // Quick check.
   if ( station.length() == 0 )
      return false;

   // The station string is assumed to be in the format x+y.z
   std::_tstring x;
   std::_tstring y;
   std::_tstring z;

   //
   // Get all the characters to the left of the '+' sign
   //
   std::_tstring::size_type plus_pos = station.find(_T('+'));
   if ( plus_pos < 1 || plus_pos == station.npos )
      return false; // no digits before the + or the + was not found.

   // assign all the characters to the left of the + to x.
   x.assign( station, 0, plus_pos );

   if ( contains_alpha(x) )
      return false; // there was a non-numeric digit in x.

   //
   // Get all the characters between the '+' and the '.'
   //
   std::_tstring::size_type dot_pos = station.find('.');
   if ( dot_pos < plus_pos ||
        dot_pos == station.length() ||
        dot_pos == station.npos )
   {
      // The . was before the +  or
      // The . was the last character in the string   or
      // The . was not found
      return false;
   }

   // assign all the characters between the + and the . to y.
   y.assign( station, plus_pos+1, dot_pos-plus_pos-1 );

   if ( contains_alpha(y) )
      return false; // there was a non-numeric digit in y.

   // make sure there is the right number of digits between
   // the + and the .
   if ( y.length() != nSepDigits )
      return false;

   // 
   // Get all the characters after the '.'
   //
   z.assign( station, dot_pos+1, station.npos-dot_pos-1 );

   if ( contains_alpha(z) )
      return false;

   // The string seems to be in proper format... Convert the string
   // representation of x, y, and z to numbers.
   std::_tistringstream is_x(x);
   is_x >> *pX;

   std::_tistringstream is_y(y);
   is_y >> *pY;

   std::_tistringstream is_z(z);
   is_z >> *pZ;

   // Z has to be made a decimal
   *pZ /= pow(10.,(Float64)z.length());

   return true;
}


