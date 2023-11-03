///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

// EAFBrokerDocument.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFHelp.h>
#include <EAF\EAFHints.h>
#include <EAF\EAFAutoProgress.h>
#include "EAFDocProxyAgent.h"
#include <AgentTools.h>

#include "ConfigureReportsDlg.h"

#include "WBFLReportManagerAgent.h"
#include "WBFLGraphManagerAgent.h"

#include <sstream> // for ostringstream

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEAFBrokerDocument

IMPLEMENT_DYNAMIC(CEAFBrokerDocument, CEAFDocument)

CEAFBrokerDocument::CEAFBrokerDocument(bool bReporting,bool bGraphing)
{
   m_bUseReportManager = bReporting;
   m_bUseGraphManager = bGraphing;
   m_pBroker = nullptr;
   m_pDocProxyAgent =  nullptr;
   m_bIsGraphMenuPopulated = false;

   // The base class registers as a unit mode listener
   // However, the DocProxyAgent also registers as a listener
   // This generates 2 units changed events whenever the units change
   // Remove this document from the listener list so that only one event is received
   CEAFApp* pApp = EAFGetApp();
   pApp->RemoveUnitModeListener(this);

   m_bFavoriteReports = TRUE; // enable feature by default
   m_bDisplayFavoriteReports = FALSE;
   m_helpIDCustom = -1;
   m_helpIDFavorite = -1;
   m_helpIDCustomReportDefinition = -1;
}

CEAFBrokerDocument::~CEAFBrokerDocument()
{
}


BEGIN_MESSAGE_MAP(CEAFBrokerDocument, CEAFDocument)
	//{{AFX_MSG_MAP(CEAFBrokerDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(EAFID_REPORT_MENU_DISPLAY_MODE, OnReportMenuDisplayMode)
   ON_UPDATE_COMMAND_UI(EAFID_REPORT_MENU_DISPLAY_MODE, OnUpdateReportMenuDisplayMode)
	ON_COMMAND(EAFID_OPTIONS_REPORTING, OnConfigureReports)

END_MESSAGE_MAP()

BOOL CEAFBrokerDocument::OnOpenDocument(LPCTSTR lpszPathName)
{
   BOOL bResult = CEAFDocument::OnOpenDocument(lpszPathName);

   return bResult;
}

void CEAFBrokerDocument::OnCloseDocument()
{
   // Put report favorites options back into CPGSuperBaseAppPlugin
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   CComPtr<IEAFAppPlugin> pAppPlugin;
   pTemplate->GetPlugin(&pAppPlugin);
   CEAFCustomReportMixin* pCustomReportMixin = dynamic_cast<CEAFCustomReportMixin*>(pAppPlugin.p);
   if ( pCustomReportMixin )
   {
      BOOL bDisplayFavorites = DisplayFavoriteReports();
      const std::vector<std::_tstring>& vFavorites = GetFavoriteReports();

      pCustomReportMixin->DisplayFavoriteReports(bDisplayFavorites);
      pCustomReportMixin->SetFavoriteReports(vFavorites);

      // user-defined custom reports
      const CEAFCustomReports& reports = GetCustomReports();
      pCustomReportMixin->SetCustomReports(reports);
   }

   CEAFDocument::OnCloseDocument();
}

void CEAFBrokerDocument::DeleteContents()
{
   CEAFDocument::DeleteContents();
   BrokerShutDown();
}

void CEAFBrokerDocument::OnCreateFinalize()
{
   CEAFDocument::OnCreateFinalize();

   GET_IFACE(IEAFStatusCenter,pStatusCenter);
   m_scidCustomReportWarning = pStatusCenter->RegisterCallback(new CEAFStatusItemCallback(eafTypes::statusWarning)); 
   m_StatusGroupID = pStatusCenter->CreateStatusGroupID();


   // Transfer report favorites and custom reports data from CXBeamRateAppPlugin to CEAFBrokerDocument (this)
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   CComPtr<IEAFAppPlugin> pAppPlugin;
   pTemplate->GetPlugin(&pAppPlugin);
   CEAFCustomReportMixin* pCustomReportMixin = dynamic_cast<CEAFCustomReportMixin*>(pAppPlugin.p);
   if ( pCustomReportMixin )
   {
      pCustomReportMixin->SaveCustomReports(TRUE);

      BOOL bDisplayFavorites = pCustomReportMixin->DisplayFavoriteReports();
      std::vector<std::_tstring> vFavorites = pCustomReportMixin->GetFavoriteReports();

      DisplayFavoriteReports(bDisplayFavorites);
      SetFavoriteReports(vFavorites);

      CEAFCustomReports customs = pCustomReportMixin->GetCustomReports();
      SetCustomReports(customs);

      // At this point we have loaded all hard-coded reports and read custom
      // report data from the registry, and broker is loaded. Create custom reports
      m_bmpCustomReports.LoadBitmap(IDB_CREPORT_BMP);

      IntegrateCustomReports(true);
   }
}

/////////////////////////////////////////////////////////////////////////////
// CEAFBrokerDocument diagnostics

#ifdef _DEBUG
void CEAFBrokerDocument::AssertValid() const
{
	CEAFDocument::AssertValid();
}

void CEAFBrokerDocument::Dump(CDumpContext& dc) const
{
	CEAFDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFBrokerDocument commands
HRESULT CEAFBrokerDocument::GetBroker(IBroker** ppBroker)
{
   if ( m_pBroker )
   {
      (*ppBroker) = m_pBroker;
      (*ppBroker)->AddRef();
      return S_OK;
   }

   return E_FAIL;
}

CATID CEAFBrokerDocument::GetExtensionAgentCategoryID()
{
   return CLSID_NULL;
}

BOOL CEAFBrokerDocument::Init()
{
   if ( !CreateBroker() )
   {
      InitFailMessage();
      return FALSE;
   }

   if ( !CEAFDocument::Init() )
   {
      return FALSE;
   }

   // tell the broker to wait on calling the IAgent::Init function until
   // pBrokerInit->InitAgents() is called
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);
   pBrokerInit->DelayInit();

   BOOL bAgentsLoaded = LoadAgents();
   if ( !bAgentsLoaded )
   {
      OnLoadAgentsError();
      return FALSE;
   }

   InitAgents();
   
   return TRUE;
}

