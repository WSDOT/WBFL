///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// EAFAutoCalcGraphView.h : header file
//

#include <EAF\EAFExp.h>
#include <EAF\EAFGraphView.h>
#include <EAF\EAFAutoCalcView.h>

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcGraphView view
class EAFCLASS CEAFAutoCalcGraphView : public CEAFGraphView,
                                       public CEAFAutoCalcViewMixin // mix-in class
{
public:
protected:
	CEAFAutoCalcGraphView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEAFAutoCalcGraphView)

// Attributes
public:

// Operations
public:
   virtual bool DoResultsExist() override;
   virtual void UpdateNow() override;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFGraphView)
public:
	virtual void OnInitialUpdate() override;

protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
	//}}AFX_VIRTUAL

// Implementation
public:

protected:
	virtual ~CEAFAutoCalcGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const override;
	virtual void Dump(CDumpContext& dc) const override;
#endif

   // Generated message map functions
protected:
	//{{AFX_MSG(CEAFAutoCalcGraphView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
