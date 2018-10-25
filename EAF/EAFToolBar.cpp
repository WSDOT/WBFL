///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// EAFToolBar.cpp: implementation of the CEAFToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFToolBar.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFPluginCommandManager.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFToolBar::CEAFToolBar()
{
   bOwnsToolBar = false;
   m_pToolBar = NULL;
   m_pCmdMgr  = NULL;

   m_OwnerID = -1;
   m_ToolBarID = -1;
}

CEAFToolBar::~CEAFToolBar()
{
   if ( bOwnsToolBar && m_pToolBar )
   {
      m_pToolBar->DestroyWindow();
      delete m_pToolBar;
      m_pToolBar = NULL;
   }
}

BOOL CEAFToolBar::LoadToolBar(LPCTSTR lpszResourceName,IEAFCommandCallback* pCallback)
{
   if ( !m_pToolBar->LoadToolBar(lpszResourceName) )
      return FALSE;

   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();
   int nButtons = tb.GetButtonCount();
   for ( int i = 0; i < nButtons; i++ )
   {
      TBBUTTON tbButton;
      tb.GetButton(i,&tbButton);
      UINT nID = tbButton.idCommand; // this is the ID that the plug supplied (not unique in the app)
      UINT nCmdID;// this command ID is unique in the app
      if ( !m_pCmdMgr->AddCommandCallback(nID,pCallback,&nCmdID) )
         return FALSE;

      tb.SetCmdID(i,nCmdID); // replace the comand ID on the button to be the unique one
   }

   return TRUE;
}

BOOL CEAFToolBar::LoadToolBar(UINT nIDResource,IEAFCommandCallback* pCallback)
{
   if ( !m_pToolBar->LoadToolBar(nIDResource) )
      return FALSE;

   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();
   int nButtons = tb.GetButtonCount();
   for ( int i = 0; i < nButtons; i++ )
   {
      TBBUTTON tbButton;
      tb.GetButton(i,&tbButton);
      UINT nID = tbButton.idCommand; // this is the ID that the plug supplied (not unique in the app)
      UINT nCmdID;// this command ID is unique in the app
      if ( !m_pCmdMgr->AddCommandCallback(nID,pCallback,&nCmdID) )
         return FALSE;

      tb.SetCmdID(i,nCmdID); // replace the comand ID on the button to be the unique one
   }

   return TRUE;
}

BOOL CEAFToolBar::AddButtons(int nButtons,UINT* nIDs,UINT nBitmapID,LPCTSTR lpszStrings,IEAFCommandCallback* pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   int nFirstNewImage  = tb.AddBitmap(nButtons,nBitmapID);
   int nFirstNewString = tb.AddStrings(lpszStrings);

   TBBUTTON* pTBButtons = new TBBUTTON[nButtons];
   for ( int i = 0; i < nButtons; i++ )
   {
      UINT nCmdID;
      if ( !m_pCmdMgr->AddCommandCallback(nIDs[i],pCallback,&nCmdID) )
         return FALSE;

      TBBUTTON tbButton;
      tbButton.iBitmap = nFirstNewImage  + i;
      tbButton.iString = nFirstNewString + i;

      tbButton.idCommand = nCmdID;
      tbButton.fsState = TBSTATE_ENABLED;
      tbButton.fsStyle = TBSTYLE_BUTTON;
      tbButton.dwData = 0;

      pTBButtons[i] = tbButton;
   }

   if ( !tb.AddButtons(nButtons,pTBButtons) )
   {
      delete[] pTBButtons;
      return FALSE;
   }

   tb.AutoSize();

   delete[] pTBButtons;
   return TRUE;
}

BOOL CEAFToolBar::InsertButton(int nIndex,UINT nID,UINT nBitmapID,LPCTSTR lpszString,IEAFCommandCallback* pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   int nFirstNewImage  = tb.AddBitmap(1,nBitmapID);
   int nFirstNewString = tb.AddStrings(lpszString);

   UINT nCmdID;
   if ( !m_pCmdMgr->AddCommandCallback(nID,pCallback,&nCmdID) )
        return FALSE;

   TBBUTTON tbButton;
   tbButton.iBitmap = nFirstNewImage;
   tbButton.iString = nFirstNewString;

   tbButton.idCommand = nCmdID;
   tbButton.fsState = TBSTATE_ENABLED;
   tbButton.fsStyle = TBSTYLE_BUTTON;
   tbButton.dwData = 0;

   if ( !tb.InsertButton(nIndex,&tbButton) )
      return FALSE;

   tb.AutoSize();

   return TRUE;
}

void CEAFToolBar::RemoveButtons(IEAFCommandCallback* pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   std::vector<UINT> nCmdIDs = m_pCmdMgr->GetMappedCommandIDs(pCallback);
   std::vector<UINT>::iterator iter;
   for ( iter = nCmdIDs.begin(); iter != nCmdIDs.end(); iter++ )
   {
      UINT nCmdID = *iter;

      UINT btnIdx = tb.CommandToIndex(nCmdID);
      tb.DeleteButton(btnIdx);
   }
}

