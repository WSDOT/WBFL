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

// EAFMenu.cpp: implementation of the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFMenu.h>
#include <EAF\EAFPluginCommandManager.h>

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
   const CMenu* pMenu = GetMenu();
   if ( pMenu )
      return pMenu->GetMenuItemCount();

   return 0;
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

   m_Popups.push_back( pNewMenu );

   CMenu* pMenu = GetMenu();

   if ( pos < 0 )
      pMenu->AppendMenu(MF_POPUP, (UINT)pNewMenu->m_Menu.m_hMenu, lpszName );
   else
      pMenu->InsertMenu(pos,MF_BYPOSITION | MF_POPUP, (UINT)pNewMenu->m_Menu.m_hMenu, lpszName );

   if ( m_pWnd )
      m_pWnd->DrawMenuBar();

   return pNewMenu;
}

void CEAFMenu::LoadMenu(CMenu* pMenu,IEAFCommandCallback* pCallback)
{
   UINT nMenuItems = pMenu->GetMenuItemCount();
   for (UINT i = 0; i < nMenuItems; i++ )
   {
      INT nID = pMenu->GetMenuItemID(i);
      if ( nID < 0 )
      {
         LoadMenu(pMenu->GetSubMenu(i),pCallback); // sub-menu
      }
      else if ( nID == 0 )
      {
         AppendSeparator(pMenu); // separator
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
   
   m_Popups.insert(m_Popups.begin()+nPosition,NULL);

   return TRUE;
}

void CEAFMenu::AppendSeparator(CMenu* pMenu)
{
   pMenu->AppendMenu(MF_SEPARATOR);
}

void CEAFMenu::AppendSeparator()
{
   CMenu* pMenu = GetMenu();
   AppendSeparator(pMenu);
}

void CEAFMenu::InsertSeparator(CMenu* pMenu,UINT nPosition,UINT nFlags)
{
   pMenu->InsertMenu(nPosition,nFlags,MF_SEPARATOR);
}

void CEAFMenu::InsertSeparator(UINT nPosition,UINT nFlags)
{
   CMenu* pMenu = GetMenu();
   InsertSeparator(pMenu,nPosition,nFlags);
}

void CEAFMenu::RemoveMenu(UINT nPosition,UINT nFlags, IEAFCommandCallback* pCallback)
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

   pMenu->RemoveMenu(nPosition,nFlags);
}

int CEAFMenu::GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags) const
{
   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuStringA(nIDItem,lpString,nMaxCount,nFlags);
}

int CEAFMenu::GetMenuString(UINT nIDItem,CString& rString,UINT nFlags) const
{
   const CMenu* pMenu = GetMenu();
   return pMenu->GetMenuStringA(nIDItem,rString,nFlags);
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

UINT CEAFMenu::FindMenuItem(const char* strTargetMenu)
{
   CMenu* pMenu = GetMenu();
   UINT nItems = pMenu->GetMenuItemCount();
   for ( UINT menuPos = 0; menuPos < nItems; menuPos++ )
   {
      CString strMenu;
      pMenu->GetMenuString(menuPos,strMenu,MF_BYPOSITION);
      if ( strMenu.Compare(strTargetMenu) == 0 )
         return menuPos;
   }

   return -1;
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

      CMenu* pSubMenu = pMenu->GetSubMenu(menuIdx);
      if ( pSubMenu && pSubMenu->GetSafeHmenu() != NULL )
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
}
