///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ShapeOnCompositeImpl.h>

namespace WBFL
{
   namespace Geometry
   {
      class Polygon;
      
      /// Object representing the cross section of a voided slab
      ///
      /// \image html VoidedSlab/VoidedSlab2.jpg  
      class GEOMMODELCLASS VoidedSlab2 : public ShapeOnCompositeImpl
      {
      public:
         VoidedSlab2();

         VoidedSlab2(Float64 h, Float64 w, Float64 d1,Float64 d2, Float64 h1, Float64 h2, Float64 s1,Float64 s2, Float64 c1, Float64 c2, Float64 c3, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, std::shared_ptr<Point2d>& hookPnt);

         VoidedSlab2(const VoidedSlab2& other) = default;
         VoidedSlab2& operator=(const VoidedSlab2& other) = default;

         virtual ~VoidedSlab2() override;

         void SetHeight(Float64 h);
         Float64 GetHeight() const;

         void SetWidth(Float64 width);
         Float64 GetWidth() const;

         void SetExteriorVoidDiameter(Float64 d1);
         Float64 GetExteriorVoidDiameter() const;

         void SetInteriorVoidDiameter(Float64 d2);
         Float64 GetInteriorVoidDiameter() const;

         void SetExteriorVoidElevation(Float64 h1);
         Float64 GetExteriorVoidElevation() const;

         void SetInteriorVoidElevation(Float64 h2);
         Float64 GetInteriorVoidElevation() const;

         void SetExteriorVoidSpacing(Float64 s1);
         Float64 GetExteriorVoidSpacing() const;

         void SetInteriorVoidSpacing(Float64 s2);
         Float64 GetInteriorVoidSpacing() const;

         void SetVoidCount(IndexType nVoids);
         IndexType GetVoidCount() const;

         void SetC1(Float64 c1);
         Float64 GetC1() const;

         void SetC2(Float64 c2);
         Float64 GetC2() const;

         void SetC3(Float64 c3);
         Float64 GetC3() const;

         void SetLeftBlockout(bool bBlockout);
         bool GetLeftBlockout() const;

         void SetRightBlockout(bool bBlockout);
         bool GetRightBlockout() const;

         /// Translates a shape by a delta amount.
         virtual void Offset(const Size2d& delta) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void Rotate(const Point2d& center, Float64 angle) override;


         // Creates a clone.
         virtual std::unique_ptr<Shape> CreateClone() const override;

         std::shared_ptr<Shape> GetSlabShape() const;
         std::shared_ptr<Shape> GetVoidShape(IndexType voidIdx) const;

      protected:
         virtual void OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const override;


      private:
         Float64 m_Rotation{ 0.0 };
         Float64   m_W{ 0.0 };
         Float64   m_H{ 0.0 };
         Float64   m_D1{ 0.0 };
         Float64   m_D2{ 0.0 };
         Float64   m_H1{ 0.0 };
         Float64   m_H2{ 0.0 };
         Float64   m_S1{ 0.0 };
         Float64   m_S2{ 0.0 };
         Float64   m_C1{ 0.0 };
         Float64   m_C2{ 0.0 };
         Float64   m_C3{ 0.0 };
         IndexType m_nVoids{ 0 };
         bool m_bLeftBlockout{ true };
         bool m_bRightBlockout{ true };
      };
   }; // Geometry
}; // WBFL
