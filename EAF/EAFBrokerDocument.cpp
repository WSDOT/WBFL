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

// EAFBrokerDocument.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFBrokerDocument.h>
#include <EAF\Help.h>
#include <EAF\EAFHints.h>
#include <EAF\AutoProgress.h>
#include "EAFDocProxyAgent.h"
#include <AgentTools.h>
#include <../Core/CLSID.h>

#include "GraphManagerAgent.h"
#include "ReportManagerAgent.h"

#include "ConfigureReportsDlg.h"

#include <sstream> // for ostringstream


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
   auto pluginApp = pTemplate->GetPluginApp();
   CEAFCustomReportMixin* pCustomReportMixin = dynamic_cast<CEAFCustomReportMixin*>(pluginApp.get());
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
   m_scidCustomReportWarning = pStatusCenter->RegisterCallback(std::make_shared<WBFL::EAF::StatusItemCallback>(WBFL::EAF::StatusSeverityType::Warning)); 
   m_StatusGroupID = pStatusCenter->CreateStatusGroupID();


   // Transfer report favorites and custom reports data from CXBeamRateAppPlugin to CEAFBrokerDocument (this)
   CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)GetDocTemplate();
   auto pluginApp = pTemplate->GetPluginApp();
   CEAFCustomReportMixin* pCustomReportMixin = dynamic_cast<CEAFCustomReportMixin*>(pluginApp.get());
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
std::shared_ptr<WBFL::EAF::Broker> CEAFBrokerDocument::GetBroker()
{
   return m_pBroker;
}

CATID CEAFBrokerDocument::GetExtensionAgentCategoryID()
{
   return CLSID_NULL;
}

