///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool StatusItemCompare::operator()(const std::shared_ptr<CEAFStatusItem>& a, const std::shared_ptr<CEAFStatusItem>& b) const
{
   // Use a simple string compare with message. Older versions (pre Jan 2019) tried to get tricky
   // and use IsEqual, but this caused unexpected issues with the strict weak ordering
   // requirements of std::set. One issue was duplicate issues in the status center
   int st = a->CompareDescriptions(b.get());

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

CEAFStatusCenter::CEAFStatusCenter()
{
   m_NextID = 1;
   m_NextStatusGroupID = 1;
   m_NextCallbackID = 1;
   m_pCurrentItem = nullptr;
   m_bIsEnabled = true;
}

CEAFStatusCenter::~CEAFStatusCenter()
{
}

bool CEAFStatusCenter::IsEnabled() const
{
   return m_bIsEnabled;
}

void CEAFStatusCenter::Enable(bool bEnable)
{
   m_bIsEnabled = bEnable;
}
   
StatusGroupIDType CEAFStatusCenter::CreateStatusGroupID()
{
   return m_NextStatusGroupID++;
}

StatusItemIDType CEAFStatusCenter::Add(CEAFStatusItem* pItem)
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

bool CEAFStatusCenter::RemoveByID(StatusItemIDType id)
{
   Container::iterator itemIter(m_Items.begin());
   Container::iterator itemIterEnd(m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      auto pItem = *itemIter;
      if ( pItem->GetID() == id && m_pCurrentItem != pItem.get() )
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

bool CEAFStatusCenter::RemoveByIndex(CollectionIndexType index)
{
   if ( index < 0 || (CollectionIndexType)m_Items.size() <= index )
      return false;

   Container::iterator iter = m_Items.begin();
   for ( CollectionIndexType i = 1; i < index; i++ )
   {
      iter++;
   }

   auto pItem = *iter;
   if ( m_pCurrentItem != pItem.get() )
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

bool CEAFStatusCenter::RemoveByStatusGroupID(StatusGroupIDType id)
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
         if ( m_pCurrentItem != pItem.get() )
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

CEAFStatusItem* CEAFStatusCenter::GetByID(StatusItemIDType id)
{
   for (auto pItem : m_Items)
   {
      if (pItem->GetID() == id)
         return pItem.get();
   }

   return nullptr;
}

const CEAFStatusItem* CEAFStatusCenter::GetByID(StatusItemIDType id) const
{
   for(const auto pItem : m_Items)
   {
      if (pItem->GetID() == id)
         return pItem.get();
   }

   return nullptr;
}

CEAFStatusItem* CEAFStatusCenter::GetByIndex(CollectionIndexType index)
{
   if ( m_Items.size() <= index )
      return nullptr;

   auto iter = m_Items.begin();
   for ( CollectionIndexType i = 0; i < index; i++ )
   {
      iter++;
   }

   return iter->get();
}

const CEAFStatusItem* CEAFStatusCenter::GetByIndex(CollectionIndexType index) const
{
   if (m_Items.size() <= index)
      return nullptr;

   auto iter = m_Items.cbegin();
   for (CollectionIndexType i = 0; i < index; i++)
   {
      iter++;
   }

   return iter->get();
}

CollectionIndexType CEAFStatusCenter::Count() const
{
   return m_Items.size();
}

eafTypes::StatusSeverityType CEAFStatusCenter::GetSeverity() const
{
   eafTypes::StatusSeverityType severity = eafTypes::statusInformation;

   for(const auto pItem : m_Items)
   {
      severity = Max(severity, GetSeverity(pItem->GetCallbackID()));
      if (severity == eafTypes::statusError)
         break; // serverity is at it's maximum level, no reason to continue the loop
   }

   return severity;
}

void CEAFStatusCenter::SinkEvents(IEAFStatusCenterEventSink* pSink)
{
   m_Sinks.insert(pSink);
}

void CEAFStatusCenter::UnSinkEvents(IEAFStatusCenterEventSink* pSink)
{
   Sinks::iterator found = m_Sinks.find(pSink);
   if ( found != m_Sinks.end() )
      m_Sinks.erase(found);
}

void CEAFStatusCenter::NotifyAdded(CEAFStatusItem* pNewItem)
{
   if ( !IsEnabled() )
      return;

   Sinks::iterator iter(m_Sinks.begin());
   Sinks::iterator end(m_Sinks.end());
   for ( ; iter != end; iter++ )
   {
      IEAFStatusCenterEventSink* pSink = *iter;
      pSink->OnStatusItemAdded(pNewItem);
   }
}

void CEAFStatusCenter::NotifyRemoved(StatusItemIDType id)
{
   if ( !IsEnabled() )
      return;

   Sinks::iterator iter(m_Sinks.begin());
   Sinks::iterator end(m_Sinks.end());
   for ( ; iter != end; iter++ )
   {
      IEAFStatusCenterEventSink* pSink = *iter;
      pSink->OnStatusItemRemoved(id);
   }
}

StatusCallbackIDType CEAFStatusCenter::RegisterCallbackItem(iStatusCallback* pCallback)
{
   StatusCallbackIDType callbackID = m_NextCallbackID++;
   m_Callbacks.emplace(callbackID,pCallback);
   return callbackID;
}

eafTypes::StatusSeverityType CEAFStatusCenter::GetSeverity(StatusCallbackIDType callbackID) const
{
   const auto pCallback = GetCallback(callbackID);
   if ( !pCallback )
      return eafTypes::statusInformation;

   return pCallback->GetSeverity();
}

std::shared_ptr<iStatusCallback> CEAFStatusCenter::GetCallback(StatusCallbackIDType callbackID)
{
   auto found = m_Callbacks.find(callbackID);
   if (found == m_Callbacks.end())
      return nullptr;

   return (*found).second;
}

const std::shared_ptr<iStatusCallback> CEAFStatusCenter::GetCallback(StatusCallbackIDType callbackID) const
{
   auto found = m_Callbacks.find(callbackID);
   if (found == m_Callbacks.end())
      return nullptr;

   return (*found).second;
}

void CEAFStatusCenter::EditItem(StatusItemIDType id)
{
   if ( !IsEnabled() )
      return;

   CEAFStatusItem* pItem = GetByID(id);
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
      AfxMessageBox(_T("An error occured while attempting to display status item details"),MB_OK | MB_ICONEXCLAMATION);
   }
}
