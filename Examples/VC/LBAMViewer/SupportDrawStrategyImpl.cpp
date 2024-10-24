#include "stdafx.h"
#include "LBAMViewer.h"
#include "LBAMViewerDoc.h"
#include "SupportDrawStrategyImpl.h"
#include "mfcdual.h"

#define SIZE 20

#include "DrawSupports.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSupportDrawStrategyImpl::CSupportDrawStrategyImpl(CLBAMViewerDoc* pDoc)
{
   m_pDoc = pDoc;
}

void CSupportDrawStrategyImpl::SetSupport(ISupport* support, IDType supportID)
{
   m_Support = support;
   m_SupportID = supportID;
}

void CSupportDrawStrategyImpl::Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO,CDC* pDC) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = RGB(80,60,0);

   auto pos = pDO->GetPosition();
   Draw(pDO,pDC,color,pos);
}

void CSupportDrawStrategyImpl::DrawHighlight(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO,CDC* pDC,bool bHighlite) const
{
   Draw(pDO,pDC);
}

void CSupportDrawStrategyImpl::DrawDragImage(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO,CDC* pDC, std::shared_ptr<const WBFL::DManip::iCoordinateMap> map, const POINT& dragStart, const POINT& cpdragPoint) const
{
   auto dragPoint = map->LPtoWP(cpdragPoint.x, cpdragPoint.y);

   // Draw the support
   Draw(pDO,pDC,RGB(255,0,0),dragPoint);
}

WBFL::Geometry::Rect2d CSupportDrawStrategyImpl::GetBoundingBox(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   auto pMap = pDispMgr->GetCoordinateMap();

   // height and width
   double xo,yo;
   pMap->TPtoWP(0,0,&xo,&yo);
   double x2,y2;
   pMap->TPtoWP(SUPSIZE,SUPSIZE,&x2,&y2);

   double width = (x2-xo)/2.0;
   double height = (y2-yo);

   auto point = pDO->GetPosition();
   auto [xp, yp] = point.GetLocation();

   return WBFL::Geometry::Rect2d(xp - width, yp - height, xp + width, yp);
}

void CSupportDrawStrategyImpl::Draw(std::shared_ptr<const WBFL::DManip::iPointDisplayObject> pDO,CDC* pDC,COLORREF color, const WBFL::Geometry::Point2d& loc) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   auto pMap = pDispMgr->GetCoordinateMap();

   // location of top
   long topx,topy; 
   pMap->WPtoLP(loc,&topx,&topy);

   // height/width
   long xo,yo;
   pMap->TPtoLP(0,0,&xo,&yo);
   long x2,y2;
   pMap->TPtoLP(SUPSIZE,SUPSIZE,&x2,&y2);

   long wid  = x2-xo;
   long hgt = abs(y2-yo);

   CPen pen(PS_SOLID,1,color);
   CPen* pOldPen = pDC->SelectObject(&pen);

   CBrush brush(color);
   CBrush* pOldBrush = pDC->SelectObject(&brush);

   double length;
   m_Support->get_Length(&length);
   BoundaryConditionType ct;
   m_Support->get_BoundaryCondition(&ct);

   if (length==0.0)
   {
      DrawZeroLengthSupport( pDC, ct, topx, topy, wid, hgt);
   }
   else
   {
      // support has length - need to draw 
      double dbotx, dboty;
      m_pDoc->m_pModel->ComputeLocation(m_SupportID, mtSupport, 0.0, &dbotx, &dboty);
      long botx,boty; // location of bottom
      pMap->WPtoLP(dbotx,dboty,&botx,&boty);
      pDC->MoveTo(topx, topy);
      pDC->LineTo(botx, boty);
      DrawZeroLengthSupport( pDC, ct, botx, boty, wid, hgt);
   }

   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}


