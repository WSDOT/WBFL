///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_LIVELOAD_H_
#define INCLUDED_BRIDGEANALYSIS_LIVELOAD_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\Truck.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

class BAMCLASS bamLiveLoad
{
public:
   // LIFECYCLE

   // Method:      LiveLoad
   // Description: Default c'tor
   // Return:      N/A
   bamLiveLoad(Int32 id,Int32 minLoadingId,Int32 maxLoadingId);

   // Method:      LiveLoad
   // Description: Copy c'tor
   // Return:      N/A
   bamLiveLoad(const bamLiveLoad& rOther);

   // Method:      ~LiveLoad
   // Description: d'tor
   // Return:      N/A
   virtual ~bamLiveLoad(); 

   // OPERATORS

   // Method:      operator =
   // Description: Assignment operator
   // Return:      Reference to self
   bamLiveLoad& operator = (const bamLiveLoad& rOther);

   // Method:      operator ==
   // Description: Equality operator
   // Return:      True if the two live loads are equal
   bool operator == (const bamLiveLoad& rOther) const;

   // OPERATIONS

   // Method:      AddTruck
   // Description: Adds a truck to the live load
   // Return:      None
   void AddTruck(const bamTruck& t);

   // ACCESS

   // Method:      SetLaneLoad
   // Description: Sets the intensity of the lane load
   // Return:      None
   void SetLaneLoad(Float64 w);

   // These need to be replaced with an Impact object
   void SetTruckLoadImpact(Float64 impact);
   void SetLaneLoadImpact(Float64 impact);

   void SetID(Int32 id);
   Int32 GetID() const;
   Float64 GetLaneLoad() const;
   Float64 GetLaneLoadImpact() const;
   Float64 GetTruckLoadImpact() const;

   Int32 GetMinLoadingId() const;
   Int32 GetMaxLoadingId() const;
   void SetMinLoadingId(Int32 loadingId);
   void SetMaxLoadingId(Int32 loadingId);

   // Interface to allow the truck train to be accessed as one giant truck
   Int32 GetNumAxles();
   void GetAxle(Int32 axleIndex,Float64& offset,Float64& weight);

   Float64 GetMinLength() const;
   Float64 GetMaxLength() const;

   // INQUIRY

protected:
   // DATA MEMBERS
   Int32 m_ID;
   Float64 m_LaneLoad;
   Float64 m_LaneLoadImpact;
   Float64 m_TruckLoadImpact;

   // :COMPILER: rab 11.17.96 : Supressed warning
   // :FILE: LiveLoad.h
   // Warning C4251 has been suppressed.
   // not be exported.
   typedef std::vector<bamTruck> TruckContainer;
   typedef TruckContainer::iterator TruckIterator;
   typedef TruckContainer::const_iterator ConstTruckIterator;
   #pragma warning (disable : 4251)
   TruckContainer m_Trucks;

   Int32 m_MinId; // id for the min envelope
   Int32 m_MaxId; // id for the max envelope

   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   void MakeCopy( const bamLiveLoad& rOther );
   void MakeAssignment( const bamLiveLoad& rOther );

   // ACCESS
   bamTruck* GetTruck(Int32 axleIndex);

   // INQUIRY

private:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//
inline void bamLiveLoad::SetID(Int32 id) { m_ID = id; }
inline Int32 bamLiveLoad::GetID() const {return m_ID;}
inline Float64 bamLiveLoad::GetLaneLoad() const {return m_LaneLoad;}
inline Float64 bamLiveLoad::GetLaneLoadImpact() const {return m_LaneLoadImpact;}
inline Float64 bamLiveLoad::GetTruckLoadImpact() const {return m_TruckLoadImpact;}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LIVELOAD_H_
