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

#include <System\SysLib.h>

/****************************************************************************
CLASS
   sysTime
****************************************************************************/

#include <System\Time.h>
#include <sstream>
#include <string>
#include <strstream>
#include <iomanip>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum TimeZone { CarolineIslands=-11,    MarianaIslands,         Japan, 
                China,                  minusSeven,             minusSix, 
                Pakistan,               CaspianSea,             Turkey, 
                Finland,                Europe,                 Greenwich, 
                Azores,                 two,                    Greenland, 
                Atlantic,               USEastern,              USCentral, 
                USMountain,             USPacific,              Alaska, 
                Hawaii,                 Bearing};

static const Uint32 SECONDS_IN_DAY  = 86400L;
static const Uint32 SECONDS_IN_HOUR = 3600L;
static const Uint16 SECONDS_IN_MIN  = 60;

struct sysIniTime
{
    sysIniTime()
        { _tzset(); }
};

static sysIniTime cludgeTime;      // To force the call to tzset()


const sysDate sysTime::RefDate( (DayTy)0, (YearTy)0 );
const sysDate sysTime::MaxDate( (DayTy)49709L, (YearTy)0 ); // ((2**32)-1)/SECONDS_IN_DAY -1
static const Int16 SUNDAY = 7;

bool sysTime::AssertDate( const sysDate  & date )
{
    return date.Between(RefDate,MaxDate);
}   

//----------------------------------------------------------------------------
//                     private member functions

//
// Adjust for local time zone and Daylight Savings Time.
//
ClockTy sysTime::LocalSecs() const
{
	long s;
	_get_timezone(&s);
    sysTime local_time( Sec - s );
    if (local_time.IsDST())
        local_time.Sec += SECONDS_IN_HOUR;
    return local_time.Sec;
}

//
// Builds the time from a local time, adjusting to GMT.  Does *not* adjust for DST.
//
sysTime sysTime::BuildLocal( const sysDate  & date, HourTy h )
{
	long s;
	_get_timezone(&s);
    return sysTime( SECONDS_IN_DAY * (date-RefDate) + 
                  SECONDS_IN_HOUR * h + 
                  s );
}

//----------------------------------------------------------------------------
//                  public static member functions

//
// Return the time at which DST starts for the given year.
// Note that the time returned is the time at which DST starts locally,
// but it is returned in GMT.
//
sysTime sysTime::BeginDST( Uint16 year )
{
    if( year > 1986 ) 
        {
        sysDate endMarch(31, 3, year);
        return BuildLocal( endMarch.Previous(SUNDAY)+7, 2 );
        }

    // Ah, remember those energy conscious years...???
    if( year==1974 )
        return BuildLocal( sysDate(6,1,1974), 2 );
    if( year==1975 )
        return BuildLocal( sysDate(23,2,1975), 2 );

    sysDate endApril( 30, 4, year );
    return BuildLocal( endApril.Previous(SUNDAY), 2 );
}


//
// Return the time at which DST ends for the given year.
// Note that the time returned is the time at which DST ends locally,
// but it is returned in GMT.
//
sysTime sysTime::EndDST( Uint16 year )
{
    sysDate endOctober( 31, 10, year );
    return BuildLocal( endOctober.Previous(SUNDAY), 1 );
}


//----------------------------------------------------------------------------
//                            constructors

//
// Construct sysTime with current time (seconds since Jan 1, 1901).
//
sysTime::sysTime()
{
  time_t ltime;
  time(&ltime);
  struct tm  t;
  localtime_s(&t,&ltime);

  // Construct the date.  The time struct returns int, so casts are used.
  //
  sysDate today( (DayTy)t.tm_mday,
               (MonthTy)(t.tm_mon + 1),
               (YearTy)t.tm_year+1900 );

  *this = sysTime( today, 
                 (HourTy)t.tm_hour, 
                 (MinuteTy)t.tm_min, 
                 (SecondTy)t.tm_sec );
} 

//
// Specified time and today's date:
//
sysTime::sysTime( HourTy h, MinuteTy m, SecondTy s )
{
    Sec = sysTime( sysDate(),h,m,s ).Sec;
}

