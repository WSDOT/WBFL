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
#include <CoordGeom/GirderLineFactory.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A simple girder line factory that creates girder lines based on previously defined layout lines
      class COORDGEOMCLASS SimpleGirderLineFactory : public GirderLineFactory
      {
      public:
         SimpleGirderLineFactory() = default;
         SimpleGirderLineFactory(const SimpleGirderLineFactory&) = default;
         ~SimpleGirderLineFactory() = default;
         SimpleGirderLineFactory& operator=(const SimpleGirderLineFactory&) = default;

         /// @brief ID of the first girder line
         /// @param id 
         void SetGirderLineID(IDType id);
         IDType GetGirderLineID() const;

         /// @brief The girder line ID increment
         /// @param idIncrement 
         void SetGirderLineIDIncrement(IDType idIncrement);
         IDType GetGirderLineIDIncrement() const;

         /// @brief The identifiers of the left and right layout lines. Girder lines are generated for each layout line.
         /// @param side 
         /// @param id 
         void SetLayoutLineID(SideType side,IDType id);
         IDType GetLayoutLineID(SideType side) const;

         /// @brief The layout line identifier increment
         /// @param idIncrement 
         void SetLayoutLineIDIncrement(IDType idIncrement);
         IDType GetLayoutLineIDIncrement() const;

         /// @brief The type of girder line to create
         /// @param type 
         void SetGirderLineType(GirderLineType type);
         GirderLineType GetGirderLineType() const;

         /// @brief The start and end pier line identifiers
         /// @param endType 
         /// @param id 
         void SetPierID(EndType endType,IDType id);
         IDType GetPierID(EndType endType) const;

         /// @brief The pier line identifier increment
         /// @param idIncrement 
         void SetPierIDIncrement(IDType idIncrement);
         IDType GetPierIDIncrement() const;

         /// @brief Parameter defining if the girder lines are continuous between the start to end pier lines
         /// @param bIsContinuous If true, single continuous girder line is created, otherwise multiple simple span girder lines are created
         void IsContinuous(bool bIsContinuous);
         bool IsContinuous() const;

         /// @brief The girder spacing measurement type
         /// @param endType 
         /// @param measurementType 
         void SetMeasurementType(EndType endType, MeasurementType measurementType);
         MeasurementType GetMeasurementType(EndType endType) const;

         /// @brief The girder spacing measurement location
         /// @param endType 
         /// @param measurementLocation 
         void SetMeasurementLocation(EndType endType, MeasurementLocation measurementLocation);
         MeasurementLocation GetMeasurementLocation(EndType endType) const;

         virtual std::vector<std::shared_ptr<GirderLine>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         IDType m_GirderLineID = INVALID_ID;     // ID of the girder line that will be created
         IDType m_GirderLineIDIncrement = 1;
         std::array<IDType, 2> m_LayoutLineID{ INVALID_ID,INVALID_ID };       // ID of the layout line used to create the girder line
         IDType m_LayoutLineIDIncrement = 1;
         GirderLineType m_GirderLineType = GirderLineType::Chord; // Type of girder line that will be created
         std::array<IDType, 2> m_PierID{ INVALID_ID,INVALID_ID };    // ID of the piers where the girder line begins and ends
         IDType m_PierIDIncrement = 1;
         bool m_bIsContinuous = false;
         std::array<MeasurementType, 2> m_MeasurementType{ MeasurementType::NormalToItem,MeasurementType::NormalToItem };   // Defines if the girder layout line is intersected with
         // the centerline of the pier or with the normal to the alignment
         // where the pier intersects the alignment
         std::array<MeasurementLocation, 2> m_MeasurementLocation{ MeasurementLocation::PierLine,MeasurementLocation::PierLine }; // Defines if the girder layout line is intersected with
         // the centerline of the pier or the centerline of bearing
      };
   };
};
