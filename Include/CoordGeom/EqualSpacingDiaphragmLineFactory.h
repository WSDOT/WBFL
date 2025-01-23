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
#include <CoordGeom/DiaphragmLineFactory.h>
#include <CoordGeom/Station.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A DiaphragmLineFactory that creates a series of equally spaced DiaphragmLine objects between two stations on an alignment.
      /// The diaphragm lines are oriented normal to the alignment.
      /// @image html EqualSpacingDiaphragmLineFactory.png
      /// In the figure above, the station range is divided into 4 equal sections. Three diaphragm lines, that are perpendicular to the alignment,
      /// are generated.
      class COORDGEOMCLASS EqualSpacingDiaphragmLineFactory : public DiaphragmLineFactory
      {
      public:
         EqualSpacingDiaphragmLineFactory() = default;
         EqualSpacingDiaphragmLineFactory(const EqualSpacingDiaphragmLineFactory&) = default;
         ~EqualSpacingDiaphragmLineFactory() = default;
         EqualSpacingDiaphragmLineFactory& operator=(const EqualSpacingDiaphragmLineFactory&) = default;

         /// @brief ID of the alignment on which the stations are defined
         /// @param alignmentID 
         void SetAlignmentID(IDType alignmentID);
         IDType GetAlignmentID() const;

         /// @brief The stationing range for layout out the diaphragm lines
         /// @param startStation Station of the first diaphragm line
         /// @param endStation Station of the last diaphragm line
         void SetStationRange(const Station& startStation, const Station& endStation);

         /// @brief Returns the station range for diaphragm line creation
         /// @return Pair in the form (Start Station, End Station)
         std::pair<const Station&, const Station&> GetStationRange() const;

         /// @brief The ID of the first diaphragm line
         /// @param id 
         void SetDiaphragmLineID(IDType id);
         IDType GetDiaphragmLineID() const;

         /// @brief The diaphragm line ID increment
         /// @param idIncrement 
         void SetDiaphragmLineIDIncrement(IDType idIncrement);
         IDType GetDiaphragmLineIDIncrement() const;

         /// @brief Sets the number of spaces to divide the spacing range into
         /// @param divisor
         void SetDivisor(Uint16 divisor);
         Uint16 GetDivisor() const;

         /// @brief If true, the diaphragms lines are staggered, otherwise they are in a continuous line
         /// @param bIsStaggered 
         void IsStaggered(bool bIsStaggered);
         bool IsStaggered() const;

         /// @brief Sets the identifiers of the girder lines that bound the diaphragm lines
         /// @param side Side of the diaphragm
         /// @param id ID of the girder line
         void SetGirderLineID(SideType side, IDType id);
         IDType GetGirderLineID(SideType side) const;

         virtual std::vector<std::shared_ptr<DiaphragmLine>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         IDType m_ID = INVALID_ID;
         IDType m_IDIncrement = 1;
         IDType m_AlignmentID = INVALID_ID;
         Station m_StartStation{ 0.0 }, m_EndStation{ 0.0 };
         Uint16 m_Divisor = 0;
         bool m_bIsStaggered = false;
         std::array<IDType, 2> m_GirderLineID{INVALID_ID, INVALID_ID};
      };
   };
};
