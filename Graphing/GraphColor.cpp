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

#include "stdafx.h"
#include <Graphing/GraphColor.h>
#include <System\ColorConverter.h>
#include <math.h>
#include <tuple>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Graphing;

//------------------------------------------------------------------------------
// Psuedo-Random (repeatable if using same seed) graph color code inspired by:
// https://github.com/xuboying/randomcolor-cpp
//
typedef std::tuple<Float64, Float64> RangeType;

int randomWithin(const RangeType & range, int seed) 
{
   //
   //Seeded random algorithm from http://indiegamr.com/generate-repeatable-random-numbers-in-js/
   //
   Float64 max   = std::get<1>(range); //||1
   Float64 min   = std::get<0>(range); //||0
   min          = min < 0 ? 0 : min;
   seed = size_t(seed * 9301 + 49297) % 233280;
   Float64 rnd   = seed / 233280.0;
   auto   r     = floor(min + rnd * (max - min));
   ATLASSERT(r >= 0);
   ATLASSERT(min <= r && max >= r);
   return int(r);
}

int pickHue(const RangeType & hueRange, int seed) 
{
    int hue = randomWithin(hueRange, seed);

    return hue;
}


GraphColor::GraphColor()
{
   Init();
}


void GraphColor::Init()
{
   m_MinHue = 0.0;        // full color range by default
   m_MaxHue = 360.0;
   m_MinSaturation = 0.7; // highly saturated colors by default
   m_MaxSaturation = 1.0;
   m_MinLightness = 0.3; // mid-range between black and white by default
   m_MaxLightness = 0.8;
}

void GraphColor::SetHueRange(Float64 minHue,Float64 maxHue)
{
   ATLASSERT(minHue < maxHue);
   ATLASSERT(0.0 <=minHue && minHue <= 1.0);
   ATLASSERT(0.0 <=maxHue && maxHue <= 1.0);

   m_MinHue = minHue;
   m_MaxHue = maxHue;
}

void GraphColor::SetSaturationRange(Float64 minSaturation, Float64 maxSaturation)
{
   ATLASSERT(minSaturation < maxSaturation);
   ATLASSERT(0.0 <=minSaturation && minSaturation <= 360.0);
   ATLASSERT(0.0 <=maxSaturation && maxSaturation <= 360.0);

   m_MinSaturation = minSaturation;
   m_MaxSaturation = maxSaturation;
}

void GraphColor::SetLightnessRange(Float64 minLightness, Float64 maxLightness)
{
   ATLASSERT(minLightness < maxLightness);
   ATLASSERT(0.0 <=minLightness && minLightness <= 1.0);
   ATLASSERT(0.0 <=maxLightness && maxLightness <= 1.0);

   m_MinLightness = minLightness;
   m_MaxLightness = maxLightness;
}

COLORREF GraphColor::GetColor(IndexType graphIndex)
{
   // multiply values by 100 to get better randomized values
   const Float64 fctr = 100.0;
   Float64 lightness = randomWithin(RangeType(m_MinLightness*fctr, m_MaxLightness*fctr), (int)graphIndex);
   lightness /= fctr;

   Float64 saturation = randomWithin(RangeType(m_MinSaturation*fctr, m_MaxSaturation*fctr), (int)graphIndex);
   saturation /= fctr;

   Float64 hue = pickHue(RangeType(m_MinHue, m_MaxHue), (int)graphIndex*5); // 5 gives a good color distribution (after testing)

   BYTE red, green, blue;
   WBFL::System::ColorConverter::HLStoRGB(hue,lightness,saturation,&red,&green,&blue);
   return RGB(red,green,blue);
}
