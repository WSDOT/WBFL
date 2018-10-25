///////////////////////////////////////////////////////////////////////
// Library - Framework for libraries
// Copyright © 1999-2017  Washington State Department of Transportation
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

// LibraryViewer.cpp : Implementation of CLibraryViewer

#include "stdafx.h"
#include "WBFLLibrary.h"
#include "LibraryViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibraryViewer

HRESULT CLibraryViewer::FinalConstruct()
{
   // Load up the tree view image list
   m_hTVImageList = ImageList_Create(16,16,ILC_COLOR4,2,0);
   if ( m_hTVImageList == NULL )
      return E_FAIL;

   HBITMAP hBmp;
   hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_FOLDERCLOSED));
   ImageList_AddMasked(m_hTVImageList,hBmp,RGB(255,0,0));

   hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_FOLDEROPEN));
   ImageList_AddMasked(m_hTVImageList,hBmp,RGB(255,0,0));

   // Create the list view image list
   m_hLVImageList = ImageList_Create(16,16,ILC_COLOR4,2,0);
   if ( m_hLVImageList == NULL )
   {
      // Tree view image list was successfully created.
      // If we have to abort construction, it has to be destroyed.
      ImageList_Destroy(m_hTVImageList);
      return E_FAIL;
   }

   return S_OK;
}

void CLibraryViewer::FinalRelease()
{
   // Clean up the image lists
   ImageList_Destroy(m_hTVImageList);
   m_hTVImageList = 0;

   ImageList_Destroy(m_hLVImageList);
   m_hLVImageList = 0;
}

STDMETHODIMP CLibraryViewer::get_LibraryMgr(ILibraryMgr **pVal)
{
   *pVal = m_LibMgr;
   if ( *pVal )
      (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLibraryViewer::putref_LibraryMgr(ILibraryMgr *newVal)
{
   m_LibMgr = newVal;

   PopulateListViewImageList();
   PopulateTreeControl();

	return S_OK;
}

LRESULT CLibraryViewer::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   // Associated the image list with the tree view
   HWND hWndTree = GetDlgItem(IDC_TREE);
   TreeView_SetImageList(hWndTree,m_hTVImageList,TVSIL_NORMAL);

   // Associated the image list with the list view
   HWND hWndList = GetDlgItem(IDC_LIST);
   ListView_SetImageList(hWndList,m_hLVImageList,LVSIL_NORMAL);

   PopulateTreeControl();

	return 0;
}

void CLibraryViewer::PopulateTreeControl()
{
   USES_CONVERSION;

   HWND hWndTree = GetDlgItem(IDC_TREE);
   TreeView_DeleteAllItems(hWndTree);

   if ( m_LibMgr == 0 )
   {
      TVINSERTSTRUCT insert;
      insert.hParent = NULL;
      insert.hInsertAfter = TVI_LAST;
      insert.item.mask = TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
      insert.item.lParam = -1;
      insert.item.iImage = 0;
      insert.item.iSelectedImage = 1;
      insert.item.pszText = _T("I need a library manager");
      insert.item.cchTextMax = 24;

      TreeView_InsertItem(hWndTree,&insert);
      return;
   }

   // Root = Library Mgr Name
   //    Children = Library Names

   // Add the root  node
   CComBSTR bstrName;
   m_LibMgr->get_Name(&bstrName);

   TVINSERTSTRUCT insert;
   insert.hParent = NULL;
   insert.hInsertAfter = TVI_LAST;
   insert.item.mask = TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
   insert.item.lParam = -1;
   insert.item.iImage = 0;
   insert.item.iSelectedImage = 1;
   insert.item.pszText = OLE2T(bstrName);

   HTREEITEM htiRoot = TreeView_InsertItem(hWndTree,&insert);

   // Add child nodes
   CComPtr<IUnknown> punk;
   m_LibMgr->get__NewEnum(&punk);
   CComQIPtr<IEnumVARIANT> pEnum(punk);
   CComVariant var;
   while ( pEnum->Next(1,&var,NULL) != S_FALSE )
   {
      CComPtr<ILibrary> lib;
      var.pdispVal->QueryInterface(&lib);

      lib->get_Name(&bstrName);

      insert.hParent = htiRoot;
      insert.hInsertAfter = TVI_LAST;
      insert.item.mask = TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
      //insert.item.lParam = i;
      insert.item.iImage = 0;
      insert.item.iSelectedImage = 1;
      insert.item.pszText = OLE2T(bstrName);

      HTREEITEM item = TreeView_InsertItem(hWndTree,&insert);
   }

   TreeView_SelectItem(hWndTree,htiRoot);
}

void CLibraryViewer::PopulateListControl(BSTR bstrLibName)
{
   if ( m_LibMgr == NULL )
      return;

   USES_CONVERSION;
   HWND hWndList = GetDlgItem(IDC_LIST);
   ListView_DeleteAllItems(hWndList);

   CComPtr<ILibrary> lib;
   m_LibMgr->get_Item(bstrLibName,&lib);

   if ( lib == NULL )
      return;

   CComPtr<IUnknown> punk;
   lib->get__NewEnum(&punk);
   CComQIPtr<IEnumVARIANT> pEnum(punk);
   CComVariant var;
   long i = 0;
   while ( pEnum->Next(1,&var,NULL) != S_FALSE )
   {
      CComPtr<ILibraryEntry> entry;
      var.pdispVal->QueryInterface(&entry);

      CComBSTR bstrName;
      entry->get_Name(&bstrName);

      LVITEM item;
      item.mask = LVIF_IMAGE | LVIF_TEXT;
      item.iItem = i;
      item.iSubItem = 0;
      item.pszText = OLE2T(bstrName);
      item.iImage = 1;
//      item.iImage = index;
      int iResult = ListView_InsertItem(hWndList,&item);

      i++;
   }
}

void CLibraryViewer::PopulateListViewImageList()
{
   if ( m_LibMgr == 0 )
      return;

   // Clear out the image list for the list view control
   // and populate it with bitmaps from the libraries
   ImageList_RemoveAll(m_hLVImageList);

   HBITMAP hBmp;
   hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_FOLDERCLOSED));

   ImageList_AddMasked(m_hLVImageList,hBmp,RGB(255,0,0));

