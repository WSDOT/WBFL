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

#include <Cogo\CogoHelpers.h>
#include <Units\SysUnits.h>
#include <MathEx.h>

void cogoUtil::ToDMS(Float64 value,Int16* deg,Uint16* min,Float64* sec)
{
   value = ::Convert( value, unitMeasure::Radian, unitMeasure::Degree );

   Int16 sign = BinarySign( value );
   value = fabs(value);

   *deg = (Int16)floor(value);
   value -= *deg;
   value *= 60;
   *min = (Uint16)floor(value);
   value -= *min;
   *sec = value*60;

   if ( IsZero(60. - *sec,0.051) ) // 59.95 ==> 60.0, 59.94 ==> 59.9
   {
      *sec = 0.;
      *min += 1;
   }

   if ( *min == 60 )
   {
      *min = 0;
      *deg += 1;
   }

   *deg *= sign;
}

Float64 cogoUtil::FromDMS(Int16 deg,Uint16 min,Float64 sec)
{
   Float64 angle;

   angle = BinarySign(deg)*(abs(deg) + (Float64)min/60. + sec/3600.);

   return ::Convert( angle, unitMeasure::Degree, unitMeasure::Radian );
}

Int16 cogoUtil::StationToString(Float64 station,Uint16 nDigOffset,Uint16 nDec,char* str,Uint16 cch)
{
   if ( station < 0 )
      return -1;

   Float64 shifter = pow(10.,nDigOffset);
   Int16 v1 = (Int16)floor(station/shifter);
   Float64 v2 = station - v1*shifter;
   
   // Check to make sure that v2 is not basically the same as shifter
   // If station = 69500.00000, we sometimes get 694+100.00 instead of
   // 695+00.
   if ( IsEqual(v2,shifter,pow(10.,-(nDec+1))) )
   {
      v2 = 0;
      v1++;
   }

   Uint16 width = nDigOffset + nDec + 1; // add one for the '.'

   Uint16 nChar;
   nChar = (v1 == 0) ? 1 : (Uint16)log10((Float64)v1) + 1;
   nChar += width; // includes one for the '.'
   nChar++; // one for the '+'
   nChar++; // one for the '\n'

   if ( nChar > cch )
      return nChar;

   char* pBuffer = new char[nChar];
	sprintf_s(pBuffer,nChar,"%d+%0*.*f",v1,width,nDec,v2);
   strncpy_s( str, nChar, pBuffer, cch );
   delete[] pBuffer;

   return 0;
}

bool cogoUtil::StringToStation(const char* str,Uint16 nDigOffset,Uint16 nDec,Float64* pStation)
{
   char* pBuffer = 0;
   bool bRetVal = true;
	char chFirst;
   Float64 d;

   if ( pStation == 0 )
      return false;

   // Look for the +
   int nChar = strlen(str)+1;
   pBuffer = new char[nChar];
   strcpy_s( pBuffer, nChar, str );
   char* pChar = pBuffer;
	while (*pChar != '+' && *pChar != '\0')
	{
		pChar++;
	}

	if (*pChar == '+')
	{
		// The + was found

		// Verify that the station is not ill-formed
		// That is, there must be nOffsetDigits between the +
		// and the decimal point or the end of the string
		char cDecimal = *(pChar + nDigOffset + 1);
		if ( cDecimal != '.' && cDecimal != 0 && cDecimal != '\n' && !isspace(cDecimal) )
		{
         *pStation = 0;
         bRetVal = false;
         goto CleanUp;
		}


	   // Remove the + by shifting the remaining characters 1 to the left
	   strcpy_s(pChar,nChar - size_t(pChar-pBuffer),pChar+1);
	}
   else
   {
      // The + wasn't found, this must be a regular number
      *pStation = atof( pBuffer );
      if ( IsZero( *pStation ) && pBuffer[0] != '0' )
      {
         bRetVal = false;
         goto CleanUp;
      }

      bRetVal = true;
      goto CleanUp;
   }
		
	// Now that the + has been removed, convert the string to a Float64
	chFirst = pBuffer[0];
   d = strtod(pBuffer,&pChar);
   if ( d < 0.0 ) // Negative stations aren't allowed.
   {
      bRetVal = false;
      goto CleanUp;
   }

   if (d == 0.0 && chFirst != '0')
	{
		// Could not convert
      *pStation = 0;
      bRetVal = false;
      goto CleanUp;
	}

	while (*pChar == ' ' || *pChar == '\t')
	   pChar++;

   if (*pChar != '\0')
	{
	   // Not terminated properly
      *pStation = 0;
      bRetVal = false;
      goto CleanUp;
	}

	*pStation = d;
   bRetVal = true;

CleanUp:
   delete[] pBuffer;
   return bRetVal;
}

