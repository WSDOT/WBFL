///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEANALYSIS_POINTOFINTEREST_H_
#define INCLUDED_BRIDGEANALYSIS_POINTOFINTEREST_H_
#pragma once

#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <set>

struct BAMCLASS bamStressPoint
{
   CollectionIndexType m_ID;
   Float64 m_S;

   bool operator<(const bamStressPoint& rOther) const
   {
      return m_ID < rOther.m_ID;
   }
};

struct BAMCLASS bamPointOfInterest
{
   bamPointOfInterest() {}
   virtual ~bamPointOfInterest() {}
   bamPointOfInterest(const bamPointOfInterest& poi);
   bamPointOfInterest& operator = (const bamPointOfInterest& poi);

   PoiIDType m_ID;
   SpanIDType m_SpanId;
   Float64 m_Offset;
   Float64 m_AbsLocation;

   std::set<bamStressPoint> m_StressPoints;

   void AddStressPoint(CollectionIndexType idx,Float64 S)
   {
      bamStressPoint sp;
      sp.m_ID = idx;
      sp.m_S = S;
      m_StressPoints.insert( sp );
   }

   void RemoveStressPoint(CollectionIndexType idx)
   {
      bamStressPoint sp;
      sp.m_ID = idx;
      m_StressPoints.erase( sp );
   }

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const
   {
      return true;
   }

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const
   {
      os << "Dump for bamPointOfInterest" << endl;
      os << "m_ID          = " << m_ID << endl;
      os << "m_SpanId      = " << m_SpanId << endl;
      os << "m_Offset      = " << m_Offset << endl;
      os << "m_AbsLocation = " << m_AbsLocation << endl;
      if ( m_StressPoints.size() > 0 )
      {
         os << "Stress Points" << endl;
         std::set<bamStressPoint>::const_iterator iter;
         for ( iter = m_StressPoints.begin(); iter != m_StressPoints.end(); iter++ )
         {
            os << "m_ID = " << (*iter).m_ID << endl;
            os << "m_S  = " << (*iter).m_S  << endl;
            os << endl;
         }
      }
   }
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog)
   {
      return true;
   }
   #endif // _UNITTEST
};

inline bamPointOfInterest::bamPointOfInterest(const bamPointOfInterest& poi)
{
   m_ID          = poi.m_ID;
   m_SpanId      = poi.m_SpanId;
   m_Offset      = poi.m_Offset;
   m_AbsLocation = poi.m_AbsLocation;
   m_StressPoints = poi.m_StressPoints;
}

inline bamPointOfInterest& bamPointOfInterest::operator= (const bamPointOfInterest& poi)
{
   m_ID          = poi.m_ID;
   m_SpanId      = poi.m_SpanId;
   m_Offset      = poi.m_Offset;
   m_AbsLocation = poi.m_AbsLocation;
   m_StressPoints = poi.m_StressPoints;

   return *this;
}

#endif // INCLUDED_BRIDGEANALYSIS_POINTOFINTEREST_H_