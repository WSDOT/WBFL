///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_MATERIAL_LINEARSTRESSSTRAINCURVE_H_
#define INCLUDED_MATERIAL_LINEARSTRESSSTRAINCURVE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Material\MaterialExp.h>
#include <Material\YieldStressStrainCurve.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class MATCLASS matMetal;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matLinearStressStrainCurve

   A concrete implementation of matYieldStressStrainCurve, provides a linear
   approximation for stress strain curves.


DESCRIPTION
   A concrete implementation of matYieldStressStrainCurve, provides a linear
   approximation for stress strain curves.  The stress-strain curve basically
   just "connects-the-dots".


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matLinearStressStrainCurve : public matYieldStressStrainCurve
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   matLinearStressStrainCurve();

   //------------------------------------------------------------------------
   // Constructor. Initializes the stress strain curve with the supplied parameters.
   matLinearStressStrainCurve(const std::_tstring& name,
                              Float64 E,
                              Float64 tensYieldStress,
                              Float64 compYieldStress,
                              Float64 tensUltStrain,
                              Float64 tensUltStress,
                              Float64 compUltStrain,
                              Float64 compUltStress,
                              Float64 fractureStrain,
                              Float64 fractureStress,
                              Float64 crushingStrain,
                              Float64 crushingStress);

   //------------------------------------------------------------------------
   matLinearStressStrainCurve(const std::_tstring& name,
                              Float64 E,
                              Float64 tensYieldStress,
                              Float64 tensUltStrain,
                              Float64 tensUltStress,
                              Float64 fractureStrain,
                              Float64 fractureStress);


   //------------------------------------------------------------------------
   matLinearStressStrainCurve(const matMetal& metal);

   //------------------------------------------------------------------------
   // Copy constructor
   matLinearStressStrainCurve(const matLinearStressStrainCurve& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matLinearStressStrainCurve();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matLinearStressStrainCurve& operator = (const matLinearStressStrainCurve& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a polymorphic type-safe clone of this curve.
   virtual matStressStrainCurve * CreateClone() const;

   //------------------------------------------------------------------------
   // Computes the stress for the given strain.  Returns the strain state
   // for the material for the given strain level.  If the return value
   // is Fractured or Crushed, the value pointed to
   // by pStress is undefined.  Throws a matXStressStrainEvalError
   // exception if an error occurs when evaluating the stress strain curve.
   virtual StrainState GetStress(Float64 strain,Float64* pStress) const;

   // GROUP: ACCESS
  
   //------------------------------------------------------------------------
   // Promote accessors
   matYieldStressStrainCurve::SetFractureStrain;
   matYieldStressStrainCurve::SetFractureStress;
   matYieldStressStrainCurve::SetCrushingStrain;
   matYieldStressStrainCurve::SetCrushingStress;
   matYieldStressStrainCurve::SetTensYieldStress;
   matYieldStressStrainCurve::SetCompYieldStress;
   matYieldStressStrainCurve::SetTensUltStrain;
   matYieldStressStrainCurve::SetTensUltStress;
   matYieldStressStrainCurve::SetCompUltStrain;
   matYieldStressStrainCurve::SetCompUltStress; 

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
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const matLinearStressStrainCurve& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const matLinearStressStrainCurve& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATERIAL_LINEARSTRESSSTRAINCURVE_H_
