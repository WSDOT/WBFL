///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// DisplayView.cpp : implementation file
//

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include <DManip\DisplayView.h>
#include <math.h>

#include "DisplayMgrImpl.h"
#include "TaskFactoryImpl.h"
#include "MappingImpl.h"

#include "DManipDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// function to determine percent difference
static bool PassedPD(Float64 datum, Float64 test, Float64 minPD, Float64 Tolerance)
{
   ATLASSERT(datum>=0.0);
   ATLASSERT(test>=0.0);
   ATLASSERT(minPD>0.0);
   ATLASSERT(Tolerance>0.0);

   if (datum>Tolerance)
   {
      Float64 pd = fabs(datum-test)/datum;

      return pd<minPD;
   }
   else
   {
      return fabs(datum-test)<Tolerance;
   }
}

static void CopyRect(IRect2d* pSource, IRect2d* pTarget)
{
   Float64 left, right, bottom, top;
   pSource->get_Left(&left);
   pSource->get_Bottom(&bottom);
   pSource->get_Right(&right);
   pSource->get_Top(&top);

   pTarget->put_Left(left);
   pTarget->put_Bottom(bottom);
   pTarget->put_Right(right);
   pTarget->put_Top(top);
}

static void GetRect(IRect2d* rect,Float64 *left,Float64 *top,Float64 *right,Float64 *bottom)
{
   ATLASSERT( rect != 0 && left != 0 && top != 0 && right != 0 && bottom != 0);
   rect->get_Left(left);
   rect->get_Right(right);
   rect->get_Top(top);
   rect->get_Bottom(bottom);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayView

IMPLEMENT_DYNCREATE(CDisplayView, CScrollView)

CDisplayView::CDisplayView()
{
   CComObject<CDisplayMgrImpl>* pDM;
   CComObject<CDisplayMgrImpl>::CreateInstance(&pDM);
   m_pDispMgr = pDM;

   CComObject<CTaskFactoryImpl>* pTF;
   CComObject<CTaskFactoryImpl>::CreateInstance(&pTF);
   m_pDispMgr->SetTaskFactory(pTF);

   // create mappings for screen and printer
   CComObject<CMappingImpl>* ppMapping;
   CComObject<CMappingImpl>::CreateInstance(&ppMapping);
   m_pPrinterMapping = ppMapping;
   m_pPrinterMapping->QueryInterface(IID_iCoordinateMap,(void**)&m_pPrinterCoordinateMap);

   CComObject<CMappingImpl>* psMapping;
   CComObject<CMappingImpl>::CreateInstance(&psMapping);
   m_pScreenMapping = psMapping;
   m_pScreenMapping->QueryInterface(IID_iCoordinateMap,(void**)&m_pScreenCoordinateMap);

   // default to screen at first
   m_IsPrinting = false;
   m_pMapping       = m_pScreenMapping;
   m_pCoordinateMap = m_pScreenCoordinateMap;

   m_nMapMode = MM_TEXT;
}

CDisplayView::~CDisplayView()
{
}

void CDisplayView::GetDisplayMgr(iDisplayMgr** dispMgr)
{
   m_pDispMgr.CopyTo(dispMgr);
}


BEGIN_MESSAGE_MAP(CDisplayView, CScrollView)
	//{{AFX_MSG_MAP(CDisplayView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
   ON_WM_MOUSEWHEEL()
   ON_WM_KEYDOWN()
   ON_WM_DESTROY()
	ON_WM_PAINT()
   ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT,0,0xFFFF,OnNeedToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayView drawing

void CDisplayView::OnInitialUpdate()
{
   m_pDispMgr->SetView(this);

   CScrollView::OnInitialUpdate();

   // set up initial mapping for logical size
   CRect rect;
   GetClientRect(&rect);
   CSize size = rect.Size();
   SetScrollSizes(MM_TEXT,size,CScrollView::sizeDefault,CScrollView::sizeDefault);

   SetLogicalViewRect(MM_TEXT, rect);
}

INT_PTR CDisplayView::OnToolHitTest(CPoint point,TOOLINFO* pTI) const
{
   INT_PTR retval = CView::OnToolHitTest(point,pTI);
   if ( retval < 0 )
   {
      // NOTE: MFC defines this as a const method. There is nothing we
      // can do about that. In order to get this method to work we need
      // to cast away constness. Be very careful to make sure constness is
      // preserved when working with this method.
      CDisplayView* pMe = const_cast<CDisplayView*>(this);

      CDManipClientDC dc(pMe);
      CPoint logPoint(point);
      dc.DPtoLP(&logPoint);
      retval = pMe->m_pDispMgr->OnToolHitTest(logPoint,pTI);

      if ( 0 < retval )
      {
         CPoint tl(pTI->rect.left,pTI->rect.top);
         CPoint br(pTI->rect.right,pTI->rect.bottom);

         dc.LPtoDP(&tl);
         dc.LPtoDP(&br);

         pTI->rect.left = tl.x;
         pTI->rect.top  = tl.y;

         pTI->rect.right = br.x;
         pTI->rect.bottom = br.y;
      }
   }
   return retval;
}

CRect CDisplayView::GetViewRect()
{
   CRect rView;
   if ( m_IsPrinting )
      rView = m_PrintingRect;
   else
      GetClientRect(&rView);

   return rView;
}

void CDisplayView::OnDraw(CDC* pDC)
{
   int nBkMode = pDC->SetBkMode(TRANSPARENT);
#if defined(_DEBUG)
//   m_pDispMgr->DrawGravityWells(pDC);
#endif 

   // Delegate
   m_pDispMgr->DrawDisplayObjects(pDC);

   pDC->SetBkMode(nBkMode);

//#if defined _DEBUG
//   CPen redPen(PS_SOLID,3,RGB(0,0,255));
//   CPen* pOldPen = pDC->SelectObject(&redPen);
//   // Draw coordinate axes
//   Float64 xmin = -1000;
//   Float64 xmax =  1000;
//   Float64 ymin = -1000;
//   Float64 ymax =  1000;
//
//   LONG lx1,ly1;
//   LONG lx2,ly2;
//   m_pCoordinateMap->WPtoLP(0,ymin,&lx1,&ly1);
//   m_pCoordinateMap->WPtoLP(0,ymax,&lx2,&ly2);
//   pDC->MoveTo(lx1,ly1);
//   pDC->LineTo(lx2,ly2);
//
//   m_pCoordinateMap->WPtoLP(xmin,0,&lx1,&ly1);
//   m_pCoordinateMap->WPtoLP(xmax,0,&lx2,&ly2);
//   pDC->MoveTo(lx1,ly1);
//   pDC->LineTo(lx2,ly2);
//
//   m_pCoordinateMap->WPtoLP(0,0,&lx1,&ly1);
//   pDC->SetTextAlign(TA_BASELINE | TA_LEFT);
//   pDC->TextOut(lx1,ly1,"Origin");
//
//   pDC->SelectObject(pOldPen);
//#endif
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayView diagnostics

#ifdef _DEBUG
void CDisplayView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDisplayView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisplayView message handlers
int CDisplayView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

   return 0;
}

void CDisplayView::OnLButtonDown(UINT nFlags, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnLButtonDown(nFlags,logPoint) )
      HandleLButtonDown(nFlags,logPoint);

	CScrollView::OnLButtonDown(nFlags, point);
}

