// EAFPluginManager.h: interface for the CEAFPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EAFPluginManager_H__CFB14911_A143_4649_986A_033E59386F83__INCLUDED_)
#define AFX_EAFPluginManager_H__CFB14911_A143_4649_986A_033E59386F83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <comdef.h>
#include <comcat.h>
#include <vector>
#include <EAF\EAFAppPlugin.h>
#include <EAF\EAFExp.h>

_COM_SMARTPTR_TYPEDEF(IEAFAppPlugin,IID_IEAFAppPlugin);

class EAFCLASS CEAFPluginManager
{
public:
	CEAFPluginManager();
	virtual ~CEAFPluginManager();

	virtual BOOL LoadPlugins(const CATID& catid);
   virtual void UnloadPlugins();

   virtual void RegisterDocTemplates(CWinApp* pApp);
   virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

   UINT GetPluginCount() const;
   HRESULT GetPlugin(UINT idx,IEAFAppPlugin** ppPlugin);

protected:
   std::vector<IEAFAppPluginPtr> m_Plugins;
};

#endif // !defined(AFX_EAFPluginManager_H__CFB14911_A143_4649_986A_033E59386F83__INCLUDED_)
