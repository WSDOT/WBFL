#ifndef INCLUDED_JOINTEVENTS_H_
#define INCLUDED_JOINTEVENTS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JointEvents.h : header file
//

class CFEA2DDoc;

using namespace WBFL::DManip;

/////////////////////////////////////////////////////////////////////////////
// CJointEvents command target

class CJointEvents : public WBFL::DManip::iDisplayObjectEvents, public WBFL::DManip::iDragData
{
public:
	CJointEvents(CFEA2DDoc* pDoc);
   ~CJointEvents();

   virtual void OnChanged(std::shared_ptr<iDisplayObject> pDO) override;
   virtual void OnDragMoved(std::shared_ptr<iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset) override;
   virtual bool OnKeyDown(std::shared_ptr<iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags) override;
   virtual bool OnContextMenu(std::shared_ptr<iDisplayObject> pDO, CWnd* pWnd, const POINT& point) override;
   virtual bool OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   virtual bool OnLButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   virtual bool OnLButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   virtual bool OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   virtual bool OnRButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   virtual bool OnRButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   virtual bool OnMouseMove(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   virtual bool OnMouseWheel(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point) override;
   virtual void OnMoved(std::shared_ptr<iDisplayObject> pDO) override;
   virtual void OnCopied(std::shared_ptr<iDisplayObject> pDO) override;
   virtual void OnSelect(std::shared_ptr<iDisplayObject> pDO) override;
   virtual void OnUnselect(std::shared_ptr<iDisplayObject> pDO) override;

   virtual UINT Format() override;
   virtual bool PrepareForDrag(std::shared_ptr<iDisplayObject> pDO, std::shared_ptr<iDragDataSink> pSink) override;
   virtual void OnDrop(std::shared_ptr<iDisplayObject> pDO, std::shared_ptr<iDragDataSource> pSource) override;

public:
   static UINT ms_Format;
   CFEA2DDoc* m_pDoc;

private:
   void EditJoint(IDType jntID);
   void DeleteJoint(IDType jntID);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // INCLUDED_JOINTEVENTS_H_
