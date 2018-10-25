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

BEGIN_INTERFACE_MAP(CPointLoadDrawStrategyImpl,CCmdTarget)
   INTERFACE_PART(CPointLoadDrawStrategyImpl,IID_iDrawPointStrategy,DrawPointStrategy)
   INTERFACE_PART(CPointLoadDrawStrategyImpl,IID_iPointLoadDrawStrategy,Strategy)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CPointLoadDrawStrategyImpl,DrawPointStrategy);
DELEGATE_CUSTOM_INTERFACE(CPointLoadDrawStrategyImpl,Strategy);

STDMETHODIMP_(void) CPointLoadDrawStrategyImpl::XStrategy::SetLoad(IFem2dPointLoad* load)
{
   METHOD_PROLOGUE(CPointLoadDrawStrategyImpl,Strategy);
   pThis->m_Load = load;
}

STDMETHODIMP_(void) CPointLoadDrawStrategyImpl::XStrategy::SetColor(COLORREF color)
{
   METHOD_PROLOGUE(CPointLoadDrawStrategyImpl,Strategy);
   pThis->m_Color = color;
}

STDMETHODIMP_(void) CPointLoadDrawStrategyImpl::XDrawPointStrategy::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   METHOD_PROLOGUE(CPointLoadDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = pThis->m_Color;

   CComPtr<IPoint2d> pos;
   pDO->GetPosition(&pos);

   pThis->Draw(pDO,pDC,color,pos);
}

STDMETHODIMP_(void) CPointLoadDrawStrategyImpl::XDrawPointStrategy::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   METHOD_PROLOGUE(CPointLoadDrawStrategyImpl,DrawPointStrategy);
   Draw(pDO,pDC);
}

STDMETHODIMP_(void) CPointLoadDrawStrategyImpl::XDrawPointStrategy::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint)
{
   METHOD_PROLOGUE(CPointLoadDrawStrategyImpl,DrawPointStrategy);

   CComPtr<IPoint2d> dragPoint;
   map->LPtoWP(cpdragPoint.x, cpdragPoint.y, &dragPoint);

   pThis->Draw(pDO,pDC,RGB(255,0,0),dragPoint);
}

STDMETHODIMP_(void) CPointLoadDrawStrategyImpl::XDrawPointStrategy::GetBoundingBox(iPointDisplayObject* pDO, IRect2d** ppRect)
{
   METHOD_PROLOGUE(CPointLoadDrawStrategyImpl,DrawPointStrategy);

   CComPtr<IPoint2d> point;
   pDO->GetPosition(&point);

   double px, py;
   point->get_X(&px);
   point->get_Y(&py);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   double xo,yo;
   pMap->TPtoWP(0,0,&xo,&yo);
   double x2,y2;
   pMap->TPtoWP(SSIZE,SSIZE,&x2,&y2);

   double wid = fabs(x2-xo)/2.0;
   double hgt = fabs(y2-yo)/2.0;

   CComPtr<IRect2d> rect;
   rect.CoCreateInstance(CLSID_Rect2d);

   rect->put_Left(px-wid);
   rect->put_Bottom(py-hgt);
   rect->put_Right(px+wid);
   rect->put_Top(py+hgt);

   (*ppRect) = rect;
   (*ppRect)->AddRef();
}


void CPointLoadDrawStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

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
