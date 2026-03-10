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
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A line drawing strategy that draws a line dashed with two colors
      class DMANIPCLASS SimpleDrawDashedLineStrategy : public iDrawLineStrategy
      {
      protected:
         SimpleDrawDashedLineStrategy() = default;

      public:
         static std::shared_ptr<SimpleDrawDashedLineStrategy> Create() { return std::shared_ptr<SimpleDrawDashedLineStrategy>(new SimpleDrawDashedLineStrategy()); }
	      virtual ~SimpleDrawDashedLineStrategy() = default;

         void SetWidth(UINT nWidth);
         UINT GetWidth() const;
         void SetColor1(COLORREF crColor);
         COLORREF GetColor1() const;
         void SetColor2(COLORREF crColor);
         COLORREF GetColor2() const;
         void SetDashLength(DWORD dwDash);
         DWORD GetDashLength() const;

      // iLineDrawStrategy
      public:
         virtual void Draw(std::shared_ptr<const iLineDisplayObject> pDO, CDC* pDC) const override;
         virtual void DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO, CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
         virtual void DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO, CDC* pDC, bool bHighlight) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const override;

      private:
         UINT m_nWidth = 1;
         COLORREF m_crColor1 = BLACK;
         COLORREF m_crColor2 = WHITE;
         DWORD m_dwDash = 0;

         WBFL::Geometry::Point2d GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         WBFL::Geometry::Point2d GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const;
         void GetPointsInWorldSpace(std::shared_ptr<const iLineDisplayObject> pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey) const;
      };
   };
};
