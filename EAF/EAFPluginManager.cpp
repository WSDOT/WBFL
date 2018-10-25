// EAFEAFPluginManager.cpp: implementation of the CEAFEAFPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFPluginManager.h>
#include <EAF\EAFSplashScreen.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFPluginManager::CEAFPluginManager()
{

}

CEAFPluginManager::~CEAFPluginManager()
{

}

BOOL CEAFPluginManager::LoadPlugins(const CATID &catid)
{
   USES_CONVERSION;

   _COM_SMARTPTR_TYPEDEF(ICatRegister,__uuidof(ICatRegister));
   ICatRegisterPtr pICatReg;

   HRESULT hr = pICatReg.CreateInstance(CLSID_StdComponentCategoriesMgr);

   if ( FAILED(hr) )
   {
      AfxMessageBox("Failed to create the component category manager");
      return FALSE;
   }

   _COM_SMARTPTR_TYPEDEF(ICatInformation,__uuidof(ICatInformation));
   ICatInformationPtr pICatInfo;
   pICatReg->QueryInterface(&pICatInfo);

   _COM_SMARTPTR_TYPEDEF(IEnumCLSID,__uuidof(IEnumCLSID));
   IEnumCLSIDPtr pIEnumCLSID;

   const int nID = 1;
   CATID ID[nID];
   ID[0] = catid;

   pICatInfo->EnumClassesOfCategories(nID,ID,0,NULL,&pIEnumCLSID);

   // load plug-ins 5 at a time
   CLSID clsid[5]; 
   ULONG nFetched = 0;
   while ( SUCCEEDED(pIEnumCLSID->Next(5,clsid,&nFetched)) && 0 < nFetched)
   {
      for ( ULONG i = 0; i < nFetched; i++ )
      {
         IEAFAppPluginPtr plugin;
         plugin.CreateInstance(clsid[i]);

         if ( plugin == NULL )
         {
            LPOLESTR pszUserType;
            OleRegGetUserType(clsid[i],USERCLASSTYPE_SHORT,&pszUserType);
            CString strMsg;
            strMsg.Format("Failed to load %s Application plug in",OLE2A(pszUserType));
            AfxMessageBox(strMsg);
         }
         else
         {
            CString str = plugin->GetComponentName();
            CString strMsg;
            strMsg.Format("Loading %s",str);
            CEAFSplashScreen::SetText(strMsg);

            m_Plugins.push_back(plugin);
         }
      }
   }

   std::vector<IEAFAppPluginPtr>::iterator iter;
   for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
   {
      IEAFAppPluginPtr plugin = *iter;
      CString str = plugin->GetComponentName();
      CString strMsg;
      strMsg.Format("Initializing %s",str);
      CEAFSplashScreen::SetText(strMsg);

      plugin->Init();
   }

   CEAFSplashScreen::SetText("");
   CEAFSplashScreen::CloseOnNextTimeout();

   return TRUE;
}

void CEAFPluginManager::UnloadPlugins()
{
   std::vector<IEAFAppPluginPtr>::iterator iter;
   for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
   {
      IEAFAppPluginPtr plugin = *iter;
      plugin->Terminate();
   }
   m_Plugins.clear();
}

void CEAFPluginManager::RegisterDocTemplates(CWinApp* pApp)
{
   std::vector<IEAFAppPluginPtr>::iterator iter;
   for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
   {
      IEAFAppPluginPtr plugin = *iter;
      CEAFDocTemplate* pDocTemplate = plugin->CreateDocTemplate();
      if ( pDocTemplate )
      {
         if ( pDocTemplate->m_pPlugin == NULL )
            pDocTemplate->m_pPlugin = plugin.GetInterfacePtr();

         pApp->AddDocTemplate( pDocTemplate );
      }
   }
}

BOOL CEAFPluginManager::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
   // TODO: Improve EAF Plugin Command Routing
   // This isn't what we want to do.... we want to route the command to the command target
   // of the active plug in (the one for which the document was created)

   std::vector<IEAFAppPluginPtr>::iterator iter;
   for ( iter = m_Plugins.begin(); iter != m_Plugins.end(); iter++ )
   {
      IEAFAppPluginPtr plugin = *iter;
      CCmdTarget* pCmdTarget = plugin->GetCommandTarget();
      if ( pCmdTarget != NULL && pCmdTarget->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo) )
         return TRUE;
   }

   return FALSE;
}

UINT CEAFPluginManager::GetPluginCount() const
{
   return m_Plugins.size();
}

HRESULT CEAFPluginManager::GetPlugin(UINT idx,IEAFAppPlugin** ppPlugin)
{
   if ( m_Plugins.size() <= idx )
      return E_INVALIDARG;

   (*ppPlugin) = m_Plugins[idx];
   (*ppPlugin)->AddRef();
   return S_OK;
}
