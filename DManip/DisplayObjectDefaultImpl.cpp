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

#include "pch.h"
#include <DManip/DisplayObjectDefaultImpl.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include <DManip/DropSite.h>
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

DisplayObjectDefaultImpl::DisplayObjectDefaultImpl(IDType id) :
   m_ID(id)
{
};

DisplayObjectDefaultImpl::~DisplayObjectDefaultImpl()
{
   if ( m_pItemData && m_bDeleteItemData )
   {
      delete m_pItemData;
      m_pItemData = nullptr;
   }

   UnregisterEventSink();
   UnregisterDropSite();
}

void DisplayObjectDefaultImpl::SetID(IDType id)
{
   m_ID = id;
}

IDType DisplayObjectDefaultImpl::GetID() const
{
   return m_ID;
}

void DisplayObjectDefaultImpl::SetItemData(void* pVoid,bool bDelete)
{
   if ( m_pItemData && m_bDeleteItemData )
   {
      delete m_pItemData;
      m_pItemData = nullptr;
   }

   m_pItemData = pVoid;
   m_bDeleteItemData = bDelete;
}

void DisplayObjectDefaultImpl::GetItemData(void** ppVoid)
{
   (*ppVoid) = m_pItemData;
}

void DisplayObjectDefaultImpl::Visible(bool bVisible)
{
   BOOL bRedraw = (m_bIsVisible != bVisible);
   m_bIsVisible = bVisible;

   if ( bRedraw && m_pDispList.lock() != nullptr )
   {
      auto pDispMgr = m_pDispList.lock()->GetDisplayMgr();
      CRect box = GetLogicalBoundingBox();
      box.InflateRect(1,1);
      pDispMgr->GetView()->InvalidateRect(box);
   }
}

bool DisplayObjectDefaultImpl::IsVisible() const
{
   return m_bIsVisible;
}

#if defined(_DEBUG)
void DisplayObjectDefaultImpl::DrawGravityWell(CDC* pDC)
{
   // Draw gravity well for selected objects only
//   if ( !m_pParent->IsSelected() )
//      return;

   auto strategy = GetGravityWellStrategy();

   COLORREF color = RGB(255,200,200);

   CBrush fillBrush;
   fillBrush.CreateHatchBrush(HS_DIAGCROSS,color);

   CBrush frameBrush;
   frameBrush.CreateSolidBrush(color);
   if ( strategy )
   {
      CRgn rgn;
      strategy->GetGravityWell(shared_from_this(), &rgn);
      pDC->FrameRgn(&rgn,&frameBrush,2,2);
      pDC->FillRgn(&rgn,&fillBrush);
   }
   else
   {
      CRect box = GetLogicalBoundingBox();
      pDC->FrameRect(&box,&frameBrush);
      pDC->FillRect(&box,&fillBrush);
   }
}
#endif

void DisplayObjectDefaultImpl::SetDisplayList(std::weak_ptr<iDisplayList> pDL)
{
   m_pDispList = pDL;
}

std::shared_ptr<iDisplayList> DisplayObjectDefaultImpl::GetDisplayList()
{
   return m_pDispList.lock();
}

std::shared_ptr<const iDisplayList> DisplayObjectDefaultImpl::GetDisplayList() const
{
   return m_pDispList.lock();
}

void DisplayObjectDefaultImpl::SetGravityWellStrategy(std::shared_ptr<iGravityWellStrategy> pStrategy)
{
   m_pGravityWellStrategy = pStrategy;
}

std::shared_ptr<iGravityWellStrategy> DisplayObjectDefaultImpl::GetGravityWellStrategy()
{
   return m_pGravityWellStrategy;
}

bool DisplayObjectDefaultImpl::HitTest(const POINT& point) const
{
   if ( m_pGravityWellStrategy )
   {
      CRgn rgn;
      m_pGravityWellStrategy->GetGravityWell(shared_from_this(), &rgn);
      if ( rgn.m_hObject != nullptr )
         return rgn.PtInRegion(point) == TRUE ? true : false;
      else
         return false;
   }
   else
   {
      CRect box = GetLogicalBoundingBox();
      return box.PtInRect(point);
   }

   return false;
}

bool DisplayObjectDefaultImpl::TouchesRect(const RECT& r) const
{
   CRect box = GetLogicalBoundingBox();
   return ( (box.left < r.right && r.left < box.right) &&
      (box.bottom > r.top && r.bottom > box.top) ) ? true : false;
}

