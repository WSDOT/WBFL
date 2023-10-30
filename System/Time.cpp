///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>
#include <System\Time.h>
#include <sstream>
#include <string>
#include <strstream>
#include <iomanip>
#include <time.h>

using namespace WBFL::System;

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

struct IniTime
{
    IniTime()
        { _tzset(); }
};

static IniTime cludgeTime; // To force the call to tzset()


const Date Time::RefDate( (DayTy)0, (YearTy)0 );
const Date Time::MaxDate( (DayTy)49709L, (YearTy)0 ); // ((2**32)-1)/SECONDS_IN_DAY -1
static const Int16 SUNDAY = 7;

bool Time::AssertDate( const Date  & date )
{
    return date.Between(RefDate,MaxDate);
}   

//----------------------------------------------------------------------------
//                     private member functions

//
// Adjust for local time zone and Daylight Savings Time.
//
ClockTy Time::LocalSecs() const
{
	long s;
	_get_timezone(&s);
    Time local_time( Sec - s );
    if (local_time.IsDST())
        local_time.Sec += SECONDS_IN_HOUR;
    return local_time.Sec;
}

//
// Builds the time from a local time, adjusting to GMT.  Does *not* adjust for DST.
//
Time Time::BuildLocal( const Date  & date, HourTy h )
{
	long s;
	_get_timezone(&s);
    return Time( SECONDS_IN_DAY * (date-RefDate) + 
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
Time Time::BeginDST( Uint16 year )
{
    if( year > 1986 ) 
        {
        Date endMarch(31, 3, year);
        return BuildLocal( endMarch.Previous(SUNDAY)+7, 2 );
        }

    // Ah, remember those energy conscious years...???
    if( year==1974 )
        return BuildLocal( Date(6,1,1974), 2 );
    if( year==1975 )
        return BuildLocal( Date(23,2,1975), 2 );

    Date endApril( 30, 4, year );
    return BuildLocal( endApril.Previous(SUNDAY), 2 );
}


//
// Return the time at which DST ends for the given year.
// Note that the time returned is the time at which DST ends locally,
// but it is returned in GMT.
//
Time Time::EndDST( Uint16 year )
{
    Date endOctober( 31, 10, year );
    return BuildLocal( endOctober.Previous(SUNDAY), 1 );
}


//----------------------------------------------------------------------------
//                            constructors

//
// Construct Time with current time (seconds since Jan 1, 1901).
//
Time::Time()
{
  time_t ltime;
  time(&ltime);
  struct tm  t;
  localtime_s(&t,&ltime);

  // Construct the date.  The time struct returns int, so casts are used.
  //
  Date today( (DayTy)t.tm_mday,
               (MonthTy)(t.tm_mon + 1),
               (YearTy)t.tm_year+1900 );

  *this = Time( today, 
                 (HourTy)t.tm_hour, 
                 (MinuteTy)t.tm_min, 
                 (SecondTy)t.tm_sec );
} 

//
// Specified time and today's date:
//
Time::Time( HourTy h, MinuteTy m, SecondTy s )
{
    Sec = Time( Date(),h,m,s ).Sec;
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
Time::Time( const Date  & date, HourTy h, MinuteTy m, SecondTy s )
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
//                  conversion from Time to Date

//
// Type conversion to date.
//
Date::Date( const Time  & t )
{
    Julnum = t.IsValid() ? jul1901 + (JulTy)(t.LocalSecs()/SECONDS_IN_DAY) : 0;
}

//----------------------------------------------------------------------------
//                     public member functions

Int16 Time::CompareTo( const Time  &t ) const
{
    return Sec == t.Sec ? 0 : Sec>t.Sec ? 1 : -1;
}

//
// Hash function:
//
Uint16 Time::Hash() const
{
    return (Uint16)Sec;
}

//
// The hour in local time:
//
HourTy Time::Hour() const
{
    return HourTy((LocalSecs() % SECONDS_IN_DAY) / SECONDS_IN_HOUR);
}

//
// The hour in GMT:
//
HourTy Time::HourGMT() const 
{
    return HourTy((Sec % SECONDS_IN_DAY) / SECONDS_IN_HOUR);
} 

//
// Return TRUE if DST is active for this time:
//
bool Time::IsDST() const
{
   int hours;
   _get_daylight(&hours);
   if( !hours ) 
      return false;

  DayTy daycount = (Uint16)(Sec/SECONDS_IN_DAY);
  YearTy year = Date( (DayTy)daycount, (YearTy)0 ).Year();

  // Check to see if the time falls between the starting & stopping DST times.
  //
  return *this >= BeginDST( year ) && *this < EndDST( year );
}

Time Time::Max( const Time  & t ) const 
{
    if( *this > t ) 
        return *this;
    else
        return t;
}

Time Time::Min( const Time  & t ) const 
{
    if( *this < t ) 
        return *this;
    else
        return t;
}

//
// minute, in local time
//
MinuteTy Time::Minute() const
{
    return MinuteTy(((LocalSecs()%SECONDS_IN_DAY)%SECONDS_IN_HOUR)/SECONDS_IN_MIN);
}

//
// minute, in GMT
//
MinuteTy Time::MinuteGMT() const 
{
    return MinuteTy(((Sec%SECONDS_IN_DAY)%SECONDS_IN_HOUR)/SECONDS_IN_MIN);
} 

//
// second, in local time or GMT 
//
SecondTy Time::Second() const 
{
    return SecondTy(((Sec%SECONDS_IN_DAY)%SECONDS_IN_HOUR)%SECONDS_IN_MIN);
}

//
// Static variable intialization:
//
bool Time::PrintDateFlag = true;

std::_tstring Time::AsString() const
{
    std::_tostringstream strtemp;
    strtemp << (*this);
    return strtemp.str();
}

bool Time::PrintDate( bool f )
{
   std::swap(PrintDateFlag, f);
   return f;
}

bool Time::PrintDate()
{
   return PrintDateFlag;
}

SYSCLASS std::_tostream& WBFL::System::operator<<(std::_tostream& s, const Time& t)
{

   // We use an ostrstream to format into buf so that
   // we don't affect the std::ostream's width setting.
   //
   std::_tostringstream out;

   // First print the date if requested:
   //
   if (Time::PrintDate())
      out << Date(t) << _T(" ");

   Uint16 hh = t.Hour();
   out << (hh <= 12 ? hh : hh - 12) << _T(':')
      << std::setfill(_T('0')) << std::setw(2) << t.Minute() << _T(':')
      << std::setw(2) << t.Second() << _T(' ') << std::setfill(_T(' '));
   out << (hh < 12 ? _T("am") : _T("pm"));//<< std::ends;

   // now we write out the formatted buffer, and the std::ostream's
   // width setting will control the actual width of the field.
   //
   s << out.str();
   return s;
}
