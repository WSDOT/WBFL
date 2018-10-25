///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2016  Washington State Department of Transportation
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
#include <BridgeAnalysis\LiveLoad.h>
#include <float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamLiveLoad::bamLiveLoad(Int32 id,Int32 minLoadingId,Int32 maxLoadingId)
{
   m_ID = id;
   m_MinId = minLoadingId;
   m_MaxId = maxLoadingId;

   m_LaneLoad = 0;
   m_LaneLoadImpact = 1;
   m_TruckLoadImpact = 1;

}

bamLiveLoad::bamLiveLoad(const bamLiveLoad& rOther)
{
   MakeCopy( rOther );
}

bamLiveLoad::~bamLiveLoad()
{
}

bamLiveLoad& bamLiveLoad::operator=(const bamLiveLoad& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

void bamLiveLoad::AddTruck(const bamTruck& t)
{
   m_Trucks.push_back(t);
}

void bamLiveLoad::SetLaneLoad(Float64 w)
{
   m_LaneLoad = w;
}

void bamLiveLoad::SetTruckLoadImpact(Float64 impact)
{
   m_TruckLoadImpact = impact;
}

void bamLiveLoad::SetLaneLoadImpact(Float64 impact)
{
   m_LaneLoadImpact = impact;
}

IDType bamLiveLoad::GetMinLoadingId() const
{
   return m_MinId;
}

IDType bamLiveLoad::GetMaxLoadingId() const
{
   return m_MaxId;
}

void bamLiveLoad::SetMinLoadingId(IDType loadingId)
{
   m_MinId = loadingId;
}

void bamLiveLoad::SetMaxLoadingId(IDType loadingId)
{
   m_MaxId = loadingId;
}

AxleIndexType bamLiveLoad::GetNumAxles()
{
   AxleIndexType numAxles = 0;
   TruckIterator begin = m_Trucks.begin();
   TruckIterator end   = m_Trucks.end();
   while ( begin != end )
   {
      bamTruck truck = *begin++;
      numAxles += truck.GetNumAxles();
   }

   return numAxles;
}

void bamLiveLoad::GetAxle(AxleIndexType axleIndex,Float64& offset,Float64& weight)
{
	Float64 cumAxleDistance = 0;
	AxleIndexType cumAxleCount = 0;

   TruckIterator begin = m_Trucks.begin();
   TruckIterator end   = m_Trucks.end();
   while ( begin != end )
   {
      bamTruck truck = *begin++;
		AxleIndexType numAxles = truck.GetNumAxles();
		for(AxleIndexType axle = 0; axle < numAxles; axle++)
		{
		cumAxleDistance += truck.GetAxleSpacing(axle);
      if (cumAxleCount == axleIndex)
		   {
		      offset = cumAxleDistance;
            weight = truck.GetAxleWeight(axle);
			   return;
		   }
		cumAxleCount++;
		}
	}
}

bamTruck* bamLiveLoad::GetTruck(AxleIndexType axleIndex) 
{
	AxleIndexType cumAxleCount = 0;

   bamTruck* pTruck;

   TruckIterator begin = m_Trucks.begin();
   TruckIterator end   = m_Trucks.end();
   while ( begin != end )
   {
      pTruck = &(*begin++);
		cumAxleCount += pTruck->GetNumAxles();

		if (cumAxleCount >= axleIndex)
			return pTruck;
	}

   return 0;
}

Float64 bamLiveLoad::GetMinLength() const
{
   Float64 length = 0;

   ConstTruckIterator begin = m_Trucks.begin();
   ConstTruckIterator end   = m_Trucks.end();
   while ( begin != end )
   {
      const bamTruck* pTruck = &(*begin++);
      length += pTruck->GetMinLength();
	}

   return length;
}

Float64 bamLiveLoad::GetMaxLength() const
{
   Float64 length = 0;

   ConstTruckIterator begin = m_Trucks.begin();
   ConstTruckIterator end   = m_Trucks.end();
   while ( begin != end )
   {
      const bamTruck* pTruck = &(*begin++);
      length += pTruck->GetMaxLength();
	}

   return length;
}

bool bamLiveLoad::operator == (const bamLiveLoad& other) const
{
   return m_ID == other.GetID();
}

void bamLiveLoad::MakeCopy( const bamLiveLoad& rOther )
{
   m_ID = rOther.GetID();

   m_MinId = rOther.m_MinId;
   m_MaxId = rOther.m_MaxId;

   m_LaneLoad = rOther.GetLaneLoad();
   m_LaneLoadImpact = rOther.GetLaneLoadImpact();
   m_TruckLoadImpact = rOther.GetTruckLoadImpact();

   m_Trucks = rOther.m_Trucks;
}

void bamLiveLoad::MakeAssignment( const bamLiveLoad& rOther )
{
   //Base::MakeAssignment( rOther );
   MakeCopy( rOther );
}


//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamLiveLoad::AssertValid() const
{
   return true;
}

void bamLiveLoad::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamLiveLoad" << endl;
   os << "m_ID = " << m_ID << endl;
   os << "m_MinId = " << m_MinId << endl;
   os << "m_MaxId = " << m_MaxId << endl;
   os << "m_LaneLoad = " << m_LaneLoad << endl;
   os << "m_LaneLoadImpact = " << m_LaneLoadImpact << endl;
   os << "m_TruckLoadImpact = " << m_TruckLoadImpact << endl;

   os << "Trucks" << endl;
   TruckContainer::const_iterator iter;
   for ( iter = m_Trucks.begin(); iter != m_Trucks.end(); iter++ )
   {
      (*iter).Dump(os);
      os << endl;
   }


}
#endif // _DEBUG

#if defined _UNITTEST
bool bamLiveLoad::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamLiveLoad");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamLiveLoad");

   TESTME_EPILOG("LiveLoad");
}
#endif // _UNITTEST
