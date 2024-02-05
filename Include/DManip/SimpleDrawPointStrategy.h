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
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Strategy that draws a simple point
      class DMANIPCLASS SimpleDrawPointStrategy :
         public iDrawPointStrategy
      {
      private:
         SimpleDrawPointStrategy() = default;

      public:
         static std::shared_ptr<SimpleDrawPointStrategy> Create() { return std::shared_ptr<SimpleDrawPointStrategy>(new SimpleDrawPointStrategy()); }
	      virtual ~SimpleDrawPointStrategy() = default;

         void SetColor(COLORREF crColor);
         COLORREF GetColor() const;
         void SetPointType(PointType type);
         PointType GetPointType() const;

         /// @brief Size of the point in model space coordinates.
         /// Callimg this method causes the logical point size to be ignored and
         /// the point is drawn using the model space size provided.
         /// @param size 
         void SetPointSize(Float64 size);
         Float64 GetPointSize() const;

         /// @brief Size of the point in logical coordinates
         /// Calling this method causes the model space size to be ignored and
         /// the point is drawn using the logical point size provided.
         /// @param size 
         void SetLogicalPointSize(int size);
         int GetLogicalPointSize() const;

         /// @brief Returns true if the logical point size is used to draw thie display object
         bool UsesLogicalPointSize() const;

         // iDrawPointStrategy Implementation
         virtual void Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC) const override;
         virtual void DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,bool bHighlight) const override;
         virtual void DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const override;

      private:
         void DrawMe(const CRect& rect,CDC* pDC) const;
         WBFL::Geometry::Point2d GetPointInWorldSpace(std::shared_ptr<const iPointDisplayObject> pDO) const;
         CRect GetPointBox(std::shared_ptr<const iPointDisplayObject> pDO) const;

         bool m_bIsLogicalPoint = false; // if true, SetLogicalPointSize was called so use m_LogicalSize for the point size
         COLORREF m_Color = BLACK;
         PointType m_Type = PointType::Circle;
         Float64 m_Size = 0.0;
         int m_LogicalSize = 0;

         mutable WBFL::Geometry::Point2d m_CachePoint;
      };
   };
};
