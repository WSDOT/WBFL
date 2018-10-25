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

#ifndef INCLUDED_EAFSTATUSBAR_H_
#define INCLUDED_EAFSTATUSBAR_H_

#pragma once


// CEAFStatusBar

#include <EAF\EAFExp.h>

class CEAFDocument;

class EAFCLASS CEAFStatusBar : public CStatusBar
{
	DECLARE_DYNAMIC(CEAFStatusBar)

public:
	CEAFStatusBar();
	virtual ~CEAFStatusBar();

   /// Enables/disables the "Modified" flag on the status bar
   virtual void EnableModifiedFlag(BOOL bEnable);
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
   virtual void OnStatusChanged();

   virtual void Reset();

#ifdef _DEBUG
   virtual void AssertValid() const;
#endif

protected:
   //{{AFX_MSG(CEAFStatusBar)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   //}}AFX_MSG

	DECLARE_MESSAGE_MAP()

   virtual void GetStatusIndicators(const UINT** lppIDArray,int* pnIDCount);

   // Returns the pane index for the "Modified" flag
   int GetPaneCount();
   int GetModifiedPaneIndex();
   int GetStatusPaneIndex();

   CEAFDocument* GetDocument();

private:
   int m_nIndicators;
   int m_ModifiedPaneIdx;
   int m_StatusPaneIdx;


public:
   virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, UINT nID = AFX_IDW_STATUS_BAR);
};


#endif // INCLUDED_EAFSTATUSBAR_H_