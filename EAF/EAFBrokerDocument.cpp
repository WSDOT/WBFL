///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <EAF\EAFResources.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFHints.h>
#include "EAFDocProxyAgent.h"
#include <AgentTools.h>
#include <IReportManager.h>

#include "ConfigureReportsDlg.h"

#include <sstream> // for ostringstream

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEAFBrokerDocument

IMPLEMENT_DYNAMIC(CEAFBrokerDocument, CEAFDocument)

CEAFBrokerDocument::CEAFBrokerDocument()
{
   m_pBroker = NULL;
   m_pDocProxyAgent =  NULL;
   m_DisplayFavoriteReports = FALSE;

   // The base class registers as a unit mode listener
   // However, the DocProxyAgent also registers as a listener
   // This generates 2 units changed events whenever the units change
   // Remove this document from the listener list so that only one event is received
   CEAFApp* pApp = EAFGetApp();
   pApp->RemoveUnitModeListener(this);
}

CEAFBrokerDocument::~CEAFBrokerDocument()
{
}


BEGIN_MESSAGE_MAP(CEAFBrokerDocument, CEAFDocument)
	//{{AFX_MSG_MAP(CEAFBrokerDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_REPORT_MENU_DISPLAY_MODE, OnReportMenuDisplayMode)
   ON_UPDATE_COMMAND_UI(ID_REPORT_MENU_DISPLAY_MODE, OnUpdateReportMenuDisplayMode)
	ON_COMMAND(ID_OPTIONS_REPORTING, OnConfigureReports)

END_MESSAGE_MAP()

BOOL CEAFBrokerDocument::OnOpenDocument(LPCTSTR lpszPathName)
{
   BOOL bResult = CEAFDocument::OnOpenDocument(lpszPathName);

   return bResult;
}

void CEAFBrokerDocument::DeleteContents()
{
   CEAFDocument::DeleteContents();
   BrokerShutDown();
}