BOOL CEAFBrokerDocument::CreateBroker()
{
   // create the broker object
   HRESULT hr;
   hr = ::CoCreateInstance( CLSID_Broker2, nullptr, CLSCTX_INPROC_SERVER, IID_IBroker, (void**)&m_pBroker );
   if ( FAILED(hr) )
   {
      std::_tostringstream msg;
      msg << _T("Failed to create broker. hr = ") << hr << std::endl << std::ends;
      FailSafeLogMessage( msg.str().c_str() );
      return FALSE;
   }

   // get the IBrokerInitEx2 interface
   // the broker we want to be using implements this interface so
   // generate an error if it doesn't have it
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);
   if ( pBrokerInit == nullptr )
   {
      FailSafeLogMessage(_T("Wrong version of Broker installed\nRe-install"));
      return FALSE;
   }

   // tell the broker to wait on calling the IAgent::Init function until
   // pBrokerInit->InitAgents() is called
   pBrokerInit->DelayInit();

   return TRUE;
}

void CEAFBrokerDocument::BrokerShutDown()
{
   // if we are done with the broker, we must also be done with
   // all of our cached interfaces
   m_pReportManager = nullptr;
   m_pGraphManager = nullptr;

   if ( m_pBroker )
   {
      m_pBroker->ShutDown();
      ULONG cRef = m_pBroker->Release();
      ASSERT( cRef == 0 );
      
      m_pBroker = nullptr;

      m_pDocProxyAgent = nullptr;
   }
}

BOOL CEAFBrokerDocument::LoadAgents()
{
   // get the correct interface from the broker
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);

   // create component category manager
   CComPtr<ICatRegister> pICatReg;
   HRESULT hr;
   hr = ::CoCreateInstance( CLSID_StdComponentCategoriesMgr,
                            nullptr,
                            CLSCTX_INPROC_SERVER,
                            IID_ICatRegister,
                            (void**)&pICatReg );

   // deal with failure
   if ( FAILED(hr) )
   {
      std::_tostringstream msg;
      msg << "Failed to create Component Category Manager. hr = " << hr << std::endl;
      msg << "Is the correct version of Internet Explorer installed?" << std::endl << std::ends;
      FailSafeLogMessage( msg.str().c_str() );
      return FALSE;
   }

   // get the necessary interfaces from the component category manager
   CComQIPtr<ICatInformation> pICatInfo(pICatReg);

   CComPtr<IEnumCLSID> pIEnumCLSID;

   // get the agent category identifier
   const int nID = 1;
   CATID ID[nID];
   ID[0] = GetAgentCategoryID();

   // enum agents
   pICatInfo->EnumClassesOfCategories(nID,ID,0,nullptr,&pIEnumCLSID);

   // load up to 10 agents at a time
   const int nMaxAgents = 10;
   CLSID clsid[nMaxAgents];

   ULONG nAgentsLoaded = 0;
   while (SUCCEEDED(pIEnumCLSID->Next(nMaxAgents,clsid,&nAgentsLoaded)) && 0 < nAgentsLoaded )
   {
      // load the agents
      if ( !LoadAgents(pBrokerInit, clsid, nAgentsLoaded) )
      {
         return FALSE;
      }
   }

   // load the special agents
   if ( !LoadSpecialAgents(pBrokerInit) )
   {
      return FALSE;
   }

   //
   // Load extension agents
   //

   ID[0] = GetExtensionAgentCategoryID();
   if ( ID[0] != CLSID_NULL )
   {
      // enum agents
      pIEnumCLSID.Release();
      pICatInfo->EnumClassesOfCategories(nID,ID,0,nullptr,&pIEnumCLSID);

      CWinApp* pApp = AfxGetApp();

      nAgentsLoaded = 0;
      while (SUCCEEDED(pIEnumCLSID->Next(nMaxAgents,clsid,&nAgentsLoaded)) && 0 < nAgentsLoaded )
      {
         // load the extension agents - do it one at a time so that disabled ones can be skipped
         for (ULONG i = 0; i < nAgentsLoaded; i++ )
         {
            USES_CONVERSION;

            LPOLESTR pszCLSID;
            ::StringFromCLSID(clsid[i],&pszCLSID);

            CString strState = pApp->GetProfileString(_T("Extensions"),OLE2T(pszCLSID),_T("Enabled"));
            if ( strState.CompareNoCase(_T("Enabled")) == 0 )
            {
               CLSID* pCLSID = &clsid[i];
               LoadAgents(pBrokerInit,pCLSID,1,false); // false = not required
            }

            ::CoTaskMemFree((void*)pszCLSID);
         }
      }
   }

   return TRUE;
}