BOOL CEAFToolBar::DeleteButton(int nIndex)
{
   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().DeleteButton(nIndex);

   return FALSE;
}

UINT CEAFToolBar::GetToolBarID() const
{
   return m_ToolBarID;
}

DWORD CEAFToolBar::GetOwnerID() const
{
   return m_OwnerID;
}

BOOL CEAFToolBar::IsWindowVisible()
{
   if ( m_pToolBar )
      return m_pToolBar->IsWindowVisible();

   return FALSE;
}

BOOL CEAFToolBar::HideButton(int nID,IEAFCommandCallback* pCallback,BOOL bHide)
{
   UINT nMappedCmdID; // unique command id
   if ( !m_pCmdMgr->GetMappedCommandID(nID,pCallback,&nMappedCmdID) )
      return FALSE;

   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().HideButton(nMappedCmdID,bHide);

   return FALSE;
}

BOOL CEAFToolBar::GetItemRect(int nIndex,LPRECT lpRect)
{
   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().GetItemRect(nIndex,lpRect);

   return FALSE;
}

void CEAFToolBar::ClientToScreen(LPPOINT lpPoint) const
{
   if ( m_pToolBar )
      m_pToolBar->GetToolBarCtrl().ClientToScreen(lpPoint);
}

void CEAFToolBar::ClientToScreen(LPRECT lpRect) const
{
   if ( m_pToolBar )
      m_pToolBar->GetToolBarCtrl().ClientToScreen(lpRect);
}

void CEAFToolBar::SetItemID(int nIndex,UINT nID,IEAFCommandCallback* pCallback)
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

void CEAFToolBar::GetItemID(int nIndex,UINT* pID,IEAFCommandCallback** ppCallback)
{
   UINT nMappedCmdID;
   if ( m_pToolBar )
   {
      nMappedCmdID = m_pToolBar->GetItemID(nIndex);
      if ( !m_pCmdMgr->GetCommandCallback(nMappedCmdID,pID,ppCallback) )
      {
         *pID = nMappedCmdID;
         *ppCallback = NULL;
      }
   }
}

int CEAFToolBar::CommandToIndex(UINT nPluginCmdID,IEAFCommandCallback* pCallback) const
{
   // NOTE: MFC documentation says return type is UINT, but looking at the header file, it is an int
   UINT nMappedCmdID; // unique command id
   if ( !m_pCmdMgr->GetMappedCommandID(nPluginCmdID,pCallback,&nMappedCmdID) )
      return -1;

   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().CommandToIndex(nMappedCmdID);

   return -1;
}

DWORD CEAFToolBar::GetExtendedStyle()
{
   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().GetExtendedStyle();

   return 0;
}

void CEAFToolBar::SetExtendedStyle(DWORD dwStyleEx)
{
   if ( m_pToolBar )
      m_pToolBar->SendMessage(TB_SETEXTENDEDSTYLE,0,(LPARAM)dwStyleEx);
}

void CEAFToolBar::SetButtonStyle(int nIndex,UINT nStyle)
{
   if ( m_pToolBar )
      m_pToolBar->SetButtonStyle(nIndex,nStyle);
}

UINT CEAFToolBar::GetButtonStyle(int nIndex) const
{
   if ( m_pToolBar )
      return m_pToolBar->GetButtonStyle(nIndex);
   
   return 0;
}

CString CEAFToolBar::GetButtonText(int nIndex) const
{
   if ( m_pToolBar )
      return m_pToolBar->GetButtonText(nIndex);

   return CString("");
}

BOOL CEAFToolBar::SetButtonText(int nIndex,LPCTSTR lpszText) const
{
   if ( m_pToolBar )
      return m_pToolBar->SetButtonText(nIndex,lpszText);

   return FALSE;
}

BOOL CEAFToolBar::MoveButton(UINT nOldIndex,UINT nNewIndex)
{
   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().MoveButton(nOldIndex,nNewIndex);

   return FALSE;
}

BOOL CEAFToolBar::CreateDropDownButton(UINT nPluginCmd,IEAFCommandCallback* pCallback,DWORD dwBtnStyle)
{
   // REF: http://www.codejock.com/support/articles/mfc/general/g_5.asp
   if ( !m_pToolBar )
      return FALSE;

   DWORD dwStyleEx = GetExtendedStyle();
   dwStyleEx |= TBSTYLE_EX_DRAWDDARROWS;
   SetExtendedStyle(dwStyleEx);

   int idx = CommandToIndex(nPluginCmd,pCallback);
   if ( idx < 0 ) 
      return FALSE;

   DWORD dwStyle = GetButtonStyle(idx);
   dwStyle |= dwBtnStyle | BTNS_AUTOSIZE;
   SetButtonStyle(idx,dwStyle);

   return TRUE;
}

UINT CEAFToolBar::GetMappedID(UINT nPluginCmdID,IEAFCommandCallback* pCallback) const
{
   UINT nMappedCmdID; // unique command id
   if ( !m_pCmdMgr->GetMappedCommandID(nPluginCmdID,pCallback,&nMappedCmdID) )
      return -1;

   return nMappedCmdID;
}