void CDisplayView::OnLButtonUp(UINT nFlags, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnLButtonUp(nFlags,logPoint) )
      HandleLButtonUp(nFlags,logPoint);

	CScrollView::OnLButtonUp(nFlags, point);
}

void CDisplayView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnLButtonDblClk(nFlags,logPoint) )
      HandleLButtonDblClk(nFlags,logPoint);

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CDisplayView::OnRButtonDown(UINT nFlags, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnRButtonDown(nFlags,logPoint) )
      HandleRButtonDown(nFlags,logPoint);

	CScrollView::OnRButtonDown(nFlags, point);
}

void CDisplayView::OnRButtonUp(UINT nFlags, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnRButtonUp(nFlags,logPoint) )
      HandleRButtonUp(nFlags,logPoint);

	CScrollView::OnRButtonUp(nFlags, point);
}

void CDisplayView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnRButtonDblClk(nFlags,logPoint) )
      HandleRButtonDblClk(nFlags,logPoint);

	CScrollView::OnRButtonDblClk(nFlags, point);
}

void CDisplayView::OnMouseMove(UINT nFlags, CPoint point)
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnMouseMove(nFlags,logPoint) )
      HandleMouseMove(nFlags,logPoint);

	CScrollView::OnMouseMove(nFlags, point);
}