RECT DisplayObjectDefaultImpl::GetLogicalBoundingBox() const
{
   // In lieu of an implementation supplied by the parent object,
   // get the bounding box in world coordinates and map to
   // logical coordinates.
   auto box = GetBoundingBox();
   auto wl = box.Left();
   auto wr = box.Right();
   auto wt = box.Top();
   auto wb = box.Bottom();

   auto pDispMgr = m_pDispList.lock()->GetDisplayMgr();
   auto map = pDispMgr->GetCoordinateMap();

   LONG l,r,t,b;
   map->WPtoLP(wl, wt, &l, &t);
   map->WPtoLP(wr, wb, &r, &b);

   CRect rect(l,t,r,b);
   rect.NormalizeRect();
   return rect;
}

void DisplayObjectDefaultImpl::Select(bool bSelect)
{
   // If the display object cannot be selected, just get the heck outta here
   if ( m_SelectionType == SelectionType::None )
      return;

   if ( m_bSelected == bSelect )
      return;

   m_bSelected = bSelect;
   
   if ( m_bSelected )
      Fire_OnSelect();
   else
      Fire_OnUnselect();

   auto pDispMgr = m_pDispList.lock()->GetDisplayMgr();

// selecting the gravity well region tends to leave stray marks when an object is
// unselected. For this reason, I've changed this to use only the bounding box
// RAB 2/1/08
//
//   CComPtr<iGravityWellStrategy> gravityWellStrategy;
//   m_pParent->GetGravityWellStrategy(&gravityWellStrategy);
//   if ( gravityWellStrategy )
//   {
//      CRgn rgnGravityWell;
//      gravityWellStrategy->GetGravityWell(m_pParent,&rgnGravityWell);
//      pDispMgr->InvalidateRgn(&rgnGravityWell);
//   }
//   else
//   {
      CRect box = GetLogicalBoundingBox();
      box.InflateRect(1,1); // inflate a bit for tolerancing
      pDispMgr->GetView()->InvalidateRect(box);
//   }
}

bool DisplayObjectDefaultImpl::IsSelected() const
{
   return m_bSelected;
}

void DisplayObjectDefaultImpl::SetSelectionType(SelectionType st)
{
   m_SelectionType = st;
}

SelectionType DisplayObjectDefaultImpl::GetSelectionType() const
{
   return m_SelectionType;
}

void DisplayObjectDefaultImpl::RetainSelection(bool bRetain)
{
   m_bRetainSelection = bRetain;
}

bool DisplayObjectDefaultImpl::RetainSelection() const
{
   return m_bRetainSelection;
}

bool DisplayObjectDefaultImpl::OnLButtonDblClk(UINT nFlags,const POINT& point)
{
   return Fire_OnLButtonDblClk(nFlags,point);
}

bool DisplayObjectDefaultImpl::OnLButtonDown(UINT nFlags, const POINT& point)
{
   return Fire_OnLButtonDown(nFlags,point);
}

bool DisplayObjectDefaultImpl::OnLButtonUp(UINT nFlags, const POINT& point)
{
   return Fire_OnLButtonUp(nFlags,point);
}

bool DisplayObjectDefaultImpl::OnRButtonDown(UINT nFlags, const POINT& point)
{
   return Fire_OnRButtonDown(nFlags,point);
}

bool DisplayObjectDefaultImpl::OnRButtonUp(UINT nFlags, const POINT& point)
{
   return Fire_OnRButtonUp(nFlags,point);
}

bool DisplayObjectDefaultImpl::OnRButtonDblClk(UINT nFlags, const POINT& point)
{
   return Fire_OnRButtonDblClk(nFlags,point);
}

bool DisplayObjectDefaultImpl::OnMouseMove(UINT nFlags, const POINT& point)
{
   return Fire_OnMouseMove(nFlags,point);
}

bool DisplayObjectDefaultImpl::OnMouseWheel(UINT nFlags,short zDelta, const POINT& point)
{
   return Fire_OnMouseWheel(nFlags,zDelta,point);
}

bool DisplayObjectDefaultImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   return Fire_OnKeyDown(nChar,nRepCnt,nFlags);
}

bool DisplayObjectDefaultImpl::OnContextMenu(CWnd* pWnd, const POINT& point)
{
   return Fire_OnContextMenu(pWnd,point);
}

void DisplayObjectDefaultImpl::SetToolTipText(LPCTSTR lpszToolTipText)
{
   m_strToolTipText = lpszToolTipText;
}

