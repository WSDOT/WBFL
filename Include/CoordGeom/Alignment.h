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
#include <CoordGeom/Path.h>
#include <CoordGeom/Station.h>
#include <CoordGeom/StationEquation.h>
#include <CoordGeom/Profile.h>
#include <map>

namespace WBFL
{
   namespace COGO
   {
      /// @brief An object that represents a roadway, highway or other construction alignment.
      /// An alignment consists of PathElement objects.
      /// PathElement objects are positioned end to end in the order they are defined. Straight lines are used to connect the PathElement objects together. 
      /// The tangents at the beginning and end of the alignment are projected as straight lines.
      /// If an Alignment does not contain any PathElement objects, it is assumed that it begins at Station 0+00, point N 0.00, E 0.00, and is a straight line bearing N 90 E.
      class COORDGEOMCLASS Alignment : public std::enable_shared_from_this<Alignment>
      {
      private:
         Alignment();
         Alignment(const Alignment&);
         Alignment& operator=(const Alignment& other) = delete;

      public:
         /// @brief Creates an Alignment
         /// @return 
         static std::shared_ptr<Alignment> Create();
         static std::shared_ptr<Alignment> Create(const Alignment& alignment);
         ~Alignment() = default;

         /// @brief Sets the alignment reference station.
         /// The reference station defines the stationing of the entire alignment. The reference station is the station at the beginning of the first PathElement. 
         /// @param station This station must be normalized (the StationingZoneIndex must be INVALID_INDEX)
         void SetReferenceStation(const Station& station);

         /// @brief Returns the reference station
         /// @return 
         Station GetReferenceStation() const;

         /// @brief Adds a PathElement to the alignment
         /// @param pathElement 
         void AddPathElement(std::shared_ptr<PathElement> pathElement);

         /// @brief Inserts a PathElement object into the alignment at the specified index.
         /// @param idx 
         /// @param pathElement 
         void InsertPathElement(IndexType idx, std::shared_ptr<PathElement> pathElement);

         /// @brief The number of PathElement items in the alignment
         /// @return 
         IndexType GetPathElementCount() const;

         /// @brief Gets the PathElement at the specified index
         /// @param idx 
         /// @return 
         std::shared_ptr<const PathElement> GetPathElement(IndexType idx) const;
         std::shared_ptr<PathElement> GetPathElement(IndexType idx);

         /// @brief Returns the path elements
         /// @return 
         std::vector<std::shared_ptr<PathElement>>& GetPathElements();

         /// @brief Returns the path elements
         /// @return 
         const std::vector<std::shared_ptr<PathElement>>& GetPathElements() const;

         /// @brief Removes all PathElement objects
         void ClearPathElements();

         /// @brief Associates a profile with this alignment
         /// @param id ID used to identify the profile
         /// @param profile 
         void AddProfile(IDType id, std::shared_ptr<Profile> profile);

         /// @brief Gets a profile with the specified ID
         /// @param id The profile ID
         /// @return 
         std::shared_ptr<Profile> GetProfile(IDType id);

         /// @brief Gets a profile with the specified ID
         /// @param id The profile ID
         /// @return 
         std::shared_ptr<const Profile> GetProfile(IDType id) const;

         /// @brief Returns all of the profiles
         /// @return 
         const std::map<IDType, std::shared_ptr<Profile>>& GetProfiles() const;

         /// @brief Returns the number of profiles.
         /// @return 
         IndexType GetProfileCount() const;

         /// @brief Returns the profile ID for the specified index
         /// @param idx 
         /// @return 
         IDType GetProfileID(IndexType idx) const;

         /// @brief Removes all Profile objects
         void ClearProfiles();

         /// @brief Moves the alignment
         /// @param distance Distance to move the alignment. The alignment is moved in the opposite direction then the Direction object indicates when this parameter is less than zero.
         /// @param direction The direction to move the alignment.
         void Move(Float64 distance, const Direction& direction);

