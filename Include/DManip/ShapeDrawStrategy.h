///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include <DManip/DManipExp.h>
#include <DManip/DrawPointStrategy.h>
#include <DManip/DManipTypes.h>
#include <DManip/GravityWellStrategy.h>
#include <Colors.h>
#include <optional>

namespace WBFL
{
   namespace Geometry
   {
      class CompositeShape;
   };

   namespace DManip
   {
      /// @brief Drawing strategy that draws a shape for the associated point display object.
      /// Also uses the shape to define a gravity well
      class DMANIPCLASS ShapeDrawStrategy :
         public iDrawPointStrategy,
         public iGravityWellStrategy
      {
      private:
         ShapeDrawStrategy(std::shared_ptr<const WBFL::Geometry::Shape> shape);
      public:
         static std::shared_ptr<ShapeDrawStrategy> Create(std::shared_ptr<const WBFL::Geometry::Shape> shape=nullptr) { return std::shared_ptr<ShapeDrawStrategy>(new ShapeDrawStrategy(shape)); }
         virtual ~ShapeDrawStrategy() = default;

         /// @brief The shape to draw
         /// @param shape 
         void SetShape(std::shared_ptr<const WBFL::Geometry::Shape> shape);
         std::shared_ptr<const WBFL::Geometry::Shape> GetShape() const;
         void SetSolidLineStyle(LineStyleType lineStyle);
         LineStyleType GetSolidLineStyle() const;
         void SetSolidLineColor(COLORREF crColor);
         COLORREF GetSolidLineColor() const;
         void SetSolidFillColor(COLORREF crColor);
         COLORREF GetSolidFillColor() const;
         void SetSolidLineWidth(UINT nPixels);
         UINT GetSolidLineWidth() const;
         void SetVoidLineStyle(LineStyleType lineStyle);
         LineStyleType GetVoidLineStyle() const;
         void SetVoidLineColor(COLORREF crColor);
         COLORREF GetVoidLineColor() const;
         void SetVoidFillColor(COLORREF crColor);
         COLORREF GetVoidFillColor() const;
         void SetVoidLineWidth(UINT nPixels);
         UINT GetVoidLineWidth() const;
         void Fill(bool bFill);
         bool Fill() const;

         /// @brief If true, the bounding perimeter of the shape can be used for hit testing
         /// @param bHasBoundingShape 
         void HasBoundingShape(bool bHasBoundingShape);
         bool HasBoundingShape() const;

         // iDrawPointStrategy Implementation
         virtual void Draw(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC) const override;
         virtual void DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
         virtual void DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const override;

         // iGravityWellStrategy
         virtual void GetGravityWell(std::shared_ptr<const iDisplayObject> pDO, CRgn* pRgn) override;

      private:
         LineStyleType m_SolidLineStyle = LineStyleType::Solid;
         LineStyleType m_VoidLineStyle = LineStyleType::Solid;
         COLORREF m_SolidLineColor = BLACK;
         COLORREF m_SolidFillColor = BLACK;
         COLORREF m_VoidLineColor = WHITE;
         COLORREF m_VoidFillColor = WHITE;
         UINT m_SolidLineWidth = 1;
         UINT m_VoidLineWidth = 1;
         bool m_bFill = false;
         bool m_bHasBoundingShape = true;

         std::shared_ptr<const WBFL::Geometry::Shape> m_Shape;
         std::shared_ptr<const WBFL::Geometry::CompositeShape> m_CompositeShape;

         mutable std::optional<WBFL::Geometry::Rect2d> m_BoundingBox;

         void DrawMe(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const;
         void DrawShape(std::shared_ptr<const iDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::Geometry::CompositeShape> compositeShape, CPen& solidPen, CBrush& solidBrush, CPen& voidPen, CBrush& voidBrush) const;
         void DrawShape(std::shared_ptr<const iDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::Geometry::Shape> shape) const;
         std::vector<WBFL::Geometry::Point2d> GetPointsInWorldSpace(std::shared_ptr<const iDisplayObject> pDO, std::shared_ptr<const WBFL::Geometry::Shape> shape) const;
      };
   };
};
