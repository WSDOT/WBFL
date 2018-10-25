///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_TASK_H_
#define INCLUDED_TASK_H_
#pragma once

interface iTask : public IUnknown
{
   STDMETHOD_(void,Start)() PURE;

   STDMETHOD_(void,OnLButtonDown)(UINT nFlags, const CPoint& point) PURE;
	STDMETHOD_(void,OnLButtonUp)(UINT nFlags,const CPoint& point) PURE;
   STDMETHOD_(void,OnLButtonDblClk)(UINT nFlags,const CPoint& point) PURE;

   STDMETHOD_(void,OnRButtonDown)(UINT nFlags, const CPoint& point) PURE;
	STDMETHOD_(void,OnRButtonUp)(UINT nFlags,const CPoint& point) PURE;
   STDMETHOD_(void,OnRButtonDblClk)(UINT nFlags,const CPoint& point) PURE;

   STDMETHOD_(void,OnMouseMove)(UINT nFlags, const CPoint& point) PURE;
   STDMETHOD_(void,OnMouseWheel)(UINT nFlags, short zDelta, const CPoint& point) PURE;

   STDMETHOD_(void,OnContextMenu)(CWnd* pWnd, const CPoint& point) PURE;

   STDMETHOD_(void,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags)  PURE;

   STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) PURE;
   STDMETHOD_(void,OnDragLeave)() PURE;
   STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) PURE;
   STDMETHOD_(DROPEFFECT,OnDragScroll)(DWORD dwKeyState,CPoint point) PURE;
   STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) PURE;
   STDMETHOD_(DROPEFFECT,OnDropEx)(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) PURE;
};

#endif // INCLUDED_TASK_H_