//   CComPtr<ILibraryCollection> libs;
//   m_LibMgr->get_Libraries(&libs);
//
//   long count;
//   libs->get_Count(&count);
//   for (long i = 0; i < count; i++)
//   {
//      CComPtr<ILibrary> lib;
//      libs->get_Item(i,&lib);
//
//      HBITMAP hBmp;
//      lib->get_BitmapHandle(&hBmp);
//
//      ImageList_AddMasked(m_hLVImageList,hBmp,RGB(255,0,0));
//   }
}

STDMETHODIMP CLibraryViewer::EditCurSel()
{
   CComBSTR bstrLibName = CurLibName();
   CComBSTR bstrEntryName = CurEntryName();


   CComPtr<ILibrary> lib;
   m_LibMgr->get_Item(bstrLibName,&lib);

   CComPtr<ILibraryEntry> entry;
   lib->get_Item(bstrEntryName,&entry);

   // NOTE: This code is duplicated in the header file.
   CComQIPtr<ISpecifyPropertyPages> spp(entry);
   if ( spp )
   {
      IUnknown* ppunk[1];
      entry->QueryInterface(&ppunk[0]);

      CAUUID pages;
      spp->GetPages(&pages);

      HWND hwnd;
      CComQIPtr<IOleWindow> oleWindow(GetUnknown());
      oleWindow->GetWindow(&hwnd);
      OleCreatePropertyFrame(hwnd,0,0,CComBSTR("Edit Library Entry"),1,ppunk,pages.cElems,pages.pElems,0,0,0);
   }

   return S_OK;
}

LRESULT CLibraryViewer::OnDblClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
   EditCurSel();

   return 0;
}

LRESULT CLibraryViewer::OnRightClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
   CComBSTR bstrLibName = CurLibName();

   CComPtr<ILibrary> lib;
   m_LibMgr->get_Item(bstrLibName,&lib);

   CComPtr<ILibraryEntry> entry;
   lib->CreateEntry(CComBSTR("NewEntry"),&entry);

   return 0;
}

LRESULT CLibraryViewer::OnSelChanged_Tree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
   ATLASSERT(idCtrl == IDC_TREE);
   LPNMTREEVIEW tvnm = (LPNMTREEVIEW)pnmh;

   PopulateListControl(CurLibName());
//   TVITEM item;
//   item.mask = TVIF_PARAM;
//   item.hItem = tvnm->itemNew.hItem;
//   TreeView_GetItem(tvnm->hdr.hwndFrom,&item);
//
//   if ( item.lParam >= 0 )
//   {
//      PopulateListControl(item.lParam);
//   }
//   else
//   {
//      PopulateListControl(-1); // Clears the list control
//   }
   
   bHandled = TRUE;
   return 1;
}

BSTR CLibraryViewer::CurLibName()
{
   HWND hWndTree = GetDlgItem(IDC_TREE);

   // Get the selected tree node to identify the library
   HTREEITEM htiLib = TreeView_GetSelection(hWndTree);
   if ( htiLib == NULL )
      return 0; // Nothing selected

   // Get the item so that we can grab the library name
   TCHAR libName[20];
   TVITEM tvItem;
   tvItem.hItem = htiLib;
   tvItem.mask = TVIF_TEXT;
   tvItem.pszText = libName;
   tvItem.cchTextMax = 20;
   TreeView_GetItem(hWndTree,&tvItem);

   return CComBSTR(libName).Copy();
}

BSTR CLibraryViewer::CurEntryName()
{
   HWND hWndList = GetDlgItem(IDC_LIST);
   int idx = ListView_GetNextItem(hWndList,-1,LVNI_SELECTED);
   if ( idx == -1 )
      return 0;

   TCHAR entryName[20];
   LVITEM lvItem;
   lvItem.iItem = idx;
   lvItem.iSubItem = 0;
   lvItem.mask = LVIF_TEXT;
   lvItem.pszText = entryName;
   lvItem.cchTextMax = 20;
   ListView_GetItem(hWndList,&lvItem);

   return CComBSTR(entryName).Copy();
}

LRESULT CLibraryViewer::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.
   int cx = LOWORD(lParam);
   int cy = HIWORD(lParam);

   int splitter_width = 4;
   int tree_cx = (cx-splitter_width)/2;
   int list_cx = (cx-splitter_width)/2;

   HWND hWndTree = GetDlgItem(IDC_TREE);
   HWND hWndList = GetDlgItem(IDC_LIST);

   ::SetWindowPos(hWndTree, HWND_NOTOPMOST, 0,0,tree_cx,cy,SWP_NOZORDER);
   ::SetWindowPos(hWndList, HWND_NOTOPMOST, tree_cx + splitter_width,0,list_cx,cy,SWP_NOZORDER);

   bHandled = TRUE;

   return 0;
}
