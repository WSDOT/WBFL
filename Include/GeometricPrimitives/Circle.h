///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2023  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMETRY_CIRCLE_H_
#define INCLUDED_GEOMETRY_CIRCLE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeometricPrimitives\GeometryExp.h>
#include <GeometricPrimitives\Primitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gpArc;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpCircle

   A class to represent a circle in the X-Y Plane


DESCRIPTION
   A class to represent a circle in the X-Y Plane

LOG
   Richard Brice : 05.07.1999 : Created file
*****************************************************************************/

class GEOMCLASS gpCircle
{
public:

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Circle centered at (0,0) with radius of zero
   gpCircle();

   //------------------------------------------------------------------------
   // Copy constructor
   gpCircle(const gpCircle& rOther);

   //------------------------------------------------------------------------
   gpCircle(const gpPoint2d& center,Float64 radius);

   //------------------------------------------------------------------------
   // Defines a circle with two points on its diameter
   gpCircle(const gpPoint2d& p1,const gpPoint2d& p2);

   //------------------------------------------------------------------------
   // Defines a circle using three non-colinear points.  If the points
   // are colinear a circle with center at p2 with a radius of zero is created.
   gpCircle(const gpPoint2d& p1,const gpPoint2d& p2, const gpPoint2d& p3);

   //------------------------------------------------------------------------
   gpCircle(const gpArc& arc);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpCircle();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpCircle& operator = (const gpCircle& rOther);

   // GROUP: OPERATIONS
   
   // GROUP: ACCESS
   //------------------------------------------------------------------------
   void SetRadius(Float64 r);
   //------------------------------------------------------------------------
   Float64 GetRadius() const;
   //------------------------------------------------------------------------
   void SetCenter(const gpPoint2d& center);
   //------------------------------------------------------------------------
   gpPoint2d GetCenter() const;
   //------------------------------------------------------------------------
   Float64 GetPerimeter() const;
   //------------------------------------------------------------------------
   bool IsPointOnCircle(const gpPoint2d& p) const;

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
   // A self-test function - returns true if passed.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpCircle& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const gpCircle& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gpPoint2d m_Center;
   Float64 m_Radius;

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

   //------------------------------------------------------------------------
   // operator ==
   // Returns true if lhs is equal to rhs,  otherwise returns false. 
   GEOMFUNC bool operator==(const gpCircle& lhs, const gpCircle& rhs);

   //------------------------------------------------------------------------
   // operator !=
   // Returns true if lhs is not equal to rhs,  otherwise returns false. 
   GEOMFUNC bool operator!=(const gpCircle& lhs, const gpCircle& rhs);


#endif // INCLUDED_GEOMETRY_CIRCLE_H_
