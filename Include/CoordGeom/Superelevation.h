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
#include <memory>

namespace WBFL
{
   namespace COGO
   {
      class Surface; // forward declaration
      class SuperelevationImpl;

      /// @brief An Alignment modifier for a superelevation transition as would typically occur at a horizontal curve
      /// A Superelevation is defined by its limits, transitions, rate, and pivot point.
      /// Superelevation transitions can be linear or parabolic
      /// @image html Images/Superelevation.png
      class COORDGEOMCLASS Superelevation : public std::enable_shared_from_this<Superelevation>
      {
      public:
         /// @brief Constant defining the type of superelevation transition
         enum class TransitionType
         {
            Linear,    ///< Superelevation transition is linear
            Parabolic  ///< Superelevation transition is parabolic
         };

      private:
         Superelevation();
         Superelevation(const Superelevation& superelevation);
         Superelevation& operator=(const Superelevation&) = delete;

         void SetSurface(std::weak_ptr<const Surface> surface);
         friend Surface;

      public:
         /// @brief Creates a new Superelevation
         /// @return 
         static std::shared_ptr<Superelevation> Create();
         static std::shared_ptr<Superelevation> Create(const Superelevation& superelevation);

         /// @brief Creates a new Superelevation
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
         /// @return 
         static std::shared_ptr<Superelevation> Create(const Station& beginTransitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTransitionStation, Float64 rate, IndexType pivotPointIdx, 
            TransitionType beginTransitionType = TransitionType::Linear, Float64 beginL1 = 0.0, Float64 beginL2 = 0.0, TransitionType endTransitionType = TransitionType::Linear, Float64 endL1 = 0.0, Float64 endL2 = 0.0);

         ~Superelevation();

         /// @brief Returns the Surface that is modified
         /// @return 
         std::shared_ptr<const Surface> GetSurface() const;
         
         /// @brief Initialize the superelefation
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
         void Init(const Station& beginTransitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTransitionStation, Float64 rate, IndexType pivotPointIdx,
            TransitionType beginTransitionType = TransitionType::Linear, Float64 beginL1=0.0, Float64 beginL2=0.0, TransitionType endTransitionType=TransitionType::Linear, Float64 endL1=0.0, Float64 endL2=0.0);

         /// @brief Sets the location of the beginning transition point
         /// @param beginTrasitionStation 
         void SetBeginTransition(const Station& beginTrasitionStation);

         /// @brief Returns the location of the beginning transition point
         /// @return 
         const Station& GetBeginTransition() const;

         /// @brief Sets the location of the beginning of full superelevation
         /// @param beginFullSuperStation 
         void SetBeginFullSuperelevation(const Station& beginFullSuperStation);

         /// @brief Returns the location of the beginning of full superelevation
         /// @return 
         const Station& GetBeginFullSuperelevation() const;

         /// @brief Sets the location of the end of full superelevation
         /// @param endFullSuperStation 
         void SetEndFullSuperelevation(const Station& endFullSuperStation);

         /// @brief Returns the location of the end of full superelevation
         /// @return 
         const Station& GetEndFullSuperelevation() const;

         /// @brief Sets the location of the ending transition point
         /// @param endTrasitionStation 
         void SetEndTransition(const Station& endTrasitionStation);

         /// @brief Returns the location of the ending transition point
         /// @return 
         const Station& GetEndTransition() const;

         /// @brief Sets the superelevation rate (cross slope). 
         /// @param rate Positive values indicates the roadway slopes upwards from left to right.
         void SetRate(Float64 rate);

         /// @brief Returns the supelevation rate
         /// @return 
         Float64 GetRate() const;

         /// @brief Ridge point index that the superelevation pivot occurs about.
         /// @param pivotPointIdx 
         void SetPivotPoint(IndexType pivotPointIdx);

         /// @brief Ridge point index that the superelevation pivot occurs about.
         /// @return 
         IndexType GetPivotPoint() const;

         /// @brief Type of transition at the beginning of the curve
         /// @param type 
         void SetBeginTransitionType(TransitionType type);

         /// @brief Type of transition at the beginning of the curve
         /// @return 
         TransitionType GetBeginTransitionType() const;

         /// @brief Beginning transition parameters
         /// @param l1 Length of the parabola at the beginning of the transition
         /// @param l2 Length of the parabola at the beginning of full superelevation
         void SetBeginTransitionParameters(Float64 l1, Float64 l2);

         /// @brief Beginning transition parameters
         /// @return A pair in the format (L1,L2)
         std::pair<Float64,Float64> GetBeginTransitionParameters() const;

         /// @brief Type of transition at the end of the curve
         /// @param type 
         void SetEndTransitionType(TransitionType type);

         /// @brief Type of transition at the end of the curve
         TransitionType GetEndTransitionType() const;

         /// @brief Ending transition parameters
         /// @param l1 Length of the parabola at the end of full superelevation
         /// @param l2 Length of the parabola at the end of the transition
         void SetEndTransitionParameters(Float64 l1, Float64 l2);

         /// @brief Ending transition parameters
         /// @return A pair in the format (L1,L2)
         std::pair<Float64,Float64> GetEndTransitionParameters() const;

         /// @brief Computes the slope at the specified station
         /// @param station The station where the slope is computed
         /// @param templateSlope The basic slope from the SurfaceTemplate before superelevation transitions are applied.
         /// @return The roadway cross slope
         Float64 GetSlope(const Station& station, Float64 templateSlope) const;


#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         std::unique_ptr<SuperelevationImpl> m_pImpl;
      };
   };
};
