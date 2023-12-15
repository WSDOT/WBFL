///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Units\Convert.h>
#include <Units\Measure.h>
#include <Units\XUnit.h>
#include <MathEx.h>
#include <ctype.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Units;

bool contains_alpha(const std::_tstring& s);
std::tuple<bool,Float64, IndexType> parse_station(const std::_tstring& station,Int16 nSepDigits);

StationFormat::StationFormat(UnitOfMeasure unitOfMeasure)
{
   m_UnitOfMeasure = unitOfMeasure;
}

StationFormat::~StationFormat()
{
}

bool StationFormat::operator==(const StationFormat& other) const
{
   return m_UnitOfMeasure == other.m_UnitOfMeasure;
}

bool StationFormat::operator!=(const StationFormat& other) const
{
   return !operator==(other);
}

std::pair<Float64, ZoneIndexType> StationFormat::FromString(const std::_tstring& strStation) const
{
   Int16 nSepDigits = (m_UnitOfMeasure == UnitOfMeasure::Meter) ? 3 : 2;

   auto [bSuccess, station, zoneIdx] = parse_station(strStation, nSepDigits);
   if ( !bSuccess)
      THROW(XUnit,Reason::BadStationFormat);

   if (m_UnitOfMeasure == UnitOfMeasure::Meter)
   {
      station = WBFL::Units::ConvertToSysUnits(station, Measure::Meter);
   }
   else
   {
      station = WBFL::Units::ConvertToSysUnits(station, Measure::Feet);
   }

   return std::make_pair(station, zoneIdx);
}

std::_tstring StationFormat::AsString(Float64 station, ZoneIndexType zoneIdx) const
{
   Uint8 plus_seperator;
   Uint8 num_decimal_places;
   Float64 value = fabs(station);

   if (m_UnitOfMeasure == UnitOfMeasure::Meter)
   {
      plus_seperator = 3;
      num_decimal_places = 3;
      value = WBFL::Units::ConvertFromSysUnits(value, Measure::Meter);
   }
   else
   {
      plus_seperator = 2;
      num_decimal_places = 2;
      value = WBFL::Units::ConvertFromSysUnits(value, Measure::Feet);
   }

   Float64 shifter = pow(10., plus_seperator);
   int v1 = (int)floor(value / shifter);
   Float64 v2 = value - v1 * shifter;

   // Check to make sure that v2 is not basically the same as shifter
   // If station = 69500.00000, we sometimes get 694+100.00 instead of
   // 695+00.
   if (IsZero(v2 - shifter, 5 * pow(10., -(num_decimal_places + 1))))
   {
      v2 = 0;
      v1++;
   }

   int width = plus_seperator + num_decimal_places + 1; // add one for the '.'

   int nChar;
   nChar = (v1 == 0) ? 1 : (int)log10(fabs((Float64)v1)) + 1;
   nChar += width; // includes one for the '.'
   nChar++; // one for the '+'
   nChar++; // one for the '\n'
   if (station < 0)
      nChar++; // for the leading "-" sign

   bool bIncludeZoneIdx = (zoneIdx != INVALID_INDEX);
   if (bIncludeZoneIdx)
   {
      if (zoneIdx == 0)
         nChar += 2; // ",1" will be added to the station string
      else
         nChar += (int)log10((Float64)zoneIdx) + 2; // ",nnn" where nnn is the zone index
   }

   auto pBuffer(std::make_unique<TCHAR[]>(nChar));
   if (bIncludeZoneIdx)
   {
      _stprintf_s(pBuffer.get(), nChar, (station < 0 ? _T("-%d+%0*.*f,%d") : _T("%d+%0*.*f,%d")), v1, width, num_decimal_places, v2, zoneIdx + 1);
   }
   else
   {
      _stprintf_s(pBuffer.get(), nChar, (station < 0 ? _T("-%d+%0*.*f") : _T("%d+%0*.*f")), v1, width, num_decimal_places, v2);
   }
   std::_tstring strStation(pBuffer.get());
   return strStation;
}

