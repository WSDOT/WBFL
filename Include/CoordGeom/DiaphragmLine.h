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
#include <CoordGeom/CoordGeomTypes.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/Line2d.h>

#include <array>
#include <map>

namespace WBFL
{
   namespace COGO
   {
      class BridgeFramingGeometry;

      /// @brief Defines a transverse line for diaphragm geometry. 
      /// A diaphragm line runs continuously between left and right girder lines. The girder lines can be a subset of the girder lines in a span.
      /// 
      /// Diaphragm geometry is generated from the diaphragm line. A diaphragm is defined by a start and end point on two adjacent girder lines.
      /// A diaphragm can be along the direction of the diaphragm line, or it can be staggered. Staggered diaphragms are pass through a point
      /// on the diaphragm line at the mid-point between the adjacent girder lines. A staggered diaphragm passes though this point and is perpendicular
      /// to the left girder line.
      /// 
      /// @image html DiaphragmLine.png
      class COORDGEOMCLASS DiaphragmLine
      {
      private:
         friend BridgeFramingGeometry;

         DiaphragmLine() = delete;
         DiaphragmLine(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType id, IDType leftGirderLineID, IDType rightGirderLineID, bool bIsStaggered, const WBFL::Geometry::Line2d& line);
         DiaphragmLine(const DiaphragmLine&) = default;
         DiaphragmLine& operator=(const DiaphragmLine& other) = delete;

      public:
         static std::shared_ptr<DiaphragmLine> Create(const DiaphragmLine& diaphragmLine);

         /// @brief Used by a BridgeFramingGeometry object to create a diaphragm line
         /// @param bridge The BridgeFramingGeometry object with which this diaphragm line is associated
         /// @param id ID of the diaphragm line
         /// @param leftGirderLineID ID of the left girder line
         /// @param rightGirderLineID ID of the right girder line
         /// @param bIsStaggered If true, the diaphragms are staggered within their respective bays.
         /// @param line A line object used to defined the diaphragm line location.
         /// @return 
         static std::shared_ptr<DiaphragmLine> Create(std::weak_ptr<const BridgeFramingGeometry> bridge, IDType id, IDType leftGirderLineID, IDType rightGirderLineID, bool bIsStaggered, const WBFL::Geometry::Line2d& line);

         ~DiaphragmLine() = default;

         /// @brief Returns the diaphragm line identifier
         /// @return 
         IDType GetID() const;

         /// @brief Returns the length of the diaphragm within a bay
         /// @param girderLineID The ID of the girder line on the left side of the bay
         /// @return 
         Float64 Length(IDType girderLineID) const;

         /// @brief Returns the end points of a diaphragm within a bay
         /// @param girderLineID The ID of the girder line on the left side of the bay
         /// @param endType The end of the diaphragm for the requested point
         /// @return The point where the diaphragm intersects the girder line
         const WBFL::Geometry::Point2d& GetPoint(IDType girderLineID, EndType endType) const;

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         std::weak_ptr<const BridgeFramingGeometry> m_pBridge;
         IDType m_ID = INVALID_ID;
         std::array<IDType, 2> m_GirderLineID = { INVALID_ID,INVALID_ID }; // id's of the girder lines where the diaphragm starts and ends
         bool m_bIsStaggered = false;
         WBFL::Geometry::Line2d m_Line;

         std::map<IDType, std::array<WBFL::Geometry::Point2d, 2>> m_EndPoints; // intersection of diaphragm lines between girder lines
         // key is left hand girder ID

         std::array<WBFL::Geometry::Point2d, 2> m_Point; // intersection of diaphragm line and start and end girder line

         std::shared_ptr<const BridgeFramingGeometry> GetBridge() const;
         void UpdateGeometry();
         void LocatePoints();
      };
   };
};
