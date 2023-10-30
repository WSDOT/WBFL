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
      /// \image html MultiWeb/MultiWeb.png   
      class GEOMMODELCLASS MultiWeb : public ShapeOnPolygonImpl
      {
      public:

         MultiWeb();

         MultiWeb(Float64 w1, Float64 w2, Float64 d1, Float64 d2, Float64 t1, Float64 t2, IndexType nWebs, std::shared_ptr<Point2d>& hookPnt);

         MultiWeb(const MultiWeb& other) = default;
         MultiWeb& operator=(const MultiWeb& other) = default;

         virtual ~MultiWeb() override;

         void SetW1(Float64 w1);
         Float64 GetW1() const;

         void SetW2(Float64 w2);
         Float64 GetW2() const;

         void SetD1(Float64 d1);
         Float64 GetD1() const;

         void SetD2(Float64 d2);
         Float64 GetD2() const;

         void SetT1(Float64 t1);
         Float64 GetT1() const;

         void SetT2(Float64 t2);
         Float64 GetT2() const;

         void SetWebCount(WebIndexType nWebs);
         WebIndexType GetWebCount() const;

         Float64 GetWebLocation(WebIndexType webIdx);

         Float64 GetTopFlangeWidth() const;
         Float64 GetAvgWebWidth() const;
         Float64 GetHeight() const;

         /// Translates a shape by a delta amount.
         virtual void DoOffset(const Size2d& delta) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void DoRotate(const Point2d& center, Float64 angle) override;

         // Creates a clone.
         virtual std::unique_ptr<Shape> CreateClone() const override;

      protected:
         virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

      private:
         Float64 m_Rotation{ 0.0 };
         Float64 m_D1{ 0.0 };
         Float64 m_D2{ 0.0 };
         Float64 m_T1{ 0.0 };
         Float64 m_T2{ 0.0 };
         Float64 m_W1{ 0.0 };
         Float64 m_W2{ 0.0 };
         WebIndexType m_WebCount{ 0 };
      };
   }; // Geometry
}; // WBFL