BOOL CEAFBrokerDocument::LoadAgents(IBrokerInitEx2* pBrokerInit, CLSID* pClsid, long nClsid,bool bRequiredAgent)
{
   // this function does the actual work of loading an agent
   CComPtr<IIndexArray> lErrArray;
   HRESULT hr;
   if ( bRequiredAgent )
   {
      hr = pBrokerInit->LoadAgents( pClsid, nClsid, &lErrArray );
   }
   else
   {
      hr = pBrokerInit->LoadExtensionAgents( pClsid, nClsid, &lErrArray );
   }

   if ( FAILED(hr) )
   {
      IndexType nErrors;
      lErrArray->get_Count(&nErrors);
      for ( IndexType errIdx = 0; errIdx < nErrors; errIdx++ )
      {
         IndexType agentIdx;
         lErrArray->get_Item(errIdx,&agentIdx);
         LPOLESTR pszCLSID;
         StringFromCLSID( pClsid[agentIdx], &pszCLSID );
         CString strCLSID(pszCLSID);
         ::CoTaskMemFree( (LPVOID)pszCLSID );

         LPOLESTR pszProgID;
         ProgIDFromCLSID( pClsid[agentIdx], &pszProgID );
         CString strProgID(pszProgID);
         ::CoTaskMemFree( (LPVOID)pszProgID );

         std::_tostringstream msg;
         msg << "Failed to load agent. hr = " << hr << std::endl;
         msg << "CLSID = " << strCLSID.LockBuffer() << std::endl;
         msg << "ProgID = " << strProgID.LockBuffer() << std::endl << std::ends;
         FailSafeLogMessage( msg.str().c_str() );

         if ( !bRequiredAgent )
         {
            // there was an error and this agent isn't required, prompt user
            // to disable it so it doesn't get loaded next time
            USES_CONVERSION;

            LPOLESTR pszUserType;
            OleRegGetUserType(pClsid[agentIdx],USERCLASSTYPE_SHORT,&pszUserType);

            CString strMsg;
            strMsg.Format(_T("Failed to load %s.\n\nWould you like to disable this component?"),OLE2T(pszUserType));
            if ( AfxMessageBox(strMsg,MB_YESNO | MB_ICONQUESTION) == IDYES )
            {
               CEAFApp* pApp = EAFGetApp();
               pApp->WriteProfileString(_T("Extensions"),strCLSID,_T("Disabled"));
            }
         }

         strCLSID.UnlockBuffer();
         strProgID.UnlockBuffer();
      }

      return FALSE;
   }
   return TRUE;
}

BOOL CEAFBrokerDocument::LoadSpecialAgents(IBrokerInitEx2* pBrokerInit)
{
   // Load up the proxy agent -> This guy implements several interfaces
   // required for Agent Plug in integration as well as
   // provides the bridge between the MFC Doc/View architecture
   // and the WBFL Agent/Broker architecture.

   CEAFMainFrame* pMainFrame = EAFGetMainFrame();

   CComObject<CEAFDocProxyAgent>* pDocProxyAgent;
   CComObject<CEAFDocProxyAgent>::CreateInstance(&pDocProxyAgent);
   CComPtr<IAgentEx> pAgent(pDocProxyAgent);

   m_pDocProxyAgent = dynamic_cast<CEAFDocProxyAgent*>(pDocProxyAgent);

   m_pDocProxyAgent->SetDocument( this );
   m_pDocProxyAgent->SetBroker( m_pBroker );
   m_pDocProxyAgent->SetMainFrame(pMainFrame);
   
   HRESULT hr = pBrokerInit->AddAgent( pAgent );

   // Since we use the ILogFile and IProgress interfaces, we required the SysAgent
   int n = 1 + m_bUseReportManager + m_bUseGraphManager;
   std::unique_ptr<CLSID[]> clsid(new CLSID[n]);
   int i = 0;
   clsid[i++] = CLSID_SysAgent;
   if (m_bUseReportManager) clsid[i++] = CLSID_ReportManagerAgent;
   if (m_bUseGraphManager) clsid[i++] = CLSID_GraphManagerAgent;
   if ( !CEAFBrokerDocument::LoadAgents(pBrokerInit, clsid.get(), i) )
   {
      return FALSE;
   }

   return SUCCEEDED(hr);
}

void CEAFBrokerDocument::InitAgents()
{
   // and finally, initialize all the agents
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);
   pBrokerInit->InitAgents();


   // OnCmdMsg uses these interfaces tens of thousands of time. Get them once
   m_pBroker->GetInterface(IID_IReportManager, (IUnknown**)&m_pReportManager);
   m_pBroker->GetInterface(IID_IGraphManager, (IUnknown**)&m_pGraphManager);

   if (m_pReportManager)
   {
      CEAFApp* pApp = EAFGetApp();
      auto strBrowserType = pApp->GetProfileString(_T("Settings"), _T("ReportBrowser"), _T("Edge"));
      WBFL::Reporting::ReportBrowser::Type browserType = (strBrowserType.CompareNoCase(_T("IE")) == 0 ? WBFL::Reporting::ReportBrowser::Type::IE : WBFL::Reporting::ReportBrowser::Type::Edge);
      m_pReportManager->SetReportBrowserType(browserType);
   }
}

void CEAFBrokerDocument::DoIntegrateWithUI(BOOL bIntegrate)
{
   CEAFDocument::DoIntegrateWithUI(bIntegrate);

   CComQIPtr<IBrokerInitEx3> pBrokerInit(m_pBroker);

   if ( bIntegrate )
   {
      pBrokerInit->Integrate(TRUE,m_pReportManager == nullptr ? FALSE : TRUE,m_pGraphManager == nullptr ? FALSE : TRUE,TRUE);
   }
   else
   {
      pBrokerInit->RemoveIntegration();
   }
}

BOOL CEAFBrokerDocument::ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo)
{
   if ( CEAFDocument::ProcessCommandLineOptions(cmdInfo) )
   {
      return TRUE; // handled
   }

   CComQIPtr<IManageAgents> manageAgents(m_pBroker);
   IndexType nAgents;
   manageAgents->get_AgentCount(&nAgents);
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_Agent(agentIdx,&agent);

      CComQIPtr<IEAFProcessCommandLine,&IID_IEAFProcessCommandLine> processCommandLine(agent);
      if ( processCommandLine )
      {
         if ( processCommandLine->ProcessCommandLineOptions(cmdInfo) )
         {
            return TRUE; // handled
         }
      }
   }

   manageAgents->get_ExtensionAgentCount(&nAgents);
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_ExtensionAgent(agentIdx,&agent);

      CComQIPtr<IEAFProcessCommandLine,&IID_IEAFProcessCommandLine> processCommandLine(agent);
      if ( processCommandLine )
      {
         if ( processCommandLine->ProcessCommandLineOptions(cmdInfo) )
         {
            return TRUE; // handled
         }
      }
   }

   return FALSE; // not handled
}

void CEAFBrokerDocument::OnLoadAgentsError()
{
   // over ride this method to provide an error message or log 
   InitFailMessage();
}

