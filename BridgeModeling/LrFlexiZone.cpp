///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfLrFlexiZone
****************************************************************************/

#include <BridgeModeling\LrFlexiZone.h>
#include <BridgeModeling\Girder.h>
#include <BridgeModeling\lrLayout.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfLrFlexiZone::bmfLrFlexiZone() :
bmfLrZone(),
m_Factor(0.0),
m_Justification(Left)
{
}



bmfLrFlexiZone::bmfLrFlexiZone(const bmfLrFlexiZone& rOther) :
bmfLrZone(rOther)
{
   MakeCopy(rOther);
}

bmfLrFlexiZone::~bmfLrFlexiZone()
{
}

//======================== OPERATORS  =======================================
bmfLrFlexiZone& bmfLrFlexiZone::operator= (const bmfLrFlexiZone& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

bmfLrZone* bmfLrFlexiZone::CreateClone() const
{
   return new bmfLrFlexiZone(*this);
}

//======================== ACCESS     =======================================
const bmfGirder* bmfLrFlexiZone::GetGirder() const
{
   const bmfLrLayout* pLay = this->GetLayout();
   CHECK(pLay!=0);
   return pLay->GetGirder();
}

bmfLrFlexiZone::ZoneJustification bmfLrFlexiZone::GetZoneJustification() const
{
   ASSERTVALID;
   return m_Justification;
}

void bmfLrFlexiZone::SetZoneJustification( bmfLrFlexiZone::ZoneJustification just)
{
   m_Justification = just;
}

Float64 bmfLrFlexiZone::GetFactor() const
{
   ASSERTVALID;
   return m_Factor;
}

void bmfLrFlexiZone::SetFactor(Float64 factor)
{
   m_Factor = factor;
}

void bmfLrFlexiZone::GetZoneLocation(Float64* zoneStart, Float64* zoneLength)const
{
   ASSERTVALID;
   Float64 gird_len = GetGirder()->GetLength();
   *zoneLength   = gird_len*m_Factor;

   if (m_Justification==Left)
      *zoneStart = 0.0;
   else if (m_Justification==Center)
      *zoneStart  = (gird_len - *zoneLength)/2.0;
   else if (m_Justification==Right)
      *zoneStart = gird_len - *zoneLength;
   else
      CHECK(0);
}


//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfLrFlexiZone::MakeCopy(const bmfLrFlexiZone& rOther)
{
   m_Factor  = rOther.m_Factor;
   m_Justification  = rOther.m_Justification;
}

void bmfLrFlexiZone::MakeAssignment(const bmfLrFlexiZone& rOther)
{
   bmfLrZone::MakeAssignment( rOther );
   MakeCopy( rOther );
}

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
bool bmfLrFlexiZone::AssertValid() const
{
   if (m_Factor<0.0 || m_Factor>1.0)
      return false;

   if (GetGirder()==0)
      return false;

   return bmfLrZone::AssertValid();
}

void bmfLrFlexiZone::Dump(dbgDumpContext& os) const
{
   bmfLrZone::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfLrFlexiZone::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfLrFlexiZone");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfLrFlexiZone");

   TESTME_EPILOG("LrFlexiZone");
}
#endif // _UNITTEST
