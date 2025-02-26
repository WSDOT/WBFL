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
            BearingCalculator(SpecType spec)
            {
                m_specification = spec;
            }
            BearingCalculator(const BearingCalculator&) = default;
            BearingCalculator(BearingCalculator&&) = default;
            BearingCalculator& operator=(const BearingCalculator&) = default;
            BearingCalculator& operator=(const BearingCalculator&&) = delete;
            ~BearingCalculator() = default;


            /// @return Analysis Method
            enum class AnalysisMethod
            {
                MethodA = 0,
                MethodB = 1,
            };

            /// @brief Set Specification
            void SetSpecification(SpecType spec);
            /// @brief Set Analysis Method
            void SetAnalysisMethod(AnalysisMethod method);
            /// @brief Set Design Criteria
            void SetDesignCriteria(const Criteria& criteria);
            /// @brief Set Maximum Alowable Bearing Stress
            /// @param sigma_max
            void SetMaximumAllowableStress(Float64 sigma_max);
            /// @brief Set Elastic Bulk Modulus
            /// @param k
            void SetElastomerBulkModulus(Float64 k);

            /// @return compute total bearing height
            Float64 ComputeBearingHeight(const Bearing& brg) const;

            /// @return analysis method
            AnalysisMethod GetAnalysisMethod() const;
            /// @return Maximum Allowable Stress
            Float64 GetMaximumAllowableStress() const;
            /// @return Absolute Minimimum Shim Thickness
            Float64 GetAbsoluteMinimumShimThickness() const;
            /// @return Minimum Elastomer Cover Thickness
            Float64 GetMinimumElastomerCoverThickness() const;
            /// @return Maximum Elastomer Cover Thickness
            Float64 GetMaximumElastomerCoverThickness(const Bearing&) const;
            /// @return Elastomer Bulk Modulus
            Float64 GetElastomerBulkModulus() const;
            /// @return Method A Elastomer Elastic Modulus
            Float64 GetElastomerElasticModulusMethodA(const Bearing&) const;
            /// @return Method B Elastomer Elastic Modulus 
            Float64 GetElastomerElasticModulusMethodB(const Bearing&) const;
            /// @return Method A Initial Dead Load Deflection
            Float64 GetInitialDeadLoadDeflectionMethodA(const Bearing&, const BearingLoads&) const;
            /// @return Method B Initial Dead Load Deflection 
            Float64 GetInitialDeadLoadDeflectionMethodB(const Bearing&, const BearingLoads&) const;
            /// @return Method A Instantaneous Live Load Deflection 
            Float64 GetInstantaneousLiveLoadDeflectionMethodA(const Bearing&, const BearingLoads&) const;
            /// @return Method B Instantaneous Live Load Deflection 
            Float64 GetInstantaneousLiveLoadDeflectionMethodB(const Bearing&, const BearingLoads&) const;
            /// @return Total Load Stress
            Float64 GetTotalLoadStress(const Bearing&, const BearingLoads&) const;
            /// @return Live load Stress
            Float64 GetLiveLoadStress(const Bearing&, const BearingLoads&) const;
            /// @return Multiplier for max stress
            Float64 GetSigmaMultiplier(const BearingLoads&) const;
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
            Float64 GetElasticModulusCoefficient() const;
            /// @return Primary Intermediate Calculation for parameter A 
            Float64 GetPrimaryIntermediateCalculationA(const Bearing&) const;
            /// @return Secondary Intermediate Calculation for parameter A 
            Float64 GetSecondaryIntermediateCalculationA(const Bearing&) const;
            /// @return Primary Intermediate Calculation for parameter B
            Float64 GetPrimaryIntermediateCalculationB(const Bearing&) const;
            /// @return Secondary Intermediate Calculation for parameter B 
            Float64 GetSecondaryIntermediateCalculationB(const Bearing&) const;
            /// @return Compressibility Index
            Float64 GetCompressibilityIndex(const Bearing&) const;
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
            Float64 GetMaximumStress(const Bearing&) const;
            /// @return Minimum allowable area 
            Float64 GetMinimumAllowableArea(const Bearing&, const BearingLoads&) const;
            /// @return Minimum Allowable length 
            Float64 GetMinimumAllowableLength(const Bearing&, const BearingLoads&) const;
            /// @return Minimum Allowable width 
            Float64 GetMinimumAllowableWidth(const Bearing&, const BearingLoads&) const;
            /// @return Maximum allowable intermediate elastomer layer thickness
            Float64 GetMaximumAllowableIntermediateLayerThickness(const Bearing&, const BearingLoads&) const;
            /// @return Minimum allowable shape factor
            Float64 GetMinimumAllowableShapeFactor(const Bearing&, const BearingLoads&) const;
            /// @return Maximum allowable shape factor
            Float64 GetMaximumAllowableShapeFactor(const Bearing&, const BearingLoads&) const;
            /// @return Minimum allowable number of elastomer layers for shear deformation
            Float64 GetMinimumAllowableNumLayersShearDeformation(const Bearing&, const BearingLoads&) const;
            /// @return Calculation for minimum allowable number of elastomer layers for X-axis rotation
            Float64 GetNumLayersRotationXCalc(const Bearing&, const BearingLoads&) const;
            /// @return Calculation for minimum allowable number of elastomer layers for Y-axis rotation
            Float64 GetMinimumAllowableNumLayersRotationX(const Bearing&, const BearingLoads&) const;
            /// @return Minimum allowable number of elastomer layers for Y-axis rotation
            Float64 GetNumLayersRotationYCalc(const Bearing&, const BearingLoads&) const;
            /// @return Minimum allowable number of elastomer layers for X-axis rotation
            Float64 GetMinimumAllowableNumLayersRotationY(const Bearing&, const BearingLoads&) const;
            /// @return Maximum allowable number of elastomer layers for stability in the X direction 
            Float64 GetMaximumAllowableNumLayersStabilityX(const Bearing&, const BearingLoads&) const;
            /// @return Maximum allowable number of elastomer layers for stability in the Y direction 
            Float64 GetMaximumAllowableNumLayersStabilityY(const Bearing&, const BearingLoads&) const;
            /// @return Check applicapility for checking X direction stability due to total load 
            bool CheckApplicabilityTotalStressStabilityX(const Bearing&, const BearingLoads&) const;
            /// @return Check applicapility for checking Y direction stability due to total load
            bool CheckApplicabilityTotalStressStabilityY(const Bearing&, const BearingLoads&) const;
            /// @return Allowable Total Load Stress for Stability in the X direction
            Float64 GetAllowableTotalLoadStressStabilityX(const Bearing&, const BearingLoads&) const;
            /// @return Allowable Total Load Stress for Stability in the Y direction 
            Float64 GetAllowableTotalLoadStressStabilityY(const Bearing&, const BearingLoads&) const;
            /// @return Minimum allowable steel shim thickness for service limit state
            Float64 GetMinimumAllowableSteelShimThicknessService(const Bearing&, const BearingLoads&) const;
            /// @return Minimum allowable steel shim thickness for fatigue limit state 
            Float64 GetMinimumAllowableSteelShimThicknessFatigue(const Bearing&, const BearingLoads&) const;
            /// @return Restraint system applicability calculation 
            Float64 RestraintSystemCalc(const Bearing&, const BearingLoads&) const;
            /// @return horizontal force
            Float64 GetHorizontalForce(const Bearing&, const BearingLoads&) const;
            /// @return Minimum Allowable Shear Modulus


            /// @return Check for the minimum required bearing pad area
            bool MinimumAreaCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the minimum required bearing pad length
            bool MinimumLengthCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the minimum required bearing pad width
            bool MinimumWidthCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowed bearing pad stress
            bool MaximumStressCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for maximum allowable intermediate elastomer layer thickness
            bool MaximumIntermediateLayerThicknessCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the minimum required shape factor
            bool MinimumShapeFactorCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowed shape factor
            bool MaximumShapeFactorCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the required number of elastomer layers for shear deformation resistance 
            bool MinimumNumLayersShearDeformationCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the minimum required number of elastomer layers for X-axis rotation resistance 
            bool MinimumNumLayersRotationXCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the minimum allowable number of elastomer layers for Y-axis rotation resistance
            bool MinimumNumLayersRotationYCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable number of elastomer layers for stability in the X direction
            bool MaximumNumLayersStabilityXCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowed number of elastomer layers for stability in the Y direction
            bool MaximumNumLayersStabilityYCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the absolute minimum required steel shim thickness
            bool MinimumSteelShimThicknessAbsoluteCheck(const Bearing&) const;
            /// @return Check for the minimum allowable elastomer cover thickness
            bool MinimumElastomerCoverThicknessCheck(const Bearing&) const;
            /// @return Check for the maximum allowable elastomer cover thickness
            bool MaximumElastomerCoverThicknessCheck(const Bearing&) const;
            /// @return Check for the minimum steel shim thickness for the service limit state 
            bool MinimumSteelShimThicknessServiceCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the minimum steel shim thickness for the fatigue limit state
            bool MinimumSteelShimThicknessFatigueCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable compressive strain
            bool MaximumCompressiveStrainCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for static rotational primary shear strain
            bool StaticRotationalPrimaryShearStrainCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable shear deformation
            bool ShearDeformationCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain in the primary direction due to static axial load 
            bool StaticAxialPrimaryShearStrainCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain in the secondary direction due to static axial load 
            bool StaticAxialSecondaryShearStrainCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain combination sum in the primary direction 
            bool PrimaryShearStrainComboSumCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable shear strain combination sum in the secondary direction
            bool SecondaryShearStrainComboSumCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for stability in the X direction 
            bool StabilityXDirectionCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for stability in the Y direction 
            bool StabilityYDirectionCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check if a restraint system is required for stability
            bool RestraintSystemRequirementCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check if a restraint system is required for horizontal force
            bool HorizontalForceCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the maximum allowable hydrostatic stress
            bool HydrostaticStressCheck(const Bearing&, const BearingLoads&) const;
            /// @return Check for the minmimum allowable shear modulus
            bool MinimumAllowableShearModulusCheck(const Bearing&, const Criteria&) const;
            /// @return Check for the maximum allowable shear modulus
            bool MaximumAllowableShearModulusCheck(const Bearing&, const Criteria&) const;
            /// @return Required intermediate elastomer layer thickness check
            bool RequiredIntermediateElastomerThicknessCheck(const Bearing&, const Criteria&) const;
            /// @return Minimum Total Bearing Height Check
            bool MinimumTotalBearingHeightCheck(const Bearing&, const Criteria&) const;
            /// @return Minimum bearing edge to girder bottom flange distance Check
            bool MinimumBearingEdgeToBottomFlangeEdgeDistCheck(const Bearing&, const Criteria&, Float64) const;
            /// @return Maximum bearing edge to girder bottom flange distance Check
            bool MaximumBearingEdgeToBottomFlangeEdgeDistCheck(const Bearing&, const Criteria&, Float64) const;
            /// @return Required bearing edge to girder bottom flange distance Check
            bool RequiredBearingEdgeToBottomFlangeEdgeDistCheck(const Bearing&, const Criteria&, Float64) const;
            /// @return Maximum live load deflection check
            bool MaximumLiveLoadDeflectionCheck(const Bearing&, const BearingLoads&, const Criteria&) const;
            /// @return Maximum total vertical service load check
            bool MaximumTotalLoadCheck(const BearingLoads&, const Criteria&) const;
            



        private:
           AnalysisMethod m_method{AnalysisMethod::MethodA};///< design method
           Float64 m_maximum_allowable_stress{ WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI) };///< max allowable stress
           Float64 m_elastomer_bulk_modulus{ WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI) };///< elastomer bulk modulus
           SpecType m_specification{WBFL::LRFD::BDSManager::Edition::LastEdition};///< AASHTO BDS spec
           Criteria m_criteria;///< Bearing design criteria
           Float64 m_Ecoeff{ 4.8 };///< coefficient used in elastic modulus calculation
           Float64 m_girder_edge_dist{ 10.0 };///< girder edge distance from bearing center line
        };
    }; // EngTools
}; // WBFL