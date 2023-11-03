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


#pragma once

// EAFReportView.h : header file
//

#include <EAF\EAFExp.h>
#include <IReportManager.h>
#include <EAF\EAFView.h>

class CReportButton;

// Creation data that is needed by the report view to create the proper report
struct EAFCLASS CEAFReportViewCreationData
{
   IndexType m_RptIdx; // Index of the report to be created (index into the report manager)

   // Option 1 - Provide Report Specification
   std::shared_ptr<WBFL::Reporting::ReportSpecification> m_pRptSpecification; // the report specification
   std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder> m_pRptSpecificationBuilder; // and the corresponding builder
   BOOL m_bInitializeOnly; // if true, creates the report view, sets the spec and spec builder, but does not generate the report

   // Option 2 - Report view creates specification
   BOOL m_bPromptForSpec; // true = prompt user to configure spec through UI, otherwise use default
   
   // The report manager
   std::shared_ptr<const WBFL::Reporting::ReportBuilderManager> m_pReportBuilderMgr; // Use this when using regular Doc/View
   IReportManager* m_pRptMgr; // Use this when using the Agent/Broker architecture

   CEAFReportViewCreationData()
   {
      m_RptIdx = 0;
      m_bPromptForSpec = TRUE;
      m_pReportBuilderMgr = nullptr;
      m_pRptMgr = nullptr;
      m_bInitializeOnly = FALSE;
   }
};

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView view
class EAFCLASS CEAFReportView : public CEAFView
{
protected:
	CEAFReportView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEAFReportView)

// Attributes
public:

   // one of these is nullptr, the other is not
   std::shared_ptr<const WBFL::Reporting::ReportBuilderManager> m_pReportBuilderMgr;
   IReportManager* m_pRptMgr; // for use with Agent/Broker

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFReportView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
   virtual void UpdateNow(const std::shared_ptr<const WBFL::Reporting::ReportHint>& pHint);

protected:
	virtual ~CEAFReportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
   // Initializes the report view, but doesn't create the report. This methods is called by CreateReport
   // so you generally will not need to call it directly
   virtual bool InitReport(std::shared_ptr<WBFL::Reporting::ReportSpecification>& pSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pSpecBuilder);

   // Creates a report. The report specification is created by the user through the UI
   virtual bool CreateReport(IndexType rptIdx,BOOL bPromptForSpec=true);

   // Creates a report. The report specification was created elsewhere and is supplied here
   virtual bool CreateReport(IndexType rptIdx, std::shared_ptr<WBFL::Reporting::ReportSpecification>& pSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pSpecBuilder);

   // listen if our button was clicked
   void NotifyReportButtonWasClicked();

   std::shared_ptr<const WBFL::Reporting::ReportSpecification> GetReportSpecification() const;

   virtual BOOL CanEditReport();

   // Generated message map functions
protected:
	//{{AFX_MSG(CEAFReportView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnToolbarPrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	//}}AFX_MSG
   afx_msg void OnCmenuSelected(UINT id);
	DECLARE_MESSAGE_MAP()

   virtual void EditReport();
   virtual void RefreshReport(); // called from EditReport when the report needs to be refreshed
   virtual void CreateReportSpecification(IndexType rptIdx,BOOL bCreateDefaultReport);
   virtual HRESULT UpdateReportBrowser(const std::shared_ptr<const WBFL::Reporting::ReportHint>&  pHint);

   // Translate an MFC OnUpdate hint into a CReportHint object that will be passed into
   // the report build and chapter builders to determine if the report needs to be updated
   virtual WBFL::Reporting::ReportHint* TranslateHint(CView* pSender, LPARAM lHint, CObject* pHint);


protected:
   std::shared_ptr<WBFL::Reporting::ReportBrowser> m_pReportBrowser;
   std::shared_ptr<WBFL::Reporting::ReportSpecification> m_pReportSpec;
   std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder> m_pRptSpecBuilder;

   BOOL m_bInvalidReport; // true if an update event is received and the contents of the report are not invalid
   BOOL m_bNoBrowser;     // true if the browser window couldn't be created
   BOOL m_bUpdateError;   // true if an error occurred while updating the report contents
   BOOL m_bIsNewReport;   // true while calls are coming from OnInitialUpdate
   BOOL m_bUpdateInProgress; // true if the report is being generated/updated

   std::_tstring m_ErrorMsg;

   static bool ms_bIsUpdatingReport; // true while the report content is being updated

   CWnd* m_pwndEdit;
   CFont   m_fnEdit;

   void UpdateViewTitle();
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual CWnd* CreateEditButton();

private:
   CReportButton* m_pBtnEdit;

   std::vector<std::_tstring> GetReportNames();
   std::shared_ptr<const WBFL::Reporting::ReportBuilder> GetReportBuilder(const std::_tstring& strRptName) const;
   std::shared_ptr<WBFL::Reporting::ReportBrowser> CreateReportBrowser(HWND hwndParent, DWORD dwStyle,const std::shared_ptr<WBFL::Reporting::ReportSpecification>& pRptSpec, const std::shared_ptr<const WBFL::Reporting::ReportSpecificationBuilder>& pRptSpecBuilder);
};
