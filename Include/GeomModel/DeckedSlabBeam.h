///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2024  Washington State Department of Transportation
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
      /// Object representing the cross section of a decked slab beam
      ///
      /// \image html DeckedSlabBeam/DeckedSlabBeam.jpg
      class GEOMMODELCLASS DeckedSlabBeam : public ShapeOnCompositeImpl
      {
      public:
         DeckedSlabBeam();
         DeckedSlabBeam(Float64 a, Float64 b, Float64 c, Float64 w, Float64 tt, Float64 tb, Float64 f, IndexType nVoids,bool bLeftBlockout,bool bRightBlockout, std::shared_ptr<Point2d>& hookPnt);
         DeckedSlabBeam(Float64 a, Float64 b, Float64 c, Float64 w, Float64 tt, Float64 tb, Float64 f, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, const Point2d& hookPnt);
         DeckedSlabBeam(const DeckedSlabBeam& rOther) = default;
         virtual ~DeckedSlabBeam();

         DeckedSlabBeam& operator= (const DeckedSlabBeam& rOther) = default;

         void SetA(Float64 a);
         Float64 GetA() const;

         void SetB(Float64 b);
         Float64 GetB() const;

         void SetC(Float64 c);
         Float64 GetC() const;

         void SetW(Float64 w);
         Float64 GetW() const;

         void SetTt(Float64 tt);
         Float64 GetTt() const;

         void SetTb(Float64 tb);
         Float64 GetTb() const;

         void SetF(Float64 f);
         Float64 GetF() const;

         ///  Sets the void count. Valid values are 0 and 1.
         void SetVoidCount(IndexType nVoids);
         IndexType GetVoidCount() const;

         void SetLeftBlockout(bool bBlockout);
         bool GetLeftBlockout() const;

         void SetRightBlockout(bool bBlockout);
         bool GetRightBlockout() const;

         Float64 GetHeight() const;

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
         Float64 m_A{ 0.0 };
         Float64 m_B{ 0.0 };
         Float64 m_C{ 0.0 };
         Float64 m_W{ 0.0 };
         Float64 m_Tt{ 0.0 };
         Float64 m_Tb{ 0.0 };
         Float64 m_F{ 0.0 };
         IndexType m_nVoids{ 1 };
         bool m_bLeftBlockout{ true };
         bool m_bRightBlockout{ true };
         Float64 m_Rotation{ 0.0 };
      };
   }; // Geometry
}; // WBFL
