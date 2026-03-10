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
#include <DManip/DisplayObjectDefaultImpl.h>
#include <optional>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display object that is composed from other display objects
      class DMANIPCLASS CompositeDisplayObject : public DisplayObjectDefaultImpl
      {
      protected:
         CompositeDisplayObject(IDType id);

      public:
         static std::shared_ptr<CompositeDisplayObject> Create(IDType id = INVALID_ID) { return std::shared_ptr<CompositeDisplayObject>(new CompositeDisplayObject(id)); }
         virtual ~CompositeDisplayObject();

         void AddDisplayObject(std::shared_ptr<iDisplayObject> pDO);
         void RemoveDisplayObject(IDType key, AccessType access);
         IndexType GetDisplayObjectCount();
         std::shared_ptr<iDisplayObject> GetDisplayObject(IDType key, AccessType access);
         void ClearDisplayObjects();
         std::shared_ptr<iDisplayList> GetDisplayObjects();

         // iDisplayObject Implementation
         virtual void SetDisplayList(std::weak_ptr<iDisplayList> pDL) override;
         virtual void Visible(bool bVisible) override;
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC, bool bHighlight) override;
      #if defined(_DEBUG)
         virtual void DrawGravityWell(CDC* pDC) override;
      #endif

         // Size and Hit Testing
         virtual bool HitTest(const POINT& point) const override;
         virtual RECT GetLogicalBoundingBox() const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override;
         virtual bool TouchesRect(const RECT& r) const override;

         // Selection
         virtual void Select(bool bSelect) override;
         virtual void SetSelectionType(SelectionType st) override;
         virtual void RetainSelection(bool bRetain);

      private:
         std::shared_ptr<iDisplayList> m_CompositeItems;
         mutable std::optional<WBFL::Geometry::Rect2d> m_BoundingBox;
      };
   };
};
