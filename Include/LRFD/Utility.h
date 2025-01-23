///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#pragma once

#include <Lrfd\LrfdExp.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Utility class for miscellaneous LRFD formulations.
      class LRFDCLASS Utility
      {
      public:
         enum class GirderPosition{ LeftExterior, Interior, RightExterior};

         Utility() = delete;
         Utility(const Utility&) = delete;
         ~Utility() = delete;

         Utility& operator=(const Utility&) = delete;

         /// @brief Computes the effective slab width of a slab on IBeam section.
         /// Code Reference: 1st Edition Article 4.6.2.6
         /// Units: Consistant Length Units
         /// 
         /// @param effLength        Effective Span Length
         /// @param leftSpacing      Spacing to girder left of this one or distance to edge of slab if left exterior girder.
         /// @param rightSpacing     Spacing to girder right of this one or distance to edge of slab if right exterior girder
         /// @param tSlab            Structural depth of the slab
         /// @param tWeb             Thickness of the I-beam web
         /// @param tWeb             Thickness of the I-beam web
         /// wTopFlange       Width of the I-beam top flange
         /// @param tWeb             Thickness of the I-beam web
         /// pos              Position of this girder in the cross section
         static Float64 IbeamEffFlangeWidth(Float64 effSpanLength,
                                            Float64 leftSpacing,
                                            Float64 rightSpacing,
                                            Float64 tSlab,
                                            Float64 tWeb,
                                            Float64 wTopFlange,
                                            GirderPosition position);

         /// @brief Returns the multiple presence factor the the specified number of loaded lanes. Article 3.6.1.1.2
         static Float64 GetMultiplePresenceFactor(IndexType nLanesLoaded);

         /// @brief Returns the width of a single design lane, given the curb to curb width of the driving surface. Article 3.6.1.1.1
         static Float64 GetDesignLaneWidth(Float64 wCurbToCurb);

         /// @brief Returns the number of design lanes, given the curb to curb width of the driving surface. Article 3.6.1.1.1
         static Uint16 GetNumDesignLanes(Float64 wCurbToCurb);
      };
   };
};
