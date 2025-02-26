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



namespace WBFL
{
    namespace EngTools
    {
        /// Criteria for bearing analysis
        struct BearingDesignCriteria
        {

            Float64 Gmin{ WBFL::Units::ConvertToSysUnits(0.080, WBFL::Units::Measure::KSI) }; ///< Minimum Elastomer Shear Modulus
            Float64 Gmax{ WBFL::Units::ConvertToSysUnits(0.175, WBFL::Units::Measure::KSI) }; ///< Maximum Elastomer Shear Modulus
            Float64 maxLLdef{ WBFL::Units::ConvertToSysUnits(0.125, WBFL::Units::Measure::Inch) }; ///< Maximum Live Load Deflection
            bool bHri{ false }; ///< Specific intermediate layer thickness requirement
            Float64 hri{ WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch) }; ///< Required Intermediate Elastomer Layer Thickness
            bool bHeight{ false }; ///< Minimum Total Bearing Height Requirement
            Float64 minHeight{ WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch) }; ///< Minimum Total Bearing Height
            bool bMinDistBrg2gBf{ false }; ///< Minimum distance from edge of bearing to edge of girder bottom flange requirement
            Float64 minDistBrg2gBf{ WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch) }; ///< Minimum distance from edge of bearing to edge of girder bottom flange
            bool bMaxDistBrg2gBf{ false }; ///< Maximum distance from edge of bearing to edge of girder bottom flange requirement
            Float64 maxDistBrg2gBf{ WBFL::Units::ConvertToSysUnits(9.0, WBFL::Units::Measure::Inch) }; ///< Maximum distance from edge of bearing to edge of girder bottom flange
            bool bDistBrg2gBf{ false }; ///< Distance from edge of bearing to edge of girder bottom flange requirement
            Float64 distBrg2gBf{ WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch) }; ///< Required distance from edge of bearing to edge of girder bottom flange
            bool bMaxTL{ false };///< Maximum vertical service load requirement
            Float64 maxTL{ WBFL::Units::ConvertToSysUnits(800.0, WBFL::Units::Measure::Kip) }; ///< Maximum vertical service load
        };
    }
}