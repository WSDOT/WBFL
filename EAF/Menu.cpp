///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// EAFMenu.cpp: implementation of the Menu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\Menu.h>
#include <EAF\PluginCommandManager.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFChildFrame.h>

#include <algorithm> // for std::find()

using namespace WBFL::EAF;

Menu::Menu(CWnd* pWnd,std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr)
{
   m_bOwnsMenuHandle = false;
   Init(pWnd,pCmdMgr);
}

Menu::Menu(HMENU hMenu, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr)
{
   m_Menu.Attach(hMenu);
   m_bOwnsMenuHandle = true;
   
   Init(nullptr,pCmdMgr);
}

Menu::~Menu()
{
   for(auto& popup : m_Popups)
   {
      if ( popup && 
           ::IsMenu(popup->m_Menu) && 
           popup->m_Menu.GetSafeHmenu() != nullptr && 
           !popup->m_bOwnsMenuHandle 
         )
      {
         popup->m_Menu.Detach();
      }
   }
}

void Menu::Init(CWnd* pWnd, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr)
{
   m_pWnd    = pWnd;
   m_pCmdMgr = pCmdMgr;
   CreateSubMenus();
}

CMenu* Menu::GetMenu()
{
   if ( ::IsMenu( m_Menu.m_hMenu ) )
      return &m_Menu;
   else if ( m_pWnd )
      return m_pWnd->GetMenu();
   else
      return nullptr;
}

const CMenu* Menu::GetMenu() const
{
   if ( ::IsMenu( m_Menu.m_hMenu ) )
      return &m_Menu;
   else if ( m_pWnd )
      return m_pWnd->GetMenu();
   else
      return nullptr;
}

UINT Menu::GetMenuItemCount() const
{
   return (UINT)m_Popups.size();
}

std::shared_ptr<Menu> Menu::GetSubMenu(INT pos)
{
   if ( pos < 0 || (INT)m_Popups.size() <= pos )
      return nullptr;

   return m_Popups[pos];
}

std::shared_ptr<Menu> Menu::CreateMenu(CWnd* pWnd, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr)
{
   return std::shared_ptr<Menu>(new Menu(pWnd, pCmdMgr));
}

std::shared_ptr<Menu> Menu::CreateMenu(HMENU hMenu, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr)
{
   return std::shared_ptr<Menu>(new Menu(hMenu, pCmdMgr));
}

std::shared_ptr<Menu> Menu::CreateContextMenu(std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr)
{
   auto newMenu = std::shared_ptr<Menu>(new Menu());
   newMenu->m_Menu.CreatePopupMenu();
   newMenu->m_bOwnsMenuHandle = true;
   newMenu->Init( nullptr, pCmdMgr );
   return newMenu;
}

std::shared_ptr<Menu> Menu::CreatePopupMenu(INT pos,LPCTSTR lpszName)
{
   auto newMenu = std::shared_ptr<Menu>(new Menu());
   newMenu->m_Menu.CreatePopupMenu();
   newMenu->m_bOwnsMenuHandle = true;
   newMenu->m_strMenu = lpszName;
   newMenu->Init( nullptr, m_pCmdMgr );

   CMenu* pMenu = GetMenu();

   INT offset = GetMenuItemOffset();

   if ( pos < 0 )
   {
      m_Popups.push_back(newMenu);
      pMenu->AppendMenu(MF_POPUP, (UINT_PTR)newMenu->m_Menu.m_hMenu, lpszName );
   }
   else
   {
      pMenu->InsertMenu(pos+offset,MF_BYPOSITION | MF_POPUP, (UINT_PTR)newMenu->m_Menu.m_hMenu, lpszName );
      if ( 0 < pos )
      {
         CString strMenu;
         pMenu->GetMenuString(pos+offset-1,strMenu,MF_BYPOSITION);

         auto iter(m_Popups.begin());
         auto end(m_Popups.end());
         for ( ; iter != end; iter++ )
         {
            auto pPopupMenu = *iter;
            if ( pPopupMenu->m_strMenu.Compare(strMenu) == 0 )
            {
               m_Popups.insert(iter+1,newMenu);
               break;
            }
         }
      }
      else
      {
         m_Popups.insert( m_Popups.begin() + pos, newMenu );
      }
   }

   if ( m_pWnd )
      m_pWnd->DrawMenuBar();

   return newMenu;
}

