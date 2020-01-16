///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2020  Washington State Department of Transportation
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

// DocTemplateDialog.cpp : implementation file
//
#include "stdafx.h"
#include <mfcTools\DocTemplateDialog.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateDialog dialog

// data for list control
#define NUM_COLUMNS	3

static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("Template"), _T("Size"), _T("Modified")
};

static int _gnColumnFmt[NUM_COLUMNS] = 
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT
};

static int _gnColumnWidth[NUM_COLUMNS] = 
{
	190, 80, 140
};


CDocTemplateDialog::CDocTemplateDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(CDocTemplateDialog::IDD, pParent),
   m_pTabList(0),
   m_pSelectedTabHelper(0),
   m_bOmitDefaultFile(false)
{

	//{{AFX_DATA_INIT(CDocTemplateDialog)
	m_RadioButton = -1;
	//}}AFX_DATA_INIT

   // load up default icons for list boxitems
   CWinApp* papp = AfxGetApp();
   ASSERT(papp);
   HICON hentry = papp->LoadIcon(IDI_TEMPLATE);
   ASSERT(hentry);

   VERIFY(m_FileImages32.Create(32,32,ILC_COLOR,2,1));
   int st = m_FileImages32.Add(hentry);
   ASSERT(st!=-1);

   VERIFY(m_FileImages16.Create(16,16,ILC_COLOR,2,1));
   st = m_FileImages16.Add(hentry);
   ASSERT(st!=-1);
}

CDocTemplateDialog::~CDocTemplateDialog()
{
   // this code has to be here otherwise the imagelist stuff
   // gets very confused about which process it is in. If the
   // call to DeleteImageList is called in the imagelist destructor,
   // it may not be in the right state.
   m_FileImages32.DeleteImageList();
   m_FileImages16.DeleteImageList();
}

void CDocTemplateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDocTemplateDialog)
	DDX_Control(pDX, IDOK, m_OkButton);
	DDX_Control(pDX, IDC_FILE_SELECTED, m_FileSelected);
	DDX_Control(pDX, IDC_FILE_LISTCTRL, m_FileListCtrl);
	DDX_Control(pDX, IDC_FILE_VIEW_TAB, m_TabCtrl);
	DDX_Radio(pDX, IDC_RADIO_LARGE, m_RadioButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDocTemplateDialog, CDialog)
	//{{AFX_MSG_MAP(CDocTemplateDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_FILE_VIEW_TAB, OnSelchangeFileViewTab)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO_LARGE,IDC_RADIO_LIST, OnRadioClicked)
	ON_NOTIFY(NM_CLICK, IDC_FILE_LISTCTRL, OnClickFileListctrl)
	ON_NOTIFY(NM_DBLCLK, IDC_FILE_LISTCTRL, OnDblclkFileListctrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateDialog message handlers

BOOL CDocTemplateDialog::OnInitDialog() 
{

   PRECONDITION(m_pTabList);

   switch( m_ListMode )
   {
   case mfcDocTemplateFinder::LargeIconMode:
      m_RadioButton = 0;
      break;
   
   case mfcDocTemplateFinder::SmallIconMode:
      m_RadioButton = 1;
      break;

   case mfcDocTemplateFinder::ReportMode:
      m_RadioButton = 2;
      break;
   }

	CDialog::OnInitDialog();

   // icons for radio buttons
   CWinApp* papp = AfxGetApp();
   // large
   HICON hentry = papp->LoadIcon(IDI_LARGE_ICON);
   ASSERT(hentry);
   CButton* pbut = (CButton*)GetDlgItem(IDC_RADIO_LARGE);
   ASSERT(pbut);
   pbut->SetIcon(hentry);
   // small
   hentry = papp->LoadIcon(IDI_SMALL_ICON);
   ASSERT(hentry);
   pbut = (CButton*)GetDlgItem(IDC_RADIO_SMALL);
   ASSERT(pbut);
   pbut->SetIcon(hentry);
   // list
   hentry = papp->LoadIcon(IDI_LIST_ICON);
   ASSERT(hentry);
   pbut = (CButton*)GetDlgItem(IDC_RADIO_LIST);
   ASSERT(pbut);
   pbut->SetIcon(hentry);

   // set image list for file list control
   m_FileListCtrl.SetImageList(&m_FileImages32,LVSIL_NORMAL);
   m_FileListCtrl.SetImageList(&m_FileImages16,LVSIL_SMALL ); // small same as large?

   // insert columns in file list control
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(int i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		m_FileListCtrl.InsertColumn(i,&lvc);
	}

   // Set the list view in the proper mode
   UpdateListViewMode();

   // fill tab control
   // list control data items
	TC_ITEM TabCtrlItem;
   int igen=-1;
   int i = 0;
   for(TabListIterator it=m_pTabList->begin(); it!=m_pTabList->end(); it++)
   {
      i++;
      TCHAR buf[MAX_PATH];

      mfcTemplateTabHelper& tab_helper = (*it).second;

      std::vector<mfcTemplateTabHelper::TabDisplayFile> file_list;
      tab_helper.GetFileList(&file_list);
      if ( 0 < file_list.size() )
      {
         if ((*it).first == _T("general") )
         {
            igen = i-1;
         }

         std::_tstring tmp = tab_helper.GetName();
         _tcscpy_s(buf, MAX_PATH, tmp.c_str());
         TabCtrlItem.pszText = buf;
         TabCtrlItem.lParam = (LPARAM)&((*it).first); // store pointer to key
         TabCtrlItem.mask = TCIF_TEXT|TCIF_PARAM;

	      m_TabCtrl.InsertItem( i, &TabCtrlItem);
      }
   }

   ClearSelectedFile();

   if ( m_TabCtrl.GetItemCount() == 0 )
      return TRUE;
	
   // open with the general tab selected
   if ( igen < 0 )
      igen = 0;

   m_TabCtrl.SetCurSel(igen);
   // get tab key from lparam
   TC_ITEM  tab_item;
   tab_item.mask = TCIF_PARAM;
   VERIFY(m_TabCtrl.GetItem(igen,&tab_item));
   std::_tstring* pstr = (std::_tstring*)tab_item.lParam;
   ASSERT(pstr);

   // select this tab for display
   SelectTab(*pstr);

   // Size the tab view to just fit its tabs
   int nTabRows = m_TabCtrl.GetRowCount();
   CRect tab_rect;
   m_TabCtrl.GetItemRect(0,&tab_rect);

   int tab_height = nTabRows*tab_rect.Height();

   CRect tab_client_rect;
   m_TabCtrl.GetClientRect(&tab_client_rect);
   tab_client_rect.bottom = tab_height;
   m_TabCtrl.SetWindowPos(nullptr,0,0,tab_client_rect.Width(),tab_client_rect.Height(),SWP_NOMOVE);

   // Position the list control below the tabs and above the status item
   CRect tab_window_rect;
   m_TabCtrl.GetWindowRect(&tab_window_rect);

   CRect status_window_rect;
   GetDlgItem(IDC_FILE_SELECTED)->GetWindowRect(&status_window_rect);

   CRect list_rect;
   list_rect.left   = tab_window_rect.left;
   list_rect.right  = tab_window_rect.right;
   list_rect.top    = tab_window_rect.bottom;
   list_rect.bottom = status_window_rect.top;

   ScreenToClient(&list_rect);

   m_FileListCtrl.SetWindowPos(&wndTop,list_rect.left,list_rect.top,list_rect.Width(),list_rect.Height(),SWP_SHOWWINDOW);

   return TRUE;  // return TRUE unless you set the focus to a control
     // EXCEPTION: OCX Property Pages should return FALSE
}

void CDocTemplateDialog::SetTabList(TabList* ptab_list)
{

   ASSERT(ptab_list);
   m_pTabList = ptab_list;
}

void CDocTemplateDialog::OnSelchangeFileViewTab(NMHDR* pNMHDR, LRESULT* pResult) 
{

	int nt = m_TabCtrl.GetCurSel();
   if (nt!=-1)
   {
      // get tab key from lparam
      TC_ITEM  tab_item;
      tab_item.mask = TCIF_PARAM;
      VERIFY(m_TabCtrl.GetItem(nt,&tab_item));
      std::_tstring* pstr = (std::_tstring*)tab_item.lParam;
      ASSERT(pstr);

      // select this tab for display
      SelectTab(*pstr);
   }
   else 
      ASSERT(0);
	
	*pResult = 0;
}

void CDocTemplateDialog::SelectTab(const std::_tstring& key)
{
   // fill list control
   m_FileListCtrl.DeleteAllItems();

   TabListIterator it=m_pTabList->find(key);
   ASSERT(it!=m_pTabList->end());

   if (it!=m_pTabList->end())
   {
      // fill list control with file names
      // get pointer to current helper first
      m_pSelectedTabHelper = &((*it).second);
      ASSERT(m_pSelectedTabHelper);

      mfcTemplateTabHelper::TabDisplayFileList file_list;
      m_pSelectedTabHelper->GetFileList(&file_list);

      TCHAR buf[MAX_PATH];
      int i = 0;
      LV_ITEM lvi;
      lvi.mask = LVIF_TEXT | LVIF_IMAGE;
	   lvi.iItem = 0;
	   lvi.iSubItem = 0;
	   lvi.pszText = 0;
	   lvi.iImage = 0;

      // if this is the general tab, put in default file name
      if (_T("general") == key && !m_bOmitDefaultFile)
      {
         _tcscpy_s(buf,MAX_PATH, m_DefaultFile.c_str());
         lvi.pszText = buf;
		   m_FileListCtrl.InsertItem(&lvi);
         i++;
      }


      for(mfcTemplateTabHelper::TabDisplayFileIterator its=file_list.begin(); its!=file_list.end(); its++)
      {
         _tcscpy_s(buf,MAX_PATH,its->m_FileName);

		   lvi.iItem = i;
		   lvi.pszText = buf;

		   m_FileListCtrl.InsertItem(&lvi);
			m_FileListCtrl.SetItemText(i,1,its->m_SizeInBytes);
			m_FileListCtrl.SetItemText(i,2,its->m_LastWriteDate);
         i++;
      }
   }
   // no file selected when new tab is chosen
   ClearSelectedFile();
}

void CDocTemplateDialog::SetIcon(HICON hicon)
{

   VERIFY(m_FileImages32.Remove(0));
   int st = m_FileImages32.Add(hicon);
   ASSERT(st!=-1);

   VERIFY(m_FileImages16.Remove(0));
   st = m_FileImages16.Add(hicon);
   ASSERT(st!=-1);
}

void CDocTemplateDialog::OnRadioClicked(UINT i) 
{
   m_ListMode = mfcDocTemplateFinder::SmallIconMode;
   int chk = GetCheckedRadioButton(IDC_RADIO_LARGE, IDC_RADIO_LIST);
   if (chk == IDC_RADIO_LARGE)
   {
      m_ListMode = mfcDocTemplateFinder::LargeIconMode;
   }
   else if (chk == IDC_RADIO_LIST)
   {
      m_ListMode = mfcDocTemplateFinder::ReportMode;
   }

   UpdateListViewMode();
}

void CDocTemplateDialog::UpdateListViewMode()
{
   DWORD style;
   switch( m_ListMode )
   {
   case mfcDocTemplateFinder::SmallIconMode:
      style = LVS_SMALLICON;
      break;

   case mfcDocTemplateFinder::LargeIconMode:
      style = LVS_ICON;
      break;

   case mfcDocTemplateFinder::ReportMode:
      style = LVS_REPORT;
      break;
   }

	DWORD old_style;
	old_style = GetWindowLong(m_FileListCtrl.m_hWnd, GWL_STYLE);
					
	if ((old_style & LVS_TYPEMASK) != style)
   {
		SetWindowLong(m_FileListCtrl.m_hWnd, GWL_STYLE,
	             		(old_style & ~LVS_TYPEMASK) | style);
   }
}

void CDocTemplateDialog::SetDefaultFile(const std::_tstring& filename)
{
   m_DefaultFile = filename;
}


void CDocTemplateDialog::SetSelectedFile(const std::_tstring& file)
{
   ASSERT(file.size());
   m_OkButton.EnableWindow(TRUE);
   m_CurrentlySelectedFile = file;
   std::_tstring tmp(_T("Selected File: "));

   // deal with default file
   if (file != m_DefaultFile)
   {
      ASSERT(m_pSelectedTabHelper);
      m_CurrentlySelectedFile = std::_tstring(m_pSelectedTabHelper->GetFilePath(m_CurrentlySelectedFile));
      tmp += m_CurrentlySelectedFile;
   }
   else
   {
      tmp += m_DefaultFile;
   }
   m_FileSelected.SetWindowText(tmp.c_str());
}

void CDocTemplateDialog::ClearSelectedFile()
{
   m_OkButton.EnableWindow(FALSE);
   m_CurrentlySelectedFile.erase();
   m_FileSelected.SetWindowText(_T("No File Selected"));
}

std::_tstring CDocTemplateDialog::GetSelectedFile() const 
{
   return m_CurrentlySelectedFile;
}

void CDocTemplateDialog::OnClickFileListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{

   ClearSelectedFile();
   int idx = m_FileListCtrl.GetNextItem(-1,LVNI_SELECTED);

   if ( idx != -1)
   {
      SetSelectedFile(std::_tstring(m_FileListCtrl.GetItemText(idx,0)));
   }

	*pResult = 0;
}

void CDocTemplateDialog::OnDblclkFileListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{

   ClearSelectedFile();
   int idx = m_FileListCtrl.GetNextItem(-1,LVNI_SELECTED);

   if ( idx != -1)
   {
      SetSelectedFile(std::_tstring(m_FileListCtrl.GetItemText(idx,0)));

      // select file and bail
      EndDialog(IDOK);
   }
	
	*pResult = 0;
}

void CDocTemplateDialog::SetListMode(mfcDocTemplateFinder::ListMode mode)
{
   m_ListMode = mode;
}

mfcDocTemplateFinder::ListMode CDocTemplateDialog::GetListMode() const
{
   return m_ListMode;
}
