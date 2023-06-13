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
#include <CoordGeom/Angle.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

#include <System\Tokenizer.h>
#include <MathEx.h>

#include <sstream>
#include <iomanip>

using namespace WBFL::COGO;

Angle::Angle(Float64 angle) : m_Angle(angle)
{
}

Angle::Angle(short deg, unsigned short min, Float64 sec)
{
   m_Angle = COGO::FromDMS(deg, min, sec);
}

Angle::Angle(const std::_tstring& strAngle)
{
   FromString(strAngle);
}

bool Angle::operator==(const Angle& other) const
{
   return IsEqual(m_Angle, other.m_Angle);
}

bool Angle::operator!=(const Angle& other) const
{
   return !operator==(other);
}

void Angle::SetValue(Float64 value)
{
   m_Angle = value;
}

Float64 Angle::GetValue() const
{
   return m_Angle;
}

void Angle::SetDMS(short deg, unsigned short min, Float64 sec)
{
   m_Angle = COGO::FromDMS(deg, min, sec);
}

std::tuple<short,unsigned short,Float64> Angle::GetDMS() const
{
   return COGO::ToDMS(m_Angle);
}

void Angle::FromString(const std::_tstring& strAngle)
{
   // parse into space-delimited tokens
   LPCTSTR delims[] = { _T(" "),_T("\t"), 0 };
   WBFL::System::Tokenizer tokizer(delims);
   tokizer.push_back(strAngle);

   WBFL::System::Tokenizer::size_type nParts = tokizer.size();
   if (nParts < 1 || 4 < nParts)
      THROW_COGO(WBFL_COGO_E_ANGLESTRING);  // string is empty or has too many parts

   if (nParts == 1)
   {
      // String is of the format [+|-]ddd.ddd[R|L]
      // check for R or L
      std::_tstring stmp = tokizer[0];
      std::_tstring::size_type endloc = stmp.length() - 1;
      TCHAR end = stmp[endloc];
      Float64 rlfactor = 1.;
      if (end == _T('R') || end == _T('r') || end == _T('L') || end == _T('l'))
      {
         // can't begin with a - or + sign and have L/R
         if (stmp[0] == _T('+') || stmp[0] == _T('-'))
            THROW_COGO(WBFL_COGO_E_ANGLESTRING);

         if (end == _T('R') || end == _T('r'))
            rlfactor = -1;

         stmp.erase(endloc, endloc);
      }

      Float64 angle;
      if (!WBFL::System::Tokenizer::ParseDouble(stmp.c_str(), &angle))
         THROW_COGO(WBFL_COGO_E_ANGLESTRING);

      angle *= rlfactor;

      m_Angle = ToRadians(angle);
   }
   else if (nParts == 2)
   {
      // String is of the format ddd.ddd [L|R]

      std::_tstring stmp = tokizer[0];

      Float64 angle;
      if (!WBFL::System::Tokenizer::ParseDouble(stmp.c_str(), &angle))
         THROW_COGO(WBFL_COGO_E_ANGLESTRING);

      std::_tstring rl = tokizer[1];
      if (rl == _T("L") || rl == _T("l") || rl == _T("R") || rl == _T("r"))
      {
         // can't begin with a - or + sign
         if (stmp[0] == _T('+') || stmp[0] == _T('-'))
            THROW_COGO(WBFL_COGO_E_ANGLESTRING);

         if (rl == _T("R") || rl == _T("r"))
            angle *= -1;
      }
      else
      {
         THROW_COGO(WBFL_COGO_E_ANGLESTRING);
      }

      m_Angle = ToRadians(angle);
   }
   else if (nParts == 3 || nParts == 4)
   {
      // String is of the format [+|-]ddd mm ss.s or ddd mm ss.s [L|R]
      std::_tstring stmp = tokizer[0];

      // deal with [L|R]
      std::_tstring rl = tokizer[nParts - 1];

      short rlfactor = 0;
      if (rl == _T("L") || rl == _T("l") || rl == _T("R") || rl == _T("r"))
      {
         // can't begin with a - or + sign
         if (stmp[0] == _T('+') || stmp[0] == _T('-'))
            THROW_COGO(WBFL_COGO_E_ANGLESTRING);

         rlfactor = (rl == _T("R") || rl == _T("r")) ? -1 : 1;
      }
      else if (nParts == 4)
      {
         // we are expecting L|R
         THROW_COGO(WBFL_COGO_E_ANGLESTRING);
      }

      // ddd
      short deg;
      LPCTSTR lpszDeg = stmp.c_str();
      Float64 sign = 1;
      if (lpszDeg[0] == _T('-'))
      {
         // the angle is signed...
         sign = -1;
         lpszDeg++;
      }

      if (!WBFL::System::Tokenizer::ParseShort(lpszDeg, &deg))
         THROW_COGO(WBFL_COGO_E_ANGLESTRING);

      deg = abs(deg); // make sure deg is unsigned because we will be multiplying it by "sign" below

      // mm
      unsigned short min;
      stmp = tokizer[1];
      if (!WBFL::System::Tokenizer::ParseUShort(stmp.c_str(), &min))
         THROW_COGO(WBFL_COGO_E_ANGLESTRING);

      // sss.s
      Float64 sec = 0.0;
      // only parse seconds if they exist
      if (rlfactor == 0 || nParts == 4)
      {
         stmp = tokizer[2];
         if (!WBFL::System::Tokenizer::ParseDouble(stmp.c_str(), &sec))
            THROW_COGO(WBFL_COGO_E_ANGLESTRING);
      }


      try
      {
         SetDMS(deg, min, sec);
      }
      catch (...)
      {
         THROW_COGO(WBFL_COGO_E_ANGLESTRING);
      }

      m_Angle *= sign;

      if (rlfactor != 0)
      {
         m_Angle *= rlfactor;
      }
   }
}

