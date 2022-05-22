///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#pragma once

#include <System\SysExp.h>
#include <istream>
#include <ostream>
#include <string>


namespace WBFL
{
   namespace System
   {
      class Time;


      typedef Uint16 DayTy;
      typedef Uint16 MonthTy;
      typedef Uint16 YearTy;
      typedef Uint32 JulTy;

      static const JulTy jul1901 = 2415386L;  // Julian day for 1/1/1901

      /// The class may be used for various date-related activities.
      class SYSCLASS Date
      {

      public:
          enum class PrintFormat
              {
              Normal,
              Terse,
              Numbers,
              EuropeanNumbers,
              European
              };

         /// Construct with the current date
         Date();

         /// Construct with a given day of the year and a given year.
         /// The base date for this computation is Dec. 31 of the previous year.
         /// If year == 0, Construct a sysDate with Jan. 1, 1901 as the "day zero".
         /// i.e., sysDate(-1,0) = Dec. 31, 1900 and sysDate(1,0) = Jan. 2, 1901.
         /// If year is between 00 and 99, 1900 will be added to year.
         Date( DayTy day, YearTy year );

         /// Construct for the given day, month, and year.
         /// If year is between 00 and 99, 1900 will be added to year.
         Date( DayTy, LPCTSTR month, YearTy );

         /// Construct forr the given day, month, and year.
         /// If year is between 00 and 99, 1900 will be added to year.
         Date( DayTy, MonthTy, YearTy );

         /// Read date from stream.
         Date( std::_tistream& s );   

         /// Construct from a Time object
         Date( const Time& ); 

         /// Construct from Julean date
         Date( JulTy j );

         Int16 operator< ( const Date& date ) const;
         Int16 operator<=( const Date& date ) const;
         Int16 operator> ( const Date& date ) const;
         Int16 operator>=( const Date& date ) const;
         Int16 operator==( const Date& date ) const;
         Int16 operator!=( const Date& date ) const;

         JulTy operator - ( const Date & dt ) const;
         SYSCLASS friend Date operator + ( const Date& dt, Int16 dd );
         SYSCLASS friend Date operator + ( Int16 dd, const Date& dt );
         SYSCLASS friend Date operator - ( const Date& dt, Int16 dd );
         void operator++();
         void operator--();
         void operator+=( Int16 dd );
         void operator-=( Int16 dd );

         /// return date in current format as defined by SetPrintOption
         std::_tstring AsString() const;

         /// Returns true if this data is between two other dates
         bool Between( const Date& d1, const Date& d2 ) const;

         // compare to dates: - if before, 0 if same, + if after
         Int16 CompareTo(const Date& ) const;

         /// return day of year 1-365
         DayTy Day() const;

         /// return day of month 1-31
         DayTy DayOfMonth() const;

         /// return first day of month 1-365
         DayTy FirstDayOfMonth() const;

         /// return first day of month 1-365
         DayTy FirstDayOfMonth( MonthTy ) const;

         /// a unique hash value for the date
         Uint32 Hash() const;

         /// returns true of the date is valid
         Int16 IsValid() const;

         /// returns true if this date is in a leap year
         bool IsLeapYear() const;

         /// returns true is the year a leap year
         static bool IsLeapYear( YearTy year );

         /// return the later of this date and dt
         Date Max( const Date& dt ) const;

         /// return the earlier of this date and dt
         Date Min(const Date& dt ) const;

         /// return the month 1-12
         MonthTy Month() const;

         /// return the days' name
         LPCTSTR NameOfDay() const;

         /// return the months' name
         LPCTSTR NameOfMonth() const;

         /// Return date of previous dayName
         Date Previous( LPCTSTR dayName ) const;

         /// Same as above, but use day of week
         Date Previous( DayTy ) const;

         /// return day of week 1-7
         DayTy WeekDay() const;

         /// return year
         YearTy Year() const;


         /// get name of day for a given day number
         static LPCTSTR DayName( DayTy weekDayNumber );

         /// return day number 1-7 for a given day name
         static DayTy DayOfWeek( LPCTSTR dayName );

         /// Is a day (1-31) within a given month?
         static Int16 DayWithinMonth( MonthTy, DayTy, YearTy );

