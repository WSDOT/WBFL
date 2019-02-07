///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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


// EAFAutoCalcView.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include <EAF\EAFAutoCalcView.h>
#include <EAF\EAFLicensePlateChildFrame.h>
#include <EAF\EAFAutoCalcDoc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcViewMixin

CEAFAutoCalcViewMixin::CEAFAutoCalcViewMixin(CView* pView)
{
   m_pView = pView;

   // Until some results exist, the lp frame is not in use.
   // While the lp frame is not in use, we don't have to worry about
   // turning it on and off
   m_bLpFrameEnabled = false;
}

CEAFAutoCalcViewMixin::~CEAFAutoCalcViewMixin()
{
}

bool CEAFAutoCalcViewMixin::IsLpFrameEnabled() const
{
   return m_bLpFrameEnabled;
}

void CEAFAutoCalcViewMixin::EnableLpFrame(bool bEnable)
{
   // don't want a lp frame if nothing to report
   if ( !DoResultsExist() )
      bEnable = false;

   if ( m_bLpFrameEnabled != bEnable )
   {
      // We are switching modes
      CEAFLicensePlateChildFrame* pLpFrame = GetLpFrame();
      pLpFrame->SetLicensePlateMode( bEnable ? eafTypes::lpfOn : eafTypes::lpfOff );
      m_bLpFrameEnabled = bEnable;
   }
}

CEAFAutoCalcDocMixin* CEAFAutoCalcViewMixin::GetAutoCalcDocument()
{
   CDocument* pDoc = m_pView->GetDocument();
   CEAFAutoCalcDocMixin* pMixin = dynamic_cast<CEAFAutoCalcDocMixin*>(pDoc);
   return pMixin;
}

CEAFLicensePlateChildFrame* CEAFAutoCalcViewMixin::GetLpFrame()
{
   CEAFLicensePlateChildFrame* plp = 0;
   CWnd *pParent = m_pView->GetParentFrame();
   ASSERT_KINDOF(CEAFLicensePlateChildFrame,pParent); // frame must be in a license plate frame
   plp = (CEAFLicensePlateChildFrame*)(pParent);
   return plp;
}

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcViewMixin message handlers

void CEAFAutoCalcViewMixin::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   CEAFAutoCalcDocMixin* pDoc = dynamic_cast<CEAFAutoCalcDocMixin*>(m_pView->GetDocument());
   EnableLpFrame( pDoc->IsAutoCalcEnabled() ? false : true );
}

void CEAFAutoCalcViewMixin::OnUpdateNow()
{
   bool bIsLpFrameEnabled = IsLpFrameEnabled();
   EnableLpFrame( false );

   if ( !DoResultsExist() || bIsLpFrameEnabled )
      UpdateNow();
}

void CEAFAutoCalcViewMixin::Initialize()
{
   CEAFLicensePlateChildFrame* pLpFrame = GetLpFrame();
   pLpFrame->SetBackground(IDB_LPFRAME);
   pLpFrame->SetLicensePlateText("Warning: Contents out of date");
   pLpFrame->SetFramedWindow((CWnd*)m_pView );
}
