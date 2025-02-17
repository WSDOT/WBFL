///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <EAF\EAFApp.h>
#include <EAF\EAFUtilities.h>
#include "commctrl.h"
#include "BackDoor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CNewProjectDlg dialog

IMPLEMENT_DYNAMIC(CNewProjectDlg, CDialog)

CNewProjectDlg::CNewProjectDlg(CEAFTemplateGroup* pRootTemplateGroup,CWnd* pParent) :
CDialog(CNewProjectDlg::IDD,pParent)
{
   m_pRootTemplateGroup = pRootTemplateGroup;
	m_pSelectedTemplate = nullptr;
   m_pTemplateItem = nullptr;
}

CNewProjectDlg::~CNewProjectDlg()
{
   ::DestroyIcon(m_hDefaultIcon);
   ::DestroyIcon(m_hDefaultSelectedIcon);
}

void CNewProjectDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_PROJECTTYPES, m_ctrlProjectTypes);
   DDX_Control(pDX, IDC_TEMPLATES, m_ctrlTemplates);

   if ( pDX->m_bSaveAndValidate )
   {
      ATLASSERT(m_ctrlTemplates.GetSelectedCount() == 1 );
      POSITION pos = m_ctrlTemplates.GetFirstSelectedItemPosition();
      int selIdx = m_ctrlTemplates.GetNextSelectedItem(pos);
      m_pTemplateItem = (const CEAFTemplateItem*)m_ctrlTemplates.GetItemData(selIdx);
      m_pSelectedTemplate = m_pTemplateItem->GetDocTemplate();
   }

	DDX_Radio(pDX, IDC_LARGE, m_ViewMode);
}

void CNewProjectDlg::SetOKButtonState()
{
   // OK button is only enabled if something in the list control is selected
   GetDlgItem(IDOK)->EnableWindow( (0 == m_ctrlTemplates.GetSelectedCount() ? FALSE : TRUE) );
   if ( !GetDlgItem(IDOK)->IsWindowEnabled() )
   {
      GetDlgItem(IDC_DESCRIPTION)->SetWindowText(_T("Select a project template"));
      GetDlgItem(IDC_DESCRIPTION)->Invalidate();
   }
}

BEGIN_MESSAGE_MAP(CNewProjectDlg, CDialog)
   ON_NOTIFY(TVN_SELCHANGED, IDC_PROJECTTYPES, &CNewProjectDlg::OnProjectTypeSelectionChanged)
   ON_NOTIFY(LVN_ITEMCHANGED, IDC_TEMPLATES, &CNewProjectDlg::OnTemplatesItemChanged)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_LARGE,IDC_SMALL, &CNewProjectDlg::OnViewModeClicked)
   ON_NOTIFY_EX(TTN_NEEDTEXT,0,&CNewProjectDlg::OnToolTipNotify)
   ON_WM_DESTROY()
   ON_NOTIFY(NM_DBLCLK, IDC_TEMPLATES, &CNewProjectDlg::OnTemplatesDblClick)
   ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CNewProjectDlg message handlers
