///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/PierLine.h>
#include <CoordGeom/Path.h>

#include <array>

namespace WBFL
{
   namespace COGO
   {
      class BridgeFramingGeometry;

      /// @brief Defines a line representing a girder. The key geometry parameters are show in the figure below.
      /// @image html GirderLine.png
      class COORDGEOMCLASS GirderLine
      {
      private:
         friend BridgeFramingGeometry;

         GirderLine() = delete;
         GirderLine(
            std::weak_ptr<const BridgeFramingGeometry> bridge,
            IDType girderLineID,
            IDType layoutLineID,
            GirderLineType type,
            IDType startPierID,
            MeasurementType startPierMeasurementType,
            MeasurementLocation startPierMeasurementLocation,
            IDType endPierID,
            MeasurementType endPierMeasurementType,
            MeasurementLocation endPierMeasurementLocation
            );
         GirderLine(const GirderLine&) = default;
         GirderLine& operator=(const GirderLine& other) = delete;

      public:
         static std::shared_ptr<GirderLine> Create(const GirderLine& girderLine);

         /// @brief Creates a new girder line
         /// @param bridge The associated bridge geometry
         /// @param girderLineID The girder line identifier
         /// @param layoutLineID Identifier of the layout out line used to establish the girder line geometry.
         /// @param type The type of girder line
         /// @param startPierID The ID of the pier line where the girder line starts
         /// @param startPierMeasurementType Parameter defining how girder spacing is measured at the start pier
         /// @param startPierMeasurementLocation Parameter where girder spacing is measured at the start pier
         /// @param endPierID The ID of the pier line where the girder line ends
         /// @param endPierMeasurementType Parameter definition how girder spacing is measured at the end pier
         /// @param endPierMeasurementLocation Parameter defining where girder spacing is measured at the end pier
         /// @return 
         static std::shared_ptr<GirderLine> Create(
            std::weak_ptr<const BridgeFramingGeometry> bridge,
            IDType girderLineID,
            IDType layoutLineID,
            GirderLineType type,
            IDType startPierID,
            MeasurementType startPierMeasurementType,
            MeasurementLocation startPierMeasurementLocation,
            IDType endPierID,
            MeasurementType endPierMeasurementType,
            MeasurementLocation endPierMeasurementLocation
            );
         ~GirderLine() = default;

         /// @brief Returns the girder line identifier
         /// @return 
         IDType GetID() const;

         /// @brief Returns the identifier of the layout line used to define this girder line
         /// @return 
         IDType GetLayoutLineID() const;

         /// @brief Returns the PierLine object at the specified end of the girder line
         /// @param endType 
         /// @return 
         std::shared_ptr<const PierLine> GetPierLine(EndType endType) const;

         /// @brief Returns the end to end length of the girder line
         /// @return 
         Float64 GetGirderLength() const;

         /// @brief Returns the CL Bearing to CL Bearing length of the girder line
         /// @return 
         Float64 GetSpanLength() const;

         /// @brief Returns the length of the girder line measured between the bounding PierLine objects
         /// @return 
         Float64 GetLayoutLength() const;

         /// @brief Returns the point where the girder line intersects the pier line
         /// @param endType 
         /// @return 
         const WBFL::Geometry::Point2d& GetPierPoint(EndType endType) const;

         /// @brief Returns the point where the girder line intersects the centerline bearing line
         /// @param endType 
         /// @return 
         const WBFL::Geometry::Point2d& GetBearingPoint(EndType endType) const;

         /// @brief Returns the location of the end point of the girder line
         /// @param endType 
         /// @return 
         const WBFL::Geometry::Point2d& GetEndPoint(EndType endType) const;

         /// @brief Returns all of the girder points
         /// @return Tuple in the format (Start Pier Point, Start End Point, Start Bearing Point, End Bearing Point, End End Point, End Pier Point)
         std::tuple<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d, WBFL::Geometry::Point2d> GetEndPoints() const;

         /// @brief Returns the geometric path of the girder line
         /// @return 
         std::shared_ptr<const Path> GetPath() const;

         /// @brief Returns the direction of a line connecting the start and end Bearing Points
         /// @return 
         const Direction& GetDirection() const;

         /// @brief Returns the distance from the pier line to the centerline bearing point measured along the girder line
         /// @param endType 
         /// @return 
         Float64 GetBearingOffset(EndType endType) const;

         /// @brief Returns the distance from the centerline bearing point to the end point measured along the girder line
         /// @param endType 
         /// @return 
         Float64 GetEndDistance(EndType endType) const;

      private:
         IDType m_ID = INVALID_ID;
         IDType m_LayoutLineID = INVALID_ID; // why do we need this?
         std::array<IDType, 2> m_PierID{ INVALID_ID,INVALID_ID };
         GirderLineType m_Type = GirderLineType::Chord;
         std::array<MeasurementType, 2> m_MeasurementType{ MeasurementType::AlongItem,MeasurementType::AlongItem };
         std::array<MeasurementLocation, 2> m_MeasurementLocation{ MeasurementLocation::PierLine,MeasurementLocation::PierLine };

         std::weak_ptr<const BridgeFramingGeometry> m_pBridge;
         std::array<std::shared_ptr<const PierLine>, 2> m_PierLine;
         std::shared_ptr<Path> m_Path;
         std::array<WBFL::Geometry::Point2d, 2> m_PierPoint;
         std::array<WBFL::Geometry::Point2d, 2> m_BearingPoint;
         std::array<WBFL::Geometry::Point2d, 2> m_EndPoint;
         Float64 m_LayoutLength = -99999; // pier to pier length
         Float64 m_SpanLength = -99999; // cl-brg to cl-brg length
         Float64 m_GirderLength = -99999; // end to end length
         std::array<Float64, 2> m_BearingOffset{ -99999, -99999 }; // distance from cl-pier to cl-bearing along cl-girder
         std::array<Float64, 2> m_EndDistance{ -99999, -99999 }; // distance from cl-bearing to end of girder along cl-girder
         Direction m_Direction;

         std::shared_ptr<const BridgeFramingGeometry> GetBridge();
         void UpdateGeometry();
         void CreatePath();
         void LocatePoints();
         WBFL::Geometry::Line2d GetGirderSpacingLine(EndType endType);
      };
   };
};
