///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Tools
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
#include <DManip/PolyLineDisplayObject.h>
#include <Colors.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display object for a polygon line. The polyline is defined by a sequence of points and is connected by straight lines.
      class DMANIPCLASS PolyLineDisplayObject : public iPolyLineDisplayObject
      {
      private:
         PolyLineDisplayObject(IDType id);

      public:
         static std::shared_ptr<PolyLineDisplayObject> Create(IDType id = INVALID_ID) { return std::shared_ptr<PolyLineDisplayObject>(new PolyLineDisplayObject(id)); }
         ~PolyLineDisplayObject() = default;

         // iDisplayObject Implementation

         // Drawing
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC, bool bHighlight) override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override;

         // iPolyLineDisplayObject
         virtual void SetPoints(const std::vector<WBFL::Geometry::Point2d>& points) override;
         virtual void AddPoints(const std::vector<WBFL::Geometry::Point2d>& points) override;
         virtual void AddPoint(const WBFL::Geometry::Point2d& point) override;
         virtual void InsertPoint(IndexType idx, const WBFL::Geometry::Point2d& point) override;
         virtual const WBFL::Geometry::Point2d& GetPoint(IndexType idx) const override;
         virtual void RemovePoint(IndexType idx) override;
         virtual IndexType GetPointCout() const override;
         virtual void ClearPoints() override;
         virtual void SetColor(COLORREF color) override;
         virtual COLORREF GetColor() const override;
         virtual void SetWidth(unsigned width) override;
         virtual unsigned GetWidth() const override;
         virtual void SetPointType(PointType ptType) override;
         virtual PointType GetPointType() const override;
         virtual void SetPointSize(UINT size) override;
         virtual UINT GetPointSize() const override;

      private:
         COLORREF m_Color = BLACK;
         unsigned m_Width = 100;
         UINT m_Size = 0;
         PointType m_PointType = PointType::None;

         std::vector<WBFL::Geometry::Point2d> m_Points;
         void DrawPoint(CDC* pDC, LONG lx, LONG ly);
      };
   };
};