HRESULT CEAFBrokerDocument::LoadTheDocument(IStructuredLoad* pStrLoad)
{
   CComQIPtr<IBrokerPersist> pPersist(m_pBroker);
   return pPersist->Load( pStrLoad );
}

HRESULT CEAFBrokerDocument::WriteTheDocument(IStructuredSave* pStrSave)
{
   CComQIPtr<IBrokerPersist> pPersist(m_pBroker);
   return pPersist->Save( pStrSave );
}

CString CEAFBrokerDocument::GetLogFileName()
{
   // Creates the log file on the User's desktop so that it is easy to find
   CString strFileName;
   strFileName.Format(_T("%s.log"),EAFGetApp()->m_pszExeName);

   PWSTR strDesktop;
   ::SHGetKnownFolderPath(FOLDERID_Desktop,0,nullptr,&strDesktop);

   CString strFilePath;
   strFilePath.Format(_T("%s\\%s"),strDesktop,strFileName);

   ::CoTaskMemFree((void*)strDesktop);

   return strFilePath;
}

void CEAFBrokerDocument::OnLogFileOpened()
{
   // Does nothing by default
}

void CEAFBrokerDocument::OnLogFileClosing()
{
   // Does nothing by default
}

BOOL CEAFBrokerDocument::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
   if ( m_pBroker )
   {
      // Interrupt the normal command processing to handle reports and graphs
      // The report and graph menu items are dynamically generated and so are their IDs
      // If the command code is in the range of the report/graphg commands a specific
      // report/graph name was selected from a menu. Send the message on to the OnReport/OnGraph handler
      // and tell MFC that this message has been handled (return TRUE)

      if ( m_pReportManager )
      {
         IndexType nReports = m_pReportManager->GetReportBuilderCount();
         BOOL bIsReport      = (GetReportCommand(0,false) <= nID && nID <= GetReportCommand(nReports-1,false));
         BOOL bIsQuickReport = (GetReportCommand(0,true)  <= nID && nID <= GetReportCommand(nReports-1,true));

         if ( bIsReport || bIsQuickReport )
         {
            if ( nCode == CN_UPDATE_COMMAND_UI )
            {
               CCmdUI* pCmdUI = (CCmdUI*)(pExtra);
               pCmdUI->Enable(TRUE);
               return TRUE;
            }
            else if ( nCode == CN_COMMAND )
            {
               if ( bIsQuickReport )
               {
                  OnQuickReport(nID);
               }
               else
               {
                  OnReport(nID);
               }

               return TRUE;
            }
         }
      }

      // Don't use GET_IFACE because the ASSERTs will fire if the interface is missing (which is valid in this case)
      if ( m_pGraphManager )
      {
         IndexType nGraphs = m_pGraphManager->GetGraphBuilderCount();
         BOOL bIsGraph = (GetGraphCommand(0) <= nID && nID <= GetGraphCommand(nGraphs-1));
         if ( bIsGraph )
         {
            if ( nCode == CN_UPDATE_COMMAND_UI )
            {
               CCmdUI* pCmdUI = (CCmdUI*)(pExtra);
               pCmdUI->Enable(TRUE);
               return TRUE;
            }
            else if ( nCode == CN_COMMAND )
            {
               OnGraph(nID);
               return TRUE;
            }
         }
      }
   }
	
	return CEAFDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CEAFBrokerDocument::PopulateReportMenu(CEAFMenu* pReportMenu)
{
   // remove any old reports and placeholders
   UINT nItems = pReportMenu->GetMenuItemCount();
   for ( UINT idx = 0; idx < nItems; idx++ )
   {
      pReportMenu->RemoveMenu(0,MF_BYPOSITION,nullptr);
   }

   if ( m_bFavoriteReports )
   {
      // Add favorites option at top
      CString msg = m_bDisplayFavoriteReports==FALSE ? _T("Show only favorites") : _T("Show all reports");
      pReportMenu->AppendMenu(EAFID_REPORT_MENU_DISPLAY_MODE,msg,nullptr);
      pReportMenu->AppendSeparator();
   }

   BuildReportMenu(pReportMenu,false);
}

void CEAFBrokerDocument::BuildReportMenu(CEAFMenu* pMenu,BOOL bQuickReport)
{
   GET_IFACE(IReportManager,pReportMgr);
   std::vector<std::_tstring> rptNames = pReportMgr->GetReportNames();

   // if this assert fires, there are more reports than can be put into the menus
   // EAF only reserves enough room for EAF_REPORT_MENU_COUNT reports
   ATLASSERT(rptNames.size() < EAF_REPORT_MENU_BASE+EAF_REPORT_MENU_COUNT);

   UINT i = 0;
   bool didlist = false;
   std::vector<std::_tstring>::iterator iter(rptNames.begin());
   std::vector<std::_tstring>::iterator end(rptNames.end());
   for ( ; iter != end; iter++ )
   {
      std::_tstring rptName = *iter;

      // list all or favorites
      bool dolist = false;
      if ( m_bDisplayFavoriteReports == FALSE || IsFavoriteReport(rptName) )
      {
         dolist = true;
      }

      if (dolist)
      {
         UINT nCmd = GetReportCommand(i,bQuickReport);
         pMenu->AppendMenu(nCmd,rptName.c_str(),nullptr);

         const CBitmap* pBmp = pReportMgr->GetMenuBitmap(rptName);
         pMenu->SetMenuItemBitmaps(nCmd,MF_BYCOMMAND,pBmp,nullptr,nullptr);

         didlist = true;
      }

      i++;
      ASSERT(i <= EAF_REPORT_MENU_COUNT);
   }

   // Deal with case where there are no favorites
   if ( m_bFavoriteReports && !didlist )
   {
      pMenu->AppendMenu(EAFID_OPTIONS_REPORTING,_T("No favorite reports exist. You can add some by clicking here."),nullptr);
   }
}

