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


// UnitsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "UnitsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnitsDlg dialog


CUnitsDlg::CUnitsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnitsDlg)
	m_Units = -1;
	//}}AFX_DATA_INIT
}


void CUnitsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnitsDlg)
	DDX_Radio(pDX, IDC_US_UNITS, m_Units);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUnitsDlg, CDialog)
	//{{AFX_MSG_MAP(CUnitsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnitsDlg message handlers
