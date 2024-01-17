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

#include <CoordGeom/CoordGeomLib.h>
#include "SuperelevationImpl.h"

#include <CoordGeom/Surface.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

using namespace WBFL::COGO;

SuperelevationImpl::SuperelevationImpl(const Station& beginTrasitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTransitionStation,
   Float64 rate, IndexType pivotPointIdx, Superelevation::TransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, Superelevation::TransitionType endTransitionType, Float64 endL1, Float64 endL2)
{
   Init(beginTrasitionStation, beginFullSuperStation, endFullSuperStation, endTransitionStation, rate, pivotPointIdx, beginTransitionType, beginL1, beginL2, endTransitionType, endL1, endL2);
}

void SuperelevationImpl::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_Surface = surface;
}

std::shared_ptr<const Surface> SuperelevationImpl::GetSurface() const
{
   return m_Surface.lock();
}

void SuperelevationImpl::Init(const Station& beginTrasitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTransitionStation,
   Float64 rate, IndexType pivotPointIdx, Superelevation::TransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, Superelevation::TransitionType endTransitionType, Float64 endL1, Float64 endL2)
{
   m_BeginTransition = beginTrasitionStation;
   m_BeginFullSuper = beginFullSuperStation;
   m_EndFullSuper = endFullSuperStation;
   m_EndTransition = endTransitionStation;
   m_Rate = rate;
   m_PivotPoint = pivotPointIdx;
   m_BeginTransitionType = beginTransitionType;
   m_EndTransitionType = endTransitionType;
   m_BeginTransitionLength[0] = beginL1;
   m_BeginTransitionLength[1] = beginL2;
   m_EndTransitionLength[0] = endL1;
   m_EndTransitionLength[1] = endL2;
}

void SuperelevationImpl::SetBeginTransition(const Station& beginTrasitionStation)
{
   m_BeginTransition = beginTrasitionStation;
}

const Station& SuperelevationImpl::GetBeginTransition() const
{
   return m_BeginTransition;
}

void SuperelevationImpl::SetBeginFullSuperelevation(const Station& beginFullSuperStation)
{
   m_BeginFullSuper = beginFullSuperStation;
}

const Station& SuperelevationImpl::GetBeginFullSuperelevation() const
{
   return m_BeginFullSuper;
}

void SuperelevationImpl::SetEndFullSuperelevation(const Station& endFullSuperStation)
{
   m_EndFullSuper = endFullSuperStation;
}

const Station& SuperelevationImpl::GetEndFullSuperelevation() const
{
   return m_EndFullSuper;
}

void SuperelevationImpl::SetEndTransition(const Station& endTransitionStation)
{
   m_EndTransition = endTransitionStation;
}

const Station& SuperelevationImpl::GetEndTransition() const
{
   return m_EndTransition;
}

void SuperelevationImpl::SetRate(Float64 rate)
{
   m_Rate = rate;
}

Float64 SuperelevationImpl::GetRate() const
{
   return m_Rate;
}

void SuperelevationImpl::SetPivotPoint(IndexType pivotPointIdx)
{
   m_PivotPoint = pivotPointIdx;
}

IndexType SuperelevationImpl::GetPivotPoint() const
{
   return m_PivotPoint;
}

void SuperelevationImpl::SetBeginTransitionType(Superelevation::TransitionType type)
{
   m_BeginTransitionType = type;
}

Superelevation::TransitionType SuperelevationImpl::GetBeginTransitionType() const
{
   return m_BeginTransitionType;
}

void SuperelevationImpl::SetBeginTransitionParameters(Float64 l1, Float64 l2)
{
   m_BeginTransitionLength[0] = l1;
   m_BeginTransitionLength[1] = l2;
}

std::pair<Float64, Float64> SuperelevationImpl::GetBeginTransitionParameters() const
{
   return std::make_pair(m_BeginTransitionLength[0], m_BeginTransitionLength[1]);
}


void SuperelevationImpl::SetEndTransitionType(Superelevation::TransitionType type)
{
   m_EndTransitionType = type;
}

Superelevation::TransitionType SuperelevationImpl::GetEndTransitionType() const
{
   return m_EndTransitionType;
}

void SuperelevationImpl::SetEndTransitionParameters(Float64 l1, Float64 l2)
{
   m_EndTransitionLength[0] = l1;
   m_EndTransitionLength[1] = l2;
}

