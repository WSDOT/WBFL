///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_REINFCONC_REINFORCEMENTELEMENT_H_
#define INCLUDED_REINFCONC_REINFORCEMENTELEMENT_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <ReinforcedConcrete\ReinfConcExp.h>
#include <GeometricPrimitives\GeometricPrimitives.h>
#include <GeomModel\IShape.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class rcaCapacityProblem;
class grlibPointMapper;
class matYieldStressStrainCurve;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rcaReinforcementElement

   Element in a CapacityProblem.


DESCRIPTION
   Represents metal reinforcement in a rc capacity problem


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 01.20.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaReinforcementElement
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor.
   // rcaReinforcementElement
   rcaReinforcementElement(const gmIShape& shape, 
                           const matYieldStressStrainCurve& rMaterialModel, 
                           const rcaCapacityProblem& rProblem, 
                           Float64 initStrain = 0);

   //------------------------------------------------------------------------
   // Copy constructor
   rcaReinforcementElement(const rcaReinforcementElement& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaReinforcementElement();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaReinforcementElement& operator = (const rcaReinforcementElement& rOther);

   // GROUP: OPERATIONS


   //------------------------------------------------------------------------
   // SetProblem
   // Associates this element with the capacity problem that it is a part of.
   void SetProblem(const rcaCapacityProblem& rProblem);

   //------------------------------------------------------------------------
   // GetProblem
   // Returns a reference to the capacity problem that this element is a part of.
   const rcaCapacityProblem& GetProblem() const;

   //------------------------------------------------------------------------
   // GetForces
   // Computes the local forces on this element.
   virtual void GetForces(Float64* pFz,
                          Float64* pMx,
                          Float64* pMy,
                          gpPoint2d* cg) const;

   //------------------------------------------------------------------------
   // GetShape
   // Returns a reference to the element’s shape.
   const gmIShape& GetShape() const;

   //------------------------------------------------------------------------
   // GetInitialStrain
   // Returns the initial strain of the element.
   Float64 GetInitialStrain() const;

   //------------------------------------------------------------------------
   // GetStressStrainCurve
   // Returns a reference to the stress strain curve associated with this element.
   const matYieldStressStrainCurve& GetStressStrainCurve() const;

   //------------------------------------------------------------------------
   // GetBoundingBox
   // Returns the bounding box of the element.
   gpRect2d GetBoundingBox() const;

   //------------------------------------------------------------------------
   // Draw
   // Draws the element on the given device context using the give mapper.
   void Draw(HDC hDC, const grlibPointMapper& mapper) const;

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
   void MakeCopy(const rcaReinforcementElement& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const rcaReinforcementElement& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   gmIShape* m_pShape;
   Float64   m_InitialStrain;
   const rcaCapacityProblem* m_pProblem;
   const matYieldStressStrainCurve* m_pCurve;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   rcaReinforcementElement();
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

#endif // INCLUDED_REINFCONC_REINFORCEMENTELEMENT_H_
