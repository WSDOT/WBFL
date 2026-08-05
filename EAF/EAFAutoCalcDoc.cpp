///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2026  Washington State Department of Transportation
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
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFUIIntegration.h>
#include <AgentTools.h>


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
   // This mixin is always used by a broker-based document (CEAFBrokerDocument), so go through the
   // broker-registered IEAFAcceleratorTable rather than reaching CEAFMainFrame's accelerator table
   // directly - see WBFL EAF UI Integration devdocs.
   auto* pBrokerDoc = dynamic_cast<CEAFBrokerDocument*>(m_pDocument);
   ATLASSERT(pBrokerDoc);
   auto pBroker = pBrokerDoc->GetBroker();
   GET_IFACE2(pBroker,IEAFAcceleratorTable,pAccelTable);
   pAccelTable->AddAccelKey(FVIRTKEY,           VK_F5, EAFID_AUTOCALC_UPDATENOW,nullptr);
   pAccelTable->AddAccelKey(FCONTROL | FVIRTKEY,VK_U,  EAFID_AUTOCALC_UPDATENOW,nullptr);
}

void CEAFAutoCalcDocMixin::RemoveAcceleratorKeys()
{
   auto* pBrokerDoc = dynamic_cast<CEAFBrokerDocument*>(m_pDocument);
   ATLASSERT(pBrokerDoc);
   auto pBroker = pBrokerDoc->GetBroker();
   GET_IFACE2(pBroker,IEAFAcceleratorTable,pAccelTable);
   pAccelTable->RemoveAccelKey(FVIRTKEY,           VK_F5);
   pAccelTable->RemoveAccelKey(FCONTROL | FVIRTKEY,VK_U );
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
