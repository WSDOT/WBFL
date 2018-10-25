///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// EAFGraphBuilderBase.h : header file
//

#include <EAF\EAFExp.h>

class CEAFGraphBuilderBase;

/////////////////////////////////////////////////////////////////////////////
// CEAFGraphControlWindow
//
// A window that the user interacts with to control the contents of a graph.
class EAFCLASS CEAFGraphControlWindow : public CDialogBar
{
public:
   CEAFGraphControlWindow();
   DECLARE_DYNCREATE(CEAFGraphControlWindow);

   // Sets a pointer to a command target to route commands to.
   // The command target is usually a CEAFGraphBuilderBase object.
   // The EAF framework sets up the command routing so there isn't a need
   // to call this method unless you want to change the command rounting
   void SetCommandTarget(CCmdTarget* pCmdTarget);

   void SetGraphBuilder(CEAFGraphBuilderBase* pBuilder);
   CEAFGraphBuilderBase* GetGraphBuilder();

protected:
   CCmdTarget* m_pCmdTarget; // pointer to the command target
   CEAFGraphBuilderBase* m_pGraphBuilder;

   // Simulates OnInitDialog for CDialog based windows
   virtual BOOL OnInitDialog();

	//{{AFX_MSG(CTestDialogBar)
   //}}AFX_MSG
   afx_msg int OnCreate(LPCREATESTRUCT lpcs);
   afx_msg LRESULT OnInitDialog(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()

   virtual BOOL OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo);

#ifdef _DEBUG
public:
   void AssertValid() const;
   void Dump(CDumpContext& dc) const;
#endif //_DEBUG
};
