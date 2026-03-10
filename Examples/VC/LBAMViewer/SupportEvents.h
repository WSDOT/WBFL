#ifndef INCLUDED_SUPPORTEVENTS_H_
#define INCLUDED_SUPPORTEVENTS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SupportEvents.h : header file
//

class CLBAMViewerDoc;

/////////////////////////////////////////////////////////////////////////////
// CSupportEvents command target

class CSupportEvents : public WBFL::DManip::iDisplayObjectEvents, public WBFL::DManip::iDragData
{
public:
	CSupportEvents(CLBAMViewerDoc* pDoc);
   ~CSupportEvents();

   // iDisplayObjectEvents Implementation
   void OnChanged(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnDragMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,const WBFL::Geometry::Size2d& offset) override;
   bool OnLButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point) override;
   bool OnLButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point) override;
   bool OnLButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point) override;
   bool OnRButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point) override;
   bool OnRButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point) override;
   bool OnRButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point) override;
   bool OnMouseMove(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point) override;
   bool OnMouseWheel(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,short zDelta,const POINT& point) override;
   void OnMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnCopied(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   bool OnKeyDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags) override;
   bool OnContextMenu(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,CWnd* pWnd,const POINT& point) override;
   void OnSelect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnUnselect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;

   // iDragData Implementation
   UINT Format() override;
   bool PrepareForDrag(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,std::shared_ptr<WBFL::DManip::iDragDataSink> pSink) override;
   void OnDrop(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,std::shared_ptr<WBFL::DManip::iDragDataSource> pSource) override;

public:
   static UINT ms_Format;
   CLBAMViewerDoc* m_pDoc;

private:
   void EditSupport(IDType jntID);
   void DeleteSupport(IDType jntID);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // INCLUDED_SUPPORTEVENTS_H_
