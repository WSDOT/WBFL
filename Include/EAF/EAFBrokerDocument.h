///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <IReportManager.h>
#include <IGraphManager.h>


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
	CEAFBrokerDocument(bool bReporting = true,bool bGraphing = true);           // protected constructor used by dynamic creation
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
   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName) override;
   virtual void OnCloseDocument() override;
   virtual void DeleteContents() override;
   virtual BOOL OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo) override;
   // called after the document data is created/loaded
   virtual void OnCreateFinalize() override;

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEAFBrokerDocument();

#ifdef _DEBUG
	virtual void AssertValid() const override;
	virtual void Dump(CDumpContext& dc) const override;
#endif

   void BuildReportMenu(CEAFMenu* pMenu,BOOL bQuickReport);
   void BuildGraphMenu(CEAFMenu* pMenu);

   // Determine whether to display favorite reports or all reports in menu dropdowns
   BOOL DisplayFavoriteReports() const;
   void DisplayFavoriteReports(BOOL doDisplay);

   // Current list of favorite reports
   const std::vector<std::_tstring>& GetFavoriteReports() const;
   void SetFavoriteReports(const std::vector<std::_tstring>& reports);
   BOOL IsFavoriteReport(const std::_tstring& rptName);

   // Custom, user-defined reports
   const CEAFCustomReports& GetCustomReports() const;
   void SetCustomReports(const CEAFCustomReports& reports);

   // this must still be pure virtual methods... see note in base calss
   virtual BOOL GetStatusBarMessageString(UINT nID,CString& rMessage) const = 0;
   virtual BOOL GetToolTipMessageString(UINT nID, CString& rMessage) const = 0;

   // called when help on the custom reporting feature is to be activiated
   // Help topic IDs are set with SetCustomReportHelpID
   // Call AFX_MANAGE_STATE(AfxGetStaticModuleState()) in the derived class
   // before calling this method
   virtual void ShowCustomReportHelp(eafTypes::CustomReportHelp helpType) = 0;

   // called when help on the Custom Report Definition dialog is activated.
   virtual void ShowCustomReportDefinitionHelp() = 0;

   // Causes the documentation map file to be loaded
   virtual void LoadDocumentationMap() override;

   // Returns the full documentation URL for the given URL
   virtual eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL) override;

   // Returns TRUE if the command id (nID) is for a report.
   BOOL IsReportCommand(UINT nID,BOOL bQuickReport);

   // Returns TRUE if the command id is for a graph
   BOOL IsGraphCommand(UINT nID);

// Generated message map functions
protected:
   IBroker* m_pBroker;

   bool m_bIsGraphMenuPopulated;

   BOOL m_bDisplayFavoriteReports;
   std::vector<std::_tstring> m_FavoriteReports;

   CEAFCustomReports m_CustomReports;
   std::vector<std::_tstring> m_BuiltInReportNames;

   // Bitmap shown on the menus for custom reports
   CBitmap m_bmpCustomReports;

   // returns the CATID for the agents to be used with this document
   // All agents registered with this category ID will be loaded when
   // LoadAgents() is called
   virtual CATID GetAgentCategoryID() = 0;

   // returns the CATID for the extension agents to be used with this document
   // All agents registered with this category ID will be loaded when
   // LoadAgents() is called.
   // Return CLSID_NULL if you don't want to support extension agents
   virtual CATID GetExtensionAgentCategoryID();
   
   /// called when a document is created (New or Open)
   virtual BOOL Init() override; 

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
   virtual void DoIntegrateWithUI(BOOL bIntegrate) override;

   // Called by the framework to give plug-ins an opportunity to process command line options
   // Return TRUE if the command line options where handled
   virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo) override;

   // creates the broker
   virtual BOOL CreateBroker();

   // called by the framework when the it is time to shutdown the broker
   virtual void BrokerShutDown();

   // Called by the base-class when thte document is to be loaded
   // and saved. Calls Load and Save on the IBrokerPersist interface
   virtual HRESULT LoadTheDocument(IStructuredLoad* pStrLoad) override;
   virtual HRESULT WriteTheDocument(IStructuredSave* pStrSave) override;

   // Application logging
   virtual CString GetLogFileName(); // returns the log file name (AppName.log is default)
   virtual void OnLogFileOpened(); // called when the log file is first opened
   virtual void OnLogFileClosing(); // called when the log file is about to close

   /// populates a menu with the names of the reports
   void PopulateReportMenu(CEAFMenu* pReportMenu);
   UINT GetReportCommand(IndexType rptIdx,BOOL bQuickReport) const;
   IndexType GetReportIndex(UINT nID,BOOL bQuickReport) const;
   virtual void CreateReportView(IndexType rptIdx,BOOL bPrompt); // does nothing by default
   void OnReport(UINT nID);
   void OnQuickReport(UINT nID);

   /////////////////////////////////////
   // Custom Reporting
   void FavoriteReports(BOOL bEnable); // Enables/Disables the Favorites Report feature
   BOOL FavoriteReports() const;
   void SetCustomReportHelpID(eafTypes::CustomReportHelp helpType,UINT nHelpID);
   UINT GetCustomReportHelpID(eafTypes::CustomReportHelp helpType) const;
   void SetCustomReportDefinitionHelpID(UINT nHelpID);
   UINT GetCustomReportDefinitionHelpID() const;
   virtual void OnChangedFavoriteReports(BOOL bIsFavorites, BOOL bFromMenu);
   virtual void OnCustomReportError(eafTypes::CustomReportError error, LPCTSTR lpszReportName, LPCTSTR lpszOtherName);
   void IntegrateCustomReports(bool bFirst=false);

   void PopulateGraphMenu(CEAFMenu* pGraphMenu);
   UINT GetGraphCommand(IndexType graphIdx) const;
   IndexType GetGraphIndex(UINT nID) const;
   void OnGraph(UINT nID);
   virtual void CreateGraphView(IndexType graphIdx); // does nothing by default

   virtual void OnUpdateAllViews(CView* pSender, LPARAM lHint = 0L,CObject* pHint = nullptr) override;

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
   // can be initialized for menu and toolbar integration functionality
   CEAFDocProxyAgent* m_pDocProxyAgent;

   bool m_bUseReportManager = false;
   bool m_bUseGraphManager = false;
   IReportManager* m_pReportManager = nullptr; // weak pointers
   IGraphManager* m_pGraphManager = nullptr; // weak pointers

   UINT m_helpIDCustom;
   UINT m_helpIDFavorite;
   UINT m_helpIDCustomReportDefinition;
   BOOL m_bFavoriteReports;

   // callback IDs for any status callbacks we register
   StatusCallbackIDType m_scidCustomReportWarning;
   StatusGroupIDType m_StatusGroupID;

   friend CEAFDocProxyAgent;
   friend CEAFDocTemplate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EAFBrokerDocument_H__94649CAC_01E1_467D_9445_9E8CAA727538__INCLUDED_)
