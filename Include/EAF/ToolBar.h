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

// EAFToolBar.h: interface for the WBFL::EAF::ToolBar class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <afxext.h>

class CEAFMainFrame;
class CEAFDocument;

namespace WBFL
{
   namespace EAF
   {
	  class PluginCommandManager;
	  class ICommandCallback;

	  class EAFCLASS ToolBar  
	  {
	  public:
		  ToolBar();
		  virtual ~ToolBar();

		 // These 4 methods add buttons to toolbars. The pCallback is a pointer to the object
		 // that gets called when the toolbar button is pressed. If pCallback is nullptr, the
		 // the command is processed by MFC command routing.
		 BOOL LoadToolBar(LPCTSTR lpszResourceName, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL LoadToolBar(UINT nIDResource, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL AddButtons(int nButtons,UINT* nIDs,UINT nBitmapID,LPCTSTR lpszStrings, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL InsertButton(int nIndex,UINT nID,UINT nBitmapID,LPCTSTR lpszString, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 void RemoveButtons(std::shared_ptr<WBFL::EAF::ICommandCallback> );
		 BOOL DeleteButton(int nIndex);

		 DWORD GetOwnerID() const; // returns the key of the object creating this toolbar
		 UINT GetToolBarID() const;   // returns the ID of this toolbar
		 DWORD GetExtendedStyle();
		 void SetExtendedStyle(DWORD dwStyleEx);
		 BOOL HideButton(int nID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback,BOOL bHide=TRUE);
		 BOOL GetItemRect(int nIndex,LPRECT lpRect);
		 void SetItemID(int nIndex,UINT nID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 std::pair<UINT, std::shared_ptr<WBFL::EAF::ICommandCallback>> GetItemID(int nIndex);
		 int CommandToIndex(UINT nPluginCmdID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const;
		 void SetButtonStyle(int nIndex,UINT nStyle);
		 UINT GetButtonStyle(int nIndex) const;
		 BOOL SetButtonText(int nIndex,LPCTSTR lpszText) const;
		 CString GetButtonText(int nIndex) const;
		 BOOL MoveButton(UINT nOldIndex,UINT nNewIndex);

		 BOOL CreateDropDownButton(UINT nPluginCmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback,DWORD dwBtnStyle);

		 // CWnd
		 BOOL IsWindowVisible();
		 void ClientToScreen(LPPOINT lpPoint) const;
		 void ClientToScreen(LPRECT lpRect) const;

		 void GetWindowText(CString& rString) const;


	  private:
		 friend CEAFMainFrame;

		 UINT  m_ToolBarID;
		 DWORD m_OwnerID;

		 bool bOwnsToolBar;
		 CToolBar* m_pToolBar;
		 std::shared_ptr<WBFL::EAF::PluginCommandManager> m_pCmdMgr;

		 UINT GetMappedID(UINT nPluginCmdID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const;
	  };

   };
};
