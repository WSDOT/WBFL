///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

#include <sstream>
#include <iomanip>

using namespace WBFL::COGO;

Direction::Direction(Float64 direction)
{
   SetValue(direction);
}

Direction::Direction(NSDirection ns, unsigned short deg, unsigned short min, Float64 sec, EWDirection ew)
{
   SetDMS(ns, deg, min, sec, ew);
}

Direction::Direction(const std::_tstring& strDirection)
{
   FromString(strDirection);
}

bool Direction::operator==(const Direction& other) const
{
   return IsEqual(m_Direction, other.m_Direction);
}

bool Direction::operator!=(const Direction& other) const
{
   return !operator==(other);
}

Direction& Direction::operator+=(const Angle& angle)
{
   return Increment(angle);
}

Direction& Direction::operator-=(const Angle& angle)
{
   return Increment(-angle);
}

void Direction::SetValue(Float64 direction)
{
   m_Direction = COGO::NormalizeAngle(direction);
}

Float64 Direction::GetValue() const
{
   return m_Direction;
}

void Direction::SetAzimuth(Float64 azimuth)
{
   if (::IsLE(azimuth, -TWO_PI) || ::IsLE(TWO_PI, azimuth))
      BadAzimuth();

   m_Direction = COGO::NormalizeAngle(PI_OVER_2 - azimuth);
}

void Direction::SetAzimuth(short deg, unsigned short min, Float64 sec)
{
   if ( (deg <= -360 || 360 <= deg) || (min < 0 || 60 <= min) || (sec < 0.0 || 60.0 <= sec))
      BadAzimuth();

   Float64 azimuth = COGO::FromDMS(deg, min, sec);
   CHECK(-TWO_PI < azimuth && azimuth < TWO_PI);

   SetAzimuth(azimuth);
}

Float64 Direction::GetAzimuth() const
{
   return COGO::NormalizeAngle(PI_OVER_2 - m_Direction);
}

void Direction::SetDMS(NSDirection ns, unsigned short deg, unsigned short min, Float64 sec, EWDirection ew)
{
   if ((deg < 0 || 90 < deg) || (min < 0 || 60 <= min) || (sec < 0 || 60.0 <= sec))
      BadDirection();

   Float64 angle;
   Float64 sign;

   if (90. < (deg + min / 60. + sec / 3600.))
      BadDirection();

   // Convert component parts to a decimal angle (radians)
   if (ns == NSDirection::North && ew == EWDirection::East)
   {
      angle = PI_OVER_2;
      sign = -1.0;
   }
   else if (ns == NSDirection::South && ew == EWDirection::West)
   {
      angle = 1.5 * M_PI;
      sign = -1.0;
   }
   else if (ns == NSDirection::South && ew == EWDirection::East)
   {
      angle = 1.5 * M_PI;
      sign = 1.0;
   }
   else if (ns == NSDirection::North && ew == EWDirection::West)
   {
      angle = PI_OVER_2;
      sign = 1.0;
   }
   else
   {
      // Should never get here
      CHECK(false);
   }

   angle += sign * COGO::FromDMS(deg, min, sec);

   if (::IsEqual(angle, TWO_PI))
   {
      angle = 0;
   }

   m_Direction = angle;
}

std::tuple<Direction::NSDirection, unsigned short, unsigned short, Float64, Direction::EWDirection> Direction::GetDMS() const
{
   Float64 dir = m_Direction;

   auto ns = InRange(0., m_Direction, M_PI) ? NSDirection::North : NSDirection::South;
   auto ew = InRange(0., m_Direction, PI_OVER_2) || InRange(1.5 * M_PI, m_Direction, TWO_PI) ? EWDirection::East : EWDirection::West;

   if (InRange(0.0, m_Direction, PI_OVER_2))
   {
      dir = PI_OVER_2 - m_Direction;
   }
   else if (InRange(PI_OVER_2, m_Direction, M_PI))
   {
      dir = m_Direction - PI_OVER_2;
   }
   else if (InRange(M_PI, m_Direction, 3 * PI_OVER_2))
   {
      dir = 3 * PI_OVER_2 - m_Direction;
   }
   else
   {
      dir = m_Direction - 3 * PI_OVER_2;
   }

   short deg;
   unsigned short min;
   Float64 sec;
   std::tie(deg,min,sec) = COGO::ToDMS(dir);
   return std::make_tuple(ns, deg, min, sec, ew);
}