         /// returns number of days in the year
         static DayTy DaysInYear( YearTy );

         /// return the index 1-12 of this month
         static MonthTy IndexOfMonth( LPCTSTR  monthName );

         /// return the julian date number
         static JulTy Jday( MonthTy, DayTy, YearTy );

         /// return the name of the given month
         static LPCTSTR MonthName( MonthTy monthNumber );

         /// set print format for date
         static PrintFormat SetPrintFormat(PrintFormat h );
         static PrintFormat GetPrintFormat();

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      protected:

          static Int16 AssertWeekDayNumber( DayTy d );
          static Int16 AssertIndexOfMonth( MonthTy m );

      private:

          JulTy Julnum;                   // Julian Day Number (Not same as Julian date.)
          static PrintFormat DatePrintFormat;  // Printing with different formats

          void ParseFrom( std::_tistream  & );     // Reading dates
          void  Mdy( MonthTy  &, DayTy  &, YearTy  & ) const;

          SYSCLASS friend std::_tostream& operator << (std::_tostream& s, const Date& d);
          SYSCLASS friend std::_tistream& operator >> (std::_tistream& s, Date& d);
      };

      inline Date::Date( std::_tistream& s )
      {
          ParseFrom(s);
      }

      inline bool Date::Between( const Date& d1, const Date& d2 ) const
      {
          return Julnum >= d1.Julnum && Julnum <= d2.Julnum;
      }

      inline DayTy Date::FirstDayOfMonth() const
      {
          return FirstDayOfMonth(Month());
      }

      inline Int16 Date::IsValid() const
      {
          return Julnum>0;
      }

      inline bool Date::IsLeapYear() const
      {
          return IsLeapYear(Year());
      }

      inline LPCTSTR Date::NameOfDay() const
      {
          return DayName(WeekDay());
      }

      inline LPCTSTR Date::NameOfMonth() const
      {
          return MonthName(Month());
      }

      inline Int16 Date::operator < ( const Date& date ) const
      {
          return Julnum < date.Julnum;
      }

      inline Int16 Date::operator <= ( const Date& date ) const
      {
          return Julnum <= date.Julnum;
      }

      inline Int16 Date::operator > ( const Date& date ) const
      {
          return Julnum > date.Julnum;
      }

      inline Int16 Date::operator >= ( const Date& date ) const
      {
          return Julnum >= date.Julnum;
      }

      inline Int16 Date::operator == ( const Date& date ) const
      {
          return Julnum == date.Julnum;
      }

      inline Int16 Date::operator != ( const Date& date ) const
      {
          return Julnum != date.Julnum;
      }

      inline JulTy Date::operator - ( const Date& dt ) const
      {
          return Julnum - dt.Julnum;
      }

      SYSCLASS inline Date  operator + ( const Date& dt, Int16 dd )
      {
          return Date(dt.Julnum + dd);
      }

      SYSCLASS inline Date  operator + ( Int16 dd, const Date& dt )
      {
          return Date(dt.Julnum + dd);
      }

      SYSCLASS inline Date  operator - ( const Date& dt, Int16 dd )
      {
          return Date(dt.Julnum - dd);
      }

      inline void Date::operator ++ ()
      {
          Julnum += 1;
      }

      inline void Date::operator -- ()
      {
          Julnum -= 1;
      }

      inline void Date::operator += ( Int16 dd )
      {
          Julnum += dd;
      }

      inline void Date::operator -= ( Int16 dd )
      {
          Julnum -= dd;
      }

      SYSCLASS inline std::_tistream&  operator >> ( std::_tistream& s, Date& d )
      {
          d.ParseFrom(s);
          return s;
      }

      inline Int16 Date::AssertWeekDayNumber( DayTy d )
      {
          return d>=1 && d<=7;
      }

      inline Int16 Date::AssertIndexOfMonth( MonthTy m )
      {
          return m>=1 && m<=12;
      }

      inline Date::Date( JulTy j )
      {
          Julnum = j;
      }

      SYSCLASS inline Uint32 HashValue( Date  & d )
      {
          return d.Hash();
      }
   };
};
