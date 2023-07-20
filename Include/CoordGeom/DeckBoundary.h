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
#include <CoordGeom/Path.h>

#include <GeomModel/Primitives.h>

#include <array>

namespace WBFL
{
   namespace COGO
   {
      class BridgeFramingGeometry;
      
      /// @brief An object that defines the plan view boundary of a deck.
      /// @image html DeckBoundary.png
      class COORDGEOMCLASS DeckBoundary
      {
      private:
         friend BridgeFramingGeometry;

         DeckBoundary() = delete;
         DeckBoundary(std::weak_ptr<const BridgeFramingGeometry> bridge,
            const std::array<IDType, 2>& transverseEdgeIDs,
            const std::array<TransverseEdgeType, 2>& transverseEdgeTypes,
            const std::array<IDType, 2>& edgeIDs,
            const std::array<IDType, 2>& edgeBreakIDs,
            const std::array<std::array<bool, 2>, 2>& bBreakEdge);

         DeckBoundary(const DeckBoundary&) = default;
         DeckBoundary& operator=(const DeckBoundary&) = default;

      public:
         ~DeckBoundary() = default;

         static std::shared_ptr<DeckBoundary> Create(const DeckBoundary& deckBoundary);

         /// @brief Creates a deck boundary object
         /// @param bridge A reference to the associated bridge
         /// @param transverseEdgeIDs ID of layout or pier lines defining the transverse edges of the deck boundary
         /// @param transverseEdgeTypes Indicates the type of line defining the transverse edges of the deck boundary
         /// @param edgeIDs Layout lines used to construct the deck edges
         /// @param edgeBreakIDs Layout lines that intersect with the transverse edges at the break points
         /// @param bBreakEdge Boolean value indicating of the transverse edges have break points
         /// @return 
         static std::shared_ptr<DeckBoundary> Create(std::weak_ptr<const BridgeFramingGeometry> bridge,
            const std::array<IDType, 2>& transverseEdgeIDs,
            const std::array<TransverseEdgeType, 2>& transverseEdgeTypes,
            const std::array<IDType, 2>& edgeIDs,
            const std::array<IDType, 2>& edgeBreakIDs,
            const std::array<std::array<bool, 2>, 2>& bBreakEdge);

         /// @brief Returns a collection of points defining the perimeter of the deck boundary.
         /// @param nMinPointsPerSide Minimum number of points for each side of the deck boundary. Key points in the deck boundary layout lines, such as angle points or points of curvature, are also included.
         /// @return 
         std::vector<WBFL::Geometry::Point2d> GetPerimeter(IndexType nMinPointsPerSide) const;

         /// @brief Returns a collection of points defining the perimeter of a subset of the deck boundary.
         /// @param nMinPointsPerSide Minimum number of points for each side of the deck boundary. Key points in the deck boundary layout lines, such as angle points or points of curvature, are also included.
         /// @param startPierID Identifier of the pier where the boundary starts. The transverse boundary is based on the centerline of the PierLine
         /// @param Xstart Offset from the start pier where the boundary starts. 
         /// @param endPierID Identifier of the pier where the boundary ends. The transverse boundary is based on the centerline of the PierLine
         /// @param Xend Offset from the end pier where the boundary starts
         /// @param bParallelToPiers If true, the transverse boundary is parallel to the centerline of the PierLine otherwise it is normal to the alignment
         /// @return 
         std::vector<WBFL::Geometry::Point2d> GetPerimeter(IndexType nMinPointsPerSide, IDType startPierID, Float64 Xstart, IDType endPierID, Float64 Xend, bool bParallelToPiers) const;

         /// @brief Returns the points the define the transverse edge of the deck boundary
         /// @param endType Indicates the start or end of the deck
         /// @return 
         std::array<WBFL::Geometry::Point2d, 4> GetTransverseEdgePoints(EndType endType) const;

         /// @brief Returns a path representing an edge of the deck boundary
         /// @param side Indicates the side of the deck boundary
         /// @param bReturnLayoutPath If true, the layout line path is returned, otherwise the deck edge path is returned
         /// @return 
         std::shared_ptr<const Path> GetEdgePath(SideType side, bool bReturnLayoutPath) const;

      private:
         std::weak_ptr<const BridgeFramingGeometry> m_pBridge;

         // Use the EndType enum to access these arrays
         std::array<IDType, 2> m_TransverseEdgeID; // ID of the path that defines the transverse edge of the deck
         std::array<TransverseEdgeType, 2> m_TransverseEdgeType; // Type of line that defines the transverse edge of deck

         // Use the SideType enum to access these arrays
         std::array<IDType, 2> m_EdgeID; // ID of layout line that defines the edge of deck
         std::array<IDType, 2> m_EdgeBreakID; // ID of layout line that defines the break back points

         // Boolean value that indicates if there is a break point 
         // in the ends of the slab.
         // use the EndType and SideType to access the array
         // e.g. m_vbBreakEdge[etStart][stLeft]
         std::array<std::array<bool,2>,2> m_bBreakEdge;

         // Coordinates that define the ends of the slab. 
         // Use the EndType and SideType to access the array
         // e.g. m_EdgePoint[etStart][stLeft]
         std::array<std::array<WBFL::Geometry::Point2d, 2>, 2> m_EdgePoint; // intersection of slab edge with the slab path
         std::array<std::array<WBFL::Geometry::Point2d, 2>, 2> m_EdgeBreakPoint; // location of break back point

         std::array<std::shared_ptr<Path>, 2> m_EdgePath; // path that defined the edge of the deck. Use the SideType enum to access the array

         std::shared_ptr<const BridgeFramingGeometry> GetBridge() const;
         void UpdateGeometry();
         void CreateDeckBoundaryEndPoints(EndType endType);
         void CreateEdgePath(SideType sideType);
      };
   };
};
