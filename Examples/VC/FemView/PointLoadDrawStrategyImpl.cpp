#include "stdafx.h"
#include "FEA2D.h"
#include "PointLoadDrawStrategyImpl.h"
#include "mfcdual.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// make our symbols 5/8" in size
static const long SSIZE = 1440 * 5/8; // (twips)

CPointLoadDrawStrategyImpl::CPointLoadDrawStrategyImpl()
{
}

void CPointLoadDrawStrategyImpl::SetLoad(IFem2dPointLoad* load)
{
   m_Load = load;
}

void CPointLoadDrawStrategyImpl::SetColor(COLORREF color)
{
   m_Color = color;
}

void CPointLoadDrawStrategyImpl::Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = m_Color;

   auto pos = pDO->GetPosition();

   Draw(pDO,pDC,color,pos);
}

void CPointLoadDrawStrategyImpl::DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const
{
   Draw(pDO,pDC);
}

void CPointLoadDrawStrategyImpl::DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& cpdragPoint) const
{
   auto dragPoint = map->LPtoWP(cpdragPoint.x, cpdragPoint.y);
   Draw(pDO,pDC,RGB(255,0,0),dragPoint);
}

WBFL::Geometry::Rect2d CPointLoadDrawStrategyImpl::GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   auto point = pDO->GetPosition();

   auto [px,py] = point.GetLocation();

   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   
   auto pMap = pDispMgr->GetCoordinateMap();

   double xo,yo;
   pMap->TPtoWP(0,0,&xo,&yo);
   double x2,y2;
   pMap->TPtoWP(SSIZE,SSIZE,&x2,&y2);

   double wid = fabs(x2-xo)/2.0;
   double hgt = fabs(y2-yo)/2.0;

   return WBFL::Geometry::Rect2d(px - wid, py - hgt, px + wid, py + hgt);
}


void CPointLoadDrawStrategyImpl::Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,COLORREF color,const WBFL::Geometry::Point2d& loc) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();

   auto pMap = pDispMgr->GetCoordinateMap();

   long cx,cy;
   pMap->WPtoLP(loc,&cx,&cy);

   // height and width
   long xo,yo;
   pMap->TPtoLP(0,0,&xo,&yo);
   long x2,y2;
   pMap->TPtoLP(SSIZE,SSIZE,&x2,&y2);
   long wid = abs(x2-xo)/2;
   long hgt = abs(y2-yo)/2;

   CPen pen(PS_SOLID,2,color);
   CPen* pOldPen = pDC->SelectObject(&pen);

   Float64 fx,fy,mz;
   m_Load->get_Fx(&fx);
   m_Load->get_Fy(&fy);
   m_Load->get_Mz(&mz);

   if ( !IsZero(fx) )
   {
      // Loaded in the X direction
      pDC->MoveTo(cx-wid,cy);
      pDC->LineTo(cx,cy);


      // draw arrow head
      long x = cx;
      long sign = 1;
      if ( fx < 0 )
      {
         x = cx - wid;
         sign = -1;
      }
      
      pDC->MoveTo(x - sign*wid/4,cy+hgt/4);
      pDC->LineTo(x,cy);
      
      pDC->MoveTo(x - sign*wid/4,cy-hgt/4);
      pDC->LineTo(x,cy);
   }

   if ( !IsZero(fy) )
   {
      // Loaded in the Y direction
      pDC->MoveTo(cx,cy+hgt);
      pDC->LineTo(cx,cy);
      
      long y = cy;
      long sign = 1;
      if ( fy < 0 )
      {
         y = cy + hgt;
         sign = -1;
      }
      pDC->MoveTo(cx-wid/4,y + sign*hgt/4);
      pDC->LineTo(cx,y);
      
      pDC->MoveTo(cx+wid/4,y + sign*hgt/4);
      pDC->LineTo(cx,y);
   }

   if ( !IsZero(mz) )
   {
      // Moment 
      pDC->Arc(CRect(CPoint(cx-wid/2,cy-hgt/2),CSize(wid,hgt)),
               CPoint(cx-wid/2,cy),CPoint(cx+wid/2,cy));

      if ( mz < 0 )
      {
         // CCW
         pDC->MoveTo(CPoint(cx+wid/2,cy));
         pDC->LineTo(CPoint(cx+wid/2-wid/4,cy+hgt/4));

         pDC->MoveTo(CPoint(cx+wid/2,cy));
         pDC->LineTo(CPoint(cx+wid/2+wid/4,cy+hgt/4));
      }
      else
      {
         // CW
         pDC->MoveTo(CPoint(cx-wid/2,cy));
         pDC->LineTo(CPoint(cx-wid/2-wid/4,cy+hgt/4));

         pDC->MoveTo(CPoint(cx-wid/2,cy));
         pDC->LineTo(CPoint(cx-wid/2+wid/4,cy+hgt/4));
      }
   }

   pDC->SelectObject(pOldPen);
}
