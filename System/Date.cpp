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
#include <System\Date.h>
#include <time.h>
#include <string>
#include <strstream>

using namespace WBFL::System;

/****************************************************************
 *                                                              *
 *                      static constants                        *
 *                                                              *
 ****************************************************************/

static const Uint8 DaysInMonth[12] = 
    { 31,28,31,30,31,30,31,31,30,31,30,31 };
static const DayTy FirstDayOfEachMonth[12] =
    { 1,32,60,91,121,152,182,213,244,274,305,335 };
static LPCTSTR MonthNames[12] = 
    { _T("January"),_T("February"),_T("March"),_T("April"),_T("May"),_T("June"),
      _T("July"),_T("August"),_T("September"),_T("October"),_T("November"),_T("December") };
static LPCTSTR UCMonthNames[12] =
    { _T("JANUARY"),_T("FEBRUARY"),_T("MARCH"),_T("APRIL"),_T("MAY"),_T("JUNE"),
      _T("JULY"),_T("AUGUST"),_T("SEPTEMBER"),_T("OCTOBER"),_T("NOVEMBER"),_T("DECEMBER") };
static LPCTSTR WeekDayNames[7] =
    { _T("Monday"),_T("Tuesday"),_T("Wednesday"),
      _T("Thursday"),_T("Friday"),_T("Saturday"),_T("Sunday") };
static LPCTSTR UCWeekDayNames[7] =
    { _T("MONDAY"),_T("TUESDAY"),_T("WEDNESDAY"),
      _T("THURSDAY"),_T("FRIDAY"),_T("SATURDAY"),_T("SUNDAY") };

static size_t 
FindMatch( LPCTSTR str, LPCTSTR* candidates, size_t icand );

//
// Construct a Date for today's date.
//
Date::Date()
{
    time_t clk = time(0);
    struct tm now;
	localtime_s(&now,&clk);
    Julnum = Jday(now.tm_mon+1, now.tm_mday, now.tm_year+1900);
}

//
// Construct a Date with a given day of the year and a given year.  The
// base date for this computation is Dec. 31 of the previous year.  If
// year == 0, Construct a Date with Jan. 1, 1901 as the "day zero".
// i.e., Date(-1) = Dec. 31, 1900 and Date(1) = Jan. 2, 1901.
//
Date::Date(DayTy day, YearTy year)
{
   if( year )
      Julnum = Jday( 12, 31, year-1 ) + (JulTy)day;
   else
      Julnum = jul1901                + (JulTy)day;
}

//
//   Construct a Date for the given day, monthName, and year.
//
Date::Date( DayTy day, LPCTSTR monthName, YearTy year )
{
   Julnum = Jday( IndexOfMonth(monthName), day, year );
}

//
//   Construct a Date for the given day, month, and year.
//
Date::Date( DayTy day, MonthTy month, YearTy year )
{
   Julnum = Jday( month, day, year );
}

/***************************************************************************/

//                      static member functions

/***************************************************************************/

//
// Returns a string name for the weekday number.
// Monday == 1, ... , Sunday == 7
// Return 0 for weekday number out of range
//
LPCTSTR Date::DayName( DayTy weekDayNumber )
{
    return AssertWeekDayNumber(weekDayNumber) ? WeekDayNames[weekDayNumber-1] : 0;
}

//
// Return the number, 1-7, of the day of the week named nameOfDay.
// Return 0 if name doesn't match.
//
DayTy Date::DayOfWeek( LPCTSTR nameOfDay )
{
    return (DayTy)(FindMatch( nameOfDay, UCWeekDayNames, 7 )+1);
}

//
// Is a day (1-31) within a given month?
//
Int16 Date::DayWithinMonth( MonthTy month, DayTy day, YearTy year )
{
   if( day <= 0 || !AssertIndexOfMonth(month) ) 
        return 0;
    Uint16 d = DaysInMonth[month-1];
    if( IsLeapYear(year) && month == 2 )
        d++;
    return day <= d;
}

//
// How many days are in the given YearTy year?
//
DayTy Date::DaysInYear( YearTy year )
{
   return IsLeapYear(year) ? 366 : 365;
}

//
// Returns the number, 1-12, of the month named nameOfMonth.
// Return 0 for no match.
//
MonthTy Date::IndexOfMonth( LPCTSTR nameOfMonth )
{
    return (MonthTy)(FindMatch( nameOfMonth, UCMonthNames, 12 )+1);
}

