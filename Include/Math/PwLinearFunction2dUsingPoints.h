///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_MATH_PWLINEARFUNCTION2DUSINGPOINTS_H_
#define INCLUDED_MATH_PWLINEARFUNCTION2DUSINGPOINTS_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Math\MathExp.h>
#include <Math\PwLinearFunction2d.h>
#include <GeomModel/Primitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathPwLinearFunction2dUsingPoints

   Piecewise Linear representation of a function


DESCRIPTION
   Derived from mathFunction2d

LOG
   rdp : 01.25.1999 : Created file
*****************************************************************************/

// predeclaration

class MATHCLASS mathPwLinearFunction2dUsingPoints : public mathPwLinearFunction2d
{
public:
   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   mathPwLinearFunction2dUsingPoints();

   //------------------------------------------------------------------------
   // Construct using an array of points
   mathPwLinearFunction2dUsingPoints(const std::vector<WBFL::Geometry::Point2d>& points);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathPwLinearFunction2dUsingPoints();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Evaluates the function at x.
   Float64 Evaluate(Float64 x) const;

   virtual mathFunction2d* Clone() const override;

   //------------------------------------------------------------------------
   // GetRange
   // Returns the range over which the function is valid.
   virtual math1dRange GetRange() const override;

   //------------------------------------------------------------------------
   // GetNumPoints
   // Returns the number of points which define the segments of the function.
   virtual CollectionIndexType GetNumPoints() const override;

   //------------------------------------------------------------------------
   // GetPoint
   // Returns the ith point. (zero-based)
   virtual WBFL::Geometry::Point2d GetPoint(CollectionIndexType pnum) const override;

   //------------------------------------------------------------------------
   // GetPoints
   // Returns all points for the line segments which make up the function.
   virtual std::vector<WBFL::Geometry::Point2d> GetPoints() const override;

   //------------------------------------------------------------------------
   // SetPoints
   // Sets all points which make up the function
   void SetPoints(const std::vector<WBFL::Geometry::Point2d>& points);

   //------------------------------------------------------------------------
   // AddPoint
   // Adds a new point to the the end of the function. Returns the total number of 
   // points in the function including the new point.
   CollectionIndexType AddPoint(const WBFL::Geometry::Point2d& point);
   CollectionIndexType AddPoint(Float64 X,Float64 Y);

   //------------------------------------------------------------------------
   // Intersect
   // Find the intersection of two mathPwLinearFunction2dUsingPoints' over the
   // given range. This routine will return the left-most intersection if more
   // than one intersection exists.
   // Returns 0 if the lines are parallel or do not intersect,  the contents 
   // of p are undefined.  Returns 1 if an intersect is found, p contains the 
   // intersection point.  Returns -1 if the lines are collinear and 
   // overlapping,  p contains the coordinates of the first overlapping point..
   //------------------------------------------------------------------------
   Int16 Intersect(const mathPwLinearFunction2dUsingPoints& rOther, 
                   const math1dRange& range, WBFL::Geometry::Point2d* p);

   //------------------------------------------------------------------------
   // GetMaximumsInRange
   // Determine the max and min Y values within the specified range.
   // The entire range must be contained within the function or a 
   // mathXEvalError will be thrown
   void GetMaximumsInRange(const math1dRange& range, Float64* pMin, Float64* pMax);

   //------------------------------------------------------------------------
   // Clear
   // Clears all points.
   void Clear();

   //------------------------------------------------------------------------
   // Mirror function about Y axis around xLocation. Changes bounds and order of points for func
   void MirrorAboutY(Float64 xLocation);

   //------------------------------------------------------------------------
   // Get vector of raw Y values in function
   void GetYValues(std::vector<Float64>& Yvec);

   //------------------------------------------------------------------------
   // Reset outer X bounds for function. This allows the end points of the function to be set to the 
   // input values. Note that it will throw if the left bound is greater than m_Points[1].X(), or the
   // right bound is less than m_Points[size-2].X()
   // This function was created because we were getting numerical issues with the bounds after a call
   // to MirrorPwLinearFunction2dUsingPointsAboutY
   void ResetOuterRange( const math1dRange& range);

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // Prevent accidental copying and assignment
   mathPwLinearFunction2dUsingPoints(const mathPwLinearFunction2dUsingPoints&) = delete;
   mathPwLinearFunction2dUsingPoints& operator=(const mathPwLinearFunction2dUsingPoints&) = delete;

private:
   // GROUP: DATA MEMBERS
   std::vector<WBFL::Geometry::Point2d> m_Points;

   //------------------------------------------------------------------------
   // Optimize evaluations by assuming that the last segment evaluated was 
   // close the the next evaluation. Segment counting is one-based.
   mutable CollectionIndexType m_LastSegment;

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
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(WBFL::Debug::LogContext& os) const override;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(WBFL::Debug::Log& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATH_PWLINEARFUNCTION2DUSINGPOINTS_H_
