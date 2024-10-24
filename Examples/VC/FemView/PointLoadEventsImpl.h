#ifndef INCLUDED_POINTLOADEVENTSIMPL_H_
#define INCLUDED_POINTLOADEVENTSIMPL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointLoadEventsImpl.h : header file
//

using namespace WBFL::DManip;

class CFEA2DDoc;

/////////////////////////////////////////////////////////////////////////////
// CPointLoadEventsImpl command target

class CPointLoadEventsImpl : public iPointLoadEvents, public iDisplayObjectEvents, public iDragData
{
public:
   CPointLoadEventsImpl(CFEA2DDoc* pDoc);
   ~CPointLoadEventsImpl();

   // iPointLoadEvents
   void InitFromLoad(IFem2dPointLoad* load) override;

   // iDisplayObjectEvents
   bool OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseMove(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseWheel(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point) override;
   bool OnKeyDown(std::shared_ptr<iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags) override;
   bool OnContextMenu(std::shared_ptr<iDisplayObject> pDO, CWnd* pWnd, const POINT& point) override;
   void OnChanged(std::shared_ptr<iDisplayObject> pDO) override;
   void OnDragMoved(std::shared_ptr<iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset) override;
   void OnMoved(std::shared_ptr<iDisplayObject> pDO) override;
   void OnCopied(std::shared_ptr<iDisplayObject> pDO) override;
   void OnSelect(std::shared_ptr<iDisplayObject> pDO) override;
   void OnUnselect(std::shared_ptr<iDisplayObject> pDO) override;

   // iDragData
   UINT Format() override;
   bool PrepareForDrag(std::shared_ptr<iDisplayObject> pDO, std::shared_ptr<iDragDataSink> pSink) override;
   void OnDrop(std::shared_ptr<iDisplayObject> pDO, std::shared_ptr<iDragDataSource> pSource) override;

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
