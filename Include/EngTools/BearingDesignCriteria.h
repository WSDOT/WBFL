///////////////////////////////////////////////////////////////////////
// Stability
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
#include "Bearing.h"
#include "BearingLoads.h"
#include <LRFD\BDSManager.h>
#include <LibraryFw\LibraryEntry.h>


namespace WBFL
{

    typedef LRFD::BDSManager::Edition Spec;

    namespace EngTools
    {

        /// @return Analysis Method
        enum class BearingAnalysisMethod
        {
            MethodA = 0,
            MethodB = 1,
        };
        
        /// Criteria for bearing analysis

        struct ENGTOOLSCLASS BearingProjectCriteria
        {
            BearingProjectCriteria() = default;
            BearingProjectCriteria(const BearingProjectCriteria&) = default;
            ~BearingProjectCriteria() = default;

            BearingAnalysisMethod AnalysisMethod = BearingAnalysisMethod::MethodB;
            Float64 MinimumElastomerShearModulus = WBFL::Units::ConvertToSysUnits(0.080, WBFL::Units::Measure::KSI); ///< See LRFD 14.7.5.2
            Float64 MaximumElastomerShearModulus = WBFL::Units::ConvertToSysUnits(0.175, WBFL::Units::Measure::KSI); ///< See LRFD 14.7.5.2

            bool bRequiredIntermediateElastomerThickness = false;
            Float64 RequiredIntermediateElastomerThickness = WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch);
            bool bMinimumTotalBearingHeight = false;
            Float64 MinimumTotalBearingHeight = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch);
            bool bMinimumBearingEdgeToGirderEdgeDistance = false;
            Float64 MinimumBearingEdgeToGirderEdgeDistance = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch);
            bool bMaximumBearingEdgeToGirderEdgeDistance = false;
            Float64 MaximumBearingEdgeToGirderEdgeDistance = WBFL::Units::ConvertToSysUnits(9.0, WBFL::Units::Measure::Inch);
            bool bRequiredBearingEdgeToGirderEdgeDistance = false;
            Float64 RequiredBearingEdgeToGirderEdgeDistance = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch);
            Float64 MaximumLiveLoadDeflection = WBFL::Units::ConvertToSysUnits(0.125, WBFL::Units::Measure::Inch);
            bool bMaximumTotalLoad = false;
            Float64 MaximumTotalLoad = WBFL::Units::ConvertToSysUnits(800.0, WBFL::Units::Measure::Kip);

        };


        class ENGTOOLSCLASS BearingDesignCriteria : public BearingProjectCriteria
        {
        public:

            BearingDesignCriteria();

            BearingDesignCriteria(const Bearing& bearing, const BearingLoads& loads, const WBFL::LRFD::BDSManager::Edition& spec);

            BearingDesignCriteria(const Bearing& bearing, const BearingLoads& loads, 
                const WBFL::LRFD::BDSManager::Edition& spec, const BearingProjectCriteria& base);

            ~BearingDesignCriteria();

            const Bearing& GetBearing() const;

            const BearingLoads& GetBearingLoads() const;

            const WBFL::LRFD::BDSManager::Edition& GetSpecification() const;


            Float64 MaximumAllowableStressMethodA = WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI);
            Float64 MaximumStaticAxialShearStrain = 3.0;
            Float64 MaximumCombinedShearStrain = 5.0;
            Float64 maxLLdef{ WBFL::Units::ConvertToSysUnits(0.125, WBFL::Units::Measure::Inch) }; ///< Maximum Live Load Deflection



            Float64 GetSigmaMultiplier() const;
            Float64 GetMaximumAllowableHydrostaticStress() const;
            Float64 GetPrimaryIntermediateCalculationA() const;
            Float64 GetSecondaryIntermediateCalculationA() const;
            Float64 GetPrimaryIntermediateCalculationB() const;
            Float64 GetSecondaryIntermediateCalculationB() const;
            bool CheckApplicabilityTotalStressStabilityX() const;
            bool CheckApplicabilityTotalStressStabilityY() const;
            /// @return Absolute Minimimum Shim Thickness
            Float64 GetAbsoluteMinimumShimThickness() const;
            /// @return Minimum allowable steel shim thickness for service limit state
            Float64 GetMinimumAllowableSteelShimThicknessService() const;
            /// @return Minimum allowable steel shim thickness for fatigue limit state 
            Float64 GetMinimumAllowableSteelShimThicknessFatigue() const;
            /// @return Minimum Elastomer Cover Thickness
            Float64 GetMinimumElastomerCoverThickness() const;
            /// @return Maximum Elastomer Cover Thickness
            Float64 GetMaximumElastomerCoverThickness() const;
            /// @return Allowable Total Load Stress for Stability in the X direction
            Float64 GetAllowableTotalLoadStressStabilityX() const;
            /// @return Allowable Total Load Stress for Stability in the Y direction 
            Float64 GetAllowableTotalLoadStressStabilityY() const;
            /// @return Minimum allowable area 
            Float64 GetMinimumAllowableArea() const;
            /// @return Minimum Allowable length 
            Float64 GetMinimumAllowableLength() const;
            /// @return Minimum Allowable width 
            Float64 GetMinimumAllowableWidth() const;
            /// @return Maximum allowable intermediate elastomer layer thickness
            Float64 GetMaximumAllowableIntermediateLayerThickness() const;
            /// @return Minimum allowable shape factor
            Float64 GetMinimumAllowableShapeFactor() const;
            /// @return Maximum allowable shape factor
            Float64 GetMaximumAllowableShapeFactor() const;
            /// @return Minimum allowable number of elastomer layers for shear deformation
            Float64 GetMinimumAllowableNumLayersShearDeformation() const;
            /// @return Calculation for minimum allowable number of elastomer layers for X-axis rotation
            Float64 GetNumLayersRotationXCalc() const;
            /// @return Calculation for minimum allowable number of elastomer layers for Y-axis rotation
            Float64 GetMinimumAllowableNumLayersRotationX() const;
            /// @return Minimum allowable number of elastomer layers for Y-axis rotation
            Float64 GetNumLayersRotationYCalc() const;
            /// @return Minimum allowable number of elastomer layers for X-axis rotation
            Float64 GetMinimumAllowableNumLayersRotationY() const;
            /// @return Maximum allowable number of elastomer layers for stability in the X direction 
            Float64 GetMaximumAllowableNumLayersStabilityX() const;
            /// @return Maximum allowable number of elastomer layers for stability in the Y direction 
            Float64 GetMaximumAllowableNumLayersStabilityY() const;

        private:

            Bearing m_bearing;
            BearingLoads m_loads;
            WBFL::LRFD::BDSManager::Edition m_spec;

        };
    }
}





