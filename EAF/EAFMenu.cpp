///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// EAFMenu.cpp: implementation of the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFMenu.h>
#include <EAF\EAFPluginCommandManager.h>
#include <EAF\EAFUtilities.h>

#include <algorithm> // for std::find()

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFMenu::CEAFMenu(CWnd* pWnd,CEAFPluginCommandManager* pCmdMgr)
{
   m_bOwnsMenuHandle = false;
   Init(pWnd,pCmdMgr);
}

CEAFMenu::CEAFMenu(HMENU hMenu,CEAFPluginCommandManager* pCmdMgr)
{
   m_Menu.Attach(hMenu);
   m_bOwnsMenuHandle = true;
   
   Init(NULL,pCmdMgr);
}

CEAFMenu::CEAFMenu()
{
   m_pWnd    = NULL;
   m_pCmdMgr = NULL;
   m_bOwnsMenuHandle = false;
}

CEAFMenu::~CEAFMenu()
{
   std::vector<CEAFMenu*>::iterator iter;
   for ( iter = m_Popups.begin(); iter != m_Popups.end(); iter++ )
   {
      CEAFMenu* pPopup = *iter;
      if ( pPopup && 
           ::IsMenu(pPopup->m_Menu) && 
           pPopup->m_Menu.GetSafeHmenu() != NULL && 
           !pPopup->m_bOwnsMenuHandle 
         )
      {
         pPopup->m_Menu.Detach();
      }
      delete pPopup;
   }
}

void CEAFMenu::Init(CWnd* pWnd,CEAFPluginCommandManager* pCmdMgr)
{
   m_pWnd    = pWnd;
   m_pCmdMgr = pCmdMgr;
   CreateSubMenus();
}

CMenu* CEAFMenu::GetMenu()
{
   if ( ::IsMenu( m_Menu.m_hMenu ) )
      return &m_Menu;
   else if ( m_pWnd )
      return m_pWnd->GetMenu();
   else
      return NULL;
}

const CMenu* CEAFMenu::GetMenu() const
{
   if ( ::IsMenu( m_Menu.m_hMenu ) )
      return &m_Menu;
   else if ( m_pWnd )
      return m_pWnd->GetMenu();
   else
      return NULL;
}

UINT CEAFMenu::GetMenuItemCount() const
{
   return (UINT)m_Popups.size();
}

CEAFMenu* CEAFMenu::GetSubMenu(INT pos)
{
   if ( pos < 0 || (INT)m_Popups.size() <= pos )
      return NULL;

   return m_Popups[pos];
}

CEAFMenu* CEAFMenu::CreateContextMenu(CEAFPluginCommandManager* pCmdMgr)
{
   CEAFMenu* pNewMenu = new CEAFMenu;
   pNewMenu->m_Menu.CreatePopupMenu();
   pNewMenu->m_bOwnsMenuHandle = true;
   pNewMenu->Init( NULL, pCmdMgr );

   return pNewMenu;
}

CEAFMenu* CEAFMenu::CreatePopupMenu(INT pos,LPCTSTR lpszName)
{
   CEAFMenu* pNewMenu = new CEAFMenu();
   pNewMenu->m_Menu.CreatePopupMenu();
   pNewMenu->m_bOwnsMenuHandle = true;
   pNewMenu->m_strMenu = lpszName;
   pNewMenu->Init( NULL, m_pCmdMgr );

   CMenu* pMenu = GetMenu();

   INT offset = GetMenuItemOffset();

   if ( pos < 0 )
   {
      m_Popups.push_back(pNewMenu);
      pMenu->AppendMenu(MF_POPUP, (UINT)pNewMenu->m_Menu.m_hMenu, lpszName );
   }
   else
   {
      m_Popups.insert( m_Popups.begin() + pos, pNewMenu );
      pMenu->InsertMenu(pos+offset,MF_BYPOSITION | MF_POPUP, (UINT)pNewMenu->m_Menu.m_hMenu, lpszName );
   }

   if ( m_pWnd )
      m_pWnd->DrawMenuBar();

   return pNewMenu;
}

