// BridgeGeometryView.cpp : implementation file
//

#include "stdafx.h"
#include "BridgeGeometry.h"
#include <BridgeGeometry\BridgeGeometryView.h>
#include <WBFLDManip.h>
#include <EAF\EAFBrokerDocument.h>

#include <AgentTools.h>

#include <initguid.h>
#include <BridgeGeometryInterfaces.h>

// CBridgeGeometryView

IMPLEMENT_DYNCREATE(CBridgeGeometryView, CDisplayView)

CBridgeGeometryView::CBridgeGeometryView()
{

}

CBridgeGeometryView::~CBridgeGeometryView()
{
}

BEGIN_MESSAGE_MAP(CBridgeGeometryView, CDisplayView)
END_MESSAGE_MAP()



// CBridgeGeometryView diagnostics

#ifdef _DEBUG
void CBridgeGeometryView::AssertValid() const
{
//   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDisplayView::AssertValid();
}

#ifndef _WIN32_WCE
void CBridgeGeometryView::Dump(CDumpContext& dc) const
{
	CDisplayView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBridgeGeometryView message handlers

void CBridgeGeometryView::OnInitialUpdate()
{
   CDisplayView::OnInitialUpdate();

   CEAFBrokerDocument* pDoc = (CEAFBrokerDocument*)GetDocument();
   CComPtr<IBroker> pBroker;
   pDoc->GetBroker(&pBroker);

   GET_IFACE2(pBroker,IRoadwayDisplayBuilder,pBuilder);
   pBuilder->BuildRoadwayDisplay(this);
}
