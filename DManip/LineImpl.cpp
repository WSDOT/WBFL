///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// LineImpl.cpp: implementation of the CLineImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "LineImpl.h"
#include "LineHitTest.h"
#include "SimpleDrawLineStrategyImpl.h"
#include <MathEx.h>

#include <WBFLGeometry\GeomHelpers.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineImpl::CLineImpl()
{
}

CLineImpl::~CLineImpl()
{
}

HRESULT CLineImpl::FinalConstruct()
{
   SetDisplayObject(this);

   // Create the drawing strategy
   CComObject<CSimpleDrawLineStrategyImpl>* pStrategy;
   CComObject<CSimpleDrawLineStrategyImpl>::CreateInstance(&pStrategy);
   m_DrawStrategy = pStrategy;

   return CConnectorImpl::FinalConstruct();
}

void CLineImpl::FinalRelease()
{
   CConnectorImpl::FinalRelease();
   CDisplayObjectDefaultImpl::Do_FinalRelease();
}

/////////////////////////////////////////////////////////
// iDisplayObject Implementation

STDMETHODIMP_(void) CLineImpl::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   //CComPtr<IPoint2d> start, end;
   //GetStartPoint(&start);
   //GetEndPoint(&end);

   //CRect box = CLineHitTest::GetHitRect(this, start, end);
   //COLORREF color = RGB(0, 200, 0);
   //pDC->FillSolidRect(box, color);

   m_DrawStrategy->Draw(this,pDC);
}

STDMETHODIMP_(void) CLineImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
   m_DrawStrategy->DrawHighlite(this,pDC,bHighlite);
}

STDMETHODIMP_(BOOL) CLineImpl::HitTest(CPoint point)
{
   if ( m_pGravityWellStrategy )
   {
      // If there is a gravity well, use the default hit test implementation
      return Do_HitTest(point);
   }
   else
   {
      // ***** This is a Temporary HACK!!! ***************
      // Do not merge code below into the new DManip architecture
      //
      iSimpleDrawLineStrategy* pSimple = dynamic_cast<iSimpleDrawLineStrategy*>(m_DrawStrategy.p);
      if (pSimple)
      {
         CComPtr<iDisplayList> pDL;
         Do_GetDisplayList(&pDL);
         CComPtr<iDisplayMgr> pDispMgr;
         pDL->GetDisplayMgr(&pDispMgr);
         CComPtr<iCoordinateMap> pMap;
         pDispMgr->GetCoordinateMap(&pMap);

         // Get line width threshold in model coords
         LONG lwid = max(4, pSimple->GetWidth());

         // Width in model space
         Float64 wxo, wyo;
         pMap->LPtoWP(0, 0, &wxo, &wyo);
         Float64 wx2, wy2;
         pMap->LPtoWP(lwid, lwid, &wx2, &wy2);
         Float64 mxo, myo;
         pMap->WPtoMP(wxo, wyo, &mxo, &myo);
         Float64 mx2, my2;
         pMap->WPtoMP(wx2, wy2, &mx2, &my2);

         Float64 threshold = abs(mx2 - mxo); // just use distance along x

         // Convert target point to model coords
         CComPtr<IPoint2d> wpoint;
         pMap->LPtoWP(point.x, point.y,&wpoint);
         Float64 mx, my;
         pMap->WPtoMP(wpoint, &mx, &my);

         CComPtr<IPoint2d> mpoint;
         mpoint.CoCreateInstance(CLSID_Point2d);
         mpoint->Move(mx, my);

         // First need to use a line to get nearest point along an infinite line
         CComPtr<IPoint2d> startpoint, endpoint;
         GetEndPoints(&startpoint, &endpoint);

         if (S_OK != startpoint->SameLocation(endpoint)) // Line2d will throw below if we have equal points
         {
            CComPtr<ILine2d> line;
            line.CoCreateInstance(CLSID_Line2d);
            line->ThroughPoints(startpoint, endpoint);

            CComPtr<IGeomUtil2d> util;
            util.CoCreateInstance(CLSID_GeomUtil);

            CComPtr<IPoint2d> closestPoint;
            util->PointOnLineNearest(line, mpoint, &closestPoint);

            Float64 dist;
            mpoint->DistanceEx(closestPoint, &dist);
            if (dist < threshold)
            {
               // Point is close enough to an infinite line. Now we need to see if it's along our segment
               CComPtr<ILineSegment2d> lineSeg;
               lineSeg.CoCreateInstance(CLSID_LineSegment2d);
               lineSeg->ThroughPoints(startpoint, endpoint);

               VARIANT_BOOL retVal;
               geomUtil::DoesLineSegmentContainPoint(lineSeg, closestPoint, 0.01, &retVal);// assuming metric, and a mm is close enough
               if (retVal==VARIANT_TRUE) 
               {
                  return TRUE;
               }
            }
         }
      }
      else
      {
         // otherwise, use this strategy
         CComPtr<IPoint2d> start, end;
         GetStartPoint(&start);
         GetEndPoint(&end);
         BOOL hit = CLineHitTest::HitTest(this, start, end, point);
         return hit;
      }
   }

   return FALSE;
}

