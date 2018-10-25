///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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



#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFAutoCalcDoc.h>
#include <EAF\EAFAutoCalcReportView.h>
#include <EAF\EAFLicensePlateChildFrame.h>
#include <EAF\EAFDocTemplate.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcReportView


IMPLEMENT_DYNCREATE(CEAFAutoCalcReportView, CEAFReportView)

CEAFAutoCalcReportView::CEAFAutoCalcReportView() :
CEAFAutoCalcViewMixin(this)
{
}

CEAFAutoCalcReportView::~CEAFAutoCalcReportView()
{
}

BEGIN_MESSAGE_MAP(CEAFAutoCalcReportView, CEAFReportView)
	//{{AFX_MSG_MAP(CEAFAutoCalcReportView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcReportView drawing

void CEAFAutoCalcReportView::OnInitialUpdate() 
{
   CEAFAutoCalcViewMixin::Initialize();

   CDocument* pDoc = GetDocument();
   CEAFAutoCalcDocMixin* pAutoCalcDoc = dynamic_cast<CEAFAutoCalcDocMixin*>(pDoc);
   ATLASSERT(pAutoCalcDoc); // your document must use the autocalc mix in
   if ( pAutoCalcDoc->IsAutoCalcEnabled() )
   {
      CEAFReportView::OnInitialUpdate();
   }
   else
   {
      m_bInvalidReport = true;

      CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
      ASSERT( pDocTemplate->IsKindOf(RUNTIME_CLASS(CEAFDocTemplate)) );

      CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDocTemplate;
      CEAFReportViewCreationData* pCreateData = (CEAFReportViewCreationData*)pTemplate->GetViewCreationData();
      ASSERT(pCreateData != NULL);

      m_pReportBuilderMgr = pCreateData->m_pReportBuilderMgr;
      m_pRptMgr = pCreateData->m_pRptMgr;
      ATLASSERT(m_pReportBuilderMgr != NULL || m_pRptMgr != NULL); // one of these should not be NULL

      CollectionIndexType rptIdx = pCreateData->m_RptIdx;
      bool bPromptForSpec = pCreateData->m_bPromptForSpec;

      CreateReportSpecification(rptIdx,bPromptForSpec);

      UpdateViewTitle();
      m_bIsNewReport = false;
   }

}

void CEAFAutoCalcReportView::OnDraw(CDC* pDC)
{
   CEAFReportView::OnDraw(pDC);
   if ( !m_pReportBrowser )
   {
      // don't draw license plate frame if nothing to view
      EnableLpFrame( false );
   }
}

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcReportView diagnostics

#ifdef _DEBUG
void CEAFAutoCalcReportView::AssertValid() const
{
	CEAFReportView::AssertValid();
}

void CEAFAutoCalcReportView::Dump(CDumpContext& dc) const
{
	CEAFReportView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcReportView message handlers

void CEAFAutoCalcReportView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   CEAFAutoCalcViewMixin::OnUpdate(pSender,lHint,pHint); // turns on LP frame if needed

   CEAFAutoCalcDocMixin* pAutoCalcDoc = GetAutoCalcDocument();

   // this comes for some kind of event.. only have the report view update itself
   // if auto calc is enabled

   // Something has changed to invalidate the report
   m_bInvalidReport = true;

   if ( pAutoCalcDoc->IsAutoCalcEnabled() )
      CEAFReportView::OnUpdate(pSender,lHint,pHint);
}

void CEAFAutoCalcReportView::UpdateNow()
{
   // Update is forced by the user
   CEAFReportView::UpdateNow(NULL);
}

void CEAFAutoCalcReportView::UpdateNow(CReportHint* pHint)
{
   // Update is forced by the user
   CEAFReportView::UpdateNow(pHint);
}

void CEAFAutoCalcReportView::EditReport()
{
   CDocument* pDoc = GetDocument();
   CEAFAutoCalcDocMixin* pAutoCalcDoc = dynamic_cast<CEAFAutoCalcDocMixin*>(pDoc);
   ATLASSERT(pAutoCalcDoc); // your document must use the autocalc mix in

   if ( pAutoCalcDoc->IsAutoCalcEnabled() )
   {
      CEAFReportView::EditReport();
   }
   else
   {
      if ( m_pReportBrowser->Edit(false) ) // false = don't update the report results
      {
         m_pReportSpec = m_pReportBrowser->GetReportSpecification();
         EnableLpFrame(true);
         m_bInvalidReport = true;
      }
   }
}

HRESULT CEAFAutoCalcReportView::UpdateReportBrowser(CReportHint* pHint)
{
   HRESULT hr = CEAFReportView::UpdateReportBrowser(pHint);

   CEAFLicensePlateChildFrame* pParent = GetLpFrame();
   if ( FAILED(hr) )
   {
      pParent->SetLicensePlateMode(eafTypes::lpfOn);
      pParent->SetLicensePlateText(m_ErrorMsg.c_str());
   }
   else
   {
      CDocument* pDoc = GetDocument();
      CEAFAutoCalcDocMixin* pAutoCalcDoc = dynamic_cast<CEAFAutoCalcDocMixin*>(pDoc);
      ATLASSERT(pAutoCalcDoc); // your document must use the autocalc mix in
      if ( pAutoCalcDoc->IsAutoCalcEnabled() && pParent->GetLicensePlateMode() == eafTypes::lpfOn )
      {
         // if auto calc is enable and there was no error updating the view,
         // make sure the license plate frame is off
         pParent->SetLicensePlateMode(eafTypes::lpfOff);
      }
   }

   return hr;
}

bool CEAFAutoCalcReportView::DoResultsExist()
{
   return (m_pReportBrowser != 0 ? true : false);
}
