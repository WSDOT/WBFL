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
#include <DManip/DrawLineStrategy.h>
#include <DManip/DManipTypes.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Line drawing strategy that draws a basic line
      class DMANIPCLASS SimpleDrawLineStrategy : public iDrawLineStrategy
      {
      protected:
         SimpleDrawLineStrategy() = default;

      public:
         static std::shared_ptr<SimpleDrawLineStrategy> Create() { return std::shared_ptr<SimpleDrawLineStrategy>(new SimpleDrawLineStrategy()); }
	      virtual ~SimpleDrawLineStrategy() = default;

         void SetWidth(UINT nPixels);
         UINT GetWidth() const;
         void SetColor(COLORREF crColor);
         COLORREF GetColor() const;
         void SetBeginType(PointType type);
         PointType GetBeginType() const;
         UINT GetBeginSize() const;
         void SetBeginSize(UINT size);
         void SetEndType(PointType type);
         PointType GetEndType() const;
         UINT GetEndSize() const;
         void SetEndSize(UINT size);
         void SetLineStyle(LineStyleType style);
         LineStyleType GetLineStyle() const;

      // iLineDrawStrategy
         virtual void Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const override;
         virtual void DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
         virtual void DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const override;

      private:
         UINT m_nWidth = 1;
         COLORREF m_crColor = BLACK;

         PointType m_BeginType = PointType::None;
         UINT m_BeginSize = 0;
         PointType m_EndType = PointType::None;
         UINT m_EndSize = 0;
         LineStyleType m_Style = LineStyleType::Solid;

         WBFL::Geometry::Point2d GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         WBFL::Geometry::Point2d GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         void GetPointsInWorldSpace(std::shared_ptr<const iLineDisplayObject> pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey) const;
      };
   };
};
