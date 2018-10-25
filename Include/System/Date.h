///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_DATE_H_
#define INCLUDED_SYSTEM_DATE_H_
#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <System\SysExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class sysTime;


// MISCELLANEOUS
//
typedef Uint16 DayTy;
typedef Uint16 MonthTy;
typedef Uint16 YearTy;
typedef Uint32 JulTy;

static const JulTy jul1901 = 2415386L;  // Julian day for 1/1/1901

/*****************************************************************************
CLASS 
   sysDate

   Utility date class.


DESCRIPTION
   The class may be used for various date-related activities.

LOG
   rdp : 05.04.1997 : Created file
*****************************************************************************/

class SYSCLASS sysDate
{

public:

   // GROUP: ENUMERATIONS
    enum HowToPrint
        {
        Normal,
        Terse,
        Numbers,
        EuropeanNumbers,
        European
        };

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Construct a sysDate with the current date
   sysDate();

   //------------------------------------------------------------------------
   // Construct a sysDate with a given day of the year and a given year.
   // The base date for this computation is Dec. 31 of the previous year.
   // If year == 0, Construct a sysDate with Jan. 1, 1901 as the "day zero".
   // i.e., sysDate(-1,0) = Dec. 31, 1900 and sysDate(1,0) = Jan. 2, 1901.
   // If year is between 00 and 99, 1900 will be added to year.
   sysDate( DayTy day, YearTy year );

   //------------------------------------------------------------------------
   //  Construct a sysDate for the given day, month, and year.
   // If year is between 00 and 99, 1900 will be added to year.
   sysDate( DayTy, LPCTSTR month, YearTy );

   //------------------------------------------------------------------------
   //  Construct a sysDate for the given day, month, and year.
   // If year is between 00 and 99, 1900 will be added to year.
   sysDate( DayTy, MonthTy, YearTy );

   //------------------------------------------------------------------------
   // Read date from stream.
   sysDate( std::_tistream& s );   

   //------------------------------------------------------------------------
   // Construct a sysDate from a sysTime
   sysDate( const sysTime& ); 

   sysDate( JulTy j );

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Date comparisons:
   Int16 operator <  ( const sysDate& date ) const;
   Int16 operator <= ( const sysDate& date ) const;
   Int16 operator >  ( const sysDate& date ) const;
   Int16 operator >= ( const sysDate& date ) const;
   Int16 operator == ( const sysDate& date ) const;
   Int16 operator != ( const sysDate& date ) const;

   //------------------------------------------------------------------------
   // Arithmetic operators:
   JulTy operator - ( const sysDate & dt ) const;
   SYSCLASS friend sysDate  operator + ( const sysDate& dt, Int16 dd );
   SYSCLASS friend sysDate  operator + ( Int16 dd, const sysDate& dt );
   SYSCLASS friend sysDate  operator - ( const sysDate& dt, Int16 dd );
   void operator ++ ();
   void operator -- ();
   void operator += ( Int16 dd );
   void operator -= ( Int16 dd );

   //------------------------------------------------------------------------
   // Read or write dates:
   SYSCLASS friend std::_tostream&  operator << ( std::_tostream& s, const sysDate& d );
   SYSCLASS friend std::_tistream&  operator >> ( std::_tistream& s, sysDate& d );


   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // return date in current format as defined by SetPrintOption
   std::_tstring AsString() const;

   //------------------------------------------------------------------------
   // is date between two other dates
   bool Between( const sysDate& d1, const sysDate& d2 ) const;

   //------------------------------------------------------------------------
   // compare to dates: - if before, 0 if same, + if after
   Int16 CompareTo( const sysDate& ) const;

   //------------------------------------------------------------------------
   // return day of year 1-365
   DayTy Day() const;

   //------------------------------------------------------------------------
   // return day of month 1-31
   DayTy DayOfMonth() const;

   //------------------------------------------------------------------------
   // return first day of month 1-365
   DayTy FirstDayOfMonth() const;

   //------------------------------------------------------------------------
   // return first day of month 1-365
   DayTy FirstDayOfMonth( MonthTy ) const;

   //------------------------------------------------------------------------
   // a unique hash value for the date
   Uint32 Hash() const;

   //------------------------------------------------------------------------
   // is date valid?
   Int16 IsValid() const;

   //------------------------------------------------------------------------
   // is this a leap year?
   bool IsLeapYear() const;

   //------------------------------------------------------------------------
   // is the year a leap year
   static bool IsLeapYear( YearTy year );

   //------------------------------------------------------------------------
   // return the later date
   sysDate Max( const sysDate& dt ) const;

   //------------------------------------------------------------------------
   // return the earlier date
   sysDate Min( const sysDate& dt ) const;

   //------------------------------------------------------------------------
   // return the month 1-12
   MonthTy Month() const;

   //------------------------------------------------------------------------
   // return the days' name
   LPCTSTR NameOfDay() const;

   //------------------------------------------------------------------------
   // return the months' name
   LPCTSTR NameOfMonth() const;

