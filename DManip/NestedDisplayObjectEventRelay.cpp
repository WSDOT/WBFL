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
#include <DManip/NestedDisplayObjectEventRelay.h>

using namespace WBFL::DManip;

std::shared_ptr<NestedDisplayObjectEventRelay> NestedDisplayObjectEventRelay::Create(DisplayObjectDefaultImpl* parent)
{
   return std::shared_ptr<NestedDisplayObjectEventRelay>(new NestedDisplayObjectEventRelay(parent));
}

NestedDisplayObjectEventRelay::NestedDisplayObjectEventRelay(DisplayObjectDefaultImpl* parent) : m_pParent(parent)
{
}

void NestedDisplayObjectEventRelay::OnChanged(std::shared_ptr<iDisplayObject> pDO)
{
   m_pParent->Fire_OnChanged();
}

void NestedDisplayObjectEventRelay::OnDragMoved(std::shared_ptr<iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset)
{
   m_pParent->Fire_OnDragMoved(offset);
}

bool NestedDisplayObjectEventRelay::OnKeyDown(std::shared_ptr<iDisplayObject> pDO, UINT nChar, UINT nRepCnt, UINT nFlags)
{
   return m_pParent->Fire_OnKeyDown(nChar, nRepCnt, nFlags);
}

bool NestedDisplayObjectEventRelay::OnContextMenu(std::shared_ptr<iDisplayObject> pDO, CWnd* pWnd, const POINT& point)
{
   return m_pParent->Fire_OnContextMenu(pWnd, point);
}

bool NestedDisplayObjectEventRelay::OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return m_pParent->Fire_OnLButtonDblClk(nFlags, point);
}

bool NestedDisplayObjectEventRelay::OnLButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return m_pParent->Fire_OnLButtonDown(nFlags, point);
}

bool NestedDisplayObjectEventRelay::OnLButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return m_pParent->Fire_OnLButtonUp(nFlags, point);
}

bool NestedDisplayObjectEventRelay::OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return m_pParent->Fire_OnRButtonDblClk(nFlags, point);
}

bool NestedDisplayObjectEventRelay::OnRButtonDown(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return m_pParent->Fire_OnRButtonDown(nFlags, point);
}

bool NestedDisplayObjectEventRelay::OnRButtonUp(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return m_pParent->Fire_OnRButtonUp(nFlags, point);
}

bool NestedDisplayObjectEventRelay::OnMouseMove(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, const POINT& point)
{
   return m_pParent->Fire_OnMouseMove(nFlags, point);
}

bool NestedDisplayObjectEventRelay::OnMouseWheel(std::shared_ptr<iDisplayObject> pDO, UINT nFlags, short zDelta, const POINT& point)
{
   return m_pParent->Fire_OnMouseWheel(nFlags, zDelta, point);
}

void NestedDisplayObjectEventRelay::OnMoved(std::shared_ptr<iDisplayObject> pDO)
{
   m_pParent->Fire_OnMoved();
}

void NestedDisplayObjectEventRelay::OnCopied(std::shared_ptr<iDisplayObject> pDO)
{
   m_pParent->Fire_OnCopied();
}

void NestedDisplayObjectEventRelay::OnSelect(std::shared_ptr<iDisplayObject> pDO)
{
   m_pParent->Fire_OnSelect();
}

void NestedDisplayObjectEventRelay::OnUnselect(std::shared_ptr<iDisplayObject> pDO)
{
   m_pParent->Fire_OnUnselect();
}