         /// @brief Computes the station and offset from the alignment for a given point
         /// @image html Images/Offset.jpg
         /// @param point The point whose station and offset is to be computed
         /// @return A pair of the form (Station,Offset). Station is where a normal line passing through point intersects the alignment. Offset is the distance from the alignment to the point
         std::pair<Station,Float64> StationAndOffset(const WBFL::Geometry::Point2d& point) const;
         
         /// @brief Divides the alignment into nParts equal length parts
         /// @param nParts Number of equal length parts
         /// @return Points along the path at the division points
         std::vector<WBFL::Geometry::Point2d> Divide(IndexType nParts) const;

         /// @brief Divides the alignment, between start and end, into nParts equal length parts
         /// @param start Station where the division begins
         /// @param end Station where the division ends.
         /// @param nParts Number of equal length parts
         /// @return Points along the path at the division points
         std::vector<WBFL::Geometry::Point2d> Divide(const Station& start, const Station& end, IndexType nParts) const;

         /// @brief Projects a point onto the Alignment
         /// If the projected point falls before the start or after the end of the alignment, then it will be a point on the back or forward tangent, respectively.
         /// @image html Images/ProjectPoint.jpg
         /// @param point The point to project onto the alignment
         /// @return A tuple of the form (Point,Station,OnProjection). Point is the projected point on the alignment. Station is the station on the alignment at Point. OnProjection is a boolean where true indicates Point is on a projection of the Alignment.
         std::tuple<WBFL::Geometry::Point2d,Station,bool> ProjectPoint(const WBFL::Geometry::Point2d& point) const;
         
         /// @brief Locates a Point object on the alignment at a specified location.
         /// @image html Images/LocatePoint.jpg
         /// @param station Station from which the point is to be located
         /// @param offsetType Specifies how offset is measured
         /// @param offset Offset from the alignment to the point
         /// @param dir Direction from the alignment at which to locate the point
         /// @return The new point
         WBFL::Geometry::Point2d LocatePoint(const Station& station, OffsetType offsetType, Float64 offset, const Direction& dir) const;

         /// @brief Intersects a Line2d object with the alignment, projecting the start and end tangents if specified, returning the intersection point nearest a specified point.
         /// @param line The line to intersect with the alignment.
         /// @param nearest A point used for comparison with multiple intersection points. The resulting point is the one nearest this point.
         /// @param bProjectBack If true, the back tangent line at the start of the alignment is considered to be part of the alignment
         /// @param bProjectAhead If true, the ahead tangent line at the end of the alignment is considered to be part of the alignment
         /// @return Pair of the format (Success,Point). Success is true if an intersection point is found, otherwise false and Point is undetermined. Point is the intersection point closest to nearest.
         std::pair<bool, WBFL::Geometry::Point2d> Intersect(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Point2d& nearest, bool bProjectBack,bool bProjectAhead) const;

         /// @brief Computes the bearing of the alignment at a specified station.
         /// @image html Images/Bearing.jpg
         /// @param station  Station at which the bearing is to be computed
         /// @return A Direction object representing the bearing
         Direction GetBearing(const Station& station) const;

         /// @brief Computes the normal to the alignment at a specified station.
         /// @image html Images/Normal.jpg
         /// @param station Station at which the normal is to be computed
         /// @return A Direction object representing the normal
         Direction GetNormal(const Station& station) const;

         /// @brief Gets the direction of a line at a specified station.
         /// The line orientation is a text string that represents a skew angle from the alignment normal, a direction, or the keyword **Normal** indicating a line normal to the alignment.
         /// See \ref WBFL_COGO_Angles_Directions_Stations.         
         /// @param station Station where the direction is to be determined
         /// @param strOrientation Orientation of the line.
         /// @return A Direction object representing the line.
         Direction GetDirection(const Station& station, const std::_tstring& strOrientation) const;

         /// @brief Length of the alignment
         /// @return 
         Float64 GetLength() const;

