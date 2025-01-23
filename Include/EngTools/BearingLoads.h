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
#include <Units/AutoSystem.h>
#include <Units\Convert.h>

namespace WBFL
{
    namespace EngTools
    {
        ///Bearing Loads Per AASHTO LRFD Method A & Method B\n\n
        ///See 'Bearing_Design_Method_A_All_Pass.pdf',\n
        ///'Bearing_Design_Method_A_All_Fail.pdf',\n
        ///'Bearing_Design_Method_A_Etc.pdf',\n
        ///'Bearing_Design_Method_B_All_Pass.pdf',\n
        ///'Bearing_Design_Method_B_All_Fail.pdf',\n
        ///& 'Bearing_Design_Method_B_Etc.pdf':
 
        class ENGTOOLSCLASS BearingLoads
        {
        public:

            /// @return bearing pad fixidity in the X direction
            enum class FixedTranslationX
            {
                Yes,
                No,
            };
            /// @return bearing pad fixidity in the Y direction
            enum class FixedTranslationY
            {
                Yes,
                No,
            };

            /// @brief Sets the bearing dead load
            /// @param DL
            void SetDeadLoad(Float64 DL);
            /// @brief Sets the bearing live load
            /// @param LL
            void SetLiveLoad(Float64 LL);
            /// @brief Sets the bearing X-axis rotation
            /// @param rx
            void SetRotationX(Float64 rx);
            /// @brief Sets the bearing Y-axis rotation
            /// @param ry
            void SetRotationY(Float64 ry);
            /// @brief Sets the bearing static rotation
            /// @param rst
            void SetStaticRotation(Float64 rst);
            /// @brief Sets the bearing cyclic rotation
            /// @param rcy
            void SetCyclicRotation(Float64 rcy);
            /// @brief Sets the bearing shear deformation
            /// @param shear_def
            void SetShearDeformation(Float64 shear_def);
            /// @brief Sets the fixity for X-Translation
            /// @param fx
            void SetFixedTranslationX(FixedTranslationX fx);
            /// @brief Sets the fixity for Y-Translation
            /// @param fy
            void SetFixedTranslationY(FixedTranslationY fy);


            /// @return dead weight of bearing pad
            Float64 GetDeadLoad() const;
            /// @return applied live load
            Float64 GetLiveLoad() const;
            /// @return total load 
            Float64 GetTotalLoad() const;
            /// @return bearing pad X-axis rotation
            Float64 GetRotationX() const;
            /// @return bearing pad Y-axis rotation
            Float64 GetRotationY() const;
            /// @return bearing pad static rotation
            Float64 GetStaticRotation() const;
            /// @return bearing pad cyclic rotation 
            Float64 GetCyclicRotation() const;
            /// @return bearing pad shear deformation 
            Float64 GetShearDeformation() const;
            /// @return if translation is fixed in the X direction
            FixedTranslationX GetFixedTranslationX() const;
            /// @return if translation is fixed in the Y direction
            FixedTranslationY GetFixedTranslationY() const;
            /// @return bearing pad X Direction effective K factor 
            Float64 GetEffectiveKFactorX() const;
            /// @return bearing pad Y Direction effective K factor
            Float64 GetEffectiveKFactorY() const;


        private:

            Float64 m_dead_load{ WBFL::Units::ConvertToSysUnits(86.0, WBFL::Units::Measure::Kip) }; ///< dead load
            Float64 m_live_load{ WBFL::Units::ConvertToSysUnits(47.0, WBFL::Units::Measure::Kip) }; ///< live load
            Float64 m_shear_deformation{ WBFL::Units::ConvertToSysUnits(0.47, WBFL::Units::Measure::Inch) }; ///< shear deformation
            Float64 m_rotation_x{ 0.014 };///< x-axis rotation
            Float64 m_rotation_y{ 0.005 };///< y-axis rotation
            Float64 m_static_rotation{ 0.008 };///< static rotation
            Float64 m_cyclic_rotation{ 0.006 };///< cyclic rotation
            FixedTranslationX m_fixed_translation_x{ FixedTranslationX::Yes };///< fixed X translation
            FixedTranslationY m_fixed_translation_y{ FixedTranslationY::No };///< fixed Y translation

        };
    }; // EngTools
}; // WBFL
