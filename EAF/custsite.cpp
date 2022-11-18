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



//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=

// 
// NOTE: 
// Some of the code in this file is MFC implementation specific.
// Changes in future versions of MFC implementation may require
// the code to be changed. Please check the readme of this
// sample for more information 
// 
#include "stdafx.h"
#include "resource.h"

#undef AFX_DATA
#define AFX_DATA AFX_DATA_IMPORT

#include <occimpl.h>

#undef AFX_DATA
#define AFX_DATA AFX_DATA_EXPORT

#pragma warning(disable:4192 4278)

#include "custsite.h"
#include <EAF\EAFCustSiteVars.h>
#include <system\tokenizer.h>
#include <Reporter\HtmlHelper.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ------- free functions
enum anchorType {atChapter, atParagraph, atNone};
static anchorType GetAnchorInfo(long i, MSHTML::IHTMLElementCollectionPtr& pcoll, long* pid, CString* ptitle);

BEGIN_INTERFACE_MAP(CCustomControlSite, COleControlSite)
	INTERFACE_PART(CCustomControlSite, IID_IDocHostUIHandler, DocHostUIHandler)
END_INTERFACE_MAP()

CCustomControlSite::CCustomControlSite(COleControlContainer *pCnt) :
COleControlSite(pCnt)
{ 
   m_bHasEdit = TRUE;
}
void CCustomControlSite::HasEditCommand(BOOL bHasEdit)
{
   m_bHasEdit = bHasEdit;
}

ULONG FAR EXPORT  CCustomControlSite::XDocHostUIHandler::AddRef()
{
	METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
	return pThis->ExternalAddRef();
}


ULONG FAR EXPORT  CCustomControlSite::XDocHostUIHandler::Release()
{                            
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

	return pThis->ExternalRelease();
}

HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::QueryInterface(REFIID riid, void **ppvObj)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}

// * CImpIDocHostUIHandler::GetHostInfo
// *
// * Purpose: Called at initialization
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::GetHostInfo( DOCHOSTUIINFO* pInfo )
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

	pInfo->dwFlags = DOCHOSTUIFLAG_NO3DBORDER;
    pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

    return S_OK;
}

// * CImpIDocHostUIHandler::ShowUI
// *
// * Purpose: Called when MSHTML.DLL shows its UI
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::ShowUI(
				DWORD dwID, 
				IOleInPlaceActiveObject * /*pActiveObject*/,
				IOleCommandTarget * pCommandTarget,
				IOleInPlaceFrame* pFrame,
				IOleInPlaceUIWindow * /*pDoc*/)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

	// We've already got our own UI in place so just return S_OK
    return S_OK;
}

// * CImpIDocHostUIHandler::HideUI
// *
// * Purpose: Called when MSHTML.DLL hides its UI
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::HideUI(void)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return S_OK;
}

// * CImpIDocHostUIHandler::UpdateUI
// *
// * Purpose: Called when MSHTML.DLL updates its UI
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::UpdateUI(void)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

	// MFC is pretty good about updating it's UI in it's Idle loop so I don't do anything here
	return S_OK;
}

// * CImpIDocHostUIHandler::EnableModeless
// *
// * Purpose: Called from MSHTML.DLL's IOleInPlaceActiveObject::EnableModeless
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::EnableModeless(BOOL /*fEnable*/)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::OnDocWindowActivate
// *
// * Purpose: Called from MSHTML.DLL's IOleInPlaceActiveObject::OnDocWindowActivate
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::OnDocWindowActivate(BOOL /*fActivate*/)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::OnFrameWindowActivate
// *
// * Purpose: Called from MSHTML.DLL's IOleInPlaceActiveObject::OnFrameWindowActivate
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::OnFrameWindowActivate(BOOL /*fActivate*/)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::ResizeBorder
// *
// * Purpose: Called from MSHTML.DLL's IOleInPlaceActiveObject::ResizeBorder
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::ResizeBorder(
				LPCRECT /*prcBorder*/, 
				IOleInPlaceUIWindow* /*pUIWindow*/,
				BOOL /*fRameWindow*/)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::ShowContextMenu
// *
// * Purpose: Called when MSHTML.DLL would normally display its context menu
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::ShowContextMenu(
				DWORD dwID, 
				POINT* pptPosition,
				IUnknown* pCommandTarget,
				IDispatch* pdispObject)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   // get the document 
	if (pdispObject != nullptr )
	{
      MSHTML::IHTMLElement *pElem;
      HRESULT hr;

      hr = pdispObject->QueryInterface(__uuidof(MSHTML::IHTMLElement)/*IID_IHTMLElement*/, (void**)&pElem);
      if(SUCCEEDED (hr))
      {
         IDispatch* pDispDoc;
         hr = pElem->get_document(&pDispDoc);
         if(SUCCEEDED (hr))
         {
		      MSHTML::IHTMLDocument2* pHTMLDocument;
		      HRESULT hr;
            hr = pDispDoc->QueryInterface( __uuidof(MSHTML::IHTMLDocument2)/*IID_IHTMLDocument2*/, (void**)&pHTMLDocument );
		      if (hr == S_OK)
		      {
               // check to see if any text is selected. If so, use IE's UI instead of our own
			      MSHTML::IHTMLSelectionObjectPtr pSel;
      			pSel = pHTMLDocument->Getselection( );

               _bstr_t bstr;
               bstr = pSel->Gettype();
               CString strTag((TCHAR*)bstr);
               if (strTag=="None") // nothing selected, show our context menu
               {
                  CMenu menu;
	               if (!(menu.CreatePopupMenu()))
	               {
                     ::AfxMessageBox(_T("Could not create CMenu"));
	               }
                  if ( pThis->m_bHasEdit )
                  {
                     menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_EDIT, _T("&Edit") );
                  }
                  menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_FIND, _T("&Find") );
                  menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_PRINT, _T("&Print") );
                  menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_SELECT_ALL, _T("&Select All") );
                  menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_REFRESH, _T("&Refresh") );
