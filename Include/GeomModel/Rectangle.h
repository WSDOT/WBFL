///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ShapeOnPolygonImpl.h>
#include <GeomModel/ShapeProperties.h>

namespace WBFL
{
   namespace Geometry
   {
class Polygon;

/// Object representing a Rectangle
///
/// \image html Rectangle/Rectangle.jpg
class GEOMMODELCLASS Rectangle : public ShapeOnPolygonImpl
{
public:
   /// Default constructor.  Creates a rectangle with height and width equal 
   /// to zero,  with its hook point at (0,0).
   Rectangle();

   /// Explicit constructor.  Creates a rectangle with height h, width w, and
   /// the hook point positioned at hookPnt.
   Rectangle(std::shared_ptr<Point2d>& hookPnt, Float64 w, Float64 h);
   Rectangle(const Point2d& hookPnt, Float64 w, Float64 h);

   Rectangle(const Rectangle& other);
   Rectangle& operator=(const Rectangle& other);

   virtual ~Rectangle() override;

   /// Sets the width of the rectangle.
   void SetWidth(Float64 w);

   /// Returns the width of the rectangle.
   Float64 GetWidth() const;

   /// Sets the height of the rectangle.
   void SetHeight(Float64 h);

   /// Returns the height of the rectangle.
   Float64 GetHeight() const;

   /// Translates a shape by a delta amount.
   virtual void DoOffset(const Size2d& delta) override;

   /// Rotates a shape.  The rotation is centered about point center.  The 
   /// rotation angle is measured in radians counter clockwise.
   virtual void DoRotate(const Point2d& center, Float64 angle) override;

   /// Overrides base class implementation and provides a direct solution
   virtual Float64 GetPerimeter() const override;

   // Creates a clone.
   virtual std::unique_ptr<Shape> CreateClone() const override;

#if defined _DEBUG
   /// Returns true if the class is in a valid state, otherwise returns false
   virtual bool AssertValid() const override;

   /// Dumps the contents of the class to the given stream.
   virtual void Dump(WBFL::Debug::LogContext& os) const override;
#endif // _DEBUG

#if defined _UNITTEST
   // Self-diagnostic test function
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif _UNITTEST

protected:
   virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

private:
   Float64 m_Height{ 0.0 };
   Float64 m_Width{ 0.0 };
   Float64 m_Rotation{ 0.0 };
  
   void Copy(const Rectangle& other);
};

   }; // Geometry
}; // WBFL