STDMETHODIMP_(void) CLineImpl::GetBoundingBox(IRect2d** rect)
{
   if ( m_DrawStrategy )
   {
      m_DrawStrategy->GetBoundingBox(this, rect);
   }
   else
   {
      // the end points of this line are in Model Space
      // the need to be converted to World Space for the bounding box


      // start by getting the coordinate mapper
      CComPtr<iDisplayList> display_list;
      GetDisplayList(&display_list);

      CComPtr<iDisplayMgr> display_mgr;
      display_list->GetDisplayMgr(&display_mgr);

      CComPtr<iCoordinateMap> map;
      display_mgr->GetCoordinateMap(&map);

      // get the points
      CComPtr<IPoint2d> pStart;
      CComPtr<IPoint2d> pEnd;
      GetStartPoint(&pStart);
      GetEndPoint(&pEnd);

      // convert them to world space
      Float64 sx, sy, ex, ey;
      map->MPtoWP(pStart,&sx,&sy);
      map->MPtoWP(pEnd,  &ex,&ey);

      CComPtr<IRect2d> bounding_box;
      bounding_box.CoCreateInstance(CLSID_Rect2d);

      bounding_box->put_Left(Min(sx, ex));
      bounding_box->put_Bottom(Min(sy, ey));
      bounding_box->put_Right(Max(sx, ex));
      bounding_box->put_Top(Max(sy, ey));

      (*rect) = bounding_box;
      (*rect)->AddRef();
   }
}


STDMETHODIMP_(bool) CLineImpl::OnLButtonDown(UINT nFlags,CPoint point)
{
   return Do_OnLButtonDown(nFlags,point);
}

STDMETHODIMP_(bool) CLineImpl::OnLButtonUp(UINT nFlags,CPoint point)
{
   return Do_OnLButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CLineImpl::OnLButtonDblClk(UINT nFlags,CPoint point)
{
   return Do_OnLButtonDblClk(nFlags,point);
}

STDMETHODIMP_(bool) CLineImpl::OnRButtonDown(UINT nFlags,CPoint point)
{
   return Do_OnRButtonDown(nFlags,point);
}

STDMETHODIMP_(bool) CLineImpl::OnRButtonUp(UINT nFlags,CPoint point)
{
   return Do_OnRButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CLineImpl::OnRButtonDblClk(UINT nFlags,CPoint point)
{
   return Do_OnRButtonDown(nFlags,point);
}

STDMETHODIMP_(bool) CLineImpl::OnMouseMove(UINT nFlags,CPoint point)
{
   return Do_OnMouseMove(nFlags,point);
}

STDMETHODIMP_(bool) CLineImpl::OnMouseWheel(UINT nFlags,short zDelta,CPoint point)
{
   return Do_OnMouseWheel(nFlags,zDelta,point);
}

STDMETHODIMP_(bool) CLineImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   return Do_OnKeyDown(nChar,nRepCnt,nFlags);
}

STDMETHODIMP_(bool) CLineImpl::OnContextMenu(CWnd* pWnd,CPoint point)
{
   return Do_OnContextMenu(pWnd,point);
}

/////////////////////////////////////////////////////////
// ILine Implementation
STDMETHODIMP_(void) CLineImpl::SetDrawLineStrategy(iDrawLineStrategy* pStrategy)
{
   m_DrawStrategy = pStrategy;

   // If the drawing strategy implements a gravity well, use it.

   CComQIPtr<iGravityWellStrategy,&IID_iGravityWellStrategy> gravityWell(pStrategy);
   if ( gravityWell )
      SetGravityWellStrategy(gravityWell);
}

STDMETHODIMP_(void) CLineImpl::GetDrawLineStrategy(iDrawLineStrategy* *pStrategy)
{
   (*pStrategy) = m_DrawStrategy;
   (*pStrategy)->AddRef();
}

STDMETHODIMP_(void) CLineImpl::GetEndPoints(CPoint* pStart,CPoint* pEnd)
{
   CComPtr<IPoint2d> start, end;
   GetEndPoints(&start,&end);

   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> dispMgr;
   pDL->GetDisplayMgr(&dispMgr);

   CComPtr<iCoordinateMap> map;
   dispMgr->GetCoordinateMap(&map);

   LONG lx, ly;
   map->WPtoLP(start,&lx,&ly);
   pStart->x = lx;
   pStart->y = ly;

   map->WPtoLP(end,&lx,&ly);
   pEnd->x = lx;
   pEnd->y = ly;
}

STDMETHODIMP_(void) CLineImpl::GetEndPoints(IPoint2d* *pStart,IPoint2d* *pEnd)
{
   GetStartPoint(pStart);
   GetEndPoint(pEnd);
}

//////////////////////////////////

void CLineImpl::GetStartPoint(IPoint2d* *point)
{
   CComPtr<iPlug> plug;
   GetStartPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CLineImpl::GetEndPoint(IPoint2d* *point)
{
   CComPtr<iPlug> plug;
   GetEndPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}
