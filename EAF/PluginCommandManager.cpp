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

// EAFPluginCommandManager.cpp: implementation of the PluginCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\PluginCommandManager.h>

using namespace WBFL::EAF;

// Initialize static data members... using the all remaining commands for plug-ins
UINT PluginCommandManager::ms_MinID = EAF_FIRST_USER_COMMAND;
UINT PluginCommandManager::ms_MaxID = 0xDFFF;
UINT PluginCommandManager::ms_NextID = PluginCommandManager::ms_MinID;

void PluginCommandManager::ReserveTotalCommandIDRange(UINT nMinID,UINT nMaxID)
{
   ATLASSERT(EAF_FIRST_USER_COMMAND <= nMinID);
   ATLASSERT(nMaxID <= 0xDFFF);
   ms_MinID = nMinID;
   ms_MaxID = nMaxID;
   ms_NextID = ms_MinID;
}

UINT PluginCommandManager::GetCommandTotal()
{
   return ms_MaxID - ms_MinID;
}

UINT PluginCommandManager::ReserveCommandIDRange(UINT nCommands)
{
   if ( 0xDFFF < PluginCommandManager::ms_MaxID )
   {
      return -1; // out of room.... all the command IDs given to us by MFC have been used up
   }

   UINT nActualCommands;
   if ( PluginCommandManager::ms_MaxID <= (PluginCommandManager::ms_NextID + nCommands) )
   {
      nActualCommands = PluginCommandManager::ms_MaxID - PluginCommandManager::ms_NextID; // requesting more than we have left
   }
   else
   {
      nActualCommands = nCommands;
   }

   m_nBaseID = PluginCommandManager::ms_NextID;
   m_nCommands = nActualCommands;
   m_nNextID = m_nBaseID;
 
   m_Callbacks.clear(); // remove any previously mapped command IDs

   // increment for the next command range requested
   PluginCommandManager::ms_NextID += nActualCommands;

   return nActualCommands;
}

UINT PluginCommandManager::GetReservedCommandIDCount() const
{
   return m_nCommands;
}

void PluginCommandManager::GetReservedCommandIDRange(UINT* pFirst,UINT* pLast) const
{
   *pFirst = m_nBaseID;
   *pLast  = m_nBaseID + m_nCommands;
}

std::pair<BOOL,UINT> PluginCommandManager::AddCommandCallback(UINT nPluginCmdID, std::shared_ptr<WBFL::EAF::ICommandCallback>& pCallback)
{
   // If these asserts fire, you forgot to call ReserveCommandIDRange
   ATLASSERT(m_nBaseID != INVALID_ID);
   ATLASSERT(m_nCommands != INVALID_ID);

   if (pCallback == nullptr)
   {
      // plug-in commands without an associated callback cannot be in the plugin command mapping range
      ATLASSERT(nPluginCmdID < PluginCommandManager::ms_MinID || PluginCommandManager::ms_MaxID < nPluginCmdID);

      // no callback, nothing to map... pretend it was added
      return { TRUE,nPluginCmdID };
   }

   auto [bSuccess, nMappedCmdID] = GetMappedCommandID(nPluginCmdID, pCallback);
   if (bSuccess)
   {
      // command was already mapped
      return { TRUE,nMappedCmdID };
   }

   // command callback was not previously added... add it now
   nMappedCmdID = m_nNextID++; // generate the next command ID for the menus

   if (m_nBaseID + m_nCommands < nMappedCmdID)
   {
      ATLASSERT(FALSE); // command ID exceeds max value reserved for our range
      return { FALSE,-1 };
   }

   CCallbackItem callbackItem;
   callbackItem.nPluginCmdID = nPluginCmdID;
   callbackItem.pCallback = pCallback;
   m_Callbacks.insert(std::make_pair(nMappedCmdID, callbackItem));

   return { TRUE,nMappedCmdID };
}

std::pair<BOOL,UINT> PluginCommandManager::GetMappedCommandID(UINT nPluginCmdID, std::shared_ptr<WBFL::EAF::ICommandCallback>& pCallback)
{
   if (pCallback == nullptr)
   {
      return { TRUE,nPluginCmdID };
   }

   for (const auto& callbackEntry : m_Callbacks)
   {
      CCallbackItem callbackItem = callbackEntry.second;
      if (pCallback == callbackItem.pCallback && nPluginCmdID == callbackItem.nPluginCmdID)
      {
         return { TRUE,callbackEntry.first };
      }
   }

   return { FALSE,nPluginCmdID };
}

std::tuple<BOOL,UINT,std::shared_ptr<WBFL::EAF::ICommandCallback>> PluginCommandManager::GetCommandCallback(UINT nMappedID)
{
   CallbackContainer::iterator found;
   found = m_Callbacks.find(nMappedID);
   if (found != m_Callbacks.end())
   {
      CCallbackItem callbackItem = (*found).second;
      return { TRUE,callbackItem.nPluginCmdID,callbackItem.pCallback };
   }
   return { FALSE,-1,nullptr };
}

void PluginCommandManager::RemoveCommandCallback(UINT nMappedID)
{
   CallbackContainer::iterator found;
   found = m_Callbacks.find(nMappedID);
   if ( found != m_Callbacks.end() )
   {
      m_Callbacks.erase(found);
   }
}

std::vector<UINT> PluginCommandManager::GetMappedCommandIDs(std::shared_ptr<WBFL::EAF::ICommandCallback>& pCallback)
{
   std::vector<UINT> nMappedIDs;

   for ( const auto& callbackEntry : m_Callbacks)
   {
      CCallbackItem callbackItem = callbackEntry.second;

      if ( pCallback == callbackItem.pCallback)
      {
         nMappedIDs.push_back(callbackEntry.first);
      }
   }

   return nMappedIDs;
}

void PluginCommandManager::Clear()
{
   m_Callbacks.clear();
}

bool PluginCommandManager::IsInStandardRange(UINT nPluginCmdID)
{
   // Command IDs in this range are handled by MFC with standard
   // command processors.
   bool bIsMFCCommand = (0xE000 <= nPluginCmdID && nPluginCmdID <= 0xEFFF) ? true : false;
   UINT eafReservedCommandBase = EAF_RESERVED_COMMAND_BASE;
   UINT eafFirstUserCommand = EAF_FIRST_USER_COMMAND;
   bool bIsEAFCommand = (eafReservedCommandBase <= nPluginCmdID && nPluginCmdID < eafFirstUserCommand);
   return bIsMFCCommand // command ID from plugin is in the range of standard command processed by MFC
          ||
          bIsEAFCommand; // command ID from plugin is in the range of standard commands processed by EAF
}
