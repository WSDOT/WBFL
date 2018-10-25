///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
   bmfLrRowPattern
****************************************************************************/

#include <BridgeModeling\LrRowPattern.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfLrRowPattern::bmfLrRowPattern():
m_BarSpacing(0.0),
m_NumBars(0),
m_Orientation(HCenter)
{
}

bmfLrRowPattern::bmfLrRowPattern(const matRebar* pRebar, gpPoint2d anchor, Orientation orient,
                                 Uint32 numBars, Float64 spacing):
bmfLrPattern(pRebar),
m_BarSpacing(0.0),
m_NumBars(0),
m_Orientation(HCenter)
{
   ASSERTVALID;
}

bmfLrRowPattern::~bmfLrRowPattern()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bmfLrPattern* bmfLrRowPattern::CreateClone() const
{
   return new bmfLrRowPattern( *this );
}

Uint32 bmfLrRowPattern::GetNumBars() const
{
   return m_NumBars;
}

gpPoint2d bmfLrRowPattern::GetBarLocation(Uint32 barNum) const
{
   ASSERTVALID;
   PRECONDITION(barNum<m_NumBars);

   gpPoint2d point;
   switch (m_Orientation)
   {
   case Left:
      point.X() = m_AnchorPoint.X() + barNum*m_BarSpacing;
      point.Y() = m_AnchorPoint.Y();
      break;
   case HCenter:
      {
         Float64 bw = (m_NumBars-1)*m_BarSpacing/2.0;
         point.X() = m_AnchorPoint.X() - bw + barNum*m_BarSpacing;
         point.Y() = m_AnchorPoint.Y();
      }
      break;
   case Right:
      point.X() = m_AnchorPoint.X() - barNum*m_BarSpacing;
      point.Y() = m_AnchorPoint.Y();
      break;
   case Up:
      point.X() = m_AnchorPoint.X();
      point.Y() = m_AnchorPoint.Y() + barNum*m_BarSpacing;
      break;
   case VCenter:
      {
         Float64 bw = (m_NumBars-1)*m_BarSpacing/2.0;
         point.X() = m_AnchorPoint.X();
         point.Y() = m_AnchorPoint.Y() - bw + barNum*m_BarSpacing;
      }
      break;
      
   case Down:
      point.X() = m_AnchorPoint.X();
      point.Y() = m_AnchorPoint.Y() - barNum*m_BarSpacing;;
      break;
   default:
      CHECK(0);
   }

   return point;
}

void bmfLrRowPattern::SetNumBars(Uint32 numBars)
{
   m_NumBars = numBars;
}

gpPoint2d bmfLrRowPattern::GetAnchorPoint() const
{
   return m_AnchorPoint;
}

void bmfLrRowPattern::SetAnchorPoint(const gpPoint2d& point)
{
   m_AnchorPoint = point;
}

bmfLrRowPattern::Orientation bmfLrRowPattern::GetOrientation() const
{
   return m_Orientation;
}

void bmfLrRowPattern::SetOrientation(bmfLrRowPattern::Orientation orient)
{
   m_Orientation = orient;
}

Float64 bmfLrRowPattern::GetBarSpacing() const
{
   ASSERTVALID;
   return m_BarSpacing;
}

void bmfLrRowPattern::SetBarSpacing(Float64 spac)
{
   PRECONDITION(spac>=0.0);
   m_BarSpacing = spac;
}


//======================== ACCESS     =======================================

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
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bmfLrRowPattern::AssertValid() const
{
   if (m_BarSpacing<0)
      return false;

   return bmfLrPattern::AssertValid();
}

void bmfLrRowPattern::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfLrRowPattern" << endl;
   os << "m_BarSpacing = "<<m_BarSpacing << endl; 
   os << "m_NumBars = "<<m_NumBars << endl;
   os << "m_Orientation = "<<m_Orientation << endl;
   os << "m_Anchor X = "<<m_AnchorPoint.X()<<" Y = "<<m_AnchorPoint.Y()<<endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfLrRowPattern::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfLrRowPattern");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfLrRowPattern");

   TESTME_EPILOG("LrPattern");
}
#endif // _UNITTEST
