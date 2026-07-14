
#pragma once
// EditMbrLength.h : header file
//

using namespace WBFL::DManip;


/////////////////////////////////////////////////////////////////////////////
// CEditMbrLength command target

class CEditMbrLength : public iDisplayObjectEvents
{
public:
	CEditMbrLength(CFEA2DDoc* pDoc);
   virtual ~CEditMbrLength();

// Attributes
public:

// Operations
public:

   // iDisplayObjectEvents
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

private:
   CFEA2DDoc* m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

