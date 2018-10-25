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


#pragma once

// EAFReportView.h : header file
//

#include <EAF\EAFExp.h>
#include <IReportManager.h>

class CReportButton;

// Creation data that is needed by the report view to create the proper report
struct EAFCLASS CEAFReportViewCreationData
{
   CollectionIndexType m_RptIdx; // Index of the report to be created (index into the report manager)

   // Option 1 - Provide Report Specification
   boost::shared_ptr<CReportSpecification> m_pRptSpecification; // the report specification
   boost::shared_ptr<CReportSpecificationBuilder> m_pRptSpecificationBuilder; // and the corresponding builder
   bool m_bInitializeOnly; // if true, creates the report view, sets the spec and spec builder, but does not generate the report

   // Option 2 - Report view creates specification
   bool m_bPromptForSpec; // true = prompt user to configure spec through UI, otherwise use default
   
   // The report manager
   CReportBuilderManager* m_pReportBuilderMgr; // Use this when using regular Doc/View
   IReportManager* m_pRptMgr; // Use this when using the Agent/Broker architecture

   CEAFReportViewCreationData()
   {
      m_RptIdx = 0;
      m_bPromptForSpec = true;
      m_pReportBuilderMgr = NULL;
      m_pRptMgr = NULL;
      m_bInitializeOnly = false;
   }
};

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView view
class EAFCLASS CEAFReportView : public CView
{
protected:
	CEAFReportView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEAFReportView)

// Attributes
public:

   // one of these is NULL, the other is not
   CReportBuilderManager* m_pReportBuilderMgr;
   IReportManager* m_pRptMgr; // for use with Agent/Broker

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFReportView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
   virtual void UpdateNow(CReportHint* pHint);

protected:
	virtual ~CEAFReportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
   // Initializes the report view, but doesn't create the report. This methods is called by CreateReport
   // so you generally will not need to call it directly
   virtual bool InitReport(boost::shared_ptr<CReportSpecification>& pSpec,boost::shared_ptr<CReportSpecificationBuilder>& pSpecBuilder);

   // Creates a report. The report specification is created by the user through the UI
   virtual bool CreateReport(CollectionIndexType rptIdx,bool bPromptForSpec=true);

   // Creates a report. The report specification was created elsewhere and is supplied here
   virtual bool CreateReport(CollectionIndexType rptIdx,boost::shared_ptr<CReportSpecification>& pSpec,boost::shared_ptr<CReportSpecificationBuilder>& pSpecBuilder);

   // listen if our button was clicked
   void NotifyReportButtonWasClicked();

   boost::shared_ptr<CReportSpecification> GetReportSpecification();

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
   virtual void CreateReportSpecification(CollectionIndexType rptIdx,bool bCreateDefaultReport);
   virtual HRESULT UpdateReportBrowser(CReportHint* pHint);

   // Translate an MFC OnUpdate hint into a CReportHint object that will be passed into
   // the report build and chapter builders to determine if the report needs to be updated
   virtual CReportHint* TranslateHint(CView* pSender, LPARAM lHint, CObject* pHint);


protected:
   boost::shared_ptr<CReportBrowser> m_pReportBrowser;
   boost::shared_ptr<CReportSpecification> m_pReportSpec;
   boost::shared_ptr<CReportSpecificationBuilder> m_pRptSpecBuilder;

   bool m_bInvalidReport; // true if an update event is received and the contents of the report are not invalid
   bool m_bNoBrowser;     // true if the browser window couldn't be created
   bool m_bUpdateError;   // true if an error occured while updating the report contents
   bool m_bIsNewReport;   // true while calls are coming from OnInitialUpdate
   bool m_bUpdateInProgress; // true if the report is being generated/updated

   std::_tstring m_ErrorMsg;

   static bool ms_bIsUpdatingReport; // true while the report content is being updated

   CReportButton* m_pBtnEdit;
   CFont   m_btnFont;
 
   void UpdateViewTitle();
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void CreateEditButton();

private:
   std::vector<std::_tstring> GetReportNames();
   boost::shared_ptr<CReportBuilder> GetReportBuilder(const std::_tstring& strRptName);
   boost::shared_ptr<CReportBrowser> CreateReportBrowser(HWND hwndParent,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder);
};
