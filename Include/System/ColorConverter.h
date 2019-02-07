///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2019  Washington State Department of Transportation
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

/*****************************************************************************
CLASS 
   sysColorConverter

   Utility class for converting between color models


DESCRIPTION
   Utility class for converting between color models
*****************************************************************************/

class SYSCLASS sysColorConverter
{
public:
   // Hue-Lightness-Saturation
   //
   // Reference : "Computer Graphics - Principles and Practice"
   // Foley, van Dam, Feiner, Hughes, 1990 Addison-Wesly,
   // ISBN 0-201-12110-7 pg 592 -596
   //
   // Note:
   // Due to floating point to integer round off, a call to HLStoRGB followed by
   // a call to RGBtoHLS will not yield the original HLS values.
   //
   // A call to RGBtoHLS followed by a call to HLStoRGB will yield the original
   // RGB values.
   static void HLStoRGB(Float64 hue,Float64 lightness,Float64 saturation,BYTE* pRed,BYTE* pGreen,BYTE* pBlue);
   static void RGBtoHLS(BYTE red,BYTE green,BYTE blue,Float64* pHue,Float64* pLightness,Float64* pSaturation);

   // Hue-Saturation-Value(Brightness)
   //
   // Reference : "Computer Graphics - Principles and Practice"
   // Foley, van Dam, Feiner, Hughes, 1990 Addison-Wesly,
   // ISBN 0-201-12110-7 pg 590 -593
   //
   // Note:
   // Due to floating point to integer round off, a call to HSVtoRGB followed by
   // a call to RGBtoHSV will not yield the original HSV values.
   //
   // A call to RGBtoHSV followed by a call to HSVtoRGB will yield the original
   // RGB values.
   static void HSVtoRGB(Float64 hue,Float64 saturation,Float64 value,BYTE* pRed,BYTE* pGreen,BYTE* pBlue);
   static void RGBtoHSV(BYTE red,BYTE green,BYTE blue,Float64* pHue,Float64* pSaturation,Float64* pValue);

private:
   static Float64 ComputeValue(Float64 n1,Float64 n2,Float64 hue);
};