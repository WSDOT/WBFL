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
   cogoDirection
****************************************************************************/

#include <Cogo\CogoDirection.h>        // class implementation
#include <Cogo\CogoAngle.h>
#include <Cogo\CogoHelpers.h>
#include <MathEx.h>
#include <Algorithm>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <system\tokenizer.h>

const cogoDirection COGOFUNC operator+(const cogoDirection& dir,const cogoAngle& angle)
{
   cogoDirection d(dir);
   d += angle;
   return d;
}

const cogoDirection COGOFUNC operator-(const cogoDirection& dir,const cogoAngle& angle)
{
   cogoDirection d(dir);
   d -= angle;
   return d;
}

const cogoAngle COGOFUNC operator-(const cogoDirection& dir1,const cogoDirection& dir2)
{
   cogoAngle angle( dir1.AsFloat64() - dir2.AsFloat64() );
   angle.Normalize();
   return angle;
}


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
cogoDirection::cogoDirection()
{
   m_Direction = 0;
}

cogoDirection::cogoDirection(Int8 n,Uint16 deg,Uint16 min,Float64 sec,Int8 e)
{
   m_Direction = cogoDirection::BearingToDBearing( n, deg, min, sec, e );
   ASSERTVALID;
}

cogoDirection::cogoDirection(Int16 deg,Uint16 min,Float64 sec)
{
   m_Direction = cogoDirection::AzimuthToDAzimuth( deg, min, sec );
   ASSERTVALID;
}

cogoDirection::cogoDirection(const cogoAngle& rAzimuth)
{
   m_Direction = rAzimuth.AsFloat64();
   ASSERTVALID;
}

cogoDirection::cogoDirection(Float64 direction)
{
   m_Direction = direction;
   Normalize();
   ASSERTVALID;
}

cogoDirection::cogoDirection(const cogoDirection& rOther)
{
   MakeCopy(rOther);
}

cogoDirection::~cogoDirection()
{
}

