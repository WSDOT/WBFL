///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_TIME_H_
#define INCLUDED_SYSTEM_TIME_H_
#pragma once

// SYSTEM INCLUDES
//
#include <istream>
#include <ostream>
#include <string>
#include <System\SysExp.h>
#include <System\Date.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class sysTime;


// MISCELLANEOUS
//

typedef Uint16 HourTy;
typedef Uint16 MinuteTy;
typedef Uint16 SecondTy;
typedef Uint32 ClockTy;

static const Uint32 secFrom_Jan_1_1901_to_Jan_1_1970 = 2177452800L;

/*****************************************************************************
CLASS 
   sysTime

   Utility time class


DESCRIPTION
   The class may be used for various Time-related activities.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.04.1997 : Created file
*****************************************************************************/

class SYSCLASS sysTime
{

public:

    friend sysDate::sysDate( const sysTime  & );

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Construct with the current time
    sysTime();

   //------------------------------------------------------------------------
   // Construct with the Seconds since Jan 1, 1901.
    sysTime( ClockTy s ); 

   //------------------------------------------------------------------------
   // construct an explicit time
    sysTime( HourTy h, MinuteTy m, SecondTy s = 0 );

   //------------------------------------------------------------------------
   // Specified time and today's date or a given date and time
    sysTime( const sysDate  &, HourTy h=0, MinuteTy m=0, SecondTy s=0 );
                                
   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Write times:
    SYSCLASS friend std::_tostream  &  operator << ( std::_tostream  &, const sysTime  & );


    // Boolean operators.
    bool operator <  ( const sysTime  & t ) const;
    bool operator <= ( const sysTime  & t ) const;
    bool operator >  ( const sysTime  & t ) const;
    bool operator >= ( const sysTime  & t ) const;
    bool operator == ( const sysTime  & t ) const;
    bool operator != ( const sysTime  & t ) const;
    bool Between( const sysTime  & a, const sysTime  & b ) const;

    // Add or subtract seconds.
    SYSCLASS friend sysTime  operator + ( const sysTime  & t, long s );
    SYSCLASS friend sysTime  operator + ( long s, const sysTime  & t );
    SYSCLASS friend sysTime operator - ( const sysTime  & t, long s );
    SYSCLASS friend sysTime operator - ( long s, const sysTime  & t );
    void operator++();
    void operator--();
    void operator+=(long s);
    void operator-=(long s);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // return a string representation of the time
    std::_tstring AsString() const;

   //------------------------------------------------------------------------
    // compare with a time
    Int16 CompareTo( const sysTime  & ) const;

   //------------------------------------------------------------------------
    // return a unique hash value for the current date and time
    Uint16 Hash() const;

   //------------------------------------------------------------------------
   // hour: local time
    HourTy Hour() const;

   //------------------------------------------------------------------------
   // hour : GMT
    HourTy HourGMT() const;

   //------------------------------------------------------------------------
    // is the time in DST
    bool IsDST() const;

   //------------------------------------------------------------------------
    // is the time valid
    bool IsValid() const;

   //------------------------------------------------------------------------
   // return the max of two times
    sysTime Max( const sysTime  & t ) const;

   //------------------------------------------------------------------------
   // return the min of two times
    sysTime Min( const sysTime  & t ) const;

   //------------------------------------------------------------------------
   // minute: local time
    MinuteTy Minute() const;

   //------------------------------------------------------------------------
   // minute: GMT
    MinuteTy MinuteGMT() const;

   //------------------------------------------------------------------------
   // second: local time or GMT
    SecondTy Second() const;

   //------------------------------------------------------------------------
   // return number of seconds since 1/1/1901.
    ClockTy Seconds() const;


    // Static member functions:
   //------------------------------------------------------------------------
   // Start of DST for given year.
    static sysTime BeginDST( Uint16 year );

   //------------------------------------------------------------------------
   // End of DST for given year.
    static sysTime EndDST( Uint16 year );

   //------------------------------------------------------------------------
   // Set whether to include date when printing time
    static bool PrintDate( bool );

#if defined _UNITTEST
    static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:

    static bool AssertDate( const sysDate  & );
    static const sysDate RefDate;
    static const sysDate MaxDate;

private:

    ClockTy Sec;        // Seconds since 1/1/1901.
    static bool PrintDateFlag;  // True to print date along with time.

    ClockTy LocalSecs() const;
    static sysTime BuildLocal( const sysDate  &, HourTy );

};

#if defined( BI_OLDNAMES )
#define BI_Time sysTime
#endif

inline sysTime::sysTime( ClockTy s )
{
    Sec = s;
}

inline bool sysTime::IsValid() const
{
    return Sec > 0;
}

inline ClockTy sysTime::Seconds() const
{
    return Sec;
}

inline bool sysTime::operator <  ( const sysTime& t ) const
{
    return Sec < t.Sec;
}

inline bool sysTime::operator <= ( const sysTime& t ) const
{
    return Sec <= t.Sec;
}

inline bool sysTime::operator >  ( const sysTime& t ) const
{
    return Sec > t.Sec;
}

inline bool sysTime::operator >= ( const sysTime& t ) const
{
    return Sec >= t.Sec;
}

inline bool sysTime::operator == ( const sysTime& t ) const
{
    return Sec == t.Sec;
}

inline bool sysTime::operator != ( const sysTime& t ) const
{
    return Sec != t.Sec;
}

inline bool sysTime::Between( const sysTime& a, const sysTime& b ) const
{
    return *this >= a && *this <= b;
}

SYSCLASS inline sysTime operator + ( const sysTime& t, long s )
{
    return sysTime(t.Sec+s);
}

SYSCLASS inline sysTime operator + ( long s, const sysTime& t )
{
    return sysTime(t.Sec+s);
}

SYSCLASS inline sysTime operator - ( const sysTime& t, long s )
{
    return sysTime(t.Sec-s);
}

SYSCLASS inline sysTime operator - ( long s, const sysTime& t )
{
    return sysTime(t.Sec-s);
}

inline void sysTime::operator++()
{
    Sec += 1;
}

inline void sysTime::operator--()
{
    Sec -= 1;
}

inline void sysTime::operator+=(long s)
{
    Sec += s;
}

inline void sysTime::operator-=(long s)
{
    Sec -= s;
}

SYSCLASS inline Uint16 HashValue( sysTime  & t )
{
    return t.Hash();
}


#endif  // INCLUDED_SYSTEM_TIME_H_