UINT CEAFBrokerDocument::GetReportCommand(IndexType rptIdx,BOOL bQuickReport) const
{
   IndexType baseID = EAF_REPORT_MENU_BASE;

   if ( !bQuickReport )
   {
      GET_IFACE(IReportManager,pReportMgr);
      IndexType nReports = pReportMgr->GetReportBuilderCount();

      baseID += nReports + 1;
   }

   ASSERT(rptIdx + baseID <= EAF_REPORT_MENU_BASE+2*EAF_REPORT_MENU_COUNT);
   return (UINT)(rptIdx + baseID);
}

IndexType CEAFBrokerDocument::GetReportIndex(UINT nID,BOOL bQuickReport) const
{
   if ( nID < EAF_REPORT_MENU_BASE || EAF_REPORT_MENU_BASE+2*EAF_REPORT_MENU_COUNT < nID )
   {
      return INVALID_INDEX;
   }

   IndexType baseID = EAF_REPORT_MENU_BASE;
   if ( !bQuickReport )
   {
      GET_IFACE(IReportManager,pReportMgr);
      IndexType nReports = pReportMgr->GetReportBuilderCount();

      baseID += nReports + 1;
   }

   return (IndexType)(nID - baseID);
}

void CEAFBrokerDocument::OnReport(UINT nID)
{
   // User picked a report from a menu.
   // get the report index
   IndexType rptIdx = GetReportIndex(nID,FALSE);
   CreateReportView(rptIdx,TRUE);
}

void CEAFBrokerDocument::OnQuickReport(UINT nID)
{
   // User picked a report from a menu.
   // This is a "quick report" so don't prompt
   IndexType rptIdx = GetReportIndex(nID,TRUE);
   CreateReportView(rptIdx,FALSE);
}

void CEAFBrokerDocument::CreateReportView(IndexType rptIdx,BOOL bPrompt)
{
   // User must override this method to display the report
   AfxMessageBox(_T("Override CEAFBrokerDocument::CreateReportView to create the specific report view you want"));
}

void CEAFBrokerDocument::PopulateGraphMenu(CEAFMenu* pGraphMenu)
{
   if (m_bIsGraphMenuPopulated)
   {
      return;
   }

   // remove any old graphs and placeholders
   UINT nItems = pGraphMenu->GetMenuItemCount();
   for ( UINT idx = 0; idx < nItems; idx++ )
   {
      pGraphMenu->RemoveMenu(0,MF_BYPOSITION,nullptr);
   }

   BuildGraphMenu(pGraphMenu);

   m_bIsGraphMenuPopulated = true;
}

void CEAFBrokerDocument::BuildGraphMenu(CEAFMenu* pMenu)
{
   GET_IFACE(IGraphManager,pGraphMgr);
   std::vector<std::_tstring> graphNames = pGraphMgr->GetGraphNames();

   // if this assert fires, there are more graphs than can be put into the menus
   // EAF only reserves enough room for EAF_GRAPH_MENU_COUNT graphs
   ATLASSERT(graphNames.size() < EAF_GRAPH_MENU_COUNT);

   UINT i = 0;
   std::vector<std::_tstring>::iterator iter(graphNames.begin());
   std::vector<std::_tstring>::iterator end(graphNames.end());
   for ( ; iter != end && i < EAF_GRAPH_MENU_COUNT; iter++ )
   {
      std::_tstring graphName = *iter;
      UINT nCmd = GetGraphCommand(i);
      pMenu->AppendMenu(nCmd,graphName.c_str(),nullptr);

      const CBitmap* pBmp = pGraphMgr->GetMenuBitmap(graphName);
      pMenu->SetMenuItemBitmaps(nCmd,MF_BYCOMMAND,pBmp,nullptr,nullptr);

      i++;

      ASSERT(i <= EAF_GRAPH_MENU_COUNT);
   }
}

UINT CEAFBrokerDocument::GetGraphCommand(IndexType graphIdx) const
{
   IndexType baseID = EAF_GRAPH_MENU_BASE;
   ASSERT(graphIdx + baseID <= EAF_GRAPH_MENU_BASE+EAF_GRAPH_MENU_COUNT);
   return (UINT)(graphIdx + baseID);
}

IndexType CEAFBrokerDocument::GetGraphIndex(UINT nID) const
{
   if ( nID < EAF_GRAPH_MENU_BASE || EAF_GRAPH_MENU_BASE+EAF_GRAPH_MENU_COUNT < nID )
   {
      return INVALID_INDEX;
   }

   IndexType baseID = EAF_GRAPH_MENU_BASE;
   return (IndexType)(nID - baseID);
}

void CEAFBrokerDocument::OnGraph(UINT nID)
{
   // User picked a graph from a menu.
   // get the graph index and create the graph view
   IndexType graphIdx = GetGraphIndex(nID);
   CreateGraphView(graphIdx);
}

void CEAFBrokerDocument::CreateGraphView(IndexType graphIdx)
{ 
   // does nothing by default
   AfxMessageBox(_T("Override CEAFBrokerDocument::CreateGraphView to create the specific graph view you want"));
}

void CEAFBrokerDocument::OnUpdateAllViews(CView* pSender, LPARAM lHint,CObject* pHint)
{
   GET_IFACE(IProgress,pProgress);
   CEAFAutoProgress progress(pProgress);
   pProgress->UpdateMessage(_T("Updating views"));
   CEAFDocument::OnUpdateAllViews(pSender,lHint,pHint);
}

BOOL CEAFBrokerDocument::DisplayFavoriteReports() const
{
   return m_bDisplayFavoriteReports;
}

void CEAFBrokerDocument::DisplayFavoriteReports(BOOL doDisplay)
{
   BOOL bDoDisplay = doDisplay;
   if ( m_bDisplayFavoriteReports != bDoDisplay )
   {
      m_bDisplayFavoriteReports = bDoDisplay;
      UpdateAllViews(nullptr,EAF_HINT_FAVORITE_REPORTS_CHANGED,nullptr);
   }
}

const std::vector<std::_tstring>& CEAFBrokerDocument::GetFavoriteReports() const
{
   return m_FavoriteReports;
}

