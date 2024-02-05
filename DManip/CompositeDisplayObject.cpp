///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <DManip/CompositeDisplayObject.h>
#include <DManip/DisplayListImpl.h>

using namespace WBFL::DManip;

CompositeDisplayObject::CompositeDisplayObject(IDType id) : DisplayObjectDefaultImpl(id)
{
   m_CompositeItems = DisplayList::Create();
}

CompositeDisplayObject::~CompositeDisplayObject()
{
}

void CompositeDisplayObject::AddDisplayObject(std::shared_ptr<iDisplayObject> pDO)
{
   pDO->SetParent(weak_from_this());
   m_CompositeItems->AddDisplayObject(pDO);
   m_BoundingBox.reset();
}

void CompositeDisplayObject::RemoveDisplayObject(IDType key,AccessType access)
{
   m_CompositeItems->RemoveDisplayObject(key,access);
   m_BoundingBox.reset();
}

std::shared_ptr<iDisplayObject> CompositeDisplayObject::GetDisplayObject(IDType key,AccessType access)
{
   if ( access == AccessType::ByIndex )
      return m_CompositeItems->GetDisplayObject(key);
   else
      return m_CompositeItems->FindDisplayObject(key);
}

IndexType CompositeDisplayObject::GetDisplayObjectCount()
{
   return m_CompositeItems->GetDisplayObjectCount();
}

void CompositeDisplayObject::ClearDisplayObjects()
{
   m_CompositeItems->Clear();
   m_BoundingBox.reset();
}

std::shared_ptr<iDisplayList> CompositeDisplayObject::GetDisplayObjects()
{
   return m_CompositeItems;
}

//////////////////////////////////////////
// iDisplayObject implementation
void CompositeDisplayObject::SetDisplayList(std::weak_ptr<iDisplayList> pDL)
{
   __super::SetDisplayList(pDL);

   // Sync the display manager with the internal display list
   auto display_list = pDL.lock();
   if ( display_list )
   {
      auto disp_mgr = display_list->GetDisplayMgr();
      m_CompositeItems->SetDisplayMgr(disp_mgr);
   }
}

void CompositeDisplayObject::Visible(bool bVisible)
{
   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( IndexType i = 0; i < nDO; i++ )
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);
      dispObj->Visible(bVisible);
   }

   __super::Visible(bVisible); 
}

void CompositeDisplayObject::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   // Draw every display object
   m_CompositeItems->DrawDisplayObjects(pDC,FALSE);
}

void CompositeDisplayObject::Highlight(CDC* pDC,bool bHighlight)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( IndexType i = 0; i < nDO; i++ )
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);
      dispObj->Highlight(pDC,bHighlight);
   }
}

#if defined(_DEBUG)
void CompositeDisplayObject::DrawGravityWell(CDC* pDC)
{
   m_CompositeItems->DrawGravityWells(pDC);
}
#endif

RECT CompositeDisplayObject::GetLogicalBoundingBox() const
{
   CRect box;
   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( IndexType i = 0; i < nDO; i++ )
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);
      CRect doBox = dispObj->GetLogicalBoundingBox();
      if ( i == 0 )
         box = doBox;
      else
         box.UnionRect(&box,&doBox);
   }

   return box;
}

WBFL::Geometry::Rect2d CompositeDisplayObject::GetBoundingBox() const
{
   if (m_BoundingBox.has_value())
      return m_BoundingBox.value();

   WBFL::Geometry::Rect2d bbox;

   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( IndexType i = 0; i < nDO; i++ )
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);

      auto box = dispObj->GetBoundingBox();
      if ( i == 0 )
      {
         bbox = box;
      }
      else
      {
         bbox.Union(box);
      }
   }

   m_BoundingBox = bbox;
   return m_BoundingBox.value();
}

bool CompositeDisplayObject::HitTest(const POINT& point) const
{
   if ( m_pGravityWellStrategy )
   {
      // If the composite has its own gravity well, use it
      CRgn rgn;
      m_pGravityWellStrategy->GetGravityWell(shared_from_this(), &rgn);
      return rgn.PtInRegion(point);
   }
   else
   {
      // Hit test each member of the composite individually
      IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
      for ( IndexType i = 0; i < nDO; i++ )
      {
         auto dispObj = m_CompositeItems->GetDisplayObject(i);
         if ( dispObj->HitTest(point) )
            return TRUE;
      }

      return FALSE;
   }

   return FALSE;
}

bool CompositeDisplayObject::TouchesRect(const RECT& r) const
{
   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( IndexType i = 0; i < nDO; i++ )
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);
      if ( dispObj->TouchesRect(r) )
         return TRUE;
   }

   return FALSE;
}

void CompositeDisplayObject::Select(bool bSelect)
{
   // This this display object isn't selectable, simply return
   if ( GetSelectionType() == SelectionType::None )
      return;

   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( IndexType i = 0; i < nDO; i++ )
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);
      dispObj->Select(bSelect);
   }

   __super::Select(bSelect); 
}

void CompositeDisplayObject::SetSelectionType(SelectionType st)
{
   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( IndexType i = 0; i < nDO; i++ )
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);
      dispObj->SetSelectionType(st);
   }

   __super::SetSelectionType(st);
}

void CompositeDisplayObject::RetainSelection(bool bRetain)
{
   IndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for (IndexType i = 0; i < nDO; i++)
   {
      auto dispObj = m_CompositeItems->GetDisplayObject(i);
      dispObj->RetainSelection(bRetain);
   }

   __super:: RetainSelection(bRetain);
}
