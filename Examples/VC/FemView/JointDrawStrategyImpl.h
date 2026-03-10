#ifndef INCLUDED_JOINTDRAWSTRATEGYIMPL_H_
#define INCLUDED_JOINTDRAWSTRATEGYIMPL_H_

using namespace WBFL::DManip;

class CJointDrawStrategyImpl : public iJointDrawStrategy, public iDrawPointStrategy
{
public:
   CJointDrawStrategyImpl(CFEA2DDoc* pDoc);
   ~CJointDrawStrategyImpl()
   {;}

   // iJointDrawStrategy
   void SetJoint(IFem2dJoint* jnt) override;

   // iDrawPointStrategy
   void Draw(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC) const override;
   void DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
   void DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const override;
   WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const override;

private:
   CFEA2DDoc* m_pDoc;
   CComPtr<IFem2dJoint> m_Joint;

    void Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,COLORREF color,const WBFL::Geometry::Point2d& loc) const;
};

#endif // INCLUDED_JOINTDRAWSTRATEGYIMPL_H_