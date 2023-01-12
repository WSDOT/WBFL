///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Stability/StabilityExp.h>
#include <Stability/HaulingTensionStressLimit.h>
#include <array>

namespace WBFL
{
   namespace Stability
   {
      /// Criteria for hauling analysis
      class STABILITYCLASS HaulingCriteria
      {
      public:
         HaulingCriteria();

         Float64 MinFScr; ///< Minimum factor of safety against cracking
         Float64 MinFSf;  ///< Minimum factor of safety against failure

         Float64 AllowableCompression_GlobalStress; ///< Compression stress limit for global stress
         Float64 AllowableCompression_PeakStress; ///< Compression stress limit for peak stress
         Float64 CompressionCoefficient_GlobalStress; ///< Compression stress limit coefficient for global stress
         Float64 CompressionCoefficient_PeakStress; ///< Compression stress limit coefficient for peak stress

         std::shared_ptr<IHaulingTensionStressLimit> TensionStressLimit;

         Float64 MaxClearSpan; ///< Maximum clear span between supports
         Float64 MaxLeadingOverhang; ///< Maximum leading overhang (overhang nearest tractor)
         Float64 MaxGirderWeight; ///< Maximum girder weight
      };
   }
}