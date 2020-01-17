///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2020  Washington State Department of Transportation
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
   grGraphColor(IndexType nGraphs);

   void SetGraphCount(IndexType nGraphs);
   void SetHueRange(Float64 minHue,Float64 maxHue); // a value between 0 and 360
   void SetSaturation(Float64 saturation); // a value between 0 and 1
   void SetLightness(Float64 lightness); // a value between 0 and 1

   // number of colors before repeating
   // note that repeat colors are shifted in the hue range so that
   // no two same colors are used (e.g. every time red is used
   // it will be a different shade)
   void SetColorPerBandCount(IndexType nColorsPerBand);

   COLORREF GetColor(IndexType index);

private:
   bool m_bInitialized;
   void Init();
   void ComputeColorParameters();

   IndexType m_nGraphs;
   Float64 m_MinHue;
   Float64 m_MaxHue;
   Float64 m_Saturation;
   Float64 m_Lightness;
   IndexType m_nColorBands;
   IndexType m_ColorsPerBand;
   Float64 m_BandHueStep;
};



