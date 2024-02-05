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

#include "pch.h"
#include <DManip/DisplayListImpl.h>
#include <DManip/DisplayObject.h>
#include <DManip/DisplayMgr.h>

using namespace WBFL::DManip;

void DisplayList::SetDisplayMgr(std::weak_ptr<iDisplayMgr> pDispMgr)
{
   m_pDispMgr = pDispMgr;
}

std::shared_ptr<iDisplayMgr> DisplayList::GetDisplayMgr()
{
   return m_pDispMgr.lock();
}

std::shared_ptr<const iDisplayMgr> DisplayList::GetDisplayMgr() const
{
   return m_pDispMgr.lock();
}

void DisplayList::SetID(IDType id)
{
   m_ID = id;
}

IDType DisplayList::GetID() const
{
   return m_ID;
}

void DisplayList::AddDisplayObject(std::shared_ptr<iDisplayObject> pDO)
{
   m_DisplayObjects.emplace_back(pDO);
   pDO->SetDisplayList(weak_from_this());
   Fire_OnDisplayObjectAdded(pDO);
}

std::shared_ptr<iDisplayObject> DisplayList::GetDisplayObject(IndexType index)
{
   PRECONDITION(0 <= index and index <= m_DisplayObjects.size());
   if (m_DisplayObjects.empty()) return nullptr;
   return m_DisplayObjects[index];
}

std::shared_ptr<const iDisplayObject> DisplayList::GetDisplayObject(IndexType index) const
{
   PRECONDITION(0 <= index and index <= m_DisplayObjects.size());
   if (m_DisplayObjects.empty()) return nullptr;
   return m_DisplayObjects[index];
}

std::shared_ptr<iDisplayObject> DisplayList::FindDisplayObject(IDType id)
{
   auto iter = std::find_if(m_DisplayObjects.begin(), m_DisplayObjects.end(), [id](auto& dispObj) {return dispObj->GetID() == id; });
   return (iter == m_DisplayObjects.end() ? nullptr : *iter);
}

std::shared_ptr<const iDisplayObject> DisplayList::FindDisplayObject(IDType id) const
{
   auto iter = std::find_if(m_DisplayObjects.cbegin(), m_DisplayObjects.cend(), [id](auto& dispObj) {return dispObj->GetID() == id; });
   return (iter == m_DisplayObjects.cend() ? nullptr : *iter);
}

void DisplayList::RemoveDisplayObject(IDType key,AccessType access)
{
   IDType doID = INVALID_ID;
   if ( access == AccessType::ByIndex )
   {
      IndexType index = (IndexType)key;
      // Remove display object by index
      if ( index < 0 || m_DisplayObjects.size() <= index )
         return;

      auto iter = m_DisplayObjects.begin() + index;
      auto pDO(*iter);
      
      doID = pDO->GetID();

      m_DisplayObjects.erase(iter);
   }
   else
   {
      // Remove display object by id
      auto iter = std::find_if(m_DisplayObjects.begin(), m_DisplayObjects.end(), [key](auto& dispObj) {return dispObj->GetID() == key; });
      if (iter == m_DisplayObjects.end())
         return;

      doID = key;
      m_DisplayObjects.erase(iter);
   }

   Fire_OnDisplayObjectRemoved(doID);
}

void DisplayList::Clear()
{
   if ( !m_DisplayObjects.empty() )
   {
      m_DisplayObjects.clear();
      Fire_OnDisplayObjectsCleared();
   }
}

