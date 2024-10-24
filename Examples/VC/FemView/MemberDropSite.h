// MemberDropSite.h: interface for the CMemberDropSite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBERDROPSITE_H__1F8A97C9_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
#define AFX_MEMBERDROPSITE_H__1F8A97C9_F789_11D4_8B9B_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace WBFL::DManip;

class CMemberDropSite : public iDisplayObjectEvents, public iDropSite
{
public:
	CMemberDropSite(CFEA2DDoc* pDoc);
	virtual ~CMemberDropSite();

   // iDisplayObjectEvents Implementation
   void OnChanged(std::shared_ptr<iDisplayObject> pDO) override;
   void OnDragMoved(std::shared_ptr<iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset) override;
   bool OnKeyDown(std::shared_ptr<iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags) override;
   bool OnContextMenu(std::shared_ptr<iDisplayObject> pDO, CWnd* pWnd, const POINT& point) override;
   bool OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseMove(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseWheel(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point) override;
   void OnMoved(std::shared_ptr<iDisplayObject> pDO) override;
   void OnCopied(std::shared_ptr<iDisplayObject> pDO) override;
   void OnSelect(std::shared_ptr<iDisplayObject> pDO) override;
   void OnUnselect(std::shared_ptr<iDisplayObject> pDO) override;

   // iDropSite
   DROPEFFECT CanDrop(COleDataObject* pDataObject, DWORD dwKeyState, const WBFL::Geometry::Point2d& point) override;
   void OnDropped(COleDataObject* pDataObject, DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point) override;
   void SetDisplayObject(std::weak_ptr<iDisplayObject> pDO) override;
   std::shared_ptr<iDisplayObject> GetDisplayObject() override;
   void Highlight(CDC* pDC, BOOL bHighlight) override;

private:
   CFEA2DDoc* m_pDoc;
   std::weak_ptr<iDisplayObject> m_DispObj;

   void DeleteMember(IDType mbrID);
   void EditMember(IDType mbrID);
};

#endif // !defined(AFX_MEMBERDROPSITE_H__1F8A97C9_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
