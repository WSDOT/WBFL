///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/PathElement.h>
#include <CoordGeom/Path.h>

using namespace WBFL::COGO;

PathElement::PathElement(const PathElement& other)
{
   // Do nothing here.
   // Note that the default copy constructor doesn't work for us
   // Doing nothing makes the associated m_Path a nullptr, which is what we want
}

std::shared_ptr<const Path> PathElement::GetPath() const
{
   return m_Path.lock();
}

std::shared_ptr<Path> PathElement::GetPath()
{
   return m_Path.lock();
}

WBFL::Geometry::Line2d PathElement::GetStartTangent() const
{
   auto direction = GetBearing(0.0);
   WBFL::Geometry::Vector2d v(1.0, direction);
   const auto& start_point = GetStartPoint();
   WBFL::Geometry::Line2d tangent(start_point, v);
   return tangent;
}

WBFL::Geometry::Line2d PathElement::GetEndTangent() const
{
   auto direction = GetBearing(GetLength());
   WBFL::Geometry::Vector2d v(1.0, direction);
   const auto& end_point = GetEndPoint();
   WBFL::Geometry::Line2d tangent(end_point, v);
   return tangent;
}

void PathElement::OnPathElementChanged()
{
   auto path = GetPath();
   if(path) path->OnPathChanged();
}
