#ifndef INCLUDED_JOINTDRAWSTRATEGYIMPL_H_
#define INCLUDED_JOINTDRAWSTRATEGYIMPL_H_

class CJointDrawStrategyImpl : public CCmdTarget
{
public:
   CJointDrawStrategyImpl(CFEA2DDoc* pDoc);
   ~CJointDrawStrategyImpl()
   {;}


   DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(Strategy,iJointDrawStrategy)
      STDMETHOD_(void,SetJoint)(IFem2dJoint* jnt);
   END_INTERFACE_PART(Strategy)

   BEGIN_INTERFACE_PART(DrawPointStrategy,iDrawPointStrategy)
      STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
      STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
      STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
      STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO,IRect2d** ppRect);
   END_INTERFACE_PART(DrawPointStrategy)

private:
   CFEA2DDoc* m_pDoc;
   CComPtr<IFem2dJoint> m_Joint;

   virtual void Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc);
};

#endif // INCLUDED_JOINTDRAWSTRATEGYIMPL_H_