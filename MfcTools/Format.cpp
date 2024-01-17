///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include "StdAfx.h"
#include <MFCTools\Format.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString FormatDirection(IDirection* pDirection)
{
   NSDirectionType nsDir;
   EWDirectionType ewDir;
   long deg;
   long min;
   Float64 sec;

   pDirection->get_NSDirection(&nsDir);
   pDirection->get_EWDirection(&ewDir);
   pDirection->get_Degree(&deg);
   pDirection->get_Minute(&min);
   pDirection->get_Second(&sec);

   CString str;
   str.Format(_T("%c %02d %02d %04.1f %c"),nsDir == nsNorth ? _T('N') : _T('S'), deg, min, sec, ewDir == ewEast ? _T('E') : _T('W'));
   str.TrimLeft();
   return str;
}

CString FormatAngle(IAngle* pAngle)
{
   long deg;
   long min;
   Float64 sec;

   pAngle->get_Degree(&deg);
   pAngle->get_Minute(&min);
   pAngle->get_Second(&sec);

   char cDir = (deg < 0 ? _T('R') : _T('L'));

   CString str;
   str.Format(_T("%02d %02d %04.1f %c"),abs(deg), min, sec, cDir);
   str.TrimLeft();
   return str;
}

CString FormatOffset(Float64 offset,const WBFL::Units::LengthData& indirectMeasure,bool bIncludeUnitTag)
{
   offset = WBFL::Units::ConvertFromSysUnits( IsZero(offset,indirectMeasure.Tol) ? 0.00 : offset, indirectMeasure.UnitOfMeasure );
   WBFL::System::NumericFormatTool format_tool(indirectMeasure.Format,indirectMeasure.Width,indirectMeasure.Precision);
   std::_tstring str = format_tool.AsString( offset );
   CString strOffset;
   if ( offset < 0 )
      strOffset.Format(_T("%*.*f L"),indirectMeasure.Width,indirectMeasure.Precision, -offset );
   else if ( 0 < offset )
      strOffset.Format(_T("%*.*f R"),indirectMeasure.Width,indirectMeasure.Precision, offset );
   else
      strOffset.Format(_T("%*.*f"),  indirectMeasure.Width,indirectMeasure.Precision, offset );

   strOffset.TrimLeft();

   if ( bIncludeUnitTag )
      strOffset += indirectMeasure.UnitOfMeasure.UnitTag().c_str();

   strOffset.TrimLeft();

   return strOffset;
}

CString FormatScalar(Float64 value,const WBFL::Units::ScalarData& indirectMeasure)
{
   WBFL::System::NumericFormatTool format_tool(indirectMeasure.Format,indirectMeasure.Width,indirectMeasure.Precision);
   std::_tstring str = format_tool.AsString( value );
   CString strScalar;
   strScalar.Format(_T("%s"),str.c_str());
   strScalar.TrimLeft();
   return strScalar;
}

CString FormatPercentage(Float64 value,bool bIncludeUnitTag)
{
   WBFL::System::NumericFormatTool format_tool(WBFL::System::NumericFormatTool::Format::Automatic, 9, 4);
   std::_tstring str = format_tool.AsString( value*100.0 );
   CString strPercentage;
   if ( bIncludeUnitTag )
      strPercentage.Format(_T("%s %%"),str.c_str());
   else
      strPercentage.Format(_T("%s"),str.c_str());

   strPercentage.TrimLeft();
   return strPercentage;
}

CString FormatStation(const WBFL::Units::StationFormat& format,Float64 value,ZoneIndexType zoneIdx)
{
   return format.AsString(value,zoneIdx).c_str();
}
