///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

bool StatusItemCompare::operator()(CEAFStatusItem* a,CEAFStatusItem* b)
{
   if ( a->IsEqual(b) || b->IsEqual(a) )
      return false;

   return a->GetID() < b->GetID();
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
   Container::iterator itemIter(m_Items.begin());
   Container::iterator itemIterEnd(m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      CEAFStatusItem* pItem = *itemIter;
      delete pItem;
      pItem = nullptr;
   }

   Callbacks::iterator callbackIter(m_Callbacks.begin());
   Callbacks::iterator callbackIterEnd(m_Callbacks.end());
   for ( ; callbackIter != callbackIterEnd; callbackIter++ )
   {
      iStatusCallback* pCallback = (*callbackIter).second;
      delete pCallback;
      (*callbackIter).second = nullptr;
   }
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

   pItem->SetID(m_NextID++);

   std::pair<Container::iterator,bool> result;
   result = m_Items.insert(pItem);

   if ( result.second == true )
   {
      NotifyAdded(pItem);
      return pItem->GetID();
   }
   else
   {
      delete pItem;
      pItem = nullptr;
   }

   return INVALID_ID; // failed
}

bool CEAFStatusCenter::RemoveByID(StatusItemIDType id)
{
   Container::iterator itemIter(m_Items.begin());
   Container::iterator itemIterEnd(m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      CEAFStatusItem* pItem = *itemIter;
      if ( pItem->GetID() == id && m_pCurrentItem != pItem )
      {
         delete pItem;
         pItem = nullptr;
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

   CEAFStatusItem* pItem = *iter;
   if ( m_pCurrentItem != pItem )
   {
      StatusItemIDType id = pItem->GetID();
      delete pItem;
      pItem = nullptr;
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
      CEAFStatusItem* pItem = *itemIter;
      if ( pItem->GetStatusGroupID() == id )
      {
         if ( m_pCurrentItem != pItem )
         {
            StatusItemIDType itemID = pItem->GetID();
            delete pItem;
            pItem = nullptr;
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
   Container::iterator itemIter(m_Items.begin());
   Container::iterator itemIterEnd(m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      CEAFStatusItem* pItem = *itemIter;
      if ( pItem->GetID() == id )
         return pItem;
   }

   return nullptr;
}

CEAFStatusItem* CEAFStatusCenter::GetByIndex(CollectionIndexType index)
{
   if ( m_Items.size() <= index )
      return nullptr;

   Container::iterator iter = m_Items.begin();
   for ( CollectionIndexType i = 0; i < index; i++ )
   {
      iter ++;
   }

   return *iter;
}

CollectionIndexType CEAFStatusCenter::Count()
{
   return m_Items.size();
}

eafTypes::StatusSeverityType CEAFStatusCenter::GetSeverity()
{
   eafTypes::StatusSeverityType severity = eafTypes::statusInformation;

   Container::iterator itemIter(m_Items.begin());
   Container::iterator itemIterEnd(m_Items.end());
   for ( ; itemIter != itemIterEnd; itemIter++ )
   {
      CEAFStatusItem* pItem = *itemIter;
      severity = Max(severity, GetSeverity(pItem->GetCallbackID()));
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
   m_Callbacks.insert(std::make_pair(callbackID,pCallback));
   return callbackID;
}

eafTypes::StatusSeverityType CEAFStatusCenter::GetSeverity(StatusCallbackIDType callbackID)
{
   iStatusCallback* pCallback = GetCallback(callbackID);
   if ( !pCallback )
      return eafTypes::statusInformation;

   return pCallback->GetSeverity();
}

iStatusCallback* CEAFStatusCenter::GetCallback(StatusCallbackIDType callbackID)
{
   Callbacks::iterator found = m_Callbacks.find(callbackID);
   if ( found == m_Callbacks.end() )
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
   iStatusCallback* pCallback = GetCallback(callbackID);
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
