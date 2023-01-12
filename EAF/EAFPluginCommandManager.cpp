///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

// EAFPluginCommandManager.cpp: implementation of the CEAFPluginCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFPluginCommandManager.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Initialize static data members... using the all remaining commands for plug-ins
UINT CEAFPluginCommandManager::ms_MinID = EAF_FIRST_USER_COMMAND;
UINT CEAFPluginCommandManager::ms_MaxID = 0xDFFF;
UINT CEAFPluginCommandManager::ms_NextID = CEAFPluginCommandManager::ms_MinID;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CEAFPluginCommandManager::ReserveTotalCommandIDRange(UINT nMinID,UINT nMaxID)
{
   ATLASSERT(EAF_FIRST_USER_COMMAND <= nMinID);
   ATLASSERT(nMaxID <= 0xDFFF);
   ms_MinID = nMinID;
   ms_MaxID = nMaxID;
   ms_NextID = ms_MinID;
}

UINT CEAFPluginCommandManager::GetCommandTotal()
{
   return ms_MaxID - ms_MinID;
}

CEAFPluginCommandManager::CEAFPluginCommandManager()
{
   // bogus values to detect if user forget to call ReseveCommandIDRange 
   m_nBaseID   = INVALID_ID;
   m_nCommands = INVALID_ID;
   m_nNextID   = INVALID_ID;
}

CEAFPluginCommandManager::~CEAFPluginCommandManager()
{

}

UINT CEAFPluginCommandManager::ReserveCommandIDRange(UINT nCommands)
{
   if ( 0xDFFF < CEAFPluginCommandManager::ms_MaxID )
   {
      return -1; // out of room.... all the command IDs given to us by MFC have been used up
   }

   UINT nActualCommands;
   if ( CEAFPluginCommandManager::ms_MaxID <= (CEAFPluginCommandManager::ms_NextID + nCommands) )
   {
      nActualCommands = CEAFPluginCommandManager::ms_MaxID - CEAFPluginCommandManager::ms_NextID; // requesting more than we have left
   }
   else
   {
      nActualCommands = nCommands;
   }

   m_nBaseID = CEAFPluginCommandManager::ms_NextID;
   m_nCommands = nActualCommands;
   m_nNextID = m_nBaseID;
 
   m_Callbacks.clear(); // remove any previously mapped command IDs

   // increment for the next command range requested
   CEAFPluginCommandManager::ms_NextID += nActualCommands;

   return nActualCommands;
}

UINT CEAFPluginCommandManager::GetReservedCommandIDCount() const
{
   return m_nCommands;
}

void CEAFPluginCommandManager::GetReservedCommandIDRange(UINT* pFirst,UINT* pLast) const
{
   *pFirst = m_nBaseID;
   *pLast  = m_nBaseID + m_nCommands;
}

BOOL CEAFPluginCommandManager::AddCommandCallback(UINT nPluginCmdID,IEAFCommandCallback* pCallback,UINT* pMappedID)
{
   // If these asserts fire, you forgot to call ReserveCommandIDRange
   ATLASSERT(m_nBaseID   != INVALID_ID);
   ATLASSERT(m_nCommands != INVALID_ID);

   if ( pCallback == nullptr )
   {
      // plug-in commands without an associated callback cannot be in the plugin command mapping range
      ATLASSERT(nPluginCmdID < CEAFPluginCommandManager::ms_MinID || CEAFPluginCommandManager::ms_MaxID < nPluginCmdID);

      // no callback, nothing to map... pretend it was added
      *pMappedID = nPluginCmdID;
      return TRUE;
   }

   if ( GetMappedCommandID(nPluginCmdID,pCallback,pMappedID) )
   {
      // command was already mapped
      return TRUE;
   }

   // command callback was not previously added... add it now
   *pMappedID = m_nNextID++; // generate the next command ID for the menus

   if ( m_nBaseID+m_nCommands < *pMappedID )
   {
      ATLASSERT(FALSE); // command ID exceeds max value reserved for our range
      return FALSE;
   }

   CCallbackItem callbackItem;
   callbackItem.nPluginCmdID = nPluginCmdID;
   callbackItem.pCallback    = pCallback;
   m_Callbacks.insert( std::make_pair(*pMappedID,callbackItem) );

   return TRUE;
}

BOOL CEAFPluginCommandManager::GetMappedCommandID(UINT nPluginCmdID,IEAFCommandCallback* pCallback,UINT* pMappedCmdID)
{
   if ( pCallback == nullptr )
   {
      *pMappedCmdID = nPluginCmdID;
      return TRUE;
   }

   CComQIPtr<IUnknown, &IID_IUnknown> pUnk1(pCallback);


   for ( const auto& callbackEntry : m_Callbacks)
   {
      CCallbackItem callbackItem = callbackEntry.second;

      CComQIPtr<IUnknown, &IID_IUnknown> pUnk2(callbackItem.pCallback);
      if ( pUnk1 == pUnk2 && nPluginCmdID == callbackItem.nPluginCmdID )
      {
         *pMappedCmdID = callbackEntry.first;
         return TRUE;
      }
   }

   *pMappedCmdID = nPluginCmdID;
   return FALSE;
}

BOOL CEAFPluginCommandManager::GetCommandCallback(UINT nMappedID,UINT* pPluginCmdID,IEAFCommandCallback** ppCallback)
{
   CallbackContainer::iterator found;
   found = m_Callbacks.find(nMappedID);
   if ( found != m_Callbacks.end() )
   {
      CCallbackItem callbackItem = (*found).second;
      *pPluginCmdID = callbackItem.nPluginCmdID;
      (*ppCallback) = callbackItem.pCallback;
      if (*ppCallback)
      {
         (*ppCallback)->AddRef();
      }

      return TRUE;
   }

   (*ppCallback) = nullptr;
   return TRUE;
}

void CEAFPluginCommandManager::RemoveCommandCallback(UINT nMappedID)
{
   CallbackContainer::iterator found;
   found = m_Callbacks.find(nMappedID);
   if ( found != m_Callbacks.end() )
   {
      m_Callbacks.erase(found);
   }
}

std::vector<UINT> CEAFPluginCommandManager::GetMappedCommandIDs(IEAFCommandCallback* pCallback)
{
   std::vector<UINT> nMappedIDs;
   CComQIPtr<IUnknown, &IID_IUnknown> pUnk1(pCallback);

   for ( const auto& callbackEntry : m_Callbacks)
   {
      CCallbackItem callbackItem = callbackEntry.second;

      CComQIPtr<IUnknown, &IID_IUnknown> pUnk2(callbackItem.pCallback);

      if ( pUnk1 == pUnk2 )
      {
         nMappedIDs.push_back(callbackEntry.first);
      }
   }

   return nMappedIDs;
}

void CEAFPluginCommandManager::Clear()
{
   m_Callbacks.clear();
}

bool CEAFPluginCommandManager::IsInStandardRange(UINT nPluginCmdID)
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
