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
#include <CoordGeom/Station.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Primitives3d.h>

namespace WBFL
{
   namespace COGO
   {
      class Surface;
      class SurfaceProfile;

      /// @brief A point on a Surface. SurfacePoint objects define the ridge points of a SurfaceProfile.
      class COORDGEOMCLASS SurfacePoint
      {
      private:
         SurfacePoint() = default;
         SurfacePoint(const Station& station, Float64 normalOffset, Float64 cutlineOffset, Float64 elevation, const WBFL::Geometry::Point2d& location);
         SurfacePoint(const SurfacePoint&) = delete;
         SurfacePoint& operator=(const SurfacePoint&) = delete;

         void SetSurface(std::weak_ptr<const Surface> surface);
         friend SurfaceProfile;

      public:
         ~SurfacePoint() = default;

         /// @brief Creates a SurfacePoint
         static std::shared_ptr<SurfacePoint> Create();

         /// @brief Creates a SurfacePoint
         /// @param station Station where the point occurs
         /// @param normalOffset Offset normal to the alignment to the point
         /// @param cutlineOffset Offset from the alignment, along a cut line, to the point
         /// @param elevation Elevation of the point
         /// @param location Plan coordinate of the point
         static std::shared_ptr<SurfacePoint> Create(const Station& station,Float64 normalOffset,Float64 cutlineOffset,Float64 elevation,const WBFL::Geometry::Point2d& location);

         /// @brief Returns the Surface with which this point is associated
         /// @return 
         std::shared_ptr<const Surface> GetSurface() const;

         /// @brief Sets the station
         /// @param station 
         void SetStation(const Station& station);

         /// @brief Gets the station
         /// @return 
         const Station& GetStation() const;

         /// @brief Sets the distance to this point measured normal from the alignment
         /// @param offset 
         void SetNormalOffset(Float64 offset);
         Float64 GetNormalOffset() const;

         /// @brief Sets the distance to this point measured from the alignment along a cut line
         /// @param offset 
         void SetCutlineOffset(Float64 offset);
         Float64 GetCutlineOffset() const;

         /// @brief Sets the elevation
         /// @param elevation 
         void SetElevation(Float64 elevation);

         /// @brief Gets the elevation
         /// @return 
         Float64 GetElevation() const;

         /// @brief Set the plan view location of the point
         /// @param location 
         void SetLocation(const WBFL::Geometry::Point2d& location);
         const WBFL::Geometry::Point2d& GetLocation() const;

         /// @brief Returns the point as a 3D point
         /// @return 
         WBFL::Geometry::Point3d GetPoint() const;

      private:
         std::weak_ptr<const Surface> m_Surface;

         Station m_Station = 0.0;
         Float64 m_NormalOffset = 0.0;
         Float64 m_CutlineOffset = 0.0;
         Float64 m_Elevation = 0.0;
         WBFL::Geometry::Point2d m_Location;
      };
   };
};