IndexType DisplayList::GetDisplayObjectCount() const
{
   return m_DisplayObjects.size();
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayList::FindDisplayObjects(const POINT& point)
{
   std::vector<std::shared_ptr<iDisplayObject>> dispObjs;
   std::copy_if(m_DisplayObjects.begin(), m_DisplayObjects.end(), std::back_inserter(dispObjs), [&point](auto& dispObj) { return dispObj->HitTest(point); });
   return dispObjs;
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayList::FindDisplayObjects(const POINT& point) const
{
   std::vector<std::shared_ptr<const iDisplayObject>> dispObjs;
   std::copy_if(m_DisplayObjects.begin(), m_DisplayObjects.end(), std::back_inserter(dispObjs), [&point](auto& dispObj) { return dispObj->HitTest(point); });
   return dispObjs;
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayList::FindDisplayObjects(const WBFL::Geometry::Point2d& point)
{
   auto dispMgr = GetDisplayMgr();
   auto map = dispMgr->GetCoordinateMap();

   POINT p;
   map->WPtoLP(point,&p.x,&p.y);
   return FindDisplayObjects(p);
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayList::FindDisplayObjects(const WBFL::Geometry::Point2d& point) const
{
   auto dispMgr = GetDisplayMgr();
   auto map = dispMgr->GetCoordinateMap();

   POINT p;
   map->WPtoLP(point, &p.x, &p.y);
   return FindDisplayObjects(p);
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayList::FindDisplayObjects(const RECT& rect)
{
   CRect r(rect);
   r.NormalizeRect();

   std::vector<std::shared_ptr<iDisplayObject>> dispObjs;
   std::copy_if(m_DisplayObjects.begin(), m_DisplayObjects.end(), std::back_inserter(dispObjs), [&r](auto& dispObj) { return dispObj->TouchesRect(r); });
   return dispObjs;
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayList::FindDisplayObjects(const RECT& rect) const
{
   CRect r(rect);
   r.NormalizeRect();

   std::vector<std::shared_ptr<const iDisplayObject>> dispObjs;
   std::copy_if(m_DisplayObjects.begin(), m_DisplayObjects.end(), std::back_inserter(dispObjs), [&r](auto& dispObj) { return dispObj->TouchesRect(r); });
   return dispObjs;
}

std::vector<std::shared_ptr<iDisplayObject>> DisplayList::FindDisplayObjects(const WBFL::Geometry::Rect2d& rect)
{
   auto dispMgr = GetDisplayMgr();
   auto map = dispMgr->GetCoordinateMap();

   POINT tl, br;
   map->WPtoLP(rect.TopLeft(), &tl.x, &tl.y);
   map->WPtoLP(rect.BottomRight(), &br.x, &br.y);
   RECT r;
   r.left = tl.x;
   r.right = br.x;
   r.top = tl.y;
   r.bottom = br.y;
   return FindDisplayObjects(r);
}

std::vector<std::shared_ptr<const iDisplayObject>> DisplayList::FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) const
{
   auto dispMgr = GetDisplayMgr();
   auto map = dispMgr->GetCoordinateMap();

   POINT tl, br;
   map->WPtoLP(rect.TopLeft(), &tl.x, &tl.y);
   map->WPtoLP(rect.BottomRight(), &br.x, &br.y);
   RECT r;
   r.left = tl.x;
   r.right = br.x;
   r.top = tl.y;
   r.bottom = br.y;
   return FindDisplayObjects(r);
}

void DisplayList::DrawDisplayObjects(CDC* pDC,bool bSkipSelected)
{
   for(auto& display_object : m_DisplayObjects)
   {
      if ( !bSkipSelected )
      {
         // if not skipping selected, draw
         display_object->Draw(pDC);
      }
      else
      {
         // if skipping selected, draw only if not selected
         if ( !display_object->IsSelected() )
            display_object->Draw(pDC);
      }
   }
}

void DisplayList::HideDisplayObjects(bool bHide)
{
   std::for_each(m_DisplayObjects.begin(), m_DisplayObjects.end(), [bHide](auto& display_object) {display_object->Visible(!bHide); });
}

void DisplayList::SelectAll()
{
   auto display_mgr = GetDisplayMgr();
   std::for_each(m_DisplayObjects.begin(), m_DisplayObjects.end(), [display_mgr](auto& display_object) {display_mgr->SelectObject(display_object,FALSE); });
}

WBFL::Geometry::Size2d DisplayList::GetModelExtents() const
{
   WBFL::Geometry::Rect2d world_rect;

   if (m_DisplayObjects.size() == 0)
      return world_rect.Size();

   auto iter = m_DisplayObjects.begin();
   auto& display_object(*iter);
   world_rect = display_object->GetBoundingBox();
   iter++;
   std::for_each(iter, m_DisplayObjects.end(), [&world_rect](auto& display_object) {world_rect.Union(display_object->GetBoundingBox()); });

   return world_rect.Size();
}

#if defined(_DEBUG)
void DisplayList::DrawGravityWells(CDC* pDC)
{
   std::for_each(m_DisplayObjects.begin(), m_DisplayObjects.end(), [pDC](auto& display_object) {display_object->DrawGravityWell(pDC); });
}
#endif

void DisplayList::RegisterEventSink(std::shared_ptr<iDisplayListEvents> pEventSink)
{
   UnregisterEventSink();
   m_EventSink = pEventSink;
}

void DisplayList::UnregisterEventSink()
{
   m_EventSink.reset();
}

std::shared_ptr<iDisplayListEvents> DisplayList::GetEventSink()
{
   return m_EventSink;
}

void DisplayList::Fire_OnDisplayObjectAdded(std::shared_ptr<iDisplayObject> pDO)
{
   if (auto event_sink = m_EventSink)
      event_sink->OnDisplayObjectAdded(m_ID,pDO);
}

void DisplayList::Fire_OnDisplayObjectRemoved(IDType doID)
{
   if (auto event_sink = m_EventSink)
      event_sink->OnDisplayObjectRemoved(m_ID,doID);
}

void DisplayList::Fire_OnDisplayObjectsCleared()
{
   if (auto event_sink = m_EventSink)
      event_sink->OnDisplayObjectsCleared(m_ID);
}
