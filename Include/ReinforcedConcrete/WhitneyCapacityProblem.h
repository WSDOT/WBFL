///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#ifndef INCLUDED_REINFORCEDCONCRETE_WHITNEYCAPACITYPROBLEM_H_
#define INCLUDED_REINFORCEDCONCRETE_WHITNEYCAPACITYPROBLEM_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <ReinforcedConcrete\ReinfConcExp.h>
#include <ReinforcedConcrete\CapacityProblem.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rcaWhitneyCapacityProblem

   Derived from CapacityProblem,  this class computes the forces in a
   concrete section using the Whitney method.


DESCRIPTION
   Overrides the DoCaluclateCompressionBlock method to create a compression
   block offset equal to Beta1*c


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 01.22.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaWhitneyCapacityProblem : public rcaCapacityProblem
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rcaWhitneyCapacityProblem();

   //------------------------------------------------------------------------
   // Copy constructor
   rcaWhitneyCapacityProblem(const rcaWhitneyCapacityProblem& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaWhitneyCapacityProblem();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaWhitneyCapacityProblem& operator = (const rcaWhitneyCapacityProblem& rOther);

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
   // DoCreateMildSteelMaterialModel
   // Called by AddMildSteel() when a steel material is added to the problem.
   // This is a factory method that creates a stress strain curve for mild steel.
   // The default behavior of this method is to create a matBilinearCurve 
   // material model.
   virtual matYieldStressStrainCurve* DoCreateMildSteelMaterialModel(const matMetal& steel);

   //------------------------------------------------------------------------
   // DoCreateStrandMaterialModel
   // Called by AddStrand() when a strand material is added to the problem.  
   // This is a factory method that creates a stress strain curve for prestress
   // strands.  The default behavior of this method is to create a 
   // matPsStrandCurve material model.
   virtual matYieldStressStrainCurve* DoCreateStrandMaterialModel(const matPsStrand& strand);

   //------------------------------------------------------------------------
   // GetBeta1
   // Get Beta1 for the current nuetral axis configuration.
   // Calculated based on an average of the areas of the concrete elements above
   // the nuetral axis.
   virtual Float64 GetBeta1() const;

   //------------------------------------------------------------------------
   void MakeCopy(const rcaWhitneyCapacityProblem& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const rcaWhitneyCapacityProblem& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void Clean();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFORCEDCONCRETE_WHITNEYCAPACITYPROBLEM_H_
