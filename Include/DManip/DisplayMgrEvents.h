///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include <DManip\DisplayMgr.h>

interface iDisplayMgrEvents : public IUnknown
{
   // UI Events that are directed towards the display object
   STDMETHOD_(bool,OnLButtonDblClk)(iDisplayMgr* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonDown)(iDisplayMgr* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonUp)(iDisplayMgr* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDblClk)(iDisplayMgr* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDown)(iDisplayMgr* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonUp)(iDisplayMgr* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnMouseMove)(iDisplayMgr* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnMouseWheel)(iDisplayMgr* pDO,UINT nFlags,short zDelta,CPoint point) PURE;
   STDMETHOD_(bool,OnKeyDown)(iDisplayMgr* pDO,UINT nChar, UINT nRepCnt, UINT nFlags) PURE;
   STDMETHOD_(bool,OnContextMenu)(iDisplayMgr* pDO,CWnd* pWnd,CPoint point) PURE;
};
