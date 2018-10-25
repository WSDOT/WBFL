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

// EAFMenu.h: interface for the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <vector>

class CWnd;
class CEAFPluginCommandManager;
class CEAFDocument;
interface ICommandCallback;

class EAFCLASS CEAFMenu  
{
public:
	CEAFMenu(CWnd* pWnd,CEAFPluginCommandManager* pCmdMgr);
	CEAFMenu(const CEAFMenu& rOther);
	virtual ~CEAFMenu();

   CEAFMenu& operator=(const CEAFMenu& rOther);

   UINT GetMenuItemCount() const;

   CEAFMenu* GetSubMenu(INT pos);

   CEAFMenu* CreatePopupMenu(INT pos,LPCTSTR lpszName);
   BOOL LoadMenu( UINT nIDResource,ICommandCallback* pCallback );
   BOOL LoadMenu(LPCTSTR lpszResourceName,ICommandCallback* pCallback );

   BOOL AppendMenu(UINT nID,LPCTSTR lpszNewItem,ICommandCallback* pCallback);
   BOOL InsertMenu(UINT nPosition, UINT nID, LPCTSTR lpszNewItem, ICommandCallback* pCallback);
   void AppendSeparator();
   void InsertSeparator(UINT nPosition,UINT nFlags);

   int GetMenuString(UINT nIDItem,LPTSTR lpString,int nMaxCount,UINT nFlags) const;
   int GetMenuString(UINT nIDItem,CString& rString,UINT nFlags) const;

   BOOL SetMenuItemBitmaps(UINT nPosition,UINT nFlags,const CBitmap* pBmpUnchecked,const CBitmap* pBmpChecked, ICommandCallback* pCallback);

   void RemoveMenu(UINT nPosition,UINT nFlags,ICommandCallback* pCallback);

   void DestroyMenu(CEAFMenu* pMenu);

   UINT FindMenuItem(const char* strTargetMenu);

   BOOL TrackPopupMenu(UINT nFlags,int x,int y,CWnd* pWnd,LPCRECT lpRect = 0);

private:
   void MakeAssignment(const CEAFMenu& rOther);

   CEAFMenu();
   void Init(CWnd* pWnd,CEAFPluginCommandManager* pCmdMgr);
   
   CMenu* GetMenu();
   const CMenu* GetMenu() const;

   void LoadMenu(CMenu* pMenu,ICommandCallback* pCallback);
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
