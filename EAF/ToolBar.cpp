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


#include "stdafx.h"
#include <EAF\ToolBar.h>
#include <EAF\EAFUtilities.h>
#include <EAF\PluginCommandManager.h>


using namespace WBFL::EAF;


ToolBar::ToolBar()
{
   bOwnsToolBar = false;
   m_pToolBar = nullptr;
   m_pCmdMgr  = nullptr;

   m_OwnerID = -1;
   m_ToolBarID = -1;
}

ToolBar::~ToolBar()
{
   if ( bOwnsToolBar && m_pToolBar )
   {
      m_pToolBar->DestroyWindow();
      delete m_pToolBar;
      m_pToolBar = nullptr;
   }
}

BOOL ToolBar::LoadToolBar(LPCTSTR lpszResourceName, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   if ( m_pToolBar == nullptr || !m_pToolBar->LoadToolBar(lpszResourceName) )
   {
      return FALSE;
   }

   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();
   int nButtons = tb.GetButtonCount();
   for ( int i = 0; i < nButtons; i++ )
   {
      TBBUTTON tbButton;
      tb.GetButton(i,&tbButton);
      UINT nID = tbButton.idCommand; // this is the ID that the plug supplied (not unique in the app)
      auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(nID, pCallback);
      if ( !bSuccess )
      {
         return FALSE;
      }

      tb.SetCmdID(i,nCmdID); // replace the command ID on the button to be the unique one
   }

   return TRUE;
}

BOOL ToolBar::LoadToolBar(UINT nIDResource, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   if (m_pToolBar == nullptr || !m_pToolBar->LoadToolBar(nIDResource) )
   {
      ATLASSERT(false); // did you forget to call AFX_MANAGE_STATE(AfxGetStaticModuleState()); ????
      return FALSE;
   }

   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();
   int nButtons = tb.GetButtonCount();
   for ( int i = 0; i < nButtons; i++ )
   {
      TBBUTTON tbButton;
      tb.GetButton(i,&tbButton);
      UINT nID = tbButton.idCommand; // this is the ID that the plug supplied (not unique in the app)
      auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(nID, pCallback);
      if (!bSuccess)
      {
         return FALSE;
      }

      tb.SetCmdID(i,nCmdID); // replace the command ID on the button to be the unique one
   }

   return TRUE;
}

BOOL ToolBar::AddButtons(int nButtons,UINT* nIDs,UINT nBitmapID,LPCTSTR lpszStrings, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   int nFirstNewImage  = tb.AddBitmap(nButtons,nBitmapID);
   int nFirstNewString = tb.AddStrings(lpszStrings);

   auto pTBButtons = std::make_unique<TBBUTTON[]>(nButtons);
   for ( int i = 0; i < nButtons; i++ )
   {
      auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(nIDs[i], pCallback);
      if ( !bSuccess )
      {
         return FALSE;
      }

      TBBUTTON tbButton;
      tbButton.iBitmap = nFirstNewImage  + i;
      tbButton.iString = nFirstNewString + i;

      tbButton.idCommand = nCmdID;
      tbButton.fsState = TBSTATE_ENABLED;
      tbButton.fsStyle = TBSTYLE_BUTTON;
      tbButton.dwData = 0;

      pTBButtons[i] = tbButton;
   }

   if ( !tb.AddButtons(nButtons,pTBButtons.get()) )
   {
      return FALSE;
   }

   tb.AutoSize();

   return TRUE;
}

BOOL ToolBar::InsertButton(int nIndex,UINT nID,UINT nBitmapID,LPCTSTR lpszString, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   int nFirstNewImage  = (nBitmapID == -1 ? -1 : tb.AddBitmap(1,nBitmapID));
   int nFirstNewString = (lpszString == nullptr ? -1 : tb.AddStrings(lpszString));

   auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(nID, pCallback);
   if ( !bSuccess )
   {
        return FALSE;
   }

   TBBUTTON tbButton;
   tbButton.iBitmap = nFirstNewImage;
   tbButton.iString = nFirstNewString;

   tbButton.idCommand = nCmdID;
   tbButton.fsState = TBSTATE_ENABLED;
   tbButton.fsStyle = TBSTYLE_BUTTON;
   tbButton.dwData = 0;

   if ( !tb.InsertButton(nIndex,&tbButton) )
   {
      return FALSE;
   }

   tb.AutoSize();

   return TRUE;
}

void ToolBar::RemoveButtons(std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   auto nCmdIDs = m_pCmdMgr->GetMappedCommandIDs(pCallback);
   for(auto& nCmdID : nCmdIDs)
   {
      UINT btnIdx = tb.CommandToIndex(nCmdID);
      tb.DeleteButton(btnIdx);
   }
}

BOOL ToolBar::DeleteButton(int nIndex)
{
   if ( m_pToolBar )
   {
      if ( m_pToolBar->GetToolBarCtrl().DeleteButton(nIndex) )
      {
         m_pToolBar->GetToolBarCtrl().AutoSize();
         return TRUE;
      }
   }

   return FALSE;
}

UINT ToolBar::GetToolBarID() const
{
   return m_ToolBarID;
}

DWORD ToolBar::GetOwnerID() const
{
   return m_OwnerID;
}

BOOL ToolBar::IsWindowVisible()
{
   if ( m_pToolBar )
   {
      return m_pToolBar->IsWindowVisible();
   }

   return FALSE;
}