void CEAFBrokerDocument::OnCreateFinalize()
{
   CEAFDocument::OnCreateFinalize();

   // At this point we have loaded all hard-coded reports and read custom
   // report data from the registry, and broker is loaded. Create custom reports
   m_bmpCustomReports.LoadBitmap(IDB_CREPORT_BMP);

   IntegrateCustomReports(true);
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
   if ( !CEAFDocument::Init() )
      return FALSE;

   if ( !CreateBroker() )
   {
      InitFailMessage();
      return FALSE;
   }

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
   hr = ::CoCreateInstance( CLSID_Broker2, NULL, CLSCTX_INPROC_SERVER, IID_IBroker, (void**)&m_pBroker );
   if ( FAILED(hr) )
   {
      std::_tostringstream msg;
      msg << _T("Failed to create broker. hr = ") << hr << std::endl << std::ends;
      FailSafeLogMessage( msg.str().c_str() );
      return FALSE;
   }

   // get the IBrokerInitEx2 interface
   // the broker we want to be using implements this interface so
   // generate an error if it doesn't
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);
   if ( pBrokerInit == NULL )
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
   if ( m_pBroker )
   {
      m_pBroker->ShutDown();
      ULONG cRef = m_pBroker->Release();
      ASSERT( cRef == 0 );
      
      m_pBroker = NULL;

      m_pDocProxyAgent = NULL;
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
                            NULL,
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
   pICatInfo->EnumClassesOfCategories(nID,ID,0,NULL,&pIEnumCLSID);

   // load up to 10 agents at a time
   const int nMaxAgents = 10;
   CLSID clsid[nMaxAgents];

   ULONG nAgentsLoaded = 0;
   while (SUCCEEDED(pIEnumCLSID->Next(nMaxAgents,clsid,&nAgentsLoaded)) && 0 < nAgentsLoaded )
   {
      // load the agents
      if ( !LoadAgents(pBrokerInit, clsid, nAgentsLoaded) )
         return FALSE;
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
      pICatInfo->EnumClassesOfCategories(nID,ID,0,NULL,&pIEnumCLSID);

      nAgentsLoaded = 0;
      while (SUCCEEDED(pIEnumCLSID->Next(nMaxAgents,clsid,&nAgentsLoaded)) && 0 < nAgentsLoaded )
      {
         // load the extension agents - do it one at a time so that disabled ones can be skipped
         CEAFApp* pApp = EAFGetApp();
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
      hr = pBrokerInit->LoadAgents( pClsid, nClsid, &lErrArray );
   else
      hr = pBrokerInit->LoadExtensionAgents( pClsid, nClsid, &lErrArray );

   if ( FAILED(hr) )
   {
      CollectionIndexType nErrors;
      lErrArray->get_Count(&nErrors);
      for ( CollectionIndexType errIdx = 0; errIdx < nErrors; errIdx++ )
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

   return SUCCEEDED(hr);
}

void CEAFBrokerDocument::InitAgents()
{
   // and finally, initialize all the agents
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);
   pBrokerInit->InitAgents();
}

void CEAFBrokerDocument::DoIntegrateWithUI(BOOL bIntegrate)
{
   CEAFDocument::DoIntegrateWithUI(bIntegrate);

   CComQIPtr<IBrokerInitEx3> pBrokerInit(m_pBroker);
   pBrokerInit->IntegrateWithUI(bIntegrate);
}

BOOL CEAFBrokerDocument::ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo)
{
   if ( CEAFDocument::ProcessCommandLineOptions(cmdInfo) )
      return TRUE; // handled

   CComQIPtr<IManageAgents> manageAgents(m_pBroker);
   CollectionIndexType nAgents;
   manageAgents->get_AgentCount(&nAgents);
   for ( CollectionIndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_Agent(agentIdx,&agent);

      CComQIPtr<IEAFProcessCommandLine,&IID_IEAFProcessCommandLine> processCommandLine(agent);
      if ( processCommandLine )
      {
         if ( processCommandLine->ProcessCommandLineOptions(cmdInfo) )
            return TRUE; // handled
      }
   }

   manageAgents->get_ExtensionAgentCount(&nAgents);
   for ( CollectionIndexType agentIdx = 0; agentIdx < nAgents; agentIdx++ )
   {
      CComPtr<IAgent> agent;
      manageAgents->get_ExtensionAgent(agentIdx,&agent);

      CComQIPtr<IEAFProcessCommandLine,&IID_IEAFProcessCommandLine> processCommandLine(agent);
      if ( processCommandLine )
      {
         if ( processCommandLine->ProcessCommandLineOptions(cmdInfo) )
            return TRUE; // handled
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
   ::SHGetKnownFolderPath(FOLDERID_Desktop,0,NULL,&strDesktop);

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
      // Interrupt the normal command processing to handle reports
      // The report menu items are dynamically generated and so are their IDs
      // If the command code is in the range IDM_REPORT to IDM_REPORT+nReports a specific
      // report name was selected from a menu. Send the message on to the OnReport handler
      // and tell MFC that this message has been handled (return TRUE)
      GET_IFACE(IReportManager,pReportMgr);
      CollectionIndexType nReports = pReportMgr->GetReportBuilderCount();
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
               OnQuickReport(nID);
            else
               OnReport(nID);

            return TRUE;
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
      pReportMenu->RemoveMenu(0,MF_BYPOSITION,NULL);
   }

   // Add favorites option at top
   CString msg = m_DisplayFavoriteReports==FALSE ? _T("Show only favorites") : _T("Show all reports");
   pReportMenu->AppendMenu(ID_REPORT_MENU_DISPLAY_MODE,msg,NULL);
   pReportMenu->AppendSeparator();

   BuildReportMenu(pReportMenu,false);
}

void CEAFBrokerDocument::BuildReportMenu(CEAFMenu* pMenu,bool bQuickReport)
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
      if ( m_DisplayFavoriteReports == FALSE || IsFavoriteReport(rptName) )
      {
         dolist = true;
      }

      if (dolist)
      {
         UINT nCmd = GetReportCommand(i,bQuickReport);
         pMenu->AppendMenu(nCmd,rptName.c_str(),NULL);

         const CBitmap* pBmp = pReportMgr->GetMenuBitmap(rptName);
         pMenu->SetMenuItemBitmaps(nCmd,MF_BYCOMMAND,pBmp,NULL,NULL);

         didlist = true;
      }

      i++;
      ASSERT(i <= EAF_REPORT_MENU_COUNT);
   }

   // Deal with case where there are no favorites
   if (!didlist)
   {
      pMenu->AppendMenu(ID_OPTIONS_REPORTING,_T("No favorite reports exist. You can add some by clicking here."),NULL);
   }
}

