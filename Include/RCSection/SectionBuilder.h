///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <RCSection/RCSectionExp.h>
#include <RCSection/GeneralSection.h>
#include <Materials/StressStrainModel.h>

namespace WBFL
{
   namespace RCSection
   {
      /// Utility class to that creates simple reinforced concrete section models for analysis.
      class RCSCLASS SectionBuilder
      {
      public:
         SectionBuilder() = delete;
         SectionBuilder(const SectionBuilder&) = delete;
         ~SectionBuilder() = delete;

         SectionBuilder& operator=(const SectionBuilder&) = delete;

         /// Creates a GeneralSection  representing a rectangular reinforced concrete column.
         /// \image html SectionBuilder/RectangularColumn.gif
         /// It may look like the corner bars are counted twice (once with N1 and then again with N2), they are not. The section modeling takes the number of bars definition into account and compensates for the overlap.
         static std::shared_ptr<GeneralSection> RectangularColumn(
            Float64 H, ///< Height of cross section
            Float64 W, ///< Width of cross section
            Float64 cover, ///< Cover to center of reinforcement
            IndexType Nh, ///< Number of bars over the height of the section (N2)
            IndexType Nw, ///< Number of bars over the width of the section (N1)
            Float64 As, ///< Area of one reinforcing bar
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& concrete, ///< Constituative model for concrete
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& rebar, ///< Constituative model for reinforcing bars
            bool bModelBarsAsGenericShape ///< If true, bars are modeled as a WBFL::Geometry::GenericShape, otherwise they are modeled as a WBFL::Geometry::Circle
         );

         /// Creates a GeneralSection representing a circular reinforced concrete column.
         /// \image html SectionBuilder/CircularColumn.gif
         static std::shared_ptr<GeneralSection> CircularColumn(
            Float64 D, ///< Diameter of the column
            Float64 cover,  ///< Cover to center of reinforcement
            IndexType Nb, ///< Number of reinforcing bars
            Float64 As, ///< Area of one reinforcing bar
            Float64 startAngle, ///< Angle from the right end a horizontal line passing through the center of a circle where the first bar is located (rad)
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& concrete, ///< Constituative model for concrete
            const std::shared_ptr<const WBFL::Materials::StressStrainModel>& rebar, ///< Constituative model for reinforcing bars
            bool bModelBarsAsGenericShape ///< If true, bars are modeled as a WBFL::Geometry::GenericShape, otherwise they are modeled as a WBFL::Geometry::Circle
         );

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};
