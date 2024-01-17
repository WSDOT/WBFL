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
#include <Stability/OneEndSeatedResults.h>
#include <Stability/OneEndSeatedCriteria.h>

namespace WBFL
{
   namespace Stability
   {

      /// Results of a OneEndSeated check analysis
      class STABILITYCLASS OneEndSeatedCheckArtifact
      {
      public:
         /// Constructions a default artifact. 
         /// Init must be called to initialize the artifact with analysis results.
         OneEndSeatedCheckArtifact();

         /// Constructs a check artifact, initializing it with analysis results and check criteria.
         /// There is no need to call Init if this constructor is used.
         OneEndSeatedCheckArtifact(
            const OneEndSeatedResults& results, ///< OneEndSeated analysis results
            const OneEndSeatedCriteria& criteria ///< OneEndSeated check criteria
         );

         /// Initializes this object
         void Init(
            const OneEndSeatedResults& results, ///< OneEndSeated analysis results
            const OneEndSeatedCriteria& criteria ///< OneEndSeated check criteria
         );

         /// Returns the results of a OneEndSeated analysis
         const OneEndSeatedResults& GetOneEndSeatedResults() const;

         /// Returns the OneEndSeated check criteria
         const OneEndSeatedCriteria& GetCriteria() const;

         struct ControllingTensionCase
         {
            ImpactDirection impact; ///< Impact direction associated with the controlling case
            WindDirection wind; ///< Wind direction associated with the controlling case
            Corner corner; ///< Corner associated with the controlling case
            Float64 stress_limit; ///< Tension stress limit associated with the controlling case
            bool  bPassed; ///< Indicates if the controlling case passes the specification check
            Float64 CD; ///< Capacity-Demand ratio for the controlling case
         };

         /// Analyzes the section results and retrieves the controlling tension stress case
         /// \param sectionResult Analysis results to be evaluated
         ControllingTensionCase GetControllingTensionCase(const OneEndSeatedSectionResult& sectionResult) const;

         struct ControllingGlobalCompressionCase
         {
            ImpactDirection impact; ///< Impact direction associated with the controlling case
            Corner corner; ///< Corner associated with the controlling case
            Float64 stress_limit; ///< Tension stress limit associated with the controlling case
            bool bPassed; ///< Indicates if the controlling case passes the specification check
            Float64 CD; ///< Capacity-Demand ratio for the controlling case
         };

         /// Analyzes the section results and retrieves the controlling global compression case.
         /// \param[in] sectionResult Analysis results to be evaluated
         ControllingGlobalCompressionCase GetControllingGlobalCompressionCase(const OneEndSeatedSectionResult& sectionResult) const;

         using ControllingPeakCompressionCase = ControllingTensionCase;
         /// Analyzes the section results and retrieves the controlling peak compression case.
         /// \param sectionResult Analysis results to be evaluated
         ControllingPeakCompressionCase GetControllingPeakCompressionCase(const OneEndSeatedSectionResult& sectionResult) const;

         /// Returns true if the OneEndSeated check was successful
         bool Passed() const;

         /// Returns true if the cracking check passed
         bool PassedCrackingCheck() const;

         /// Returns true if the failure check passed
         bool PassedFailureCheck() const;

         /// Returns true if the rollover check passed
         bool PassedRolloverCheck() const;

         /// Returns true if the stress check without lateral load and tilt effects passed
         bool PassedDirectStressCheck() const;

         /// Returns true if the compression stress check without lateral load and tilt effects passed
         bool PassedDirectCompressionCheck() const;

         /// Returns true if the tension stress check without lateral load and tilt effects passed
         bool PassedDirectTensionCheck() const;

         /// Returns true if the stress check with lateral load and tilt effects passed
         bool PassedStressCheck() const;

         /// Returns true if the compression stress check with lateral load and tilt effects passed
         bool PassedCompressionCheck() const;

         /// Returns true if the tension stress check with lateral load and tilt effects passed
         bool PassedTensionCheck() const;

#if defined REBAR_FOR_DIRECT_TENSION
         /// Returns the tension stress limit
         /// \param[in] sectionResult Analysis results to be evaluated
         /// \param[in] impact Impact direction
         Float64 GetAllowableTension(const OneEndSeatedSectionResult& sectionResult, ImpactDirection impact) const;
#else
         /// Returns the tension stress limit
         /// \param[in] sectionResult Analysis results to be evaluated
         /// \param[in] impact Impact direction
         /// \param[in] wind Wind direction
         Float64 GetAllowableTension(const OneEndSeatedSectionResult& sectionResult, ImpactDirection impact, WindDirection wind) const;
#endif

         /// Returns the concrete strength required to satisfy the compression stress limit
         Float64 RequiredFcCompression() const;

         /// Returns the concrete strength required to satisfy the tension stress limit
         Float64 RequiredFcTension() const;
         Float64 RequiredFcTensionWithoutRebar() const;
         Float64 RequiredFcTensionWithRebar() const;

      private:
         OneEndSeatedResults m_Results;
         OneEndSeatedCriteria m_Criteria;
      };
   }
}