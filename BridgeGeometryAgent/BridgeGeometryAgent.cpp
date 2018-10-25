// BridgeGeometryAgent.cpp : Implementation of CBridgeGeometryAgent

#include "stdafx.h"
#include <WBFLBridgeGeometryAgent.h>
#include "BridgeGeometryAgent.h"
#include "BridgeGeometryInterfaces.h"

#include <DManip\DManip.h>

#include <EAF\EAFUIIntegration.h>

#define ALIGNMENT_DISPLAY_LIST 1


BEGIN_MESSAGE_MAP(CMyCmdTarget,CCmdTarget)
   ON_COMMAND(ID_EDIT_ALIGNMENT,OnEditAlignment)
END_MESSAGE_MAP()

void CMyCmdTarget::OnEditAlignment()
{
   m_pAgent->OnEditAlignment();
}

void CBridgeGeometryAgent::IntegrateMenuCommands()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   GET_IFACE(IEAFMainMenu,pMainMenu);
   CEAFMenu* pMenu = pMainMenu->GetMainMenu();

   INT nMenus = pMenu->GetMenuItemCount();

   m_pAlignmentMenu = pMenu->CreatePopupMenu(nMenus-1,_T("&Alignment"));
   m_pAlignmentMenu->AppendMenu(ID_EDIT_ALIGNMENT,_T("Edit"),this);
}

void CBridgeGeometryAgent::RemoveMenuCommands()
{
   // menus
   GET_IFACE(IEAFMainMenu,pMainMenu);
   CEAFMenu* pMenu = pMainMenu->GetMainMenu();
   pMenu->DestroyMenu(m_pAlignmentMenu);

}

/////////////////////////////////////////////////////////////////////////////
// Command Functions
void CBridgeGeometryAgent::OnEditAlignment()
{
   //if ( m_AlignmentMgr.EditAlignment() )
   //{
   //   m_bNeedsValidation = true;
   //   Fire_OnRoadwayChanged();
   //}
}

void CBridgeGeometryAgent::AdviseConnectionPoints()
{
   //CComQIPtr<IBrokerInitEx,&IID_IBrokerInitEx> pBrokerInit( m_pBroker );
   //CComPtr<IConnectionPoint> pCP;
   //HRESULT hr = S_OK;

   //// Connection point 
   //hr = pBrokerInit->FindConnectionPoint( IID_I???, &pCP );
   //ATLASSERT( SUCCEEDED(hr) );
   //hr = pCP->Advise( GetUnknown(), &m_dwCookie );
   //ATLASSERT( SUCCEEDED(hr) );
}

void CBridgeGeometryAgent::UnadviseConnectionPoints()
{
   ////
   //// Detach to connection points
   ////
   //CComQIPtr<IBrokerInitEx,&IID_IBrokerInitEx> pBrokerInit( m_pBroker );
   //CComPtr<IConnectionPoint> pCP;
   //HRESULT hr = S_OK;

   //hr = pBrokerInit->FindConnectionPoint(IID_I???, &pCP );
   //ATLASSERT( SUCCEEDED(hr) );
   //hr = pCP->Unadvise( m_dwCookie );
   //ATLASSERT( SUCCEEDED(hr) );
   //pCP.Release(); // Recycle the connection point
}

void CBridgeGeometryAgent::RegisterViews()
{
   //GET_IFACE(IEAFViewRegistrar,pViewReg);
   //m_ViewKey = pViewReg->RegisterView(RUNTIME_CLASS(CBridgeGeometryFrame),RUNTIME_CLASS(CBridgeGeometryView),NULL,1);
}

void CBridgeGeometryAgent::UnregisterViews()
{
   //GET_IFACE(IEAFViewRegistrar,pViewReg);
   //pViewReg->RemoveView(m_ViewKey);
}

// CBridgeGeometryAgent

