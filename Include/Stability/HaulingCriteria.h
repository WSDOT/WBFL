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

/*****************************************************************************
CLASS 
   stbCriteria

DESCRIPTION
   Encapsulates the criteria for analysis
*****************************************************************************/

/// Criteria for hauling analysis
class STABILITYCLASS stbHaulingCriteria
{
public:
   stbHaulingCriteria();

   Float64 Lambda; ///< concrete density modification factor (see LRFD 5.4.2.8)

   Float64 CompressionCoefficient_GlobalStress; ///< Compression stress limit coefficienent for global stress
   Float64 CompressionCoefficient_PeakStress; ///< Compression stress limit coefficient for peak stress
   std::array<Float64, 2> TensionCoefficient; ///< Tension stress limit coefficient (array index is stbTypes::HaulingSlope)
   std::array<bool, 2> bMaxTension; ///< Boolean indicating if there is a maximum tension stress limit (array index is stbTypes::HaulingSlope)
   std::array<Float64, 2> MaxTension; ///< Maximum tension stress limit (array index is stbTypes::HaulingSlope)
   std::array<Float64, 2> TensionCoefficientWithRebar; ///< Tension stress limit coefficient for sections with adequate reinforcement (array index is stbTypes::HaulingSlope)

   Float64 MinFScr; ///< Minimum factor of safety against cracking
   Float64 MinFSf;  ///< Minimum factor of safety against failure

   Float64 AllowableCompression_GlobalStress; ///< Compression stress limit for global stress
   Float64 AllowableCompression_PeakStress; ///< Compression stress limit for peak stress
   std::array<Float64, 2> AllowableTension; ///< Tension stress limit (array index is stbTypes::HaulingSlope)
   std::array<Float64, 2> AllowableTensionWithRebar; ///< Tension tension stress limit if there is adequate rebar (array index is stbTypes::HaulingSlope)

   Float64 MaxClearSpan; ///< Maximum clear span between supports
   Float64 MaxLeadingOverhang; ///< Maximum leading overhang (overhang nearest tractor)
   Float64 MaxGirderWeight; ///< Maximum girder weight
};