BOOL CDisplayView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   if ( !m_pDispMgr->OnMouseWheel(nFlags,zDelta,logPoint) )
      HandleMouseWheel(nFlags,zDelta,logPoint);

	return CScrollView::OnMouseWheel(nFlags, zDelta, point);
}

void CDisplayView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CDManipClientDC dc(this);
   if ( !m_pDispMgr->OnKeyDown(nChar,nRepCnt,nFlags) )
      HandleKeyDown(nChar,nRepCnt,nFlags);

	CScrollView::OnKeyDown(nChar,nRepCnt,nFlags);
}

void CDisplayView::OnContextMenu(CWnd* pWnd,CPoint screenPoint)
{
   if ( !m_pDispMgr->OnContextMenu(pWnd,screenPoint) )
      HandleContextMenu(pWnd,screenPoint);

	CScrollView::OnContextMenu(pWnd, screenPoint);
}

BOOL CDisplayView::OnNeedToolTipText(UINT id,NMHDR* pNMHDR,LRESULT* pResult)
{
   return m_pDispMgr->OnNeedToolTipText(id,pNMHDR,pResult);
}

DROPEFFECT CDisplayView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   DROPEFFECT de = m_pDispMgr->OnDragEnter(pDataObject,dwKeyState,logPoint);

   if ( de == DROPEFFECT_NONE )
	   de = CScrollView::OnDragEnter(pDataObject, dwKeyState, point);

   return de;
}

void CDisplayView::OnDragLeave() 
{
   m_pDispMgr->OnDragLeave();
   CScrollView::OnDragLeave();
}

DROPEFFECT CDisplayView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   DROPEFFECT de = m_pDispMgr->OnDragOver(pDataObject,dwKeyState,logPoint);

   if ( de == DROPEFFECT_NONE )
      de = CScrollView::OnDragOver(pDataObject,dwKeyState,point);

   return de;
}

BOOL CDisplayView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   BOOL bDropped = m_pDispMgr->OnDrop(pDataObject,dropEffect,logPoint);

   if ( !bDropped )
      bDropped = CScrollView::OnDrop(pDataObject,dropEffect,point);

   return bDropped;
}

DROPEFFECT CDisplayView::OnDragScroll( DWORD dwKeyState, CPoint point )
{
   // Convert the point to logical coordinates
   CPoint logPoint = point;
   CDManipClientDC dc(this);
   dc.DPtoLP(&logPoint);

   DROPEFFECT de = m_pDispMgr->OnDragScroll(dwKeyState,logPoint);
   if ( de == DROPEFFECT_NONE )
      de = CScrollView::OnDragScroll(dwKeyState,point);

   return de;
}

DROPEFFECT CDisplayView::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point)
{
   return DROPEFFECT_NONE;
}

void CDisplayView::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point)
{
   // Do nothing
}

void CDisplayView::GetCoordinateMap(iCoordinateMap** map)
{
   m_pCoordinateMap.CopyTo(map);
}

void CDisplayView::DoCenterOnPoint()
{
   CComPtr<iTaskFactory> pFactory;
   m_pDispMgr->GetTaskFactory(&pFactory);

   CComPtr<iTask> task;
   pFactory->CreateCenterOnPointTask(this,&task);
   m_pDispMgr->SetTask(task);
}

void CDisplayView::DoZoom()
{
   CComPtr<iTaskFactory> pFactory;
   m_pDispMgr->GetTaskFactory(&pFactory);

   CComPtr<iTask> task;
   pFactory->CreateZoomTask(this,NULL,RGB(0,255,0),&task);
   m_pDispMgr->SetTask(task);
}

