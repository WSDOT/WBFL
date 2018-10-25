///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <EAF\EAFCustomReport.h>
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
   // called after the document data is created/loaded
   virtual void OnCreateFinalize();

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEAFBrokerDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   void BuildReportMenu(CEAFMenu* pMenu,bool bQuickReport);

   // Determine whether to display favorite reports or all reports in menu dropdowns
   bool GetDoDisplayFavoriteReports() const;
   void SetDoDisplayFavoriteReports(bool doDisplay);

   // Current list of favorite reports
   std::vector<std::_tstring> GetFavoriteReports() const;
   void SetFavoriteReports( std::vector<std::_tstring> reports);
   bool IsFavoriteReport(const std::_tstring& rptName);

   // Custom, user-defined reports
   CEAFCustomReports GetCustomReports() const;
   void SetCustomReports(const CEAFCustomReports& reports);

   // Generated message map functions
protected:
   IBroker* m_pBroker;

   BOOL m_DisplayFavoriteReports;
   std::vector<std::_tstring> m_FavoriteReports;

   CEAFCustomReports m_CustomReports;
   std::vector<std::_tstring> m_BuiltInReportNames;

   // Bitmap shown on the menus for custom reports
   CBitmap m_bmpCustomReports;

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

   // Fire when changed from favorite reports to all reports. Let know if from a menu or other source
   virtual void OnChangedFavoriteReports(bool isFavorites, bool fromMenu);

   // Virtual error handling when custom or favorite report data has gone wrong in some way
   enum custReportErrorType {
      creParentMissingAtLoad,   // Parent for custom missing at program load time
      creParentMissingAtImport, // Parent for custom missing when importing
      creChapterMissingAtLoad,
      creChapterMissingAtImport
   };
   virtual void OnCustomReportError(custReportErrorType error, const std::_tstring& reportName, const std::_tstring& otherName);
   void IntegrateCustomReports(bool bFirst);

public:
   // Allow applications to publish help for custom reports and favorites
   enum custRepportHelpType {
      crhCustomReport,
      crhFavoriteReport
   };
   virtual void OnCustomReportHelp(custRepportHelpType helpType);

protected:  
	//{{AFX_MSG(CEAFBrokerDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnReportMenuDisplayMode();
   afx_msg void OnUpdateReportMenuDisplayMode(CCmdUI* pCmdUI);
	afx_msg void OnConfigureReports();

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