//======================== OPERATORS  =======================================
cogoDirection& cogoDirection::operator= (const cogoDirection& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

cogoDirection& cogoDirection::operator = (Float64 direction)
{
   m_Direction = direction;
   Normalize();
   return *this;
}

bool cogoDirection::operator == (const cogoDirection& rOther) const
{
   return IsEqual( m_Direction, rOther.AsFloat64() );
}

bool cogoDirection::operator != (const cogoDirection& rOther) const
{
   return !(*this == rOther);
}

bool cogoDirection::operator < (const cogoDirection& rOther) const
{
   return m_Direction < rOther.AsFloat64();
}

cogoDirection& cogoDirection::operator+=(const cogoAngle& angle)
{
   return Increment( angle );
}

cogoDirection& cogoDirection::operator-=(const cogoAngle& angle)
{
   return Increment( -angle );
}


cogoDirection& cogoDirection::Increment(const cogoAngle& angle)
{
   m_Direction += angle.AsFloat64();
   Normalize();
   ASSERTVALID;
   return *this;
}

cogoDirection cogoDirection::IncrementBy(const cogoAngle& angle) const
{
   cogoDirection dir( *this );
   dir += angle;
   ASSERTVALID;
   return dir;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
Float64 cogoDirection::AsFloat64() const
{
   ASSERTVALID;
   return m_Direction;
}

std::string cogoDirection::AsBearingString(bool bFull,bool bSymbols) const
{
   Int8 n,e;
   Uint16 deg;
   Uint16 min;
   Float64 sec;

   std::stringstream s;
   cogoDirection::DBearingToBearing( m_Direction, n, deg, min, sec, e );
   Int16 prec = 1;
   sec = IsZero(sec) ? 0 : sec;
   s << std::setw(1) << n << " " 
     << std::setw(2) << std::setfill('0') << deg;

   if ( bSymbols )
      s << "°";

   if ( bFull || ( min != 0 || sec != 0 ) )
   {
      s << " " << std::setw(2) << std::setfill('0') << min;
      s << ( bSymbols ? "' " : " ");
      s << std::setw(4) << std::setfill('0') << std::showpoint << std::fixed << std::setprecision(prec) << sec;
      s << ( bSymbols ? "\"" : "");
   }

   s << " " << std::setw(1) << e << std::ends;
   ASSERTVALID;
   return s.str();
}

std::string cogoDirection::AsAzimuthString(bool bSymbols) const
{
   std::string str;
   AsDmsString( str, bSymbols );
   ASSERTVALID;
   return str;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void cogoDirection::MakeCopy(const cogoDirection& rOther)
{
   m_Direction = rOther.AsFloat64();
}

void cogoDirection::MakeAssignment(const cogoDirection& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void cogoDirection::Normalize()
{
   do
   {
      if ( m_Direction < 0 )
         m_Direction += TWO_PI;

      if ( m_Direction > TWO_PI )
         m_Direction -= TWO_PI;
   } while ( m_Direction < 0 || TWO_PI < m_Direction );
}

void cogoDirection::DBearingToBearing(Float64 dir,Int8& n,Uint16& deg,Uint16& min,Float64& sec,Int8& e)
{
   if ( dir < 0 )
      dir += TWO_PI;

   n = InRange( 0., dir, PI_OVER_2 ) || InRange( 1.5*M_PI, dir, TWO_PI) ? 'N' : 'S';
   e = InRange( 0., dir, M_PI ) ? 'E' : 'W';

   if ( InRange( PI_OVER_2, dir, M_PI ) )
      dir = M_PI - dir;
   else if ( InRange( PI_OVER_2, dir, 3*PI_OVER_2) )
      dir -= M_PI;
   else if ( InRange( 3*PI_OVER_2, dir, TWO_PI ) )
      dir = TWO_PI - dir;

   Int16 temp_deg;
   cogoUtil::ToDMS( dir, &temp_deg, &min, &sec );
   deg = temp_deg;

}

bool cogoDirection::BearingFromString(const char* str,cogoDirection* pDir)
{
   if ( pDir == 0 )
      return false;

   Int8 cY;
   Int8 cX;
   Uint16 deg=0;
   Uint16 min=0;
   Float64 sec=0;

   std::string strDir( str );

   // Trim the whitespace off both ends
   std::string::size_type last_leading_space   = strDir.find_first_not_of(" ");
   if ( last_leading_space == std::string::npos )
      return false; // string is all spaces
   std::string::size_type cChar;
   cChar = last_leading_space;  // number of characters to remove
   strDir.erase( 0, cChar );

   std::string::size_type first_trailing_space = strDir.find_last_not_of(" ");
   cChar = strDir.length() - first_trailing_space - 1;
   strDir.erase( first_trailing_space+1, cChar );

   if ( strDir.size() == 0 )
      return false; // string is empty

   // Lets start breaking apart the string
   cY = toupper( strDir[0] );
   if ( cY != 'N' && cY != 'S' )
      return false;

   cX = toupper( strDir[strDir.size()-1] );
   if ( cX != 'E' && cX != 'W' )
      return false;

   strDir.erase( strDir.size()-1, 1 );
   strDir.erase( 0, 1 );

   const char *delims[] = {" ","\t", 0};
   sysTokenizer tokizer(delims);
   tokizer.push_back(strDir);

   sysTokenizer::size_type size = tokizer.size();
   if (size>3 || size<1)
      return false;

   // Get the degrees
   std::string stmp = tokizer[0];
   long ltmp;
   if (!sysTokenizer::ParseLong(stmp.c_str(), &ltmp))
      return false;

   if (ltmp>90 || ltmp<0) 
      return false;

   deg = (Uint16)ltmp;

   // minutes
   if (size>1)
   {
      stmp = tokizer[1];
      if (!sysTokenizer::ParseLong(stmp.c_str(), &ltmp))
         return false;

      if (ltmp>60 || ltmp<0) 
         return false;

      min = (Uint16)ltmp;
   }

   // seconds
   if (size==3)
   {
      stmp = tokizer[2];
      if (!sysTokenizer::ParseDouble(stmp.c_str(), &sec))
         return false;

      if (sec>60.0 || sec<0.0) 
         return false;
   }

   // check that total is not more than 90 degrees
   Float64 ang = deg + (Float64)min/60.0 + sec/3600.0;
   if (ang>90.0)
      return false;

   *pDir = cogoDirection( cY, deg, min, sec, cX );
   return true;
}

Float64 cogoDirection::BearingToDBearing(Int8 n,Uint16 deg,Uint16 min,Float64 sec,Int8 e)
{
   n = toupper(n);
   e = toupper(e);

   PRECONDITION( n == 'N' || n == 'S');
   PRECONDITION( e == 'E' || e == 'W');
   PRECONDITION( 0 <= deg );
   PRECONDITION( 0 <= min && min <= 60 );
   PRECONDITION( InRange(0.,sec,60.) );

   Float64 angle;
   Float64 sign;

   // Convert component parts to a decimal angle (radians)
   if( n == 'N' && e == 'E')
   {
      angle = 0.;
      sign  = 1.;
   }
   else if (n == 'S' && e == 'W')
   {
      angle = M_PI;
      sign  = 1.;
   }
   else if (n == 'S' && e == 'E')
   {
      angle = M_PI;
      sign  = -1.;
   }
   else if (n == 'N' && e == 'W')
   {
      angle = TWO_PI;
      sign  = -1;
   }
   else
      CHECK(false);

   angle += sign * cogoUtil::FromDMS(deg,min,sec);

   if ( IsEqual( angle, TWO_PI ) )
      angle = 0;

   return angle;
}

Float64 cogoDirection::AzimuthToDAzimuth(Int16 deg,Uint16 min,Float64 sec)
{
   return cogoUtil::FromDMS(deg, min, sec);;
}

void cogoDirection::DAzimuthToAzimuth(Float64 angle,Int16& deg,Uint16& min,Float64& sec)
{
   cogoUtil::ToDMS(angle, &deg, &min, &sec);
}

void cogoDirection::AsDmsString(std::string& str,bool bSymbols) const
{
   ASSERTVALID;
   Int16 deg;
   Uint16 min;
   Float64 sec;
   std::stringstream s;
   cogoUtil::ToDMS( m_Direction, &deg, &min, &sec );
   s << std::setw(2) << deg;
   s << (bSymbols ? "°" : " ");
   s << std::setw(2) << std::setfill('0') << min;
   s << (bSymbols ? "' " : " ");
   s << std::setw(4) << std::showpoint << std::setprecision(1) << (IsZero(sec) ? 0. : sec );
   if ( bSymbols )
      s << "\""; 
   s << std::ends;
   str = s.str();
}
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool cogoDirection::AssertValid() const
{
   if (m_Direction < 0)
	   return false;

   if (m_Direction > TWO_PI)
	   return false;

   return true;
}

void cogoDirection::Dump(dbgDumpContext& os) const
{
   ASSERTVALID;
   os << "Dump for cogoDirection - Not Implemented" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool cogoDirection::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoDirection");
#pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for cogoDirection");

   // Tests for BearingFromString
   cogoDirection dir;
   std::string str;
   bool bRetVal;

   str = "N 23 W";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('N', 23, 0, 0, 'W') );

   str = "S 23 W";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('S', 23, 0, 0, 'W') );

   str = "N 23 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('N', 23, 0, 0, 'E') );

   str = "S 23 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('S', 23, 0, 0, 'E') );

   str = "N 23 10 10 W";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('N', 23, 10, 10, 'W') );

   str = "S 23 10 10 W";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('S', 23, 10, 10, 'W') );

   str = "N 23 10 10 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('N', 23, 10, 10, 'E') );

   str = "S 23 10 10 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('S', 23, 10, 10, 'E') );

   str = "    S 23 10 10 E   ";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('S', 23, 10, 10, 'E') );

   str = "s 23 10 10 e";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( dir == cogoDirection('S', 23, 10, 10, 'E') );

   str = "ABCDEFG";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   str = "N ab 10 10 e";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   str = "N ab E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   str = "k 10 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   str = "N 10 l";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   str = "N 99 10 10 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   str = "N 10 99 10 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   str = "N 10 10 99 E";
   bRetVal = cogoDirection::BearingFromString( str.c_str(), &dir );
   TRY_TESTME( bRetVal == false );

   bRetVal = cogoDirection::BearingFromString( str.c_str(), 0 );
   TRY_TESTME( bRetVal == false );

   // Test equivalent directions
   TRY_TESTME( cogoDirection('N', 0,0,0,'W') == cogoDirection('N', 0,0,0,'E') );
   TRY_TESTME( cogoDirection('S', 0,0,0,'W') == cogoDirection('S', 0,0,0,'E') );
   TRY_TESTME( cogoDirection('N',90,0,0,'W') == cogoDirection('S',90,0,0,'W') );
   TRY_TESTME( cogoDirection('N',90,0,0,'E') == cogoDirection('S',90,0,0,'E') );

   // test BearingToDBearing
   // should return an angle from due north, where positive is CW.
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('N', 0,0,0,'E'), 0.0 ) );
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('N',90,0,0,'E'), PI_OVER_2 ) );
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('S', 0,0,0,'W'), M_PI ) );
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('S',90,0,0,'W'), 3.0 * PI_OVER_2 ) );
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('N',45,0,0,'E'), 1.0 * M_PI / 4.0 ) );
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('S',45,0,0,'E'), 3.0 * M_PI / 4.0 ) );
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('S',45,0,0,'W'), 5.0 * M_PI / 4.0 ) );
   TRY_TESTME( IsEqual( cogoDirection::BearingToDBearing('N',45,0,0,'W'), 7.0 * M_PI / 4.0 ) );

   // Test math operators
   TRY_TESTME( cogoAngle( 30,0,0) == (cogoDirection('N',10,0,0,'E') - cogoDirection('N',20,0,0,'W')) );
   TRY_TESTME( cogoAngle(330,0,0) == (cogoDirection('N',20,0,0,'W') - cogoDirection('N',10,0,0,'E')) );
   TRY_TESTME( cogoDirection('N',45,0,0,'E') == (cogoDirection('N',0,0,0,'E') + cogoAngle(45,0,0)) );
   TRY_TESTME( cogoDirection('N',45,0,0,'W') == (cogoDirection('N',0,0,0,'E') - cogoAngle(45,0,0)) );

   // Test Normalization
   TRY_TESTME( IsEqual( cogoDirection( 47.1238898037).AsFloat64(), M_PI) );
   TRY_TESTME( IsEqual( cogoDirection(-47.1238898037).AsFloat64(), M_PI) );


   TESTME_EPILOG("cogoDirection");
}
#endif