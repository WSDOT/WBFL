///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <System\SysLib.h>
#include <System\ColorConverter.h>
#include <System\XProgrammingError.h>
#include <MathEx.h>

void sysColorConverter::HLStoRGB(Float64 hue,Float64 lightness,Float64 saturation,BYTE* pRed,BYTE* pGreen,BYTE* pBlue)
{
   Float64 red,green,blue;
   Float64 m1,m2;

   ATLASSERT(hue <= 360.);
   ATLASSERT(0. <= lightness && lightness <= 1.);
   ATLASSERT(0. <= saturation && saturation <= 1.);

   if (lightness <= 0.5)
      m2 = lightness*(1 + saturation);
   else
      m2 = lightness + saturation - lightness*saturation;

   m1 = 2*lightness - m2;

   if (IsZero(saturation))
   {
      // Achromatic : there is no hue
      if (hue < 0) // UNDEFINED
      {
         red   = lightness;
         green = lightness;
         blue  = lightness;
      }
      else
      {
         // Major error... Throw an exception
         // if hue is undefined, saturation must be zero...
         THROW(sysXProgrammingError,InvalidValue);
      }
   }
   else
   {
      // Chromatic case, so there is a hue
      red   = ComputeValue(m1,m2,hue + 120.);
      green = ComputeValue(m1,m2,hue);
      blue  = ComputeValue(m1,m2,hue - 120.);
   }

   // Convert to r,g,b values for Windows
   // The 0.001 provides just a little "boost" for those values that
   // are just about the next whole number so that they get truncated
   // to int's properly (e.g. 1.9995 normally becomes 1, but the correct
   // answer in this implementation is 2, so 1.9995 + 0.001 = 2.0005, or 2
   // when represented as an int). If a number is something like 5.0032 adding
   // 0.001 wont have any effect.
   *pRed   = BYTE(red  *255. + 0.001);
   *pGreen = BYTE(green*255. + 0.001);
   *pBlue  = BYTE(blue *255. + 0.001);
}

void sysColorConverter::RGBtoHLS(BYTE r,BYTE g,BYTE b,Float64* pHue,Float64* pLightness,Float64* pSaturation)
{
   Float64 maxColor, minColor;
   Float64 delta;
   Float64 red, green, blue;

   ATLASSERT(0 <= r && r <= 255);
   ATLASSERT(0 <= b && b <= 255);
   ATLASSERT(0 <= g && g <= 255);

   // convert r,g,b to [0,1]
   red   = r/255.;
   green = g/255.;
   blue  = b/255.;

   maxColor = max(max(red,green),blue);
   minColor = min(min(red,green),blue);

   // Compute lightness
   *pLightness = (maxColor + minColor)/2;

   // Compute saturation
   if (IsZero(maxColor - minColor))
   {
      // Achromatic case, because r=b=g
      *pSaturation = 0.0;
      *pHue        = -1.0; // UNDEFINED
   }
   else
   {
      // Chromatic case
      // First calculate saturation
      if (*pLightness <= 0.5)
         *pSaturation = (maxColor - minColor)/(maxColor + minColor);
      else
         *pSaturation = (maxColor - minColor)/(2 - maxColor - minColor);

      // Now, calculate hue
      delta = maxColor - minColor;
      if (IsZero(red - maxColor))
         *pHue = (green - blue)/delta; // resulting color is between yellow and magenta
      else if (IsZero(green - maxColor))
         *pHue = 2 + (blue - red)/delta; // resulting color is between cyan and yellow
      else if (IsZero(blue - maxColor))
         *pHue = 4 + (red - green)/delta; // resulting color is between magenta and cyan

      // convert to degrees
      *pHue *= 60.;

      // Make degrees be nonnegative
      if (*pHue < 0)
      {
         *pHue += 360.;
      }
   }
}

