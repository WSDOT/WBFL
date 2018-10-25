///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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
   bmfLrLayout
****************************************************************************/

#include <BridgeModeling\LrLayout.h>
#include <BridgeModeling\LrZone.h>
#include <BridgeModeling\LrRowPattern.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfLrLayout::bmfLrLayout():
m_pGirder(0)
{
}

bmfLrLayout::bmfLrLayout(const bmfGirder* pGirder):
m_pGirder(pGirder)
{
   CHECK(m_pGirder!=0);
}

bmfLrLayout::bmfLrLayout(const bmfLrLayout& rOther)
{
   MakeCopy(rOther);
}

bmfLrLayout::~bmfLrLayout()
{
}

//======================== OPERATORS  =======================================
bmfLrLayout& bmfLrLayout::operator= (const bmfLrLayout& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
const bmfGirder* bmfLrLayout::GetGirder() const
{
   return m_pGirder;
}

void bmfLrLayout::SetGirder(const bmfGirder* pGirder)
{
   CHECK(pGirder!=0);
   m_pGirder = pGirder;
}


ZoneIndexType bmfLrLayout::GetNumZones() const
{
   ASSERTVALID;
   return m_ZoneVec.size();
}

bmfLrZone* bmfLrLayout::GetZone(ZoneIndexType zoneNum) const
{
   ASSERTVALID;
   PRECONDITION (zoneNum<m_ZoneVec.size());
   return m_ZoneVec[zoneNum].get();
}

ZoneIndexType bmfLrLayout::AddZone(bmfLrZone* pZone)
{
   // zone belongs to us now
   pZone->SetLayout(this);

   ZonePtr ptr(pZone);
   m_ZoneVec.push_back(ptr);
   return m_ZoneVec.size();
}

bmfLrLayout::RebarInstanceList bmfLrLayout::GetRebarsAtCut(Float64 cutLocation) const
{
   // iterate through all zones and patterns and return all bars
   RebarInstanceList the_list;

   for (ZoneVecConstIterator i=m_ZoneVec.begin(); i!=m_ZoneVec.end(); i++)
   {
      Float64 nearest_end;
      if ((*i)->IsInZone(cutLocation,&nearest_end))
      {
         // cut location is in zone, need to add bar instances to list
         CollectionIndexType num_pats = (*i)->GetNumPatterns();
         for (CollectionIndexType j=0; j<num_pats; j++)
         {
            const bmfLrPattern* pPat = (*i)->GetPattern(j);
            CHECK(pPat!=0);
            const matRebar* pmat = pPat->GetRebar();
            CHECK(pmat!=0);

            CollectionIndexType num_bars = pPat->GetNumBars();
            for (CollectionIndexType k=0; k<num_bars; k++)
            {
               gpPoint2d pt = pPat->GetBarLocation(k);

               // finally, can add bar instance to list
               the_list.push_back(RebarInstance(pt,pmat,nearest_end));
            }
         }
      }
   }

   return the_list;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfLrLayout::MakeCopy(const bmfLrLayout& rOther)
{
   m_pGirder = rOther.m_pGirder;

   // copy zones
   // assign them to new layout
   for(ZoneVecConstIterator i=rOther.m_ZoneVec.begin(); i!=rOther.m_ZoneVec.end(); i++)
   {
      ZonePtr ptr((*i)->CreateClone());
      ptr->SetLayout(this);
      m_ZoneVec.push_back(ptr);
   }
}

void bmfLrLayout::MakeAssignment(const bmfLrLayout& rOther)
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
bool bmfLrLayout::AssertValid() const
{
//   if (m_pGirder==0)
//      return false;

   return true;
}

void bmfLrLayout::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfLrLayout" << endl;
   os << "m_pGirder = "<< (Uint32)m_pGirder<<endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfLrLayout::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfLrLayout");


   TESTME_EPILOG("LrLayout");
}
#endif // _UNITTEST
