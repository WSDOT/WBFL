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

// EAFMenu.h: interface for the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <vector>
#include <memory>

class CWnd;
class CEAFDocument;

namespace WBFL
{
   namespace EAF
   {
	  class PluginCommandManager;
	  class ICommandCallback;

	  // Wrapper class for MFC CMenu. Plug-ins cannot access CMenu objects directly because of the 
	  // need to map plug-in command ID's which are not guaranteed to be unique into application
	  // command IDs that must be unique. This class provides access to CMenu-like functions
	  // while managing the command IDs
	  class EAFCLASS Menu  
	  {
	  public:
		 virtual ~Menu();

		 UINT GetMenuItemCount() const;

		 std::shared_ptr<Menu> GetSubMenu(INT pos);

		 static std::shared_ptr<Menu> CreateMenu(CWnd* pWnd, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr);
		 static std::shared_ptr<Menu> CreateMenu(HMENU hMenu, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr);

		 // Creates a context menu
		 static std::shared_ptr<Menu> CreateContextMenu(std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr);

		 // Creates a pop-up menu at pos
		 std::shared_ptr<Menu> CreatePopupMenu(INT pos,LPCTSTR lpszName);

		 // Loads a menu resource into the menu.
		 BOOL LoadMenu(UINT nIDResource, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL LoadMenu(LPCTSTR lpszResourceName, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);

		 BOOL AppendMenu(UINT nID, LPCTSTR lpszNewItem, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL InsertMenu(UINT nPosition, UINT nID, LPCTSTR lpszNewItem, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL AppendSeparator();
		 BOOL InsertSeparator(UINT nPosition,UINT nFlags);

		 // if nFlags is MF_BYCOMMAND, nIDItem is a plug-in command ID
		 int GetMenuString(UINT nIDItem, LPTSTR lpString, int nMaxCount, UINT nFlags, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const;
		 int GetMenuString(UINT nIDItem, CString& rString, UINT nFlags, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const;

		 // if nFlags is MF_BYCOMMAND, nIDItem is an application unique command ID
		 int GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags) const;
		 int GetMenuString(UINT nIDItem,CString& rString,UINT nFlags) const;
   
		 BOOL SetMenuString(UINT nIDItem,LPTSTR lpString,UINT nFlags);
		 BOOL SetMenuString(UINT nIDItem,CString& rString,UINT nFlags);

		 BOOL SetMenuItemBitmaps(UINT nPosition, UINT nFlags, const CBitmap* pBmpUnchecked, const CBitmap* pBmpChecked, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);

		 BOOL RemoveMenu(UINT nPosition, UINT nFlags, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);

		 void DestroyMenu(std::shared_ptr<Menu> pMenu);

		 UINT FindMenuItem(LPCTSTR strTargetMenu);

		 // tuple = mapped ID, original ID, callback
		 std::tuple<UINT,UINT,std::shared_ptr<WBFL::EAF::ICommandCallback>> GetMenuItemID(UINT nPosition);

		 BOOL TrackPopupMenu(UINT nFlags,int x,int y,CWnd* pWnd,LPCRECT lpRect = 0);


	  private:
		 Menu(CWnd* pWnd, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr);
		 Menu(HMENU hMenu, std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr);
		 Menu() = default; // this construction is meant to be private, for internal use only
		 void Init(CWnd* pWnd,std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr);
   
		 CMenu* GetMenu();
		 const CMenu* GetMenu() const;

		 void LoadMenu(CMenu* pMenu, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 void LoadSubMenu(std::shared_ptr<Menu> pEAFMenu, CMenu* pMenu, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 void CreateSubMenus(); // called by SetWindow to fill up m_Popups with the pop up menus for the main menu

		 BOOL AppendSeparator(CMenu* pMenu);
		 BOOL InsertSeparator(CMenu* pMenu,UINT nPosition,UINT nFlags);

		 CWnd* m_pWnd = nullptr; // pointer to window that owns main menu, Call GetMenu() to get the main menu
   
		 std::shared_ptr<WBFL::EAF::PluginCommandManager> m_pCmdMgr;
   
		 bool m_bOwnsMenuHandle = false;
		 CMenu m_Menu; // this is the MFC CMenu for this popup menu
		 std::vector<std::shared_ptr<Menu>> m_Popups; // these are the popup menus that hang off this menu

		 INT GetMenuItemOffset();

		 CString m_strMenu;

		 friend CEAFDocument;
	  };
   };
};