UINT CEAFBrokerDocument::GetReportCommand(CollectionIndexType rptIdx,bool bQuickReport)
{
   CollectionIndexType baseID = EAF_REPORT_MENU_BASE;

   if ( !bQuickReport )
   {
      GET_IFACE(IReportManager,pReportMgr);
      CollectionIndexType nReports = pReportMgr->GetReportBuilderCount();

      baseID += nReports + 1;
   }

   ASSERT(rptIdx + baseID <= EAF_REPORT_MENU_BASE+2*EAF_REPORT_MENU_COUNT);
   return (UINT)(rptIdx + baseID);
}

CollectionIndexType CEAFBrokerDocument::GetReportIndex(UINT nID,bool bQuickReport)
{
   if ( nID < EAF_REPORT_MENU_BASE || EAF_REPORT_MENU_BASE+2*EAF_REPORT_MENU_COUNT < nID )
      return INVALID_INDEX;

   CollectionIndexType baseID = EAF_REPORT_MENU_BASE;
   if ( !bQuickReport )
   {
      GET_IFACE(IReportManager,pReportMgr);
      CollectionIndexType nReports = pReportMgr->GetReportBuilderCount();

      baseID += nReports + 1;
   }

   return (CollectionIndexType)(nID - baseID);
}

void CEAFBrokerDocument::OnReport(UINT nID)
{
   // User picked a report from a menu.
   // get the report index
   CollectionIndexType rptIdx = GetReportIndex(nID,false);
   CreateReportView(rptIdx,true);
}

void CEAFBrokerDocument::OnQuickReport(UINT nID)
{
   // User picked a report from a menu.
   // This is a "quick report" so don't prompt
   CollectionIndexType rptIdx = GetReportIndex(nID,true);
   CreateReportView(rptIdx,false);
}

void CEAFBrokerDocument::CreateReportView(CollectionIndexType rptIdx,bool bPrompt)
{
   // User must override this method to display the report
   AfxMessageBox(_T("Override CEAFBrokerDocument::CreateReportView to create the specific report view you want"));
}


bool CEAFBrokerDocument::GetDoDisplayFavoriteReports() const
{
   return m_DisplayFavoriteReports!=FALSE;
}

void CEAFBrokerDocument::SetDoDisplayFavoriteReports(bool doDisplay)
{
   BOOL bDoDisplay = doDisplay == true ? TRUE : FALSE;
   if ( m_DisplayFavoriteReports != bDoDisplay )
   {
      m_DisplayFavoriteReports = bDoDisplay;
      UpdateAllViews(NULL,EAF_HINT_FAVORITE_REPORTS_CHANGED,NULL);
   }
}

std::vector<std::_tstring> CEAFBrokerDocument::GetFavoriteReports() const
{
   return m_FavoriteReports;
}

void CEAFBrokerDocument::SetFavoriteReports( std::vector<std::_tstring> reports)
{
   m_FavoriteReports = reports;
}

bool CEAFBrokerDocument::IsFavoriteReport(const std::_tstring& rptName)
{
   return (m_FavoriteReports.end() != std::find(m_FavoriteReports.begin(), m_FavoriteReports.end(), rptName));
}

CEAFCustomReports CEAFBrokerDocument::GetCustomReports() const
{
   return m_CustomReports;
}

void CEAFBrokerDocument::SetCustomReports(const CEAFCustomReports& reports)
{
   m_CustomReports = reports;
}

void CEAFBrokerDocument::OnReportMenuDisplayMode()
{
   // flip value
   SetDoDisplayFavoriteReports(!m_DisplayFavoriteReports);
   OnChangedFavoriteReports(m_DisplayFavoriteReports!=FALSE, true);
}

void CEAFBrokerDocument::OnUpdateReportMenuDisplayMode(CCmdUI* pCmdUI)
{
   pCmdUI->SetText( (m_DisplayFavoriteReports ? _T("Show all reports") : _T("Show only favorites") ) );
}

