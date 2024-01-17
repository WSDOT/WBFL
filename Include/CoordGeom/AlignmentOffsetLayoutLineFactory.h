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
      /// @brief A factory that creates layout lines that are parallel to an alignment
      class COORDGEOMCLASS AlignmentOffsetLayoutLineFactory : public LayoutLineFactory
      {
      public:
         AlignmentOffsetLayoutLineFactory() = default;
         /// @brief Constructs and initializes the factory
         /// @param alignmentID ID of the alignment from which the layout lines are derived
         /// @param firstLineID ID of the first layout line
         /// @param idIncrement ID increment
         /// @param nLayoutLines Number of layout lines to generate
         /// @param offset Offset of the first layout line from the alignment
         /// @param offsetIncrement Layout line offset increment
         AlignmentOffsetLayoutLineFactory(IDType alignmentID, IDType firstLineID, IDType idIncrement, IndexType nLayoutLines, Float64 offset, Float64 offsetIncrement);
         AlignmentOffsetLayoutLineFactory(const AlignmentOffsetLayoutLineFactory&) = default;
         ~AlignmentOffsetLayoutLineFactory() = default;
         AlignmentOffsetLayoutLineFactory& operator=(const AlignmentOffsetLayoutLineFactory&) = default;

         /// @brief Initializes the factory with new parameters
         /// @param alignmentID ID of the alignment from which the layout lines are derived
         /// @param firstLineID ID of the first layout line
         /// @param idIncrement ID increment
         /// @param nLayoutLines Number of layout lines to generate
         /// @param offset Offset of the first layout line from the alignment
         /// @param offsetIncrement Layout line offset increment
         void SetLayoutLineParameters(IDType alignmentID,IDType firstLineID, IDType idIncrement, IndexType nLayoutLines,Float64 offset,Float64 offsetIncrement);

         /// @brief Returns the layout parameters
         /// @return Tuple if the form of (Alignment ID,First Layout Line ID, Layout Line Increment, Number of Layout Lines to Generate, Offset of the First Layout Line, Offset Increment)
         std::tuple<IDType, IDType, IDType, IndexType,Float64,Float64> GetLayoutLineParameters() const;

         /// @brief ID of the alignment from which the layout lines are created
         /// @param id 
         void SetAlignmentID(IDType id);
         IDType GetAlignmentID() const;

         /// @brief Identifier of the first layout line created
         /// @param id 
         void SetLayoutLineID(IDType id);
         IDType GetLayoutLineID() const;

         /// @brief The amount to increment the layout line identifier
         /// @param idIncrement 
         void SetLayoutLineIDIncrement(IDType idIncrement);
         IDType GetLayoutLineIDIncrement() const;

         /// @brief The number of layout lines to create
         /// @param nLayoutLines 
         void SetLayoutLineCount(IndexType nLayoutLines);
         IndexType GetLayoutLineCount() const;

         /// @brief Offset from the alignment to the first layout line
         /// @param offset 
         void SetOffset(Float64 offset);
         Float64 GetOffset() const;

         /// @brief Incremental offset between layout lines
         /// @param increment 
         void SetOffsetIncrement(Float64 increment);
         Float64 GetOffsetIncrement() const;

         virtual std::vector<std::pair<IDType, std::shared_ptr<Path>>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         IDType m_AlignmentID = INVALID_ID;
         IDType m_ID = INVALID_ID;
         IDType m_IDInc = 1;
         IndexType m_nLayoutLines = 1;
         Float64 m_Offset = 0.0;
         Float64 m_OffsetInc = 0.0;
      };
   };
};