std::_tstring Angle::AsString(const std::_tstring& strFormat, bool bSigned, bool bCondensed) const
{
   Float64 value = m_Angle;
   if (IsZero(value))  value = 0.0;

   value = COGO::NormalizeAngle(value);

   std::_tstring strDegTag, strMinTag, strSecTag;
   std::tie(strDegTag,strMinTag,strSecTag) = COGO::ParseAngleTags(strFormat);

   short deg;
   unsigned short min;
   Float64 sec;
   std::tie(deg, min, sec) = COGO::ToDMS(value);

   std::_tostringstream os;
   os << (bSigned ? deg : abs(deg)) << strDegTag;

   if (bCondensed == false || (0 < min || 0 < sec))
   {
      os << _T(" ") << std::setw(2) << std::setfill(_T('0')) << min << strMinTag;
      os << _T(" ") << std::setw(5) << std::setfill(_T('0')) << std::showpoint << std::fixed << std::setprecision(2) << (IsZero(sec) ? 0 : sec) << strSecTag;
   }

   if (!bSigned)
   {
      TCHAR dir;
      dir = (value < 0) ? 'R' : 'L';
      os << _T(" ") << dir;
   }

   os << std::ends;

   return os.str();
}

Angle& Angle::Increment(const Angle& increment)
{
   m_Angle += increment.m_Angle;
   return *this;
}

Angle Angle::IncrementBy(const Angle& increment) const
{
   return Angle(m_Angle + increment.m_Angle);
}

void Angle::Normalize()
{
   m_Angle = COGO::NormalizeAngle(m_Angle);
}


