///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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
#include "EAFDocProxyAgent.h"
#include <AgentTools.h>
#include <IReportManager.h>

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
   m_bIsReportMenuPopulated = false;

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
   CString strFileName;
   strFileName.Format(_T("%s.log"),EAFGetApp()->m_pszExeName);
   return strFileName;
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
   if (m_bIsReportMenuPopulated)
      return;

   // remove any old reports and placeholders
   UINT nItems = pReportMenu->GetMenuItemCount();
   for ( UINT idx = 0; idx < nItems; idx++ )
   {
      pReportMenu->RemoveMenu(0,MF_BYPOSITION,NULL);
   }

   BuildReportMenu(pReportMenu,false);

   m_bIsReportMenuPopulated = true;
}

void CEAFBrokerDocument::BuildReportMenu(CEAFMenu* pMenu,bool bQuickReport)
{
   GET_IFACE(IReportManager,pReportMgr);
   std::vector<std::_tstring> rptNames = pReportMgr->GetReportNames();

   // if this assert fires, there are more reports than can be put into the menus
   // EAF only reserves enough room for EAF_REPORT_MENU_COUNT reports
   ATLASSERT(rptNames.size() < EAF_REPORT_MENU_BASE+EAF_REPORT_MENU_COUNT);

   UINT i = 0;
   std::vector<std::_tstring>::iterator iter(rptNames.begin());
   std::vector<std::_tstring>::iterator end(rptNames.end());
   for ( ; iter != end; iter++ )
   {
      std::_tstring rptName = *iter;
      UINT nCmd = GetReportCommand(i,bQuickReport);
      pMenu->AppendMenu(nCmd,rptName.c_str(),NULL);

      const CBitmap* pBmp = pReportMgr->GetMenuBitmap(rptName);
      pMenu->SetMenuItemBitmaps(nCmd,MF_BYCOMMAND,pBmp,NULL,NULL);

      i++;

      ASSERT(i <= EAF_REPORT_MENU_COUNT);
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
}
