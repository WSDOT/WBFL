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

#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/Primitives.h>

namespace WBFL
{
   namespace Geometry
   {
/// Object that performs 2D coordinate transformations
///
/// \image html CoordinateXform2d/CoordinateXform2d.jpg
/// Original to New
///
/// \f[ x' = (x - x_o)\cos\theta + (y - y_o)\sin\theta \f]
/// \f[ y' = -(x - x_o)\sin\theta + (y - y_o)\cos\theta \f]
///
/// New to Original
///
/// \f[ x = x'\cos\theta - y'\sin\theta + x_o \f]
/// \f[ y = x'\sin\theta + y'\cos\theta + y_o \f]
class GEOMMODELCLASS CoordinateXform2d
{
public:
   enum class Type
   {
      OldToNew,
      NewToOld
   };

   CoordinateXform2d();
   CoordinateXform2d(const Point2d& origin, Float64 angle);
   ~CoordinateXform2d();

   CoordinateXform2d(const CoordinateXform2d&) = default;
   CoordinateXform2d& operator=(const CoordinateXform2d&) = default;

   void SetRotationAngle(Float64 angle);
   Float64 GetRotationAngle() const;

   void SetNewOrigin(const Point2d& origin);
   Point2d& GetNewOrigin();
   const Point2d& GetNewOrigin() const;

   Point2d& Xform(Point2d& point, Type type) const;
   Point2d XformBy(const Point2d& point, Type type) const;

#if defined _DEBUG
   /// Returns true if the class is in a valid state, otherwise returns false
   bool AssertValid() const;

   /// Dumps the contents of the class to the given stream.
   void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   /// A self-test function - returns true if passed.
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

private:
   Point2d m_Origin;
   Float64 m_Angle{ 0 };
   Float64 m_SinAngle{ 1 };
   Float64 m_CosAngle{ 0 };

   void OldToNew(Point2d& point) const;
   void NewToOld(Point2d& point) const;
};

   }; // Geometry
}; // WBFL
