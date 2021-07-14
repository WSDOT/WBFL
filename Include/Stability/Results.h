///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2021  Washington State Department of Transportation
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

#include <Stability\StabilityExp.h>
#include <array>

namespace WBFL
{
   namespace Stability
   {

      /// Base class for analysis results
      class STABILITYCLASS Results
      {
      public:
         Results();

         Float64 Ll; ///< left overhang (trailing overhang)
         Float64 Lr; ///< right overhang (leading overhang)
         Float64 Ls; ///< span length between supports
         Float64 Wg; ///< total weight of girder

         CalculationMethod XcgMethod; ///< Indicates the method that was used to compute the location of the center of mass
         Float64 Xleft; ///< horizontal location of the CG with respect to the roll axis

         Float64 Yr;  ///< location from the center of gravity from the roll axis in girder section coordinates (positive means roll center is above CG)
         std::array<Float64, 3> Dra; ///< distance from the center of gravity to the roll axis, adjusted for camber. Array index is ImpactDirection.

         Float64 OffsetFactor; ///< cg offset factor
         Float64 CamberOffsetFactor; ///< factor used to multiple with Yr to adjust for camber (this is the Bob Mast "increase by 2% to account for camber") method
         Float64 LateralSweep; ///< lateral sweep due to imperfections (SweepTolerance*Lg + SupportOffset)
         std::array<Float64, 3> EccLateralSweep; ///< eccentricty of CG due to lateral sweep (OffsetFactor*LateralSweep + SupportPlacementTolerance)*emag[impact]. Array index is ImpactDirection.

         Float64 WindPressure; ///< computed or input wind pressure
         std::array<Float64, 3> Ywind;   ///< distance between roll center and resultant wind force (mid-height of girder). Array index is ImpactDirection.
         std::array<Float64, 3> EccWind; ///< vertical eccentricty of the girder self-weight load with respect to the roll axis. Array index is ImpactDirection.
         Float64 Wwind;   ///< total wind force (applied at EccWind)

         CalculationMethod ZoMethod; ///< Indicates the method for computing the location of the center of mass
         std::array<Float64, 3> Zo;  ///< lateral deflection of center of gravity for full dead load applied laterally. Array index is ImpactDirection.
         std::array<Float64, 3> ZoWind; ///< lateral deflection of center of gravity for full wind applied laterally. Array index is ImpactDirection.
      };
   }
}