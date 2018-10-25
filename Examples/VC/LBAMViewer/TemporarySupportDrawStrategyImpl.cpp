#include "stdafx.h"
#include "LBAMViewer.h"
#include "LBAMViewerDoc.h"
#include "TemporarySupportDrawStrategyImpl.h"
#include "mfcdual.h"

#define SIZE 20
#include "DrawSupports.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTemporarySupportDrawStrategyImpl::CTemporarySupportDrawStrategyImpl(CLBAMViewerDoc* pDoc)
{
   m_pDoc = pDoc;
}

BEGIN_INTERFACE_MAP(CTemporarySupportDrawStrategyImpl,CCmdTarget)
   INTERFACE_PART(CTemporarySupportDrawStrategyImpl,IID_iDrawPointStrategy,DrawPointStrategy)
   INTERFACE_PART(CTemporarySupportDrawStrategyImpl,IID_iTemporarySupportDrawStrategy,Strategy)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CTemporarySupportDrawStrategyImpl,DrawPointStrategy);
DELEGATE_CUSTOM_INTERFACE(CTemporarySupportDrawStrategyImpl,Strategy);

STDMETHODIMP_(void) CTemporarySupportDrawStrategyImpl::XStrategy::SetTemporarySupport(ITemporarySupport* support, long supportID)
{
   METHOD_PROLOGUE(CTemporarySupportDrawStrategyImpl,Strategy)

   pThis->m_Support = support;
   pThis->m_SupportID = supportID;
}

STDMETHODIMP_(void) CTemporarySupportDrawStrategyImpl::XDrawPointStrategy::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   METHOD_PROLOGUE(CTemporarySupportDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = RGB(200,200,255);

   CComPtr<IPoint2d> pos;
   pDO->GetPosition(&pos);
   pThis->Draw(pDO,pDC,color,pos);
}

STDMETHODIMP_(void) CTemporarySupportDrawStrategyImpl::XDrawPointStrategy::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   METHOD_PROLOGUE(CTemporarySupportDrawStrategyImpl,DrawPointStrategy);
   Draw(pDO,pDC);
}

STDMETHODIMP_(void) CTemporarySupportDrawStrategyImpl::XDrawPointStrategy::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint)
{
   METHOD_PROLOGUE(CTemporarySupportDrawStrategyImpl,DrawPointStrategy);

   CComPtr<IPoint2d> dragPoint;
   map->LPtoWP(cpdragPoint.x, cpdragPoint.y, &dragPoint);

   // Draw the support
   pThis->Draw(pDO,pDC,RGB(255,0,0),dragPoint);
}

STDMETHODIMP_(void) CTemporarySupportDrawStrategyImpl::XDrawPointStrategy::GetBoundingBox(iPointDisplayObject* pDO,IRect2d** pBox)
{
   METHOD_PROLOGUE(CTemporarySupportDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

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


void CTemporarySupportDrawStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc)
{
   HRESULT hr;

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   long topx,topy; // location of top
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
      m_pDoc->m_pModel->ComputeLocation(m_SupportID, mtTemporarySupport, 0.0, &dbotx, &dboty);
      long botx,boty; // location of bottom
      pMap->WPtoLP(dbotx,dboty,&botx,&boty);
      pDC->MoveTo(topx, topy);
      pDC->LineTo(botx, boty);
      DrawZeroLengthSupport( pDC, ct, botx, boty, wid, hgt);
   }

   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}


