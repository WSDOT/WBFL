// EAFDocProxyAgent.h: interface for the CEAFDocProxyAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EAFDocProxyAgent_H__F3E2AEF7_0B1E_41B3_979B_63CF96EB1B2F__INCLUDED_)
#define AFX_EAFDocProxyAgent_H__F3E2AEF7_0B1E_41B3_979B_63CF96EB1B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <EAF\EAFExp.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFUIIntegration.h>

#include <WBFLCore.h> // IBroker, et. al.

class EAFCLASS CEAFDocProxyAgent : 
public IAgentEx,
public IViewRegistrar,
public IMainMenu,
public IToolBars,
public IDocument
{
public:
	CEAFDocProxyAgent();
	virtual ~CEAFDocProxyAgent();

   void SetDocument(CEAFBrokerDocument* pDoc);
   void SetMainFrame(CEAFMainFrame* pFrame);
   CEAFMainFrame* GetMainFrame();

// IUnknown
public:
   STDMETHOD(QueryInterface)(const IID& iid, void** ppv);
   STDMETHOD_(ULONG,AddRef)();
   STDMETHOD_(ULONG,Release)();

// IAgentEx
public:
   STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker);
	STDMETHOD(RegInterfaces)();
	STDMETHOD(Init)();
	STDMETHOD(Init2)();
	STDMETHOD(Reset)();
	STDMETHOD(ShutDown)();
   STDMETHOD(GetClassID)(CLSID* pCLSID);

// IViewRegistrar
public:
   virtual long RegisterView(CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=NULL,int maxViewCount=-1);
   virtual void RemoveView(long key);
   virtual CView* CreateView(long key);

// IMainMenu
public:
   virtual CEAFMenu* GetMainMenu();

// IToolBars
public:
   virtual CEAFToolBar* GetMainToolBar();
   virtual CEAFToolBar* CreateToolBar(LPCTSTR lpszName);
   virtual void DestroyToolBar(CEAFToolBar* pToolBar);

// IDocument
public:
   virtual BOOL IsModified();
   virtual void SetModified();
   virtual CString GetFileName();
   virtual CString GetFileTitle();
   virtual CString GetFilePath();
   virtual CString GetFileRoot();
   virtual void UpdateAllViews(CView* pSender,LPARAM lHint = 0L,CObject* pHint = NULL);

protected:
   virtual void OnInit(); // sub-classes to over-ride. Called from IAgent::Init

protected:
   IBroker* m_pBroker;
   CEAFBrokerDocument* m_pDoc;
   CEAFMainFrame* m_pMainFrame;

private:
   LONG m_cRef; // COM reference count
};

#endif // !defined(AFX_EAFDocProxyAgent_H__F3E2AEF7_0B1E_41B3_979B_63CF96EB1B2F__INCLUDED_)