std::_tstring DisplayObjectDefaultImpl::GetToolTipText() const
{
   return m_strToolTipText;
}

void DisplayObjectDefaultImpl::SetMaxTipWidth(INT maxWidth)
{
   m_MaxToolTipWidth = maxWidth;
}

INT DisplayObjectDefaultImpl::GetMaxTipWidth() const
{
   return m_MaxToolTipWidth;
}

void DisplayObjectDefaultImpl::SetTipDisplayTime(INT iTime)
{
   m_ToolTipDisplayTime = iTime;
}

INT DisplayObjectDefaultImpl::GetTipDisplayTime() const
{
   return m_ToolTipDisplayTime;
}

void DisplayObjectDefaultImpl::RegisterEventSink(std::shared_ptr<iDisplayObjectEvents> pEventSink)
{
   UnregisterEventSink();

   m_EventSink = pEventSink;
}

void DisplayObjectDefaultImpl::UnregisterEventSink()
{
   m_EventSink.reset();
}

std::shared_ptr<iDisplayObjectEvents> DisplayObjectDefaultImpl::GetEventSink()
{
   return m_EventSink;
}

void DisplayObjectDefaultImpl::RegisterDropSite(std::shared_ptr<iDropSite> pDropSite)
{
   m_pDropSite = pDropSite;
   m_pDropSite->SetDisplayObject(weak_from_this());
}

void DisplayObjectDefaultImpl::UnregisterDropSite()
{
   if (m_pDropSite)
   {
      m_pDropSite->SetDisplayObject(std::shared_ptr<iDisplayObject>());
      m_pDropSite.reset();
   }
}

std::shared_ptr<iDropSite> DisplayObjectDefaultImpl::GetDropSite()
{
   return m_pDropSite;
}

void DisplayObjectDefaultImpl::SetParent(std::weak_ptr<iDisplayObject> pParent)
{
   m_pCompositeParent = pParent;
}

std::shared_ptr<iDisplayObject> DisplayObjectDefaultImpl::GetParent()
{
   return m_pCompositeParent.lock();
}

void DisplayObjectDefaultImpl::Fire_OnChanged()
{
   if (m_EventSink)
      m_EventSink->OnChanged(shared_from_this());
}

void DisplayObjectDefaultImpl::Fire_OnDragMoved(const WBFL::Geometry::Size2d& offset)
{
   if (m_EventSink)
      m_EventSink->OnDragMoved(shared_from_this(), offset);
}

void DisplayObjectDefaultImpl::Fire_OnMoved()
{
   if (m_EventSink)
      m_EventSink->OnMoved(shared_from_this());
}

void DisplayObjectDefaultImpl::Fire_OnCopied()
{
   if (m_EventSink)
      m_EventSink->OnCopied(shared_from_this());
}

bool DisplayObjectDefaultImpl::Fire_OnLButtonDblClk(UINT nFlags, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnLButtonDblClk(shared_from_this(), nFlags, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnLButtonDown(UINT nFlags, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnLButtonDown(shared_from_this(), nFlags, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnLButtonUp(UINT nFlags, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnLButtonUp(shared_from_this(), nFlags, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnRButtonDown(UINT nFlags, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnRButtonDown(shared_from_this(), nFlags, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnRButtonUp(UINT nFlags, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnRButtonUp(shared_from_this(), nFlags, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnRButtonDblClk(UINT nFlags, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnRButtonDblClk(shared_from_this(), nFlags, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnMouseMove(UINT nFlags, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnMouseMove(shared_from_this(), nFlags, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnMouseWheel(UINT nFlags, short zDelta, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnMouseWheel(shared_from_this(), nFlags, zDelta, point);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if (m_EventSink)
   {
      return m_EventSink->OnKeyDown(shared_from_this(), nChar, nRepCnt, nFlags);
   }
   else
   {
      return false;
   }
}

bool DisplayObjectDefaultImpl::Fire_OnContextMenu(CWnd* pWnd, const POINT& point)
{
   if (m_EventSink)
   {
      return m_EventSink->OnContextMenu(shared_from_this(), pWnd, point);
   }
   else
   {
      return false;
   }
}

void DisplayObjectDefaultImpl::Fire_OnSelect()
{
   if (m_EventSink)
      m_EventSink->OnSelect(shared_from_this());
}

void DisplayObjectDefaultImpl::Fire_OnUnselect()
{
   if (m_EventSink)
      m_EventSink->OnUnselect(shared_from_this());
}
