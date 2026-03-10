///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include <DManip/DManipExp.h>
#include <DManip/DrawLineStrategy.h>
#include <DManip/GravityWellStrategy.h>
#include <DManip/DManipTypes.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A line drawing strategy that represents a line as a rectangular area centered on the line.
      /// The shape of the line representation is also used as a gravity well.
      class DMANIPCLASS RectangleDrawLineStrategy :
         public iDrawLineStrategy,
         public iGravityWellStrategy
      {
      protected:
         RectangleDrawLineStrategy() = default;

      public:
         static std::shared_ptr<RectangleDrawLineStrategy> Create() { return std::shared_ptr<RectangleDrawLineStrategy>(new RectangleDrawLineStrategy()); }
	      virtual ~RectangleDrawLineStrategy() = default;

         /// @brief Defines the width of the rectangle in model space
         /// @param width 
         void SetWidth(Float64 width);
         Float64 GetWidth() const;
         
         /// @brief Sets the width of the line used to draw the rectangle
         /// @param nWidth 
         void SetLineWidth(UINT nWidth);
         UINT GetLineWidth() const;

         /// @brief Sets the line color
         /// @param crColor 
         void SetColor(COLORREF crColor);
         COLORREF GetColor() const;

         /// @brief Sets the line style
         /// @param style 
         void SetLineStyle(LineStyleType style);
         LineStyleType GetLineStyle() const;

         /// @brief Sets the fill color
         /// @param crColor 
         void SetFillColor(COLORREF crColor);
         COLORREF GetFillColor() const;

         /// @brief Indicates if the rectangle is filled
         /// @param bFill 
         void Fill(bool bFill);
         bool Fill() const;

         /// @brief If true, the perimeter of the rectangle is used as the
         /// gravity well, otherwise hits must be on the line.
         /// @param bPerimeterGravityWell 
         void PerimeterGravityWell(bool bPerimeterGravityWell);

      // iLineDrawStrategy
      public:
         virtual void Draw(std::shared_ptr<const iLineDisplayObject> pDO, CDC* pDC) const override;
         virtual void DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO, CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
         virtual void DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO, CDC* pDC, bool bHighlight) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const override;

      // iGravityWellStrategy
      public:
         virtual void GetGravityWell(std::shared_ptr<const iDisplayObject> pDO, CRgn* pRgn) override;

      private:
         bool m_bPerimeterGravityWell = true;
         bool m_bFill = false;
         Float64 m_RectWidth = 0.0;
         UINT m_nWidth = 1;
         COLORREF m_crColor = BLACK;
         COLORREF m_crFillColor = WHITE;

         LineStyleType m_Style = LineStyleType::Solid;

         WBFL::Geometry::Point2d GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         WBFL::Geometry::Point2d GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         void GetPoints(std::shared_ptr<const iLineDisplayObject> pDO,WBFL::Geometry::Point2d* pntTopLeft, WBFL::Geometry::Point2d* pntBottomLeft, WBFL::Geometry::Point2d* pntBottomRight, WBFL::Geometry::Point2d* pntTopRight) const;
         void GetDrawRect(std::shared_ptr<const iLineDisplayObject>,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4) const;
         void DrawPerimeter(CDC* pDC,LineStyleType lineStyle, COLORREF color, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4) const;
      };
   };
};
