///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2023  Washington State Department of Transportation
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
            /// @brief Set Maximum Alowable Bearing Stress
            /// @param sigma_max
            void SetMaximumAllowableStress(Float64 sigma_max);
            /// @brief Set Minimum Shim Thickness
            /// @param tmin
            void SetAbsoluteMinimumShimThickness(Float64 tmin);
            /// @brief Set Elastic Bulk Modulus
            /// @param k
            void SetElastomerBulkModulus(Float64 k);


            /// @return Maximum Allowable Stress
            Float64 GetMaximumAllowableStress() const;
            /// @return Absolute Minimimum Shim Thickness
            Float64 GetAbsoluteMinimumShimThickness() const;
            /// @return Elastomer Bulk Modulus
            Float64 GetElastomerBulkModulus() const;
            /// @return Method A Concrete Elastic Modulus
            Float64 GetConcreteElasticModulusMethodA(Bearing&) const;
            /// @return Method B Concrete Elastic Modulus 
            Float64 GetConcreteElasticModulusMethodB(Bearing&) const;
            /// @return Method A Initial Dead Load Deflection
            Float64 GetInitialDeadLoadDeflectionMethodA(Bearing&, BearingLoads&) const;
            /// @return Method B Initial Dead Load Deflection 
            Float64 GetInitialDeadLoadDeflectionMethodB(Bearing&, BearingLoads&) const;
            /// @return Method A Instantaneous Live Load Deflection 
            Float64 GetInstantaneousLiveLoadDeflectionMethodA(Bearing&, BearingLoads&) const;
            /// @return Method B Instantaneous Live Load Deflection 
            Float64 GetInstantaneousLiveLoadDeflectionMethodB(Bearing&, BearingLoads&) const;
            /// @return Total Load Stress
            Float64 GetTotalLoadStress(Bearing&, BearingLoads&) const;
            /// @return Live load Stress
            Float64 GetLiveLoadStress(Bearing&, BearingLoads&) const;
            /// @return Multiplier for max stress
            Float64 GetSigmaMultiplier(BearingLoads&) const;
            /// @return Multiplier for Nlay
            Float64 GetNlayMultiplier(Bearing&) const;
            /// @return Primary shear strain due to static shear displacement
            Float64 GetStaticDisplacementPrimaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Primary shear strain due to cyclic shear displacement
            Float64 GetCyclicDisplacementPrimaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Primary shear strain due to static axial load
            Float64 GetStaticAxialPrimaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Primary shear strain due to cyclic axial load 
            Float64 GetCyclicAxialPrimaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Primary shear strain due to static rotation
            Float64 GetStaticRotationalPrimaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Primary shear strain due to cyclic rotation 
            Float64 GetCyclicRotationalPrimaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Primary shear strain combination sum 
            Float64 GetPrimaryShearStrainComboSum(Bearing&, BearingLoads&) const;
            /// @return Secondary shear strain due to static shear displacement 
            Float64 GetStaticDisplacementSecondaryShearStrain() const;
            /// @return Secondary shear strain due to cyclic shear displacement 
            Float64 GetCyclicDisplacementSecondaryShearStrain() const;
            /// @return Secondary shear strain due to static axial load 
            Float64 GetStaticAxialSecondaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Secondary shear strain due to cyclic axial load 
            Float64 GetCyclicAxialSecondaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Secondary shear strain due to static rotation 
            Float64 GetStaticRotationalSecondaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Secondary shear strain due to cyclic rotation 
            Float64 GetCyclicRotationalSecondaryShearStrain(Bearing&, BearingLoads&) const;
            /// @return Secondary shear strain combination sum 
            Float64 GetSecondaryShearStrainComboSum(Bearing&, BearingLoads&) const;
            /// @return Static stress 
            Float64 GetStaticStress(Bearing&, BearingLoads&) const;
            /// @return Cyclic stress 
            Float64 GetCyclicStress(Bearing&, BearingLoads&) const;
            /// @return Total stress 
            Float64 GetTotalStress(Bearing&, BearingLoads&) const;
            /// @return Primary Intermediate Calculation for parameter A 
            Float64 GetPrimaryIntermediateCalculationA(Bearing&) const;
            /// @return Secondary Intermediate Calculation for parameter A 
            Float64 GetSecondaryIntermediateCalculationA(Bearing&) const;
            /// @return Primary Intermediate Calculation for parameter B
            Float64 GetPrimaryIntermediateCalculationB(Bearing&) const;
            /// @return Secondary Intermediate Calculation for parameter B 
            Float64 GetSecondaryIntermediateCalculationB(Bearing&) const;
            /// @return Compressibility Index 
            Float64 GetCompressibilityIndex(Bearing&) const;
            /// @return da1 parameter 
            Float64 Getda1(Bearing&) const;
            /// @return da2 parameter
            Float64 Getda2(Bearing&) const;
            /// @return da3 parameter
            Float64 Getda3(Bearing&) const;
            /// @return Coefficient for primary shear strain due to axial load 
            Float64 GetPrimaryShearStrainAxialCoefficient(Bearing&) const;
            /// @return Coefficient for secondary shear strain due to axial load 
            Float64 GetSecondaryShearStrainAxialCoefficient(Bearing&) const;
            /// @return Coefficient for primary strain due to rotation 
            Float64 GetPrimaryShearStrainRotationCoefficient(Bearing&) const;
            /// @return Coefficient for secondary shear strain due to rotation 
            Float64 GetSecondaryShearStrainRotationCoefficient(Bearing&) const;
            /// @return Coefficient for peak hydrostatic stress 
            Float64 GetPeakHydrostaticStressCoefficient(Bearing&) const;
            /// @return Total axial strain 
            Float64 GetTotalAxialStrain(Bearing&, BearingLoads&) const;
            /// @return Alpha coefficent 
            Float64 GetAlphaCoefficient(Bearing&, BearingLoads&) const;
            /// @return Ca 
            Float64 GetCaCoefficient(Bearing&, BearingLoads&) const;
            /// @return Hydrostatic stress 
            Float64 GetHydrostaticStress(Bearing&, BearingLoads&) const;
            /// @return Maximum stress 
            Float64 GetMaximumStress(Bearing&) const;
            /// @return Minimum allowable area 
            Float64 GetMinimumAllowableArea(Bearing&, BearingLoads&) const;
            /// @return Minimum Allowable length 
            Float64 GetMinimumAllowableLength(Bearing&, BearingLoads&) const;
            /// @return Minimum Allowable width 
            Float64 GetMinimumAllowableWidth(Bearing&, BearingLoads&) const;
            /// @return Maximum allowable intermediate elastomer layer thickness
            Float64 GetMaximumAllowableIntermediateLayerThickness(Bearing&, BearingLoads&) const;
            /// @return Minimum allowable shape factor
            Float64 GetMinimumAllowableShapeFactor(Bearing&, BearingLoads&) const;
            /// @return Maximum allowable shape factor
            Float64 GetMaximumAllowableShapeFactor(Bearing&, BearingLoads&) const;
            /// @return Minimum allowable number of elastomer layers for shear deformation
            Float64 GetMinimumAllowableNumLayersShearDeformation(Bearing&, BearingLoads&) const;
            /// @return Calculation for minimum allowable number of elastomer layers for X-axis rotation
            Float64 GetNumLayersRotationXCalc(Bearing&, BearingLoads&) const;
            /// @return Calculation for minimum allowable number of elastomer layers for Y-axis rotation
            Float64 GetMinimumAllowableNumLayersRotationX(Bearing&, BearingLoads&) const;
            /// @return Minimum allowable number of elastomer layers for Y-axis rotation
            Float64 GetNumLayersRotationYCalc(Bearing&, BearingLoads&) const;
            /// @return Minimum allowable number of elastomer layers for X-axis rotation
            Float64 GetMinimumAllowableNumLayersRotationY(Bearing&, BearingLoads&) const;
            /// @return Maximum allowable number of elastomer layers for stability in the X direction 
            Float64 GetMaximumAllowableNumLayersStabilityX(Bearing&, BearingLoads&) const;
            /// @return Maximum allowable number of elastomer layers for stability in the Y direction 
            Float64 GetMaximumAllowableNumLayersStabilityY(Bearing&, BearingLoads&) const;
            /// @return Check applicapility for checking X direction stability due to total load 
            bool CheckApplicabilityTotalStressStabilityX(Bearing&, BearingLoads&) const;
            /// @return Check applicapility for checking Y direction stability due to total load
            bool CheckApplicabilityTotalStressStabilityY(Bearing&, BearingLoads&) const;
            /// @return Allowable Total Load Stress for Stability in the X direction
            Float64 GetAllowableTotalLoadStressStabilityX(Bearing&, BearingLoads&) const;
            /// @return Allowable Total Load Stress for Stability in the Y direction 
            Float64 GetAllowableTotalLoadStressStabilityY(Bearing&, BearingLoads&) const;
            /// @return Minimum allowable steel shim thickness for service limit state
            Float64 GetMinimumAllowableSteelShimThicknessService(Bearing&, BearingLoads&) const;
            /// @return Minimum allowable steel shim thickness for fatigue limit state 
            Float64 GetMinimumAllowableSteelShimThicknessFatigue(Bearing&, BearingLoads&) const;
            /// @return Restraint system applicability calculation 
            Float64 RestraintSystemCalc(Bearing&, BearingLoads&) const;
            /// @return horizontal force
            Float64 GetHorizontalForce(Bearing&, BearingLoads&) const;

            /// @return Check for the minimum required bearing pad area
            bool MinimumAreaCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the minimum required bearing pad length
            bool MinimumLengthCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the minimum required bearing pad width
            bool MinimumWidthCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowed bearing pad stress
            bool MaximumStressCheck(Bearing&, BearingLoads&) const;
            /// @return Check for maximum allowable intermediate elastomer layer thickness
            bool MaximumIntermediateLayerThicknessCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the minimum required shape factor
            bool MinimumShapeFactorCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowed shape factor
            bool MaximumShapeFactorCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the required number of elastomer layers for shear deformation resistance 
            bool MinimumNumLayersShearDeformationCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the minimum required number of elastomer layers for X-axis rotation resistance 
            bool MinimumNumLayersRotationXCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the minimum allowable number of elastomer layers for Y-axis rotation resistance
            bool MinimumNumLayersRotationYCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable number of elastomer layers for stability in the X direction
            bool MaximumNumLayersStabilityXCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowed number of elastomer layers for stability in the Y direction 
            bool MaximumNumLayersStabilityYCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the absolute minimum required steel shim thickness
            bool MinimumSteelShimThicknessAbsoluteCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the minimum steel shim thickness for the service limit state 
            bool MinimumSteelShimThicknessServiceCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the minimum steel shim thickness for the fatigue limit state 
            bool MinimumSteelShimThicknessFatigueCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable compressive strain
            bool MaximumCompressiveStrainCheck(Bearing&, BearingLoads&) const;
            /// @return Check for static rotational primary shear strain
            bool StaticRotationalPrimaryShearStrainCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable shear deformation
            bool ShearDeformationCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain in the primary direction due to static axial load 
            bool StaticAxialPrimaryShearStrainCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain in the secondary direction due to static axial load 
            bool StaticAxialSecondaryShearStrainCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain combination sum in the primary direction 
            bool PrimaryShearStrainComboSumCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain combination sum in the secondary direction
            bool SecondaryShearStrainComboSumCheck(Bearing&, BearingLoads&) const;
            /// @return Check for stability in the X direction 
            bool StabilityXDirectionCheck(Bearing&, BearingLoads&) const;
            /// @return Check for stability in the Y direction 
            bool StabilityYDirectionCheck(Bearing&, BearingLoads&) const;
            /// @return Check if a restraint system is required for stability
            bool RestraintSystemRequirementCheck(Bearing&, BearingLoads&) const;
            /// @return Check if a restraint system is required for horizontal force
            bool HorizontalForceCheck(Bearing&, BearingLoads&) const;
            /// @return Check for the maximum allowable hydrostatic stress
            bool HydrostaticStressCheck(Bearing&, BearingLoads&) const;


        private:
           Float64 m_maximum_allowable_stress{ WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI) };///< max allowable stress
           Float64 m_absolute_minimum_shim_thickness{ WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch) };///< absolute minimum shim thickness
           Float64 m_elastomer_bulk_modulus{ WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI) };///< elastomer bulk modulus


            

        };
    }; // EngTools
}; // WBFL