BOOL CEAFBrokerDocument::Init()
{
   // Hard code the system agent component information here instead of having a manifest
   // that implementers need to remember to load. This is not idea, but it works. The root
   // cause problem is the Progress Window doesn't work in this DLL so it didn't get moved
   // from the WBFLCore.DLL (we wanted to eliminate WBFLCore.DLL all together when removing
   // COM Component Categories, but it didn't work).
   WBFL::EAF::ComponentInfo info;
   info.clsid = CLSID_SysAgent;
   info.dll = _T("WBFLCore.dll");
   info.name = _T("System Agent");
   WBFL::EAF::ComponentManager::GetInstance().RegisterComponent(info);

   if ( !CreateBroker() )
   {
      InitFailMessage();
      return FALSE;
   }

   if ( !LoadAgents())
   {
      OnLoadAgentsError();
      return FALSE;
   }

   InitAgents();

   if (!CEAFDocument::Init())
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CEAFBrokerDocument::CreateBroker()
{
   m_pBrokerChecker = std::make_shared<WBFL::EAF::BrokerChecker>();
   m_pBroker = std::make_shared<WBFL::EAF::Broker>(m_pBrokerChecker);

   return TRUE;
}

void CEAFBrokerDocument::BrokerShutDown()
{
   m_pDocProxyAgent = nullptr; // get ride of the doc proxy agent so it doesn't have a scope beyond that of the broker

   if (m_pBroker)
   {
      m_pBroker->ShutDown();
      m_pBroker = nullptr;

      // This assert fires when the broker or some of the agents have not been destroyed.
      // They should all be destroyed at this point. If they have not been destroyed,
      // something has a circular reference keeping the broker or agents alive.
      ASSERT(m_pBrokerChecker->CheckFinal() == true);
   }
}

void CEAFBrokerDocument::LogAgentError(const WBFL::EAF::AgentError& error)
{
   std::_tostringstream os;
   os << _T("Failed to load agent: ") << error.component.name << _T(" - ") << error.reason << std::endl;
   os << _T("CLSID: ") << EAFStringFromCLSID(error.component.clsid);
   os << _T("DLL: ") << error.component.dll;
   WBFL::System::Logger::Error(os.str());
}

BOOL CEAFBrokerDocument::LoadAgents()
{
   auto result = m_pBroker->LoadAgents(GetAgentCategoryID());
   if (result.first == false) // primary agents are required so if there is a failure, exit with FALSE
   {
      for (auto& agent_error : result.second)
      {
         LogAgentError(agent_error);
      }
      return FALSE;
   }

   result = LoadSpecialAgents();
   if (result.first == false)
   {
      for (auto& agent_error : result.second)
      {
         LogAgentError(agent_error);
      }
      return FALSE;
   }

   result = m_pBroker->LoadExtensionAgents(GetExtensionAgentCategoryID());
   if (result.first == false)
   {
      // there was an error loading one or more optional agents
      // prompt the user if they want to disable the extension agent
      // so it doesn't load next time
      for (auto& agent_error : result.second)
      {
         LogAgentError(agent_error);

         CString strMsg;
         strMsg.Format(_T("Failed to load %s.\n\nWould you like to disable this component?"), agent_error.component.name.c_str());
         if (AfxMessageBox(strMsg, MB_YESNO | MB_ICONQUESTION) == IDYES)
         {
            CString strCLSID(EAFStringFromCLSID(agent_error.component.clsid).c_str());
            CEAFApp* pApp = EAFGetApp();
            pApp->WriteProfileString(_T("Extensions"), strCLSID, _T("Disabled"));
         }
      }
      // Extension agents are optional so don't return FALSE here
      //return FALSE;
   }

   return TRUE;
}

std::pair<bool, WBFL::EAF::AgentErrors> CEAFBrokerDocument::LoadSpecialAgents()
{
   // Load up the proxy agent -> This guy implements several interfaces
   // required for Agent Plug-in integration as well as
   // provides the bridge between the MFC Doc/View architecture
   // and the WBFL Agent/Broker architecture.

   CEAFMainFrame* pMainFrame = EAFGetMainFrame();

   WBFL::EAF::AgentErrors errors;

   m_pDocProxyAgent = std::make_shared<CEAFDocProxyAgent>(this, pMainFrame);
   auto result = m_pBroker->AddAgent(m_pDocProxyAgent);
   if (result.first == false)
   {
      AFX_MANAGE_STATE(AfxGetStaticModuleState());
      result.second.component.dll = AfxGetApp()->m_pszExeName;
      result.second.reason += _T(" - could not add EAFDocProxyAgent to broker");
      errors.push_back(result.second);
   }

   result = m_pBroker->LoadAgent(CLSID_SysAgent);
   if (result.first == false)
   {
      AFX_MANAGE_STATE(AfxGetStaticModuleState());
      result.second.component.dll = AfxGetApp()->m_pszExeName;
      result.second.reason += _T(" - could not add System Agent to broker");
      errors.push_back(result.second);
   }

   // if the document is using the graph manager, add it
   if (m_bUseGraphManager)
   {
      auto graph_manager_agent = std::make_shared<WBFL::EAF::GraphManagerAgent>();
      auto result = m_pBroker->AddAgent(graph_manager_agent);
      if(result.first == false)
      {
         AFX_MANAGE_STATE(AfxGetStaticModuleState());
         result.second.component.dll = AfxGetApp()->m_pszExeName;
         result.second.reason += _T(" - could not add GraphManagerAgent to broker");
         errors.push_back(result.second);
      }
   }

   // if the document is using the report manager, add it
   if (m_bUseReportManager)
   {
      auto report_manager_agent = std::make_shared<WBFL::EAF::ReportManagerAgent>();
      auto result = m_pBroker->AddAgent(report_manager_agent);
      if (result.first == false)
      {
         AFX_MANAGE_STATE(AfxGetStaticModuleState());
         result.second.component.dll = AfxGetApp()->m_pszExeName;
         result.second.reason += _T(" - could not add ReportManagerAgent to broker");
         errors.push_back(result.second);
      }
   }

   return { errors.empty(), errors };
}

void CEAFBrokerDocument::InitAgents()
{
   // and finally, initialize all the agents
   m_pBroker->InitAgents();

   if (m_bUseReportManager)
   {
      GET_IFACE(IEAFReportManager, reportManager);
      CEAFApp* pApp = EAFGetApp();
      auto strBrowserType = pApp->GetProfileString(_T("Settings"), _T("ReportBrowser"), _T("Edge"));
      WBFL::Reporting::ReportBrowser::Type browserType = (strBrowserType.CompareNoCase(_T("IE")) == 0 ? WBFL::Reporting::ReportBrowser::Type::IE : WBFL::Reporting::ReportBrowser::Type::Edge);
      reportManager->SetReportBrowserType(browserType);
   }

   // Checks to confirm all agents are initialized
   ASSERT(m_pBrokerChecker->CheckInitial() == true);
}

void CEAFBrokerDocument::DoIntegrateWithUI(BOOL bIntegrate)
{
   CEAFDocument::DoIntegrateWithUI(bIntegrate);

   if ( bIntegrate )
   {
      m_pBroker->Integrate(true, m_bUseReportManager, m_bUseGraphManager, true);
   }
   else
   {
      m_pBroker->RemoveIntegration();
   }
}

BOOL CEAFBrokerDocument::ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo)
{
   if ( CEAFDocument::ProcessCommandLineOptions(cmdInfo) )
   {
      return TRUE; // handled
   }

   auto nAgents = m_pBroker->GetAgentCount();
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      auto agent = m_pBroker->GetAgent(agentIdx);

      auto processCommandLine = std::dynamic_pointer_cast<IEAFProcessCommandLine>(agent);
      if ( processCommandLine )
      {
         if ( processCommandLine->ProcessCommandLineOptions(cmdInfo) )
         {
            return TRUE; // handled
         }
      }
   }

   nAgents = m_pBroker->GetExtensionAgentCount();
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      auto agent = m_pBroker->GetExtensionAgent(agentIdx);

      auto processCommandLine = std::dynamic_pointer_cast<IEAFProcessCommandLine>(agent);
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
   auto result = m_pBroker->Load(pStrLoad);
   HRESULT hr = S_OK;
   switch (result)
   {
   case WBFL::EAF::Broker::LoadResult::Error:
      hr = E_FAIL;
      break;

   case WBFL::EAF::Broker::LoadResult::Success:
      hr = S_OK;
      break;

   case WBFL::EAF::Broker::LoadResult::Modified:
      hr = S_FALSE;
      break;

   default:
      ASSERT(false); // is there a new result type?
   }

   return hr;
}