void sysColorConverter::HSVtoRGB(Float64 hue,Float64 saturation,Float64 value,BYTE* pRed,BYTE* pGreen,BYTE* pBlue)
{
   Float64 red,green,blue;
   Float64 f,p,q,t;
   int i;

   ATLASSERT(hue <= 360.);
   ATLASSERT(0. <= saturation && saturation <= 1.);
   ATLASSERT(saturation <= value && value <= 1.);

   if (IsZero(saturation))
   {
      // color is on the black-and-white centerline
      if (hue < 0) // UNDEFINED
      {
         // Achromatic color : There is no hue
         red   = value;
         green = value;
         blue  = value;
      }
      else
      {
         // Major error... Throw an exception
         // if hue is undefined, saturation must be zero...
         THROW(sysXProgrammingError,InvalidValue);
      }
   }
   else
   {
      // Chromatic case
      hue /= 60.;
      i = (int)floor(hue);
      f = hue - i;
      p = value*(1 - saturation);
      q = value*(1 - saturation*f);
      t = value*(1 - saturation*(1 - f));
      switch (i)
      {
         case 0:
              red   = value;
              green = t;
              blue  = p;
              break;

         case 1:
              red   = q;
              green = value;
              blue  = p;
              break;

         case 2:
              red   = p;
              green = value;
              blue  = t;
              break;

         case 3:
              red   = p;
              green = q;
              blue  = value;
              break;

         case 4:
              red   = t;
              green = p;
              blue  = value;
              break;

         case 5:
              red   = value;
              green = p;
              blue  = q;
              break;
      }
   }

   // Convert to r,g,b values for Windows
   // The 0.001 provides just a little "boost" for those values that
   // are just about the next whole number so that they get truncated
   // to int's properly (e.g. 1.9995 normally becomes 1, but the correct
   // answer in this implementation is 2, so 1.9995 + 0.001 = 2.0005, or 2
   // when represented as an int). If a number is something like 5.0032 adding
   // 0.001 wont have any effect.
   *pRed   = BYTE(red  *255. + 0.001);
   *pGreen = BYTE(green*255. + 0.001);
   *pBlue  = BYTE(blue *255. + 0.001);
}

void sysColorConverter::RGBtoHSV(BYTE r,BYTE g,BYTE b,Float64* pHue,Float64* pSaturation,Float64* pValue)
{
   Float64 red,green,blue;
   Float64 maxColor, minColor;
   Float64 delta;

   ATLASSERT(0 <= r && r <= 255);
   ATLASSERT(0 <= b && b <= 255);
   ATLASSERT(0 <= g && g <= 255);

   // Convert from Windows color numbers to normalized values [0,1]
   red   = r/255.;
   green = g/255.;
   blue  = b/255.;

   maxColor = max(max(red,green),blue);
   minColor = min(min(red,green),blue);

   *pValue = maxColor; // This is the value (Brightness)

   // calculate saturation
   if (!IsZero(maxColor))
      *pSaturation = (maxColor - minColor)/maxColor;
   else
      *pSaturation = 0.;

   if (IsZero(*pSaturation))
   {
      // Achromatic case
      *pHue = -1; // UNDEFINED
   }
   else
   {
      // Chromatic case
      delta = maxColor - minColor;
      if (IsZero(red - maxColor))
         *pHue = (green - blue)/delta; // Resulting color is between yellow and magenta
      else if(IsZero(green - maxColor))
         *pHue = 2 + (blue - red)/delta; // Resulting color is between cyan and yellow
      else if(IsZero(blue - maxColor))
         *pHue = 4 + (red - green)/delta; // Resulting color is between magenta and cyan

      *pHue *= 60.;

      // make sure hue is nonnegative
      if (*pHue < 0)
      {
         *pHue += 360.;
      }
   }
}

Float64 sysColorConverter::ComputeValue(Float64 n1,Float64 n2,Float64 hue)
{
   Float64 value;

   if (360. < hue)
      hue -= 360.;
   else if (hue < 0.)
      hue += 360.;

   if (hue < 60.)
      value = n1 + (n2 - n1)*hue/60.;
   else if (hue < 180.)
      value = n2;
   else if (hue < 240.)
      value = n1 + (n2 - n1)*(240. - hue)/60.;
   else
      value = n1;

   return value;
}
