#pragma once

#include <DManip/DisplayObjectEvents.h>
#include <memory>

class CDataPointEventsImpl : public WBFL::DManip::iDisplayObjectEvents
{
public:
   static UINT ms_Format;

   bool OnLButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnLButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnRButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseMove(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, const POINT& point) override;
   bool OnMouseWheel(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point) override;
   bool OnKeyDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags) override;
   bool OnContextMenu(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, CWnd* pWnd, const POINT& point) override;
   void OnChanged(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnDragMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset) override;
   void OnMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnCopied(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnSelect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
   void OnUnselect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO) override;
};