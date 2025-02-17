///////////////////////////////////////////////////////////////////////
// Stability
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <Stability/StabilityProblem.h>
#include <Stability/LiftingResults.h>
#include <Stability/LiftingCheckArtifact.h>
#include <Reporter\Chapter.h>

namespace WBFL
{
   namespace Stability
   {
      ///  Generates reports for lifting stability analysis
      class STABILITYCLASS LiftingStabilityReporter
      {
      public:
         LiftingStabilityReporter();

         /// Builds the specification check chapter
         void BuildSpecCheckChapter(
            const IGirder* pGirder, ///< The girder that was analyzed
            const ILiftingStabilityProblem* pStabilityProblem, ///< The stability problem parameters
            const LiftingCheckArtifact* pArtifact, ///< The specification checking artifact
            rptChapter* pChapter, ///< The report chapter to populate
            const WBFL::Units::IndirectMeasure* pDisplayUnits, ///< The display units
            LPCTSTR lpszLocColumnLabel = nullptr, ///< Label for the Location column for report tables
            Float64 offset = 0 ///< Offset to be applied to analysis point locations
         );

         /// Builds the analysis details chapter
         void BuildDetailsChapter(
            const IGirder* pGirder, ///< The girder that was analyzed
            const ILiftingStabilityProblem* pStabilityProblem, ///< The stability problem parameters
            const LiftingResults* pResults, ///< The results of the stability analysis
            rptChapter* pChapter,  ///< The report chapter to populate
            const WBFL::Units::IndirectMeasure* pDisplayUnits, ///< The display units
            LPCTSTR lpszLocColumnLabel = nullptr, ///< Label for the Location column for report tables
            Float64 offset = 0, ///< Offset to be applied to analysis point locations
            bool bReportTensileForceDetails = true ///< If true, the details for computing the tension force required to be carried by auxiliary reinforcement are reported
         );
      };
   }
}