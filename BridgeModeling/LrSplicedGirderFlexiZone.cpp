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

/****************************************************************************
CLASS
   bmfLrSplicedGirderFlexiZone
****************************************************************************/

#include <BridgeModeling\LrSplicedGirderFlexiZone.h>
#include <BridgeModeling\lrLayout.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfLrSplicedGirderFlexiZone::bmfLrSplicedGirderFlexiZone(SegmentIndexType segment) :
m_Segment(segment)
{
}




bmfLrSplicedGirderFlexiZone::bmfLrSplicedGirderFlexiZone(const bmfLrSplicedGirderFlexiZone& rOther) :
bmfLrFlexiZone(rOther)
{
   MakeCopy(rOther);
}

bmfLrSplicedGirderFlexiZone::~bmfLrSplicedGirderFlexiZone()
{
}

//======================== OPERATORS  =======================================
bmfLrSplicedGirderFlexiZone& bmfLrSplicedGirderFlexiZone::operator= (const bmfLrSplicedGirderFlexiZone& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

bmfLrZone* bmfLrSplicedGirderFlexiZone::CreateClone() const
{
   return new bmfLrSplicedGirderFlexiZone(*this);
}

//======================== ACCESS     =======================================
const bmfSplicedGirder* bmfLrSplicedGirderFlexiZone::GetSplicedGirder() const
{
   const bmfLrLayout* pLay = this->GetLayout();
   CHECK(pLay!=0);

   const bmfGirder* girder = pLay->GetGirder();   

   const bmfSplicedGirder* sgirder = dynamic_cast<const bmfSplicedGirder*>(girder);
   CHECK(sgirder!=NULL);

   return sgirder;
}


void bmfLrSplicedGirderFlexiZone::GetSegmentZoneLocation(Float64* zoneStart, Float64* zoneLength)const
{
   ASSERTVALID;
   Float64 gird_len = GetSplicedGirder()->GetSegmentLength(m_Segment);
   *zoneLength   = gird_len*GetFactor();

   switch(this->GetZoneJustification())
   {
   case Left:
         *zoneStart = 0.0;
         break;
   case Center:
         *zoneStart  = (gird_len - *zoneLength)/2.0;
         break;
   case Right:
         *zoneStart = gird_len - *zoneLength;
         break;
   default:
         CHECK(0);
   }
}

void bmfLrSplicedGirderFlexiZone::GetZoneLocation(Float64* zoneStart, Float64* zoneLength)const
{
   ASSERTVALID;

   // location wrt start of this segment
   Float64 segzon_start;
   this->GetSegmentZoneLocation(&segzon_start, zoneLength);

   // now need location of start of this segment from girder start
   const bmfSplicedGirder* pgird = this->GetSplicedGirder();

   Float64 start_loc=0.0;
   // add up previous segment and closure pour lengths
   for (SegmentIndexType seg=0; seg<m_Segment; seg++)
   {
      start_loc += pgird->GetSegmentLength(seg);
      start_loc += pgird->GetClosurePourSize(seg);
   }

   *zoneStart = start_loc + segzon_start;
}

SegmentIndexType bmfLrSplicedGirderFlexiZone::GetSegment()const
{
   ASSERTVALID;
   return m_Segment;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfLrSplicedGirderFlexiZone::MakeCopy(const bmfLrSplicedGirderFlexiZone& rOther)
{
   m_Segment  = rOther.m_Segment;
}

void bmfLrSplicedGirderFlexiZone::MakeAssignment(const bmfLrSplicedGirderFlexiZone& rOther)
{
   bmfLrFlexiZone::MakeAssignment( rOther );
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
bool bmfLrSplicedGirderFlexiZone::AssertValid() const
{
   if (m_Segment<0)
      return false;

   return bmfLrFlexiZone::AssertValid();
}

void bmfLrSplicedGirderFlexiZone::Dump(dbgDumpContext& os) const
{
   bmfLrFlexiZone::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfLrSplicedGirderFlexiZone::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfLrSplicedGirderFlexiZone");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfLrSplicedGirderFlexiZone");

   TESTME_EPILOG("LrSplicedGirderFlexiZone");
}
#endif // _UNITTEST
