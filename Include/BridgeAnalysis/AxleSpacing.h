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

#ifndef INCLUDED_BRIDGEANALYSIS_AXLESPACING_H_
#define INCLUDED_BRIDGEANALYSIS_AXLESPACING_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamAxleSpacing

   Encapsulates the spacing between axles on a truck or between rear and lead
   axles on adjacent trucks.

DESCRIPTION
   Encapsulates the spacing between axles on a truck or between rear and lead
   axles on adjacent trucks.  Axle spacings can be fixed, have their lower limit
   fix, have their upper limit fixed, or have both their upper and lower limits
   fixed.

COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.21.1998 : Created file
*****************************************************************************/

class BAMCLASS bamAxleSpacing
{
public:
   // GROUP: ENUMERATORS

   //------------------------------------------------------------------------
   enum Measure {Fixed, LowerBound, UpperBound, Bounded};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Method:      bamAxleSpacing
   // Description: Default c'tor
   // Return:      N/A
   bamAxleSpacing(Float64 minSpace = 0,
                  Float64 maxSpace = 0,
                  Measure measure = Fixed);

   //------------------------------------------------------------------------
   // Method:      bamAxleSpacing
   // Description: Copy c'tor
   // Return:      N/A
   bamAxleSpacing(const bamAxleSpacing& rOther);

   //------------------------------------------------------------------------
   // Method:      ~bamAxleSpacing
   // Description: d'tor
   // Return:      N/A
   virtual ~bamAxleSpacing(); 

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Method:      operator =
   // Description: Assignment operator
   // Return:      Reference to self
   bamAxleSpacing& operator = (const bamAxleSpacing& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Method:      SetSpacing
   // Description: Sets the axle spacing parameters
   // Return:      None
   void SetSpacing(Measure measure,Float64 minSpace,Float64 maxSpace=0.);

   //------------------------------------------------------------------------
   // Method:      GetMinSpacing
   // Description: 
   // Return:      Returns the minimum axle spacing
   Float64 GetMinSpacing() const;

   //------------------------------------------------------------------------
   // Method:      GetMaxSpacing
   // Description: 
   // Return:      Returns the maximum axle spacing
   Float64 GetMaxSpacing() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   Measure m_Measure;
   Float64 m_MinSpacing;
   Float64 m_MaxSpacing;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   void MakeCopy(const bamAxleSpacing& rOther);
   void MakeAssignment(const bamAxleSpacing& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

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

#endif // INCLUDED_BRIDGEANALYSIS_AXLESPACING_H_
