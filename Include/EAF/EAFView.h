///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// EAFView.h : header file
//

#include <EAF\EAFExp.h>

// in C++ friendship is not inherited. Therefore derivatives of CDocument
// cannot call CView::OnUpdate() because CView::OnUpdate is protected.
// The purpose of CEAFView is to make CEAFDocument a friend so CEAFDocuments
// can call CEAFView::OnUpdate.


/////////////////////////////////////////////////////////////////////////////
// CEAFView view
class EAFCLASS CEAFView : public CView
{
protected:
	CEAFView();           // protected constructor used by dynamic creation
	DECLARE_DYNAMIC(CEAFView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFView)
	//}}AFX_VIRTUAL

// Implementation
public:

protected:
	virtual ~CEAFView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   // Generated message map functions
protected:
	//{{AFX_MSG(CEAFView)
	//}}AFX_MSG

   friend class CEAFDocument;

   DECLARE_MESSAGE_MAP()
};