void Direction::FromString(const std::_tstring& strDirection)
{
   auto strDir(strDirection); // copy the string because we are going to change it

   TCHAR cY;
   unsigned short deg;
   unsigned short min;
   Float64 sec;
   TCHAR cX;

   // Trim the whitespace off both ends
   std::_tstring::size_type last_leading_space = strDir.find_first_not_of(_T(" "));
   if (last_leading_space == std::_tstring::npos)
      BadDirectionString();

   std::_tstring::size_type cChar;
   cChar = last_leading_space;  // number of characters to remove
   strDir.erase(0, cChar);

   std::_tstring::size_type first_trailing_space = strDir.find_last_not_of(_T(" "));
   cChar = strDir.length() - first_trailing_space - 1;
   strDir.erase(first_trailing_space + 1, cChar);

   // Determine the number of "parts" used in the angle by counting the 
   // remaining spaces (spaces are the delimiters between the parts)
   // nParts = 3 ->  N dd E
   // nParts = 4 ->  N dd mm E
   // nParts = 5 ->  N dd mm ss.s E
   CollectionIndexType nParts = std::count(strDir.begin(), strDir.end(), _T(' ')) + 1;
   CHECK(0 < nParts);
   if (nParts < 3 || 5 < nParts)
      BadDirectionString();

   //
   // Lets start breaking apart the string
   //

   // Get N/S part. Make sure it is an N or an S, and there
   // is a space following it.
   cY = toupper(strDir[0]);
   if (cY != _T('N') && cY != _T('S') || strDir[1] != _T(' '))
      BadDirectionString();

   NSDirection nsDir = (cY == _T('N') ? NSDirection::North : NSDirection::South);

   // Get the E/W part. Make sure it is an E or a W, and there
   // is a space following it.
   cX = toupper(strDir[strDir.size() - 1]);
   if (cX != _T('E') && cX != _T('W') || strDir[strDir.size() - 2] != _T(' '))
      BadDirectionString();

   EWDirection ewDir = (cX == _T('E') ? EWDirection::East : EWDirection::West);

   //
   // Get the degrees
   //
   std::_tstring::size_type pos;
   pos = strDir.find_first_of(_T(' '));
   strDir.erase(0, pos + 1);
   pos = strDir.find_first_of(_T(' '));
   std::_tstring strDeg(strDir, 0, pos);
   strDir.erase(0, pos + 1);
   deg = _ttoi(strDeg.c_str());

   // If the value of deg is zero, make sure that "0" or "00" were
   // in the string and not some other value that _ttoi evaluates to zero
   if (deg == 0 && (strDeg != _T("0") && strDeg != _T("00")))
      BadDirectionString();

   if (90 < deg)
      BadDirectionString();

   min = 0;
   sec = 0;

   if (4 <= nParts)
   {
      // get the minutes part
      pos = strDir.find_first_of(_T(' '));
      std::_tstring strMin(strDir, 0, pos);
      strDir.erase(0, pos + 1);
      min = _ttoi(strMin.c_str());

      if (min == 0 && (strMin != _T("0") && strMin != _T("00")))
         BadDirectionString();

      if (59 < min)
         BadDirectionString();

      if (nParts == 5)
      {
         // get the seconds part
         pos = strDir.find_first_of(_T(' '));
         std::_tstring strSec(strDir, 0, pos);
         sec = _tstof(strSec.c_str());

         if (IsZero(sec) && strSec[0] != _T('0'))
            BadDirectionString();

         if (60.0 <= sec)
            BadDirectionString();
      }
   }

   SetDMS(nsDir, deg, min, sec, ewDir);
}

