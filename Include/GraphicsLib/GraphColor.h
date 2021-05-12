///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2021  Washington State Department of Transportation
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

#include <GraphicsLib\GraphicsLibExp.h>

class GRCLASS grGraphColor
{
public:
   grGraphColor();

   void SetHueRange(Float64 minHue,Float64 maxHue); // a value between 0 and 360
   void SetSaturationRange(Float64 minSaturation, Float64 maxSaturation); // values between 0 and 1
   void SetLightnessRange(Float64 minLightness,Float64 maxLightness); // values between 0 and 1


   // Returns randomized color based on seed
   COLORREF GetColor(IndexType index);

   // reset defaults
   void Init();
private:

   Float64 m_MinHue, m_MaxHue;
   Float64 m_MinSaturation, m_MaxSaturation;
   Float64 m_MinLightness, m_MaxLightness;
};



