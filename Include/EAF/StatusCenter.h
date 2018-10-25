///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include <EAF\EAFStatusItem.h>
#include <set>
#include <map>

class IEAFStatusCenterEventSink
{
public:
   virtual void OnStatusItemAdded(CEAFStatusItem* pItem) = 0;
   virtual void OnStatusItemRemoved(StatusItemIDType id) = 0;
};

class StatusItemCompare
{
public:
   bool operator()(CEAFStatusItem* a,CEAFStatusItem* b);
};

class EAFCLASS CEAFStatusCenter
{
public:
   CEAFStatusCenter();
   ~CEAFStatusCenter();

   bool IsEnabled() const;
   void Enable(bool bEnable);

   StatusGroupIDType CreateStatusGroupID();
   StatusItemIDType Add(CEAFStatusItem* pItem);
   bool RemoveByID(StatusItemIDType id);
   bool RemoveByIndex(CollectionIndexType index);
   bool RemoveByStatusGroupID(StatusGroupIDType id);
   CEAFStatusItem* GetByID(StatusItemIDType id);
   CEAFStatusItem* GetByIndex(CollectionIndexType index);
   CollectionIndexType Count();

   eafTypes::StatusSeverityType GetSeverity();

   StatusCallbackIDType RegisterCallbackItem(iStatusCallback* pCallback);
   eafTypes::StatusSeverityType GetSeverity(StatusCallbackIDType callbackID);

   void EditItem(StatusItemIDType id);

   void SinkEvents(IEAFStatusCenterEventSink* pSink);
   void UnSinkEvents(IEAFStatusCenterEventSink* pSink);

private:
   bool m_bIsEnabled;
   StatusGroupIDType m_NextStatusGroupID;
   StatusItemIDType m_NextID;
   StatusCallbackIDType m_NextCallbackID;
   CEAFStatusItem* m_pCurrentItem;

   typedef std::set<CEAFStatusItem*,StatusItemCompare> Container;
   Container m_Items;

   typedef std::set<IEAFStatusCenterEventSink*> Sinks;
   Sinks m_Sinks;

   typedef std::map<StatusCallbackIDType,iStatusCallback*> Callbacks;
   Callbacks m_Callbacks;

   iStatusCallback* GetCallback(StatusCallbackIDType callbackID);

   void NotifyAdded(CEAFStatusItem* pNewItem);
   void NotifyRemoved(StatusItemIDType id);
};