void CNewProjectDlg::AddProjectGroup(HTREEITEM hParent,HTREEITEM hAfter,const CEAFTemplateGroup* pGroup,const CString& strLastSelection, 
                                     bool isInSelectedProject,HTREEITEM* pDefaultItem)
{
   HICON hIcon = pGroup->GetIcon();
   int imageIdx        = (hIcon == nullptr ? m_DefaultIconIdx         : m_ProjectTypeImageList.Add(hIcon));
   int seletedImageIdx = (hIcon == nullptr ? m_DefaultSelectedIconIdx : imageIdx);

   HTREEITEM hGroup = m_ctrlProjectTypes.InsertItem(TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE,pGroup->GetGroupName(),imageIdx,seletedImageIdx,0,0,(LPARAM)(pGroup),hParent,hAfter);

   if (isInSelectedProject && pGroup->GetGroupName() == strLastSelection)
   {
      *pDefaultItem = hGroup;
   }

   IndexType nGroups = pGroup->GetGroupCount();
   for ( IndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
   {
      const CEAFTemplateGroup* p = pGroup->GetGroup(grpIdx);
      AddProjectGroup(hGroup,hGroup,p,strLastSelection, isInSelectedProject, pDefaultItem);
   }
}

BOOL CNewProjectDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   EnableToolTips(TRUE);

   GetDlgItem(IDC_DESCRIPTION)->SetWindowText(_T(""));

   CEAFApp* pApp = EAFGetApp();
   m_ViewMode = pApp->GetProfileInt(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("NewProject_ViewMode"),IDC_LARGE);
   CheckRadioButton(IDC_LARGE,IDC_SMALL,m_ViewMode);
   OnViewModeClicked(m_ViewMode);

   CRect rect;
   GetWindowRect(&rect);
   m_cxMin = rect.Width();
   m_cyMin = rect.Height();

   CButton* pBtn = (CButton*)GetDlgItem(IDC_LARGE);
   pBtn->SetIcon( ::LoadIcon(GetInstanceHandle(),MAKEINTRESOURCE(IDI_LARGEICON)) );

   pBtn = (CButton*)GetDlgItem(IDC_SMALL);
   pBtn->SetIcon( ::LoadIcon(GetInstanceHandle(),MAKEINTRESOURCE(IDI_SMALLICON)) );

   m_TemplateLargeImageList.Create(32, 32, ILC_COLOR16, 2, 2);
   m_TemplateLargeImageList.SetBkColor(m_ctrlTemplates.GetBkColor());

   m_TemplateSmallImageList.Create(16, 16, ILC_COLOR16, 2, 2);
   m_TemplateSmallImageList.SetBkColor(m_ctrlTemplates.GetBkColor());

   m_ctrlTemplates.SetImageList(&m_TemplateLargeImageList,LVSIL_NORMAL);
   m_ctrlTemplates.SetImageList(&m_TemplateSmallImageList,LVSIL_SMALL);
   m_ctrlTemplates.SetExtendedStyle(LVS_EX_LABELTIP);


   m_ProjectTypeImageList.Create(16, 16, ILC_COLOR16, 2, 2);
   m_ProjectTypeImageList.SetBkColor(m_ctrlProjectTypes.GetBkColor());
   m_ctrlProjectTypes.SetImageList(&m_ProjectTypeImageList,LVSIL_NORMAL);

   SHFILEINFO sfi;
   SecureZeroMemory(&sfi,sizeof sfi);
   ::SHGetFileInfo(_T("Doesn't Matter"),FILE_ATTRIBUTE_DIRECTORY,&sfi, sizeof sfi, SHGFI_ICON | SHGFI_USEFILEATTRIBUTES);
   m_hDefaultIcon = sfi.hIcon;
   
   SecureZeroMemory(&sfi,sizeof sfi);
   ::SHGetFileInfo(_T("Doesn't Matter"),FILE_ATTRIBUTE_DIRECTORY,&sfi, sizeof sfi, SHGFI_ICON | SHGFI_USEFILEATTRIBUTES | SHGFI_OPENICON);
   m_hDefaultSelectedIcon = sfi.hIcon;
   
   m_DefaultIconIdx         = m_ProjectTypeImageList.Add(m_hDefaultIcon);
   m_DefaultSelectedIconIdx = m_ProjectTypeImageList.Add(m_hDefaultSelectedIcon);

   CString strLastSelection = pApp->GetProfileString(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("NewProject_LastSelection"));
   CString strLastSelectedApp = pApp->GetProfileString(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("NewProject_LastSelectedApp"));
   HTREEITEM hSelectedItem = TVI_ROOT;

	// add all the CDocTemplates in the project tree by name
   GroupIndexType nGroups = m_pRootTemplateGroup->GetGroupCount();
   for ( GroupIndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
   {
      const CEAFTemplateGroup* pTemplateGroup = m_pRootTemplateGroup->GetGroup(grpIdx);

      CString strTypeName(pTemplateGroup->GetGroupName());

      // Set flag if this was the last selected project app
      bool isSelectedProject(strTypeName == strLastSelectedApp);

      HICON hIcon = pTemplateGroup->GetIcon();
      int imageIdx        = (hIcon == nullptr ? m_DefaultIconIdx         : m_ProjectTypeImageList.Add(hIcon));
      int seletedImageIdx = (hIcon == nullptr ? m_DefaultSelectedIconIdx : imageIdx);

      HTREEITEM hPrevItem = TVI_ROOT;
      hPrevItem = m_ctrlProjectTypes.InsertItem(TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE,strTypeName,imageIdx,seletedImageIdx,0,0,(LPARAM)(pTemplateGroup),TVI_ROOT,hPrevItem);

      if (strTypeName == strLastSelection)
      {
         hSelectedItem = hPrevItem;
      }

      IndexType nGroups = pTemplateGroup->GetGroupCount();
      for ( IndexType grpIdx = 0; grpIdx < nGroups; grpIdx++ )
      {
         const CEAFTemplateGroup* pGroup = pTemplateGroup->GetGroup(grpIdx);
         AddProjectGroup(hPrevItem,hPrevItem,pGroup,strLastSelection,isSelectedProject,&hSelectedItem);
      }
   }

   // sort alphabetically
   m_ctrlProjectTypes.SortChildren(TVI_ROOT);

   // Select one of the tree nodes... the list box will be updated when the selection event fires
   if (hSelectedItem == TVI_ROOT)
   {
      hSelectedItem = m_ctrlProjectTypes.GetNextItem(TVI_ROOT, TVGN_ROOT);
   }
   VERIFY(m_ctrlProjectTypes.SelectItem(hSelectedItem));

   // Expand the selected branch in the tree
   ExpandProjectType(hSelectedItem);

   SetOKButtonState();
   
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewProjectDlg::ExpandProjectType(HTREEITEM hItem)
{
   m_ctrlProjectTypes.Expand(hItem,TVE_EXPAND);
}

void CNewProjectDlg::ExpandProjectTypes()
{
   HTREEITEM hItem = m_ctrlProjectTypes.GetFirstVisibleItem();
   while (hItem )
   {
      ExpandProjectType(hItem);
      hItem = m_ctrlProjectTypes.GetNextVisibleItem(hItem);
   }
}

void CNewProjectDlg::OnProjectTypeSelectionChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
   USES_CONVERSION;

   LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

   if ( pNMTreeView->itemNew.mask & TVIF_PARAM )
   {
      m_ctrlTemplates.DeleteAllItems();

      m_TemplateLargeImageList.SetImageCount(0);
      m_TemplateSmallImageList.SetImageCount(0);

      LPARAM lParam = pNMTreeView->itemNew.lParam;
      const CEAFTemplateGroup* pGroup = (const CEAFTemplateGroup*)lParam;
      IndexType nItems = pGroup->GetItemCount();
      for ( IndexType itemIdx = 0; itemIdx < nItems; itemIdx++ )
      {
         const CEAFTemplateItem* pItem = pGroup->GetItem(itemIdx);

         HICON hIcon = pItem->GetIcon();
         m_TemplateLargeImageList.Add(hIcon == nullptr ? m_hDefaultIcon : hIcon);
         m_TemplateSmallImageList.Add(hIcon == nullptr ? m_hDefaultIcon : hIcon);

         CString itemName = pItem->GetName();
         m_ctrlTemplates.InsertItem(LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE,(int)itemIdx,itemName,0,0,(int)itemIdx,(LPARAM)pItem);
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
      const CEAFTemplateItem* pItem = (const CEAFTemplateItem*)m_ctrlTemplates.GetItemData(itemIdx);
      CString strDescription = pItem->GetDocTemplate()->GetTemplateGroupItemDescription(pItem);

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
	old_style = GetWindowLong(m_ctrlTemplates.m_hWnd, GWL_STYLE);
					
	if ((old_style & LVS_TYPEMASK) != dwStyle)
   {
		SetWindowLong(m_ctrlTemplates.m_hWnd, GWL_STYLE,(old_style & ~LVS_TYPEMASK) | dwStyle);
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
         pTTT->hinst = nullptr;
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
         
         if (cx < m_cxMin)
         {
            rect->right = rect->left + m_cxMin;
         }

         if (cy < m_cyMin)
         {
            rect->bottom = rect->top + m_cyMin;
         }

         return TRUE;
      }
   }

   return CDialog::WindowProc(message,wParam,lParam);
}

void CNewProjectDlg::OnDestroy()
{
   CEAFApp* pApp = EAFGetApp();
   m_ViewMode = GetCheckedRadioButton(IDC_LARGE,IDC_SMALL);
   pApp->WriteProfileInt(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("NewProject_ViewMode"),m_ViewMode);

   HTREEITEM hItem = m_ctrlProjectTypes.GetSelectedItem();
   CString strSelection = m_ctrlProjectTypes.GetItemText(hItem);
   pApp->WriteProfileString(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("NewProject_LastSelection"),strSelection);

   // Walk up tree to find app-level item
   while(true)
   {
      HTREEITEM hparent = m_ctrlProjectTypes.GetParentItem(hItem);
      if (hparent==nullptr)
      {
         // name of app is at top level
         strSelection = m_ctrlProjectTypes.GetItemText(hItem);
         pApp->WriteProfileString(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("NewProject_LastSelectedApp"),strSelection);

         break;
      }
      else
      {
         hItem = hparent;
      }
   }


   // Save the layout of the application window
   WINDOWPLACEMENT wp;
   wp.length = sizeof wp;
   if (GetWindowPlacement(&wp))
   {
      pApp->WriteWindowPlacement(CString((LPCTSTR)IDS_WINDOW_POSITIONS),_T("NewProject"), &wp);
   }

   CDialog::OnDestroy();
}

void CNewProjectDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
   CDialog::OnShowWindow(bShow, nStatus);

   // Restore the layout of the application window
   if (bShow)
   {
      WINDOWPLACEMENT wp;
      if (EAFGetApp()->ReadWindowPlacement(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("NewProject"), &wp))
      {
         //CWnd* pDesktop = GetDesktopWindow();
         //CRect rDesktop;
         //pDesktop->GetWindowRect(&rDesktop); // this is the size of the monitor containing the mouse pointer.... use GetSystemMetrics to get the entire desktop
         //CRect rDesktop(0, 0, GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN)); // this is the size of the virtual screen which may be larger than the monitors (https://docs.microsoft.com/en-us/windows/win32/gdi/the-virtual-screen)
         HMONITOR hMonitor = MonitorFromRect(&wp.rcNormalPosition, MONITOR_DEFAULTTONULL); // get the monitor that has maximum overlap with the dialog rectangle (returns null if none)
         if (hMonitor != NULL)
         {
            // if dialog is within a monitor, set its position... otherwise the default position will be sued
            SetWindowPos(NULL, wp.rcNormalPosition.left, wp.rcNormalPosition.top, wp.rcNormalPosition.right - wp.rcNormalPosition.left, wp.rcNormalPosition.bottom - wp.rcNormalPosition.top, 0);
         }
      }
   }
}

void CNewProjectDlg::OnTemplatesDblClick(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
   if ( 0 <= pNMItemActivate->iItem )
      PostMessage(WM_COMMAND,MAKEWPARAM(IDOK,BN_CLICKED),(LPARAM)GetDlgItem(IDOK)->GetSafeHwnd());

   *pResult = 0;
}