void StationFormat::SetUnitOfMeasure(UnitOfMeasure unitOfMeasure)
{
   m_UnitOfMeasure = unitOfMeasure;
}

StationFormat::UnitOfMeasure StationFormat::GetUnitOfMeasure() const
{
   return m_UnitOfMeasure;
}

const StationFormat StationFormats::SI(StationFormat::UnitOfMeasure::Meter);
const StationFormat StationFormats::US(StationFormat::UnitOfMeasure::Feet);

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

std::tuple<bool, Float64, IndexType> parse_station(const std::_tstring& station, Int16 nDigOffset)
{
   TCHAR chFirst;
   Float64 d;

   // Look for the +
   auto nChar = station.length() + 1;
   auto pBuffer(std::make_unique<TCHAR[]>(nChar));
   _tcscpy_s(pBuffer.get(), station.length() + 1, station.c_str());

   LPTSTR pChar = pBuffer.get() + nChar - 2;
   int idx = (int)(nChar) - 2;
   while (*pChar != _T(',') && 0 <= idx)
   {
      pChar--;
      idx--;
   }

   IndexType zoneIdx = INVALID_INDEX;
   if (*pChar == _T(','))
   {
      // found a zone index
      LPTSTR pEnd = pBuffer.get() + nChar - 2;
      zoneIdx = (IndexType)_tcstol(pChar + 1, &pEnd, 10) - 1;
      *pChar = _T('\0');
   }

   pChar = pBuffer.get();
   while (*pChar != _T('+') && *pChar != _T('\0'))
   {
      pChar++;
   }

   if (*pChar == _T('+'))
   {
      // The + was found

      // Verify that the station is not ill-formed
      // That is, there must be nOffsetDigits between the +
      // and the decimal point or the end of the string

      // first, the string must be long enough to hold the correct number of digits
      IndexType pos = (pChar - pBuffer.get());
      IndexType min_length = pos + nDigOffset + 2;
      if (nChar < (int)min_length)
      {
         return std::make_tuple(false, 0, INVALID_INDEX);
      }

      TCHAR cDecimal = *(pChar + nDigOffset + 1);
      if (cDecimal != _T('.') && cDecimal != 0 && cDecimal != _T('\n') && !isspace(cDecimal))
      {
         return std::make_tuple(false, 0, INVALID_INDEX);
      }


      // Remove the + by shifting the remaining characters 1 to the left
      _tcscpy_s(pChar, nChar - size_t(pChar - pBuffer.get()), pChar + 1);
   }
   else
   {
      // The + wasn't found, this must be a regular number
      d = _tstof(pBuffer.get());
      if (IsZero(d) && pBuffer[0] != _T('0'))
      {
         return std::make_tuple(false, 0, INVALID_INDEX);
      }

      return std::make_tuple(true, d, INVALID_INDEX);
   }

   // Now that the + has been removed, convert the string to a Float64
   chFirst = pBuffer[0];
   d = _tcstod(pBuffer.get(), &pChar);

   // _tcstod returns 0.0 if the string could not be converted
   // but 0.0 is a valid conversion for "0+00.00" and "-0.000", and others
   // if the string is -0.0, d = 0 and first char is '-'
   // this is valid
   bool bValidFirstChar = chFirst == _T('0') || chFirst == _T('-');

   if (d == 0.0 && !bValidFirstChar)
   {
      // Could not convert
      return std::make_tuple(false, 0, INVALID_INDEX);
   }

   while (*pChar == _T(' ') || *pChar == _T('\t'))
      pChar++;

   if (*pChar != _T('\0'))
   {
      // Not terminated properly
      return std::make_tuple(false, 0, INVALID_INDEX);
   }

   return std::make_tuple(true, d, zoneIdx);
}


