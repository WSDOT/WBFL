///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <EAF\EAFResources.h>
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
   m_nBaseID   = -1;
   m_nCommands = -1;
   m_nNextID   = -1;
}

CEAFPluginCommandManager::~CEAFPluginCommandManager()
{

}

UINT CEAFPluginCommandManager::ReserveCommandIDRange(UINT nCommands)
{
   if ( 0xDFFF <= CEAFPluginCommandManager::ms_MaxID )
      return -1; // out of room.... all the command IDs given to us by MFC have been used up

   UINT nActualCommands;
   if ( 0xDFFF <= CEAFPluginCommandManager::ms_NextID + nCommands )
      nActualCommands = 0xDFFF - CEAFPluginCommandManager::ms_NextID; // requesting more than we have left
   else
      nActualCommands = nCommands;

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
   // If these asserts fire, you forgot to callReserveCommandIDRange
   ATLASSERT(m_nBaseID != -1);
   ATLASSERT(m_nCommands != -1);

   if ( GetMappedCommandID(nPluginCmdID,pCallback,pMappedID) )
   {
      return TRUE;
   }

   // command callback was not previously added... add it now

   if ( pCallback )
   {
      *pMappedID = m_nNextID++; // generate the next command ID for the menus

      if ( m_nBaseID+m_nCommands < *pMappedID )
      {
         ATLASSERT(FALSE); // command ID exceeds max value reserved for our range
         return FALSE;
      }
   }
   else
   {
      *pMappedID = nPluginCmdID; // using default MFC message routing, so don't alter the command ID
   }

   CCallbackItem callbackItem;
   callbackItem.nPluginCmdID = nPluginCmdID;
   callbackItem.pCallback    = pCallback;
   m_Callbacks.insert( std::make_pair(*pMappedID,callbackItem) );

   return TRUE;
}

BOOL CEAFPluginCommandManager::GetMappedCommandID(UINT nPluginCmdID,IEAFCommandCallback* pCallback,UINT* pMappedCmdID)
{
   CallbackContainer::iterator iter;
   CComQIPtr<IUnknown, &IID_IUnknown> pUnk1(pCallback);

   for ( iter = m_Callbacks.begin(); iter != m_Callbacks.end(); iter++ )
   {
      CCallbackItem callbackItem = (*iter).second;

      CComQIPtr<IUnknown, &IID_IUnknown> pUnk2(callbackItem.pCallback.m_T);
      if ( pUnk1 == pUnk2 && nPluginCmdID == callbackItem.nPluginCmdID )
      {
         *pMappedCmdID = (*iter).first;
         return TRUE;
      }
   }

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
      (*ppCallback) = callbackItem.pCallback.m_T;
      if (*ppCallback)
         (*ppCallback)->AddRef();

      return TRUE;
   }

   (*ppCallback) = NULL;
   return FALSE;
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

   CallbackContainer::iterator iter;
   CComQIPtr<IUnknown, &IID_IUnknown> pUnk1(pCallback);

   for ( iter = m_Callbacks.begin(); iter != m_Callbacks.end(); iter++ )
   {
      CCallbackItem callbackItem = (*iter).second;

      CComQIPtr<IUnknown, &IID_IUnknown> pUnk2(callbackItem.pCallback.m_T);

      if ( pUnk1 == pUnk2 )
      {
         nMappedIDs.push_back((*iter).first);
      }
   }

   return nMappedIDs;
}

void CEAFPluginCommandManager::Clear()
{
   m_Callbacks.clear();
}