void CEAFBrokerDocument::OnConfigureReports()
{
   GET_IFACE(IReportManager,pReportMgr);
   std::vector<std::_tstring> rptNames = pReportMgr->GetReportNames();

   CConfigureReportsDlg dlg(_T("Configure Reports"));

   dlg.m_pBroker = m_pBroker;
   dlg.SetFavorites(m_FavoriteReports);
   dlg.m_FavoriteReportsPage.m_bShowFavoritesInMenus = m_DisplayFavoriteReports;
   dlg.m_CustomReports = m_CustomReports;

   if (dlg.DoModal() == IDOK)
   {
      m_FavoriteReports = dlg.GetFavorites();
      m_DisplayFavoriteReports = dlg.m_FavoriteReportsPage.m_bShowFavoritesInMenus;
      m_CustomReports = dlg.m_CustomReports;

      IntegrateCustomReports(false);
      OnChangedFavoriteReports(m_DisplayFavoriteReports!=FALSE, false);
   }
}

void CEAFBrokerDocument::OnChangedFavoriteReports(bool isFavorites, bool fromMenu)
{
   // Do nothing in base class
}

void CEAFBrokerDocument::OnCustomReportError(custReportErrorType error, const std::_tstring& reportName, const std::_tstring& otherName)
{
   // Do nothing in base class. Error handling happens in app
}

void CEAFBrokerDocument::OnCustomReportHelp(custRepportHelpType helpType)
{
   // Do nothing in base class. Magic happens in app
}


void CEAFBrokerDocument::IntegrateCustomReports(bool bFirst)
{
   GET_IFACE(IReportManager,pReportMgr);

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
            boost::shared_ptr<CReportBuilder> ptr = pReportMgr->RemoveReportBuilder(rName.c_str());
         }

         itn++;
      }
   }

   // Add custom reports
   CEAFCustomReports::ReportIterator itcr = m_CustomReports.m_Reports.begin();
   while(itcr != m_CustomReports.m_Reports.end())
   {
      CEAFCustomReport& rCustom = *itcr;

      // First check that custom report does not have same name as a built-in. This always be blocked by the UI
      std::vector<std::_tstring>::const_iterator itfnd = std::find(m_BuiltInReportNames.begin(), m_BuiltInReportNames.end(), rCustom.m_ReportName);
      if ( itfnd == m_BuiltInReportNames.end() )
      {
         // get parent report
         boost::shared_ptr<CReportBuilder> pParentBuilder = pReportMgr->GetReportBuilder(rCustom.m_ParentReportName);
         if (pParentBuilder)
         {
            // found parent. Now we can create new builder for custom
            boost::shared_ptr<CReportBuilder> newBuilder( new CReportBuilder(rCustom.m_ReportName.c_str()));
            newBuilder->SetReportSpecificationBuilder( pParentBuilder->GetReportSpecificationBuilder() );

            // Title page
            boost::shared_ptr<CTitlePageBuilder> ptp = pParentBuilder->GetTitlePageBuilder();
            if (ptp)
            {
               boost::shared_ptr<CTitlePageBuilder> pntp( ptp->Clone() );
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
               boost::shared_ptr<CChapterBuilder> pChapterB( pParentBuilder->GetChapterBuilder( itChapName->c_str() ) );
               if ( pChapterB )
               {
                  newBuilder->AddChapterBuilder( pChapterB );
                  didAddChapter = true;
                  itChapName++;
               }
               else
               {
                  // Chapter referenced from custom does not exist in parent report. 
                  OnCustomReportError(bFirst?creChapterMissingAtLoad:creChapterMissingAtImport,rCustom.m_ReportName,*itChapName);
                  itChapName = rCustom.m_Chapters.erase(itChapName);
                  ATLASSERT(0);
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
               ATLASSERT(0); // should never have empty reports
               itcr = m_CustomReports.m_Reports.erase(itcr);
            }
         }
         else
         {
            // parent report does not exist for custom report. remove report and post
            OnCustomReportError(bFirst?creParentMissingAtLoad:creParentMissingAtImport,rCustom.m_ReportName,rCustom.m_ParentReportName);
            itcr = m_CustomReports.m_Reports.erase(itcr);
            ATLASSERT(0);
         }
      }
      else
      {
         // Custom report has same name as a built-in. This would be a very rare case where a built-in
         // was added later that matches a custom. Or, there is a bug in the UI checking. Let it go by silently
         ATLASSERT(0);
         itcr = m_CustomReports.m_Reports.erase(itcr);
      }
   }
}