///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef __CUSTOMSITEH__
#define __CUSTOMSITEH__

#include <mshtmhst.h>
#include <EAF\EAFReportView.h>
#include "EAFHelpWindow.h"

// 
// NOTE: 
// Some of the code in this file is MFC implementation specific.
// Changes in future versions of MFC implementation may require
// the code to be changed. Please check the readme of this
// sample for more information 
// 

class CCustomControlSite:public COleControlSite
{
public:
	CCustomControlSite(COleControlContainer *pCnt);
   void HasEditCommand(BOOL bHasEdit);

protected:
   BOOL m_bHasEdit;

	DECLARE_INTERFACE_MAP();
BEGIN_INTERFACE_PART(DocHostUIHandler, IDocHostUIHandler)
	STDMETHOD(ShowContextMenu)(/* [in] */ DWORD dwID,
            /* [in] */ POINT __RPC_FAR *ppt,
            /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
            /* [in] */ IDispatch __RPC_FAR *pdispReserved) override;
	STDMETHOD(GetHostInfo)( 
            /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo) override;
	STDMETHOD(ShowUI)( 
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
            /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
            /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc) override;
	STDMETHOD(HideUI)(void) override;
	STDMETHOD(UpdateUI)(void) override;
	STDMETHOD(EnableModeless)(/* [in] */ BOOL fEnable) override;
	STDMETHOD(OnDocWindowActivate)(/* [in] */ BOOL fEnable) override;
	STDMETHOD(OnFrameWindowActivate)(/* [in] */ BOOL fEnable) override;
	STDMETHOD(ResizeBorder)( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
            /* [in] */ BOOL fRameWindow) override;
	STDMETHOD(TranslateAccelerator)( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID) override;
	STDMETHOD(GetOptionKeyPath)( 
            /* [out] */ LPOLESTR __RPC_FAR *pchKey,
            /* [in] */ DWORD dw) override;
	STDMETHOD(GetDropTarget)(
            /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget) override;
    STDMETHOD(GetExternal)( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch) override;
    STDMETHOD(TranslateUrl)( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut) override;
    STDMETHOD(FilterDataObject)( 
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet) override;
END_INTERFACE_PART(DocHostUIHandler)
};


class CCustomOccManager :public COccManager
{
public:
	CCustomOccManager(){}
	COleControlSite* CreateSite(COleControlContainer* pCtrlCont)
	{
      int ID = pCtrlCont->m_pWnd->GetDlgCtrlID();
		CCustomControlSite *pSite = new CCustomControlSite(pCtrlCont);
      if ( ID == IDC_HELP_WEB_BROWSER )
      {
         pSite->HasEditCommand(FALSE);
      }
      else if ( ID == IDC_REPORT_WEB_BROWSER )
      {
         CWnd* pParent = pCtrlCont->m_pWnd->GetParent();
         if ( pParent->IsKindOf(RUNTIME_CLASS(CEAFReportView)) )
         {
            CEAFReportView* pReportView = (CEAFReportView*)pParent;
            pSite->HasEditCommand(pReportView->CanEditReport());
         }
         else
         {
            pSite->HasEditCommand(FALSE);
         }
      }

		return pSite;
	}
};

#endif