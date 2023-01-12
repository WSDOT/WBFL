///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

// EAFMDISnapper.h: interface for the CMDISnapper class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFChildFrame.h>

class EAFCLASS CEAFMDISnapper
{
public:
   CEAFMDISnapper(DWORD snapWidth = 8);
	virtual ~CEAFMDISnapper();

	void	SetSnapWidth(DWORD snapWidth);
	DWORD	GetSnapWidth() const		{ return m_snapWidth; }

	LRESULT	OnMessage(CEAFChildFrame * wnd, UINT msg, WPARAM wp, LPARAM lp);

	void	OnMoving(CEAFChildFrame * wnd, WPARAM edge, LPRECT newrect);
	void	OnEnterSizeMove(CEAFChildFrame * wnd);
	void	OnExitSizeMove();

   virtual bool AllowSnap();

protected:
	LONG	 m_snapWidth;
   bool   m_bSizeMoveIsSysCommand;    ///< size/move was selected from the menu
	CEAFChildFrame*  m_wndMoving; // this is the window that is being moved
};
