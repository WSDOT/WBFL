// PluginCommandManager.h: interface for the CPluginCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUGINCOMMANDMANAGER_H__1E2BBC96_C93D_4C4C_A7DE_33C8541F0943__INCLUDED_)
#define AFX_PLUGINCOMMANDMANAGER_H__1E2BBC96_C93D_4C4C_A7DE_33C8541F0943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <EAF\EAFUIIntegration.h>

class CPluginCommandManager  
{
public:
	CPluginCommandManager();
	virtual ~CPluginCommandManager();

   void SetBaseCommandID(UINT nBaseID);

   UINT AddCommandCallback(UINT nPluginCmdID,ICommandCallback* pCallback);
   BOOL GetCommandCallback(UINT nMappedID,UINT* pPluginCmdID,ICommandCallback** ppCallback);
   void RemoveCommandCallback(UINT nMappedID);

   // returns all the mapped command ids of this callback
   std::vector<UINT> GetMappedCommandIDs(ICommandCallback* pCallback);


   BOOL GetMappedCommandID(UINT nPluginCmdID,ICommandCallback* pCallback,UINT* pMappedCmdID);

private:
   UINT m_nBaseID; // ID of first callback command

   struct CCallbackItem 
   {
      UINT nPluginCmdID;
      CComPtr<ICommandCallback> pCallback;
   };

   typedef std::map<UINT,CCallbackItem> CallbackContainer;
   CallbackContainer m_Callbacks;
};

#endif // !defined(AFX_PLUGINCOMMANDMANAGER_H__1E2BBC96_C93D_4C4C_A7DE_33C8541F0943__INCLUDED_)
