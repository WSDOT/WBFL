#pragma once

using namespace WBFL::DManip;

class CPointLoadDrawStrategyImpl : public iPointLoadDrawStrategy, public iDrawPointStrategy
{
public:
   CPointLoadDrawStrategyImpl();
   ~CPointLoadDrawStrategyImpl()
   {;}

   void Init(WBFL::FEA2D::PointLoad* pLoad,COLORREF color);

   // iPointLoadDrawStrategy
   void SetLoad(WBFL::FEA2D::PointLoad* load) override;
   void SetColor(COLORREF color) override;

   // iDrawPointStrategy
   void Draw(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC) const override;
   void DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const override;
   void DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const override;
   WBFL::Geometry::Rect2d GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const override;

private:
   void Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,COLORREF color, const WBFL::Geometry::Point2d& loc) const;
   WBFL::FEA2D::PointLoad* m_Load;
   COLORREF m_Color;
};

