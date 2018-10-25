///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// NewProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewProjectDlg.h"
#include <EAF\EAFDocTemplate.h>
#include "commctrl.h"
#include "BackDoor.h"
// CNewProjectDlg dialog

static CString strNewDialogSection("NewProjectDialog");

IMPLEMENT_DYNAMIC(CNewProjectDlg, CDialog)

CNewProjectDlg::CNewProjectDlg(CPtrList* pList,CWnd* pParent /*=NULL*/)
	: CDialog(CNewProjectDlg::IDD, pParent)
{
	m_pList = pList;
	m_pSelectedTemplate = NULL;
   m_pTemplateItem = NULL;
}

CNewProjectDlg::~CNewProjectDlg()
{
}

void CNewProjectDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_PROJECTTYPES, m_ProjectTypes);
   DDX_Control(pDX, IDC_TEMPLATES, m_Templates);

   if ( pDX->m_bSaveAndValidate )
   {
      CEAFTemplateGroup* pGroup = NULL;
      m_pTemplateItem = NULL;

      HTREEITEM hTreeItem = m_ProjectTypes.GetSelectedItem();
      if ( hTreeItem != NULL )
      {
         pGroup = (CEAFTemplateGroup*)m_ProjectTypes.GetItemData(hTreeItem);
      }
      m_pSelectedTemplate = pGroup->GetDocTemplate();

      ATLASSERT(m_Templates.GetSelectedCount() == 1 );
      POSITION pos = m_Templates.GetFirstSelectedItemPosition();
      int selIdx = m_Templates.GetNextSelectedItem(pos);
      m_pTemplateItem = (const CEAFTemplateItem*)m_Templates.GetItemData(selIdx);
   }

	DDX_Radio(pDX, IDC_LARGE, m_ViewMode);
}

void CNewProjectDlg::SetOKButtonState()
{
   // OK button is only enabled if something in the list control is selected
   GetDlgItem(IDOK)->EnableWindow( (0 == m_Templates.GetSelectedCount() ? FALSE : TRUE) );
   if ( !GetDlgItem(IDOK)->IsWindowEnabled() )
   {
      GetDlgItem(IDC_DESCRIPTION)->SetWindowText("Select a project template");
      GetDlgItem(IDC_DESCRIPTION)->Invalidate();
   }
}

BEGIN_MESSAGE_MAP(CNewProjectDlg, CDialog)
   ON_NOTIFY(TVN_SELCHANGED, IDC_PROJECTTYPES, &CNewProjectDlg::OnProjectTypeSelectionChanged)
   ON_NOTIFY(LVN_ITEMCHANGED, IDC_TEMPLATES, &CNewProjectDlg::OnTemplatesItemChanged)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_LARGE,IDC_SMALL, &CNewProjectDlg::OnViewModeClicked)
   ON_NOTIFY_EX(TTN_NEEDTEXT,0,&CNewProjectDlg::OnToolTipNotify)
   ON_WM_SIZE()
   ON_WM_DESTROY()
   ON_NOTIFY(NM_DBLCLK, IDC_TEMPLATES, &CNewProjectDlg::OnTemplatesDblClick)
END_MESSAGE_MAP()


