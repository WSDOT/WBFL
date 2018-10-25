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

#ifndef INCLUDED_GEOMETRY_LINE2D_H_
#define INCLUDED_GEOMETRY_LINE2D_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeometricPrimitives\GeometryExp.h>
#include <GeometricPrimitives\Vector2d.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gpLineSegment2d;
class gpPoint2d;
class gpSize2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gpLine2d

   gpLine2d encapsulates the notion of a line with infinite length.


DESCRIPTION
   gpLine2d encapsulates the notion of a line with infinite length. The 
   implementation for this is taken from Chapter 1 of the original
   Graphics Gems book by Brett Glassner.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 11.10.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpLine2d
{
   // friends
   friend bool GEOMFUNC operator==(const gpLine2d& lhs, const gpLine2d& rhs);

public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Enumerations
   // The side of a line can be best defined by an illustration.  Imagine 
   // you are standing at the point P1 and looking toward P2: Left is to the 
   // left side, Right is the right side.
   enum Side { Left, Right };

   //------------------------------------------------------------------------
   // Default constructor
   // Creates a line parallel to the x-axis at y = 0.
   gpLine2d();

   //------------------------------------------------------------------------
   // Explicit constructor.  Creates a line passing through points p1 and p2.
   // Has the same behavior as the default constructor if the points are 
   // identical
   gpLine2d(const gpPoint2d& p1,const gpPoint2d& p2);

   //------------------------------------------------------------------------
   // Explicit constructor.  Creates a line from line segment ls.
   gpLine2d(const gpLineSegment2d& ls);

   //------------------------------------------------------------------------
   // Explicit constructor.  Creates a line from its implicit representation
   // refer to Graphics Gems, Chapter 1 for details
   // c  - distance from closest point on origin to the origin
   // rn - vector normal to the line. Left side of line is in positive rn
   gpLine2d(Float64 c, const gpVector2d& rn);

   //------------------------------------------------------------------------
   // Explicit constructor.  Creates a line from its explicit representation
   // refer to Graphics Gems, Chapter 1 for details
   // ru - a point on the line
   // rv - tangent vector to line. Left side of line is on left looking in 
   //      positive rv direction.
   gpLine2d(const gpPoint2d& ru, const gpVector2d& rv);

   //------------------------------------------------------------------------
   // Copy constructor
   gpLine2d(const gpLine2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpLine2d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpLine2d& operator = (const gpLine2d& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns true if point is contained in the locus of points that define 
   // this line,  otherwise returns false.
   bool Contains(const gpPoint2d& point) const;

   //------------------------------------------------------------------------
   // GetSlope
   // Returns the slope of the line.  If the line is vertical and pointing 
   // upwards,  returns std::numeric_limits<float>::infinity().
   // If the line is vertical and pointing downwards,  returns 
   // -std::numeric_limits<float>::infinity()
   Float64 GetSlope() const;

   //------------------------------------------------------------------------
   // IsCollinear
   // Returns true if rOther is colinear to this.
   bool IsCollinear(const gpLine2d& rOther) const;

   //------------------------------------------------------------------------
   // Offsets this line by the given delta arguments. This line is changed
   // by translating its control points by the given distance.  Returns a 
   // reference to this line.
   gpLine2d& Offset(Float64 dx,Float64 dy);
   gpLine2d& Offset(const gpSize2d& size);
   

   //------------------------------------------------------------------------
   // Returns a line which is offset to this line by the given displacement 
   // arguments. This line is not changed.
   gpLine2d OffsetBy(Float64 dx, Float64 dy) const;
   gpLine2d OffsetBy(const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // PointOnLineNearest
   // Returns a point on the line which is nearest to the given point.
   gpPoint2d PointOnLineNearest(const gpPoint2d& point) const;

   //------------------------------------------------------------------------
   // DistanceToPoint
   // Returns the distance from the line to a given point. If the point is on
   // the left side of the line, it returns a positive value. If the point is
   // on the right side of the line it returna a negative value.
   Float64 DistanceToPoint(const gpPoint2d& rPnt) const;

   //------------------------------------------------------------------------
   // Rotates this line about the given center point by the given angle. 
   // This line is changed. Returns a reference to this line.
   gpLine2d& Rotate(const gpPoint2d& centerPoint, Float64 angle);

   //------------------------------------------------------------------------
   // Returns a line equal to this line rotated about the given center point 
   // by the given angle. This line is not changed.
   gpLine2d RotateBy(const gpPoint2d& centerPoint, Float64 angle) const;

   //------------------------------------------------------------------------
   // Returns a line that is parallel to this line and offset from this line 
   // by the specified amount.  The offset is measured perpendicular to this 
   // line.  An negative offset reverses the effect of the side argument.
   gpLine2d Parallel(Float64 offset, gpLine2d::Side side) const;

   //------------------------------------------------------------------------
   // Returns a line that is parallel to this line and passes through point.
   gpLine2d Parallel(const gpPoint2d& point) const;

   //------------------------------------------------------------------------
   // Returns a line that passes from point to the normal to this line. 
   gpLine2d Normal(const gpPoint2d& point) const;
   
   //------------------------------------------------------------------------
   // Returns the side of the line that the point is on.  If the point
   // is on the line, Left is returned.
   gpLine2d::Side GetSide(const gpPoint2d& point) const;

   //------------------------------------------------------------------------
   // Reverse the direction of the line.
   void Reverse();

   // GROUP: ACCESS

    //------------------------------------------------------------------------
   // Set implicit form of line
   void SetImplicit(Float64 c, const gpVector2d& rn);
   
   //------------------------------------------------------------------------
   // get implicit form of line
   void GetImplicit(Float64* pc, gpVector2d* rn) const;
   
   //------------------------------------------------------------------------
   // set explicit form of line
   void SetExplicit(const gpPoint2d& ru, const gpVector2d& rv);
   
   //------------------------------------------------------------------------
   // get explicit form of line
   void GetExplicit(gpPoint2d* pu, gpVector2d* pv) const;

   //------------------------------------------------------------------------
   // SetPoints
   // Sets a line passing through points p1 and p2.
   // Has the same behavior as the default constructor if the points are 
   // identical. These points are not retrievable.
   void SetPoints(const gpPoint2d& p1,const gpPoint2d& p2);

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
   void MakeCopy(const gpLine2d& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gpLine2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // line is stored implicitely (refer to Graphics Gems)
   gpVector2d m_N; // normal vector *** Must be normalized !!!!
   Float64    m_c; // distance from origin

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
   GEOMFUNC bool operator==(const gpLine2d& lhs, const gpLine2d& rhs);

   //------------------------------------------------------------------------
   // operator !=
   // Returns true if lhs is not equal to rhs,  otherwise returns false. 
   GEOMFUNC bool operator!=(const gpLine2d& lhs, const gpLine2d& rhs);

#endif // INCLUDED_GEOMETRY_LINE2D_H_
