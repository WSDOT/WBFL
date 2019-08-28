///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
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

#include <GraphicsLib\GraphicsLibLib.h>
#include <GraphicsLib\GraphColor.h>
#include <System\ColorConverter.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

grGraphColor::grGraphColor()
{
   Init();
}

grGraphColor::grGraphColor(IndexType nGraphs)
{
   Init();
   SetGraphCount(nGraphs);
}

void grGraphColor::Init()
{
   m_bInitialized = false;
   m_nGraphs = 0;

   m_MinHue = 128;
   m_MaxHue = 360;
   m_Saturation = 1.0; // primary colors
   m_Lightness = 0.50; // half-way between black and white

   m_ColorsPerBand = 10;
}

void grGraphColor::SetGraphCount(IndexType nGraphs)
{
   m_nGraphs = nGraphs;
   ComputeColorParameters();
}

void grGraphColor::SetHueRange(Float64 minHue,Float64 maxHue)
{
   m_MinHue = minHue;
   m_MaxHue = maxHue;
   ComputeColorParameters();
}

void grGraphColor::SetSaturation(Float64 saturation)
{
   m_Saturation = saturation;
   ComputeColorParameters();
}

void grGraphColor::SetLightness(Float64 lightness)
{
   m_Lightness = lightness;
   ComputeColorParameters();
}

void grGraphColor::SetColorPerBandCount(IndexType nColorsPerBand)
{
   m_ColorsPerBand = nColorsPerBand;
   ComputeColorParameters();
}

COLORREF grGraphColor::GetColor(IndexType graphIndex)
{
   ATLASSERT(m_bInitialized);

   IndexType bandIdx = graphIndex / m_ColorsPerBand; // color band from which we get the color for this graph

   Float64 maxHue = m_MaxHue - bandIdx*m_ColorsPerBand; // maximum hue in this band

   IndexType colorIdx = graphIndex - bandIdx*m_ColorsPerBand; // color index within this band

   Float64 hue = maxHue - colorIdx*m_BandHueStep;

   BYTE red, green, blue;
   sysColorConverter::HLStoRGB(hue,m_Lightness,m_Saturation,&red,&green,&blue);
   return RGB(red,green,blue);
}

void grGraphColor::ComputeColorParameters()
{
   if ( m_nGraphs == 0 )
   {
      return;
   }

   // number of color bands
   m_nColorBands = (IndexType)ceil( (Float64)m_nGraphs / (Float64)m_ColorsPerBand );

   // total number of colors modeled
   IndexType nColors = m_ColorsPerBand*m_nColorBands;
   ATLASSERT(m_nGraphs <= nColors);

   // step size for full range of colors
   Float64 hueStep = (m_MaxHue - m_MinHue)/nColors;

   // hue step per band
   m_BandHueStep = (m_MaxHue - (m_MinHue + (m_nColorBands - 1)*hueStep))/m_ColorsPerBand;

   m_bInitialized = true;
}