// CNewProjectDlg message handlers
void CNewProjectDlg::AddProjectGroup(HTREEITEM hParent,HTREEITEM hAfter,const CEAFTemplateGroup* pGroup)
{
   HTREEITEM hGroup = m_ProjectTypes.InsertItem(TVIF_TEXT | TVIF_PARAM,pGroup->GetGroupName(),0,0,0,0,(LPARAM)(pGroup),hParent,hAfter);
   CollectionIndexType nGroups = pGroup->GetGroupCount();
   for ( CollectionIndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
   {
      const CEAFTemplateGroup* p = pGroup->GetGroup(grpIdx);
      AddProjectGroup(hGroup,hGroup,p);
   }
}

BOOL CNewProjectDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   EnableToolTips(TRUE);

   GetDlgItem(IDC_DESCRIPTION)->SetWindowText("");

   CWinApp* pApp = AfxGetApp();
   m_ViewMode = pApp->GetProfileInt(strNewDialogSection,_T("ViewMode"),IDC_LARGE);
   CheckRadioButton(IDC_LARGE,IDC_SMALL,m_ViewMode);
   OnViewModeClicked(m_ViewMode);

   CRect rect;
   GetWindowRect(&rect);
   m_cxMin = rect.Width();
   m_cyMin = rect.Height();

   int cx = pApp->GetProfileInt(strNewDialogSection,_T("cx"),m_cxMin);
   int cy = pApp->GetProfileInt(strNewDialogSection,_T("cy"),m_cyMin);
   cx = max(m_cxMin,cx);
   cy = max(m_cyMin,cy);

   CButton* pBtn = (CButton*)GetDlgItem(IDC_LARGE);
   pBtn->SetIcon( ::LoadIcon(GetInstanceHandle(),MAKEINTRESOURCE(IDI_LARGEICON)) );

   pBtn = (CButton*)GetDlgItem(IDC_SMALL);
   pBtn->SetIcon( ::LoadIcon(GetInstanceHandle(),MAKEINTRESOURCE(IDI_SMALLICON)) );

   m_TemplateLargeImageList.Create(32, 32, ILC_COLOR, 2, 2);
   m_TemplateLargeImageList.SetBkColor(m_Templates.GetBkColor());

   m_TemplateSmallImageList.Create(16, 16, ILC_COLOR, 2, 2);
   m_TemplateSmallImageList.SetBkColor(m_Templates.GetBkColor());

   m_Templates.SetImageList(&m_TemplateLargeImageList,LVSIL_NORMAL);
   m_Templates.SetImageList(&m_TemplateSmallImageList,LVSIL_SMALL);
   m_Templates.SetExtendedStyle(LVS_EX_LABELTIP);

   POSITION pos = m_pList->GetHeadPosition();
	// add all the CDocTemplates in the project tree by name
   int idx = 0;
	while (pos != NULL)
	{
		CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)m_pList->GetNext(pos);
		ASSERT_KINDOF(CEAFDocTemplate, pTemplate);

      HTREEITEM hPrevItem = TVI_ROOT;

		CString strTypeName;
		if (pTemplate->GetDocString(strTypeName, CDocTemplate::fileNewName) && !strTypeName.IsEmpty())
		{
         const CEAFTemplateGroup* pTemplateGroup = pTemplate->GetTemplateGroup();
         hPrevItem = m_ProjectTypes.InsertItem(TVIF_TEXT | TVIF_PARAM,strTypeName,0,0,0,0,(LPARAM)(pTemplateGroup),TVI_ROOT,hPrevItem);

         CollectionIndexType nGroups = pTemplateGroup->GetGroupCount();
         for ( CollectionIndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
         {
            const CEAFTemplateGroup* pGroup = pTemplateGroup->GetGroup(grpIdx);
            AddProjectGroup(hPrevItem,hPrevItem,pGroup);
         }
      }

      idx++;
	}


   // Select one of the tree nodes... the list box will be updated when the selection event fires
   HTREEITEM hItem = m_ProjectTypes.GetNextItem(TVI_ROOT, TVGN_ROOT);
   m_ProjectTypes.SelectItem(hItem);


   // Expand the entire tree 
   ExpandProjectTypes(hItem);

   SetOKButtonState();

   SetWindowPos(NULL,0,0,cx,cy,SWP_NOMOVE); // restore original dialog size
   
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewProjectDlg::ExpandProjectTypes(HTREEITEM hRoot)
{
   m_ProjectTypes.Expand(hRoot,TVE_EXPAND);

   HTREEITEM hChild = m_ProjectTypes.GetNextItem(hRoot,TVGN_CHILD);
   if ( hChild )
   {
      m_ProjectTypes.Expand(hChild,TVE_EXPAND);
      ExpandProjectTypes(hChild);
   }

   HTREEITEM hSibling = m_ProjectTypes.GetNextItem(hRoot,TVGN_NEXT);
   while ( hSibling )
   {
      m_ProjectTypes.Expand(hSibling,TVE_EXPAND);
      hSibling = m_ProjectTypes.GetNextItem(hSibling,TVGN_NEXT);
   }
}

void CNewProjectDlg::OnProjectTypeSelectionChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
   USES_CONVERSION;

   LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

   if ( pNMTreeView->itemNew.mask & TVIF_PARAM )
   {
      m_Templates.DeleteAllItems();

      m_TemplateLargeImageList.SetImageCount(0);
      m_TemplateSmallImageList.SetImageCount(0);

      LPARAM lParam = pNMTreeView->itemNew.lParam;
      const CEAFTemplateGroup* pGroup = (const CEAFTemplateGroup*)lParam;
      CollectionIndexType nItems = pGroup->GetItemCount();
      for ( CollectionIndexType itemIdx = 0; itemIdx < nItems; itemIdx++ )
      {
         const CEAFTemplateItem* pItem = pGroup->GetItem(itemIdx);

         HICON hIcon = pItem->GetIcon();
         m_TemplateLargeImageList.Add(hIcon);
         m_TemplateSmallImageList.Add(hIcon);

         CString itemName = pItem->GetName();
         m_Templates.InsertItem(LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE,itemIdx,itemName,0,0,itemIdx,(LPARAM)pItem);
      }
   }

   SetOKButtonState();

   *pResult = 0;
}