HRESULT CEAFBrokerDocument::WriteTheDocument(IStructuredSave* pStrSave)
{
   return m_pBroker->Save(pStrSave) ? S_OK : E_FAIL;
}

BOOL CEAFBrokerDocument::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
   if ( m_pBroker && m_pBroker->IsInitialized() )
   {
      // Interrupt the normal command processing to handle reports and graphs
      // The report and graph menu items are dynamically generated and so are their IDs
      // If the command code is in the range of the report/graphing commands a specific
      // report/graph name was selected from a menu. Send the message on to the OnReport/OnGraph handler
      // and tell MFC that this message has been handled (return TRUE)

      if ( m_bUseGraphManager )
      {
         GET_IFACE(IEAFGraphManager, graphManager);
         IndexType nGraphs = graphManager->GetGraphBuilderCount();
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

      if (m_bUseReportManager)
      {
         GET_IFACE(IEAFReportManager, reportManager);
         IndexType nReports = reportManager->GetReportBuilderCount();
         BOOL bIsReport = (GetReportCommand(0, false) <= nID && nID <= GetReportCommand(nReports - 1, false));
         BOOL bIsQuickReport = (GetReportCommand(0, true) <= nID && nID <= GetReportCommand(nReports - 1, true));

         if (bIsReport || bIsQuickReport)
         {
            if (nCode == CN_UPDATE_COMMAND_UI)
            {
               CCmdUI* pCmdUI = (CCmdUI*)(pExtra);
               pCmdUI->Enable(TRUE);
               return TRUE;
            }
            else if (nCode == CN_COMMAND)
            {
               if (bIsQuickReport)
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
   }
	
	return CEAFDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CEAFBrokerDocument::PopulateReportMenu(std::shared_ptr<WBFL::EAF::Menu> pReportMenu)
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
      pReportMenu->AppendMenu(EAFID_REPORT_MENU_DISPLAY_MODE,msg, nullptr);
      pReportMenu->AppendSeparator();
   }

   BuildReportMenu(pReportMenu,false);
}

void CEAFBrokerDocument::BuildReportMenu(std::shared_ptr<WBFL::EAF::Menu> pMenu,BOOL bQuickReport)
{
   GET_IFACE(IEAFReportManager, reportManager);
   std::vector<std::_tstring> rptNames = reportManager->GetReportNames();

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
         pMenu->AppendMenu(nCmd,rptName.c_str(), nullptr);

         const CBitmap* pBmp = reportManager->GetMenuBitmap(rptName);
         pMenu->SetMenuItemBitmaps(nCmd,MF_BYCOMMAND,pBmp,nullptr, nullptr);

         didlist = true;
      }

      i++;
      ASSERT(i <= EAF_REPORT_MENU_COUNT);
   }

   // Deal with case where there are no favorites
   if ( m_bFavoriteReports && !didlist )
   {
      pMenu->AppendMenu(EAFID_OPTIONS_REPORTING,_T("No favorite reports exist. You can add some by clicking here."), nullptr);
   }
}

