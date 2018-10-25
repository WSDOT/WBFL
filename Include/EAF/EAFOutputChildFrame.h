///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <EAF\EAFExp.h>
#include <EAF\EAFLicensePlateChildFrame.h>

// :TRICKY: rab 11.23.96 : Modifying default behavior
// :FILE: ChildFrm.h
//
// We override CMDIChildWnd to customize the MDI child's title bar.
// By default the title bar shows the document name.  But we want
// it to instead show the text defined as the first string in
// the document template STRINGTABLE resource.  This string is
// the name of the view.  If we didn't customize the title bar, two
// MDI child windows containing differnt view types would
// show MYDOC:1 and MYDOC:2 if the document were named MYDOC.

class EAFCLASS CEAFOutputChildFrame : public CEAFLicensePlateChildFrame
{
	DECLARE_DYNCREATE(CEAFOutputChildFrame)
public:
	CEAFOutputChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFOutputChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEAFOutputChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   void OnUpdateFrameTitle(BOOL bAddToTitle);

   // Generated message map functions
protected:
	//{{AFX_MSG(COutputChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
