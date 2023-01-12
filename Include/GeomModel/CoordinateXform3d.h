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
#include <GeomModel/Primitives3d.h>
#include <GeomModel/Vector3d.h>

namespace WBFL
{
   namespace Geometry
   {
/// Object that performs 3D coordinate transformations
///
/// \f[ \overrightarrow{P'} = \left[ \left( \overrightarrow{P} - \overrightarrow{T'} \right) \cdot \overrightarrow{n} \right] \overrightarrow{n}(1 - \cos \theta) + \left[ \left( \overrightarrow{P} - \overrightarrow{T'} \right) \cos(\theta) \times \overrightarrow{n} \right] \sin \theta \f]
/// \f[ \overrightarrow{P} = \left[ \left( \overrightarrow{P'} \cdot \overrightarrow{n} \right) \overrightarrow{n} (1 - \cos \theta) \right] + \overrightarrow{P'} \cos\theta + \left( \overrightarrow{P'} \times \overrightarrow{n} \right) \sin(-\theta) + \overrightarrow{T'} \f]
///
/// where
///
/// \f$ \overrightarrow{P'} = \f$ point in the new coordinate system
///
/// \f$ \overrightarrow{P} = \f$ point in the old coordinate system
///
/// \f$ \overrightarrow{T'} = \f$ origin of the new coordinate system
///
/// \f$ \theta = \f$ rotation angle
class GEOMMODELCLASS CoordinateXform3d
{
public:
   enum class Type
   {
      OldToNew,
      NewToOld
   };

   CoordinateXform3d();
   CoordinateXform3d(const Point3d& origin, const Vector3d& rv, Float64 angle);

   ~CoordinateXform3d();

   CoordinateXform3d(const CoordinateXform3d&) = default;
   CoordinateXform3d& operator=(const CoordinateXform3d&) = default;

   void SetRotationVector(const Vector3d& vector);
   Vector3d& GetRotationVector();
   const Vector3d& GetRotationVector() const;

   void SetRotationAngle(Float64 angle);
   Float64 GetRotationAngle() const;

   void SetNewOrigin(const Point3d& origin);
   Point3d& GetNewOrigin();
   const Point3d& GetNewOrigin() const;

   Point3d& Xform(Point3d& point, Type type) const;
   Point3d XformBy(const Point3d& point, Type type) const;

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
   Point3d m_Origin;
   Float64 m_Angle{ 0 };
   Vector3d m_RotationVector;

   void OldToNew(Point3d& point) const;
   void NewToOld(Point3d& point) const;
};

   }; // Geometry
}; // WBFL