void CEAFBrokerDocument::SetFavoriteReports(const std::vector<std::_tstring>& reports)
{
   m_FavoriteReports = reports;
}

BOOL CEAFBrokerDocument::IsFavoriteReport(const std::_tstring& rptName)
{
   return (m_FavoriteReports.end() != std::find(m_FavoriteReports.begin(), m_FavoriteReports.end(), rptName));
}

const CEAFCustomReports& CEAFBrokerDocument::GetCustomReports() const
{
   return m_CustomReports;
}

void CEAFBrokerDocument::SetCustomReports(const CEAFCustomReports& reports)
{
   m_CustomReports = reports;
}

void CEAFBrokerDocument::LoadDocumentationMap()
{
   CEAFDocument::LoadDocumentationMap();

   CComQIPtr<IManageAgents> manageAgents(m_pBroker);

   IndexType nAgents;
   manageAgents->get_AgentCount(&nAgents);
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_Agent(agentIdx,&agent);

      CComQIPtr<IAgentDocumentationIntegration,&IID_IAgentDocumentationIntegration> pDocIntegration(agent);
      if ( pDocIntegration )
      {
         HRESULT hr = pDocIntegration->LoadDocumentationMap();
         ATLASSERT(SUCCEEDED(hr));
      }
   }

   manageAgents->get_ExtensionAgentCount(&nAgents);
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_ExtensionAgent(agentIdx,&agent);

      CComQIPtr<IAgentDocumentationIntegration,&IID_IAgentDocumentationIntegration> pDocIntegration(agent);
      if ( pDocIntegration )
      {
         HRESULT hr = pDocIntegration->LoadDocumentationMap();
         ATLASSERT(SUCCEEDED(hr));
      }
   }
}

eafTypes::HelpResult CEAFBrokerDocument::GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL)
{
   // let the base class do its thing first
   eafTypes::HelpResult helpResult = CEAFDocument::GetDocumentLocation(lpszDocSetName,nHID,strURL);
   if ( helpResult == eafTypes::hrOK || helpResult== eafTypes::hrTopicNotFound )
   {
      // if we have a good help document location or if the doc set was found but the HID was bad,
      // we are done... return the result
      return helpResult;
   }

   // Search through the agents and extension agents for anyone implementing the IAgentDocumentationIntegration interface

   USES_CONVERSION;
   CComQIPtr<IManageAgents> manageAgents(m_pBroker);

   CComBSTR bstrDocSetName(lpszDocSetName);

   IndexType nAgents;
   manageAgents->get_AgentCount(&nAgents);
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_Agent(agentIdx,&agent);

      CComQIPtr<IAgentDocumentationIntegration,&IID_IAgentDocumentationIntegration> pDocIntegration(agent);
      if ( pDocIntegration )
      {
         CComBSTR bstrMyDocSetName;
         pDocIntegration->GetDocumentationSetName(&bstrMyDocSetName);
         if ( bstrMyDocSetName == bstrDocSetName )
         {
            // matched the target document set...

            CComBSTR bstrURL;
            HRESULT hr = pDocIntegration->GetDocumentLocation(nHID,&bstrURL);
            if ( SUCCEEDED(hr) )
            {
               // found the help topic
               strURL = OLE2T(bstrURL);
               return eafTypes::hrOK;
            }
            else
            {
               // did not find the help topic
               return eafTypes::hrTopicNotFound;
            }
         }
      }
   }

   manageAgents->get_ExtensionAgentCount(&nAgents);
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_ExtensionAgent(agentIdx,&agent);

      CComQIPtr<IAgentDocumentationIntegration,&IID_IAgentDocumentationIntegration> pDocIntegration(agent);
      if ( pDocIntegration )
      {
         CComBSTR bstrMyDocSetName;
         pDocIntegration->GetDocumentationSetName(&bstrMyDocSetName);
         if ( bstrMyDocSetName == bstrDocSetName )
         {
            // matched the target document set...

            CComBSTR bstrURL;
            HRESULT hr = pDocIntegration->GetDocumentLocation(nHID,&bstrURL);
            if ( SUCCEEDED(hr) )
            {
               // found the help topic
               strURL = OLE2T(bstrURL);
               return eafTypes::hrOK;
            }
            else
            {
               // did not find the help topic
               return eafTypes::hrTopicNotFound;
            }
         }
      }
   }

   return eafTypes::hrDocSetNotFound;
}

BOOL CEAFBrokerDocument::IsReportCommand(UINT nID,BOOL bQuickReport)
{
   if ( m_pReportManager )
   {
      IndexType nReports = m_pReportManager->GetReportBuilderCount();
      BOOL bIsReport      = (GetReportCommand(0,false) <= nID && nID <= GetReportCommand(nReports-1,false));
      BOOL bIsQuickReport = (GetReportCommand(0,true)  <= nID && nID <= GetReportCommand(nReports-1,true));
      if ( bQuickReport )
      {
         return bIsQuickReport;
      }
      else
      {
         return bIsReport;
      }
   }
   else
   {
      return FALSE;
   }
}

BOOL CEAFBrokerDocument::IsGraphCommand(UINT nID)
{
   if ( m_pGraphManager )
   {
      IndexType nGraphs = m_pGraphManager->GetGraphBuilderCount();
      BOOL bIsGraph = (GetGraphCommand(0) <= nID && nID <= GetGraphCommand(nGraphs-1));
      return bIsGraph;
   }
   else
   {
      return FALSE;
   }
}

BOOL CEAFBrokerDocument::GetStatusBarMessageString(UINT nID,CString& rMessage) const
{
   BOOL bHandled = FALSE;
   if ( m_pReportManager )
   {
      IndexType nReports = m_pReportManager->GetReportBuilderCount();
      if ( (GetReportCommand(0,FALSE) <= nID && nID <= GetReportCommand(nReports-1,FALSE)) ||
           (GetReportCommand(0,TRUE)  <= nID && nID <= GetReportCommand(nReports-1,TRUE)) )
      {
         rMessage.Format(_T("Creates a report"));
         bHandled = TRUE;
      }
   }

   if ( m_pGraphManager )
   {
      IndexType nGraphs = m_pGraphManager->GetGraphBuilderCount();
      if ( GetGraphCommand(0) <= nID && nID <= GetGraphCommand(nGraphs-1) )
      {
         rMessage.Format(_T("Creates a graph"));
         bHandled = TRUE;
      }
   }

   if ( !bHandled )
   {
      bHandled = __super::GetStatusBarMessageString(nID,rMessage);
   }

   return bHandled;
}

