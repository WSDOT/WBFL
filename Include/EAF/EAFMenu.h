// EAFMenu.h: interface for the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EAFMENU_H__03459BF9_79DE_4B73_BD36_CFDD20405ED2__INCLUDED_)
#define AFX_EAFMENU_H__03459BF9_79DE_4B73_BD36_CFDD20405ED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <EAF\EAFExp.h>
#include <vector>

class CWnd;
class CPluginCommandManager;
class CEAFDocument;
interface ICommandCallback;

class EAFCLASS CEAFMenu  
{
public:
	CEAFMenu();
	CEAFMenu(const CEAFMenu& rOther);
	virtual ~CEAFMenu();

   CEAFMenu& operator=(const CEAFMenu& rOther);

   UINT GetMenuCount() const;

   CEAFMenu* CreatePopupMenu(INT pos,LPCTSTR lpszName);
   BOOL LoadMenu( UINT nIDResource,ICommandCallback* pCallback );
   BOOL LoadMenu(LPCTSTR lpszResourceName,ICommandCallback* pCallback );

   BOOL AppendMenu(UINT nID,LPCTSTR lpszNewItem,ICommandCallback* pCallback);
   BOOL InsertMenu(UINT nPosition, UINT nID, LPCTSTR lpszNewItem, ICommandCallback* pCallback);
   void AppendSeparator();

   void DestroyMenu(CEAFMenu* pMenu);

private:
   void MakeAssignment(const CEAFMenu& rOther);

   void SetWindow(CWnd* pWnd);
   void SetPluginCommandManager(CPluginCommandManager* pCmdMgr);
   
   CMenu* GetMenu();

   void LoadMenu(CMenu* pMenu,ICommandCallback* pCallback);

   CWnd* m_pWnd; // pointer to window that owns main menu
                 // Call GetMenu() to get the main menu
   CPluginCommandManager* m_pCmdMgr;
   
   CMenu m_Menu; // this is the MFC CMenu for this popup menu
   std::vector<CEAFMenu*> m_Popups; // these are the popup menus that hang off this menu

   friend CEAFDocument;
};

#endif // !defined(AFX_EAFMENU_H__03459BF9_79DE_4B73_BD36_CFDD20405ED2__INCLUDED_)
