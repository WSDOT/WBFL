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
#include <EngTools\BearingLoads.h>
#include <EngTools\BearingDesignCriteria.h>
#include <LRFD/BDSManager.h>
#include "BearingCheckArtifact.h"


namespace WBFL
{
    namespace EngTools
    {
        ///Bearing Design Calculations Per AASHTO LRFD Method A & Method B\n\n
        ///See 'Bearing_Design_Method_A_All_Pass.pdf',\n
        ///'Bearing_Design_Method_A_All_Fail.pdf',\n
        ///'Bearing_Design_Method_A_Etc.pdf',\n
        ///'Bearing_Design_Method_B_All_Pass.pdf',\n
        ///'Bearing_Design_Method_B_All_Fail.pdf',\n
        ///& 'Bearing_Design_Method_B_Etc.pdf':
 
        class ENGTOOLSCLASS BearingCalculator
        {

        public:
            typedef WBFL::LRFD::BDSManager::Edition SpecType;
            typedef WBFL::EngTools::BearingDesignCriteria Criteria;

            BearingCalculator() = default;
            BearingCalculator(const BearingCalculator&) = default;
            BearingCalculator(BearingCalculator&&) = default;
            BearingCalculator& operator=(const BearingCalculator&) = default;
            BearingCalculator& operator=(const BearingCalculator&&) = delete;
            ~BearingCalculator() = default;


            /// @return compute total bearing height
            Float64 ComputeBearingHeight(const Bearing& brg) const;
            /// @return Method A Elastomer Elastic Modulus
            Float64 GetElastomerElasticModulusMethodA(const Bearing& brg, const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return Method B Elastomer Elastic Modulus 
            Float64 GetElastomerElasticModulusMethodB(const Bearing& brg, const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return Method A Initial Dead Load Deflection
            Float64 GetInitialDeadLoadDeflectionMethodA(const Bearing& brg, const BearingLoads& loads, const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return Method B Initial Dead Load Deflection 
            Float64 GetInitialDeadLoadDeflectionMethodB(const Bearing& brg, const BearingLoads& loads, const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return Method A Instantaneous Live Load Deflection 
            Float64 GetInstantaneousLiveLoadDeflectionMethodA(const Bearing& brg, const BearingLoads& loads, const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return Method B Instantaneous Live Load Deflection 
            Float64 GetInstantaneousLiveLoadDeflectionMethodB(const Bearing& brg, const BearingLoads& loads,
                const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return Total Load Stress
            Float64 GetTotalLoadStress(const Bearing&, const BearingLoads&) const;
            /// @return Live load Stress
            Float64 GetLiveLoadStress(const Bearing&, const BearingLoads&) const;
            /// @return Multiplier for Nlay
            Float64 GetNlayMultiplier(const Bearing&) const;
            /// @return Primary shear strain due to static shear displacement
            Float64 GetStaticDisplacementPrimaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Primary shear strain due to cyclic shear displacement
            Float64 GetCyclicDisplacementPrimaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Primary shear strain due to static axial load
            Float64 GetStaticAxialPrimaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Primary shear strain due to cyclic axial load 
            Float64 GetCyclicAxialPrimaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Primary shear strain due to static rotation
            Float64 GetStaticRotationalPrimaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Primary shear strain due to cyclic rotation 
            Float64 GetCyclicRotationalPrimaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Primary shear strain combination sum 
            Float64 GetPrimaryShearStrainComboSum(const Bearing&, const BearingLoads&) const;
            /// @return Secondary shear strain due to static shear displacement 
            Float64 GetStaticDisplacementSecondaryShearStrain() const;
            /// @return Secondary shear strain due to cyclic shear displacement 
            Float64 GetCyclicDisplacementSecondaryShearStrain() const;
            /// @return Secondary shear strain due to static axial load 
            Float64 GetStaticAxialSecondaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Secondary shear strain due to cyclic axial load 
            Float64 GetCyclicAxialSecondaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Secondary shear strain due to static rotation 
            Float64 GetStaticRotationalSecondaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Secondary shear strain due to cyclic rotation 
            Float64 GetCyclicRotationalSecondaryShearStrain(const Bearing&, const BearingLoads&) const;
            /// @return Secondary shear strain combination sum 
            Float64 GetSecondaryShearStrainComboSum(const Bearing&, const BearingLoads&) const;
            /// @return Static stress 
            Float64 GetStaticStress(const Bearing&, const BearingLoads&) const;
            /// @return Cyclic stress 
            Float64 GetCyclicStress(const Bearing&, const BearingLoads&) const;
            /// @return Total stress 
            Float64 GetTotalStress(const Bearing&, const BearingLoads&) const;
            /// @return elastic modulus coefficient
            Float64 GetElasticModulusCoefficient(const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return da1 parameter 
            Float64 Getda1(const Bearing&) const;
            /// @return da2 parameter
            Float64 Getda2(const Bearing&) const;
            /// @return da3 parameter
            Float64 Getda3(const Bearing&) const;
            /// @return Coefficient for primary shear strain due to axial load 
            Float64 GetPrimaryShearStrainAxialCoefficient(const Bearing&) const;
            /// @return Coefficient for secondary shear strain due to axial load 
            Float64 GetSecondaryShearStrainAxialCoefficient(const Bearing&) const;
            /// @return Coefficient for primary strain due to rotation 
            Float64 GetPrimaryShearStrainRotationCoefficient(const Bearing&) const;
            /// @return Coefficient for secondary shear strain due to rotation 
            Float64 GetSecondaryShearStrainRotationCoefficient(const Bearing&) const;
            /// @return Coefficient for peak hydrostatic stress 
            Float64 GetPeakHydrostaticStressCoefficient(const Bearing&) const;
            /// @return Total axial strain 
            Float64 GetTotalAxialStrain(const Bearing&, const BearingLoads&) const;
            /// @return Alpha coefficent 
            Float64 GetAlphaCoefficient(const Bearing&, const BearingLoads&) const;
            /// @return Ca 
            Float64 GetCaCoefficient(const Bearing&, const BearingLoads&) const;
            /// @return Hydrostatic stress 
            Float64 GetHydrostaticStress(const Bearing&, const BearingLoads&) const;
            /// @return Maximum stress 
            /// @return Restraint system applicability calculation 
            Float64 RestraintSystemCDRatio(const Bearing&, const BearingLoads&, const WBFL::LRFD::BDSManager::Edition& spec) const;
            /// @return horizontal force
            Float64 GetHorizontalForce(const Bearing&, const BearingLoads&) const;
            /// @return Minimum Allowable Shear Modulus

            BearingResults AnalyzeBearing(const Bearing& bearing, const BearingLoads& loads, const WBFL::LRFD::BDSManager::Edition& spec) const;
            
            BearingCheckArtifact CheckBearing(const Bearing& bearing, const BearingLoads& loads, 
                const WBFL::LRFD::BDSManager::Edition& spec, const BearingDesignCriteria& criteria) const;

        };
    }; // EngTools
}; // WBFL