///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief Object that represents a segment in a SurfaceTemplate
      class COORDGEOMCLASS SurfaceTemplateSegment
      {
      public:
         /// @brief Constant defining how a template segment slope is measured
         enum class SlopeType
         {
            Horizontal, ///< measured as rise over 1
            FixedHorizontal, ///< measured as rise over 1 and is not changed by superelevations
            FixedVertical ///< measured as 1 over run and is not changed by superelevations
         };

         SurfaceTemplateSegment() = default;
         SurfaceTemplateSegment(Float64 width, Float64 slope, SlopeType slopeType);
         SurfaceTemplateSegment(const SurfaceTemplateSegment&) = default;
         ~SurfaceTemplateSegment() = default;
         SurfaceTemplateSegment& operator=(const SurfaceTemplateSegment&) = default;

         /// @brief SetParameters the SurfaceTemplateSegment
         /// @param width Width of the segment
         /// @param slope Slope of the segment
         /// @param slopeType Type of slope used to define the segment
         void SetParameters(Float64 width, Float64 slope, SlopeType slopeType);

         /// @brief Get all of the SurfaceTemplateSegment parameters in one call
         /// @return Returns a tuple of the form (Width,Slope,SlopeType)
         std::tuple<Float64,Float64,SurfaceTemplateSegment::SlopeType> GetParameters() const;

         /// @brief Set width of the template segment
         /// @param width 
         void SetWidth(Float64 width);

         /// @brief Returns the width of the template segment
         /// @return 
         Float64 GetWidth() const;

         /// @brief Sets the slope of the template segment
         /// @param slope 
         void SetSlope(Float64 slope);

         /// @brief Returns the width of the template segment
         /// @return 
         Float64 GetSlope() const;

         /// @brief Set the slope type
         /// @param slopeType 
         void SetSlopeType(SlopeType slopeType);

         /// @brief Returns the slope type
         /// @return 
         SlopeType GetSlopeType() const;

      private:
         Float64 m_Width{ 1.0 };
         Float64 m_Slope{ 0.02 };
         SlopeType m_SlopeType{ SlopeType::Horizontal };
      };
   };
};
