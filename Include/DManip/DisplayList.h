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
#include <DManip/DManipTypes.h>
#include <vector>

namespace WBFL
{
   namespace DManip
   {
      class iDisplayObject;
      class iDisplayMgr;
      class iDisplayListEvents;

      /// @brief Interface defining a list of display objects.
      class DMANIPCLASS iDisplayList
      {
      public:
#if defined _DEBUG
         iDisplayList();
         virtual ~iDisplayList();
#endif

         /// @brief Sets the display list identifier. Display lists must be given unique identifiers.
         /// @param id 
         virtual void SetID(IDType id) = 0;
         virtual IDType GetID() const = 0;

         /// @brief Manages the associated display manager
         /// @param pDispMgr 
         virtual void SetDisplayMgr(std::weak_ptr<iDisplayMgr> pDispMgr) = 0;
         virtual std::shared_ptr<iDisplayMgr> GetDisplayMgr() = 0;
         virtual std::shared_ptr<const iDisplayMgr> GetDisplayMgr() const = 0;

         /// @brief Adds a display object to the list
         /// @param pDO 
         virtual void AddDisplayObject(std::shared_ptr<iDisplayObject> pDO) = 0;

         /// @brief Returns a display object from the list
         /// @param index Index of the display object
         /// @return If the display list is empty, a nullptr is returned
         virtual std::shared_ptr<iDisplayObject> GetDisplayObject(IndexType index) = 0;
         virtual std::shared_ptr<const iDisplayObject> GetDisplayObject(IndexType index) const = 0;
         
         /// @brief Searches for a display object based on its identifier
         /// @param id 
         /// @return 
         virtual std::shared_ptr<iDisplayObject> FindDisplayObject(IDType id) = 0;
         virtual std::shared_ptr<const iDisplayObject> FindDisplayObject(IDType id) const = 0;

         /// @brief Finds a display object based on a logical rectangle
         /// @param rect 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const RECT& rect) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const RECT& rect) const = 0;

         /// @brief Finds a display object that overlaps a logical point
         /// @param point 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const POINT& point) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const POINT& point) const = 0;

         /// @brief Finds a display object contained within a model space rectangle
         /// @param rect 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Rect2d& rect) const = 0;

         /// @brief Find a display object that overlaps a model space point
         /// @param point 
         /// @return 
         virtual std::vector<std::shared_ptr<iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) = 0;
         virtual std::vector<std::shared_ptr<const iDisplayObject>> FindDisplayObjects(const WBFL::Geometry::Point2d& point) const = 0;


         /// @brief Removes a display object
         /// @param key display object identifier
         /// @param access Indicates identifier type
         virtual void RemoveDisplayObject(IDType key,AccessType access) = 0;

         /// @brief Clears the display, removing all display objects
         virtual void Clear() = 0;

         /// @brief Returns teh number of display objects in the list
         /// @return 
         virtual IndexType GetDisplayObjectCount() const = 0;

         /// @brief Selects all display objects
         virtual void SelectAll() = 0;

         /// @brief Draws all display objects in the list
         /// @param pDC 
         /// @param bSkipSelected If true, selected display objects are not drawn
         virtual void DrawDisplayObjects(CDC* pDC,bool bSkipSelected) = 0;

         /// @brief Hides display objects. Hidden display objects are not considered when
         /// computing model extents
         /// @param bHide 
         virtual void HideDisplayObjects(bool bHide) = 0;

         /// @brief Returns the model space extents of all the display objects in the list
         /// @return 
         virtual WBFL::Geometry::Size2d GetModelExtents() const = 0;

      #if defined(_DEBUG)
         virtual void DrawGravityWells(CDC* pDC) = 0;
      #endif

         /// @brief Registers an event sink with this display list. The event sink is notified of any events
         /// that occur on the list (such as adding or remove a display object)
         /// @param pEventSink 
         virtual void RegisterEventSink(std::shared_ptr<iDisplayListEvents> pEventSink) = 0;

         /// @brief Unregisters the event sink
         virtual void UnregisterEventSink() = 0;

         /// @brief Returns the event sink
         /// @return 
         virtual std::shared_ptr<iDisplayListEvents> GetEventSink() = 0;
      };
   };
};
