///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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


// EAFAutoCalcDoc.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFAutoCalcDoc.h>
#include <EAF\EAFAutoCalcView.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcDocMixin
CEAFAutoCalcDocMixin::CEAFAutoCalcDocMixin()
{
   m_pDocument = nullptr;
}

CEAFAutoCalcDocMixin::~CEAFAutoCalcDocMixin()
{
}

void CEAFAutoCalcDocMixin::SetDocument(CEAFDocument* pDoc)
{
   m_pDocument = pDoc;
}

void CEAFAutoCalcDocMixin::CreateAcceleratorKeys()
{
   m_pDocument->GetAcceleratorTable()->AddAccelKey(FVIRTKEY,           VK_F5, EAFID_AUTOCALC_UPDATENOW,nullptr);
   m_pDocument->GetAcceleratorTable()->AddAccelKey(FCONTROL | FVIRTKEY,VK_U,  EAFID_AUTOCALC_UPDATENOW,nullptr);
}

void CEAFAutoCalcDocMixin::RemoveAcceleratorKeys()
{
   m_pDocument->GetAcceleratorTable()->RemoveAccelKey(FVIRTKEY,           VK_F5);
   m_pDocument->GetAcceleratorTable()->RemoveAccelKey(FCONTROL | FVIRTKEY,VK_U );
}

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcDocMixin serialization

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcDocMixin commands

void CEAFAutoCalcDocMixin::OnAutoCalc()
{
   EnableAutoCalc( !IsAutoCalcEnabled() );
}

void CEAFAutoCalcDocMixin::OnUpdateAutoCalc(CCmdUI* pCmdUI)
{
	if ( IsAutoCalcEnabled() )
   {
      pCmdUI->SetText( _T("Turn AutoCalc Off") );
   }
   else
   {
      pCmdUI->SetText( _T("Turn AutoCalc On") );
   }
}

void CEAFAutoCalcDocMixin::OnUpdateNow()
{
   POSITION pos = m_pDocument->GetFirstViewPosition();
   while (pos != nullptr)   
   {
      CView* pView = m_pDocument->GetNextView(pos);
      CEAFAutoCalcViewMixin* pAutoCalcView = dynamic_cast<CEAFAutoCalcViewMixin*>(pView);
      if ( pAutoCalcView )
      {
         pAutoCalcView->OnUpdateNow();
      }
   }
}

void CEAFAutoCalcDocMixin::OnUpdateUpdateNow(CCmdUI* pCmdUI)
{
   if ( IsAutoCalcEnabled() )
      pCmdUI->Enable( FALSE );
   else
      pCmdUI->Enable( TRUE );
}
