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
#include <DManip/PointDisplayObjectImpl.h>
#include <DManip/DisplayMgr.h>
#include <DManip/DragData.h>
#include <DManip/SimpleDrawPointStrategy.h>
#include <DManip/DisplayView.h>

#include <math.h>

using namespace WBFL::DManip;

UINT PointDisplayObject::ms_cfFormat = ::RegisterClipboardFormat(_T("WBFLDManip.PointDisplayObject"));

PointDisplayObject::PointDisplayObject(IDType id) :
   iPointDisplayObject(id)
{
   m_pDrawStrategy = SimpleDrawPointStrategy::Create();
}

void PointDisplayObject::Draw(CDC* pDC)
{
   if (!IsVisible()) return; // don't draw if not visible

   if (m_pDrawStrategy)
   {
      auto dispObj = std::dynamic_pointer_cast<iPointDisplayObject>(shared_from_this());
      m_pDrawStrategy->Draw(dispObj, pDC);
   }
}

void PointDisplayObject::Highlight(CDC* pDC, bool bHighlight)
{
   if (!IsVisible()) return; // don't draw if not visible

   if (m_pDrawStrategy)
   {
      auto dispObj = std::dynamic_pointer_cast<iPointDisplayObject>(shared_from_this());
      m_pDrawStrategy->DrawHighlight(dispObj, pDC, bHighlight);
   }
}

WBFL::Geometry::Rect2d PointDisplayObject::GetBoundingBox() const
{
   if (m_pDrawStrategy)
   {
      auto dispObj = std::dynamic_pointer_cast<const iPointDisplayObject>(shared_from_this());
      return m_pDrawStrategy->GetBoundingBox(dispObj);
   }
   else
   {
      return { m_Position,m_Position };
   }
}

void PointDisplayObject::SetPosition(const WBFL::Geometry::Point2d& pos, bool bRedraw, bool bFireEvent)
{
   if ( bRedraw )
   {
      // Erase the old graphic
      auto pDL = GetDisplayList();
      auto pDispMgr = pDL->GetDisplayMgr();

      CRect box = GetLogicalBoundingBox();
      pDispMgr->GetView()->InvalidateRect(box);
   }
   
   // Set the new position
   auto [currX, currY] = m_Position.GetLocation();
   m_Position = pos;

   // Update the position of all the sockets
   std::for_each(m_Sockets.begin(), m_Sockets.end(), [p=m_Position](auto& socket) {socket->SetPosition(p); });

   if ( bRedraw )
   {
      auto pDL = GetDisplayList();
      auto pDispMgr = pDL->GetDisplayMgr();
      CRect box = GetLogicalBoundingBox();
      pDispMgr->GetView()->InvalidateRect(box);
   }

   if ( bFireEvent )
   {
      // Compute the amount moved
      auto [x, y] = m_Position.GetLocation();

      WBFL::Geometry::Size2d offset(x - currX, y - currY);
      Fire_OnDragMoved(offset);
   }
}

const WBFL::Geometry::Point2d& PointDisplayObject::GetPosition() const
{
   return m_Position;
}

CPoint PointDisplayObject::GetLogicalPosition() const
{
   auto pDL = GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   auto map = pDispMgr->GetCoordinateMap();

   LONG lx,ly;
   map->WPtoLP(m_Position,&lx,&ly);

   CPoint p(lx,ly);

   return p;
}

void PointDisplayObject::Offset(const WBFL::Geometry::Size2d& offset, bool bRedraw, bool bFireEvent)
{
   m_Position.Offset(offset);
   SetPosition(m_Position,bRedraw,bFireEvent);
}

void PointDisplayObject::SetDrawingStrategy(std::shared_ptr<iDrawPointStrategy> pStrategy)
{
   m_pDrawStrategy = pStrategy;
}

std::shared_ptr<iDrawPointStrategy> PointDisplayObject::GetDrawingStrategy()
{
   return m_pDrawStrategy;
}

void PointDisplayObject::EnableAutoUpdate(bool bEnable)
{
   m_bAutoUpdate = bEnable;
}

bool PointDisplayObject::IsAutoUpdateEnabled() const
{
   return m_bAutoUpdate;
}

void PointDisplayObject::SetDragData(std::shared_ptr<iDragData> dd)
{
   m_pDragData = dd;
}

std::shared_ptr<iDragData> PointDisplayObject::GetDragData()
{
   return m_pDragData;
}

UINT PointDisplayObject::Format()
{
   return ( m_pDragData ) ? m_pDragData->Format() : 0;
}

void PointDisplayObject::PrepareDrag(std::shared_ptr<iDragDataSink> pSink)
{
   pSink->CreateFormat(ms_cfFormat);
   UINT size = sizeof(Float64);

   auto [x, y] = m_Position.GetLocation();

   pSink->Write(ms_cfFormat,&x,size);
   pSink->Write(ms_cfFormat,&y,size);

   if ( m_pDragData )
   {
      m_pDragData->PrepareForDrag(shared_from_this(), pSink);
   }
}

void PointDisplayObject::OnDrop(std::shared_ptr<iDragDataSource> pSource)
{
   Float64 x,y;
   UINT size = sizeof(Float64);

   pSource->Read(ms_cfFormat,&x,size);
   pSource->Read(ms_cfFormat,&y,size);

   m_Position.Move(x, y);

  if ( m_pDragData )
     m_pDragData->OnDrop(shared_from_this(), pSource);
}

void PointDisplayObject::DrawDragImage(CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint)
{
   m_pDrawStrategy->DrawDragImage(std::dynamic_pointer_cast<iPointDisplayObject>(shared_from_this()), pDC, map, dragStart, dragPoint);
}

void PointDisplayObject::OnDragMoved(const WBFL::Geometry::Size2d& offset)
{
   if (m_bAutoUpdate)
   {
      Offset(offset,TRUE,FALSE); // TRUE = Redraw
                                 // FALSE = don't fire event... We fire it below
   }

   Fire_OnDragMoved(offset);
}

void PointDisplayObject::OnMoved()
{
   // This display object got moved onto another drop target
   Fire_OnMoved();
}

void PointDisplayObject::OnCopied()
{
   // This display object got copied onto another drop target
   Fire_OnCopied();
}
