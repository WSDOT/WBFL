///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#ifndef INCLUDED_LRFD_LOADMODIFIER_H_
#define INCLUDED_LRFD_LOADMODIFIER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <LRFD\LrfdExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdLoadModifier

   Computes the load modifier used in limit state combinations.


DESCRIPTION
   Computes the load modifier used in limit state combinations.  See Article
   1.3.2.1


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.11.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLoadModifier
{
public:
   // GROUP: ENUMERATOR

   //------------------------------------------------------------------------
   enum Level { Low, Normal, High };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdLoadModifier();

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdLoadModifier(const lrfdLoadModifier& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdLoadModifier();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdLoadModifier& operator = (const lrfdLoadModifier& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Computes the load modifier. The type parameter is ignored if the current 
   // specification is lrfdVersionMgr::FirstEdition.
   Float64 LoadModifier(lrfdTypes::LimitState ls,lrfdTypes::Optimization opt = lrfdTypes::Max);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the load modifier for ductility.  If nd is zero, the load modifier
   // for is taken as 0.95 for Low, 1.0 for Normal and 1.05 for high.  nd
   // is ignored for Normal and the load modifier is always taken as 1.0.
   void SetDuctilityFactor(Level level,Float64 nd = 0.0);

   //------------------------------------------------------------------------
   // Returns the load modifier for ductility.
   Float64 GetDuctilityFactor() const;

   //------------------------------------------------------------------------
   // Returns an enumerated value indicating the level of ductility.
   Level GetDuctilityLevel() const;

   //------------------------------------------------------------------------
   // Sets the load modifier for importance.  If ni is zero, the load modifier
   // for is taken as 0.95 for Low, 1.0 for Normal and 1.05 for high.  ni
   // is ignored for Normal and the load modifier is always taken as 1.0.
   void SetImportanceFactor(Level level,Float64 ni = 0.0);

   //------------------------------------------------------------------------
   // Returns the load modifier for importance.
   Float64 GetImportanceFactor() const;

   //------------------------------------------------------------------------
   // Returns an enumerated value indicating the level of importance.
   Level GetImportanceLevel() const;

   //------------------------------------------------------------------------
   // Sets the load modifier for redundancy.  If nr is zero, the load modifier
   // for is taken as 0.95 for Low, 1.0 for Normal and 1.05 for high.  nr
   // is ignored for Normal and the load modifier is always taken as 1.0.
   void SetRedundancyFactor(Level level,Float64 nr = 0.0);

   //------------------------------------------------------------------------
   // Returns the load modifier for redundancy.
   Float64 GetRedundancyFactor() const;

   //------------------------------------------------------------------------
   // Returns an enumerated value indicating the level of redundancy.
   Level GetRedundancyLevel() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLoadModifier& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLoadModifier& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Ductility;
   Float64 m_Importance;
   Float64 m_Redundancy;
   Level   m_DuctilityLevel;
   Level   m_ImportanceLevel;
   Level   m_RedundancyLevel;

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

#endif // INCLUDED_LRFD_LOADMODIFIER_H_
