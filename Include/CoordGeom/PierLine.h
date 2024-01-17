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
#include <CoordGeom/Station.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/Angle.h>
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/ConnectionGeometry.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>

#include <array>

namespace WBFL
{
   namespace COGO
   {
      class BridgeFramingGeometry;

      /// @brief Defines a line representing a pier. The key geometric parameters are shown in the figure below.
      /// @image html PierLine.png
      class COORDGEOMCLASS PierLine
      {
      private:
         PierLine() = delete;
         PierLine(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType pierLineID, IDType alignmentID, const Station& station, const std::_tstring& strOrientation, Float64 length, Float64 offset, const ConnectionGeometry& back, const ConnectionGeometry& ahead);
         PierLine(const PierLine&) = default;
         PierLine& operator=(const PierLine& other) = delete;

         friend BridgeFramingGeometry; // friend so it can set the index
         void SetIndex(IndexType index) { m_Index = index; }

      public:
         static std::shared_ptr<PierLine> Create(const PierLine& other);

         /// @brief Creates a pier line
         /// @param bridge The associated bridge geometry
         /// @param pierLineID The pier line identifier 
         /// @param alignmentID Identifier of the alignment on which the pier line is located. The pier line can be located on a different alignment that the bridge alignment
         /// @param station The station on the alignment where the pier line is located.
         /// @param strOrientation The orientation of the pier line
         /// @param length The length of the pier line.
         /// @param offset The offset of the left end of the pier line from the alignment
         /// @param back The connection geometry on the back face side of the pier line
         /// @param ahead The connection geometry of the ahead face side of the pier line
         /// @return 
         static std::shared_ptr<PierLine> Create(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType pierLineID, IDType alignmentID, const Station& station, const std::_tstring& strOrientation, Float64 length, Float64 offset, const ConnectionGeometry& back, const ConnectionGeometry& ahead);
         ~PierLine() = default;

         /// @brief Returns the pier line identifier
         /// @return 
         IDType GetID() const;

         IndexType GetIndex() const;

         /// @brief Returns the identifier of the alignment used to locate the pier line
         /// @return 
         IDType GetAlignmentID() const;

         /// @brief Station on the alignment where the pier line is located
         /// @return 
         const Station& GetStation() const;

         /// @brief Direction of the pier line
         /// @return 
         const Direction& GetDirection() const;

         /// @brief Direction of a line normal to the pier line
         /// @return 
         const Direction& GetNormal() const;

         /// @brief Skew angle of the pier line
         /// @return 
         const Angle& GetSkewAngle() const;

         /// @brief Set the connection geometry
         /// @param pierFace 
         /// @param connectionGeometry 
         void SetConnectionGeometry(PierFaceType pierFace, const ConnectionGeometry& connectionGeometry);
         const ConnectionGeometry& GetConnectionGeometry(PierFaceType pierFace) const;

         /// @brief Returns the point where the pier line intersects the alignment
         /// @return 
         const WBFL::Geometry::Point2d& GetAlignmentPoint() const;

         /// @brief Returns the point where the pier line intersects the bridge line
         /// @return 
         const WBFL::Geometry::Point2d& GetBridgeLinePoint() const;

         /// @brief Returns the point at the left end of the pier line
         /// @return 
         const WBFL::Geometry::Point2d& GetLeftPoint() const;

         /// @brief Returns the point at the right end of the pier line
         /// @return 
         const WBFL::Geometry::Point2d& GetRightPoint() const;

         /// @brief Returns the a line representing the centerline of the pier
         /// @return 
         const WBFL::Geometry::Line2d& GetCenterLine() const;

         /// @brief Returns the offset to the CL bearing measured in the specified direction
         /// @param pierFace 
         /// @param direction 
         /// @return 
         Float64 GetBearingOffset(PierFaceType pierFace, const Direction& direction) const;

      private:
         std::weak_ptr<const BridgeFramingGeometry> m_pBridge;
         IDType m_ID = INVALID_ID;
         IndexType m_Index = INVALID_INDEX;
         IDType m_AlignmentID = INVALID_ID;
         Station m_Station;
         Direction m_Direction;
         Direction m_Normal;
         Angle m_SkewAngle;

         std::_tstring m_strOrientation;
         Float64 m_Length = 0;
         Float64 m_Offset = 0;

         std::array<ConnectionGeometry,2 > m_ConnectionGeometry;

         WBFL::Geometry::Point2d m_pntAlignment;
         WBFL::Geometry::Point2d m_pntBridgeLine;
         WBFL::Geometry::Point2d m_pntLeft;
         WBFL::Geometry::Point2d m_pntRight;

         WBFL::Geometry::Line2d m_Centerline;

         std::shared_ptr<const BridgeFramingGeometry> GetBridge() const;
         void UpdateGeometry();
      };
   };
};