void CEAFMenu::LoadSubMenu(CEAFMenu* pEAFMenu,CMenu* pMenu,IEAFCommandCallback* pCallback)
{
   UINT nMenuItems = pMenu->GetMenuItemCount();
   for (UINT i = 0; i < nMenuItems; i++ )
   {
      INT nID = pMenu->GetMenuItemID(i);
      if ( nID < 0 )
      {
         CMenu* pSubMenu = pMenu->GetSubMenu(i);
         ASSERT( pSubMenu->GetSafeHmenu() != NULL );

         CString strName;
         pMenu->GetMenuString(i,strName,MF_BYPOSITION);

         CEAFMenu* pEAFSubMenu = CreatePopupMenu(-1,strName);
         LoadSubMenu(pEAFSubMenu,pSubMenu,pCallback); // sub-menu
         m_Popups.push_back(pEAFSubMenu);
      }
      else if ( nID == 0 )
      {
         pEAFMenu->AppendSeparator(); // separator
      }
      else
      {
         CString strMenuItem;
         pMenu->GetMenuString( nID, strMenuItem, MF_BYCOMMAND );
         pEAFMenu->AppendMenu(nID,strMenuItem,pCallback);
      }
   }
}

void CEAFMenu::LoadMenu(CMenu* pMenu,IEAFCommandCallback* pCallback)
{
   UINT nMenuItems = pMenu->GetMenuItemCount();
   for (UINT i = 0; i < nMenuItems; i++ )
   {
      INT nID = pMenu->GetMenuItemID(i);
      if ( nID < 0 )
      {
         CMenu* pSubMenu = pMenu->GetSubMenu(i);
         ASSERT( pSubMenu->GetSafeHmenu() != NULL );

         CString strName;
         pMenu->GetMenuString(i,strName,MF_BYPOSITION);
         if ( strName.GetLength() == 0 )
         {
            LoadMenu(pSubMenu,pCallback);
         }
         else
         {
            CEAFMenu* pEAFSubMenu = CreatePopupMenu(-1,strName);
            m_Popups.push_back(pEAFSubMenu);
            LoadSubMenu(pEAFSubMenu,pSubMenu,pCallback); // sub-menu
         }
      }
      else if ( nID == 0 )
      {
         AppendSeparator(); // separator
      }
      else
      {
         CString strMenuItem;
         pMenu->GetMenuString( nID, strMenuItem, MF_BYCOMMAND );
         AppendMenu(nID,strMenuItem,pCallback);
      }
   }
}

BOOL CEAFMenu::LoadMenu( UINT nIDResource,IEAFCommandCallback* pCallback )
{
   CMenu menu;
   if ( !menu.LoadMenu(nIDResource) )
   {
      ASSERT(FALSE); // did you forget to call    AFX_MANAGE_STATE(AfxGetStaticModuleState());
      return FALSE;
   }

   LoadMenu(&menu,pCallback);
   menu.Detach();
   return TRUE;
}

BOOL CEAFMenu::LoadMenu(LPCTSTR lpszResourceName,IEAFCommandCallback* pCallback )
{
   CMenu menu;
   if ( !menu.LoadMenu(lpszResourceName) )
   {
      ASSERT(FALSE); // did you forget to call    AFX_MANAGE_STATE(AfxGetStaticModuleState());
      return FALSE;
   }

   LoadMenu(&menu,pCallback);
   menu.Detach();
   return TRUE;
}

BOOL CEAFMenu::AppendMenu(UINT nID,LPCTSTR lpszNewItem,IEAFCommandCallback* pCallback)
{
   UINT nCmdID;
   if ( !m_pCmdMgr->AddCommandCallback(nID,pCallback,&nCmdID) )
      return FALSE;

   CMenu* pMenu = GetMenu();
   if ( !pMenu->AppendMenu(MF_STRING,nCmdID,lpszNewItem) )
   {
      m_pCmdMgr->RemoveCommandCallback(nCmdID);
      return FALSE;
   }
   
   m_Popups.push_back(NULL);

   return TRUE;
}

BOOL CEAFMenu::InsertMenu(UINT nPosition, UINT nID, LPCTSTR lpszNewItem, IEAFCommandCallback* pCallback)
{
   UINT nCmdID;
   if ( !m_pCmdMgr->AddCommandCallback(nID,pCallback,&nCmdID) )
      return FALSE;

   CMenu* pMenu = GetMenu();
   if (!pMenu->InsertMenu(nPosition,MF_BYPOSITION | MF_STRING, nCmdID, lpszNewItem) )
   {
      m_pCmdMgr->RemoveCommandCallback(nCmdID);
      return FALSE;
   }
   
   ASSERT(nPosition <= m_Popups.size());
   m_Popups.insert(m_Popups.begin()+nPosition,NULL);

   return TRUE;
}

