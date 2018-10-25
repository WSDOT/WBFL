// EAFDocProxyAgent.cpp: implementation of the CEAFDocProxyAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFApp.h>
#include <EAF\EAFDocProxyAgent.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFAppPlugin.h>
#include <EAF\EAFDocTemplateRegistrar.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFDocProxyAgent::CEAFDocProxyAgent()
{
   m_pBroker = 0;
   m_pDoc = 0;
   m_pMainFrame = 0;
   m_cRef = 0;
}

CEAFDocProxyAgent::~CEAFDocProxyAgent()
{

}

void CEAFDocProxyAgent::SetDocument(CEAFBrokerDocument* pDoc)
{
   m_pDoc = pDoc;
}

void CEAFDocProxyAgent::SetMainFrame(CEAFMainFrame* pFrame)
{
   m_pMainFrame = pFrame;
}

CEAFMainFrame* CEAFDocProxyAgent::GetMainFrame()
{
   return m_pMainFrame;
}

void CEAFDocProxyAgent::OnInit()
{
   // does nothing by default
   // sub-classes to provide functionality
   // such as registering for connection points implemented
   // by agents so that events can be passed to the Doc/View model
}

//////////////////////////////////////////
// IUnknown
STDMETHODIMP CEAFDocProxyAgent::QueryInterface(const IID& iid, void** ppv)
{
   if ( iid == IID_IUnknown )
   {
      *ppv = static_cast<IAgent*>(this);
   }
   else if ( iid == IID_IAgent )
   {
      *ppv = static_cast<IAgent*>(this);
   }
   else if ( iid == IID_IAgentEx )
   {
      *ppv = static_cast<IAgentEx*>(this);
   }
   else if ( iid == IID_IViewRegistrar )
   {
      *ppv = static_cast<IViewRegistrar*>(this);
   }
   else if ( iid == IID_IMainMenu )
   {
      *ppv = static_cast<IMainMenu*>(this);
   }
   else if ( iid == IID_IToolBars )
   {
      *ppv = static_cast<IToolBars*>(this);
   }
   else if ( iid == IID_IDocument )
   {
      *ppv = static_cast<IDocument*>(this);
   }
   else
   {
      *ppv = NULL;
      return E_NOINTERFACE;
   }

   reinterpret_cast<IUnknown*>(*ppv)->AddRef();
   return S_OK;
}

STDMETHODIMP_(ULONG) CEAFDocProxyAgent::AddRef()
{
   return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CEAFDocProxyAgent::Release()
{
   if ( InterlockedDecrement(&m_cRef) == 0 )
   {
      delete this;
      return 0;
   }

   return m_cRef;
}

//////////////////////////////////////////
// IAgentEx
STDMETHODIMP CEAFDocProxyAgent::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::RegInterfaces()
{
   _COM_SMARTPTR_TYPEDEF(IBrokerInitEx2,IID_IBrokerInitEx2);
   IBrokerInitEx2Ptr pBrokerInit;
   m_pBroker->QueryInterface(&pBrokerInit);

   pBrokerInit->RegInterface( IID_IViewRegistrar,    this );
   pBrokerInit->RegInterface( IID_IMainMenu,         this );
   pBrokerInit->RegInterface( IID_IToolBars,         this );
   pBrokerInit->RegInterface( IID_IDocument,         this );
//   pBrokerInit->RegInterface( IID_IAcceleratorTable, this );

   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::Init()
{
   OnInit();
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::Init2()
{
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::Reset()
{
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::ShutDown()
{
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::GetClassID(CLSID* pCLSID)
{
   *pCLSID = CLSID_NULL;
   return S_OK;
}

///////////////////////////////////////////////////////
// IViewRegistrar
long CEAFDocProxyAgent::RegisterView(CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu,int maxViewCount)
{
   CEAFDocTemplate* pMyTemplate = (CEAFDocTemplate*)(m_pDoc->GetDocTemplate());
   UINT nResourceID = pMyTemplate->m_pPlugin->GetDocumentResourceID();

   CEAFDocTemplate* pNewDocTemplate = new CEAFDocTemplate(nResourceID,m_pDoc->GetRuntimeClass(),pFrameClass,pViewClass,hSharedMenu,maxViewCount);

   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();

   long key = pRegistrar->AddDocTemplate(pNewDocTemplate);
   return key;
}

void CEAFDocProxyAgent::RemoveView(long key)
{
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();
   pRegistrar->RemoveDocTemplate(key);
}

CView* CEAFDocProxyAgent::CreateView(long key)
{
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();

   // if this assert fires, you probably added AFX_MANAGE_STATE(AfxGetStaticModuleState())
   // in the scope of calling this method
   // Try removing AFX_MANAGE_STATE or re-scoping it
   ASSERT(pApp->IsKindOf(RUNTIME_CLASS(CEAFApp)));


   CEAFDocTemplateRegistrar* pRegistrar = pApp->GetDocTemplateRegistrar();
   CEAFDocTemplate* pTemplate = pRegistrar->GetDocTemplate(key);

   return m_pMainFrame->CreateOrActivateFrame(pTemplate);
}

///////////////////////////////////////////////////////
// IMainMenu
CEAFMenu* CEAFDocProxyAgent::GetMainMenu()
{
   return m_pDoc->GetMenu();
}

///////////////////////////////////////////////////////
// IToolBars
CEAFToolBar* CEAFDocProxyAgent::GetMainToolBar()
{
   return m_pMainFrame->GetMainToolBar();
}

CEAFToolBar* CEAFDocProxyAgent::CreateToolBar(LPCTSTR lpszName)
{
   return m_pMainFrame->CreateToolBar(lpszName,m_pDoc->m_pPluginCommandMgr);
}

void CEAFDocProxyAgent::DestroyToolBar(CEAFToolBar* pToolBar)
{
   m_pMainFrame->DestroyToolBar(pToolBar);
}

///////////////////////////////////////////////////////
// IDocument
BOOL CEAFDocProxyAgent::IsModified()
{
   return m_pDoc->IsModified();
}

void CEAFDocProxyAgent::SetModified()
{
   m_pDoc->SetModifiedFlag(TRUE);
}

CString CEAFDocProxyAgent::GetFileName()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetFileName();
      finder.Close();
   }

   return strResult;
}

CString CEAFDocProxyAgent::GetFileTitle()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetFileTitle();
      finder.Close();
   }

   return strResult;
}

CString CEAFDocProxyAgent::GetFilePath()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetFilePath();
      finder.Close();
   }

   return strResult;
}

CString CEAFDocProxyAgent::GetFileRoot()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetRoot();
      finder.Close();
   }

   return strResult;
}

void CEAFDocProxyAgent::UpdateAllViews(CView* pSender,LPARAM lHint,CObject* pHint)
{
   m_pDoc->UpdateAllViews(pSender,lHint,pHint);
}
