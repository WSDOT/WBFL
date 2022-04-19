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
#include <GeomModel/ShapeOnCompositeImpl.h>

namespace WBFL
{
   namespace Geometry
   {
      class Polygon;
      
      /// Object representing the cross section of a voided slab
      ///
      /// \image html VoidedSlab/VoidedSlab.jpg  
      class GEOMMODELCLASS VoidedSlab : public ShapeOnCompositeImpl
      {
      public:
         VoidedSlab();

         VoidedSlab(Float64 h, Float64 w, Float64 d, Float64 s, IndexType nVoids, std::shared_ptr<Point2d>& hookPnt);

         VoidedSlab(const VoidedSlab& other) = default;
         VoidedSlab& operator=(const VoidedSlab& other) = default;

         virtual ~VoidedSlab() override;

         void SetHeight(Float64 h);
         Float64 GetHeight() const;

         void SetWidth(Float64 width);
         Float64 GetWidth() const;

         void SetVoidDiameter(Float64 d);
         Float64 GetVoidDiameter() const;

         void SetVoidSpacing(Float64 s);
         Float64 GetVoidSpacing() const;

         void SetVoidCount(IndexType nVoids);
         IndexType GetVoidCount() const;

         /// Translates a shape by a delta amount.
         virtual void Offset(const Size2d& delta) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void Rotate(const Point2d& center, Float64 angle) override;


         // Creates a clone.
         virtual std::unique_ptr<Shape> CreateClone() const override;

         std::shared_ptr<Shape> GetSlabShape() const;
         std::shared_ptr<Shape> GetVoidShape(IndexType voidIdx) const;

#if defined _DEBUG
         /// Returns true if the class is in a valid state, otherwise returns false
         virtual bool AssertValid() const override;

         /// Dumps the contents of the class to the given stream.
         virtual void Dump(dbgDumpContext& os) const override;
#endif // _DEBUG

#if defined _UNITTEST
         // Self-diagnostic test function
         static bool TestMe(dbgLog& rlog);
#endif _UNITTEST
      protected:
         virtual void OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const override;


      private:
         Float64 m_Rotation{ 0.0 };
         Float64   m_W{ 0.0 };
         Float64   m_H{ 0.0 };
         Float64   m_D{ 0.0 };
         Float64   m_S{ 0.0 };
         IndexType m_nVoids{ 0 };
      };
   }; // Geometry
}; // WBFL
