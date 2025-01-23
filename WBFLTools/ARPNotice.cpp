///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ARPNotice.cpp : Implementation of CARPNotice
#include "stdafx.h"
#include "WBFLTools.h"
#include "ARPNotice.h"
#include "LegalWiz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CARPNotice

STDMETHODIMP CARPNotice::Show(VARIANT_BOOL bGiveChoice,LicenseType lt,AcceptanceType* accept)
{
   CWnd* pWnd;
   {
      AFX_MANAGE_STATE(AfxGetAppModuleState());
      pWnd = AfxGetMainWnd();
   }

   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   CLegalWiz wiz( pWnd, lt == ltAROSL ? IDR_AROSL : IDR_ARLOSL );
   wiz.GiveChoice( bGiveChoice );
   wiz.ShowLegalNoticeAgain( m_bShowAgain );
   INT_PTR result = wiz.DoModal();
   m_bShowAgain = wiz.ShowLegalNoticeAgain();

   *accept = ( result == IDCANCEL ) ? atReject : atAccept;

	return S_OK;
}

STDMETHODIMP CARPNotice::get_ShowAgain(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   *pVal = m_bShowAgain;
	return S_OK;
}

STDMETHODIMP CARPNotice::put_ShowAgain(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   m_bShowAgain = newVal;
	return S_OK;
}
