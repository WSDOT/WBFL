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

#pragma once

#include <System\SysExp.h>

namespace WBFL
{
   namespace System
   {

      /// Utility class for converting between color models
      ///
      /// Hue-Lightness-Saturation
      ///
      /// Reference : "Computer Graphics - Principles and Practice"
      /// Foley, van Dam, Feiner, Hughes, 1990 Addison-Wesly,
      /// ISBN 0-201-12110-7 pg 592 -596
      ///
      /// Hue-Saturation-Value(Brightness)
      ///
      /// Reference : "Computer Graphics - Principles and Practice"
      /// Foley, van Dam, Feiner, Hughes, 1990 Addison-Wesly,
      /// ISBN 0-201-12110-7 pg 590 -593
      ///
      /// 
      /// > Due to floating point to integer round off, a call to HLStoRGB followed by
      /// > a call to RGBtoHLS will not yield the original HLS values.
      /// 
      /// > A call to RGBtoHLS followed by a call to HLStoRGB will yield the original
      /// > RGB values.
      class SYSCLASS ColorConverter
      {
      public:
         ColorConverter() = delete;
         ColorConverter(const ColorConverter&) = delete;
         ~ColorConverter() = delete;
         ColorConverter& operator=(const ColorConverter&) = delete;


         /// Converts color from HLS to RGB model
         /// @return A tuple in the format (Red,Green,Blue)
         static std::tuple <BYTE, BYTE, BYTE> HLStoRGB(Float64 hue, Float64 lightness, Float64 saturation);

         ///  Converts color from RGB to HLS model
         /// @return A tuple in the format (Hue,Lightness,Saturation)
         static std::tuple<Float64,Float64,Float64> RGBtoHLS(BYTE red, BYTE green, BYTE blue);

         // Note:
         // Due to floating point to integer round off, a call to HSVtoRGB followed by
         // a call to RGBtoHSV will not yield the original HSV values.
         //
         // A call to RGBtoHSV followed by a call to HSVtoRGB will yield the original
         // RGB values.

         /// Converts color from HSV to RGB model
         /// @return A tuple in the format (Red,Green,Blue)
         static std::tuple <BYTE, BYTE, BYTE> HSVtoRGB(Float64 hue,Float64 saturation,Float64 value);

         /// Converts color from RGB to HSV model
         /// @return A tuple in the format (Hue,Lightness,Value)
         static std::tuple<Float64, Float64, Float64> RGBtoHSV(BYTE red,BYTE green,BYTE blue);

      private:
         static Float64 ComputeValue(Float64 n1,Float64 n2,Float64 hue);
      };
   };
};