//
// Convert Gregorian calendar date to the corresponding Julian day
// number j.  Algorithm 199 from Communications of the ACM, Volume 6, No.
// 8, (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
// This function not valid before that.
// Returns 0 if the date is invalid.
//
JulTy Date::Jday( MonthTy m, DayTy d, YearTy y )
{
   Uint32 c, ya;

   if( y <= 99 )
      y += 1900;

   if( !DayWithinMonth(m, d, y) ) 
      return (JulTy)0;

   if( m > 2 )          
      m -= 3;
   else 
   {
      m += 9;
      y--;
   } 

   c = y / 100;
   ya = y - 100*c;
   return ((146097L*c)>>2) + ((1461*ya)>>2) + (153*m + 2)/5 + d + 1721119L;
} 

//
// Algorithm from K & R, "The C Programming Language", 1st ed.
//
// There is some evidence that the standard leap year algorithm is
// not complete.  There seems to be an additional rule to determine
// if a century year is a leap year, but I have not been able to 
// confirm it.  The rule is, century years divisible by 900 will
// be leap years only if the remainder is 200 or 600. This
// information comes from http://www.sprinc.com/marktime.htm
bool Date::IsLeapYear( YearTy year )
{
   return (year&3) == 0 && year%100 != 0 || year % 400 == 0;
}

//
// Returns a string name for the month number.
// Return 0 if invalid month number.
//
LPCTSTR Date::MonthName( MonthTy monthNumber )
{
    return AssertIndexOfMonth(monthNumber) ? MonthNames[monthNumber-1] : 0;
}

//
// Return index of case-insensitive match; -1 if no match.
//
static size_t FindMatch( LPCTSTR str, LPCTSTR* candidates, size_t icand )
{
    size_t len = _tcslen(str);

    while(icand--)
        {
        if( _tcsnicmp(str, candidates[icand], len) == 0)
            break;
        }
    return icand;
}

/****************************************************************
 *                                                              *
 *                      Member functions                        *
 *                                                              *
 ****************************************************************/

//
// Compare function:
//
Int16 Date::CompareTo( const Date  &d ) const
{
    if( Julnum < d.Julnum )
        return -1;
    else if( Julnum > d.Julnum )
        return 1;
    else
        return 0;
}

//
//
//
DayTy Date::Day() const
{
    return DayTy(Julnum - Jday( 12, 31, Year()-1 ));
}

//
// Returns the day of the month of this Date.
//
DayTy Date::DayOfMonth() const
{
    MonthTy m; DayTy d; YearTy y;
    Mdy( m, d, y );
    return d;
}

//
// Return the number of the first day of a given month
// Return 0 if "month" is outside of the range 1 through 12, inclusive.
//
DayTy Date::FirstDayOfMonth( MonthTy month ) const
{
    if ( !AssertIndexOfMonth(month) )
        return 0;
    Uint16 firstDay = FirstDayOfEachMonth[month-1];
    if (month > 2 && IsLeapYear())
        firstDay++;
    return firstDay;
}

Uint32 Date::Hash() const
{
    return (Uint32)Julnum;
}

//
// Convert a Julian day number to its corresponding Gregorian calendar
// date.  Algorithm 199 from Communications of the ACM, Volume 6, No. 8,
// (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
// This function not valid before that.  
//
void  Date::Mdy( MonthTy  & m, DayTy  & D, YearTy  & y ) const
{
    Uint32 d;
    JulTy j = Julnum - 1721119L;
    y = (YearTy) (((j<<2) - 1) / 146097L);
    j = (j<<2) - 1 - 146097L*y;
    d = (j>>2);
    j = ((d<<2) + 3) / 1461;
    d = (d<<2) + 3 - 1461*j;
    d = (d + 4)>>2;
    m = (MonthTy)(5*d - 3)/153;
    d = 5*d - 3 - 153*m;
    D = (DayTy)((d + 5)/5);
    y = (YearTy)(100*y + j);

    if( m < 10 )
        m += 3;
    else 
        {
        m -= 9;
        y++;
        } 
   CHECK( y >= 1752 );
} 

//
//
//
Date Date::Max( const Date  & dt ) const
{
    return dt.Julnum > Julnum ? dt : *this;
}

//
//
//
Date Date::Min( const Date  & dt ) const 
{
    return dt.Julnum < Julnum ? dt : *this;
}

//
// Returns the month of this Date.
//
MonthTy Date::Month() const
{
    MonthTy m; DayTy d; YearTy y;
    Mdy(m, d, y);
    return m;
}

//
//
//
Date Date::Previous( LPCTSTR dayName) const
{
    return Previous( DayOfWeek(dayName) );
}

//
//
//
Date Date::Previous( DayTy desiredDayOfWeek ) const
{
    //    Renumber the desired and current day of week to start at 0 (Monday)
    //    and end at 6 (Sunday).

    desiredDayOfWeek--;
    DayTy thisDayOfWeek = WeekDay() - 1;
    JulTy j = Julnum;

    //    Have to determine how many days difference from current day back to
    //    desired, if any.  Special calculation under the 'if' statement to
    //    effect the wraparound counting from Monday (0) back to Sunday (6).

    if( desiredDayOfWeek > thisDayOfWeek )
        thisDayOfWeek += 7 - desiredDayOfWeek;
    else
        thisDayOfWeek -= desiredDayOfWeek;
    j -= thisDayOfWeek; // Adjust j to set it at the desired day of week.
    return  Date(j);
}

