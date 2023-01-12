///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMMODEL_BOXBEAM_H_
#define INCLUDED_GEOMMODEL_BOXBEAM_H_
#pragma once

#include <GeomModel/GeomModelExp.h>
#include <GeomModel/ShapeOnCompositeImpl.h>

namespace WBFL
{
   namespace Geometry
   {
      /// Object representing the cross section of a box beam
      ///
      /// \image html BoxBeam/BoxBeam.jpg 
      class GEOMMODELCLASS BoxBeam : public ShapeOnCompositeImpl
      {
      public:
         BoxBeam();
         BoxBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 h1, Float64 h2, Float64 h3, Float64 h4, Float64 h5, Float64 h6, Float64 h7, Float64 f1, Float64 f2, Float64 f3, Float64 c1, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, const Point2d& hookPnt);
         BoxBeam(const BoxBeam& rOther) = default;
         virtual ~BoxBeam();

         BoxBeam& operator= (const BoxBeam& rOther) = default;

         void SetW1(Float64 w1);
         Float64 GetW1() const;

         void SetW2(Float64 w2);
         Float64 GetW2() const;

         void SetW3(Float64 w3);
         Float64 GetW3() const;

         void SetW4(Float64 w4);
         Float64 GetW4() const;

         void SetH1(Float64 h1);
         Float64 GetH1() const;

         void SetH2(Float64 h2);
         Float64 GetH2() const;

         void SetH3(Float64 h3);
         Float64 GetH3() const;

         void SetH4(Float64 h4);
         Float64 GetH4() const;

         void SetH5(Float64 h5);
         Float64 GetH5() const;

         void SetH6(Float64 h6);
         Float64 GetH6() const;

         void SetH7(Float64 h7);
         Float64 GetH7() const;

         void SetF1(Float64 f1);
         Float64 GetF1() const;

         void SetF2(Float64 f2);
         Float64 GetF2() const;

         void SetC1(Float64 c1);
         Float64 GetC1() const;

         void SetVoidCount(IndexType nVoids);
         IndexType GetVoidCount() const;

         void SetLeftBlockout(bool bBlockout);
         bool GetLeftBlockout() const;

         void SetRightBlockout(bool bBlockout);
         bool GetRightBlockout() const;

         Float64 GetWebWidth() const;
         void GetBottomFlangeWidth(Float64* left, Float64* right) const;
         void GetTopFlangeWidth(Float64* left, Float64* right) const;
         Float64 GetWidth() const;
         Float64 GetHeight() const;
         void GetBoundaryPoints(Point2d* leftTop, Point2d* leftBottom, Point2d* rightTop, Point2d* rightBottom) const;

         /// Translates a shape by a delta amount.
         virtual void Offset(const Size2d& delta) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void Rotate(const Point2d& center, Float64 angle) override;

         // Creates a clone.
         virtual std::unique_ptr<Shape> CreateClone() const override;

         std::shared_ptr<Shape> GetBoxShape() const;
         std::shared_ptr<Shape> GetVoidShape(IndexType voidIdx) const;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);

#endif // _UNITTEST
      protected:
         virtual void OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const override;

      private:
         Float64 m_W1{ 0.0 };
         Float64 m_W2{ 0.0 };
         Float64 m_W3{ 0.0 };
         Float64 m_W4{ 0.0 };
         Float64 m_H1{ 0.0 };
         Float64 m_H2{ 0.0 };
         Float64 m_H3{ 0.0 };
         Float64 m_H4{ 0.0 };
         Float64 m_H5{ 0.0 };
         Float64 m_H6{ 0.0 };
         Float64 m_H7{ 0.0 };
         Float64 m_F1{ 0.0 };
         Float64 m_F2{ 0.0 };
         Float64 m_F3{ 0.0 };
         Float64 m_C1{ 0.0 };
         Float64 m_Rotation{ 0.0 };
         IndexType m_nVoids{ 1 };
         bool m_bLeftBlockout{ true };
         bool m_bRightBlockout{ true };

         // Shape point indices for top and bottom stress points
         mutable IndexType m_LeftTopPointIdx{ INVALID_INDEX }, m_LeftBottomPointIdx{ INVALID_INDEX }, m_RightTopPointIdx{ INVALID_INDEX }, m_RightBottomPointIdx{ INVALID_INDEX };
      };
   }; // Geometry
}; // WBFL

#endif // INCLUDED_GEOMMODEL_BOXBEAM_H_