std::_tstring Direction::AsString(const std::_tstring& strFormat, bool bAsBearing, bool bSigned, bool bCondensed) const
{
   Float64 value = m_Direction;
   if (IsZero(value)) value = 0.0;

   value = COGO::NormalizeAngle(value);

   std::_tstring strDegTag, strMinTag, strSecTag;
   std::tie(strDegTag, strMinTag, strSecTag) = COGO::ParseAngleTags(strFormat);

   std::_tostringstream os;
   if (bAsBearing)
   {
      NSDirection ns;
      EWDirection ew;
      unsigned short deg;
      unsigned short min;
      Float64 sec;
      std::tie(ns, deg, min, sec, ew) = GetDMS();

      sec = IsZero(sec) ? 0.0 : sec;

      os << std::setw(1) << (ns == NSDirection::North ? _T('N') : _T('S')) << _T(" ") << deg << strDegTag;

      if (bCondensed == false || (0 < min || 0 < sec))
      {
         os << _T(" ") << std::setw(2) << std::setfill(_T('0')) << min << strMinTag;
         os << _T(" ") << std::setw(5) << std::setfill(_T('0')) << std::showpoint << std::fixed << std::setprecision(2) << sec << strSecTag;
      }

      os << _T(" ") << std::setw(1) << (ew == EWDirection::East? _T('E') : _T('W')) << std::ends;
   }
   else
   {
      // azimuth
      value = COGO::NormalizeAngle(PI_OVER_2 - value);
      short deg;
      unsigned short min;
      Float64 sec;
      std::tie(deg, min, sec) = WBFL::COGO::COGO::ToDMS(value);

      sec = IsZero(sec) ? 0.0 : sec;

      os << deg << strDegTag;

      if (bCondensed == false || (0 < min || 0 < sec))
      {
         os << _T(" ") << std::setw(2) << std::setfill(_T('0')) << min << strMinTag;
         os << _T(" ") << std::setw(5) << std::setfill(_T('0')) << std::showpoint << std::fixed << std::setprecision(2) << sec << strSecTag;
      }

      os << std::ends;
   }

   return os.str();
}

Direction& Direction::Increment(const Angle& increment)
{
   m_Direction += increment.GetValue();
   m_Direction = COGO::NormalizeAngle(m_Direction);
   return *this;
}

Direction Direction::IncrementBy(const Angle& increment) const
{
   Float64 dir = m_Direction + increment.GetValue();
   dir = COGO::NormalizeAngle(dir);
   return Direction(dir);
}

Angle Direction::AngleBetween(const Direction& dir) const
{
   Float64 angle = m_Direction - dir.GetValue();
   if (IsZero(angle)) angle = 0.0;

   Angle a(angle);
   a.Normalize();
   return a;
}

void Direction::BadDirectionString()
{
   THROW_COGO(WBFL_COGO_E_DIRECTIONSTRING);
}

void Direction::BadAzimuth()
{
   THROW_COGO(WBFL_COGO_E_AZIMUTH);
}

void Direction::BadDirection()
{
   THROW_COGO(WBFL_COGO_E_DIRECTION);
}

