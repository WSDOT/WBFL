///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfIBeamEndBlockGirderProfile
****************************************************************************/

#include <BridgeModeling\IBeamEndBlockGirderProfile.h>        // class implementation
#include <GeomModel\PrecastBeam.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfIBeamEndBlockGirderProfile::bmfIBeamEndBlockGirderProfile(Float64 w1, Float64 w2, Float64 w3, Float64 w4,
                                                             Float64 d1, Float64 d2, Float64 d3, Float64 d4, 
                                                             Float64 d5, Float64 d6, Float64 d7,
                                                             Float64 t1, Float64 t2, 
                                                             Float64 EndBlockWidth, Float64 EndBlockLength)
{
   m_W1 = w1;
   m_W2 = w2;
   m_W3 = w3;
   m_W4 = w4;

   m_D1 = d1;
   m_D2 = d2;
   m_D3 = d3;
   m_D4 = d4;
   m_D5 = d5;
   m_D6 = d6;
   m_D7 = d7;

   m_T1 = t1;
   m_T2 = t2;

   m_EndBlockWidth  = EndBlockWidth;
   m_EndBlockLength = EndBlockLength;
}

bmfIBeamEndBlockGirderProfile::~bmfIBeamEndBlockGirderProfile()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bmfGirderProfile* bmfIBeamEndBlockGirderProfile::CreateClone() const
{
   return new bmfIBeamEndBlockGirderProfile(m_W1, m_W2, m_W3, m_W4,
                                            m_D1, m_D2, m_D3, m_D4, 
                                            m_D5, m_D6, m_D7,
                                            m_T1, m_T2,
                                            m_EndBlockWidth,m_EndBlockLength);
}

gmIShape* bmfIBeamEndBlockGirderProfile::CreateShape(Float64 x,Float64 girderLength) const
{
   Float64 Wt, Wb;
   GetEndBlockDimension(x,girderLength,&Wt,&Wb);

   Float64 w1, w2, w3, w4;
   Float64 d1, d2, d3, d4, d5, d6, d7;
   Float64 t1, t2;

   w1 = m_W1;
   w2 = m_W2;
   w3 = m_W3;
   w4 = m_W4;
   d1 = m_D1;
   d2 = m_D2;
   d3 = m_D3;
   d4 = m_D4;
   d5 = m_D5;
   d6 = m_D6;
   d7 = m_D7;
   t1 = Wt;
   t2 = Wb;

   if ( Wt/2 > m_W2 + m_T1/2 )
   {
      w2 = 0;
      w1 = m_W1 + m_W2 + m_T1/2 - Wt/2;
      d2 = (m_D2/m_W1)*w1;
      d3 = m_D3 + (m_D2 - d2);
   }
   else if ( Wt/2 > m_T1/2 )
   {
      w2 = m_W2 + m_T1/2 - Wt/2;
      d3 = (m_D3/m_W2)*w2;
      d7 += (m_D3 - d3);
   }

   if ( Wb/2 > m_W4 + m_T2/2 )
   {
      w4 = 0;
      w3 = m_W3 + m_W4 + m_T2/2 - Wb/2;
      w3 = (IsZero(w3) ? 0 : w3); // eliminate noise
      d5 = (m_D5/m_W3)*w3;
      d6 = m_D6 + (m_D5 - d5);
   }
   else if ( Wb/2 > m_T2/2 )
   {
      w4 = m_W4 + m_T2/2 - Wb/2;
      d6 = (m_D6/m_W4)*w4;
      d7 += m_D6 - d6;
   }

   CHECK(IsEqual(d1+d2+d3+d4+d5+d6+d7,m_D1+m_D2+m_D3+m_D4+m_D5+m_D6+m_D7));

   gmPrecastBeam* pBeam = new gmPrecastBeam(w1, w2, w3, w4,
                                            d1, d2, d3, d4, d5, d6, d7,
                                            t1, t2,
                                            gpPoint2d(0,d1+d2+d3+d4+d5+d6+d7));

   return pBeam;
}

Float64 bmfIBeamEndBlockGirderProfile::GetEndBlockLength() const
{
   return m_EndBlockLength;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfIBeamEndBlockGirderProfile::GetEndBlockDimension(Float64 x,Float64 girderLength,Float64* pWt,Float64* pWb) const
{
   if ( x < m_EndBlockLength || (girderLength-m_EndBlockLength) < x )
   {
      if ( x > m_EndBlockLength )
         x = girderLength - x;


      *pWt = ((m_EndBlockLength-x)/m_EndBlockLength)*(m_EndBlockWidth - m_T1) + m_T1;
      *pWb = ((m_EndBlockLength-x)/m_EndBlockLength)*(m_EndBlockWidth - m_T2) + m_T2;
   }
   else
   {
      *pWt = m_T1;
      *pWb = m_T2;
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

