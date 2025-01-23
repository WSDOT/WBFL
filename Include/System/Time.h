///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <System\Date.h>
#include <istream>
#include <ostream>
#include <string>

namespace WBFL
{
   namespace System
   {
      class Time;

      using HourTy = Uint16;
      using MinuteTy = Uint16;
      using SecondTy = Uint16;
      using ClockTy = Uint32;

      static const Uint32 secFrom_Jan_1_1901_to_Jan_1_1970 = 2177452800L;

      /// The class may be used for various Time-related activities.
      class SYSCLASS Time
      {

      public:
          /// Construct with the current time
          Time();

          /// Construct with the Seconds since Jan 1, 1901.
          Time( ClockTy s ); 

          /// construct an explicit time
          Time( HourTy h, MinuteTy m, SecondTy s = 0 );

          /// Specified time and today's date or a given date and time
          Time( const Date  &, HourTy h=0, MinuteTy m=0, SecondTy s=0 );
                                
          // Boolean operators.
          bool operator <  ( const Time  & t ) const;
          bool operator <= ( const Time  & t ) const;
          bool operator >  ( const Time  & t ) const;
          bool operator >= ( const Time  & t ) const;
          bool operator == ( const Time  & t ) const;
          bool operator != ( const Time  & t ) const;
          bool Between( const Time  & a, const Time  & b ) const;

          // Add or subtract seconds.
          void operator++();
          void operator--();
          void operator+=(long s);
          void operator-=(long s);

          /// return a string representation of the time
          std::_tstring AsString() const;

          /// compare with a time
          Int16 CompareTo( const Time  & ) const;

          /// return a unique hash value for the current date and time
          Uint16 Hash() const;

          /// hour: local time
          HourTy Hour() const;

          /// hour : GMT
          HourTy HourGMT() const;

          /// is the time in DST
          bool IsDST() const;

          /// is the time valid
          bool IsValid() const;

          /// return the max of two times
          Time Max( const Time  & t ) const;

          /// return the min of two times
          Time Min( const Time  & t ) const;

          /// minute: local time
          MinuteTy Minute() const;

          /// minute: GMT
          MinuteTy MinuteGMT() const;

          /// second: local time or GMT
          SecondTy Second() const;

          /// return number of seconds since 1/1/1901.
          ClockTy Seconds() const;


          /// Start of DST for given year.
          static Time BeginDST( Uint16 year );

          /// End of DST for given year.
          static Time EndDST( Uint16 year );

          /// Set whether to include date when printing time
          static bool PrintDate( bool );
          static bool PrintDate();

      protected:

          static bool AssertDate( const Date  & );
          static const Date RefDate;
          static const Date MaxDate;

      private:

          ClockTy Sec;        // Seconds since 1/1/1901.
          static bool PrintDateFlag;  // True to print date along with time.

          ClockTy LocalSecs() const;
          static Time BuildLocal( const Date  &, HourTy );

          friend Date::Date(const Time&);
          SYSCLASS friend std::_tostream& operator<<(std::_tostream&, const Time&);
          SYSCLASS friend Time operator + (const Time& t, long s);
          SYSCLASS friend Time operator + (long s, const Time& t);
          SYSCLASS friend Time operator - (const Time& t, long s);
          SYSCLASS friend Time operator - (long s, const Time& t);
      };

      #if defined( BI_OLDNAMES )
      #define BI_Time Time
      #endif

      inline Time::Time( ClockTy s )
      {
          Sec = s;
      }

      inline bool Time::IsValid() const
      {
          return Sec > 0;
      }

      inline ClockTy Time::Seconds() const
      {
          return Sec;
      }

      inline bool Time::operator <  ( const Time& t ) const
      {
          return Sec < t.Sec;
      }

      inline bool Time::operator <= ( const Time& t ) const
      {
          return Sec <= t.Sec;
      }

      inline bool Time::operator >  ( const Time& t ) const
      {
          return Sec > t.Sec;
      }

      inline bool Time::operator >= ( const Time& t ) const
      {
          return Sec >= t.Sec;
      }

      inline bool Time::operator == ( const Time& t ) const
      {
          return Sec == t.Sec;
      }

      inline bool Time::operator != ( const Time& t ) const
      {
          return Sec != t.Sec;
      }

      inline bool Time::Between( const Time& a, const Time& b ) const
      {
          return *this >= a && *this <= b;
      }

      SYSCLASS inline Time operator + ( const Time& t, long s )
      {
          return Time(t.Sec+s);
      }

      SYSCLASS inline Time operator + ( long s, const Time& t )
      {
          return Time(t.Sec+s);
      }

      SYSCLASS inline Time operator - ( const Time& t, long s )
      {
          return Time(t.Sec-s);
      }

      SYSCLASS inline Time operator - ( long s, const Time& t )
      {
          return Time(t.Sec-s);
      }

      inline void Time::operator++()
      {
          Sec += 1;
      }

      inline void Time::operator--()
      {
          Sec -= 1;
      }

      inline void Time::operator+=(long s)
      {
          Sec += s;
      }

      inline void Time::operator-=(long s)
      {
          Sec -= s;
      }

      SYSCLASS inline Uint16 HashValue( Time  & t )
      {
          return t.Hash();
      }
   };
};