#if defined _UNITTEST
bool Angle::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Angle");

   Angle angle;
   TRY_TESTME(IsZero(angle.GetValue())); // test default value
   
   // Test setting values
   angle.SetValue(10.0);
   TRY_TESTME(IsEqual(angle.GetValue(), 10.0));

   // Test DMS
   try { angle.SetDMS(-14, 60, 13.5); } // Invalid minutes
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLE); }

   try { angle.SetDMS(-14, 65, 13.5); } // Invalid minutes
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLE); }

   //try { angle.SetDMS(-14, -10, 13.5); } // Invalid minutes (generates compiler warning C4244)
   //catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLE); }

   try { angle.SetDMS(-14, 25, 60.0); } // Invalid seconds
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLE); }

   try { angle.SetDMS(-14, 25, -10.0); } // Invalid seconds
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLE); }

   try { angle.SetDMS(-14, 25, 13.5); } // Valid angle
   catch (XCoordGeom& ) { TRY_TESTME(false); } // should not get here

   short d;
   unsigned short m;
   Float64 s;
   std::tie(d,m,s) = angle.GetDMS();
   TRY_TESTME(d == -14);
   TRY_TESTME(m == 25);
   TRY_TESTME(IsEqual(s,13.5));

   // Test Normalize
   angle.SetValue(-2 * TWO_PI);
   angle.Normalize();
   TRY_TESTME(IsZero(angle.GetValue()));

   angle.SetValue(2 * TWO_PI);
   angle.Normalize();
   TRY_TESTME(IsZero(angle.GetValue()));

   angle.SetValue(TWO_PI);
   angle.Normalize();
   TRY_TESTME(IsZero(angle.GetValue()));

   angle.SetValue(1.25 * TWO_PI);
   angle.Normalize();
   TRY_TESTME(IsEqual(angle.GetValue(), PI_OVER_2));

   angle.SetValue(-1.25 * TWO_PI);
   angle.Normalize();
   TRY_TESTME(IsEqual(angle.GetValue(), 3*PI_OVER_2));

   // Test FromString
   try { angle.FromString(_T("")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("                 ")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("A")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("+12.5 L")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("-12.5 L")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("+12.5 R")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("-12.5 R")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("x12.5 L")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12.5 LR")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12.5 x")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("DD 13 14.15")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 MM 14.15")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 13 SS.ss")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 -10 14.15")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 60 14.15")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 65 14.15")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 13 -14.15")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 13 60.00")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 13 65.00")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 13 14.15 LR")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("12 13 14.15 x")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("-12 13 14.15 L")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("+12 13 14.15 L")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("-12 13 14.15 R")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   try { angle.FromString(_T("+12 13 14.15 R")); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_ANGLESTRING); }

   // these should work
   try { angle.FromString(_T("12 13 R")); }
   catch (XCoordGeom& ) { TRY_TESTME(false); }
   std::tie(d,m,s) = angle.GetDMS();
   TRY_TESTME(d == -12);
   TRY_TESTME(m == 13);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)*(fabs(d) + m / 60.))));

   try { angle.FromString(_T("12 13 L")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 13);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("12.5")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("-12.5")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == -12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("12.5 L")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("12.5 R")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == -12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("12.5 l")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("12.5 r")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == -12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("               12.5 L")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("12.5 L                 ")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("         12.5 L           ")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 30);
   TRY_TESTME(IsZero(s));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60.))));

   try { angle.FromString(_T("12 13 14.15 L")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 13);
   TRY_TESTME(IsEqual(s,14.15));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60. + s / 3600.))));

   try { angle.FromString(_T("12 13 14.15 R")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == -12);
   TRY_TESTME(m == 13);
   TRY_TESTME(IsEqual(s, 14.15));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60. + s / 3600.))));

   try { angle.FromString(_T("12 13 14.15")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 13);
   TRY_TESTME(IsEqual(s, 14.15));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60. + s / 3600.))));

   try { angle.FromString(_T("+12 13 14.15")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 12);
   TRY_TESTME(m == 13);
   TRY_TESTME(IsEqual(s, 14.15));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60. + s / 3600.))));

   try { angle.FromString(_T("-12 13 14.15")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == -12);
   TRY_TESTME(m == 13);
   TRY_TESTME(IsEqual(s, 14.15));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60. + s / 3600.))));

   try { angle.FromString(_T("00 00 14.15")); }
   catch (XCoordGeom&) { TRY_TESTME(false); }
   std::tie(d, m, s) = angle.GetDMS();
   TRY_TESTME(d == 0);
   TRY_TESTME(m == 0);
   TRY_TESTME(IsEqual(s, 14.15));
   TRY_TESTME(IsEqual(angle.GetValue(), ToRadians(BinarySign(d)* (fabs(d) + m / 60. + s / 3600.))));

   // Test Increment and IncrementBy
   angle.SetValue(0.0);
   angle.Increment(PI_OVER_2);
   TRY_TESTME(IsEqual(angle.GetValue(), PI_OVER_2));

   auto incremented_angle = angle.IncrementBy(PI_OVER_2);
   TRY_TESTME(IsEqual(incremented_angle.GetValue(), M_PI));
   TRY_TESTME(IsEqual(angle.GetValue(), PI_OVER_2));

   TESTME_EPILOG("Angle");
}
#endif // _UNITTEST


