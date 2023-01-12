///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
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

#include <Graphing/GraphingExp.h>

namespace WBFL
{
   namespace Graphing
   {

/// Class that implements a Hue-Saturation-Lightness (HSL) color model and returns a randomized graph color.
/// Inspired by https://github.com/xuboying/randomcolor-cpp
class GRAPHINGCLASS GraphColor
{
public:
   GraphColor();

   /// Sets the hue range. Enter values between 0 and 360
   void SetHueRange(Float64 minHue,Float64 maxHue);

   /// Sets the saturation range. Enter values between 0 and 1
   void SetSaturationRange(Float64 minSaturation, Float64 maxSaturation);

   /// Sets the lightness range. Enter values between 0 and 1
   void SetLightnessRange(Float64 minLightness,Float64 maxLightness);

   /// Returns randomized color based on seed
   COLORREF GetColor(IndexType index);

   /// Reset defaults
   void Init();
private:

   Float64 m_MinHue, m_MaxHue;
   Float64 m_MinSaturation, m_MaxSaturation;
   Float64 m_MinLightness, m_MaxLightness;
};

   }; // Graphing
}; // WBFL
