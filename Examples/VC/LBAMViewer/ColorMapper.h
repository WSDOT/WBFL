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
// Feb 2002 - Converted to mfc

#pragma once

// Color managment in the lbamviewer is a mess. Start collecting colors here:
#define SELECTED_OBJECT_LINE_COLOR RED4
#define SELECTED_OBJECT_FILL_COLOR BLUE


// Color mapping class for Windows
//
// Maps between RGB<>HLS and RGB<>HSV
// RGB is as defined by Windows
// 
// Hue-Lightness-Saturation (HLS) - Color model
// Valid value ranges:     
//                            H < 360.
//                      0. <= L <= 1.
//                      0. <= S <= 1.
// 
// Hue-Saturation-Value(Brightness) (HSV) Color model
// Valid value ranges:
//                            H < 360.
//                      0. <= S <= 1.
//                      0. <= V <= 1.
// 
//
// Reference : "Computer Graphics - Principles and Practice"
// Foley, van Dam, Feiner, Hughes, 1990 Addison-Wesly,
// ISBN 0-201-12110-7 pg 592 -596
//
// Note:
// Due to floating point to integer round off, a call to HLStoRGB/HSVtoRGB followed by
// a call to RGBtoHLS/RGBtoHSV will not yield the original values.
//
// A call to RGBtoHLS followed by a call to HLStoRGB will yield the original
// RGB values.

class CColorMapper
{
public:
   CColorMapper(COLORREF color = RGB(0,0,0));

   COLORREF GetCOLORREF();
   void SetCOLORREF( COLORREF color);

   void SetRGB(int r, int g, int b); 
   void GetRGB(int* r, int* g, int* b);

   void SetHLS(double  h, double  l, double s);
   void GetHLS(double* h, double* l, double *s);

   void SetHSV(double  h, double  s, double v);
   void GetHSV(double* h, double* s, double *v);

   // statics - used to do work.
   static void HLStoRGB(double h,double l,double s,int *r,int *g,int *b);
   static void RGBtoHLS(int r,int g,int b,double *h,double *l,double *s);

   static void HSVtoRGB(double h,double s,double v,int *r,int *g,int *b);
   static void RGBtoHSV(int r,int g,int b,double *h,double *s,double *v);

#if defined (GEN_DEBUG_CODE)
   static bool Test();
#endif

private:
   static double ComputeValue(double n1,double n2,double hue);
   COLORREF m_COLORREF;
};


// Color iterator class - used for creating gradient fill patterns - allows you to pick two colors
// and the number of steps between them and then iterate along the gradient
class CColorIterator
{
public:
   // constructor - two colors (start and end) and number of increments
   // RGB model
   CColorIterator( COLORREF startColor, COLORREF endColor, int numIcrements);
   // HLS model
   CColorIterator( double HStart, double LStart, double SStart, double HEnd, double LEnd, double SEnd, int numIcrements);

   // iteration and accessors
   int NumberOfIncrements() const;
   // zero-based access to gradient "collection"
   COLORREF Item(int inc);

private:
// internally we use HLS to perform mapping
   int m_NumIncs;
   double m_HStart;
   double m_LStart;
   double m_SStart;

   double m_HEnd;
   double m_LEnd;
   double m_SEnd;

   double m_HInc;
   double m_LInc;
   double m_SInc;

   CColorIterator();
};