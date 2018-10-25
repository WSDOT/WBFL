///////////////////////////////////////////////////////////////////////
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
//
// This library was developed as part of the Alternate Route Project
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Revision Log
// ============
// May 1997 - Created, Richard Brice
// Oct 1999 - Released as open source
#include "stdafx.h"
#include "ColorMapper.h"
#include "MathEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define EPS 10e-6
#define zero_val(x) (-EPS < (x) && (x) < EPS)

CColorMapper::CColorMapper(COLORREF color):
m_COLORREF(color)
{
}

COLORREF CColorMapper::GetCOLORREF()
{
   return m_COLORREF;
}

void CColorMapper::SetCOLORREF( COLORREF color)
{
   m_COLORREF = color;
}

void CColorMapper::SetRGB(int r, int g, int b)
{
   ASSERT(0 <= r && r <= 255);
   ASSERT(0 <= b && b <= 255);
   ASSERT(0 <= g && g <= 255);

   SetCOLORREF(RGB(r,g,b));
}

void CColorMapper::GetRGB(int* r, int* g, int* b)
{
   *r = GetRValue(m_COLORREF);
   *g = GetGValue(m_COLORREF);
   *b = GetBValue(m_COLORREF);
}

void CColorMapper::SetHLS(double h,double l,double s)
{
   int r, g, b;

   CColorMapper::HLStoRGB(h,l,s,&r,&g,&b);
   SetCOLORREF(RGB(r,g,b));
}

void CColorMapper::GetHLS(double* h, double* l,double* s)
{
   int r, g, b;
   GetRGB(&r, &g, &b);
   RGBtoHLS( r, g, b, h, l, s);
}

void CColorMapper::SetHSV(double h,double s,double v)
{
   int r, g, b;

   CColorMapper::HSVtoRGB(h,s,b,&r,&g,&b);
   SetCOLORREF(RGB(r,g,b));
}

void CColorMapper::GetHSV(double* h, double* s,double* v)
{
   int r, g, b;
   GetRGB(&r, &g, &b);
   RGBtoHSV( r, g, b, h, s, v);
}


// HLStoRGB
//
// Converts hls to rgb
// h in [0,360) (or less than zero = UNDEFINED)
// l and s in [0,1]
// r,g,b each in [0,255]
void CColorMapper::HLStoRGB(double h,double l,double s,int *r,int *g,int *b)
{
   double red,green,blue;
   double m1,m2;

   ASSERT( h < 360. );
   ASSERT(0. <= l && l <= 1.);
   ASSERT(0. <= s && s <= 1.);

   if (l <= 0.5)
      m2 = l*(1 + s);
   else
      m2 = l + s - l*s;

   m1 = 2*l - m2;

   if (zero_val(s))
   {
      // Achromatic : there is no hue
      if (h < 0) // UNDEFINED
      {
         red   = l;
         green = l;
         blue  = l;
      }
      else
      {
         // Major error... 
         // if hue is undefined, saturation must be zero...
         ASSERT(0);
      }
   }
   else
      {
      // Chromatic case, so there is a hue
      red   = ComputeValue(m1,m2,h + 120.);
      green = ComputeValue(m1,m2,h);
      blue  = ComputeValue(m1,m2,h - 120.);
      }

   // Convert to r,g,b values for Windows
   // The 0.001 provides just a little "boost" for those values that
   // are just about the next whole number so that they get truncated
   // to int's properly (e.g. 1.9995 normally becomes 1, but the correct
   // answer in this implementation is 2, so 1.9995 + 0.001 = 2.0005, or 2
   // when represented as an int). If a number is something like 5.0032 adding
   // 0.001 wont have any effect.
   *r = int(red*255. + 0.001);
   *g = int(green*255. + 0.001);
   *b = int(blue*255. + 0.001);
}

// RGBtoHLS
//
// Converts rgb to hls.
// r,g,b each in [0,255]
// h in [0,360)
// l and s in [0,1], except if s = 0, then h = (less than zero - UNDEFINED)
void CColorMapper::RGBtoHLS(int r,int g,int b,double *h,double *l,double *s)
{
   double maxColor, minColor;
   double delta;
   double red, green, blue;

   ASSERT(0 <= r && r <= 255);
   ASSERT(0 <= b && b <= 255);
   ASSERT(0 <= g && g <= 255);

   // convert r,g,b to [0,1]
   red   = r/255.;
   green = g/255.;
   blue  = b/255.;

   maxColor = max(max(red,green),blue);
   minColor = min(min(red,green),blue);

   // Compute lightness
   *l = (maxColor + minColor)/2;

   // Compute saturation
   if (zero_val(maxColor - minColor))
   {
      // Achromatic case, because r=b=g
      *s = 0.0;
      *h = -1.0; // UNDEFINED
   }
   else
   {
      // Chromatic case
      // First calculate saturation
      if (*l <= 0.5)
         *s = (maxColor - minColor)/(maxColor + minColor);
      else
         *s = (maxColor - minColor)/(2 - maxColor - minColor);

      // Now, calculate hue
      delta = maxColor - minColor;
      if (zero_val(red - maxColor))
         *h = (green - blue)/delta; // resulting color is between yellow and magenta
      else if (zero_val(green - maxColor))
         *h = 2 + (blue - red)/delta; // resulting color is between cyan and yellow
      else if (zero_val(blue - maxColor))
         *h = 4 + (red - green)/delta; // resulting color is between magenta and cyan

      // convert to degrees
      *h *= 60.;

      // Make degrees be nonnegative
      if (*h < 0)
         *h += 360.;
      }
}


