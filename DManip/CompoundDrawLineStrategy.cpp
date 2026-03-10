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
#include <DManip/CompoundDrawLineStrategy.h>

using namespace WBFL::DManip;

void CompoundDrawLineStrategy::Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const
{
   for (auto& strategy : m_Strategies)
   {
      strategy->Draw(pDO, pDC);
   }
}

void CompoundDrawLineStrategy::DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
   for (auto& strategy : m_Strategies)
   {
      strategy->DrawDragImage(pDO, pDC, map, dragStart, dragPoint);
   }
}

void CompoundDrawLineStrategy::DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const
{
   for (auto& strategy : m_Strategies)
   {
      strategy->DrawHighlight(pDO, pDC, bHighlight);
   }
}

WBFL::Geometry::Rect2d CompoundDrawLineStrategy::GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   WBFL::Geometry::Rect2d bounding_box;

   if (m_Strategies.empty())
      return bounding_box;

   auto iter = m_Strategies.begin();
   auto end = m_Strategies.end();
   bounding_box = (*iter)->GetBoundingBox(pDO);
   iter++;
   for (; iter != end; iter++)
   {
      bounding_box.Union((*iter)->GetBoundingBox(pDO));
   }
   return bounding_box;
}

/////////////////////////////////////////////////////////
// iSimpleLineDrawStrategy Implementation
void CompoundDrawLineStrategy::AddStrategy(std::shared_ptr<iDrawLineStrategy> pStrategy)
{
   m_Strategies.push_back(pStrategy);
}

void CompoundDrawLineStrategy::RemoveStrategy(IndexType index)
{
   PRECONDITION(0 <= index and index < m_Strategies.size());
   m_Strategies.erase(m_Strategies.begin() + index);
}

std::shared_ptr<iDrawLineStrategy> CompoundDrawLineStrategy::GetStrategy(IndexType index)
{
   PRECONDITION(0 <= index and index < m_Strategies.size());
   return m_Strategies[index];
}

std::shared_ptr<const iDrawLineStrategy> CompoundDrawLineStrategy::GetStrategy(IndexType index) const
{
   PRECONDITION(0 <= index and index < m_Strategies.size());
   return m_Strategies[index];
}

IndexType CompoundDrawLineStrategy::Count() const
{
   return m_Strategies.size();
}
