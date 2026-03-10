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

// EAFMenu.cpp: implementation of the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\AcceleratorTable.h>
#include <EAF\PluginCommandManager.h>

#include <algorithm> // for std::find()

using namespace WBFL::EAF;

AcceleratorTable::~AcceleratorTable()
{
   DestroyAcceleratorTable(m_hAccelTable);
}

void AcceleratorTable::Init(std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr)
{
   m_pCmdMgr = pCmdMgr;
}

BOOL AcceleratorTable::AddAccelTable(HACCEL hAccelTable, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   int nAccelerators = CopyAcceleratorTable(m_hAccelTable, nullptr, 0); // number in the current table
   int nNewAccelerators = CopyAcceleratorTable(hAccelTable, nullptr, 0);   // number in the table that is being added

   // allocate enough space for both
   LPACCEL lpAccel = (LPACCEL)LocalAlloc(LPTR, (nAccelerators + nNewAccelerators) * sizeof(ACCEL));
   if (lpAccel != nullptr)
   {
      // copy the current table into the new array
      CopyAcceleratorTable(m_hAccelTable, lpAccel, nAccelerators);
   }

   // get the new accelerator mappings
   LPACCEL lpAccelNew = (LPACCEL)LocalAlloc(LPTR, (nNewAccelerators) * sizeof(ACCEL));
   CopyAcceleratorTable(hAccelTable, lpAccelNew, nNewAccelerators);

   // create commands for the new values
   for (int i = 0; i < nNewAccelerators; i++)
   {
      auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(lpAccelNew[i].cmd, pCallback);
      if (!bSuccess)
         return FALSE;

      lpAccel[nAccelerators + i].cmd = (WORD)nCmdID;
      lpAccel[nAccelerators + i].fVirt = lpAccelNew[i].fVirt;
      lpAccel[nAccelerators + i].key = lpAccelNew[i].key;
   }

   DestroyAcceleratorTable(m_hAccelTable);
   m_hAccelTable = CreateAcceleratorTable(lpAccel, nAccelerators + nNewAccelerators);

   LocalFree(lpAccelNew);
   LocalFree(lpAccel);

   return TRUE;
}

BOOL AcceleratorTable::AddAccelKey(BYTE fVirt, WORD key, WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   int nAccelerators = CopyAcceleratorTable(m_hAccelTable, nullptr, 0);
   LPACCEL lpAccelNew = (LPACCEL)LocalAlloc(LPTR, (nAccelerators + 1) * sizeof(ACCEL));
   if (lpAccelNew != nullptr)
   {
      CopyAcceleratorTable(m_hAccelTable, lpAccelNew, nAccelerators);
   }

   auto [bSuccess, nCmdID] = m_pCmdMgr->AddCommandCallback(cmd, pCallback);
   if (!bSuccess)
      return FALSE;

   lpAccelNew[nAccelerators].fVirt = fVirt;
   lpAccelNew[nAccelerators].key = key;
   lpAccelNew[nAccelerators].cmd = (WORD)nCmdID;

   DestroyAcceleratorTable(m_hAccelTable);
   m_hAccelTable = CreateAcceleratorTable(lpAccelNew, nAccelerators + 1);

   LocalFree(lpAccelNew);

   return TRUE;
}

BOOL AcceleratorTable::RemoveAccelKey(WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   int nAccelerators = CopyAcceleratorTable(m_hAccelTable, nullptr, 0);
   LPACCEL lpAccelNew = (LPACCEL)LocalAlloc(LPTR, nAccelerators * sizeof(ACCEL));
   if (lpAccelNew != nullptr)
   {
      CopyAcceleratorTable(m_hAccelTable, lpAccelNew, nAccelerators);
   }

   auto [bSuccess, nCmdID] = m_pCmdMgr->GetMappedCommandID(cmd, pCallback);
   if (!bSuccess)
      return FALSE;

   int i;
   for (i = 0; i < nAccelerators; i++)
   {
      if (lpAccelNew[i].cmd == nCmdID)
      {
         i++;
         break;
      }
   }

   for (; i < nAccelerators; i++)
   {
      lpAccelNew[i] = lpAccelNew[i - 1];
   }

   DestroyAcceleratorTable(m_hAccelTable);
   m_hAccelTable = CreateAcceleratorTable(lpAccelNew, nAccelerators - 1);

   m_pCmdMgr->RemoveCommandCallback(nCmdID);

   LocalFree(lpAccelNew);

   return TRUE;
}

BOOL AcceleratorTable::RemoveAccelKey(BYTE fVirt,WORD key)
{
   int nAccelerators = CopyAcceleratorTable(m_hAccelTable,nullptr,0);
   LPACCEL lpAccelNew = (LPACCEL)LocalAlloc(LPTR,nAccelerators*sizeof(ACCEL));
   if ( lpAccelNew != nullptr )
   {
      CopyAcceleratorTable(m_hAccelTable,lpAccelNew,nAccelerators);
   }

   UINT nCmdID;
   int i;
   for ( i = 0; i < nAccelerators; i++ )
   {
      if ( lpAccelNew[i].fVirt == fVirt && lpAccelNew[i].key == key )
      {
         i++;
         nCmdID = lpAccelNew[i].cmd;
         break;
      }
   }

   if ( nAccelerators <= i )
   {
      LocalFree(lpAccelNew);
      return FALSE;
   }

   for ( ; i < nAccelerators; i++ )
   {
      lpAccelNew[i] = lpAccelNew[i-1];
   }

   DestroyAcceleratorTable(m_hAccelTable);
   m_hAccelTable = CreateAcceleratorTable(lpAccelNew,nAccelerators-1);

   m_pCmdMgr->RemoveCommandCallback(nCmdID);

   LocalFree(lpAccelNew);

   return TRUE;
}

BOOL AcceleratorTable::TranslateMessage(CWnd* pWnd,MSG* pMsg)
{
   return (m_hAccelTable != nullptr && ::TranslateAccelerator(pWnd->GetSafeHwnd(),m_hAccelTable,pMsg));
}
