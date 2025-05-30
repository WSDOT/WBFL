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

#include "stdafx.h"
#include <EAF\StatusCenter.h>
#include <MathEx.h>

using namespace WBFL::EAF;

bool StatusItemCompare::operator()(const std::shared_ptr<StatusItem>& a, const std::shared_ptr<StatusItem>& b) const
{
   // Use a simple string compare with message. Older versions (pre Jan 2019) tried to get tricky
   // and use IsEqual, but this caused unexpected issues with the strict weak ordering
   // requirements of std::set. One issue was duplicate issues in the status center
   int st = a->CompareDescriptions(b);

#ifdef _DEBUG
   if (st == 0)
   {
      // Different classes should never create identical messages. This is probably an error.
      CString stra = typeid(*a).name();
      CString strb = typeid(*b).name();
      ATLASSERT(stra == strb);
   }
#endif
   
   return st < 0;
}

StatusCenter::StatusCenter()
{
   m_NextID = 1;
   m_NextStatusGroupID = 1;
   m_NextCallbackID = 1;
   m_pCurrentItem = nullptr;
   m_bIsEnabled = true;
}

StatusCenter::~StatusCenter()
{
}

bool StatusCenter::IsEnabled() const
{
   return m_bIsEnabled;
}

void StatusCenter::Enable(bool bEnable)
{
   m_bIsEnabled = bEnable;
}
   
StatusGroupIDType StatusCenter::CreateStatusGroupID()
{
   return m_NextStatusGroupID++;
}

StatusItemIDType StatusCenter::Add(std::shared_ptr<StatusItem> pItem)
{
#if defined _DEBUG
   StatusCallbackIDType callbackID = pItem->GetCallbackID();
   Callbacks::iterator found = m_Callbacks.find(callbackID);

   // If this assert fires, then an associated callback handler
   // has not been registered
   ASSERT( found != m_Callbacks.end() );
#endif // _DEBUG


   auto result = m_Items.emplace(pItem);

   if ( result.second == true )
   {
      pItem->SetID(m_NextID++);
      NotifyAdded(pItem);
      return pItem->GetID();
   }
   return INVALID_ID; // failed
}

bool StatusCenter::RemoveByID(StatusItemIDType id)
{
   Container::iterator itemIter(m_Items.begin());
   Container::iterator itemIterEnd(m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      auto pItem = *itemIter;
      if ( pItem->GetID() == id && m_pCurrentItem != pItem )
      {
         m_Items.erase(itemIter);
         NotifyRemoved(id);
         return true;
      }
      else
      {
         pItem->RemoveAfterEdit(true);
      }
   }

   return false;
}

bool StatusCenter::RemoveByIndex(IndexType index)
{
   if ( index < 0 || (IndexType)m_Items.size() <= index )
      return false;

   Container::iterator iter = m_Items.begin();
   for ( IndexType i = 1; i < index; i++ )
   {
      iter++;
   }

   auto pItem = *iter;
   if ( m_pCurrentItem != pItem )
   {
      StatusItemIDType id = pItem->GetID();
      m_Items.erase(iter);
      NotifyRemoved(id);
      return true;
   }
   else
   {
      pItem->RemoveAfterEdit(true);
   }

   return false;
}

bool StatusCenter::RemoveByStatusGroupID(StatusGroupIDType id)
{
   bool bItemsRemoved = false;
   Container::iterator iter;

   Container items = m_Items;
   m_Items.clear();

   Container::iterator itemIter(items.begin());
   Container::iterator itemIterEnd(items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      auto pItem = *itemIter;
      if ( pItem->GetStatusGroupID() == id )
      {
         if ( m_pCurrentItem != pItem )
         {
            StatusItemIDType itemID = pItem->GetID();
            NotifyRemoved(itemID);
            bItemsRemoved = true;
         }
         else
         {
            NotifyRemoved(pItem->GetID());
            pItem->RemoveAfterEdit(true);
         }
      }
      else
      {
         m_Items.insert(pItem);
      }
   }

   return bItemsRemoved;
}

std::shared_ptr<StatusItem> StatusCenter::GetByID(StatusItemIDType id)
{
   for (auto pItem : m_Items)
   {
      if (pItem->GetID() == id)
         return pItem;
   }

   return nullptr;
}

