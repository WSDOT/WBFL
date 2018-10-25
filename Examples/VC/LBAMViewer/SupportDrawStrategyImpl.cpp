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

BEGIN_INTERFACE_MAP(CSupportDrawStrategyImpl,CCmdTarget)
   INTERFACE_PART(CSupportDrawStrategyImpl,IID_iDrawPointStrategy,DrawPointStrategy)
   INTERFACE_PART(CSupportDrawStrategyImpl,IID_iSupportDrawStrategy,Strategy)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CSupportDrawStrategyImpl,DrawPointStrategy);
DELEGATE_CUSTOM_INTERFACE(CSupportDrawStrategyImpl,Strategy);

STDMETHODIMP_(void) CSupportDrawStrategyImpl::XStrategy::SetSupport(ISupport* support, long supportID)
{
   METHOD_PROLOGUE(CSupportDrawStrategyImpl,Strategy)

   pThis->m_Support = support;
   pThis->m_SupportID = supportID;
}

STDMETHODIMP_(void) CSupportDrawStrategyImpl::XDrawPointStrategy::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   METHOD_PROLOGUE(CSupportDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = RGB(80,60,0);

   CComPtr<IPoint2d> pos;
   pDO->GetPosition(&pos);
   pThis->Draw(pDO,pDC,color,pos);
}

STDMETHODIMP_(void) CSupportDrawStrategyImpl::XDrawPointStrategy::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   METHOD_PROLOGUE(CSupportDrawStrategyImpl,DrawPointStrategy);
   Draw(pDO,pDC);
}

STDMETHODIMP_(void) CSupportDrawStrategyImpl::XDrawPointStrategy::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint)
{
   METHOD_PROLOGUE(CSupportDrawStrategyImpl,DrawPointStrategy);

   CComPtr<IPoint2d> dragPoint;
   map->LPtoWP(cpdragPoint.x, cpdragPoint.y, &dragPoint);

   // Draw the support
   pThis->Draw(pDO,pDC,RGB(255,0,0),dragPoint);
}

STDMETHODIMP_(void) CSupportDrawStrategyImpl::XDrawPointStrategy::GetBoundingBox(iPointDisplayObject* pDO,IRect2d** pBox)
{
   METHOD_PROLOGUE(CSupportDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // height and width
   double xo,yo;
   pMap->TPtoWP(0,0,&xo,&yo);
   double x2,y2;
   pMap->TPtoWP(SUPSIZE,SUPSIZE,&x2,&y2);

   double width = (x2-xo)/2.0;
   double height = (y2-yo);

   CComPtr<IPoint2d> point;
   pDO->GetPosition(&point);
   double xp, yp;
   point->get_X(&xp);
   point->get_Y(&yp);

   CComPtr<IRect2d> box;
   box.CoCreateInstance(CLSID_Rect2d);

   box->put_Top(yp);
   box->put_Left(xp - width);
   box->put_Bottom(yp - height);
   box->put_Right(xp + width);

   (*pBox) = box;
   (*pBox)->AddRef();
}

void CSupportDrawStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color, IPoint2d* loc)
{
   HRESULT hr;

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

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
   hr = m_Support->get_Length(&length);
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


