///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

class CWnd;
class CEAFPluginCommandManager;
class CEAFDocument;
interface IEAFCommandCallback;

// Wrapper class for MFC CMenu. Plug-ins cannot access CMenu objects directly because of the 
// need to map plug-in command ID's which are not guarenteed to be unique into application
// command IDs that must be unique. This class provides access to CMenu-like functions
// while managing the command IDs
class EAFCLASS CEAFMenu  
{
public:
	CEAFMenu(CWnd* pWnd,CEAFPluginCommandManager* pCmdMgr);
	CEAFMenu(HMENU hMenu,CEAFPluginCommandManager* pCmdMgr);
	CEAFMenu(const CEAFMenu& rOther);
	virtual ~CEAFMenu();

   UINT GetMenuItemCount() const;

   CEAFMenu* GetSubMenu(INT pos);

   // Creates a context menu
   static CEAFMenu* CreateContextMenu(CEAFPluginCommandManager* pCmdMgr);

   // Creates a pop-up menu at pos
   CEAFMenu* CreatePopupMenu(INT pos,LPCTSTR lpszName);

   // Loads a menu resource into the menu.
   BOOL LoadMenu( UINT nIDResource,IEAFCommandCallback* pCallback );
   BOOL LoadMenu(LPCTSTR lpszResourceName,IEAFCommandCallback* pCallback );

   BOOL AppendMenu(UINT nID,LPCTSTR lpszNewItem,IEAFCommandCallback* pCallback);
   BOOL InsertMenu(UINT nPosition, UINT nID, LPCTSTR lpszNewItem, IEAFCommandCallback* pCallback);
   void AppendSeparator();
   void InsertSeparator(UINT nPosition,UINT nFlags);

   // if nFlags is MF_BYCOMMAND, nIDItem is a plug-in command ID
   int GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags, IEAFCommandCallback* pCallback) const;
   int GetMenuString(UINT nIDItem,CString& rString,UINT nFlags, IEAFCommandCallback* pCallback) const;

   // if nFlags is MF_BYCOMMAND, nIDItem is an application unique command ID
   int GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags) const;
   int GetMenuString(UINT nIDItem,CString& rString,UINT nFlags) const;

   BOOL SetMenuItemBitmaps(UINT nPosition,UINT nFlags,const CBitmap* pBmpUnchecked,const CBitmap* pBmpChecked, IEAFCommandCallback* pCallback);

   BOOL RemoveMenu(UINT nPosition,UINT nFlags,IEAFCommandCallback* pCallback);

   void DestroyMenu(CEAFMenu* pMenu);

   UINT FindMenuItem(LPCTSTR strTargetMenu);

   UINT GetMenuItemID(UINT nPosition,UINT* pOriginalID, IEAFCommandCallback** ppCallback);

   BOOL TrackPopupMenu(UINT nFlags,int x,int y,CWnd* pWnd,LPCRECT lpRect = 0);


private:
   CEAFMenu();
   void Init(CWnd* pWnd,CEAFPluginCommandManager* pCmdMgr);
   
   CMenu* GetMenu();
   const CMenu* GetMenu() const;

   void LoadMenu(CMenu* pMenu,IEAFCommandCallback* pCallback);
   void CreateSubMenus(); // called by SetWindow to fill up m_Popups with the pop up menus for the main menu

   void AppendSeparator(CMenu* pMenu);
   void InsertSeparator(CMenu* pMenu,UINT nPosition,UINT nFlags);

   CWnd* m_pWnd; // pointer to window that owns main menu
                 // Call GetMenu() to get the main menu
   CEAFPluginCommandManager* m_pCmdMgr;
   
   bool m_bOwnsMenuHandle;
   CMenu m_Menu; // this is the MFC CMenu for this popup menu
   std::vector<CEAFMenu*> m_Popups; // these are the popup menus that hang off this menu

   CString m_strMenu;

   friend CEAFDocument;
};
