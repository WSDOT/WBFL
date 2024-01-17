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
#include <CoordGeom/Angle.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/CircularCurve.h>
#include <CoordGeom/TransitionCurve.h>
#include <CoordGeom/Path.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/ProfileSegment.h>
#include <CoordGeom/VerticalCurve.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/CubicSpline.h>
#include <CoordGeom/Station.h>

#include <GeomModel/Primitives.h>
#include <map>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A coordinate geometry model.
      /// 
      /// A coordinate geometry (COGO) model is defined by storing points, path segments, curves and other path and profile elements.
      /// This class provides data management for the stored elements of the model as well as geometric operations.
      /// Model elements do not need to be defined before using then in a definition. However all model elements in a definition must
      /// be defined before creating instances of the associated objects. For example, a path segment can be defined with end points 1 and 2
      /// before points 1 and 2 are stored in the model. However, points 1 and 2 must be defined before a PathSegment object is created.
      /// 
      /// Most data management functions return a boolean value indicating if it was successful. For those methods that do not return
      /// a boolean value, exceptions are thrown if the operation cannot be completed. For example, GetSegmentPath will throw an exception
      /// if the segment path ID is invalid.
      class COORDGEOMCLASS Model
      {
      public:
         Model() = default;
         Model(const Model&) = default;
         ~Model() = default;
         Model& operator=(const Model&) = default;

         /// @brief Enumeration that indicates the type of a path element
         enum class PathElementType
         {
            Point,
            Segment,
            CircularCurve,
            TransitionCurve,
            CompoundCurve,
            CubicSpline,
            Path
         };

         /// @brief Enumeration that indicates the type of a profile element
         enum class ProfileElementType
         {
            Point,
            Segment,
            VerticalCurve
         };

         /// @brief Parameters for defining a path segment in a COGO Model
         struct PathSegmentDefinition
         {
            IDType startID = INVALID_ID; ///< ID of the start point
            IDType endID = INVALID_ID; ///< ID of the end point
         };

         /// @brief Parameters for defining a compound curve in a COGO Model
         struct CompoundCurveDefinition
         {
            IDType pbtID = INVALID_ID; ///< ID of a point on the back tangent
            IDType piID = INVALID_ID; ///< ID of the tangent intersection point
            IDType pftID = INVALID_ID;///< ID of a point on the forward tangent
            Float64 radius = 0; ///< Radius of the curve
            Float64 entry_spiral_length = 0; ///< Entry spiral length
            TransitionCurveType entry_spiral_type = TransitionCurveType::Clothoid; ///< Entry spiral transition type
            Float64 exit_spiral_length = 0; ///< Exit spiral length
            TransitionCurveType exit_spiral_type = TransitionCurveType::Clothoid; ///< Exit spiral transition type
         };

         /// @brief Parameters for defining a circular curve in a COGO Model
         struct CircularCurveDefinition
         {
            IDType pbtID = INVALID_ID; ///< ID of a point on the back tangent
            IDType piID = INVALID_ID; ///< ID of the tangent intersection point
            IDType pftID = INVALID_ID;///< ID of a point on the forward tangent
            Float64 radius = 0; ///< Radius of the curve
         };

         /// @brief Parameters for defining a transition curve in a COGO Model
         struct TransitionCurveDefinition
         {
            IDType startID = INVALID_ID; ///< ID of the starting point
            Direction start_direction = 0; ///< Tangent direction at the start of the transition curve.
            Float64 start_radius = 0; ///< Radius at the start of the transition curve. A value of 0 indicates infinite radius
            Float64 end_radius = 0; ///< Radius at the end of the transition curve. A value of 0 indicates infinite radius
            Float64 length = 0; ///< Length of the transition curve
            TransitionCurveType transition_type = TransitionCurveType::Clothoid; ///< Type of transition
         };

         /// @brief Parameters for defining a profile segment in a COGO Model
         struct ProfileSegmentDefinition
         {
            IDType startID = INVALID_ID; ///< ID of the start point
            IDType endID = INVALID_ID; ///< ID of the end point
         };

         /// @brief Parameters for definition a vertical curve in a COGO Model
         /// Vertical curves can be defined in two ways:
         /// Length method: PBG, PVI, PFT, L1, L2 (grades are computed)
         /// Grade method: BVC, EVC, g1, g2 (PBG = BVC, PFT = EVC, and lengths are computed)
         /// Use pviID = INVALID_ID for the Grade method 
         struct VerticalCurveDefinition
         {
            IDType pbgID = INVALID_ID; ///< ID of a point on back grade (or beginning of curve point for grade method)
            IDType pviID = INVALID_ID; ///< ID of the point of vertical intersection (or INVALID_ID for grade method)
            IDType pfgID = INVALID_ID; ///< ID of a point on forward grade (or end of curve point for grade method)
            Float64 l1_or_g1 = 0.0; ///< l1_or_g1 Length or grade of back side of curve
            Float64 l2_or_g2 = 0.0; ///< l2_or_g2 Length or grade of forward side of curve
         };

         /// @brief Defines a superelevation transition surface modifier
         struct SuperelevationDefinition
         {
            Station begin_transition_station; ///< Station where the entry superelevation transition begins
            Station begin_full_super_station; ///< Station where the full superelevation begins
            Station end_full_super_station; ///< Station where the full superelevation ends
            Station end_transition_station; ///< Station where the exit superelevation transition ends
            Float64 rate = 0.0; ///< The superelevation rate(cross slope).Positive values indicates the roadway slopes upwards from left to right.
            IndexType pivot_point_index = INVALID_INDEX; ///< Ridge point index that the superelevation pivot occurs about.
            Superelevation::TransitionType begin_transition_type = Superelevation::TransitionType::Linear; ///< Entry transition type
            Float64 begin_l1 = 0.0; ///< If the entry transition is parabolic, this is the length of the parabola at the beginning of the transition
            Float64 begin_l2 = 0.0; ///< If the entry transition is parabolic, this is the length of the parabola at the beginning of full superelevation
            Superelevation::TransitionType end_transition_type = Superelevation::TransitionType::Linear; ///< Exit transition type
            Float64 end_l1 = 0.0; ///< If the exit transition is parabolic, this is the length of the parabola at the end of full superelevation
            Float64 end_l2 = 0.0; ///< If the exit transition is parabolic, this is the length of the parabola at the end of the transition
         };

         /// @brief Defines a widing surface modifier
         struct WideningDefinition
         {
            Station begin_transition_station; ///< Station where the entry widening transition begins
            Station begin_full_widening_station; ///< Station where the full widening begins
            Station end_full_widening_station; ///< Station where the fill widening ends
            Station end_transition_station; ///< Station where the exit widening transition ends
            Float64 widening = 0.0; ///< The width of the widening.Positive values widen the surface and negative values make it more narrow.
            IndexType segment1 = 0; ///< Index of a TemplateSegment to widen. 
            IndexType segment2 = INVALID_INDEX; ///< Index of a TemplateSegment to widen. Use INVALID_INDEX if the widening is applied to only one TemplateSegment.
         };


         /// @brief An item in a path definition defined as a pair (PathElementType,ElementID)
         using PathElementDefinition = std::pair<PathElementType, IDType>;

         /// @brief Defines a station equation in the format of a pair (Back Station, Ahead Station);
         using StationEquationDefinition = std::pair<Float64, Float64>;

         /// @brief Defines a surface with a tuple of the format (Number of Template Segments, Alignment Point Index, Profile Point Index)
         using SurfaceDefinition = std::tuple<IndexType, IndexType, IndexType>;

         /// @brief Defines a surface template segment as a tuple of the format (Width, Slope, SlopeType)
         using SurfaceTemplateSegmentDefinition = std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType>;

         /// @brief Defines a surface template as a pair of (Station, Collection of Surface Template Segments)
         using SurfaceTemplateDefinition = std::pair<Station, std::vector<SurfaceTemplateSegmentDefinition>>;

         ///@name COGO Data Management
         ///@{

         /// @brief Stores a point in the COGO model
         /// @param id Point ID
         /// @param point The point to be stored
         /// @return true if successful
         bool StorePoint(IDType id, const WBFL::Geometry::Point2d& point);

         /// @brief Stores a point in the COGO model
         /// @param id Point ID
         /// @param x X-ordinate of the point (aka Easting)
         /// @param y Y-ordinate of the point (aka Northing)
         /// @return true if successful
         bool StorePoint(IDType id, Float64 x, Float64 y);

         /// @brief Stores multiple points in the COGO model.
         /// This is an atomic operation where all points are stored or none of them are stored
         /// @param firstID ID of the first point to store
         /// @param idInc Value to increment the ID for each subsequent point
         /// @param vPoints A collection of points
         /// @return true if successful (all points stored)
         bool StorePoints(IDType firstID, IDType idInc, const std::vector<WBFL::Geometry::Point2d>& vPoints);

         /// @brief Stores multiple points in the COGO model.
         /// This is an atomic operation where all points are stored or none of them are stored
         /// @param firstID ID of the first point to store
         /// @param idInc Value to increment the ID for each subsequent point
         /// @param i1 Iterator to the first point to be stored
         /// @param i2 Iterator to the last point to be stored
         /// @return true if successful (all points stored)
         bool StorePoints(IDType firstID, IDType idInc, std::vector<WBFL::Geometry::Point2d>::const_iterator i1, std::vector<WBFL::Geometry::Point2d>::const_iterator i2);

         /// @brief Replaces a previously stored point
         /// @param id ID of the point
         /// @param point The new value of the point
         /// @return true if successful
         bool ReplacePoint(IDType id, const WBFL::Geometry::Point2d& point);

         /// @brief Replaces a previously stored point
         /// @param id ID of the point
         /// @param x new X value (Easting)
         /// @param y new Y value (Northing)
         /// @return true if successful
         bool ReplacePoint(IDType id, Float64 x, Float64 y);

         /// @brief Removes a previously stored point from the COGO model
         /// @param id ID of the point
         /// @return true if successful
         bool RemovePoint(IDType id);

         /// @brief Returns a previously stored point
         /// @param id ID of the point
         WBFL::Geometry::Point2d GetPoint(IDType id);

         /// @brief Returns a previously stored point
         /// @param id ID of the point
         const WBFL::Geometry::Point2d& GetPoint(IDType id) const;

         /// @brief Returns the collection of points and their associated IDs
         const std::map<IDType, WBFL::Geometry::Point2d>& GetPoints() const;

         /// @brief Removes all points from the model
         void ClearPoints();

         /// @brief Stores a path segment definition
         /// @param id ID of the path segment definition
         /// @param startID ID of the starting point
         /// @param endID ID of the ending point
         /// @return true if successful
         bool StorePathSegment(IDType id, IDType startID, IDType endID);

         /// @brief Stores a path segment definition
         /// @param id ID of the path segment definition
         /// @param definition Path segment definition parameters
         /// @return true if successful
         bool StorePathSegment(IDType id, const PathSegmentDefinition& definition);

         /// @brief Removes a previously stored path segment
         /// @param id ID of the path segment definition
         /// @return true if successful
         bool RemovePathSegment(IDType id);

         /// @brief Returns a path segment definition
         /// @param id ID of the path segment definition
         /// @return Path segment definition
         const PathSegmentDefinition& GetPathSegment(IDType id) const;

         /// @brief Creates a PathSegment object using a previously stored path segment definition
         /// @param id ID of the path segment definition
         /// @return Pointer to a PathSegment
         std::shared_ptr<PathSegment> CreatePathSegment(IDType id) const;

         /// @brief Returns the path segment definitions
         const std::map<IDType, PathSegmentDefinition>& GetPathSegments() const;

         /// @brief Removes all path segment definitions
         void ClearPathSegments();

         /// @brief Stores a compound curve definition
         /// @param id ID of the curve
         /// @param pbtID ID of a point on back tangent
         /// @param piID ID of the tangent intersection point
         /// @param pftID ID of a point on forward tangent
         /// @param radius Curve radius
         /// @param lsEntry Entry spiral length
         /// @param lsEntryType Entry spiral type
         /// @param lsExit Exit spiral length
         /// @param lsExitType Exit spiral type
         /// @return true if successful
         bool StoreCompoundCurve(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius, Float64 lsEntry = 0.0, TransitionCurveType lsEntryType = TransitionCurveType::Clothoid, Float64 lsExit = 0.0, TransitionCurveType lsExitType = TransitionCurveType::Clothoid);

         /// @brief Stores a compound curve definition
         /// @param id ID of the curve
         /// @param definition Curve definition parameters
         /// @return true if successful
         bool StoreCompoundCurve(IDType id, CompoundCurveDefinition& definition);

         /// @brief Removes a previously stored compound curve definition
         /// @param id ID of the curve
         /// @return true if successful
         bool RemoveCompoundCurve(IDType id);

         /// @brief Returns a previously stored compound curve definition
         /// @param id ID of the curve
         /// @return Curve definition parameters
         const CompoundCurveDefinition& GetCompoundCurve(IDType id) const;

         /// @brief Creates a CompoundCurve object using a previously stored compound curve definition
         /// @param id ID of the curve
         /// @return Pointer to a CompoundCurve object
         std::shared_ptr<CompoundCurve> CreateCompoundCurve(IDType id) const;

         /// @brief Returns the compound curve definitions
         const std::map<IDType, CompoundCurveDefinition>& GetCompoundCurves() const;

         /// @brief Removes all compound curve definitions
         void ClearCompoundCurves();

         /// @brief Stores a circular curve definition
         /// @param id ID of the curve
         /// @param pbtID ID of a point on back tangent
         /// @param piID ID of the tangent intersection point
         /// @param pftID ID of a point on forward tangent
         /// @param radius Curve radius
         /// @return true if successful
         bool StoreCircularCurve(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius);

         /// @brief Stores a circular curve definition
         /// @param id ID of the curve
         /// @param definition Curve definition parameters
         /// @return true if successful
         bool StoreCircularCurve(IDType id, const CircularCurveDefinition& definition);

         /// @brief Removes a previously stored circular curve definition
         /// @param id ID of the curve
         /// @return true if successful
         bool RemoveCircularCurve(IDType id);

         /// @brief Returns a previously stored circular curve definition
         /// @param id ID of the curve
         /// @return Curve definition parameters
         const CircularCurveDefinition& GetCircularCurve(IDType id) const;

         /// @brief Creates a CircularCurve object using a previously stored circular curve definition
         /// @param id ID of the curve
         /// @return Pointer to a CircularCurve object
         std::shared_ptr<CircularCurve> CreateCircularCurve(IDType id) const;

         /// @brief Returns the circular curve definition
         const std::map<IDType, CircularCurveDefinition>& GetCircularCurves() const;

         /// @brief Removes all circular curves
         void ClearCircularCurves();

         /// @brief Stores a transition curve definition
         /// @param id ID of the curve
         /// @param startID ID of the point at the start of the curve
         /// @param startDirection Tangent direction at the start of the curve
         /// @param r1 Radius at the start of the curve (use 0.0 for infinite radius)
         /// @param r2 Radius at the end of the curve (use 0.0 for infinite radius)
         /// @param L Length of the transition curve
         /// @param transitionType Transition type
         /// @return true if successful
         bool StoreTransitionCurve(IDType id, IDType startID, const Direction& startDirection, Float64 r1,Float64 r2, Float64 L, TransitionCurveType transitionType = TransitionCurveType::Clothoid);

         /// @brief Stores a transition curve definition
         /// @param id ID of the curve
         /// @param definition Curve definition parameters
         /// @return true if successful
         bool StoreTransitionCurve(IDType id, const TransitionCurveDefinition& definition);

         /// @brief Removes a previously stored transition curve
         /// @param id ID of the curve
         /// @return true if successful
         bool RemoveTransitionCurve(IDType id);

         /// @brief Returns a previously stored transition curve definition
         /// @param id ID of the curve
         /// @return Curve definition parameters
         const TransitionCurveDefinition& GetTransitionCurve(IDType id) const;

         /// @brief Creates a TransitionCurve from a previously stored transition curve definition
         /// @param id ID of the curve
         /// @return Pointer to a TransitionCurve object
         std::shared_ptr<TransitionCurve> CreateTransitionCurve(IDType id) const;

         /// @brief Returns the transition curve definitions
         const std::map<IDType, TransitionCurveDefinition>& GetTransitionCurves() const;

         /// @brief Removes all transition curves
         void ClearTransitionCurves();

         /// @brief Stores a cubic spline definition
         /// @param id ID of the curve
         /// @param vPointIDs Collection of IDs for the spline points
         /// @return true if successful
         bool StoreCubicSpline(IDType id, const std::vector<IDType>& vPointIDs);

         /// @brief Removes a previously stored cubic spline definition
         /// @param id ID of the curve
         /// @return true if successful
         bool RemoveCubicSpline(IDType id);

         /// @brief Returns a previously stored cubic spline definition
         /// @param id ID of the curve
         /// @return Collection of IDs for the cubic spline points
         const std::vector<IDType>& GetCubicSpline(IDType id) const;

         /// @brief Creates a CubicSpline object from a previously stored cubic spline definition
         /// @param id ID of the curve
         /// @return Pointer to a CubicSpline object
         std::shared_ptr<CubicSpline> CreateCubicSpline(IDType id) const;

         /// @brief Returns the cubic spline definitions
         const std::map<IDType, std::vector<IDType>>& GetCubicSplines();

         /// @brief Removes all cubic spline definitions
         void ClearCubicSplines();

         /// @brief Stores a definition of an empty alignment
         /// @param id ID of the alignment
         /// @return true if successful
         bool StoreAlignment(IDType id);

         /// @brief Stores a definition of an alignment 
         /// @param alignmentID ID of the alignment
         /// @param vElements Collection of path element types and IDs making up the alignment
         /// @return true if successful
         bool StoreAlignment(IDType alignmentID, const std::vector<PathElementDefinition>& vElements);

         /// @brief Appends a path element definition to the end of a previous stored alignment definition
         /// @param alignmentID ID of the alignment
         /// @param elementType Type of the path element
         /// @param elementID ID of the path element
         /// @return true if successful
         bool AppendElementToAlignment(IDType alignmentID, PathElementType elementType, IDType elementID);

         /// @brief Appends a path element definition to the end of a previously stored alignment definition
         /// @param alignentID ID of the alignment
         /// @param item Path element definition
         /// @return true if successful
         bool AppendElementToAlignment(IDType alignentID, const PathElementDefinition& item);

         /// @brief Removes a previously stored alignment definition
         /// @param alignmentID ID of the alignment
         /// @return true if successful
         bool RemoveAlignment(IDType alignmentID);

         /// @brief Returns a previously stored alignment definition
         /// @param alignmentID ID of the alignment
         /// @return Collection of path element items.
         const std::vector<PathElementDefinition>& GetAlignment(IDType alignmentID) const;

         /// @brief Creates an Alignment from a previously stored alignment definition
         /// @param alignmentID ID of the alignment
         /// @return Pointer to an Alignment object
         std::shared_ptr<Alignment> CreateAlignment(IDType alignmentID) const;

         /// @brief Returns the alignment definitions
         const std::map<IDType, std::vector<PathElementDefinition>>& GetAlignments() const;

         /// @brief Removes all alignment definitions
         /// @param bClearRefStations If true, alignment reference stations are also removed from the model
         void ClearAlignments(bool bClearRefStations=true);

         /// @brief Sets the reference station for a previously defined alignment
         /// @param alignmentID ID of the alignment
         /// @param station Reference station value (station at the beginning of the alignment)
         /// @return true if successful
         bool SetAlignmentReferenceStation(IDType alignmentID, const Station& station);

         /// @brief Removes a previously defined alignment reference station.
         /// Alignments without explicitly defined references are assumed to have a reference station of 0.0 at the start of the alignment.
         /// @param alignmentID ID of the alignment
         /// @return true if successful
         bool RemoveAlignmentReferenceStation(IDType alignmentID);

         /// @brief Returns the reference station for an alignment
         /// @param alignmentID ID of the alignment
         /// @return 
         const Station& GetAlignmentReferenceStation(IDType alignmentID) const;

         /// @brief Adds a station equation definition to an alignment
         /// @param alignmentID ID of the alignment 
         /// @param back Back stationing value
         /// @param ahead Ahead stationing value
         /// @return true if successful
         bool AddStationEquation(IDType alignmentID, Float64 back, Float64 ahead);

         /// @brief Adds a station equation definition to an alignment
         /// @param alignmentID ID of the alignment
         /// @param definition Station equation definition parameters
         /// @return true if successful
         bool AddStationEquation(IDType alignmentID, const StationEquationDefinition& definition);

         /// @brief Returns the station equations definition for an alignment
         /// @param alignmentID ID of the alignment
         /// @return A collection of (Back Station, Ahead Station) pairs
         const std::vector<StationEquationDefinition>& GetStationEquations(IDType alignmentID) const;

         /// @brief Removes station equations from an alignment
         /// @param alignmentID ID of the alignment. Use INVALID_ID to clear station equations from all alignments
         void ClearStationEquations(IDType alignmentID = INVALID_ID);

         /// @brief Stores a definition of an empty path
         /// @param pathID ID of the path
         /// @return true if successful
         bool StorePath(IDType pathID);

         /// @brief Stores a definition of a path
         /// @param pathID ID of the path
         /// @param vElements Collection of path element types and IDs making up the path
         /// @return true if successful
         bool StorePath(IDType pathID, const std::vector<PathElementDefinition>& vElements);

         /// @brief Appends a path element definition to the end of a previously stored path definition
         /// @param pathID ID of the path
         /// @param elementType Type of the path element
         /// @param elementID ID of the path element
         /// @return true if successful
         bool AppendElementToPath(IDType pathID, PathElementType elementType, IDType elementID);

         /// @brief Appends a path element definition to the end of a previously stored path definition
         /// @param pathID ID of the path
         /// @param item Path element definition
         /// @return true if successful
         bool AppendElementToPath(IDType pathID, const PathElementDefinition& item);

         /// @brief Removes a previously stored path definition
         /// @param pathID ID of the path
         /// @return 
         bool RemovePath(IDType pathID);

         /// @brief Returns a previously stored path definition
         /// @param pathID ID of the path definition
         /// @return Collection of path element types and IDs
         const std::vector<PathElementDefinition>& GetPath(IDType pathID) const ;

         /// @brief Create a Path from a previously stored path definition
         /// @param pathID ID of the path
         /// @return Pointer to a Path object
         std::shared_ptr<Path> CreatePath(IDType pathID) const;

         /// @brief Returns the path definitions
         const std::map<IDType, std::vector<PathElementDefinition>>& GetPaths() const;

         /// @brief Removes all path definitions
         void ClearPaths();

         /// @brief Stored a profile point in the COGO model
         /// @param id Point ID
         /// @param profilePoint  The point to be stored
         /// @return true if successful
         bool StoreProfilePoint(IDType id, const ProfilePoint& profilePoint);

         /// @brief Stores a profile point in the COGO model
         /// @param id Point ID
         /// @param station The point's station
         /// @param elevation The point's elevation
         /// @return true if successful
         bool StoreProfilePoint(IDType id, const Station& station, Float64 elevation);

         /// @brief Replaces a previous stored profile point
         /// @param id ID of the point
         /// @param profilePoint The new value of the point
         /// @return true if successful
         bool ReplaceProfilePoint(IDType id, const ProfilePoint& profilePoint);

         /// @brief Replaces a previous stored profile point
         /// @param id ID of the point
         /// @param station The new station
         /// @param elevation The new elevation
         /// @return true if successful
         bool ReplaceProfilePoint(IDType id, const Station& station, Float64 elevation);

         /// @brief Removes a previously stored point from the COGO model
         /// @param id ID of the point
         /// @return true if successful
         bool RemoveProfilePoint(IDType id);

         /// @brief Returns a previously stored profile point
         /// @param id ID of the point
         ProfilePoint GetProfilePoint(IDType id);

         /// @brief Returns a previously stored profile point
         /// @param id ID of the point
         const ProfilePoint& GetProfilePoint(IDType id) const;

         /// @brief Returns the collection of profile points and their associated IDs
         const std::map<IDType, ProfilePoint>& GetProfilePoints() const;

         /// @brief Removes all profile points from the model
         void ClearProfilePoints();
         
         /// @brief Stores a profile segment definition
         /// @param id ID of the profile segment definition
         /// @param startID ID of the starting point
         /// @param endID ID of the ending point
         /// @return true if successful
         bool StoreProfileSegment(IDType id, IDType startID, IDType endID);

         /// @brief Stores a profile segment definition
         /// @param id ID of the profile segment definition
         /// @param definition Profile element definition parameters
         /// @return true if successful
         bool StoreProfileSegment(IDType id, const ProfileSegmentDefinition& definition);

         /// @brief Removes a previous stored profile segment
         /// @param id ID of the profile segment
         /// @return true if successful
         bool RemoveProfileSegment(IDType id);

         /// @brief Returns a profile segment definition
         /// @param id ID of the profile segment definition
         /// @return Pair in the format (StartProfilePointID,EndProfilePointID)
         const ProfileSegmentDefinition& GetProfileSegment(IDType id) const;

         /// @brief Creates a ProfileSegment object using a previously stored profile segment definition
         /// @param id ID of the profile segment
         /// @return Pointer to a ProfileSegment
         std::shared_ptr<ProfileSegment> CreateProfileSegment(IDType id) const;

         /// @brief Returns the profile segment definitions
         const std::map<IDType, ProfileSegmentDefinition>& GetProfileSegments() const;

         /// @brief Removes all profile segment definitions
         void ClearProfileSegments();

         /// @brief Stores a vertical curve definition.
         /// Vertical curves can be defined in two ways:
         /// Length method: PBG, PVI, PFT, L1, L2 (grades are computed)
         /// Grade method: BVC, EVC, g1, g2 (PBG = BVC, PFT = EVC, and lengths are computed)
         /// Use pviID = INVALID_D for the Grade method 
         /// @param id ID of the vertical curve
         /// @param pbgID ID of a point on back grade (or beginning of curve point for grade method)
         /// @param pviID ID of the point of vertical intersection (or INVALID_ID for grade method)
         /// @param pftID ID of a point on forward grade (or end of curve point for grade method)
         /// @param l1_or_g1 Length or grade of back side of curve
         /// @param l2_or_g2 Length or grade of forward side of curve
         /// @return true if successful
         bool StoreVerticalCurve(IDType id, IDType pbgID, IDType pviID, IDType pftID, Float64 l1_or_g1, Float64 l2_or_g2);

         /// @brief Stores a vertical curve definition
         /// @param id ID of the vertical curve
         /// @param definition Curve definition parameters
         /// @return true if successful
         bool StoreVerticalCurve(IDType id, const VerticalCurveDefinition& definition);

         /// @brief Removes a previously stored vertical curve definition
         /// @param id ID of the vertical curve 
         /// @return true if successful
         bool RemoveVerticalCurve(IDType id);

         /// @brief Returns a previously stored vertical curve definition
         /// @param id ID of the vertical curve 
         /// @return tuple of the format (PBG ID, PVI ID, PFG ID, L1 or G1, L2 or G2). See StoreVerticalCurve for more information.
         const VerticalCurveDefinition& GetVerticalCurve(IDType id) const;

         /// @brief Creates a VerticalCurve from a previously stored vertical curve definition
         /// @param id ID of the vertical curve
         /// @return Pointer to a VerticalCurve
         std::shared_ptr<VerticalCurve> CreateVerticalCurve(IDType id) const;

         /// @brief Returns the vertical curve definitions
         const std::map<IDType, VerticalCurveDefinition>& GetVerticalCurves() const;

         /// @brief Removes all vertical curves
         void ClearVerticalCurves();

         /// @brief Stores a definition of an empty profile
         /// @param profileID ID of the profile 
         /// @return true if successful
         bool StoreProfile(IDType profileID);

         /// @brief Stores a definition of a profile
         /// @param profileID ID of the profile
         /// @param vElements Collection of profile element types and IDs making up the profile
         /// @return true if successful
         bool StoreProfile(IDType profileID, const std::vector<std::pair<ProfileElementType, IDType>>& vElements);

         /// @brief Appends a profile element definition to the end of a previously stored profile definition
         /// @param profileID ID of the profile
         /// @param elementType Type of the profile element
         /// @param elementID ID of the profile element
         /// @return 
         bool AppendElementToProfile(IDType profileID, ProfileElementType elementType, IDType elementID);

         /// @brief Removes a previously stored profile definition
         /// @param profileID ID of the profile
         /// @return true if successful
         bool RemoveProfile(IDType profileID);

         /// @brief Returns a previous stored profile definition
         /// @param profileID ID of the profile
         /// @return Collection of profile element types and IDs.
         const std::vector<std::pair<ProfileElementType, IDType>>& GetProfile(IDType profileID) const;

         /// @brief Creates a Profile from a previously stored profile definition
         /// @param profileID ID of the profile
         /// @return Pointer to a Profile object
         std::shared_ptr<Profile> CreateProfile(IDType profileID) const;

         /// @brief Returns the profile definitions
         const std::map<IDType, std::vector<std::pair<ProfileElementType, IDType>>>& GetProfiles() const;

         /// @brief Removes all Profiles
         void ClearProfiles();

         /// @brief Stores an empty surface definition
         /// @param surfaceID ID of the surface
         /// @param nSurfaceTemplateSegments Number of surface template segments
         /// @param alignmentPointIdx Ridge point index corresponding to the alignment
         /// @param profilePointIdx Ridge point index corresponding to the profile
         /// @return true if successful
         bool StoreSurface(IDType surfaceID, IndexType nSurfaceTemplateSegments, IndexType alignmentPointIdx, IndexType profilePointIdx);

         /// @brief Stores an empty surface definition
         /// @param surfaceID ID of the surface
         /// @param surfaceDef Surface definition parameters
         /// @return true if successful
         bool StoreSurface(IDType surfaceID, const SurfaceDefinition& surfaceDef);

         /// @brief Returns a previously stored surface definition
         /// @param surfaceID IS of the surface
         /// @return Surface definition parameters
         const SurfaceDefinition& GetSurface(IDType surfaceID) const;

         /// @brief Returns the surface definitions
         const std::map<IDType, SurfaceDefinition>& GetSurfaces() const;

         /// @brief Adds a surface template to a surface
         /// @param surfaceID ID of the surface
         /// @param station Station where the surface template is defined
         /// @return true if successful
         bool AddSurfaceTemplate(IDType surfaceID, const Station& station);

         /// @brief Copies a surface template
         /// @param surfaceID ID of the surface
         /// @param templateIdx Index of a previous defined surface template
         /// @param station Location of the new surface template
         /// @return true if successful
         bool CopySurfaceTemplate(IDType surfaceID, IndexType templateIdx, const Station& station);

         /// @brief Moves a previously defined surface template
         /// @param surfaceID ID of the surface
         /// @param templateIdx Index of the previous defined surface template
         /// @param station New location of the surface template
         /// @return true if successful
         bool MoveSurfaceTemplate(IDType surfaceID, IndexType templateIdx, const Station& station);

         /// @brief Returns the number of surface templates defined for a surface
         /// @param surfaceID ID of the surface
         /// @return Number of surface templates
         IndexType GetSurfaceTemplateCount(IDType surfaceID) const;

         /// @brief Returns the location of a surface template
         /// @param surfaceID ID of the surface
         /// @param templateIdx Index of the surface template
         /// @return Location of the surface template
         const Station& GetSurfaceTemplateLocation(IDType surfaceID, IndexType templateIdx);

         /// @brief Returns a previously defined surface template
         /// @param surfaceID ID of the surface
         /// @param templateIdx Index of the surface template
         /// @return Surface template parameters
         const SurfaceTemplateDefinition& GetSurfaceTemplate(IDType surfaceID, IndexType templateIdx) const;

         /// @brief Updates the definition of a surface template segment
         /// @param surfaceID ID of the surface
         /// @param templateIdx Index of the surface template
         /// @param segmentIdx ID of the surface template segment within the surface template
         /// @param width Segment width
         /// @param slope Segment slope
         /// @param slopeType Segment slope type
         /// @return true if successful
         bool UpdateSurfaceTemplateSegment(IDType surfaceID, IndexType templateIdx, IndexType segmentIdx, Float64 width, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType);

         /// @brief Updates the definition of a surface template segment
         /// @param surfaceID ID of the surface
         /// @param templateIdx Index of the surface template
         /// @param segmentIdx ID of the surface template segment within the surface template
         /// @param surfaceTemplateSegment Surface template segment parameters
         /// @return true if successful
         bool UpdateSurfaceTemplateSegment(IDType surfaceID, IndexType templateIdx, IndexType segmentIdx, const SurfaceTemplateSegmentDefinition& surfaceTemplateSegment);

         /// @brief Stores a superelevation definition for a surface
         /// @param surfaceID ID of the surface
         /// @param beginTransitionStation Station where the entry superelevation transition begins
         /// @param beginFullSuperStation Station where the full superelevation begins
         /// @param endFullSuperStation Station where the full superelevation ends
         /// @param endTransitionStation Station where the exit superelevation transition ends
         /// @param rate The superelevation rate (cross slope). Positive values indicates the roadway slopes upwards from left to right.
         /// @param pivotPointIdx Ridge point index that the superelevation pivot occurs about.
         /// @param beginTransitionType  Entry transition type
         /// @param beginL1 If the entry transition is parabolic, this is the length of the parabola at the beginning of the transition
         /// @param beginL2 If the entry transition is parabolic, this is the length of the parabola at the beginning of full superelevation
         /// @param endTransitionType Exit transition type
         /// @param endL1 If the exit transition is parabolic, this is the length of the parabola at the end of full superelevation
         /// @param endL2 If the exit transition is parabolic, this is the length of the parabola at the end of the transition
         /// @return true if successful
         bool StoreSuperelevation(IDType surfaceID, const Station& beginTransitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTransitionStation, Float64 rate, IndexType pivotPointIdx,
            Superelevation::TransitionType beginTransitionType = Superelevation::TransitionType::Linear, Float64 beginL1 = 0.0, Float64 beginL2 = 0.0, Superelevation::TransitionType endTransitionType = Superelevation::TransitionType::Linear, Float64 endL1 = 0.0, Float64 endL2 = 0.0);

         /// @brief Stores a superelevation definition for a surface
         /// @param surfaceID ID of the surface
         /// @param definition Superelevation definition parameters
         /// @return true if successful
         bool StoreSuperelevation(IDType surfaceID, const SuperelevationDefinition& definition);

         /// @brief Returns the superelevation definitions
         /// @return 
         const std::map<IDType, std::vector<SuperelevationDefinition>>& GetSuperelevations() const;

         /// @brief Returns the superelevation definitions for a specified surface
         /// @param surfaceID ID of the surface
         /// @return 
         const std::vector<SuperelevationDefinition>& GetSuperelevations(IDType surfaceID) const;

         /// @brief Clears the superelevations for a surface
         /// @param surfaceID ID of the surface
         /// @return 
         bool ClearSuperelevations(IDType surfaceID);

         /// @brief Clears all superelevations from the model
         void ClearSuperelevations();

         /// @brief Stores a widening definition for a surface
         /// @param surfaceID ID of the surface
         /// @param beginTransitionStation Station where the entry widening transition begins
         /// @param beginFullWidening Station where the full widening begins
         /// @param endFullWidening Station where the fill widening ends
         /// @param endTransitionStation Station where the exit widening transition ends
         /// @param widening The width of the widening. Positive values widen the surface and negative values make it more narrow.
         /// @param segment1 Index of a TemplateSegment to widen
         /// @param segment2 Index of a TemplateSegment to widen. Use INVALID_INDEX if the widening is applied to only one TemplateSegment.
         /// @return true if successful
         bool StoreWidening(IDType surfaceID, const Station& beginTransitionStation, const Station& beginFullWidening, const Station& endFullWidening, const Station& endTransitionStation, Float64 widening, IndexType segment1, IndexType segment2);

         /// @brief Stores a widening definition for a surface
         /// @param surfaceID ID of the surface
         /// @param definition Widening definition parameters
         /// @return true if successful
         bool StoreWidening(IDType surfaceID, const WideningDefinition& definition);

         /// @brief Returns the widening definitions
         /// @return 
         const std::map<IDType, std::vector<WideningDefinition>>& GetWidenings() const;

         /// @brief Returns the widening definitions for a specified surface
         /// @param surfaceID ID of the surface
         /// @return 
         const std::vector<WideningDefinition>& GetWidenings(IDType surfaceID) const;

         /// @brief Clears the WideningDefinition for a surface
         /// @param surfaceID ID of the surface
         /// @return 
         bool ClearWidenings(IDType surfaceID);

         /// @brief Clears all widenings from the model
         void ClearWidenings();

         /// @brief Creates a Surface object from a previously stored surface definition
         /// @param surfaceID ID of the surface
         /// @return Pointer to a Surface object
         std::shared_ptr<Surface> CreateSurface(IDType surfaceID) const;

         /// @brief Removes a surface from the model
         /// @param surfaceID ID of the surface
         /// @param bClearModifiers If true, modifiers (superelevations and widenings) associated with the surface are also cleared
         /// @return true if successful
         bool RemoveSurface(IDType surfaceID, bool bClearModifiers = true);

         /// @brief Removes all surfaces from the model
         /// @param bClearModifiers If true, modifiers (superelevations and widenings) associated with the surface are also cleared
         void ClearSurfaces(bool bClearModifiers = true);

         /// @brief Stores an association between a profile and an alignment.
         /// @param profileID ID of the profile
         /// @param alignmentID ID of the alignment
         void AttachProfileToAlignment(IDType profileID, IDType alignmentID);

         /// @brief Stores an association between a surface and a profile
         /// @param surfaceID ID of the surface
         /// @param profileID ID of the profile
         void AttachSurfaceToProfile(IDType surfaceID, IDType profileID);

         /// @brief Clears the entire COGO model
         void Clear();

         ///@}

         ///@name Measure
         ///@{
         
         /// @brief Measures the angle formed by three non-coincident points.
         /// @image html Images/Angle.jpg
         /// @param fromID ID of the point the angle is measured from
         /// @param vertexID ID of the point at the vertex of the angle
         /// @param toID ID of the point the angle is measured to
         /// @return The angle
         Angle MeasureAngle(IDType fromID, IDType vertexID, IDType toID) const;

         /// @brief Measures the angle of a polygon.
         /// @image html Images/Area.jpg
         /// The polygon must consist of at least three non-colinear points. Points may be defined either clockwise or counter-clockwise. The last point need not be the same as the first. 
         /// Degenerate polygons (polygon with intersecting edges such as a bow-tie shape) are not detected. An incorrect area will be computed if a degenerate polygon is input.
         /// @param vIDs An array of IDs identifying the points that comprise the polygon
         /// @return The area of the polygon
         Float64 MeasureArea(const std::vector<IDType>& vIDs) const;

         /// @brief Measures the distance between two points.
         /// @image html Images/Distance.jpg
         /// @param fromID ID of the first point
         /// @param toID ID of the second point
         /// @return Distance between the points
         Float64 MeasureDistance(IDType fromID, IDType toID) const;

         /// @brief Measures the direction between two points.
         /// @image html Images/Direction.jpg
         /// @param fromID ID of the first point
         /// @param toID ID of the second point
         /// @return Direction of the line from the first to second point
         Direction MeasureDirection(IDType fromID, IDType toID) const;

         /// @brief Measures the distance and direction between two points.
         /// @image html Images/Direction.jpg
         /// @param fromID ID of the first point
         /// @param toID ID of the second point
         /// @return Returns a pair of the format (Distance,Direction). Distance between points. Direction of the line from the first to second point
         std::pair<Float64,Direction> ComputeInverse(IDType fromID, IDType toID) const;

         ///@}

         ///@name Locate
         ///@{

         /// @brief Locates a point by distance and angle
         /// @image html Images/ByDistAngle.jpg
         /// @param newPointID ID for storing the new point
         /// @param fromID ID of the first point
         /// @param toID ID of the second point
         /// @param distance Distance from the second point where the new point is located
         /// @param angle Angle from the line between the first and second point at which to locate the new point
         /// @param offset Offset from the line between the first and second point.
         /// @return True if successful
         bool LocateByDistanceAndAngle(IDType newPointID, IDType fromID, IDType toID, Float64 distance, const Angle& angle, Float64 offset);

         /// @brief Locates a point by distance and deflection angle
         /// @image html Images/ByDistDefAngle.jpg
         /// @param newPointID ID for storing the new point
         /// @param fromID ID of the first point
         /// @param toID ID of the second point
         /// @param distance Distance from the second point where the new point is located
         /// @param defAngle Deflection angle the line between the first and second point at which to locate the point
         /// @param offset Offset from the line between the first and second point.
         /// @return True if successful
         bool LocateByDistanceAndDeflectionAngle(IDType newPointID, IDType fromID, IDType toID, Float64 distance, const Angle& defAngle, Float64 offset);

         /// @brief Locates a point by distance and direction
         /// @image html Images/ByDistDir.jpg
         /// @param newPointID ID for storing the new point
         /// @param fromID ID of the point the new point is located from
         /// @param distance Distance from the point to the new point
         /// @param direction Direction at which to locate the point
         /// @param offset Offset from the line defined by the point and direction
         /// @return True if successful
         bool LocateByDistanceAndDirection(IDType newPointID, IDType fromID, Float64 distance, const Direction& direction, Float64 offset);

         /// @brief Locates a point on a line
         /// @image html Images/PointOnLine.jpg
         /// @param newPointID ID for storing the new point
         /// @param fromID ID of the point the new point is located from
         /// @param toID ID of the second point
         /// @param distance Distance from the first point to the new point. If a negative value is used, the new point will be located before the start point.
         /// @param offset Offset from the line between the first and second point to the new point.
         /// @return True if successful
         bool LocatePointOnLine(IDType newPointID, IDType fromID, IDType toID, Float64 distance, Float64 offset);

         /// @brief Locates a line parallel to a line defined by two points.
         /// @image html Images/ParallelLineByPoints.jpg
         /// @param newFromID ID for storing the new line start point
         /// @param newToID ID for storing the new line end point
         /// @param fromID ID of the start point of the line
         /// @param toID ID of the end point of the line
         /// @param offset Offset from the source line to the new line.
         /// @return True if successful
         bool LocateParallelLineByPoints(IDType newFromID, IDType newToID, IDType fromID, IDType toID, Float64 offset);

         /// @brief Locates a parallel line segment.
         /// @image html Images/ParallelLineSegment.jpg
         /// @param newSegmentID ID for storing the new line
         /// @param newFromID ID for storing the start point for the new line segment
         /// @param newToID ID for storing the end point for the new line segment
         /// @param segmentID ID of the source line segment
         /// @param offset Offset from the source line segment
         bool LocateParallelLineSegment(IDType newSegmentID, IDType newFromID, IDType newToID, IDType segmentID, Float64 offset);

         ///@}

         ///@name Intersect
         ///@{

         /// @brief Intersects two lines defined by point and direction.
         /// @image html Images/Bearings.jpg
         /// @param newID ID for storing the new point
         /// @param id1 ID of a point on the first line
         /// @param dir1 Direction of the first line
         /// @param offset1 Offset from the first line
         /// @param id2 ID of a point on the second line
         /// @param dir2 Direction of the second line
         /// @param offset2 Offset from the second line
         /// @return True if successful
         bool IntersectBearings(IDType newID, IDType id1, const Direction& dir1, Float64 offset1, IDType id2, const Direction& dir2, Float64 offset2);

         /// @brief Intersects a line defined by a point and direction with a circle.
         /// @image html Images/BearingCircle.jpg
         /// @param newID ID for storing the new point
         /// @param startID ID of a point on the line
         /// @param dir Direction of the line
         /// @param offset Offset from the line
         /// @param centerID ID of the circle center point 
         /// @param radius Circle radius
         /// @param nearestID ID of a point that will be nearest the solution point in the event two intersection points are found
         /// @return True if successful
         bool IntersectBearingAndCircle(IDType newID, IDType startID, const Direction& dir, Float64 offset, IDType centerID, Float64 radius, IDType nearestID);

         /// @brief Intersects two circles
         /// @image html Images/Circles.jpg
         /// @param newID ID for storing the new point
         /// @param centerID1 ID of the first circle center point
         /// @param radius1 Radius of the first circle
         /// @param centerID2 ID of the second circle center point
         /// @param radius2 Radius of the second circle
         /// @param nearestID ID of a point that will be nearest the solution point in the event two intersection points are found 
         /// @return True if successful
         bool IntersectCircles(IDType newID, IDType centerID1, Float64 radius1, IDType centerID2, Float64 radius2, IDType nearestID);

         /// @brief Intersects a line defined by two points with a circle.
         /// @image html Images/LineByPointsCircle.jpg
         /// @param newID ID for storing the new point
         /// @param startID ID of first point on the line
         /// @param endID ID of the second point on the line
         /// @param offset Offset from the line
         /// @param centerID ID of the circle center point
         /// @param radius Circle radius
         /// @param nearestID ID of a point that will be nearest the solution point in the event two intersection points are found 
         /// @return True if successful
         bool IntersectLineByPointsAndCircle(IDType newID, IDType startID, IDType endID, Float64 offset, IDType centerID, Float64 radius, IDType nearestID);

         /// @brief Intersects two lines defined by points.
         /// @image html Images/LinesByPoints.jpg
         /// @param newID ID for storing the new point
         /// @param startID1 ID of first point through which the first line passes
         /// @param endID1 ID of second point through which the first line passes
         /// @param offset1 Offset from first line
         /// @param startID2 ID of first point through which the second line passes
         /// @param endID2 ID of second point through which the second line passes
         /// @param offset2 Offset from second line
         /// @return True if successful
         bool IntersectLinesByPoints(IDType newID, IDType startID1, IDType endID1, Float64 offset1, IDType startID2, IDType endID2, Float64 offset2);

         /// @brief Intersects two line segments.
         /// @image html Images/Lines.jpg
         /// @param newID ID for storing the new point
         /// @param lsID1 ID of first line segment
         /// @param offset1 Offset from first line segment
         /// @param lsID2 ID of second line segment
         /// @param offset2 Offset from second line segment
         /// @return True if successful
         bool IntersectPathSegments(IDType newID, IDType lsID1, Float64 offset1, IDType lsID2, Float64 offset2);

         /// @brief Intersects a line segment and a circle
         /// @image html Images/LineSegmentCircle.jpg
         /// @param newID ID for storing the new point
         /// @param lsID ID of the line segment
         /// @param offset Offset from the line segment
         /// @param centerID ID of the circle center point
         /// @param radius Circle radius
         /// @param nearestID ID of a point that will be nearest the solution point in the event two intersection points are found 
         /// @return True if successful
         bool IntersectPathSegmentAndCircle(IDType newID, IDType lsID, Float64 offset, IDType centerID, Float64 radius, IDType nearestID);

         ///@}

         ///@name Project
         ///@{

         /// @brief Project a point onto a compound curve
         /// @param newID ID for storing the new point
         /// @param fromID The point to project
         /// @param curveID ID of the curve
         /// @return True if successful
         bool ProjectPointOnCompoundCurve(IDType newID, IDType fromID, IDType curveID);

         /// @brief Project a point onto a transition curve
         /// @param newID ID for storing the new point
         /// @param fromID The point to project
         /// @param curveID ID of the curve
         /// @return True if successful
         bool ProjectPointOnTransitionCurve(IDType newID, IDType fromID, IDType curveID);

         /// @brief Project a point onto a circular curve
         /// @param newID ID for storing the new point
         /// @param fromID The point to project
         /// @param curveID ID of the curve
         /// @return True if successful
         bool ProjectPointOnCircularCurve(IDType newID, IDType fromID, IDType curveID);

         /// @brief Project a point onto a path
         /// @param newID ID for storing the new point
         /// @param fromID The point to project
         /// @param pathID ID of the path
         /// @return True if successful
         bool ProjectPointOnPath(IDType newID, IDType fromID, IDType pathID);

         /// @brief Project a point onto an alignment
         /// @param newID ID for storing the new point
         /// @param fromID The point to project
         /// @param alignmentID ID of the alignment
         /// @return True if successful
         bool ProjectPointOnAlignment(IDType newID, IDType fromID, IDType alignmentID);

         /// @brief Projects a point onto a line defined by two points.
         /// @image html Images/PointOnLineByPoints.jpg
         /// @param newID ID for storing the new point
         /// @param fromID The point to project 
         /// @param startID First point on the line
         /// @param endID Second point on the line
         /// @param offset Offset from the line
         /// @return  True if successful
         bool ProjectPointOnLineByPoints(IDType newID, IDType fromID, IDType startID, IDType endID, Float64 offset);

         /// @brief Projects a point onto a line segment.
         /// @image html Images/PointOnLneSegment.jpg
         /// @param newID ID for storing the new point
         /// @param fromID ID of the point to be projected
         /// @param lsID ID of the line segment
         /// @param offset Offset from the line segment
         /// @return True if successful
         bool ProjectPointOnPathSegment(IDType newID, IDType fromID, IDType lsID, Float64 offset);

         ///@}

         ///@name Divide
         ///@{

         /// @brief Divides an arc into nPart equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param fromID Start point of the arc
         /// @param vertexID Vertex point of the arc 
         /// @param toID End point of the arc
         /// @param nParts Number of equal length parts
         /// @return True if successful
         bool DivideArc(IDType firstID, IDType idInc, IDType fromID, IDType vertexID, IDType toID, IndexType nParts);

         /// @brief Divides the line segment between two points in nParts equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param fromID Start point of the line segment
         /// @param toID End point of the line segment
         /// @param nParts Number of equal length parts
         /// @return True if successful
         bool DivideBetweenPoints(IDType firstID, IDType idInc, IDType fromID, IDType toID, IndexType nParts);

         /// @brief Divides a stored line segment into nParts equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param lsID ID of the line segment to divide
         /// @param nParts Number of equal length parts
         /// @return True if successful
         bool DivideLineSegment(IDType firstID, IDType idInc, IDType lsID, IndexType nParts);

         /// @brief Divides a stored compound curve into nParts equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param curveID ID of the curve to divide
         /// @param nParts Number of equal length parts
         /// @return True if successful
         bool DivideCompoundCurve(IDType firstID, IDType idInc, IDType curveID, IndexType nParts);

         /// @brief Divides a stored transition curve into nParts equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param curveID ID of the curve to divide
         /// @param nParts Number of equal length parts
         /// @return True if successful
         bool DivideTransitionCurve(IDType firstID, IDType idInc, IDType curveID, IndexType nParts);
         
         /// @brief Divides a stored circular curve into nParts equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param curveID ID of the curve to divide
         /// @param nParts Number of equal length parts
         /// @return True if successful
         bool DivideCircularCurve(IDType firstID, IDType idInc, IDType curveID, IndexType nParts);

         /// @brief Divides a stored path into nParts equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param pathID ID of the path to divide
         /// @param nParts Number of equal length parts
         /// @param start Distance from the start of the path where the division begins
         /// @param end Distance from the start of the path where the division ends
         /// @return True if successful
         bool DividePath(IDType firstID, IDType idInc, IDType pathID, IndexType nParts, Float64 start, Float64 end);

         
         /// @brief Divides a stored alignment into nParts equal length parts
         /// @param firstID ID of the first stored point
         /// @param idInc Point ID increment
         /// @param alignmentID ID of the alignment to divide
         /// @param nParts Number of equal length parts
         /// @param start Station where the division begins
         /// @param end Station where the division ends
         /// @return True if successful
         bool DivideAlignment(IDType firstID, IDType idInc, IDType alignmentID, IndexType nParts, const Station& start, const Station& end);

         ///@}

         ///@name Tangent
         ///@{
         
         /// @brief Locates points tangent to two circles where the tangent lines cross between circles.
         /// If sign is CW then the points indicated in the figure are located. If sign is CCW, then the tangent points on the opposite tangent are located.
         /// @image html Images/Cross.gif
         /// @param newID1 ID of the new point on the first circle
         /// @param centerID1 ID of the second circle center point
         /// @param radius1 First circle radius
         /// @param newID2 ID of the second circle center point
         /// @param centerID2 ID of the second circle center point
         /// @param radius2 Second circle radius
         /// @param sign Indicates which of the two tangent lines to use to locate the tangent points
         /// @return True if successful
         bool CrossingTangents(IDType newID1, IDType centerID1, Float64 radius1, IDType newID2, IDType centerID2, Float64 radius2,TangentSign sign);

         /// @brief Locates points tangent to two circles where the tangent lines are external to the circles.
         /// If sign is CW then the points indicated in the figure are located. If sign is CCW, then the tangent points on the opposite tangent are located.
         /// @image html Images/External.gif
         /// @param newID1 ID of the new point on the first circle
         /// @param centerID1 ID of the second circle center point
         /// @param radius1 First circle radius
         /// @param newID2 ID of the second circle center point
         /// @param centerID2 ID of the second circle center point
         /// @param radius2 Second circle radius
         /// @param sign Indicates which of the two tangent lines to use to locate the tangent points
         /// @return True if successful
         bool ExternalTangents(IDType newID1, IDType centerID1, Float64 radius1, IDType newID2, IDType centerID2, Float64 radius2, TangentSign sign);

         /// @brief Locates point tangent to a circle.
         /// If sigh is CW then the points indicated in the figure are located. If sign is CCW, then the tangent points on the opposite tangent are located.
         /// @image html Images/Point.gif
         /// @param newID ID of the new point
         /// @param centerID ID of the circle center point
         /// @param radius Circle radius
         /// @param pointID ID of the point forming a line passing through the circle center point
         /// @param sign Indicates which of the two tangent lines to use to locate the tangent points
         /// @return True if successful
         bool TangentPoint(IDType newID, IDType centerID, Float64 radius, IDType pointID, TangentSign sign);

         ///@}

      private:
         // Storage of basic model items
         // The map key is the ID of the item begin stored (eg, point ID, segment ID, etc).
         std::map<IDType, WBFL::Geometry::Point2d> m_Points;
         std::map<IDType, PathSegmentDefinition> m_Segments;
         std::map<IDType, CompoundCurveDefinition> m_CompoundCurves;
         std::map<IDType, CircularCurveDefinition> m_CircularCurves;
         std::map<IDType, TransitionCurveDefinition> m_TransitionCurves;
         std::map<IDType, std::vector<IDType>> m_CubicSplines; // vector holds point IDs for the points making up the spline
         std::map<IDType, std::vector<PathElementDefinition>> m_Alignments;
         std::map<IDType, std::vector<PathElementDefinition>> m_Paths;
         std::map<IDType, ProfilePoint> m_ProfilePoints;
         std::map<IDType, ProfileSegmentDefinition> m_ProfileSegments;
         std::map<IDType, VerticalCurveDefinition> m_VerticalCurves;
         std::map<IDType, std::vector<std::pair<ProfileElementType, IDType>>> m_Profiles;

         // Storage of surfaces, surface templates, and surface modifiers
         // The map key is the ID of the surface the information is related to
         std::map<IDType, SurfaceDefinition> m_Surfaces;
         std::map<IDType, std::vector<SurfaceTemplateDefinition>> m_SurfaceTemplates;
         std::map<IDType, std::vector<SuperelevationDefinition>> m_Superelevations;
         std::map<IDType, std::vector<WideningDefinition>> m_Widenings;


         std::map<IDType, IDType> m_ProfileAlignmentAssociations;// key is profile ID, value is alignment ID for the associated alignment (profiles can only be assigned to one alignment)
         std::map<IDType, IDType> m_SurfaceProfileAssociations; // key is surfaceID, value is profileID

         std::map<IDType, Station> m_AlignmentReferenceStations; // key is alignment ID
         std::map<IDType, std::vector<StationEquationDefinition>> m_StationEquations; // pair is back, ahead

         // Stores all provided points. If any point storage fails, rolls back any points there were stored
         bool AtomicStorePoints(std::vector<std::pair<IDType, WBFL::Geometry::Point2d>>& points);

         std::shared_ptr<Profile> CreateProfile(IDType profileID,std::shared_ptr<Alignment> alignment) const;
         const ProfilePoint& GetStartProfilePoint(const std::pair<ProfileElementType, IDType>& elementData) const;
         WBFL::Geometry::Point2d GetStartPathPoint(const std::pair<PathElementType, IDType>& elementData) const;

         std::shared_ptr<Surface> CreateSurface(IDType surfaceID, std::shared_ptr<Profile> profile) const;

         template <class C> bool RemoveItem(C& container,IDType id);
         template <class C, class P> void CreatePath(IDType id, const C& container, std::shared_ptr<P> path) const;
      };
   };
};
