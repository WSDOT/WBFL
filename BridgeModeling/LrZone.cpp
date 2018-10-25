///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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
   bmfLrZone
****************************************************************************/

#include <BridgeModeling\LrZone.h>
#include <BridgeModeling\LrPattern.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfLrZone::bmfLrZone():
m_pLayout(0)
{
}

bmfLrZone::bmfLrZone(const bmfLrZone& rOther)
{
   MakeCopy(rOther);
}

bmfLrZone::~bmfLrZone()
{
}

//======================== OPERATORS  =======================================
bmfLrZone& bmfLrZone::operator= (const bmfLrZone& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

CollectionIndexType bmfLrZone::GetNumPatterns() const
{
   return m_PatternVec.size();
}

bmfLrPattern* bmfLrZone::GetPattern(CollectionIndexType idx)
{
   PRECONDITION(idx < GetNumPatterns());
   return m_PatternVec[idx].get();
}

CollectionIndexType bmfLrZone::AddPattern(bmfLrPattern* pPattern)
{
   PRECONDITION(pPattern!=0);
   PatternPtr ptr(pPattern);
   m_PatternVec.push_back(ptr);
   return m_PatternVec.size();
}

bool bmfLrZone::IsInZone(Float64 testLoc, Float64* nearest)
{
   ASSERTVALID;
   Float64 zone_start, zone_length, zone_end;
   GetZoneLocation(&zone_start, &zone_length);
   zone_end = zone_start + zone_length;

   Float64 to_start = testLoc - zone_start;
   Float64 to_end   = zone_end - testLoc;
   *nearest = min(fabs(to_end),fabs(to_start));

   return (to_start>=0.0 && to_end>=0.0);
}

//======================== ACCESS     =======================================

const bmfLrLayout* bmfLrZone::GetLayout() const
{
   return m_pLayout;
}

void bmfLrZone::SetLayout(const bmfLrLayout* pLay)
{
   CHECK(pLay!=0);
   m_pLayout = pLay;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfLrZone::MakeCopy(const bmfLrZone& rOther)
{
   m_pLayout = rOther.m_pLayout;

   for (PatternVecConstIterator i= rOther.m_PatternVec.begin(); i!=rOther.m_PatternVec.end(); i++)
   {
      PatternPtr ptr((*i)->CreateClone());
      m_PatternVec.push_back(ptr);
   }

}

void bmfLrZone::MakeAssignment(const bmfLrZone& rOther)
{
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
bool bmfLrZone::AssertValid() const
{
   return true;
}

void bmfLrZone::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfLrZone" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfLrZone::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfLrZone");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfLrZone");

   TESTME_EPILOG("LrZone");
}
#endif // _UNITTEST
