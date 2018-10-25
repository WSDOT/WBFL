///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Cogo\CogoLib.h>

/****************************************************************************
CLASS
   cogoAngle
****************************************************************************/

#include <Cogo\CogoAngle.h>        // class implementation
#include <Cogo\CogoHelpers.h>
#include <Units\SysUnits.h>
#include <System\Tokenizer.h>
#include <MathEx.h>
#include <algorithm>
#include <strstream>
#include <iomanip>


bool COGOFUNC operator == (const cogoAngle& a,const cogoAngle& b)
{
   return IsEqual( a.AsFloat64(), b.AsFloat64() );
}

bool COGOFUNC operator != (const cogoAngle& a,const cogoAngle& b)
{
   return !operator==(a,b);
}

bool COGOFUNC operator  > (const cogoAngle& a,const cogoAngle& b)
{
   return (a.AsFloat64() > b.AsFloat64());
}

bool COGOFUNC operator  < (const cogoAngle& a,const cogoAngle& b)
{
   return (a.AsFloat64() < b.AsFloat64());
}

bool COGOFUNC operator >= (const cogoAngle& a,const cogoAngle& b)
{
   return ( (a.AsFloat64() > b.AsFloat64()) || IsEqual(a.AsFloat64(),b.AsFloat64()) );
}