BOOL ToolBar::HideButton(int nID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback,BOOL bHide)
{
   auto [bSuccess, nMappedCmdID] = m_pCmdMgr->GetMappedCommandID(nID, pCallback);
   if ( !bSuccess )
   {
      return FALSE;
   }

   if ( m_pToolBar )
   {
      return m_pToolBar->GetToolBarCtrl().HideButton(nMappedCmdID,bHide);
   }

   return FALSE;
}

BOOL ToolBar::GetItemRect(int nIndex,LPRECT lpRect)
{
   if ( m_pToolBar )
   {
      return m_pToolBar->GetToolBarCtrl().GetItemRect(nIndex,lpRect);
   }

   return FALSE;
}

void ToolBar::ClientToScreen(LPPOINT lpPoint) const
{
   if ( m_pToolBar )
   {
      m_pToolBar->GetToolBarCtrl().ClientToScreen(lpPoint);
   }
}

void ToolBar::ClientToScreen(LPRECT lpRect) const
{
   if ( m_pToolBar )
   {
      m_pToolBar->GetToolBarCtrl().ClientToScreen(lpRect);
   }
}

void ToolBar::GetWindowText(CString& rString) const
{
   if (m_pToolBar)
   {
      m_pToolBar->GetWindowText(rString);
   }
}

void ToolBar::SetItemID(int nIndex,UINT nID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   if ( m_pToolBar )
   {
      UINT nOldID;
      UINT style;
      int iImage;
      m_pToolBar->GetButtonInfo(nIndex,nOldID,style,iImage);
      m_pToolBar->SetButtonInfo(nIndex,nID,style,iImage);
   }
}

std::pair<UINT, std::shared_ptr<WBFL::EAF::ICommandCallback>> ToolBar::GetItemID(int nIndex)
{
   UINT ID = -1;
   std::shared_ptr<WBFL::EAF::ICommandCallback> callback = nullptr;
   if ( m_pToolBar )
   {
      auto nMappedCmdID = m_pToolBar->GetItemID(nIndex);
      BOOL bSuccess;
      std::tie(bSuccess, ID, callback) = m_pCmdMgr->GetCommandCallback(nMappedCmdID);
      if (!bSuccess)
      {
         ID = nMappedCmdID;
         callback = nullptr;
      }
   }
   return { ID,callback };
}

int ToolBar::CommandToIndex(UINT nPluginCmdID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const
{
   // NOTE: MFC documentation says return type is UINT, but looking at the header file, it is an int
   auto [bSuccess, nMappedCmdID] = m_pCmdMgr->GetMappedCommandID(nPluginCmdID, pCallback);
   if ( !bSuccess )
   {
      return -1;
   }

   if ( m_pToolBar )
   {
      return m_pToolBar->GetToolBarCtrl().CommandToIndex(nMappedCmdID);
   }

   return -1;
}

DWORD ToolBar::GetExtendedStyle()
{
   if ( m_pToolBar )
   {
      return m_pToolBar->GetToolBarCtrl().GetExtendedStyle();
   }

   return 0;
}

void ToolBar::SetExtendedStyle(DWORD dwStyleEx)
{
   if ( m_pToolBar )
   {
      m_pToolBar->SendMessage(TB_SETEXTENDEDSTYLE,0,(LPARAM)dwStyleEx);
      m_pToolBar->GetToolBarCtrl().AutoSize();
   }
}

void ToolBar::SetButtonStyle(int nIndex,UINT nStyle)
{
   if ( m_pToolBar )
   {
      m_pToolBar->SetButtonStyle(nIndex,nStyle);
      m_pToolBar->GetToolBarCtrl().AutoSize();
   }
}

UINT ToolBar::GetButtonStyle(int nIndex) const
{
   if ( m_pToolBar )
   {
      return m_pToolBar->GetButtonStyle(nIndex);
   }
   
   return 0;
}

CString ToolBar::GetButtonText(int nIndex) const
{
   if ( m_pToolBar )
   {
      return m_pToolBar->GetButtonText(nIndex);
   }

   return CString("");
}

BOOL ToolBar::SetButtonText(int nIndex,LPCTSTR lpszText) const
{
   if ( m_pToolBar )
   {
      return m_pToolBar->SetButtonText(nIndex,lpszText);
      m_pToolBar->GetToolBarCtrl().AutoSize();
   }

   return FALSE;
}

BOOL ToolBar::MoveButton(UINT nOldIndex,UINT nNewIndex)
{
   if ( m_pToolBar )
   {
      return m_pToolBar->GetToolBarCtrl().MoveButton(nOldIndex,nNewIndex);
   }

   return FALSE;
}

BOOL ToolBar::CreateDropDownButton(UINT nPluginCmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback,DWORD dwBtnStyle)
{
   // REF: http://www.codejock.com/support/articles/mfc/general/g_5.asp
   if ( !m_pToolBar )
   {
      return FALSE;
   }

   DWORD dwStyleEx = GetExtendedStyle();
   dwStyleEx |= TBSTYLE_EX_DRAWDDARROWS;
   SetExtendedStyle(dwStyleEx);

   int idx = CommandToIndex(nPluginCmd,pCallback);
   if ( idx < 0 ) 
   {
      return FALSE;
   }

   DWORD dwStyle = GetButtonStyle(idx);
   dwStyle |= dwBtnStyle | BTNS_AUTOSIZE;
   SetButtonStyle(idx,dwStyle);

   return TRUE;
}

UINT ToolBar::GetMappedID(UINT nPluginCmdID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) const
{
   auto [bSuccess, nMappedCmdID] = m_pCmdMgr->GetMappedCommandID(nPluginCmdID, pCallback);
   if ( !bSuccess )
   {
      return -1;
   }

   return nMappedCmdID;
}
