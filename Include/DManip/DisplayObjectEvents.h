///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_DISPLAYOBJECTEVENTS_H_
#define INCLUDED_DISPLAYOBJECTEVENTS_H_
#pragma once

interface iDisplayObjectEvents : public IUnknown
{
   // UI Events that are directed towards the display object
   STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point) PURE;
   STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags) PURE;
   STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point) PURE;

   // The display object contains some internal data that was changed
   STDMETHOD_(void,OnChanged)(iDisplayObject* pDO) PURE;

   // The display object was moved to a different location on the canvas via
   // dragging
   STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset) PURE;

   // The display object was drag and dropped
   STDMETHOD_(void,OnMoved)(iDisplayObject* pDO) PURE;

   // The display object was drag/dropped copied
   STDMETHOD_(void,OnCopied)(iDisplayObject* pDO) PURE;

   STDMETHOD_(void,OnSelect)(iDisplayObject* pDO) PURE;
   STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO) PURE;
};

#endif // INCLUDED_DISPLAYOBJECTEVENTS_H_