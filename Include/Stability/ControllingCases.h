///////////////////////////////////////////////////////////////////////
// Stability
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

#pragma once

#include <Stability/StabilityExp.h>
#include <Stability/StabilityTypes.h>

namespace WBFL
{
   namespace Stability
   {

      struct STABILITYCLASS ControllingTensionCase
      {
         ImpactDirection impact; ///< Impact direction associated with the controlling case
         WindDirection wind; ///< Wind direction associated with the controlling case
         Corner corner; ///< Corner associated with the controlling case
         Float64 stress_limit; ///< Tension stress limit associated with the controlling case
         bool  bPassed; ///< Indicates if the controlling case passes the specification check
         Float64 CD; ///< Capacity-Demand ratio for the controlling case
      };


      struct STABILITYCLASS ControllingGlobalCompressionCase
      {
         ImpactDirection impact; ///< Impact direction associated with the controlling case
         Corner corner; ///< Corner associated with the controlling case
         Float64 stress_limit; ///< Tension stress limit associated with the controlling case
         bool bPassed; ///< Indicates if the controlling case passes the specification check
         Float64 CD; ///< Capacity-Demand ratio for the controlling case
      };


      using ControllingPeakCompressionCase = ControllingTensionCase;

   }
}