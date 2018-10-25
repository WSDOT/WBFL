///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bmfPierLayout           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeModeling\PierLayout.h>            // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bmfPierLayout::bmfPierLayout()
{
   m_Orientation = NormalToAlignment;
} // PierLayout

bmfPierLayout::bmfPierLayout(IAngle* pSkewAngle)
{
   m_Orientation = SkewAngle;
   m_SkewAngle.Release();
   pSkewAngle->Clone(&m_SkewAngle);
}

bmfPierLayout::bmfPierLayout(IDirection* pDirection)
{
   m_Orientation = Bearing;
   m_Direction.Release();
   pDirection->Clone(&m_Direction);
}

bmfPierLayout::bmfPierLayout(const bmfPierLayout& pl)
{
   *this = pl;
} // PierLayout

bmfPierLayout::~bmfPierLayout()
{
} // ~bmfPierLayout

//======================== OPERATORS  =======================================

bmfPierLayout& bmfPierLayout::operator = (const bmfPierLayout& pl)
{
   m_Orientation = pl.GetOrientation();

   m_SkewAngle.Release();
   m_Direction.Release();

   CComPtr<IAngle> skewAngle;
   CComPtr<IDirection> bearing;
   pl.GetSkewAngle(&skewAngle);
   pl.GetBearing(&bearing);

   m_SkewAngle.Release();
   m_Direction.Release();

   if ( skewAngle )
      skewAngle->Clone(&m_SkewAngle);

   if ( bearing )
      bearing->Clone(&m_Direction);

   return *this;
} // operator =

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================

void bmfPierLayout::SetLayout()
{
   m_Orientation = NormalToAlignment;
} // SetLayout

void bmfPierLayout::SetLayout(IAngle* pAngle)
{
   m_Orientation = SkewAngle;

   m_Direction.Release();

   m_SkewAngle.Release();
   pAngle->Clone(&m_SkewAngle);
}

void bmfPierLayout::SetLayout(IDirection* pDirection)
{
   m_Orientation = Bearing;

   m_SkewAngle.Release();
   m_Direction.Release();
   pDirection->Clone(&m_Direction);
}

void bmfPierLayout::SetLayoutAngle(Float64 angle)
{
   m_Orientation = SkewAngle;
   m_Direction.Release();

   if ( !m_SkewAngle )
      m_SkewAngle.CoCreateInstance(CLSID_Angle);

   m_SkewAngle->put_Value(angle);
}

void bmfPierLayout::SetLayoutBearing(Float64 direction)
{
   m_Orientation = Bearing;
   m_SkewAngle.Release();

   if ( !m_Direction )
      m_Direction.CoCreateInstance(CLSID_Direction);

   m_Direction->put_Value(direction);
}

bmfPierLayout::Orientation bmfPierLayout::GetOrientation() const
{
   return m_Orientation;
}

void bmfPierLayout::GetSkewAngle(IAngle** ppAngle) const
{
   if ( m_SkewAngle )
      m_SkewAngle->Clone(ppAngle);
   else
      (*ppAngle) = 0;
}

void bmfPierLayout::GetBearing(IDirection** ppDirection) const
{
   if ( m_Direction )
      m_Direction->Clone(ppDirection);
   else
      (*ppDirection) = 0;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