void Menu::LoadSubMenu(std::shared_ptr<Menu> pEAFMenu, CMenu* pMenu, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   UINT nMenuItems = pMenu->GetMenuItemCount();
   for (UINT i = 0; i < nMenuItems; i++)
   {
      INT nID = pMenu->GetMenuItemID(i);
      if (nID < 0)
      {
         CMenu* pSubMenu = pMenu->GetSubMenu(i);
         ASSERT(pSubMenu->GetSafeHmenu() != nullptr);

         CString strName;
         pMenu->GetMenuString(i, strName, MF_BYPOSITION);

         auto pEAFSubMenu = CreatePopupMenu(-1, strName);
         LoadSubMenu(pEAFSubMenu, pSubMenu, pCallback); // sub-menu
         m_Popups.push_back(pEAFSubMenu);
      }
      else if (nID == 0)
      {
         pEAFMenu->AppendSeparator(); // separator
      }
      else
      {
         CString strMenuItem;
         pMenu->GetMenuString(nID, strMenuItem, MF_BYCOMMAND);
         pEAFMenu->AppendMenu(nID, strMenuItem, pCallback);
      }
   }
}

void Menu::LoadMenu(CMenu* pMenu, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   UINT nMenuItems = pMenu->GetMenuItemCount();
   for (UINT i = 0; i < nMenuItems; i++)
   {
      INT nID = pMenu->GetMenuItemID(i);
      if (nID < 0)
      {
         CMenu* pSubMenu = pMenu->GetSubMenu(i);
         ASSERT(pSubMenu->GetSafeHmenu() != nullptr);

         CString strName;
         pMenu->GetMenuString(i, strName, MF_BYPOSITION);
         if (strName.GetLength() == 0)
         {
            LoadMenu(pSubMenu, pCallback);
         }
         else
         {
            auto pEAFSubMenu = CreatePopupMenu(-1, strName);
            m_Popups.push_back(pEAFSubMenu);
            LoadSubMenu(pEAFSubMenu, pSubMenu, pCallback); // sub-menu
         }
      }
      else if (nID == 0)
      {
         AppendSeparator(); // separator
      }
      else
      {
         CString strMenuItem;
         pMenu->GetMenuString(nID, strMenuItem, MF_BYCOMMAND);
         AppendMenu(nID, strMenuItem, pCallback);
      }
   }
}

BOOL Menu::LoadMenu(UINT nIDResource, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   CMenu menu;
   if (!menu.LoadMenu(nIDResource))
   {
      ASSERT(FALSE); // did you forget to call    AFX_MANAGE_STATE(AfxGetStaticModuleState());
      return FALSE;
   }

   LoadMenu(&menu, pCallback);
   menu.Detach();
   return TRUE;
}

BOOL Menu::LoadMenu(LPCTSTR lpszResourceName, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   CMenu menu;
   if (!menu.LoadMenu(lpszResourceName))
   {
      ASSERT(FALSE); // did you forget to call    AFX_MANAGE_STATE(AfxGetStaticModuleState());
      return FALSE;
   }

   LoadMenu(&menu, pCallback);
   menu.Detach();
   return TRUE;
}

BOOL Menu::AppendMenu(UINT nID, LPCTSTR lpszNewItem, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(nID, pCallback);
   if (!bSuccess)
      return FALSE;

   CMenu* pMenu = GetMenu();
   if (!pMenu->AppendMenu(MF_STRING, nCmdID, lpszNewItem))
   {
      m_pCmdMgr->RemoveCommandCallback(nCmdID);
      return FALSE;
   }

   m_Popups.push_back(nullptr);

   return TRUE;
}