void CNewProjectDlg::OnTemplatesItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
   if ( pNMLV->uNewState & LVIS_SELECTED )
   {
      int itemIdx = pNMLV->iItem;
      const CEAFTemplateItem* pItem = (const CEAFTemplateItem*)m_Templates.GetItemData(itemIdx);

      HTREEITEM hTreeItem = m_ProjectTypes.GetSelectedItem();
      CEAFTemplateGroup* pGroup = (CEAFTemplateGroup*)m_ProjectTypes.GetItemData(hTreeItem);
      CString strDescription = pGroup->GetDocTemplate()->GetTemplateGroupItemDescription(pItem);

      GetDlgItem(IDC_DESCRIPTION)->SetWindowText(strDescription);
   }

   SetOKButtonState();

   *pResult = 0;
}

void CNewProjectDlg::OnViewModeClicked(UINT i)
{
   DWORD dwStyle;
   if (i == IDC_LARGE)
   {
      dwStyle = LVS_ICON;
   }
   else
   {
      dwStyle = LVS_SMALLICON;
   }

	DWORD old_style;
	old_style = GetWindowLong(m_Templates.m_hWnd, GWL_STYLE);
					
	if ((old_style & LVS_TYPEMASK) != dwStyle)
   {
		SetWindowLong(m_Templates.m_hWnd, GWL_STYLE,(old_style & ~LVS_TYPEMASK) | dwStyle);
   }
}

BOOL CNewProjectDlg::OnToolTipNotify(UINT id,NMHDR* pNMHDR, LRESULT* pResult)
{
   TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
   HWND hwndTool = (HWND)pNMHDR->idFrom;
   if ( pTTT->uFlags & TTF_IDISHWND )
   {
      // idFrom is actually HWND of tool
      UINT nID = ::GetDlgCtrlID(hwndTool);
      BOOL bShowTip = false;
      switch(nID)
      {
      case IDC_LARGE:
         m_strToolTipText = "Large Icons";
         bShowTip = true;
         break;

       case IDC_SMALL:
         m_strToolTipText = "Small Icons";
         bShowTip = true;
         break;

       default:
         return FALSE;
      }

      if ( bShowTip )
      {
         //::SendMessage(pNMHDR->hwndFrom,TTM_SETMAXTIPWIDTH,0,300); // makes it a multi-line tooltip
         pTTT->lpszText = m_strToolTipText.LockBuffer();
         pTTT->hinst = NULL;
         return TRUE;
      }
      else
      {
         return FALSE;
      }
   }

   return FALSE;
}

LRESULT CNewProjectDlg::WindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
   // prevent the dialog from getting smaller than the original size
   if ( message == WM_SIZING )
   {
      LPRECT rect = (LPRECT)lParam;
      int cx = rect->right - rect->left;
      int cy = rect->bottom - rect->top;

      if ( cx < m_cxMin || cy < m_cyMin )
      {
         // prevent the dialog from moving right or down
         if ( wParam == WMSZ_BOTTOMLEFT ||
              wParam == WMSZ_LEFT       ||
              wParam == WMSZ_TOP        ||
              wParam == WMSZ_TOPLEFT    ||
              wParam == WMSZ_TOPRIGHT )
         {
            CRect r;
            GetWindowRect(&r);
            rect->left = r.left;
            rect->top  = r.top;
         }
         
         if ( cx < m_cxMin )
            rect->right = rect->left + m_cxMin;

         if ( cy < m_cyMin )
            rect->bottom = rect->top + m_cyMin;

         return TRUE;
      }
   }

   return CDialog::WindowProc(message,wParam,lParam);
}

