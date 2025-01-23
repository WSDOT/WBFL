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

#ifndef INCLUDED_DATAPOINTEVENTSIMPL_H_
#define INCLUDED_DATAPOINTEVENTSIMPL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataPointEventsImpl.h : header file
//
#include "DataPointEvents.h"


/////////////////////////////////////////////////////////////////////////////
// CDataPointEventsImpl command target

class CDataPointEventsImpl : public CCmdTarget
{
public:
   CDataPointEventsImpl();
   ~CDataPointEventsImpl();

   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(Events,iDataPointEvents)
   END_INTERFACE_PART(Events)

   BEGIN_INTERFACE_PART(DisplayObjectEvents,iDisplayObjectEvents)
      STDMETHOD_(void,OnChanged)(iDisplayObject* pDO) override;
      STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset) override;
      STDMETHOD_(void,OnMoved)(iDisplayObject* pDO) override;
      STDMETHOD_(void,OnCopied)(iDisplayObject* pDO) override;
      STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
      STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
      STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
      STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
      STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
      STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
      STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
      STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point) override;
      STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags) override;
      STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point) override;
      STDMETHOD_(void,OnSelect)(iDisplayObject* pDO) override;
      STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO) override;
   END_INTERFACE_PART(DisplayObjectEvents)

// let's avoid draggability until we figure out how best to use it.
/*
   // iDragData Implementation
   BEGIN_INTERFACE_PART(DragData,iDragData)
      STDMETHOD_(UINT,Format)() override;
      STDMETHOD_(BOOL,PrepareForDrag)(iDisplayObject* pDO,iDragDataSink* pSink) override;
      STDMETHOD_(void,OnDrop)(iDisplayObject* pDO,iDragDataSource* pSource) override;
   END_INTERFACE_PART(DragData)
*/

public:

   static UINT ms_Format;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // INCLUDED_DataPointEVENTSIMPL_H_
