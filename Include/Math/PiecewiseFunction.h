///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2025  Washington State Department of Transportation
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

#pragma once

#include <Math\MathExp.h>
#include <Math\Function.h>
#include <Math/Range.h>
#include <GeomModel/Primitives.h>
#include <vector>

namespace WBFL
{
   namespace Math
   {
      /// Piecewise Linear representation of a function defined by a series of Point2d objects
      class MATHCLASS PiecewiseFunction : public Function
      {
      public:
         PiecewiseFunction();
         PiecewiseFunction(const PiecewiseFunction&) = delete;
         PiecewiseFunction(const std::vector<WBFL::Geometry::Point2d>& points);

         virtual ~PiecewiseFunction() = default;

         PiecewiseFunction& operator=(const PiecewiseFunction&) = delete;

         /// Evaluates the function at x.
         Float64 Evaluate(Float64 x) const;

         virtual std::unique_ptr<Function> Clone() const override;

         /// Returns the range over which the function is valid.
         Range GetRange() const;

         // Behavior for case when Evaluate is called with an x value that's outside of the function's range 
         enum class OutOfRangeBehavior {
            ThrowException,      // Obvious, throw XFunction::Reason::Undefined
            ExtendOuterValue,    // Return boundary Y value at edge of range that was violated
            Extrapolate  // Extend endmost line to x value that is out of range
         };

         void SetOutOfRangeBehavior(OutOfRangeBehavior behavior);
         OutOfRangeBehavior GetOutOfRangeBehavior() const;

         /// Returns the number of points which define the segments of the function.
         IndexType GetPointCount() const;

         /// Returns the ith point. (zero-based)
         const WBFL::Geometry::Point2d& GetPoint(IndexType idx) const;

         /// Returns all points for the line segments which make up the function.
         const std::vector<WBFL::Geometry::Point2d>& GetPoints() const;

         /// Sets all points which make up the function
         void SetPoints(const std::vector<WBFL::Geometry::Point2d>& points);

         /// Adds a new point to the the end of the function. Returns the total number of 
         /// points in the function including the new point.
         IndexType AddPoint(const WBFL::Geometry::Point2d& point);
         IndexType AddPoint(Float64 X,Float64 Y);

         /// Appends points to the end of the function
         IndexType AddPoints(std::vector<WBFL::Geometry::Point2d>& points);

         /// Clears all points.
         void Clear();

         /// Find the intersection of two mathPwLinearFunction2dUsingPoints' over the
         /// given range. This routine will return the left-most intersection if more
         /// than one intersection exists.
         /// Returns 0 if the lines are parallel or do not intersect,  the contents 
         /// of p are undefined.  Returns 1 if an intersect is found, p contains the 
         /// intersection point.  Returns -1 if the lines are collinear and 
         /// overlapping,  p contains the coordinates of the first overlapping point..
         Int16 Intersect(const PiecewiseFunction& rOther, const Range& range, WBFL::Geometry::Point2d* p) const;

         /// Determine the max and min Y values within the specified range.
         /// The entire range must be contained within the function or a 
         /// mathXEvalError will be thrown
         void GetMaximumsInRange(const Range& range, Float64* pMin, Float64* pMax) const;

         /// Mirror function about Y axis around xLocation. Changes bounds and order of points for func
         void MirrorAboutY(Float64 xLocation);

         /// Get vector of raw Y values in function
         void GetYValues(std::vector<Float64>& Yvec) const;

         /// Reset outer X bounds for function. This allows the end points of the function to be set to the 
         /// input values. Note that it will throw if the left bound is greater than m_Points[1].X(), or the
         /// right bound is less than m_Points[size-2].X()
         /// This function was created because we were getting numerical issues with the bounds after a call
         /// to MirrorPwLinearFunction2dUsingPointsAboutY
         void ResetOuterRange( const Range& range);

      private:
         std::vector<WBFL::Geometry::Point2d> m_Points;

         OutOfRangeBehavior m_OutOfRangeBehavior{ OutOfRangeBehavior::ExtendOuterValue };

         // Optimize evaluations by assuming that the last segment evaluated was 
         // close the the next evaluation. Segment counting is one-based.
         mutable IndexType m_LastSegment{0};

      #if defined _DEBUG
         bool AssertValid() const;
      #endif // _DEBUG
      };
   };
};