BOOL CEAFMenu::AppendSeparator(CMenu* pMenu)
{
   return pMenu->AppendMenu(MF_SEPARATOR);
}

BOOL CEAFMenu::AppendSeparator()
{
   CMenu* pMenu = GetMenu();
   return AppendSeparator(pMenu);
}

BOOL CEAFMenu::InsertSeparator(CMenu* pMenu,UINT nPosition,UINT nFlags)
{
   return pMenu->InsertMenu(nPosition,nFlags,MF_SEPARATOR);
}

BOOL CEAFMenu::InsertSeparator(UINT nPosition,UINT nFlags)
{
   CMenu* pMenu = GetMenu();
   return InsertSeparator(pMenu,nPosition,nFlags);
}

BOOL CEAFMenu::RemoveMenu(UINT nPosition,UINT nFlags, IEAFCommandCallback* pCallback)
{
   CMenu* pMenu = GetMenu();

   if ( nFlags == MF_BYCOMMAND)
   {
      // nPosition comes in as a command ID defined by the plugin
      // Convert nPosition into the unique command ID for the application
      m_pCmdMgr->GetMappedCommandID(nPosition,pCallback,&nPosition);

      m_pCmdMgr->RemoveCommandCallback(nPosition);
   }
   else
   {
      UINT menuID = pMenu->GetMenuItemID(nPosition);
      m_pCmdMgr->RemoveCommandCallback(menuID);
   }

   return pMenu->RemoveMenu(nPosition,nFlags);
}

int CEAFMenu::GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags, IEAFCommandCallback* pCallback) const
{
   if ( nFlags == MF_BYCOMMAND )
   {
      // nIDItem comes in as a command ID defined by the plugin
      // Convert nIDItem into the unique command ID for the application
      m_pCmdMgr->GetMappedCommandID(nIDItem,pCallback,&nIDItem);
   }

   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem,lpString,nMaxCount,nFlags);
}

int CEAFMenu::GetMenuString(UINT nIDItem,CString& rString,UINT nFlags, IEAFCommandCallback* pCallback) const
{
   if ( nFlags == MF_BYCOMMAND )
   {
      // nIDItem comes in as a command ID defined by the plugin
      // Convert nIDItem into the unique command ID for the application
      m_pCmdMgr->GetMappedCommandID(nIDItem,pCallback,&nIDItem);
   }

   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem,rString,nFlags);
}


int CEAFMenu::GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags) const
{
   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem,lpString,nMaxCount,nFlags);
}

int CEAFMenu::GetMenuString(UINT nIDItem,CString& rString,UINT nFlags) const
{
   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem,rString,nFlags);
}

BOOL CEAFMenu::SetMenuString(UINT nIDItem,LPTSTR lpString,UINT nFlags)
{
   return SetMenuString(nIDItem,CString(lpString),nFlags);
}

BOOL CEAFMenu::SetMenuString(UINT nIDItem,CString& rString,UINT nFlags)
{
   CMenu* pMenu = GetMenu();
   if ( pMenu )
   {
      MENUITEMINFO menuInfo;
      memset((void*)&menuInfo,0,sizeof(MENUITEMINFO));
      menuInfo.cbSize = sizeof(MENUITEMINFO);
      menuInfo.fMask = MIIM_STRING;
      menuInfo.dwTypeData = rString.GetBuffer();
      menuInfo.cch = rString.GetLength();
      return pMenu->SetMenuItemInfo(nIDItem,&menuInfo,nFlags & MF_BYPOSITION ? TRUE : FALSE);
   }
   return FALSE;
}

BOOL CEAFMenu::SetMenuItemBitmaps(UINT nPosition,UINT nFlags,const CBitmap* pBmpUnchecked,const CBitmap* pBmpChecked, IEAFCommandCallback* pCallback)
{
   CMenu* pMenu = GetMenu();
   if ( nFlags == MF_BYCOMMAND )
      m_pCmdMgr->GetMappedCommandID(nPosition,pCallback,&nPosition);

   return pMenu->SetMenuItemBitmaps(nPosition,nFlags,pBmpUnchecked,pBmpChecked);
}