//
// Construct a Time for the specified (local) Date, hour, minute, and second.
// Note: this algorithm will fail if DST correction is something other
// than an hour.
// It is complicated by the DST boundary problem: 
// 1) Times in the phantom zone between 2AM and 3AM when DST is invoked are invalid.
// 2) Times in the hour after 1AM when DST ends, are redundant.
// Checking for these situations necessitates a lot of jumping back 
// and forth by an hour to check for the boundary.
//
sysTime::sysTime( const sysDate  & date, HourTy h, MinuteTy m, SecondTy s )
{
    if( date.IsValid() )
        {
        Sec =   SECONDS_IN_DAY  * (date-RefDate) + 
                SECONDS_IN_HOUR * (h-1L) +    /* Note the adjustment by one hour */
                SECONDS_IN_MIN  * m + s;
        if( Sec )
		{
			long s;
			_get_timezone(&s);
            Sec += s;           // Adjust to GMT.
		}

        if( IsDST() )
            {
            Sec += SECONDS_IN_HOUR;
            if( IsDST() ) 
                Sec -= SECONDS_IN_HOUR;
            }
        else
            {
            Sec += SECONDS_IN_HOUR;
            if( IsDST() ) 
                Sec = 0;            // Invalid "phantom" time.
            }
        }
    else
        Sec = 0;    // Invalid date
}

//----------------------------------------------------------------------------
//                  conversion from sysTime to sysDate

//
// Type conversion to date.
//
sysDate::sysDate( const sysTime  & t )
{
    Julnum = t.IsValid() ? jul1901 + (JulTy)(t.LocalSecs()/SECONDS_IN_DAY) : 0;
}

//----------------------------------------------------------------------------
//                     public member functions

Int16 sysTime::CompareTo( const sysTime  &t ) const
{
    ClockTy diff = Sec - t.Sec;
    return diff==0 ? 0 : diff>0 ? 1 : -1;
}

//
// Hash function:
//
Uint16 sysTime::Hash() const
{
    return (Uint16)Sec;
}

//
// The hour in local time:
//
HourTy sysTime::Hour() const
{
    return HourTy((LocalSecs() % SECONDS_IN_DAY) / SECONDS_IN_HOUR);
}

//
// The hour in GMT:
//
HourTy sysTime::HourGMT() const 
{
    return HourTy((Sec % SECONDS_IN_DAY) / SECONDS_IN_HOUR);
} 

//
// Return TRUE if DST is active for this time:
//
bool sysTime::IsDST() const
{
   int hours;
   _get_daylight(&hours);
   if( !hours ) 
      return 0;

  DayTy daycount = (Uint16)(Sec/SECONDS_IN_DAY);
  YearTy year = sysDate( (DayTy)daycount, (YearTy)0 ).Year();

  // Check to see if the time falls between the starting & stopping DST times.
  //
  return *this >= BeginDST( year ) && *this < EndDST( year );
}

sysTime sysTime::Max( const sysTime  & t ) const 
{
    if( *this > t ) 
        return *this;
    else
        return t;
}

sysTime sysTime::Min( const sysTime  & t ) const 
{
    if( *this < t ) 
        return *this;
    else
        return t;
}

//
// minute, in local time
//
MinuteTy sysTime::Minute() const
{
    return MinuteTy(((LocalSecs()%SECONDS_IN_DAY)%SECONDS_IN_HOUR)/SECONDS_IN_MIN);
}

//
// minute, in GMT
//
MinuteTy sysTime::MinuteGMT() const 
{
    return MinuteTy(((Sec%SECONDS_IN_DAY)%SECONDS_IN_HOUR)/SECONDS_IN_MIN);
} 

//
// second, in local time or GMT 
//
SecondTy sysTime::Second() const 
{
    return SecondTy(((Sec%SECONDS_IN_DAY)%SECONDS_IN_HOUR)%SECONDS_IN_MIN);
}

//
// Static variable intialization:
//
bool sysTime::PrintDateFlag = true;

std::_tstring sysTime::AsString() const
{
    std::_tostringstream strtemp;
    strtemp << (*this);
    return strtemp.str();
}

SYSCLASS std::_tostream  &  operator << ( std::_tostream  & s, const sysTime  & t )
{

    // We use an ostrstream to format into buf so that
    // we don't affect the std::ostream's width setting.
    //
    std::_tostringstream out;
  
    // First print the date if requested:
    //
    if(sysTime::PrintDateFlag) 
        out << sysDate(t) << _T(" ");

    Uint16 hh = t.Hour();
    out << (hh <= 12 ? hh : hh-12) << _T(':') 
        << std::setfill(_T('0')) << std::setw(2) << t.Minute() << _T(':')
        << std::setw(2) << t.Second() << _T(' ') << std::setfill(_T(' '));
    out << ( hh<12 ? _T("am") : _T("pm")) ;//<< std::ends;

    // now we write out the formatted buffer, and the std::ostream's
    // width setting will control the actual width of the field.
    //
    s << out.str();
    return s;
}

bool sysTime::PrintDate( bool f )
{
    bool temp = PrintDateFlag;
    PrintDateFlag = f;
    return temp;
}

#if defined _UNITTEST
#include <iostream>
bool sysTime::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("sysTime");

   sysTime now;
   rlog << _T("The current time is ")<< now.AsString() << endl;

   TESTME_EPILOG("sysTime");
}
#endif // _UNITTEST


