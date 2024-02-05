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
#include <DManip/ShapeGravityWellStrategy.h>
#include <DManip/DisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>

using namespace WBFL::DManip;

ShapeGravityWellStrategy::ShapeGravityWellStrategy(std::shared_ptr<WBFL::Geometry::Shape> shape)
{
   SetShape(shape);
}

void ShapeGravityWellStrategy::SetShape(std::shared_ptr<WBFL::Geometry::Shape> shape)
{
   m_Shape = shape;
   m_CompositeShape = std::dynamic_pointer_cast<WBFL::Geometry::CompositeShape>(m_Shape);
}

std::shared_ptr<WBFL::Geometry::Shape> ShapeGravityWellStrategy::GetShape()
{
   return m_Shape;
}

std::shared_ptr<const WBFL::Geometry::Shape> ShapeGravityWellStrategy::GetShape() const
{
   return m_Shape;
}

void ShapeGravityWellStrategy::GetGravityWell(std::shared_ptr<const iDisplayObject> pDO,CRgn* pRgn)
{
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();
   auto points = m_Shape->GetPolyPoints();
   POINT* logical_points = new POINT[points.size()];
   IndexType i = 0;
   for (auto& point : points)
   {
      POINT lp;
      map->WPtoLP(map->MPtoWP(point), &lp.x, &lp.y);
      logical_points[i++] = lp;
   }
   pRgn->CreatePolygonRgn(logical_points,(int)points.size(), ALTERNATE);
   delete [] logical_points;
}
