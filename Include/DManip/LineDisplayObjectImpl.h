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
#include <DManip/LineDisplayObject.h>
#include <DManip/SimpleDrawLineStrategy.h>
#include <DManip/ConnectorImpl.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display object based on a line connecting two points
      /// The visual elements of a line and defined by an associated iDrawLineStrategy object
      class DMANIPCLASS LineDisplayObject :
         public iLineDisplayObject,
         public Connector<DisplayObjectDefaultImpl>
      {
      protected:
         LineDisplayObject(IDType id);

      public:
         static std::shared_ptr<LineDisplayObject> Create(IDType id = INVALID_ID) {
            auto line = std::shared_ptr<LineDisplayObject>(new LineDisplayObject(id));
            line->SetConnectorParent(line->weak_from_this());
            return line;
         }
	      virtual ~LineDisplayObject() = default;

         // iDisplayObject implementations (methods that override or are not implemented by DisplayObjectDefaultImpl
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC, bool bHighlight) override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override;
         virtual bool HitTest(const POINT& point) const override;

         // iLineDisplayObject Implementation
         virtual void SetDrawLineStrategy(std::shared_ptr<iDrawLineStrategy> pStrategy) override;
         virtual std::shared_ptr<iDrawLineStrategy> GetDrawLineStrategy() override;
         virtual std::pair<CPoint,CPoint> GetLogicalEndPoints() const override;
         virtual std::pair<WBFL::Geometry::Point2d,WBFL::Geometry::Point2d> GetEndPoints() const override;

      private:
         std::shared_ptr<iDrawLineStrategy> m_DrawStrategy = SimpleDrawLineStrategy::Create();

         WBFL::Geometry::Point2d GetStartPoint() const;
         WBFL::Geometry::Point2d GetEndPoint() const;
      };
   };
};
