///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFPluginCommandManager::CEAFPluginCommandManager()
{
   m_nBaseID = 1;
}

CEAFPluginCommandManager::~CEAFPluginCommandManager()
{

}

void CEAFPluginCommandManager::SetBaseCommandID(UINT nBaseID)
{
   // set the base ID to be 1 more than the highest command ID used by non-plugin objects
   m_nBaseID = nBaseID;
}

UINT CEAFPluginCommandManager::AddCommandCallback(UINT nPluginCmdID,ICommandCallback* pCallback)
{
   UINT nMappedID;
   if ( GetMappedCommandID(nPluginCmdID,pCallback,&nMappedID) )
      return nMappedID;

   // command callback was not previously added... add it now

   if ( pCallback )
      nMappedID = m_nBaseID++; // generate the next command ID for the menus
   else
      nMappedID = nPluginCmdID; // using default MFC message routing, so don't alter the command ID

   CCallbackItem callbackItem;
   callbackItem.nPluginCmdID = nPluginCmdID;
   callbackItem.pCallback = pCallback;
   m_Callbacks.insert( std::make_pair(nMappedID,callbackItem) );

   return nMappedID;
}

BOOL CEAFPluginCommandManager::GetMappedCommandID(UINT nPluginCmdID,ICommandCallback* pCallback,UINT* pMappedCmdID)
{
   CallbackContainer::iterator iter;
   CComQIPtr<IUnknown, &IID_IUnknown> pUnk1(pCallback);

   for ( iter = m_Callbacks.begin(); iter != m_Callbacks.end(); iter++ )
   {
      CCallbackItem callbackItem = (*iter).second;

      CComQIPtr<IUnknown, &IID_IUnknown> pUnk2(callbackItem.pCallback);
      if ( pUnk1 == pUnk2 && nPluginCmdID == callbackItem.nPluginCmdID )
      {
         *pMappedCmdID = (*iter).first;
         return TRUE;
      }
   }

   return FALSE;
}

BOOL CEAFPluginCommandManager::GetCommandCallback(UINT nMappedID,UINT* pPluginCmdID,ICommandCallback** ppCallback)
{
   CallbackContainer::iterator found;
   found = m_Callbacks.find(nMappedID);
   if ( found != m_Callbacks.end() )
   {
      CCallbackItem callbackItem = (*found).second;
      *pPluginCmdID = callbackItem.nPluginCmdID;
      (*ppCallback) = callbackItem.pCallback;
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

std::vector<UINT> CEAFPluginCommandManager::GetMappedCommandIDs(ICommandCallback* pCallback)
{
   std::vector<UINT> nMappedIDs;

   CallbackContainer::iterator iter;
   CComQIPtr<IUnknown, &IID_IUnknown> pUnk1(pCallback);

   for ( iter = m_Callbacks.begin(); iter != m_Callbacks.end(); iter++ )
   {
      CCallbackItem callbackItem = (*iter).second;

      CComQIPtr<IUnknown, &IID_IUnknown> pUnk2(callbackItem.pCallback);

      if ( pUnk1 == pUnk2 )
      {
         nMappedIDs.push_back((*iter).first);
      }
   }

   return nMappedIDs;
}