         /// @brief Creates a new Alignment that is offset from this Alignment. Profiles are not copied.
         /// @param offset Offset to the new alignment. The new alignment is to the right of the original alignment for positive values.
         /// @return 
         std::shared_ptr<Alignment> CreateOffsetAlignment(Float64 offset) const;

         /// @brief Creates a new Alignment that is a subset of this Alignment.
         /// @param start Station of the start of the sub-alignment
         /// @param end Station of the end of the sub-alignment
         /// @return A new Alignment object
         std::shared_ptr<Alignment> CreateSubAlignment(const Station& start, const Station& end) const;

         /// @brief Creates a new Path that is parallel to the this Alignment.
         /// @param offset Offset to the new path. The new path is to the right of the original path for positive values.
         /// @return The new path.
         std::shared_ptr<Path> CreateOffsetPath(Float64 offset) const;

         /// @brief Creates a new Path that is a subset of this Alignment.
         /// @param start Station at the start of the sub-path
         /// @param end Station at the end of the sub-path
         /// @return A new Path object
         std::shared_ptr<Path> CreateSubpath(const Station& start, const Station& end) const;

         /// @brief Creates a new StationEquation
         /// @param back The back station
         /// @param ahead The ahead station
         /// @return The new station object
         const StationEquation& AddStationEquation(Float64 back, Float64 ahead);

         /// @brief Returns the station equations
         /// @return 
         const std::vector<StationEquation>& GetStationEquations() const;

         /// @brief Removes all station equations
         void ClearStationEquations();

         /// @brief Computes the distance between two stations. This is effectively s2 - s2, however station equations are taken into consideration.
         /// @param s1 The first station
         /// @param s2 The second station
         /// @return The distance between stations
         Float64 DistanceBetweenStations(const Station& s1, const Station& s2) const;

         /// @brief Moves the station by the specified distance, making considerations for the station equations
         /// @param station Station to be moved
         /// @param distance Distance to move the station
         /// @return The station object after incrementing its location
         Station& IncrementStation(Station& station, Float64 distance) const;

         /// @brief Moves the station by the specified distance, making considerations for the station equations
         /// @param station Station from which the new station will be located
         /// @param distance Distance to move the station
         /// @return A new station object offset from the original station
         Station IncrementStationBy(const Station& station, Float64 distance) const;

         /// @brief Converts the station object to a normalized value
         /// @param station Station to be converted
         /// @return The normalized station
         Station ConvertToNormalizedStation(const Station& station) const;
         
         /// @brief Converts a normalized station value to a Station object, making considerations for the station equations
         /// @param normalizedStation Station value
         /// @return Station object
         Station ConvertFromNormalizedStation(Float64 normalizedStation) const;

         /// @brief Converts a normalized station object to a Station object, making considerations for the station equations
         /// @param station Station object, which must be normalized (StationZoneIndex is INVALID_INDEX)
         /// @return Station object
         Station ConvertFromNormalizedStation(const Station& station) const;

         /// @brief Compares the relative location of two stations
         /// @param s1 
         /// @param s2 
         /// @return 0 if s1 is at the same location as s2, 1 if s1 is before s2 and -1 if s1 is after s2
         Int8 CompareStations(const Station& s1, const Station& s2) const;

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
         static bool TestStationEquations(WBFL::Debug::Log& rlog);
         static bool TestAlignment(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         Float64 m_ReferenceStation{ 0.0 };
         std::shared_ptr<Path> m_Path;
         std::vector<StationEquation> m_StationEquations;

         std::map<IDType, std::shared_ptr<Profile>> m_Profiles;

         Float64 ComputeNormalizedStation(Float64 back);
         void BackStationError() const;
         void AheadStationError() const;
         void StationEquationError() const;

         Float64 StationToPathDistance(const Station& station) const;
         Station CreateStation(Float64 normalizedStation) const;
      };
   };
};
