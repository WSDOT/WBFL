///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
#ifndef INCLUDED_COGO_COGOHELPERS_H_
#define INCLUDED_COGO_COGOHELPERS_H_
#pragma once

#include <string>
#include <MathEx.h>

/*****************************************************************************
CLASS 
   cogoUtil

   Utility class for cogo related operations.

DESCRIPTION
   Utility class for cogo related operations.  This classes handles things like
   converting to and from DMS format and stationing format.

COPYRIGHT
   Copyright (c) 2001
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.19.1997 : Created file
*****************************************************************************/

class cogoUtil
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Converts an angle given in radians to deg-min-sec format
   static void ToDMS(Float64 value,long* deg,long* min,Float64* sec);

   //------------------------------------------------------------------------
   // Converts an angle given in deg-min-sec format to an angle in radians
   static Float64 FromDMS(long deg,long min = 0,Float64 sec = 0.0);

   //------------------------------------------------------------------------
   // Normalizes an angle between 0 and 2pi.
   static Float64 NormalizeAngle(Float64 angle);

   static HRESULT DirectionFromVariant(VARIANT varDir,IDirection** dir);
   static HRESULT AngleFromVariant(VARIANT varAngle,IAngle** angle);
   static HRESULT StationFromVariant(VARIANT varStation,IStation** station);
   static HRESULT LocateByDistDir(IPoint2d* from,Float64 dist,IDirection* dir,Float64 offset,IPoint2dFactory* pFactory,IPoint2d** ppoint);

   static bool IsEqual(IPoint2d* p1,IPoint2d* p2);
   static void CopyPoint(IPoint2d* to,IPoint2d* from);
   static void LineCircleIntersect(ILine2d* line,ICircle* circle,IPoint2d* pntNearest,IPoint2dFactory* pFactory,IPoint2d** newPnt);

   // Gets the parts of a bearing
	static void GetBrgParts(Float64 brgVal,NSDirectionType* pnsDir,long* pDeg,long* pMin,Float64* pSec,EWDirectionType *pewDir);

   // returns true if pPoint is on the line formed by pStart and pEnd and comes before pStart
   static bool IsPointBeforeStart(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint);

   // returns true if pPoint is on the line formed by pStart and pEnd and comes after pEnd
   static bool IsPointAfterEnd(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint);

//   //------------------------------------------------------------------------
//   // Converts a floating point number to a station string.  station must
//   // be a positive number.  Unit conversions are not performed on station.
//   // nDigOffset is the number of digits between the + sign and the decimal 
//   // place. nDec is the number of digits after the decimal place. The macros 
//   // COGO_US_STATION and COGO_SI_STATION can be used in place of the second 
//   // and third parameters.
//   //
//   // Example
//   // retval = cogoUtil::StationToString( station, COGO_US_STATION, buffer, sizeof(buffer) );
//   //
//   // The resulting string is stored in str.  cch is the size of str.
//   //
//   // Returns zero on success, required size of str if it is too small, or -1 on
//   // an other error.
//   static short StationToString(Float64 station,short nDigOffset,short nDec,TCHAR* str,short cch);
//
//   //------------------------------------------------------------------------
//   // Converts a station string to a floating point number.  nDigOffset is the 
//   // number of digits between the + sign and the decimal place. nDec is the 
//   // number of digits after the decimal place.  The macros COGO_US_STATION and
//   // COGO_SI_STATION can be used in place of the second and third parameters.
//   //
//   // Returns false if the station string was not correctly formed.
//   //
//   // Unit conversions are not performed on the resulting station.
//   static bool StringToStation(LPCTSTR str,short nDigOffset,short nDec,Float64* pStation);
//
   //------------------------------------------------------------------------
   // Solves the inverse problem for points (x1,y1) and (x2,y2);
   static void Inverse(IPoint2d* p1,IPoint2d* p2,Float64* pDist,IDirection** ppDir);


   static HRESULT ParseAngleTags(std::_tstring& strTag,std::_tstring* strDegTag,std::_tstring* strMinTag,std::_tstring* strSecTag);

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   cogoUtil();
   cogoUtil(const cogoUtil& rOther);
   cogoUtil& operator = (const cogoUtil& rOther);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

//cogoAngle ToAngle(IAngle* pAngle);
//void ToPoint(IPoint2dEx* pPoint,Float64* pX,Float64* pY);
//
//HRESULT CreateCogoPoint2d( VARIANT id,Float64 x,Float64 y, IPoint2dEx** ppPoint);
//HRESULT CreateAngle(const cogoAngle& angle,IAngle** ppAngle);
HRESULT CreateDirection(Float64 dir,IDirection** ppDirection);


inline bool operator<(CComPtr<IStation> sta1,CComPtr<IStation> sta2)
{
   if ( sta1.p == NULL || sta2.p == NULL )
      return false;

   Float64 val1, val2;
   sta1->get_Value(&val1);
   sta2->get_Value(&val2);
   return val1 < val2;
}

inline bool operator<=(CComPtr<IStation> sta1,CComPtr<IStation> sta2)
{
   if ( sta1.p == NULL || sta2.p == NULL )
      return false;

   Float64 val1, val2;
   sta1->get_Value(&val1);
   sta2->get_Value(&val2);
   return (val1 < val2) || IsEqual(val1,val2);
}

inline bool operator==(CComPtr<IStation> sta1,CComPtr<IStation> sta2)
{
   if ( sta1.p == NULL && sta2.p == NULL )
      return true;

   if ( (sta1.p != NULL && sta2.p == NULL) || (sta1.p == NULL && sta2.p != NULL))
      return false;

   Float64 val1, val2;
   sta1->get_Value(&val1);
   sta2->get_Value(&val2);
   return IsEqual(val1,val2);
}

inline bool operator!=(CComPtr<IStation> sta1,CComPtr<IStation> sta2)
{
   return !(sta1 == sta2);
}

inline Float64 operator-(CComPtr<IStation> sta1,CComPtr<IStation> sta2)
{
   Float64 val1, val2;
   sta1->get_Value(&val1);
   sta2->get_Value(&val2);
   return val1 - val2;
}

inline Float64 operator+(CComPtr<IStation> sta1,CComPtr<IStation> sta2)
{
   Float64 val1, val2;
   sta1->get_Value(&val1);
   sta2->get_Value(&val2);
   return val1 + val2;
}

#endif // INCLUDED_COGO_COGOHELPERS_H_

