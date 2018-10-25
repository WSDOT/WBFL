///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEANALYSIS_TRUCK_H_
#define INCLUDED_BRIDGEANALYSIS_TRUCK_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\AxleSpacing.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamTruck

   Encapsulates a live load truck object.


DESCRIPTION
   Encapsulates a live load truck object.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.08.1998 : Created file
*****************************************************************************/

class BAMCLASS bamTruck
{
public:
   // LIFECYCLE

   // Method:      bamTruck
   // Description: Default c'tor
   // Return:      N/A
   bamTruck();

   // Method:      bamTruck
   // Description: Copy c'tor
   // Return:      N/A
   bamTruck(const bamTruck& rOther);

   // Method:      ~bamTruck
   // Description: d'tor
   // Return:      N/A
   virtual ~bamTruck(); 

   // OPERATORS

   // Method:      operator =
   // Description: Assignment operator
   // Return:      Reference to self
   bamTruck& operator = (const bamTruck& rOther);

   // Method:      operator <
   // Description: Equality operator
   // Return:      True if the trucks are identical
   bool operator < (const bamTruck& rOther) const;
   bool operator == (const bamTruck& rOther) const;

   // OPERATIONS
   void AddAxle(Float64 wgt,bamAxleSpacing& space);
   
   // ACCESS
   Float64 GetAxleWeight(Int32 axleIndex);
   Float64 GetAxleSpacing(Int32 axleIndex);
   Int32 GetNumAxles();
   Float64 GetMinLength() const;
   Float64 GetMaxLength() const;

   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   void MakeCopy(const bamTruck& rOther);
   void MakeAssignment(const bamTruck& rOther);

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   // :COMPILER: rab 11.17.96 : Supressed warning
   // :FILE: Truck.h
   // Warning C4251 has been suppressed.
   // not be exported.
   typedef std::vector<Float64> AxleWgtContainer;
   typedef AxleWgtContainer::iterator AxleWgtIterator;
   typedef std::vector<bamAxleSpacing> SpacingContainer;
   typedef SpacingContainer::iterator SpacingIterator;

   #pragma warning (disable : 4251)
   AxleWgtContainer m_AxleWeight;
   SpacingContainer m_AxleSpacing;

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

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_TRUCK_H_
