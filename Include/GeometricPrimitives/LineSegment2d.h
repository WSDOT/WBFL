///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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

#ifndef INCLUDED_GEOMETRY_LINESEGMENT2D_H_
#define INCLUDED_GEOMETRY_LINESEGMENT2D_H_
#pragma once

// SYSTEM INCLUDES
//

#include <vector>
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
   gpLineSegment2d

   gpLineSegment2d encapsulates the notion of a line with finite length.


DESCRIPTION
   gpLineSegment2d encapsulates the notion of a line with finite length.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 11.10.1997 : Created file
*****************************************************************************/

class GEOMCLASS gpLineSegment2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   gpLineSegment2d();

   //------------------------------------------------------------------------
   // gpLineSegment2d
   // Explicit constructor.  Creates a line segment from start to end.
   gpLineSegment2d(const gpPoint2d& start, const gpPoint2d& end);

   //------------------------------------------------------------------------
   // gpLineSegment2d
   // Explicit constructor.  Creates a line segment from start to end.
   gpLineSegment2d(Float64 x1,Float64 y1, Float64 x2,Float64 y2);

   //------------------------------------------------------------------------
   // gpLineSegment2d
   // Explicit constructor.  Creates a line segment that starts at start 
   // and ends at (start.X()+relEnd.Dx(),start.Y()+relEnd.Dy()).
   gpLineSegment2d(const gpPoint2d& start, const gpSize2d& relEnd);

   //------------------------------------------------------------------------
   // Copy constructor
   gpLineSegment2d(const gpLineSegment2d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gpLineSegment2d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gpLineSegment2d& operator = (const gpLineSegment2d& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Contains
   // Returns true if point is contained between the end points of this line 
   // segment,  otherwise returns false.
   bool Contains(const gpPoint2d& point,Float64 tol = 1.0e-8) const;

   //------------------------------------------------------------------------
   // Length
   // Returns the length of the line segment.
   Float64 Length() const;

   //------------------------------------------------------------------------
   // SetStartPoint
   // Sets the start point of the line segment.
   void SetStartPoint (const gpPoint2d&);

   //------------------------------------------------------------------------
   // GetStartPoint
   // Returns the start point of the line segment.
   gpPoint2d GetStartPoint() const;

   //------------------------------------------------------------------------
   // SetEndPoint
   // Sets the end point of the line segment.
   void SetEndPoint(const gpPoint2d&);

   //------------------------------------------------------------------------
   // GetEndPoint
   // Returns the end point of the line segment.
   gpPoint2d GetEndPoint() const;

   //------------------------------------------------------------------------
   // Returns the mid point of the line segment.
   gpPoint2d GetMidPoint() const;

   //------------------------------------------------------------------------
   // Offset
   // Offsets this line segment by the given delta arguments. This line is 
   // changed by translating its control points by the given distance.  
   // Returns a reference to this line segment.
   gpLineSegment2d& Offset(Float64 dx,Float64 dy);
   gpLineSegment2d& Offset(const gpSize2d& size);

   //------------------------------------------------------------------------
   // OffsetBy
   // Returns a segment line which is offset to this line segment by the given 
   // displacement arguments. This is not changed.
   gpLineSegment2d OffsetBy(Float64 dx, Float64 dy) const;
   gpLineSegment2d OffsetBy(const gpSize2d& size) const;

   //------------------------------------------------------------------------
   // Rotate
   // Rotates this line segment about the given center point by the given 
   // angle (in radians). This is changed. Returns a reference to this line segment.
   gpLineSegment2d& Rotate(const gpPoint2d& centerPoint, Float64 angle);

   //------------------------------------------------------------------------
   // RotateBy
   // Returns a line segment equal to this line segment rotated about the 
   // given center point by the given angle (in radians). This is not changed.
   gpLineSegment2d RotateBy(const gpPoint2d& centerPoint, Float64 angle) const;
   
   //------------------------------------------------------------------------
   // Divide
   // Divides the line segment into nSpaces equally divided spaces.  Returns
   // a vector containing the coordinate of each point.
   std::vector<gpPoint2d> Divide(Uint16 nSpaces) const;
  
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
   // TestMe
   // Self-Test function. Returns true if successful.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const gpLineSegment2d& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gpLineSegment2d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // start and end points
   gpPoint2d m_P1, m_P2;

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
   GEOMFUNC bool operator==(const gpLineSegment2d& lhs, const gpLineSegment2d& rhs);

   //------------------------------------------------------------------------
   // operator !=
   // Returns true if lhs is not equal to rhs,  otherwise returns false. 
   GEOMFUNC bool operator!=(const gpLineSegment2d& lhs, const gpLineSegment2d& rhs);

#endif // INCLUDED_GEOMETRY_LINESEGMENT2D_H_
