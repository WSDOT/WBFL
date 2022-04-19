///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <EAF\EAFAutoCalcGraphView.h>
#include <EAF\EAFAutoCalcGraphBuilder.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcGraphView


IMPLEMENT_DYNCREATE(CEAFAutoCalcGraphView, CEAFGraphView)

CEAFAutoCalcGraphView::CEAFAutoCalcGraphView() :
CEAFAutoCalcViewMixin(this)
{
}

CEAFAutoCalcGraphView::~CEAFAutoCalcGraphView()
{
}

BEGIN_MESSAGE_MAP(CEAFAutoCalcGraphView, CEAFGraphView)
	//{{AFX_MSG_MAP(CEAFAutoCalcGraphView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcGraphView drawing

void CEAFAutoCalcGraphView::OnInitialUpdate() 
{
   CEAFAutoCalcViewMixin::Initialize();
   CEAFGraphView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcGraphView diagnostics

#ifdef _DEBUG
void CEAFAutoCalcGraphView::AssertValid() const
{
	CEAFGraphView::AssertValid();
}

void CEAFAutoCalcGraphView::Dump(CDumpContext& dc) const
{
	CEAFGraphView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcGraphView message handlers

void CEAFAutoCalcGraphView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   CEAFAutoCalcViewMixin::OnUpdate(pSender,lHint,pHint); // turns on LP frame if needed

   CDocument* pDoc = GetDocument();
   CEAFAutoCalcDocMixin* pAutoCalcDoc = dynamic_cast<CEAFAutoCalcDocMixin*>(pDoc);
   ATLASSERT(pAutoCalcDoc); // your document must use the autocalc mix in

   // this comes from some kind of event.. only have the graph view update itself
   // if auto calc is enabled

   if ( pAutoCalcDoc->IsAutoCalcEnabled() )
   {
      CEAFGraphView::OnUpdate(pSender,lHint,pHint);
   }
}

bool CEAFAutoCalcGraphView::DoResultsExist()
{
   std::unique_ptr<WBFL::Graphing::GraphBuilder>& pGraphBuilder = GetGraphBuilder();
   CEAFAutoCalcGraphBuilder* pGraphBuilderBase = dynamic_cast<CEAFAutoCalcGraphBuilder*>(pGraphBuilder.get());
   return pGraphBuilderBase->IsValidGraph();
}

void CEAFAutoCalcGraphView::UpdateNow()
{
   std::unique_ptr<WBFL::Graphing::GraphBuilder>& pGraphBuilder = GetGraphBuilder();
   CEAFAutoCalcGraphBuilder* pGraphBuilderBase = dynamic_cast<CEAFAutoCalcGraphBuilder*>(pGraphBuilder.get());
   return pGraphBuilderBase->ForceUpdate();
}
