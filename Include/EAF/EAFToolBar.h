///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// EAFToolBar.h: interface for the CEAFToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EAFTOOLBAR_H__44A9C83E_AD58_4EF2_9D53_FDD7452FFC9B__INCLUDED_)
#define AFX_EAFTOOLBAR_H__44A9C83E_AD58_4EF2_9D53_FDD7452FFC9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <EAF\EAFExp.h>
#include <afxext.h>

class CEAFMainFrame;
class CEAFDocument;
class CEAFPluginCommandManager;
interface IEAFCommandCallback;

class EAFCLASS CEAFToolBar  
{
public:
	CEAFToolBar();
	virtual ~CEAFToolBar();

   // These 4 methods add buttons to toolbars. The pCallback is a pointer to the object
   // that gets called when the toolbar button is pressed. If pCallback is nullptr, the
   // the command is processed by MFC command routing.
   BOOL LoadToolBar(LPCTSTR lpszResourceName,IEAFCommandCallback* pCallback);
   BOOL LoadToolBar(UINT nIDResource,IEAFCommandCallback* pCallback);
   BOOL AddButtons(int nButtons,UINT* nIDs,UINT nBitmapID,LPCTSTR lpszStrings,IEAFCommandCallback* pCallback);
   BOOL InsertButton(int nIndex,UINT nID,UINT nBitmapID,LPCTSTR lpszString,IEAFCommandCallback* pCallback);
   void RemoveButtons(IEAFCommandCallback* pCallback);
   BOOL DeleteButton(int nIndex);

   DWORD GetOwnerID() const; // returns the key of the object creating this toolbar
   UINT GetToolBarID() const;   // returns the ID of this toolbar
   DWORD GetExtendedStyle();
   void SetExtendedStyle(DWORD dwStyleEx);
   BOOL HideButton(int nID,IEAFCommandCallback* pCallback,BOOL bHide=TRUE);
   BOOL GetItemRect(int nIndex,LPRECT lpRect);
   void SetItemID(int nIndex,UINT nID,IEAFCommandCallback* pCallback);
   void GetItemID(int nIndex,UINT* pID,IEAFCommandCallback** ppCallback);
   int CommandToIndex(UINT nPluginCmdID,IEAFCommandCallback* pCallback) const; 
   void SetButtonStyle(int nIndex,UINT nStyle);
   UINT GetButtonStyle(int nIndex) const;
   BOOL SetButtonText(int nIndex,LPCTSTR lpszText) const;
   CString GetButtonText(int nIndex) const;
   BOOL MoveButton(UINT nOldIndex,UINT nNewIndex);

   BOOL CreateDropDownButton(UINT nPluginCmd,IEAFCommandCallback* pCallback,DWORD dwBtnStyle);

   // CWnd
   BOOL IsWindowVisible();
   void ClientToScreen(LPPOINT lpPoint) const;
   void ClientToScreen(LPRECT lpRect) const;


private:
   friend CEAFMainFrame;

   UINT  m_ToolBarID;
   DWORD m_OwnerID;

   bool bOwnsToolBar;
   CToolBar* m_pToolBar;
   CEAFPluginCommandManager* m_pCmdMgr;

   UINT GetMappedID(UINT nPluginCmdID,IEAFCommandCallback* pCallback) const; 
};

#endif // !defined(AFX_EAFTOOLBAR_H__44A9C83E_AD58_4EF2_9D53_FDD7452FFC9B__INCLUDED_)
