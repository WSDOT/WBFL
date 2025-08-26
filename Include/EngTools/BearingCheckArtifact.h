///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#include <EngTools\EngToolsExp.h>
#include <EngTools\Bearing.h>
#include <EngTools\BearingResults.h>
#include <EngTools\BearingDesignCriteria.h>
#include "BearingLoads.h"



namespace WBFL
{

    namespace EngTools
    {
        
        class ENGTOOLSCLASS BearingCheckArtifact
        {
        public:

            BearingCheckArtifact() = delete;

            BearingCheckArtifact(
                const Bearing& bearing,
                const BearingLoads& loads,
                const BearingResults& results,
                const BearingDesignCriteria& criteria);

            ~BearingCheckArtifact();

            const Bearing& GetBearing() const;

            const BearingLoads& GetBearingLoads() const;

            const BearingResults& GetBearingResults() const;

            const BearingDesignCriteria& GetBearingDesignCriteria() const;

            /// @return Check for the minimum required bearing pad area
            bool MinimumAreaCheck() const;
            /// @return Check for the minimum required bearing pad length
            bool MinimumLengthCheck() const;
            /// @return Check for the minimum required bearing pad width
            bool MinimumWidthCheck() const;
            /// @return Check for the maximum allowed bearing pad stress
            bool MaximumStressCheck() const;
            /// @return Check for maximum allowable intermediate elastomer layer thickness
            bool MaximumIntermediateLayerThicknessCheck() const;
            /// @return Check for the minimum required shape factor
            bool MinimumShapeFactorCheck() const;
            /// @return Check for the maximum allowed shape factor
            bool MaximumShapeFactorCheck() const;
            /// @return Check for the required number of elastomer layers for shear deformation resistance 
            bool MinimumNumLayersShearDeformationCheck() const;
            /// @return Check for the minimum required number of elastomer layers for X-axis rotation resistance 
            bool MinimumNumLayersRotationXCheck() const;
            /// @return Check for the minimum allowable number of elastomer layers for Y-axis rotation resistance
            bool MinimumNumLayersRotationYCheck() const;
            /// @return Check for the maximum allowable number of elastomer layers for stability in the X direction
            bool MaximumNumLayersStabilityXCheck() const;
            /// @return Check for the maximum allowed number of elastomer layers for stability in the Y direction
            bool MaximumNumLayersStabilityYCheck() const;
            /// @return Check for the absolute minimum required steel shim thickness
            bool MinimumSteelShimThicknessAbsoluteCheck() const;
            /// @return Check for the minimum allowable elastomer cover thickness
            bool MinimumElastomerCoverThicknessCheck() const;
            /// @return Check for the maximum allowable elastomer cover thickness
            bool MaximumElastomerCoverThicknessCheck() const;
            /// @return Check for the minimum steel shim thickness for the service limit state 
            bool MinimumSteelShimThicknessServiceCheck() const;
            /// @return Check for the minimum steel shim thickness for the fatigue limit state
            bool MinimumSteelShimThicknessFatigueCheck() const;
            /// @return Check for the maximum allowable compressive strain
            bool MaximumCompressiveStrainCheck() const;
            /// @return Check for the maximum allowable shear deformation
            bool ShearDeformationCheck() const;
            /// @return Check for the maximum allowable shear strain in the primary direction due to static axial load 
            bool StaticAxialPrimaryShearStrainCheck() const;
            /// @return Check for the maximum allowable shear strain in the secondary direction due to static axial load 
            bool StaticAxialSecondaryShearStrainCheck() const;
            /// @return Check for the maximum allowable shear strain combination sum in the primary direction 
            bool PrimaryShearStrainComboSumCheck() const;
            /// @return Check for the maximum allowable shear strain combination sum in the secondary direction
            bool SecondaryShearStrainComboSumCheck() const;
            /// @return Check for stability in the X direction 
            bool StabilityXDirectionCheck() const;
            /// @return Check for stability in the Y direction 
            bool StabilityYDirectionCheck() const;
            /// @return Check if a restraint system is required for stability
            bool RestraintSystemRequirementCheck() const;
            /// @return Check if a restraint system is required for horizontal force
            bool HorizontalForceCheck() const;
            /// @return Check for the maximum allowable hydrostatic stress
            bool HydrostaticStressCheck() const;
            /// @return Check for the minmimum allowable shear modulus
            bool MinimumAllowableShearModulusCheck() const;
            /// @return Check for the maximum allowable shear modulus (method A)
            bool MaximumAllowableShearModulusCheck() const;
            /// @return Required intermediate elastomer layer thickness check
            bool RequiredIntermediateElastomerThicknessCheck() const;
            /// @return Minimum Total Bearing Height Check
            bool MinimumTotalBearingHeightCheck() const;
            /// @return Minimum bearing edge to girder bottom flange distance Check
            bool MinimumBearingEdgeToBottomFlangeEdgeDistCheck() const;
            /// @return Maximum bearing edge to girder bottom flange distance Check
            bool MaximumBearingEdgeToBottomFlangeEdgeDistCheck() const;
            /// @return Required bearing edge to girder bottom flange distance Check
            bool RequiredBearingEdgeToBottomFlangeEdgeDistCheck() const;
            /// @return Maximum live load deflection (method A) check
            bool MaximumLiveLoadDeflectionMethodACheck() const;
            /// @return Maximum live load deflection (method B) check
            bool MaximumLiveLoadDeflectionMethodBCheck() const;
            /// @return Maximum total vertical service load check
            bool MaximumTotalLoadCheck() const;



        private:

            Bearing m_bearing;
            BearingLoads m_loads;
            BearingResults m_results;
            BearingDesignCriteria m_criteria;

        };
    }; // EngTools
}; // WBFL
