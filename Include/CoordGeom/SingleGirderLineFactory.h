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
      /// @brief A factory that creates a single girder line
      class COORDGEOMCLASS SingleGirderLineFactory : public GirderLineFactory
      {
      public:
         SingleGirderLineFactory() = default;
         SingleGirderLineFactory(const SingleGirderLineFactory&) = default;
         ~SingleGirderLineFactory() = default;
         SingleGirderLineFactory& operator=(const SingleGirderLineFactory&) = default;

         /// @brief The girder line identifier
         /// @param id 
         void SetGirderLineID(IDType id);
         IDType GetGirderLineID() const;

         /// @brief The identifier of the layout line used to define the girder line
         /// @param id 
         void SetLayoutLineID(IDType id);
         IDType GetLayoutLineID() const;

         /// @brief The type of girder line 
         /// @param type 
         void SetGirderLineType(GirderLineType type);
         GirderLineType GetGirderLineType() const;

         /// @brief Identifiers of the pier lines at the start and end of the girder line
         /// @param endType 
         /// @param id 
         void SetPierID(EndType endType,IDType id);
         IDType GetPierID(EndType endType) const;

         /// @brief Defines if the girder layout line is intersected with the centerline of the pier or with the normal to the alignment
         /// where the pier intersects the alignment
         /// @param endType End of the girder line where the measurement type is defined
         /// @param measurementType
         void SetMeasurementType(EndType endType, MeasurementType measurementType);
         MeasurementType GetMeasurementType(EndType endType) const;

         /// @brief Defines if the girder layout line is intersected with the centerline of the pier or the centerline of bearing
         /// @param endType End of the girder line where the measurement type is defined
         /// @param measurementLocation 
         void SetMeasurementLocation(EndType endType, MeasurementLocation measurementLocation);
         MeasurementLocation GetMeasurementLocation(EndType endType) const;

         /// @brief Creates girder lines using the framing information of the provided bridge.
         /// @param bridge 
         /// @return 
         virtual std::vector<std::shared_ptr<GirderLine>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

      private:
         IDType m_GirderLineID = INVALID_ID;     // ID of the girder line that will be created
         IDType m_LayoutLineID = INVALID_ID;       // ID of the layout line used to create the girder line
         GirderLineType m_GirderLineType = GirderLineType::Chord; // Type of girder line that will be created
         std::array<IDType, 2> m_PierID{ INVALID_ID,INVALID_ID };    // ID of the piers where the girder line begins and ends
         std::array<MeasurementType, 2> m_MeasurementType{ MeasurementType::NormalToItem,MeasurementType::NormalToItem };   // Defines if the girder layout line is intersected with
         // the centerline of the pier or with the normal to the alignment
         // where the pier intersects the alignment
         std::array<MeasurementLocation, 2> m_MeasurementLocation{ MeasurementLocation::PierLine,MeasurementLocation::PierLine }; // Defines if the girder layout line is intersected with
         // the centerline of the pier or the centerline of bearing
      };
   };
};
