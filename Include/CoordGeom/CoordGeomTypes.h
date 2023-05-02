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
#pragma once

#include <CoordGeom/CoordGeomExp.h>

namespace WBFL
{
   namespace COGO
   {
      /// Constant identifying the direction of the angle formed by a circular curve tangent line and the line connecting the centers of circles.
      enum class TangentSign
      {
         CCW = 1, ///< Counter-clockwise angle
         CW = -1 ///< Clockwise angle
      };

      enum class CurveDirection
      {
         Left,
         Right
      };

      enum class DegreeCurvature
      {
         Chord,
         Arc,
         Railroad,
         Highway
      };

      enum class TransitionCurveType
      {
         Clothoid
         // Bloss.... and others in the future
      };

      enum class OffsetType
      {
         AlongDirection, ///< Offset is measured along a line projecting from an object
         Normal ///< Offset is measured normal to the object
      };
   };
};