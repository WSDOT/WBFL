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
#include "SuperelevationImpl.h"
#include <CoordGeom/Station.h>
#include <CoordGeom/Superelevation.h>
#include <array>

namespace WBFL
{
   namespace COGO
   {
      class SuperelevationImpl
      {
      public:
         SuperelevationImpl() = default;
         SuperelevationImpl(const SuperelevationImpl&) = default;
         SuperelevationImpl& operator=(const SuperelevationImpl&) = delete;
         SuperelevationImpl(const Station& beginTrasitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTrasitionStation, Float64 rate, IndexType pivotPointIdx,
            Superelevation::TransitionType beginTransitionType = Superelevation::TransitionType::Linear, Float64 beginL1 = 0.0, Float64 beginL2 = 0.0, Superelevation::TransitionType endTransitionType = Superelevation::TransitionType::Linear, Float64 endL1 = 0.0, Float64 endL2 = 0.0);
         ~SuperelevationImpl() = default;

         void SetSurface(std::weak_ptr<const Surface> surface);
         std::shared_ptr<const Surface> GetSurface() const;
         
         void Init(const Station& beginTrasitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTrasitionStation, Float64 rate, IndexType pivotPointIdx, 
            Superelevation::TransitionType beginTransitionType = Superelevation::TransitionType::Linear, Float64 beginL1=0.0, Float64 beginL2=0.0, Superelevation::TransitionType endTransitionType= Superelevation::TransitionType::Linear, Float64 endL1=0.0, Float64 endL2=0.0);

         void SetBeginTransition(const Station& beginTrasitionStation);
         const Station& GetBeginTransition() const;

         void SetBeginFullSuperelevation(const Station& beginFullSuperStation);
         const Station& GetBeginFullSuperelevation() const;

         void SetEndFullSuperelevation(const Station& endFullSuperStation);
         const Station& GetEndFullSuperelevation() const;

         void SetEndTransition(const Station& endTrasitionStation);
         const Station& GetEndTransition() const;

         void SetRate(Float64 rate);
         Float64 GetRate() const;

         void SetPivotPoint(IndexType pivotPointIdx);
         IndexType GetPivotPoint() const;

         void SetBeginTransitionType(Superelevation::TransitionType type);
         Superelevation::TransitionType GetBeginTransitionType() const;

         void SetBeginTransitionParameters(Float64 l1, Float64 l2);
         std::pair<Float64, Float64> GetBeginTransitionParameters() const;

         void SetEndTransitionType(Superelevation::TransitionType type);
         Superelevation::TransitionType GetEndTransitionType() const;

         void SetEndTransitionParameters(Float64 l1, Float64 l2);
         std::pair<Float64, Float64> GetEndTransitionParameters() const;

         Float64 GetSlope(const Station& station, Float64 templateSlope) const;

      private:
         std::weak_ptr<const Surface> m_Surface;
         Station m_BeginTransition;
         Station m_BeginFullSuper;
         Station m_EndFullSuper;
         Station m_EndTransition;
         Float64 m_Rate = 0.0;
         IndexType m_PivotPoint = 0;
         Superelevation::TransitionType m_BeginTransitionType = Superelevation::TransitionType::Linear;
         Superelevation::TransitionType m_EndTransitionType = Superelevation::TransitionType::Linear;
         std::array<Float64, 2> m_BeginTransitionLength{0.0,0.0}; // L1, L2
         std::array<Float64, 2> m_EndTransitionLength{ 0.0,0.0 }; // L1, L2

         Float64 ComputeSlopeInBeginTransition(const Station& station, Float64 templateSlope) const;
         Float64 ComputeSlopeInEndTransition(const Station& station, Float64 templateSlope) const;
         Float64 ComputeSlopeInTransition(const Station& station, const Station& startTransition, const Station& endTransition, Superelevation::TransitionType transitionType, Float64 L1, Float64 L2, Float64 startSlope, Float64 endSlope) const;

         std::shared_ptr<const Alignment> GetAlignment() const;
      };
   };
};
