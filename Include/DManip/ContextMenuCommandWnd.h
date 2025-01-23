///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <DManip/ContextMenuCommandCallback.h>

#define MC_MSG_BASE 100
#define MC_MSG_MAX  200

/// @brief A specialized window to capture user interaction events in the legend
/// This class is not a visible window. It's sole purpose is to catch messages from
/// context menus associated with a display object.
/// 
/// Context menus will direct command messages to this window. This window will 
/// in turn forward the menu command to the iMessageListener object
/// 
/// Context menu command IDs must be in the range MC_MSG_BASE and MC_MSG_MAX
class CContextMenuCommandWnd : public CWnd
{
public:
	CContextMenuCommandWnd() = delete;
	CContextMenuCommandWnd(std::weak_ptr<WBFL::DManip::iContextMenuCommandCallback> plistener);

	virtual ~CContextMenuCommandWnd();

   void OnMessage(UINT id);

protected:
	//{{AFX_MSG(CContextMenuCommandWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	std::weak_ptr<WBFL::DManip::iContextMenuCommandCallback> m_pListener;
};