UINT CEAFBrokerDocument::GetReportCommand(IndexType rptIdx,BOOL bQuickReport) const
{
   IndexType baseID = EAF_REPORT_MENU_BASE;

   if ( !bQuickReport )
   {
      GET_IFACE(IEAFReportManager, reportManager);
      IndexType nReports = reportManager->GetReportBuilderCount();

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
      GET_IFACE(IEAFReportManager, reportManager);
      IndexType nReports = reportManager->GetReportBuilderCount();

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

void CEAFBrokerDocument::PopulateGraphMenu(std::shared_ptr<WBFL::EAF::Menu> pGraphMenu)
{
   if (m_bIsGraphMenuPopulated)
   {
      return;
   }

   // remove any old graphs and placeholders
   UINT nItems = pGraphMenu->GetMenuItemCount();
   for ( UINT idx = 0; idx < nItems; idx++ )
   {
      pGraphMenu->RemoveMenu(0,MF_BYPOSITION, nullptr);
   }

   BuildGraphMenu(pGraphMenu);

   m_bIsGraphMenuPopulated = true;
}

void CEAFBrokerDocument::BuildGraphMenu(std::shared_ptr<WBFL::EAF::Menu> pMenu)
{
   GET_IFACE(IEAFGraphManager, graphManager);
   std::vector<std::_tstring> graphNames = graphManager->GetGraphNames();

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
      pMenu->AppendMenu(nCmd,graphName.c_str(), nullptr);

      const CBitmap* pBmp = graphManager->GetMenuBitmap(graphName);
      pMenu->SetMenuItemBitmaps(nCmd,MF_BYCOMMAND,pBmp,nullptr, nullptr);

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
   GET_IFACE(IEAFProgress,pProgress);
   WBFL::EAF::AutoProgress progress(pProgress);
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

   auto nAgents = m_pBroker->GetAgentCount();
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      auto agent = m_pBroker->GetAgent(agentIdx);

      auto pDocIntegration = std::dynamic_pointer_cast<WBFL::EAF::IAgentDocumentationIntegration>(agent);
      if ( pDocIntegration )
      {
         HRESULT hr = pDocIntegration->LoadDocumentationMap();
         ATLASSERT(SUCCEEDED(hr));
      }
   }

   nAgents = m_pBroker->GetExtensionAgentCount();
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      auto agent = m_pBroker->GetExtensionAgent(agentIdx);

      auto pDocIntegration = std::dynamic_pointer_cast<WBFL::EAF::IAgentDocumentationIntegration>(agent);
      if ( pDocIntegration )
      {
         HRESULT hr = pDocIntegration->LoadDocumentationMap();
         ATLASSERT(SUCCEEDED(hr));
      }
   }
}

