///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
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

#include <MfcTools\MfcToolsExp.h>
#include <UnitMgt\UnitMgt.h>
#include <WBFLCogo.h>


// Helper function for formatting text
template <class T>
inline CString FormatDimension(Float64 value,const T& indirectMeasure,bool bIncludeUnitTag = true)
{
   value = ::ConvertFromSysUnits( value, indirectMeasure.UnitOfMeasure );
   if (IsZero(value, indirectMeasure.Tol))
   {
      value = 0.0;
   }
   sysNumericFormatTool format_tool(indirectMeasure.Format,indirectMeasure.Width,indirectMeasure.Precision);
   std::_tstring str = format_tool.AsString( value );
   CString strDimension;
   if ( bIncludeUnitTag )
   {
      strDimension.Format(_T("%s %s"),str.c_str(),indirectMeasure.UnitOfMeasure.UnitTag().c_str());
   }
   else
   {
      strDimension.Format(_T("%s"),str.c_str());
   }

   strDimension.TrimLeft();
   return strDimension;
}

CString MFCTOOLSFUNC FormatOffset(Float64 offset,const unitmgtLengthData& indirectMeasure,bool bIncludeUnitTag = true);
CString MFCTOOLSFUNC FormatScalar(Float64 value,const unitmgtScalar& indirectMeasure);
CString MFCTOOLSFUNC FormatPercentage(Float64 value,bool bIncludeUnitTag = true);
CString MFCTOOLSFUNC FormatStation(const unitStationFormat& format,Float64 value);
CString MFCTOOLSFUNC FormatDirection(IDirection* pDirection);
CString MFCTOOLSFUNC FormatAngle(IAngle* pAngle);
