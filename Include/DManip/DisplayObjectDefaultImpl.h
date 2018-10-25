///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// DisplayObjectDefaultImpl.h: interface for the CDisplayObjectDefaultImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYOBJECTDEFAULTIMPL_H__BCB8A107_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_DISPLAYOBJECTDEFAULTIMPL_H__BCB8A107_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DManip\DManipExp.h>
#include <DManip\DisplayObject.h>
#include <DManip\DisplayList.h>

#include <set>

struct iDropSite;
interface ISize2d;

class DMANIPCLASS CDisplayObjectDefaultImpl
{
public:
	CDisplayObjectDefaultImpl();
	virtual ~CDisplayObjectDefaultImpl();

   void SetDisplayObject(iDisplayObject* pParent);

   // iDisplayObject implementation
   virtual void Do_SetID(IDType id);
   virtual IDType Do_GetID();

   virtual void Do_SetItemData(void* pVoid,bool bDelete);
   virtual void Do_GetItemData(void** ppVoid);

   virtual void Do_SetDisplayList(iDisplayList * pList);
   virtual void Do_GetDisplayList(iDisplayList** list);

   virtual void Do_Visible(BOOL bVisible);
   virtual BOOL Do_IsVisible();
#if defined(_DEBUG)
   virtual void Do_DrawGravityWell(CDC* pDC);
#endif 

   // Size and Hit Testing
   virtual void Do_SetGravityWellStrategy(iGravityWellStrategy* pStrategy);
   virtual void Do_GetGravityWellStrategy(iGravityWellStrategy** pStrategy);
   virtual BOOL Do_HitTest(CPoint point);
   virtual BOOL Do_TouchesRect(CRect r);
   virtual CRect Do_GetBoundingBox();

   // Selection
   virtual void Do_Select(BOOL bSelect);
   virtual BOOL Do_IsSelected();
   virtual void Do_SetSelectionType(SelectionType st);
   virtual SelectionType Do_GetSelectionType();

   // Tool Tips
   virtual void Do_SetToolTipText(LPCTSTR lpszToolTipText);
   virtual CString Do_GetToolTipText();
   virtual void Do_SetMaxTipWidth(INT maxWidth);
   virtual INT Do_GetMaxTipWidth();
   virtual void Do_SetTipDisplayTime(INT iTime);
   virtual INT Do_GetTipDisplayTime();


   // Interface Events
   virtual bool Do_OnLButtonDown(UINT nFlags,CPoint point);
   virtual bool Do_OnLButtonUp(UINT nFlags,CPoint point);
   virtual bool Do_OnLButtonDblClk(UINT nFlags,CPoint point);
   virtual bool Do_OnRButtonDown(UINT nFlags,CPoint point);
   virtual bool Do_OnRButtonUp(UINT nFlags,CPoint point);
   virtual bool Do_OnRButtonDblClk(UINT nFlags,CPoint point);
   virtual bool Do_OnMouseMove(UINT nFlags,CPoint point);
   virtual bool Do_OnMouseWheel(UINT nFlags,short zDelta,CPoint point);
   virtual bool Do_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   virtual bool Do_OnContextMenu(CWnd* pWnd,CPoint point);

   // Event Sinks
   virtual void Do_RegisterEventSink(iDisplayObjectEvents* pEventSink);
   virtual void Do_UnregisterEventSink();
   virtual void Do_GetEventSink(iDisplayObjectEvents** pEventSink);

   // Drag Drop
   virtual void Do_SetDropSite(iDropSite* pDropSite);
   virtual void Do_GetDropSite(iDropSite** dropSite);

   // Notifies all sinks of display object events
   virtual void Fire_OnChanged();
   virtual void Fire_OnDragMoved(ISize2d* offset);
   virtual void Fire_OnMoved();
   virtual void Fire_OnCopied();
   virtual bool Fire_OnLButtonDown(UINT nFlags,CPoint point);
   virtual bool Fire_OnLButtonUp(UINT nFlags,CPoint point);
   virtual bool Fire_OnLButtonDblClk(UINT nFlags,CPoint point);
   virtual bool Fire_OnRButtonDown(UINT nFlags,CPoint point);
   virtual bool Fire_OnRButtonUp(UINT nFlags,CPoint point);
   virtual bool Fire_OnRButtonDblClk(UINT nFlags,CPoint point);
   virtual bool Fire_OnMouseMove(UINT nFlags,CPoint point);
   virtual bool Fire_OnMouseWheel(UINT nFlags,short zDelta,CPoint point);
   virtual bool Fire_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   virtual bool Fire_OnContextMenu(CWnd* pWnd,CPoint point);
   virtual void Fire_OnSelect();
   virtual void Fire_OnUnselect();


protected:
   IDType m_ID;
   BOOL m_bIsVisible;
   iDisplayObject* m_pParent;
   CComPtr<iGravityWellStrategy> m_pGravityWellStrategy;
   iDisplayList* m_pDispList;
   CComPtr<iDropSite> m_pDropSite;
   BOOL m_bSelected;
   CString m_strToolTipText;
   INT m_MaxToolTipWidth;
   INT m_ToolTipDisplayTime;
   SelectionType m_SelectionType;
   CComPtr<IRect2d> m_ReusableRect;

   void* m_pItemData;
   bool m_bDeleteItemData;

   CComPtr<iDisplayObjectEvents> m_EventSink;
};

#endif // !defined(AFX_DISPLAYOBJECTDEFAULTIMPL_H__BCB8A107_E659_11D4_8B81_006097C68A9C__INCLUDED_)