std::pair<Float64, Float64> SuperelevationImpl::GetEndTransitionParameters() const
{
   return std::make_pair(m_EndTransitionLength[0], m_EndTransitionLength[1]);
}

Float64 SuperelevationImpl::GetSlope(const Station& station, Float64 templateSlope) const
{
   // adjusts the specified template slope with the superelevation

   auto alignment = GetAlignment();

   Float64 slope = 0;
   if (0 < COGO::CompareStations(alignment, station, m_BeginTransition) ||
       0 < COGO::CompareStations(alignment, m_EndTransition, station))
   {
      // station is not in the supertransition area
      slope = templateSlope;
   }
   else if (0 <= COGO::CompareStations(alignment, m_BeginTransition,station) &&
            0 <= COGO::CompareStations(alignment, station,m_BeginFullSuper))
   {
      // In begin transition
      slope = ComputeSlopeInBeginTransition(station, templateSlope);
   }
   else if (0 <= COGO::CompareStations(alignment, m_EndFullSuper, station) &&
            0 <= COGO::CompareStations(alignment, station, m_EndTransition))
   {
      // In end transition
      slope = ComputeSlopeInEndTransition(station, templateSlope);
   }
   else
   {
      // In full super
      slope = m_Rate;
   }

   return slope;
}

Float64 SuperelevationImpl::ComputeSlopeInBeginTransition(const Station& station, Float64 templateSlope) const
{
   return ComputeSlopeInTransition(station, m_BeginTransition, m_BeginFullSuper, m_BeginTransitionType, m_BeginTransitionLength[0], m_BeginTransitionLength[1], templateSlope, m_Rate);
}

Float64 SuperelevationImpl::ComputeSlopeInEndTransition(const Station& station, Float64 templateSlope) const
{
   return ComputeSlopeInTransition(station, m_EndFullSuper, m_EndTransition, m_EndTransitionType, m_EndTransitionLength[0], m_EndTransitionLength[1], m_Rate, templateSlope);
}

Float64 SuperelevationImpl::ComputeSlopeInTransition(const Station& station, const Station& startTransition, const Station& endTransition, Superelevation::TransitionType transitionType, Float64 L1, Float64 L2, Float64 startSlope, Float64 endSlope) const
{
   auto alignment = GetAlignment();

   Float64 sta   = COGO::ConvertToNormalizedStation(alignment, station);
   Float64 start = COGO::ConvertToNormalizedStation(alignment, startTransition);
   Float64 end   = COGO::ConvertToNormalizedStation(alignment, endTransition);

   Float64 slope = 0.0;
   if (IsEqual(start, end))
   {
      slope = endSlope;
   }
   else if (transitionType == Superelevation::TransitionType::Linear)
   {
      slope = ::LinInterp(sta - start, startSlope, endSlope, end - start);
   }
   else if (transitionType == Superelevation::TransitionType::Parabolic)
   {
      Float64 L3 = end - start - L1 - L2;
      L3 = IsZero(L3) ? 0 : L3;
      if (L3 < 0)
      {
         THROW_COGO(WBFL_COGO_E_SUPERTRANSITIONERROR);
      }

      Float64 x = sta - start; // distance into transition zone
      Float64 K = IsZero(L1) && IsZero(L2) ? 0 : (endSlope - startSlope) / (L1 * L1 + 2 * L1 * L3 + L1 * L2);
      if (x < L1)
      {
         // first parabola
         slope = K * x * x + startSlope;
      }
      else if (x < (L1 + L3))
      {
         // linear section
         Float64 Ya = K * L1 * L1 + startSlope; // slope at end of first parabola
         Float64 Yb = -L1 * L2 * K + endSlope;  // slope at start of second parabola
         slope = ::LinInterp(x - L1, Ya, Yb, L3);
      }
      else
      {
         // second parabola
         Float64 x2 = x - L1 - L3;
         slope = -L1 * K * x2 * x2 / L2 + 2 * L1 * K * x2 - L1 * L2 * K + endSlope;
      }
   }
   else
   {
      CHECK(false); // is there a new transition type?
   }

   return slope;
}

std::shared_ptr<const Alignment> SuperelevationImpl::GetAlignment() const
{
   auto surface = GetSurface();
   auto profile = (surface ? surface->GetProfile() : nullptr);
   auto alignment = (profile ? profile->GetAlignment() : nullptr);
   return alignment;
}
