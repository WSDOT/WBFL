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
#include <Units/AutoSystem.h>
#include <Units\Convert.h>

namespace WBFL
{
    namespace EngTools
    {
        ///Bearing Properties Per AASHTO LRFD Method A & Method B\n\n
        ///See 'Bearing_Design_Method_A_All_Pass.pdf',\n
        ///'Bearing_Design_Method_A_All_Fail.pdf',\n
        ///'Bearing_Design_Method_A_Etc.pdf',\n
        ///'Bearing_Design_Method_B_All_Pass.pdf',\n
        ///'Bearing_Design_Method_B_All_Fail.pdf',\n
        ///& 'Bearing_Design_Method_B_Etc.pdf':
        
        class ENGTOOLSCLASS Bearing
        {
        public:


            /// @brief Sets the bearing pad length
            /// @param l
            void SetLength(Float64 l);
            /// @brief Sets the bearing pad width
            /// @param w
            void SetWidth(Float64 w);
            /// @brief Sets the minimum shear modulus
            /// @param Gmin
            void SetShearModulusMinimum(Float64 Gmin);
            /// @brief Sets the maximum shear modulus
            /// @param Gmax
            void SetShearModulusMaximum(Float64 Gmax);
            /// @brief Sets the intermediate layer thickness
            /// @param layer
            void SetIntermediateLayerThickness(Float64 layer);
            /// @brief Sets the steel cover thickness
            /// @param cover
            void SetCoverThickness(Float64 cover);
            /// @brief Sets the steel shim thickness
            /// @param shim
            void SetSteelShimThickness(Float64 shim);
            /// @brief Sets the steel shim yield strength
            /// @param fy
            void SetYieldStrength(Float64 fy);
            /// @brief Sets the steel shim fatigue threshold
            /// @param fth
            void SetFatigueThreshold(Float64 fth);
            /// @brief Sets the number of intermediate elastomer layers
            /// @param n
            void SetNumIntLayers(IndexType n);
            /// @brief Sets the density of the steel shims
            /// @param ps
            void SetDensitySteel(Float64 ps);
            /// @brief Sets the density of the elastomer
            /// @param pe
            void SetDensityElastomer(Float64 pe);



            
            /// @return bearing pad length
            Float64 GetLength() const;
            /// @return bearing pad width 
            Float64 GetWidth() const;
            /// @return minimum elastormeric shear modulus
            Float64 GetShearModulusMinimum() const;
            /// @return maximum elastomeric shear modulus
            Float64 GetShearModulusMaximum() const;
            /// @return intermediate elastomer layer thickness
            Float64 GetIntermediateLayerThickness() const;
            /// @return bearing pad steel cover thickness
            Float64 GetCoverThickness() const;
            /// @return intermediate steel shim thickness
            Float64 GetSteelShimThickness() const;
            /// @return steel shim yield strength
            Float64 GetYieldStrength() const;
            /// @return steel shim fatigue strength
            Float64 GetFatigueThreshold() const;
            /// @return number of intermediate elastomer layers
            IndexType GetNumIntLayers() const;
            /// @return density of the steel shims
            Float64 GetDensitySteel() const;
            /// @return density of the elastomer
            Float64 GetDensityElastomer() const;
            /// @return bearing pad area
            Float64 GetArea() const;
            /// @return total elastomer thickness
            Float64 GetTotalElastomerThickness() const;
            /// @return total steel shim thickness
            Float64 GetTotalSteelShimThickness() const;
            /// @return total steel shims thickness
            IndexType GetTotalSteelShims() const;
            /// @return bearing pad shape factor
            Float64 GetShapeFactor() const;




        private:
            Float64 m_length{ WBFL::Units::ConvertToSysUnits(11, WBFL::Units::Measure::Inch) }; ///< length
            Float64 m_width{ WBFL::Units::ConvertToSysUnits(27, WBFL::Units::Measure::Inch) };///< width
            Float64 m_shear_modulus_min{ WBFL::Units::ConvertToSysUnits(140, WBFL::Units::Measure::PSI) };///< minimum shear modulus
            Float64 m_shear_modulus_max{ WBFL::Units::ConvertToSysUnits(190, WBFL::Units::Measure::PSI) };///< maximum shear modulus
            Float64 m_intermediate_layer_thickness{ WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch) };///< intermediate elastomer layer thickness
            Float64 m_cover_thickness{ WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch) };///< steel cover thickness
            Float64 m_steel_shim_thickness{ WBFL::Units::ConvertToSysUnits(0.0747, WBFL::Units::Measure::Inch) };///< steel shim thickness
            Float64 m_yield_strength{ WBFL::Units::ConvertToSysUnits(36, WBFL::Units::Measure::KSI) };///< steel yield strength
            Float64 m_fatigue_threshold{ WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::KSI) };///< steel fatigue threshold
            IndexType m_number_intermediate_layers{ 4 }; ///< number of intermediate elastomer layers
            Float64 m_density_steel{ WBFL::Units::ConvertToSysUnits(490.0, WBFL::Units::Measure::LbfPerFeet3) }; ///< steel density
            Float64 m_density_elastomer{ WBFL::Units::ConvertToSysUnits(74.93, WBFL::Units::Measure::LbfPerFeet3) }; ///< elastomer density

        };
    }; // EngTools
}; // WBFL
