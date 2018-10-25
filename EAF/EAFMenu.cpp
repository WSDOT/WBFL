// EAFMenu.cpp: implementation of the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFMenu.h>
#include "PluginCommandManager.h"

#include <algorithm> // for std::find()

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFMenu::CEAFMenu()
{
   m_pWnd    = NULL;
   m_pCmdMgr = NULL;
}

CEAFMenu::~CEAFMenu()
{
   std::vector<CEAFMenu*>::iterator iter;
   for ( iter = m_Popups.begin(); iter != m_Popups.end(); iter++ )
   {
      CEAFMenu* pPopup = *iter;
      delete pPopup;
   }
}

void CEAFMenu::SetWindow(CWnd* pWnd)
{
   m_pWnd = pWnd;
}

void CEAFMenu::SetPluginCommandManager(CPluginCommandManager* pCmdMgr)
{
   m_pCmdMgr = pCmdMgr;
}

CMenu* CEAFMenu::GetMenu()
{
   if ( ::IsMenu( m_Menu.m_hMenu ) )
      return &m_Menu;
   else
      return m_pWnd->GetMenu();
}

UINT CEAFMenu::GetMenuCount() const
{
   return m_pWnd->GetMenu()->GetMenuItemCount();
}

CEAFMenu* CEAFMenu::CreatePopupMenu(INT pos,LPCTSTR lpszName)
{
   CEAFMenu* pNewMenu = new CEAFMenu();
   pNewMenu->m_Menu.CreatePopupMenu();
   pNewMenu->SetPluginCommandManager( m_pCmdMgr );

   m_Popups.push_back( pNewMenu );

   CMenu* pMenu = m_pWnd->GetMenu();

   if ( pos < 0 )
      pMenu->AppendMenu(MF_POPUP, (UINT)pNewMenu->m_Menu.m_hMenu, lpszName );
   else
      pMenu->InsertMenu(pos,MF_BYPOSITION | MF_POPUP, (UINT)pNewMenu->m_Menu.m_hMenu, lpszName );

   m_pWnd->DrawMenuBar();

   return pNewMenu;
}

void CEAFMenu::LoadMenu(CMenu* pMenu,ICommandCallback* pCallback)
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

BOOL CEAFMenu::LoadMenu( UINT nIDResource,ICommandCallback* pCallback )
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

BOOL CEAFMenu::LoadMenu(LPCTSTR lpszResourceName,ICommandCallback* pCallback )
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

BOOL CEAFMenu::AppendMenu(UINT nID,LPCTSTR lpszNewItem,ICommandCallback* pCallback)
{
   UINT nCmdID = m_pCmdMgr->AddCommandCallback(nID,pCallback);

   CMenu* pMenu = GetMenu();
   if ( !pMenu->AppendMenu(MF_STRING,nCmdID,lpszNewItem) )
   {
      m_pCmdMgr->RemoveCommandCallback(nCmdID);
      return FALSE;
   }
   return TRUE;
}

BOOL CEAFMenu::InsertMenu(UINT nPosition, UINT nID, LPCTSTR lpszNewItem, ICommandCallback* pCallback)
{
   UINT nCmdID = m_pCmdMgr->AddCommandCallback(nID,pCallback);
   CMenu* pMenu = GetMenu();
   if (!pMenu->InsertMenu(nPosition,MF_BYPOSITION | MF_STRING, nCmdID, lpszNewItem) )
   {
      m_pCmdMgr->RemoveCommandCallback(nCmdID);
      return FALSE;
   }
   return TRUE;
}

void CEAFMenu::AppendSeparator()
{
   CMenu* pMenu = GetMenu();
   pMenu->AppendMenu(MF_SEPARATOR);
}

void CEAFMenu::DestroyMenu(CEAFMenu* pPopupMenu)
{
   CMenu* pMenu = GetMenu();
   UINT nMenus = pMenu->GetMenuItemCount();
   for ( UINT i = 0; i < nMenus; i++ )
   {
      CMenu* pSubMenu = pMenu->GetSubMenu(i);
      if ( pSubMenu->m_hMenu == pPopupMenu->m_Menu.m_hMenu )
      {
         pMenu->DeleteMenu(i,MF_BYPOSITION);

         pPopupMenu->m_Menu.Detach();
         std::vector<CEAFMenu*>::iterator found = std::find(m_Popups.begin(),m_Popups.end(),pPopupMenu);
         ASSERT( found != m_Popups.end() );
         m_Popups.erase(found);
         delete pPopupMenu;
         pPopupMenu = NULL;

         m_pWnd->DrawMenuBar();
         return;
      }
   }
}