   //------------------------------------------------------------------------
   // Return date of previous dayName
   sysDate Previous( LPCTSTR dayName ) const;

   //------------------------------------------------------------------------
   // Same as above, but use day of week
   sysDate Previous( DayTy ) const;

   //------------------------------------------------------------------------
   // return day of week 1-7
   DayTy WeekDay() const;

   //------------------------------------------------------------------------
   // return year
   YearTy Year() const;


   // Static member functions:
   //------------------------------------------------------------------------
   // get name of day for a given day number
   static LPCTSTR DayName( DayTy weekDayNumber );

   //------------------------------------------------------------------------
   // return day number 1-7 for a given day name
   static DayTy DayOfWeek( LPCTSTR dayName );

   //------------------------------------------------------------------------
   // Is a day (1-31) within a given month?
   static Int16 DayWithinMonth( MonthTy, DayTy, YearTy );

   //------------------------------------------------------------------------
   // how many days in a given year
   static DayTy DaysInYear( YearTy );

   //------------------------------------------------------------------------
   // return the index 1-12 of this month
   static MonthTy IndexOfMonth( LPCTSTR  monthName );

   //------------------------------------------------------------------------
   // return the julian date number
   static JulTy Jday( MonthTy, DayTy, YearTy );

   //------------------------------------------------------------------------
   // return the name of the given month
   static LPCTSTR MonthName( MonthTy monthNumber );

   //------------------------------------------------------------------------
   // set prInt16 format for date
   static HowToPrint SetPrintOption( HowToPrint h );

#if defined _UNITTEST
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:

    static Int16 AssertWeekDayNumber( DayTy d );
    static Int16 AssertIndexOfMonth( MonthTy m );

private:

    JulTy Julnum;                   // Julian Day Number (Not same as Julian date.)
    static HowToPrint PrintOption;  // Printing with different formats

    void ParseFrom( std::_tistream  & );     // Reading dates
    void  Mdy( MonthTy  &, DayTy  &, YearTy  & ) const;

};

// INLINE METHODS
//

inline sysDate::sysDate( std::_tistream& s )
{
    ParseFrom(s);
}

inline bool sysDate::Between( const sysDate& d1, const sysDate& d2 ) const
{
    return Julnum >= d1.Julnum && Julnum <= d2.Julnum;
}

inline DayTy sysDate::FirstDayOfMonth() const
{
    return FirstDayOfMonth(Month());
}

inline Int16 sysDate::IsValid() const
{
    return Julnum>0;
}

inline bool sysDate::IsLeapYear() const
{
    return IsLeapYear(Year());
}

inline LPCTSTR sysDate::NameOfDay() const
{
    return DayName(WeekDay());
}

inline LPCTSTR sysDate::NameOfMonth() const
{
    return MonthName(Month());
}

inline Int16 sysDate::operator < ( const sysDate& date ) const
{
    return Julnum < date.Julnum;
}

inline Int16 sysDate::operator <= ( const sysDate& date ) const
{
    return Julnum <= date.Julnum;
}

inline Int16 sysDate::operator > ( const sysDate& date ) const
{
    return Julnum > date.Julnum;
}

inline Int16 sysDate::operator >= ( const sysDate& date ) const
{
    return Julnum >= date.Julnum;
}

inline Int16 sysDate::operator == ( const sysDate& date ) const
{
    return Julnum == date.Julnum;
}

inline Int16 sysDate::operator != ( const sysDate& date ) const
{
    return Julnum != date.Julnum;
}

inline JulTy sysDate::operator - ( const sysDate& dt ) const
{
    return Julnum - dt.Julnum;
}

SYSCLASS inline sysDate  operator + ( const sysDate& dt, Int16 dd )
{
    return sysDate(dt.Julnum + dd);
}

SYSCLASS inline sysDate  operator + ( Int16 dd, const sysDate& dt )
{
    return sysDate(dt.Julnum + dd);
}

SYSCLASS inline sysDate  operator - ( const sysDate& dt, Int16 dd )
{
    return sysDate(dt.Julnum - dd);
}

inline void sysDate::operator ++ ()
{
    Julnum += 1;
}

inline void sysDate::operator -- ()
{
    Julnum -= 1;
}

inline void sysDate::operator += ( Int16 dd )
{
    Julnum += dd;
}

inline void sysDate::operator -= ( Int16 dd )
{
    Julnum -= dd;
}

SYSCLASS inline std::_tistream&  operator >> ( std::_tistream& s, sysDate& d )
{
    d.ParseFrom(s);
    return s;
}

inline Int16 sysDate::AssertWeekDayNumber( DayTy d )
{
    return d>=1 && d<=7;
}

inline Int16 sysDate::AssertIndexOfMonth( MonthTy m )
{
    return m>=1 && m<=12;
}

inline sysDate::sysDate( JulTy j )
{
    Julnum = j;
}

SYSCLASS inline Uint32 HashValue( sysDate  & d )
{
    return d.Hash();
}


#endif  // INCLUDED_SYSTEM_H_