void CNewProjectDlg::OnSize(UINT nType, int cx, int cy)
{
   CDialog::OnSize(nType, cx, cy);

   CWnd* pOK     = GetDlgItem(IDOK);
   CWnd* pCancel = GetDlgItem(IDCANCEL);
   CWnd* pDesc   = GetDlgItem(IDC_DESCRIPTION);
   CWnd* pLarge  = GetDlgItem(IDC_LARGE);
   CWnd* pSmall  = GetDlgItem(IDC_SMALL);

   if ( pOK == NULL || pCancel == NULL || pDesc == NULL)
      return;

   CRect rCancel, rOK, rDesc, rLarge, rSmall, rProjects, rTemplates;
   pCancel->GetWindowRect(&rCancel);
   pOK->GetWindowRect(&rOK);
   pDesc->GetWindowRect(&rDesc);
   pLarge->GetWindowRect(&rLarge);
   pSmall->GetWindowRect(&rSmall);
   m_ProjectTypes.GetWindowRect(&rProjects);
   m_Templates.GetWindowRect(&rTemplates);

   ScreenToClient(&rCancel);
   ScreenToClient(&rOK);
   ScreenToClient(&rDesc);
   ScreenToClient(&rLarge);
   ScreenToClient(&rSmall);
   ScreenToClient(&rProjects);
   ScreenToClient(&rTemplates);

   // Convert a 7du x 7du rect into pixels
   CRect sizeRect(0,0,7,7);
   MapDialogRect(&sizeRect);

   POINT ptOffset;
   ptOffset.x = cx - rCancel.right - sizeRect.Width();
   ptOffset.y = cy - rCancel.bottom - sizeRect.Height();

   // OK and Cancel, translate x and y
   rCancel.OffsetRect(ptOffset);
   rOK.OffsetRect(ptOffset);

   // Description: translate y, stretch x
   rDesc.top    += ptOffset.y;
   rDesc.bottom += ptOffset.y;
   rDesc.right  += ptOffset.x;

   // Large and small: translate x
   rLarge.left  += ptOffset.x;
   rLarge.right += ptOffset.x;

   rSmall.left  += ptOffset.x;
   rSmall.right += ptOffset.x;

   // Projects: stretch y
   rProjects.bottom += ptOffset.y;

   // Templates: stretch x, stetch y
   rTemplates.right  += ptOffset.x;
   rTemplates.bottom += ptOffset.y;

   // move OK and Cancel
   pOK->SetWindowPos(NULL,rOK.left,rOK.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
   pCancel->SetWindowPos(NULL,rCancel.left,rCancel.top,0,0,SWP_NOSIZE | SWP_NOZORDER);

   // move and stretch horizontally Description
   pDesc->SetWindowPos(NULL,rDesc.left,rDesc.top,rDesc.Width(),rDesc.Height(),SWP_NOZORDER);

   pLarge->SetWindowPos(NULL,rLarge.left,rLarge.top,rLarge.Width(),rLarge.Height(),SWP_NOZORDER);
   pSmall->SetWindowPos(NULL,rSmall.left,rSmall.top,rSmall.Width(),rSmall.Height(),SWP_NOZORDER);

   m_ProjectTypes.SetWindowPos(NULL,rProjects.left,rProjects.top,rProjects.Width(),rProjects.Height(),SWP_NOZORDER);
   m_Templates.SetWindowPos(NULL,rTemplates.left,rTemplates.top,rTemplates.Width(),rTemplates.Height(),SWP_NOZORDER);

   Invalidate();
}

void CNewProjectDlg::OnDestroy()
{
   CWinApp* pApp = AfxGetApp();
   m_ViewMode = GetCheckedRadioButton(IDC_LARGE,IDC_SMALL);
   pApp->WriteProfileInt(strNewDialogSection,_T("ViewMode"),m_ViewMode);

   CRect rect;
   GetClientRect(&rect);
   pApp->WriteProfileInt(strNewDialogSection,_T("cx"),rect.Width());
   pApp->WriteProfileInt(strNewDialogSection,_T("cy"),rect.Height());

   CDialog::OnDestroy();
}

void CNewProjectDlg::OnTemplatesDblClick(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
   if ( 0 <= pNMItemActivate->iItem )
      PostMessage(WM_COMMAND,MAKEWPARAM(IDOK,BN_CLICKED),(LPARAM)GetDlgItem(IDOK)->GetSafeHwnd());

   *pResult = 0;
}
