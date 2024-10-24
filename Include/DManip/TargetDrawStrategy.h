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
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A point drawing strategy that draws a surveyor's target symbol
      class DMANIPCLASS TargetDrawStrategy :  public iDrawPointStrategy
      {
      protected:
         TargetDrawStrategy() = default;

      public:
         static std::shared_ptr<TargetDrawStrategy> Create() { return std::shared_ptr<TargetDrawStrategy>(new TargetDrawStrategy()); }
	      virtual ~TargetDrawStrategy() = default;

         /// @brief Radius of the target in logical units
         /// @param radius 
         void SetRadius(LONG radius);
         LONG GetRadius() const;

         /// @brief Target foreground color
         /// @param crColor 
         void SetFgColor(COLORREF crColor);
         COLORREF GetFgColor() const;

         /// @brief Target background color
         /// @param crColor 
         void SetBgColor(COLORREF crColor);
         COLORREF GetBgColor() const;

         // iDrawPointStrategy Implementation
         virtual void Draw(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC) const override;
         virtual void DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
         virtual void DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const override;

      private:
         void DrawMe(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC) const;

         COLORREF m_FgColor = RED3;
         COLORREF m_BgColor = GREY86;
         LONG m_Radius = 7;
         
         mutable WBFL::Geometry::Point2d m_CachePoint;
         mutable COLORREF m_Color; // color used for drawing foreground (changes based on object's state)
      };
   };
};
