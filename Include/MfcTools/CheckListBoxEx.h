///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2020  Washington State Department of Transportation
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

////////////////////////////////////////////
//  Specialized CheckListBox control that:
//     1) Avoids overlap of checkbox items
//     2) Provides tooltips for list items
////////////////////////////////////////////
class MFCTOOLSCLASS CCheckListBoxEx : public CCheckListBox
{
// Construction
public:
	CCheckListBoxEx();

// Attributes
public:
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const override;
	UINT ItemFromPoint2(CPoint pt, BOOL& bOutside) const;
//	void PreSubclassWindow() ;
	
	BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckListBoxEx)
	protected:
	virtual void PreSubclassWindow();
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCheckListBoxEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckListBoxEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};


