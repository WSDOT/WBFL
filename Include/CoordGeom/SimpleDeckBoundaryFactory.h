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
#include <CoordGeom/DeckBoundaryFactory.h>
#include <CoordGeom/CoordGeomTypes.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A simple deck boundary factory that creates a deck boundary using layout lines and pier lines.
      class COORDGEOMCLASS SimpleDeckBoundaryFactory : public DeckBoundaryFactory
      {
      public:
         SimpleDeckBoundaryFactory() = default;
         SimpleDeckBoundaryFactory(const SimpleDeckBoundaryFactory&) = default;
         ~SimpleDeckBoundaryFactory() = default;
         SimpleDeckBoundaryFactory& operator=(const SimpleDeckBoundaryFactory&) = default;

         /// @brief ID of the layout or pier line identifier used to create the transverse boundary edge at the end of the deck
         /// @param endType Indicates the end of the deck
         /// @param id The layout or pier line identifier
         void SetTransverseEdgeID(EndType endType, IDType id);
         IDType GetTransverseEdgeID(EndType endType) const;

         /// @brief Indicates if the transverse edge is defined using a layout line or a pier line
         /// @param endType Indicates the end of the deck
         /// @param type Defines the type of line used to defined the deck edge
         void SetTransverseEdgeType(EndType endType, TransverseEdgeType type);
         TransverseEdgeType GetTransverseEdgeType(EndType endType) const;

         /// @brief ID of the layout line used to define side of the deck
         /// @param sideType Indicates the side of the deck
         /// @param id The layout line identifier
         void SetEdgeID(SideType sideType, IDType id);
         IDType GetEdgeID(SideType sideType);

         /// @brief ID of the layout line used to define break points in the transverse boundary edge of the deck.
         /// @param sideType 
         /// @param id The layout line identifier. Use INVALID_ID if the transverse boundary edge does not have break points
         void SetEdgeBreakID(SideType sideType, IDType id);
         IDType GetEdgeBreakID(SideType sideType);

         /// @brief Boolean value indicating if the transverse boundary edge of the deck has a break point
         /// @param endType End of the deck
         /// @param sideType Side of the deck
         /// @param bBreak A value of true means the deck edge has a break
         void SetBreakEdge(EndType endType, SideType sideType, bool bBreak);
         bool GetBreakEdge(EndType endType, SideType sideType) const;

         virtual std::shared_ptr<DeckBoundary> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         // Use the EndType enum to access these arrays
         std::array<IDType, 2> m_TransverseEdgeID; // ID of the path that defines the transverse edge of the deck
         std::array<TransverseEdgeType, 2> m_TransverseEdgeType; // Type of line that defines the transverse edge of deck

         // Use the SideType enum to access these arrays
         std::array<IDType, 2> m_EdgeID; // ID of construction line that defines the edge of deck
         std::array<IDType, 2> m_EdgeBreakID; // ID of construction line that defines the break back points

         // Boolean value that indicates if there is a break point 
         // in the ends of the slab.
         // use the EndType and SideType to access the array
         // e.g. m_bBreakEdge[+EndType::Start][+SideType::Left]
         std::array<std::array<bool, 2>, 2> m_bBreakEdge;
      };
   };
};
