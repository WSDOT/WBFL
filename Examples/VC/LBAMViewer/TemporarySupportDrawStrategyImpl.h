#ifndef INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGYIMPL_H_
#define INCLUDED_TEMPORARYSUPPORTDRAWSTRATEGYIMPL_H_

#include "TemporarySupportDrawStrategy.h"

class CTemporarySupportDrawStrategyImpl : public CCmdTarget
{
public:
   CTemporarySupportDrawStrategyImpl(CLBAMViewerDoc* pDoc);


   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(Strategy,iTemporarySupportDrawStrategy)
      STDMETHOD_(void,SetTemporarySupport)(ITemporarySupport* jnt, IDType supportID);
   END_INTERFACE_PART(Strategy)

   BEGIN_INTERFACE_PART(DrawPointStrategy,iDrawPointStrategy)
      STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
      STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint);
      STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
      STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO,IRect2d**box);
   END_INTERFACE_PART(DrawPointStrategy)

private:
   CLBAMViewerDoc* m_pDoc;
   CComPtr<ITemporarySupport> m_Support;
   IDType                       m_SupportID;

   virtual void Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc);

};

#endif // INCLUDED_SUPPORTDRAWSTRATEGYIMPL_H_