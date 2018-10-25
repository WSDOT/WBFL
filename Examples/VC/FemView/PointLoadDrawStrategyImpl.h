#ifndef INCLUDED_POINTLOADDRAWSTRATEGYIMPL_H_
#define INCLUDED_POINTLOADDRAWSTRATEGYIMPL_H_

class CPointLoadDrawStrategyImpl : public CCmdTarget
{
public:
   CPointLoadDrawStrategyImpl();
   ~CPointLoadDrawStrategyImpl()
   {;}

   void Init(IFem2dPointLoad* pLoad,COLORREF color);

   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(Strategy,iPointLoadDrawStrategy)
      STDMETHOD_(void,SetLoad)(IFem2dPointLoad* load);
      STDMETHOD_(void,SetColor)(COLORREF color);
   END_INTERFACE_PART(Strategy)


   BEGIN_INTERFACE_PART(DrawPointStrategy,iDrawPointStrategy)
      STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
      STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
      STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
      STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO,IRect2d** ppRect);
   END_INTERFACE_PART(DrawPointStrategy)

private:
   virtual void Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc);
   CComPtr<IFem2dPointLoad> m_Load;
   COLORREF m_Color;
};

#endif // INCLUDED_POINTLOADDRAWSTRATEGYIMPL_H_