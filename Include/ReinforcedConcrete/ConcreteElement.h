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

#ifndef INCLUDED_REINFCONC_CONCRETEELEMENT_H_
#define INCLUDED_REINFCONC_CONCRETEELEMENT_H_
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

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rcaConcreteElement

   Element in a CapacityProblem.


DESCRIPTION
   Returns force for capacity problem. 
   The stress on the element,  for any compressive strain is 0.85f’c.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 01.19.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaConcreteElement
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // rcaConcreteElement
   // Creates a concrete element with the shape rShape.
   // This version allows the n factor to be defined explicitely.
   rcaConcreteElement(const gmIShape& rShape, CollectionIndexType concreteIdx, Float64 nFactor,
                      const rcaCapacityProblem& rProblem);

   //------------------------------------------------------------------------
   // rcaConcreteElement
   // Creates a concrete element with the shape rShape.  
   // For this version, the n factor is calculated based on the material defined
   // by concreteKey for the given rcaCapacityProblem.
   rcaConcreteElement(const gmIShape& rShape, CollectionIndexType concreteIdx, 
                      const rcaCapacityProblem& rProblem);

   //------------------------------------------------------------------------
   // Copy constructor
   rcaConcreteElement(const rcaConcreteElement& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaConcreteElement();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaConcreteElement& operator = (const rcaConcreteElement& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // GetProblem
   // Returns a reference to the capacity problem that this element is a part
   // of.
   const rcaCapacityProblem& GetProblem() const;

   //------------------------------------------------------------------------
   // GetForces
   // Computes the resultant local forces on this element and the point of 
   // application of the forces.  Uses the compression block boundary to 
   // determine if the entire element is in compression.  If not,  the 
   // element is clipped to the compression block boundary.
   virtual void GetForces(Float64* pFz,
                          Float64* pMx,
                          Float64* pMy,
                          gpPoint2d* cg) const;

   //------------------------------------------------------------------------
   // GetClippedArea
   // Returns the clipped area of an element - the area is the shape area multiplied
   // by the N factor.
   Float64 GetClippedArea(const gpLine2d& clipLine, gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   // GetArea
   // Returns the area of an element - the area is the shape area multiplied
   // by the N factor.
   Float64 GetArea() const;

   //------------------------------------------------------------------------
   // GetShape
   // Returns a reference to the element’s shape.
   const gmIShape& GetShape() const;

   //------------------------------------------------------------------------
   // GetConcreteIdx
   // Returns the index of the concrete associated with this element
   CollectionIndexType GetConcreteIdx() const;

   //------------------------------------------------------------------------
   // GetFc
   // Returns the concrete compressive strength associated with this element.
   Float64 GetFc() const;

   //------------------------------------------------------------------------
   // GetN
   // Returns the factor N associated with this element.
   Float64 GetN() const;

   //------------------------------------------------------------------------
   // GetBoundingBox
   // Returns the bounding box of the element.
   gpRect2d GetBoundingBox() const;

   //------------------------------------------------------------------------
   // Draw
   // Draws the element on the given device context using the given mapper.
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
   void MakeCopy(const rcaConcreteElement& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const rcaConcreteElement& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::auto_ptr<gmIShape> m_pShape;
   CollectionIndexType     m_ConcreteKey;
   mutable bool      m_IsNSpecified;
   mutable Float64   m_N;
   const rcaCapacityProblem* m_pProblem;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   rcaConcreteElement();
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFCONC_CONCRETEELEMENT_H_
