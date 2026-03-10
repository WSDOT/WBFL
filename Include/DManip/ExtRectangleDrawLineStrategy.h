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
#include <DManip/DManipTypes.h>
#include <DManip/GravityWellStrategy.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Similar to RectangleDrawLineStrategy except the offset on either side of the line can be different,
      /// the line can be extended at the start and end, and the ends can be skewed
      class DMANIPCLASS ExtRectangleDrawLineStrategy :
         public iDrawLineStrategy,
         public iGravityWellStrategy
      {
      protected:
         ExtRectangleDrawLineStrategy() = default;

      public:
         static std::shared_ptr<ExtRectangleDrawLineStrategy> Create() { return std::shared_ptr<ExtRectangleDrawLineStrategy>(new ExtRectangleDrawLineStrategy()); }
	      virtual ~ExtRectangleDrawLineStrategy() = default;

         void SetLeftOffset(Float64 offset);
         Float64 GetLeftOffset() const;
         void SetRightOffset(Float64 offset);
         Float64 GetRightOffset() const;
         void SetStartExtension(Float64 ext);
         Float64 GetStartExtension() const;
         void SetEndExtension(Float64 ext);
         Float64 GetEndExtension() const;
         void SetStartSkew(Float64 skew);
         Float64 GetStartSkew() const;
         void SetEndSkew(Float64 skew);
         Float64 GetEndSkew() const;
         void SetLineWidth(UINT nWidth);
         UINT GetLineWidth() const;
         void SetColor(COLORREF crColor);
         COLORREF GetColor() const;
         void SetLineStyle(LineStyleType style);
         LineStyleType GetLineStyle() const;
         void PerimeterGravityWell(bool bPerimeterGravityWell);
         void SetFillColor(COLORREF crColor);
         COLORREF GetFillColor() const;
         void Fill(bool bFill);
         bool Fill() const;

      // iLineDrawStrategy
         virtual void Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const override;
         virtual void DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
         virtual void DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const override;

      // iGravityWellStrategy
      public:
         virtual void GetGravityWell(std::shared_ptr<const iDisplayObject> pDO,CRgn* pRgn) override;

      private:
         bool m_bPerimeterGravityWell = true;
         bool m_bFill = false;
         Float64 m_LeftOffset = 0;
         Float64 m_RightOffset = 0;
         Float64 m_StartSkew = 0;
         Float64 m_EndSkew = 0;
         Float64 m_StartExtension = 0;
         Float64 m_EndExtension = 0;
         UINT m_nWidth = 1;
         COLORREF m_crColor = BLACK;
         COLORREF m_crFillColor = WHITE;

         LineStyleType m_Style;

         WBFL::Geometry::Point2d GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         WBFL::Geometry::Point2d GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         void GetPoints(std::shared_ptr<const iLineDisplayObject> pDO,WBFL::Geometry::Point2d* pntTopLeft, WBFL::Geometry::Point2d* pntBottomLeft, WBFL::Geometry::Point2d* pntBottomRight, WBFL::Geometry::Point2d* pntTopRight) const;
         void GetDrawRect(std::shared_ptr<const iLineDisplayObject> pDO,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4) const;
         void DrawPerimeter(CDC* pDC,LineStyleType lineStype, COLORREF color, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4) const;
      };
   };
};
