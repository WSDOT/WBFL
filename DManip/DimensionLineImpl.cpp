///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

// DimensionLineImpl.cpp: implementation of the CDimensionLineImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "DimensionLineImpl.h"
#include "Helpers.h"
#include "TextBlockImpl.h"
#include "LineHitTest.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDimensionLineImpl::CDimensionLineImpl()
{
}

CDimensionLineImpl::~CDimensionLineImpl()
{
}

HRESULT CDimensionLineImpl::FinalConstruct()
{
   SetDisplayObject(this);
   Do_SetSelectionType(stNone); // Not selectable by default

   m_Angle = 0;
   m_bAlignWithPlugs = TRUE;

   m_HiddenWitnessLength = 0;

   m_LenWitness    = 1440 * 3/8;
   m_DimOffset     = 1440 * 1/16;
   m_WitnessOffset = 1440 * 1/32;

   m_ArrowHeight = 1440 * 1/16;
   m_ArrowWidth  = 1440 * 1/16;

   m_Style = DManip::ahsFilled;

   m_bAutoText = FALSE;

   return CConnectorImpl::FinalConstruct();
}

void CDimensionLineImpl::FinalRelease()
{
   CConnectorImpl::FinalRelease();
   CDisplayObjectDefaultImpl::Do_FinalRelease();
}


/////////////////////////////////////////////////////////
// iDisplayObject Implementation
STDMETHODIMP_(void) CDimensionLineImpl::SetDisplayList(iDisplayList* pDL)
{
   Do_SetDisplayList(pDL);

   if ( m_TextBlock )
      m_TextBlock->SetDisplayList(pDL);
}

STDMETHODIMP_(void) CDimensionLineImpl::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   UpdateWorkPoints();

   // Draw the left witness line
   pDC->MoveTo(m_ptA);
   pDC->LineTo(m_ptB);

   // Draw the Right witness line
   pDC->MoveTo(m_ptD);
   pDC->LineTo(m_ptE);

   // Draw dimension line
   pDC->MoveTo(m_ptC);
   pDC->LineTo(m_ptF);

   // Draw arrow heads
   DrawArrowHead(pDC,m_Style,m_StartArrow.left,m_StartArrow.tip,m_StartArrow.right);
   DrawArrowHead(pDC,m_Style,m_EndArrow.left,m_EndArrow.tip,m_EndArrow.right);

   if ( m_TextBlock )
      m_TextBlock->Draw(pDC);
}

STDMETHODIMP_(void) CDimensionLineImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
#pragma Reminder("Clean this up")
   // Need to draw in a highlite color
   Draw(pDC);
}

STDMETHODIMP_(BOOL) CDimensionLineImpl::HitTest(CPoint point)
{
   UpdateWorkPoints();

   if ( m_TextBlock && m_TextBlock->HitTest(point) )
      return TRUE;

   if ( m_pGravityWellStrategy )
   {
      // Use the default strategy
      return Do_HitTest(point);
   }
   else
   {
      // otherwise, use this strategy
      CComPtr<IPoint2d> start, end;
      GetStartPoint(&start);
      GetEndPoint(&end);
      return CLineHitTest::HitTest(this,start,end,point);
   }

   return FALSE;
}

STDMETHODIMP_(void) CDimensionLineImpl::GetBoundingBox(IRect2d** rect)
{
   UpdateWorkPoints();

   CRect r(m_ptA,m_ptA);
   IncludePointInRect(m_ptB,&r);
   IncludePointInRect(m_ptC,&r);
   IncludePointInRect(m_ptD,&r);
   IncludePointInRect(m_ptE,&r);
   IncludePointInRect(m_ptF,&r);
   IncludePointInRect(m_ptZ,&r);
   IncludePointInRect(m_StartArrow.tip,&r);
   IncludePointInRect(m_StartArrow.left,&r);
   IncludePointInRect(m_StartArrow.right,&r);
   IncludePointInRect(m_EndArrow.tip,&r);
   IncludePointInRect(m_EndArrow.left,&r);
   IncludePointInRect(m_EndArrow.right,&r);

   if ( m_TextBlock )
   {
      CRect box = m_TextBlock->GetBoundingBox();
      r.NormalizeRect();
      box.NormalizeRect();
      r.UnionRect(&r,&box);
   }

   // convert to world
   CComPtr<iDisplayList> pDL;
   Do_GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   Float64 left,top, right, bottom;
   pMap->LPtoWP(r.left, r.top, &left, &top);
   pMap->LPtoWP(r.right, r.bottom, &right, &bottom);

   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   bounding_box->put_Top(Max(top, bottom) );
   bounding_box->put_Left(Min(left,right) );
   bounding_box->put_Bottom(Min(top, bottom) );
   bounding_box->put_Right(Max(left,right) );

   (*rect) = bounding_box;
   (*rect)->AddRef();
}

