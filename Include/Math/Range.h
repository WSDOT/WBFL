///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#pragma once

#include <Math\MathExp.h>


namespace WBFL
{
   namespace Math
   {
      /// Class which defines a range in the real (Float64) number system
      class MATHCLASS Range
      {
      public:
         /// This enumeration encapsulates all types of range boundaries in the real domain
         enum class BoundType { Bound,     ///< range has defined value at bound location
                                Limit};    ///< range defined up to, but not at, at this location (eg, Tan(90))

         /// Defines the null range: from (0,Limit) to (0,Limit)
         Range() = default;

         Range(Float64 leftLocation, BoundType leftBound, Float64 rightLocation, BoundType rightBound);

         Range(const Range&) = default;

         ~Range() = default;

         Range& operator=(const Range&) = default;

         bool operator==(const Range& rhs) const;

         /// Set all parameters at once
         void Set(Float64 leftLocation, BoundType leftBound, Float64 rightLocation, BoundType rightBound);

         /// Returns the location of the left bound of the range. 
         Float64 GetLeftBoundLocation() const;

         /// Sets the left bound of the range.
         void SetLeftBoundLocation(Float64 bound);

         /// Returns the type of the left bound of the range.
         Range::BoundType GetLeftBoundType() const;

         /// Sets the type of the left bound of the range.
         void SetLeftBoundType(Range::BoundType type);

         /// Returns the location of the Right bound of the range. 
         Float64 GetRightBoundLocation() const;

         /// Sets the Right bound of the range.
         void SetRightBoundLocation(Float64 bound);

         /// Returns the type of the Right bound of the range.
         Range::BoundType GetRightBoundType() const;

         /// Sets the type of the Right bound of the range.
         void SetRightBoundType(Range::BoundType type);

         /// Returns true if the value is within the range
         bool IsInRange(Float64 value) const;

         /// Returns true if the range is the empty set.
         bool IsNull() const;

         /// Sets the left and right bounds to (0,Limit).
         void SetNull();

         /// Returns true if the two ranges overlap
         bool IsIntersection(const Range& rOther) const;

         /// Returns the intersection (overlapping part) of the two ranges.
         Range Intersection(const Range& rOther) const;

         /// Returns the union (enclosing boundary) of two ranges. The two ranges do not have to overlap.
         Range Union(const Range& rOther) const;

      private:
         Float64 m_LeftLocation{0.0};
         BoundType m_LeftBound{BoundType::Limit};
         Float64 m_RightLocation{0.0};
         BoundType m_RightBound{BoundType::Limit};

      public:
         #if defined _DEBUG
         virtual bool AssertValid() const;
      #endif // _DEBUG
      };
   };
};
