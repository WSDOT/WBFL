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
#include <GeomModel/ShapeOnPolygonImpl.h>

namespace WBFL
{
   namespace Geometry
   {

      /// Object representing a built-up steel plate girder
      ///
      /// \image html PlateGirder/PlateGirder.jpg
      class GEOMMODELCLASS PlateGirder : public ShapeOnPolygonImpl
      {
      public:
         PlateGirder();
         PlateGirder(std::shared_ptr<Point2d>& hookPnt, Float64 tfw, Float64 tft, Float64 bfw, Float64 bft, Float64 hWeb, Float64 wWeb, Float64 rotAngle = 0.);
         PlateGirder(const Point2d& hookPnt, Float64 tfw, Float64 tft, Float64 bfw, Float64 bft, Float64 hWeb, Float64 wWeb, Float64 rotAngle = 0.);

         PlateGirder(const PlateGirder& other) = default;
         PlateGirder& operator=(const PlateGirder& other) = default;

         virtual ~PlateGirder();

         void SetTopFlangeWidth(Float64 wtf);
         Float64 GetTopFlangeWidth() const;

         void SetTopFlangeThickness(Float64 ttf);
         Float64 GetTopFlangeThickness() const;

         void SetBottomFlangeWidth(Float64 wbf);
         Float64 GetBottomFlangeWidth() const;

         void SetBottomFlangeThickness(Float64 tbf);
         Float64 GetBottomFlangeThickness() const;

         void SetWebHeight(Float64 tWeb);
         Float64 GetWebHeight() const;

         void SetWebWidth(Float64 wWeb);
         Float64 GetWebWidth() const;

         Float64 GetHeight() const;

         /// First moment of area of the top flange
         Float64 GetQTopFlange() const;

         /// First moment of area of the bottom flange
         Float64 GetQBottomFlange() const;

         /// Translates a shape by a delta amount.
         virtual void DoOffset(const Size2d& delta) override;

         /// Rotates a shape.  The rotation is centered about point center.  The 
         /// rotation angle is measured in radians counter clockwise.
         virtual void DoRotate(const Point2d& center, Float64 angle) override;

         /// Creates a clone.
         virtual std::unique_ptr<Shape> CreateClone() const override;

      protected:
         virtual void OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const override;

      private:
         Float64 m_webWidth{ 0 };
         Float64 m_webHeight{ 0 };
         Float64 m_bfThickness{ 0 };
         Float64 m_bfWidth{ 0 };
         Float64 m_tfThickness{ 0 };
         Float64 m_tfWidth{ 0 };
         Float64 m_Rotation{ 0 };
      };

   }; // Geometry
}; // WBFL
