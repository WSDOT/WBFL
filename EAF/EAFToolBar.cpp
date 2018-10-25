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

// EAFToolBar.cpp: implementation of the CEAFToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFToolBar.h>

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

BOOL CEAFToolBar::AddButtons(int nButtons,UINT* nIDs,UINT nBitmapID,LPCSTR lpszStrings,IEAFCommandCallback* pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   int nFirstNewImage  = tb.AddBitmap(nButtons,nBitmapID);
   int nFirstNewString = tb.AddStrings(lpszStrings);

   TBBUTTON* pTBButtons = new TBBUTTON[nButtons];
   for ( int i = 0; i < nButtons; i++ )
   {
      UINT nCmdID;
      if ( pCallback )
      {
         if ( !m_pCmdMgr->AddCommandCallback(nIDs[i],pCallback,&nCmdID) )
            return FALSE;
      }
      else
      {
         nCmdID = nIDs[i];
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

   if ( !tb.AddButtons(nButtons,pTBButtons) )
   {
      delete[] pTBButtons;
      return FALSE;
   }

   tb.AutoSize();

   delete[] pTBButtons;
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

BOOL CEAFToolBar::HideButton(int nID,BOOL bHide)
{
   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().HideButton(nID,bHide);

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

int CEAFToolBar::CommandToIndex(UINT nID) const
{
   // NOTE: MFC documentation says return type is UINT, but looking at the header file, it is an int
   // nID is the unique command ID
   if ( m_pToolBar )
      return m_pToolBar->GetToolBarCtrl().CommandToIndex(nID);

   return -1;
}

int CEAFToolBar::CommandToIndex(UINT nPluginCmdID,IEAFCommandCallback* pCallback) const
{
   // NOTE: MFC documentation says return type is UINT, but looking at the header file, it is an int
   UINT nMappedCmdID; // unique command id
   if ( !m_pCmdMgr->GetMappedCommandID(nPluginCmdID,pCallback,&nMappedCmdID) )
      return -1;

   return CommandToIndex(nMappedCmdID);
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