bool COGOFUNC operator <= (const cogoAngle& a,const cogoAngle& b)
{
   return ( (a.AsFloat64() < b.AsFloat64()) || IsEqual(a.AsFloat64(),b.AsFloat64()) );
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
cogoAngle::cogoAngle(Float64 angle)
{
   m_Angle = angle;
}

cogoAngle::cogoAngle(Int16 deg,Uint16 min,Float64 sec)
{
   m_Angle = cogoUtil::FromDMS( deg, min, sec );
}

cogoAngle::cogoAngle(Uint16 deg, Uint16 min,Float64 sec,Int8 dir)
{
   m_Angle = (toupper(dir) == 'L' ? -1 : 1) * cogoUtil::FromDMS(deg,min,sec);
}

cogoAngle::cogoAngle(const cogoAngle& rOther)
{
   MakeCopy(rOther);
}

cogoAngle::~cogoAngle()
{
}

//======================== OPERATORS  =======================================
cogoAngle& cogoAngle::operator= (const cogoAngle& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

cogoAngle& cogoAngle::operator = (Float64 angle)
{
   m_Angle = angle;
   return *this;
}

cogoAngle cogoAngle::operator+(const cogoAngle& rOther) const
{
   return cogoAngle( m_Angle + rOther.AsFloat64() );
}

cogoAngle cogoAngle::operator-(const cogoAngle& rOther) const
{
   return cogoAngle( m_Angle - rOther.AsFloat64() );
}

cogoAngle cogoAngle::operator*(Float64 scalar) const
{
   return cogoAngle( m_Angle * scalar );
}

cogoAngle cogoAngle::operator/(Float64 scalar) const
{
   return cogoAngle( m_Angle / scalar );
}

cogoAngle& cogoAngle::operator+=(const cogoAngle& rOther)
{
   m_Angle += rOther.AsFloat64();
   return *this;
}

cogoAngle& cogoAngle::operator-=(const cogoAngle& rOther)
{
   m_Angle -= rOther.AsFloat64();
   return *this;
}

cogoAngle& cogoAngle::operator*=(Float64 scalar)
{
   m_Angle *= scalar;
   return *this;
}

cogoAngle& cogoAngle::operator/=(Float64 scalar)
{
   m_Angle /= scalar;
   return *this;
}

cogoAngle cogoAngle::operator-() const
{
   return cogoAngle( -m_Angle );
}

//======================== OPERATIONS =======================================
void cogoAngle::Normalize()
{
   do
   {
      if ( m_Angle < 0 )
         m_Angle += TWO_PI;

      if ( m_Angle >= TWO_PI )
         m_Angle -= TWO_PI;

   } while ( m_Angle < 0 || TWO_PI < m_Angle );
}

//======================== ACCESS     =======================================
void cogoAngle::SetAngle(Float64 angle)
{
   m_Angle = angle;
}

void cogoAngle::SetAngle(Int16 deg,Uint16 min,Float64 sec)
{
   m_Angle = cogoUtil::FromDMS( deg, min, sec );
}

Float64 cogoAngle::AsFloat64() const
{
   return m_Angle;
}

std::string cogoAngle::AsString(bool bSigned,bool bFull,bool bSymbols) const
{
   Int16 deg;
   Uint16 min;
   Float64 sec;
   Int8 dir;

   dir = (m_Angle < 0) ? 'L' : 'R';
   cogoUtil::ToDMS( m_Angle, &deg, &min, &sec );

   std::stringstream s;
   s << std::setw(2) << std::setfill('0') << (bSigned ? deg : abs(deg));

   if ( bSymbols )
      s << "°";

   if ( bFull || (min != 0 || sec != 0 ) )
   {
      s << " " << std::setw(2) << std::setfill('0') << min << (bSymbols ? "' " : " ")
        << std::setw(4) << std::setfill('0') << std::showpoint << std::fixed << std::setprecision(1) << (IsZero(sec) ? 0. : sec );
      if ( bSymbols ) 
         s << "\"";
   }

   if ( !bSigned )
     s << " " << dir;

   return s.str();
}

bool cogoAngle::AngleFromString(const char* str,cogoAngle* pCogoAngle)
{
   CHECK(pCogoAngle!=0);
   if ( pCogoAngle == 0 )
      return false;

   // parse into space-delimited tokens
   const char *delims[] = {" ","\t", 0};
   sysTokenizer tokizer(delims);
   tokizer.push_back(str);

   sysTokenizer::size_type nParts = tokizer.size();
   if (nParts>4 || nParts<1)
      return false;  // string is empty or has too many parts

   if ( nParts == 1 )
   {
      // String is of the format [+|-]ddd.ddd[R|L]
      // check for R or L
      std::string stmp = tokizer[0];
      int endloc = stmp.length()-1;
      char end = stmp[endloc];
      Float64 rlfactor=1.;
      if (end=='R' || end=='r' || end=='L' || end=='l')
      {
         // can't begin with a - or + sign
         if ( stmp[0] == '+' || stmp[0] == '-' )
            return false;

         if (end=='L' || end=='l')
            rlfactor = -1;

         stmp.erase(endloc,endloc);
      }

      Float64 angle;
      if (!sysTokenizer::ParseDouble(stmp.c_str(),&angle))
         return false;

      angle *=rlfactor;

      *pCogoAngle = ::Convert(angle,unitMeasure::Degree,unitMeasure::Radian);
   }
   else if ( nParts == 2 )
   {
      // String is of the format ddd.ddd [L|R]

      std::string stmp = tokizer[0];

      // can't begin with +|- sign
      if ( stmp[0] == '+' || stmp[0] == '-' )
         return false;

      Float64 angle;
      if (!sysTokenizer::ParseDouble(stmp.c_str(),&angle))
         return false;

      stmp = tokizer[1];
      if (stmp=="L" || stmp=="l" || stmp=="R" || stmp=="r")
      {
         if (stmp=="L" || stmp=="l")
            angle *= -1;
      }
      else 
         return false;

      *pCogoAngle = ::Convert(angle,unitMeasure::Degree,unitMeasure::Radian);
   }
   else if ( nParts == 3 || nParts == 4)
   {
      // String is of the format [+|-]ddd mm ss.s or ddd mm ss.s [L|R]
	   Int16 deg;
	   Uint16 min;
	   Float64 sec;

      std::string stmp = tokizer[0];

      // deal with [L|R]
      Float64 rlfactor = 1;
      if (nParts==4)
      {
         // can't begin with +|- sign
         if ( stmp[0] == '+' || stmp[0] == '-' )
            return false;

         std::string rl = tokizer[3];
         if (rl=="L" || rl=="l" || rl=="R" || rl=="r")
         {
            if (rl=="L" || rl=="l")
               rlfactor=-1;
         }
         else
            return false;
      }

      // ddd
      long ltmp;
      if (!sysTokenizer::ParseLong(stmp.c_str(),&ltmp))
         return false;

      deg = (Int16)ltmp;

      // mm
      stmp = tokizer[1];
      if (!sysTokenizer::ParseLong(stmp.c_str(),&ltmp))
         return false;

      if (ltmp<0 || ltmp>60)
         return false;

      min = (Uint16)ltmp;

      // sss.s
      stmp = tokizer[2];
      if (!sysTokenizer::ParseDouble(stmp.c_str(),&sec))
         return false;

      if (0>sec || sec>60)
         return false;

      Float64 angle = cogoUtil::FromDMS( deg, min, sec ) * rlfactor;
      *pCogoAngle = angle;
   }

   return true;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void cogoAngle::MakeCopy(const cogoAngle& rOther)
{
   m_Angle = rOther.AsFloat64();
}

void cogoAngle::MakeAssignment(const cogoAngle& rOther)
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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool cogoAngle::AssertValid() const
{
   return true;
}

void cogoAngle::Dump(dbgDumpContext& os) const
{
   os << "Dump for cogoAngle - Not Implemented" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool cogoAngle::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoAngle");
#pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for cogoAngle");

   /////////////////////////////////////////////////////////////////
   // Unit tests for cogoAngle::AngleFromString
   //
   cogoAngle angle;
   std::string str;
   bool bRetVal;

   str = "12";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle( ::Convert(12.0,unitMeasure::Degree,unitMeasure::Radian) ) );

   str = "+12";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(::Convert(12.0,unitMeasure::Degree,unitMeasure::Radian)) );

   str = "-12";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(::Convert(-12.0,unitMeasure::Degree,unitMeasure::Radian)) );

   str = "12 12 12";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(12,12,12) );

   str = "+12 12 12";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(12,12,12) );

   str = "-12 12 12";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(-12,12,12) );

   str = "12 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(::Convert(-12.0,unitMeasure::Degree,unitMeasure::Radian)) );

   str = "12 l";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(::Convert(-12.0,unitMeasure::Degree,unitMeasure::Radian)) );

   str = "12 R";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(::Convert(12.0,unitMeasure::Degree,unitMeasure::Radian)) );

   str = "12 r";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(::Convert(12.0,unitMeasure::Degree,unitMeasure::Radian)) );

   str = "12 12 12 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(-12,12,12) );

   str = "12 12 12 l";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(-12,12,12) );

   str = "12 12 12 R";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(12,12,12) );

   str = "12 12 12 r";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(12,12,12) );

   str = "     12 12 12 R    ";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( angle == cogoAngle(12,12,12) );

   str = "AB CD EFG";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "99 -6 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "99 10 -6 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "99 99 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "99 10 99 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "+12 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "-12 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "12 12";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "-A";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "A L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "-0 0A 00";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "0 A0 00 L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "12 12 12 k";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "              ";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   str = "12 12 ab L";
   bRetVal = cogoAngle::AngleFromString( str.c_str(), &angle );
   TRY_TESTME( bRetVal == false );

   // Test Normalization
   cogoAngle a(47.1238898037);
   a.Normalize();
   TRY_TESTME( IsEqual( a.AsFloat64(), M_PI) );
   a = -47.1238898037;
   a.Normalize();
   TRY_TESTME( IsEqual( a.AsFloat64(), M_PI) );


   // Test AsString
   TRY_TESTME( cogoAngle( 10,0,0).AsString(false,true)  == std::string("10 00 00.0 R") );
   TRY_TESTME( cogoAngle(-10,0,0).AsString(false,true)  == std::string("10 00 00.0 L") );
   TRY_TESTME( cogoAngle( 10,0,0).AsString(false,false) == std::string("10 R") );
   TRY_TESTME( cogoAngle(-10,0,0).AsString(false,false) == std::string("10 L") );

   TRY_TESTME( cogoAngle( 10,0,0).AsString(true,true)  == std::string("10 00 00.0") );
   TRY_TESTME( cogoAngle(-10,0,0).AsString(true,true)  == std::string("-10 00 00.0") );
   TRY_TESTME( cogoAngle( 10,0,0).AsString(true,false) == std::string("10") );
   TRY_TESTME( cogoAngle(-10,0,0).AsString(true,false) == std::string("-10") );

   TESTME_EPILOG("cogoAngle");
}
#endif