///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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
//
// Derived from CEAFDocument, the CEAFBrokerDocument class provides default
// implementations necessary to support the Agent/Broker architecture.
//
// The GetAgentCategoryID() must be implemented by a derived class

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
   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
   virtual void DeleteContents();
   virtual BOOL OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo);

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEAFBrokerDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   void BuildReportMenu(CEAFMenu* pMenu,bool bQuickReport);

   // Generated message map functions
protected:
   IBroker* m_pBroker;

   bool m_bIsReportMenuPopulated; 

   // returns the CATID for the agents to be used with this document
   // All agents registred with this category ID will be loaded when
   // LoadAgents() is called
   virtual CATID GetAgentCategoryID() = 0;

   // returns the CATID for the extension agents to be used with this document
   // All agents registred with this category ID will be loaded when
   // LoadAgents() is called.
   // Return CLSID_NULL if you don't want to support extension agents
   virtual CATID GetExtensionAgentCategoryID();
   
   /// called when a document is created (New or Open)
   virtual BOOL Init(); 

   /// called during initialization
   virtual BOOL LoadAgents(); 

   // called during initialization. Load agents such as the WBFL Report Manager and Sys Agents
   // This method creates the EAFDocProxyAgent
   virtual BOOL LoadSpecialAgents(IBrokerInitEx2* pBrokerInit); 

   // helper function for loading an agent
   virtual BOOL LoadAgents(IBrokerInitEx2* pBrokerInit, CLSID* pClsid, long nClsid,bool bRequiredAgent = true);  
   
   // called when an error occurs loading an agent
   virtual void OnLoadAgentsError(); 

   // called after all agents are loaded
   virtual void InitAgents(); 

   // Called by the framework to give plug-ins the opportunity to
   // integrate with the user interface
   virtual void DoIntegrateWithUI(BOOL bIntegrate);

   // Called by the framework to give plug-ins an opportunity to process command line options
   // Return TRUE if the command line options where handled
   virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo);

   // creates the broker
   virtual BOOL CreateBroker();

   // called by the framework when the it is time to shutdown the broker
   virtual void BrokerShutDown();

   // Called by the base-class when thte document is to be loaded
   // and saved. Calls Load and Save on the IBrokerPersist interface
   virtual HRESULT LoadTheDocument(IStructuredLoad* pStrLoad);
   virtual HRESULT WriteTheDocument(IStructuredSave* pStrSave);

   // Application logging
   virtual CString GetLogFileName(); // returns the log file name (AppName.log is default)
   virtual void OnLogFileOpened(); // called when the log file is first opened
   virtual void OnLogFileClosing(); // called when the log file is about to close

   /// populates a menu with the names of the reports
   void PopulateReportMenu(CEAFMenu* pReportMenu);
   UINT GetReportCommand(CollectionIndexType rptIdx,bool bQuickReport);
   CollectionIndexType GetReportIndex(UINT nID,bool bQuickReport);
   virtual void CreateReportView(CollectionIndexType rptIdx,bool bPrompt); // does nothing by default
   void OnReport(UINT nID);
   void OnQuickReport(UINT nID);

	//{{AFX_MSG(CEAFBrokerDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   // since the broker has no way of returning a registered agent
   // we need to keep a pointer to the doc proxy agent so it
   // can be initialized for menu and toolbar intergration functionality
   CEAFDocProxyAgent* m_pDocProxyAgent;


   friend CEAFDocProxyAgent;
   friend CEAFDocTemplate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EAFBrokerDocument_H__94649CAC_01E1_467D_9445_9E8CAA727538__INCLUDED_)
