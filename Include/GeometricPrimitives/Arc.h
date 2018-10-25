///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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

#ifndef INCLUDED_GEOMETRY_ARC_H_
#define INCLUDED_GEOMETRY_ARC_H_
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

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpArc

   A class to represent an arc in the X-Y Plane


DESCRIPTION
   A class to represent an arc in the X-Y Plane.  The arc is defined its start,
   center, and end points.  The arc is always taken in a counter-clockwise
   direction.
   
COPYRIGHT
   Copyright (c) 1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   Richard Brice : 05.07.1999 : Created file
*****************************************************************************/

class GEOMCLASS gpArc
{
public:

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Circle centered at (0,0) with radius of zero
   gpArc();

   //------------------------------------------------------------------------
   // Copy constructor
   gpArc(const gpArc& rOther);

   //------------------------------------------------------------------------
   // Defines an arc using three non-colinear points.
   gpArc(const gpPoint2d& start,const gpPoint2d& center, const gpPoint2d& end);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpArc();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpArc& operator = (const gpArc& rOther);

   // GROUP: OPERATIONS
   
   // GROUP: ACCESS
   //------------------------------------------------------------------------
   void SetStart(const gpPoint2d& start);
   //------------------------------------------------------------------------
   gpPoint2d GetStart() const;
   //------------------------------------------------------------------------
   void SetCenter(const gpPoint2d& center);
   //------------------------------------------------------------------------
   gpPoint2d GetCenter() const;
   //------------------------------------------------------------------------
   void SetEnd(const gpPoint2d& end);
   //------------------------------------------------------------------------
   gpPoint2d GetEnd() const;
   //------------------------------------------------------------------------
   // Reverses the direction of the arc by swapping the start and end points.
   void Reverse();

   //------------------------------------------------------------------------
   Float64 GetRadius() const;
   //------------------------------------------------------------------------
   Float64 GetLength() const;
   //------------------------------------------------------------------------
   // Computes the distance along the arc to the point found by intersecting
   // a line from center to p with the arc.  If the line does not intersect
   // the arc, the projected arc length is used.
   Float64 Distance(const gpPoint2d& p) const;
   //------------------------------------------------------------------------
   bool IsPointOnArc(const gpPoint2d& p) const;
   //------------------------------------------------------------------------
   // Returns the central angle of the arc.
   Float64 GetCentralAngle() const;

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
   void MakeCopy(const gpArc& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gpArc& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gpPoint2d m_Start;
   gpPoint2d m_Center;
   gpPoint2d m_End;

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
   GEOMFUNC bool operator==(const gpArc& lhs, const gpArc& rhs);

   //------------------------------------------------------------------------
   // operator !=
   // Returns true if lhs is not equal to rhs,  otherwise returns false. 
   GEOMFUNC bool operator!=(const gpArc& lhs, const gpArc& rhs);


#endif // INCLUDED_GEOMETRY_ARC_H_
