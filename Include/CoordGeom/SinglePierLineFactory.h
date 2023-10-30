///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/PierLineFactory.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A factory that creates a single pier line
      class COORDGEOMCLASS SinglePierLineFactory : public PierLineFactory
      {
      public:
         SinglePierLineFactory() = default;
         /// @brief Constructs and initializes the factor
         /// @param pierID The pier line identifier
         /// @param alignmentID The identifier of an alignment for the station
         /// @param station Station where the pier line is located
         /// @param strDirection The pier line direction
         /// @param length The length of the pier line
         /// @param offset The offset of the left end of the pier from the alignment, measured along the pier line
         /// @param back The connection geometry on the back face of the pier
         /// @param ahead The connection geometry on the ahead fact of the pier
         SinglePierLineFactory(IDType pierID, IDType alignmentID, const Station& station, const std::_tstring& strDirection, Float64 length, Float64 offset, const ConnectionGeometry& back, const ConnectionGeometry& ahead);
         SinglePierLineFactory(const SinglePierLineFactory&) = default;
         ~SinglePierLineFactory() = default;
         SinglePierLineFactory& operator=(const SinglePierLineFactory&) = default;

         /// @brief The pier line identifier
         /// @param pierLineID 
         void SetPierLineID(IDType pierLineID);
         IDType GetPierLineID() const;

         /// @brief The identifier of the associated alignment
         /// @param alignmentID 
         void SetAlignmentID(IDType alignmentID);
         IDType GetAlignmentID() const;

         /// @brief The station on the associated alignment where the pier line is located
         /// @param station 
         void SetStation(const Station& station);
         const Station& GetStation() const;

         /// @brief The direction of the pier line
         /// @param strDirection 
         void SetDirection(const std::_tstring& strDirection);
         const std::_tstring& GetDirection() const;

         /// @brief The length of the pier line
         /// @param length 
         void SetLength(Float64 length);
         Float64 GetLength() const;

         /// @{
         /// @brief Offset from the alignment to the left end of the pier line
         void SetOffset(Float64 offset);
         Float64 GetOffset() const;
         /// @}

         /// @brief Get connection geometry associated with the pier line
         /// @param face 
         /// @param connection 
         void SetConnectionGeometry(PierFaceType face, const ConnectionGeometry& connection);
         const ConnectionGeometry& GetConnectionGeometry(PierFaceType face) const;

         virtual std::vector<std::shared_ptr<PierLine>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         IDType m_ID = INVALID_ID; // The pier line ID
         IDType m_AlignmentID = INVALID_ID; // The alignment where the pier line is located relative to (does not need to be the bridge alignment)
         Station m_Station; // Station on the alignment where the pier line (possibly projected) intersects the alignment
         std::_tstring m_strDirection; // Direction of the pier line
         Float64 m_Length; // Length of the pier line
         Float64 m_Offset; // Offset from the alignment to the left end of the pier line
         std::array<ConnectionGeometry,2> m_Connections; // The pier connection geometry (use PierFaceType enum to access the array)
      };
   };
};