BOOL CEAFBrokerDocument::GetToolTipMessageString(UINT nID, CString& rMessage) const
{
   BOOL bHandled = FALSE;
   if ( m_pReportManager )
   {
      IndexType nReports = m_pReportManager->GetReportBuilderCount();
      if ( (GetReportCommand(0,FALSE) <= nID && nID <= GetReportCommand(nReports-1,FALSE)) ||
           (GetReportCommand(0,TRUE)  <= nID && nID <= GetReportCommand(nReports-1,TRUE)) )
      {
         rMessage.Format(_T("Creates a report"));
         bHandled = TRUE;
      }
   }

   if ( m_pGraphManager )
   {
      IndexType nGraphs = m_pGraphManager->GetGraphBuilderCount();
      if ( GetGraphCommand(0) <= nID && nID <= GetGraphCommand(nGraphs-1) )
      {
         rMessage.Format(_T("Creates a graph"));
         bHandled = TRUE;
      }
   }

   if ( !bHandled )
   {
      bHandled = __super::GetToolTipMessageString(nID,rMessage);
   }

   return bHandled;
}

void CEAFBrokerDocument::OnReportMenuDisplayMode()
{
   // flip value
   DisplayFavoriteReports(!m_bDisplayFavoriteReports);
   OnChangedFavoriteReports(m_bDisplayFavoriteReports!=FALSE, TRUE);
}

void CEAFBrokerDocument::OnUpdateReportMenuDisplayMode(CCmdUI* pCmdUI)
{
   pCmdUI->SetText( (m_bDisplayFavoriteReports ? _T("Show all reports") : _T("Show only favorites") ) );
}

void CEAFBrokerDocument::OnConfigureReports()
{
   GET_IFACE(IReportManager,pReportMgr);
   std::vector<std::_tstring> rptNames = pReportMgr->GetReportNames();

   CConfigureReportsDlg dlg(m_bFavoriteReports);

   dlg.m_pBroker = m_pBroker;
   dlg.SetFavorites(m_FavoriteReports);
   dlg.m_FavoriteReportsPage.m_bShowFavoritesInMenus = m_bDisplayFavoriteReports;
   dlg.m_CustomReports = m_CustomReports;

   if (dlg.DoModal() == IDOK)
   {
      m_FavoriteReports = dlg.GetFavorites();
      m_bDisplayFavoriteReports = dlg.m_FavoriteReportsPage.m_bShowFavoritesInMenus;
      m_CustomReports = dlg.m_CustomReports;

      IntegrateCustomReports(FALSE);
      OnChangedFavoriteReports(m_bDisplayFavoriteReports!=FALSE, FALSE);
   }
}

void CEAFBrokerDocument::FavoriteReports(BOOL bEnable)
{
   m_bFavoriteReports = bEnable;
}

BOOL CEAFBrokerDocument::FavoriteReports() const
{
   return m_bFavoriteReports;
}

void CEAFBrokerDocument::SetCustomReportHelpID(eafTypes::CustomReportHelp helpType,UINT nHelpID)
{
   if ( helpType == eafTypes::crhCustomReport )
   {
      m_helpIDCustom = nHelpID;
   }
   else
   {
      m_helpIDFavorite = nHelpID;
   }
}

UINT CEAFBrokerDocument::GetCustomReportHelpID(eafTypes::CustomReportHelp helpType) const
{
   if ( helpType == eafTypes::crhCustomReport )
   {
      return m_helpIDCustom;
   }
   else
   {
      return m_helpIDFavorite;
   }
}

void CEAFBrokerDocument::SetCustomReportDefinitionHelpID(UINT nHelpID)
{
   m_helpIDCustomReportDefinition = nHelpID;
}

UINT CEAFBrokerDocument::GetCustomReportDefinitionHelpID() const
{
   return m_helpIDCustomReportDefinition;
}

void CEAFBrokerDocument::OnChangedFavoriteReports(BOOL bIsFavorites, BOOL bFromMenu)
{
   if (bFromMenu)
   {
      Uint32 mask = EAF_UIHINT_FAVORITES_MENU;
      Uint32 hintSettings = GetUIHintSettings();
      if ( WBFL::System::Flags<Uint32>::IsClear(hintSettings,mask) )
      {
         CString strText(_T("This menu item allows you to display only your favorite reports in the Reports menus, or display all available reports. The change will occur the next time you open a Report menu."));
         if ( EAFShowUIHints(strText) )
         {
            WBFL::System::Flags<Uint32>::Set(&hintSettings,mask);
            SetUIHintSettings(hintSettings);
         }
      }
   }
}

void CEAFBrokerDocument::OnCustomReportError(eafTypes::CustomReportError error, LPCTSTR lpszReportName, LPCTSTR lpszOtherName)
{
   CString strError;

   switch(error)
   {
   case eafTypes::creParentMissingAtLoad:
         strError.Format(_T("For custom report \"%s\": the parent report %s could not be found at program load time. The custom report was deleted."),lpszReportName,lpszOtherName);
         break;
      case eafTypes::creParentMissingAtImport:
         strError.Format(_T("For custom report \"%s\": the parent report %s could not be found. The report may have depended on an application extension. The custom report was deleted."), lpszReportName, lpszOtherName);
         break;
      case eafTypes::creChapterMissingAtLoad:
      case eafTypes::creChapterMissingAtImport:
         strError.Format(_T("For custom report \"%s\": the following chapter %s does not exist in the parent report. The chapter was removed. Perhaps the chapter name changed? You may want to edit the report."), lpszReportName, lpszOtherName);
         break;
      default:
         ATLASSERT(false);
   };

   GET_IFACE(IEAFStatusCenter,pStatusCenter);
   CEAFStatusItem* pStatusItem = new CEAFDefaultStatusItem(m_StatusGroupID,m_scidCustomReportWarning,strError);
   pStatusCenter->Add(pStatusItem);
}