std::shared_ptr<const StatusItem> StatusCenter::GetByID(StatusItemIDType id) const
{
   for(const auto pItem : m_Items)
   {
      if (pItem->GetID() == id)
         return pItem;
   }

   return nullptr;
}

std::shared_ptr<StatusItem> StatusCenter::GetByIndex(IndexType index)
{
   if ( m_Items.size() <= index )
      return nullptr;

   auto iter = m_Items.begin();
   for ( IndexType i = 0; i < index; i++ )
   {
      iter++;
   }

   return *iter;
}

std::shared_ptr<const StatusItem> StatusCenter::GetByIndex(IndexType index) const
{
   if (m_Items.size() <= index)
      return nullptr;

   auto iter = m_Items.cbegin();
   for (IndexType i = 0; i < index; i++)
   {
      iter++;
   }

   return *iter;
}

IndexType StatusCenter::Count() const
{
   return m_Items.size();
}

WBFL::EAF::StatusSeverityType StatusCenter::GetSeverity() const
{
   WBFL::EAF::StatusSeverityType severity = WBFL::EAF::StatusSeverityType::Information;

   for(const auto pItem : m_Items)
   {
      severity = Max(severity, GetSeverity(pItem->GetCallbackID()));
      if (severity == WBFL::EAF::StatusSeverityType::Error)
         break; // severity is at it's maximum level, no reason to continue the loop
   }

   return severity;
}

IDType StatusCenter::RegisterEventSink(std::shared_ptr<StatusCenterEventSink> pSink)
{
   auto cookie = m_EventSinkCookie++;
   m_Sinks.insert(std::make_pair(cookie, pSink));
   return cookie;
}

void StatusCenter::UnregisterEventSink(IDType cookie)
{
   auto found = m_Sinks.find(cookie);
   if (found != m_Sinks.end())
      m_Sinks.erase(found);
}

void StatusCenter::NotifyAdded(std::shared_ptr<const StatusItem> pNewItem)
{
   if ( !IsEnabled() )
      return;

   for (auto& [cookie, sink] : m_Sinks)
   {
      sink->OnStatusItemAdded(pNewItem);
   }
}

void StatusCenter::NotifyRemoved(StatusItemIDType id)
{
   if ( !IsEnabled() )
      return;

   for(auto& [cookie,sink] : m_Sinks)
   {
      sink->OnStatusItemRemoved(id);
   }
}

StatusCallbackIDType StatusCenter::RegisterCallbackItem(std::shared_ptr<StatusCallback> pCallback)
{
   StatusCallbackIDType callbackID = m_NextCallbackID++;
   m_Callbacks.emplace(callbackID,pCallback);
   return callbackID;
}

WBFL::EAF::StatusSeverityType StatusCenter::GetSeverity(StatusCallbackIDType callbackID) const
{
   const auto pCallback = GetCallback(callbackID);
   if ( !pCallback )
      return WBFL::EAF::StatusSeverityType::Information;

   return pCallback->GetSeverity();
}

std::shared_ptr<StatusCallback> StatusCenter::GetCallback(StatusCallbackIDType callbackID)
{
   auto found = m_Callbacks.find(callbackID);
   if (found == m_Callbacks.end())
      return nullptr;

   return (*found).second;
}

const std::shared_ptr<StatusCallback> StatusCenter::GetCallback(StatusCallbackIDType callbackID) const
{
   auto found = m_Callbacks.find(callbackID);
   if (found == m_Callbacks.end())
      return nullptr;

   return (*found).second;
}

void StatusCenter::EditItem(StatusItemIDType id)
{
   if ( !IsEnabled() )
      return;

   auto pItem = GetByID(id);
   ASSERT(pItem != nullptr);

   StatusCallbackIDType callbackID = pItem->GetCallbackID();
   auto pCallback = GetCallback(callbackID);
   ASSERT(pCallback != nullptr);

   if ( pCallback )
   {
      m_pCurrentItem = pItem;

      pCallback->Execute(pItem);

      m_pCurrentItem = nullptr;

      // remove item if required
      if (pItem->RemoveAfterEdit())
      {
         RemoveByID(id);
      }
   }
   else
   {
      AfxMessageBox(_T("An error occurred while attempting to display status item details"),MB_OK | MB_ICONEXCLAMATION);
   }
}
