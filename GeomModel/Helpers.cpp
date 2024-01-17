///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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
#include <GeomModel/GeomModelLib.h>
#include "Helpers.h"

using namespace WBFL::Geometry;

void WBFL::Geometry::GenerateFillet(std::vector<Point2d>& vPoints, Float64 cx, Float64 cy, Float64 r, Float64 startAngle, Float64 delta, IndexType nSpaces)
{
   Float64 dAngle = delta / nSpaces;
   for (IndexType i = 0; i <= nSpaces; i++)
   {
      Float64 x = cx + r * cos(startAngle + i * dAngle);
      Float64 y = cy + r * sin(startAngle + i * dAngle);

      vPoints.emplace_back(x, y);
   }
}
