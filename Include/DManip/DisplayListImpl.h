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
#include <DManip/DisplayList.h>
#include <DManip/DisplayListEvents.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display list, implementing the iDisplayList interface
      class DMANIPCLASS DisplayList : public iDisplayList, public std::enable_shared_from_this<DisplayList>
      {
      protected:
         DisplayList(IDType id) : m_ID(id) {};

      public:
         static std::shared_ptr<DisplayList> Create(IDType id = INVALID_ID) { return std::shared_ptr<DisplayList>(new DisplayList(id)); }
	      virtual ~DisplayList() = default;

         // iDisplayList Implementation
         virtual void SetID(IDType id) override;
         virtual IDType GetID() const override;

         virtual void SetDisplayMgr(std::weak_ptr<iDisplayMgr> pDispMgr) override;
         virtual std::shared_ptr<iDisplayMgr> GetDisplayMgr() override;
         virtual std::shared_ptr<const iDisplayMgr> GetDisplayMgr() const override;

         virtual void AddDisplayObject(std::shared_ptr<iDisplayObject> pDO) override;
         virtual std::shared_ptr<iDisplayObject> GetDisplayObject(IndexType index) override;
         virtual std::shared_ptr<const iDisplayObject> GetDisplayObject(IndexType index) const override;
         virtual std::shared_ptr<iDisplayObject> FindDisplayObject(IDType id) override;
         virtual std::shared_ptr<const iDisplayObject> FindDisplayObject(IDType id) const override;
         virtual void RemoveDisplayObject(IDType key, AccessType access) override;
         virtual void Clear() override;
         virtual IndexType GetDisplayObjectCount() const override;

         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const RECT& rect) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const RECT& rect) const override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const POINT& point) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const POINT& point) const override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) const override;
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) override;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) const override;

         virtual void DrawDisplayObjects(CDC* pDC, bool bSkipSelected) override;
         virtual void HideDisplayObjects(bool bHide) override;
         virtual void SelectAll() override;

         virtual WBFL::Geometry::Size2d GetModelExtents() const override;

#if defined(_DEBUG)
         virtual void DrawGravityWells(CDC* pDC) override;
#endif

         // Event Sink
         virtual void RegisterEventSink(std::shared_ptr<iDisplayListEvents> pEventSink) override;
         virtual void UnregisterEventSink() override;
         virtual std::shared_ptr<iDisplayListEvents> GetEventSink() override;

      private:
         std::weak_ptr<iDisplayMgr> m_pDispMgr;
         IDType m_ID = INVALID_ID;

         std::shared_ptr<iDisplayListEvents> m_EventSink;

         std::vector<std::shared_ptr<iDisplayObject>> m_DisplayObjects;

         void Fire_OnDisplayObjectAdded(std::shared_ptr<iDisplayObject> pDO);
         void Fire_OnDisplayObjectRemoved(IDType doID);
         void Fire_OnDisplayObjectsCleared();
      };
   };
};