void CDisplayView::Zoom(CRect rect, bool reDraw)
{
   rect.NormalizeRect();

   Float64 wbot, wleft, wtop, wright;
   m_pCoordinateMap->LPtoWP(rect.left,  rect.bottom, &wleft,  &wbot);
   m_pCoordinateMap->LPtoWP(rect.right, rect.top,    &wright, &wtop);

   CComPtr<IRect2d> wrect;
   wrect.CoCreateInstance(CLSID_Rect2d);
   wrect->put_Bottom(wbot);
   wrect->put_Left(wleft);
   wrect->put_Top(wtop);
   wrect->put_Right(wright);
   wrect->Normalize();

   SetWorldViewRect(wrect);

   CComPtr<IPoint2d> point;
   wrect->get_CenterCenter(&point);

   CenterOnPoint(point, reDraw);
//
//   CComPtr<IRect2d> worldRect;
//   m_pDispMgr->GetBoundingBox(m_pCoordinateMap,false,&worldRect);
//
//   Float64 left, top, right, bottom;
//   GetRect(worldRect,&left,&top,&right,&bottom);
//   CPoint pntTL, pntBR;
//   m_pCoordinateMap->WPtoLP(left,top,    &pntTL.x,&pntTL.y);
//   m_pCoordinateMap->WPtoLP(right,bottom,&pntBR.x,&pntBR.y);
//
//   CRect rWorld(pntTL,pntBR);
//   CSize szWorld = rWorld.Size();
//   SetScrollSizes(m_nMapMode,szWorld);
}

void CDisplayView::Zoom(IRect2d* rect, bool reDraw)
{
   Float64 left, right, top, bottom;
   rect->get_Left(&left);
   rect->get_Right(&right);
   rect->get_Top(&top);
   rect->get_Bottom(&bottom);

   CPoint pntTL, pntBR;
   m_pCoordinateMap->WPtoLP(left,top,&pntTL.x,&pntTL.y);
   m_pCoordinateMap->WPtoLP(right,bottom,&pntBR.x,&pntBR.y);

   CRect lRect(pntTL,pntBR);
   Zoom(lRect,reDraw);
}

void CDisplayView::Zoom(Float64 factor, bool reDraw)
{
   if (factor<=0.0)
   {
      ATLASSERT(false);
      return;
   }
   
   // need to zoom from adjusted space so we are centered properly
   CComPtr<IRect2d> rect;
   this->GetAdjustedWorldViewRect(&rect);
   Float64 wid, hgt;
   rect->get_Width(&wid);
   rect->get_Height(&hgt);

   Float64 new_wid = wid/factor;
   Float64 new_hgt = hgt/factor;

   Float64 wneed = (new_wid - wid)/2.0;
   Float64 hneed = (new_hgt - hgt)/2.0;

   rect->Inflate(wneed, hneed);

   SetWorldViewRect(rect);

   if (reDraw)
      Invalidate();
}


void CDisplayView::ScaleToFit(bool reDraw)
{
   // create fresh dc for mapper in GetBoundingBox if we are not printing
   CDManipClientDC dc2(this);

   // bounding box computation is iterative. Iterate until box size on consecutive iterations
   // is within 2 percent
   Float64 pd_tolerance = 0.002;
   CollectionIndexType max_iter = 10;

   // Tricky: Things get weird if the windows is shrunken to far.
   // we can run into numerical problems with the mapper if the extents become too large. Modify
   // current world orgin and extents to reasonable values so we are more likely to converge on a good solution
   m_pMapping->SetWorldOrg(0.0, 0.0);
   m_pMapping->SetWorldExt(1.0, 1.0);

   Float64 orig_width = 0.0;
   Float64 orig_height = 0.0;

   for (CollectionIndexType it=0; it<max_iter; it++)
   {
      CComPtr<IRect2d> rect;
      m_pDispMgr->GetBoundingBox(m_pCoordinateMap, false, &rect);
      Zoom(rect,false);

      Float64 wid, hgt;
      rect->get_Width(&wid);
      rect->get_Height(&hgt);

      // test if we passed tolerance
      if (it+1 == max_iter ||
          PassedPD(wid, orig_width,  pd_tolerance, 1.0e-4) &&
          PassedPD(hgt, orig_height, pd_tolerance, 1.0e-4) )
      {
         WATCHX(DManip,1,_T("Found bounding rect after ") << it << _T(" iterations"));
         break;
      }
      else 
      {
         orig_width  = wid;
         orig_height = hgt;
      }
   }

   if (reDraw)
      Invalidate();
}

