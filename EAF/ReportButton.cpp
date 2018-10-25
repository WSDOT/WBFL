///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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
// ReportButton.cpp : implementation file
//

#include "stdafx.h"
#include "ReportButton.h"

// CReportButton

IMPLEMENT_DYNAMIC(CReportButton, CButton)

CReportButton::CReportButton():
m_bIsButtonDown(false),
m_pListener(NULL)
{
}

CReportButton::~CReportButton()
{
}

BEGIN_MESSAGE_MAP(CReportButton, CButton)
     ON_WM_LBUTTONDOWN()
     ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CReportButton message handlers
void CReportButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
   if (m_bIsButtonDown)
   {
      // Fire event to listener
      if (m_pListener)
         m_pListener->NotifyReportButtonWasClicked();
   }

   CButton::OnLButtonUp(nFlags, point);

   m_bIsButtonDown = false;
}

void CReportButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
   CButton::OnLButtonDown(nFlags, point);

   m_bIsButtonDown = true;
}

void CReportButton::Register(CEAFReportView* pView)
{
   ATLASSERT(m_pListener==NULL);
   m_pListener = pView;
}