BOOL Menu::InsertMenu(UINT nPosition, UINT nID, LPCTSTR lpszNewItem, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(nID, pCallback);
   if (!bSuccess)
      return FALSE;

   CMenu* pMenu = GetMenu();
   if (!pMenu->InsertMenu(nPosition, MF_BYPOSITION | MF_STRING, nCmdID, lpszNewItem))
   {
      m_pCmdMgr->RemoveCommandCallback(nCmdID);
      return FALSE;
   }

   ASSERT(nPosition <= m_Popups.size());
   m_Popups.insert(m_Popups.begin() + nPosition, nullptr);

   return TRUE;
}

BOOL Menu::AppendSeparator(CMenu* pMenu)
{
   return pMenu->AppendMenu(MF_SEPARATOR);
}

BOOL Menu::AppendSeparator()
{
   CMenu* pMenu = GetMenu();
   return AppendSeparator(pMenu);
}

BOOL Menu::InsertSeparator(CMenu* pMenu,UINT nPosition,UINT nFlags)
{
   return pMenu->InsertMenu(nPosition,nFlags,MF_SEPARATOR);
}

BOOL Menu::InsertSeparator(UINT nPosition,UINT nFlags)
{
   CMenu* pMenu = GetMenu();
   return InsertSeparator(pMenu,nPosition,nFlags);
}

BOOL Menu::RemoveMenu(UINT nPosition, UINT nFlags, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   CMenu* pMenu = GetMenu();

   INT offset = GetMenuItemOffset();
   nPosition += offset;

   if (nFlags == MF_BYCOMMAND)
   {
      // nPosition comes in as a command ID defined by the plugin
      // Convert nPosition into the unique command ID for the application
      BOOL bSuccess;
      std::tie(bSuccess,nPosition) = m_pCmdMgr->GetMappedCommandID(nPosition, pCallback);
      CHECK(bSuccess);

      m_pCmdMgr->RemoveCommandCallback(nPosition);
   }
   else
   {
      UINT menuID = pMenu->GetMenuItemID(nPosition);
      m_pCmdMgr->RemoveCommandCallback(menuID);
   }

   return pMenu->RemoveMenu(nPosition, nFlags);
}

int Menu::GetMenuString(UINT nIDItem, LPTSTR lpString, int nMaxCount, UINT nFlags, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const
{
   if (nFlags == MF_BYCOMMAND)
   {
      // nIDItem comes in as a command ID defined by the plugin
      // Convert nIDItem into the unique command ID for the application
      BOOL bSuccess;
      std::tie(bSuccess,nIDItem) = m_pCmdMgr->GetMappedCommandID(nIDItem, pCallback);
      CHECK(bSuccess);
   }

   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem, lpString, nMaxCount, nFlags);
}

int Menu::GetMenuString(UINT nIDItem, CString& rString, UINT nFlags, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const
{
   if (nFlags == MF_BYCOMMAND)
   {
      // nIDItem comes in as a command ID defined by the plugin
      // Convert nIDItem into the unique command ID for the application
      BOOL bSuccess;
      std::tie(bSuccess,nIDItem) = m_pCmdMgr->GetMappedCommandID(nIDItem, pCallback);
      CHECK(bSuccess);
   }

   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem, rString, nFlags);
}

int Menu::GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags) const
{
   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem,lpString,nMaxCount,nFlags);
}

int Menu::GetMenuString(UINT nIDItem,CString& rString,UINT nFlags) const
{
   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuString(nIDItem,rString,nFlags);
}

BOOL Menu::SetMenuString(UINT nIDItem,LPTSTR lpString,UINT nFlags)
{
   CString str(lpString);
   return SetMenuString(nIDItem,str,nFlags);
}

BOOL Menu::SetMenuString(UINT nIDItem, CString& rString,UINT nFlags)
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

