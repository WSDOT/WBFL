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

// EAFBrokerDocument.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFBrokerDocument.h>
#include "EAFDocProxyAgent.h"

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

   // The base class registers as a unit mode listener
   // However, the DocProxyAgent also registers as a listener
   // This generates 2 units changed events whenever the units change
   // Remove this document from the listener list so that only one event is received
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
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
      std::ostringstream msg;
      msg << "Failed to create broker. hr = " << hr << std::endl << std::ends;
      FailSafeLogMessage( msg.str().c_str() );
      return FALSE;
   }

   // get the IBrokerInitEx2 interface
   // the broker we want to be using implements this interface so
   // generate an error if it doesn't
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);
   if ( pBrokerInit == NULL )
   {
      FailSafeLogMessage("Wrong version of Broker installed\nRe-install");
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
      std::ostringstream msg;
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
         AFX_MANAGE_STATE(AfxGetAppModuleState());
         CWinApp* pApp = AfxGetApp();
         for (ULONG i = 0; i < nAgentsLoaded; i++ )
         {
            USES_CONVERSION;

            LPOLESTR pszCLSID;
            ::StringFromCLSID(clsid[i],&pszCLSID);

            CString strState = pApp->GetProfileString(_T("Extensions"),OLE2A(pszCLSID),_T("Enabled"));
            if ( strState.CompareNoCase(_T("Enabled")) == 0 )
            {
               CLSID* pCLSID = &clsid[i];
               LoadAgents(pBrokerInit,pCLSID,1,false); // false = not required

               // it is ok if extension agents fail to load... need to present user with a UI
               // to disable these agents so they wont be loaded in the future
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
   CComPtr<ILongArray> lErrArray;
   HRESULT hr = pBrokerInit->LoadAgents( pClsid, nClsid, &lErrArray );
   if ( FAILED(hr) )
   {
      long nErrors;
      lErrArray->get_Count(&nErrors);
      for ( long errIdx = 0; errIdx < nErrors; errIdx++ )
      {
         long agentIdx;
         lErrArray->get_Item(errIdx,&agentIdx);
         LPOLESTR pszCLSID;
         StringFromCLSID( pClsid[agentIdx], &pszCLSID );
         CString strCLSID(pszCLSID);
         ::CoTaskMemFree( (LPVOID)pszCLSID );

         LPOLESTR pszProgID;
         ProgIDFromCLSID( pClsid[agentIdx], &pszProgID );
         CString strProgID(pszProgID);
         ::CoTaskMemFree( (LPVOID)pszProgID );

         std::ostringstream msg;
         msg << "Failed to load agent. hr = " << hr << std::endl;
         msg << "CLSID = " << strCLSID.LockBuffer() << std::endl;
         msg << "ProgID = " << strProgID.LockBuffer() << std::endl << std::ends;
         FailSafeLogMessage( msg.str().c_str() );

         if ( !bRequiredAgent )
         {
            USES_CONVERSION;
            LPOLESTR pszUserType;
            OleRegGetUserType(pClsid[agentIdx],USERCLASSTYPE_SHORT,&pszUserType);

            CString strMsg;
            strMsg.Format("Failed to load %s.\n\nWould you like to disable this component?",OLE2A(pszUserType));
            if ( AfxMessageBox(strMsg,MB_YESNO | MB_ICONQUESTION) == IDYES )
            {
               AFX_MANAGE_STATE(AfxGetAppModuleState());
               CWinApp* pApp = AfxGetApp();
               pApp->WriteProfileString(_T("Extensions"),OLE2A(pszCLSID),_T("Disabled"));
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

   CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();

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
   strFileName.Format("%s.log",AfxGetApp()->m_pszExeName);
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