#if defined _UNITTEST
bool Direction::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Direction");

   Direction dir;
   TRY_TESTME(IsZero(dir.GetValue()));

   dir.SetValue(3.23);
   TRY_TESTME(IsEqual(dir.GetValue(), 3.23));

   dir.SetValue(-3.23);
   TRY_TESTME(IsEqual(dir.GetValue(), TWO_PI - 3.23));

   // N 45 15 22.5 E =  44.74375deg = 0.780925757rad
   dir.SetDMS(NSDirection::North, 45, 15, 22.5, EWDirection::East);
   TRY_TESTME(IsEqual(dir.GetValue(), 0.780925757));
   dir.SetValue(0);
   dir.SetValue(0.780925757);
   NSDirection ns;
   EWDirection ew;
   unsigned short d, m;
   Float64 s;
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5,0.1));
   TRY_TESTME(ew == EWDirection::East);

   // N 45 15 22.5 W = 135.25625deg = 2.360666897rad
   dir.SetDMS(NSDirection::North, 45, 15, 22.5, EWDirection::West);
   TRY_TESTME(IsEqual(dir.GetValue(), 2.360666897));
   dir.SetValue(0);
   dir.SetValue(2.360666897);
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5, 0.1));
   TRY_TESTME(ew == EWDirection::West);

   // S 45 15 22.5 W = 224.74375deg = 3.922518411rad
   dir.SetDMS(NSDirection::South, 45, 15, 22.5, EWDirection::West);
   TRY_TESTME(IsEqual(dir.GetValue(), 3.922518411));
   dir.SetValue(0);
   dir.SetValue(3.922518411);
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::South);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5, 0.1));
   TRY_TESTME(ew == EWDirection::West);

   // S 45 15 22.5 E = 315.25625deg = 5.502259551rad
   dir.SetDMS(NSDirection::South, 45, 15, 22.5, EWDirection::East);
   TRY_TESTME(IsEqual(dir.GetValue(), 5.502259551));
   dir.SetValue(0);
   dir.SetValue(5.502259551);
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::South);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5, 0.1));
   TRY_TESTME(ew == EWDirection::East);

   // Test Increment and IncrementBy
   dir.SetValue(M_PI/4);
   dir.Increment(M_PI / 4);
   TRY_TESTME(IsEqual(dir.GetValue(), PI_OVER_2));

   dir.SetValue(3 * PI_OVER_2); // S 0 0 0 E
   dir.Increment(M_PI);
   TRY_TESTME(IsEqual(dir.GetValue(), PI_OVER_2));

   dir.SetValue(3 * PI_OVER_2); // S 0 0 0 E
   dir.Increment(-M_PI);
   TRY_TESTME(IsEqual(dir.GetValue(), PI_OVER_2));

   dir.SetValue(0);
   auto incremented_direction = dir.IncrementBy(1.0);
   TRY_TESTME(IsEqual(dir.GetValue(), 0.0));
   TRY_TESTME(IsEqual(incremented_direction.GetValue(), 1.0));

   // Test FromString
   try { dir.FromString(_T("")); } 
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("                ")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("ABC123")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N S")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 100 45 12.3 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 90 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 15 90.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("0.76")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("E 45 15 22.5 W")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 15 22.5 N")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("NS 45 15 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 15 22.5 EW")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 0A 15 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N A0 15 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 0A 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 A0 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 15 A0.0 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N     45 15 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45     15 22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 15     22.5 E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   try { dir.FromString(_T("N 45 15 22.5     E")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTIONSTRING); }

   // these ones are good
   try { dir.FromString(_T("      N 45 15 22.5 E")); }
   catch (XCoordGeom& ) { TRY_TESTME(false); }

   try { dir.FromString(_T("N 45 15 22.5 E        ")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }

   try { dir.FromString(_T("        N 45 15 22.5 E        ")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }

   try { dir.FromString(_T("N 45 15 22.5 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5));
   TRY_TESTME(ew == EWDirection::East);

   try { dir.FromString(_T("N 00 15 22.5 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 0);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5));
   TRY_TESTME(ew == EWDirection::East);

   try { dir.FromString(_T("N 45 00 22.5 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 22.5));
   TRY_TESTME(ew == EWDirection::East);

   try { dir.FromString(_T("N 45 15 0.00 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East);

   try { dir.FromString(_T("N 45 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East);

   try { dir.FromString(_T("N 0 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 0);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East);
   TRY_TESTME(IsEqual(dir.GetValue(), PI_OVER_2));

   try { dir.FromString(_T("N 0 W")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 0);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East);
   TRY_TESTME(IsEqual(dir.GetValue(), PI_OVER_2));

   try { dir.FromString(_T("N 90 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 90);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East);
   TRY_TESTME(IsEqual(dir.GetValue(), 0.0));

   try { dir.FromString(_T("N 90 W")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 90);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::West);
   TRY_TESTME(IsEqual(dir.GetValue(), M_PI));

   try { dir.FromString(_T("S 0 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::South);
   TRY_TESTME(d == 0);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East);
   TRY_TESTME(IsEqual(dir.GetValue(), 3 * PI_OVER_2));

   try { dir.FromString(_T("S 0 W")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::South);
   TRY_TESTME(d == 0);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East); // East is favored when ambiguous
   TRY_TESTME(IsEqual(dir.GetValue(), 3 * PI_OVER_2));

   try { dir.FromString(_T("S 90 E")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);  // North is favored when ambiguous
   TRY_TESTME(d == 90);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::East);
   TRY_TESTME(IsEqual(dir.GetValue(), 0.0));

   try { dir.FromString(_T("S 90 W")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);  // North is favored when ambiguous
   TRY_TESTME(d == 90);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::West);
   TRY_TESTME(IsEqual(dir.GetValue(), M_PI));

   try { dir.FromString(_T("N 34 54 W")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 34);
   TRY_TESTME(m == 54);
   TRY_TESTME(IsEqual(s, 0.0));
   TRY_TESTME(ew == EWDirection::West);
   

   // Test SetDMS
   try { dir.SetDMS(NSDirection::North,100,15,22.5,EWDirection::East); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTION); }

   try { dir.SetDMS(NSDirection::North, -10, 15, 22.5, EWDirection::East); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTION); }

   try { dir.SetDMS(NSDirection::North, 45, 90, 22.5, EWDirection::East); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTION); }

   try { dir.SetDMS(NSDirection::North, 45, -1, 22.5, EWDirection::East); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTION); }

   try { dir.SetDMS(NSDirection::North, 45, 15, 122.5, EWDirection::East); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTION); }

   try { dir.SetDMS(NSDirection::North, 45, 15, -22.5, EWDirection::East); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_DIRECTION); }


   try { dir.SetDMS(NSDirection::North, 45, 15, 22.5, EWDirection::East); }
   catch (XCoordGeom& ) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5));
   TRY_TESTME(ew == EWDirection::East);

   // Test Azimuth
   try { dir.SetAzimuth(370, 15, 22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(360, 15, 22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(-360, 15, 22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(-370, 15, 22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(45, 60, 22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(45, 90, 22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(45, -15, 22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(45, 15, 60.0); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(45, 15, 90.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }

   try { dir.SetAzimuth(45, 15, -22.5); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_AZIMUTH); }


   try { dir.SetAzimuth(45, 15, 22.5); }
   catch (XCoordGeom& ) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5));
   TRY_TESTME(ew == EWDirection::East);

   try { dir.SetAzimuth(-45, 15, 22.5); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(ns,d,m,s,ew) = dir.GetDMS();
   TRY_TESTME(ns == NSDirection::North);
   TRY_TESTME(d == 45);
   TRY_TESTME(m == 15);
   TRY_TESTME(IsEqual(s, 22.5));
   TRY_TESTME(ew == EWDirection::West);

   // Test AngleBetween
   Direction d1(NSDirection::North, 45, 0, 0, EWDirection::East);
   Direction d2(NSDirection::North, 45, 0, 0, EWDirection::West);
   auto angle = d2.AngleBetween(d1);
   TRY_TESTME(IsEqual(angle.GetValue(), PI_OVER_2));

   angle = d1.AngleBetween(d2);
   TRY_TESTME(IsEqual(angle.GetValue(), 3 * PI_OVER_2));

   angle = d1.AngleBetween(d1);
   TRY_TESTME(IsEqual(angle.GetValue(), 0.0));

   TESTME_EPILOG("Direction");
}
#endif // _UNITTEST