void CDisplayView::CenterOnPoint(IPoint2d* wOrg, bool reDraw)
{
   Float64 wpx, wpy;
   wOrg->get_X(&wpx);
   wOrg->get_Y(&wpy);

   CenterOnPoint(wpx, wpy, reDraw);
}

void CDisplayView::CenterOnPoint(Float64 wpx, Float64 wpy, bool reDraw)
{
   // get center of adjusted world extents
   Float64 wox, woy, wex, wey;
   m_pMapping->GetWorldOrg(&wox, &woy);
   m_pMapping->GetAdjustedWorldExt(&wex, &wey);

   Float64 wcx = wox + wex/2.0;
   Float64 wcy = woy + wey/2.0;

   // compute distance between centers and offset world view rect this much
   Float64 xoff = wpx-wcx;
   Float64 yoff = wpy-wcy;

   m_pMapping->SetWorldOrg(wox+xoff, woy+yoff);

   if (reDraw)
      Invalidate();
}

void CDisplayView::CenterOnPoint(CPoint center, bool reDraw)
{
   // move world rect required distance
   Float64 wpx, wpy;
   m_pCoordinateMap->LPtoWP(center.x, center.y, &wpx, &wpy);

   CenterOnPoint(wpx, wpy, reDraw);
}

CRect CDisplayView::GetAdjustedLogicalViewRect()
{
   LONG lex, ley;
   m_pMapping->GetAdjustedLogicalExt(&lex, &ley);
   
   LONG lox, loy;
   m_pMapping->GetLogicalOrg(&lox, &loy);

   CRect rect(lox, loy, lox+lex, loy+ley);
   rect.NormalizeRect();
   return rect;
}

void CDisplayView::GetAdjustedWorldViewRect(IRect2d* *rect)
{
   CComPtr<IRect2d> wrect;
   wrect.CoCreateInstance(CLSID_Rect2d);

   Float64 wex, wey;
   m_pMapping->GetAdjustedWorldExt(&wex, &wey);
   Float64 wox, woy;
   m_pMapping->GetWorldOrg(&wox, &woy);

   wrect->put_Left(wox);
   wrect->put_Bottom(woy);
   wrect->put_Right(wox+wex);
   wrect->put_Top(woy+wey);

   wrect.CopyTo(rect);
}

void CDisplayView::SetMappingMode(DManip::MapMode mm, bool reDraw)
{
   m_pMapping->SetMappingMode(mm);

   if (reDraw)
      Invalidate();
}

DManip::MapMode CDisplayView::GetMappingMode()
{
   return m_pMapping->GetMappingMode();
}

void CDisplayView::SetLogicalViewRect(int mapMode, CRect rect)
{
   m_nMapMode = mapMode;
   
   // assume that bottom of rect is always origin
   m_pMapping->SetLogicalOrg(rect.left, rect.bottom);
   m_pMapping->SetLogicalExt(rect.right-rect.left, rect.top-rect.bottom);
}

RECT CDisplayView::GetLogicalViewRect()
{
   RECT rect;
   m_pMapping->GetLogicalOrg(&rect.left, &rect.bottom);
   LONG lex, ley;
   m_pMapping->GetLogicalExt(&lex, &ley);
   rect.right = rect.left + lex;
   rect.top   = rect.bottom + ley;

   return rect;
}

void CDisplayView::SetWorldViewRect(IRect2d* rect)
{
   Float64 bot, lft, top, rgt;
   GetRect(rect, &lft, &top, &rgt, &bot);

   m_pMapping->SetWorldOrg(lft, bot);
   m_pMapping->SetWorldExt(rgt-lft, top-bot);
}


void CDisplayView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
   CScrollView::OnPrepareDC(pDC,pInfo);

   pDC->SetMapMode(m_nMapMode);
   m_pMapping->PrepareDC(pDC);
}