std::pair<WBFL::EAF::HelpResult,CString> CEAFBrokerDocument::GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID)
{
   // let the base class do its thing first
   auto helpResult = CEAFDocument::GetDocumentLocation(lpszDocSetName,nHID);
   if ( helpResult.first == WBFL::EAF::HelpResult::OK || helpResult.first == WBFL::EAF::HelpResult::TopicNotFound )
   {
      // if we have a good help document location or if the doc set was found but the HID was bad,
      // we are done... return the result
      return helpResult;
   }

   // Search through the agents and extension agents for anyone implementing the IAgentDocumentationIntegration interface

   USES_CONVERSION;
   CString strDocSetName(lpszDocSetName);

   auto nAgents = m_pBroker->GetAgentCount();
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      auto agent = m_pBroker->GetAgent(agentIdx);
      auto pDocIntegration = std::dynamic_pointer_cast<WBFL::EAF::IAgentDocumentationIntegration>(agent);
      if ( pDocIntegration )
      {
         auto strMyDocSetName = pDocIntegration->GetDocumentationSetName();
         if ( strMyDocSetName == strDocSetName )
         {
            // matched the target document set...

            return pDocIntegration->GetDocumentLocation(nHID);
         }
      }
   }

   nAgents = m_pBroker->GetExtensionAgentCount();
   for ( IndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      auto agent = m_pBroker->GetExtensionAgent(agentIdx);
      auto pDocIntegration = std::dynamic_pointer_cast<WBFL::EAF::IAgentDocumentationIntegration>(agent);
      if ( pDocIntegration )
      {
         auto strMyDocSetName = pDocIntegration->GetDocumentationSetName();
         if ( strMyDocSetName == strDocSetName )
         {
            // matched the target document set...

            return pDocIntegration->GetDocumentLocation(nHID);
         }
      }
   }

   return { WBFL::EAF::HelpResult::DocSetNotFound,CString() };
}