#ifdef _DEBUG
                  menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_VIEW_SOURCE, _T("&View Source") );
#endif

                  // create pop up

                  MSHTML::IHTMLElementCollectionPtr pcoll;
                  pcoll = pHTMLDocument->Getanchors();
                  if (pcoll)
                  {
                     CMenu popup;
	                  if (!(popup.CreatePopupMenu()))
	                  {
                        ::AfxMessageBox(_T("Could not create CMenu"));
	                  }

                     long len;
                     len = pcoll->Getlength();
                     long i = 0;
                     while (i<len)
                     {
                        long chid;
                        CString chtitle;
                        anchorType at = GetAnchorInfo(i, pcoll, &chid, &chtitle);
                        if (at==atChapter)
                        {
                           // chapter items
                           bool no_para = true;

                           // next look for titled paragraphs - create submenu if they exist
                           if (i+1<len)
                           {
                              CString partitle;
                              long pid;
                              at = GetAnchorInfo(i+1, pcoll, &pid, &partitle);
                              if(at==atParagraph)
                              {
                                 no_para = false;

                                 CMenu popup2;
	                              if (!(popup2.CreatePopupMenu()))
	                              {
                                    ::AfxMessageBox(_T("Could not create CMenu"));
	                              }

                                 while(at==atParagraph && i<len)
                                 {
                                    popup2.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_TOC+pid, partitle );
                                    i++;
                                    if (i+1<len)
                                       at = GetAnchorInfo(i+1, pcoll, &pid, &partitle);
                                    else
                                       break;
                                 }

                                 popup.AppendMenu( MF_POPUP | MF_ENABLED, (UINT_PTR)popup2.Detach(), chtitle );
                              }
                           }

                           // append chapter menu item as string if no paragraphs
                           if (no_para)
                              popup.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_TOC+chid, chtitle );

                        }

                        i++;
                     }

                     if ( 0 < popup.GetMenuItemCount() )
                     {
                        menu.AppendMenu( MF_SEPARATOR, 0);
                        menu.AppendMenu( MF_POPUP | MF_ENABLED, (UINT_PTR)popup.Detach(), _T("&Table of Contents") );
                     }
                  }

                  //
                  // Wiring is here for Forward and back browser options, but it doesn't work as advertised.
                  // must be a problem with the history list settings. shine it for now.
                  //
                  // menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_VIEW_FORWARD, "&Forward" );
                  // menu.AppendMenu( MF_STRING | MF_ENABLED, CCS_CMENU_BASE+CCS_RB_VIEW_BACK, "&Back" );

                  POINT cpt = *pptPosition;

                  CWnd* pwtop = CWnd::GetActiveWindow(); // cannot call AfxGetMainWnd() here. It will bust menus when in CDialogs
                  CWnd* pwcommand = pwtop;

                  menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, cpt.x, cpt.y, pwcommand );

                  return S_OK; // We've shown our own context menu. MSHTML.DLL will no longer try to show its own.
               }
            }
         }
      }
   }

   return S_FALSE;  // let ie show it's menu.
}

// * CImpIDocHostUIHandler::TranslateAccelerator
// *
// * Purpose: Called from MSHTML.DLL's TranslateAccelerator routines
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::TranslateAccelerator(LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return S_FALSE;
}

// * CImpIDocHostUIHandler::GetOptionKeyPath
// *
// * Purpose: Called by MSHTML.DLL to find where the host wishes to store 
// *	its options in the registry
// *
HRESULT FAR EXPORT  CCustomControlSite::XDocHostUIHandler::GetOptionKeyPath(BSTR* pbstrKey, DWORD)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

	return E_NOTIMPL;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetDropTarget( 
            /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   return E_NOTIMPL;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetExternal( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch)
{
	// return the IDispatch we have for extending the object Model
/*
	IDispatch* pDisp = (IDispatch*)theApp.m_pDispOM;
	pDisp->AddRef();
	*ppDispatch = pDisp;
*/
	*ppDispatch = 0;
    return S_OK;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::TranslateUrl( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return E_NOTIMPL;
}
        
STDMETHODIMP CCustomControlSite::XDocHostUIHandler::FilterDataObject( 
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet)
{
	METHOD_PROLOGUE_(CCustomControlSite, DocHostUIHandler)
   AFX_MANAGE_STATE(AfxGetAppModuleState());

    return E_NOTIMPL;
}

anchorType GetAnchorInfo(long i, MSHTML::IHTMLElementCollectionPtr& pcoll, long* pid, CString* ptitle)
{
   MSHTML::IHTMLElementPtr pel;
   _variant_t iv(i);
   pel = pcoll->item(iv,iv);

   _bstr_t btitle = pel->Gettitle ( );
   CString title((TCHAR*)btitle);
   *ptitle = title;

   _bstr_t bid = pel->Getid( );
   CString cid((TCHAR*)bid);

   // parse id
   CString nid = cid.Right(cid.GetLength()-1);
   WBFL::System::Tokenizer::ParseLong(nid, pid);
   if (*pid < rptHtmlHelper::ParaStart)
      return atChapter;
   else
      return atParagraph;
}