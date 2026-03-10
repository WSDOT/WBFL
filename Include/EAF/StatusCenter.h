///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#include <EAF\EAFExp.h>
#include <EAF\StatusItem.h>
#include <set>
#include <map>

namespace WBFL
{
   namespace EAF
   {
      class StatusCenterEventSink
      {
      public:
         virtual void OnStatusItemAdded(std::shared_ptr<const StatusItem> pItem) = 0;
         virtual void OnStatusItemRemoved(StatusItemIDType id) = 0;
      };

      class StatusItemCompare
      {
      public:
         bool operator()(const std::shared_ptr<StatusItem>& a, const std::shared_ptr<StatusItem>& b) const;
      };

      class EAFCLASS StatusCenter
      {
      public:
         StatusCenter();
         ~StatusCenter();

         bool IsEnabled() const;
         void Enable(bool bEnable);

         StatusGroupIDType CreateStatusGroupID();
         StatusItemIDType Add(std::shared_ptr<StatusItem> pItem);
         bool RemoveByID(StatusItemIDType id);
         bool RemoveByIndex(IndexType index);
         bool RemoveByStatusGroupID(StatusGroupIDType id);
         std::shared_ptr<StatusItem> GetByID(StatusItemIDType id);
         std::shared_ptr<const StatusItem> GetByID(StatusItemIDType id) const;
         std::shared_ptr<StatusItem> GetByIndex(IndexType index);
         std::shared_ptr<const StatusItem> GetByIndex(IndexType index) const;
         IndexType Count() const;

         WBFL::EAF::StatusSeverityType GetSeverity() const;

         /// @brief Registers a callback object that is called upon when a status item needs to provide its severity or execute a remidation action
         /// @param pCallback 
         /// @return 
         StatusCallbackIDType RegisterCallbackItem(std::shared_ptr<StatusCallback> pCallback);
         WBFL::EAF::StatusSeverityType GetSeverity(StatusCallbackIDType callbackID) const;

         void EditItem(StatusItemIDType id);

         /// @brief Registers an event sink that is notified of status center events
         /// @param pSink 
         IDType RegisterEventSink(std::shared_ptr<StatusCenterEventSink> pSink);
         void UnregisterEventSink(IDType cookie);

      private:
         bool m_bIsEnabled;
         StatusGroupIDType m_NextStatusGroupID;
         StatusItemIDType m_NextID;
         StatusCallbackIDType m_NextCallbackID;
         std::shared_ptr<StatusItem> m_pCurrentItem;

         using Container = std::set<std::shared_ptr<StatusItem>,StatusItemCompare>;
         Container m_Items;

         IDType m_EventSinkCookie = 0;
         using Sinks = std::map<IDType,std::shared_ptr<StatusCenterEventSink>>;
         Sinks m_Sinks;

         using Callbacks = std::map<StatusCallbackIDType,std::shared_ptr<StatusCallback>>;
         Callbacks m_Callbacks;

         std::shared_ptr<StatusCallback> GetCallback(StatusCallbackIDType callbackID);
         const std::shared_ptr<StatusCallback> GetCallback(StatusCallbackIDType callbackID) const;

         void NotifyAdded(std::shared_ptr<const StatusItem> pNewItem);
         void NotifyRemoved(StatusItemIDType id);
      };
   };
};