#if defined _UNITTEST
bool cogoUtil::TestMe( dbgLog& rlog )
{
   TESTME_PROLOGUE("cogoUtil");

   // Test FromDMS
   TRY_TESTME( IsEqual(FromDMS(45), M_PI/4) );
   TRY_TESTME( IsEqual(FromDMS(-12,12,12), ::Convert(-12.20333333333333333,unitMeasure::Degree,unitMeasure::Radian)) );
   TRY_TESTME( IsEqual(FromDMS( 12,12,12), ::Convert( 12.20333333333333333,unitMeasure::Degree,unitMeasure::Radian)) );

   // Test ToDMS
   Int16 deg;
   Uint16 min;
   Float64 sec;

   ToDMS( M_PI/4, &deg, &min, &sec);
   TRY_TESTME( deg == 45 && min == 0 && IsZero(sec) );

   ToDMS( ::Convert(-12.2033333333333333333333333,unitMeasure::Degree,unitMeasure::Radian), &deg, &min, &sec );
   TRY_TESTME( deg == -12 && min == 12 && IsEqual( sec, 12. ) );

   ToDMS( ::Convert( 12.2033333333333333333333333,unitMeasure::Degree,unitMeasure::Radian), &deg, &min, &sec );
   TRY_TESTME( deg == 12 && min == 12 && IsEqual( sec, 12. ) );

   ToDMS( ::Convert(0.016638888888888888888888888,unitMeasure::Degree, unitMeasure::Radian), &deg, &min, &sec );
   TRY_TESTME( deg == 0 && min == 0 && IsEqual( sec, 59.9 ) );

   ToDMS( ::Convert(0.016652777777777777777777777,unitMeasure::Degree, unitMeasure::Radian), &deg, &min, &sec );
   TRY_TESTME( deg == 0 && min == 1 && IsEqual( sec, 0.0 ) );

   ToDMS( ::Convert(0.999986111111111111111111111,unitMeasure::Degree, unitMeasure::Radian), &deg, &min, &sec );
   TRY_TESTME( deg == 1 && min == 0 && IsEqual( sec, 0.0 ) );

   // Test StringToStation
   Float64 station;
   bool bRetVal;
   std::string strStation;

   // Correctly formatted US station
   strStation = "1+23.45";
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual( station, 123.45 ) );

   // Correctly formatted US station (leading spaces)
   strStation = "   1+23.45";
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual( station, 123.45 ) );

   // Correctly formatted US station (trailing spaces)
   strStation = "1+23.45   ";
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual( station, 123.45 ) );

   // Correctly formatted US station (both leading and trailing spaces)
   strStation = "   1+23.45   ";
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual( station, 123.45 ) );

   // Correctly formatted SI station
   strStation = "123+456.789";
   bRetVal = StringToStation( strStation.c_str(), COGO_SI_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual(station,123456.789) );

   // Correctly formatted SI station
   strStation = "123456.789";
   bRetVal = StringToStation( strStation.c_str(), COGO_SI_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual(station,123456.789) );

   // Correctly formatted SI station
   strStation = "123456";
   bRetVal = StringToStation( strStation.c_str(), COGO_SI_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual(station,123456.) );

   // Correctly formatted SI station
   strStation = "123456.";
   bRetVal = StringToStation( strStation.c_str(), COGO_SI_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual(station,123456.) );

   // Correctly formatted SI station
   strStation = "123+456";
   bRetVal = StringToStation( strStation.c_str(), COGO_SI_STATION, &station );
   TRY_TESTME( bRetVal == true );
   TRY_TESTME( IsEqual(station,123456.) );

   // Poorly formatted station (SI station when US specified )
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == false );

   // Poorly formatted station
   strStation = "-10+45.45";
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == false );

   // Poorly formatted station (send a SI station as a US station)
   strStation = "123+456.789";
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == false );

   // Poorly formatted station (not NULL terminated)
   strStation = "1234+56.789";
   strStation[11] = 'Z'; // replac NULL terminator with a Z
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, &station );
   TRY_TESTME( bRetVal == false );

   // Poorly formatted station
   strStation = "ABC+DEF.GHI";
   bRetVal = StringToStation( strStation.c_str(), COGO_SI_STATION, &station );
   TRY_TESTME( bRetVal == false );

   // Poorly formatted station
   strStation = "ABCDEF.GHI";
   bRetVal = StringToStation( strStation.c_str(), COGO_SI_STATION, &station );
   TRY_TESTME( bRetVal == false );

   // Missing pointer for station
   bRetVal = StringToStation( strStation.c_str(), COGO_US_STATION, 0 );
   TRY_TESTME( bRetVal == false );

   // Test StationToString
   char buffer[30];
   Int16 retval;

   // Correctly formatted US station
   station = 12345.6789;
   retval = StationToString( station, COGO_US_STATION, buffer, sizeof(buffer) );
   TRY_TESTME( retval == 0 );
   TRY_TESTME( std::string("123+45.68") == std::string(buffer) );

   station = 69500.00;
   retval = StationToString( station, COGO_US_STATION, buffer, sizeof(buffer) );
   TRY_TESTME( retval == 0 );
   TRY_TESTME( std::string("695+00.00") == std::string(buffer) );

   // Correctly formatted SI station
   station = 12345.6789;
   retval = StationToString( station, COGO_SI_STATION, buffer, sizeof(buffer) );
   TRY_TESTME( retval == 0 );
   TRY_TESTME( std::string("12+345.679") == std::string(buffer) );

   // Correctly formatted US Station
   station = 0.45;
   retval = StationToString( station, COGO_US_STATION, buffer, sizeof(buffer) );
   TRY_TESTME( retval == 0 );
   TRY_TESTME( std::string("0+00.45") == std::string(buffer) );

   // Correctly formatted SI Station
   station = 0.45;
   retval = StationToString( station, COGO_SI_STATION, buffer, sizeof(buffer) );
   TRY_TESTME( retval == 0 );
   TRY_TESTME( std::string("0+000.450") == std::string(buffer) );

   // Undersized buffer
   station = 12345.6789;
   retval = StationToString( station, COGO_US_STATION, buffer, 0 );
   TRY_TESTME( retval == 10 );

   // Incorrectly formatted station
   station = -100.00;
   retval = StationToString( station, COGO_US_STATION, buffer, sizeof(buffer) );
   TRY_TESTME( retval == -1 );

   TESTME_EPILOG("cogoUtil");
}
#endif // _UNITTEST