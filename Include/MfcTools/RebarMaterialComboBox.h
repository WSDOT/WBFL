///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2024  Washington State Department of Transportation
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
#pragma once

#include <MfcTools\MfcToolsExp.h>
#include <Lrfd\Lrfd.h>

/////////////////////////////////////////////////////////////////////////////
// CRebarMaterialComboBox window

void MFCTOOLSFUNC DDX_RebarMaterial(CDataExchange* pDX,UINT nIDC,WBFL::Materials::Rebar::Type& type,WBFL::Materials::Rebar::Grade& grade);

class MFCTOOLSCLASS CRebarMaterialComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CRebarMaterialComboBox)

public:
	CRebarMaterialComboBox();
	virtual ~CRebarMaterialComboBox();

   void Initialize(bool bFilterBySpec=true);

   void GetMaterial(WBFL::Materials::Rebar::Type* pType,WBFL::Materials::Rebar::Grade* pGrade);
   void SetMaterial(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRebarMaterialComboBox)
   virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRebarMaterialComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