void CDisplayView::OnCleanUpDC(CDC* pDC, CPrintInfo* pInfo)
{
   m_pMapping->CleanUpDC(pDC);
}

void CDisplayView::OnDestroy()
{
   m_pDispMgr.Release();
   CScrollView::OnDestroy();
}

void CDisplayView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnEndPrinting(pDC, pInfo);

   // clean up print DC. 
   m_IsPrinting = false;
   m_pMapping->CleanUpPrintDC(pDC);

   // restore mapping to screen
   m_pMapping       = m_pScreenMapping;
   m_pCoordinateMap = m_pScreenCoordinateMap;


   Invalidate();
}

void CDisplayView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo,CRect rcDraw)
{
   m_IsPrinting = true;
   m_PrintingRect = rcDraw;

   CRgn clip;
   clip.CreateRectRgnIndirect(&rcDraw);
   pDC->SelectClipRgn(&clip);

   OnBeginPrinting(pDC,pInfo);
}

void CDisplayView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
   // Set up printer mapping to scale to the current clip box or to the 
   // physical extents of the printer of none has been defined
   // Get logical extents of device rect
   CRect box;
   pDC->GetClipBox(&box);
   if (!box.IsRectEmpty())
   {
      pDC->DPtoLP(&box);
   }
   else
   {
      // no clip box or drawing rect has been specified
      // draw to the full extents of the printer
      LONG dex = pDC->GetDeviceCaps(PHYSICALWIDTH);
      LONG dey = pDC->GetDeviceCaps(PHYSICALHEIGHT);
      LONG dox = pDC->GetDeviceCaps(PHYSICALOFFSETX);
      LONG doy = pDC->GetDeviceCaps(PHYSICALOFFSETY);

      box.left   = dox;
      box.top    = doy;
      box.right  = dex - 2*dox;
      box.bottom = dey - 2*doy;

      pDC->DPtoLP(&box);
   }

   m_pPrinterMapping->SetLogicalOrg(box.left, box.bottom);
   m_pPrinterMapping->SetLogicalExt(box.right-box.left, 
                             box.top-box.bottom);
	
   // set world extents and center so that center of screen is at center of view
   Float64 wox, woy, wex, wey;
   m_pMapping->GetWorldOrg(&wox, &woy);
   m_pMapping->GetWorldExt(&wex, &wey);
   DManip::MapMode mode = m_pMapping->GetMappingMode();

   m_pPrinterMapping->SetWorldOrg(wox, woy);
   m_pPrinterMapping->SetWorldExt(wex, wey);
   m_pPrinterMapping->SetMappingMode(mode);

   Float64 cx,cy,angle;
   m_pMapping->GetRotation(&cx,&cy,&angle);
   m_pPrinterMapping->SetRotation(cx,cy,angle);

   Float64 waex, waey;
   m_pMapping->GetAdjustedWorldExt(&waex, &waey);

   Float64 wcx = wox + waex/2;  // center of screen - adjusted world
   Float64 wcy = woy + waey/2;

   // set mapping to printer - to be set back in OnEndPrinting
   m_pMapping       = m_pPrinterMapping;
   m_pCoordinateMap = m_pPrinterCoordinateMap;

   CenterOnPoint(wcx, wcy);

	CScrollView::OnBeginPrinting(pDC, pInfo);
}

void CDisplayView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	OnPrepareDC(&dc);
	OnDraw(&dc);
   OnCleanUpDC(&dc);
}

void CDisplayView::HandleLButtonDown(UINT nFlags, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleLButtonUp(UINT nFlags, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleLButtonDblClk(UINT nFlags, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleRButtonDown(UINT nFlags, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleRButtonUp(UINT nFlags, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleRButtonDblClk(UINT nFlags, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleMouseMove(UINT nFlags, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleMouseWheel(UINT nFlags, short zDelta, CPoint logPoint)
{
   // Do nothing
}

void CDisplayView::HandleKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // Do nothing
}

void CDisplayView::HandleContextMenu(CWnd* pWnd,CPoint logPoint)
{
   // Do nothing
}
