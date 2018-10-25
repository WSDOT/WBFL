#ifndef INCLUDED_POINTLOADEVENTSIMPL_H_
#define INCLUDED_POINTLOADEVENTSIMPL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointLoadEventsImpl.h : header file
//

class CFEA2DDoc;

/////////////////////////////////////////////////////////////////////////////
// CPointLoadEventsImpl command target

class CPointLoadEventsImpl : public CCmdTarget
{
public:
   CPointLoadEventsImpl(CFEA2DDoc* pDoc);
   ~CPointLoadEventsImpl();

   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(Events,iPointLoadEvents)
      STDMETHOD_(void,InitFromLoad)(IFem2dPointLoad* load);
   END_INTERFACE_PART(Events)

   BEGIN_INTERFACE_PART(DisplayObjectEvents,iDisplayObjectEvents)
      STDMETHOD_(void,OnChanged)(iDisplayObject* pDO);
      STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset);
      STDMETHOD_(void,OnMoved)(iDisplayObject* pDO);
      STDMETHOD_(void,OnCopied)(iDisplayObject* pDO);
      STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point);
      STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags);
      STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point);
      STDMETHOD_(void,OnSelect)(iDisplayObject* pDO);
      STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO);
   END_INTERFACE_PART(DisplayObjectEvents)

   // iDragData Implementation
   BEGIN_INTERFACE_PART(DragData,iDragData)
      STDMETHOD_(UINT,Format)();
      STDMETHOD_(BOOL,PrepareForDrag)(iDisplayObject* pDO,iDragDataSink* pSink);
      STDMETHOD_(void,OnDrop)(iDisplayObject* pDO,iDragDataSource* pSource);
   END_INTERFACE_PART(DragData)

public:
   CFEA2DDoc* m_pDoc;

   // Because we just can't create a joint load by itself (it must
   // be part of a model) we have to capture the basic data for
   // drag and drop
   IDType m_ID;
   MemberIDType m_MemberID;
   double m_Location;
   Fem2dLoadOrientation m_Orientation;
   LoadCaseIDType m_Loading;
   double m_Fx;
   double m_Fy;
   double m_Mz;

   void EditLoad(IDType loadingID,IDType loadID);
   void DeleteLoad(IDType loadingID,IDType loadID);

   static UINT ms_Format;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // INCLUDED_POINTLOADEVENTSIMPL_H_
