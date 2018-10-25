///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <EAF\EAFReportView.h>

// CReportButton
// This class is a special button to go on top of CEAFReportView. This is a solution to a
// problem with display of the button on top of the IE web control. The button needs to be 
// a child of the IE control to display right, but then the IE control eats notifications
// so they don't get back to the CEAFReportView. This class makes the CEAFReportView a 
// direct listener to solve that problem.

class CReportButton : public CButton
{
	DECLARE_DYNAMIC(CReportButton)

public:
	CReportButton();
	virtual ~CReportButton();

   void Register(CEAFReportView* pView);

protected:
     afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
     afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()

private:
   bool m_bIsButtonDown;

   CEAFReportView* m_pListener; // view will be listening for our clicks
};