BOOL CEAFBrokerDocument::IsReportCommand(UINT nID,BOOL bQuickReport)
{
   if ( m_bUseReportManager )
   {
      GET_IFACE(IEAFReportManager, reportManager);
      IndexType nReports = reportManager->GetReportBuilderCount();
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
   if ( m_bUseGraphManager )
   {
      GET_IFACE(IEAFGraphManager, graphManager);
      IndexType nGraphs = graphManager->GetGraphBuilderCount();
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
   if ( m_bUseReportManager )
   {
      GET_IFACE(IEAFReportManager, reportManager);
      IndexType nReports = reportManager->GetReportBuilderCount();
      if ( (GetReportCommand(0,FALSE) <= nID && nID <= GetReportCommand(nReports-1,FALSE)) ||
           (GetReportCommand(0,TRUE)  <= nID && nID <= GetReportCommand(nReports-1,TRUE)) )
      {
         rMessage.Format(_T("Creates a report"));
         bHandled = TRUE;
      }
   }

   if ( m_bUseGraphManager )
   {
      GET_IFACE(IEAFGraphManager, graphManager);
      IndexType nGraphs = graphManager->GetGraphBuilderCount();
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
   if ( m_bUseReportManager)
   {
      GET_IFACE(IEAFReportManager, reportManager);
      IndexType nReports = reportManager->GetReportBuilderCount();
      if ( (GetReportCommand(0,FALSE) <= nID && nID <= GetReportCommand(nReports-1,FALSE)) ||
           (GetReportCommand(0,TRUE)  <= nID && nID <= GetReportCommand(nReports-1,TRUE)) )
      {
         rMessage.Format(_T("Creates a report"));
         bHandled = TRUE;
      }
   }

   if ( m_bUseGraphManager )
   {
      GET_IFACE(IEAFGraphManager, graphManager);
      IndexType nGraphs = graphManager->GetGraphBuilderCount();
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
   GET_IFACE(IEAFReportManager, reportManager);
   std::vector<std::_tstring> rptNames = reportManager->GetReportNames();

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

void CEAFBrokerDocument::SetCustomReportHelpID(WBFL::EAF::CustomReportHelp helpType,UINT nHelpID)
{
   if ( helpType == WBFL::EAF::CustomReportHelp::CustomReport )
   {
      m_helpIDCustom = nHelpID;
   }
   else
   {
      m_helpIDFavorite = nHelpID;
   }
}

UINT CEAFBrokerDocument::GetCustomReportHelpID(WBFL::EAF::CustomReportHelp helpType) const
{
   if ( helpType == WBFL::EAF::CustomReportHelp::CustomReport )
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

void CEAFBrokerDocument::OnCustomReportError(WBFL::EAF::CustomReportError error, LPCTSTR lpszReportName, LPCTSTR lpszOtherName)
{
   CString strError;

   switch(error)
   {
   case WBFL::EAF::CustomReportError::ParentMissingAtLoad:
         strError.Format(_T("For custom report \"%s\": the parent report %s could not be found at program load time. The custom report was deleted."),lpszReportName,lpszOtherName);
         break;
      case WBFL::EAF::CustomReportError::ParentMissingAtImport:
         strError.Format(_T("For custom report \"%s\": the parent report %s could not be found. The report may have depended on an application extension. The custom report was deleted."), lpszReportName, lpszOtherName);
         break;
      case WBFL::EAF::CustomReportError::ChapterMissingAtLoad:
      case WBFL::EAF::CustomReportError::ChapterMissingAtImport:
         strError.Format(_T("For custom report \"%s\": the following chapter %s does not exist in the parent report. The chapter was removed. Perhaps the chapter name changed? You may want to edit the report."), lpszReportName, lpszOtherName);
         break;
      default:
         ATLASSERT(false);
   };

   GET_IFACE(IEAFStatusCenter,pStatusCenter);
   pStatusCenter->Add(std::make_shared<WBFL::EAF::DefaultStatusItem>(m_StatusGroupID, m_scidCustomReportWarning, strError));
}

void CEAFBrokerDocument::ShowCustomReportHelp(WBFL::EAF::CustomReportHelp helpType)
{
   // Base class must call AFX_MANAGE_STATE(AfxGetStaticModuleState()) before calling this method
   UINT helpID = helpType==WBFL::EAF::CustomReportHelp::CustomReport ? m_helpIDCustom : m_helpIDFavorite;
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
   if ( !m_bUseReportManager )
   {
      // reporting isn't supported
      return;
   }

   GET_IFACE(IEAFReportManager, reportManager);
   if (bFirst)
   {
      // First time through. Store names of built-in reports
      m_BuiltInReportNames = reportManager->GetReportNames();
   }
   else
   {
      // Subsequent times through we need to remove custom reports before reloading them
      std::vector<std::_tstring> strNames = reportManager->GetReportNames();
      std::vector<std::_tstring>::const_iterator itn = strNames.begin();
      while(itn != strNames.end())
      {
         const std::_tstring& rName = *itn;
         std::vector<std::_tstring>::const_iterator itfnd = std::find(m_BuiltInReportNames.begin(), m_BuiltInReportNames.end(), rName);
         if (itfnd == m_BuiltInReportNames.end())
         {
            // Remove report if it's not built in. ptr release should delete it.
            std::shared_ptr<WBFL::Reporting::ReportBuilder> ptr = reportManager->RemoveReportBuilder(rName.c_str());
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
         std::shared_ptr<WBFL::Reporting::ReportBuilder> pParentBuilder = reportManager->GetReportBuilder(rCustom.m_ParentReportName);
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
                  OnCustomReportError(bFirst?WBFL::EAF::CustomReportError::ChapterMissingAtLoad:WBFL::EAF::CustomReportError::ChapterMissingAtImport,rCustom.m_ReportName.c_str(),(*itChapName).c_str());
                  itChapName = rCustom.m_Chapters.erase(itChapName);
                  ATLASSERT(false);
               }
            }

            // 
            if(didAddChapter)
            {
               reportManager->AddReportBuilder(newBuilder);
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
            OnCustomReportError(bFirst?WBFL::EAF::CustomReportError::ParentMissingAtLoad:WBFL::EAF::CustomReportError::ParentMissingAtImport,rCustom.m_ReportName.c_str(),rCustom.m_ParentReportName.c_str());
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