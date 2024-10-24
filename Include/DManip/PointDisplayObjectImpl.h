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
#include <DManip/PointDisplayObject.h>
#include <DManip/Draggable.h>
#include <DManip/DrawPointStrategy.h>
#include <DManip/ConnectableImpl.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display object based on a single coordinate point
      /// The visual elements of a point and defined by an associated iDrawPointStrategy object
      class DMANIPCLASS PointDisplayObject :
         public iPointDisplayObject,
         public iDraggable,
         public Connectable<DisplayObjectDefaultImpl>
      {
      protected:
         PointDisplayObject(IDType id);

      public:
         static std::shared_ptr<PointDisplayObject> Create(IDType id = INVALID_ID) {
            auto point = std::shared_ptr<PointDisplayObject>(new PointDisplayObject(id));
            point->SetConnectableParent(point->weak_from_this());
            return point;
         }
	      virtual ~PointDisplayObject() = default;

         // iDisplayObject
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC, bool bHighlight) override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override;

         // iPointDisplayObject
         virtual void SetPosition(const WBFL::Geometry::Point2d& pos, bool bRedraw, bool bFireEvent) override;
         virtual const WBFL::Geometry::Point2d& GetPosition() const override;
         virtual CPoint GetLogicalPosition() const override;
         virtual void Offset(const WBFL::Geometry::Size2d& offset, bool bRedraw, bool bFireEvent) override;
         virtual void SetDrawingStrategy(std::shared_ptr<iDrawPointStrategy> pStrategy) override;
         virtual std::shared_ptr<iDrawPointStrategy> GetDrawingStrategy() override;
         virtual void EnableAutoUpdate(bool bEnable) override;
         virtual bool IsAutoUpdateEnabled() const override;

         // iDraggable Implementation
         virtual void SetDragData(std::shared_ptr<iDragData> dd) override;
         virtual std::shared_ptr<iDragData> GetDragData() override;
         virtual UINT Format() override;
         virtual void PrepareDrag(std::shared_ptr<iDragDataSink> pSink) override;
         virtual void OnDrop(std::shared_ptr<iDragDataSource> pSource) override;
         virtual void DrawDragImage(CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) override;
         virtual void OnDragMoved(const WBFL::Geometry::Size2d& offset) override;
         virtual void OnMoved() override;
         virtual void OnCopied() override;


      private:
         bool m_bAutoUpdate = false;
         std::shared_ptr<iDrawPointStrategy> m_pDrawStrategy;
         WBFL::Geometry::Point2d m_Position;
         std::shared_ptr<iDragData> m_pDragData;

         static UINT ms_cfFormat;
      };
   };
};