// HSVtoRGB
//
// Converts hsv to rgb
// h in [0,360) (or less than zero = UNDEFINED)
// s and v in [0,1]
// r,g,b each in [0,255]
void CColorMapper::HSVtoRGB(double h,double s,double v,int *r,int *g,int *b)
{
   double red,green,blue;
   double f,p,q,t;
   int i;

   ASSERT(h < 360.);
   ASSERT(0. <= s && s <= 1.);
   ASSERT(s  <= v && v <= 1.);

   if (zero_val(s))
   {
      // color is on the black-and-white centerline
      if (h < 0) // UNDEFINED
      {
         // Achromatic color : There is no hue
         red   = v;
         green = v;
         blue  = v;
      }
      else
      {
         // Major error... Throw an exception
         // if hue is undefined, saturation must be zero...
         ASSERT(0);
      }
   }
   else
   {
      // Chromatic case
      h /= 60.;
      i = (int)floor(h);
      f = h - i;
      p = v*(1 - s);
      q = v*(1 - s*f);
      t = v*(1 - s*(1 - f));
      switch (i)
         {
         case 0:
              red   = v;
              green = t;
              blue  = p;
              break;

         case 1:
              red   = q;
              green = v;
              blue  = p;
              break;

         case 2:
              red   = p;
              green = v;
              blue  = t;
              break;

         case 3:
              red   = p;
              green = q;
              blue  = v;
              break;

         case 4:
              red   = t;
              green = p;
              blue  = v;
              break;

         case 5:
              red   = v;
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
   *r = int(red*255.   + 0.001);
   *g = int(green*255. + 0.001);
   *b = int(blue*255.  + 0.001);
}

// RGBtoHSV
//
// Converts rgb to hsv.
// r,g,b each in [0,255]
// h in [0,360)
// s and v in [0,1], except if s = 0, then h = (less than zero - UNDEFINED)
void CColorMapper::RGBtoHSV(int r,int g,int b,double *h,double *s,double *v)
{
   double red,green,blue;
   double maxColor, minColor;
   double delta;

   ASSERT(0 <= r && r <= 255);
   ASSERT(0 <= b && b <= 255);
   ASSERT(0 <= g && g <= 255);

   // Convert from Windows color numbers to normalized values [0,1]
   red   = r/255.;
   green = g/255.;
   blue   = b/255.;

   maxColor = max(max(red,green),blue);
   minColor = min(min(red,green),blue);

   *v = maxColor; // This is the value (Brightness)

   // calculate saturation
   if (!zero_val(maxColor))
      *s = (maxColor - minColor)/maxColor;
   else
      *s = 0.;

   if (zero_val(*s))
   {
      // Achromatic case
      *h = -1; // UNDEFINED
   }
   else
   {
      // Chromatic case
      delta = maxColor - minColor;
      if (zero_val(red - maxColor))
         *h = (green - blue)/delta; // Resulting color is between yellow and magenta
      else if(zero_val(green - maxColor))
         *h = 2 + (blue - red)/delta; // Resulting color is between cyan and yellow
      else if(zero_val(blue - maxColor))
         *h = 4 + (red - green)/delta; // Resulting color is between magenta and cyan

      *h *= 60.;

      // make sure hue is nonnegative
      if (*h < 0)
         *h += 360;
   }
}

double CColorMapper::ComputeValue(double n1,double n2,double hue)
{
   double value;

   if (hue > 360.)
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

#if defined (GEN_DEBUG_CODE)

bool CColorMapper::Test()
{
   bool success = true; // assume successful
   int i,j,k;
   int rIn,gIn,bIn;
   int rOut,gOut,bOut;
   double h,l,s;

   for (i = 0; i < 255; i++)
      {
      for (j = 0; j < 255; j++)
         {
         for (k = 0; k < 255; k++)
            {
            rIn = i;
            gIn = j;
            bIn = k;

            RGBtoHLS(rIn,gIn,bIn,h,l,s);
            HLStoRGB(h,l,s,rOut,gOut,bOut);

            if (rIn != rOut || gIn != gOut || bIn != bOut)
               {
               success = false;
               break;
               }
            }
         if (!success)
            break;
         }
      if (!success)
         break;
      }

   return success;
}

#endif


CColorIterator::CColorIterator( COLORREF startColor, COLORREF endColor, int numIncrements)
{
   ASSERT(numIncrements>=0);
   m_NumIncs = numIncrements;

   double h, l, s;
   int r,g,b;
   r = GetRValue(startColor);
   g = GetGValue(startColor);
   b = GetBValue(startColor);
   CColorMapper::RGBtoHLS(r, g, b, &h, &l, &s);
   m_HStart = h;
   m_LStart = l;
   m_SStart = s;

   r = GetRValue(endColor);
   g = GetGValue(endColor);
   b = GetBValue(endColor);
   CColorMapper::RGBtoHLS(r, g, b, &h, &l, &s);
   m_HEnd = h;
   m_LEnd = l;
   m_SEnd = s;

   m_HInc = (m_HEnd-m_HStart)/m_NumIncs;
   m_LInc = (m_LEnd-m_LStart)/m_NumIncs;
   m_SInc = (m_SEnd-m_SStart)/m_NumIncs;
}
   // HLS model
CColorIterator::CColorIterator( double HStart, double LStart, double SStart, double HEnd, double LEnd, double SEnd, int numIcrements)
{
}

int CColorIterator::NumberOfIncrements() const
{
   return m_NumIncs;
}

COLORREF CColorIterator::Item(int inc)
{
   ASSERT(inc>=0);
   ASSERT(inc<m_NumIncs);

   double h,l,s;
   h = m_HStart + m_HInc*inc;
   l = m_LStart + m_LInc*inc;
   s = m_SStart + m_SInc*inc;

   int r, g, b;
   CColorMapper::HLStoRGB(h, l, s, &r, &g, &b);

   return RGB(r,g,b);
}



