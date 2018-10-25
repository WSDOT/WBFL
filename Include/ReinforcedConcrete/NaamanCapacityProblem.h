///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_REINFORCEDCONCRETE_NAAMANCAPACITYPROBLEM_H_
#define INCLUDED_REINFORCEDCONCRETE_NAAMANCAPACITYPROBLEM_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <ReinforcedConcrete\ReinfConcExp.h>
#include <ReinforcedConcrete\WhitneyCapacityProblem.h>
#include <Math\Function2d.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rcaNaamanCapacityProblem

   Derived from CapacityProblem,  this class computes the forces in a
   concrete section using the Naaman method.


DESCRIPTION
   Overrides the DoCaluclateCompressionBlock method to create a compression
   block offset so that the block's area is equal to Beta1*c times the
   compression area above the n.a.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 01.22.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaNaamanCapacityProblem : public rcaWhitneyCapacityProblem, 
                                                private mathFunction2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rcaNaamanCapacityProblem();

   //------------------------------------------------------------------------
   // Copy constructor
   rcaNaamanCapacityProblem(const rcaNaamanCapacityProblem& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaNaamanCapacityProblem();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaNaamanCapacityProblem& operator = (const rcaNaamanCapacityProblem& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // DoCalculateCompressionBlockBoundary
   // Sets the location of the compression block boundary.  The offset is 
   // measured normal to the neutral axis line.
   virtual Float64 DoCalculateCompressionBlockBoundary();

   //------------------------------------------------------------------------
   void MakeCopy(const rcaNaamanCapacityProblem& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rcaNaamanCapacityProblem& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // status variables for the compression block offset calculation. These are
   // temporary values for the DoCalculateCompressionBlockBoundary and Evaluate
   // functions and do not need to be copied.
   Float64 m_TargetArea;
   gpLine2d m_NaLine;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Interface routine for function2d class. use this to calculate section
   // area as a function of compression block offset.
   Float64 Evaluate(Float64 x) const;

   mathFunction2d* Clone() const;

   void Init();
   void Clean();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFORCEDCONCRETE_NaamanCAPACITYPROBLEM_H_