void CEAFMenu::DestroyMenu(CEAFMenu* pPopupMenu)
{
   CMenu* pMenu = GetMenu();
   UINT nMenus = pMenu->GetMenuItemCount();
   for ( UINT i = 0; i < nMenus; i++ )
   {
      CMenu* pSubMenu = pMenu->GetSubMenu(i);
      if ( pSubMenu && (pSubMenu->m_hMenu == pPopupMenu->m_Menu.m_hMenu) )
      {
         pMenu->DeleteMenu(i,MF_BYPOSITION);

         pPopupMenu->m_Menu.Detach();
         std::vector<CEAFMenu*>::iterator found = std::find(m_Popups.begin(),m_Popups.end(),pPopupMenu);
         ASSERT( found != m_Popups.end() );
         m_Popups.erase(found);
         delete pPopupMenu;
         pPopupMenu = NULL;

         if ( m_pWnd )
            m_pWnd->DrawMenuBar();

         return;
      }
   }
}

UINT CEAFMenu::FindMenuItem(LPCTSTR strTargetMenu)
{
   CMenu* pMenu = GetMenu();

   INT offset = GetMenuItemOffset();

   UINT nItems = pMenu->GetMenuItemCount();
   for ( UINT menuPos = 0; menuPos < nItems; menuPos++ )
   {
      CString strMenu;
      pMenu->GetMenuString(menuPos,strMenu,MF_BYPOSITION);
      if ( strMenu.Compare(strTargetMenu) == 0 )
      {
         return menuPos - offset;
      }
   }

   return -1;
}

UINT CEAFMenu::GetMenuItemID(UINT nPosition,UINT* pOriginalID, IEAFCommandCallback** ppCallback)
{
   // Returns the ID assigned to the actual menu
   // OriginalID is the ID used by the plug-in and callback is the associated callback object
   CMenu* pMenu = GetMenu();
   UINT nMappedID = pMenu->GetMenuItemID(nPosition);
   m_pCmdMgr->GetCommandCallback(nMappedID,pOriginalID,ppCallback);
   return nMappedID; 
}

BOOL CEAFMenu::TrackPopupMenu(UINT nFlags,int x,int y,CWnd* pWnd,LPCRECT lpRect)
{
   CMenu* pMenu = GetMenu();
   if ( pMenu )
      return pMenu->TrackPopupMenu(nFlags,x,y,pWnd,lpRect);

   return FALSE;
}

void CEAFMenu::CreateSubMenus()
{
   CMenu* pMenu = GetMenu();
   if ( !pMenu )
      return;

   UINT nSubMenus = pMenu->GetMenuItemCount(); // number of sub menus (like File, Options, Help)
   for (UINT menuIdx = 0; menuIdx < nSubMenus; menuIdx++ )
   {
      CString strName;
      pMenu->GetMenuString(menuIdx,strName,MF_BYPOSITION);

      // Attempting to detect the System/Window menu. We want to skip this menu
      // Using m_pWnd->GetSystemMenu(TRUE) and m_pWnd->GetSystemMenu(FALSE) and comparing
      // the menu handle to the handle of the current menu and sub menu doesn't work
      //
      // The system menu does not have a name so it returns an empty string... but so
      // do separators.... need to let separators through, but not unnamed menus (hopefully the system menu)
      // pMenu->GetMenuItemID(menuIdx) returns 0 if the menu item is a SEPARATOR
      if ( strName.IsEmpty() && pMenu->GetMenuItemID(menuIdx) != 0)
         continue; 

      CMenu* pSubMenu = pMenu->GetSubMenu(menuIdx);
      if ( pSubMenu )
      {
         if ( pSubMenu->GetSafeHmenu() != NULL )
         {
            CEAFMenu* pEAFSubMenu = new CEAFMenu();
            pEAFSubMenu->m_strMenu = strName;

            pEAFSubMenu->m_bOwnsMenuHandle = false;
            pEAFSubMenu->m_Menu.Attach(pSubMenu->GetSafeHmenu());

            pEAFSubMenu->Init(NULL,m_pCmdMgr);
            m_Popups.push_back(pEAFSubMenu);
         }
         else
         {
            m_Popups.push_back(NULL); // place holder for basic menu item
         }
      }
      else
      {
         m_Popups.push_back(NULL); // place holder for basic menu item
      }
   }
}

INT CEAFMenu::GetMenuItemOffset()
{
   // if the active frame is maximized, the window/system menu for that frame is added to the
   // the menu bar. This offsets all the menu items by one.
   CEAFMainFrame* pMainFrame = EAFGetMainFrame();
   CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
   INT offset = 0;
   if ( pActiveFrame && m_pWnd && pActiveFrame->IsZoomed() )
   {
      offset = 1;
   }

   return offset;
}
