///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// InplaceEdit.cpp : implementation file
//

#include "stdafx.h"
#include <DManip\InplaceEditCtrl.h>

#include <DManip\Task.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInplaceEdit

CInplaceEdit::CInplaceEdit()
{
   m_pTask = 0;
}

CInplaceEdit::~CInplaceEdit()
{
}

void CInplaceEdit::SetTask(iTask* pTask)
{
   m_pTask = pTask;
}

BEGIN_MESSAGE_MAP(CInplaceEdit, CEdit)
	//{{AFX_MSG_MAP(CInplaceEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInplaceEdit message handlers

void CInplaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   ASSERT(m_pTask != 0);
   m_pTask->AddRef();
   m_pTask->OnKeyDown(nChar,nRepCnt,nFlags);

	CEdit::OnChar(nChar, nRepCnt, nFlags);
   m_pTask->Release();
}