void CBridgeGeometryAgent::Validate()
{
   if ( !m_bNeedsValidation )
      return;

   CComPtr<IPathCollection> alignments;
   m_CogoModel->get_Alignments(&alignments);

   CComPtr<IPointCollection> points;
   m_CogoModel->get_Points(&points);

//   Uint32 nAlignments = m_AlignmentMgr.GetAlignmentCount();
//   for ( Uint32 alignmentIdx = 0; alignmentIdx < nAlignments; alignmentIdx++ )
//   {
//      Int32 alignmentID = m_AlignmentMgr.GetAlignmentID(alignmentIdx);
//      CAlignmentDescription alignmentDesc = m_AlignmentMgr.GetAlignmentDescription(alignmentID);
//
//      CComPtr<IPath> path;
//      alignments->Add(alignmentIdx,&path);
//      CComQIPtr<IAlignment> alignment(path);
//
////      if ( pRoadwayData->GetHorzCurveCount(alignmentIdx) == 0 )
//      {
//         Int32 id1 = -20000;
//         Int32 id2 = -20001;
//
//         points->Add(id1,0,0,NULL);
//
//         CComQIPtr<ILocate> locate(m_CogoModel);
//         locate->ByDistDir(id2,id1,100.00,CComVariant(alignmentDesc.GetInitialDirection()),0.00);
//
//         CComPtr<IPoint2d> pnt1, pnt2;
//         points->get_Item(id1,&pnt1);
//         points->get_Item(id2,&pnt2);
//
//         alignment->put_RefStation(CComVariant(0.00));
//         alignment->AddEx(pnt1);
//         alignment->AddEx(pnt2);
//      }
      //else
      //{
      //}
//   }

   m_bNeedsValidation = false;
}

HRESULT CBridgeGeometryAgent::GetAlignment(CogoObjectID alignmentID,IAlignment** ppAlignment)
{
   CComPtr<IPathCollection> alignments;
   m_CogoModel->get_Alignments(&alignments);

   CComPtr<IPath> path;
   alignments->get_Item(alignmentID,&path);

   CComQIPtr<IAlignment> alignment(path);
   *ppAlignment = alignment;
   (*ppAlignment)->AddRef();
   return S_OK;
}

//
// IAgentEx
//
STDMETHODIMP CBridgeGeometryAgent::SetBroker(IBroker* pBroker)
{
   m_pBroker = pBroker;
   return S_OK;
}

STDMETHODIMP CBridgeGeometryAgent::RegInterfaces()
{
   CComQIPtr<IBrokerInitEx2,&IID_IBrokerInitEx2> pBrokerInit(m_pBroker);

   pBrokerInit->RegInterface(IID_IRoadwayData,         this );
   pBrokerInit->RegInterface(IID_IRoadway,this);
   pBrokerInit->RegInterface(IID_IRoadwayDisplayBuilder,this);
   

   return S_OK;
}

STDMETHODIMP CBridgeGeometryAgent::Init()
{
   AdviseConnectionPoints();
   return S_OK;
}

STDMETHODIMP CBridgeGeometryAgent::Init2()
{
   return S_OK;
}

STDMETHODIMP CBridgeGeometryAgent::Reset()
{
   return S_OK;
}

STDMETHODIMP CBridgeGeometryAgent::ShutDown()
{
   UnadviseConnectionPoints();

   return S_OK;
}

STDMETHODIMP CBridgeGeometryAgent::GetClassID(CLSID* pCLSID)
{
   *pCLSID = CLSID_BridgeGeometryAgent;
   return S_OK;
}

STDMETHODIMP CBridgeGeometryAgent::IntegrateWithUI(BOOL bIntegrate)
{
   if ( bIntegrate )
   {
      IntegrateMenuCommands();
      RegisterViews();
   }
   else
   {
      GET_IFACE(IEAFMainMenu,pMainMenu);
      CEAFMenu* pMenu = pMainMenu->GetMainMenu();
      pMenu->DestroyMenu(m_pAlignmentMenu);

      UnregisterViews();
   }

   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ICommandCallback
/////////////////////////////////////////////////////////////////////////////
BOOL CBridgeGeometryAgent::OnCommandMessage(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
   return m_CmdTarget.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}

BOOL CBridgeGeometryAgent::GetStatusBarMessageString(UINT nID, CString& rMessage) const
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   // load appropriate string
	if ( rMessage.LoadString(nID) )
	{
		// first newline terminates actual string
      rMessage.Replace('\n','\0');
      return TRUE;
	}
	else
	{
		// not found
		TRACE1("Warning: no message line prompt for ID 0x%04X.\n", nID);
      return FALSE;
	}
}