DayTy Date::WeekDay() const
{
    return DayTy(((((Julnum+1)%7)+6)%7)+1);
}

//
// Returns the year of this Date.
//
YearTy Date::Year() const
{
    MonthTy m; DayTy d; YearTy y;
    Mdy(m, d, y);
    return y;
}


//
//
Date::PrintFormat Date::DatePrintFormat = Date::PrintFormat::Normal;

//
//
//
std::_tstring Date::AsString() const
{
   std::_tostringstream os;
   os << (*this) << std::ends;
   return os.str();
}

//
//
//
Date::PrintFormat Date::SetPrintFormat( Date::PrintFormat h )
{
   std::swap(Date::DatePrintFormat, h);
   return h;
}

Date::PrintFormat Date::GetPrintFormat()
{
   return Date::DatePrintFormat;
}

//
// Skip any characters except alphanumeric characters
//
static void  SkipDelim( std::_tistream  & strm )
{
    TCHAR c;
    if( !strm.good() )
        return;

    do  {
        strm >> c;
        } while (strm.good() && !isalnum(c)) ;

    if (strm.good())
        strm.putback(c);
}

//
// Parse the name of a month from input stream.
//
static LPCTSTR  ParseMonth( std::_tistream  & s )
{
    static TCHAR month[12];
    LPTSTR p = month;
    TCHAR c;
    SkipDelim(s);
    s.get(c);
    while (s.good() && isalpha(c) && (p != &month[10]))
        {
        *p++ = c;
        s.get(c);
        }
    if( s.good() )
        s.putback(c);
    *p = '\0';
    return month;
}

//
//  Parse a date from the specified input stream.  
//    The date must be in one of the following forms: 
//                dd-mmm-yy, mm/dd/yy, or mmm dd,yy
//        e.g.: 10-MAR-86,  3/10/86, or March 10, 1986.  
//  Any non-alphanumeric character may be used as a delimiter.
//
void Date::ParseFrom( std::_tistream  & s )
{
    Uint16 d(0),m(0),y(0);
    Julnum = 0;                 // Assume failure

    if (s.good())
        {
        SkipDelim(s);
        s >> m;                 // try to parse day or month number 
        SkipDelim(s);
        if (s.eof())
            return;
        if( s.fail() )          // parse <monthName><day><year> 
            {
            s.clear();
            m = IndexOfMonth(ParseMonth(s)); // parse month name
            SkipDelim(s);
            s >> d;                 // parse day 
            }
        else                        // try to parse day number 
            {
            s >> d;
            if (s.eof()) return;
            if (s.fail())           // parse <day><monthName><year> 
                {
                d = m;
                s.clear();
                m = IndexOfMonth(ParseMonth(s)); // parse month name
                }
            }
        SkipDelim(s);
        s >> y;
        }
    Julnum = s.good() ? Jday(m, d, y) : 0;
    if(Julnum==0)
        s.clear(std::ios::badbit);
}

//
//
//
SYSCLASS std::_tostream&  WBFL::System::operator<<( std::_tostream  & s, const Date  & d )
{
    std::_tostringstream out;
  
    switch ( Date::GetPrintFormat() )
        {
    case Date::PrintFormat::Normal:
            out << d.NameOfMonth() << _T(" ") 
                << d.DayOfMonth()  << _T(", ")
                << d.Year() << std::ends;
            break;
        case Date::PrintFormat::Terse:
           {
              TCHAR buf[50];
            _stprintf_s(buf,_T("%2u-%.3s-%.2u"),
                    d.DayOfMonth(),
                    d.NameOfMonth(),
                    d.Year() % 100);

            out << buf;
           }
            break;
        case Date::PrintFormat::Numbers:
            out << d.Month() << _T("/")
                << d.DayOfMonth() << _T("/")
                << (d.Year() % 100) << std::ends;
            break;
        case Date::PrintFormat::EuropeanNumbers:
            out << d.DayOfMonth()   << _T("/")
                << d.Month() << _T("/")
                << (d.Year() % 100) << std::ends;
            break;
        case Date::PrintFormat::European:
            out << d.DayOfMonth() << _T(" ")
                << d.NameOfMonth() << _T(" ")
                << d.Year() << std::ends;
            break;
        };

    // now we write out the formatted buffer, and the ostream's
    // width setting will control the actual width of the field.
    //

    s << out.str();
    return s;
}