void CEAFBrokerDocument::ShowCustomReportHelp(eafTypes::CustomReportHelp helpType)
{
   // Base class must call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before calling this method
   UINT helpID = helpType==eafTypes::crhCustomReport ? m_helpIDCustom : m_helpIDFavorite;
   if ( 0 < helpID )
   {
      EAFHelp(GetDocumentationSetName(),helpID);
   }
}

void CEAFBrokerDocument::ShowCustomReportDefinitionHelp()
{
   // Base class must call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before calling this method
   if ( 0 < m_helpIDCustomReportDefinition )
   {
      EAFHelp(GetDocumentationSetName(),m_helpIDCustomReportDefinition);
   }
}

void CEAFBrokerDocument::IntegrateCustomReports(bool bFirst)
{
   CComPtr<IReportManager> pReportMgr;
   HRESULT hr = m_pBroker->GetInterface(IID_IReportManager,(IUnknown**)&pReportMgr);
   if ( FAILED(hr) )
   {
      // reporting isn't supported
      return;
   }

   if (bFirst)
   {
      // First time through. Store names of built-in reports
      m_BuiltInReportNames = pReportMgr->GetReportNames();
   }
   else
   {
      // Subsequent times through we need to remove custom reports before reloading them
      std::vector<std::_tstring> strNames = pReportMgr->GetReportNames();
      std::vector<std::_tstring>::const_iterator itn = strNames.begin();
      while(itn != strNames.end())
      {
         const std::_tstring& rName = *itn;
         std::vector<std::_tstring>::const_iterator itfnd = std::find(m_BuiltInReportNames.begin(), m_BuiltInReportNames.end(), rName);
         if (itfnd == m_BuiltInReportNames.end())
         {
            // Remove report if it's not built in. ptr release should delete it.
            std::shared_ptr<WBFL::Reporting::ReportBuilder> ptr = pReportMgr->RemoveReportBuilder(rName.c_str());
         }

         itn++;
      }
   }

   // Add custom reports
   CEAFCustomReports::ReportIterator itcr = m_CustomReports.m_Reports.begin();
   while(itcr != m_CustomReports.m_Reports.end())
   {
      CEAFCustomReport& rCustom = const_cast<CEAFCustomReport&>(*itcr); // do not change the name of the report, it will mess up the sort order of the container

      // First check that custom report does not have same name as a built-in. This always be blocked by the UI
      std::vector<std::_tstring>::const_iterator itfnd = std::find(m_BuiltInReportNames.begin(), m_BuiltInReportNames.end(), rCustom.m_ReportName);
      if ( itfnd == m_BuiltInReportNames.end() )
      {
         // get parent report
         std::shared_ptr<WBFL::Reporting::ReportBuilder> pParentBuilder = pReportMgr->GetReportBuilder(rCustom.m_ParentReportName);
         if (pParentBuilder)
         {
            // found parent. Now we can create new builder for custom
            std::shared_ptr<WBFL::Reporting::ReportBuilder> newBuilder( std::make_shared<WBFL::Reporting::ReportBuilder>(rCustom.m_ReportName.c_str()));
            newBuilder->SetReportSpecificationBuilder( pParentBuilder->GetReportSpecificationBuilder() );

            // Title page
            std::shared_ptr<WBFL::Reporting::TitlePageBuilder> ptp = pParentBuilder->GetTitlePageBuilder();
            if (ptp)
            {
               std::shared_ptr<WBFL::Reporting::TitlePageBuilder> pntp( ptp->Clone() );
               pntp->SetReportTitle( rCustom.m_ReportName.c_str() );
               newBuilder->AddTitlePageBuilder(pntp);
            }

            // Use custom menu bitmap
            newBuilder->SetMenuBitmap(&m_bmpCustomReports);

            // Add chapter builders
            bool didAddChapter(false);
            std::vector<std::_tstring>::iterator itChapName = rCustom.m_Chapters.begin();
            while(itChapName != rCustom.m_Chapters.end())
            {
               std::shared_ptr<WBFL::Reporting::ChapterBuilder> pChapterB( pParentBuilder->GetChapterBuilder( itChapName->c_str() ) );
               if ( pChapterB )
               {
                  newBuilder->AddChapterBuilder( pChapterB );
                  didAddChapter = true;
                  itChapName++;
               }
               else
               {
                  // Chapter referenced from custom does not exist in parent report. 
                  OnCustomReportError(bFirst?eafTypes::creChapterMissingAtLoad:eafTypes::creChapterMissingAtImport,rCustom.m_ReportName.c_str(),(*itChapName).c_str());
                  itChapName = rCustom.m_Chapters.erase(itChapName);
                  ATLASSERT(false);
               }
            }

            // 
            if(didAddChapter)
            {
               pReportMgr->AddReportBuilder(newBuilder);
               itcr++;
            }
            else
            {
               ATLASSERT(false); // should never have empty reports
               itcr = m_CustomReports.m_Reports.erase(itcr);
            }
         }
         else
         {
            // parent report does not exist for custom report. remove report and post
            OnCustomReportError(bFirst?eafTypes::creParentMissingAtLoad:eafTypes::creParentMissingAtImport,rCustom.m_ReportName.c_str(),rCustom.m_ParentReportName.c_str());
            itcr = m_CustomReports.m_Reports.erase(itcr);
            ATLASSERT(false);
         }
      }
      else
      {
         // Custom report has same name as a built-in. This would be a very rare case where a built-in
         // was added later that matches a custom. Or, there is a bug in the UI checking. Let it go by silently
         ATLASSERT(false);
         itcr = m_CustomReports.m_Reports.erase(itcr);
      }
   }
}