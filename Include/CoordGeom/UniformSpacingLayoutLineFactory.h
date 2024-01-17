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
#include <CoordGeom/LayoutLineFactory.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A factory that creates uniformly spaced layout lines
      class COORDGEOMCLASS UniformSpacingLayoutLineFactory : public LayoutLineFactory
      {
      public:
         UniformSpacingLayoutLineFactory() = default;
         UniformSpacingLayoutLineFactory(const UniformSpacingLayoutLineFactory&) = default;
         ~UniformSpacingLayoutLineFactory() = default;
         UniformSpacingLayoutLineFactory& operator=(const UniformSpacingLayoutLineFactory&) = default;

         /// @brief Identifier of an alignment on which to locate the layout lines
         /// @param alignmentID 
         void SetAlignmentID(IDType alignmentID);
         IDType GetAlignmentID() const;

         /// @brief Identifier of the pier line that intersects the start of the layout line
         /// @param pierID 
         void SetStartPierLineID(IDType pierID);
         IDType GetStartPierLineID() const;

         /// @brief Identifier of the pier line that intersects the end of the layout line
         /// @param pierID 
         void SetEndPierLineID(IDType pierID);
         IDType GetEndPierLineID() const;

         /// @brief The pier line identifier increment
         /// @param idIncrement 
         void SetPierLineIDIncrement(IDType idIncrement);
         IDType GetPierLineIDIncrement() const;

         /// @brief Identifier of the first layout line
         /// @param id 
         void SetLayoutLineID(IDType id);
         IDType GetLayoutLineID() const;

         /// @brief The layout line identifier increment
         /// @param idIncrement 
         void SetLayoutLineIDIncrement(IDType idIncrement);
         IDType GetLayoutLineIDIncrement() const;

         /// @brief Offset from the alignment for the start spacing
         /// @param offset 
         void SetStartSpacingOffset(Float64 offset);
         Float64 GetStartSpacingOffset() const;

         /// @brief Offset from the alignment for the end spacing
         /// @param offset 
         void SetEndSpacingOffset(Float64 offset);
         Float64 GetEndSpacingOffset() const;

         /// @brief Spacing at the start of the layout
         /// @param spacing 
         void SetStartSpacing(const std::vector<Float64>& spacing);
         const std::vector<Float64>& GetStartSpacing() const;

         /// @brief Spacing at the end of the layout
         /// @param spacing 
         void SetEndSpacing(const std::vector<Float64>& spacing);
         const std::vector<Float64>& GetEndSpacing() const;

         virtual std::vector<std::pair<IDType, std::shared_ptr<Path>>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         IDType m_AlignmentID = INVALID_ID;
         IDType m_StartPierLineID = INVALID_ID;
         IDType m_EndPierLineID = INVALID_ID;
         IDType m_PierLineIDInc = 1;
         Float64 m_StartOffset = 0;
         Float64 m_EndOffset = 0;
         std::vector<Float64> m_StartSpacing;
         std::vector<Float64> m_EndSpacing;
         IDType m_LayoutLineID = INVALID_ID; // ID of first layout line
         IDType m_LayoutLineIDInc = 1; // Layout line ID increment
      };
   };
};