BOOL Menu::SetMenuItemBitmaps(UINT nPosition, UINT nFlags, const CBitmap* pBmpUnchecked, const CBitmap* pBmpChecked, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   CMenu* pMenu = GetMenu();
   if (nFlags == MF_BYCOMMAND)
   {
      BOOL bSuccess;
      std::tie(bSuccess,nPosition) = m_pCmdMgr->GetMappedCommandID(nPosition, pCallback);
      CHECK(bSuccess);
   }

   return pMenu->SetMenuItemBitmaps(nPosition, nFlags, pBmpUnchecked, pBmpChecked);
}

void Menu::DestroyMenu(std::shared_ptr<Menu> pPopupMenu)
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
         auto found = std::find(m_Popups.begin(),m_Popups.end(),pPopupMenu);
         ASSERT( found != m_Popups.end() );
         m_Popups.erase(found);
         pPopupMenu = nullptr;

         if ( m_pWnd )
            m_pWnd->DrawMenuBar();

         return;
      }
   }
}

UINT Menu::FindMenuItem(LPCTSTR strTargetMenu)
{
   CMenu* pMenu = GetMenu();

   CString strTargetMenuItem(strTargetMenu);
   strTargetMenuItem.Remove(L'&');

   INT offset = GetMenuItemOffset();
   UINT nItems = pMenu->GetMenuItemCount();
   for ( UINT menuPos = 0; menuPos < nItems; menuPos++ )
   {
      CString strMenu;
      pMenu->GetMenuString(menuPos,strMenu,MF_BYPOSITION);
      strMenu.Remove(L'&');
      int pos = strMenu.Find(_T("\t"));
      if (pos != -1)
      {
         strMenu = strMenu.Mid(0, pos);
      }
      if ( strMenu.Compare(strTargetMenuItem) == 0 )
      {
         return menuPos - offset;
      }
   }

   return -1;
}

std::tuple<UINT,UINT,std::shared_ptr<WBFL::EAF::ICommandCallback>> Menu::GetMenuItemID(UINT nPosition)
{
   // Returns the ID assigned to the actual menu
   // OriginalID is the ID used by the plug-in and callback is the associated callback object
   CMenu* pMenu = GetMenu();
   UINT nMappedID = pMenu->GetMenuItemID(nPosition);
   auto [bSuccess,nCmdID,callback] = m_pCmdMgr->GetCommandCallback(nMappedID);
   CHECK(bSuccess);
   return std::make_tuple(nMappedID,nCmdID,callback);
}

BOOL Menu::TrackPopupMenu(UINT nFlags,int x,int y,CWnd* pWnd,LPCRECT lpRect)
{
   CMenu* pMenu = GetMenu();
   if ( pMenu )
      return pMenu->TrackPopupMenu(nFlags,x,y,pWnd,lpRect);

   return FALSE;
}

void Menu::CreateSubMenus()
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
         if ( pSubMenu->GetSafeHmenu() != nullptr )
         {
            auto pEAFSubMenu = std::shared_ptr<Menu>(new Menu());
            pEAFSubMenu->m_strMenu = strName;

            pEAFSubMenu->m_bOwnsMenuHandle = false;
            pEAFSubMenu->m_Menu.Attach(pSubMenu->GetSafeHmenu());

            pEAFSubMenu->Init(nullptr,m_pCmdMgr);
            m_Popups.push_back(pEAFSubMenu);
         }
         else
         {
            m_Popups.push_back(nullptr); // place holder for basic menu item
         }
      }
      else
      {
         m_Popups.push_back(nullptr); // place holder for basic menu item
      }
   }
}

INT Menu::GetMenuItemOffset()
{
   CMenu* pMenu = GetMenu();

   INT offset = 0;
   CString strMenu;
   pMenu->GetMenuString(0, strMenu, MF_BYPOSITION);
   if (strMenu == _T(""))
   {
      offset = 1;
   }
   return offset;
}
