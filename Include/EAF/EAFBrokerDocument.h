#if !defined(AFX_EAFBrokerDocument_H__94649CAC_01E1_467D_9445_9E8CAA727538__INCLUDED_)
#define AFX_EAFBrokerDocument_H__94649CAC_01E1_467D_9445_9E8CAA727538__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EAFBrokerDocument.h : header file
//
#include <EAF\EAFExp.h>
#include <EAF\EAFDocument.h>
#include <comcat.h>


class CEAFDocProxyAgent;
class CEAFDocTemplate;

/////////////////////////////////////////////////////////////////////////////
// CEAFBrokerDocument document

class EAFCLASS CEAFBrokerDocument : public CEAFDocument
{
protected:
	CEAFBrokerDocument();           // protected constructor used by dynamic creation
	DECLARE_DYNAMIC(CEAFBrokerDocument)

// Attributes
public:

// Operations
public:
   HRESULT GetBroker(IBroker** ppBroker);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFBrokerDocument)
	protected:
   virtual void OnCloseDocument();

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEAFBrokerDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
   IBroker* m_pBroker;

   // since the broker has no way of returning a registered agent
   // we need to keep a pointer to the doc proxy agent so it
   // can be initialized for menu and toolbar intergration functionality
   CEAFDocProxyAgent* m_pDocProxyAgent;

   /// returns the CATID for the agents to be used with this document
   virtual CATID GetAgentCategoryID() = 0;
   
   /// called when a document is created (New or Open)
   virtual BOOL Init(); 

   /// called during initialization
   virtual BOOL LoadAgents(); 

   /// called during initialization. load agents such as the WBFL Report Manager and Sys Agents
   virtual BOOL LoadSpecialAgents(IBrokerInitEx2* pBrokerInit); 

   /// helper function for loading an agent
   virtual BOOL LoadAgents(IBrokerInitEx2* pBrokerInit, CLSID* pClsid, long nClsid);  
   
   /// called when an error occurs loading an agent
   virtual void OnLoadAgentsError(); 

   /// called after all agents are loaded (called from CEAFDocTemplate::InitialUpdateFrame)
   virtual void InitAgents(); 

   // over-ride this method to create a different agent
   virtual CEAFDocProxyAgent* CreateDocProxyAgent();

   // creates the broker
   virtual BOOL CreateBroker();

   // Called by the base-class when thte document is to be loaded
   // and saved
   virtual HRESULT LoadTheDocument(IStructuredLoad* pStrLoad);
   virtual HRESULT SaveTheDocument(IStructuredSave* pStrSave);

	//{{AFX_MSG(CEAFBrokerDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   friend CEAFDocProxyAgent;
   friend CEAFDocTemplate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EAFBrokerDocument_H__94649CAC_01E1_467D_9445_9E8CAA727538__INCLUDED_)
