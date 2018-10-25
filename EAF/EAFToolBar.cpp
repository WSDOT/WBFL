// EAFToolBar.cpp: implementation of the CEAFToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFToolBar.h>

#include "PluginCommandManager.h"

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

   m_ID = -1;
}

CEAFToolBar::~CEAFToolBar()
{
   if ( bOwnsToolBar && m_pToolBar )
   {
      delete m_pToolBar;
      m_pToolBar = NULL;
   }
}

BOOL CEAFToolBar::AddButtons(int nButtons,UINT* nIDs,UINT nBitmapID,LPCSTR lpszStrings,ICommandCallback* pCallback)
{
   CToolBarCtrl& tb = m_pToolBar->GetToolBarCtrl();

   int nFirstNewImage  = tb.AddBitmap(nButtons,nBitmapID);
   int nFirstNewString = tb.AddStrings(lpszStrings);

   TBBUTTON* pTBButtons = new TBBUTTON[nButtons];
   for ( int i = 0; i < nButtons; i++ )
   {
      UINT nCmdID = m_pCmdMgr->AddCommandCallback(nIDs[i],pCallback);

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

void CEAFToolBar::RemoveButtons(ICommandCallback* pCallback)
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

DWORD CEAFToolBar::GetID()
{
   return m_ID;
}