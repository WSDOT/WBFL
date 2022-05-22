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

namespace WBFL
{
   namespace Geometry
   {
      class Polygon;

      /// Object representing the cross section of a multi-web girder
      ///
      /// \image html MultiWeb/MultiWeb2.jpg   
      class GEOMMODELCLASS MultiWeb2 : public ShapeOnPolygonImpl
      {
      public:

         MultiWeb2();

         MultiWeb2(Float64 h1,Float64 h2,Float64 h3,Float64 w1, Float64 w2, Float64 t1, Float64 t2, Float64 t3,Float64 t4,Float64 t5,Float64 f1,Float64 f2,Float64 c1,Float64 c2, IndexType nWebs, bool bLeftBlockOut, bool bRightBlockOut, std::shared_ptr<Point2d>& hookPnt);

         MultiWeb2(const MultiWeb2& other) = default;
         MultiWeb2& operator=(const MultiWeb2& other) = default;

         virtual ~MultiWeb2() override;


         void SetH1(Float64 h1);
         Float64 GetH1() const;

         void SetH2(Float64 h2);
         Float64 GetH2() const;

         void SetH3(Float64 h3);
         Float64 GetH3() const;

         void SetW1(Float64 w1);
         Float64 GetW1() const;

         void SetW2(Float64 w2);
         Float64 GetW2() const;

         void SetT1(Float64 t1);
         Float64 GetT1() const;

         void SetT2(Float64 t2);
         Float64 GetT2() const;

         void SetT3(Float64 t3);
         Float64 GetT3() const;

         void SetT4(Float64 t4);
         Float64 GetT4() const;

         void SetT5(Float64 t5);
         Float64 GetT5() const;

         void SetF1(Float64 f1);
         Float64 GetF1() const;

         void SetF2(Float64 f2);
         Float64 GetF2() const;

         void SetC1(Float64 c1);
         Float64 GetC1() const;

         void SetC2(Float64 c2);
         Float64 GetC2() const;

         void SetWebCount(WebIndexType nWebs);
         WebIndexType GetWebCount() const;

         void SetLeftBlockout(bool bBlockout);
         bool GetLeftBlockout() const;

         void SetRightBlockout(bool bBlockout);
         bool GetRightBlockout() const;

         Float64 GetWebLocation(WebIndexType webIdx);

         Float64 GetTopFlangeWidth() const;
         Float64 GetAvgWebWidth(WebIndexType webIdx) const;
         Float64 GetHeight() const;

         /// Translates a shape by a delta amount.
         virtual void DoOffset(const Size2d& delta) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void DoRotate(const Point2d& center, Float64 angle) override;

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
         Float64 m_Rotation{ 0.0 };
         Float64 m_H1{ 0.0 };
         Float64 m_H2{ 0.0 };
         Float64 m_H3{ 0.0 };
         Float64 m_W1{ 0.0 };
         Float64 m_W2{ 0.0 };
         Float64 m_T1{ 0.0 };
         Float64 m_T2{ 0.0 };
         Float64 m_T3{ 0.0 };
         Float64 m_T4{ 0.0 };
         Float64 m_T5{ 0.0 };
         Float64 m_F1{ 0.0 };
         Float64 m_F2{ 0.0 };
         Float64 m_C1{ 0.0 };
         Float64 m_C2{ 0.0 };
         WebIndexType m_WebCount{ 2 };
         bool m_bLeftBlockout{ true };
         bool m_bRightBlockout{ true };
      };
   }; // Geometry
}; // WBFL
