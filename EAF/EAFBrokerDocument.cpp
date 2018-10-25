// EAFBrokerDocument.cpp : implementation file
//

#include "stdafx.h"
#include <comdef.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFDocProxyAgent.h>

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
}

CEAFBrokerDocument::~CEAFBrokerDocument()
{
}


BEGIN_MESSAGE_MAP(CEAFBrokerDocument, CEAFDocument)
	//{{AFX_MSG_MAP(CEAFBrokerDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEAFBrokerDocument::OnCloseDocument()
{
   if ( m_pBroker )
   {
      m_pBroker->ShutDown();
      ULONG cRef = m_pBroker->Release();
      ASSERT( cRef == 0 );
      
      m_pBroker = 0;
   }

   CEAFDocument::OnCloseDocument();
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

   // NOTE: DO NOT CALL InitAgents() here
   // Before agents can initialize the menu command handling
   // has to be set up. This can't happen until the frame
   // window is created.
   //
   // CEAFDocTemplate extends the InitialUpdateFrame() function
   // to call CEAFBrokerDocument::InitAgents() after the frame window is created.
   
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
   _COM_SMARTPTR_TYPEDEF(IBrokerInitEx2,IID_IBrokerInitEx2);
   IBrokerInitEx2Ptr pBrokerInit = NULL;
   m_pBroker->QueryInterface(IID_IBrokerInitEx2,(void**)&pBrokerInit);
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

BOOL CEAFBrokerDocument::LoadAgents()
{
   // get the correct interface from the broker
   _COM_SMARTPTR_TYPEDEF(IBrokerInitEx2,IID_IBrokerInitEx2);
   IBrokerInitEx2Ptr pBrokerInit = NULL;
   m_pBroker->QueryInterface(IID_IBrokerInitEx2,(void**)&pBrokerInit);

   // create component category manager
   _COM_SMARTPTR_TYPEDEF(ICatRegister,__uuidof(ICatRegister));
   ICatRegisterPtr pICatReg;
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
   _COM_SMARTPTR_TYPEDEF(ICatInformation,__uuidof(ICatInformation));
   ICatInformationPtr pICatInfo;
   pICatReg->QueryInterface(&pICatInfo);

   _COM_SMARTPTR_TYPEDEF(IEnumCLSID,__uuidof(IEnumCLSID));
   IEnumCLSIDPtr pIEnumCLSID;

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

   return TRUE;
}

BOOL CEAFBrokerDocument::LoadAgents(IBrokerInitEx2* pBrokerInit, CLSID* pClsid, long nClsid)
{
   // this function does the actual work of loading an agent
   long lErrIndex = 0;
   HRESULT hr = pBrokerInit->LoadAgents( pClsid, nClsid, &lErrIndex );
   if ( FAILED(hr) )
   {
      LPOLESTR pszCLSID;
      StringFromCLSID( pClsid[lErrIndex], &pszCLSID );
      CString strCLSID(pszCLSID);
      ::CoTaskMemFree( (LPVOID)pszCLSID );

      LPOLESTR pszProgID;
      ProgIDFromCLSID( pClsid[lErrIndex], &pszProgID );
      CString strProgID(pszProgID);
      ::CoTaskMemFree( (LPVOID)pszProgID );

      std::ostringstream msg;
      msg << "Failed to load agent. hr = " << hr << std::endl;
      msg << "CLSID = " << strCLSID.LockBuffer() << std::endl;
      msg << "ProgID = " << strProgID.LockBuffer() << std::endl << std::ends;
      FailSafeLogMessage( msg.str().c_str() );

      strCLSID.UnlockBuffer();
      strProgID.UnlockBuffer();

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

   m_pDocProxyAgent = CreateDocProxyAgent();
   m_pDocProxyAgent->SetBroker( m_pBroker );
   
   HRESULT hr = pBrokerInit->AddAgent( m_pDocProxyAgent );

   return SUCCEEDED(hr);
}

void CEAFBrokerDocument::InitAgents()
{
   // NOTE: This function called from CEAFDocTemplate::InitialUpdateFrame()

   // and finally, initialize the agents
   _COM_SMARTPTR_TYPEDEF(IBrokerInitEx2,IID_IBrokerInitEx2);
   IBrokerInitEx2Ptr pBrokerInit = NULL;
   m_pBroker->QueryInterface(IID_IBrokerInitEx2,(void**)&pBrokerInit);

   pBrokerInit->InitAgents();
}

CEAFDocProxyAgent* CEAFBrokerDocument::CreateDocProxyAgent()
{
   return new CEAFDocProxyAgent();
}

void CEAFBrokerDocument::OnLoadAgentsError()
{
   // over ride this method to provide an error message or log 
   InitFailMessage();
}

HRESULT CEAFBrokerDocument::LoadTheDocument(IStructuredLoad* pStrLoad)
{
   _COM_SMARTPTR_TYPEDEF(IBrokerPersist,IID_IBrokerPersist);
   IBrokerPersistPtr pPersist;
   m_pBroker->QueryInterface( &pPersist );
   ASSERT( pPersist.GetInterfacePtr() != NULL );
   return pPersist->Load( pStrLoad );
}

HRESULT CEAFBrokerDocument::SaveTheDocument(IStructuredSave* pStrSave)
{
   _COM_SMARTPTR_TYPEDEF(IBrokerPersist,IID_IBrokerPersist);
   IBrokerPersistPtr pPersist;
   m_pBroker->QueryInterface( &pPersist );
   ASSERT( pPersist.GetInterfacePtr() != NULL );
   return pPersist->Save( pStrSave );
}
