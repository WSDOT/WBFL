#ifndef INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGYIMPL_H_
#define INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGYIMPL_H_

#include "TemporarySupportDrawStrategy.h"

class CTemporarySupportDrawStrategyImpl : public iTemporarySupportDrawStrategy, public WBFL::DManip::iDrawPointStrategy
{
public:
   CTemporarySupportDrawStrategyImpl(CLBAMViewerDoc* pDoc);


   void SetTemporarySupport(ITemporarySupport* jnt, IDType supportID) override;

   void Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC) const override;
   void DrawDragImage(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::DManip::iCoordinateMap> map, const POINT& dragStart, const POINT& cpdragPoint) const override;
   void DrawHighlight(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO, CDC* pDC, bool bHighlite) const override;
   WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO) const override;

private:
   CLBAMViewerDoc* m_pDoc;
   CComPtr<ITemporarySupport> m_Support;
   IDType                       m_SupportID;

   virtual void Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO,CDC* pDC,COLORREF color,const WBFL::Geometry::Point2d& loc) const;
};

#endif // INCLUDED_SUPPORTDRAWSTRATEGYIMPL_H_