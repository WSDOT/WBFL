// PluginCommandManager.cpp: implementation of the CPluginCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PluginCommandManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPluginCommandManager::CPluginCommandManager()
{
   m_nBaseID = 1;
}

CPluginCommandManager::~CPluginCommandManager()
{

}

void CPluginCommandManager::SetBaseCommandID(UINT nBaseID)
{
   m_nBaseID = nBaseID;
}

UINT CPluginCommandManager::AddCommandCallback(UINT nPluginCmdID,ICommandCallback* pCallback)
{
   UINT nMappedID;
   if ( GetMappedCommandID(nPluginCmdID,pCallback,&nMappedID) )
      return nMappedID;

   // command callback was not previously added... add it now

   nMappedID = m_nBaseID++; // generate the next command ID for the menus

   CCallbackItem callbackItem;
   callbackItem.nPluginCmdID = nPluginCmdID;
   callbackItem.pCallback = pCallback;
   m_Callbacks.insert( std::make_pair(nMappedID,callbackItem) );

   return nMappedID;
}

BOOL CPluginCommandManager::GetMappedCommandID(UINT nPluginCmdID,ICommandCallback* pCallback,UINT* pMappedCmdID)
{
   CallbackContainer::iterator iter;
   _COM_SMARTPTR_TYPEDEF(IUnknown,__uuidof(IUnknown));

   IUnknownPtr pUnk1;
   pCallback->QueryInterface(__uuidof(IUnknown),(void**)&pUnk1);

   for ( iter = m_Callbacks.begin(); iter != m_Callbacks.end(); iter++ )
   {
      CCallbackItem callbackItem = (*iter).second;
      IUnknownPtr pUnk2;

      callbackItem.pCallback->QueryInterface(__uuidof(IUnknown),(void**)&pUnk2);
      if ( pUnk1 == pUnk2 && nPluginCmdID == callbackItem.nPluginCmdID )
      {
         *pMappedCmdID = (*iter).first;
         return TRUE;
      }
   }

   return FALSE;
}

BOOL CPluginCommandManager::GetCommandCallback(UINT nMappedID,UINT* pPluginCmdID,ICommandCallback** ppCallback)
{
   CallbackContainer::iterator found;
   found = m_Callbacks.find(nMappedID);
   if ( found != m_Callbacks.end() )
   {
      CCallbackItem callbackItem = (*found).second;
      *pPluginCmdID = callbackItem.nPluginCmdID;
      (*ppCallback) = callbackItem.pCallback;
      (*ppCallback)->AddRef();
      return TRUE;
   }

   (*ppCallback) = NULL;
   return FALSE;
}

void CPluginCommandManager::RemoveCommandCallback(UINT nMappedID)
{
   CallbackContainer::iterator found;
   found = m_Callbacks.find(nMappedID);
   if ( found != m_Callbacks.end() )
   {
      m_Callbacks.erase(found);
   }
}

std::vector<UINT> CPluginCommandManager::GetMappedCommandIDs(ICommandCallback* pCallback)
{
   std::vector<UINT> nMappedIDs;

   CallbackContainer::iterator iter;
   _COM_SMARTPTR_TYPEDEF(IUnknown,__uuidof(IUnknown));

   IUnknownPtr pUnk1;
   pCallback->QueryInterface(__uuidof(IUnknown),(void**)&pUnk1);

   for ( iter = m_Callbacks.begin(); iter != m_Callbacks.end(); iter++ )
   {
      CCallbackItem callbackItem = (*iter).second;
      IUnknownPtr pUnk2;

      callbackItem.pCallback->QueryInterface(__uuidof(IUnknown),(void**)&pUnk2);
      if ( pUnk1 == pUnk2 )
      {
         nMappedIDs.push_back((*iter).first);
      }
   }

   return nMappedIDs;
}