STDMETHODIMP_(CString) CDimensionLineImpl::GetToolTipText()
{
   CString strMyTip = Do_GetToolTipText();
   if ( strMyTip.GetLength() == CString("") && m_TextBlock )
      return m_TextBlock->GetToolTipText();
   else
      return strMyTip;
}

STDMETHODIMP_(void) CDimensionLineImpl::SetMaxTipWidth(INT maxWidth)
{ 
   if ( m_TextBlock )
      m_TextBlock->SetMaxTipWidth(maxWidth);
   else
      Do_SetMaxTipWidth(maxWidth); 
}

STDMETHODIMP_(INT) CDimensionLineImpl::GetMaxTipWidth()
{
   INT width = Do_GetMaxTipWidth();
   if ( m_TextBlock )
      return m_TextBlock->GetMaxTipWidth();
   else
      return width;
}

STDMETHODIMP_(void) CDimensionLineImpl::SetTipDisplayTime(INT iTime)
{
   if ( m_TextBlock )
      m_TextBlock->SetTipDisplayTime(iTime);
   else
      Do_SetTipDisplayTime(iTime); 
}

STDMETHODIMP_(INT) CDimensionLineImpl::GetTipDisplayTime()
{
   if ( m_TextBlock )
      return m_TextBlock->GetTipDisplayTime();
   else
      return Do_GetTipDisplayTime();
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      m_TextBlock->OnKeyDown(nChar,nRepCnt,nFlags);
      return true;
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnContextMenu(CWnd* pWnd,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      m_TextBlock->OnContextMenu(pWnd,point);
      return true;
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnLButtonDown(UINT nFlags,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnLButtonDown(nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnLButtonUp(UINT nFlags,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnLButtonUp(nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnLButtonDblClk(UINT nFlags,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnLButtonDblClk(nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnRButtonDown(UINT nFlags,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnRButtonDown(nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnRButtonUp(UINT nFlags,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnRButtonUp(nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnRButtonDblClk(UINT nFlags,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnRButtonDblClk(nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnMouseMove(UINT nFlags,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnMouseMove(nFlags,point);
   }
   else
   {
      return false;
   }
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnMouseWheel(UINT nFlags,short zDelta,CPoint point)
{
   // If there is a text block, forward the event
   if ( m_TextBlock )
   {
      return m_TextBlock->OnMouseWheel(nFlags,zDelta,point);
   }
   else
   {
      return false;
   }
}

/////////////////////////////////////////////////////////
// IDimensionLine Implementation
STDMETHODIMP_(void) CDimensionLineImpl::SetAngle(Float64 angle)
{
   m_Angle = angle;
   m_bAlignWithPlugs = FALSE;
}

STDMETHODIMP_(Float64) CDimensionLineImpl::GetAngle()
{
   return m_Angle;
}

STDMETHODIMP_(LONG) CDimensionLineImpl::GetHiddenWitnessLength()
{
   return m_HiddenWitnessLength;
}

STDMETHODIMP_(void) CDimensionLineImpl::SetHiddenWitnessLength(LONG l)
{
   m_HiddenWitnessLength = l;
}

STDMETHODIMP_(void) CDimensionLineImpl::SetWitnessLength(LONG l)
{
   m_LenWitness = l;
}

STDMETHODIMP_(LONG) CDimensionLineImpl::GetWitnessLength()
{
   return m_LenWitness;
}

STDMETHODIMP_(void) CDimensionLineImpl::SetWitnessOffset(LONG wOffset)
{
   m_WitnessOffset = wOffset;
}

STDMETHODIMP_(LONG) CDimensionLineImpl::GetWitnessOffset()
{
   return m_WitnessOffset;
}

STDMETHODIMP_(void) CDimensionLineImpl::SetArrowHeadSize(CSize size)
{
   m_ArrowWidth = size.cx;
   m_ArrowHeight = size.cy;
}

STDMETHODIMP_(CSize) CDimensionLineImpl::GetArrowHeadSize()
{
   return CSize(m_ArrowWidth,m_ArrowHeight);
}

STDMETHODIMP_(void) CDimensionLineImpl::SetArrowHeadStyle(DManip::ArrowHeadStyleType style)
{
   m_Style = style;
}

STDMETHODIMP_(DManip::ArrowHeadStyleType) CDimensionLineImpl::GetArrowHeadStyle()
{
   return m_Style;
}

STDMETHODIMP_(void) CDimensionLineImpl::EnableAutoText(BOOL bEnable)
{
   m_bAutoText = bEnable;
}

STDMETHODIMP_(BOOL) CDimensionLineImpl::IsAutoTextEnabled()
{
   return m_bAutoText;
}

STDMETHODIMP_(void) CDimensionLineImpl::SetTextBlock(iTextBlock* pTextBlock)
{
   if ( m_TextBlock )
   {
      InternalAddRef(); // opposite of InternalRelease below
      m_TextBlock->UnregisterEventSink();
      m_TextBlock = 0;
   }

   m_TextBlock = pTextBlock;
   if ( m_TextBlock )
   {
      CComPtr<iDisplayList> list;
      GetDisplayList(&list);
      m_TextBlock->SetDisplayList(list);
      m_TextBlock->RegisterEventSink(this); // this causes a circular reference
      InternalRelease(); // decrement our reference count
   }
}

STDMETHODIMP_(void) CDimensionLineImpl::GetTextBlock(iTextBlock** textBlock)
{
   (*textBlock) = m_TextBlock;

   if ( m_TextBlock )
      (*textBlock)->AddRef();
}

/////////////////////////////////////////////////////////
// iDisplayObjectEvents Implementation
STDMETHODIMP_(void) CDimensionLineImpl::OnChanged(iDisplayObject* pDO)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));

   // The text block changed...
   Fire_OnChanged();
}

STDMETHODIMP_(void) CDimensionLineImpl::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));

   // The text block moved...
   Fire_OnDragMoved(offset);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnLButtonDblClk(nFlags,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnLButtonDown(nFlags,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnLButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnRButtonDblClk(nFlags,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnRButtonDown(nFlags,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnRButtonUp(nFlags,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnMouseMove(nFlags,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
//   ASSERT(m_TextBlock.IsEqualObject(pDO));
   return Fire_OnMouseWheel(nFlags,zDelta,point);
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   return false; // Do nothing
}

STDMETHODIMP_(bool) CDimensionLineImpl::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   return false; // Do nothing
}

STDMETHODIMP_(void) CDimensionLineImpl::OnMoved(iDisplayObject* pDO)
{
   ATLASSERT(FALSE); // Should receive this event
}

STDMETHODIMP_(void) CDimensionLineImpl::OnCopied(iDisplayObject* pDO)
{
   ATLASSERT(FALSE); // Should receive this event
}

STDMETHODIMP_(void) CDimensionLineImpl::OnSelect(iDisplayObject* pDO)
{
   // Do nothing
}

STDMETHODIMP_(void) CDimensionLineImpl::OnUnselect(iDisplayObject* pDO)
{
   // Do nothing
}

/////////////////////
void CDimensionLineImpl::UpdateWorkPoints()
{
   // note that work points are in logical units
   CComPtr<iPlug> pStart;
   GetStartPlug(&pStart);

   CComPtr<iPlug> pEnd;
   GetEndPlug(&pEnd);

   CComPtr<iSocket> startSocket;
   pStart->GetSocket(&startSocket);
   CComPtr<IPoint2d> pStartPoint;
   startSocket->GetPosition(&pStartPoint);

   CComPtr<iSocket> endSocket;
   pEnd->GetSocket(&endSocket);
   CComPtr<IPoint2d> pEndPoint;
   endSocket->GetPosition(&pEndPoint);

   CComPtr<iDisplayList> pDL;
   Do_GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // determine number of logial units/twip in x and y
   LONG dotx, doty, dptx, dpty;
   pMap->TPtoLP(0,0,&dotx, &doty);
   pMap->TPtoLP(14400,14400,&dptx, &dpty);
   Float64 stx = fabs(Float64(dotx-dptx))/14400.;  // scale factor
   Float64 sty = fabs(Float64(doty-dpty))/14400.;

   pMap->WPtoLP(pStartPoint,&m_ptStart.x,&m_ptStart.y);
   pMap->WPtoLP(pEndPoint,&m_ptEnd.x,&m_ptEnd.y);

   Float64 angle = m_Angle;
   if ( m_bAlignWithPlugs )
   {
      Float64 sx,sy;
      pStartPoint->get_X(&sx);
      pStartPoint->get_Y(&sy);
      
      Float64 ex,ey;
      pEndPoint->get_X(&ex);
      pEndPoint->get_Y(&ey);

      Float64 dy = ey - sy;
      Float64 dx = ex - sx;

      angle = atan2(dy,dx);
   }

   // Determine the angle and length of the dimension line
   Float64 c = cos(angle);
   Float64 s = sin(angle);

   // things must be flipped around if witness length is negative
   Float64 fw = m_LenWitness<0.0 ? -1 : 1;

   // Left witness line
   //

   // Start of Witness Line
   m_ptA.x = m_ptStart.x - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*s*stx*fw);
   m_ptA.y = m_ptStart.y - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*c*sty*fw);

   // End of Witness Line
   m_ptB.x = m_ptStart.x - (LONG)(m_LenWitness*s*stx);
   m_ptB.y = m_ptStart.y - (LONG)(m_LenWitness*c*sty);


   // Right witness line
   //

   // Determine the amount to extend the right witness line
   // Find the point on the line between ptStart and angle
   // that is nearest ptEnd.
   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);
   p->Move(m_ptStart.x,-m_ptStart.y);

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_Direction(angle);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(p,v);

   CComPtr<IPoint2d> p3;
   p3.CoCreateInstance(CLSID_Point2d);
   p3->Move(m_ptEnd.x,-m_ptEnd.y);

   CComPtr<IGeomUtil2d> util;
   util.CoCreateInstance(CLSID_GeomUtil);

   CComPtr<IPoint2d> p4;
   util->PointOnLineNearest(line,p3,&p4);

   Float64 zx,zy;
   p4->get_X(&zx);
   p4->get_Y(&zy);
   m_ptZ.x = (LONG)(zx);
   m_ptZ.y = (LONG)(-zy);

   CSize extension = m_ptZ - m_ptEnd;

   // Start of Witness Line
   m_ptD.x = m_ptEnd.x - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*s*stx*fw);
   m_ptD.y = m_ptEnd.y - (LONG)((m_WitnessOffset+m_HiddenWitnessLength)*c*sty*fw);

   // End of Witness Line
   m_ptE.x = m_ptEnd.x + extension.cx - (LONG)(m_LenWitness*s*stx);
   m_ptE.y = m_ptEnd.y - extension.cy - (LONG)(m_LenWitness*c*sty);

   // Dimension line
   //

   // Start of dimension line (left side)
   m_ptC.x = m_ptStart.x - (LONG)((m_LenWitness - m_DimOffset*fw)*s*stx);
   m_ptC.y = m_ptStart.y - (LONG)((m_LenWitness - m_DimOffset*fw)*c*sty);

   // End of dimension line (right side)
   m_ptF.x = m_ptEnd.x + extension.cx - (LONG)((m_LenWitness - m_DimOffset*fw)*s*stx);
   m_ptF.y = m_ptEnd.y - extension.cy - (LONG)((m_LenWitness - m_DimOffset*fw)*c*sty);

   UpdateArrowHeads(stx, sty);
   UpdateTextBlock();
}

void CDimensionLineImpl::UpdateArrowHeads(Float64 stx, Float64 sty)
{
   CSize dl = m_ptF - m_ptC;
   Float64 angle = atan2((Float64)dl.cy,(Float64)dl.cx);

   m_StartArrow.tip = m_ptC;
   m_StartArrow.left.x = m_StartArrow.tip.x  + (LONG)((m_ArrowHeight*cos(angle) + m_ArrowWidth/2*sin(angle))*stx);
   m_StartArrow.left.y = m_StartArrow.tip.y  + (LONG)((m_ArrowHeight*sin(angle) - m_ArrowWidth/2*cos(angle))*sty);
   m_StartArrow.right.x = m_StartArrow.tip.x + (LONG)((m_ArrowHeight*cos(angle) - m_ArrowWidth/2*sin(angle))*stx);
   m_StartArrow.right.y = m_StartArrow.tip.y + (LONG)((m_ArrowHeight*sin(angle) + m_ArrowWidth/2*cos(angle))*sty);

   m_EndArrow.tip = m_ptF;
   m_EndArrow.left.x = m_EndArrow.tip.x  - (LONG)((m_ArrowHeight*cos(angle) - m_ArrowWidth/2*sin(angle))*stx);
   m_EndArrow.left.y = m_EndArrow.tip.y  - (LONG)((m_ArrowHeight*sin(angle) + m_ArrowWidth/2*cos(angle))*sty);
   m_EndArrow.right.x = m_EndArrow.tip.x - (LONG)((m_ArrowHeight*cos(angle) + m_ArrowWidth/2*sin(angle))*stx);
   m_EndArrow.right.y = m_EndArrow.tip.y - (LONG)((m_ArrowHeight*sin(angle) - m_ArrowWidth/2*cos(angle))*sty);
}

void CDimensionLineImpl::UpdateTextBlock()
{
   if ( m_TextBlock == 0 )
      return;

   // Update position
   CComPtr<iDisplayList> pDL;
   Do_GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // put the text block above the arrowheads
   Float64 x1,y1;
   pMap->LPtoWP(m_StartArrow.right.x,m_StartArrow.right.y,&x1,&y1);

   Float64 x2,y2;
   pMap->LPtoWP(m_EndArrow.left.x,m_EndArrow.left.y,&x2,&y2);

   CComPtr<IPoint2d> loc;
   loc.CoCreateInstance(CLSID_Point2d);
   loc->Move(0.5*(x1+x2),0.5*(y1+y2));
   m_TextBlock->SetPosition(loc);
   m_TextBlock->SetTextAlign(TA_BOTTOM | TA_CENTER);

   // Compute the angle of the text
   CSize delta = m_ptF - m_ptC;
   Float64 angle = atan(-(Float64)delta.cy/(Float64)delta.cx);

   LONG lAngle = (LONG)(1800.0*angle/M_PI); // tenth of a degree
   m_TextBlock->SetAngle(lAngle);

   if ( m_bAutoText )
   {
      CComPtr<iPlug> pStart;
      GetStartPlug(&pStart);

      CComPtr<iPlug> pEnd;
      GetEndPlug(&pEnd);

      CComPtr<iSocket> startSocket;
      pStart->GetSocket(&startSocket);
      CComPtr<IPoint2d> start;
      startSocket->GetPosition(&start);

      CComPtr<iSocket> endSocket;
      pEnd->GetSocket(&endSocket);
      CComPtr<IPoint2d> end;
      endSocket->GetPosition(&end);

      Float64 dist;
      start->DistanceEx(end, &dist);

      CString strDist;
      strDist.Format(_T("%f"),dist);

      m_TextBlock->SetText(strDist);
   }
}

void CDimensionLineImpl::IncludePointInRect(CPoint p,CRect* pRect)
{
   if ( p.x < pRect->left )
      pRect->left = p.x;

   if ( pRect->right < p.x )
      pRect->right = p.x;

   if ( p.y < pRect->top )
      pRect->top = p.y;

   if ( pRect->bottom < p.y )
      pRect->bottom = p.y;
}

//////////////////////////////////

void CDimensionLineImpl::GetStartPoint(IPoint2d* *point)
{
   CComPtr<iPlug> plug;
   GetStartPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}

void CDimensionLineImpl::GetEndPoint(IPoint2d* *point)
{
   CComPtr<iPlug> plug;
   GetEndPlug(&plug);

   CComPtr<iSocket> socket;
   plug->GetSocket(&socket);

   socket->GetPosition(point);
}