BOOL CBridgeGeometryAgent::GetToolTipMessageString(UINT nID, CString& rMessage) const
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   CString string;
   // load appropriate string
	if ( string.LoadString(nID) )
	{
		// tip is after first newline 
      int pos = string.Find('\n');
      if ( 0 < pos )
         rMessage = string.Mid(pos+1);

      return TRUE;
	}
	else
	{
		// not found
		TRACE1("Warning: no tool tip for ID 0x%04X.\n", nID);
      return FALSE;
	}
}


////////////////////////////////////////////////////////
// IRoadway
void CBridgeGeometryAgent::GetBearing(IDType alignmentID,Float64 station,IDirection** ppBearing)
{
   Validate();
   CComPtr<IAlignment> alignment;
   GetAlignment(alignmentID,&alignment);
   alignment->Bearing(CComVariant(station),ppBearing);
}

void CBridgeGeometryAgent::GetNormal(IDType alignmentID,Float64 station,IDirection** ppBearing)
{
   Validate();
   CComPtr<IAlignment> alignment;
   GetAlignment(alignmentID,&alignment);
   alignment->Normal(CComVariant(station),ppBearing);
}

////////////////////////////////////////////////////////
// IRoadwayData
IndexType CBridgeGeometryAgent::GetAlignmentCount()
{
//   return m_AlignmentMgr.GetAlignmentCount();
   return 0;
}

IndexType CBridgeGeometryAgent::GetAlignmentIndex(IDType alignmentID)
{
   //return m_AlignmentMgr.GetAlignmentIndex(alignmentID);
   return 0;
}

IDType CBridgeGeometryAgent::GetAlignmentID(IndexType alignmentIdx)
{
   //return m_AlignmentMgr.GetAlignmentID(alignmentIdx);
   return 0;
}
//
//void CBridgeGeometryAgent::SetAlignmentDescription(Int32 alignmentID,const CAlignmentDescription& alignmentDesc)
//{
//   //m_AlignmentMgr.SetAlignmentDescription(alignmentID,alignmentDesc);
//}
//
//CAlignmentDescription CBridgeGeometryAgent::GetAlignmentDescription(Int32 alignmentID)
//{
//   //return m_AlignmentMgr.GetAlignmentDescription(alignmentID);
//   return CAlignmentDescription();
//}

////////////////////////////////////////////////////////
// IRoadwayDisplayBuilder
void CBridgeGeometryAgent::BuildRoadwayDisplay(CDisplayView* pView)
{
   pView->EnableToolTips();

   CDManipClientDC dc(pView);

   CComPtr<iDisplayMgr> dispMgr;
   pView->GetDisplayMgr(&dispMgr);

   // Set up the display lists
   CComPtr<iDisplayList> alignment_list;
   ::CoCreateInstance(CLSID_DisplayList,NULL,CLSCTX_ALL,IID_iDisplayList,(void**)&alignment_list);
   alignment_list->SetID(ALIGNMENT_DISPLAY_LIST);
   dispMgr->AddDisplayList(alignment_list);

   CComPtr<iTextBlock> doText;
   doText.CoCreateInstance(CLSID_TextBlock);
   doText->SetText(_T("Text block"));

   CComPtr<IPoint2d> pnt;
   doText->GetPosition(&pnt);
   pnt->Move(5,0);
   doText->SetPosition(pnt);

   alignment_list->AddDisplayObject(doText);

   pView->ScaleToFit();
}
